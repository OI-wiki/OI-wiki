author: HeRaNO, Zhoier, Ir1d, Xeonacid, wangdehu, ouuan, ranwen, ananbaobeichicun, Ycrpro, dbxxx-oi

## 引入

树状数组是一种支持 **单点修改** 和 **前缀查询** 的，代码量小的数据结构。

??? note "什么是「单点修改」和「前缀查询」？"
    假设有这样一道题：
    
    已知一个数列 $a$，你需要进行下面两种操作：
    
    - 给定 $x, y$，将 $a[x]$ 自增 $y$。
    
    - 给定 $x$，求解 $a[1 \cdots x]$ 的和。
    
    其中第一种操作就是「单点修改」，第二种操作就是「前缀查询」。
    
    类似地，还有：「区间修改」、「区间查询」、「单点查询」。它们分别的一个例子如下：
    
    - 区间修改：给定 $l, r, x$，将 $a[l \cdots r]$ 中的每个数都分别自增 $x$；
    - 区间查询：给定 $l, r$，求解 $a[l \cdots r]$ 的和；
    - 单点查询：给定 $x$，求解 $a[x]$ 的值。
    
    注意到，区间问题一般严格强于单点问题，因为对单点的操作相当于对一个长度为 $1$ 的区间操作。

维护的信息要求满足结合律，比如 $+$ 和 $\max$。用后者举例：$\max\{\max\{a, b\}, c\} = \max\{a, b, c\}$。

对于可差分信息（例如和等），我们可将区间查询转化为前缀查询。例如对于一个数组 $a$，查询 $a[4 \cdots 7]$ 的区间和，只需求出 $a[1 \cdots 7]$ 的前缀和，以及 $a[1 \cdots 3]$ 的前缀和，再将两个和作差。

