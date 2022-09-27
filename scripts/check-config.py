import os
from pathlib import Path
import sys
import json
import yaml

annotations = []

def generate_annotations_and_exit(file, message):
    print(f"::error file={file},line={1},col={1}::{message}")
    sys.exit(1)

filename = "config.txt"

with open(filename) as file_object:
    lines=file_object.readlines()

for line in lines:
    line=line[:-1]
    with open(line) as f:
        temp=yaml.load(f.read(),Loader=yaml.FullLoader)
        testcases=temp['testcases']
        answer=testcases['answer']
        input=testcases['input']
        answer_file=Path(answer)
        input_file=Path(input)
        if answer_file.is_file() :
            print(answer+" is exist!")
        else:
            print(answer+" is not exist!")
            generate_annotations_and_exit(answer, "Not Exist")
        if input_file.is_file():
            print(input +" is exist!")
        else:
            print(input+" is exist!")
            generate_annotations_and_exit(input, "Not Exist")