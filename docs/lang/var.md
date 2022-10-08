## 数据类型

C++ 内置了六种基本数据类型：

| 类型     | 关键字      |
| ------ | -------- |
| 布尔型    | `bool`   |
| 字符型    | `char`   |
| 整型     | `int`    |
| 单精度浮点型 | `float`  |
| 双精度浮点型 | `double` |
| 无类型    | `void`   |

### 布尔类型

一个 `bool` 类型的变量取值只可能为两种：`true` 和 `false`。

一般情况下，一个 `bool` 类型变量占有 $1$ 字节（一般情况下，$1$ 字节 =$8$ 位）的空间。

### 字符型

`signed char`、`unsigned char`、`char` 这三种类型的变量用于存放字符（实际上存储的仍然是整数，一般通过 [ASCII 编码](http://www.asciitable.com/) 实现字符与整数的一一对应），位数一般为 $8$ 位。

- `signed char`：有符号字符表示的类型，表示范围在 $-128 \sim 127$ 之间。
- `unsigned char`：无符号字符表示的类型，表示范围在 $0 \sim 255$ 之间。
-   `char` 拥有与 `signed char` 或 `unsigned char` 之一相同的表示和对齐，但始终是独立的类型。

    `char` 的符号性取决于编译器和目标平台：ARM 和 PowerPC 的默认设置通常没有符号，而 x86 与 x64 的默认设置通常有符号。

    GCC 可以在编译参数中添加 `-fsigned-char` 或 `-funsigned-char` 指定将 `char` 视作 `signed char` 或 `unsigned char`，其他编译器请参照文档。需要注意指定与架构默认值不同的符号有可能会破坏 ABI，造成程序无法正常工作。

???+warning "注意"
    与其他整型不同，`char`、`signed char`、`unsigned char` 是三种不同的类型。

### 整型

int 类型的变量用于存储整数。

???+note "`int` 类型的大小"
    在 C++ 标准中，规定 `int` 的位数 **至少** 为 $16$ 位。
    
    事实上在现在的绝大多数平台，`int` 的位数均为 $32$ 位。

对于 `int` 关键字，可以使用如下修饰关键字进行修饰：

符号性：

- `signed`：表示带符号整数（默认）；
- `unsigned`：表示无符号整数。

大小：

- `short`：表示 **至少**  $16$ 位整数；
- `long`：表示 **至少**  $32$ 位整数；
- `long long`：表示 **至少**  $64$ 位整数。

下表给出在 **一般情况下**，各整数类型的位宽和表示范围大小（少数平台上一些类型的表示范围可能与下表不同）：

| 类型名                      | 位宽   | 表示范围                   |
| ------------------------ | ---- | ---------------------- |
| `short int`              | $16$ | $-2^{15}\sim 2^{15}-1$ |
| `unsigned short int`     | $16$ | $0 \sim 2^{16}-1$      |
| `int`                    | $32$ | $-2^{31}\sim 2^{31}-1$ |
| `unsigned int`           | $32$ | $0 \sim 2^{32}-1$      |
| `long int`               | $32$ | $-2^{31}\sim 2^{31}-1$ |
| `unsigned long int`      | $32$ | $0 \sim 2^{32}-1$      |
| `long long int`          | $64$ | $-2^{63}\sim 2^{63}-1$ |
| `unsigned long long int` | $64$ | $0 \sim 2^{64}-1$      |

???+note "等价的类型表述"
    在不引发歧义的情况下，允许省略部分修饰关键字，或调整修饰关键字的顺序。这意味着同一类型会存在多种等价表述。
    
    例如 `int`，`signed`，`int signed`，`signed int` 表示同一类型，而 `unsigned long` 和 `unsigned long int` 表示同一类型。

### 浮点型

包括以下三种：

- `float`：单精度浮点类型。如果支持就会匹配 IEEE-754 binary32 格式。
- `double`：双精度浮点类型。如果支持就会匹配 IEEE-754 binary64 格式。
- `long double`：扩展精度浮点类型。如果支持就会匹配 IEEE-754 binary128 格式，否则如果支持就会匹配 IEEE-754 binary64 扩展格式，否则匹配某种精度优于 binary64 而值域至少和 binary64 一样好的非 IEEE-754 扩展浮点格式，否则匹配 IEEE-754 binary64 格式。

| 浮点格式                   | 位宽        | 最大正数                       | 精度位数             |
| ---------------------- | --------- | -------------------------- | ---------------- |
| IEEE-754 binary32 格式   | $32$      | $3.4\times 10^{38}$        | $6\sim 9$        |
| IEEE-754 binary64 格式   | $64$      | $1.8\times 10^{308}$       | $15\sim 17$      |
| IEEE-754 binary64 扩展格式 | $\geq 80$ | $\geq 1.2\times 10^{4932}$ | $\geq 18\sim 21$ |
| IEEE-754 binary128 格式  | $128$     | $1.2\times 10^{4932}$      | $33\sim 36$      |

> IEEE-754 浮点格式的最小负数是最大正数的相反数。

因为 `float` 类型表示范围较小，且精度不高，实际应用中常使用 `double` 类型（双精度浮点型）表示浮点数。

### 无类型

`void` 类型为无类型，与上面几种类型不同的是，不能将一个变量声明为 `void` 类型。但是函数的返回值允许为 `void` 类型，表示该函数无返回值。

## 类型转换

在一些时候（比如某个函数接受 `int` 类型的参数，但传入了 `double` 类型的变量），我们需要将某种类型，转换成另外一种类型。

C++ 中类型的转换机制较为复杂，这里主要介绍对于基础数据类型的两种转换：数值提升和数值转换。

### 数值提升

数值提升过程中，值本身保持不变。

数值提升遵循如下规则：

???+ note
    C 风格的可变参数域在传值过程中会进行默认参数提升。如：
    
    ???+ mdui-shadow-6 "测试代码"
        ```c
        #include <stdarg.h>
        #include <stdio.h>
        
        void test(int tot, ...) {
          va_list valist;
          int i;
        
          // 初始化可变参数列表
          va_start(valist, tot);
        
          for (i = 0; i < tot; ++i) {
            // 获取第 i 个变量的值
            double xx = va_arg(valist, double);  // Correct
            // float xx = va_arg(valist, float); // Wrong
        
            // 输出第 i 个变量的底层存储内容
            printf("i = %d, value = 0x%016llx\n", i, *(long long *)(&xx));
          }
        
          // 清理可变参数列表的内存
          va_end(valist);
        }
        
        int main() {
          float f;
          double fd, d;
          f = 123.;   // 0x42f60000
          fd = 123.;  // 0x405ec00000000000
          d = 456.;   // 0x407c800000000000
          test(3, f, fd, d);
        }
        ```
    
    在调用 `test` 时，`f` 提升为 `double`，从而底层存储内容和 `fd` 相同，输出为
    
    ```text
    i = 0, value = 0x405ec00000000000
    i = 1, value = 0x405ec00000000000
    i = 2, value = 0x407c800000000000
    ```
    
    若将 `double xx = va_arg(valist, double);` 改为 `float xx = va_arg(valist, float);`，GCC 应该给出一条类似下文的警告：
    
    ```text
    In file included from test.c:2:
    test.c: In function ‘test’:
    test.c:14:35: warning: ‘float’ is promoted to ‘double’ when passed through ‘...’
      14 |         float xx = va_arg(valist, float);
         |                                   ^
    test.c:14:35: note: (so you should pass ‘double’ not ‘float’ to ‘va_arg’)
    test.c:14:35: note: if this code is reached, the program will abort
    ```
    
    此时的程序将会在输出前终止。
    
    这一点也能解释为什么 `printf` 的 `%f` 既能匹配 `float` 也能匹配 `double`。

#### 整数提升

小整数类型（如 `char`）的纯右值可转换成较大整数类型（如 `int`）的纯右值。

具体而言，算术运算符不接受小于 `int` 的类型作为它的实参，而在左值到右值转换后，如果适用就会自动实施整数提升。

具体地，有如下规则：

- 源类型为 `signed char`、`signed short / short` 时，可提升为 `int`。
- 源类型为 `unsigned char`、`unsigned short` 时，若 `int` 能保有源类型的值范围，则可提升为 `int`，否则可提升为 `unsigned int`。（`C++20` 起 `char8_t` 也适用本规则）
- `char` 的提升规则取决于其底层类型是 `signed char` 还是 `unsigned char`。
- `bool` 类型可转换到 `int`：`false` 变为 `0`，`true` 变为 `1`。
- 若目标类型的值范围包含源类型，且源类型的值范围不能被 `int` 和 `unsigned int` 包含，则源类型可提升为目标类型。[^note4]

???+warning "注意"
    `char`->`short` 不是数值提升，因为 `char` 要优先提升为 `int / unsigned int`，之后是 `int / unsigned int`->`short`，不满足数值提升的条件。

如（以下假定 `int` 为 32 位，`unsigned short` 为 16 位，`signed char` 和 `unsigned char` 为 8 位，`bool` 为 1 位）

- `(signed char)'\0' - (signed char)'\xff'` 会先将 `(signed char)'\0'` 提升为 `(int)0`、将 `(signed char)'\xff'` 提升为 `(int)-1`, 再进行 `int` 间的运算，最终结果为 `(int)1`。
- `(unsigned char)'\0' - (unsigned char)'\xff'` 会先将 `(unsigned char)'\0'` 提升为 `(int)0`、将 `(unsigned char)'\xff'` 提升为 `(int)255`, 再进行 `int` 间的运算，最终结果为 `(int)-255`。
- `false - (unsigned short)12` 会先将 `false` 提升为 `(int)0`、将 `(unsigned short)12` 提升为 `(int)12`, 再进行 `int` 间的运算，最终结果为 `(int)-12`。

#### 浮点提升

位宽较小的浮点数可以提升为位宽较大的浮点数（例如 `float` 类型的变量和 `double` 类型的变量进行算术运算时，会将 `float` 类型变量提升为 `double` 类型变量），其值不变。

### 数值转换

数值转换过程中，值可能会发生改变。

???+note "注意"
    数值提升优先于数值转换。如 `bool`->`int` 时是数值提升而非数值转换。

#### 整数转换

-   如果目标类型为位宽为 $x$ 的无符号整数类型，则转换结果是原值 $\bmod 2^x$ 后的结果。

    -   若目标类型位宽大于源类型位宽：

        -   若源类型为有符号类型，一般情况下需先进行符号位扩展再转换。

            如

            - 将 `(short)-1`（`(short)0b1111'1111'1111'1111`）转换为 `unsigned int` 类型时，先进行符号位扩展，得到 `0b1111'1111'1111'1111'1111'1111'1111'1111`，再进行整数转换，结果为 `(unsigned int)4'294'967'295`（`(unsigned int)0b1111'1111'1111'1111'1111'1111'1111'1111`）。
            - 将 `(short)32'767`（`(short)0b0111'1111'1111'1111`）转换为 `unsigned int` 类型时，先进行符号位扩展，得到 `0b0000'0000'0000'0000'0111'1111'1111'1111`，再进行整数转换，结果为 `(unsigned int)32'767`（`(unsigned int)0b0000'0000'0000'0000'0111'1111'1111'1111`）。

        -   若源类型为无符号类型，则需先进行零扩展再转换。

            如将 `(unsigned short)65'535`（`(unsigned short)0b1111'1111'1111'1111`）转换为 `unsigned int` 类型时，先进行零扩展，得到 `0b0000'0000'0000'0000'1111'1111'1111'1111`，再进行整数转换，结果为 `(unsigned int)65'535`（`(unsigned int)0b0000'0000'0000'0000'1111'1111'1111'1111`）。

    -   若目标类型位宽不大于源类型位宽，则需先截断再转换。

        如将 `(unsigned int)4'294'967'295`（`(unsigned int)0b1111'1111'1111'1111'1111'1111'1111'1111`）转换为 `unsigned short` 类型时，先进行截断，得到 `0b1111'1111'1111'1111`，再进行整数转换，结果为 `(unsigned short)65'535`（`(unsigned short)0b1111'1111'1111'1111`）。

-   如果目标类型为位宽为 $x$ 的带符号整数类型，则 **一般情况下**，转换结果可以认为是原值 $\bmod 2^x$ 后的结果。[^note1]

    例如将 `(unsigned int)4'294'967'295`（`(unsigned int)0b1111'1111'1111'1111'1111'1111'1111'1111`）转换为 `short` 类型时，结果为 `(short)-1`（`(short)0b1111'1111'1111'1111`）。

- 如果目标类型是 `bool`，则是 [布尔转换](#布尔转换)。

- 如果源类型是 `bool`，则 `false` 转为对应类型的 0，`true` 转为对应类型的 1。

#### 浮点转换

位宽较大的浮点数转换为位宽较小的浮点数，会将该数舍入到目标类型下最接近的值。

#### 浮点整数转换

-   浮点数转换为整数时，会舍弃浮点数的全部小数部分。

    如果目标类型是 `bool`，则是 [布尔转换](#布尔转换)。

-   整数转换为浮点数时，会舍入到目标类型下最接近的值。

    如果该值不能适应到目标类型中，那么行为未定义。

    如果源类型是 `bool`，那么 `false` 转换为零，而 `true` 转换为一。

#### 布尔转换

将其他类型转换为 `bool` 类型时，零值转换为 `false`，非零值转换为 `true`。

## 定义变量

简单地说[^note2]，定义一个变量，需要包含类型说明符（指明变量的类型），以及要定义的变量名。

例如，下面这几条语句都是变量定义语句。

```c++
int oi;
double wiki;
char org = 'c';
```

在目前我们所接触到的程序段中，定义在花括号包裹的地方的变量是局部变量，而定义在没有花括号包裹的地方的变量是全局变量。实际有例外，但是现在不必了解。

定义时没有初始化值的全局变量会被初始化为 $0$。而局部变量没有这种特性，需要手动赋初始值，否则可能引起难以发现的 bug。

## 变量作用域

作用域是变量可以发挥作用的代码块。

全局变量的作用域，自其定义之处开始[^note3]，至文件结束位置为止。

局部变量的作用域，自其定义之处开始，至代码块结束位置为止。

由一对大括号括起来的若干语句构成一个代码块。

```c++
int g = 20;  // 定义全局变量

int main() {
  int g = 10;         // 定义局部变量
  printf("%d\n", g);  // 输出 g
  return 0;
}
```

如果一个代码块的内嵌块中定义了相同变量名的变量，则内层块中将无法访问外层块中相同变量名的变量。

例如上面的代码中，输出的 $g$ 的值将是 $10$。因此为了防止出现意料之外的错误，请尽量避免局部变量与全局变量重名的情况。

## 常量

常量是固定值，在程序执行期间不会改变。

常量的值在定义后不能被修改。定义时加一个 `const` 关键字即可。

```c++
const int a = 2;
a = 3;
```

如果修改了常量的值，在编译环节就会报错：`error: assignment of read-only variable‘a’`。

## 参考资料与注释

1. [基础类型 - cppreference.com](https://zh.cppreference.com/w/cpp/language/types)
2. William Kahan (1 October 1997).["Lecture Notes on the Status of IEEE Standard 754 for Binary Floating-Point Arithmetic"](https://people.eecs.berkeley.edu/~wkahan/ieee754status/IEEE754.PDF).
3. [隐式转换 - cppreference.com](https://zh.cppreference.com/w/cpp/language/implicit_conversion)
4. [声明 - cppreference](https://zh.cppreference.com/w/cpp/language/declarations)
5. [作用域 - cppreference.com](https://zh.cppreference.com/w/cpp/language/scope)

[^note1]: 自 C++20 起生效。C++20 前结果是实现定义的。详见 [整型转换 - cppreference](https://zh.cppreference.com/w/cpp/language/implicit_conversion#.E6.95.B4.E5.9E.8B.E8.BD.AC.E6.8D.A2)。

[^note2]: 定义一个变量时，除了类型说明符之外，还可以包含其他说明符。详见 [声明 - cppreference](https://zh.cppreference.com/w/cpp/language/declarations)。

[^note3]: 更准确的说法是 [声明点](https://zh.cppreference.com/w/cpp/language/scope#.E5.A3.B0.E6.98.8E.E7.82.B9)。

[^note4]: 不包含宽字符类型、位域和枚举类型，详见 [整型转换 - cppreference](https://zh.cppreference.com/w/cpp/language/implicit_conversion#.E6.95.B4.E5.9E.8B.E8.BD.AC.E6.8D.A2)。
