import argparse
import os
import sys


# autopep8: off
# fix ModuleNotFoundError by adding current directory to Python path
sys.path.append(os.path.abspath('.'))

from scripts.linter.decorators import pipeline
from scripts.linter.utils import log
from scripts.linter.preprocess import fix_details
from scripts.linter.postprocess import fix_full_stop

sys.path.pop()
# autopep8: on


@pipeline
def apply_preprocess(md_content: str):
    """
    Apply preprocessing transformations to Markdown content.

    This function serves as the main preprocessing pipeline that applies
    various formatting fixes to Markdown content before it's processed
    by other tools.

    Args:
        md_content: The raw Markdown content to process

    Returns:
        str: The processed Markdown content with formatting fixes applied
    """
    log("Starting preprocessing pipeline...")
    md_content = fix_details(md_content)
    log("Preprocessing pipeline completed.")

    return md_content


@pipeline
def apply_postprocess(md_content: str):
    """
    Apply postprocessing transformations to Markdown content.

    This function serves as the main preprocessing pipeline that applies
    various formatting fixes to Markdown content after it's processed by
    other tools.

    Args:
        md_content: The Markdown content to process

    Returns:
        str: The processed Markdown content
    """
    log("Starting postprocessing pipeline...")
    md_content = fix_full_stop(md_content)
    log("Postprocessing pipeline completed.")

    return md_content


# Define available processing modes
MODE = {
    'pre': apply_preprocess,   # Preprocessing mode
    'post': apply_postprocess  # Postprocessing mode
}

if __name__ == '__main__':
    # Set up command line argument parser
    parser = argparse.ArgumentParser(
        description="remark-lint patches for OI-wiki")
    parser.add_argument('directory', nargs='?',
                        help='directory to process recursively')
    parser.add_argument('-f', '--files', nargs='+',
                        help='list of Markdown files to process')
    parser.add_argument(
        '-m', '--mode', choices=MODE.keys(), required=True,
        help='processing mode: pre for preprocessing, post for postprocessing')

    args = parser.parse_args()

    file_list = []

    # Build list of files to process
    if args.files:
        # Process specific files provided via command line
        print(f"Processing specific files: {args.files}")
        file_list.extend(
            filter(lambda f: os.path.splitext(f)[1] == '.md', args.files))
    elif args.directory:
        # Recursively find all Markdown files in directory
        print(f"Scanning directory: {args.directory}")
        for root, _, files in os.walk(args.directory):
            markdown_files = [fn for fn in files if os.path.splitext(fn)[
                1] == '.md']
            if markdown_files:
                print(f"Found {len(markdown_files)} Markdown files in {root}")
            file_list.extend(os.path.join(root, fn) for fn in markdown_files)
    else:
        # No files or directory specified, show help
        parser.print_help()
        exit(0)

    # Load ignore list from .remarkignore file
    ignore_list = []
    try:
        with open('.remarkignore', 'r', encoding='utf-8') as f:
            ignore_list = f.readlines()
        print(f"Loaded {len(ignore_list)} files to ignore from .remarkignore")
    except FileNotFoundError:
        print("Warning: .remarkignore file not found, no files will be ignored")

    file_list = list(filter(lambda f: os.path.isfile(f) and
                            os.path.split(f)[1] not in ignore_list,
                            file_list))

    print(f"Processing {len(file_list)} file(s) with mode '{args.mode}'")

    # Process each file
    processed_count = 0
    error_count = 0

    for file in file_list:
        try:
            MODE[args.mode](file)
            processed_count += 1
        except Exception as e:
            print(f"Error processing {file}: {str(e)}")
            error_count += 1

    # Summary
    print(f"\n=== Processing Summary ===")
    print(f"Total files found: {len(file_list)}")
    print(f"Successfully processed: {processed_count}")
    print(f"Errors: {error_count}")
    print(f"Mode: {args.mode}")
