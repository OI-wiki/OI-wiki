**注意**：考虑到算法竞赛的实际情况，本文将不会全面研究语法，只会讲述在算法竞赛中可能会应用到的部分。

本文语法参照 **C++11** 标准。语义不同的将以 **C++11** 作为标准，C++14、C++17 等语法视情况提及并会特别标注。

## `auto` 类型说明符

`auto` 类型说明符用于自动推导变量等的类型。例如：

```cpp
auto a = 1;        // a 是 int 类型
auto b = a + 0.1;  // b 是 double 类型
```

注意 `auto` 会去除引用，如果不希望出现拷贝开销，需要手动指定：

```cpp
int a = 1;
int& b = a;
auto c = b;   // c 是 int 类型，有拷贝开销
auto& e = a;  // e 是 int& 类型，没有拷贝开销
```

## decltype 说明符

`decltype` 可以根据 **实体** 或 **表达式** 推断类型，注意二者推导类型的方式不同，错误使用可能造成悬垂引用。竞赛中不常用，此处仅粗略介绍。

```cpp
#include <iostream>
#include <vector>

int main() {
  int a = 1926;
  decltype(a) b;                       // 根据实体推断， b 是 int 类型
  decltype(1 + 1) c;                   // 根据表达式推断，c 是 int 类型
  decltype((a)) d = a;                 // 根据表达式推断，d 是 int& 类型！
  std::vector<decltype(b)> vec = {0};  // 根据实体推断，vec 是 std::vector <int> 类型
  return 0;
}
```

## constexpr

