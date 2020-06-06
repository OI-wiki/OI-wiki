## 概述

C++ 的 **命名空间** 机制可以用来解决复杂项目中名字冲突的问题。

举个例子：C++ 标准库的所有内容均定义在 `std` 命名空间中，如果你定义了一个叫 `cin` 的变量，则可以通过 `cin` 来访问你定义的 `cin` 变量，通过 `std::cin` 访问标准库的 `cin` 对象，而不用担心产生冲突。

## 声明

下面的代码声明了一个名字叫 `A` 的命名空间：

```cpp
namespace A {
int cnt;
void f(int x) { cnt = x; }
}  // namespace A
```

声明之后，在这个命名空间外部，你可以通过 `A::f(x)` 来访问命名空间 `A` 内部的 `f` 函数。

命名空间的声明是可以嵌套的，因此下面这段代码也是允许的：

```cpp
namespace A {
namespace B {
void f() { ... }
}  // namespace B
void f() {
  B::f();  // 实际访问的是 A::B::f()，由于当前位于命名空间 A
           // 内，所以可以省略前面的 A::
}
}  // namespace A

void f()  //这里定义的是全局命名空间的 f 函数，与 A::f 和 A::B::f 都不会产生冲突
{
  A::f();
  A::B::f();
}
```

##  `using` 指令

声明了命名空间之后，如果在命名空间外部访问命名空间内部的成员，需要在成员名前面加上 `命名空间::` 。

有没有什么比较方便的方法能让我们直接通过成员名访问命名空间内的成员呢？答案是肯定的。我们可以使用 `using` 指令。

 `using` 指令有如下两种形式：

1.   `using 命名空间::成员名;` ：这条指令可以让我们省略某个成员名前的命名空间，直接通过成员名访问成员，相当于将这个成员导入了当前的作用域。
2.   `using namespace 命名空间;` ：这条指令可以直接通过成员名访问命名空间中的 **任何** 成员，相当于将这个命名空间的所有成员导入了当前的作用域。

因此，如果执行了 `using namespace std;` ，就会将 `std` 中的所有名字引入到全局命名空间当中。这样，我们就可以用 `cin` 代替 `std::cin` ，用 `cout` 代替 `std::cout` 。

!!! warning "`using` 指令可能会导致命名冲突！"
    由于 `using namespace std;` 会将 `std` 中的 **所有名字** 引入，因此如果声明了与 `std` 重名的变量或函数，就可能会因为命名冲突而导致编译错误。

    因此在工程中，并不推荐使用 `using namespace 命名空间;` 的指令。

有了 `using` 指令， [C++ 语法基础](./basic.md#cin-cout) 中的代码可以有这两种等价写法：

```cpp
#include <iostream>

using std::cin;
using std::cout;
using std::endl;

int main() {
  int x, y;
  cin >> x >> y;
  cout << y << endl << x;
  return 0;
}
```

```cpp
#include <iostream>

using namespace std;

int main() {
  int x, y;
  cin >> x >> y;
  cout << y << endl << x;
  return 0;
}
```

## 应用

在一些具有多个子任务的问题中，我们可以对每个子任务各开一个命名空间，在其中定义我们解决该子任务所需要的变量与函数，这样各个子任务间互不干扰，会在一定程度上方便调试，也会改善程序的可读性。
