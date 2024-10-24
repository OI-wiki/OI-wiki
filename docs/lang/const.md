C++ 定义了一套完整的只读量定义方法，被 `const` 修饰的变量都是只读量，编译器会在编译期进行冲突检查，避免对只读量的修改，同时可能会执行一些优化。

在通常情况下，应该尽可能使用 `const` 修饰变量、参数，提高代码健壮性。

## `const` 类型限定符

### 常量

const 修饰的变量在初始化后不可改变值

```cpp
const int a = 0;  // a 的类型为 const int

// a = 1; // 不能修改常量
```

### 常量引用、常量指针

常量引用和常量指针均限制了对指向的值的修改

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
  for (auto iter = data.begin(); iter != data.end(); ++iter)
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

编译时计算能允许更好的优化，比如将结果硬编码到汇编中，消除运行时计算开销。与 `const` 的带来的优化不同，当 `constexpr` 修饰的变量满足常量表达式的条件，就强制要求编译器在编译时计算出结果而非运行时。

???+ note " 实际上把 `const` 理解成 **"readonly"**，`constexpr` 理解成 **"const"**，这样更加直观 "
    ```cpp
    constexpr int a = 10;  // 直接定义常量
    
    constexpr int FivePlus(int x) { return 5 + x; }
    
    void test(const int x) {
      std::array<x> c1;            // 错误，x在编译时不可知
      std::array<FivePlus(6)> c2;  // 可行，FivePlus编译时可知
    }
    ```

以下例子很好说明了 `const` 和 `constexpr` 的区别，代码使用递归实现计算斐波那契数列，并用控制流输出。

???+ note "实现"
    ```cpp
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

???+ note "编译后的可能的汇编代码（使用 Compiler Explorer ，Clang 19）"
    ```assembly
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

`constexpr` 修饰的 `fib0` 函数在唯一的调用处用了常量参数，使得整个函数仅在编译期运行。由于函数没有运行时执行，编译器也就判断不需要生成汇编代码。

在同时注意到汇编中，`v0` 没有初始化代码，在调用 `cout` 输出 `v0` 的代码中，`v0` 已被最终结算结果替代，说明变量值已在编译时求出，优化掉了运行时运算。
而 `v1` 的初始化还是普通的 `fib1` 递归调用。

所以 `constexpr` 可以用来替换宏定义的常量，规避 [宏定义的风险](./basic.md#define-命令)。

算法题中可以使用 `constexpr` 存储数据规模较小的变量，以消除对应的运行时计算开销。尤为常见在「[打表](../contest/dictionary.md)」技巧中，使用 `constexpr` 修饰的数组等容器存储答案。


???+ note "编译时计算量过大会导致编译错误"
    编译器会限制编译时计算的开销，如果计算量过大会导致无法通过编译，应该考虑使用 `const` 。
    ```cpp
    #include <iostream>
    
    using namespace std;
    
    constexpr unsigned long long fib(unsigned long long i) {
      return i <= 2 ? i : fib(i - 2) + fib(i - 1);
    }
    
    int main() {
      // constexpr auto v = fib(32); evaluation exceeded maximum depth
      const auto v = fib(32);
      cout << v;
      return 0;
    }
    ```

???+ note "使用 constexpr 时 Clang 给出的编译错误"
    ```text
    <source>:10:20: error: constexpr variable 'v' must be initialized by a constant expression
        10 |     constexpr auto v = fib(32);
        |                    ^   ~~~~~~~~~~~~
    <source>:6:25: note: constexpr evaluation exceeded maximum depth of 512 calls
        6 |     return i <= 2 ? i : fib(i - 2) + fib(i - 1);
        |                         ^
    <source>:6:25: note: in call to 'fib(32)'
        6 |     return i <= 2 ? i : fib(i - 2) + fib(i - 1);
        |                         ^~~~~~~~~~
    <source>:6:25: note: in call to ...
    ```

## 参考资料

-   [C++ 关键字——const](https://zh.cppreference.com/w/cpp/keyword/const)
-   [C++ 关键字——constexpr](https://zh.cppreference.com/w/cpp/keyword/constexpr)
