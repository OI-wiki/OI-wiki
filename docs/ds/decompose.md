author: Ir1d, HeRaNO, Xeonacid

## 简介

其实，分块是一种思想，而不是一种数据结构。

从 NOIP 到 NOI 到 IOI，各种难度的分块思想都有出现。

分块的基本思想是，通过对原数据的适当划分，并在划分后的每一个块上预处理部分信息，从而较一般的暴力算法取得更优的时间复杂度。

分块的时间复杂度主要取决于分块的块长，一般可以通过均值不等式求出某个问题下的最优块长，以及相应的时间复杂度。

分块是一种很灵活的思想，相较于树状数组和线段树，分块的优点是通用性更好，可以维护很多树状数组和线段树无法维护的信息。

当然，分块的缺点是渐进意义的复杂度，相较于线段树和树状数组不够好。

不过在大多数问题上，分块仍然是解决这些问题的一个不错选择。

下面是几个例子。

## 区间和

??? "例题 [LibreOJ 6280 数列分块入门 4](https://loj.ac/problem/6280)"
    给定一个长度为 $n$ 的序列 $\{a_i\}$ ，需要执行 $n$ 次操作。操作分为两种：
    
    1. 给 $a_l \sim a_r$ 之间的所有数加上 $x$ ；
    2.  求 $\sum_{i=l}^r a_i$ 。
    
         $1 \leq n \leq 5 \times 10^4$ 

我们将序列按每 $s$ 个元素一块进行分块，并记录每块的区间和 $b_i$ 。

$$
\underbrace{a_1, a_2, \ldots, a_s}_{b_1}, \underbrace{a_{s+1}, \ldots, a_{2s}}_{b_2}, \dots, \underbrace{a_{(s-1) \times s+1}, \dots, a_n}_{b_{\frac{n}{s}}}
$$

最后一个块可能是不完整的（因为 $n$ 很可能不是 $s$ 的倍数），但是这对于我们的讨论来说并没有太大影响。

首先看查询操作：

- 若 $l$ 和 $r$ 在同一个块内，直接暴力求和即可，因为块长为 $s$ ，因此最坏复杂度为 $O(s)$ 。
- 若 $l$ 和 $r$ 不在同一个块内，则答案由三部分组成：以 $l$ 开头的不完整块，中间几个完整块，以 $r$ 结尾的不完整块。对于不完整的块，仍然采用上面暴力计算的方法，对于完整块，则直接利用已经求出的 $b_i$ 求和即可。这种情况下，最坏复杂度为 $O(\dfrac{n}{s}+s)$ 。

接下来是修改操作：

- 若 $l$ 和 $r$ 在同一个块内，直接暴力修改即可，因为块长为 $s$ ，因此最坏复杂度为 $O(s)$ 。
- 若 $l$ 和 $r$ 不在同一个块内，则需要修改三部分：以 $l$ 开头的不完整块，中间几个完整块，以 $r$ 结尾的不完整块。对于不完整的块，仍然是暴力修改每个元素的值（别忘了更新区间和 $b_i$ ），对于完整块，则直接修改 $b_i$ 即可。这种情况下，最坏复杂度和仍然为 $O(\dfrac{n}{s}+s)$ 。

利用均值不等式可知，当 $\dfrac{n}{s}=s$ ，即 $s=\sqrt n$ 时，单次操作的时间复杂度最优，为 $O(\sqrt n)$ 。

??? note "参考代码"
    ```cpp
    #include <cmath>
    #include <iostream>
    using namespace std;
    int id[50005], len;
    long long a[50005], b[50005], s[50005];
    void add(int l, int r, long long x) {
      int sid = id[l], eid = id[r];
      if (sid == eid) {
        for (int i = l; i <= r; i++) a[i] += x, s[sid] += x;
        return;
      }
      for (int i = l; id[i] == sid; i++) a[i] += x, s[sid] += x;
      for (int i = sid + 1; i < eid; i++) b[i] += x, s[i] += len * x;
      for (int i = r; id[i] == eid; i--) a[i] += x, s[eid] += x;
    }
    long long query(int l, int r, long long p) {
      int sid = id[l], eid = id[r];
      long long ans = 0;
      if (sid == eid) {
        for (int i = l; i <= r; i++) ans = (ans + a[i] + b[sid]) % p;
        return ans;
      }
      for (int i = l; id[i] == sid; i++) ans = (ans + a[i] + b[sid]) % p;
      for (int i = sid + 1; i < eid; i++) ans = (ans + s[i]) % p;
      for (int i = r; id[i] == eid; i--) ans = (ans + a[i] + b[eid]) % p;
      return ans;
    }
    int main() {
      int n;
      cin >> n;
      len = sqrt(n);
      for (int i = 1; i <= n; i++) {
        cin >> a[i];
        id[i] = (i - 1) / len + 1;
        s[id[i]] += a[i];
      }
      for (int i = 1; i <= n; i++) {
        int op, l, r, c;
        cin >> op >> l >> r >> c;
        if (op == 0)
          add(l, r, c);
        else
          cout << query(l, r, c + 1) << endl;
      }
      return 0;
    }
    ```

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

### 其他问题

分块思想也可以应用于其他整数相关问题：寻找零元素的数量、寻找第一个非零元素、计算满足某个性质的元素个数等等。

还有一些问题可以通过分块来解决，例如维护一组允许添加或删除数字的集合，检查一个数是否属于这个集合，以及查找第 $k$ 大的数。要解决这个问题，必须将数字按递增顺序存储，并分割成多个块，每个块中包含 $\sqrt{n}$ 个数字。每次添加或删除一个数字时，必须通过在相邻块的边界移动数字来重新分块。

一种很有名的离线算法 [莫队算法](../misc/mo-algo.md) ，也是基于分块思想实现的。

## 练习题

-  [UVA - 12003 - Array Transformer](https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=3154) 
-  [UVA - 11990 Dynamic Inversion](https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=3141) 
-  [SPOJ - Give Away](http://www.spoj.com/problems/GIVEAWAY/) 
-  [Codeforces - Till I Collapse](http://codeforces.com/contest/786/problem/C) 
-  [Codeforces - Destiny](http://codeforces.com/contest/840/problem/D) 
-  [Codeforces - Holes](http://codeforces.com/contest/13/problem/E) 
-  [Codeforces - XOR and Favorite Number](https://codeforces.com/problemset/problem/617/E) 
-  [Codeforces - Powerful array](http://codeforces.com/problemset/problem/86/D) 
-    [SPOJ - DQUERY](https://www.spoj.com/problems/DQUERY) 

     **本页面主要译自博文 [Sqrt-декомпозиция](http://e-maxx.ru/algo/sqrt_decomposition) 与其英文翻译版 [Sqrt Decomposition](https://cp-algorithms.com/data_structures/sqrt_decomposition.html) 。其中俄文版版权协议为 Public Domain + Leave a Link；英文版版权协议为 CC-BY-SA 4.0。** 
