# Check correctness of example code.
# input: mainfile list (from get_files_to_test.py, read from $FILES_TO_TEST)
# output: None. Print to GitHub Action step summary.

import argparse
import os
import subprocess
import sys

ACCEPTED = 1
ERROR = 0
SKIPPED = -1


def derive_test_files(mainfile):
    """
    Derive auxfiles, examples, and skiptest status from mainfile.

    Args:
        mainfile: Path to the main source code file

    Returns:
        tuple: (auxfiles, examples, skiptest)
            auxfiles: List of all `.cpp` files with same basename (including mainfile) if mainfile has `.cpp` extension, otherwise `[]`
            examples: List of .in files that have corresponding .ans files
            skiptest: Boolean indicating if .skip_test file exists
    """
    dirname = os.path.dirname(mainfile)
    basename = os.path.splitext(os.path.basename(mainfile))[0]

    # Check if the mainfile has .cpp extension
    if not mainfile.endswith(".cpp"):
        auxfiles = []
    else:
        # Find all auxiliary files (all .cpp files with same basename)
        auxfiles = []
        for root, _, files in os.walk(dirname):
            for file in files:
                if file.split(".")[0] == basename and file.endswith(".cpp"):
                    auxfiles.append(os.path.normpath(os.path.join(root, file)))

    # Find example test cases in corresponding examples directory
    examples = []
    examples_dir = dirname.replace("/code/", "/examples/")
    if os.path.exists(examples_dir):
        for root, _, files in os.walk(examples_dir):
            for file in files:
                if (
                    file.split(".")[0] == basename
                    and file.endswith(".in")
                    and os.path.exists(os.path.join(root, file.replace(".in", ".ans")))
                ):
                    examples.append(os.path.normpath(os.path.join(root, file)))

    # Check if test should be skipped
    skiptest = os.path.exists(os.path.join(dirname, basename + ".skip_test"))

    return auxfiles, examples, skiptest


