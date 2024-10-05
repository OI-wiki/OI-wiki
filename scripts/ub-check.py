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

    def gen(compilers, standards, optimizations, auxfiles, sanitizers, mainfile, omit_ms_style=False):
        assert compilers is not None and compilers != []
        assert standards is not None and standards != []
        assert optimizations is not None and optimizations != []
        assert sanitizers is not None and sanitizers != []

        def arrgen():
            if not omit_ms_style:
                return [
                f'{compiler} {standard} {optimization} {sanitizer} {" ".join(auxfiles)} -o {mainfile.split(".")[0]}{c_name}{s_name}{o_name}{san_name}' 
                for compiler, c_name in compilers
                for standard, s_name in standards
                for optimization, o_name in optimizations
                for sanitizer, san_name in sanitizers ]
            else: 
                return [
                f'{compiler} {standard} {optimization} {sanitizer} {" ".join(auxfiles)} /Fe:{os.path.normpath(mainfile.split(".")[0])}{c_name}{s_name}{o_name}{san_name}' 
                for compiler, c_name in compilers
                for standard, s_name in standards
                for optimization, o_name in optimizations
                for sanitizer, san_name in sanitizers
            ]

        def productgen():
            return [
                f'{os.path.normpath(mainfile.split(".")[0])}{c_name}{s_name}{o_name}{san_name}'
                for _, c_name in compilers
                for _, s_name in standards
                for _, o_name in optimizations
                for _, san_name in sanitizers
            ]
        
        return (arrgen(), productgen())
    
    concat = lambda a, b: (a[0] + b[0], a[1] + b[1])
    map = {
        "x86_64 Ubuntu": concat(gen(
            compilers=[('clang++', '.Clang'), ('g++-9', '.GCC9'), ('g++-13', '.GCC13')],
            standards=[('-std=c++14', '.CPP14'), ('-std=c++17', '.CPP17'), ('-std=c++2a', '.CPP20')],
            optimizations=[('-O0', '.O0'), ('-O2', '.O2'), ('-O3', '.O3')],
            sanitizers=[('', '.NA')],
            auxfiles=auxfiles,
            mainfile=mainfile
        ), gen(
            compilers=[('clang++', '.Clang'), ('g++-13', '.GCC13')],
            standards=[('-std=c++14', '.CPP14'), ('-std=c++17', '.CPP17'), ('-std=c++2a', '.CPP20')],
            optimizations=[('', '.NA')],
            sanitizers=[('-fsanitize=undefined,address', '.UBSAN-ASAN')],
            auxfiles=auxfiles,
            mainfile=mainfile
        )),
        "x86_64 Alpine": gen(
            compilers=[('clang++', '.Clang'), ('g++', '.GCC')],
            standards=[('-std=c++14', '.CPP14'), ('-std=c++17', '.CPP17'), ('-std=c++2a', '.CPP20')],
            optimizations=[('-O0', '.O0'), ('-O2', '.O2'), ('-O3', '.O3')],
            sanitizers=[('', '.NA')],
            auxfiles=auxfiles,
            mainfile=mainfile
        ),
        "x86_64 Windows": concat(gen(
            compilers=[('clang++', '.Clang'), ('g++', '.GCC')],
            standards=[('-std=c++14', '.CPP14'), ('-std=c++17', '.CPP17'), ('-std=c++2a', '.CPP20')],
            optimizations=[('-O0', '.O0'), ('-O2', '.O2'), ('-O3', '.O3')],
            sanitizers=[('', '.NA')],
            auxfiles=auxfiles,
            mainfile=mainfile
        ), gen(
            compilers=[(f'{CALL_VCVARS_BAT} && cl.exe /EHsc', '.MSVC')],
            standards=[('/std:c++14', '.CPP14'), ('/std:c++17', '.CPP17'), ('/std:c++20', '.CPP20')],
            optimizations=[('/Od', '.O0'), ('/O2', '.O2')],
            sanitizers=[('', '.NA')],
            auxfiles=auxfiles,
            mainfile=mainfile,
            omit_ms_style=True
        )),
        "riscv64 Ubuntu": gen(
            compilers=[('clang++', '.Clang'), ('g++', '.GCC')],
            standards=[('-std=c++14', '.CPP14'), ('-std=c++17', '.CPP17'), ('-std=c++2a', '.CPP20')],
            optimizations=[('-O0', '.O0'), ('-O2', '.O2'), ('-O3', '.O3')],
            sanitizers=[('', '.NA')],
            auxfiles=auxfiles,
            mainfile=mainfile
        ),
        "arm64 MacOS": gen(
            compilers=[('clang++', '.Clang'), ('g++-13', '.GCC13')],
            standards=[('-std=c++14', '.CPP14'), ('-std=c++17', '.CPP17'), ('-std=c++2a', '.CPP20')],
            optimizations=[('-O0', '.O0'), ('-O2', '.O2'), ('-O3', '.O3')],
            sanitizers=[('', '.NA')],
            auxfiles=auxfiles,
            mainfile=mainfile
        )
    }

    compile_commands_dict = {
        "x86_64 Ubuntu": map["x86_64 Ubuntu"][0],
        "x86_64 Alpine": map["x86_64 Alpine"][0],
        "x86_64 Windows": map["x86_64 Windows"][0],
        "riscv64 Ubuntu": map["riscv64 Ubuntu"][0],
        "arm64 MacOS": map["arm64 MacOS"][0]
    }

    compile_products_dict = {
        "x86_64 Ubuntu": map["x86_64 Ubuntu"][1],
        "x86_64 Alpine": map["x86_64 Alpine"][1],
        "x86_64 Windows": map["x86_64 Windows"][1],
        "riscv64 Ubuntu": map["riscv64 Ubuntu"][1],
        "arm64 MacOS": map["arm64 MacOS"][1]
    }
    
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
        for status in status_vector:
            print(status.colored(), end='; ')
        print()
        return_status[compile_product] = status_vector

    print(incolor(BLUE, f'Result for {mainfile}: '))
    if this_file_looks_odd:
        print(f'::error file={mainfile},title=Potential UB::Please take a look.')
    for key in return_status:
        print(f'-  {key}: ', end='')
        for status in return_status[key]:
            print(status.colored(), end='; ')
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
