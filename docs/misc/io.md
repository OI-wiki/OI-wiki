在默认情况下，`std::cin(std::cout)`是极为迟缓的读入（输出）方式，而`scanf(printf)`比`std::cin(std::cout)`快得多。

可是为什么会这样呢？有没有什么办法解决读入输出缓慢的问题呢？

## 关闭同步 / 解除绑定

### `std::iOS::sync_with_stdio(false)`

这个函数是一个“是否兼容 stdio”的开关，C++ 为了兼容 C，保证程序在使用了`printf`和`std::cout`的时候不发生混乱，将输出流绑到了一起。

这其实是 C++ 为了兼容而采取的保守措施。我们可以在 IO 之前将 stdio 解除绑定，这样做了之后要注意不要同时混用`std::cout`和`printf`之类

### `tie`

tie 是将两个 stream 绑定的函数，空参数的话返回当前的输出流指针。

在默认的情况下`std::cin`绑定的是`std::cout`，每次执行`<<`操作符的时候都要调用`flush()`，这样会增加 IO 负担。可以通过`std::cin.tie(0)`（0 表示 NULL）来解除`std::cin`与`std::cout`的绑定，进一步加快执行效率。

### 代码实现

```cpp
std::ios::sync_with_stdio(false);
std::cin.tie(0);
// 如果编译开启了 C++11 或更高版本，建议使用 std::cin.tie(nullptr);
```

## 读入优化

`scanf`和`printf`依然有优化的空间，这就是本章所介绍的内容——读入和输出优化。

-   注意，读入和输出优化均针对整数，不支持其他类型的数据

### 原理

众所周知，`getchar`是用来读入 char 类型，且速度很快，用“读入字符——转换为整形”来代替缓慢的读入

每个整数由两部分组成——符号和数字

整数的 '+' 通常是省略的，且不会对后面数字所代表的值产生影响，而 '-' 不可省略，因此要进行判定

10 进制整数中是不含空格或除 0~9 和正负号外的其他字符的，因此在读入不应存在于整数中的字符（通常为空格）时，就可以判定已经读入结束

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
    x = (x << 3) + (x << 1) + ch - '0';  // 将新读入的数字’加’在 x 的后面
    // x<<3==x*8  x<<1==x*2  所以 (x<<3)+(x<<1) 相当于 x*10
    // x 是 int 类型，char 类型的 ch 和 ’0’ 会被自动转为其 ASCII
    // 表中序号，相当于将 ch 转化为对应数字
    ch = getchar();  // 继续读入
  }
  return x * w;  // 数字 * 正负号 = 实际数值
}
```

-   举例

读入 num 可写为`num=read();`

## 输出优化

### 原理

同样是众所周知，`putchar`是输出单个字符

因此将数字的每一位转化为字符输出以加速

要注意的是，负号要单独判断输出，并且每次 %（mod）取出的是数字末位，因此要倒序输出

### 代码实现

```cpp
int write(int x) {
  if (x < 0) {  // 判负 + 输出负号 + 变原数为正数
    x = -x;
    putchar('-');
  }
  if (x > 9) write(x / 10);  // 递归，将除最后一位外的其他部分放到递归中输出
  putchar(x % 10 + '0');  // 已经输出（递归）完 x 末位前的所有数字，输出末位
}
```

但是递归实现常数是较大的，我们可以写一个栈来实现这个过程

```cpp
inline void write(int x) {
  static int sta[35];
  int top = 0;
  do {
    sta[top++] = x % 10, x /= 10;
  } while (x);
  while (top) putchar(sta[--top] + 48);  // 48 是 '0'
}
```

-   举例

输出 num 可写为`write(num);`

## 更快的读入 / 输出优化

通过`fread`或者`mmap`可以实现更快的读入。其本质为一次性读入一个巨大的缓存区，如此比一个一个字符读入要快的多 (`getchar`,`putchar`）。因为硬盘的多次读写速度是要慢于内存的，先一次性读到内存里在读入要快的多。

更通用的是`fread`，因为`mmap`不能在 Windows 使用。

`fread`类似于`scanf("%s")`，不过它更为快速，而且可以一次性读入若干个字符（包括空格换行等制表符），如果缓存区足够大，甚至可以一次性读入整个文件。

对于输出，我们还有对应的`fwrite`函数

```cpp
std::size_t fread(void* buffer, std::size_t size, std::size_t count,
                  std::FILE* stream);
std::size_t fwrite(const void* buffer, std::size_t size, std::size_t count,
                   std::FILE* stream);
```

使用示例：`fread(Buf, 1, MAXSIZE, stdin)`，如此从 stdin 文件流中读入 MAXSIZE 个大小为 1 的字符到 Buf 中。

读入之后的使用就跟普通的读入优化相似了，只需要重定义一下 getchar。它原来是从文件中读入一个 char，现在变成从 Buf 中读入一个 char，也就是头指针向后移动一位。

```cpp
char buf[1 << 20], *p1, *p2;
#define gc()                                                               \
  (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 20, stdin), p1 == p2) \
       ? EOF                                                               \
       : *p1++)
```

`fwrite`也是类似的，先放入一个`OutBuf[MAXSIZE]`中，最后通过`fwrite`一次性将`OutBuf`输出。

参考代码：

```cpp
namespace IO {
const int MAXSIZE = 1 << 20;
char buf[MAXSIZE], *p1, *p2;
#define gc()                                                               \
  (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, MAXSIZE, stdin), p1 == p2) \
       ? EOF                                                               \
       : *p1++)
inline int rd() {
  int x = 0, f = 1;
  char c = nc();
  while (!isdigit(c)) {
    if (c == '-') f = -1;
    c = nc();
  }
  while (isdigit(c)) x = (x << 1) + (x << 3) + (c ^ 48), c = nc();
  return x * f;
}
char pbuf[1 << 20], *pp = pbuf;
inline void push(const char &c) {
  if (pp - pbuf == 1 << 20) fwrite(pbuf, 1, 1 << 20, stdout), pp = pbuf;
  *pp++ = c;
}
inline void write(int x) {
  static int sta[35];
  int top = 0;
  do {
    sta[top++] = x % 10, x /= 10;
  } while (x);
  while (top) push(sta[--top] + '0');
}
}  // namespace IO
```

## 参考

[http://www.hankcs.com/program/cpp/cin-tie-with-sync_with_stdio-acceleration-input-and-output.HTML](http://www.hankcs.com/program/cpp/cin-tie-with-sync_with_stdio-acceleration-input-and-output.html)

[http://meme.biology.tohoku.ac.jp/students/iwasaki/cxx/speed.HTML](http://meme.biology.tohoku.ac.jp/students/iwasaki/cxx/speed.html)
