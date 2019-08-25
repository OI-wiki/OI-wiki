author: ybw051114
# notepad++妙用

**（推荐文末下载版）**

### 本文将讲述以下几个方面

1.  默认c++保存为cpp后缀
    
2.  C++格式化
    
3.  C++编译运行
    
4.  启用连体字
    
5.  加强版
    

### 默认c++保存为cpp后缀

打开notepad++目录下的langs.xml

找到`<Language name="cpp" ext="h cpp hpp hxx cxx cc ino" commentLine="//" commentStart="/*" commentEnd="*/">`

替换为`<Language name="cpp" ext="cpp h hpp hxx cxx cc ino" commentLine="//" commentStart="/*" commentEnd="*/">`

重启notepad++即可

### C++格式化

我是用的是coolformat插件

[下载地址](http://pan.ybw051114.ml/教程/Coolformat.zip) 下载后解压到plugins目录下（**注意：选择解压到当前目录**）

重启notepad++即可

### C++编译运行

安装NppExec插件。

**将G++的bin目录加入环境变量并将[此文件](http://pan.ybw051114.ml/教程/ConsolePauser.exe)放入**

选择execute

编译：

```bash
NPP_SAVEg++ "$(CURRENT_DIRECTORY)\$(FILE_NAME)" -o "$(CURRENT_DIRECTORY)\$(NAME_PART).exe" if $(EXITCODE) !=0 goto ERROWNPP_CONSOLE 0goto GOOD1 :ERROWNPP_CONSOLE 1:GOOD1
```

运行：

```bash


NPP_RUN ConsolePauser "$(CURRENT_DIRECTORY)\$(NAME_PART).exe" &exit
```

一键编译运行：

```bash
NPP_SAVEg++ "$(CURRENT_DIRECTORY)\$(FILE_NAME)" -o "$(CURRENT_DIRECTORY)\$(NAME_PART).exe"  if $(EXITCODE)==1 goto ERROW if $(EXITCODE)==0 goto GOOD :GOOD NPP_CONSOLE 0NPP_RUN ConsolePauser "$(CURRENT_DIRECTORY)\$(NAME_PART).exe" &exitgoto GOOD1:ERROWNPP_CONSOLE 1:GOOD1


```

### 启用连体字

下载luascript插件

选择`edit ...`

加入下面两句话

```ini
editor1.Technology = SC_TECHNOLOGY_DIRECTWRITEeditor2.Technology = SC_TECHNOLOGY_DIRECTWRITE
```

重启即可

### 加强版

**将G++的bin目录加入环境变量并将[此文件](http://pan.ybw051114.ml/%E6%95%99%E7%A8%8B/ConsolePauser.exe)放入。并在D盘根目录新建compile文件夹**

[下载](http://pan.ybw051114.ml/教程/notepad++.zip)至任意地方解压即用
