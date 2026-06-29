from scripts.linter.decorators import step
from scripts.linter.utils import index_lfirst_neq, log


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
