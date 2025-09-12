import random
import os

from functools import wraps
from typing import Iterable

TAB_LENGTH = 2


def index_lfirst_neq(l: Iterable, value):
    return next(idx for idx, v in enumerate(l) if v != value)


def log(msg, type='debug'):
    if os.environ.get('RUNNER_DEBUG'):
        print(f"::{type}::{msg}")


def step(func):
    tag = f"{func.__module__}.{func.__name__}"
    skip_tag_on = f'<!-- {tag} on -->'
    skip_tag_off = f'<!-- {tag} off -->'
    skip_placeholder = f'<!-- {tag} block {random.randint(0, 2147483647)} -->'

    @wraps(func)
    def inner(md_content: str, **kwargs):
        if not len(md_content):
            return ''

        lines = md_content.splitlines()
        removed_blocks = []
        line_origins = []
        processed_lines = []

        skip_counter = 0
        current_skip_block = []
        current_skip_block_indent = 0

        for index, line in enumerate(lines):
            if line.strip() == skip_tag_on:
                if skip_counter == 0:
                    current_skip_block_indent = index_lfirst_neq(line, ' ')
                skip_counter += 1
                log(f"line {index+1}: skip begin, level = {skip_counter}")

            if skip_counter == 0:
                processed_lines.append(line.replace('\t', ' '*TAB_LENGTH))
                line_origins.append(index)
            else:
                current_skip_block.append(line)

            if line.strip() == skip_tag_off:
                skip_counter -= 1
                log(f"line {index+1}: skip end, level = {skip_counter}")

                if skip_counter == 0:
                    removed_blocks.append(current_skip_block)
                    current_skip_block = []
                    processed_lines.append(
                        ' '*current_skip_block_indent+skip_placeholder)
                    line_origins.append(-1)

        if skip_counter != 0:
            raise RuntimeError(
                f"unclosed skip block detected for tag '{tag}' starting near line {current_skip_block_indent + 1}"
            )

        processed_content = '\n'.join(processed_lines)+'\n'

        assert line_origins

        log(f"start {func.__name__} with skip tag {tag}")
        result: str = func(processed_content,
                           line_origins=line_origins, **kwargs)

        if not removed_blocks:
            return result

        processed_lines = []
        lines = result.splitlines()
        current_block_index = 0
        for index, line in enumerate(lines):
            if line.strip() == skip_placeholder:
                processed_lines.extend(removed_blocks[current_block_index])
                current_block_index += 1
            else:
                processed_lines.append(line)

        return '\n'.join(processed_lines)+'\n'

    return inner


def pipeline(func):
    @wraps(func)
    def inner(file: str):
        log(file, type='group')

        old, new = '', ''
        with open(file, 'r', encoding='utf-8') as f:
            old = f.read()
            log(f"{len(old)} character(s) read from {file}")
            new = func(old)
        if old != new:
            with open(file, 'w', encoding='utf-8') as f:
                f.write(new)
                log(f"{len(new)} character(s) wrote")

        log('', type='endgroup')

    return inner
