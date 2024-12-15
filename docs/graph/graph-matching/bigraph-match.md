author: accelsao, thallium, Chrogeek, Enter-tainer, ksyx, StudyingFather, H-J-Granger, Henry-ZHR, countercurrent-time, william-song-shy, 5ab-juruo, XiaoQuQuSD

为了描述方便将两个集合分成左和右两个部分，所有匹配边都是横跨左右两个集合，可以假想成男女配对。

假设图有 $n$ 个顶点，$m$ 条边。

## 题目描述

给定一个二分图 $G$，即分左右两部分，各部分之间的点没有边连接，要求选出一些边，使得这些边没有公共顶点，且边的数量最大。

## 增广路算法 Augmenting Path Algorithm

因为增广路长度为奇数，路径起始点非左即右，所以我们先考虑从左边的未匹配点找增广路。
注意到因为交错路的关系，增广路上的第奇数条边都是非匹配边，第偶数条边都是匹配边，于是左到右都是非匹配边，右到左都是匹配边。
于是我们给二分图 **定向**，问题转换成，有向图中从给定起点找一条简单路径走到某个未匹配点，此问题等价给定起始点 $s$ 能否走到终点 $t$。
那么只要从起始点开始 DFS 遍历直到找到某个未匹配点，$O(m)$。
未找到增广路时，我们拓展的路也称为 **交错树**。

### 性质

因为要枚举 $n$ 个点，总复杂度为 $O(nm)$。

### 实现

```cpp
struct augment_path {
  vector<vector<int>> g;
  vector<int> pa;  // 匹配
  vector<int> pb;
  vector<int> vis;  // 访问
  int n, m;         // 两个点集中的顶点数量
  int dfn;          // 时间戳记
  int res;          // 匹配数

  augment_path(int _n, int _m) : n(_n), m(_m) {
    assert(0 <= n && 0 <= m);
    pa = vector<int>(n, -1);
    pb = vector<int>(m, -1);
    vis = vector<int>(n);
    g.resize(n);
    res = 0;
    dfn = 0;
  }

  void add(int from, int to) {
    assert(0 <= from && from < n && 0 <= to && to < m);
    g[from].push_back(to);
  }

  bool dfs(int v) {
    vis[v] = dfn;
    for (int u : g[v]) {
      if (pb[u] == -1) {
        pb[u] = v;
        pa[v] = u;
        return true;
      }
    }
    for (int u : g[v]) {
      if (vis[pb[u]] != dfn && dfs(pb[u])) {
        pa[v] = u;
        pb[u] = v;
        return true;
      }
    }
    return false;
  }

  int solve() {
    while (true) {
      dfn++;
      int cnt = 0;
      for (int i = 0; i < n; i++) {
        if (pa[i] == -1 && dfs(i)) {
          cnt++;
        }
      }
      if (cnt == 0) {
        break;
      }
      res += cnt;
    }
    return res;
  }
};
```

## 转为网络最大流模型

二分图最大匹配可以转换成网络流模型。

将源点连上左边所有点，右边所有点连上汇点，容量皆为 $1$。原来的每条边从左往右连边，容量也皆为 $1$，最大流即最大匹配。

