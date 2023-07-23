GUIDE（GAIT Universal IDE）是由北航 GAIT 研究组开发的、专门为 NOI 选手设计的、支持 C/C++/Pascal 三种程序设计语言的小型集成开发环境。

???+ note
    自 2021 年 9 月 1 日起启用的 NOI Linux 2.0 不再包含 GUIDE。[^ref1]

## 安装

### Windows

参见 <https://www.noi.cn/xw/2009-03-23/714714.shtml>。

### Linux

参见 <https://www.noi.cn/xw/2009-03-23/714714.shtml> 或按照如下步骤安装。

#### 需要的动态库文件及包名

| 动态库                 | Arch 包名          | Debian 包名      | Fedora 包名  | openSUSE x86 包名   | openSUSE x86\_64 包名     |
| ------------------- | ---------------- | -------------- | ---------- | ----------------- | ----------------------- |
| libpng12.so.0       | lib32-libpng12   | libpng12       | libpng12   | libpng12-0        | libpng12-0-32bit        |
| libSM.so.6          | lib32-libsm      | libsm6         | libSM      | libSM6            | libSM6-32bit            |
| libICE.so.6         | lib32-libice     | libice6        | libICE     | libICE6           | libICE6-32bit           |
| libXi.so.6          | lib32-libxi      | libxi6         | libXi      | libXi6            | libXi6-32bit            |
| libXrender.so.1     | lib32-libxrender | libxrender1    | libXrender | libXrender1       | libXrender1-32bit       |
| libXrandr.so.2      | lib32-libxrandr  | libxrandr      | libXrandr  | libXrandr2        | libXrandr2-32bit        |
| libfreetype.so.6    | lib32-freetype2  | libfreetype6   | freetype   | libfreetype6      | libfreetype6-32bit      |
| libfontconfig.so.1  | lib32-fontconfig | libfontconfig1 | fontconfig | libfontconfig1    | libfontconfig1-32bit    |
| libXext.so.6        | lib32-libxext    | libxext6       | libXext    | libXext6          | libXext6-32bit          |
| libX11.so.6         | lib32-libx11     | libx11-6       | libX11     | libX11-6          | libX11-6-32bit          |
| libz.so.1           | lib32-zlib       | zlib1g         | zlib       | libz1             | libz1-32bit             |
| libgthread-2.0.so.0 | lib32-glib2      | libglib2.0-0   | glib2      | libgthread-2\_0-0 | libgthread-2\_0-0-32bit |
| libglib-2.0.so.0    | lib32-glib2      | libglib2.0-0   | glib2      | libglib2\_0-0     | libglib2\_0-0-32bit     |
| libstdc++.so.6      | lib32-gcc-libs   | libstdc++6     | libstdc++  | libstdc++6        | libstdc++6-32bit        |
| libgcc\_s.so.1      | lib32-gcc-libs   | lib32gcc1      | libgcc     | libgcc\_s1        | libgcc\_s1              |
| librt.so.1          | lib32-glibc      | libc6          | glibc      | glibc             | glibc-32bit             |
| libpthread.so.0     | lib32-glibc      | libc6          | glibc      | glibc             | glibc-32bit             |
| libdl.so.2          | lib32-glibc      | libc6          | glibc      | glibc             | glibc-32bit             |
| libm.so.6           | lib32-glibc      | libc6          | glibc      | glibc             | glibc-32bit             |
| libc.so.6           | lib32-glibc      | libc6          | glibc      | glibc             | glibc-32bit             |

#### 在 Debian 或 Ubuntu 安装

```bash
sudo apt install -y libpng12 libsm6 libice6 libxi6 libxrender1 libxrandr libfreetype6 libfontconfig1 libxext6 libx11-6 zlib1g libglib2.0-0 libglib2.0-0 libstdc++6 lib32gcc1 libc6
wget -c http://download.noi.cn/T/noi/GUIDE-1.0.2-ubuntu.tar
tar -xvf GUIDE-1.0.2-ubuntu.tar
cd GUIDE-1.0.2-ubuntu
echo "install:\n\tinstall -Dm755 -t /usr/bin GUIDE\n\tinstall -Dm644 -t /usr/share/ lang_en.qm\n\tmkdir -p /usr/share/apis/ && cp -r apis/* /usr/share/apis/\n\tmkdir -p /usr/share/doc/GUIDE/ && mkdir -p /usr/share/doc/GUIDE/html/ && cp -r doc/*  /usr/share/doc/GUIDE/html/" > Makefile
sudo apt install -y checkinstall
sudo checkinstall --pkgname "GUIDE" --pkgversion "1.0.2" -y
```

#### 在 openSUSE 安装

按照 [openSUSE/opi](https://github.com/openSUSE/opi#install) 给出的方式安装 opi。

然后：（32 位用户自行删去 `-32bit`）

```bash
sudo opi checkinstall
sudo zypper install -n {libpng12-0,libSM6,libICE6,libXi6,libXrender1,libXrandr2,libfreetype6,libfontconfig1,libXext6,libX11-6,libz1,libgthread-2_0-0,libglib2_0-0,libstdc++6,libgcc_s1,glibc}-32bit
wget -c http://download.noi.cn/T/noi/GUIDE-1.0.2-ubuntu.tar
tar -xvf GUIDE-1.0.2-ubuntu.tar
cd GUIDE-1.0.2-ubuntu
echo "install:\n\tinstall -Dm755 -t /usr/bin GUIDE\n\tinstall -Dm644 -t /usr/share/ lang_en.qm\n\tmkdir -p /usr/share/apis/ && cp -r apis/* /usr/share/apis/\n\tmkdir -p /usr/share/doc/GUIDE/ && mkdir -p /usr/share/doc/GUIDE/html/ && cp -r doc/*  /usr/share/doc/GUIDE/html/" > Makefile
sudo checkinstall --pkgname "GUIDE" --pkgversion "1.0.2" -y -rpmi
```

## 编辑文件

点击页面上方工具栏的「新文件」按钮（或者使用<kbd>Ctrl</kbd>+<kbd>N</kbd>快捷键）来创建一个新文件。

在默认情况下，GUIDE 的代码字体并非等宽字体，看上去非常不美观，因此需要在设置中更改字体。

在 编辑 -> 选项 -> 语法高亮设置 中，点击「全部字体」按钮，即可切换编辑器字体。

需要注意的是，对于未保存的新文件，字体仍然是默认字体。因此建议在开始编辑前先保存文件（点击工具栏的「保存」按钮，或按下<kbd>Ctrl</kbd>+<kbd>S</kbd>快捷键），再进行编辑。

## 编译与运行

在编辑完源代码后，点击工具栏的「编译」按钮（或<kbd>F7</kbd>快捷键）进行编译。

???+ note "更改编译选项"
    GUIDE 没有设置默认编译选项的功能，用户只能更改对某个文件的编译选项。
    
    右键点击想要更改编译选项的文件的标签，选择 **设置编译命令** 选项，即可更改该文件的编译选项。

如果源代码正常编译，点击工具栏的「运行」按钮（或<kbd>Ctrl</kbd>+<kbd>F5</kbd>快捷键）即可运行程序。

## 调试

GUIDE 自带的调试功能存在很多 bug（如程序中途发生崩溃等），因此不推荐直接使用 GUIDE 的调试功能。

建议直接在 [终端](../cmd.md) 下使用 gdb 来进行调试。

[^ref1]: [NOI Linux 2.0 发布，将于 9 月 1 日起正式启用！](https://www.noi.cn/gynoi/jsgz/2021-07-16/732450.shtml)
