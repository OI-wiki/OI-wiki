import os
import subprocess

mainfiles, auxfiles, examples, skiptests = eval(os.environ.get("FILES_TO_TEST"))
runs_on = os.environ.get("RUNS_ON")

ACCEPTED = 0
ERR_CE = 1
ERR_RE = 2
ERR_WA = 3
SKIPPED = -1

RED = "\033[0;31m"
GREEN = "\033[0;32m"
YELLOW = "\033[0;33m"
BLUE = "\033[0;34m"
PURPLE = "\033[0;35m"
CYAN = "\033[0;36m"
WHITE = "\033[0;37m"
RESET = "\033[0m"

def get_color(status: str) -> str:
    if 'AC' in status or 'OK' in status:
        return GREEN
    elif 'SKIPPED' in status:
        return BLUE
    else:
        return RED

def ub_check(mainfile, auxfiles, examples, skiptest):
    """
    Check for undefined behavior.
    """

    # print(f"::group::Test for {mainfile}...")
    print(f"Test for {mainfile}...")
    # 是否跳过测试
    if skiptest:
        print(f'{BLUE}test skipped because file {mainfile + ".skip_test"} exists{RESET}')
        return ['SKIPPED']
    
    # 编译指令和编译产物
    compile_commands = [f'clang++ -std=c++14 -O0 {" ".join(auxfiles)} -o {mainfile.split(".")[0]}.Clang.O0',
                        f'clang++ -std=c++14 -O2 {" ".join(auxfiles)} -o {mainfile.split(".")[0]}.Clang.O2',
                        f'clang++ -std=c++14 -O3 {" ".join(auxfiles)} -o {mainfile.split(".")[0]}.Clang.O3',
                        f'g++-11 -std=c++14 -O0 -static {" ".join(auxfiles)} -o {mainfile.split(".")[0]}.CPP14.GCC11.O0',
                        f'g++-11 -std=c++14 -O2 -static {" ".join(auxfiles)} -o {mainfile.split(".")[0]}.CPP14.GCC11.O2', # NOI 2023
                        f'g++-11 -std=c++14 -O3 -static {" ".join(auxfiles)} -o {mainfile.split(".")[0]}.CPP14.GCC11.O3',
                        f'g++-11 -std=gnu11 -O0 -static {" ".join(auxfiles)} -o {mainfile.split(".")[0]}.GNU11.GCC11.O0',
                        f'g++-11 -std=gnu11 -O2 -static {" ".join(auxfiles)} -o {mainfile.split(".")[0]}.GNU11.GCC11.O2', # ACM ICPC 2023
                        f'g++-11 -std=gnu11 -O3 -static {" ".join(auxfiles)} -o {mainfile.split(".")[0]}.GNU11.GCC11.O3', 
                        f'g++-13 -std=c++14 -O0 -static {" ".join(auxfiles)} -o {mainfile.split(".")[0]}.CPP14.GCC13.O0',
                        f'g++-13 -std=c++14 -O2 -static {" ".join(auxfiles)} -o {mainfile.split(".")[0]}.CPP14.GCC13.O2',
                        f'g++-13 -std=c++14 -O3 -static {" ".join(auxfiles)} -o {mainfile.split(".")[0]}.CPP14.GCC13.O3',
    ]
    compile_products = [f'{mainfile.split(".")[0]}.Clang.O0',
                        f'{mainfile.split(".")[0]}.Clang.O2',
                        f'{mainfile.split(".")[0]}.Clang.O3',
                        f'{mainfile.split(".")[0]}.CPP14.GCC11.O0',
                        f'{mainfile.split(".")[0]}.CPP14.GCC11.O2',
                        f'{mainfile.split(".")[0]}.CPP14.GCC11.O3',
                        f'{mainfile.split(".")[0]}.GNU11.GCC11.O0',
                        f'{mainfile.split(".")[0]}.GNU11.GCC11.O2',
                        f'{mainfile.split(".")[0]}.GNU11.GCC11.O3',
                        f'{mainfile.split(".")[0]}.CPP14.GCC13.O0',
                        f'{mainfile.split(".")[0]}.CPP14.GCC13.O2',
                        f'{mainfile.split(".")[0]}.CPP14.GCC13.O3',
    ]

    return_status = {}
    this_file_looks_odd = False
    for compile_command, compile_product in zip(compile_commands, compile_products):
        print(compile_command, end=' ')
        result = subprocess.run(compile_command, shell=True)
        if result.returncode != 0:
            print(f'{RED}CE({result.returncode}){RESET}')
            this_file_looks_odd = True
            status_vector = ['CE']
        else: 
            status_vector = [f'Compile OK']
            print(f'{GREEN}OK{RESET}')
            for e in examples:
                print(f'{compile_product} < {e} > {e.replace(".in", ".out")}', end=' ')
                with open(e, 'r') as fstdin:
                    with open(e.replace(".in", ".out"), 'w') as fstdout:
                        result = subprocess.run(f'./{compile_product}', stdin=fstdin, stdout=fstdout, shell=True)
                if result.returncode != 0:
                    print(f'{RED}RE({result.returncode})){RESET}')
                    this_file_looks_odd = True
                    status_vector.append(f'RE({result.returncode})')
                else:
                    print(f'{GREEN}OK{RESET}')
                    print(f'diff -b -B {e.replace(".in", ".out")} {e.replace(".in", ".ans")}', end=' ')
                    result = subprocess.run(f'diff -b -B {e.replace(".in", ".out")} {e.replace(".in", ".ans")}', shell=True)
                    if result.returncode != 0:
                        print(f'{RED}WA{RESET}')
                        this_file_looks_odd = True
                        status_vector.append(f'WA')
                    else:
                        print(f'{GREEN}AC{RESET}')
                        status_vector.append(f'AC')
        print(f'{compile_product.split(os.path.pathsep)[-1]}: ', end='')
        for _ in status_vector:
            print(f'{get_color(_)}{_}{RESET}', end='; ')
        print()
        return_status[compile_product] = status_vector

    print(f'{BLUE}Result for {mainfile}: {RESET}')
    if this_file_looks_odd:
        print(f'::error file={mainfile},title=疑似UB::{RED}请核实该文件是否存在未定义行为{RESET}')
    for key in return_status:
        print(f'-  {key}: ', end='')
        for _ in return_status[key]:
            print(f'{get_color(_)}{_}{RESET}', end='; ')
        print()
    print()
    return this_file_looks_odd, return_status

mainfiles, auxfiles, examples, skiptests = eval(os.environ.get("FILES_TO_TEST"))

cnt_ac, cnt_error = 0, 0
output = {}
for mainfile, auxfile, example, skiptest in zip(mainfiles, auxfiles, examples, skiptests):
    suspect, ret = ub_check(mainfile, auxfile, example, skiptest)
    output[mainfile] = ret
    if suspect:
        cnt_error += 1
    else:
        cnt_ac += 1

# with open(os.environ.get('GITHUB_STEP_SUMMARY'), 'w') as f:
#     f.write(f'# TOTAL {len(mainfiles)} TESTS, {cnt_ac} ACCEPTED, {cnt_error} may include UB\n\n')
#     print(f'::group::TOTAL {len(mainfiles)} TESTS, {cnt_ac} ACCEPTED, {cnt_error} may include UB\n::endgroup::')

with open('output.txt', 'w') as f:
    f.write(str(output))
