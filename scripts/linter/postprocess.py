import re
from scripts.linter.common import step, log


@step
def fix_punctuations(md_content: str, **kwargs):
    """
    Fix punctuation issues in Markdown content.

    This function corrects common punctuation issues in Markdown content,
    including periods, commas, and other symbols.

    Args:
        md_content: The Markdown content to process
        **kwargs: Additional arguments including 'line_origins' for tracking

    Returns:
        str: The processed Markdown content with corrected punctuations
    """
    # Replace English punctuation with Chinese punctuation
    PUNCTUATION_MAP = {
        ',': '，',
        '.': '。',
        ';': '；',
        ':': '：',
        '!': '！',
        '?': '？'
    }
    # Pattern to match inline math followed by English punctuation
    RE_INLINE_MATH_PATTERN = re.compile(
        rf"(\$[^$]+\$)([{''.join(PUNCTUATION_MAP.keys())}]) ?")

    line_origins: list[int] = kwargs.get('line_origins', [])  # type: ignore
    lines = md_content.splitlines()

    log(f"Processing {len(lines)} lines for punctuation fixes")

    # Track changes for logging
    total_changes = 0

    for i, line in enumerate(lines):
        if line_origins[i] == -1:
            # Skip placeholder lines (from skip blocks)
            continue

        original_line = line
        modified_line = line

        # 1. Fix punctuation after inline math formulas
        modified_line = RE_INLINE_MATH_PATTERN.sub(
            lambda match: match.group(1) + PUNCTUATION_MAP[match.group(2)],
            modified_line)

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
