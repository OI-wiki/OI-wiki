本页面主要分享一下在竞赛中经常/很多人会出现的错误。

## 会引起 Compile Error 的错误

由于这类错误过于简单,~~相信是个正常人都会修~~,故略写.

-  `int main()` 写为 `int mian()` 。

-  写完 `struct` 或 `class` 忘记写分号。


## 不会引起 Compile Error 但会引发 Warning 的错误

这类错误较难发现，但会在使用 `-W{warningtype}` 参数编译时被编译器指出，所以要多学会使用 `-W{warningtype}` 参数，常见的有 `-Wall`，`-Wextra`，`-Wshadow` 等。

-  由于运算符优先级产生的错误。
    -  `1 << 1 + 1` : 1 左移了 2，即该表达式返回的值是 `4` 。

-  文件操作有可能会发生的错误。

    -   对拍时未清除文件指针即 `fclose(fp)` 就又令 `fp = fopen()` , 这会使得进程出现大量的文件野指针。
    -   `freopen()` 中的文件名未加 `.in` / `.out` 。

-  不正确地使用 `static` 修饰符。

-  `-1 >> 1 == 1` 。

- 赋值运算符和 `==` 不分。
    - 示例：
      ```cpp
      if (n = 1) puts("Yes");
      else puts("No");
      ```
      无论 $n$ 的值之前为多少，输出肯定是 `Yes`。

- 使用 `scanf` 读入的时候没加取地址符 `&``。

- 没有考虑数组下标出现负数的情况。


## 既不会引起 Compile Error 也不会引发 Warning 的错误

这类错误无法被编译器发现,所以在调试时只能依靠你自己.

-  无向图边表未开 2 倍。

-  线段树未开 4 倍空间。

-  多组数据未清空数组。

-  分治未判边界导致死递归。

-  读入优化未判断负数。

-  存图下标从 0 开始输入节点未 -1。

-  BFS 时不标记某个状态是否已访问过。

-  大/小于号打错或打反。

-  在执行 `ios::sync_with_stdio(false);` 后混用两种 IO，导致输入/输出错乱。
     - 可以参考这个例子。
      ```cpp
      //这个例子将说明，关闭与 stdio 的同步后，混用两种 IO 的后果
      //建议单步运行来观察效果
      #include <cstdio>
      #include <iostream>
      int main() {
          std::ios::sync_with_stdio(false);
          //关闭同步后，cin/cout 将使用独立缓冲区，而不是将输出同步至 scanf/printf 的缓冲区，从而减少 IO 耗时
          std::cout << "a\n";
          //cout 下，使用'\n'换行时，内容会被缓冲而不会被立刻输出，应该使用 endl 来换行并立刻刷新缓冲区
          printf("b\n");
          //printf 的 '\n' 会刷新 printf 的缓冲区，导致输出错位
          std::cout << "c\n";
          return 0;//程序结束时，cout 的缓冲区才会被输出
      }
      ```

-   由于宏的展开，且未加括号导致的错误：
	```cpp
	#define square(x) x * x
	printf("%d", square(2 + 2));
	```
	该宏返回的值并非 $4^2 = 16$ 而是 $2+2\times 2+2 = 8$ 。

-  使用宏展开编写 min/max
    这种做法虽然算不上是「错误」，但是这里还是要拎出来说一下。
	常见的写法是这样的：
	```cpp
	#define Min(x, y) (x < y ? x : y)
	#define Max(x, y) (x > y ? x : y)
	```
	这样写虽然在正确性上没有问题，但是如果你直接对函数的返回值取 max，如 `a = Max(func1(), func2())`，而这个函数的运行时间较长，则会大大影响程序的性能，因为宏展开后是 `a = func1() > func2() ? func1() : func2()` 的形式，调用了三次函数，比正常的 max 函数多调用了一次。
	这种错误在初学者写线段树时尤为多见。
