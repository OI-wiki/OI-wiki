**注意**：考虑到算法竞赛的实际情况，本文将不会全面研究语法，只会讲述在算法竞赛中可能会应用到的部分。

本文语法参照 **C++11** 标准。语义不同的将以 **C++11** 作为标准，C++14、C++17 的语法视情况提及并会特别标注。

## Lambda 表达式

Lambda 表达式因数学中的 $\lambda$ 演算得名，直接对应于其中的 lambda 抽象。Lambda 表达式能够捕获作用域中的变量的无名函数对象。我们可以将其理解为一个匿名的内联函数，可以用来替换独立函数或者函数对象，从而使代码更可读。但是从本质上来讲，Lambda 表达式只是一种语法糖，因为它能完成的工作也可以用其他复杂的 C++ 语法来实现。

下面是 Lambda 表达式的语法：

```text
[capture] (parameters) mutable -> return-type {statement}
```

下面我们分别对其中的 capture, parameters, mutable, return-type, statement 进行介绍。

### capture 捕获子句

Lambda 表达式以 capture 子句开头，它指定哪些变量被捕获，以及捕获是通过值还是引用：有 `&` 符号前缀的变量通过引用访问，没有该前缀的变量通过值访问。空的 capture 子句 `[]` 指示 Lambda 表达式的主体不访问封闭范围中的变量。

我们也可以使用默认捕获模式：`&` 表示捕获到的所有变量都通过引用访问，`=` 表示捕获到的所有变量都通过值访问。之后我们可以为特定的变量 **显式** 指定相反的模式。

例如 Lambda 体要通过引用访问外部变量 `a` 并通过值访问外部变量 `b`，则以下子句等效：

-   `[&a, b]`
-   `[b, &a]`
-   `[&, b]`
-   `[b, &]`
-   `[=, &a]`

默认捕获时，会捕获 Lambda 中提及的变量。获的变量成为 Lambda 的一部分；与函数参数相比，调用 Lambda 时不必传递它们。

以下是一些常见的例子：

```cpp
int a = 0;
auto f = []() { return a * 9; };   // Error, 无法访问 'a'
auto f = [a]() { return a * 9; };  // OK, 'a' 被值「捕获」
auto f = [&a]() { return a++; };   // OK, 'a' 被引用「捕获」
                                  // 注意：请保证 Lambda 被调用时 a 没有被销毁
auto b = f();  // f 从捕获列表里获得 a 的值，无需通过参数传入 a
```

### parameters 参数列表

大多数情况下类似于函数的参数列表，例如：

```cpp
auto lam = [](int a, int b) { return a + b; };
std::cout << lam(1, 9) << " " << lam(2, 6) << std::endl;
```

**C++14** 中，若参数类型是泛型，则可以使用 `auto` 声明类型：

```cpp
auto lam = [](auto a, auto b)
```

一个例子：

```cpp
int x[] = {5, 1, 7, 6, 1, 4, 2};
std::sort(x, x + 7, [](int a, int b) { return (a > b); });
for (auto i : x) std::cout << i << " ";
```

这将打印出 `x` 数组从大到小排序后的结果。

由于 **parameters 参数列表** 是可选的，如果不将参数传递给 Lambda 表达式，并且其 Lambda 声明器不包含 mutable，且没有后置返回值类型，则可以省略空括号。

Lambda 表达式也可以将另一个 Lambda 表达式作为其参数。

一个例子：

```cpp
#include <functional>
#include <iostream>

int main() {
  using namespace std;

  // 返回另一个计算两数之和 Lambda 表达式
  auto addtwointegers = [](int x) -> function<int(int)> {
    return [=](int y) { return x + y; };
  };

  // 接受另外一个函数 f 作为参数，返回 f(z) 的两倍
  auto higherorder = [](const function<int(int)>& f, int z) {
    return f(z) * 2;
  };

  // 调用绑定到 higherorder 的 Lambda 表达式
  auto answer = higherorder(addtwointegers(7), 8);

  // 答案为 (7 + 8) * 2 = 30
  cout << answer << endl;
}
```

### mutable 可变规范

利用可变规范，Lambda 表达式的主体可以修改通过值捕获的变量。若使用此关键字，则 parameters **不可省略**（即使为空）。

一个例子，使用 **capture 捕获字句** 中的例子，来观察 a 的值的变化：

```cpp
int a = 0;
auto func = [a]() mutable { ++a; };
```

此时 lambda 中的 a 的值改变为 1，lambda 外的 a 保持不变。

### return-type 返回类型

用于指定 Lambda 表达式的返回类型。若没有指定返回类型，则返回类型将被自动推断（行为与用 `auto` 声明返回值的普通函数一致）。具体的，如果函数体中没有 `return` 语句，返回类型将被推导为 `void`，否则根据返回值推导。若有多个 `return` 语句且返回值类型不同，将产生编译错误。

例如，上文的 `lam` 也可以写作：

```cpp
auto lam = [](int a, int b) -> int
```

再举两个例子：

```cpp
auto x1 = [](int i) { return i; };  // OK
auto x2 = [] { return {1, 2}; };    // Error, 返回类型被推导为 void
```

### statement Lambda 主体

Lambda 主体可包含任何函数可包含的部分。普通函数和 Lambda 表达式主体均可访问以下变量类型：

-   从封闭范围捕获变量
-   参数
-   本地声明的变量
-   在一个 `class` 中声明时，若捕获 `this`，则可以访问该对象的成员
-   具有静态存储时间的任何变量，如全局变量

下面是一个例子

```cpp
#include <iostream>

int main() {
  int m = 0, n = 0;
  [&, n](int a) mutable { m = (++n) + a; }(4);
  std::cout << m << " " << n << std::endl;
  return 0;
}
```

最后我们得到输出 `5 0`。这是由于 `n` 是通过值捕获的，在调用 Lambda 表达式后仍保持原来的值 `0` 不变。`mutable` 规范允许 `n` 在 Lambda 主体中被修改，将 `mutable` 删去则编译不通过。

## 参考文献

-   <https://en.cppreference.com/w/cpp/language/lambda>
