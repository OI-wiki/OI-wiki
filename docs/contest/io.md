author: Marcythm, YZircon, Chaigidel, Tiger3018, voidge, H-J-Granger, ouuan, Enter-tainer, lcfsih, Xeonacid, Ir1d

在默认情况下，`std::cin/std::cout` 是极为迟缓的读入/输出方式，而 `scanf/printf` 比 `std::cin/std::cout` 快得多。

???+ note "注意"
    `cin`/`cout` 与 `scanf`/`printf` 的实际速度差会随编译器和操作系统的不同发生一定的改变。如果想要进行详细对比，请以实际测试结果为准。

下文将详细介绍读入输出的优化方法。

## 关闭同步/解除绑定

### `std::ios::sync_with_stdio(false)`

这个函数是一个「是否兼容 stdio」的开关，C++ 为了兼容 C，保证程序在使用了 `printf` 和 `std::cout` 的时候不发生混乱，将输出流绑到了一起。同步的输出流是线程安全的。

这其实是 C++ 为了兼容而采取的保守措施，也是使 `cin`/`cout` 速度较慢的主要原因。我们可以在进行 IO 操作之前将 stdio 解除绑定，但是在这样做之后要注意不能同时使用 `std::cin` 和 `scanf`，也不能同时使用 `std::cout` 和 `printf`，但是可以同时使用 `std::cin` 和 `printf`，也可以同时使用 `scanf` 和 `std::cout`。

### `tie`

tie 是将两个 stream 绑定的函数，空参数的话返回当前的输出流指针。

在默认的情况下 `std::cin.tie()` 绑定的是 `&std::cout`，每次进行格式化输入的时候都要调用 `std::cout.flush()` 清空输出缓冲区，这样会增加 IO 负担。可以通过 `std::cin.tie(nullptr)` 来解除绑定，进一步加快执行效率。

但需要注意的是，在解除了 `std::cin` 和 `std::cout` 的绑定后，程序中必须手动 `flush` 才能确保每次 `std::cout` 展现的内容可以在 `std::cin` 前出现。这是因为 `std::cout` 被 buffer 为默认设置。例如：

```cpp
std::cout << "Please input your name: "
          << std::flush;  // 或者: std::endl;
                          // 因为每次调用 std::endl 都会 flush 输出缓冲区，而 \n
                          // 则不会。
// 但请谨慎使用，过多的 flush 会影响程序效率
std::cin >> name;
```

### 代码实现

```cpp
std::ios::sync_with_stdio(false);
std::cin.tie(nullptr);
```

## 读入优化

`scanf` 和 `printf` 依然有优化的空间，这就是本章所介绍的内容——读入和输出优化。

-   注意，本页面中介绍的读入和输出优化均针对整型数据，若要支持其他类型的数据（如浮点数），可自行按照本页面介绍的优化原理来编写代码。

### 原理

众所周知，`getchar` 是用来读入 1 byte 的数据并将其转换为 `char` 类型的函数，且速度很快，故可以用「读入字符——转换为整型」来代替缓慢的读入。

每个整数由两部分组成——符号和数字。

整数的 '+' 通常是省略的，且不会对后面数字所代表的值产生影响，而 '-' 不可省略，因此要进行判定。

10 进制整数中是不含空格或除 0\~9 和正负号外的其他字符的，因此在读入不应存在于整数中的字符（通常为空格）时，就可以判定已经读入结束。

C 和 C++ 语言分别在 ctype.h 和 cctype 头文件中，提供了函数 `isdigit`, 这个函数会检查传入的参数是否为十进制数字字符，是则返回 **true**，否则返回 **false**。对应的，在下面的代码中，可以使用 `isdigit(ch)` 代替 `ch >= '0' && ch <= '9'`，也可以使用 `!isdigit(ch)` 代替 `ch <'0' || ch> '9'`。

### 代码实现

```cpp
int read() {
  int x = 0, w = 1;
  char ch = 0;
  while (ch < '0' || ch > '9') {  // ch 不是数字时
    if (ch == '-') w = -1;        // 判断是否为负
    ch = getchar();               // 继续读入
  }
  while (ch >= '0' && ch <= '9') {  // ch 是数字时
    x = x * 10 + (ch - '0');  // 将新读入的数字「加」在 x 的后面
    // x 是 int 类型，char 类型的 ch 和 '0' 会被自动转为其对应的
    // ASCII 码，相当于将 ch 转化为对应数字
    // 此处也可以使用 (x<<3)+(x<<1) 的写法来代替 x*10
    ch = getchar();  // 继续读入
  }
  return x * w;  // 数字 * 正负号 = 实际数值
}
```

