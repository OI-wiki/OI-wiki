 **注意** ：考虑到算法竞赛的实际情况，本文将不会全面研究语法，只会讲述在算法竞赛中可能会应用到的部分。

本文语法参照 **C++11** 标准。语义不同的将以 **C++11** 作为标准，C++14、C++17 的语法视情况提及并会特别标注。

##  `auto` 类型说明符

 `auto` 类型说明符用于自动推导变量等的类型。例如：

```cpp
auto a = 1;        // a 是 int 类型
auto b = a + 0.1;  // b 是 double 类型
```

## 基于范围的 `for` 循环

下面是 **C++20 前** 基于范围的 `for` 循环的语法：

```cpp
for (range_declaration : range_expression) loop_statement
```

上述语法产生的代码等价于下列代码（ `__range` 、 `__begin` 和 `__end` 仅用于阐释）：

```cpp
auto&& __range = range_expression;
for (auto __begin = begin_expr, __end = end_expr; __begin != __end; ++__begin) {
  range_declaration = *__begin;
  loop_statement
}
```

### range_declaration 范围声明

范围声明是一个具名变量的声明，其类型是由范围表达式所表示的序列的元素的类型，或该类型的引用。通常用 `auto` 说明符进行自动类型推导。

### range_expression 范围表达式

范围表达式是任何可以表示一个合适的序列（数组，或定义了 `begin` 和 `end` 成员函数或自由函数的对象）的表达式，或一个花括号初始化器列表。正因此，我们不应在循环体中修改范围表达式使其任何尚未被遍历到的“迭代器”（包括“尾后迭代器”）非法化。

这里有一个例子：

```cpp
for (int i : {1, 1, 4, 5, 1, 4}) std::cout << i;
```

### loop_statement 循环语句

循环语句可以是任何语句，常为一条复合语句，它是循环体。

这里有一个例子：

```cpp
#include <iostream>

struct C {
  int a, b, c, d;
  C(int a = 0, int b = 0, int c = 0, int d = 0) : a(a), b(b), c(c), d(d) {}
};

int* begin(C& p) { return &p.a; }
int* end(C& p) { return &p.d + 1; }

int main() {
  C n = C(1, 9, 2, 6);
  for (auto i : n) std::cout << i << " ";
  std::cout << std::endl;
  // 下面的循环与上面的循环等价
  auto&& __range = n;
  for (auto __begin = begin(n), __end = end(n); __begin != __end; ++__begin) {
    auto ind = *__begin;
    std::cout << ind << " ";
  }
  std::cout << std::endl;
  return 0;
}
```

## Lambda 表达式

Lambda 表达式是能够捕获作用域中的变量的无名函数对象，我们可以将其理解为一个匿名的内联函数。下面是 Lambda 表达式的语法：

```text
[capture] (parameters) mutable -> return-type {statement} 
```

### capture 捕获子句

Lambda 表达式以 capture 子句开头，它指定哪些变量被捕获，以及捕获是通过值还是引用：有 `&` 符号前缀的变量通过引用访问，没有该前缀的变量通过值访问。空的 capture 子句 `[]` 指示 Lambda 表达式的主体不访问封闭范围中的变量。

我们也可以使用默认捕获模式： `&` 表示捕获到的所有变量都通过引用访问， `=` 表示捕获到的所有变量都通过值访问。之后我们可以为特定的变量 **显式** 指定相反的模式。

例如 Lambda 体要通过引用访问外部变量 `a` 并通过值访问外部变量 `b` ，则以下子句等效：

-    `[&a, b]` 
-    `[b, &a]` 
-    `[&, b]` 
-    `[b, &]` 
-    `[=, &a]` 
-    `[&a, =]` 

默认捕获时，会捕获 Lambda 中提及的变量。

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

### mutable 可变规范

利用可变规范，Lambda 表达式的主体可以修改通过值捕获的变量。若使用此关键字，则 parameters **不可省略** （即使为空）。

### return-type 返回类型

若 Lambda 主体只包含一个 `return` 语句或不返回值，则可以省略此部分。若 Lambda 表达式主体包含一个 `return` 语句，则返回类型将被自动推导，返回类型遵循 parameters（除非你想指定一个）。否则编译器会将返回类型推断为 `void` 。

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

-   从封闭范围捕获变量
-   参数
-   本地声明的变量
-   在一个 `class` 中声明时，捕获 `this` 
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

最后我们得到输出 `5 0` 。这是由于 `n` 是通过值捕获的，在调用 Lambda 表达式后仍保持原来的值 `0` 不变。 `mutable` 规范允许 `n` 在 Lambda 主体中被修改，将 `mutable` 删去则编译不通过。

## decltype 说明符

 `decltype` 说明符可以推断表达式的类型。

