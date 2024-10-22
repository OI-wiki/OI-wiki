C++ 定义了一套完善的只读量定义方法，被 `const` 修饰的变量都是只读量，编译器会在编译期进行冲突检查，避免对只读量的修改，同时可能会执行一些优化。

在通常情况下，应该尽可能使用 `const` 修饰变量、参数，提高代码健壮性。

## 常量

### 常量变量

const 类型的变量在初始化后不可改变值

```cpp
const int a = 0;  // a 的类型为 const int

// a = 1; // 不能修改常量
```

### 常量引用、常量指针

常量引用和常量指针均限制了对值的修改

```cpp
int a = 0;
const int b = 0;

int *p1 = &a;
*p1 = 1;
const int *p2 = &a;
// *p2 = 2; // 不能通过常量指针修改变量
// int *p3 = &b; // 不能用 int* 指向 const int 变量
const int *p4 = &b;

int &r1 = a;
r1 = 1;
const int &r2 = a;
// r2 = 2; // 不能通过常量引用修改变量
// int &p3 = b; // 不能用 int& 引用 const int变量
const int &r4 = b;
```

另外需要区分开的是常量指针（`const t*`）和指针常量（`t* const`)，例如下列声明

```cpp
int* const p1;  // 指针常量，初始化后指向地址不可改，可更改指向的值
const int* p2;  // 常量指针，解引用的值不可改，可指向其他 int 变量
const int* const p3;  // 常量指针常量，值不可改，指向地址不可改

// 使用别名能更好提高可读性
using const_int = const int;
using ptr_to_const_int = const_int*;
using const_ptr_to_const_int = const ptr_to_const_int;
```

在函数参数里使用 `const` 限定参数类型，可以避免变量被错误地修改，同时增加代码可读性

```cpp
void sum(const std::vector<int> &data, int &total) {
  const auto end = data.end();
  for (auto iter = data.begin(); iter != end;
       ++iter)       // 避免了结尾写成 ++end 的可能性
    total += *iter;  // iter 是迭代器，解引用后的类型是 const int
}
```

## `const` 成员函数

类型中 `const` 限定的成员函数，可以用来限制对成员的修改。

```cpp
#include <iostream>

struct ConstMember {
  int s = 0;

  void func() { std::cout << "General Function" << std::endl; }

  void constFunc1() const { std::cout << "Const Function 1" << std::endl; }

  void constFunc2(int ss) const {
    // func(); // const 成员函数不能调用非 const 成员函数
    constFunc1();

    // s = ss; // const 成员函数不能修改成员变量
  }
};

int main() {
  int b = 1;
  ConstMember c{};
  const ConstMember d = c;
  // d.func(); // 常量不能调用非 const 成员函数
  d.constFunc2(b);
  return 0;
}
```

## 常量表达式 constexpr（C++11）

常量表达式是指编译时能计算出结果的表达式，`constexpr` 则要求编译器能在编译时求得函数或变量的值。

编译时计算能允许更好的优化，比如将结果硬编码到汇编中，消除运行时计算开销。

