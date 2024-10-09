author: ShwStone

前置知识：[可持久化 01-trie](./persistent-trie.md)，[Succinct Indexable Dictionaries](./succinct-indexable-dictionaries.md)。

Wavelet Matrix 是一种简洁数据结构，在 $\mathcal O(\log W)$ 的时间内能完成任意序列的 $\operatorname{access},\operatorname{rank},\operatorname{select}$ 操作。对于这三种操作的定义，请参阅 [简洁数据结构简介](./succinct-data-structure.md)。

同时，在竞赛中，Wavelet Matrix 还可以在 $\mathcal O(\log W)$ 的时间内完成静态区间第 $k$ 大，区间排名查询，区间出现次数，区间第 $k$ 次出现等询问，在许多情况下可以当作持久化权值线段树（主席树）或持久化 01 trie 的小常数替代品。

静态的 Wavelet Matrix 使用 Succinct Indexable Dictionaries 维护信息以实现 $o(n)$ 的额外空间占用。如果使用平衡树代替 Succinct Indexable Dictionaries，则可以在单次 $\mathcal O(\log W \log n)$ 复杂度支持动态的单点修改和区间询问。

由于比较小众，没有一个公认的中文名。不过其英文名 Wavelet 来自于 Wavelet Tree 结构与离散小波变换过程的相似性，所以可以称 Wavelet Matrix 为小波矩阵，称 Wavelet Tree 为小波树。

本文将先介绍 Wavelet Matrix 的原型 Wavelet Tree，再介绍作为简洁数据结构的 Wavelet Matrix，最后给出它在竞赛中的应用。若未说明，本文默认涉及序列的长度是 $n$，元素大小最大为 $W$。

## Wavelet Tree

### 结构

Wavelet Tree 是 Wavelet Matrix 的原型。其基础结构是一个 01 trie，在每个节点上，用一个 Succinct Indexable Dictionaries 维护下一位的 01 情况。

以根节点为例，Wavelet Tree 维护一个 01 序列 $b$，其中 $b_i$ 是 $a_i$ 的最高二进制位。接下来，$a$ 按照最高位分成两个子列 $a_0,a_1$，最高位为 0 的子列 $a_0$ 进入左儿子，最高位为 1 的子列 $a_1$ 进入右儿子。

递归地，左儿子维护 01 序列 $b_0$，其中 $b_{0i}$ 是 $a_{0i}$ 的次高位；右儿子维护 01 序列 $b_1$，其中 $b_{1i}$ 是 $a_{1i}$ 的次高位。

递归完成 01 trie 的结构，整个结构就是一颗 Wavelet Tree。

下面是一个示意图：

![](./images/wavelet-matrix-1.png)

字符串只是为了帮助理解。实际上 Wavelet Tree 不存储真实数据，只存储 Succinct Indexable Dictionaries。

### 下标转移

Wavelet Tree 的一个最基本的操作是：如果节点 $a$ 的第 $i$ 位是 $c$，那么该元素在子节点 $a_c$ 里面对应的下标是多少？

我们记这个操作为 $\operatorname{id}_c(a, i)$。不难发现这个值就是 $a$ 的前缀 $[1,i]$ 中最高位是 $c$ 的元素数。也即 $\operatorname{id}_c(a, i) = \operatorname{rank}_{c}(b, i)$。

以前文的图为例。$\operatorname{id}_\text{a}(a, 7) = 4$，因为 $a_7$ 及以前 $\{\text{a}, \text{b}\}$ 出现了 4 个，则在 $[1,7]$ 内的 $\{\text{a},\text{b}\}$ 是前 4 个 $\{\text{a},\text{b}\}$。

### $\operatorname{access}$

对于查询 $\operatorname{access}(a, i)$，Wavelet Tree 要做的是确定第 $i$ 位在 Trie 结构上的对应树链。

通过查询 $c = \operatorname{access}(b,i)$，可以知道 $a_i$ 的最高位是 $c$。则 $\operatorname{access}(a, i)$ 转移到 $\operatorname{access}(a_c, \operatorname{id}_c(a, i))$。

递归到叶节点返回即可。

### $\operatorname{rank}$

对于询问 $\operatorname{rank}_w(a, i)$，我们首先考察 $w$ 的最高位。如果最高位是 $c$，那么所有的 $w$ 都出现在 $a_c$ 里，而 $a_{1-c}$ 中不会含有 $w$。

则有 $\operatorname{rank}_w(a, i) = \operatorname{rank}_{w}(a_c, \operatorname{id}_c(a, i))$。

