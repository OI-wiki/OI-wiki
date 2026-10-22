# Find related files to conduct correctness check and undefined behavior checks.
# input: changed files (from tj-actions/changed-files, read from the all_changed_files environment variable)
# output: related files to test (write to $GITHUB_OUTPUT, access by setting env to the output and with os.environ.get())

import os

# Extensions of the source files that can be tested.
extnames = [".cpp"]


def resolve_mainfile(file):
    """
    Resolve a changed source file to the main file it belongs to.

    Variants such as `foo.1.cpp` are tested through their main file `foo.cpp`.
    """
    dirname = os.path.dirname(file)
    basename, extname = os.path.splitext(os.path.basename(file))
    if "." in basename:
        basename = basename.split(".")[0]
    return os.path.normpath(os.path.join(dirname, basename + extname))


def resolve_mainfiles(example_file):
    """
    Resolve a changed example data file to the code files using it.

    `docs/<...>/examples/<topic>/foo.in` is used by
    `docs/<...>/code/<topic>/foo.<extname>`, for every supported extension.
    """
    dirname = os.path.dirname(example_file)
    basename = os.path.splitext(os.path.basename(example_file))[0]
    pos = dirname.rfind("/examples/")
    if pos == -1:
        return []
    code_dir = dirname[:pos] + "/code/" + dirname[pos + len("/examples/") :]
    return [os.path.join(code_dir, basename + extname) for extname in extnames]


def output(name, value):
    """Write an output variable to the GitHub Actions output file."""
    with open(os.environ.get("GITHUB_OUTPUT"), "a") as f:
        f.write(f"{name}={value}\n")


def get_files_to_test(filenames):
    mainfiles_to_test = set()
    mainfiles, auxfiles, examples, skiptest = [], [], [], []

    for filename in filenames:
        dirname, basename, extname = (
            os.path.dirname(filename),
            os.path.splitext(os.path.basename(filename))[0],
            os.path.splitext(filename)[1],
        )
        is_code_file = extname in extnames

        # 改动文件是代码文件时测试它的主文件，是测试数据时测试使用它的代码文件
        if is_code_file:
            mainfile = resolve_mainfile(filename)
        elif extname in (".in", ".ans"):
            if not (code_files := resolve_mainfiles(filename)):
                continue
            mainfile = code_files[0]
        else:
            continue

        if mainfile in mainfiles_to_test:
            continue
        else:
            mainfiles_to_test.add(mainfile)

        if is_code_file:
            temp_auxfiles = []
            for root, _, files in os.walk(dirname):
                for file in files:
                    if file.split(".")[0] == basename.split(".")[0] and file.endswith(
                        ".cpp"
                    ):
                        temp_auxfiles.append(os.path.normpath(os.path.join(root, file)))
            temp_examples = []
            for root, _, files in os.walk(dirname.replace("code", "examples")):
                for file in files:
                    if (
                        file.split(".")[0] == basename.split(".")[0]
                        and file.endswith(".in")
                        and os.path.exists(
                            os.path.join(root, file.replace(".in", ".ans"))
                        )
                    ):
                        temp_examples.append(os.path.normpath(os.path.join(root, file)))
        else:
            temp_auxfiles = []
            for root, _, files in os.walk(dirname.replace("examples", "code")):
                for file in files:
                    if file.split(".")[0] == basename.split(".")[0] and file.endswith(
                        ".cpp"
                    ):
                        temp_auxfiles.append(os.path.normpath(os.path.join(root, file)))
            temp_examples = [os.path.normpath(os.path.join(dirname, basename + ".in"))]

        temp_skiptest = False
        if os.path.exists(os.path.join(dirname, basename + ".skip_test")):
            temp_skiptest = True

        mainfiles.append(mainfile)
        auxfiles.append(temp_auxfiles)
        examples.append(temp_examples)
        skiptest.append(temp_skiptest)

    output("files_to_test", (mainfiles, auxfiles, examples, skiptest))


changed_files = os.environ.get("all_changed_files", "").split()
get_files_to_test(changed_files)
