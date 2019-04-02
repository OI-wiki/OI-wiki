## 介绍

`std::bitset` 是标准库中的一个存储 `0/1` 的大小不可变容器。

由于内存地址是按字节即 `byte` 寻址，而非比特 `bit`，一个 `bool` 类型的变量，虽然只能表示 `0/1` , 但是也占了 `1byte` 的内存。

`bitset` 就是通过固定的优化，使得一个字节的八个比特能分别储存 8 位的 `0/1`。

对于一个 4 字节的 `int` 变量，在只存 `0/1` 的意义下，`bitset` 占用空间只是其 $\frac{1}{32}$，计算一些信息时，所需时间也是其 $\frac 1{32}$。

在某些情况下通过 `bitset` 可以优化程序的运行效率。至于其优化的是复杂度还是常数，要看计算复杂度的角度。一般 `bitset` 的复杂度有以下几种记法：（设原复杂度为 $\mathcal O(n)$）

1. $\mathcal O(n)$，这种记法认为 `bitset` 完全没有优化复杂度。
2. $\mathcal O(\frac n{32})$，这种记法不太严谨（复杂度中不应出现常数），但体现了 `bitset` 能将所需时间优化至 $\frac 1{32}$。
3. $\mathcal O(\frac n w)$，其中 $w=32$（计算机的位数），这种记法较为普遍接受。
4. $\mathcal O(\frac n {\log w})$，其中 $w$ 为计算机一个整型变量的大小。

当然， `vector` 的一个特化 `vector<bool>` 的储存方式同 `bitset` 一样，区别在于其支持动态开空间，`bitset` 则和我们一般的静态数组一样，是在编译时就开好了的。

然而，`bitset` 有一些好用的库函数，不仅方便，而且有时可以避免使用 for 循环而没有实质的速度优化。因此，一般不使用 `vector<bool>`。

## 使用

### 头文件

```cpp
#include <bitset> 
```

??? "彩蛋"

      在 `bitset` 头文件的第 $603$ 行，可以看到如下注释：

      ```cpp
            // Are all empty bitsets equal to each other?  Are they equal to
            // themselves?  How to compare a thing which has no state?  What is
            // the sound of one zero-length bitset clapping?
      ```

### 构造函数

- `bitset()` : 每一位都是 `false`。
- `bitset(unsigned long val)` : 设为 `val` 的二进制形式。
- `bitset(const string& str)` : 设为 $01$ 串 `str`。

### 运算符

- `operator[]` : 访问其特定的一位。
- `operator ==/！=` : 比较两个 `bitset` 内容是否完全一样。
- `operator &/&=/|/|=/^/^=/~` : 进行按位与/或/异或/取反操作。**`bitset` 只能与 `bitset` 进行位运算**，若要和整型进行位运算，要先将整型转换为 `bitset`。
- `operator <</>>/<<=/>>=` : 进行二进制左移/右移。
- `operator <</>>` : 流运算符，这意味着你可以通过 `cin/cout` 进行输入输出。

### 成员函数

- `count()` : 返回 `true` 的数量。
- `size()` : 返回 `bitset` 的大小。
- `test(pos)` : 它和 `vector` 中的 `at()` 的作用是一样的，和 `[]` 运算符的区别就是越界检查。
- `any()` : 若存在某一位是 `true` 则返回 `true`，否则返回 `false`。
- `none()` : 若所有位都是 `false` 则返回 `true`，否则返回 `false`。
- `all()` : **C++11**，若所有位都是 `true` 则返回 `true`，否则返回 `false`。
- 1. `set()` : 将整个 `bitset` 设置成 `true` 。
  2. `set(pos, val = true)` : 将某一位设置成 `true`/`false`。
- 1. `reset()` : 将整个 `bitset` 设置成 `false` 。
  2. `reset(pos)` : 将某一位设置成 `false`。相当于 `set(pos, false)`。
- 1. `flip()` : 翻转每一位。（$0\leftrightarrow1$，相当于异或）
  2. `flip(pos)` : 翻转某一位。
