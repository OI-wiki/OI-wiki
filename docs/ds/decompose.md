author: Ir1d, HeRaNO, Xeonacid

## 简介

其实，分块是一种思想，而不是一种数据结构。

从 NOIP 到 NOI 到 IOI，各种难度的分块思想都有出现。

通常的分块算法的复杂度带根号，或者其他奇怪的复杂度，而不是 $\log$ 。

分块是一种很灵活的思想，几乎什么都能分块，并且不难实现。

你想写出什么数据结构就有什么，缺点是渐进意义的复杂度不够好。

当然，在 $n=10^5$ 时，由于常数小，跟线段树可能差不多。

这不是建议用分块的意思，在 OI 中，可以作为一个备用方案，首选肯定是线段树等理论复杂度更小的数据结构。

以下通过几个例子来介绍～

## 区间和

动机：线段树太难写？

将序列分段，每段长度 $T$ ，那么一共有 $\frac{n}{T}$ 段。

维护每一段的区间和。

单点修改：显然。

区间询问：会涉及一些完整的段，和最多两个段的一部分。

完整段使用维护的信息，一部分暴力求。

复杂度 $O(\frac{n}{T}+T)$ 。

区间修改：同样涉及这些东西，使用打标记和暴力修改，同样的复杂度。

当 $T=\sqrt{n}$ 时，复杂度 $O(\sqrt{n})$ 。

## 区间和 2

上一个做法的复杂度是 $\Omega(1) , O(\sqrt{n})$ 。

我们在这里介绍一种 $O(\sqrt{n}) - O(1)$ 的算法。

为了 $O(1)$ 询问，我们可以维护各种前缀和。

然而在有修改的情况下，不方便维护，只能维护单个块内的前缀和。

以及整块作为一个单位的前缀和。

每次修改 $O(T+\frac{n}{T})$ 。

询问：涉及三部分，每部分都可以直接通过前缀和得到，时间复杂度 $O(1)$ 。

## 对询问分块

同样的问题，现在序列长度为 $n$ ，有 $m$ 个操作。

如果操作数量比较少，我们可以把操作记下来，在询问的时候加上这些操作的影响。

假设最多记录 $T$ 个操作，则修改 $O(1)$ ，询问 $O(T)$ 。

 $T$ 个操作之后，重新计算前缀和， $O(n)$ 。

总复杂度： $O(mT+n\frac{m}{T})$ 。

 $T=\sqrt{n}$ 时，总复杂度 $O(m \sqrt{n})$ 。

 ## 应用

 Sqrt分解允许我们在n $O(\sqrt n)$ 的时间下执行一些常规操作(求和，查找最小/最大元素，等等)，这比普通算法的 $O(n)$ 时间复杂度要快得多。

接下来，我们将描述该算法实现的最简单的一个的数据结构，然后展示如何将其一般化以解决一些其他的问题。

该数据结构可以实现以下基本功能：给定一个大小为 $n$ 的数组 $a$ ，对于任意 $l$ 和 $r$ ，在 $O(\sqrt n)$ 操作下求得 $[l,r]$ 区间和。

### 描述

sqrt分解的基本思想就是预处理。我们将数组 $a$ 分割成很多个长度约为 $\sqrt{n}$ 的块，对于每个块，我们将预先计算其中的元素的和。

为了说明方便，我们假设块的大小等于 $\sqrt n$ 上取整。即：

$$
s = \lceil \sqrt n \rceil 
$$

然后将数组 $a$ 按如下方式划分为块，并用数组 $b$ 来记录它们的元素和:

$$
 \underbrace{a[0], a[1], \dots, a[s-1]}_{\text{b[0]}}, \underbrace{a[s], \dots, a[2s-1]}_{\text{b[1]}}, \dots, \underbrace{a[(s-1) \cdot s], \dots, a[n-1]}_{\text{b[s-1]}} 
$$

最后一个块可能比其他块少几个元素(因为 $n$ 很可能不是 $s$ 的倍数)，但是这对于我们的讨论来说并没有太大影响。

同时，对于每个区块$k$，我们知道其上的元素之和 $b[k]$ :

$$ b[k] = \sum\limits_{i=k\cdot s}^{\min {(n-1,(k+1)\cdot s - 1})} a[i] $$

我们已经计算了$b[k]$ 的值(时间复杂度为 $O(n)$ )。这些值又如何帮助我们求 $[l, r]$ 的区间和呢?

注意，如果区间 $[l, r]$ 足够长，它将包含几个完整的块，对于这些块，我们可以在单个操作中找到它们中元素的总和。实际上，求 $[l, r]$ 区间的难度只位于头和尾那些只属于某一块的一部分的元素和。

因此，为了计算区间$[l, r]$上的元素和，我们只需要求出来头和尾的元素和再加上完整块的元素和即可：

$$ \sum\limits_{i=l}^r a[i] = \sum\limits_{i=l}^{(k+1) \cdot s-1} a[i] + \sum\limits_{i=k+1}^{p-1} b[i] + \sum\limits_{i=p\cdot s}^r a[i] $$