-   举例

读入 num 可写为 `num=read();`。

## 输出优化

### 原理

同样是众所周知，`putchar` 是用来输出单个字符的函数。

因此将数字的每一位转化为字符输出以加速。

要注意的是，负号要单独判断输出，并且每次 %（mod）取出的是数字末位，因此要倒序输出。

### 代码实现

```cpp
void write(int x) {
  if (x < 0) {  // 判负 + 输出负号 + 变原数为正数
    x = -x;
    putchar('-');
  }
  if (x > 9) write(x / 10);  // 递归，将除最后一位外的其他部分放到递归中输出
  putchar(x % 10 + '0');  // 已经输出（递归）完 x 末位前的所有数字，输出末位
}
```

但是递归实现常数是较大的，我们可以写一个栈来实现这个过程。

```cpp
void write(int x) {
  static int sta[35];
  int top = 0;
  do {
    sta[top++] = x % 10, x /= 10;
  } while (x);
  while (top) putchar(sta[--top] + 48);  // 48 是 '0'
}
```

-   举例

输出 num 可写为 `write(num);`。

## 更快的读入/输出优化

通过 `fread` 或者 `mmap` 可以实现更快的读入。

`fread` 能将需要的文件部分读入内存缓冲区。`mmap` 则会调度内核级函数，将文件一次性地映射到内存中，类似于可以指针引用的内存区域。所以在日常程序读写时，只需要重复读取部分文件可以使用 `fread`，因为如果用 `mmap` 反复读取一小块文件，做一次性内存映射并且内核处理 page fault 的花费会远比使用 `fread` 的内核级函数调度大。

一次性读入缓冲区的操作比逐个字符读入（`getchar`,`putchar`）要快的多。因为硬盘的多次读写速度是要慢于直接读取内存的，所以先一次性读到缓存区里再从缓存区读入要快的多。并且 `mmap` 确保了进程间自动共享，存储区如果可以也会与内核缓存分享信息，确保了更少的拷贝操作。

更通用的是 `fread`，因为 `mmap` 不能在 Windows 环境下使用（例如 CodeForces 的 tester）。

`fread` 类似于参数为 `"%s"` 的 `scanf`，不过它更为快速，而且可以一次性读入若干个字符（包括空格换行等制表符），如果缓存区足够大，甚至可以一次性读入整个文件。

对于输出，我们还有对应的 `fwrite` 函数。

```cpp
std::size_t fread(void* buffer, std::size_t size, std::size_t count,
                  std::FILE* stream);
std::size_t fwrite(const void* buffer, std::size_t size, std::size_t count,
                   std::FILE* stream);
```

使用示例：`fread(Buf, 1, SIZE, stdin)`，表示从 stdin 文件流中读入 SIZE 个大小为 1 byte 的数据块到 Buf 中。

读入之后的使用就跟普通的读入优化相似了，只需要重定义一下 getchar。它原来是从文件中读入一个 char，现在变成从 Buf 中读入一个 char，也就是头指针向后移动一位。

```cpp
char buf[1 << 20], *p1, *p2;
#define gc()                                                               \
  (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 20, stdin), p1 == p2) \
       ? EOF                                                               \
       : *p1++)
```

`fwrite` 也是类似的，先放入一个 `OutBuf[MAXSIZE]` 中，最后通过 `fwrite` 一次性将 `OutBuf` 输出。

参考代码：

```cpp
namespace IO {
const int MAXSIZE = 1 << 20;
char buf[MAXSIZE], *p1, *p2;
#define gc()                                                               \
  (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, MAXSIZE, stdin), p1 == p2) \
       ? EOF                                                               \
       : *p1++)

int rd() {
  int x = 0, f = 1;
  char c = gc();
  while (!isdigit(c)) {
    if (c == '-') f = -1;
    c = gc();
  }
  while (isdigit(c)) x = x * 10 + (c ^ 48), c = gc();
  return x * f;
}

char pbuf[1 << 20], *pp = pbuf;

void push(const char &c) {
  if (pp - pbuf == 1 << 20) fwrite(pbuf, 1, 1 << 20, stdout), pp = pbuf;
  *pp++ = c;
}

void write(int x) {
  static int sta[35];
  int top = 0;
  do {
    sta[top++] = x % 10, x /= 10;
  } while (x);
  while (top) push(sta[--top] + '0');
}
}  // namespace IO
```

## 输入输出的缓冲

