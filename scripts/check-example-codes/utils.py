import os


def get_auxfiles(code_file):
    dirname = os.path.dirname(code_file)
    basename, extname = os.path.splitext(os.path.basename(code_file))
    auxfiles = []
    for root, _, files in os.walk(dirname):
        for file in files:
            if file.split(".")[0] == basename.split(".")[0] and file.endswith(extname):
                auxfiles.append(os.path.normpath(os.path.join(root, file)))
    return auxfiles


def get_examples(code_file):
    dirname = os.path.dirname(code_file)
    basename = os.path.splitext(os.path.basename(code_file))[0]
    examples_dir = dirname.replace("code", "examples")
    in_file = os.path.normpath(os.path.join(examples_dir, basename + ".in"))
    out_file = os.path.normpath(os.path.join(examples_dir, basename + ".out"))
    ans_file = os.path.normpath(os.path.join(examples_dir, basename + ".ans"))
    return in_file, out_file, ans_file


RED, GREEN, BLUE, RESET = "\033[0;31m", "\033[0;32m", "\033[0;34m", "\033[0m"
STATUS_COLOR = lambda status: GREEN if status == "AC" else RED
incolor = lambda color, text: f"{color}{text}{RESET}"
