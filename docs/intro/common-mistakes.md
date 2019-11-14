本页面主要分享一下在竞赛中经常/很多人会出现的错误。

## 会引起 Compile Error 的错误

由于这类错误过于简单，~~相信是个正常人都会修~~, 故略写。

-    `int main()` 写为 `int mian()` 。

-   写完 `struct` 或 `class` 忘记写分号。

-   数组开太大，（在 OJ 上）使用了不合法的函数（例如多线程），或者函数声明但未定义，会引起链接错误。

-   使用 `algorithm` 中的 `max` 函数时，一个参数类型为 `int` 而另一个参数类型为 `long long` 
    -   示例：
        ```cpp
        long long x = query(1, 1, n, l, r);
        printf("%lld\n", max(0, x));
        ```

-    `goto` 的时候，跳过了一些局部变量的初始化。

    -    `switch-case` 的时候，跳过了一些局部变量的初始化。

## 不会引起 Compile Error 但会引发 Warning 的错误

这类错误较难发现，但会在使用 `-W{warningtype}` 参数编译时被编译器指出，所以要多学会使用 `-W{warningtype}` 参数，常见的有 `-Wall` ， `-Wextra` ， `-Wshadow` 等。

-   由于运算符优先级产生的错误。
    -    `1 << 1 + 1` : `1` 左移了 `2` ，即该表达式返回的值是 `4` 。

-   不正确地使用 `static` 修饰符。

-    `-1 >> 1 == 1` 。

-   赋值运算符和 `==` 不分。
    -   示例：
        ```cpp
        if (n = 1)
          puts("Yes");
        else
          puts("No");
        ```
        无论 $n$ 的值之前为多少，输出肯定是 `Yes` 。

-   使用 `scanf` 读入的时候没加取地址符 `&` 。更一般的，使用 `scanf` 或 `printf` 的时候参数类型不对。

-   没有考虑数组下标出现负数的情况。

-   同时使用位运算和逻辑运算符（ `==` ）并且未加括号（例如 `(x>>j)&3==2` ）。

-    `int` 字面量溢出，例如： `long long x = 0x7f7f7f7f7f7f7f7f` ， `1<<62` 。

-   未初始化变量。

## 既不会引起 Compile Error 也不会引发 Warning 的错误

这类错误无法被编译器发现，所以在调试时只能依靠你自己。

### 会导致 WA

-   多组数据未清空数组。

-   读入优化未判断负数。

-   所用数据类型不够大导致溢出，即常见的不开 `long long` 见祖宗。

-   存图时，节点编号 0 开始，而题目给的边中两个端点的编号从 1 开始，读入的时候忘记 -1。

-   大/小于号打错或打反。

-   在执行 `ios::sync_with_stdio(false);` 后混用两种 IO，导致输入/输出错乱。
    -   可以参考这个例子。
        ```cpp
        // 这个例子将说明，关闭与 stdio 的同步后，混用两种 IO 的后果
        // 建议单步运行来观察效果
        #include <cstdio>
        #include <iostream>
        int main() {
          std::ios::sync_with_stdio(false);
          // 关闭同步后，cin/cout 将使用独立缓冲区，而不是将输出同步至 scanf/printf
          // 的缓冲区，从而减少 IO 耗时
          std::cout << "a\n";
          // cout 下，使用'\n'换行时，内容会被缓冲而不会被立刻输出，应该使用 endl
          // 来换行并立刻刷新缓冲区
          printf("b\n");
          // printf 的 '\n' 会刷新 printf 的缓冲区，导致输出错位
          std::cout << "c\n";
          return 0;  //程序结束时，cout 的缓冲区才会被输出
        }
        ```
    -   特别的，也不能在执行 `ios::sync_with_stdio(false);` 后使用 `freopen` 。

-   由于宏的展开，且未加括号导致的错误：
    ```cpp
    #define square(x) x* x
    printf("%d", square(2 + 2));
    ```
    该宏返回的值并非 $4^2 = 16$ 而是 $2+2\times 2+2 = 8$ 。

