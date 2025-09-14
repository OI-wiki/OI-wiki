

from scripts.linter.decorators import step
from scripts.linter.dfa import markdown_state, next_state
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

    current_state: markdown_state = markdown_state._begin
    end_mark: str = ''

    for i, line in enumerate(lines):
        if line_origins[i] == -1:
            # Skip placeholder lines (from skip blocks)
            continue

        ext_message = {
            'codeblock_end_mark': end_mark
        }
        current_state, ext_message = next_state(
            current_state, line, **ext_message)
        end_mark = ext_message.get('codeblock_end_mark')  # type: ignore

        # Skip current line if should
        if current_state not in [markdown_state.normal_line,
                                 markdown_state.math_block_content,
                                 markdown_state.normal_code_block_content]:
            continue

        modified_line = line.replace('。', '．')

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
