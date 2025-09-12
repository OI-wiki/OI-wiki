import argparse
import os
import sys

# autopep8: off
# fix ModuleNotFoundError
sys.path.append(os.path.abspath('.'))

from scripts.linter.common import pipeline
from scripts.linter.preprocess import fix_details
from scripts.linter.postprocess import fix_punctuations

sys.path.pop()
# autopep8: on


@pipeline
def apply_preprocess(md_content: str):
    md_content = fix_details(md_content)

    return md_content


@pipeline
def apply_postprocess(md_content: str):
    md_content = fix_punctuations(md_content)

    return md_content


MODE = {
    'pre': apply_preprocess,
    'post': apply_postprocess
}

if __name__ == '__main__':
    parser = argparse.ArgumentParser(description="remark-lint patches")
    parser.add_argument('directory', nargs='?', help='要递归处理的文件夹')
    parser.add_argument('-f', '--files', nargs='+', help='要处理的 Markdown 文件列表')
    parser.add_argument(
        '-m', '--mode', choices=MODE.keys(), required=True, help='模式')

    args = parser.parse_args()

    file_list = []

    if args.files:
        file_list.extend(
            filter(lambda f: os.path.splitext(f)[1] == '.md', args.files))
    elif args.directory:
        for root, _, files in os.walk(args.directory):
            file_list.extend(os.path.join(root, fn) for fn in filter(
                lambda f: os.path.splitext(f)[1] == '.md', files))
    else:
        parser.print_help()
        exit(0)

    ignore_list = []
    with open('.remarkignore', 'r') as f:
        ignore_list = f.readlines()

    file_list = list(filter(lambda f: os.path.isfile(f) and
                            os.path.split(f)[1] not in ignore_list,
                            file_list))

    print(f"{len(file_list)} file(s) found")

    for file in file_list:
        MODE[args.mode](file)