当转移到达叶子节点时，$a_{\text{leaf}}$ 的所有元素都是 $w$，则 $\operatorname{rank}_w(a_\text{leaf}, i_{\text{leaf}}) = i_\text{leaf}$。

### $\operatorname{select}$

对于询问 $\operatorname{select}_w(a, k)$，考虑 $w$ 的最高位 $c$，那么第 $k$ 个 $w$ 在 $c$ 儿子中排第 $k' = \operatorname{select}_{w}(a_c, k)$ 位。则 $c$ 儿子的第 $k'$ 位在当前节点排 $\operatorname{select}_c(b, k')$。

所以 $\operatorname{select}_w(a, k) = \operatorname{select}_c(b, \operatorname{select}_{w}(a_c, k))$。

在叶节点上，$\operatorname{select}_w(a_\text{leaf}, k_{\text{leaf}}) = k_\text{leaf}$。

如果使用 $\mathcal O(1)$ 实现的 $\operatorname{select}_c(b, k')$，时间复杂度是 $\mathcal O(\log W)$。

### 实现

由于 Wavelet Matrix 是 Wavelet Tree 的上位替代，此处不给出代码实现。

## Wavelet Matrix

### 结构

Wavelet Matrix 的主要思想是将 Wavelet Tree 的同一层的所有位向量按照一定顺序拼成一个长度为 $n$ 的位向量一起存储，这样只剩下 $\log W$ 个长为 $n$ 的位向量，无需维护 01-trie 的结构。所有位向量组成一个 $\log W \times n$ 的矩阵，也是名字中 Matrix 的来历。

具体的顺序如下：按照那一层对应的二进制位进行稳定排序，位为 1 的放在 0 的前面，但是二进制位相同的不改变顺序。

以前三层为例：在构建时，最高层对应原来的根节点，存储最高位的 01 串 $b$。

然后 $\{b\}$ 分裂成 $\{b_0, b_1\}$，再按照最高位进行稳定排序，得到 $\{b_1, b_0\}$，这就是次高层，存储次高位的 01 串。

随后，$\{b_1, b_0\}$ 分裂成 $\{b_{10}, b_{11}, b_{00}, b_{01}\}$，再按照次高位进行稳定排序，得到 $\{b_{11}, b_{01}, b_{10}, b_{00}\}$。（仔细思考为什么是这个顺序，是在次高层顺序基础上排序，所以 $b_{11}$ 排在 $b_{01}$ 前面）这就是第三层，里面存储第三高位的 01 串。

在下面，重新定义符号 $a_i, b_i$ 表示第 $i$ 层的原始数据和第 $i$ 层的位向量。

实现上，构造第 $i$ 层时，将原始数据按照上一层稳定排序（`std::stable_sort`），然后取第 $i$ 位作为第 $i$ 层存储的内容。$a_i$ 按照第 $i$ 高位进行排序之后，在第 $i$ 层的同一节点内的元素按照第 $i$ 高位自动分开，完成了第 $i$ 层到第 $i+1$ 层的划分。

特别注意，下面提到的「最后一层」对应 Wavelet Tree 中的叶子节点，实际不存储任何信息。

### 下标转移

定义 Wavelet Matrix 上的 $\operatorname{id}_c(a_j, i)$ 为第 $j$ 层第 $i$ 个元素（第 $i$ 位是 $c$）在第 $j+1$ 层的位置。

-   当 $c=1$ 时，稳定排序后排在 $i$ 之前的元素只有 $[1, i]$ 之内的 1。则 $\operatorname{id}_1(a_j, i) = \operatorname{rank}_1(b_j, i)$。
-   当 $c=0$ 时，稳定排序后排在 $i$ 之前的元素既包括 $[1, i]$ 之内的 0, 则 $\operatorname{id}_0(a_j, i) = \operatorname{rank}_1(b_j, n) + \operatorname{rank}_0(b_j, i)$。

为了方便描述，我们定义 $\operatorname{di}_c(a_j, i)$ 操作为 $\operatorname{id}$ 操作的逆运算，即对于第 $j + 1$ 层的第 $i$ 个元素（第 $i$ 位是 $c$）对应的第 $j$ 层的位置：

-   当 $c=1$ 时，第 $i$ 个元素是第 $j$ 层中的第 $i$ 个 1。则 $\operatorname{di}_1(a_j, i) = \operatorname{select}_1(b_j, i)$。
-   当 $c=0$ 时，第 $i$ 个元素是第 $j$ 层中的第 $i-\operatorname{rank}_1(b_j, n)$ 个 0。则 $\operatorname{di}_0(a_j, i) = \operatorname{select}_0(b_j, i - \operatorname{rank}_1(b_j, n))$。

当确定如何转移之后，算法思路和 Wavelet Tree 一致。不过由于 $\operatorname{id}$ 的含义已经从节点内部序号变成了层内序号，所以上述算法的答案计算过程也要有所修改。

### $\operatorname{access}$

对于查询 $\operatorname{access}(a_j, i)$，通过查询 $c = \operatorname{access}(b_j,i)$，可以知道 $(a_j)_i$ 的第 $j$ 高位是 $c$。则 $\operatorname{access}(a_j, i)$ 转移到 $\operatorname{access}(a_{j+1}, \operatorname{id}_c(a_j, i))$。

### $\operatorname{rank}$

如果按照 Wavelet Tree 中的实现，在到最后一层时，由于不知道叶子节点有多大，无法给出答案。所以 $\operatorname{rank}$ 操作需要给出对应的 Wavelet Tree 上的起点。进一步地，不难发现，如果给出节点的起点可做，那么给出任意点作为左端点也可做，这实际上是一个任意区间都可解决的查询。

定义 $\operatorname{rank}_w(a_j, l, r)$ 表示 $w$ 在序列 $a_j$ 的区间 $[l, r]$ 中的出现次数。考察 $w$ 的第 $j$ 高位 $c$，则有 $\operatorname{rank}_w(a_j, l, r) = \operatorname{rank}_{w}(a_{j+1}, \operatorname{id}_c(a_j, l - 1) + 1, \operatorname{id}_c(a_j, r))$。

当转移到达最后一层时，$[l, r]$ 内的所有元素都是 $w$，则 $\operatorname{rank}_w(a_\text{end}, l_{\text{end}}, r_{\text{end}}) = r_\text{end} - l_\text{end} + 1$。

### $\operatorname{select}$

同样地，如果按照 Wavelet Tree 中的实现，在最后一层无法知道第 $k$ 个元素对应的层序号。同样需要维护当前节点的起点。进一步地，如果给出节点的起点可做，那么给出任意点作为左端点也可做。这实际解决了从某一点开始第 $k$ 次出现 $w$ 的询问。

定义 $\operatorname{select}_w(a_j, l, k)$ 表示 $w$ 从序列 $a_j$ 的第 $l$ 位开始第 $k$ 次出现的位置。设 $w$ 的第 $j$ 位为 $c$。

第 $k$ 个 $w$ 在下一层排第 $k' = \operatorname{select}_{w}(a_{j+1}, \operatorname{id}_c(a_j, l), k)$ 位。则下一层的第 $k'$ 位在这一层排 $\operatorname{di}_c(a_j,  k')$。

所以 $\operatorname{select}_w(a_j, l, k) = \operatorname{di}_c(a_j, \operatorname{select}_{w}(a_{j + 1}, \operatorname{id}_c(a_j, l), k))$。在最后一层上，$\operatorname{select}_w(a_\text{end}, l_\text{end}, k) = l_\text{end} + k - 1$。

如果使用 $\mathcal O(1)$ 实现的 $\operatorname{select}_c(b_j, k')$，时间复杂度是 $\mathcal O(\log W)$。

### 实现

上述递归都是尾递归，代码采用循环实现。

??? note "Wavelet Matrix 模板"
    ```cpp
    struct WaveletMatrix {
      vector<Bits> b;
      int n;
    
      // 注意 a 将被修改
      WaveletMatrix(int n, int *a) {
        this->n = n;
        b.resize(32, Bits(n));
        for (int j = 31; j >= 0; j--) {
          for (int i = 1; i <= n; i++)
            if ((a[i] >> j) & 1) b[j].set(i);
          b[j].prepare();
          stable_partition(a + 1, a + n + 1, [&](int x) { return (x >> j) & 1; });
        }
      }
    
      int id(int j, int c, int i) {
        return c ? b[j].rank1(i) : b[j].rank0(i) + b[j].rank1(n);
      }
    
      int di(int j, int c, int i) {
        return c ? b[j].select1(i) : b[j].select0(i - b[j].rank1(n));
      }
    
      int access(int i) {
        int res = 0;
        for (int j = 31; j >= 0; j--) {
          int c = b[j].access(i);
          res |= (c << j);
          i = id(j, c, i);
        }
        return res;
      }
    
      int rank(int l, int r, int w) {
        for (int j = 31; j >= 0; j--) {
          l = id(j, (w >> j) & 1, l - 1) + 1;
          r = id(j, (w >> j) & 1, r);
        }
        return r - l + 1;
      }
    
      int select(int w, int l, int k) {
        for (int j = 31; j >= 0; j--) {
          l = id(j, (w >> j) & 1, l - 1) + 1;
        }
        int res = l + k - 1;
        for (int j = 0; j < 32; j++) {
          res = di(j, (w >> j) & 1, res);
        }
        return res;
      }
    };
    ```

## 竞赛常用操作

上面的基础操作展示了 Wavelet Matrix 的核心思想：类似 01-trie 的结构和 Succinct Indexable Dictionaries 带来的区间转移能力。相当于 Wavelet Matrix 能够提取序列的某个区间，并在这个区间对应的 01-trie 上进行查询。

这个能力恰好就是可持久化 01-trie 对应的能力之一。因此，对于区间查询问题，Wavelet Matrix 在稍加修改之后就可以完成多数可持久化 01-trie 能够完成的查询，并且有完胜 01-trie 的常数和空间。

下面列举一些常见操作的实现：

### 区间出现次数

将 $\operatorname{rank}$ 前缀相减即可。为了下面表述简单，记 $\operatorname{rank}_w(a, l, r) = \operatorname{rank}_w(a, r) - \operatorname{rank}_w(a, l - 1)$。

### 区间求排名

定义 $\operatorname{ranking}_w(a_j, l, r)$ 表示序列 $a_j$ 区间 $[l, r]$ 内 $w$ 的排名（严格小于 $w$ 的数的个数加一）。设 $w$ 的第 $j$ 高位为 $c$。

若 $c=1$，则 $\operatorname{ranking}_w(a_j, l, r) = \operatorname{rank}_0(b_j, l, r) + \operatorname{ranking}_w(a_{j+1}, \operatorname{id}_1(a_j, l - 1) + 1, \operatorname{id}_1(a_j, r))$。

若 $c=0$，则 $\operatorname{ranking}_w(a_j, l, r) = \operatorname{ranking}_w(a_{j+1}, \operatorname{id}_0(a_j, l - 1) + 1, \operatorname{id}_0(a_j, r))$。

对于最后一层，$\operatorname{ranking}_w(a_\text{end}, l_\text{end}, r_\text{end}) = 1$。

### 区间第 k 小

定义 $\operatorname{kth}(a_j, l, r, k)$ 为序列 $a_j$ 区间 $[l,r]$ 内排名为 $k$ 的元素。

若 $\operatorname{rank}_0(b_j, l, r) \ge k$，则答案第 $j$ 位为 0，问题转移到 $\operatorname{kth}(a_{j+1}, \operatorname{id}_0(a_j, l - 1) + 1, \operatorname{id}_0(a_j, r), k)$。

否则答案第 $j$ 位为 1，问题转移到 $\operatorname{kth}(a_{j+1}, \operatorname{id}_1(a_j, l - 1) + 1, \operatorname{id}_1(a_j, r), k - \operatorname{rank}_0(b_j, l, r))$。

递归至最后一层返回即可。

## 例题

### 例题 1

???+ note "[Luogu P3834【模板】可持久化线段树 2](https://www.luogu.com.cn/problem/P3834)"
    静态查询区间第 $k$ 小。$n, q \le 2 \times 10^5$。

这是区间第 $k$ 小的模板题。用上面给出的算法即可。

??? "参考代码"
    ```cpp
    --8<-- "docs/ds/code/wavelet-matrix/wavelet-matrix_1.cpp"
    ```

### 例题 2

???+ note "[Luogu P1972 \[SDOI2009\] HH 的项链](https://www.luogu.com.cn/problem/P1972)"
    静态查询区间本质不同的数的个数。$n, q \le 10^6$。

首先预处理出 $nxt_i$ 表示下一个与 $a_i$ 相等的数的位置。查询就是问 $[l, r]$ 内有多少数满足 $nxt_i > r$。这等价于在 $nxt$ 数组上静态询问 $r$ 的区间排名。用上面给出的算法即可。

??? "参考代码"
    ```cpp
    --8<-- "docs/ds/code/wavelet-matrix/wavelet-matrix_2.cpp"
    ```

## 动态操作

如果使用平衡树来维护位向量，就可以实现位向量的插入和删除。进而实现 Wavelet Matrix 的插入和删除。每个操作的时间复杂度都增加到 $\mathcal O(\log W \log n)$。

## 参考资料

-   Claude, Francisco, and Gonzalo Navarro. "The wavelet matrix." International Symposium on String Processing and Information Retrieval. Berlin, Heidelberg: Springer Berlin Heidelberg, 2012.
