import argparse
from argparse import FileType
from difflib import SequenceMatcher
import os
from pathlib import PurePosixPath, Path
import re
import requests
import urllib.parse

API_ENDPOINT = "https://cloudflare-workers.hikarilan.workers.dev/"

def remove_meta(doc: str) -> str:
    """
    See issue: https://github.com/squidfunk/mkdocs-material/issues/4179
    @Source: https://github.com/mkdocs/mkdocs/blob/master/mkdocs/utils/meta.py
    """
    META_RE = re.compile(r'^[ ]{0,3}(?P<key>[A-Za-z0-9_-]+):\s*(?P<value>.*)')
    META_MORE_RE = re.compile(r'^([ ]{4}|\t)(\s*)(?P<value>.*)')
    
    lines = doc.replace('\r\n', '\n').replace('\r', '\n').split('\n')
    
    while lines:
        line = lines.pop(0)

        if line.strip() == '':
            break  # blank line - done
        
        if not META_RE.match(line) and not META_MORE_RE.match(line):
            lines.insert(0, line)
            break  # no meta data - done
        
    return '\n'.join(lines).lstrip('\n')


def dump_diff(path: str, before_dir: str = before_dir):
    before = (Path(before_dir) / path).read_text(encoding="utf-8")
    after = Path(path).read_text(encoding="utf-8")
    
    before = remove_meta(before)
    after = remove_meta(after)

    diff = SequenceMatcher(None, before, after)

    return [
        {"tag": tag, "i1": i1, "i2": i2, "j1": j1, "j2": j2}
        for (tag, i1, i2, j1, j2) in diff.get_opcodes()
        if tag != "equal"
    ]
    
def path_to_url(
    raw_path: str, base_dir: str = "docs", index_file: str = "index.md"
) -> str:
    path = PurePosixPath(raw_path).relative_to(base_dir)

    if path.name == index_file:
        path = path.parent
    else:
        path = path.with_suffix("")

    path = "/" / path

    return str(path) + ("/" if path.name != "" else "")

if __name__ == '__main__':
    parser = argparse.ArgumentParser("update-feedback-sys-meta")
    parser.add_argument("--modified", type=FileType(encoding="utf-8"), required=True)
    parser.add_argument("--renamed", type=FileType(encoding="utf-8"), required=True)
    parser.add_argument("--before_dir", type=str, required=True)

    args = parser.parse_args()

    modified: list[str] = args.modified.read().split(" ")
    renamed: list[(str, str)] = [
        tuple((files.split(",")[0], files.split(",")[1]))
        for files in args.renamed.read().split(" ")
    ]

    before_dir: str = args.before_dir

    print("Modified:", modified)
    print("Renamed:", renamed)
    print("Before dir:", before_dir)

    for path in modified:
        requests.patch(
            API_ENDPOINT
            + "comment/{encoded_path}".format(
                encoded_path=urllib.parse.quote(path_to_url(path))
            ),
            headers={"Authorization": "Bearer " + os.environ["ADMINISTRATOR_SECRET"]},
            json={"type": "modified", "diff": dump_diff(path)},
        )

    for path_from, path_to in renamed:
        requests.patch(
            API_ENDPOINT
            + "comment/{encoded_path}".format(
                encoded_path=urllib.parse.quote(path_to_url(path_from))
            ),
            headers={"Authorization": "Bearer " + os.environ["ADMINISTRATOR_SECRET"]},
            json={"type": "renamed", "to": path_to_url(path_to)},
        )
