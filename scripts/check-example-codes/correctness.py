import argparse
import os
import subprocess
import sys
from utils import *


def test_cpp(test_file):
    auxfiles = " ".join(get_auxfiles(test_file))
    executable = test_file.split(".")[0]
    compile_command = f"g++ -std=c++17 {auxfiles} -o {executable}"
    print(compile_command, end=" ")
    result = subprocess.run(compile_command, shell=True)
    if result.returncode != 0:
        print(incolor(RED, "CE"))
        print(
            f"::error file={test_file},title=编译错误::编译错误（错误码：{result.returncode}）\n::endgroup::"
        )
        return 1, f"❌ `{test_file}` 编译错误（错误码：{result.returncode}）"
    print(incolor(GREEN, "OK"))

    in_file, out_file, ans_file = get_examples(test_file)
    if not (os.path.exists(in_file) and os.path.exists(ans_file)):
        print(
            f"::warning file={test_file},title=样例不存在::样例输入 {in_file} 或样例输出 {ans_file} 不存在，无法校验输出结果，请上传对应样例。如果无法提供样例，请在代码文件所在文件夹创建扩展名为 .skip_test 的文件\n::endgroup::"
        )
        return (
            1,
            f"⚠️ `{test_file}` 样例输入 {in_file} 或样例输出 {ans_file} 不存在，无法校验输出结果，请上传对应样例。如果无法提供样例，请在代码文件所在文件夹创建扩展名为 .skip_test 的文件",
        )

    print(f"{executable}", end=" ")
    try:
        result = subprocess.run(
            executable,
            shell=True,
            stdin=open(in_file, "r"),
            stdout=open(out_file, "w"),
            timeout=30,
        )
        if result.returncode != 0:
            print(incolor(RED, "RE"))
            print(
                f"::error file={test_file},title=运行时错误::运行时错误（错误码：{result.returncode}）\n::endgroup::"
            )
            return 1, f"❌ `{test_file}` 运行时错误（错误码：{result.returncode}）"
        print(incolor(GREEN, "OK"))
        return 0, f"✅ `{test_file}` 编译、运行成功"
    except subprocess.TimeoutExpired:
        print(incolor(RED, "TLE"))
        print(f"::error file={test_file},title=运行超时::运行时间超出 30 秒限制\n::endgroup::")
        return 1, f"❌ `{test_file}` 运行时间超出 30 秒限制"


def test_py(test_file):
    in_file, out_file, ans_file = get_examples(test_file)
    if not (os.path.exists(in_file) and os.path.exists(ans_file)):
        print(
            f"::warning file={test_file},title=样例不存在::样例输入 {in_file} 或样例输出 {ans_file} 不存在，无法校验输出结果，请上传对应样例。如果无法提供样例，请在代码文件所在文件夹创建扩展名为 .skip_test 的文件\n::endgroup::"
        )
        return (
            1,
            f"⚠️ `{test_file}` 样例输入 {in_file} 或样例输出 {ans_file} 不存在，无法校验输出结果，请上传对应样例。如果无法提供样例，请在代码文件所在文件夹创建扩展名为 .skip_test 的文件",
        )
    command = f"{sys.executable} {test_file}"
    print(command, end=" ")
    try:
        result = subprocess.run(
            [sys.executable, test_file],
            text=True,
            input=open(in_file).read(),
            capture_output=True,
            timeout=30,
        )
        open(out_file, "w+").write(result.stdout)
        if result.returncode != 0:
            print(incolor(RED, "RE"))
            print(
                f"::error file={test_file},title=运行时错误::运行时错误（错误码：{result.returncode}）\n::endgroup::"
            )
            return 1, f"❌ `{test_file}` 运行时错误（错误码：{result.returncode}）"
        print(incolor(GREEN, "OK"))
        return 0, f"✅ `{test_file}` 运行成功"
    except subprocess.TimeoutExpired:
        print(incolor(RED, "TLE"))
        print(f"::error file={test_file},title=运行超时::运行时间超出 30 秒限制\n::endgroup::")
        return 1, f"❌ `{test_file}` 运行时间超出 30 秒限制"


def test(language, test_file):
    match language:
        case "cpp":
            return test_cpp(test_file)
        case "py":
            return test_py(test_file)
        case _:
            return 1, f"❌ 语言代号 `{language}` 对应的运行函数不存在"


def check_answer(test_file):
    in_file, out_file, ans_file = get_examples(test_file)
    command = f"diff -b -B {out_file} {ans_file}"
    print(command, end=" ")
    result = subprocess.run(command, shell=True, stdout=subprocess.DEVNULL)
    if result.returncode != 0:
        print(incolor(RED, "WA"))
        print(f"::error file={test_file},title=输出错误::输出与答案（{ans_file}）不同\n::endgroup::")
        return (
            1,
            f"❌ `{test_file}` 输出与答案不同\n    答案：\n    ```\n    {open(ans_file).read().rstrip().replace(os.linesep, f'{os.linesep}    ')}\n    ```\n    输出：\n    ```\n    {open(out_file).read().rstrip().replace(os.linesep, f'{os.linesep}    ')}\n    ```",
        )
    print(incolor(GREEN, "AC"))
    print("::endgroup::")
    return 0, f"✅ `{test_file}` 通过测试"


def check_correctness(test_file, language):
    if not os.path.exists(test_file):
        print(incolor(RED, "文件不存在"))
        print("::endgroup::")
        return 1, f"❌ `{test_file}` 文件不存在"
    correctness, test_summary = globals()[f"run_test_{language}"](test_file)
    if correctness != 0:
        return correctness, test_summary
    return check_answer(test_file)


if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("-language", type=str, required=True, choices=["cpp", "py"])
    language = parser.parse_args().language
    test_files = os.environ.get(f"TEST_{language.upper()}_FILES", "").split()
    cnts = [0, 0]
    summary = ""
    for test_file in test_files:
        print("::group::" + incolor(BLUE, f"测试 {test_file}"))
        correctness, test_summary = check_correctness(test_file, language)
        cnts[correctness] += 1
        summary += f"- {test_summary}\n"
    general_summary = (
        f"已完成 {len(test_files)} 个测试，其中通过 {cnts[0]} 个，错误/警告/运行超时 {cnts[1]} 个"
    )
    print(general_summary)
    open(os.environ.get("GITHUB_STEP_SUMMARY"), "w").write(
        f"**{general_summary}**\n\n{summary}"
    )
    exit(cnts[1])
