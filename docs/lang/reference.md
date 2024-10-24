> 声明具名变量为引用，即既存对象或函数的别名。

引用可以看成是 C++ 封装的非空指针，可以用来传递它所指向的对象，在声明时必须指向对象。

引用不是对象，因此不存在引用的数组、无法获取引用的指针，也不存在引用的引用。

??? note "引用类型不属于对象类型"
    
    如果想让引用能完成一般的复制、赋值等操作，比如作为容器元素，则需要 [`reference_wrapper`](https://zh.cppreference.com/w/cpp/utility/functional/reference_wrapper)，通常维护一个非空指针实现。

引用主要分为两种，左值引用和右值引用。

??? note "左值和右值"
    
    对左值和右值讲解，请参考 [值类别](./value-category.md) 页面。

## 左值引用 T&

通常我们会接触到的引用为左值引用，即绑定到左值的引用，同时 `const` 限定的左值引用可以绑定右值。以下是来自 [参考手册](https://zh.cppreference.com/w/cpp/language/reference) 的一段示例代码。

```cpp
#include <iostream>
#include <string>

int main() {
  std::string s = "Ex";
  std::string& r1 = s;
  const std::string& r2 = s;

  r1 += "ample";  // 修改 r1，即修改了 s
  // r2 += "!";               // 错误：不能通过到 const 的引用修改
  std::cout << r2 << '\n';  // 打印 r2，访问了s，输出 "Example"
}
```

左值引用最常用的地方是函数参数，用于避免不需要的拷贝。

```cpp
#include <iostream>
#include <string>

// 参数中的 s 是引用，在调用函数时不会发生拷贝
char& char_number(std::string& s, std::size_t n) {
  s += s;          // 's' 与 main() 的 'str' 是同一对象
                   // 此处还说明左值也是可以放在等号右侧的
  return s.at(n);  // string::at() 返回 char 的引用
}

int main() {
  std::string str = "Test";
  char_number(str, 1) = 'a';  // 函数返回是左值，可被赋值
  std::cout << str << '\n';   // 此处输出 "TastTest"
}
```

## 右值引用 T&&（C++ 11）

右值引用是绑定到右值的引用，用于移动对象，也可以用于 **延长临时对象生存期**。

```cpp
#include <iostream>
#include <string>

using namespace std;

int main() {
  string s1 = "Test";
  // string&& r1 = s1;  错误：不能绑定到左值，需要 std::move 或者 static_cast

  const string& r2 = s1 + s1;  // 可行：到常值的左值引用延长生存期
  // r2 += "Test";                    错误：不能通过到常值的引用修改
  cout << r2 << '\n';

  string&& r3 = s1 + s1;  // 可行：右值引用延长生存期
  r3 += "Test";
  cout << r3 << '\n';

  const string& r4 = r3;  // 右值引用可以转换到 const 限定的左值
  cout << r4 << '\n';

  string& r5 = r3;  // 右值引用可以转换到左值
  cout << r5 << '\n';
}
```

## 引用相关的优化技巧

### 对 **非轻量对象** 入参使用引用消除拷贝开销

常见的 **非轻量对象** 有：

-   容器 `vector`，`array`，`map` 等
-   `string`
-   其他实现了或继承了自定义拷贝构造、移动构造等特殊函数的类型

而对 **轻量对象** 使用引用不能带来任何好处，引用类型作为参数的空间占用大小，甚至可能会比类型本身还大。

这可能会带来些的性能负担，同时可能会阻止编译器优化。

以下属于 **轻量对象**

-   基本类型 `int`，`float` 等
-   较小的 [聚合体类型](https://zh.cppreference.com/w/cpp/language/aggregate_initialization)
-   标准库容器的迭代器

### 将左值转换为右值，使用 `std::move` [转移](./value-category.md#stdmove) 对象的所有权。

这通常见于局部变量之间的，和参数与局部变量之间：

```cpp
#include <iostream>
#include <string>
#include <vector>

using namespace std;

string world(string str) { return std::move(str) += " world!"; }

int main() {
  // 1
  cout << world("hello") << '\n';

  vector<string> vec0;

  // 2
  {
    string&& size = to_string(vec0.size());

    size += ", " + to_string(size.size());

    vec0.emplace_back(std::move(size));
  }

  cout << vec0.front();
}
```

但不是所有时候都需要这么做，比如 [函数返回值优化](./value-category.md#常见误区)。

### 右值延长临时量生命期，消除可能的复制或移动。

尽管在多数情况下，编译器能通过 [复制消除](./value-category.md#复制消除) 优化掉多余的拷贝/移动，但引用能强制编译器不进行这些多余操作，避免不确定性。

## 参考内容

1.  [C++ 语言文档——引用声明](https://zh.cppreference.com/w/cpp/language/reference)
2.  [C++ 语言文档——值类别](https://zh.cppreference.com/w/cpp/language/value_category)
3.  [Does const ref lvalue to non-const func return value specifically reduce copies?](https://stackoverflow.com/questions/38909228/does-const-ref-lvalue-to-non-const-func-return-value-specifically-reduce-copies)
