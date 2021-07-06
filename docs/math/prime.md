我们说，如果存在一个整数 $k$，使得 $a = kd$，则称 $d$ 整除 $a$，记做 $d \mid a$，称 $a$ 是 $d$ 的倍数，如果 $d > 0$，称 $d$ 是 $a$ 的约数。特别地，任何整数都整除 $0$。

显然大于 $1$ 的正整数 $a$ 可以被 $1$ 和 $a$ 整除，如果除此之外 $a$ 没有其他的约数，则称 $a$ 是素数，又称质数。任何一个大于 $1$ 的整数如果不是素数，也就是有其他约数，就称为是合数。$1$ 既不是合数也不是素数。

素数计数函数：小于或等于 $x$ 的素数的个数，用 $\pi(x)$ 表示。随着 $x$ 的增大，有这样的近似结果：$\pi(x) \sim \frac{x}{\ln(x)}$

## 素数判定

我们自然地会想到，如何用计算机来判断一个数是不是素数呢？

### 暴力做法

自然可以枚举从小到大的每个数看是否能整除

```cpp
bool isPrime(a) {
  if (a < 2) return 0;
  for (int i = 2; i < a; ++i)
    if (a % i == 0) return 0;
  return 1;
}
```

这样做是十分稳妥了，但是真的有必要每个数都去判断吗？

很容易发现这样一个事实：如果 $x$ 是 $a$ 的约数，那么 $\frac{a}{x}$ 也是 $a$ 的约数。

这个结论告诉我们，对于每一对 $(x, \frac{a}{x} )$，只需要检验其中的一个就好了。为了方便起见，我们之考察每一对里面小的那个数。不难发现，所有这些较小数就是 $[1, \sqrt{a}]$ 这个区间里的数。

由于 $1$ 肯定是约数，所以不检验它。

```cpp
bool isPrime(a) {
  if (a < 2) return 0;
  for (int i = 2; i * i <= a; ++i)
    if (a % i == 0) return 0;
  return 1;
}
```

### Miller-Rabin 素性测试