- `to_string()` : 返回转换成的字符串表达。
- `to_ulong()` : 返回转换成的 `unsigned long` 表达 ( `long` 在 NT 及 32 位 POSIX 系统下与 `int` 一样，在 64 位 POSIX 下与 `long long` 一样）。
- `to_ullong()` : **C++11**，返回转换成的 `unsigned long long` 表达。

一些文档中没有的成员函数：

- `_Find_first()` : 返回 `bitset` 第一个 `true` 的下标，若没有 `true` 则返回 `bitset` 的大小。
- `_Find_next(pos)` : 返回 `pos` 后面（下标严格大于 `pos` 的位置）第一个 `true` 的下标，若 `pos` 后面没有 `true` 则返回 `bitset` 的大小。

## 应用

### [LibreOJ β Round #2」贪心只能过样例](https://loj.ac/problem/515)

这题可以用 $dp$ 做，转移方程很简单：

$f(i,j)$ 表示前 $i$ 个数的平方和能否为 $j$，那么 $f(i,j)=\bigvee\limits_{k=a}^bf(i-1,j-k^2)$（或起来）。

但如果直接做的话是 $\mathcal O(n^5)$ 的，（看起来）过不了。

发现可以用 `bitset` 优化，左移再或起来就好了：[std::bitset](https://loj.ac/submission/395274)

然后发现..被加了几个剪枝的暴力艹了：[加了几个剪枝的暴力](https://loj.ac/submission/395673)

然而，可以手写 `bitset`（只需要支持左移后或起来这一种操作）压 $64$ 位（`unsigned long long`）来艹掉暴力：[手写bitset](https://loj.ac/submission/395619)

### [CF1097F Alex and a TV Show](https://codeforces.com/contest/1097/problem/F)

#### 题意

给你 $n$ 个可重集，$4$ 种操作：

1. 把某个可重集设为一个数。
2. 把某个可重集设为另外两个可重集加起来。
3. 把某个可重集设为从另外两个可重集中各选一个数的 $\gcd$。即：$A=\{\gcd(x,y)|x\in B,y\in C\}$。
4. 询问某个可重集中某个数的个数，**在模 2 意义下**。

可重集个数 $10^5$，操作个数 $10^6$，值域 $7000$。

#### 做法

看到 “在模 2 意义下”，~~而且这是篇 bitset 教程~~，可以想到用 `bitset` 维护每个可重集。

这样的话，操作 $1$ 直接设，操作 $2$ 就是异或（因为模 $2$），操作 $4$ 就是直接查，但 .. 操作 $3$ 怎么办？

我们可以尝试维护每个可重集的所有约数构成的可重集，这样的话，操作 $3$ 就是直接按位与。

我们可以把值域内每个数的约数构成的 `bitset` 预处理出来，这样操作 $1$ 就解决了。操作 $2$ 仍然是异或。

现在的问题是，如何通过一个可重集的约数构成的可重集得到该可重集中某个数的个数。

令原可重集为 $A$，其约数构成的可重集为 $A'$，我们要求 $A$ 中 $x$ 的个数，用 [莫比乌斯反演](/math/mobius/) 推一推：

$$\begin{aligned}&\sum\limits_{i\in A}[\frac i x=1]\\=&\sum\limits_{i\in A}\sum\limits_{d|\frac i x}\mu(d)\\=&\sum\limits_{d\in A',x|d}\mu(\frac d x)\end{aligned}$$

由于是模 $2$ 意义下，$-1$ 和 $1$ 是一样的，只用看 $\frac d x$ 有没有平方因子即可。所以，可以对值域内每个数预处理出其倍数中除以它不含平方因子的位置构成的 `bitset`，求答案的时候先按位与再 `count()` 就好了。

这样的话，单次询问复杂度就是 $\mathcal O(\frac v w)$（$v=7000,\,w=32$）。预处理可以写 $\mathcal O(v\log v)$ 的，也可以写 $\mathcal O(v\sqrt v)$ 的，还可以写 $\mathcal O(v^2)$ 的，~~它们甚至跑的差不多快~~。

??? "参考代码"

      ```cpp
      #include <iostream>
      #include <cstdio>
      #include <bitset>
      #include <cctype>
      #include <cmath>

      using namespace std;

      int read()
      {
          int out=0;
          char c;
          while (!isdigit(c=getchar()));
          for (;isdigit(c);c=getchar()) out=out*10+c-'0';
          return out;
      }

      const int N=100005;
      const int M=1000005;
      const int V=7005;

      bitset<V> pre[V],pre2[V],a[N],mu;
      int n,m,tot;
      char ans[M];

      int main()
      {
          int i,j,x,y,z;

          n=read();
          m=read();

          mu.set();
          for (i=2;i*i<V;++i)
          {
              for (j=1;i*i*j<V;++j)
              {
                  mu[i*i*j]=0;
              }
          }
          for (i=1;i<V;++i)
          {
              for (j=1;i*j<V;++j)
              {
                  pre[i*j][i]=1;
                  pre2[i][i*j]=mu[j];
              }
          }

          while (m--)
          {
              switch (read())
              {
                  case 1:
                      x=read();
                      y=read();
                      a[x]=pre[y];
                      break;
                  case 2:
                      x=read();
                      y=read();
                      z=read();
                      a[x]=a[y]^a[z];
                      break;
                  case 3:
                      x=read();
                      y=read();
                      z=read();
                      a[x]=a[y]&a[z];
                      break;
                  case 4:
                      x=read();
                      y=read();
                      ans[tot++]=((a[x]&pre2[y]).count()&1)+'0';
                      break;
              }
          }

          printf("%s",ans);

          return 0;
      }
      ```

### 与树分块结合

`bitset` 与树分块结合可以解决一类求树上多条路径信息并的问题，详见 [OI Wiki/数据结构/树分块](/ds/tree-decompose/)。

### 计算高维偏序

详见 [FHR课件](https://github.com/OI-wiki/libs/blob/master/ds/stl/FHR-分块bitset求高维偏序.pdf)。
