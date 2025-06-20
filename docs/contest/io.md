author: Marcythm, YZircon, Chaigidel, Tiger3018, voidge, H-J-Granger, ouuan, Enter-tainer, lcfsih, Xeonacid, Ir1d

本文将介绍如何优化基于流的 I/O 与 C 风格的 I/O。

???+ note "注意"
    基于流的 I/O 与 C 风格的 I/O 的实际速度会随环境的不同（如编译器，操作系统与硬件规格）发生一定的改变。如果想要进行更进一步的分析，请以实验结果为准。但需要注意实验中的变量控制，避免因多变量影响导致结论错误。

## 基于流的 I/O

对于基于流的 I/O（如 `std::cin` 与 `std::cout`），最常用的优化方法为关闭与 C 流的同步与解除输入输出流的关联。

### 关闭同步

使用 [`std::ios::sync_with_stdio(false)`](https://en.cppreference.com/w/cpp/io/ios_base/sync_with_stdio) 函数来关闭与 C 流的同步。C++ 为了兼容 C，也就是为了保证程序在同时使用了 `printf` 和 `std::cout` 时不发生混乱，因此对这两种流进行了同步。同步的 C++ 流保证是线程安全的。

这其实是 C++ 为了兼容而采取的保守措施。若开启同步，在每一次 I/O 操作时，C++ 流会立即将此操作应用于对应的 C 缓冲区中，而如果代码中并不涉及 C 风格的 I/O，这一操作便是多余的。因此可以在进行 I/O 操作之前关闭与 C 流的同步，但是在这样做之后要注意后续代码中不能同时使用 `std::cin` 和 `scanf`，也不能同时使用 `std::cout` 和 `printf`，但是可以同时使用 `std::cin` 和 `printf`，也可以同时使用 `scanf` 和 `std::cout`。

### 解除关联

使用 [`tie()`](https://en.cppreference.com/w/cpp/io/basic_ios/tie) 函数解除输入流与输出流的关联。

在默认的情况下 `std::cin` 关联的是 `&std::cout`，因此每次进行格式化输入的时候都要调用 `std::cout.flush()` 清空输出缓冲区，这样会增加 I/O 负担。可以通过 `std::cin.tie(nullptr)` 来解除关联，进一步加快执行效率。

???+ warning "注意"
    使用时不可以省略参数写做 `std::cin.tie()`，这样不会解除关联，而是返回与 `std::cin` 关联的输出流。并且也无需进行 `std::cout.tie(nullptr)`，因为默认情况下没有另一条输出流与 `std::cout` 关联。

### 代码实现

```cpp
std::ios::sync_with_stdio(false);
std::cin.tie(nullptr);
```

???+ note "注意"
    在同时进行了上述两个操作后，程序中必须手动 `flush` 才能确保每次 `std::cout` 展现的内容可以在 `std::cin` 前出现。这是因为这种情况下调用 `std::cin` 时 `std::cout` 不会自动刷新缓冲区。例如：
    
    ```cpp
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout << "Please input your name: "
              << std::flush;  // 或者: std::endl;
                              // 因为每次调用 std::endl 都会 flush 输出缓冲区，而 \n
                              // 则不会。
    // 若去掉 std::flush，则在输入姓名之前不会显示提示信息
    std::cin >> name;
    ```

## C 风格的 I/O

`scanf` 和 `printf` 依然有效率提升的空间，提升方法均基于整数与字符串之间的转化。

???+ note "注意"
    本页面中介绍的读入和输出优化均针对整型数据。浮点数的读入与输出优化十分复杂，读入相关优化可参考 [Bellerophon 算法](https://dl.acm.org/doi/10.1145/93542.93557)，输出相关优化可参考 [Ryū 算法](https://dl.acm.org/doi/10.1145/3192366.3192369)。

### 实现设计

???+ note "注意"
    当前的优化方法着重于进行更快的 I/O，而在数据转换过程中均采用朴素方法，并未充分利用硬件特性。现如今绝大多数 x86 架构 CPU 均支持 AVX2 指令集，可以利用 SIMD 加速整数与字符串之间的转换。标准库函数并未利用 SIMD 优化，如 libstdc++ 的 [实现](https://github.com/gcc-mirror/gcc/blob/releases/gcc-14.3.0/libstdc%2B%2B-v3/include/bits/charconv.h#L81) 为一次转化连续两位，并通过查表的方式转化为字符，因此优化数据转换过程也可能会带来收益。但在竞赛范畴，本文中提到的优化方法已足够应对绝大多数场景。

#### 读入优化

每个整数由符号和数字两部分组成，并且符号一定在数字部分之前，因此首先会读入符号部分。对于符号部分，正整数的 `+` 通常是省略的，且不会对后面数字所代表的值产生影响，而 `-` 不可省略，因此要进行判定。如果输入不包含负整数，这部分的判定可以省略。对于数字部分，仅包含 0 至 9 的数字，因此在读入不应存在于整数中的字符（通常为空格）时，就可以判定此整数已经读入结束。

在读入时，由于是从左向右读入数字，恰好可以利用秦九韶算法进行整数转换。因此整个转换过程可以结合输入进行。

在读入数字部分的过程中，需要判断读入的字符是否为十进制数字字符。可简单采用 `ch >= '0' && ch <= '9'` 条件进行判断，也可利用 [`isdigit()`](https://en.cppreference.com/w/cpp/string/byte/isdigit) 函数。

#### 输出优化

输出时需要将整数转化为字符串，一般采取朴素算法，即直接从低到高计算出整数的每一位，转化为字符后逆序输出。

### 实现细节

#### 整型溢出问题

在实现中需要注意整型溢出的问题。如输出优化中不恰当地取相反数会导致整型最小值变为相反数后超出此整型能表示的最大值，这可能导致输出错误。读入整型最小值时也可能发生类似的溢出，但这种情况下可能并不会导致读入数据错误，这是由于溢出得到的值可能与实际输入的值相等。

有符号整型溢出是未定义行为，在实现时可以借助 C 语言中负整数除法计算向零取整的性质来避免上述问题。但如果无需输入输出负数，或不可能输入输出此整型的最小值，则这一问题将不会出现。

#### 提升实现的通用性

如果程序中使用了多个类型的整型变量，那么可能需要实现多个类型不同但逻辑相同的输入输出函数。此时可以使用 C++ 中的 [`template`](https://en.cppreference.com/w/cpp/language/templates.html) 实现对于所有整数类型的输入输出优化。例如在 C++11 标准下使用

```cpp
template <typename T>
typename std::enable_if<std::is_integral<T>::value &&
                        std::is_signed<T>::value>::type
read(T &x);
```

或在 C++20 标准下使用

```cpp
template <std::signed_integral T>
void read(T &x);
```

定义函数。

为了方便阅读，后文中的实现假定仅需读入 `int` 类型的整数，这些实现已足够应对大部分题目的需要。

### 实现

主流实现仅在使用的读入输出函数上有区别，在整数转换部分逻辑均相同。下面按照各实现使用的读入输出函数进行介绍。

#### 使用 `getchar` 与 `putchar` 实现

核心代码如下。

```cpp
--8<-- "docs/contest/code/io/io_2.cpp:core"
```

#### 使用 `fread` 与 `fwrite` 实现

通过 `fread` 与 `fwrite` 可以实现更快的读入输出。其函数签名如下。

```cpp
std::size_t fread(void* buffer, std::size_t size, std::size_t count,
                  std::FILE* stream);
std::size_t fwrite(const void* buffer, std::size_t size, std::size_t count,
                   std::FILE* stream);
```

如 `fread(Buf, 1, SIZE, stdin)`，表示从标准输入中读入 `SIZE` 个大小为 1 字节的数据块到 `Buf` 中。返回值表示成功读入了多少字节的数据。

由于 `fread` 与 `fwrite` 是整段读取和写入，因此速度相较 `getchar()` 与 `putchar()` 有优势。如果缓冲区足够大，可以一次性读入整个文件。但如果缓冲区不够大，则需要多次读取以确保读取输入的所有内容。为了实现这个功能，只需要重定义一下 `getchar`。

```cpp
char buf[1 << 20], *p1, *p2;
#define gc()                                                               \
  (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 20, stdin), p1 == p2) \
       ? EOF                                                               \
       : *p1++)
```

输出类似于读入，先将输出内容放入一个缓冲区中，最后通过 `fwrite` 一次性将缓冲区的内容输出即可。

核心代码如下。

```cpp
--8<-- "docs/contest/code/io/io_1.cpp:core"
```

使用此方法时需要注意：

-   关闭调试开关时使用 `fread()`，`fwrite()`，退出时自动析构执行 `fwrite()`。开启调试开关时使用 `getchar()`，`putchar()`，便于调试。
-   若要进行文件读写，需在所有读写进行之前加入 `freopen()`。

#### 使用 `mmap` 实现

`mmap` 是 Linux 系统调用，可以将文件一次性地映射到内存中，类似于可以指针引用的内存区域，在一些场景下有更优的速度。其函数签名如下：

```c
void *mmap(void addr[.length], size_t length, int prot, int flags, int fd,
           off_t offset);
```

???+ warning "注意"
    `mmap` 不能在 Windows 环境下使用（例如 CodeForces 与 HDU），同时也不建议在正式赛场上使用。实际上使用 `fread` 已经足够快了，且如果用 `mmap` 反复读取一小块文件，做一次内存映射并且内核处理缺页的开销会远比使用 `fread` 的开销大。

首先需获取文件描述符 `fd`，然后通过 `fstat` 获取文件大小，此后通过 `mmap` 获得文件映射到内存的指针 `*pc`。之后可以直接用 `*pc++` 替代 `getchar()` 进行文件读取。

如果需要从标准输入中读入时，可以将 `fd` 设为 `0`。**但是，对标准输入使用 mmap 是极其危险的行为，同时不能在终端输入，可以选择将文件重定向到标准输入。**

???+ note " 例题：[洛谷 P10815【模板】快速读入](https://www.luogu.com.cn/problem/P10815)"
    读入 $n$ 个范围在 $[-n, n]$ 的整数，求和并输出。其中 $n \leq 10^8$。数据保证对于序列的任何前缀，这个前缀的和在 $32$ 位有符号整形的存储范围内。

参考代码如下。

```cpp
--8<-- "docs/contest/code/io/io_3.cpp"
```

## 参考

[cin.tie 与 sync\_with\_stdio 加速输入输出 - 码农场](https://www.hankcs.com/program/cpp/cin-tie-with-sync_with_stdio-acceleration-input-and-output.html)

[C++ 高速化 - Heavy Watal](https://heavywatal.github.io/cxx/speed.html)

['Re: mmap/mlock performance versus read' - MARC](https://marc.info/?l=linux-kernel&m=95496636207616&w=2)
