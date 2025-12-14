# Generate list of code files to test based on changed files
# Input: changed files from tj-actions/changed-files (via all_changed_files env variable)
# Output: TEST_<LANGUAGE>_FILES containing space-separated list of main source files only

import os

# Supported file extensions for testing
extnames = [".cpp"]


def check_availability(file):
    """
    Check if a file is available for testing.
    
    Returns the normalized file path if available, empty string otherwise.
    A file is not available if:
    - It doesn't exist
    - It's not in a 'code' directory
    - It's a variant file (e.g., file.1.cpp) and the main file doesn't exist
    - A .skip_test marker file exists for it
    """
    if not os.path.exists(file):
        return ""
    dirname = os.path.dirname(file)
    # Only test files in 'code' directories
    if "code" not in dirname.split("/"):
        return ""
    basename, extname = os.path.splitext(os.path.basename(file))
    # Handle variant files like file.1.cpp - check if main file exists
    if "." in basename:
        basename = basename.split(".")[0]
        if not os.path.exists(os.path.join(dirname, basename + extname)):
            return ""
    # Skip if .skip_test marker exists
    if os.path.exists(os.path.join(dirname, basename + ".skip_test")):
        return ""
    return os.path.normpath(os.path.join(dirname, basename + extname))


def examples2code(example_file):
    """
    Convert an example file path (e.g., .in/.ans file) to corresponding code file paths.
    
    Maps files from docs/.../examples/... to docs/.../code/...
    Returns list of available code files with supported extensions.
    """
    dirname = os.path.dirname(example_file)
    basename = os.path.splitext(os.path.basename(example_file))[0]
    pos = dirname.rfind("/examples/")
    if pos == -1:
        return ".invalidExamplePath"
    # Convert examples path to code path
    code_dir = dirname[:pos] + "/code/" + dirname[pos + 10:]
    code_files = []
    for extname in extnames:
        code_file = os.path.normpath(os.path.join(code_dir, basename + extname))
        if available_file := check_availability(code_file):
            code_files.append(available_file)
    return code_files


def output(name, value):
    """Write output variable to GitHub Actions output file."""
    with open(os.environ.get("GITHUB_OUTPUT"), "a") as f:
        f.write(f"{name}={value if value else 'None'}\n")


if __name__ == "__main__":
    # Get changed files from environment variable
    changed_files = os.environ.get("all_changed_files")
    changed_codes = set()
    
    # Process each changed file
    for changed_file in changed_files.split():
        if os.path.splitext(changed_file)[1] in extnames:
            # Direct code file change
            changed_codes.add(changed_file)
        else:
            # Example file change - find corresponding code files
            changed_codes.update(examples2code(changed_file))
    
    # Output mainfiles only, grouped by extension
    for extname in extnames:
        changed_extnamed_codes = " ".join(
            filter(lambda x: x.endswith(extname), changed_codes)
        )
        output(f"TEST_{extname[1:].upper()}_FILES", changed_extnamed_codes)
