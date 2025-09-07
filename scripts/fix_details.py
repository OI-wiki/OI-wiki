import os
import argparse
from typing import Iterable

TAB_LENGTH = 2
SKIP_EXTNAME = '.skipdetails'


def index_lfirst_neq(l: Iterable, value):
    return next(idx for idx, v in enumerate(l) if v != value)


def log(msg, type='debug'):
    if os.environ.get('RUNNER_DEBUG'):
        print(f"::{type}::{msg}")


def fix_details(md_content: str):
    log(f"start")
    # Assume that adjacent lines with identical indentation belong to the same block
    # so blank lines should align with the indentation of the preceding line or succeding line
    log(f"preceding")
    lines: list[str] = md_content.splitlines()
    result = []
    skip_lines = []
    past_indent = 0
    first_nonblank, last_nonblank = -1, len(lines)
    first_indent, last_indent = 0, 0
    skip_counter = 0
    for index, line in enumerate(lines):
        if line.strip() == f'<!-- preprocess{SKIP_EXTNAME} on -->':
            skip_counter += 1
            log(f"line {index+1}: skip begin, level = {skip_counter}")

        if skip_counter == 0:
            line = line.replace('\t', ' '*TAB_LENGTH)
            if line.strip():  # non-blank line
                now_indent = index_lfirst_neq(line, ' ')
                if now_indent != past_indent:
                    past_indent = now_indent
                    log(f"line {index+1}: get indent = {past_indent}")
                if first_nonblank == -1:
                    first_nonblank, first_indent = index, past_indent
                last_nonblank, last_indent = index, past_indent
            else:
                line = ' '*past_indent
                log(f"line {index+1}: set indent = {past_indent}")
        else:
            skip_lines.append(index)

        if line.strip() == f'<!-- preprocess{SKIP_EXTNAME} off -->':
            skip_counter -= 1
            log(f"line {index+1}: skip end, level = {skip_counter}")

        result.append(line)

    # Align the blank line with the indentation of the succeding line if the indentation of succeding line is shorter
    log(f"succeding")
    lines, result = result, []
    past_indent = 0
    skip_counter = 0
    for index, line in enumerate(reversed(lines)):
        if line.strip() == f'<!-- preprocess{SKIP_EXTNAME} off -->':
            skip_counter += 1
            log(f"line -{index+1}: skip begin, level = {skip_counter}")

        if skip_counter == 0:
            line = line.replace('\t', ' '*TAB_LENGTH)
            if line.strip():  # non-blank line
                now_indent = index_lfirst_neq(line, ' ')
                if now_indent != past_indent:
                    past_indent = now_indent
                    log(f"line -{index+1}: get indent = {past_indent}")
            elif len(line) > past_indent:
                line = ' '*past_indent
                log(f"line -{index+1}: set indent = {past_indent}")

        if line.strip() == f'<!-- preprocess{SKIP_EXTNAME} on -->':
            skip_counter -= 1
            log(f"line -{index+1}: skip end, level = {skip_counter}")

        result.append(line)
    result = result[::-1]

    # Align the blank lines before first_nonblank or after last_nonblank
    log(f"boundary")
    for i in range(first_nonblank):
        if i not in skip_lines and not result[i].strip():
            result[i] = ' '*first_indent
            log(f"line {i+1}: set indent = {first_indent}")
    for i in range(last_nonblank+1, len(result)):
        if i not in skip_lines and not result[i].strip():
            result[i] = ' '*last_indent
            log(f"line {i+1}: set indent = {last_indent}")

    # concat
    lines, result = result, ''
    for line in lines:
        result += line+'\n'
    return result


def check(filename: str):
    log(filename, type='group')

    if os.path.exists(filename + SKIP_EXTNAME):
        log(f"skip {filename} since {SKIP_EXTNAME} file found")
        return

    old, new = '', ''
    with open(filename, 'r', encoding='utf-8') as f:
        old = f.read()
        log(f"{len(old)} character(s) read from {filename}")
        new = fix_details(old)
    if old != new:
        with open(filename, 'w', encoding='utf-8') as f:
            f.write(new)
            log(f"{len(new)} character(s) wrote")

    log('', type='endgroup')


parser = argparse.ArgumentParser(description="修复 Markdown 文件的 details 缩进")
parser.add_argument('directory', nargs='?', help='要递归处理的文件夹')
parser.add_argument('-f', '--files', nargs='+', help='要处理的 Markdown 文件列表')

if __name__ == '__main__':
    args = parser.parse_args()

    file_list = []

    if args.files:
        file_list.extend(
            filter(lambda f: os.path.splitext(f)[1] == '.md', args.files))
    elif args.directory:
        for root, _, files in os.walk(args.directory):
            file_list.extend(os.path.join(root, fn) for fn in filter(
                lambda f: os.path.splitext(f)[1] == '.md', files))
    else:
        parser.print_help()
        exit(0)

    file_list = list(filter(lambda f: os.path.isfile(f), file_list))

    print(f"{len(file_list)} file(s) found")

    for file in file_list:
        check(file)