def test_cpp(mainfile, auxfiles, examples, skiptest, summary):
    """
    Check correctness of one instance of example code.
    """
    print(f"::group::Test for {mainfile}...")
    # 是否跳过测试
    if skiptest:
        summary += f'## 跳过：{mainfile}\n测试因 {mainfile + ".skip_test"} 文件存在而跳过\n\n'
        print(f"::group::{mainfile}: test skipped")
        print(f"::endgroup::")
        return SKIPPED, summary

    # 检测文件存在
    for file in auxfiles:
        if not os.path.exists(file):
            print(f"::endgroup::")
            print(f"::error file={file},title=file {file} not found::")
            summary += f"## 找不到文件：{file}\n对{mainfile}的测试因找不到文件{file}而被迫中止\n\n"
            return ERROR, summary
    for file in examples:
        if not os.path.exists(file):
            print(f"::endgroup::")
            print(f"::error file={file},title=file {file} not found::")
            summary += f"## 找不到文件：{file}\n对{mainfile}的测试因找不到文件{file}而被迫中止\n\n"
            return ERROR, summary

    # 编译
    compile_command = (
        f'g++ -std=c++17 {" ".join(auxfiles)} -o {os.path.splitext(mainfile)[0]}'
    )
    print(compile_command, end=" ")

    result = subprocess.run(compile_command, shell=True)
    if result.returncode != 0:
        print(f"\n::endgroup::")
        print(
            f"::error file={mainfile},title=CE!::Compile Error! with error code {result.returncode}"
        )
        summary += f'## CE: {mainfile}\n- 主要文件：`{mainfile}`\n- 辅助文件：`{", ".join(auxfiles)}`\n- 测试点：`{", ".join(examples)}`\n- **编译指令**：{compile_command}\n- **错误代码**：{result.returncode}\n\n'
        return ERROR, summary
    else:
        print("OK")

    # 对不提供数据点的特殊处理
    if len(examples) == 0:
        print(f"\n::endgroup::")
        print(
            f"::warning file={mainfile},title=No data!::Can't find data to test. If you don't want this notice, create {mainfile.replace('.cpp', '.skip_test')}"
        )
        summary += f'## No Data: {mainfile}\n- 主要文件：`{mainfile}`\n- 辅助文件：`{", ".join(auxfiles)}`\n- 测试点：`{", ".join(examples)}`\n- 编译指令：{compile_command}\n成功编译，但因数据不存在未能进一步测试。**如果不希望进行测试，请创建{mainfile.replace(".cpp", ".skip_test")}**\n\n'
        return ERROR, summary

    # 逐个测试
    executable = mainfile.split(".")[0]
    for e in examples:
        in_file = e
        out_file = e.replace(".in", ".out")
        ans_file = e.replace(".in", ".ans")
        check_command = f"diff -b -B {out_file} {ans_file}"

        print(f"{executable} < {in_file} > {out_file}", end=" ")
        with open(in_file, "r") as fstdin:
            with open(out_file, "w") as fstdout:
                result = subprocess.run(
                    executable, shell=True, stdin=fstdin, stdout=fstdout
                )
        if result.returncode != 0:
            print(f"\n::endgroup::")
            print(
                f"::error file={mainfile},title=RE!::Runtime Error! with error code: {result.returncode}"
            )
            summary += f'## RE: {mainfile}\n- 主要文件：`{mainfile}`\n- 辅助文件：`{", ".join(auxfiles)}`\n- 测试点：`{", ".join(examples)}`\n- **出错测试点**：{in_file}\n- **错误代码**：{result.returncode}\n\n'
            return ERROR, summary
        else:
            print("OK")

        print(check_command, end=" ")
        result = subprocess.run(check_command, shell=True, stdout=subprocess.DEVNULL)
        if result.returncode != 0:
            print(f"\n::endgroup::")
            print(f"::error file={in_file},title=WA!::Wrong Answer on: {in_file}")
            summary += f'## WA: {mainfile}\n- 主要文件：`{mainfile}`\n- 辅助文件：`{", ".join(auxfiles)}`\n- 测试点：`{", ".join(examples)}`\n- **出错测试点**：{in_file}\n\n期望得到：\n```\n{open(ans_file).read()}\n```\n但得到输出：\n```\n{open(out_file).read()}\n```\n\n'
            return ERROR, summary
        else:
            print(f"Accepted!")

    summary += f'## AC: {mainfile} ({len(examples)} tests)\n- 主要文件：`{mainfile}`\n- 辅助文件：`{", ".join(auxfiles)}`\n- 测试点：`{", ".join(examples)}`\n\n'
    print(f"::endgroup::")
    return ACCEPTED, summary