`printf` 和 `scanf` 是有缓冲区的。这也就是为什么，如果输入函数紧跟在输出函数之后/输出函数紧跟在输入函数之后可能导致错误。

### 刷新输出缓冲区的条件

1.  程序结束；
2.  关闭文件；
3.  `printf` 输出 `\r` 或者 `\n` 到终端的时候（注：如果是输出到文件，则不会刷新缓冲区）；
4.  手动 `fflush()`；
5.  缓冲区满自动刷新；
6.  `cout` 输出 `endl`；
7.  手动 `cout.flush()`。

## 使输入输出优化更为通用

如果你的程序使用多个类型的变量，那么可能需要写多个输入输出优化的函数。下面给出的代码使用 [C++ 中的 `template`](http://www.cplusplus.com/doc/oldtutorial/templates) 实现了对于所有整数类型的输入输出优化。

```cpp
// 声明 template 类,要求提供输入的类型T,并以此类型定义内联函数 read()
template <typename T>
T read() {
  T sum = 0, fl = 1;  // 将 sum,fl 和 ch 以输入的类型定义
  int ch = getchar();
  for (; !isdigit(ch); ch = getchar())
    if (ch == '-') fl = -1;
  for (; isdigit(ch); ch = getchar()) sum = sum * 10 + ch - '0';
  return sum * fl;
}
```

如果要分别输入 `int` 类型的变量 a，`long long` 类型的变量 b 和 `__int128` 类型的变量 c，那么可以写成：

```cpp
a = read<int>();
b = read<long long>();
c = read<__int128>();
```

## 完整带调试版

关闭调试开关时使用 `fread()`,`fwrite()`，退出时自动析构执行 `fwrite()`。

开启调试开关时使用 `getchar()`,`putchar()`，便于调试。

若要开启文件读写时，请在所有读写之前加入 `freopen()`。

```cpp
// #define DEBUG 1  // 调试开关
struct IO {
#define MAXSIZE (1 << 20)
#define isdigit(x) (x >= '0' && x <= '9')
  char buf[MAXSIZE], *p1, *p2;
  char pbuf[MAXSIZE], *pp;
#if DEBUG
#else
  IO() : p1(buf), p2(buf), pp(pbuf) {}

  ~IO() { fwrite(pbuf, 1, pp - pbuf, stdout); }
#endif
  char gc() {
#if DEBUG  // 调试，可显示字符
    return getchar();
#endif
    if (p1 == p2) p2 = (p1 = buf) + fread(buf, 1, MAXSIZE, stdin);
    return p1 == p2 ? ' ' : *p1++;
  }

  bool blank(char ch) {
    return ch == ' ' || ch == '\n' || ch == '\r' || ch == '\t';
  }

  template <class T>
  void read(T &x) {
    double tmp = 1;
    bool sign = 0;
    x = 0;
    char ch = gc();
    for (; !isdigit(ch); ch = gc())
      if (ch == '-') sign = 1;
    for (; isdigit(ch); ch = gc()) x = x * 10 + (ch - '0');
    if (ch == '.')
      for (ch = gc(); isdigit(ch); ch = gc())
        tmp /= 10.0, x += tmp * (ch - '0');
    if (sign) x = -x;
  }

  void read(char *s) {
    char ch = gc();
    for (; blank(ch); ch = gc());
    for (; !blank(ch); ch = gc()) *s++ = ch;
    *s = 0;
  }

  void read(char &c) { for (c = gc(); blank(c); c = gc()); }

  void push(const char &c) {
#if DEBUG  // 调试，可显示字符
    putchar(c);
#else
    if (pp - pbuf == MAXSIZE) fwrite(pbuf, 1, MAXSIZE, stdout), pp = pbuf;
    *pp++ = c;
#endif
  }

  template <class T>
  void write(T x) {
    if (x < 0) x = -x, push('-');  // 负数输出
    static T sta[35];
    T top = 0;
    do {
      sta[top++] = x % 10, x /= 10;
    } while (x);
    while (top) push(sta[--top] + '0');
  }

  template <class T>
  void write(T x, char lastChar) {
    write(x), push(lastChar);
  }
} io;
```

## 参考

[cin.tie 与 sync\_with\_stdio 加速输入输出 - 码农场](https://www.hankcs.com/program/cpp/cin-tie-with-sync_with_stdio-acceleration-input-and-output.html)

[C++ 高速化 - Heavy Watal](https://heavywatal.github.io/cxx/speed.html)

['Re: mmap/mlock performance versus read' - MARC](https://marc.info/?l=linux-kernel&m=95496636207616&w=2)
