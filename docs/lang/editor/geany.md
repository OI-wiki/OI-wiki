# Geany

Geany 是一个轻量、便捷的编辑器，对于 Linux 环境下的初学者较为友好。

与 Dev-C++ 一样，它可以编译运行单个文件。

不过，它可以在 Linux/Windows/macOS 下运行。

其官网为： <https://geany.org/> 

## 优缺点

### 优点

1.  轻量；
2.  可以编译运行单个文件；
3.  不需要太多配置；
4.  跨平台。

### 缺点

1.  没有太多人使用；
2.  在 macOS Catalina 下有一些权限问题；
3.  新建文件时，默认不会有语法高亮，需要保存为 C++ 文件后才会有；
4.  如果从模板新建 C++ 文件，后缀名为\*.cxx，而不是我们所熟悉的\*.cpp。

## 安装

### Windows/macOS

在官网上下载安装包安装

### Linux

#### 方法一

使用 `apt` 等包管理器进行安装

#### 方法二

1.  从官网下载源码
2.  终端下运行：

```bash
    ./configure
    make
    sudo make install
```

如遇到 `No package 'gtk+-2.0' found` 可能需要安装 `libgtk2.0-dev` （使用 `apt` 等包管理器 即可）

## 常见问题

兼容深度终端：

在首选项→工具→虚拟终端，修改终端的命令为：

```bash
deepin-terminal -x "/bin/sh" %c
```

点击“应用”按钮后即可。

（来源：Deepin Wiki <https://wiki.deepin.org/> ）