注意：当 $k = p$ ，即 $l$ 和 $r$ 属于同一区块时，不能使用该公式，其和只需要进行暴力计算即可。

这种方法允许我们显著减少操作次数，从而优化时间复杂度。实际上由于我们选择了 $s \approx \sqrt n$ ，头或者尾的大小就不超过块长度$s$，块的数量也不会超过 $s$ 。所以查找区间 $[l, r]$ 上的元素和的时间复杂度不会超过 $O(s)$ ，即 $O(\sqrt{n})$ 。

### 实现

最直接的一种实现：

```cpp
int n;
vector<int> a (n);

// 预处理
int len = (int) sqrt (n + .0) + 1; // 块的大小
vector<int> b (len);
for (int i=0; i<n; ++i)
    b[i / len] += a[i];

// 询问操作
for (;;) {
    int l, r;
    int sum = 0;
    for (int i=l; i<=r; )
        if (i % len == 0 && i + len - 1 <= r) {
            sum += b[i / len];
            i += len;
        }
        else {
            sum += a[i];
            ++i;
        }
}
```

这种实现有许多的除法操作，而除法是四则运算中最慢的。因此，我们可以计算 $l$ 和 $r$ 的区块 $c_l$ 和 $c_r$ ，并循环区块 $c_l+1 \dots c_r-1$ ，分别处理区块 $c_l$ 和 $c_r$ 中的头和尾。这种方法对应于[描述](#描述)中的最后一个公式，并使得特例变成了 $c_l = c_r$ 。

```cpp
int sum = 0;
int c_l = l / len,   c_r = r / len;
if (c_l == c_r)
    for (int i=l; i<=r; ++i)
        sum += a[i];
else {
    for (int i=l, end=(c_l+1)*len-1; i<=end; ++i)
        sum += a[i];
    for (int i=c_l+1; i<=c_r-1; ++i)
        sum += b[i];
    for (int i=c_r*len; i<=r; ++i)
        sum += a[i];
}
```

### 其他问题

到目前为止，我们只讨论了求区间和的问题。这个问题可以扩展为单点更新数组中一个元素。如果一个元素 $a[i]$ 发生了变化，那么在一次操作中，更新该元素所属块的 $b[k]$ 的值就足够了( $k = i / s$ ):

$$ b[k] += a_{new}[i] - a_{old}[i] $$

Sqrt分解也可以用类似的方式应用于其他整数相关问题: 寻找零元素的数量、寻找第一个非零元素、计算满足某个性质的元素个数等等。

例如，我们可以对数组执行两种类型的操作:在区间 $[l, r]$ 上给每个元素加上 $\delta$ ，以及查询元素 $a[i]$ 的值。

先初始化所有 $b[k] = 0$ ，我们只需要在 $b[k]$ 中加上所需要增加的值。在每个“添加”操作中，需要使属于区间 $[l, r]$ 的所有块都增加 $\delta$ ，并将使区间 $[l, r]$ 的头和尾的所有元素都加上 $\delta$ 。查询新 $a[i]$ 的值的答案就是 $a[i] + b[i/s]$ 。这样，“添加”这一操作的复杂度为 $O(\sqrt{n})$ ，而查询的复杂度为 $O(1)$ 。

最后，如果任务需要同时进行元素更新和查询，那么可以将这两类问题结合起来。这两种操作都可以通 过$O(\sqrt{n})$ 复杂性完成。这将需要两个块数组 $b$ 和 $c$ :一个用于元素更新，另一个用于查询。

还有一些问题可以通过sqrt分解来解决，例如维护一组允许添加或删除数字的集合，检查一个数是否属于这个集合，以及查找第 $k$ 大的数。要解决这个问题，必须将数字按递增顺序存储，并分割成多个块，每个块中包含 $\sqrt{n}$ 个数字。每次添加或删除一个数字时，必须通过在相邻块的边界移动数字来重新分块。

一种很有名的离线算法[莫队算法](../misc/mo-algo.md)，也是基于sqrt分解的思想来实现的。

## 练习题

* [UVA - 12003 - Array Transformer](https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=3154)
* [UVA - 11990 Dynamic Inversion](https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=3141)
* [SPOJ - Give Away](http://www.spoj.com/problems/GIVEAWAY/)
* [Codeforces - Till I Collapse](http://codeforces.com/contest/786/problem/C)
* [Codeforces - Destiny](http://codeforces.com/contest/840/problem/D)
* [Codeforces - Holes](http://codeforces.com/contest/13/problem/E)
* [Codeforces - XOR and Favorite Number](https://codeforces.com/problemset/problem/617/E)
* [Codeforces - Powerful array](http://codeforces.com/problemset/problem/86/D)
* [SPOJ - DQUERY](https://www.spoj.com/problems/DQUERY)

**本页面主要译自博文[Sqrt-декомпозиция](http://e-maxx.ru/algo/sqrt_decomposition)与其英文翻译版[Sqrt Decomposition](https://cp-algorithms.com/data_structures/sqrt_decomposition.html)。其中俄文版版权协议为 Public Domain + Leave a Link；英文版版权协议为 CC-BY-SA 4.0。**
