author: H-J-Granger, orzAtalod, ksyx, Ir1d, Chrogeek, Enter-tainer, yiyangit

本页面主要列举一些竞赛中很多人经常会出现的错误。

## 会引起 CE 的错误

这类错误多为词法、语法和语义错误，引发的原因较为简单，修复难度较低。

例：

- `int main()` 写为 `int mian()` 之类的拼写错误。

- 写完 `struct` 或 `class` 忘记写分号。

- 数组开太大，（在 OJ 上）使用了不合法的函数（例如多线程），或者函数声明但未定义，会引起链接错误。

-   函数参数类型不匹配。

    -   示例：如使用 `<algorithm>` 头文件中的 `max` 函数时，传入了一个 `int` 类型参数和一个 `long long` 类型参数。

        ```cpp
        // query 为返回 long long 类型的自定义函数
        printf("%lld\n", max(0, query(1, 1, n, l, r));

        //错误    没有与参数列表匹配的 重载函数 "std::max" 实例
        ```

- 使用 `goto` 和 `switch-case` 的时候跳过了一些局部变量的初始化。

## 不会引起 CE 但会引起 Warning 的错误

犯这类错误时写下的程序虽然能通过编译，但大概率会得到错误的程序运行结果。这类错误会在使用 `-W{warningtype}` 参数编译时被编译器指出。

-   赋值运算符 `=` 和比较运算符 `==` 不分。

    -   示例：

        ```cpp
        std::srand(std::time(nullptr));
        int n = std::rand();
        if (n = 1)
          printf("Yes");
        else
          printf("No");

        // 无论 n 的随机所得值为多少，输出肯定是 Yes
        // 警告    运算符不正确: 在 Boolean 上下文中执行了常量赋值。应考虑改用“==”。
        ```

    - 如果确实想在原应使用 `==` 的语句里使用 `=`（比如 `while (foo = bar)`），又不想收到 Warning，可以使用 **双括号**：`while ((foo = bar))`。

-   由于运算符优先级产生的错误。

    -   示例：

        ```cpp
        // 错误
        // std::cout << (1 << 1 + 1);
        // 正确
        std::cout << ((1 << 1) + 1);

        // 警告    “<<”: 检查运算符优先级是否有可能的错误；使用括号阐明优先级
        ```

- 不正确地使用 `static` 修饰符。

- 使用 `scanf` 读入的时候没加取地址符 `&`。

- 使用 `scanf` 或 `printf` 的时候参数类型与格式指定符不符。

-   同时使用位运算和逻辑运算符 `==` 并且未加括号。
    - 示例：`(x >> j) & 3 == 2`

-   `int` 字面量溢出。

    - 示例：`long long x = 0x7f7f7f7f7f7f7f7f`，`1<<62`。

- 未初始化局部变量，导致局部变量被赋予垃圾初值。

- 局部变量与全局变量重名，导致全局变量被意外覆盖。（开 `-Wshadow` 就可检查此类错误。）

-   运算符重载后引发的输出错误。
    -   示例：
        ```cpp
        // 本意：前一个 << 为重载后的运算符，表示输出；后一个 << 为移位运算符，表示将 1
        // 左移 1 位。 但由于忘记加括号，导致编译器将后一个 <<
        // 也判作输出运算符，而导致输出的结果与预期不同。 错误 std::cout << 1 << 1; 正确
        std::cout << (1 << 1);
        ```

## 既不会引起 CE 也不会引发 Warning 的错误

这类错误无法被编译器发现，仅能自行查明。

### 会导致 WA 的错误

- 上一组数据处理完毕，读入下一组数据前，未清空数组。

- 读入优化未判断负数。

-   所用数据类型位宽不足，导致溢出。
    - 如习语“三年 OI 一场空，不开 `long long` 见祖宗”所描述的场景。选手因为没有在正确的地方开 `long long`（将整数定义为 `long long` 类型），导致得出错误的答案而失分。

- 存图时，节点编号 0 开始，而题目给的边中两个端点的编号从 1 开始，读入的时候忘记 -1。

- 大/小于号打错或打反。

