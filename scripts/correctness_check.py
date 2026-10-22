# Check correctness of example code.
# input: main files to test (from get_files_to_test.py, read from $FILES_TO_TEST
#        as a space separated list) and the language to test (--language)
# output: None. Print to GitHub Action step summary.

import argparse
import os
import subprocess
import sys

from test_utils import derive_test_files

ACCEPTED = 1
ERROR = 0
SKIPPED = -1


def describe(mainfile, auxfiles, examples):
    """Describe the files of one test instance in the step summary."""
    lines = [f"- 主要文件：`{mainfile}`"]
    if auxfiles:
        lines.append(f"- 辅助文件：`{', '.join(auxfiles)}`")
    lines.append(f"- 测试点：`{', '.join(examples)}`")
    return "\n".join(lines) + "\n"


def test_code(mainfile, auxfiles, examples, skiptest, summary, build, run):
    """
    Check correctness of one instance of example code.

    The languages only differ in how the code is prepared and executed:
    `build(mainfile, auxfiles)` returns the command that prepares the code, or
    an empty string when there is nothing to prepare, and `run(mainfile)`
    returns the command that executes it. Everything else, that is skipping,
    running every example and comparing its output with the answer, is shared.
    """
    print(f"::group::Test for {mainfile}...")
    details = describe(mainfile, auxfiles, examples)

    # 是否跳过测试
    if skiptest:
        summary += (
            f'## 跳过：{mainfile}\n测试因 {mainfile + ".skip_test"} 文件存在而跳过\n\n'
        )
        print(f"::group::{mainfile}: test skipped")
        print(f"::endgroup::")
        return SKIPPED, summary

    # 检测文件存在
    for file in auxfiles + examples:
        if not os.path.exists(file):
            print(f"::endgroup::")
            print(f"::error file={file},title=file {file} not found::")
            summary += f"## 找不到文件：{file}\n对{mainfile}的测试因找不到文件{file}而被迫中止\n\n"
            return ERROR, summary

    # 准备（C++ 需要编译，Python 无需准备）
    build_command = build(mainfile, auxfiles)
    if build_command:
        print(build_command, end=" ")
        result = subprocess.run(build_command, shell=True)
        if result.returncode != 0:
            print(f"\n::endgroup::")
            print(
                f"::error file={mainfile},title=CE!::Compile Error! with error code {result.returncode}"
            )
            summary += f"## CE: {mainfile}\n{details}- **编译指令**：{build_command}\n- **错误代码**：{result.returncode}\n\n"
            return ERROR, summary
        else:
            print("OK")

    # 对不提供数据点的特殊处理
    if len(examples) == 0:
        skip_marker = os.path.splitext(mainfile)[0] + ".skip_test"
        print(f"\n::endgroup::")
        print(
            f"::warning file={mainfile},title=No data!::Can't find data to test. If you don't want this notice, create {skip_marker}"
        )
        summary += f"## No Data: {mainfile}\n{details}因数据不存在未能进一步测试。**如果不希望进行测试，请创建{skip_marker}**\n\n"
        return ACCEPTED, summary

    # 逐个测试
    command = run(mainfile)
    for in_file in examples:
        out_file = in_file.replace(".in", ".out")
        ans_file = in_file.replace(".in", ".ans")

        print(f"{' '.join(command)} < {in_file} > {out_file}", end=" ")
        with open(in_file) as fstdin, open(out_file, "w") as fstdout:
            result = subprocess.run(
                command,
                stdin=fstdin,
                stdout=fstdout,
                stderr=subprocess.PIPE,
                text=True,
            )
        if result.returncode != 0:
            print(f"\n::endgroup::")
            print(
                f"::error file={mainfile},title=RE!::Runtime Error! with error code: {result.returncode}"
            )
            # 把报错信息留在运行日志里，否则 Python 的 traceback 既不会出现在
            # 日志里，也不会出现在 summary 里
            print(result.stderr, end="")
            summary += f"## RE: {mainfile}\n{details}- **出错测试点**：{in_file}\n- **错误代码**：{result.returncode}\n\n```\n{result.stderr}```\n\n"
            return ERROR, summary
        else:
            print("OK")

        print(f"diff -b -B {out_file} {ans_file}", end=" ")
        result = subprocess.run(
            ["diff", "-b", "-B", out_file, ans_file], stdout=subprocess.DEVNULL
        )
        if result.returncode != 0:
            print(f"\n::endgroup::")
            print(f"::error file={in_file},title=WA!::Wrong Answer on: {in_file}")
            with open(ans_file) as fans, open(out_file) as fout:
                summary += f"## WA: {mainfile}\n{details}- **出错测试点**：{in_file}\n\n期望得到：\n```\n{fans.read()}\n```\n但得到输出：\n```\n{fout.read()}\n```\n\n"
            return ERROR, summary
        else:
            print(f"Accepted!")

    summary += f"## AC: {mainfile} ({len(examples)} tests)\n{details}\n"
    print(f"::endgroup::")
    return ACCEPTED, summary


def test_cpp(mainfile, auxfiles, examples, skiptest, summary):
    """Compile an example with g++ and run the resulting executable."""

    def build(mainfile, auxfiles):
        executable = os.path.splitext(mainfile)[0]
        return f"g++ -std=c++17 {' '.join(auxfiles)} -o {executable}"

    return test_code(
        mainfile,
        auxfiles,
        examples,
        skiptest,
        summary,
        build=build,
        run=lambda mainfile: [os.path.splitext(mainfile)[0]],
    )


def test_py(mainfile, auxfiles, examples, skiptest, summary):
    """Run an example with the same interpreter that runs this script."""
    return test_code(
        mainfile,
        auxfiles,
        examples,
        skiptest,
        summary,
        build=lambda mainfile, auxfiles: "",
        run=lambda mainfile: [sys.executable, mainfile],
    )


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument(
        "--language",
        type=str,
        default="cpp",
        choices=["cpp", "py"],
        help="the language of the example code to test",
    )
    language = parser.parse_args().language
    test = test_cpp if language == "cpp" else test_py

    mainfiles = os.environ.get("FILES_TO_TEST", "").split()

    cnt_ac, cnt_error, cnt_skip = 0, 0, 0
    summary = ""
    for mainfile in mainfiles:
        auxfiles, examples, skiptest = derive_test_files(mainfile)
        correctness, summary = test(mainfile, auxfiles, examples, skiptest, summary)
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


if __name__ == "__main__":
    main()
