#!/usr/bin/python3

"""
Utility to find all non Chinese-Sigapore (kIICore G) IRG Source CJKs.
"""

import os
import functools
import re

# Unihan database is not included in this script.
# Find Unihan_IRGSources.txt from
# https://www.unicode.org/Public/UCD/latest/ucd/Unihan.zip

db = {}

def read_unihan_db():
    global db
    with open("Unihan_IRGSources.txt", "r") as f:
        for l in f:
            if l.startswith("#"): continue
            k = l.strip().split("\t")
            if len(k) < 3: continue

            ucode, key, value = k
            if key == 'kIICore':
                db[int(ucode[2:], 16)] = value


# no idea on how to select U+2F800..U+2FA1F so just assume they do not exist
CJK_COMPAT = "[\u3300-\u33FF\uFE30-\uFE4F\uF900-\uFAFF]"
CJK_EXT = "[\u3400-\u4DBF]"

def get_cjk(cp):
    return map(lambda x: (x.group(0), x.span(0)[0]), re.finditer("[\u4E00-\u9FFF]", cp))

def process_lines(lns, name):
    for i, ln in enumerate(lns):
        cjks = get_cjk(ln)
        for ch in cjks:
            iic = db.get(ord(ch[0]), None)
            if iic is None:
                print(f"{name}, ({i}:{ch[1]}): {ch[0]} is not in kIICore")
            elif "G" not in iic:
                print(f"{name}, ({i}:{ch[1]}): {ch[0]} is not in IRG G Source")
            # print(db[ord(ch[0])])

def main():
    read_unihan_db()

    for dirname, _, files in os.walk("../docs"):
        for f in filter(lambda x: x.endswith(".md"), files):
            with open(f"{dirname}/{f}", "r") as ff:
                lns = ff.readlines()
                process_lines(lns, f)
    
if __name__ == "__main__":
    main()
