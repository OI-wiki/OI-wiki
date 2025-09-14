import re

from scripts.linter.decorators import step
from scripts.linter.utils import index_lfirst_neq, log
from scripts.linter.dfa import markdown_state, next_state


@step
def fix_details(md_content: str, **kwargs):
    """
    Fix indentation issues in Markdown content.

    This function corrects inconsistent indentation in nested Markdown structures,
    particularly for collapse blocks. It uses a bidirectional scanning approach to
    determine proper indentation levels.

    see also:
    - <https://oi-wiki.org/intro/format/#LINT-6>
    - <https://oi-wiki.org/intro/format/#MDFM-6>

    Args:
        md_content: The Markdown content to process
        **kwargs: Additional arguments including 'line_origins' for tracking

    Returns:
        str: The processed Markdown content with corrected indentation
    """
    line_origins: list[int] = kwargs.get('line_origins')  # type: ignore
    lines: list[str] = md_content.splitlines()

    size = len(lines)
    log(f"Processing {size} lines for indentation fixes")

    # Calculate maximum possible indent (used as sentinel value)
    MAX_INDENT = max(len(line) for line in lines)+1
    log(f"Maximum indent calculated: {MAX_INDENT}")

    # Identify non-blank lines (lines with actual content)
    non_blank = [i != -1 and len(line.strip()) > 0
                 for i, line in zip(line_origins, lines)]
    non_blank_count = sum(non_blank)
    log(f"Found {non_blank_count} non-blank lines out of {size} total lines")

    # Calculate current indentation levels
    pre_indents = [index_lfirst_neq(line, ' ') if line.strip() else 0
                   for line in lines]
    # Show first 5
    log(f"Calculated initial indentation levels: {pre_indents[:5]}...")

    # Initialize new indentation levels
    now_indents = [i if flag else MAX_INDENT for i,
                   flag in zip(pre_indents, non_blank)]

    # Forward pass: propagate indentation from content lines to blank lines
    log("Starting forward pass for indentation propagation")
    past_indent = MAX_INDENT
    changes_forward = 0

    for index in filter(lambda i: line_origins[i] != -1, range(size)):
        if non_blank[index]:
            past_indent = now_indents[index]
        else:
            old_indent = now_indents[index]
            now_indents[index] = min(now_indents[index], past_indent)
            if old_indent != now_indents[index]:
                changes_forward += 1

    log(f"Forward pass completed: {changes_forward} indentations adjusted")

    # Backward pass: propagate indentation from content lines to blank lines
    log("Starting backward pass for indentation propagation")
    past_indent = MAX_INDENT
    changes_backward = 0

    for index in filter(lambda i: line_origins[i] != -1, reversed(range(size))):
        if non_blank[index]:
            past_indent = now_indents[index]
        else:
            old_indent = now_indents[index]
            now_indents[index] = min(now_indents[index], past_indent)
            if old_indent != now_indents[index]:
                changes_backward += 1

    log(f"Backward pass completed: {changes_backward} indentations adjusted")

    # Reset MAX_INDENT sentinel values to 0 (no indentation)
    log("Resetting sentinel indentation values")
    sentinel_resets = 0
    for index in filter(lambda i: line_origins[i] != -1, range(size)):
        if now_indents[index] == MAX_INDENT:
            now_indents[index] = 0
            sentinel_resets += 1

    log(f"Reset {sentinel_resets} sentinel indentation values to 0")

    # Apply indentation changes
    log("Applying indentation changes to lines")
    total_changes = 0

    for index in filter(lambda i: line_origins[i] != -1, range(size)):
        if pre_indents[index] != now_indents[index]:
            original_line_num = line_origins[index] + 1  # Convert to 1-based
            log(
                f"line {original_line_num}: old indent = {pre_indents[index]}, new indent = {now_indents[index]}")
            lines[index] = ' '*now_indents[index] + lines[index].lstrip()
            total_changes += 1

    log(f"Indentation fix completed: {total_changes} lines modified")
    result = '\n'.join(lines) + '\n'
    log(f"Final result: {len(result)} characters")

    return result


@step
def fix_punctuations(md_content: str, skipped_codeblock_lang: list[str] = ['tex', 'text', 'plain'], **kwargs):
    r"""
    Fix punctuation issues after inline math formula.

    This function corrects common punctuation issues after inline math formula,
    including periods, commas, and other symbols.

    Some expected behavior:

    1.
    $a_0$。$foo$,$bar$. baz。baz.
    ->
    $a_0$．$foo$，$bar$．baz．baz.

    2.
    $$
    \$foo\$,\$bar\$。\$baz\$.
    $$
    -> (keep unchanged)

    3.
    ```<lang>
    $foo$,$bar$。$baz$.
    ```
    - if lang in [tex, text, plain] -> (keep unchanged)
    - if lang not in [tex, text, plain]
    ->
    ```<lang>
    $foo$，$bar$．$baz$．
    ```

    Args:
        md_content: The Markdown content to process
        **kwargs: Additional arguments including 'line_origins' for tracking

    Returns:
        str: The processed Markdown content with corrected punctuations
    """
    # Replace English punctuation with Chinese punctuation
    PUNCTUATION_MAP = {
        '。': '．',
        ',': '，',
        '.': '．',
        ';': '；',
        ':': '：',
        '!': '！',
        '?': '？'
    }

    # (?P<formula>)(?P<punctuation>)?
    RE_INLINE_MATH_WITH_TRAILING_PUNCTUATION = re.compile(
        rf"(\$[^$]*?\$)(?:([{''.join(PUNCTUATION_MAP.keys())}]) ?)?")

    line_origins: list[int] = kwargs.get('line_origins', [])  # type: ignore
    lines = md_content.splitlines()

    log(f"Processing {len(lines)} lines for punctuation fixes")

    # Track changes for logging
    total_changes = 0

    current_state: markdown_state = markdown_state._begin
    end_mark: str = ''

    for i, line in enumerate(lines):
        if line_origins[i] == -1:
            # Skip placeholder lines (from skip blocks)
            continue

        ext_message = {
            'codeblock_end_mark': end_mark,
            'skipped_codeblock_lang': skipped_codeblock_lang
        }
        current_state, ext_message = next_state(
            current_state, line, **ext_message)
        end_mark = ext_message.get('codeblock_end_mark')  # type: ignore

        # Skip current line if should
        if current_state not in [markdown_state.normal_line, markdown_state.normal_code_block_content]:
            continue

        # Fix punctuation after inline math formulas
        modified_line = RE_INLINE_MATH_WITH_TRAILING_PUNCTUATION.sub(lambda match: match.group(
            1) + PUNCTUATION_MAP[match.group(2)] if match.group(2) else match.group(1), line)

        # Update line if changed
        if modified_line != line:
            lines[i] = modified_line
            total_changes += 1
            original_line_num = line_origins[i] + 1  # Convert to 1-based
            log(f"line {original_line_num}: punctuation fixes applied")

    log(f"Punctuation fix completed: {total_changes} lines modified")
    result = '\n'.join(lines) + '\n'
    log(f"Final result: {len(result)} characters")

    return result
