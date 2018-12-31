如果你正在使用 C++ 出一道算法竞赛题目，Testlib 是编写相关程序（generator, validator, checker, interactor）时的优秀辅助工具。它是俄罗斯和其他一些国家的出题人的必备工具，许多比赛也都在用它：ROI, ICPC 区域赛，所有 Codeforces round……

Testlib 库仅有 `testlib.h` 一个文件，使用时仅需在所编写的程序开头添加 `#include "testlib.h"` 即可。

Testlib 的具体用途：

-   编写 [Generator](./generator.md)，即数据生成器。
-   编写 [Validator](./validator.md)，即数据校验器，判断生成数据是否符合题目要求，如数据范围、格式等。
-   编写 [Interactor](./interactor.md)，即交互器，用于交互题。
-   编写 [Checker](./checker.md)，即 [Special Judge](/intro/spj.md)。

Testlib 与 Codeforces 开发的 [Polygon](https://polygon.codeforces.com/) 出题平台完全兼容。

`testlib.h` 在 2005 年移植自 `testlib.pas`，并一直在更新。Testlib 与绝大多数编译器兼容，如 VC++ 和 GCC g++，并兼容 C++11。

**本文翻译自[Testlib - Codeforces](https://codeforces.com/testlib)。`testlib.h` 的 GitHub 存储库为[MikeMirzayanov/testlib](https://github.com/MikeMirzayanov/testlib)。**
