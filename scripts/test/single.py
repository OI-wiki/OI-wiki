import os
import sys

def compile(name,lang):
	if lang=='py':
		return
	if os.path.exists(name):
		return
	if lang=='cpp':
		if os.system('g++ -O2 -std=c++17 -Wno-unused-result -o '+name+' '+name+'.cpp'):
			print(name+'.cpp Compile Error :(')
			sys.exit(1)
		if os.system('g++ -O2 -fsanitize=undefined,address -std=c++17 -Wno-unused-result -o '+name+'-san '+name+'.cpp'):
			print(name+'.cpp Compile Error :(')
			sys.exit(1)
		print(name+'.cpp Successfully compiled')
		sys.stdout.flush() # 不然日志会错位
		return
	print(name+'.'+lang+' Unknown language: '+lang)
	sys.exit(1)

filename=sys.argv[1]
inf=sys.argv[2]
ouf=sys.argv[3]
name=filename[:filename.rfind('.')]
lang=filename[filename.rfind('.')+1:]
path=filename[:filename.rfind('/')]

compile(name,lang)

cmds=[]
if lang=='py':
	cmds.append('ulimit -v 1048576\ntime -f \'%Us %MKB\' timeout 10s '+
		'python3 '+filename+
		'<'+inf+'>'+ouf)
if lang=='cpp':
	c=name[:name.rfind('/')]+'/.'+name[name.rfind('/'):]
	cmds.append('timeout 10s '+
		c+'-san'+
		'<'+inf+'>'+ouf)
	cmds.append('ulimit -v 1048576\ntime -f \'%Us %MKB\' timeout 10s '+
		c+
		'<'+inf+'>tmp')

for cmd in cmds:
	returnvalue=os.system(cmd)
	if returnvalue==124 or returnvalue==124<<8:
		print(filename+' Time Out :(')
		sys.exit(1)
	if returnvalue:
		print(filename+' Runtime Error or Memory Limit Exceeded :(')
		sys.exit(1)

if lang=='cpp':
	if os.system('diff -b -B tmp '+ouf):
		print(filename+' Wrong Answer :(')
		sys.exit(1)
