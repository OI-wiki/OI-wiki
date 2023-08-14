author: xingjiapeng, MingqiHuang

Geany 是一个轻量、便捷的编辑器，对于 Linux 环境下的初学者较为友好。

与 Dev-C++ 一样，它可以编译运行单个文件。

不过，它可以在 Linux/Windows/macOS 下运行。

其官网为：<https://geany.org/>

## 优缺点

### 优点

1.  轻量；
2.  可以编译运行单个文件；
3.  不需要太多配置；
4.  跨平台。

### 缺点

1.  没有太多人使用；
2.  在 macOS Catalina 下有一些权限问题[^1]；
3.  新建文件时，默认不会有语法高亮，需要手动切换文件类型。

## 安装

参见 [Download | Geany](https://geany.org/download/)

## 使用技巧

### 切换文件类型

在*文档 -> 设置文件类型*中进行切换。

如 C++ 语言，点击*文档 -> 设置文件类型 -> 编程语言 -> C++ 源文件*，即可看到文件已被转换为 C++ 语言的语法高亮了。

### 设置文件模板

在配置文件目录下建立 templates/files 文件夹，建立在其中的文件即为模板文件，再次打开 Geany，就可以在*文件 -> 从模板新建*中找到它了。

配置文件目录可以通过*帮助 -> 调试信息*的第二、三行找出。

这里给出 macOS 和 Linux 下的默认模板配置文件目录：

-   系统目录：`/usr/share/geany/templates/files/`
-   用户目录：`~/.config/geany/templates/files/`[^2]

## 常见问题

### 兼容深度终端

在*首选项 -> 工具 -> 虚拟终端*，修改终端的命令为：

```bash
deepin-terminal -x "/bin/sh" %c
```

点击「应用」按钮即可。[^3]

## 参考资料与注释

[^1]: 详见：<https://github.com/geany/geany/issues/2344>

[^2]: 来源：<https://wiki.geany.org/config/templates>

[^3]: 来源：Deepin Wiki <https://wiki.deepin.org/>
