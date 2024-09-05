import os
import subprocess

OUTPUT_UBUNTU   = eval(os.environ.get('OUTPUT_UBUNTU', ''))
OUTPUT_MACOS    = eval(os.environ.get('OUTPUT_MACOS', ''))
OUTPUT_ALPINE   = eval(os.environ.get('OUTPUT_ALPINE', ''))
OUTPUT_WINDOWS  = eval(os.environ.get('OUTPUT_WINDOWS', ''))
OUTPUT_RV       = eval(os.environ.get('OUTPUT_RV', ''))

with open(os.environ.get('GITHUB_STEP_SUMMARY'), 'w') as f:
    any_file_looks_odd = False
    for key in OUTPUT_UBUNTU:
        assert all(key in d for d in [OUTPUT_UBUNTU, OUTPUT_MACOS, OUTPUT_ALPINE, OUTPUT_WINDOWS, OUTPUT_RV])
        this_file_looks_odd = False
        print(f'\n## {key}\n')
        f.write(f'\n## **{key}**\n')

        for sysinfo, output in zip(['x86_64 Ubuntu 22.04', 'Arm64 macOS 12.0', 'x86_64 Alpine with MUSL', 'x86_64 Windows 10', 'RISC-V64 Ubuntu 22.04'], [OUTPUT_UBUNTU, OUTPUT_MACOS, OUTPUT_ALPINE, OUTPUT_WINDOWS, OUTPUT_RV]):
            print(f'## {sysinfo}')
            f.write(f'\n## {sysinfo}\n')
            for line in output[key]:
                output_line = ', '.join(output[key][line])
                print(f'- {line}: {output_line}')
                f.write(f'- {line}: {output_line}\n')
                if 'CE' in output[key][line]:
                    this_file_looks_odd = True
                if 'RE' in output[key][line]:
                    this_file_looks_odd = True
                if 'WA' in output[key][line]:
                    this_file_looks_odd = True

        if this_file_looks_odd:
            any_file_looks_odd = True
            f.write(f'\n疑似存在未定义行为，请核实\n')
    if any_file_looks_odd:
        exit(-1)
