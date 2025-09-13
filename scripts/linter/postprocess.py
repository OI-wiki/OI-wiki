import re

from scripts.linter.dfa import markdown_state, next_state
from scripts.linter.utils import log
from scripts.linter.decorators import step


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
        ',': '，',
        '.': '．',
        ';': '；',
        ':': '：',
        '!': '！',
        '?': '？'
    }

    RE_INLINE_MATH_PATTERN = re.compile(
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

        current_state, ext_message = next_state(current_state, line,
                                                codeblock_end_mark=end_mark,
                                                skipped_codeblock_lang=skipped_codeblock_lang)
        end_mark = ext_message.get('codeblock_end_mark')  # type: ignore

        # Skip current line if should
        if current_state not in [markdown_state.normal_line, markdown_state.normal_code_block_content]:
            continue

        original_line = line
        modified_line = line

        # 1. Fix punctuation after inline math formulas
        modified_line = RE_INLINE_MATH_PATTERN.sub(lambda match: match.group(
            1) + PUNCTUATION_MAP[match.group(2)] if match.group(2) else match.group(1), modified_line)

        # 2. Replace "。" with "．"
        modified_line = modified_line.replace('。', '．')

        # Update line if changed
        if modified_line != original_line:
            lines[i] = modified_line
            total_changes += 1
            original_line_num = line_origins[i] + 1  # Convert to 1-based
            log(f"line {original_line_num}: punctuation fixes applied")

    log(f"Punctuation fix completed: {total_changes} lines modified")
    result = '\n'.join(lines) + '\n'
    log(f"Final result: {len(result)} characters")

    return result
