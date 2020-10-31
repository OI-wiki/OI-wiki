author: Ir1d, partychicken, ouuan, Marcythm, TianyiQ

## 概述

前置知识：[随机函数](../misc/random.md)和[概率初步](../math/expectation.md)

本页面将对 OI/ICPC 中的随机化技巧做一个简单的分类，并对每个分类予以介绍。本文也将介绍一些在 OI/ICPC 中尚未广泛使用，但与 OI/ICPC 在风格等方面十分贴近的技巧，这些内容前将用 `*` 标注。

这一分类并不代表广泛共识，或许也并不能囊括所有可能性，因此仅供参考。

## 随机化用于非完美算法

随机化被广泛应用于 OI 中各种骗分、偷懒的场景下。在这种场景下，随机化的作用通常包括：
- 防止被出题人用针对性数据卡掉。例如在搜索时随机打乱邻居的顺序。
- 保证算法过程中进行的“操作”具有（某种意义上的）均匀性。例如 [模拟退火](../misc/simulated-annealing.md) 算法。

### 例：[「TJOI2015」线性代数](https://loj.ac/problem/2100) 

本题的标准算法是网络流，但这里我们采取这样的做法：
- 每次随机一个位置，把这个位置取反，判断大小并更新答案。

??? note "代码"
    ```cpp
    #include <algorithm>
    #include <cstdlib>
    #include <iostream>

    int n;

    int a[510], b[510], c[510][510], d[510];
    int p[510], q[510];

    int maxans = 0;

    void check() {
      memset(d, 0, sizeof d);
      int nowans = 0;
      for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) d[i] += a[j] * c[i][j];
      for (int i = 1; i <= n; i++) nowans += (d[i] - b[i]) * a[i];
      maxans = std::max(maxans, nowans);
    }

    int main() {
      srand(19260817);
      std::cin >> n;
      for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) std::cin >> c[i][j];
      for (int i = 1; i <= n; i++) std::cin >> b[i];
      for (int i = 1; i <= n; i++) a[i] = 1;
      check();
      for (int T = 1000; T; T--) {
        int tmp = rand() % n + 1;
        a[tmp] ^= 1;
        check();
      }
      std::cout << maxans << '\n';
    }
    ```

### 例：用随机化实现可并堆

可并堆最常用的写法应该是左偏树了，通过维护树高让树左偏来保证合并的复杂度。然而维护树高有点麻烦，我们希望尽量避开。

那么可以考虑使用极其难卡的随机堆，即不按照树高来交换儿子，而是随机交换。

??? note "代码"
    ```cpp
    struct Node {
      int child[2];
      long long val;
    } nd[100010];
    int root[100010];

    int merge(int u, int v) {
      if (!(u && v)) return u | v;
      int x = rand() & 1, p = nd[u].val > nd[v].val ? u : v;
      nd[p].child[x] = merge(nd[p].child[x], u + v - p);
      return p;
    }

    void pop(int &now) { now = merge(nd[now].child[0], nd[now].child[1]); }
    ```

## 与随机性有关的结论证明

这一类应用可以细分为两种：
1. **类型一**：利用某些技巧来帮助分析本就具有随机性的对象。
2. **(\*)类型二**：在确定性的问题中人为引入随机性，从而帮助分析。

其中，类型二也叫做「[概率方法](https://en.wikipedia.org/wiki/Probabilistic_method)」，是组合数学中的一类重要方法。

限于篇幅和笔者的垃圾水平，本文中只能举几个例子以对这两种方法略窥一斑。

### 例（类型一）：随机图的连通性

阅读这一例子前，建议先阅读 [概率 & 期望](../math/expectation.md) 以了解随机变量、独立性等概率论的基础概念。

求证：对于 $n \in \mathbf{N}^*; p,q\in (0,1)$ 且 $p\leq q$ ，求证随机图 $G_1(n,p)$ 的连通分量个数的期望值不超过 $G_2(n,q)$ 的连通分量个数的期望值。这里 $G(n,\alpha)$ 表示一张 $n$ 个结点的简单无向图 $G$ ，其中 $\frac {n(n-1)}2$ 条可能的边中的每一条都有 $\alpha$ 的概率出现，且这些概率互相独立。

这个结论看起来再自然不过，但严格证明却并不那么容易。

??? note "证明的大致思路"
    我们假想这两张图分别使用了一个 01 随机数生成器来获知每条边存在与否，其中 $G_1$ 的生成器 $T_1$ 每次以 $p$ 的概率输出 1 ，$G_2$ 的生成器 $T_2$ 每次以 $q$ 的概率输出 1 。这样，要构造一张图，就只需把对应的生成器运行 $\frac {n(n-1)}2$ 遍即可。
    现在我们把两个生成器合二为一。考虑随机数生成器 $T$ ，每次以 $q$ 的概率输出 0 ，以 $p-q$ 的概率输出 1 ，以 $1-p$ 的概率输出 2 。如果我们将这个 $T$ 运行 $\frac {n(n-1)}2$ 遍，就能同时构造出 $G_1$ 和 $G_2$ 。具体地说，如果输出是 0 ，则认为 $G_1$ 和 $G_2$ 中都没有当前考虑的边；如果输出是 1 ，则认为只有 $G_1$ 中有当前考虑的边；如果输出是 2 ，则认为 $G_1$ 和 $G_2$ 中都有当前考虑的边。
    容易验证，这样生成的 $G_1$ 和 $G_2$ 符合其定义，而且在每个实例中，$G_2$ 的边集都是 $G_1$ 边集的子集。因此在每个实例中，$G_2$ 的连通分量个数都不小于 $G_1$ 的连通分量个数；那么期望值自然也满足同样的大小关系。

这一段证明中用到的技巧被称为“耦合”。本例中它体现为把两个本来独立的“随机数生成器”合二为一。