-   在执行 `ios::sync_with_stdio(false);` 后混用 `scanf/printf` 和 `std::cin/std::cout` 两种 IO，导致输入/输出错乱。

    -   示例：

        ```cpp
        // 这个例子将说明关闭与 stdio 的同步后，混用两种 IO 方式的后果
        // 建议单步运行来观察效果
        #include <cstdio>
        #include <iostream>
        int main() {
          // 关闭同步后，cin/cout 将使用独立缓冲区，而不是将输出同步至 scanf/printf
          // 的缓冲区，从而减少 IO 耗时
          std::ios::sync_with_stdio(false);
          // cout 下，使用'\n'换行时，内容会被缓冲而不会被立刻输出
          std::cout << "a\n";
          // printf 的 '\n' 会刷新 printf 的缓冲区，导致输出错位
          printf("b\n");
          std::cout << "c\n";
          //程序结束时，cout 的缓冲区才会被输出
          return 0;
        }
        ```

    - 特别的，也不能在执行 `ios::sync_with_stdio(false);` 后使用 `freopen`。

-   由于宏的展开，且未加括号导致的错误。

    -   示例：该宏返回的值并非 $4^2 = 16$ 而是 $2+2\times 2+2 = 8$。

        ```cpp
        #define square(x) x* x
        printf("%d", square(2 + 2));
        ```

-   哈希的时候没有使用 `unsigned` 导致的运算错误。
    - 对负数的右移运算会在最高位补 1。参见：[位运算](../math/bit.md)

- 没有删除或注释掉调试输出语句。

-   误加了 `;`。

    -   示例：

        ```cpp
        /* clang-format off */
        while (1);
            printf("OI Wiki!\n");
        ```

- 哨兵值设置错误。例如，平衡树的 `0` 节点。

