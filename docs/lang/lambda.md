**注意**：考虑到算法竞赛的实际情况，本文将不会全面研究语法，只会讲述在算法竞赛中可能会应用到的部分。

本文语法参照 **C++11** 标准。语义不同的将以 **C++11** 作为标准，C++14、C++17 的语法视情况提及并会特别标注。

## Lambda 表达式

Lambda 表达式基于数学中的λ演算得名，直接对应于其中的 lambda 抽象。Lambda 表达式能够捕获作用域中的变量的无名函数对象。我们可以将其理解为一个匿名的内联函数，可以用来替换独立函数或者函数对象，从而使代码更可读。但是从本质上来讲，Lambda 表达式只是一种语法糖，因为它能完成的工作也可以用其他复杂的 C++ 语法来实现。

下面是 Lambda 表达式的语法：

```text
[capture] (parameters) mutable -> return-type {statement}
```

下面我们分别对其中的 capture, parameters, mutable, return-type, statement 进行介绍。

### capture 捕获子句

Lambda 表达式以 capture 子句开头，它指定哪些变量被捕获，以及捕获是通过值还是引用：有 `&` 符号前缀的变量通过引用访问，没有该前缀的变量通过值访问。空的 capture 子句 `[]` 指示 Lambda 表达式的主体不访问封闭范围中的变量。

我们也可以使用默认捕获模式：`&` 表示捕获到的所有变量都通过引用访问，`=` 表示捕获到的所有变量都通过值访问。之后我们可以为特定的变量 **显式** 指定相反的模式。

例如 Lambda 体要通过引用访问外部变量 `a` 并通过值访问外部变量 `b`，则以下子句等效：

- `[&a, b]`
- `[b, &a]`
- `[&, b]`
- `[b, &]`
- `[=, &a]`
- `[&a, =]`

默认捕获时，会捕获 Lambda 中提及的变量。获的变量成为 Lambda 的一部分；与函数参数相比，调用 Lambda 时不必传递它们。

以下是一些常见的例子：

```cpp
int a = 0;                         // Define an integer variable
auto f = []() { return a * 9; };   // Error: 'a' cannot be accessed
auto f = [a]() { return a * 9; };  // OK, 'a' is "captured" by value
auto f = [&a]() { return a++; };   // OK, 'a' is "captured" by reference
                                   //      Note: It is the responsibility of the
                                   // programmer to ensure that a is not
// destroyed before the lambda is called.
auto b = f();  // Call the lambda function. a is taken from the capture list and
               // not passed here.
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

由于 **parameters 参数列表** 是可选的，如果不将参数传递给 Lambda 表达式，并且其 Lambda 声明器不包含 mutable，则可以省略空括号。

Lambda 表达式也可以将另一个 Lambda 表达式作为其自变量。

一个例子：

```cpp
#include <functional>
#include <iostream>

int main() {
  using namespace std;

  // 返回另一个计算两数之和 Lambda 表达式
  // another lambda expression that adds two numbers.
  // The returned lambda expression captures parameter x by value.
  auto addtwointegers = [](int x) -> function<int(int)> {
    return [=](int y) { return x + y; };
  };

  // The following code declares a lambda expression that takes another
  // lambda expression as its argument.
  // The lambda expression applies the argument z to the function f
  // and multiplies by 2.
  auto higherorder = [](const function<int(int)>& f, int z) {
    return f(z) * 2;
  };

  // Call the lambda expression that is bound to higherorder.
  auto answer = higherorder(addtwointegers(7), 8);

  // Print the result, which is (7+8)*2.
  cout << answer << endl;
}
```

### mutable 可变规范

利用可变规范，Lambda 表达式的主体可以修改通过值捕获的变量。若使用此关键字，则 parameters **不可省略**（即使为空）。

一个例子，使用 **capture 捕获字句** 中的例子，来观察 a 的值的变化：

```cpp
int a = 0;  // Define an integer variable
auto func = [a]() mutable { ++a; };
```

此时 a 的值改变为 1。

### return-type 返回类型

若 Lambda 主体只包含一个 `return` 语句或不返回值，则可以省略此部分。若 Lambda 表达式主体包含一个 `return` 语句，则返回类型将被自动推导，返回类型遵循 parameters（除非你想指定一个）。否则编译器会将返回类型推断为 `void`。

例如，上文的 `lam` 也可以写作

```cpp
auto lam = [](int a, int b) -> int
```

再举两个例子

```cpp
auto x1 = [](int i) { return i; };  // OK
auto x2 = [] { return {1, 2}; };    // ERROR: 返回类型被推导为 void
```

### statement Lambda 主体

Lambda 主体可包含任何函数可包含的部分。普通函数和 Lambda 表达式主体均可访问以下变量类型：

- 从封闭范围捕获变量
- 参数
- 本地声明的变量
- 在一个 `class` 中声明时，捕获 `this`
- 具有静态存储时间的任何变量，如全局变量

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
