## 简介

AtCoder Library（简称 AC Library、ACL）是 [AtCoder](https://atcoder.jp) 提供的一个官方算法库。

ACL 的宗旨是让每一个 AtCoder 用户都可以用最少的学习成本、最短的学习时间来使用该库，并且最大限度地方便算法竞赛。在 AtCoder 上评测 C++ 代码时默认包含 ACL。

ACL 是 [开源项目](https://github.com/atcoder/ac-library)。这意味着你也可以在其他 OJ 上（通过手动包含头文件、使用展开脚本等方式）使用 ACL。

该中文文档为非官方译制，不保证适用于最新版算法库，也不保证表述的准确性。请以 [英文官方文档](https://atcoder.github.io/ac-library/production/document_en/index.html) 或 [日文官方文档](https://atcoder.github.io/ac-library/production/document_ja/index.html) 为准。

以下是官方文档内容翻译。

## 如何安装

- 前往 [GitHub Releases](https://github.com/atcoder/ac-library/releases/) 下载并解压 zip 文件，会得到一个 `atcoder` 目录。
- 如果你使用 g++，你可以将待编译的 `main.cpp` 与 `atcoder` 放在同一个目录下，然后运行 `g++ main.cpp -std=c++14 -I .`。
    - 为了正常使用 AtCoder Library，确保你的 C++ 版本设置为 14 或更高。
- 关于其他安装和使用的方式，请参见 [附录](./appendix.md)。

## 约定

- 如果输入不满足约束条件，则行为未定义。
- 简单起见，我们有以下类型的缩写：
    - `uint` 是 `unsigned int` 的缩写。
    - `ll` 是 `long long` 的缩写。
    - `ull` 是 `unsigned long long` 的缩写。
- 约定 $0^0=1$。
- 除非特别说明，否则图中允许存在重边和自环。

## 列表

`#include <atcoder/all>` 包含以下所有内容。

### 数据结构

- [`#include <atcoder/fenwicktree>` 树状数组](./fenwicktree.md)
- [`#include <atcoder/segtree>` 线段树](./segtree.md)
- [`#include <atcoder/lazysegtree>` 惰性线段树（带懒惰标记的线段树）](./lazysegtree.md)
- [`#include <atcoder/string>` 字符串](./string.md)

### 数学

- [`#include <atcoder/math>` 数学](./math.md)
- [`#include <atcoder/convolution>` 卷积](./convolution.md)
- [`#include <atcoder/modint>` 自取模整数](./modint.md)

### 图论

- [`#include <atcoder/dsu>` 并查集](./dsu.md)
- [`#include <atcoder/maxflow>` 最大流](./maxflow.md)
- [`#include <atcoder/mincostflow>` 最小费用流](./mincostflow.md)
- [`#include <atcoder/scc>` 强连通分量](./scc.md)
- [`#include <atcoder/twosat>` 2-SAT](./twosat.md)

## 附录

参见 [附录及常见问题](./appendix.md)。

## 测试

参见 [AtCoder Library Practice Contest](https://atcoder.jp/contests/practice2)。

## 协议

`atcoder` 文件夹中的文件均为 CC0 许可证。有关更多信息，请查阅 `atcoder/LICENSE`。