对于不可差分信息（例如最值等），我们仍可直接查询前缀信息，而对区间信息则需要一些技巧。比如使用两个树状数组可以用于处理区间最值，见 [Efficient Range Minimum Queries using Binary Indexed Trees](http://history.ioinformatics.org/oi/files/volume9.pdf#page=41)。本页面也会介绍一种 $\Theta(\log^2n)$ 时间复杂度解决这种问题的办法。

后文中的区间查询，都是默认信息可差分的情况下，用前缀查询来解决区间查询。

树状数组能解决的问题是线段树能解决的问题的子集：树状数组能做的，线段树一定能做；线段树能做的，树状数组不一定可以。

但树状数组的代码要远比线段树短，时间效率常数也更小，因此有学习价值。

树状数组主要用于处理：**单点修改区间查询**（信息可差分）的问题。

使用差分数组和辅助数组可以将树状数组应用于 **区间修改单点查询** 和 **区间修改区间查询**。

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

- $c_2$ 管辖的是 $a[1 \cdots 2]$；
- $c_4$ 管辖的是 $a[1 \cdots 4]$；
- $c_6$ 管辖的是 $a[5 \cdots 6]$；
- $c_8$ 管辖的是 $a[1 \cdots 8]$；
- 剩下的 $c[x]$ 管辖的都是 $a[x]$ 自己（可以看做 $a[x \cdots x]$ 的长度为 $1$ 的小区间）。

不难发现，$c[x]$ 管辖的一定是一段右边界是 $x$ 的区间总信息。我们先不关心左边界，先来感受一下树状数组是如何查询的。

举例：计算 $a[1 \cdots 7]$ 的和。

过程：从 $c_{7}$ 开始往前跳，发现 $c_{7}$ 只管辖 $a_{7}$ 这个元素；然后找 $c_{6}$，发现 $c_{6}$ 管辖的是 $a[5 \cdots 6]$，然后跳到 $c_{4}$，发现 $c_{4}$ 管辖的是 $a[1 \cdots 4]$ 这些元素，然后再试图跳到 $c_0$，但事实上 $c_0$ 不存在，不跳了。

我们刚刚找到的 $c$ 是 $c_7, c_6, c_4$，事实上这就是 $a[1 \cdots 7]$ 拆分出的三个小区间，合并得到答案是 $c_7 + c_6 + c_4$。

那怎么计算 $a[4 \cdots 7]$ 的和呢？查询 $a[1 \cdots 7]$ 的和，以及 $a[1 \cdots 3]$ 的和，作差即可。

![](images/fenwick-query.svg)

### 管辖区间

那么问题来了，$c_{x}(x \ge 1)$ 管辖的区间到底往左延伸多少？也就是说，区间长度是多少？

树状数组中，规定若 $x \bmod (2^{k})=0$，$k$ 取最大整数值，那么 $c_{x}$ 管辖的区间长度为 $2^{k}$。

- 设二进制最低位为第 $0$ 位，则 $k$ 恰好为 $x$ 二进制表示中，最低位的 `1` 所在的二进制位数；
- $2^k$ 恰好为 $x$ 二进制表示中，最低位的 `1` 以及后面所有 `0` 组成的数。

举个例子，$c_{88}$ 管辖的是哪个区间？

因为 $88_{(10)}=01011000_{(2)}$，其二进制最低位的 `1` 以及后面的 `0` 组成的二进制是 `1000`，即 $8$，所以 $c_{88}$ 管辖 $8$ 个 $a$ 数组中的元素。

因此，$c_{88}$ 代表 $a[81 \cdots 88]$ 的区间信息。

我们记 $x$ 二进制最低位 `1` 以及后面的 `0` 组成的数为 $\operatorname{lowbit}(x)$，那么 $c_{x}$ 管辖的区间就是 $[x-\operatorname{lowbit}(x)+1, x]$。

**这里注意：$\boldsymbol{\operatorname{lowbit}}$ 指的不是最低位 `1` 所在的位数 $\boldsymbol{k}$，而是这个 `1` 和后面所有 `0` 组成的 $\boldsymbol{2^k}$。**

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

### 前缀查询

接下来我们来看树状数组具体的操作实现，先来看前缀查询。

回顾查询 $a[1 \cdots 7]$ 的过程：

> 从 $c_{7}$ 往前跳，发现 $c_{7}$ 只管辖 $a_{7}$ 这个元素；然后找 $c_{6}$，发现 $c_{6}$ 管辖的是 $a[5 \cdots 6]$，然后跳到 $c_{4}$，发现 $c_{4}$ 管辖的是 $a[1 \cdots 4]$ 这些元素，然后再试图跳到 $c_0$，但事实上 $c_0$ 不存在，不跳了。
>
> 我们刚刚找到的 $c$ 是 $c_7, c_6, c_4$，事实上这就是 $a[1 \cdots 7]$ 拆分出的三个小区间，合并一下，答案是 $c_7 + c_6 + c_4$。

观察上面的过程，每次往前跳，一定是跳到现区间的左端点的左一位，作为新区间的右端点，这样才能将前缀不重不漏地拆分。比如现在 $c_6$ 管的是 $a[5 \cdots 6]$，下一次就跳到 $5 - 1 = 4$，即访问 $c_4$。

我们可以写出查询 $a[1 \cdots x]$ 的过程：

- 从 $c[x]$ 开始往前跳，有 $c[x]$ 管辖 $a[x-\operatorname{lowbit}(x)+1 \cdots x]$；
- 令 $x \gets x - \operatorname{lowbit}(x)$，如果 $x = 0$ 说明已经跳到尽头了，终止循环；否则回到第一步。
- 将跳到的 $c$ 合并。

实现时，我们不一定要先把 $c$ 都跳出来然后一起合并，可以边跳边合并。

比如我们要维护的信息是和，直接令初始 $\mathrm{ans} = 0$，然后每跳到一个 $c[x]$ 就 $\mathrm{ans} \gets \mathrm{ans} + c[x]$，最终 $\mathrm{ans}$ 就是所有合并的结果。

???+note "实现"
    === "C++"
    
        ```cpp
        int getsum(int x) {  // a[1]..a[x]的和
          int ans = 0;
          while (x > 0) {
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
            while x > 0:
                ans = ans + c[x]
                x = x - lowbit(x)
            return ans
        ```

### 树状数组与其树形态的性质

在讲解单点修改之前，先讲解树状数组的一些基本性质，以及其树形态来源，这有助于更好理解树状数组的单点修改。

我们约定：

- $l(x) = x - \operatorname{lowbit}(x) + 1$。即，$l(x)$ 是 $c[x]$ 管辖范围的左端点。
- 对于任意正整数 $x$，总能将 $x$ 表示成 $s \times 2^{k + 1} + 2^k$ 的形式，其中 $\operatorname{lowbit}(x) = 2^k$。
- 下面「$c[x]$ 和 $c[y]$ 不交」指 $c[x]$ 的管辖范围和 $c[y]$ 的管辖范围不相交，即 $[l(x), x]$ 和 $[l(y), y]$ 不相交。「$c[x]$ 包含于 $c[y]$」等表述同理。

**性质 $\boldsymbol{1}$：对于 $\boldsymbol{x \le y}$，在要么有 $\boldsymbol{c[x]}$ 和 $\boldsymbol{c[y]}$ 不交，要么有 $\boldsymbol{c[x]}$ 包含于 $\boldsymbol{c[y]}$。**

??? note "证明"
    证明：假设 $c[x]$ 和 $c[y]$ 管辖范围相交，即 $[l(x), x]$ 和 $[l(y), y]$ 相交，则一定有 $l(y) \le x \le y$。
    
    将 $y$ 表示为 $s \times 2^{k +1} + 2^k$，则 $l(y) = s \times 2^{k + 1} + 1$。所以，$x$ 可以表示为 $s \times 2^{k +1} + b$，其中 $1 \le b < 2^k$。
    
    不难发现 $\operatorname{lowbit}(x) = \operatorname{lowbit}(b)$。又因为 $b - \operatorname{lowbit}(b) \ge 0$，
    
    所以 $l(x) = x - \operatorname{lowbit}(x) + 1 = s \times 2^{k +1} + b - \operatorname{lowbit}(b) +1 \ge s \times 2^{k +1} + 1 = l(y)$，即 $l(y) \le l(x) \le x \le y$。
    
    所以，$c[x]$ 的管辖范围包含于 $c[y]$。

**性质 $\boldsymbol{2}$：在 $\boldsymbol{c[x]}$ 真包含于 $\boldsymbol{c[x + \operatorname{lowbit}(x)]}$。**

??? note "证明"
    证明：设 $y = x + \operatorname{lowbit}(x)$，$x = s \times 2^{k + 1} + 2^k$，则 $y = (s + 1) \times 2^{k +1}$，$l(x) = s \times 2^{k + 1} + 1$。
    
    不难发现 $\operatorname{lowbit}(y) \ge 2^{k + 1}$，所以 $l(y) \le s \times 2^{k +1} + 1= l(x)$，即 $l(y) \le l(x) \le x \le y$，证毕。

**性质 $3$：对于任意 $\boldsymbol{x < y < x + \operatorname{lowbit}(x)}$，有 $\boldsymbol{c[x]}$ 和 $\boldsymbol{c[y]}$ 不交。**

??? note "证明"
    证明：设 $x = s \times 2^{k + 1} + 2^k$，则 $y = s \times 2^{k + 1} + 2^k + b$，其中 $1 \le b < 2^k$。
    
    不难发现 $\operatorname{lowbit}(y) = \operatorname{lowbit}(b) < \operatorname{lowbit}(x)$，所以 $\operatorname{lowbit}(x) - \operatorname{lowbit}(y) + 1 > 0$。
    
    因此 $l(y) = y - \operatorname{lowbit}(y) + 1 = x + \operatorname{lowbit}(x) - \operatorname{lowbit}(y) + 1 > x$，即 $l(x) \le x < l(y) \le y$，证毕。

有了这三条性质的铺垫，我们接下来看树状数组的树形态（请忽略 $a$ 向 $c$ 的连边）。

![](./images/fenwick.svg)

事实上，树状数组的树形态是 $x$ 向 $x + \operatorname{lowbit}(x)$ 连边得到的图，其中 $x + \operatorname{lowbit}(x)$ 是 $x$ 的父亲。

注意，在考虑树状数组的树形态时，我们不考虑树状数组大小的影响，即我们认为这是一棵无限大的树，方便分析。实际运用时，我们只需用到 $x \le n$ 的 $c[x]$，其中 $n$ 是原数组长度。

这棵树天然满足了很多美好性质，下面列举若干比较重要的（设 $fa[u]$ 表示 $u$ 的直系父亲）：

- $u < fa[u]$。同时，$u$ 大于任何一个 $u$ 的后代。
- 点 $u$ 的 $\operatorname{lowbit}$ 严格小于 $fa[u]$ 的 $\operatorname{lowbit}$。

??? note "证明"
    设 $y = x + \operatorname{lowbit}(x)$，$x = s \times 2^{k + 1} + 2^k$，则 $y = (s + 1) \times 2^{k +1}$，不难发现 $\operatorname{lowbit}(y) \ge 2^{k + 1} > \operatorname{lowbit}(x)$，证毕。

- 我们认为 $c[1]$ 的高度是 $0$，则点 $x$ 的高度是 $\log_2\operatorname{lowbit}(x)$，即 $x$ 二进制最低位 `1` 的位数。
- $c[u]$ 真包含于 $c[fa[u]]$（性质 $2$）。
- $c[u]$ 真包含于 $c[v]$，其中 $v$ 是 $u$ 的任一祖先（在上一条性质上归纳即可）。
- $c[u]$ 真包含 $c[v]$，其中 $v$ 是 $u$ 的任一后代（上面那条性质 $u$，$v$ 颠倒）。
- 对于任意 $v' > u$，若 $v'$ 不是 $u$ 的祖先，则 $c[u]$ 和 $c[v']$ 不交。

??? note "证明"
    $u$ 和 $u$ 的祖先中，一定存在一个点 $v$ 使得 $v < v' < fa[v]$，根据性质 $3$ 得 $c[v']$ 不相交于 $c[v]$，而 $c[v]$ 包含 $c[u]$，因此 $c[v']$ 不交于 $c[u]$。

- 对于任意 $v < u$，如果 $v$ 不在 $u$ 的子树上，则 $c[u]$ 和 $c[v]$ 不交（上面那条性质 $u$，$v'$ 颠倒）。
-   设 $u = s \times 2^{k + 1} + 2^k$，则其儿子数量为 $k = \log_2\operatorname{lowbit}(x)$，编号分别为 $u - 2^t(0 \le t < k)$。
    - 举例：假设 $k = 3$，$u$ 的二进制编号为 `...1000`，则 $u$ 有三个儿子，二进制编号分别为 `...0111`、`...0110`、`...0100`。

??? note "证明"
    考虑 $u$ 的儿子 $v$，有 $v + \operatorname{lowbit}(v) = u$，即 $v = u - 2^t$ 且 $\operatorname{lowbit}(v) = 2^t$。
    
    设 $u = s \times 2^{k + 1} + 2^k$，考虑 $0 \le t < k$，$u$ 的第 $t$ 位及后方均为 $0$，所以 $v = u - 2^t$ 的第 $t$ 位变为 $1$，后面仍为 $0$，满足 $\operatorname{lowbit}(v) = 2^t$。
    
    考虑 $t = k$，则 $v = u - 2^k$，$v$ 的第 $k$ 位变为 $0$，不满足 $\operatorname{lowbit}(v) = 2^t$。
    
    考虑 $t > k$，则 $v = u - 2^t$，$v$ 的第 $k$ 位是 $1$，所以 $\operatorname{lowbit}(v) = 2^k \ne 2^t$。

-   $u$ 的所有儿子对应 $c$ 的管辖区间恰好拼接成 $[l(u), u - 1]$。
    - 举例：假设 $k = 3$，$u$ 的二进制编号为 `...1000`，则 $u$ 有三个儿子，二进制编号分别为 `...0111`、`...0110`、`...0100`。
    - `c[...0100]` 表示 `a[...0001 ~ ...0100]`。
    - `c[...0110]` 表示 `a[...0101 ~ ...0110]`。
    - `c[...0111]` 表示 `a[...0111 ~ ...0111]`。
    - 不难发现上面是三个管辖区间的并集恰好是 `a[...0001 ~ ...0111]`，即 $[l(u), u - 1]$。

??? note "证明"
    考虑 $v = u - 2^t(0 \le t < k)$，有 $\operatorname{lowbit}(v) = 2^t$。$l(v) = v - \operatorname{lowbit}(v) + 1 = u - 2^t - 2^t + 1 = u - 2^{t + 1} + 1$，所以 $c[v]$ 管辖范围是 $[u - 2^{t + 1} + 1, u - 2^t]$。
    
    不难发现，$t$ 越小，$u - 2^t$ 越大，代表的区间越靠右。而 $u - 2^t$ 的管辖右边界是 $u - 2^t$，$u - 2^{t - 1}$ 的管辖左边界是 $u - 2^t + 1$，正好可以接上。
    
    考虑最左面的儿子 $u - 2^{k - 1}$，其管辖左边界 $u - 2^k + 1$ 恰为 $l(u)$。
    
    考虑最右面的儿子 $u - 2^0 = u - 1$，其管辖右边界就是 $u - 1$。
    
    所以这些儿子可以恰好拼成 $[l(u), u - 1]$ 的区间。

### 单点修改

现在来考虑如何单点修改 $a[x]$。

我们的目标是快速正确地维护 $c$ 数组。为保证效率，我们只需修改管辖了 $a[x]$ 的所有 $c[y]$，因为其他的 $c$ 显然没有发生变化。

管辖 $a[x]$ 的 $c[y]$ 一定包含 $c[x]$（根据性质 $1$），所以 $y$ 在树状数组树形态上是 $x$ 的祖先。因此我们从 $x$ 开始跳父亲即可。

设 $n$ 表示 $a$ 的大小，不难写出单点修改 $a[x]$ 的过程：

- 初始令 $x' = x$。
- 修改 $c[x']$。
- 令 $x' \gets x' + \operatorname{lowbit}(x')$，如果 $x' > n$ 说明已经跳到尽头了，终止循环；否则回到第二步。

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

### 建树

也就是根据最开始给出的序列，将树状数组建出来（$c$ 全部预处理好）。

一般可以直接转化为 $n$ 次单点修改，时间复杂度 $\Theta(n \log n)$（复杂度分析在后面）。

比如给定序列 $a = (5, 1, 4)$ 要求建树，直接看作对 $a[1]$ 单点加 $5$，对 $a[2]$ 单点加 $1$，对 $a[3]$ 单点加 $4$ 即可。

也有 $\Theta(n)$ 的建树方法，见本页面 [$\Theta(n)$ 建树](./#on-建树) 一节。

### 复杂度分析

空间复杂度显然 $\Theta(n)$。

时间复杂度：

- 对于前缀查询操作：整个 $x \gets x - \operatorname{lowbit}(x)$ 的迭代过程，可以看做将 $x$ 二进制中的所有 $1$，从低位到高位逐渐改成 $0$ 的过程，拆分出的区间等于 $x$ 二进制中 $1$ 的数量，因此，单次查询时间复杂度是 $\Theta(\log n)$；
- 对于单点修改操作：跳父亲时，访问到的高度一直增加，且始终满足 $x \le n$。由于点 $x$ 的高度是 $\log_2\operatorname{lowbit}(x)$，所以跳到的高度不会超过 $\log_2n$，所以访问到的 $c$ 的数量是 $\log n$ 级别，单次单点修改复杂度是 $\Theta(\log n)$。

## 区间加、区间求和

区间加，求单点值可以利用差分简单转化为单点加，求区间和。这里我们直接讲一个更强的问题，区间加和区间求和。事实上，该问题使用差分和两个树状数组就可以解决。

维护序列 $a$ 的差分数组 $b$，此时我们查询 $a[1 \cdots r]$ 的和，即 $\sum_{i=1}^{r} a_i$，由差分数组定义得 $a_i=\sum_{j=1}^i b_j$。

进行推导：

$$
\begin{aligned}
&\sum_{i=1}^{r} a_i\\=&\sum_{i=1}^r\sum_{j=1}^i b_j\\=&\sum_{i=1}^r b_i\times(r-i+1)
\\=&\sum_{i=1}^r b_i\times (r+1)-\sum_{i=1}^r b_i\times i
\end{aligned}
$$

区间和可以用前缀和差分得到，因此只需要用两个树状数组分别维护 $\sum b_i$ 和 $\sum i \times b_i$，就能实现区间求和。

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

## 二维树状数组

二维树状数组，也被称作树状数组套树状数组，用来维护二维数组上的单点修改和前缀信息问题。

与一维树状数组类似，我们用 $c(x, y)$ 表示 $a(x - \operatorname{lowbit}(x) + 1, y - \operatorname{lowbit}(y) + 1) \cdots a(x, y)$ 的区间总信息，即一个以 $a(x, y)$ 为右下角，高 $\operatorname{lowbit}(x)$，宽 $\operatorname{lowbit}(y)$ 的矩阵的总信息。

对于单点修改，设：

$$
f(x, i) = \begin{cases}x &i = 0\\f(x, i - 1) + \operatorname{lowbit}(f(x, i - 1)) & i > 0\\\end{cases}
$$

则只有 $c(f(x, i), f(y, j))$ 中的元素管辖 $a(x, y)$，修改 $a(x, y)$ 时只需修改所有 $c(f(x, i) \le n, f(y, j) \le m)$ 即可。

??? note "正确性证明"
    $c(p, q)$ 管辖 $a(x, y)$，求 $p$ 和 $q$ 的取值范围。
    
    考虑一个大小为 $n$ 的一维树状数组 $c_1$（对应原数组 $a_1$）和一个大小为 $m$ 的一维树状数组 $c_2$（对应原数组 $a_2$）。
    
    则命题等价为：$c_1(p)$ 管辖 $a_1[x]$ 且 $c_2(q)$ 管辖 $a_2[y]$ 的条件。
    
    应用一维树状数组的性质，求解平凡。

对于查询，我们设：

$$
g(x, i) = \begin{cases}x &i = 0\\g(x, i - 1) - \operatorname{lowbit}(g(x, i - 1)) & i, g(x, i - 1) > 0\\0&\mathrm{otherwise.}\end{cases}
$$

则合并所有 $c(g(x, i) > 0, g(y, j) > 0)$ 即可。

下面给出单点加和查询前缀和的代码。

???+note "实现"
    === "单点加"
    
        ```cpp
        void add(int x, int y, int v) {
            for (int i = x; i <= n ;i += lowbit(i)) {
                for (int j = y; j <= m; j += lowbit(j)) {
                    // 注意这里必须得建循环变量，不能像一维数组一样直接 while (x <= n) 了
                    c[i][j] += v;
                }
            }
        }
        ```
    
    === "查询前缀和（以及区间和）"
    
        ```cpp
        int sum(int x, int y) {
          int res = 0;
          for (int i = x; i > 0; i -= lowbit(i)) {
              for (int j = y; j > 0; j -= lowbit(j)) {
                  res += c[i][j];
              }
          }
          return res;
        }
    
        int ask(int x1, int y1, int x2, int y2) {
            // 查询子矩阵和
            return sum(x2, y2) - sum(x2, y1 - 1) - sum(x1 - 1, y2) + sum(x1 - 1, y1 - 1);
        }
        ```

## 权值树状数组及应用

我们知道，普通树状数组直接在原序列的基础上构建，$c_6$ 表示的就是 $a[5 \cdots 6]$ 的区间信息。

然而事实上，我们还可以在原序列的权值数组上构建树状数组，这就是权值树状数组。

???+note "什么是权值数组？"
    一个序列 $a$ 的权值数组 $b$，满足 $b[x]$ 的值为 $x$ 在 $a$ 中的出现次数。
    
    例如：$a = (1, 3, 4, 3, 4)$ 的权值数组为 $b = (1, 0, 2, 2)$。
    
    很明显，$b$ 的大小和 $a$ 的值域有关。
    
    若原数列值域过大，且重要的不是具体值而是值与值之间的相对大小关系，常 [离散化](../../misc/discrete/) 原数组后再建立权值数组。

运用权值树状数组，我们可以解决一些经典问题。

### 单点修改，查询全局第 $k$ 小

在此处只讨论第 $k$ 小，第 $k$ 大问题可以通过简单计算转化为第 $k$ 小问题。

对于单点修改，只需将对原数列的单点修改转化为对权值数组的单点修改即可。例如：原数组 $a[x]$ 从 $y$ 修改为 $z$，转化为对权值数组 $b$ 的单点修改就是 $b[y]$ 单点减 $1$，$b[z]$ 单点加 $1$。

对于查询第 $k$ 小，考虑二分 $x$，查询权值数组中 $[1, x]$ 的前缀和，找到 $x_0$ 使得 $[1, x_0]$ 的前缀和 $< k$ 而 $[1, x_0 + 1]$ 的前缀和 $\ge k$，则第 $k$ 大的数是 $x_0 + 1$（注：这里认为 $[1, 0]$ 的前缀和是 $0$）。

这样做时间复杂度是 $\Theta(\log^2n)$ 的。

考虑用倍增替代二分。

设 $x = 0$，$\mathrm{sum} = 0$，枚举 $i$ 从 $\log_2n$ 降为 $0$：

- 查询权值数组中 $[x + 1 \cdots x + 2^i]$ 的区间和 $t$。
- 如果 $\mathrm{sum} + t < k$，扩展成功，$x \gets x + 2^i$，$\mathrm{sum} \gets \mathrm{sum} + t$；否则扩展失败，不操作。

这样得到的 $x$ 是满足 $[1 \cdots x]$ 前缀和 $< k$ 的最大值，所以最终 $x + 1$ 就是答案。

看起来这种方法时间效率没有任何改善，但事实上，查询 $[x + 1 \cdots x + 2^i]$ 的区间和只需访问 $c[x + 2^i]$ 的值即可。

原因很简单，考虑 $\operatorname{lowbit}(x + 2^i)$，它一定是 $2^i$，因为 $x$ 之前只累加过 $2^j$ 满足 $j > i$。因此 $c[x + 2^i]$ 表示的区间就是 $[x + 1 \cdots x + 2^i]$。

如此以来，时间复杂度降低为 $\Theta(\log n)$。

???+note "实现"
    === "C++"
    
        ```cpp
        // 权值树状数组查询第 k 小
        int kth(int k) {
          int sum = 0, x = 0;
          for (int i = log2(n); ~i; --i) {
            x += 1 << i;                      // 尝试扩展
            if (x >= n || sum + t[x] >= k)  // 如果扩展失败
              x -= 1 << i;
            else
              sum += t[x];
          }
          return x + 1;
        }
        ```
    
    === "Python"
    
        ```python
        # 权值树状数组查询第 k 小
        def kth(k):
            sum = 0; x = 0
            i = log2(n)
            while ~i:
                x = x + (1 << i) # 尝试扩展
                if x >= n or sum + t[x] >= k: # 如果扩展失败
                    x = x - (1 << i)
                else:
                    sum = sum + t[x]
            return x + 1
        ```

### 全局逆序对

全局逆序对也可以用权值树状数组巧妙解决。问题是这样的：给定长度为 $n$ 的序列 $a$，求 $a$ 中满足 $i < j$ 且 $a[i] > a[j]$ 的数对 $(i, j)$ 的数量。

我们考虑枚举 $i$ 从 $n$ 到 $1$，其中 $n$ 是 $a$ 的大小（该例中是 $5$），计算有多少个 $j > i$ 满足 $a[j] < a[i]$，最后累计答案即可。

事实上，我们只需要这样做（设当前 $a[i] = x$）：

- $b[x]$ 自增 $1$；
- 查询 $b[1 \cdots x - 1]$ 的前缀和，即为左端点为 $a[i]$ 的逆序对数量。

用例子说明，$a = (4, 3, 1, 2, 1)$。

$i$ 按照 $5 \to 1$ 扫：

- $a[5] = 1$，$b[1]$ 自增 $1$，$b = (1, 0, 0, 0)$，查询 $b[1 \cdots 0]$ 前缀和，为 $0$。
- $a[4] = 2$，$b[2]$ 自增 $1$，$b = (1, 1, 0, 0)$，查询 $b[1 \cdots 1]$ 前缀和，为 $1$。
- $a[3] = 1$，$b[1]$ 自增 $1$，$b = (2, 1, 0, 0)$，查询 $b[1 \cdots 0]$ 前缀和，为 $0$。
- $a[2] = 3$，$b[3]$ 自增 $1$，$b = (2, 1, 1, 0)$，查询 $b[1 \cdots 2]$ 前缀和，为 $3$。
- $a[1] = 4$，$b[4]$ 自增 $1$，$b = (2, 1, 1, 1)$，查询 $b[1 \cdots 3]$ 前缀和，为 $4$。

所以最终答案为 $0 + 1 + 0 + 3 + 4 = 8$。

## 树状数组维护区间不可差分信息

比如维护区间最值等。

注意，这种方法虽然码量小，但单点修改和区间查询的时间复杂度均为 $\Theta(\log^2n)$，比使用线段树的时间复杂度 $\Theta(\log n)$ 劣。

### 区间查询

我们还是基于之前的思路，从 $r$ 沿着 $\operatorname{lowbit}$ 一直向前跳，但是我们不能跳到 $l$ 的左边。

因此，如果我们跳到了 $c[x]$，应先判断下一次要跳到的 $x - \operatorname{lowbit}(x)$ 是否小于 $l$，如果小于，我们直接将 $a[x]$ 本身合并到总信息里，然后跳到 $c[x - 1]$ 即可；如果不小于，那么正常跳。

下面以查询区间最大值为例，给出代码：

???+note "实现"
    ```cpp
    int getmax(int l, int r) {
      int ans = 0;
      while (r >= l) {
        ans = max(ans, a[r]);
        --r;
        for (; r - lowbit(r) >= l; r -= lowbit(r)) {
          // 注意，循环条件不要写成 r - lowbit(r) + 1 >= l
          // 否则 l = 1 时，r 跳到 0 会死循环
          ans = max(ans, C[r]);
        }
      }
      return ans;
    }
    ```

可以证明，上述算法的时间复杂度是 $\Theta(\log^2n)$。

??? note "时间复杂度证明"
    考虑 $r$ 和 $l$ 不同的最高位，一定有 $r$ 在这一位上为 $1$，$l$ 在这一位上为 $0$（因为 $r \ge l$）。
    
    如果 $r$ 在这一位的后面仍然有 $1$，一定有 $r - \operatorname{lowbit}(r) \ge l$，所以下一步一定是把 $r$ 的最低位 $1$ 填为 $0$；
    
    如果 $r$ 的这一位 $1$ 就是 $r$ 的最低位 $1$，无论是 $r \gets r - \operatorname{lowbit}(r)$ 还是 $r \gets r - 1$，$r$ 的这一位 $1$ 一定会变为 $0$。
    
    因此，$r$ 经过至多 $\log n$ 次变换后，$r$ 和 $l$ 不同的最高位一定可以下降一位。所以，总时间复杂度是 $\Theta(\log^2n)$。

### 单点更新

注：请先阅读本页面中 [树状数组与其树形态的性质](./#树状数组与其树形态的性质) 一节，并掌握位于这节末尾的，树状数组树形态性质中的最后两条。

更新 $a[x]$ 后，我们只需要更新满足在树状数组树形态上，满足 $y$ 是 $x$ 的祖先的 $c[y]$。对于每一个 $c[y]$，直接用儿子的信息合并即可。

???+note "实现"
    ```cpp
    void update(int x, int v) {
      a[x] = v;
      for (int i = x; i <= n; i += lowbit(i)) {
        // 枚举受影响的区间
        C[i] = a[i];
        for (int j = 1; j < lowbit(i); j *= 2) {
          C[i] = max(C[i], C[i - j]);
        }
      }
    }
    ```

容易看出上述算法时间复杂度为 $\Theta(\log^2n)$。

### 建树

可以考虑拆成 $n$ 个单点修改，$\Theta(n\log^2n)$ 建树。

也有 $\Theta(n)$ 的建树方法，见本页面 [$\Theta(n)$ 建树](./#on-建树) 一节的方法一。

## Tricks

### $\Theta(n)$ 建树

方法一：

每一个节点的值是由所有与自己直接相连的儿子的值求和得到的。因此可以倒着考虑贡献，即每次确定完儿子的值后，用自己的值更新自己的直接父亲。

???+note "实现"
    === "C++"
    
        ```cpp
        // \Theta(n) 建树
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
        # \Theta(n) 建树
        def init():
            for i in range(1, n + 1):
                t[i] = t[i] + a[i]
                j = i + lowbit(i)
                if j <= n:
                    t[j] = t[j] + t[i]
        ```

方法二：

前面讲到 $c[i]$ 表示的区间是 $[i-\operatorname{lowbit}(i)+1, i]$，那么我们可以先预处理一个 $\mathrm{sum}$ 前缀和数组，再计算 $c$ 数组。

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

### 时间戳优化

对付多组数据很常见的技巧。若每次输入新数据都暴力清空树状数组，就可能会造成超时。因此使用 $\mathrm{tag}$ 标记，存储当前节点上次使用时间（即最近一次是被第几组数据使用）。每次操作时判断这个位置 $\mathrm{tag}$ 中的时间和当前时间是否相同，就可以判断这个位置应该是 $0$ 还是数组内的值。

???+note "实现"
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
