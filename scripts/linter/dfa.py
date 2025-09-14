from enum import IntEnum, auto

from scripts.linter.utils import index_lfirst_neq


class markdown_state(IntEnum):
    """
    States of markdown DFA
    Only support line process
    Only parse math block and code block
    """
    _begin = auto()
    normal_line = auto()
    math_block_begin = auto()
    math_block_content = auto()
    math_block_end = auto()
    normal_code_block_begin = auto()
    normal_code_block_content = auto()
    normal_code_block_end = auto()
    skip_code_block_begin = auto()
    skip_code_block_content = auto()
    skip_code_block_end = auto()


def next_state(current_state: markdown_state, current_line: str, **kwargs):
    stripped = current_line.strip()

    codeblock_end_mark: str | None = kwargs.get('codeblock_end_mark')
    skipped_codeblock_lang: list[str] | None = kwargs.get(
        'skipped_codeblock_lang')

    def require_ext_message(x, other_requirements=None):
        if x is None:
            raise RuntimeError(f"ext message {x.__name__} should be provided")
        if other_requirements is not None and not other_requirements(x):
            raise RuntimeError(f"invalid {x.__name__}: {x}")

    def process_codeblock_begin(stripped, current_state, codeblock_end_mark, skipped_codeblock_lang):
        require_ext_message(skipped_codeblock_lang)
        if stripped.endswith(tuple(f'```{i}' for i in skipped_codeblock_lang)):
            current_state = markdown_state.skip_code_block_begin
        else:
            current_state = markdown_state.normal_code_block_begin
        codeblock_end_mark = '`' * index_lfirst_neq(stripped, '`')
        return current_state, codeblock_end_mark

    # Get current state by last state
    match current_state:
        case markdown_state._begin | markdown_state.normal_line:
            if stripped == '$$':
                current_state = markdown_state.math_block_begin
            elif stripped.startswith('```'):
                current_state, codeblock_end_mark = process_codeblock_begin(
                    stripped, current_state, codeblock_end_mark, skipped_codeblock_lang)
            else:
                current_state = markdown_state.normal_line
        case markdown_state.math_block_begin | markdown_state.math_block_content:
            if stripped == '$$':
                current_state = markdown_state.math_block_end
            else:
                current_state = markdown_state.math_block_content
        case markdown_state.math_block_end:
            if stripped == '$$':
                current_state = markdown_state.math_block_begin
            elif stripped.startswith('```'):
                current_state, codeblock_end_mark = process_codeblock_begin(
                    stripped, current_state, codeblock_end_mark, skipped_codeblock_lang)
            else:
                current_state = markdown_state.normal_line
        case markdown_state.normal_code_block_begin | markdown_state.normal_code_block_content:
            require_ext_message(codeblock_end_mark,
                                lambda x: len(x) >= 3 and x.count('`') == len(x))
            if stripped == codeblock_end_mark:
                current_state = markdown_state.normal_code_block_end
                codeblock_end_mark = None
            else:
                current_state = markdown_state.normal_code_block_content
        case markdown_state.skip_code_block_begin | markdown_state.skip_code_block_content:
            require_ext_message(codeblock_end_mark,
                                lambda x: len(x) >= 3 and x.count('`') == len(x))
            if stripped == codeblock_end_mark:
                current_state = markdown_state.skip_code_block_end
                codeblock_end_mark = None
            else:
                current_state = markdown_state.skip_code_block_content
        case markdown_state.normal_code_block_end | markdown_state.skip_code_block_end:
            if stripped == '$$':
                current_state = markdown_state.math_block_begin
            elif stripped.startswith('```'):
                current_state, codeblock_end_mark = process_codeblock_begin(
                    stripped, current_state, codeblock_end_mark, skipped_codeblock_lang)
            else:
                current_state = markdown_state.normal_line

    kwargs |= {'codeblock_end_mark': codeblock_end_mark}
    return current_state, kwargs
