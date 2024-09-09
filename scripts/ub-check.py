import os
import subprocess
from dataclasses import dataclass

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

incolor = lambda color, text: f"{color}{text}{RESET}"

@dataclass(frozen=True)
class Status:
    errcode: int
    color: str

    def __str__(self):
        return f'{self.__class__.__name__}({self.errcode})'
    
    def colored(self):
        return f'{self.color}{self}{RESET}'

@dataclass(frozen=True)
class CompileOK(Status):
    errcode: int = 0
    color: str = GREEN

@dataclass(frozen=True)
class CE(Status):
    errcode: int
    color: str = RED

@dataclass(frozen=True)
class AC(Status):
    errcode: int = 0
    color: str = GREEN

@dataclass(frozen=True)
class RE(Status):
    errcode: int
    color: str = RED

@dataclass(frozen=True)
class WA(Status):
    errcode: int
    color: str = RED

@dataclass(frozen=True)
class Skipped(Status):
    errcode: int = 0
    color: str = BLUE
    
def ub_check(mainfile, auxfiles, examples, skiptest):
    """
    Check for undefined behavior.
    """

    print(incolor(BLUE, f"Test for {mainfile}..."))
    if skiptest:
        print(incolor(BLUE, f"Test for {mainfile} skipped because file {mainfile + '.skip_test'} exists"))
        return False, {mainfile, Skipped()}
    
    CALL_VCVARS_BAT = r'call "C:\Program Files\Microsoft Visual Studio\2022\Enterprise\VC\Auxiliary\Build\vcvars64.bat"'
    def arrgen(compilers, standards, optimizations, auxfiles, sanitizers, mainfile, omit_ms_style=False):
        assert compilers is not None and compilers != []
        standards = standards if standards is not None else [('', '.NA')]
        optimizations = optimizations if optimizations is not None else [('', '.NA')]
        sanitizers = sanitizers if sanitizers is not None else [('', '.NA')]
        if not omit_ms_style:
            return [
            f'{compiler} {standard} {optimization} {sanitizer} {" ".join(auxfiles)} /Fe:{mainfile.split(".")[0]}{c_name}{s_name}{o_name}{san_name}' 
            for compiler, c_name in compilers
            for standard, s_name in standards
            for optimization, o_name in optimizations
            for sanitizer, san_name in sanitizers
        ]
        else: 
            return [
            f'{compiler} {standard} {optimization} {sanitizer} {" ".join(auxfiles)} -o {mainfile.split(".")[0]}{c_name}{s_name}{o_name}{san_name}' 
            for compiler, c_name in compilers
            for standard, s_name in standards
            for optimization, o_name in optimizations
            for sanitizer, san_name in sanitizers
        ]

    def productgen(compilers, standards, optimizations, auxfiles, sanitizers, mainfile):
        assert compilers is not None and compilers != []
        standards = standards if standards is not None else [('', '.NA')]
        optimizations = optimizations if optimizations is not None else [('', '.NA')]
        sanitizers = sanitizers if sanitizers is not None else [('', '.NA')]
        return [
            f'{mainfile.split(".")[0]}{c_name}{s_name}{o_name}{san_name}'
            for _, c_name in compilers
            for _, s_name in standards
            for _, o_name in optimizations
            for _, san_name in sanitizers
        ]
    
    compile_commands_dict = {
        "x86_64 Ubuntu": arrgen(
            compilers=[('clang++', '.Clang'), ('g++-9', '.GCC9'), ('g++-13', '.GCC13')],
            standards=[('-std=c++14', '.CPP14'), ('-std=gnu++20', '.GNU20'), ('', '.NA')],
            optimizations=[('-O0', '.O0'), ('-O2', '.O2'), ('-O3', '.O3'), ('', '.NA')],
            sanitizers=[('', '.NA')],
            auxfiles=auxfiles,
            mainfile=mainfile
        ) + arrgen(
            compilers=[('clang++', '.Clang'), ('g++-13', '.GCC13')],
            standards=[('', '.NA')],
            optimizations=[('', '.NA')],
            sanitizers=[('-fsanitize=undefined,address', '.UBSAN-ASAN')],
            auxfiles=auxfiles,
            mainfile=mainfile
        ),
        "x86_64 Alpine": arrgen(
            compilers=[('clang++', '.Clang'), ('g++', '.GCC')],
            standards=[('', '.NA')],
            optimizations=[('-O0', '.O0'), ('-O2', '.O2'), ('-O3', '.O3')],
            sanitizers=[('', '.NA')],
            auxfiles=auxfiles,
            mainfile=mainfile
        ),
        "x86_64 Windows": arrgen(
            compilers=[('clang++', '.Clang'), ('g++', '.GCC')],
            standards=[('', '.NA')],
            optimizations=[('-O0', '.O0'), ('-O2', '.O2'), ('-O3', '.O3')],
            sanitizers=[('', '.NA')],
            auxfiles=auxfiles,
            mainfile=mainfile
        ) + arrgen(
            compilers=[(f'{CALL_VCVARS_BAT} && cl.exe', '.MSVC')],
            standards=[('', '.NA')],
            optimizations=[('/Od', '.O0'), ('/O2', '.O2')],
            sanitizers=[('', '.NA')],
            auxfiles=auxfiles,
            mainfile=mainfile,
            omit_ms_style=True
        ),
        "riscv64 Ubuntu": arrgen(
            compilers=[('clang++', '.Clang'), ('g++', '.GCC')],
            standards=[('', '.NA')],
            optimizations=[('-O0', '.O0'), ('-O2', '.O2'), ('-O3', '.O3')],
            sanitizers=[('', '.NA')],
            auxfiles=auxfiles,
            mainfile=mainfile
        ),
        "arm64 MacOS": arrgen(
            compilers=[('clang++', '.Clang'), ('g++-13', '.GCC13')],
            standards=[('-std=c++14', '.CPP14'), ('-std=gnu++20', '.GNU20'), ('', '.NA')],
            optimizations=[('-O0', '.O0'), ('-O2', '.O2'), ('-O3', '.O3'), ('', '.NA')],
            sanitizers=[('', '.NA')],
            auxfiles=auxfiles,
            mainfile=mainfile
        )
    }
    compile_products_dict = {
        "x86_64 Ubuntu": productgen(
            compilers=[('clang++', '.Clang'), ('g++-9', '.GCC9'), ('g++-13', '.GCC13')],
            standards=[('-std=c++14', '.CPP14'), ('-std=gnu++20', '.GNU20'), ('', '.NA')],
            optimizations=[('-O0', '.O0'), ('-O2', '.O2'), ('-O3', '.O3'), ('', '.NA')],
            sanitizers=[('', '.NA')],
            auxfiles=auxfiles,
            mainfile=mainfile
        ) + productgen(
            compilers=[('clang++', '.Clang'), ('g++-13', '.GCC13')],
            standards=[('', '.NA')],
            optimizations=[('', '.NA')],
            sanitizers=[('-fsanitize=undefined,address', '.UBSAN-ASAN')],
            auxfiles=auxfiles,
            mainfile=mainfile
        ),
        "x86_64 Alpine": productgen(
            compilers=[('clang++', '.Clang'), ('g++', '.GCC')],
            standards=[('', '.NA')],
            optimizations=[('-O0', '.O0'), ('-O2', '.O2'), ('-O3', '.O3')],
            sanitizers=[('', '.NA')],
            auxfiles=auxfiles,
            mainfile=mainfile
        ),
        "x86_64 Windows": productgen(
            compilers=[('clang++', '.Clang'), ('g++', '.GCC')],
            standards=[('', '.NA')],
            optimizations=[('-O0', '.O0'), ('-O2', '.O2'), ('-O3', '.O3')],
            sanitizers=[('', '.NA')],
            auxfiles=auxfiles,
            mainfile=mainfile
        ) + productgen(
            compilers=[(f'{CALL_VCVARS_BAT} && cl.exe', '.MSVC')],
            standards=[('', '.NA')],
            optimizations=[('/Od', '.O0'), ('/O2', '.O2')],
            sanitizers=[('', '.NA')],
            auxfiles=auxfiles,
            mainfile=mainfile
        ),
        "riscv64 Ubuntu": productgen(
            compilers=[('clang++', '.Clang'), ('g++', '.GCC')],
            standards=[('', '.NA')],
            optimizations=[('-O0', '.O0'), ('-O2', '.O2'), ('-O3', '.O3')],
            sanitizers=[('', '.NA')],
            auxfiles=auxfiles,
            mainfile=mainfile
        ),
        "arm64 MacOS": productgen(
            compilers=[('clang++', '.Clang'), ('g++-13', '.GCC13')],
            standards=[('-std=c++14', '.CPP14'), ('-std=gnu++20', '.GNU20'), ('', '.NA')],
            optimizations=[('-O0', '.O0'), ('-O2', '.O2'), ('-O3', '.O3'), ('', '.NA')],
            sanitizers=[('', '.NA')],
            auxfiles=auxfiles,
            mainfile=mainfile
        )
    }
    # compile_commands_dict = {
    #     "x86_64 Ubuntu": [  f'clang++ -std=c++14 -O0 {" ".join(auxfiles)} -o {mainfile.split(".")[0]}.Clang.CPP14.O0',
    #                         f'clang++ -std=c++14 -O2 {" ".join(auxfiles)} -o {mainfile.split(".")[0]}.Clang.CPP14.O2',
    #                         f'clang++ -std=c++14 -O3 {" ".join(auxfiles)} -o {mainfile.split(".")[0]}.Clang.CPP14.O3',
    #                         f'clang++ -O0 {" ".join(auxfiles)} -o {mainfile.split(".")[0]}.Clang.O0',
    #                         f'clang++ -O2 {" ".join(auxfiles)} -o {mainfile.split(".")[0]}.Clang.O2',
    #                         f'clang++ -O3 {" ".join(auxfiles)} -o {mainfile.split(".")[0]}.Clang.O3',
    #                         f'g++-9 -std=c++14 -O0 -static {" ".join(auxfiles)} -o {mainfile.split(".")[0]}.CPP14.GCC9.O0',
    #                         f'g++-9 -std=c++14 -O2 -static {" ".join(auxfiles)} -o {mainfile.split(".")[0]}.CPP14.GCC9.O2', # NOI 2023
    #                         f'g++-9 -std=c++14 -O3 -static {" ".join(auxfiles)} -o {mainfile.split(".")[0]}.CPP14.GCC9.O3',
    #                         f'g++-13 -std=gnu++20 -O0 -static {" ".join(auxfiles)} -o {mainfile.split(".")[0]}.GNU20.GCC13.O0',
    #                         f'g++-13 -std=gnu++20 -O2 -static {" ".join(auxfiles)} -o {mainfile.split(".")[0]}.GNU20.GCC13.O2', # ACM ICPC 2023
    #                         f'g++-13 -std=gnu++20 -O3 -static {" ".join(auxfiles)} -o {mainfile.split(".")[0]}.GNU20.GCC13.O3', 
    #                         f'g++-13 -std=c++14 -O0 -static {" ".join(auxfiles)} -o {mainfile.split(".")[0]}.CPP14.GCC13.O0',
    #                         f'g++-13 -std=c++14 -O2 -static {" ".join(auxfiles)} -o {mainfile.split(".")[0]}.CPP14.GCC13.O2',
    #                         f'g++-13 -std=c++14 -O3 -static {" ".join(auxfiles)} -o {mainfile.split(".")[0]}.CPP14.GCC13.O3',
    #                         f'g++-13 -O0 -static {" ".join(auxfiles)} -o {mainfile.split(".")[0]}.GCC13.O0',
    #                         f'g++-13 -O2 -static {" ".join(auxfiles)} -o {mainfile.split(".")[0]}.GCC13.O2',
    #                         f'g++-13 -O3 -static {" ".join(auxfiles)} -o {mainfile.split(".")[0]}.GCC13.O3',
    #                         f'g++-13 -fsanitize=undefined,address {" ".join(auxfiles)} -o {mainfile.split(".")[0]}.GCC13.Sanitize'  ], # Sanitizer Activated
    #     "x86_64 Alpine": [  f'clang++ -O0 {" ".join(auxfiles)} -o {mainfile.split(".")[0]}.Clang.O0',
    #                         f'clang++ -O2 {" ".join(auxfiles)} -o {mainfile.split(".")[0]}.Clang.O2',
    #                         f'clang++ -O3 {" ".join(auxfiles)} -o {mainfile.split(".")[0]}.Clang.O3',
    #                         f'g++ -O0 {" ".join(auxfiles)} -o {mainfile.split(".")[0]}.GCC.O0',
    #                         f'g++ -O2 {" ".join(auxfiles)} -o {mainfile.split(".")[0]}.GCC.O2',
    #                         f'g++ -O3 {" ".join(auxfiles)} -o {mainfile.split(".")[0]}.GCC.O3',  ],
    #     "x86_64 Windows": [ f'clang++ -O0 {" ".join(auxfiles)} -o {os.path.normpath(mainfile.split(".")[0])}.Clang.O0.exe',
    #                         f'clang++ -O2 {" ".join(auxfiles)} -o {os.path.normpath(mainfile.split(".")[0])}.Clang.O2.exe',
    #                         f'clang++ -O3 {" ".join(auxfiles)} -o {os.path.normpath(mainfile.split(".")[0])}.Clang.O3.exe',
    #                         f'g++ -O0 {" ".join(auxfiles)} -o {os.path.normpath(mainfile.split(".")[0])}.GCC.O0.exe',
    #                         f'g++ -O2 {" ".join(auxfiles)} -o {os.path.normpath(mainfile.split(".")[0])}.GCC.O2.exe',
    #                         f'g++ -O3 {" ".join(auxfiles)} -o {os.path.normpath(mainfile.split(".")[0])}.GCC.O3.exe',
    #                         f'{CALL_VCVARS_BAT} && cl /Od {" ".join(auxfiles)} /Fe:{os.path.normpath(mainfile.split(".")[0])}.MSVC.O0.exe',
    #                         f'{CALL_VCVARS_BAT} && cl /O2 {" ".join(auxfiles)} /Fe:{os.path.normpath(mainfile.split(".")[0])}.MSVC.O2.exe',  ],
    #     "riscv64 Ubuntu": [ f'clang++ -O0 {" ".join(auxfiles)} -o {mainfile.split(".")[0]}.Clang.O0',
    #                         f'clang++ -O2 {" ".join(auxfiles)} -o {mainfile.split(".")[0]}.Clang.O2',
    #                         f'clang++ -O3 {" ".join(auxfiles)} -o {mainfile.split(".")[0]}.Clang.O3',
    #                         f'g++ -O0 {" ".join(auxfiles)} -o {mainfile.split(".")[0]}.GCC.O0',
    #                         f'g++ -O2 {" ".join(auxfiles)} -o {mainfile.split(".")[0]}.GCC.O2',
    #                         f'g++ -O3 {" ".join(auxfiles)} -o {mainfile.split(".")[0]}.GCC.O3',  ],
    #     "arm64 MacOS": [    f'clang++ -O0 {" ".join(auxfiles)} -o {mainfile.split(".")[0]}.Clang.O0',
    #                         f'clang++ -O2 {" ".join(auxfiles)} -o {mainfile.split(".")[0]}.Clang.O2',
    #                         f'clang++ -O3 {" ".join(auxfiles)} -o {mainfile.split(".")[0]}.Clang.O3',
    #                         f'g++-13 -std=c++14 -O0 {" ".join(auxfiles)} -o {mainfile.split(".")[0]}.CPP14.GCC13.O0',
    #                         f'g++-13 -std=c++14 -O2 {" ".join(auxfiles)} -o {mainfile.split(".")[0]}.CPP14.GCC13.O2',
    #                         f'g++-13 -std=c++14 -O3 {" ".join(auxfiles)} -o {mainfile.split(".")[0]}.CPP14.GCC13.O3',
    #                         f'g++-13 -std=gnu++20 -O0 {" ".join(auxfiles)} -o {mainfile.split(".")[0]}.GNU20.GCC13.O0',
    #                         f'g++-13 -std=gnu++20 -O2 {" ".join(auxfiles)} -o {mainfile.split(".")[0]}.GNU20.GCC13.O2',
    #                         f'g++-13 -std=gnu++20 -O3 {" ".join(auxfiles)} -o {mainfile.split(".")[0]}.GNU20.GCC13.O3',
    #                         f'g++-13 -O0 {" ".join(auxfiles)} -o {mainfile.split(".")[0]}.GCC13.O0',
    #                         f'g++-13 -O2 {" ".join(auxfiles)} -o {mainfile.split(".")[0]}.GCC13.O2',
    #                         f'g++-13 -O3 {" ".join(auxfiles)} -o {mainfile.split(".")[0]}.GCC13.O3',  ],
    # }
    # compile_products_dict = {
    #     "x86_64 Ubuntu": [  f'{mainfile.split(".")[0]}.Clang.CPP14.O0',
    #                         f'{mainfile.split(".")[0]}.Clang.CPP14.O2',
    #                         f'{mainfile.split(".")[0]}.Clang.CPP14.O3',
    #                         f'{mainfile.split(".")[0]}.Clang.O0',
    #                         f'{mainfile.split(".")[0]}.Clang.O2',
    #                         f'{mainfile.split(".")[0]}.Clang.O3',
    #                         f'{mainfile.split(".")[0]}.CPP14.GCC9.O0',
    #                         f'{mainfile.split(".")[0]}.CPP14.GCC9.O2', # NOI 2023
    #                         f'{mainfile.split(".")[0]}.CPP14.GCC9.O3',
    #                         f'{mainfile.split(".")[0]}.GNU20.GCC13.O0',
    #                         f'{mainfile.split(".")[0]}.GNU20.GCC13.O2', # ACM ICPC 2023
    #                         f'{mainfile.split(".")[0]}.GNU20.GCC13.O3', 
    #                         f'{mainfile.split(".")[0]}.CPP14.GCC13.O0',
    #                         f'{mainfile.split(".")[0]}.CPP14.GCC13.O2',
    #                         f'{mainfile.split(".")[0]}.CPP14.GCC13.O3',
    #                         f'{mainfile.split(".")[0]}.GCC13.O0',
    #                         f'{mainfile.split(".")[0]}.GCC13.O2',
    #                         f'{mainfile.split(".")[0]}.GCC13.O3',
    #                         f'{mainfile.split(".")[0]}.GCC13.Sanitize'  ],
    #     "x86_64 Alpine": [  f'{mainfile.split(".")[0]}.Clang.O0',
    #                         f'{mainfile.split(".")[0]}.Clang.O2',
    #                         f'{mainfile.split(".")[0]}.Clang.O3',
    #                         f'{mainfile.split(".")[0]}.GCC.O0',
    #                         f'{mainfile.split(".")[0]}.GCC.O2',
    #                         f'{mainfile.split(".")[0]}.GCC.O3',  ],
    #     "x86_64 Windows": [ f'{os.path.normpath(mainfile.split(".")[0])}.Clang.O0.exe',
    #                         f'{os.path.normpath(mainfile.split(".")[0])}.Clang.O2.exe',
    #                         f'{os.path.normpath(mainfile.split(".")[0])}.Clang.O3.exe',
    #                         f'{os.path.normpath(mainfile.split(".")[0])}.GCC.O0.exe',
    #                         f'{os.path.normpath(mainfile.split(".")[0])}.GCC.O2.exe',
    #                         f'{os.path.normpath(mainfile.split(".")[0])}.GCC.O3.exe',
    #                         f'{os.path.normpath(mainfile.split(".")[0])}.MSVC.O0.exe',
    #                         f'{os.path.normpath(mainfile.split(".")[0])}.MSVC.O2.exe',  ],
    #     "riscv64 Ubuntu": [ f'{mainfile.split(".")[0]}.Clang.O0',
    #                         f'{mainfile.split(".")[0]}.Clang.O2',
    #                         f'{mainfile.split(".")[0]}.Clang.O3',
    #                         f'{mainfile.split(".")[0]}.GCC.O0',
    #                         f'{mainfile.split(".")[0]}.GCC.O2',
    #                         f'{mainfile.split(".")[0]}.GCC.O3',  ],
    #     "arm64 MacOS": [    f'{mainfile.split(".")[0]}.Clang.O0',
    #                         f'{mainfile.split(".")[0]}.Clang.O2',
    #                         f'{mainfile.split(".")[0]}.Clang.O3',
    #                         f'{mainfile.split(".")[0]}.CPP14.GCC13.O0',
    #                         f'{mainfile.split(".")[0]}.CPP14.GCC13.O2',
    #                         f'{mainfile.split(".")[0]}.CPP14.GCC13.O3',
    #                         f'{mainfile.split(".")[0]}.GNU20.GCC13.O0',
    #                         f'{mainfile.split(".")[0]}.GNU20.GCC13.O2',
    #                         f'{mainfile.split(".")[0]}.GNU20.GCC13.O3',
    #                         f'{mainfile.split(".")[0]}.GCC13.O0',
    #                         f'{mainfile.split(".")[0]}.GCC13.O2',
    #                         f'{mainfile.split(".")[0]}.GCC13.O3',  ],
    # }
    compile_commands = compile_commands_dict[runs_on]
    compile_products = compile_products_dict[runs_on]

    return_status = {}
    this_file_looks_odd = False
    for compile_command, compile_product in zip(compile_commands, compile_products):
        print(compile_command, end=' ')
        result = subprocess.run(compile_command, shell=True)
        if result.returncode != 0:
            this_file_looks_odd = True
            status_vector = [CE(result.returncode)]
            print(status_vector[0].colored())
        else: 
            status_vector = [CompileOK()]
            print(status_vector[0].colored())

            for e in examples:
                print(f'{compile_product} < {e} > {e.replace(".in", ".out")}', end=' ')
                with open(e, 'r') as fstdin:
                    with open(e.replace(".in", ".out"), 'w') as fstdout:
                        result = subprocess.run(f'{os.path.join(os.path.curdir, compile_product)}', stdin=fstdin, stdout=fstdout, shell=True)
                if result.returncode != 0:
                    this_file_looks_odd = True
                    status_vector.append(RE(result.returncode))
                    print(status_vector[-1].colored())
                else:
                    print(incolor(GREEN, 'OK'))
                    print(f'diff -b -B {e.replace(".in", ".out")} {e.replace(".in", ".ans")}', end=' ')
                    result = subprocess.run(f'diff -b -B {e.replace(".in", ".out")} {e.replace(".in", ".ans")}', shell=True)
                    if result.returncode != 0:
                        this_file_looks_odd = True
                        status_vector.append(WA(result.returncode))
                    else:
                        status_vector.append(AC())
                    print(status_vector[-1].colored())
        print(f'{compile_product.split(os.path.pathsep)[-1]}: ', end='')
        for _ in status_vector:
            print(_.colored(), end='; ')
        print()
        return_status[compile_product] = status_vector

    print(incolor(BLUE, f'Result for {mainfile}: '))
    if this_file_looks_odd:
        print(f'::error file={mainfile},title=Potential UB::Please take a look.')
    for key in return_status:
        print(f'-  {key}: ', end='')
        for _ in return_status[key]:
            print(_.colored(), end='; ')
        print()
    print()
    return this_file_looks_odd, return_status

cnt_ac, cnt_error = 0, 0
output = {}
for mainfile, auxfile, example, skiptest in zip(mainfiles, auxfiles, examples, skiptests):
    this_file_looks_odd, return_status = ub_check(mainfile, auxfile, example, skiptest)
    output_status = {}
    for key in return_status:
        output_status[key] = [str(_) for _ in return_status[key]]
    output[mainfile] = output_status
    if this_file_looks_odd:
        cnt_error += 1
    else:
        cnt_ac += 1

with open("output.txt", "w") as f:
    f.write(str(output))
