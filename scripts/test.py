import os
import sys
import json

annotations = []

def generate_annotations_and_exit(file, message):
    print(f"::error file={file},line={1},col={1}::{message}")
    sys.exit(1)


def test(cppname):
    name = cppname[:cppname.rfind('.')]
    num = name.rfind('/')
    content = name[:num]
    filename = name[num:]
    # 文件名
    cpp = name+'.cpp'
    indata = name+'.in'
    ansdata = name+'.ans'
    outdata = name+'.out'
    skiptest = name+'.skip_test'
    indata = indata.replace('code', 'examples')
    outdata = outdata.replace('code', 'examples')
    ansdata = ansdata.replace('code', 'examples')
    # 判断测试是否要执行
    if os.path.exists(skiptest):
        print(cpp + ' test skipped')
        return

    cmd = 'g++ -std=c++17 '+cpp+' -o '+name
    # 判断CE
    if os.system(cmd) == 0:
        print(cpp+' Successfully compiled')
    else:
        print(cpp+' Compiled Error')
        generate_annotations_and_exit(cpp, 'Compiled Error')
    # 运行程序并重定向输出
    cmd = content+'/.'+filename+' <'+indata+'> '+outdata
    os.system(cmd)
    # 判断RE
    if os.system(cmd) == 0:
        print(cpp+' Run successfully')
    else:
        print(cpp+' Runtime Error')
        generate_annotations_and_exit(cpp, 'Runtime Error')

    # 判断答案
    cmd = 'diff -b -B '+outdata+' '+ansdata
    if os.system(cmd) == 0:
        print(cpp+' Successfully passed the test')
    else:
        print(cpp + ' Wrong Answer')
        generate_annotations_and_exit(cpp, 'Wrong Answer')

filename = "res.txt"
with open(filename) as file_object:
    lines = file_object.readlines()
for line in lines:
    for filename in line.split(' '):
        test(filename)