如果使用 [Dinic 算法](../flow/max-flow.md#dinic-算法) 求该网络的最大流，可在 $O(\sqrt{n}m)$ 求出。

Dinic 算法分成两部分，第一部分用 $O(m)$ 时间 BFS 建立网络流，第二步是 $O(nm)$ 时间 DFS 进行增广。

但因为容量为 $1$，所以实际时间复杂度为 $O(m)$。

接下来前 $O(\sqrt{n})$ 轮，复杂度为 $O(\sqrt{n}m)$。$O(\sqrt{n})$ 轮以后，每条增广路径长度至少 $\sqrt{n}$，而这样的路径不超过 $\sqrt{n}$，所以此时最多只需要跑 $\sqrt{n}$ 轮，整体复杂度为 $O(\sqrt{n}m)$。

代码可以参考 [Dinic 算法](../flow/max-flow.md#dinic-算法) 的参考实现，这里不再给出。

## 补充

### 二分图最小点覆盖（König 定理）

最小点覆盖：选最少的点，满足每条边至少有一个端点被选。

二分图中，最小点覆盖 $=$ 最大匹配。

???+ note "证明"
    将二分图点集分成左右两个集合，使得所有边的两个端点都不在一个集合。
    
    考虑如下构造：从左侧未匹配的节点出发，按照匈牙利算法中增广路的方式走，即先走一条未匹配边，再走一条匹配边。由于已经求出了最大匹配，所以这样的「增广路」一定以匹配边结束，即增广路是不完整的。在所有经过这样「增广路」的节点上打标记。则最后构造的集合是：所有左侧未打标记的节点和所有右侧打了标记的节点。
    
    首先，这个集合的大小等于最大匹配。左边未打标记的点都一定对应着一个匹配边（否则会以这个点为起点开始标记），右边打了标记的节点一定在一条不完整的增广路上，也会对应一个匹配边。假设存在一条匹配边左侧标记了，右侧没标记，左边的点只能是通过另一条匹配边走过来，此时左边的点有两条匹配边，不符合最大匹配的规定；假设存在一条匹配边左侧没标记，右侧标记了，那就会从右边的点沿着这条匹配边走过来，从而左侧也有标记。因此，每一条匹配的边两侧一定都有标记（在不完整的增广路上）或都没有标记，匹配边的两个节点中必然有一个被选中。
    
    其次，这个集合是一个点覆盖。由于我们的构造方式是：所有左侧未打标记的节点和所有右侧打了标记的节点。假设存在左侧打标记且右侧没打标记的边，对于匹配边，上一段已经说明其不存在，对于非匹配边，右端点一定会由这条非匹配边经过，从而被打上标记。因此，这样的构造能够覆盖所有边。
    
    同时，不存在更小的点覆盖。为了覆盖最大匹配的所有边，至少要有最大匹配边数的点数。

### 二分图最大独立集

最大独立集：选最多的点，满足两两之间没有边相连。

因为在最小点覆盖中，任意一条边都被至少选了一个顶点，所以对于其点集的补集，任意一条边都被至多选了一个顶点，所以不存在边连接两个点集中的点，且该点集最大。因此二分图中，最大独立集 $=n-$ 最小点覆盖。

## 例题

??? note "[UOJ #78. 二分图最大匹配](https://uoj.ac/problem/78)"
    模板题
    
    ```cpp
    #include <cassert>
    #include <iostream>
    #include <vector>
    using namespace std;
    
    struct augment_path {
      vector<vector<int>> g;
      vector<int> pa;  // 匹配
      vector<int> pb;
      vector<int> vis;  // 访问
      int n, m;         // 顶点和边的数量
      int dfn;          // 时间戳记
      int res;          // 匹配数
    
      augment_path(int _n, int _m) : n(_n), m(_m) {
        assert(0 <= n && 0 <= m);
        pa = vector<int>(n, -1);
        pb = vector<int>(m, -1);
        vis = vector<int>(n);
        g.resize(n);
        res = 0;
        dfn = 0;
      }
    
      void add(int from, int to) {
        assert(0 <= from && from < n && 0 <= to && to < m);
        g[from].push_back(to);
      }
    
      bool dfs(int v) {
        vis[v] = dfn;
        for (int u : g[v]) {
          if (pb[u] == -1) {
            pb[u] = v;
            pa[v] = u;
            return true;
          }
        }
        for (int u : g[v]) {
          if (vis[pb[u]] != dfn && dfs(pb[u])) {
            pa[v] = u;
            pb[u] = v;
            return true;
          }
        }
        return false;
      }
    
      int solve() {
        while (true) {
          dfn++;
          int cnt = 0;
          for (int i = 0; i < n; i++) {
            if (pa[i] == -1 && dfs(i)) {
              cnt++;
            }
          }
          if (cnt == 0) {
            break;
          }
          res += cnt;
        }
        return res;
      }
    };
    
    int main() {
      int n, m, e;
      cin >> n >> m >> e;
      augment_path solver(n, m);
      int u, v;
      for (int i = 0; i < e; i++) {
        cin >> u >> v;
        u--, v--;
        solver.add(u, v);
      }
      cout << solver.solve() << "\n";
      for (int i = 0; i < n; i++) {
        cout << solver.pa[i] + 1 << " ";
      }
      cout << "\n";
    }
    ```

??? note "[luogu P1129 矩阵游戏](https://www.luogu.com.cn/problem/P1129)"
    ??? note "解法"
        注意到，当存在 $n$ 个 $1$，使得这些 $1$ 不在同一行、同一列，那么必然有解，否则必然无解。

        问题转化成了能否找到这 $n$ 个 $1$。

        考虑对于一个 $1$ 而言，最终的方案中选了这个 $1$ 代表这个 $1$ 的行、列被占用。

        于是可以建出一个 $n$ 个左部点、$n$ 个右部点的二分图，其中对于某个为 $1$ 的元素，我们建一条连接它的行的左部点和它的列的右部点。

        于是就可以二分图匹配了。

    ??? note "代码"
        ```cpp
        --8<-- "/docs/code/graph-matching/bigraph-match/bigraph-match_1.cpp"
        ```

??? note "[Gym 104427B Lawyers](https://codeforces.com/gym/104427/problem/B)"
    有 $n$ 个律师，都被指控有欺诈罪。于是，他们需要互相辩护，确保每一名律师都被释放。

    这 $n$ 个律师有 $m$ 对信任关系，一个信任关系 $(a, b)$ 表示 $a$ 可以为 $b$ 辩护。

    任何一个受到辩护的律师都会被无罪释放，除了一个例外：如果 $a$ 和 $b$ 互相辩护，他们都会被判有罪。

    求是否可以使得每一名律师都被释放。

    ??? note "解法"
        对于每一个 **无序对** $(a, b)$，当 $a$ 可以辩护 $b$，连这个无序对向 $a$ 的边，反之亦然。

        只保存有边相连的 $(a, b)$，问题被转化成了一个 $m$ 个左部点、$n$ 个右部点的二分图最大匹配。

    ??? note "代码"
        ```cpp
        --8<-- "/docs/code/graph-matching/bigraph-match/bigraph-match_2.cpp"
        ```

??? note "[LibreOJ 6002 最小路径覆盖](https://loj.ac/p/6002)"
    ??? note "解法"
        对于每一个点，我们建立一个入点、一个出点。对于原图的边 $(u, v)$，在 $v$ 的入点和 $u$ 的出点连边。

        显然一个出点只能和至多一个入点匹配。

        于是就变成了一个最大匹配问题。

    ??? note "代码"
        ```cpp
        --8<-- "/docs/code/graph-matching/bigraph-match/bigraph-match_3.cpp"
        ```

??? note "[CodeForces 1404E Bricks](https://codeforces.com/problemset/problem/1404/E)"
    用一些 $1 \times x$ 的砖精确覆盖一个 $n \times m$ 的网格，砖可以旋转，其中有一些格子不能覆盖。

    ??? note "解法"
        考虑一开始全铺 $1 \times 1$ 的砖。

        然后，每一次把两个砖块合并到一起。

        所以可以对横向的合并和竖向的合并之间的冲突建边。

        然后原问题转化成了一个二分图最大独立集。

    ??? note "代码"
        ```cpp
        --8<-- "/docs/code/graph-matching/bigraph-match/bigraph-match_4.cpp"
        ```

## 参考资料

1.  <http://www.matrix67.com/blog/archives/116>
