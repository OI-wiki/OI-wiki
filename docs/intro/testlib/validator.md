当你造好了一道题的数据，感觉有点虚，担心数据不合法（不符合题目的限制条件）：上溢、图不连通、不是树……你便需要 validator 来帮助你检查数据是否合法。

即便你非常有自信，也最好用 Validator 检查一下，比较稳妥。所有 Codeforces 上的题目都必须要有 validator，[Polygon](https://polygon.codeforces.com/)内建了对 validator 的支持。

使用 Testlib 写 Validator 是很方便的。

请在阅读下文前先阅读[通用](./general/)。（然后就没什么可说的了）

## 示例

以下是[100541A - Stock Market](https://codeforces.com/gym/100541/problem/A)的 validator：

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

真香，基本不会写出 bug。

更多示例可以在[GitHub](https://github.com/MikeMirzayanov/testlib/tree/master/validators)中找到。

???+ warning
    Validator 是非常严格的，它需要保证有正确的空格或换行。例如当你读入一个整数时，当前流指针位置为一个空格后接一个整数，Testlib 仍将抛出错误。

 **本文翻译自[Validators with testlib.h - Codeforces](https://codeforces.com/blog/entry/18426)。 `testlib.h` 的 GitHub 存储库为[MikeMirzayanov/testlib](https://github.com/MikeMirzayanov/testlib)。** 
