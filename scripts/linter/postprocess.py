import re
from scripts.linter.common import step, log


@step
def fix_punctuations(md_content: str, **kwargs):
    PUNCTUATION_MAP = {
        ',': '，',
        '.': '。',
        ';': '；',
        ':': '：',
        '!': '！',
        '?': '？'
    }
    RE_INLINE_MATH_PATTERN = re.compile(
        rf"(\$[^$]+\$)([{''.join(PUNCTUATION_MAP.keys())}]) ?")

    line_origins: list[int] = kwargs.get('line_origins', [])  # type: ignore
    lines = md_content.splitlines()

    log(f"Processing {len(lines)} lines for punctuation fixes")

    total_changes = 0

    for i, line in enumerate(lines):
        if line_origins[i] == -1:
            continue

        original_line = line
        modified_line = line

        modified_line = RE_INLINE_MATH_PATTERN.sub(
            lambda match: match.group(1) + PUNCTUATION_MAP[match.group(2)],
            modified_line)

        modified_line = modified_line.replace('。', '．')

        if modified_line != original_line:
            lines[i] = modified_line
            total_changes += 1
            original_line_num = line_origins[i] + 1
            log(f"line {original_line_num}: punctuation fixes applied")

    log(f"Punctuation fix completed: {total_changes} lines modified")
    result = '\n'.join(lines) + '\n'
    log(f"Final result: {len(result)} characters")

    return result