-   哈希的时候没有使用 `unsigned` ，因为对负数的位运算比较玄学。

-   没有删除调试信息。

-   误加了 `;` 。
    -   可以参考这个例子：
        ```cpp
        /* clang-format off */
        while (1);
        printf("OI Wiki!\n");
        ```

-   没有正确设置哨兵值。例如，平衡树的 `0` 节点。

### 会导致 RE

-   数组开小，包括：

    -   无向图边表未开 2 倍。

    -   线段树未开 4 倍空间。

    -   看错数据范围，少打一个零。

    -   错误预估了算法的空间复杂度。

-   除以零。

    -   对 $0$ 求逆元。

-   没删文操（某些 OJ）。

### 会导致 TLE

-   分治未判边界导致死递归。

-   死循环。

    -   循环变量重名。

    -   循环方向反了。

-   BFS 时不标记某个状态是否已访问过。

-   使用宏展开编写 min/max

    这种做法虽然算不上是「错误」，但是这里还是要拎出来说一下。

    常见的写法是这样的：

    ```cpp
    #define Min(x, y) (x < y ? x : y)
    #define Max(x, y) (x > y ? x : y)
    ```

    这样写虽然在正确性上没有问题，但是如果你直接对函数的返回值取 max，如 `a = Max(func1(), func2())` ，而这个函数的运行时间较长，则会大大影响程序的性能，因为宏展开后是 `a = func1() > func2() ? func1() : func2()` 的形式，调用了三次函数，比正常的 max 函数多调用了一次。

    这种错误在初学者写线段树时尤为多见，会直接影响算法的时间复杂度。

-   没删文操（另一些 OJ）。

-   排序时比较函数的错误 `std::sort` 要求比较函数是严格弱序： `a<a` 为 `false` ；若 `a<b` 为 `true` ，则 `b<a` 为 `false` ；若 `a<b` 为 `true` 且 `b<c` 为 `true` ，则 `a<c` 为 `true` 。其中要特别注意第二点。
    如果不满足上述要求，排序时很可能会 RE。
    例如，编写莫队的奇偶性排序时，这样写是错误的：
    ```cpp
    bool operator<(const int a, const int b) {
      if (block[a.l] == block[b.l])
        return (block[a.l] & 1) ^ (a.r < b.r);
      else
        return block[a.l] < block[b.l];
    ```
    上述代码中 `(block[a.l]&1)^(a.r<b.r)` 不满足严格弱序的要求 2。
    改成这样就正确了。
    ```cpp
    bool operator<(const int a, const int b) {
      if (block[a.l] == block[b.l])
        return (block[a.l] & 1) ? (a.r < b.r) : (a.r > b.r);
      else
        return block[a.l] < block[b.l];
    ```

### 会导致 MLE

-   数组过大。

-   STL 容器中插入了过多的元素。

    -   经常是在一个会向 STL 插入元素的循环中死循环了。

    -   也有可能被卡了。

### 会随机 TLE 或者 RE 或者 WA 或者 MLE

-   数组越界。上下都算。

    -   对线段树的叶节点 `pushup` 或 `pushdown` 。

### 会导致常数过大

-   定义模数的时候，使用了全局变量（如 `int mod = 998244353` ，正确做法是 `const int mod = 998244353` ）。

-   使用了不必要的递归（需要注意的是，尾递归不在此列）。

    -   使用了 `std::stack` 将递归转化成迭代。

    -   使用了自己手写的栈将递归转化成迭代。

    -   为了将递归转化成迭代，加入了大量额外运算。

-   使用了 `for(int i=0; i<strlen(s); ++i)` （严格来说，这句可能会引起时间复杂度的改变）。

### 有错误，但是在 OJ 上做题的时候不需要特别注意

-   文件操作有可能会发生的错误。

    -   对拍时未清除文件指针即 `fclose(fp)` 就又令 `fp = fopen()` , 这会使得进程出现大量的文件野指针。

    -    `freopen()` 中的文件名未加 `.in` / `.out` 。
-   使用堆空间忘记 `delete` 或 `free` 。
