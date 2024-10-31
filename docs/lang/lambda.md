**注意**：考虑到算法竞赛的实际情况，本文将不会全面研究语法，只会讲述在算法竞赛中可能会应用到的部分。

本文语法参照 **C++11** 标准，其他高版本的标准语法视情况提及并会特别标注。

## Lambda 表达式

Lambda 表达式因数学中的 $\lambda$ 演算得名，直接对应于其中的 lambda 抽象。编译器在编译时会根据语法生成一个匿名的 **函数对象**，以捕获的变量作为其成员，参数和函数体用于实现 `operator()` 重载。

??? note "函数对象（Function Object）"
    函数对象是一种类对象，一般通过重载 `operator()` 实现，所以能像函数一样调用。相较于使用普通的函数，函数对象有很多优点，例如可以保存状态，可以作为参数传递给其他函数等。

以下是 lambda 的一种语法：

```text
[capture] (parameters) mutable -> return-type {statement}
```

下面我们分别对语法中的各部分进行介绍。

### statement 函数体

函数体与普通函数函数体类似，除了能访问参数和全局变量等，还可访问 [捕获](#capture-捕获子句) 的变量。

### capture 捕获子句

lambda 以 capture 子句开头，它指定哪些变量被捕获，捕获列表可为空，或指定捕获方式：有 `&` 符号前缀的变量通过 [引用](./reference.md) 访问，没有该前缀的变量通过值访问。

我们也可以使用默认捕获模式，捕获 Lambda 中提及的所有变量：`&` 表示捕获到的所有变量都通过引用访问，`=` 表示捕获到的所有变量都通过值访问。

在默认捕获之后，仍然可以为特定的变量 **显式** 指定捕获模式。

如果需要引用访问外部变量 `a`，并通过值访问外部变量 `b`，那么以下捕获子句都可以做到：

-   `[&a, b]`
-   `[b, &a]`
-   `[&, b]`
-   `[b, &]`
-   `[=, &a]`

以下是一些常见的例子：

```cpp
int a = 0;
auto f0 = []() { return a * 9; }; // Error, 无法访问 'a'
auto f1 = [a]() { return a * 9; }; // OK, 'a' 被值「捕获」
auto f2 = [&a]() { return a++; }; // OK, 'a' 被引用「捕获」
// 注意，请保证被调用时 a 没有被销毁
auto b = f(); // f 从捕获列表里获得 a 的值，无需通过参数传入 a
```

在没有捕获时，lambda 可以转换为函数指针：

```cpp
int (*f)() = [] {
  std::cout << "Hello, World!" << std::endl;
  return 0;
};
int v = f(); // 输出 "Hello, World!"
```

#### 带初始化器的捕获（C++14）

在 **C++14** 中，我们可以使用带初始化器的捕获，此时的捕获成员声明如同使用 `auto`，例如：

```cpp
int x = 4;

auto y = [&r = x, x = x + 1]() -> int {
  r += 2;
  return x * x;
}(); // 更新 ::x 到 6 并初始化 y 为 25。

```

等价于

```cpp
int x = 4;

int y;
{
  // 捕获列表初始化
  auto &r = x;
  auto x = x + 1; // 本地 x 会隐藏外部 x

  // 函数体及其返回值
  r += 2;
  y = x * x; // 使用本地 x 变量
}
```

### parameters 参数列表

大多数情况下类似于函数的参数列表，例如：

```cpp
int x[] = {5, 1, 7, 6, 1, 4, 2};
std::sort(x, x + 7, [](int a, int b) { return (a > b); });
for (auto i : x) std::cout << i << " ";
```

这将打印出 `x` 数组从大到小排序后的结果。

由于 **parameters 参数列表** 是可选的，如果不将参数传递给 lambda，并且其声明不包含 [mutable](#mutable-可变规范)，且没有后置返回值类型，则可以省略空括号。

??? note " 使用 `auto` 声明的参数 "
    **C++14** 后，若参数使用 `auto` 声明类型，那么会构造一个 [泛型 Lambda 表达式](#泛型-lambdac14)。

### mutable 可变规范

使得函数体可以修改通过值捕获的变量。

```cpp
int a = 0;
auto by_value = [a]() mutable { ++a; };
auto by_ref = [&a] { ++a; };

by_value();
by_ref();
```

在执行完 `by_value()` 后，`by_value` 的捕获成员 `a` 为 1，但外部的变量 `a` 依然为 0。
而在执行完 `by_ref()` 后，外部 `a` 的值变为 1。

### return-type 返回类型

用于指定 lambda 表达式的返回类型。如果省略，则返回类型将被自动推断（行为与用 `auto` 声明返回值的函数一致）。

多个 `return` 语句且推导类型不一致时，将产生编译错误。

```cpp
auto lam = [](int a, int b) -> int { return 0; };

auto x1 = [](int i) {
  return i;
};

auto x2 = [](bool condition) {
  if (condition) return 1;
  return 1.0;
}; // Error, 推导类型不一致
```

### 泛型 Lambda（C++14）

使用 `auto` 作为参数类型，可以构造泛型 lambda。

```cpp
auto add = [](auto a, auto b) { return a + b; };
```

在 [cpp insights](https://cppinsights.io) 中可以观察到编译器生成的 `lambda` 类定义：

```cpp
class add_lambda {
 public:
  template <class T, class U>
  auto operator()(T a, U b) const {
    return a + b;
  }
};

add_lambda add{};
```

`add` 两个参数声明均使用了 `auto`，对应为 `add_lambda` 类的 `operator()` 函数模板的两个模板参数 `T` 和 `U`。

### Lambda 表达式的应用

#### 作为标准库算法的算子

从大到小排序：

```cpp
std::vector<int> v = {1, 2, 3, 4, 5};
std::sort(v.begin(), v.end(), [](int a, int b) { return a > b; });
```

使用 [std::find\_if](https://zh.cppreference.com/w/cpp/algorithm/find) 查找第一个大于 3 的元素：

```cpp
std::vector<int> v = {1, 2, 3, 4, 5};
auto it = std::find_if(v.begin(), v.end(), [](int a) { return a > 3; });
```

#### 控制中间变量的生命周期

在算法竞赛中，我们会遇到这样的场景：一个变量的初始化需要使用之前声明的变量，其初始化过程又生成占用空间较大的中间变量。

我们希望能尽快析构这些中间变量，以降低内存消耗。此时，我们可以使用 lambda 来控制这些中间变量的生命周期。

```cpp
void solution(const vector<int>& input) {
  int b = [&] {
    vector<int> large_objects(input.size());
    int c = 0;

    for (int i = 0; i < large_objects.size(); ++i)
      large_objects[i] = i + input[i];

    for (int i = 0; i < input.size(); ++i) c += large_objects[input[i]];

    return c;
  }();

  // ...
}
```

相较于使用块作用域，lambda 可以允许我们使用返回值，使得代码更加简洁；相较于函数，我们不需要额外起名和声明被捕获的各种参数，使得代码更加紧凑。

#### 递归

由于 lambda 在函数体内定义时类型仍不完整，也就无法通过捕获自身的方式实现递归，但我们可以通过其他方式实现。下面通过一个求斐波那契数列的例子来说明。

##### 泛型（C++14）

将参数声明为 `auto`，就避免了定义不完整的问题，函数模板的实例化只在调用处进行，使用时仅需传入 lambda 自身即可。

```cpp
auto nth_fibonacci = [](auto self, int n, int a = 0, int b = 1) -> int {
  return n ? self(self, n - 1, a + b, a) : b;
};

cout << nth_fibonacci(nth_fibonacci, 10);
```

##### 显式对象形参（C++23）

在 **C++23** 中，[显式对象形参](https://zh.cppreference.com/w/cpp/language/function#.E5.BD.A2.E5.8F.82.E5.88.97.E8.A1.A8) 可以在 lambda 的参数中使用。

```cpp
auto nth_fibonacci = [](this auto self, int n, int a = 0, int b = 1) -> int {
  return n ? self(n - 1, a + b, a) : b;
};

cout << nth_fibonacci(10);
```

##### 其他方式

从本质上来讲，lambda 只是通过实现匿名函数对象一种语法糖，那么我们可以通过定义函数对象来实现递归。

```cpp
class fibonacci_fn {
 public:
  int operator()(int n) const {
    return n ? (*this)(n - 1) + (*this)(n - 2) : 1;
  }
};

cout << fibonacci_fn{}(10);
```

??? warning " 不建议使用 `std::function` 实现的递归 "
    `std::function` 的类型擦除通常需要分配额外内存，同时间接调用带来的寻址操作会进一步降低性能。
    
    在 [Benchmark](https://quick-bench.com/q/6ZIWCCvBlq_Cakrae05c11vC0BI) 测试中，使用 Clang 17 编译器， libc++ 作为标准库，`std::function` 实现比 lambda 实现的递归慢了约 7 倍。
    
    以下是测试代码
    
    ```cpp
    #include <algorithm>
    #include <functional>
    #include <numeric>
    #include <random>
    
    using namespace std;
    
    const auto& nums = [] {
        random_device rd;
        mt19937 gen{rd()};
        array<unsigned, 16> arr{};
        
        std::iota(arr.begin(), arr.end(), 0u);
        ranges::shuffle(arr, gen);

        return arr;
    }();
    
    static void std_function_fib(benchmark::State& state) {
        std::function<int(int, int, int)> fib;
        
        fib = [&](int n, int a, int b) { return n ? fib(n - 1, a + b, a) : b; };
        
        auto n_fibonacci = [&](int n) { return fib(n, 0, 1); };
        
        unsigned i = 0;
        
        for (auto _ : state) {
            auto res = n_fibonacci(nums[i]);
            benchmark::DoNotOptimize(res);
            
            ++i;
            
            if (i == nums.size()) i = 0;
        }
    }
    BENCHMARK(std_function_fib);
    
    static void template_lambda_fib(benchmark::State& state) {
        auto n_fibonacci = [](const auto& self, int n, int a = 0, int b = 1) -> int {
            return n ? self(self, n - 1, a + b, a) : b;
        };
        
        unsigned i = 0;
        
        for (auto _ : state) {
            auto res = n_fibonacci(n_fibonacci, nums[i]);
            benchmark::DoNotOptimize(res);
            
            ++i;
            
            if (i == nums.size()) i = 0;
        }
    }
    BENCHMARK(template_lambda_fib);
    ```

## 参考文献

-   [cppreference-lambda](https://en.cppreference.com/w/cpp/language/lambda)
-   [Stackoverflow: Overhead with std::function](https://stackoverflow.com/a/33881130/11120338)
