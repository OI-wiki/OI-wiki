引用可以看成是 C++ 封装的指针，用来传递它所指向的对象。在 C++ 代码中实际上会经常和引用打交道，但是通常不会显式地表现出来。引用的基本原则是在声明时必须指向对象，以及对引用的一切操作都相当于对原对象操作。另外，引用不是对象，因此不存在引用的数组、无法获取引用的指针，也不存在引用的引用。

> 尽管引用不是对象，但是可以通过 [ `reference_wrapper` ](https://zh.cppreference.com/w/cpp/utility/functional/reference_wrapper) 把它对象化，间接实现相似的效果。

引用主要分为两种，左值引用和右值引用。此外还有两种特殊的引用：转发引用和垂悬引用，不作详细介绍。另外，本文还牵涉到一部分常值的内容，请用 [常值](./const.md) 一文辅助阅读。

## 左值引用

??? note "左值和右值"
    在赋值表达式 `X = Y` 中，我们说 X 是左值，它被用到的是在内存中的 **地址** ，在编译时可知；而 Y 则是右值，它被用到的是它的 **内容** （值），内容仅在运行时可知。在 C++11 之后值的概念被进一步分类，分为泛左值、纯右值和亡值，具体参见 [相关文档](https://zh.cppreference.com/w/cpp/language/value_category) 。值得一提的是，尽管右值引用在 C++11 后才支持，但是右值概念却更早就被定义了。

??? note "左值表达式"
    如果一个表达式返回的是左值（即可以被修改），那么这个表达式被称为左值表达式。右值表达式亦然。

通常我们会接触到的引用为左值引用，它通常被用来被赋值和访问，指向右值，它的名称来源于它通常放在等号左边。左值需要 **在内存中有实体** ，而不能指向临时变量。以下是来自 [参考手册](https://zh.cppreference.com/w/cpp/language/reference) 的一段示例代码。

```cpp
#include <iostream>
#include <string>

int main() {
  std::string s = "Ex";
  std::string& r1 = s;
  const std::string& r2 = s;

  r1 += "ample";  // 修改 r1，即修改了 s
  //  r2 += "!";               // 错误：不能通过到 const 的引用修改
  std::cout << r2 << '\n';  // 打印 r2，访问了s，输出 "Example"
}
```

左值引用最常用的地方是函数参数，通过左值引用传参可以起到与通过指针传参相同的效果。

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

## 右值引用 (C++ 11)

右值引用是用来赋给其他变量的引用，指向右值，它的名称来源于它通常放在赋值号右边。右值 **可以在内存里也可以在 CPU 寄存器中** 。另外，右值引用可以被看作一种 **延长临时对象生存期的方式** 。

```cpp
#include <iostream>
#include <string>

int main() {
  std::string s1 = "Test";
  //  std::string&& r1 = s1;           // 错误：不能绑定到左值

  const std::string& r2 = s1 + s1;  // 可行：到常值的左值引用延长生存期
  //  r2 += "Test";                    // 错误：不能通过到常值的引用修改

  std::string&& r3 = s1 + s1;  // 可行：右值引用延长生存期
  r3 += "Test";  // 可行：能通过到非常值的右值引用修改
  std::cout << r3 << '\n';
}
```

在上述代码中， `r3` 是一个右值引用，引用的是右值 `s1 + s1` 。 `r2` 是一个左值引用，可以发现 **右值引用可以转为 const 修饰的左值引用** 。

## 一些例子

###  `++i` 和 `i++` 

 `++i` 和 `i++` 是典型的左值和右值。 `++i` 的实现是直接给 i 变量加一，然后返回 i 本身。因为 i 是内存中的变量，因此可以是左值。实际上前自增的函数签名是 `T& T::operator++();` 。而 `i++` 则不一样，它的实现是用临时变量存下 i，然后再对 i 加一，返回的是临时变量，因此是右值。后自增的函数签名是 `T T::operator++(int);` 。

```cpp
int n1 = 1;
int n2 = ++n1;
int n3 = ++++n1;  // 因为是左值，所以可以继续操作
int n4 = n1++;
//  int n5 = n1++ ++;   // 错误，无法操作右值
//  int n6 = n1 + ++n1; // 未定义行为
int&& n7 = n1++;  // 利用右值引用延长生命期
int n8 = n7++;    // n8 = 1
```

### 移动语义和 `std::move` (C++11)

在 C++11 之后，C++ 利用右值引用新增了移动语义的支持，用来避免对象在堆空间的复制（但是无法避免栈空间复制），STL 容器对该特性有完整支持。具体特性有 [移动构造函数](https://zh.cppreference.com/w/cpp/language/move_constructor) 、 [移动赋值](https://zh.cppreference.com/w/cpp/language/move_assignment) 和具有移动能力的函数（参数里含有右值引用）。
另外， `std::move` 函数可以用来产生右值引用，需要包含 `<utility>` 头文件。

```cpp
// 移动构造函数
std::vector<int> v{1, 2, 3, 4, 5};
std::vector<int> v2(std::move(v));  // 移动v到v2, 不发生拷贝
assert(v.empty());

// 移动赋值函数
std::vector<int> v3;
v3 = std::move(v2);
assert(v2.empty());

// 有移动能力的函数
std::string s = "def";
std::vector<std::string> numbers;
numbers.push_back(std::move(s));
```

注意上述代码仅在 C++11 之后可用。

### 函数返回引用

让函数返回引用值可以避免函数在返回时对返回值进行拷贝，如

```cpp
char &get_val(std::string &str, int index) { return str[index]; }
```

你不能返回在函数中的局部变量的引用，如果一定要在函数内的变量。请使用动态内存。例如如下两个函数都会产生悬垂引用，导致未定义行为。

```cpp
std::vector<int>& getLVector() {  // 错误：返回局部变量的左值引用
  std::vector<int> x{1};
  return x;
}
std::vector<int>&& getRVector() {  // 错误：返回局部变量的右值引用
  std::vector<int> x{1};
  return std::move(x);
}
```

当右值引用指向的空间在进入函数前已经分配时，右值引用可以避免返回值拷贝。

```cpp
struct Beta {
  Beta_ab ab;
  Beta_ab const& getAB() const& { return ab; }
  Beta_ab&& getAB() && { return std::move(ab); }
};

Beta_ab ab = Beta().getAB();  // 这里是移动语义，而非拷贝
```

## 参考内容

1.   [C++ 语言文档——引用声明](https://zh.cppreference.com/w/cpp/language/reference) 
2.   [C++ 语言文档——值类别](https://zh.cppreference.com/w/cpp/language/value_category) 
3.   [Is returning by rvalue reference more efficient?](https://stackoverflow.com/questions/1116641/is-returning-by-rvalue-reference-more-efficient) 
