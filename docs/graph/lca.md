author:ouuan, Backl1ght, billchenchina, CCXXXI, ChickenHu, ChungZH, cjsoft, countercurrent-time, diauweb, Early0v0, Enter-tainer, EtaoinWu, H-J-Granger, H-Shen, Henry-ZHR, HeRaNO, hsfzLZH1, huaruoji, iamtwz, imp2002, Ir1d, kenlig, Konano, Lyccrius, Marcythm, Menci, NachtgeistW, PeterlitsZo, psz2007, shuzhouliu, SkqLiao, sshwy, SukkaW, therehello, TrisolarisHD, ttzztztz, vincent-163, WAAutoMaton, Hunter19019

## 定义

最近公共祖先简称 LCA（Lowest Common Ancestor）。两个节点的最近公共祖先，就是这两个点的公共祖先里面，离根最远的那个。
为了方便，我们记某点集 $S=\{v_1,v_2,\ldots,v_n\}$ 的最近公共祖先为 $\text{LCA}(v_1,v_2,\ldots,v_n)$ 或 $\text{LCA}(S)$。

## 性质

> 本节 **性质** 部分内容翻译自 [wcipeg](http://wcipeg.com/wiki/Lowest_common_ancestor)，并做过修改。

1.  $\text{LCA}(\{u\})=u$；
2.  $u$ 是 $v$ 的祖先，当且仅当 $\text{LCA}(u,v)=u$；
3.  如果 $u$ 不为 $v$ 的祖先并且 $v$ 不为 $u$ 的祖先，那么 $u,v$ 分别处于 $\text{LCA}(u,v)$ 的两棵不同子树中；
4.  前序遍历中，$\text{LCA}(S)$ 出现在所有 $S$ 中元素之前，后序遍历中 $\text{LCA}(S)$ 则出现在所有 $S$ 中元素之后；
5.  两点集并的最近公共祖先为两点集分别的最近公共祖先的最近公共祖先，即 $\text{LCA}(A\cup B)=\text{LCA}(\text{LCA}(A), \text{LCA}(B))$；
6.  两点的最近公共祖先必定处在树上两点间的最短路上；
7.  $d(u,v)=h(u)+h(v)-2h(\text{LCA}(u,v))$，其中 $d$ 是树上两点间的距离，$h$ 代表某点到树根的距离。

## 求法

### 朴素算法

#### 过程

可以每次找深度比较大的那个点，让它向上跳。显然在树上，这两个点最后一定会相遇，相遇的位置就是想要求的 LCA。
或者先向上调整深度较大的点，令他们深度相同，然后再共同向上跳转，最后也一定会相遇。

#### 性质

朴素算法预处理时需要 dfs 整棵树，时间复杂度为 $O(n)$，单次查询时间复杂度为 $\Theta(n)$。如果树满足某些随机性质，则时间复杂度与这种随机树的期望高度有关。

### 倍增算法

#### 过程

倍增算法是最经典的 LCA 求法，他是朴素算法的改进算法。通过预处理 $\text{fa}_{x,i}$ 数组，游标可以快速移动，大幅减少了游标跳转次数。$\text{fa}_{x,i}$ 表示点 $x$ 的第 $2^i$ 个祖先。$\text{fa}_{x,i}$ 数组可以通过 dfs 预处理出来。

现在我们看看如何优化这些跳转：
在调整游标的第一阶段中，我们要将 $u,v$ 两点跳转到同一深度。我们可以计算出 $u,v$ 两点的深度之差，设其为 $y$。通过将 $y$ 进行二进制拆分，我们将 $y$ 次游标跳转优化为「$y$ 的二进制表示所含 `1` 的个数」次游标跳转。
在第二阶段中，我们从最大的 $i$ 开始循环尝试，一直尝试到 $0$（包括 $0$），如果 $\text{fa}_{u,i}\not=\text{fa}_{v,i}$，则 $u\gets\text{fa}_{u,i},v\gets\text{fa}_{v,i}$，那么最后的 LCA 为 $\text{fa}_{u,0}$。

#### 性质

倍增算法的预处理时间复杂度为 $O(n \log n)$，单次查询时间复杂度为 $O(\log n)$。
另外倍增算法可以通过交换 `fa` 数组的两维使较小维放在前面。这样可以减少 cache miss 次数，提高程序效率。

??? 例题
    [HDU 2586 How far away?](https://vjudge.net/problem/HDU-2586) 树上最短路查询。

可先求出 LCA，再结合性质 $7$ 进行解答。也可以直接在求 LCA 时求出结果。

??? note "参考代码"
    ```cpp
    --8<-- "docs/graph/code/lca/lca_1.cpp"
    ```

### Tarjan 算法

#### 过程

`Tarjan 算法` 是一种 `离线算法`，需要使用 `并查集` 记录某个结点的祖先结点。做法如下：

1.  首先接受输入边（邻接链表）、查询边（存储在另一个邻接链表内）。查询边其实是虚拟加上去的边，为了方便，每次输入查询边的时候，将这个边及其反向边都加入到 `queryEdge` 数组里。
2.  然后对其进行一次 DFS 遍历，同时使用 `visited` 数组进行记录某个结点是否被访问过、`parent` 记录当前结点的父亲结点。
3.  其中涉及到了 `回溯思想`，我们每次遍历到某个结点的时候，认为这个结点的根结点就是它本身。让以这个结点为根节点的 DFS 全部遍历完毕了以后，再将 `这个结点的根节点` 设置为 `这个结点的父一级结点`。
4.  回溯的时候，如果以该节点为起点，`queryEdge` 查询边的另一个结点也恰好访问过了，则直接更新查询边的 LCA 结果。
5.  最后输出结果。

#### 性质

Tarjan 算法需要初始化并查集，所以预处理的时间复杂度为 $O(n)$。

朴素的 Tarjan 算法处理所有 $m$ 次询问的时间复杂度为 $O(m \alpha(m+n, n) + n)$，。但是 Tarjan 算法的常数比倍增算法大。存在 $O(m + n)$ 的实现。

???+ warning "注意"
    并不存在「朴素 Tarjan LCA 算法中使用的并查集性质比较特殊，单次调用 `find()` 函数的时间复杂度为均摊 $O(1)$」这种说法。
    
    以下的朴素 Tarjan 实现复杂度为 $O(m \alpha(m+n, n) + n)$。如果需要追求严格线性，可以参考 [Gabow 和 Tarjan 于 1983 年的论文](https://dl.acm.org/doi/pdf/10.1145/800061.808753)。其中给出了一种复杂度为 $O(m + n)$ 的做法。

#### 实现

??? note "参考代码"
    ```cpp
    --8<-- "docs/graph/code/lca/lca_tarjan.cpp"
    ```

### 用欧拉序列转化为 RMQ 问题

#### 定义

对一棵树进行 DFS，无论是第一次访问还是回溯，每次到达一个结点时都将编号记录下来，可以得到一个长度为 $2n-1$ 的序列，这个序列被称作这棵树的欧拉序列。

在下文中，把结点 $u$ 在欧拉序列中第一次出现的位置编号记为 $pos(u)$（也称作节点 $u$ 的欧拉序），把欧拉序列本身记作 $E[1..2n-1]$。

#### 过程

有了欧拉序列，LCA 问题可以在线性时间内转化为 RMQ 问题，即 $pos(LCA(u, v))=\min\{pos(k)|k\in E[pos(u)..pos(v)]\}$。

这个等式不难理解：从 $u$ 走到 $v$ 的过程中一定会经过 $LCA(u,v)$，但不会经过 $LCA(u,v)$ 的祖先。因此，从 $u$ 走到 $v$ 的过程中经过的欧拉序最小的结点就是 $LCA(u, v)$。

用 DFS 计算欧拉序列的时间复杂度是 $O(n)$，且欧拉序列的长度也是 $O(n)$，所以 LCA 问题可以在 $O(n)$ 的时间内转化成等规模的 RMQ 问题。

#### 实现

???+ note "参考代码"
    ```cpp
    int dfn[N << 1], pos[N], tot, st[30][(N << 1) + 2],
        rev[30][(N << 1) + 2];  // rev表示最小深度对应的节点编号
    
    void dfs(int cur, int dep) {
      dfn[++tot] = cur;
      depth[tot] = dep;
      pos[cur] = tot;
      for (int i = head[t]; i; i = side[i].next) {
        int v = side[i].to;
        if (!pos[v]) {
          dfs(v, dep + 1);
          dfn[++tot] = cur, depth[tot] = dep;
        }
      }
    }
    
    void init() {
      for (int i = 2; i <= tot + 1; ++i)
        lg[i] = lg[i >> 1] + 1;  // 预处理 lg 代替库函数 log2 来优化常数
      for (int i = 1; i <= tot; i++) st[0][i] = depth[i], rev[0][i] = dfn[i];
      for (int i = 1; i <= lg[tot]; i++)
        for (int j = 1; j + (1 << i) - 1 <= tot; j++)
          if (st[i - 1][j] < st[i - 1][j + (1 << i - 1)])
            st[i][j] = st[i - 1][j], rev[i][j] = rev[i - 1][j];
          else
            st[i][j] = st[i - 1][j + (1 << i - 1)],
            rev[i][j] = rev[i - 1][j + (1 << i - 1)];
    }
    
    int query(int l, int r) {
      int k = lg[r - l + 1];
      return st[k][l] < st[k][r + 1 - (1 << k)] ? rev[k][l]
                                                : rev[k][r + 1 - (1 << k)];
    }
    ```

当我们需要查询某点对 $(u, v)$ 的 LCA 时，查询区间 $[\min\{pos[u], pos[v]\}, \max\{pos[u], pos[v]\}]$ 上最小值的所代表的节点即可。

若使用 ST 表来解决 RMQ 问题，那么该算法不支持在线修改，预处理的时间复杂度为 $O(n\log n)$，每次查询 LCA 的时间复杂度为 $O(1)$。

### 树链剖分

LCA 为两个游标跳转到同一条重链上时深度较小的那个游标所指向的点。

树链剖分的预处理时间复杂度为 $O(n)$，单次查询的时间复杂度为 $O(\log n)$，并且常数较小。

### [动态树](../ds/lct.md)

设连续两次 [access](../ds/lct.md#access) 操作的点分别为 `u` 和 `v`，则第二次 [access](../ds/lct.md#access) 操作返回的点即为 `u` 和 `v` 的 LCA.

在无 link 和 cut 等操作的情况下，使用 link cut tree 单次查询的时间复杂度为 $O(\log n)$。

### 标准 RMQ

前面讲到了借助欧拉序将 LCA 问题转化为 RMQ 问题，其瓶颈在于 RMQ。如果能做到 $O(n) \sim O(1)$ 求解 RMQ，那么也就能做到 $O(n) \sim O(1)$ 求解 LCA。

注意到欧拉序满足相邻两数之差为 1 或者 -1，所以可以使用 $O(n) \sim O(1)$ 的 [加减 1RMQ](../topic/rmq.md#加减-1rmq) 来做。

时间复杂度 $O(n) \sim O(1)$，空间复杂度 $O(n)$，支持在线查询，常数较大。

#### 例题 [Luogu P3379【模板】最近公共祖先（LCA）](https://www.luogu.com.cn/problem/P3379)

??? note "参考代码"
    ```cpp
    --8<-- "docs/graph/code/lca/lca_2.cpp"
    ```

## 习题

-   [祖孙询问](https://loj.ac/problem/10135)
-   [货车运输](https://loj.ac/problem/2610)
-   [点的距离](https://loj.ac/problem/10130)
