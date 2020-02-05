author: Ir1d, sshwy, Xeonacid, partychicken, Anguei, HeRaNO
在 OI 中，想要对图进行操作，就需要先学习图的存储方式。

## 约定

本文默认读者已阅读并了解了 [图论相关概念](./concept.md) 中的基础内容，如果在阅读中遇到困难，也可以在 [图论相关概念](./concept.md) 中进行查阅。

在本文中，用 $n$ 代指图的点数，用 $m$ 代指图的边数，用 $d^+(u)$ 代指点 $u$ 的出度，即以 $u$ 为出发点的边数。

## 直接存边

### 方法

使用一个数组来存边，数组中的每个元素都包含一条边的起点与终点（带边权的图还包含边权）。（或者使用多个数组分别存起点，终点和边权。）

??? note "参考代码"
    ```cpp
    #include <iostream>
    #include <vector>
    
    using namespace std;
    
    struct Edge {
      int u, v;
    };
    
    int n, m;
    vector<Edge> e;
    vector<bool> vis;
    
    bool find_edge(int u, int v) {
      for (int i = 1; i <= m; ++i) {
        if (e[i].u == u && e[i].v == v) {
          return true;
        }
      }
      return false;
    }
    
    void dfs(int u) {
      if (vis[u]) return;
      vis[u] = true;
      for (int i = 1; i <= m; ++i) {
        if (e[i].u == u) {
          dfs(e[i].v);
        }
      }
    }
    
    int main() {
      cin >> n >> m;
    
      vis.resize(n + 1, false);
      e.resize(m + 1);
    
      for (int i = 1; i <= m; ++i) cin >> e[i].u >> e[i].v;
    
      return 0;
    }
    ```

### 复杂度

查询是否存在某条边： $O(m)$ 。

遍历一个点的所有出边： $O(m)$ 。

遍历整张图： $O(nm)$ 。

空间复杂度： $O(m)$ 。

### 应用

由于直接存边的遍历效率低下，一般不用于遍历图。