> 另请参阅 [常量表达式 constexpr（C++11）](const.md#常量表达式-constexprc11)

## 基于范围的 `for` 循环

使用范围 for 遍历可迭代对象，与使用迭代器遍历的效率相同。上述二者的效率一般优于索引遍历，因为不需要根据索引寻址。

下面是一种简单的基于范围的 `for` 循环的语法：

```cpp
for (item_declaration : range_initializer) statement
```

比如：

```c++
std::array<int, 4> arr = {1, 2, 3, 4};
for (int x : arr) {
  std::cout << x << std::endl;
}
```

上述语法产生的代码效果等价于下列代码：

```cpp
std::array<int, 4> arr = {1, 2, 3, 4};
for (auto px = arr.begin(), ed = arr.end(); px != ed; ++px) {
  std::cout << *px << std::endl;
}
```

### item-declaration 项声明

声明一个变量用于接受右侧容器中的元素，变量类型要与容器内子元素类型一致。可以用 `auto` 自动推导类型，复杂类型常用 `auto&` 防止拷贝开销。

### range-initializer 范围初始化器

范围初始化器可以是任何一种可迭代的对象（比如数组，或定义了 `begin` 和 `end` 成员函数的类对象）。如果放入表达式，表达式也只会计算一次。

例子：

```cpp
int a[] = {1, 1, 4, 5, 1, 4};
std::vector<int> b{1, 1, 4, 5, 1, 4};
std::map<std::string, int> c{{"114", 114}, {"514", 514}};
for (int i : a) std::cout << i;
for (auto i : b) std::cout << i;
// 下方 i 的类型是 std::pair<const std::string, int>&
for (auto& i : c) std::cout << i.first << i.second;
for (auto i : {1, 1, 4, 5, 1, 4}) std::cout << i;
```

### 自定义类型支持范围 for

只需提供 `begin` 和 `end` 成员函数，返回类型需要支持比较、自增和解引用（`*` 运算符）。

这里有一个例子：

```cpp
#include <iostream>

struct C {
  int a[4];

  int* begin() { return a; }
  int* end() { return a + 4; }
};

int main() {
  C c = {1, 9, 2, 6};
  for (auto i : c) std::cout << i << " ";
  std::cout << std::endl;
  // output: 1 9 2 6
  return 0;
}
```

### 初始化语句（C++20）

在 C++20 中还可以使用初始化语句实现一些功能，例如循环计数器：

```cpp
#include <iostream>
#include <vector>

int main() {
  std::vector<int> v = {0, 1, 2, 3, 4, 5};

  for (int counter = 0; auto i : v)  // the init-statement (C++20)
    std::cout << counter++ << ' ' << i << std::endl;
}
```

## 结构化绑定（C++17）

结构化绑定（Structured binding）是 C++17 提供的一种语法糖，可以方便的提取子元素或子元素的引用，像这样：

```cpp
struct C {
    int x{1}, y{2};
};
int arr[]{ 4, 5, 6 };

auto [c1, c2] = C{};      // c1=1,c2=2; int 类型
auto& [a1, a2, a3] = arr; // a1=arr[0],a2=arr[1],a3=arr[2]; int& 类型
```

注意以下几点：

-   左侧的变量数和右侧的s子元素数必须一样
-   类型声明需要使用 `auto`
-   可以使用 `&` 修饰获取引用

你可以在遍历 `map` 容器时这样写：

```cpp
std::map<std::string, int> m = {{"k1", 1}, {"k2", 2}};

// 使用 "auto&" ，没有拷贝开销
for (auto& [k, v] : m) {
  // k 的类型是 const std::string& ，因为键自带 const 修饰
  // v 的类型是 int&
  std::cout << k << ' ' << v << std::endl;
}
```

## std::tuple 元组

定义于头文件 `<tuple>`，即 [元组](https://zh.cppreference.com/w/cpp/utility/tuple)，是 `std::pair` 的推广，可以存储多个不同类型的值，下面来看一个例子：

```cpp
#include <iostream>
#include <tuple>
#include <vector>

constexpr auto expr = 4 - 1;  // expr = 3

int main() {
  std::vector<int> vec = {1, 9, 2, 6, 0};
  std::tuple<int, int, std::string, std::vector<int>> tup =
      std::make_tuple(817, 114, "514", vec);

  // 使用 get<> 获取子元素，尖括号内必须是整型常量表达式
  for (auto i : std::get<expr>(tup)) std::cout << i << " ";
  // 首元素编号为 0，故我们 std::get<3> 得到了一个 std::vector<int>
  return 0;
}
```

在 C++17 之后，可以使用结构化绑定提取值，像这样：

```cpp
std::vector<int> vec = {1, 9, 2, 6, 0};
std::tuple<int, int, std::string, std::vector<int>> tup =
    std::make_tuple(817, 114, "514", vec);

auto& [a, b, c, d] = tup;  // C++17 Structured binding
std::cout << a << ' ' << b << c << std::endl;
std::cout << d.size() << ' ' << d[2] << std::endl;
```

### 成员函数

| 函数          | 作用                   |
| ----------- | -------------------- |
| `operator=` | 赋值一个 `tuple` 的内容给另一个 |
| `swap`      | 交换二个 `tuple` 的内容     |

例子：

```cpp
constexpr std::tuple<int, int> tup = {1, 2};
std::tuple<int, int> tupA = {2, 3}, tupB;
tupB = tup;
tupB.swap(tupA);
```

### 非成员函数

| 函数             | 作用                           |
| -------------- | ---------------------------- |
| `make_tuple`   | 创建一个 `tuple` 对象，其类型根据各实参类型定义 |
| `std::get`     | 元组式访问指定的元素                   |
| `operator==` 等 | 按字典顺序比较 `tuple` 中的值          |
| `std::swap`    | 特化的 `std::swap` 算法           |

例子：

```cpp
std::tuple<int, int> tupA = {2, 3}, tupB;
tupB = std::make_tuple(1, 2);
std::swap(tupA, tupB);
std::cout << std::get<1>(tupA) << std::endl;
```

## 函数对象

可以使用函数调用运算符 `operator()` 的对象，称为函数对象（FunctionObject）。

它不是一种语言特性，而是一种 [概念或者要求](https://zh.cppreference.com/w/cpp/named_req/FunctionObject)，在标准库中广泛应用。

函数对象大致可以分成两类：

1.  函数指针
2.  重载了 `operator()` 运算符的类对象

[lambda](./lambda.md) 就是典型的第二类函数对象，它将捕获的内容存放在成员变量中，并重载了函数调用运算符。

## Lambda 表达式

> 请参考 [Lambda 表达式](lambda.md) 页面。

## std::function

???+ warning "请注意性能开销"
    `std::function` 会引入一定的性能开销，经 [Benchmark](./lambda.md#lambda-中的递归) 测试，通常会造成 2 到 3 倍以上的性能损失。
    
    因为它使用了类型擦除的技术，而这通常借由虚函数机制实现，调用虚函数会引入额外的 [开销](https://stackoverflow.com/questions/5057382/what-is-the-performance-overhead-of-stdfunction)。
    
    请考虑使用 [**Lambda 表达式**](./lambda.md) 或者 [**函数对象**](#函数对象) 代替。

`std::function` 是通用函数封装器，定义于头文件 `<functional>`。

`std::function` 的实例能存储、复制及调用任何 [**可调用**](https://zh.cppreference.com/w/cpp/named_req/Callable) 对象，这包括 [**Lambda 表达式**](./lambda.md)、成员函数指针或其他 [**函数对象**](#函数对象)。

若 `std::function` 不含任何可调用对象（比如默认构造），调用时将抛出 [`std::bad_function_call`](https://zh.cppreference.com/w/cpp/utility/functional/bad_function_call) 异常。

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

## 可变参数函数模板

在 C++11 之前，类模板和函数模板都只能接受固定数目的模板参数。C++11 允许 **任意个数、任意类型** 的模板参数。

这里仅简要介绍可变参数 **函数** 模板。

下列代码声明的函数模板 `fun` 可以接受任意个数、任意类型的模板参数作为它的模板形参。

```cpp
template <typename... Clazz>
void fun(Clazz... paras) {}
```

`paras` 是一个函数参数包（function parameter pack），表示 0 个或多个函数参数。`Clazz` 是一个模板参数包（template parameter pack），一个函数模板只能含有一个模板参数包，且模板参数包必须位于所有模板参数的最右侧。

可以简单理解：

-   模板参数包 是一堆类型
-   函数参数包 是一堆变量

现在可以这么调用 `fun` 函数：

```cpp
fun();
fun(1);
fun(1, 2, 3);
fun(1, 0.0, "abc");
```

### 参数包展开

#### 参数包展开语法

参数包展开非常简单，使用 `...` 即可，将自动使用 `,` 分隔。比如：

```cpp
template <class A, class... C>
void func(A arg1, C... arg2) {
  // C 是 模板参数包"template parameter pack"
  tuple<A, C...>();  // 展开成 tuple<int, int, double, bool>();

  // arg2 是函数参数包"function parameter pack"
  func(arg2...);  // 展开成 func( 2, 1.1, true );
}

func(1, 2, 1.1, true);
```

参数包展开时还可以附带需要的运算，比如：

```cpp
template <class A, class... C>
void func(A arg1, C... arg2) {
  func((arg2 + 1)...);
  // 展开成 func( (2+1) , (1.1+1), (2.1f+1) );
}

func(1, 2, 1.1, 2.1f);
```

#### 终止函数

上面的函数无法运行，因为参数数量不断减少，最后变为空参并报错。

我们需要指定终止条件，可以提供一个普通函数，像这样：

```cpp
void func() {}

template <class A, class... C>
void func(A arg1, C... arg2) {
  std::cout << arg1 << std::endl;
  func((arg2 + 1)...);
}

func(1, 2, 1.1, 2.1f);
```

这样，参数数量不为 0 时会调用模板，空参时会调用普通函数，就能正常运行了。

### 折叠表达式（C++17）

C++17 提供了一种简便的语法处理 **函数参数包**，他的语法是这样的（必须用小括号包裹）：

1.  `( pack op ... )`，会变成 `(E1 op (... op (EN-1 op EN)))`
2.  `( ... op pack )`，会变成 `(((E1 op E2) op ...) op EN)`
3.  `( pack op ... op init )`，会变成 `(E1 op (... op (EN−1 op (EN op I))))`
4.  `( init op ... op pack )`，会变成 `((((I op E1) op E2) op ...) op EN)`

简单演示一下就好理解了：

```cpp
template <class... C>
void func(C... args) {
  (std::cout << ... << args) << std::endl;
  // 语法 4, 等价于 ↓
  // ( ( ( std::cout << 1 ) << 2.1 ) << true ) << std::endl;
  // 输出: 12.11  注意true输出成了1，因为这里没有指定boolalpha

  std::cout << (args && ...) << std::endl;
  // 语法 1, 等价于 ↓
  // std::cout << ( 1 && ( 2.1 && true ) ) ) << std::endl;
  // 输出: 1
}

func(1, 2.1, true);
```

### 缩写函数模板（C++20）

C++20起可以直接使用 `auto ...` 作为参数类型，实现函数模板的缩写：

```cpp
void func(auto... args) {
  (std::cout << ... << args) << std::endl;
}
```

注意它本质上仍然是函数模板，与下面的写法等价：

```cpp
template <class... T>
void func(T... args) {
  (std::cout << ... << args) << std::endl;
}
```


## 范围库（C++20）

> 范围库是对迭代器和泛型算法库的一个扩展，使得迭代器和算法可以通过组合变得更强大，并且减少错误。

范围即可遍历的序列，包括数组、容器、视图等。

在需要对容器等范围进行复杂操作时，[范围库](https://zh.cppreference.com/w/cpp/ranges) 可以使得算法编写更加容易和清晰。

### View 视图

视图是一种轻量对象，通过特定机制（如自定义迭代器）来实现一些算法，给范围提供了更多的遍历方式以满足需求。

范围库中已实现了一些常用的视图，大致分为两种：

1.  **范围工厂**，用于构造一些特殊的范围工厂，使用这类工厂可以省去手动构造容器的步骤，降低开销，直接生成一个范围。
2.  **范围适配器**，提供多种多样的遍历支持，既能像函数一样调用，也可以通过管道运算符 `|` 连接，实现链式调用。

**范围适配器** 作为 [**范围适配器闭包对象**](https://zh.cppreference.com/w/cpp/named_req/RangeAdaptorClosureObject)，也属于 [**函数对象**](#函数对象)，它们重载了 `operator|`，使得它们能够像管道一样拼装起来。

??? note "管道运算符"
    此处的 `|` 应该理解成管道运算符，而非按位或运算符，这个用法来自于 Linux 中的 [管道](https://zh.wikipedia.org/wiki/%E7%AE%A1%E9%81%93_\(Unix\))。

在复杂操作下，也能保持良好可读性，有以下特性：

若 A、B、C 为一些范围适配器闭包对象，R 为某个范围，其他字母为可能的有效参数，表达式

    R | A(a) | B(b) | C(c, d)

等价于

    C(B(A(R, a), b), c, d)

下面以 `ranges::take_view` 与 `ranges::iota_view` 为例：

```cpp
#include <iostream>
#include <ranges>

int main() {
  const auto even = [](int i) { return 0 == i % 2; };

  for (int i : std::views::iota(0, 6) | std::views::filter(even))
    std::cout << i << ' ';
}
```

1.  范围工厂 `std::views::iota(0, 6)` 生成了从 0 到 5 的整数序列的范围
2.  范围适配器 `std::views::filter(even)` 过滤前一个范围，生成了一个只剩下偶数的范围
3.  两个操作使用管道运算符链接

上述代码不需要额外分配堆空间存储每步生成的范围，实际的生成和过滤运算发生在遍历操作中（更具体而言，内部的迭代器构造、自增和解引用），也就是零开销（Zero Overhead）。

同时，外部输入的范围生命周期，等同于 **范围适配器** 的内部元素的生命周期。如果外部范围（比如容器、范围工厂）已经销毁，那么再对这些的视图遍历，其效果与解引用悬垂指针一致，属于未定义行为。

为了避免上述情况，应该严格要求适配器的生命周期位于其使用的任何范围的生命周期内。

???+ note "范围被销毁时，视图内元素均悬垂"
    ```cpp
    #include <iostream>
    #include <ranges>
    #include <vector>
    
    using namespace std;
    
    int main() {
      auto view = [] {
        vector<int> vec{1, 2, 3, 4, 5};
        return vec | std::views::filter([](int i) { return 0 == i % 2; });
      }();
    
      for (int i : view) cout << i << ' ';  // runtime undefined behavior
    
      return 0;
    }
    ```

### Constrained Algorithm 受约束的算法

> C++20 在命名空间 std::ranges 中提供大多数算法的受约束版本，可以用迭代器 - 哨位对或单个 range 作为实参来指定范围，并且支持投影和指向成员指针可调用对象。另外还更改了大多数算法的返回类型，以返回算法执行过程中计算的所有潜在有用信息。

这些算法可以理解成旧标准库算法的改良版本，均为函数对象，提供更友好的重载和入参类型检查（基于 [`concept`](https://zh.cppreference.com/w/cpp/language/constraints)），让我们先以 `std::sort` 和 `ranges::sort` 的对比作为例子

```cpp
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
  vector<int> vec{4, 2, 5, 3, 1};

  sort(vec.begin(), vec.end());  // {1, 2, 3, 4, 5}

  for (const int i : vec) cout << i << ", ";
  cout << '\n';

  ranges::sort(vec, ranges::greater{});  // {5, 4, 3, 2, 1}

  for (const int i : vec) cout << i << ", ";

  return 0;
}
```

`ranges::sort` 和 `sort` 的算法实现相同，但提供了基于范围的重载，使得传参更为简洁。其他的 `std` 命名空间下的算法，多数也有对应的范围重载版本位于 `ranges` 命名空间中。

使用这些范围入参，再结合使用上节视图，能允许我们在进行复杂操作的同时，保持代码可读性，让我们看一个例子：

```cpp
#include <algorithm>
#include <array>
#include <iostream>
#include <ranges>

using namespace std;

int main() {
  const auto& inputs = views::iota(0u, 9u);  // 生产 0 到 8 的整数序列
  const auto& chunks = inputs | views::chunk(3);  // 将序列分块，每块 3 个元素
  const auto& cartesian_product =
      views::cartesian_product(chunks, chunks);  // 计算对块自身进行笛卡尔积

  for (const auto [l_chunk, r_chunk] : cartesian_product)
    // 计算笛卡尔积下的两个块整数的和
    cout << ranges::fold_left(l_chunk, 0u, plus{}) +
                ranges::fold_left(r_chunk, 0u, plus{})
         << ' ';
}
```

???+ note "输出："
    6 15 24 15 24 33 24 33 42

## 参考

1.  [C++ 参考手册](https://zh.cppreference.com/)
