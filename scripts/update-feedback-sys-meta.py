import argparse
from argparse import FileType
from difflib import SequenceMatcher
import os
from pathlib import PurePosixPath, Path
import re
import requests
import urllib.parse

API_ENDPOINT = "https://feedback-sys-backend.hikarilan.workers.dev/"

def get_latest_commit_hash():
    return os.popen("git log -1 --pretty=format:%H").read().strip()

def update_commit_hash():
    hash = get_latest_commit_hash()
    print("Updating commit hash to", hash)
    req = requests.put(
        API_ENDPOINT + "meta/commithash",
        headers={"Authorization": "Bearer " + os.environ["ADMINISTRATOR_SECRET"], "Content-Type": "application/json"},
        json={"commit_hash": hash},
    )
    if not req.ok:
        print("Failed to update commit hash, got", req.status_code, req.text)

parser = argparse.ArgumentParser("update-feedback-sys-meta")
parser.add_argument("--modified", type=FileType(encoding="utf-8"), required=True)
parser.add_argument("--renamed", type=FileType(encoding="utf-8"), required=True)
parser.add_argument("--before_dir", type=str, required=True)
args = parser.parse_args()

modified_file = args.modified.read().split(" ")
modified: list[str] = []
for f in modified_file:
    if(len(f) > 0):
        modified.append(f)

renamed_file = args.renamed.read()
renamed: list[(str, str)] = []
for files in renamed_file.split(" "):
    f = files.split(",")
    if(len(f) == 2):
        renamed.append((f[0], f[1]))

before_dir: str = args.before_dir
print("Modified:", modified)
print("Renamed:", renamed)
print("Before dir:", before_dir)

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


def dump_diff(path: str, oldPath: str = "", before_dir: str = before_dir):
    if oldPath == "":
        oldPath = path
    
    before = (Path(before_dir) / oldPath).read_text(encoding="utf-8")
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
    if os.environ["ADMINISTRATOR_SECRET"] == "":
        print("No ADMINISTRATOR_SECRET provided, skipping commit hash update")
    else:
        update_commit_hash()

        for path_from, path_to in renamed:
            req = requests.patch(
                API_ENDPOINT
                + "comment/{encoded_path}".format(
                    encoded_path=urllib.parse.quote_plus(path_to_url(path_from))
                ),
                headers={"Authorization": "Bearer " + os.environ["ADMINISTRATOR_SECRET"]},
                json={"type": "renamed", "to": path_to_url(path_to)},
            )
            print("Renamed:", path_to_url(path_from), "->", path_to_url(path_to), ", Got", req)

        for path in modified:
            diff = dump_diff(path)
            req = requests.patch(
                API_ENDPOINT
                + "comment/{encoded_path}".format(
                    encoded_path=urllib.parse.quote_plus(path_to_url(path))
                ),
                headers={"Authorization": "Bearer " + os.environ["ADMINISTRATOR_SECRET"]},
                json={"type": "modified", "diff": diff},
            )
            print("Modified:", path_to_url(path), ", Diff:", diff, ", Got", req)


        renamed_modified = []
        for path_from, path_to in renamed:
            diff = dump_diff(path_to, oldPath = path_from)
            if len(diff) > 0:
                renamed_modified.append((path_from, path_to))

        for path_from, path_to in renamed_modified:
            diff = dump_diff(path_to, oldPath = path_from)
            req = requests.patch(
                API_ENDPOINT
                + "comment/{encoded_path}".format(
                    encoded_path=urllib.parse.quote_plus(path_to_url(path_to))
                ),
                headers={"Authorization": "Bearer " + os.environ["ADMINISTRATOR_SECRET"]},
                json={"type": "modified", "diff": diff},
            )
            print("(Renamed) Modified:", path_to_url(path), ", Diff:", diff, ", Got", req)