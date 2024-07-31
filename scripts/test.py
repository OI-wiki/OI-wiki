import os
import sys
import subprocess


def get_files_to_test(filenames):
    summary = ''
    mainfiles_to_test = set()
    cnt_ac, cnt_skip, cnt_error = 0, 0, 0

    for filename in filenames:
        dirname, basename, extname = os.path.dirname(filename), os.path.splitext(os.path.basename(filename))[0], os.path.splitext(filename)[1]
        if os.path.exists(os.path.join(dirname, basename + '.skip_test')):
            cnt_skip += 1
            summary += f'## 跳过：{filename}\n测试因 {basename + ".skip_test"} 文件存在而跳过\n\n'
            print(f'::group::{filename}: test skipped')
            print(f'::endgroup::')
            continue
        if extname.endswith('.cpp'): # 代码文件改变，所有测试点重测
            mainfile = os.path.normpath(os.path.join(dirname, basename.split('.')[0] + '.cpp'))
            if mainfile in mainfiles_to_test:
                continue
            else:
                mainfiles_to_test.add(mainfile)
            auxfiles = [] # 寻找其他辅助文件
            for root, _, files in os.walk(dirname):
                for file in files:
                    if file.split('.')[0] == basename.split('.')[0] and file.endswith('.cpp'):
                        auxfiles.append(os.path.normpath(os.path.join(root, file)))
            examples = [] # 寻找样例文件
            for root, _, files in os.walk(dirname.replace('code', 'examples')):
                for file in files:
                    if file.split('.')[0] == basename.split('.')[0] and file.endswith('.in') and os.path.exists(os.path.join(root, file.replace('.in', '.ans'))):
                        examples.append(os.path.normpath(os.path.join(root, file)))

        elif extname.endswith(('.in', '.ans')): # 单一测试点改变
            mainfile = os.path.normpath(os.path.join(dirname.replace('examples', 'code'), basename.split('.')[0] + '.cpp'))
            if mainfile in mainfiles_to_test:
                continue
            else:
                mainfiles_to_test.add(mainfile)
            auxfiles = [] # 寻找其他辅助文件
            for root, _, files in os.walk(dirname.replace('examples', 'code')):
                for file in files:
                    if file.split('.')[0] == basename.split('.')[0] and file.endswith('.cpp'):
                        auxfiles.append(os.path.normpath(os.path.join(root, file)))
            examples = [os.path.normpath(os.path.join(dirname, basename + '.in'))]

        test_result, summary = test(mainfile, auxfiles, examples, summary)
        if test_result:
            cnt_ac += 1
        else:
            cnt_error += 1
        print()


    with open(os.environ.get('GITHUB_STEP_SUMMARY'), 'w') as f:
        f.write(f'# TOTAL {len(mainfiles_to_test)} TESTS, {cnt_ac} ACCEPTED, {cnt_skip} SKIPPED, {cnt_error} ERROR\n\n')
        f.write(summary)
    print(f'::group::TOTAL {len(mainfiles_to_test)} TESTS, {cnt_ac} ACCEPTED, {cnt_skip} SKIPPED, {cnt_error} ERROR\n::endgroup::')
    if cnt_error:
        sys.exit(1)


def test(mainfile, auxfiles, examples, summary):
    print(f'::group::Test for {mainfile}...')
    # 检测文件存在
    for file in auxfiles:
        if not os.path.exists(file):
            print(f'::endgroup::')
            print(f'::error file={file},title=file {file} not found::')
            summary += f'## 找不到文件：{file}\n对{mainfile}的测试因找不到文件{file}而被迫中止\n\n'
            return False, summary
    for file in examples:
        if not os.path.exists(file):
            print(f'::endgroup::')
            print(f'::error file={file},title=file {file} not found::')
            summary += f'## 找不到文件：{file}\n对{mainfile}的测试因找不到文件{file}而被迫中止\n\n'
            return False, summary
        
    # 编译
    compile_command = f'g++ -std=c++17 {" ".join(auxfiles)} -o {mainfile.split(".")[0]}'
    print(compile_command, end=' ')

    result = subprocess.run(compile_command, shell=True)
    if result.returncode != 0:
        print(f'\n::endgroup::')
        print(f'::error file={mainfile},title=CE!::Compile Error! with error code {result.returncode}')
        summary += f'## CE: {mainfile}\n- 主要文件：`{mainfile}`\n- 辅助文件：`{", ".join(auxfiles)}`\n- 测试点：`{", ".join(examples)}`\n- **编译指令**：{compile_command}\n- **错误代码**：{result.returncode}\n\n'
        return False, summary
    else:
        print('OK')

    # 对不提供数据点的特殊处理
    if len(examples) == 0:
        print(f'\n::endgroup::')
        print(f"::notice file={mainfile},title=No data!::Can't find data to test. If you don't want this notice, create {mainfile.replace('.cpp', '.skip_test')}")
        summary += f'## No Data: {mainfile}\n- 主要文件：`{mainfile}`\n- 辅助文件：`{", ".join(auxfiles)}`\n- 测试点：`{", ".join(examples)}`\n- 编译指令：{compile_command}\n成功编译，但因数据不存在未能进一步测试。**如果不希望进行测试，请创建{mainfile.replace(".cpp", ".skip_test")}**\n\n'
        return True, summary

    # 逐个测试
    executable = mainfile.split(".")[0]
    check_command = (f'diff -b -B {e.replace(".in", ".out")} {e.replace(".in", ".ans")}' for e in examples)
    for check, e in zip(check_command, examples):
        print(f'{executable} < {e} > {e.replace(".in", ".out")}', end=' ')
        with open(e, 'r') as fstdin:
            with open(e.replace(".in", ".out"), 'w') as fstdout:
                result = subprocess.run(executable, shell=True, stdin=fstdin, stdout=fstdout)
        if result.returncode != 0:
            print(f'\n::endgroup::')
            print(f'::error file={mainfile},title=RE!::Runtime Error! with error code: {result.returncode}')
            summary += f'## RE: {mainfile}\n- 主要文件：`{mainfile}`\n- 辅助文件：`{", ".join(auxfiles)}`\n- 测试点：`{", ".join(examples)}`\n- **出错测试点**：{e}\n- **错误代码**：{result.returncode}\n\n'
            return False, summary
        else:
            print('OK')

        print(check, end=' ')
        result = subprocess.run(check, shell=True, stdout=subprocess.DEVNULL)
        if result.returncode != 0:
            print(f'\n::endgroup::')
            print(f'::error file={e},title=WA!::Wrong Answer on: {e}')
            summary += f'## WA: {mainfile}\n- 主要文件：`{mainfile}`\n- 辅助文件：`{", ".join(auxfiles)}`\n- 测试点：`{", ".join(examples)}`\n- **出错测试点**：{e}\n\n期望得到：\n```\n{open(e.replace(".in", ".ans")).read()}\n```\n但得到输出：\n```\n{open(e.replace(".in", ".out")).read()}\n```\n\n'
            return False, summary
        else:
            print(f'Accepted!')

    
    summary += f'## AC: {mainfile} ({len(examples)} tests)\n- 主要文件：`{mainfile}`\n- 辅助文件：`{", ".join(auxfiles)}`\n- 测试点：`{", ".join(examples)}`\n\n'
    print(f'::endgroup::')
    return True, summary

filename = "res.txt"
with open(filename) as file_object:
    lines = file_object.readlines()
for line in lines:
    get_files_to_test(line.split())
