import os
import sys
import re

changed_files = os.environ.get("CHANGED_FILES", "")
successed_list, skipped_list, failed_list = [], [], {}

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

def fix_details(md_content):
    lines = re.split(r'\r\n|\r|\n', md_content)
    stack = [0]
    result = []

    in_code_block = False
    code_fence = None
    in_math_block = False

    i = 0
    for i in range(len(lines)):
        line = lines[i]
        trimmed = line.strip()

        if trimmed.startswith('```'):
            if code_fence is None:
                code_fence = '`' * (len(trimmed) - len(trimmed.lstrip('`')))
                in_code_block = not in_code_block
                result.append(line)
                continue
            elif trimmed.startswith(code_fence):
                code_fence = None
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

        if line.lstrip().startswith('???') or line.lstrip().startswith('==='):
            base_indent = len(line) - len(line.lstrip())
            stack.append(base_indent + 4)
            result.append(line)
            continue

        cur = i
        while cur < len(lines) and lines[cur].strip() == '':
            cur += 1
        
        indent_length = 0
        if cur < len(lines):
            indent_length = len(lines[cur]) - len(lines[cur].lstrip())

        while stack and indent_length < stack[-1]:
            stack.pop()
        
        if trimmed == '':
            result.append(' ' * stack[-1])
        else:
            result.append(line)

    return '\n'.join(result)

def check(filename):
    if os.path.exists(f"{filename}.skipdetails"):
        skipped_list.append(filename)
        return
    failed = False
    check = open(filename, "r", encoding="utf-8")
    data = check.read()
    check.close()
    result = fix_details(data)

    data_lines = re.split(r'\r\n|\r|\n', data)
    result_lines = re.split(r'\r\n|\r|\n', result)

    for i in range(min(len(data_lines), len(result_lines))):
        if data_lines[i] != result_lines[i]:
            failed = True
            if filename in failed_list.keys():
                failed_list[filename].append(i + 1)
            else:
                failed_list[filename] = [i + 1]
    
    if not failed:
        successed_list.append(filename)

if changed_files != "":
    for filename in changed_files.replace("\n", " ").split():
        check(filename)
else:
    for root, _, files in os.walk("docs"):
        for filename in files:
            if filename.endswith(".md"):
                check(os.path.join(root, filename))

summary("## :checkered_flag: Details 块缩进检查结果")
if successed_list:
    summary("### :white_check_mark: 成功")
    for filename in successed_list:
        summary(f"- {filename}")
if skipped_list:
    summary("### 跳过")
    for filename in skipped_list:
        summary(f"- {filename}")
if failed_list:
    summary("### :x: 失败")
    for filename, failed_lines in failed_list.items():
        summary(f"- {filename}")
        for line in failed_lines:
            error(filename, line, 1, "Details 块缩进错误")
    sys.exit(1)
