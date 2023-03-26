C++ 定义了一套完善的只读量定义方法，被常量修饰符 `const` 修饰的对象或类型都是只读量，只读量的内存存储与一般变量没有任何区别，但是编译器会在编译期进行冲突检查，避免对只读量的修改。因此合理使用 `const` 修饰符可以增加代码健壮性。

## 常类型

在类型的名字前增加 const 修饰会将该类型的变量标记为不可变的。具体使用情况有常量和常引用（指针）两种。

### 常量

这里的常量即常变量，指的是 const 类型的变量（而不是标题里泛指的只读量）。常类型量在声明之后便不可重新赋值，也不可访问其可变成员，只能访问其常成员。常成员的定义见后文。

??? note "类型限定符"
    C++ 中类型限定符一共有三种：常量（const）、可变（mutable）和易变（volatile），其中默认情况下是可变变量，声明易变变量的情形是为了刻意避免编译器优化。

```cpp
const int a = 0;  // a 的类型为 const int

// a = 1; // 报错，不能修改常量
```

### 常引用、常指针

常引用和常指针也与常量类似，但区别在于他们是限制了访问，而没有更改原变量的类型。

```cpp
int a = 0;
const int b = 0;

int *p1 = &a;
*p1 = 1;
const int *p2 = &a;
// *p2 = 2; // 报错，不能通过常指针修改变量
// int *p3 = &b; // 报错，不能用普通指针指向 const 变量
const int *p4 = &b;

int &r1 = a;
r1 = 1;
const int &r2 = a;
// r2 = 2; // 报错，不能通过常引用修改变量
// int &p3 = b; // 报错，不能用普通引用指向 const 变量
const int &r4 = b;
```

另外需要区分开的是「常类型指针」和「常指针变量」（即常指针、指针常量），例如下列声明

```cpp
int* const p1;        // 类型为int的常指针，需要初始化
const int* p2;        // 类型为const int的指针
const int* const p3;  // 类型为const int的常指针

int (*f1)(int);  // 普通的函数指针
// int (const *f2)(int); // 指向常函数的指针，不可行
int (*const f3)(int) = some_func;  // 指向函数的常指针，需要初始化
int const* (*f4)(int);             // 指向返回常指针的函数指针
int const* (*const f5)(int) = some_func;  // 指向返回常指针的函数的常指针
```

我们把常类型指针又称 **底层指针**、常指针变量又称 **顶层指针**。

另外，C++ 中还提供了 `const_cast` 运算符来强行去掉或者增加引用或指针类型的 const 限定，不到万不得已的时候请不要使用这个关键字。

### 常参数

在函数参数里限定参数为常类型可以避免在函数里意外修改参数，该方法通常用于引用参数。此外，在类型参数中添加 const 修饰符还能增加代码可读性，能区分输入和输出参数。

```cpp
void sum(const std::vector<int> &data, int &total) {
  for (auto iter = data.begin(); iter != data.end(); ++iter)
    total += *iter;  // iter 是 const 迭代器，解引用后的类型是 const int
}
```

## 常成员

常成员指的是类型中被 const 修饰的成员，常成员可以用来限制对常对象的修改。其中，常成员变量与常量声明相同，而常成员函数声明方法为在成员函数声明的 **末尾**（参数列表的右括号的右边）添加 const 修饰符。

```cpp
#include <iostream>

struct ConstMember {
  const int *p;  // 常类型指针成员
  int *const q;  // 常指针变量成员
  int s;

  void func() { std::cout << "General Function" << std::endl; }

  void constFunc1() const { std::cout << "Const Function 1" << std::endl; }

  void constFunc2(int ss) const {
    // func(); // 常成员函数不能调用普通成员函数
    constFunc1();  // 常成员函数可以调用常成员函数

    // s = ss; // 常成员函数不能改变普通成员变量
    // p = &ss; // 常成员函数不能改变常成员变量
  }
};

int main() {
  const int a = 1;
  int b = 1;
  struct ConstMember c = {.p = &a, .q = &b};  // 指派初始化器是C++20中的一种语法
  // *(c.p) = 2; // 常类型指针无法改变指向的值
  c.p = &b;    // 常类型指针可以改变指针指向
  *(c.q) = 2;  // 常指针变量可以改变指向的值
  // c.q = &a; // 常指针变量无法改变指针指向
  const struct ConstMember d = c;
  // d.func(); // 常对象不能调用普通成员函数
  d.constFunc2(b);  // 常对象可以调用常成员函数
  return 0;
}
```

## 常表达式 constexpr（C++11）

constexpr 说明符的作用是声明可以在编译时求得函数或变量的值，它的行为和 C 语言中的 const 关键字是一致的，会将变量结果直接编译到栈空间中。constexpr 还可以用来替换宏定义的常量，规避 [宏定义的风险](./basic.md#define-命令)。constexpr 修饰的是变量和函数，而 const 修饰的是类型。

> 实际上把 const 理解成 **"readonly"**，而把 constexpr 理解成 **"const"** 更加直观。

```cpp
constexpr int a = 10;  // 直接定义常量

constexpr int FivePlus(int x) { return 5 + x; }

void test(const int x) {
  std::array<x> c1;            // 错误，x在编译期不可知
  std::array<FivePlus(6)> c2;  // 可行，FivePlus编译期可以推断
}
```

## 参考资料

-   [C++ 关键字——const](https://zh.cppreference.com/w/cpp/keyword/const)
-   [C++ 关键字——constexpr](https://zh.cppreference.com/w/cpp/keyword/constexpr)
