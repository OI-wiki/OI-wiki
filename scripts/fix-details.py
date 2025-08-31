import os
import sys
from typing import Iterable

SKIP_EXTNAME = '.skipdetails'


def index_lfirst_neq(l: Iterable, value):
    return next(idx for idx, v in enumerate(l) if v != value)


def fix_details(md_content: str):
    # Assume that adjacent lines with identical indentation belong to the same block
    # so blank lines should align with the indentation of the preceding line or succeding line
    lines = md_content.splitlines()
    result = []
    last_indent = 0
    for line in lines:
        if line.strip():  # non-blank line
            last_indent = index_lfirst_neq(line, ' ')
        else:
            line = ' '*last_indent
        result.append(line)
    # Align the blank line with the indentation of the succeding line if the indentation of succeding line is shorter
    lines, result = result, []
    last_indent = 0
    for line in reversed(lines):
        if line.strip():  # non-blank line
            last_indent = index_lfirst_neq(line, ' ')
        elif len(line) > last_indent:
            line = ' '*last_indent
        result.append(line)
    result = result[::-1]

    return '\n'.join(result)+'\n'


def check(filename: str):
    if os.path.exists(filename + SKIP_EXTNAME):
        return

    old, new = '', ''
    with open(filename, 'r', encoding='utf-8') as f:
        old = f.read()
        new = fix_details(old)
    if old != new:
        with open(filename, 'w', encoding='utf-8') as f:
            f.write(new)


if __name__ == '__main__':
    for root, _, files in os.walk(sys.argv[1]):
        for filename in filter(lambda f: os.path.splitext(f)[1] == '.md', files):
            check(os.path.join(root, filename))
