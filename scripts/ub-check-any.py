import os
import subprocess

mainfiles, auxfiles, examples, skiptests = eval(os.environ.get("FILES_TO_TEST"))
runs_on = os.environ.get("RUNS_ON")

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

    print(f"Test for {mainfile}...")
    if skiptest:
        print(f'{BLUE}test skipped because file {mainfile + ".skip_test"} exists{RESET}')
        return ['SKIPPED']
    
    CALL_VCVARS_BAT = r'call "C:\Program Files\Microsoft Visual Studio\2022\Enterprise\VC\Auxiliary\Build\vcvars64.bat"'
    compile_commands_dict = {
        "x86_64 Ubuntu": [  f'clang++ -std=c++14 -O0 {" ".join(auxfiles)} -o {mainfile.split(".")[0]}.Clang.O0',
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
                            f'g++-13 -std=c++14 -O3 -static {" ".join(auxfiles)} -o {mainfile.split(".")[0]}.CPP14.GCC13.O3',  ],
        "x86_64 Alpine": [  f'clang++ -std=c++14 -O0 {" ".join(auxfiles)} -o {mainfile.split(".")[0]}.Clang.O0',
                            f'clang++ -std=c++14 -O2 {" ".join(auxfiles)} -o {mainfile.split(".")[0]}.Clang.O2',
                            f'clang++ -std=c++14 -O3 {" ".join(auxfiles)} -o {mainfile.split(".")[0]}.Clang.O3',
                            f'g++ -std=c++14 -O0 {" ".join(auxfiles)} -o {mainfile.split(".")[0]}.GCC.O0',
                            f'g++ -std=c++14 -O2 {" ".join(auxfiles)} -o {mainfile.split(".")[0]}.GCC.O2',
                            f'g++ -std=c++14 -O3 {" ".join(auxfiles)} -o {mainfile.split(".")[0]}.GCC.O3',  ],
        "x86_64 Windows": [ f'clang++ -std=c++14 -O0 {" ".join(auxfiles)} -o {os.path.normpath(mainfile.split(".")[0])}.Clang.O0.exe',
                            f'clang++ -std=c++14 -O2 {" ".join(auxfiles)} -o {os.path.normpath(mainfile.split(".")[0])}.Clang.O2.exe',
                            f'clang++ -std=c++14 -O3 {" ".join(auxfiles)} -o {os.path.normpath(mainfile.split(".")[0])}.Clang.O3.exe',
                            f'g++ -std=c++14 -O0 {" ".join(auxfiles)} -o {os.path.normpath(mainfile.split(".")[0])}.GCC.O0.exe',
                            f'g++ -std=c++14 -O2 {" ".join(auxfiles)} -o {os.path.normpath(mainfile.split(".")[0])}.GCC.O2.exe',
                            f'g++ -std=c++14 -O3 {" ".join(auxfiles)} -o {os.path.normpath(mainfile.split(".")[0])}.GCC.O3.exe',
                            f'{CALL_VCVARS_BAT} && cl /std:c++14 /Od {" ".join(auxfiles)} /Fe:{os.path.normpath(mainfile.split(".")[0])}.MSVC.O0.exe',
                            f'{CALL_VCVARS_BAT} && cl /std:c++14 /O2 {" ".join(auxfiles)} /Fe:{os.path.normpath(mainfile.split(".")[0])}.MSVC.O2.exe',  ],
        "riscv64 Ubuntu": [ f'clang++ -std=c++14 -O0 {" ".join(auxfiles)} -o {mainfile.split(".")[0]}.Clang.O0',
                            f'clang++ -std=c++14 -O2 {" ".join(auxfiles)} -o {mainfile.split(".")[0]}.Clang.O2',
                            f'clang++ -std=c++14 -O3 {" ".join(auxfiles)} -o {mainfile.split(".")[0]}.Clang.O3',
                            f'g++ -std=c++14 -O0 {" ".join(auxfiles)} -o {mainfile.split(".")[0]}.GCC.O0',
                            f'g++ -std=c++14 -O2 {" ".join(auxfiles)} -o {mainfile.split(".")[0]}.GCC.O2',
                            f'g++ -std=c++14 -O3 {" ".join(auxfiles)} -o {mainfile.split(".")[0]}.GCC.O3',  ],
        "arm64 MacOS": [    f'clang++ -std=c++14 -O0 {" ".join(auxfiles)} -o {mainfile.split(".")[0]}.Clang.O0',
                            f'clang++ -std=c++14 -O2 {" ".join(auxfiles)} -o {mainfile.split(".")[0]}.Clang.O2',
                            f'clang++ -std=c++14 -O3 {" ".join(auxfiles)} -o {mainfile.split(".")[0]}.Clang.O3',
                            f'g++-13 -std=c++14 -O0 {" ".join(auxfiles)} -o {mainfile.split(".")[0]}.CPP14.GCC13.O0',
                            f'g++-13 -std=c++14 -O2 {" ".join(auxfiles)} -o {mainfile.split(".")[0]}.CPP14.GCC13.O2',
                            f'g++-13 -std=c++14 -O3 {" ".join(auxfiles)} -o {mainfile.split(".")[0]}.CPP14.GCC13.O3',
                            f'g++-13 -std=gnu11 -O0 {" ".join(auxfiles)} -o {mainfile.split(".")[0]}.GNU11.GCC13.O0',
                            f'g++-13 -std=gnu11 -O2 {" ".join(auxfiles)} -o {mainfile.split(".")[0]}.GNU11.GCC13.O2',
                            f'g++-13 -std=gnu11 -O3 {" ".join(auxfiles)} -o {mainfile.split(".")[0]}.GNU11.GCC13.O3',  ],
    }
    compile_products_dict = {
        "x86_64 Ubuntu": [  f'{mainfile.split(".")[0]}.Clang.O0',
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
                            f'{mainfile.split(".")[0]}.CPP14.GCC13.O3',  ],
        "x86_64 Alpine": [  f'{mainfile.split(".")[0]}.Clang.O0',
                            f'{mainfile.split(".")[0]}.Clang.O2',
                            f'{mainfile.split(".")[0]}.Clang.O3',
                            f'{mainfile.split(".")[0]}.GCC.O0',
                            f'{mainfile.split(".")[0]}.GCC.O2',
                            f'{mainfile.split(".")[0]}.GCC.O3',  ],
        "x86_64 Windows": [ f'{os.path.normpath(mainfile.split(".")[0])}.Clang.O0.exe',
                            f'{os.path.normpath(mainfile.split(".")[0])}.Clang.O2.exe',
                            f'{os.path.normpath(mainfile.split(".")[0])}.Clang.O3.exe',
                            f'{os.path.normpath(mainfile.split(".")[0])}.GCC.O0.exe',
                            f'{os.path.normpath(mainfile.split(".")[0])}.GCC.O2.exe',
                            f'{os.path.normpath(mainfile.split(".")[0])}.GCC.O3.exe',
                            f'{os.path.normpath(mainfile.split(".")[0])}.MSVC.O0.exe',
                            f'{os.path.normpath(mainfile.split(".")[0])}.MSVC.O2.exe',  ],
        "riscv64 Ubuntu": [ f'{mainfile.split(".")[0]}.Clang.O0',
                            f'{mainfile.split(".")[0]}.Clang.O2',
                            f'{mainfile.split(".")[0]}.Clang.O3',
                            f'{mainfile.split(".")[0]}.GCC.O0',
                            f'{mainfile.split(".")[0]}.GCC.O2',
                            f'{mainfile.split(".")[0]}.GCC.O3',  ],
        "arm64 MacOS": [    f'{mainfile.split(".")[0]}.Clang.O0',
                            f'{mainfile.split(".")[0]}.Clang.O2',
                            f'{mainfile.split(".")[0]}.Clang.O3',
                            f'{mainfile.split(".")[0]}.CPP14.GCC13.O0',
                            f'{mainfile.split(".")[0]}.CPP14.GCC13.O2',
                            f'{mainfile.split(".")[0]}.CPP14.GCC13.O3',
                            f'{mainfile.split(".")[0]}.GNU11.GCC13.O0',
                            f'{mainfile.split(".")[0]}.GNU11.GCC13.O2',
                            f'{mainfile.split(".")[0]}.GNU11.GCC13.O3',  ],
    }
    compile_commands = compile_commands_dict[runs_on]
    compile_products = compile_products_dict[runs_on]

    return_status = {}
    this_file_looks_odd = False
    for compile_command, compile_product in zip(compile_commands, compile_products):
        print(compile_command, end=' ')
        result = subprocess.run(compile_command, shell=True)
        if result.returncode != 0:
            print(f'{RED}CE({result.returncode}){RESET}')
            this_file_looks_odd = True
            status_vector = [f'CE({result.returncode})']
        else: 
            status_vector = ['Compile OK']
            print(f'{GREEN}OK{RESET}')

            for e in examples:
                print(f'{compile_product} < {e} > {e.replace(".in", ".out")}', end=' ')
                with open(e, 'r') as fstdin:
                    with open(e.replace(".in", ".out"), 'w') as fstdout:
                        result = subprocess.run(f'{os.path.join(os.path.curdir, compile_product)}', stdin=fstdin, stdout=fstdout, shell=True)
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
        print(f'::error file={mainfile},title=Potential UB::{RED}Please take a look.{RESET}')
    for key in return_status:
        print(f'-  {key}: ', end='')
        for _ in return_status[key]:
            print(f'{get_color(_)}{_}{RESET}', end='; ')
        print()
    print()
    return this_file_looks_odd, return_status

cnt_ac, cnt_error = 0, 0
output = {}
for mainfile, auxfile, example, skiptest in zip(mainfiles, auxfiles, examples, skiptests):
    this_file_looks_odd, return_status = ub_check(mainfile, auxfile, example, skiptest)
    output[mainfile] = return_status
    if this_file_looks_odd:
        cnt_error += 1
    else:
        cnt_ac += 1

with open("output.txt", "w") as f:
    f.write(str(output))