在 [Kruskal 算法](./mst.md#kruskal) 中，由于需要将边按边权排序，需要直接存边。

在有的题目中，需要多次建图（如建一遍原图，建一遍反图），此时既可以使用多个其它数据结构来同时存储多张图，也可以将边直接存下来，需要重新建图时利用直接存下的边来建图。

## 邻接矩阵

### 方法

使用一个二维数组 `adj` 来存边，其中 `adj[u][v]` 为 1 表示存在 $u$ 到 $v$ 的边，为 0 表示不存在。如果是带边权的图，可以在 `adj[u][v]` 中存储 $u$ 到 $v$ 的边的边权。

??? note "参考代码"
    ```cpp
    #include <iostream>
    #include <vector>
    
    using namespace std;
    
    int n, m;
    vector<bool> vis;
    vector<vector<bool> > adj;
    
    bool find_edge(int u, int v) { return adj[u][v]; }
    
    void dfs(int u) {
      if (vis[u]) return;
      vis[u] = true;
      for (int v = 1; v <= n; ++v) {
        if (adj[u][v]) {
          dfs(v);
        }
      }
    }
    
    int main() {
      cin >> n >> m;
    
      vis.resize(n + 1, false);
      adj.resize(n + 1, vector<bool>(n + 1, false));
    
      for (int i = 1; i <= m; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u][v] = true;
      }
    
      return 0;
    }
    ```

### 复杂度

查询是否存在某条边： $O(1)$ 。

遍历一个点的所有出边： $O(n)$ 。

遍历整张图： $O(n^2)$ 。

空间复杂度： $O(n^2)$ 。

### 应用

邻接矩阵只适用于没有重边（或重边可以忽略）的情况。

其最显著的优点是可以 $O(1)$ 查询一条边是否存在。

由于邻接矩阵在稀疏图上效率很低（尤其是在点数较多的图上，空间无法承受），所以一般只会在稠密图上使用邻接矩阵。

## 邻接表

### 方法

使用一个支持动态增加元素的数据结构构成的数组，如 `vector<int> adj[n + 1]` 来存边，其中 `adj[u]` 存储的是点 $u$ 的所有出边的相关信息（终点、边权等）。

??? note "参考代码"
    ```cpp
    #include <iostream>
    #include <vector>
    
    using namespace std;
    
    int n, m;
    vector<bool> vis;
    vector<vector<int> > adj;
    
    bool find_edge(int u, int v) {
      for (int i = 0; i < adj[u].size(); ++i) {
        if (adj[u][i] == v) {
          return true;
        }
      }
      return false;
    }
    
    void dfs(int u) {
      if (vis[u]) return;
      vis[u] = true;
      for (int i = 0; i < adj[u].size(); ++i) dfs(adj[u][i]);
    }
    
    int main() {
      cin >> n >> m;
    
      vis.resize(n + 1, false);
      adj.resize(n + 1);
    
      for (int i = 1; i <= m; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
      }
    
      return 0;
    }
    ```

### 复杂度

查询是否存在 $u$ 到 $v$ 的边： $O(d^+(u))$ （如果事先进行了排序就可以使用 [二分查找](../basic/binary.md) 做到 $O(\log(d^+(u)))$ ）。

遍历点 $u$ 的所有出边： $O(d^+(u))$ 。

遍历整张图： $O(n+m)$ 。

空间复杂度： $O(m)$ 。

### 应用

存各种图都很适合，除非有特殊需求（如需要快速查询一条边是否存在，且点数较少，可以使用邻接矩阵）。

尤其适用于需要对一个点的所有出边进行排序的场合。

## 链式前向星

### 方法

本质上是用链表实现的邻接表，核心代码如下：

```cpp
// head[u] 和 cnt 的初始值都为 -1
void add(int u, int v) {
  nxt[++cnt] = head[u];  // 当前边的后继
  head[u] = cnt;         // 起点 u 的第一条边
  to[cnt] = v;           // 当前边的终点
}

// 遍历 u 的出边
for (int i = head[u]; ~i; i = nxt[i]) {  // ~i 表示 i != -1
  int v = to[i];
}
```

??? note "参考代码"
    ```cpp
    #include <iostream>
    #include <vector>
    
    using namespace std;
    
    int n, m;
    vector<bool> vis;
    vector<int> head, nxt, to;
    
    void add(int u, int v) {
      nxt.push_back(head[u]);
      head[u] = to.size();
      to.push_back(v);
    }
    
    bool find_edge(int u, int v) {
      for (int i = head[u]; ~i; i = nxt[i]) {  // ~i 表示 i != -1
        if (to[i] == v) {
          return true;
        }
      }
      return false;
    }
    
    void dfs(int u) {
      if (vis[u]) return;
      vis[u] = true;
      for (int i = head[u]; ~i; i = nxt[i]) dfs(to[i]);
    }
    
    int main() {
      cin >> n >> m;
    
      vis.resize(n + 1, false);
      head.resize(n + 1, -1);
    
      for (int i = 1; i <= m; ++i) {
        int u, v;
        cin >> u >> v;
        add(u, v);
      }
    
      return 0;
    }
    ```

### 复杂度

查询是否存在 $u$ 到 $v$ 的边： $O(d^+(u))$ 。

遍历点 $u$ 的所有出边： $O(d^+(u))$ 。

遍历整张图： $O(n+m)$ 。

空间复杂度： $O(m)$ 。

### 应用

存各种图都很适合，但不能快速查询一条边是否存在，也不能方便地对一个点的出边进行排序。

优点是边是带编号的，有时会非常有用，而且如果 `cnt` 的初始值为奇数，存双向边时 `i ^ 1` 即是 `i` 的反边（常用于 [网络流](./flow.md) ）。