Miller-Rabin 素性测试（Miller–Rabin primality test）是进阶的素数判定方法。
对数 n 进行 k 轮测试的时间复杂度是 $O(k \log^3n)$，利用 FFT 等技术可以优化到 [$O(k \log^2n \log \log n \log \log \log n)$](https://en.wikipedia.org/wiki/Miller%E2%80%93Rabin_primality_test#Complexity)。

#### Fermat 素性测试

我们可以根据 [费马小定理](./fermat.md#_1) 得出一种检验素数的思路：

它的基本思想是不断地选取在 $[2, n-1]$ 中的基 $a$，并检验是否每次都有 $a^{n-1} \equiv 1 \pmod n$

```cpp
bool millerRabin(int n) {
  if (n < 3) return n == 2;
  // test_time 为测试次数,建议设为不小于 8
  // 的整数以保证正确率,但也不宜过大,否则会影响效率
  for (int i = 1; i <= test_time; ++i) {
    int a = rand() % (n - 2) + 2;
    if (quickPow(a, n - 1, n) != 1) return 0;
  }
  return 1;
}
```

很遗憾，费马小定理的逆定理并不成立，换言之，满足了 $a^{n-1} \equiv 1 \pmod n$，$n$ 也不一定是素数。

#### 卡迈克尔数

上面的做法中随机地选择 $a$，很大程度地降低了犯错的概率。但是仍有一类数，上面的做法并不能准确地判断。

对于合数 $n$，如果对于所有正整数 $a$，$a$ 和 $n$ 互素，都有同余式 $a^{n-1} \equiv 1 \pmod n$ 成立，则合数 $n$ 为卡迈克尔数（Carmichael Number），又称为费马伪素数。

比如，$561 = 3 \times 11 \times 17$ 就是一个卡迈克尔数。

而且我们知道，若 $n$ 为卡迈克尔数，则 $m=2^{n}-1$ 也是一个卡迈克尔数，从而卡迈克尔数的个数是无穷的。[（OEIS:A006931）](https://oeis.org/A006931)

#### 二次探测定理

如果 $p$ 是奇素数，则 $x^2 \equiv 1 \pmod p$ 的解为 $x \equiv 1 \pmod p$ 或者 $x \equiv p - 1 \pmod p$。

要证明该定理，只需将上面的方程移项，再使用平方差公式，得到 $(x+1)(x-1) \equiv 0 \bmod p$，即可得出上面的结论。

#### 实现

根据卡迈克尔数的性质，可知其一定不是 $p^e$。

不妨将费马小定理和二次探测定理结合起来使用：

将 $a^{n-1} \equiv 1 \pmod n$ 中的指数 $n−1$ 分解为 $n−1=u \times 2^t$，在每轮测试中对随机出来的 $a$ 先求出 $a^{u} \pmod n$，之后对这个值执行最多 $t$ 次平方操作，若发现非平凡平方根时即可判断出其不是素数，否则通过此轮测试。

比较正确的 Miller Rabin：（来自 fjzzq2002）

```cpp
bool millerRabbin(int n) {
  if (n < 3) return n == 2;
  int a = n - 1, b = 0;
  while (a % 2 == 0) a /= 2, ++b;
  // test_time 为测试次数,建议设为不小于 8
  // 的整数以保证正确率,但也不宜过大,否则会影响效率
  for (int i = 1, j; i <= test_time; ++i) {
    int x = rand() % (n - 2) + 2, v = quickPow(x, a, n);
    if (v == 1 || v == n - 1) continue;
    for (j = 0; j < b; ++j) {
      v = (long long)v * v % n;
      if (v == n - 1) break;
    }
    if (j >= b) return 0;
  }
  return 1;
}
```

### 参考

<http://www.matrix67.com/blog/archives/234>

<https://blog.bill.moe/miller-rabin-notes/>

## 反素数

### 定义

如果某个正整数 $n$ 满足如下条件，则称为是反素数：
  任何小于 $n$ 的正数的约数个数都小于 $n$ 的约数个数

注：注意区分 [emirp](https://en.wikipedia.org/wiki/Emirp)，它是用来表示从后向前写读是素数的数。

### 简介

（本段转载自 [桃酱的算法笔记](https://zhuanlan.zhihu.com/c_1005817911142838272)，原文戳 [链接](https://zhuanlan.zhihu.com/p/41759808)，已获得作者授权）

其实顾名思义，素数就是因子只有两个的数，那么反素数，就是因子最多的数（并且因子个数相同的时候值最小），所以反素数是相对于一个集合来说的。

我所理解的反素数定义就是，在一个集合中，因素最多并且值最小的数，就是反素数。

那么，如何来求解反素数呢？

首先，既然要求因子数，我首先想到的就是素因子分解。把 $n$ 分解成 $n=p_{1}^{k_{1}}p_{2}^{k_{2}} \cdots p_{n}^{k_{n}}$ 的形式，其中 $p$ 是素数，$k$ 为他的指数。这样的话总因子个数就是 $(k_1+1) \times (k_2+1) \times (k_3+1) \cdots \times (k_n+1)$。

但是显然质因子分解的复杂度是很高的，并且前一个数的结果不能被后面利用。所以要换个方法。

我们来观察一下反素数的特点。

1. 反素数肯定是从 $2$ 开始的连续素数的幂次形式的乘积。

2. 数值小的素数的幂次大于等于数值大的素数，即 $n=p_{1}^{k_{1}}p_{2}^{k_{2}} \cdots p_{n}^{k_{n}}$ 中，有 $k_1 \geq k_2 \geq k_3 \geq \cdots \geq k_n$

解释：

1. 如果不是从 $2$ 开始的连续素数，那么如果幂次不变，把素数变成数值更小的素数，那么此时因子个数不变，但是 $n$ 的数值变小了。交换到从 $2$ 开始的连续素数的时候 $n$ 值最小。

2. 如果数值小的素数的幂次小于数值大的素数的幂，那么如果把这两个素数交换位置（幂次不变），那么所得的 $n$ 因子数量不变，但是 $n$ 的值变小。

另外还有两个问题，

1.  对于给定的 $n$，要枚举到哪一个素数呢？

    最极端的情况大不了就是 $n=p_{1}p_{2} \cdots p_{n}$，所以只要连续素数连乘到刚好小于等于 $n$ 就可以的呢。再大了，连全都一次幂，都用不了，当然就是用不到的啦！

2.  我们要枚举到多少次幂呢？

    我们考虑一个极端情况，当我们最小的素数的某个幂次已经比所给的 $n$（的最大值）大的话，那么展开成其他的形式，最大幂次一定小于这个幂次。unsigned long long 的最大值是 2 的 64 次方，所以我这边习惯展开成 2 的 64 次方。

细节有了，那么我们具体如何具体实现呢？

我们可以把当前走到每一个素数前面的时候列举成一棵树的根节点，然后一层层的去找。找到什么时候停止呢？

1. 当前走到的数字已经大于我们想要的数字了

2. 当前枚举的因子已经用不到了（和 $1$ 重复了嘻嘻嘻）

3. 当前因子大于我们想要的因子了

4. 当前因子正好是我们想要的因子（此时判断是否需要更新最小 $ans$）

然后 dfs 里面不断一层一层枚举次数继续往下迭代就好啦\~~

### 常见题型

#### 求因子数一定的最小数

题目链接：<https://codeforces.com/problemset/problem/27/E>

对于这种题，我们只要以因子数为 dfs 的返回条件基准，不断更新找到的最小值就可以了

上代码：

```cpp
#include <stdio.h>
#define ULL unsigned long long
#define INF ~0ULL
ULL p[16] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53};

ULL ans;
ULL n;

// depth: 当前在枚举第几个素数。num: 当前因子数。
// temp: 当前因子数量为 num
// 的时候的数值。up：上一个素数的幂，这次应该小于等于这个幂次嘛
void dfs(ULL depth, ULL temp, ULL num, ULL up) {
  if (num > n || depth >= 16) return;
  if (num == n && ans > temp) {
    ans = temp;
    return;
  }
  for (int i = 1; i <= up; i++) {
    if (temp / p[depth] > ans) break;
    dfs(depth + 1, temp = temp * p[depth], num * (i + 1), i);
  }
}

int main() {
  while (scanf("%llu", &n) != EOF) {
    ans = INF;
    dfs(0, 1, 1, 64);
    printf("%llu\n", ans);
  }
  return 0;
}
```

#### 求 n 以内因子数最多的数

<https://zoj.pintia.cn/problem-sets/91827364500/problems/91827366061>

思路同上，只不过要改改 dfs 的返回条件。注意这样的题目的数据范围，我一开始用了 int，应该是溢出了，在循环里可能就出不来了就超时了。上代码，0ms 过。注释就没必要写了上面写的很清楚了。

```cpp
#include <cstdio>
#include <iostream>
#define ULL unsigned long long

int p[16] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53};
ULL n;
ULL ans, ans_num;  // ans 为 n 以内的最大反素数（会持续更新），ans_sum 为 ans
                   // 的因子数。

void dfs(int depth, ULL temp, ULL num, int up) {
  if (depth >= 16 || temp > n) return;
  if (num > ans_num) {
    ans = temp;
    ans_num = num;
  }
  if (num == ans_num && ans > temp) ans = temp;
  for (int i = 1; i <= up; i++) {
    if (temp * p[depth] > n) break;
    dfs(depth + 1, temp *= p[depth], num * (i + 1), i);
  }
  return;
}

int main() {
  while (scanf("%llu", &n) != EOF) {
    ans_num = 0;
    dfs(0, 1, 1, 60);
    printf("%llu\n", ans);
  }
  return 0;
}
```
