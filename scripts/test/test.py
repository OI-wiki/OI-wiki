import os
import sys
import json

def generate_annotations_and_exit(file, message):
    print(f"::error file={file},line={1},col={1}::{message}")
    sys.exit(1)

def test(filename):
    name = filename[:filename.rfind('.')]
    lang = filename[filename.rfind('.')+1:]
    # 文件名
    indata = name+'.in'
    ansdata = name+'.ans'
    skiptest = name+'.skip_test'
    indata = indata.replace('code', 'examples')
    ansdata = ansdata.replace('code', 'examples')
    # 判断测试是否要执行
    if os.path.exists(skiptest):
        print(filename + ' test skipped')
        return
    
    # 检查文件
    if os.path.exists(indata)==0:
        generate_annotations_and_exit(indata,'No input file')
    if os.path.exists(ansdata)==0:
        generate_annotations_and_exit(ansdata,'No answer file')
    
    if os.system('./single-run-with-san '+filename+' '+indata+' out'):
        generate_annotations_and_exit(filename, 'Failed')
    if os.system('diff -b -B out '+ansdata):
        print(filename + ' Wrong Answer')
        generate_annotations_and_exit(filename, 'Wrong Answer')
    
    if os.system('./single-run '+filename+' '+indata+' out'):
        generate_annotations_and_exit(filename, 'Failed')
    if os.system('diff -b -B out '+ansdata):
        print(filename + ' Wrong Answer')
        generate_annotations_and_exit(filename, 'Wrong Answer')
    else:
        print(filename+' Successfully passed the test :)')

filename = "res.txt"
with open(filename) as file_object:
    lines = file_object.readlines()
for line in lines:
    for filename in line.split():
        test(filename)
        sys.stdout.flush() # 不然日志会错位
