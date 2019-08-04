disqus:

## 环境配置

工欲善其事，必先利其器。

### 编译器

#### Windows

需要去 [MinGW Distro](https://nuwen.net/mingw.html) 下载 MinGW 并安装

#### macOS

在终端中执行：

```bash
xcode-select --install`
```

#### NOI Linux

使用 `g++ -v` 来检查是否安装过 `g++` 。

使用如下命令可以安装：

```bash
sudo apt update && sudo apt install g++
```

### 编辑器

IDE 操作较为简单，一般入门玩家会选用 IDE 来编写代码。在竞赛中最常见的是 Dev-C++（如果考试环境是 Windows 系统，一般也会提供这一 IDE）。详情可以阅读[相关页面](/intro/editor/devcpp)。

熟练之后也有玩家会使用更灵活的命令行来编译代码，这样就不依赖 IDE 了，而是使用自己熟悉的文本编辑器编写代码。

## 第一行代码

通过这样一个示例程序来展开 C++ 入门之旅吧～

```c++
#include <cstdio>  // 引用头文件

int main() {                // 定义 main 函数
  printf("Hello, world!");  // 输出 Hello, world!
  return 0;                 // 返回 0，结束 main 函数
}
```
