from scripts.linter.common import index_lfirst_neq, log, step


@step
def fix_details(md_content: str, **kwargs):
    line_origins: list[int] = kwargs.get('line_origins')  # type: ignore
    lines: list[str] = md_content.splitlines()

    size = len(lines)
    MAX_INDENT = max(len(line) for line in lines)+1
    non_blank = [i != -1 and len(line.strip()) > 0
                 for i, line in zip(line_origins, lines)]

    pre_indents = [index_lfirst_neq(line, ' ') if line.strip() else 0
                   for line in lines]
    now_indents = [i if flag else MAX_INDENT for i,
                   flag in zip(pre_indents, non_blank)]

    past_indent = MAX_INDENT
    for index in filter(lambda i: line_origins[i] != -1, range(size)):
        if non_blank[index]:
            past_indent = now_indents[index]
        else:
            now_indents[index] = min(now_indents[index], past_indent)
    past_indent = MAX_INDENT
    for index in filter(lambda i: line_origins[i] != -1, reversed(range(size))):
        if non_blank[index]:
            past_indent = now_indents[index]
        else:
            now_indents[index] = min(now_indents[index], past_indent)
    for index in filter(lambda i: line_origins[i] != -1, range(size)):
        if now_indents[index] == MAX_INDENT:
            now_indents[index] = 0

    for index in filter(lambda i: line_origins[i] != -1, range(size)):
        if pre_indents[index] != now_indents[index]:
            log(f"line {line_origins[index]}: old indent = {pre_indents[index]}, new indent = {now_indents[index]}")
            lines[index] = ' '*now_indents[index] + lines[index].lstrip()

    return '\n'.join(lines) + '\n'
