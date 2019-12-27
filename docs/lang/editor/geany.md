# geany

geany 是一个轻量、便捷的编辑器，与 Dev-C++ 一样，它可以编译运行单个文件。
不过，它可以在 Linux/Windows/macOS 下运行。
目前最新版本为 1.36。
其官网为： <https://geany.org/> 

## 优缺点
### 优点
 1.轻量
 
 2.可以编译运行单个文件
 
 3.不需要太多配置
 
 4.跨平台

## 常见问题
兼容深度终端：
在首选项→工具→虚拟终端，修改终端的命令为：

    > deepin-terminal -x "/bin/sh" %c

点击“应用”按钮后即可。

（来源：deepin Wiki <https://wiki.deepin.org/）> 

在 Linux 下自行编译 geany 1.36 时，如遇到“No package 'gtk+-2.0' found”
可能需要安装 libgtk2.0-dev（apt-get 即可）
