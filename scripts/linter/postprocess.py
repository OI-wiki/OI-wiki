from scripts.linter.decorators import step
from scripts.linter.utils import log
import re


@step
def fix_full_stop(md_content: str, **kwargs):
    r"""
    Fix full stop issues in Markdown content.
    This function only replace "。" with "．" in Markdown content.
    Args:
        md_content: The Markdown content to process
        **kwargs: Additional arguments including 'line_origins' for tracking
    Returns:
        str: The processed Markdown content with corrected punctuations
    """
    line_origins: list[int] = kwargs.get('line_origins', [])  # type: ignore
    lines = md_content.splitlines()

    log(f"Processing {len(lines)} lines for full stop fixes")

    # Track changes for logging
    total_changes = 0

    for i, line in enumerate(lines):
        if line_origins[i] == -1:
            # Skip placeholder lines (from skip blocks)
            continue

        modified_line = line.replace('。', '．')

        # Update line if changed
        if modified_line != line:
            lines[i] = modified_line
            total_changes += 1
            original_line_num = line_origins[i] + 1  # Convert to 1-based
            log(f"line {original_line_num}: full stop fixes applied")

    log(f"Fullstop fix completed: {total_changes} lines modified")
    result = '\n'.join(lines) + '\n'
    log(f"Final result: {len(result)} characters")

    return result


@step
def fix_quotation(md_content: str, **kwargs):
    r"""
    Fix quotation mark issues in Markdown content.
    This function replaces smart quotes with corner brackets:
    - Left single quote `‘` → `『`
    - Right single quote `’` → `』`
    - Left double quote `“` → `「`
    - Right double quote `”` → `」`

    Additionally, if `’` is adjacent to ASCII characters, then it will be detected as an apostrophe, which will be left unchanged.

    Args:
        md_content: The Markdown content to process
        **kwargs: Additional arguments including 'line_origins' for tracking

    Returns:
        str: The processed Markdown content with corrected quotation marks
    """
    line_origins: list[int] = kwargs.get('line_origins', [])  # type: ignore
    lines = md_content.splitlines()

    log(f"Processing {len(lines)} lines for quotes fixes")

    # Track changes for logging
    total_changes = 0

    for i, line in enumerate(lines):
        if line_origins[i] == -1:
            # Skip placeholder lines (from skip blocks)
            continue

        stack: list[str] = []  # only `“` and `‘`.

        def inner_replace(ln, col, char) -> str:
            nonlocal stack
            match char:
                case '“':
                    if stack and stack[-1] == '“':
                        log(f"extra left double quote detected, treating as right quote",
                            type=f'warning line={ln + 1},col={col + 1}')
                        return inner_replace(ln, col, '”')
                    stack.append('“')
                    return '「'
                case '”':
                    if not stack or stack[-1] == '‘':
                        log(f"extra right double quote detected, treating as left quote",
                            type=f'warning line={ln + 1},col={col + 1}')
                        return inner_replace(ln, col, '“')
                    if stack:
                        stack.pop()
                    return '」'
                case '‘':
                    if stack and stack[-1] == '‘':
                        log(f"extra left single quote detected, treating as right quote",
                            type=f'warning line={ln + 1},col={col + 1}')
                        return inner_replace(ln, col, '’')
                    stack.append('‘')
                    return '『'
                case '’':
                    nonlocal line
                    if len(line) > 1 and (line[col - 1].isascii() if col > 0 else True) and (line[col + 1].isascii() if col < len(line) - 1 else True):
                        # This is likely an apostrophe, not a quotation mark
                        return char
                    if not stack or stack[-1] == '“':
                        log(f"extra right single quote detected, treating as left quote",
                            type=f'warning line={ln + 1},col={col + 1}')
                        return inner_replace(ln, col, '‘')
                    if stack:
                        stack.pop()
                    return '』'
                case _:
                    return char

        modified_line = ""
        for j, char in enumerate(line):
            modified_line += inner_replace(line_origins[i], j, char)

        # Update line if changed
        if modified_line != line:
            lines[i] = modified_line
            total_changes += 1
            original_line_num = line_origins[i] + 1  # Convert to 1-based
            log(f"line {original_line_num}: quotation fixes applied")

    log(f"Quotes fix completed: {total_changes} lines modified")
    result = '\n'.join(lines) + '\n'
    log(f"Final result: {len(result)} characters")

    return result