def test_py(mainfile, examples, skiptest, summary):
    """
    Check correctness of one instance of example code.
    """
    print(f"::group::Test for {mainfile}...")
    # 是否跳过测试
    if skiptest:
        summary += f'## 跳过：{mainfile}\n测试因 {mainfile + ".skip_test"} 文件存在而跳过\n\n'
        print(f"::group::{mainfile}: test skipped")
        print(f"::endgroup::")
        return SKIPPED, summary

    # 检测文件存在
    for file in examples:
        if not os.path.exists(file):
            print(f"::endgroup::")
            print(f"::error file={file},title=file {file} not found::")
            summary += f"## 找不到文件：{file}\n对{mainfile}的测试因找不到文件{file}而被迫中止\n\n"
            return ERROR, summary

    # 对不提供数据点的特殊处理
    if len(examples) == 0:
        print(f"\n::endgroup::")
        print(
            f"::warning file={mainfile},title=No data!::Can't find data to test. If you don't want this notice, create {mainfile.replace('.py', '.skip_test')}"
        )
        summary += f'## No Data: {mainfile}\n- 主要文件：`{mainfile}`\n- 测试点：`{", ".join(examples)}`\n因数据不存在未能测试。**如果不希望进行测试，请创建{mainfile.replace(".py", ".skip_test")}**\n\n'
        return ERROR, summary

    # 逐个测试
    for e in examples:
        in_file = e
        out_file = e.replace(".in", ".out")
        ans_file = e.replace(".in", ".ans")
        print(f"{mainfile} < {in_file} > {out_file}", end=" ")

        result = subprocess.run(
            [sys.executable, mainfile],
            text=True,
            input=open(in_file).read(),
            capture_output=True,
        )
        open(out_file, "w+").write(result.stdout)

        if result.returncode != 0:
            print(f"\n::endgroup::")
            print(
                f"::error file={mainfile},title=RE!::Runtime Error! with error code: {result.returncode}"
            )
            summary += f'## RE: {mainfile}\n- 主要文件：`{mainfile}`\n- 测试点：`{", ".join(examples)}`\n- **出错测试点**：{in_file}\n- **错误代码**：{result.returncode}\n\n'
            return ERROR, summary
        else:
            print("OK")

        print(f"diff -b -B {out_file} {ans_file}", end=" ")
        check_result = subprocess.run(
            f"diff -b -B {out_file} {ans_file}", shell=True, stdout=subprocess.DEVNULL
        )

        if check_result.returncode != 0:
            print(f"\n::endgroup::")
            print(f"::error file={in_file},title=WA!::Wrong Answer on: {in_file}")
            summary += f'## WA: {mainfile}\n- 主要文件：`{mainfile}`\n- 测试点：`{", ".join(examples)}`\n- **出错测试点**：{in_file}\n\n期望得到：\n```\n{open(ans_file).read()}\n```\n但得到输出：\n```\n{open(out_file).read()}\n```\n\n'
            return ERROR, summary
        else:
            print(f"Accepted!")

    summary += f'## AC: {mainfile} ({len(examples)} tests)\n- 主要文件：`{mainfile}`\n- 测试点：`{", ".join(examples)}`\n\n'
    print(f"::endgroup::")
    return ACCEPTED, summary


# Get language to test from argument
if __name__ == '__main__':
    # Ensures the following code runs only when this script is executed directly, not when imported as a module by `ub-check.py`, preventing unintended execution or missing argument errors.
    parser = argparse.ArgumentParser()
    parser.add_argument("--language", type=str, required=True, choices=["cpp", "py"])
    language = parser.parse_args().language

# Get mainfiles from environment variable (space-separated list)
mainfiles_str = os.environ.get("FILES_TO_TEST", "")
mainfiles = mainfiles_str.split() if mainfiles_str else []

cnt_ac, cnt_error, cnt_skip = 0, 0, 0
summary = ""

for mainfile in mainfiles:
    # Derive auxfiles, examples, and skiptest from mainfile
    auxfiles, examples, skiptest = derive_test_files(mainfile)
    if __name__ == '__main__':
        if language == "cpp":
            correctness, summary = test_cpp(mainfile, auxfiles, examples, skiptest, summary)
        elif language == "py":
            correctness, summary = test_py(mainfile, examples, skiptest, summary)
        cnt_ac = cnt_ac + 1 if correctness == ACCEPTED else cnt_ac
        cnt_error = cnt_error + 1 if correctness == ERROR else cnt_error
        cnt_skip = cnt_skip + 1 if correctness == SKIPPED else cnt_skip

with open(os.environ.get("GITHUB_STEP_SUMMARY"), "w") as f:
    f.write(
        f"# TOTAL {len(mainfiles)} TESTS, {cnt_ac} ACCEPTED, {cnt_skip} SKIPPED, {cnt_error} ERROR\n\n"
    )
    f.write(summary)
    print(
        f"::group::TOTAL {len(mainfiles)} TESTS, {cnt_ac} ACCEPTED, {cnt_skip} SKIPPED, {cnt_error} ERROR\n::endgroup::"
    )

if cnt_error:
    exit(1)
