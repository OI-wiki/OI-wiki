import json
import os


class ChangeNeeded(Exception):
    pass


def str_2_unicode(s):
    return s.encode("unicode-escape").decode()


def summary(s):
    os.system(f'echo "{s}" >> $GITHUB_STEP_SUMMARY')


changed_files = os.environ.get("CHANGED_FILES", "")
successed_list, skipped_list, failed_list = [], [], {}
char_map = json.load(open("scripts/char-map.json"))

for filename in changed_files.replace("\n", " ").split():
    if os.path.exists(f"{filename}.skipchars"):
        skipped_list.append(filename)
        continue
    failed = False
    check = open(filename)
    data = check.read()
    for key, value in char_map.items():
        if data.find(key) != -1:
            failed = True
            if filename in failed_list.keys():
                print(f"检查到使用错误字符的文件：{file_path}")
            print(
                f"  - {key} ({str_2_unicode(key)}) -> {char_map[value]} ({str_2_unicode(char_map[value])})"
            )
            if filename in failed_list.keys():
                failed_list[filename].append(key)
            else:
                failed_list[filename] = [key]
    if not failed:
        successed_list.append(filename)

summary("## :checkered_flag: 字符检查结果")
if successed_list:
    summary("### :white_check_mark: 成功")
    for filename in successed_list:
        summary(f"  - {filename}")
if skipped_list:
    summary("### 跳过")
    for filename in skipped_list:
        summary(f"  - {filename}")
if failed_list:
    summary("### :x: 失败")
    for filename, failed_chars in failed_list:
        summary(f"- {filename}")
        for failed_char in failed_chars:
            summary(
                f"  - {failed_char}({str_2_unicode(failed_char)}) -> {char_map[failed_char]}({str_2_unicode(char_map[failed_char])})"
            )
    raise ChangeNeeded("Change Needed!")