```cpp
#include <iostream>
#include <vector>

int main() {
  int a = 1926;
  decltype(a) b = a / 2 - 146;         // b 是 int 类型
  std::vector<decltype(b)> vec = {0};  // vec 是 std::vector <int> 类型
  std::cout << a << vec[0] << b << std::endl;
  return 0;
}
```

## constexpr

 `constexpr` 说明符声明可以在编译时求得函数或变量的值。其与 `const` 的主要区别是一定会在编译时进行初始化。用于对象声明的 `constexpr` 说明符蕴含 `const` ，用于函数声明的 `constexpr` 蕴含 `inline` 。来看一个例子

```cpp
int frac(int x) { return x ? x * frac(x - 1) : 1; }
int main() {
  constexpr int a = frac(5);  // ERROR: 函数调用在常量表达式中必须具有常量值
  return 0;
}
```

在 `int frac(int x)` 之前加上 `constexpr` 则编译通过。

## std::tuple

 `std::tuple` 定义于头文件 `<tuple>` ，是固定大小的异类值汇集（在确定初始元素后不能更改，但是初始元素能有任意多个）。它是 `std::pair` 的推广。来看一个例子：

```cpp
#include <iostream>
#include <tuple>
#include <vector>

constexpr auto expr = 1 + 1 * 4 - 5 - 1 + 4;

int main() {
  std::vector<int> vec = {1, 9, 2, 6, 0};
  std::tuple<int, int, std::string, std::vector<int> > tup =
      std::make_tuple(817, 114, "514", vec);
  std::cout << std::tuple_size<decltype(tup)>::value << std::endl;

  for (auto i : std::get<expr>(tup)) std::cout << i << " ";
  // std::get<> 中尖括号里面的必须是整型常量表达式
  // expr 常量的值是 3，注意 std::tuple 的首元素编号为 0，
  // 故我们 std::get 到了一个 std::vector<int>
  return 0;
}
```

### 成员函数

| 函数            | 作用                   |
| ------------- | -------------------- |
|  `operator=`  | 赋值一个 `tuple` 的内容给另一个 |
|  `swap`       | 交换二个 `tuple` 的内容     |

例子

```cpp
constexpr std::tuple<int, int> tup = {1, 2};
std::tuple<int, int> tupA = {2, 3}, tupB;
tupB = tup;
tupB.swap(tupA);
```

### 非成员函数

| 函数              | 作用                           |
| --------------- | ---------------------------- |
|  `make_tuple`   | 创建一个 `tuple` 对象，其类型根据各实参类型定义 |
|  `std::get`     | 元组式访问指定的元素                   |
|  `operator==` 等 | 按字典顺序比较 `tuple` 中的值          |
|  `std::swap`    | 特化的 `std::swap` 算法           |

例子

```cpp
std::tuple<int, int> tupA = {2, 3}, tupB;
tupB = std::make_tuple(1, 2);
std::swap(tupA, tupB);
std::cout << std::get<1>(tupA) << std::endl;
```

## std::function

类模板 `std::function` 是通用多态函数封装器，定义于头文件 `<functional>` 。 `std::function` 的实例能存储、复制及调用任何可调用（_Callable_）目标——函数、Lambda 表达式或其他函数对象，还有指向成员函数指针和指向数据成员指针。

存储的可调用对象被称为 `std::function` 的 **目标** 。若 `std::function` 不含目标，则称它为 **空** 。调用空 `std::function` 的目标将导致抛出 `std::bad_function_call` 异常。

来看例子

```cpp
#include <functional>
#include <iostream>

struct Foo {
  Foo(int num) : num_(num) {}
  void print_add(int i) const { std::cout << num_ + i << '\n'; }
  int num_;
};

void print_num(int i) { std::cout << i << '\n'; }

struct PrintNum {
  void operator()(int i) const { std::cout << i << '\n'; }
};

int main() {
  // 存储自由函数
  std::function<void(int)> f_display = print_num;
  f_display(-9);

  // 存储 Lambda
  std::function<void()> f_display_42 = []() { print_num(42); };
  f_display_42();

  // 存储到成员函数的调用
  std::function<void(const Foo&, int)> f_add_display = &Foo::print_add;
  const Foo foo(314159);
  f_add_display(foo, 1);
  f_add_display(314159, 1);

  // 存储到数据成员访问器的调用
  std::function<int(Foo const&)> f_num = &Foo::num_;
  std::cout << "num_: " << f_num(foo) << '\n';

  // 存储到函数对象的调用
  std::function<void(int)> f_display_obj = PrintNum();
  f_display_obj(18);
}
```

## 参考

1.   [C++ reference](https://en.cppreference.com/) 
2.   [C++ 参考手册](https://zh.cppreference.com/) 
3.   [C++ in Visual Studio](https://docs.microsoft.com/en-us/cpp/overview/visual-cpp-in-visual-studio?view=vs-2019) 
