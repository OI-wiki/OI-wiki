## 简介

RMQ 是英文 Range Maximum/Minimum Query 的缩写，表示区间最大（最小）值。

在笔者接下来的描述中，默认初始数组大小为 $n$。

在笔者接下来的描述中，默认时间复杂度标记方式为 $O($ 数据预处理 $) \sim O($ 单次询问 $)$。

## 单调栈

由于 **OI Wiki** 中已有此部分的描述，本文仅给出 [链接](../ds/monotonous-stack.md)。这部分不再展开。

时间复杂度 $O(m\log m) \sim O(\log n)$

空间复杂度 $O(n)$

## ST 表

由于 **OI Wiki** 中已有此部分的描述，本文仅给出 [链接](../ds/sparse-table.md)。这部分不再展开。

时间复杂度 $O(n\log n) \sim O(1)$

空间复杂度 $O(n\log n)$

## 线段树

由于 **OI Wiki** 中已有此部分的描述，本文仅给出 [链接](../ds/seg.md)。这部分不再展开。

时间复杂度 $O(n) \sim O(\log n)$

空间复杂度 $O(n)$

## Four Russian

Four russian 是一个由四位俄罗斯籍的计算机科学家提出来的基于 ST 表的算法。

在 ST 表的基础上 Four russian 算法对其做出的改进是序列分块。

具体来说，我们将原数组——我们将其称之为数组 A——每 $S$ 个分成一块，总共 $n/S$ 块。

对于每一块我们预处理出来块内元素的最小值，建立一个长度为 $n/S$ 的数组 B，并对数组 B 采用 ST 表的方式预处理。

同时，我们对于数组 A 的每一个零散块也建立一个 ST 表。

询问的时候，我们可以将询问区间划分为不超过 1 个数组 B 上的连续块区间和不超过 2 个数组 A 上的整块内的连续区间。显然这些问题我们通过 ST 表上的区间查询解决。

在 $S=\log n$ 时候，预处理复杂度达到最优，为 $O((n / \log n)\log n+(n / \log n)\times\log n\times\log \log n)=O(n\log \log n)$。

时间复杂度 $O(n\log \log n) \sim O(1)$

空间复杂度 $O(n\log \log n)$

当然询问由于要跑三个 ST 表，该实现方法的常数较大。

!!! note "一些小小的算法改进"
    我们发现，在询问的两个端点在数组 A 中属于不同的块的时候，数组 A 中块内的询问是关于每一块前缀或者后缀的询问。
    
    显然这些询问可以通过预处理答案在 $O(n)$ 的时间复杂度内被解决。
    
    这样子我们只需要在询问的时候进行至多一次 ST 表上的查询操作了。

