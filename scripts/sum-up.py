import os
import subprocess

OUTPUT_UBUNTU   = eval(os.environ.get('OUTPUT_UBUNTU', ''))
OUTPUT_MACOS    = eval(os.environ.get('OUTPUT_MACOS', ''))
OUTPUT_ALPINE   = eval(os.environ.get('OUTPUT_ALPINE', ''))
OUTPUT_WINDOWS  = eval(os.environ.get('OUTPUT_WINDOWS', ''))
OUTPUT_RV       = eval(os.environ.get('OUTPUT_RV', ''))

RED = "\033[0;31m"
GREEN = "\033[0;32m"
YELLOW = "\033[0;33m"
BLUE = "\033[0;34m"
PURPLE = "\033[0;35m"
CYAN = "\033[0;36m"
WHITE = "\033[0;37m"
RESET = "\033[0m"

with open(os.environ.get('GITHUB_STEP_SUMMARY'), 'w') as f:
    any_file_looks_odd = False
    for key in OUTPUT_UBUNTU:
        assert all(key in d for d in [OUTPUT_UBUNTU, OUTPUT_MACOS, OUTPUT_ALPINE, OUTPUT_WINDOWS, OUTPUT_RV])
        this_file_looks_odd = False
        print(f'\n## {key}\n')
        f.write(f'\n## **{key}**\n')

        for sysinfo, output in zip(['x86_64 Ubuntu 22.04', 'Arm64 macOS 12.0', 'x86_64 Alpine with MUSL', 'x86_64 Windows 2022', 'RISC-V64 Ubuntu 22.04'], [OUTPUT_UBUNTU, OUTPUT_MACOS, OUTPUT_ALPINE, OUTPUT_WINDOWS, OUTPUT_RV]):
            print(f'### {sysinfo}')
            f.write(f'\n### {sysinfo}\n')
            for line in output[key]:
                output_line = ', '.join(output[key][line])
                if any(_2 in _1 for _1 in output[key][line] for _2 in ['CE', 'RE', 'WA']):
                    print(f'- {line}: {RED}{output_line}{RESET}')
                    f.write(f'- **{line}: {output_line}**\n')
                    this_file_looks_odd = True
                else:
                    print(f'- {line}: {GREEN}{output_line}{RESET}')
                    f.write(f'- {line}: {output_line}\n')

        if this_file_looks_odd:
            any_file_looks_odd = True
            f.write(f'\n疑似存在未定义行为，请核实\n')
    if any_file_looks_odd:
        exit(-1)
