# Helpers shared by the example code test scripts.
#
# `get_files_to_test.py` (for now) and later `correctness_check.py` and
# `ub-check.py` need the auxiliary files, the example data and the skip marker
# that belong to a main source file. Keeping the derivation here avoids
# duplicating it, and avoids importing one entry point script from another one.

import os


def derive_test_files(mainfile):
    """
    Derive auxfiles, examples and skiptest status from a main source file.

    Args:
        mainfile: path to the main source code file

    Returns:
        tuple: (auxfiles, examples, skiptest)
            auxfiles: the `.cpp` files that share the basename of `mainfile`,
                including `mainfile` itself; empty for the other languages
            examples: the `.in` files that have a matching `.ans` file
            skiptest: whether a `.skip_test` marker file exists
    """
    dirname = os.path.dirname(mainfile)
    basename, extname = os.path.splitext(os.path.basename(mainfile))

    auxfiles = []
    if extname == ".cpp":
        for root, _, files in os.walk(dirname):
            for file in files:
                if file.split(".")[0] == basename and file.endswith(".cpp"):
                    auxfiles.append(os.path.normpath(os.path.join(root, file)))

    # The example data lives in the `examples` directory that mirrors the `code`
    # directory holding `mainfile`: `docs/math/code/foo/` is paired with
    # `docs/math/examples/foo/`.
    examples = []
    pos = dirname.rfind("/code/")
    if pos != -1:
        examples_dir = dirname[:pos] + "/examples/" + dirname[pos + len("/code/") :]
        for root, _, files in os.walk(examples_dir):
            for file in files:
                if (
                    file.split(".")[0] == basename
                    and file.endswith(".in")
                    and os.path.exists(os.path.join(root, file.replace(".in", ".ans")))
                ):
                    examples.append(os.path.normpath(os.path.join(root, file)))

    skiptest = os.path.exists(os.path.join(dirname, basename + ".skip_test"))

    return sorted(auxfiles), sorted(examples), skiptest