!!! note "一些玄学的算法改进"
    由于 Four russian 算法以 ST 表为基础，而算法竞赛一般没有非常高的时间复杂度要求，所以 Four russian 算法一般都可以被 ST 表代替，在算法竞赛中并不实用。这里提供一种在算法竞赛中更加实用的 Four russian 改进算法。
    
    我们将块大小设为 $\sqrt n$，然后预处理出每一块内前缀和后缀的 RMQ，再暴力预处理出任意连续的整块之间的 RMQ，时间复杂度为 $O(n)$。
    
    查询时，对于左右端点不在同一块内的询问，我们可以直接 $O(1)$ 得到左端点所在块的后缀 RMQ，左端点和右端点之间的连续整块 RMQ，和右端点所在块的前缀 RMQ，答案即为三者之间的最值。
    
    而对于左右端点在同一块内的询问，我们可以暴力求出两点之间的 RMQ，时间复杂度为 $O(\sqrt n)$，但是单个询问的左右端点在同一块内的期望为 $O(\frac{\sqrt n}{n})$，所以这种方法的时间复杂度为期望 $O(n)$。
    
    而在算法竞赛中，我们并不用非常担心出题人卡掉这种算法，因为我们可以通过在 $\sqrt n$ 的基础上随机微调块大小，很大程度上避免算法在根据特定块大小构造的数据中出现最坏情况。并且如果出题人想要卡掉这种方法，则暴力有可能可以通过。
    
    这是一种期望时间复杂度达到下界，并且代码实现难度和算法常数均较小的算法，因此在算法竞赛中比较实用。
    
    以上做法参考了 [P3793 由乃救爷爷](https://www.luogu.com.cn/problem/P3793) 中的题解。

## 加减 1RMQ

若序列满足相邻两元素相差为 1，在这个序列上做 RMQ 可以成为加减 1RMQ，根究这个特性可以改进 Four Russian 算法，做到 $O(n) \sim O(1)$ 的时间复杂度，$O(n)$ 的空间复杂度。

由于 Four russian 算法的瓶颈在于块内 RMQ 问题，我们重点去讨论块内 RMQ 问题的优化。

由于相邻两个数字的差值为 $\pm 1$，所以在固定左端点数字时 长度不超过 $\log n$ 的右侧序列种类数为 $\sum_{i=1}^{i \leq \log n} 2^{i-1}$，而这个式子显然不超过 $n$。

这启示我们可以预处理所有不超过 $n$ 种情况的 最小值 - 第一个元素 的值。

在预处理的时候我们需要去预处理同一块内相邻两个数字之间的差，并且使用二进制将其表示出来。

在询问的时候我们找到询问区间对应的二进制表示，查表得出答案。

这样子 Four russian 预处理的时间复杂度就被优化到了 $O(n)$。

## 笛卡尔树在 RMQ 上的应用

不了解笛卡尔树的朋友请移步 [笛卡尔树](../ds/cartesian-tree.md)。

不难发现，原序列上两个点之间的 min/max，等于笛卡尔树上两个点的 LCA 的权值。根据这一点就可以借助 $O(n) \sim O(1)$ 求解树上两个点之间的 LCA 进而求解 RMQ。$O(n) \sim O(1)$ 树上 LCA 在 [LCA - 标准 RMQ](../graph/lca.md#rmq_1) 已经有描述，这里不再展开。

总结一下，笛卡尔树在 RMQ 上的应用，就是通过将普通 RMQ 问题转化为 LCA 问题，进而转化为加减 1 RMQ 问题进行求解，时间复杂度为 $O(n) \sim O(1)$。当然由于转化步数较多，$O(n) \sim O(1)$ RMQ 常数较大。

如果数据随机，还可以暴力在笛卡尔树上查找。此时的时间复杂度为期望 $O(n) \sim O(\log n)$，并且实际使用时这种算法的常数往往很小。

### 例题 [Luogu P3865【模板】ST 表](https://www.luogu.com.cn/problem/P3865)

??? note "参考代码"
    ```cpp
    // Copyright (C) 2018 Skqliao. All rights served.
    #include <bits/stdc++.h>
    
    #define rep(i, l, r) for (int i = (l), _##i##_ = (r); i < _##i##_; ++i)
    #define rof(i, l, r) for (int i = (l)-1, _##i##_ = (r); i >= _##i##_; --i)
    #define ALL(x) (x).begin(), (x).end()
    #define SZ(x) static_cast<int>((x).size())
    typedef long long ll;
    typedef std::pair<int, int> pii;
    template <typename T>
    inline bool chkMin(T &a, const T &b) {
      return a > b ? a = b, 1 : 0;
    }
    template <typename T>
    inline bool chkMax(T &a, const T &b) {
      return a < b ? a = b, 1 : 0;
    }
    
    const int MAXN = 1e5 + 5;
    
    struct PlusMinusOneRMQ {
      const static int M = 8;
      int blocklen, block, Minv[MAXN], F[MAXN / M * 2 + 5][M << 1], T[MAXN],
          f[1 << M][M][M], S[MAXN];
      void init(int n) {
        blocklen = std::max(1, (int)(log(n * 1.0) / log(2.0)) / 2);
        block = n / blocklen + (n % blocklen > 0);
        int total = 1 << (blocklen - 1);
        for (int i = 0; i < total; i++) {
          for (int l = 0; l < blocklen; l++) {
            f[i][l][l] = l;
            int now = 0, minv = 0;
            for (int r = l + 1; r < blocklen; r++) {
              f[i][l][r] = f[i][l][r - 1];
              if ((1 << (r - 1)) & i) {
                now++;
              } else {
                now--;
                if (now < minv) {
                  minv = now;
                  f[i][l][r] = r;
                }
              }
            }
          }
        }
        T[1] = 0;
        for (int i = 2; i < MAXN; i++) {
          T[i] = T[i - 1];
          if (!(i & (i - 1))) {
            T[i]++;
          }
        }
      }
      void initmin(int a[], int n) {
        for (int i = 0; i < n; i++) {
          if (i % blocklen == 0) {
            Minv[i / blocklen] = i;
            S[i / blocklen] = 0;
          } else {
            if (a[i] < a[Minv[i / blocklen]]) {
              Minv[i / blocklen] = i;
            }
            if (a[i] > a[i - 1]) {
              S[i / blocklen] |= 1 << (i % blocklen - 1);
            }
          }
        }
        for (int i = 0; i < block; i++) {
          F[i][0] = Minv[i];
        }
        for (int j = 1; (1 << j) <= block; j++) {
          for (int i = 0; i + (1 << j) - 1 < block; i++) {
            int b1 = F[i][j - 1], b2 = F[i + (1 << (j - 1))][j - 1];
            F[i][j] = a[b1] < a[b2] ? b1 : b2;
          }
        }
      }
      int querymin(int a[], int L, int R) {
        int idl = L / blocklen, idr = R / blocklen;
        if (idl == idr)
          return idl * blocklen + f[S[idl]][L % blocklen][R % blocklen];
        else {
          int b1 = idl * blocklen + f[S[idl]][L % blocklen][blocklen - 1];
          int b2 = idr * blocklen + f[S[idr]][0][R % blocklen];
          int buf = a[b1] < a[b2] ? b1 : b2;
          int c = T[idr - idl - 1];
          if (idr - idl - 1) {
            int b1 = F[idl + 1][c];
            int b2 = F[idr - 1 - (1 << c) + 1][c];
            int b = a[b1] < a[b2] ? b1 : b2;
            return a[buf] < a[b] ? buf : b;
          }
          return buf;
        }
      }
    };
    
    struct CartesianTree {
     private:
      struct Node {
        int key, value, l, r;
        Node(int key, int value) {
          this->key = key;
          this->value = value;
          l = r = 0;
        }
        Node() {}
      };
      Node tree[MAXN];
      int sz;
      int S[MAXN], top;
    
     public:
      void build(int a[], int n) {
        top = 0;
        tree[0] = Node(-1, INT_MAX);
        S[top++] = 0;
        sz = 0;
        for (int i = 0; i < n; i++) {
          tree[++sz] = Node(i, a[i]);
          int last = 0;
          while (tree[S[top - 1]].value <= tree[sz].value) {
            last = S[top - 1];
            top--;
          }
          tree[sz].l = last;
          tree[S[top - 1]].r = sz;
          S[top++] = sz;
        }
      }
      Node &operator[](const int x) { return tree[x]; }
    };
    
    class stdRMQ {
     public:
      void work(int a[], int n) {
        ct.build(a, n);
        dfs_clock = 0;
        dfs(0, 0);
        rmq.init(dfs_clock);
        rmq.initmin(depseq, dfs_clock);
      }
      int query(int L, int R) {
        int cl = clk[L], cr = clk[R];
        if (cl > cr) {
          std::swap(cl, cr);
        }
        return Val[rmq.querymin(depseq, cl, cr)];
      }
    
     private:
      CartesianTree ct;
      PlusMinusOneRMQ rmq;
      int dfs_clock, clk[MAXN], Val[MAXN << 1], depseq[MAXN << 1];
      void dfs(int rt, int d) {
        clk[ct[rt].key] = dfs_clock;
        depseq[dfs_clock] = d;
        Val[dfs_clock++] = ct[rt].value;
        if (ct[rt].l) {
          dfs(ct[rt].l, d + 1);
          depseq[dfs_clock] = d;
          Val[dfs_clock++] = ct[rt].value;
        }
        if (ct[rt].r) {
          dfs(ct[rt].r, d + 1);
          depseq[dfs_clock] = d;
          Val[dfs_clock++] = ct[rt].value;
        }
      }
    } doit;
    
    int A[MAXN];
    
    int main() {
      int n, m, l, r;
      scanf("%d%d", &n, &m);
      for (int i = 0; i < n; ++i) {
        scanf("%d", &A[i]);
      }
      doit.work(A, n);
      while (m--) {
        scanf("%d%d", &l, &r);
        printf("%d\n", doit.query(l - 1, r - 1));
      }
      return 0;
    }
    ```
