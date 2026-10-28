# Generate the list of files to test from the changed files.
# Input: the changed files reported by tj-actions/changed-files, read from the
#        `all_changed_files` environment variable.
# Output: the files to test, written to $GITHUB_OUTPUT.

import os

from test_utils import derive_test_files

# Extensions of the source files that can be tested.
extnames = [".cpp"]


def check_availability(file):
    """
    Check whether `file` is a main source file that can be tested.

    Returns the normalized path of the main file, or an empty string when the
    file should not be tested:
    - it does not exist, e.g. because the change deleted it;
    - it does not live in a `code` directory;
    - it is a variant of a main file (`foo.1.cpp`) whose main file is missing;
    - a `foo.skip_test` marker file exists next to it.
    """
    if not os.path.exists(file):
        return ""
    dirname = os.path.dirname(file)
    if "code" not in dirname.split("/"):
        return ""
    basename, extname = os.path.splitext(os.path.basename(file))
    if "." in basename:
        # Variants such as `foo.1.cpp` are tested through their main file.
        main_basename = basename.split(".")[0]
        if not os.path.exists(os.path.join(dirname, main_basename + extname)):
            return ""
        basename = main_basename
    if os.path.exists(os.path.join(dirname, basename + ".skip_test")):
        return ""
    return os.path.normpath(os.path.join(dirname, basename + extname))


def examples2code(example_file):
    """
    Map an example data file back to the code files it belongs to.

    `docs/<...>/examples/<topic>/foo.in` belongs to
    `docs/<...>/code/<topic>/foo.<extname>`, for every supported extension.
    Returns the code files that can be tested, an empty list when the given path
    is not an example data file or when no matching code file can be tested.
    """
    dirname = os.path.dirname(example_file)
    basename = os.path.splitext(os.path.basename(example_file))[0]
    pos = dirname.rfind("/examples/")
    if pos == -1:
        return []
    code_dir = dirname[:pos] + "/code/" + dirname[pos + len("/examples/") :]
    code_files = []
    for extname in extnames:
        code_file = os.path.join(code_dir, basename + extname)
        if available_file := check_availability(code_file):
            code_files.append(available_file)
    return code_files


def output(name, value):
    """Write an output variable to the GitHub Actions output file."""
    with open(os.environ.get("GITHUB_OUTPUT"), "a") as f:
        f.write(f"{name}={value}\n")


if __name__ == "__main__":
    mainfiles, auxfiles, examples, skiptests = [], [], [], []

    for changed_file in os.environ.get("all_changed_files", "").split():
        # A changed file is resolved to the main files it belongs to: a code
        # file through its own main file, example data through the code files
        # using it.
        if os.path.splitext(changed_file)[1] in extnames:
            changed_codes = [check_availability(changed_file)]
        else:
            changed_codes = examples2code(changed_file)
        for mainfile in filter(None, changed_codes):
            if mainfile in mainfiles:
                continue
            mainfiles.append(mainfile)
            auxfile, example, skiptest = derive_test_files(mainfile)
            auxfiles.append(auxfile)
            examples.append(example)
            skiptests.append(skiptest)

    output("files_to_test", (mainfiles, auxfiles, examples, skiptests))
