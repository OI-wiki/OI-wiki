author: Ir1d, sshwy, Xeonacid, partychicken, Anguei, HeRaNO, Sam5440

在 OI 中，想要对图进行操作，就需要先学习图的存储方式。

## 约定

本文默认读者已阅读并了解了 [图论相关概念](./concept.md) 中的基础内容，如果在阅读中遇到困难，也可以在 [图论相关概念](./concept.md) 中进行查阅。

- $n$ 表示点数，$m$ 表示边数，$d^+(u)$ 表示点 $u$ 的出度（即 $u$ 的所有出边数）。
- 部分术语参考：[图论相关概念](./concept.md)
- 详细请查阅：[OI-wiki - 图的存储方式](https://oi-wiki.org/graph/representation/)
- 相关算法可见：
    - 最小生成树：[Kruskal 算法](./mst.md#kruskal-算法)、[其它 MST 算法](./mst.md)
    - 网络流相关：[网络流基础](./flow.md)
    - 辅助：[基础算法/二分查找](../basic/binary.md)
    - 更多基础请查阅：[图论相关概念](./concept.md)



## 直接存边

详细原理与讨论见：
- [OI-wiki：直接存边](https://oi-wiki.org/graph/representation/#%E7%9B%B4%E6%8E%A5%E5%AD%98%E8%BE%B9)
- [图论相关概念](./concept.md)
- [Kruskal 算法](./mst.md#kruskal-算法)

### 方法说明

用数组存下所有边，数组每元素存一条边的起点、终点（带权图还可加边权）。也可以用多个数组分别存起点、终点和边权。

### 结构可视化

```
e数组:
索引 |  u  |  v  |
-----|-----|-----|
  1  |  1  |  2  |
  2  |  1  |  3  |
  3  |  2  |  3  |
  4  |  3  |  4  |
  5  |  4  |  1  |
```
图形参考：

```
    ┌───┐
    │   │
    ▼   │
┌─► 1 ──┘
│   │
│   ▼
│   2
│   │
│   ▼
│   3
│   │
│   ▼
└── 4
```

### 代码实现

??? note "参考代码"
    === "C++"
        ```cpp
        #include <iostream>
        #include <vector>
        using namespace std;

        // 边的结构体，包含起点和终点
        struct Edge {
            int u, v;
        };

        int n, m;           // 节点和边数量
        vector<Edge> e;     // 边数组，e[i] 存第i条边(u, v)
        vector<bool> vis;   // 标记每个点是否访问过

        // 查找是否存在 u 到 v 的边
        bool find_edge(int u, int v) {
            for (int i = 1; i <= m; ++i) {
                if (e[i].u == u && e[i].v == v)
                    return true;
            }
            return false;
        }

        // 从结点 u 开始 DFS 遍历
        void dfs(int u) {
            if (vis[u]) return;
            vis[u] = true;
            for (int i = 1; i <= m; ++i) {
                if (e[i].u == u)
                    dfs(e[i].v);
            }
        }

        int main() {
            cin >> n >> m;
            vis.resize(n + 1, false); // 1-based
            e.resize(m + 1);          // 1-based
            // 录入每条边
            for (int i = 1; i <= m; ++i)
                cin >> e[i].u >> e[i].v;
            // 可以调用dfs或find_edge
            return 0;
        }
        ```
    === "Python"
        ```python
        # 定义边的数据结构
        class Edge:
            def __init__(self, u=0, v=0):
                self.u = u
                self.v = v

        n, m = map(int, input().split())
        e = [Edge() for _ in range(m)]      # 边列表
        vis = [False] * (n+1)               # 访问标记

        # 读入 m 条边
        for i in range(m):
            e[i].u, e[i].v = map(int, input().split())

        # 判断是否存在 u 到 v 的边
        def find_edge(u, v):
            for i in range(m):
                if e[i].u == u and e[i].v == v:
                    return True
            return False

        # DFS遍历，从点u出发
        def dfs(u):
            if vis[u]:
                return
            vis[u] = True
            for i in range(m):
                if e[i].u == u:
                    dfs(e[i].v)
        ```

### 复杂度分析

- 查边：$O(m)$
- 遍历 $u$ 所有出边：$O(m)$
- 遍历整图DFS：$O(nm)$
- 空间：$O(m)$

### 应用场景

- 适用于 [Kruskal 最小生成树算法](./mst.md#kruskal-算法) 等“边排序”场景
- 需要多次建图（原/反图等），如网络流残余建图等
- 不适合遍历效率优先场合




## 邻接矩阵

链接：
- [OI-wiki：邻接矩阵](https://oi-wiki.org/graph/representation/#%E9%82%BB%E6%8E%A5%E7%9F%A9%E9%98%B5)
- [图论相关概念](./concept.md)

### 方法说明

用二维数组 `adj`，`adj[u][v]=1` 代表存在 $u \to v$ 的边。带权则存权值。

### 结构可视化

```
    | 1 | 2 | 3 | 4 |
----|---|---|---|---|
 1  | 0 | 1 | 1 | 0 |
 2  | 0 | 0 | 1 | 0 |
 3  | 0 | 0 | 0 | 1 |
 4  | 1 | 0 | 0 | 0 |
↑
行(起点)
```

### 代码实现

??? note "参考代码"
    === "C++"
        ```cpp
        #include <iostream>
        #include <vector>
        using namespace std;

        int n, m;
        vector<bool> vis;                // 访问标记
        vector<vector<bool>> adj;        // 邻接矩阵

        // 判断是否存在 u 到 v 的边
        bool find_edge(int u, int v) {
            return adj[u][v];
        }

        // 从节点 u 开始 DFS
        void dfs(int u) {
            if (vis[u]) return;
            vis[u] = true;
            for (int v = 1; v <= n; ++v) {    // 遍历所有可能终点
                if (adj[u][v]) {
                    dfs(v);
                }
            }
        }

        int main() {
            cin >> n >> m;
            vis.resize(n + 1);
            adj.resize(n + 1, vector<bool>(n + 1, false)); // 下标1~n

            // 输入每一条边
            for (int i = 1; i <= m; ++i) {
                int u, v;
                cin >> u >> v;
                adj[u][v] = true;
            }
            return 0;
        }
        ```
    === "Python"
        ```python
        n, m = map(int, input().split())
        vis = [False] * (n+1) # 访问标记
        adj = [[False] * (n+1) for _ in range(n+1)] # 邻接矩阵

        # 读入 m 条边
        for _ in range(m):
            u, v = map(int, input().split())
            adj[u][v] = True

        # 判断u到v是否有边
        def find_edge(u, v):
            return adj[u][v]

        # 从u出发DFS
        def dfs(u):
            if vis[u]:
                return
            vis[u] = True
            for v in range(1, n+1):
                if adj[u][v]:
                    dfs(v)
        ```

### 复杂度分析

- 查边：$O(1)$
- 遍历 $u$ 所有出边：$O(n)$
- 遍历整图DFS：$O(n^2)$
- 空间：$O(n^2)$

### 应用场景

- 稠密图、小点集、需快速查边
- 不适合大点数稀疏图
- **注意：只适用于没有重边或重边可以忽略的情况。**



## 邻接表

链接：
- [OI-wiki：邻接表](https://oi-wiki.org/graph/representation/#%E9%82%BB%E6%8E%A5%E8%A1%A8)
- [图论相关概念](./concept.md)
- 辅助查找可用 [基础算法/二分查找](../basic/binary.md)

### 方法说明

用数组 `adj`，每项为动态数组/链表，`adj[u]` 存 $u$ 的所有出边终点或边权。

### 结构可视化

```
1 → [2, 3]
2 → [3]
3 → [4]
4 → [1]
```
字符画：

```
1 → [2, 3]
     │
     ▼
     2
     │
     ▼
     3
     │
     ▼
     4
```

### 代码实现

??? note "参考代码"
    === "C++"
        ```cpp
        #include <iostream>
        #include <vector>
        using namespace std;

        int n, m;                           // 点数、边数
        vector<bool> vis;                   // 访问标记数组
        vector<vector<int>> adj;            // 邻接表

        // 判断u到v是否有边
        bool find_edge(int u, int v) {
            for (int neighbor : adj[u]) {
                if (neighbor == v)
                    return true;
            }
            return false;
        }

        // 从u出发DFS
        void dfs(int u) {
            if (vis[u]) return;
            vis[u] = true;
            for (int v : adj[u]) {
                dfs(v);
            }
        }

        int main() {
            cin >> n >> m;
            vis.resize(n + 1, false);
            adj.resize(n + 1);

            // 录入每条边
            for (int i = 1; i <= m; ++i) {
                int u, v;
                cin >> u >> v;
                adj[u].push_back(v);
            }
            return 0;
        }
        ```
    === "Python"
        ```python
        n, m = map(int, input().split())
        vis = [False] * (n+1)          # 访问标记数组
        adj = [[] for _ in range(n+1)] # 邻接表，每个点存出边列表

        # 读取每条边
        for _ in range(m):
            u, v = map(int, input().split())
            adj[u].append(v)

        # 检查u到v是否有边
        def find_edge(u, v):
            return v in adj[u]

        # DFS从u出发
        def dfs(u):
            if vis[u]:
                return
            vis[u] = True
            for v in adj[u]:
                dfs(v)
        ```

### 复杂度分析

- 查边：$O(d^+(u))$。如果对邻接表有序，可以用 [二分查找](../basic/binary.md) 优化为 $O(\log d^+(u))$。
- 遍历 $u$ 所有出边：$O(d^+(u))$
- 遍历整图DFS：$O(n+m)$
- 空间：$O(n+m)$

### 应用场景

- 稀疏图，常规图方便遍历时使用
- 适合需要灵活操作和高效遍历的场景
- 适用于需要对一个点的所有出边进行排序的场合



## 链式前向星

链接：
- [OI-wiki：链式前向星](https://oi-wiki.org/graph/representation/#%E9%93%BE%E5%BC%8F%E5%89%8D%E5%90%91%E6%98%9F)
- [图论相关概念](./concept.md)
- 网络流相关：[网络流基础](./flow.md)

### 方法说明

本质为链表实现的邻接表，便于“边编号”，高效建反边等，常用于网络流等题目。每次加边时，利用数组来存每条边 `to[]` 终点和 `nxt[]` 下一条同起点的边的编号，`head[u]` 指向 $u$ 的第一条出边编号。

**补充——核心技巧与等价代码片段说明（文档2补全）：**

- `head[u]` 和计数器 `cnt` 的初始值**都设为 -1**。
- 每加一条边，`nxt[++cnt]=head[u]; head[u]=cnt; to[cnt]=v;`。
- 遍历 $u$ 的所有出边时，`for(int i=head[u]; ~i; i=nxt[i])`。
- 若用双向边，且 $cnt$ 从偶数（0/1）起，则有 `i^1` 得到 $i$ 号边的反向边（常用于网络流反边操作）。
- 在存双向边时，**$i^1$ 即为该边的反边下标**（如边0与1互为反边）。

#### 示意代码（最小子结构补全）

=== "C++"
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

=== "Python"
    ```python
    # head[u] 和 cnt 的初始值都为 -1
    def add(u, v):
        cnt = cnt + 1
        nxt[cnt] = head[u]  # 当前边的后继
        head[u] = cnt  # 起点 u 的第一条边
        to[cnt] = v  # 当前边的终点

    # 遍历 u 的出边
    i = head[u]
    while ~i:  # ~i 表示 i != -1
        v = to[i]
        i = nxt[i]
    ```

### 结构可视化

```
to:   [2, 3, 3, 4, 1]
nxt:  [-1, 0, -1, -1, -1]
head: [-1, 1, 2, 3, 4]
```

链表拓扑：

```
节点1 head[1]: 1 → nxt[1]: 0 → nxt[0]: -1
   ↓          ↓
  to[1]=3    to[0]=2
节点2 head[2]: 2 → -1
节点3 head[3]: 3 → -1
节点4 head[4]: 4 → -1
```

### 代码实现

??? note "参考代码"
    === "C++"
        ```cpp
        #include <iostream>
        #include <vector>
        using namespace std;

        int n, m;                    // 点数与边数
        vector<bool> vis;            // 访问标记
        vector<int> head, nxt, to;
        int cnt = -1;                // 边计数器补充：初始值为-1，便于编号与 ^1 反边技巧

        // 向链式前向星中加一条 u->v 边
        void add(int u, int v) {
            nxt.push_back(head[u]);    // 当前链表头节点的后继为head[u]
            head[u] = ++cnt;           // (补全)每加边加1，head[u]指向最新边号
            to.push_back(v);           // to新增边的目标点
        }

        // 查询u到v是否有边
        bool find_edge(int u, int v) {
            for (int i = head[u]; ~i; i = nxt[i]) { // 遍历u的边表
                if (to[i] == v)
                    return true;
            }
            return false;
        }

        // DFS遍历
        void dfs(int u) {
            if (vis[u]) return;
            vis[u] = true;
            for (int i = head[u]; ~i; i = nxt[i])
                dfs(to[i]);
        }

        int main() {
            cin >> n >> m;
            vis.resize(n + 1, false);
            head.resize(n + 1, -1);

            // 输入每一条边
            for (int i = 1; i <= m; ++i) {
                int u, v;
                cin >> u >> v;
                add(u, v);
            }
            return 0;
        }
        ```
    === "Python"
        ```python
        n, m = map(int, input().split())
        vis = [False] * (n+1)
        head = [-1] * (n+1)    # 每个点指向出链第一条边下标
        nxt = []               # nxt[i]指向同起点的下一条边
        to = []                # to[i]保存目标点编号
        cnt = -1               # 边计数器，初始-1（补全自文档2）

        # 增加一条 u -> v 的边
        def add(u, v):
            global cnt
            cnt += 1
            nxt.append(head[u])        # 新边的后继为原head[u]
            head[u] = cnt             # head[u]指向新边
            to.append(v)              # 边目标节点

        for _ in range(m):
            u, v = map(int, input().split())
            add(u, v)

        # 判断 u->v 是否存在
        def find_edge(u, v):
            i = head[u]
            while i != -1:
                if to[i] == v:
                    return True
                i = nxt[i]
            return False

        # 从u出发DFS
        def dfs(u):
            if vis[u]:
                return
            vis[u] = True
            i = head[u]
            while i != -1:
                dfs(to[i])
                i = nxt[i]
        ```

### 复杂度分析

- 查边：$O(d^+(u))$
- 遍历 $u$ 所有出边：$O(d^+(u))$
- 遍历整图DFS：$O(n+m)$
- 空间：$O(m)$

### 应用场景

- 适用于边有编号、网络流、反向边操作（如 $i^1$ 得反边技巧，[见网络流](./flow.md)）
- 常用稀疏图或高效按边驱动算法
- 不方便对某点的所有出边排序


## 总结对比表

| 存储方式    | 空间复杂度 | 查边复杂度 | 遍历出边复杂度 | 最佳应用场景         |
|------------|-----------|-----------|---------------|---------------------|
| 直接存边    | O(m)      | O(m)      | O(m)          | [边能排序/Kruskal](./mst.md#kruskal-算法)    |
| 邻接矩阵    | O(n²)     | O(1)      | O(n)          | 稠密图/查边快       |
| 邻接表      | O(n+m)    | O(d⁺(u))  | O(d⁺(u))      | 稀疏图/常规         |
| 链式前向星   | O(m)      | O(d⁺(u))  | O(d⁺(u))      | 边要编号/网络流      |


**更多图论相关基础内容请见：[图论相关概念](./concept.md)**


**相关扩展阅读：**
- [Kruskal 最小生成树算法](./mst.md#kruskal-算法)
- [其它最小生成树算法](./mst.md)
- [基础算法 - 二分查找](../basic/binary.md)
- [网络流基础](./flow.md)

