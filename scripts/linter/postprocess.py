import unicodedata

from scripts.linter.decorators import step
from scripts.linter.utils import log


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

    Additionally, if the previous character of a single quote is alnum-like, then it will be detected as an apostrophe, which will be preserved as `’`.

    This function also attempts to detect mismatched quotes and log warnings, treating them as the expected type based on the current stack of open quotes. For example, if a `”` is found but the last opened quote was `‘`, it will be treated as a `“` and a warning will be logged.

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

    stack: list[str] = []  # only `“` and `‘`.

    for i, line in enumerate(lines):
        if line_origins[i] == -1:
            # Skip placeholder lines (from skip blocks)
            continue

        def _quote_replace(ln, col, char) -> str:
            match char:
                case '“' | '”':
                    corrected = '”' if stack and stack[-1] == '“' else '“'
                    if char != corrected:
                        log(f"mismatched quote detected, treating as `{corrected}`",
                            type=f'warning line={ln + 1},col={col + 1}')
                    if corrected == '“':
                        stack.append(corrected)
                    else:
                        stack.pop()
                    return '「' if corrected == '“' else '」'
                case '‘' | '’':
                    if len(line) > 1 and (unicodedata.category(line[col-1]) in ('Ll', 'Lu', 'Lt', 'Lm', 'Nd', 'Nl') if col > 0 else False):
                        # Treat as apostrophe
                        if char == '‘':
                            log("`‘` as apostrophe detected, treating as `’`",
                                type=f'warning line={ln + 1},col={col + 1}')
                        return '’'
                    corrected = '’' if stack and stack[-1] == '‘' else '‘'
                    if char != corrected:
                        log(f"mismatched quote detected, treating as `{corrected}`",
                            type=f'warning line={ln + 1},col={col + 1}')
                    if corrected == '‘':
                        stack.append(corrected)
                    else:
                        stack.pop()
                    return '『' if corrected == '‘' else '』'
                case _:
                    return char

        modified_line = ''.join(_quote_replace(
            line_origins[i], j, char) for j, char in enumerate(line))

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