-   在类或结构体的构造函数中使用 `:` 初始化变量时，变量声明顺序不符合初始化时候的依赖关系。

    - 成员变量的初始化顺序与它们在类中声明的顺序有关，而与初始化列表中的顺序无关。参见：[构造函数与成员初始化器列表](https://zh.cppreference.com/w/cpp/language/constructor) 的“初始化顺序”
    -   示例：

        ```cpp
        #include <iostream>

        class Foo {
         public:
          int a, b;
          // a 将在 b 前初始化，其值不确定
          Foo(int x) : b(x), a(b + 1) {}
        };

        int main() {
          Foo bar(1, 2);
          std::cout << bar.a << ' ' << bar.b;
        }

        // 可能的输出结果：-858993459 1
        ```

-   并查集合并集合时没有把两个元素的祖先合并。

    -   示例：

        ```cpp
        f[a] = b;              // 错误
        f[find(a)] = find(b);  // 正确
        ```

#### 换行符不同

???+ warning
    在正式比赛中会尽量保证选手答题的环境和最终测试的环境相同。
    
    本节内容仅适用于模拟赛等情况，而我们也建议出题人尽量让数据符合 [数据格式](../problemsetting/#_29)。

不同的操作系统使用不同的符号来标记换行，以下为几种常用系统的换行符：

- LF（用 `\n` 表示）：`Unix` 或 `Unix` 兼容系统

- CR+LF（用 `\r\n` 表示）：`Windows`

- CR（用 `\r` 表示）：`Mac OS` 至版本 9

而 C/C++ 利用转义序列 `\n` 来换行，这可能会导致我们认为输入中的换行符也一定是由 `\n` 来表示，而只读入了一个字符来代表换行符，这就会导致我们没有完全读入输入文件。

以下为解决方案：

- 多次 `getchar()`，直到读到想要的字符为止。

- 使用 `cin` 读入，**这可能会增大代码常数**。

- 使用 `scanf("%s",str)` 读入一个字符串，然后取 `str[0]` 作为读入的字符。

- 使用 `scanf(" %c",&c)` 过滤掉所有空白字符。

### 会导致 RE

-   对整数除以 $0$。
    - 对 $0$ 求逆元。

- 没删文件操作（某些 OJ）。

-   排序时比较函数的错误 `std::sort` 要求比较函数是严格弱序：`a<a` 为 `false`；若 `a<b` 为 `true`，则 `b<a` 为 `false`；若 `a<b` 为 `true` 且 `b<c` 为 `true`，则 `a<c` 为 `true`。其中要特别注意第二点。
    如果不满足上述要求，排序时很可能会 RE。
    例如，编写莫队的奇偶性排序时，这样写是错误的：
    ```cpp
    bool operator<(const int a, const int b) {
      if (block[a.l] == block[b.l])
        return (block[a.l] & 1) ^ (a.r < b.r);
      else
        return block[a.l] < block[b.l];
    }
    ```
    上述代码中 `(block[a.l]&1)^(a.r<b.r)` 不满足上述要求的第二点。
    改成这样就正确了：
    ```cpp
    bool operator<(const int a, const int b) {
      if (block[a.l] == block[b.l])
        // 错误：不满足严格弱序的要求
        // return (block[a.l] & 1) ^ (a.r < b.r);
        // 正确
        return (block[a.l] & 1) ? (a.r < b.r) : (a.r > b.r);
      else
        return block[a.l] < block[b.l];
    }
    ```

- 解引用空指针。

### 会导致 TLE

- 分治未判边界导致死递归。

-   死循环。

    - 循环变量重名。

    - 循环方向反了。

- BFS 时不标记某个状态是否已访问过。

-   使用宏展开编写 min/max

    这种错误会大大增加程序的运行时间，甚至直接影响代码的时间复杂度。在初学者写线段树时尤为多见。

    常见的错误写法是这样的：

    ```cpp
    #define Min(x, y) ((x) < (y) ? (x) : (y))
    #define Max(x, y) ((x) > (y) ? (x) : (y))
    ```

    这样写虽然在正确性上没有问题，但是如果直接对函数的返回值取 max，如 `a = Max(func1(), func2())`，而这个函数的运行时间较长，则会大大影响程序的性能，因为宏展开后是 `a = func1() > func2() ? func1() : func2()` 的形式，调用了三次函数，比正常的 max 函数多调用了一次。注意，如果 `func1()` 每次返回的答案不一样，还会导致这种 `max` 的写法出现错误。例如 `func1()` 为 `return ++a;` 而 `a` 为全局变量的情况。

    示例：如下代码会被卡到单次查询 $\Theta(n)$ 导致 TLE。

    ```cpp
    #define max(x, y) ((x) > (y) ? (x) : (y))

    int query(int t, int l, int r, int ql, int qr) {
      if (ql <= l && qr >= r) {
        ++ti[t];  // 记录结点访问次数方便调试
        return vi[t];
      }

      int mid = (l + r) >> 1;
      if (mid >= qr) return query(lt(t), l, mid, ql, qr);
      if (mid < ql) return query(rt(t), mid + 1, r, ql, qr);
      return max(query(lt(t), l, mid, ql, qr), query(rt(t), mid + 1, r, ql, qr));
    ```

- 没删文件操作（某些 OJ）。

- 在 `for/while` 循环中重复执行复杂度非 $O(1)$ 的函数。严格来说，这可能会引起时间复杂度的改变。

### 会导致 MLE

- 数组过大。

-   STL 容器中插入了过多的元素。

    - 经常是在一个会向 STL 插入元素的循环中死循环了。

    - 也有可能被卡了。

### [未定义行为](https://zh.cppreference.com/w/cpp/language/ub)

-   数组越界。多数会引发 RE。

    - 未正确设置循环的初值导致访问了下标为 -1 的值。

    - 无向图边表未开 2 倍。

    - 线段树未开 4 倍空间。

    - 看错数据范围，少打一个零。

    - 错误预估了算法的空间复杂度。

    - 写线段树的时候，`pushup` 或 `pushdown` 叶节点。

-   解引用野指针。

    - 未初始化就解引用指针。

    - 指针指向的内存区域已经释放。

### 会导致常数过大

-   定义模数的时候，未定义为常量。

    -   示例：

        ```cpp
        // int mod = 998244353;      // 错误
        const int mod = 998244353  // 正确，方便编译器按常量处理
        ```

- 使用了不必要的递归（尾递归不在此列）。

- 将递归转化成迭代的时候，引入了大量额外运算。

### 只在程序在本地运行的时候造成影响的错误

-   文件操作有可能会发生的错误：

    - 对拍时未关闭文件指针 `fclose(fp)` 就又令 `fp = fopen()`。这会使得进程出现大量的文件野指针。

    - `freopen()` 中的文件名未加 `.in`/`.out`。

- 使用堆空间后忘记 `delete` 或 `free`。
