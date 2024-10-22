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

> 另请参阅 [新版 C++ 特性：constexpr](new.md#constexpr)

`constexpr` 要求编译器能在编译时求得函数或变量的值，语义和 C 语言中的 `const` 类似。

但编译时计算能允许更好的优化，将结果硬编码到汇编中，消除运行时计算开销。

[示例代码](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGe1wAyeAyYAHI%2BAEaYxCDSAA6oCoRODB7evnoJSY4CQSHhLFEx0naYDilCBEzEBGk%2Bfly2mPY5DJXVBHlhkdGxtlU1dRmNCgOdwd2FvZIAlLaoXsTI7BzmAMzByN5YANQma25Oo8SYrPvYJhoAgpdXXklGO8xsCnFMyzuj6PtW17doDFGmFUcWIOy8gLwwBC6B2NAiGggEKS0MwsIYMz2AHZflcdvidicCIsGE89gd9gARHZcckAMRpOxAO2oeAREFJAFoaZjrHC2YiuTszDMZj9biYsZSJddkVCYfyIlwkZDUejeTjCZhicRSaT9m4qYz9gzaczWUqOTtuVxeZZFcqhSKxWsLNjpX9rsECDsWExghANbiCTsAUCQWCmF4iDsAG4acnU%2BGIgCcLuDBLDPqjMdjtKN8OVafFnrxmYWPoNBrjGhLZfxaGj5MNBx2YA4bdWrtuIcblYprbzdcllI4c1onAArLw/NxeKhOIbLHyFAslpg9mY1jxSARNGO5gBrWKTgB0XAAHCnJxpJGssdusViL9IJxxJLwWBINBpSLOtKQC4cLwCggL%2Be4cFocxwLAMCICgqAsHEdDROQlBoEhKExFshjAAA%2BgQxAQoefB0AQ0SgRAET7qQETBNUACenA7nRzDEAxADyETaGUEE7hhbCCBxDC0ExkG8FgEReMAbhiLQoFzqQWB%2BkY4jiUpeAnOUsaYApAHAmU0YrAB3rNDRtBssQjEeFgNGEXgX6KTpxARIkmCUpgKnABZRj7nMVAGMACgAGp4JgADuHFxIwzG8PwggiGI7BSDIgiKCo6jqbojQGL5pjLpY%2BhsqBkBzKgcStApnJfFS%2BVWJYW7WhxazWl8FkRFS7V1dY87OcQeBYCVgZNC0KQuAw7iePU/gTV0BRFJkiTJAIQwNKQWTLQwc09DEIzNLxFRjKteilOUAjtDU21TLt/QdMdIxjFdC22vMizLBI45TjONFATsqgXgAbJyAOSKGuXACyhHEZiEC4IQJCbtuMy8BBUGkBASAYch9BkBQEBY1hICxsgcRxHheYpnhBjkaMeGqCDpG0ORxCUdR6msYxsW0fR7FcTxDhcwJjAEMJok0ZJ0mybQ8lc8puFqQB%2BBaY4Ol6bwBnIEZNGmW%2BAHtVZ7E2cZKP9Y5O7Oa5SgeV5PmgOJ/mBSFYWRdFs47vFwiiOIKUe%2Blag0boaz6LhKDWNYRURENZUVSkCkAPRfKHBUWGYCZxwA6qDGcABq9dE/WDfAcyna042Teka2BBM829I0G2tPd61La0T21yNB3nUdU3DO3Z1tI91c7SdXcV8PHSt7txdru9L1vtOf4/Zwf0g76CjE3GXApqe1O6T6sP4EQYLrLaKN%2BUesQaKek6TlwANYgDk4plikgaCmOWcB%2BpBfgDZinhek5YikGYf%2BgDJDAMnNIf885OAgTAruPy6M4IYxABWOI0Y0L40QtjaIoRWArH%2BkDFeOFHgQChgwQ8yNSBonhgXPQHtEre2kL7JQ/ssp6HClZOICC57fXUkBDi0Y0E%2BlQFQP6gNgag2IRDUhRFyEww8JhHGiMT7wPtujJAqD0F4wJjjXBbBOD01BiwNeyAN5bx3qMdWB8SADTobIBhyUmGyD9plACgdSAcKYFwucn0ODzygYBTgAiCBCJ2CI5eRiTFmO3kwGme8FHYKPluNYlDUYHlIAgU4WAYjDTfJ/L895zxgJAUAkpkgAYLz4TA2wcC0milIMeCBf8uC3mvD/AGF4zBmC4FifQnA1i8IAkBU%2B9tfFmEGdA4CqioJzGckkZwkggA%3D%3D%3D)
```
#include <iostream>

using namespace std;

constexpr unsigned fib0(unsigned n) {
    return n <= 1 ? 1 : (fib0(n - 1) + fib0(n - 2));
}

unsigned fib1(unsigned n) { return n <= 1 ? 1 : (fib1(n - 1) + fib1(n - 2)); }

int main() {
    constexpr auto v0 = fib0(9);
    const auto v1 = fib1(9);

    cout << v0;
    cout << ' ';
    cout << v1;
}
```

汇编
```
fib1(unsigned int):
        push    r14
        push    rbx
        push    rax
        mov     ebx, 1
        cmp     edi, 2
        jb      .LBB0_4
        mov     r14d, edi
        xor     ebx, ebx
.LBB0_2:
        lea     edi, [r14 - 1]
        call    fib1(unsigned int)
        add     r14d, -2
        add     ebx, eax
        cmp     r14d, 1
        ja      .LBB0_2
        inc     ebx
.LBB0_4:
        mov     eax, ebx
        add     rsp, 8
        pop     rbx
        pop     r14
        ret

main:
        push    r14
        push    rbx
        push    rax
        mov     edi, 9
        call    fib1(unsigned int) # `v1` 的初始化进行了函数调用
        mov     ebx, eax
        mov     r14, qword ptr [rip + std::__1::cout@GOTPCREL]
        mov     rdi, r14
        mov     esi, 55 # `v0` 被最终计算结果替代
        call    std::__1::basic_ostream<char, std::__1::char_traits<char>>::operator<<(unsigned int)@PLT
        mov     byte ptr [rsp + 7], 32
        lea     rsi, [rsp + 7]
        mov     edx, 1
        mov     rdi, r14
        call    std::__1::basic_ostream<char, std::__1::char_traits<char>>& std::__1::__put_character_sequence[abi:ne200000]<char, std::__1::char_traits<char>>(std::__1::basic_ostream<char, std::__1::char_traits<char>>&, char const*, unsigned long)
        mov     rdi, r14
        mov     esi, ebx # 读取了变量值
        call    std::__1::basic_ostream<char, std::__1::char_traits<char>>::operator<<(unsigned int)@PLT
        xor     eax, eax
        add     rsp, 8
        pop     rbx
        pop     r14
        ret
```

上述代码使用递归实现计算斐波那契数列，并用控制流输出。

`constexpr` 修饰的 `fib0` 函数在唯一的调用处用了常量参数，使得整个函数仅在编译期运行。由于函数没有运行时执行，编译器也就判断不需要生成汇编代码。

在同时注意到汇编中，`v0` 没有初始化代码 ，在调用 `cout` 输出 `v0` 的代码中， `v0` 已被最终结算结果替代，说明变量值已在编译时求出，优化掉了运行时运算。

而 `v1` 的初始化还是普通的 `fib1` 递归调用。

所以 `constexpr` 可以用来替换宏定义的常量，规避 [宏定义的风险](./basic.md#define-命令)。

算法题中可以使用 `constexpr` 存储数据规模较小的变量，以消除对应的运行时计算开销。

在[“打表”](https://baike.baidu.com/item/%E6%89%93%E8%A1%A8/7928573)技巧中，常见为使用 `constexpr` 修饰的数组等容器变量存储答案。

???+ note
    实际上把 `const` 理解成 **"readonly"**，而把 constexpr 理解成 **"const"** 更加直观。

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
