import os
import sys

TAB_WIDTH = 4
SKIP_EXTNAME = '.skipdetails'


def index_lfirst_neq(l, value):
    return next(idx for idx, v in enumerate(l) if v != value)


def fix_details(md_content: str):
    lines = md_content.splitlines()
    if not lines or lines[-1]:
        lines.append('')
    stack = [0]
    result = []

    in_code_block, in_math_block = False, False
    code_fence = ''

    for i, line in enumerate(lines):
        assert not in_math_block or not in_code_block

        trimmed = line.strip()

        if not in_math_block and trimmed.startswith('```'):
            if not code_fence:
                code_fence = '`' * index_lfirst_neq(trimmed, '`')
                in_code_block = not in_code_block
                result.append(line)
                continue
            elif trimmed.startswith(code_fence):
                code_fence = ''
                in_code_block = not in_code_block
                result.append(line)
                continue

        if not in_code_block and trimmed == '$$':
            in_math_block = not in_math_block
            result.append(line)
            continue

        if in_code_block or in_math_block:
            result.append(line)
            continue

        if trimmed.startswith(('???', '!!!', '===')):
            stack.append(index_lfirst_neq(line, ' ') + TAB_WIDTH)
            result.append(line)
            continue

        try:
            indent_len = index_lfirst_neq(
                lines[index_lfirst_neq((l.strip() for l in lines[i:]), '')+i], ' ')
            while stack and indent_len < stack[-1]:
                stack.pop()
        except StopIteration:
            pass

        result.append(line if trimmed else ' ' * stack[-1])

    return '\n'.join(result)


def check(filename):
    if os.path.exists(f"{filename}{SKIP_EXTNAME}"):
        return

    old, new = '', ''
    with open(filename, "r", encoding="utf-8") as f:
        old = f.read()
        new = fix_details(old)
    if old != new:
        with open(filename, "w", encoding="utf-8") as f:
            f.write(new)


if __name__ == '__main__':
    for root, _, files in os.walk(sys.argv[1]):
        for filename in filter(lambda f: os.path.splitext(f)[1] == '.md', files):
            check(os.path.join(root, filename))
