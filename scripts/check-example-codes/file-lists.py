import os

extnames = [".cpp", ".py"]


def check_availability(file):
    if not os.path.exists(file):
        return False
    dirname = os.path.dirname(file)
    if "code" not in dirname.split("/"):
        return False
    basename, extname = os.path.splitext(os.path.basename(file))
    if os.path.exists(os.path.join(dirname, basename + ".skip_test")):
        return False
    if "." in basename:
        basename = basename.split(".")[0]
        if not os.path.exists(os.path.join(dirname, basename + extname)):
            return False
    return os.path.normpath(os.path.join(dirname, basename + extname))


def examples2code(example_file):
    dirname = os.path.dirname(example_file)
    basename = os.path.splitext(os.path.basename(example_file))[0]
    code_dir = dirname.replace("examples", "code")
    code_files = []
    for extname in extnames:
        code_file = os.path.normpath(os.path.join(code_dir, basename + extname))
        if available_file := check_availability(code_file):
            code_files.append(available_file)
    return code_files


def output(name, value):
    with open(os.environ.get("GITHUB_OUTPUT"), "a") as f:
        f.write(f"{name}={value if value else 'None'}\n")


if __name__ == "__main__":
    changed_files = os.environ.get("all_changed_files")
    changed_codes = set()
    for changed_file in changed_files.split():
        if os.path.splitext(changed_file)[1] in extnames:
            changed_codes.add(changed_file)
        else:
            changed_codes.update(examples2code(changed_file))
    for extname in extnames:
        changed_extnamed_codes = " ".join(
            filter(lambda x: x.endswith(extname), changed_codes)
        )
        output(f"TEST_{extname[1:].upper()}_FILES", changed_extnamed_codes)
