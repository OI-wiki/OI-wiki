geany 是一个轻量、便捷的编辑器，与 Dev-C++ 一样，它可以编译运行单个文件。
不过，它可以在 Linux/Windows/macOS 下运行。
目前（20191223）最新版本为 1.36。

兼容深度终端：
在首选项→工具→虚拟终端，修改终端的命令为：

    > deepin-terminal -x "/bin/sh" %c

点击“应用”按钮后即可。

（来源：deepin Wiki <https://wiki.deepin.org/）> 

在Linux下自行编译geany 1.36时， 如遇到 “No package 'gtk+-2.0' found”
可能需要安装libgtk2.0-dev （apt-get即可）

其官网为： <https://geany.org/> 
