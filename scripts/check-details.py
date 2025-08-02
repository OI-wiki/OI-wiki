import os

TAB_WIDTH = 4
succeeded_files, skipped_files, failed_file_lines = [], [], {}


def summary(message):
    if os.environ.get("GITHUB_ACTIONS") == "true":
        os.system(f'echo "{message}" >> $GITHUB_STEP_SUMMARY')
    print(message)


def error(filename, line, col, message):
    if os.environ.get("GITHUB_ACTIONS") == "true":
        os.system(
            f'echo "::error file={filename},line={line},col={col}::Check Details: {message}"'
        )
    print(f"Check Characters: {filename} {line}:{col} {message}")


def index_lfirst_neq(l, value):
    return next((idx for idx, v in enumerate(l) if v != value), -1)


def fix_details(md_content: str):
    lines = md_content.splitlines()
    if not lines or lines[-1]:
        lines.append('')
    stack = [0]
    result = []

    in_code_block, in_math_block = False, False
    code_fence = ''

    for i, line in enumerate(lines):
        trimmed = line.strip()

        if trimmed.startswith('```'):
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

        if trimmed == '$$':
            in_math_block = not in_math_block
            result.append(line)
            continue

        if in_code_block or in_math_block:
            result.append(line)
            continue

        if trimmed.startswith(('???', '!!!', '===')):
            base_indent = index_lfirst_neq(line, ' ')
            stack.append(base_indent + TAB_WIDTH)
            result.append(line)
            continue

        cur = index_lfirst_neq((l.strip() for l in lines[i:]), '')
        indent_len = index_lfirst_neq(lines[cur+i], ' ') if cur > 0 else 0

        while stack and indent_len < stack[-1]:
            stack.pop()

        result.append(line if trimmed else ' ' * stack[-1])

    return result


def check(filename):
    if os.path.exists(f"{filename}.skipdetails"):
        skipped_files.append(filename)
        return
    with open(filename, "r", encoding="utf-8") as f:
        data = f.read()
        result_lines = fix_details(data)

        failed_lnum = list(
            idx+1 for idx, tup in enumerate(zip(data.splitlines(), result_lines)) if tup[0] != tup[1])
        if failed_lnum:
            failed_file_lines[filename] = failed_lnum
        else:
            succeeded_files.append(filename)


if __name__ == '__main__':
    changed_files = os.environ.get("CHANGED_FILES", "")
    if changed_files:
        for filename in changed_files.split():
            check(filename)
    else:
        for root, _, files in os.walk("docs"):
            for filename in filter(lambda f: f.endswith(".md"), files):
                check(os.path.join(root, filename))

    summary("## :checkered_flag: Details 块缩进检查结果")
    if succeeded_files:
        summary("### :white_check_mark: 成功")
        for filename in succeeded_files:
            summary(f"- {filename}")
    if skipped_files:
        summary("### 跳过")
        for filename in skipped_files:
            summary(f"- {filename}")
    if failed_file_lines:
        summary("### :x: 失败")
        for filename, failed_lines in failed_file_lines.items():
            summary(f"- {filename}")
            for line in failed_lines:
                error(filename, line, 1, "Details 块缩进错误")
        raise RuntimeError()
