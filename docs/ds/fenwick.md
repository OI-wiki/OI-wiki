author: HeRaNO, Zhoier, Ir1d, Xeonacid, wangdehu, ouuan, ranwen, ananbaobeichicun, Ycrpro, dbxxx-oi

## 引入

树状数组是一种支持 **单点修改** 和 **前缀查询** 的，代码量小的数据结构。

维护的信息要求满足结合律，比如 $+$ 和 $\max$。用后者举例：$\max\{\max\{a, b\}, c\} = \max\{a, b, c\}$。

对于可差分信息（例如和等），我们可将区间查询转化为前缀查询。例如对于一个数组 $a$，查询 $a[4 \cdots 7]$ 的区间和，只需求出 $a[1 \cdots 7]$ 的前缀和，以及 $a[1 \cdots 3]$ 的前缀和，再将两个和作差。

对于不可差分信息（例如最值等），我们仍可直接查询前缀信息，而对区间信息则需要一些技巧。比如使用两个树状数组可以用于处理区间最值，见 [Efficient Range Minimum Queries using Binary Indexed Trees](http://history.ioinformatics.org/oi/files/volume9.pdf#page=41)。还有一种 $\Theta(\log^2n)$ 时间复杂度，采用树状数组处理区间不可差分信息的方法，本文不做提及。对于复杂的区间问题，推荐使用线段树。

后文中的区间查询，都是默认信息可差分的情况下，用前缀查询来解决区间查询。

树状数组能解决的问题是线段树能解决的问题的子集：树状数组能做的，线段树一定能做；线段树能做的，树状数组不一定可以。

但树状数组的代码要远比线段树短，时间效率常数也更小，因此有学习价值。

树状数组主要用于处理：**单点修改区间查询**（信息可差分）的问题。

使用差分数组和辅助数组可以将树状数组应用于 **区间修改单点查询** 和 **区间修改区间查询**。

本文主要介绍树状数组在 **单点修改区间查询** 问题中的应用。

## 树状数组

### 初步感受

先来举个例子：我们想知道 $a[1 \cdots 7]$ 的前缀和，怎么做？

一种做法是：$a_1 + a_2 + a_3 + a_4 + a_5 + a_6 + a_7$，需要求 $7$ 个数的和。

那如果我告诉你三个数 $A$，$B$，$C$，$A = a[1 \cdots 4]$ 的和，$B = a[5 \cdots 6]$ 的总和，$C = a[7 \cdots 7]$ 的总和（其实就是 $a[7]$ 自己）。你会怎么算？你一定会回答：$A + B + C$，只需要求 $3$ 个数的和。

这就是树状数组能快速求解信息的原因：我们总能将一段前缀 $[1, n]$ 拆成 **不多于 $\log n$ 段区间**，使得这 $\log n$ 段区间的信息是 **已知的**。

于是，我们只需合并这 $\log n$ 段区间的信息，就可以得到答案。相比于原来直接合并 $n$ 个信息，效率有了很大的提高。

不难发现信息必须满足结合律，否则就不能像上面这样合并了。

下面这张图展示了树状数组的工作原理：

![](./images/fenwick.svg)

最下面的八个方块代表原始数据数组 $a$。上面参差不齐的方块（与最上面的八个方块是同一个数组）代表数组 $a$ 的上级——$c$ 数组。

$c$ 数组就是用来储存原始数组 $a$ 某段区间的和的，也就是说，这些区间的信息是已知的，我们的目标就是把查询前缀拆成这些小区间。

例如，从图中可以看出：

- $c_2$ 管理的是 $a[1 \cdots 2]$；
- $c_4$ 管理的是 $a[1 \cdots 4]$；
- $c_6$ 管理的是 $a[5 \cdots 6]$；
- $c_8$ 管理的是 $a[1 \cdots 8]$；
- 剩下的 $c_x$ 管理的都是 $a_x$ 自己（可以看做 $a[x \cdots x]$ 的长度为 $1$ 的小区间）。

不难发现，$c_x$ 管辖的一定是一段右边界是 $x$ 的区间总信息。我们先不关心左边界，先来感受一下树状数组是如何查询的。

举例：计算 $a[1 \cdots 7]$ 的和。

过程：从 $c_{7}$ 开始往前跳，发现 $c_{7}$ 只管理 $a_{7}$ 这个元素；然后找 $c_{6}$，发现 $c_{6}$ 管理的是 $a[5 \cdots 6]$，然后跳到 $c_{4}$，发现 $c_{4}$ 管理的是 $a[1 \cdots 4]$ 这些元素，然后再试图跳到 $c_0$，但事实上 $c_0$ 不存在，不跳了。

我们刚刚找到的 $c$ 是 $c_7, c_6, c_4$，事实上这就是 $a[1 \cdots 7]$ 拆分出的三个小区间，合并得到答案是 $c_7 + c_6 + c_4$。

那怎么计算 $a[4 \cdots 7]$ 的和呢？查询 $a[1 \cdots 7]$ 的和，以及 $a[1 \cdots 3]$ 的和，作差即可。

![](images/fenwick-query.svg)

### 管辖区间

那么问题来了，$c_{x}(x \ge 1)$ 管理的区间到底往左延伸多少？也就是说，区间长度是多少？

树状数组中，规定若 $x \bmod (2^{n})=0$，$n$ 取最大整数值，那么 $c_{x}$ 管理的区间长度为 $2^{n}$。

- $n$ 恰好为 $x$ 二进制表示中，最低位的 `1` 所在的二进制位数（设最低位是第 $0$ 位）；
- $2^n$ 恰好为 $x$ 二进制表示中，最低位的 `1` 以及后面所有 `0` 组成的数。

举个例子，$c_{88}$ 管理的是哪个区间？

因为 $88_{(10)}=01011000_{(2)}$，其二进制最低位的 `1` 以及后面的 `0` 组成的二进制是 `1000`，即 $8$，所以 $c_{88}$ 管理 $8$ 个 $a$ 数组中的元素。

因此，$c_{88}$ 代表 $a[81 \cdots 88]$ 的区间信息。

我们记 $x$ 二进制最低位 `1` 以及后面的 `0` 组成的数为 $\operatorname{lowbit}(x)$，那么 $c_{x}$ 管理的区间就是 $[x-\operatorname{lowbit}(x)+1, x]$。

这里注意：$\operatorname{lowbit}$ 指的不是最低位 `1` 所在的位数 $n$，而是这个 `1` 和后面所有 `0` 组成的 $2^n$。

怎么计算 `lowbit`？根据位运算知识，可以得到 `lowbit(x) = x & -x`。

??? note "lowbit 的原理"
    将 `x` 的二进制所有位全部取反，再加 1，就可以得到 `-x` 的二进制编码。例如，$6$ 的二进制编码是 `110`，全部取反后得到 `001`，加 `1` 得到 `010`。
    
    设原先 `x` 的二进制编码是 `...10...00`，全部取反后得到 `...01...11`，加 `1` 后得到 `...10...00`，也就是 `-x` 的二进制编码了。这里面第一个省略号后面那一位是 `x` 最低位的 `1`。
    
    观察到，`x` 和 `-x` 第一个省略号中的每一位分别相反，`&` 后第一个省略号会全变成 `0`；而最后的一串 `0` 在 `&` 之后显然还是 `0`；只有原先的最低位 `1` 同时在 `x` 和 `-x` 中保留，因此 `x & -x` 得到的结果就是 `lowbit`。

???+note "实现"
    === "C++"
    
        ```cpp
        int lowbit(int x) {
          // x 的二进制中，最低位的 1 以及后面所有 0 组成的数。
          // lowbit(0b01011000) == 0b00001000
          //          ~~~~^~~~
          // lowbit(0b01110010) == 0b00000010
          //          ~~~~~~^~
          return x & -x;
        }
        ```
    
    === "Python"
    
        ```python
        def lowbit(x):
            """
            x 的二进制中，最低位的 1 以及后面所有 0 组成的数。
            lowbit(0b01011000) == 0b00001000
                    ~~~~~^~~
            lowbit(0b01110010) == 0b00000010
                    ~~~~~~~^~
            """
            return x & -x
        ```

### 操作实现

#### 前缀查询

接下来我们来看树状数组具体的操作实现，先来看前缀查询。

回顾查询 $a[1 \cdots 7]$ 的过程：

> 从 $c_{7}$ 开始往前跳，发现 $c_{7}$ 只管理 $a_{7}$ 这个元素；然后找 $c_{6}$，发现 $c_{6}$ 管理的是 $a[5 \cdots 6]$，然后跳到 $c_{4}$，发现 $c_{4}$ 管理的是 $a[1 \cdots 4]$ 这些元素，然后再试图跳到 $c_0$，但事实上 $c_0$ 不存在，不跳了。
>
> 我们刚刚找到的 $c$ 是 $c_7, c_6, c_4$，事实上这就是 $a[1 \cdots 7]$ 拆分出的三个小区间，合并一下，答案是 $c_7 + c_6 + c_4$。

观察上面的过程，每次往前跳，一定是跳到现区间的左端点的左一位，作为新区间的右端点，这样才能将前缀不重不漏地拆分。比如上次 $c_6$ 管的是 $a[5 \cdots 6]$，下一次肯定得跳到 $5 - 1 = 4$，即访问 $c_4$。

我们可以写出查询 $a[1 \cdots x]$ 的过程：

> - 从 $c_x$ 开始往前跳，发现 $c_x$ 管理 $a[x-\operatorname{lowbit}(x)+1 \cdots x]$；
> - 令 $x \gets x - \operatorname{lowbit}(x)$，如果 $x = 0$ 说明已经跳到尽头了，终止；否则回到第一步。
> - 将跳到的 $c$ 合并。

实际实现时，我们不一定要先把 $c$ 都跳出来然后一起合并，可以边跳边合并。

比如我们要维护的信息是和，直接令初始 $\mathrm{ans} = 0$，然后每跳到一个 $c_x$ 就 $\mathrm{ans} \gets \mathrm{ans} + c_x$，最后 $\mathrm{ans}$ 就是所有合并的结果。

???+note "实现"
    === "C++"
    
        ```cpp
        int getsum(int x) {  // a[1]..a[x]的和
          int ans = 0;
          while (x >= 1) {
            ans = ans + c[x];
            x = x - lowbit(x);
          }
          return ans;
        }
        ```
    
    === "Python"
    
        ```python
        def getsum(x): # a[1]..a[x]的和
            ans = 0
            while x >= 1:
                ans = ans + c[x]
                x = x - lowbit(x)
            return ans
        ```

#### 单点修改

为方便，下面我们默认维护的信息是和，操作是单点加。

我们让 $a_x \gets a_x + k$ 之后，还需要让管辖 $a_x$ 的所有 $c_y$ 也自增 $k$。

哪些 $c_y$ 管辖了 $a_x$ 呢？可以证明，设：

$$
p(i) = \begin{cases}x &i = 0\\p(i - 1) + \operatorname{lowbit}(p(i - 1)) & i > 0\\\end{cases}
$$

有且只有 $c[p(0)], c[p(1)], \cdots$ 覆盖 $a_x$。

实际上 $p$ 是一个单调递增的序列，根据上面的迭代式，我们只需要初始让 $x' = x$，不断重复先修改 $c[x']$，再将 $x' \gets x' + \operatorname{lowbit}(x')$ 的过程，直到 $x' >n$，即超过整个序列的长度时停止。

??? note "仅有以 $p(i)$ 作为下标的 $c$ 管辖 $a[x]$ 的证明"
    注：网上几乎所有关于这一点都是在树状数组的示例图上“感性理解”证明的。这里给出一个比较简单的严谨证明。
    
    约定：
    
    设 $l(x)$ 表示 $x - \operatorname{lowbit}(x) + 1$；
    
    对于任意正整数 $x$，总能将 $x$ 表示成 $s \times 2^{k + 1} + 2^k$ 的形式，其中 $\operatorname{lowbit}(x) = 2^k$。
    
    **引理 $1$（管辖的传递性）：对于 $\boldsymbol{1 \le x \le y \le z}$，若 $\boldsymbol{c[y]}$ 管辖 $\boldsymbol{a[x]}$，$\boldsymbol{c[z]}$ 管辖 $\boldsymbol{a[y]}$，则 $\boldsymbol{c[z]}$ 管辖 $\boldsymbol{a[x]}$。**
    
    证明：因为 $c[z]$ 管辖 $a[y]$，所以 $l(z) \le y \le z$，设 $z = s \times 2^{k + 1} + 2^k$，则 $l(z) = s \times 2^{k+1} + 1$。
    
    因此，可以将 $y$ 表示成 $s \times 2^{k + 1} + b$ 的形式，其中 $1 \le b \le 2^k$。
    
    所以，$\operatorname{lowbit}(y) = \operatorname{lowbit}(b)$。又因为 $b - \operatorname{lowbit}(b) \ge 0$，
    
    所以 $l(y) = y - \operatorname{lowbit}(y) + 1 = s \times 2^{k +1} + b - \operatorname{lowbit}(b) +1 \ge s \times 2^{k +1} + 1 = l(z)$。
    
    所以 $l(z) \le l(y) \le y \le z$。
    
    因此 $c[y]$ 所管辖的区间是 $c[z]$ 所管辖区间的子集，$c[y]$ 管辖 $a[x]$ 则 $c[z]$ 管辖 $a[x]$。
    
    **引理 $2$：$\boldsymbol{c[x + \operatorname{lowbit}(x)]}$ 管辖 $\boldsymbol{a[x]}$。**
    
    证明：设 $y = x + \operatorname{lowbit}(x)$，$x = s \times 2^{k + 1} + 2^k$。则 $y = (s + 1) \times 2^{k +1}$。
    
    不难发现 $\operatorname{lowbit}(y) \ge 2^{k + 1} > \operatorname{lowbit}(x)$，所以 $\operatorname{lowbit}(x) - \operatorname{lowbit}(y) + 1 \le 0$。
    
    因此 $l(y) = y - \operatorname{lowbit}(y) + 1 = x + \operatorname{lowbit}(x) - \operatorname{lowbit}(y) + 1 \le x$。所以 $l(y) \le x \le y$，$c[y]$ 管辖 $a[x]$。
    
    **引理 $3$：对于任意 $\boldsymbol{x < y < x + \operatorname{lowbit}(x)}$，$\boldsymbol{c[y]}$ 不管辖 $\boldsymbol{a[x]}$。**
    
    证明：设 $x = s \times 2^{k + 1} + 2^k$，则 $y = s \times 2^{k + 1} + 2^k + b$，其中 $1 \le b < 2^k$。
    
    不难发现 $\operatorname{lowbit}(y) = \operatorname{lowbit}(b) < \operatorname{lowbit}(x)$，所以 $\operatorname{lowbit}(x) - \operatorname{lowbit}(y) + 1 > 0$。
    
    因此 $l(y) = y - \operatorname{lowbit}(y) + 1 = x + \operatorname{lowbit}(x) - \operatorname{lowbit}(y) + 1 > x$。所以 $c[y]$ 不管辖 $a[x]$。
    
    **命题 $1$：$\boldsymbol{c[p(i)]}$ 一定管辖 $\boldsymbol{a[x]}$。**
    
    归纳证明：$c[p(0)]$ 显然管辖 $a[x]$。
    
    设 $c[p(i)]$ 管辖 $a[x]$，根据引理 $2$，有 $c[p(i + 1)]$ 管辖 $c[p(i)]$，根据引理 $1$（管辖的传递性），$c[p(i + 1)]$ 管辖 $a[x]$。
    
    **命题 $2$：不在 $\boldsymbol{p}$ 中的任意 $\boldsymbol{y}$ 都有 $\boldsymbol{c[y]}$ 不管辖 $\boldsymbol{a[x]}$。**
    
    如果 $y < p(0) = x$，显然 $c[y]$ 不管辖 $a[x]$；
    
    如果 $p(i) < y < p(i + 1)$，根据引理 $3$，有 $c[y]$ 不管辖 $a[p(i)]$，$l(y) > p(i)$。因为 $p(i) \ge x$，所以 $l(y) > x$，$c[y]$ 不管辖 $a[x]$。

???+note "实现"
    === "C++"
    
        ```cpp
        void add(int x, int k) {
          while (x <= n) {  // 不能越界
            c[x] = c[x] + k;
            x = x + lowbit(x);
          }
        }
        ```
    
    === "Python"
    
        ```python
        def add(x, k):
            while x <= n: # 不能越界
                c[x] = c[x] + k
                x = x + lowbit(x)
        ```

#### 建树

也就是根据最开始给出的序列，将树状数组建出来（$c$ 全部预处理好）。

一般可以直接转化为 $n$ 次单点修改，时间复杂度 $\Theta(n \log n)$（复杂度分析在后面）。

比如给定序列 $a = (5, 1, 4)$ 要求建树，直接看作对 $a[1]$ 单点加 $5$，对 $a[2]$ 单点加 $1$，对 $a[3]$ 单点加 $4$ 即可。

也有 $\Theta(n)$ 的建树方法，见 `Tricks` 一节。

### 复杂度分析

空间复杂度显然 $\Theta(n)$。

时间复杂度：

- 对于前缀查询操作：整个 $x \gets x - \operatorname{lowbit}(x)$ 的迭代过程，可以看做将 $x$ 二进制中的所有 $1$，从低位到高位逐渐改成 $0$ 的过程，拆分出的区间不会超过 $x$ 二进制中 $1$ 的数量，因此，单次查询时间复杂度是 $\Theta(\log n)$；
- 对于单点修改操作：$p(i)$ 到 $p(i + 1)$ 的过程中，总会将 $p(i)$ 的最低位 $1$ 修改为 $0$，且更低位均保持 $0$ 不变，因此 $\operatorname{lowbit}(p(i +1)) > \operatorname{lowbit}(p(i))$。由于 $n$ 以内所有数的 $\operatorname{lowbit}$ 只有 $\log n$ 种取值，因此只会修改最多 $\log n$ 个 $c$，所以单次单点修改时间复杂度是 $\Theta(\log n)$。

## 区间加 & 区间求和

若维护序列 $a$ 的差分数组 $b$，此时我们对 $a$ 的一个前缀 $r$ 求和，即 $\sum_{i=1}^{r} a_i$，由差分数组定义得 $a_i=\sum_{j=1}^i b_j$

进行推导

???+note "证明"
    $$
    \begin{aligned}
    &\sum_{i=1}^{r} a_i\\=&\sum_{i=1}^r\sum_{j=1}^i b_j\\=&\sum_{i=1}^r b_i\times(r-i+1)
    \\=&\sum_{i=1}^r b_i\times (r+1)-\sum_{i=1}^r b_i\times i
    \end{aligned}
    $$

区间和可以用两个前缀和相减得到，因此只需要用两个树状数组分别维护 $\sum b_i$ 和 $\sum i \times b_i$，就能实现区间求和。

代码如下

???+note "实现"
    === "C++"
    
        ```cpp
        int t1[MAXN], t2[MAXN], n;
    
        inline int lowbit(int x) { return x & (-x); }
    
        void add(int k, int v) {
          int v1 = k * v;
          while (k <= n) {
            t1[k] += v, t2[k] += v1;
            k += lowbit(k);
          }
        }
    
        int getsum(int *t, int k) {
          int ret = 0;
          while (k) {
            ret += t[k];
            k -= lowbit(k);
          }
          return ret;
        }
    
        void add1(int l, int r, int v) {
          add(l, v), add(r + 1, -v);  // 将区间加差分为两个前缀加
        }
    
        long long getsum1(int l, int r) {
          return (r + 1ll) * getsum(t1, r) - 1ll * l * getsum(t1, l - 1) -
                (getsum(t2, r) - getsum(t2, l - 1));
        }
        ```
    
    === "Python"
    
        ```python
        t1 = [0] * MAXN, t2 = [0] * MAXN; n = 0
    
        def lowbit(x):
            return x & (-x)
    
        def add(k, v):
            v1 = k * v
            while k <= n:
                t1[k] = t1[k] + v; t2[k] = t2[k] + v1
                k = k + lowbit(k)
    
        def getsum(t, k):
            ret = 0
            while k:
                ret = ret + t[k]
                k = k - lowbit(k)
            return ret
    
        def add1(l, r, v):
            add(l, v)
            add(r + 1, -v)
    
        def getsum1(l, r):
            return (r) * getsum(t1, r) - l * getsum(t1, l - 1) - \
                  (getsum(t2, r) - getsum(t2, l - 1))
        ```

## Tricks

### $O(n)$ 建树

方法一：

每一个节点的值是由所有与自己直接相连的儿子的值求和得到的。因此可以倒着考虑贡献，即每次确定完儿子的值后，用自己的值更新自己的直接父亲。

???+note "实现"
    === "C++"
    
        ```cpp
        // O(n) 建树
        void init() {
          for (int i = 1; i <= n; ++i) {
            t[i] += a[i];
            int j = i + lowbit(i);
            if (j <= n) t[j] += t[i];
          }
        }
        ```
    
    === "Python"
    
        ```python
        def init():
            for i in range(1, n + 1):
                t[i] = t[i] + a[i]
                j = i + lowbit(i)
                if j <= n:
                    t[j] = t[j] + t[i]
        ```

方法二：

前面讲到 $c_i$ 表示的区间是 $[i-\operatorname{lowbit}(i)+1, i]$，那么我们可以先预处理一个 $sum$ 前缀和数组，再计算 $c$ 数组。

???+note "实现"
    === "C++"
    
        ```cpp
        void init() {
          for (int i = 1; i <= n; ++i) {
            t[i] = sum[i] - sum[i - lowbit(i)];
          }
        }
        ```
    
    === "Python"
    
        ```python
        def init():
            for i in range(1, n + 1):
                t[i] = sum[i] - sum[i-lowbit(i)]
        ```

### $O(\log n)$ 查询第 $k$ 小/大元素

#### 过程

在此处只讨论第 $k$ 小，第 $k$ 大问题可以通过简单计算转化为第 $k$ 小问题。

参考「可持久化线段树」章节中，关于求区间第 $k$ 小的思想。将所有数字看成一个可重集合，即定义数组 $a$ 表示值为 $i$ 的元素在整个序列中出现了 $a_i$ 次。找第 $k$ 小就是找到最小的 $x$ 恰好满足 $\sum_{i=1}^{x}a_i \geq k$

因此可以想到算法：如果已经找到 $x$ 满足 $\sum_{i=1}^{x}a_i < k$，考虑能不能让 $x$ 继续增加，使其仍然满足这个条件。找到最大的 $x$ 后，$x+1$ 就是所要的值。
在树状数组中，节点是根据 2 的幂划分的，每次可以扩大 2 的幂的长度。令 $sum$ 表示当前的 $x$ 所代表的前缀和，有如下算法找到最大的 $x$：

1. 求出 $depth=\left \lfloor \log_2n \right \rfloor$
2. 计算 $t=\sum_{i=x+1}^{x+2^{depth}}a_i$
3. 如果 $sum+t < k$，则此时扩展成功，将 $2^{depth}$ 累加到 $x$ 上；否则扩展失败，对 $x$ 不进行操作
4. 将 $depth$ 减 1，回到步骤 2，直至 $depth$ 为 0

#### 实现

=== "C++"

    ```cpp
    // 权值树状数组查询第k小
    int kth(int k) {
      int cnt = 0, ret = 0;
      for (int i = log2(n); ~i; --i) {      // i 与上文 depth 含义相同
        ret += 1 << i;                      // 尝试扩展
        if (ret >= n || cnt + t[ret] >= k)  // 如果扩展失败
          ret -= 1 << i;
        else
          cnt += t[ret];  // 扩展成功后 要更新之前求和的值
      }
      return ret + 1;
    }
    ```

=== "Python"

    ```python
    # 权值树状数组查询第 k 小
    def kth(k):
        cnt = 0; ret = 0
        i = log2(n) # i 与上文 depth 含义相同
        while ~i:
            ret = ret + (1 << i) # 尝试扩展
            if ret >= n or cnt + t[ret] >= k: # 如果扩展失败
                ret = ret - (1 << i)
            else:
                cnt = cnt + t[ret] # 扩展成功后 要更新之前求和的值
        return ret + 1
    ```

### 时间戳优化

#### 过程

对付多组数据很常见的技巧。如果每次输入新数据时，都暴力清空树状数组，就可能会造成超时。因此使用 $tag$ 标记，存储当前节点上次使用时间（即最近一次是被第几组数据使用）。每次操作时判断这个位置 $tag$ 中的时间和当前时间是否相同，就可以判断这个位置应该是 0 还是数组内的值。

#### 实现

=== "C++"

    ```cpp
    // 时间戳优化
    int tag[MAXN], t[MAXN], Tag;

    void reset() { ++Tag; }

    void add(int k, int v) {
      while (k <= n) {
        if (tag[k] != Tag) t[k] = 0;
        t[k] += v, tag[k] = Tag;
        k += lowbit(k);
      }
    }

    int getsum(int k) {
      int ret = 0;
      while (k) {
        if (tag[k] == Tag) ret += t[k];
        k -= lowbit(k);
      }
      return ret;
    }
    ```

=== "Python"

    ```python
    # 时间戳优化
    tag = [0] * MAXN; t = [0] * MAXN; Tag = 0
    def reset():
        Tag = Tag + 1
    def add(k, v):
        while k <= n:
            if tag[k] != Tag:
                t[k] = 0
            t[k] = t[k] + v
            tag[k] = Tag
            k = k + lowbit(k)
    def getsum(k):
        ret = 0
        while k:
            if tag[k] == Tag:
                ret = ret + t[k]
            k = k - lowbit(k)
        return ret
    ```

## 例题

- [树状数组 1：单点修改，区间查询](https://loj.ac/problem/130)
- [树状数组 2：区间修改，单点查询](https://loj.ac/problem/131)
- [树状数组 3：区间修改，区间查询](https://loj.ac/problem/132)
- [二维树状数组 1：单点修改，区间查询](https://loj.ac/problem/133)
- [二维树状数组 3：区间修改，区间查询](https://loj.ac/problem/135)
