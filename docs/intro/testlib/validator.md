Validator，即校验器。当你造好了一道题的数据，感觉有点虚，担心数据不合法（不符合题目的限制条件）：上溢、图不连通、不是树……你便需要 validator 来帮助你检查数据是否合法。即便你非常有自信，也最好用 validator 检查一下，比较稳妥。

因为 Coderforces 支持 hack 功能，所以所有 Codeforces 上的题目都必须要有 validator，UOJ 也如此。 [Polygon](../polygon.md) 内建了对 validator 的支持。

请在阅读下文前先阅读 [通用](./general.md) 。

## 概述

我们要做的事情很简单，就是把输入完全读进来然后判断是否合法（当然很多工作可以通过带判断的输入函数），但是有一些小提示：

-   写 validator 时你不能对被 validate 的数据做任何假设，它可能包含任何内容。因此，你要对各种不合法的情况进行判断（使用 Testlib 会大大简化这一流程）。
    -   例如输入一个点数为 $n$ 的树，你的主要工作是判断 $n$ 是否符合范围和判断是否是树。但是切不可在判断过 $n$ 范围之后就不对接下来输入的边的起点与终点的范围进行判断，否则可能会导致你的 validator RE。
    -   即使不会 RE 也不应该不判断，这会导致你的报错不正确。如上例，如果不判断，报错可能会是“不是一棵树”，但是正确的报错应当是“边起点/终点不在 $[1,n]$ 之间”。
-   同时，你也不能对选手的读入方式做任何假设（例如，选手可能逐字符地读入数字，在数字与数字之间只读入一个空格），因此，你必须保证能通过 validate 的数据完全符合输入格式。比如，数据中的每一个空白字符都要在 validator 中显式地读入（如空格和换行）。
-   结束时不要忘记 `inf.readEof()` 。
-   如果题目开放 hack（或者说，validator 的错误信息会给别人看），请使报错信息尽量友好。
    -   读入变量时使用“项别名”。
    -   在判断使用的表达式不那么易懂时，使用 ensuref 而非 ensure。

## 使用方法

直接命令行 `./val` 即可，数据通过 stdin 输入，如果想从文件输入可 `./val < a.in` 。

若数据没有问题则什么都不会输出且返回 0，否则会输出错误信息并返回一个非 0 值。

## 示例

以下是 [CF Gym 100541A - Stock Market](https://codeforces.com/gym/100541/problem/A) 的 validator：

```cpp
#include "testlib.h"

int main(int argc, char* argv[]) {
  registerValidation(argc, argv);
  int testCount = inf.readInt(1, 10, "testCount");
  inf.readEoln();

  for (int i = 0; i < testCount; i++) {
    int n = inf.readInt(1, 100, "n");
    inf.readSpace();
    inf.readInt(1, 1000000, "w");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
      inf.readInt(1, 1000, "p_i");
      if (i < n - 1) inf.readSpace();
    }
    inf.readEoln();
  }

  inf.readEof();
}
```

更多示例可以在 [GitHub](https://github.com/MikeMirzayanov/testlib/tree/master/validators) 中找到。

 **本文部分来自 [Validators with testlib.h - Codeforces](https://codeforces.com/blog/entry/18426) 。 `testlib.h` 的 GitHub 存储库为 [MikeMirzayanov/testlib](https://github.com/MikeMirzayanov/testlib) 。** 
