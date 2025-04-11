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

void f()  // 这里定义的是全局命名空间的 f 函数，与 A::f 和 A::B::f
          // 都不会产生冲突
{
  A::f();
  A::B::f();
}
```

## `using` 指令

声明了命名空间之后，如果在命名空间外部访问命名空间内部的成员，需要在成员名前面加上 `命名空间::`。

有没有什么比较方便的方法能让我们直接通过成员名访问命名空间内的成员呢？答案是肯定的。我们可以使用 `using` 指令。

`using` 指令有如下两种形式：

1.  `using 命名空间::成员名;`：这条指令可以让我们省略某个成员名前的命名空间，直接通过成员名访问成员，相当于将这个成员导入了当前的作用域。
2.  `using namespace 命名空间;`：这条指令可以直接通过成员名访问命名空间中的 **任何** 成员，相当于将这个命名空间的所有成员导入了当前的作用域。

因此，如果执行了 `using namespace std;`，就会在当前作用域将 `std` 中的所有名字引入到全局命名空间当中。这样，我们就可以用 `cin` 代替 `std::cin`，用 `cout` 代替 `std::cout`。

??? warning "`using` 指令可能会导致命名冲突！"
    由于 `using namespace std;` 会将 `std` 中的 **所有名字** 引入，因此如果声明了与 `std` 重名的变量或函数，就可能会因为命名冲突而导致编译错误。
    
    因此在工程中，并不推荐使用 `using namespace 命名空间;` 的指令。

有了 `using` 指令，[C++ 语法基础](./basic.md#cin-与-cout) 中的代码可以有这两种等价写法：

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

## 无名命名空间

当我们在一个作用域里只定义了一个用于防止名字冲突的命名空间时，其定义和使用将可以变得非常简洁。我们可以使用无名命名空间。

形如 `namespace { /* something ... */ } `（省略命名空间的名字）定义的命名空间被称为无名命名空间。一个文件里的无名命名空间会被视为拥有独有的名字，和其他命名空间都不同，但同一个作用域内多个无名命名空间被视为相同的命名空间。在无名命名空间定义后，其中的名字在其外的作用域内可以在使用时被查找到，如同在定义后加入了一条 `using namespace` 指令。

## 应用

### 防止子任务间名字冲突
在一些具有多个子任务的问题中，我们可以对每个子任务各定义一个命名空间，在其中定义我们解决该子任务所需要的变量与函数，这样即使两个子任务的实现中即使声明了相同名字也不会冲突，从而使各个子任务间互不干扰，会在一定程度上方便调试，也会改善程序的可读性。

### 防止与标准库以及环境引入的名字冲突

同时，使用命名空间也可以防止一些算法竞赛中常用的名字与标准冲突，如下例：

```cpp
#include <math.h>
#include <vector>
using namespace std;
namespace Sol {
	int end; // std::end 被 using namespace std; 引入

	int y1; // y1 是 POSIX 定义的第二类 Bessel 函数
	// 因此通常情况下，在 Linux 下会有冲突而在 Windows 下没有

	void solve() {
		// 在 Sol::solve() 里无限定（不用 ::）地使用我们声明的 end 以及 y1 并不会导致名字冲突；
		// 而若以上代码在全局命名空间中，将会导致冲突：
		// 其中 end 只会在名字查找（即编译使用它的代码）时与 std::end 冲突，而 y1 在声明时就会冲突；
		// 并且 y1 的冲突因为与环境有关甚至在 Windows 下不会被发现，却会在 Linux 的评测环境下造成编译错误。
	}
}
int main() {
	Sol::solve();
}
```

## 参考

- [Namespaces - cppreference.com](https://en.cppreference.com/w/cpp/language/namespace)