[示例代码](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGe1wAyeAyYAHI%2BAEaYxCDSAA6oCoRODB7evnoJSY4CQSHhLFEx0naYDilCBEzEBGk%2Bfly2mPY5DJXVBHlhkdGxtlU1dRmNCgOdwd2FvZIAlLaoXsTI7BzmAMzByN5YANQma25Oo8SYrPvYJhoAgpdXXklGO8xsCnFMyzuj6PtW17doDFGmFUcWIOy8gLwwBC6B2NAiGggEKS0MwsIYMz2AHZflcdvidicCIsGE89gd9gARHZcckAMRpOxAO2oeAREFJAFoaZjrHC2YiuTszDMZj9biYsZSJddkVCYfyIlwkZDUejeTjCZhicRSaT9m4qYz9gzaczWUqOTtuVxeZZFcqhSKxWsLNjpX9rsECDsWExghANbiCTsAUCQWCmF4iDsAG4acnU%2BGIgCcLuDBLDPqjMdjtKN8OVafFnrxmYWPoNBrjGhLZfxaGj5MNBx2YA4bdWrtuIcblYprbzdcllI4c1onAArLw/NxeKhOIbLHyFAslpg9mY1jxSARNGO5gBrWKTgB0XAAHCnJxpJGssdusViL9IJxxJLwWBINBpSLOtKQC4cLwCggL%2Be4cFocxwLAMCICgqAsHEdDROQlBoEhKExFshjAAA%2BgQxAQoefB0AQ0SgRAET7qQETBNUACenA7nRzDEAxADyETaGUEE7hhbCCBxDC0ExkG8FgEReMAbhiLQoFzqQWB%2BkY4jiUpeAnOUsaYApAHAmU0YrAB3rNDRtBssQjEeFgNGEXgX6KTpxARIkmCUpgKnABZRj7nMVAGMACgAGp4JgADuHFxIwzG8PwggiGI7BSDIgiKCo6jqbojQGL5pjLpY%2BhsqBkBzKgcStApnJfFS%2BVWJYW7WhxazWl8FkRFS7V1dY87OcQeBYCVgZNC0KQuAw7iePU/gTV0BRFJkiTJAIQwNKQWTLQwc09DEIzNLxFRjKteilOUAjtDU21TLt/QdMdIxjFdC22vMizLBI45TjONFATsqgXgAbJyAOSKGuXACyhHEZiEC4IQJCbtuMy8BBUGkBASAYch9BkBQEBY1hICxsgcRxHheYpnhBjkaMeGqCDpG0ORxCUdR6msYxsW0fR7FcTxDhcwJjAEMJok0ZJ0mybQ8lc8puFqQB%2BBaY4Ol6bwBnIEZNGmW%2BAHtVZ7E2cZKP9Y5O7Oa5SgeV5PmgOJ/mBSFYWRdFs47vFwiiOIKUe%2Blag0boaz6LhKDWNYRURENZUVSkCkAPRfKHBUWGYCZxwA6qDGcABq9dE/WDfAcyna042Teka2BBM829I0G2tPd61La0T21yNB3nUdU3DO3Z1tI91c7SdXcV8PHSt7txdru9L1vtOf4/Zwf0g76CjE3GXApqe1O6T6sP4EQYLrLaKN%2BUesQaKek6TlwANYgDk4plikgaCmOWcB%2BpBfgDZinhek5YikGYf%2BgDJDAMnNIf885OAgTAruPy6M4IYxABWOI0Y0L40QtjaIoRWArH%2BkDFeOFHgQChgwQ8yNSBonhgXPQHtEre2kL7JQ/ssp6HClZOICC57fXUkBDi0Y0E%2BlQFQP6gNgag2IRDUhRFyEww8JhHGiMT7wPtujJAqD0F4wJjjXBbBOD01BiwNeyAN5bx3qMdWB8SADTobIBhyUmGyD9plACgdSAcKYFwucn0ODzygYBTgAiCBCJ2CI5eRiTFmO3kwGme8FHYKPluNYlDUYHlIAgU4WAYjDTfJ/L895zxgJAUAkpkgAYLz4TA2wcC0milIMeCBf8uC3mvD/AGF4zBmC4FifQnA1i8IAkBU%2B9tfFmEGdA4CqioJzGckkZwkggA%3D%3D%3D)

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

汇编

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

上述代码使用递归实现计算斐波那契数列，并用控制流输出。

`constexpr` 修饰的 `fib0` 函数在唯一的调用处用了常量参数，使得整个函数仅在编译期运行。由于函数没有运行时执行，编译器也就判断不需要生成汇编代码。

在同时注意到汇编中，`v0` 没有初始化代码，在调用 `cout` 输出 `v0` 的代码中，`v0` 已被最终结算结果替代，说明变量值已在编译时求出，优化掉了运行时运算。
而 `v1` 的初始化还是普通的 `fib1` 递归调用。

所以 `constexpr` 可以用来替换宏定义的常量，规避 [宏定义的风险](./basic.md#define-命令)。

算法题中可以使用 `constexpr` 存储数据规模较小的变量，以消除对应的运行时计算开销。尤为常见在 [“打表”](https://baike.baidu.com/item/%E6%89%93%E8%A1%A8/7928573) 技巧中，使用 `constexpr` 修饰的数组等容器变量存储答案。

???+ note
    实际上把 `const` 理解成 **"readonly"**，而把 constexpr 理解成 **"const"** 更加直观。

```cpp
constexpr int a = 10;  // 直接定义常量

constexpr int FivePlus(int x) { return 5 + x; }

void test(const int x) {
  std::array<x> c1;            // 错误，x在编译时不可知
  std::array<FivePlus(6)> c2;  // 可行，FivePlus编译时可知
}
```

## 参考资料

-   [C++ 关键字——const](https://zh.cppreference.com/w/cpp/keyword/const)
-   [C++ 关键字——constexpr](https://zh.cppreference.com/w/cpp/keyword/constexpr)
