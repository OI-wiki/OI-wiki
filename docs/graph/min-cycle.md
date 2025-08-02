## 引入

???+ question "问题"
    给出一个图，问其中的由 $n$ 个节点构成的边权和最小的环 $(n\ge 3)$ 是多大。

图的最小环也称围长。

## 过程

### 暴力解法

设 $u$ 和 $v$ 之间有一条边长为 $w$ 的边，$dis(u,v)$ 表示删除 $u$ 和 $v$ 之间的连边之后，$u$ 和 $v$ 之间的最短路。

那么无向图中的最小环是 $dis(u,v)+w$。

注意若是在有向图中求最小环，相对应的公式要修改，最小环是 $dis(v,u)+w$。

总时间复杂度 $O(n^2m)$。

### Dijkstra

相关链接：[最短路/Dijkstra](./shortest-path.md#dijkstra-算法)

#### 过程

枚举所有边，每一次求删除一条边之后对这条边的起点跑一次 Dijkstra，道理同上。

#### 性质

时间复杂度 $O(m(n+m)\log n)$。

### Floyd

相关链接：[最短路/Floyd](./shortest-path.md#floyd-算法)

#### 过程

记原图中 $u,v$ 之间边的边权为 $val\left(u,v\right)$。

我们注意到 Floyd 算法有一个性质：在最外层循环到点 $k$ 时（尚未开始第 $k$ 次循环），最短路数组 $dis$ 中，$dis_{u,v}$ 表示的是从 $u$ 到 $v$ 且仅经过编号在 $\left[1, k\right)$ 区间中的点的最短路。

由最小环的定义可知其至少有三个顶点，设其中编号最大的顶点为 $w$，环上与 $w$ 相邻两侧的两个点为 $u,v$，则在最外层循环枚举到 $k=w$ 时，该环的长度即为 $dis_{u,v}+val\left(v,w\right)+val\left(w,u\right)$。

故在循环时对于每个 $k$ 枚举满足 $i<k,j<k$ 的 $(i,j)$，更新答案即可。

#### 记录路径

现在已经知道了环的形式为 $u\to k\to v$，然后再从 $v$ 回到 $u$（经过的点编号均 $<k$）。

问题转化为求 $v\leadsto u$ 的路径。由三角不等式 $dis_{u,v}\le dis_{u,i}+dis_{i,v}$，考虑记录 $pos_{u,v}=j$ 表示使得 $dis_{u,v}=dis_{u,j}+dis_{j,v}$ 的点。显然 $j$ 就在 $v\leadsto u$ 的路径上。

于是可以将路径转化为 $v\leadsto j$ 和 $j\leadsto u$ 两段，分别递归处理即可。

???+ note "证明递归不会陷入死循环"
    使用反证法。
    
    假设环会重复经过一个点 $u$，那么环上必然会有一条 $u$ 出发经过若干条边回到 $u$ 的边。这就构成了一个新的环。
    
    由于图中不会出现负环（如果出现负环就不会有最小环了），所以新环的边权和必然是小于等于原环的。
    
    所以只需要截取这一个环，那么就不会重复经过一个点 $u$，假设不成立，故环不会重复经过一个点。
    
    所以当递归到 $u,v$ 两点时，其 $pos_{u,v}$ 必然不等于两点编号，也就是新加入了一个点。
    
    特别地，当 $u$ 和 $v$ 相邻时，直接返回即可。
    
    由于总点数为 $n$，那么新加入的次数（即递归次数）不会超过 $n$，因此递归不会陷入死循环。

#### 性质

时间复杂度：$O(n^3)$。

#### 实现

下面给出 C++ 和 Python 的参考实现（记录路径）：

=== "C++"
    ```cpp
    // 图的点数为 n
    int val[MAXN + 1][MAXN + 1];  // 原图的邻接矩阵
    int cnt, path[MAXN + 5];      // 记录最小环的路径和长度
    
    void get_path(int u, int v) {  // 获得 u 到 v 之间的路径
      if (pos[u][v] == 0) return;
    
      int k = pos[u][v];
      get_path(u, k);
      path[++cnt] = k;
      get_path(k, v);
    }
    
    void Floyd(const int &n) {
      static int dis[MAXN + 1][MAXN + 1];  // 最短路矩阵
      static int pos[MAXN + 1][MAXN + 1];
      memcpy(dis, val, sizeof(val));
      memset(pos, 0, sizeof(pos));
      for (int k = 1; k <= n; ++k) {
        for (int i = 1; i < k; ++i)
          for (int j = 1; j < i; ++j)
            if (ans >
                (long long)val[i][k] + val[k][j] + dis[i][j]) {  // 发现了更短的环
              // 由于这里保证了 j<i<k，所以三个点不同，不会出现零环。
              ans = val[i][k] + val[k][j] + dis[i][j], cnt = 0;
              path[++cnt] = i, path[++cnt] = k,
              path[++cnt] = j;  // 依次加入 i,k,j 三点
              get_path(j, i);   // 加入 j 到 i 的路径
            }
    
        for (int i = 1; i <= n; ++i)  // 正常 Floyd 更新最短路
          for (int j = 1; j <= n; ++j) {
            if (dis[i][j] > dis[i][k] + dis[k][j]) {
              dis[i][j] = dis[i][k] + dis[k][j];
              pos[i][j] = k;  // 当前路径可以由 k 更新得到
            }
          }
      }
    }
    ```

=== "Python"
    ```python
    # 定义一个足够大的值表示无穷大
    INF = sys.maxsize
    
    
    def get_path(i, j, pos, path, cnt):
        """
        递归地获取从节点 i 到节点 j 的最短路径上的中间节点。
    
        Args:
            i (int): 起始节点 (0-based index).
            j (int): 结束节点 (0-based index).
            pos (list[list[int]]): 记录最短路径中间节点的矩阵. pos[i][j] = k 表示从 i 到 j 的最短路径经过 k.
            path (list[int]): 存储路径节点的列表 (使用 0-based index).
            cnt (int): 当前路径节点的数量.
    
        Returns:
            int: 更新后的路径节点数量.
        """
        # 如果 pos[i][j] 为 -1，表示 i 到 j 没有中间节点
        if pos[i][j] == -1:
            return cnt
    
        # 获取中间节点 k
        k = pos[i][j]
        # 递归获取 i 到 k 的路径
        cnt = get_path(i, k, pos, path, cnt)
        # 将中间节点 k 加入路径
        path[cnt] = k
        cnt += 1
        # 递归获取 k 到 j 的路径
        cnt = get_path(k, j, pos, path, cnt)
        return cnt
    
    
    def find_minimum_cycle_undirected(n, edges):
        """
        使用 Floyd-Warshall 算法查找无向图中的最小环。
    
        Args:
            n (int): 图的节点数 (1 到 n).
            edges (list[tuple]): 边的列表，每个元素是 (u, v, w)，表示节点 u 和 v 之间有一条权重为 w 的边。
                                 节点索引是 1 到 n。
    
        Returns:
            tuple: 包含最小环的长度和路径。
                   如果不存在环，返回 (INF, []).
                   路径是一个节点索引列表 (1-based index)。
        """
        # 内部使用 0-based indexing
        N = n
        # 初始化邻接矩阵 g，表示原始边的权重
        g = [[INF for _ in range(N)] for _ in range(N)]
        # 初始化最短路矩阵 dis，开始时与 g 相同
        dis = [[INF for _ in range(N)] for _ in range(N)]
        # 初始化 pos 矩阵，记录最短路径的中间节点
        pos = [[-1 for _ in range(N)] for _ in range(N)]
    
        # 初始化对角线为 0 (节点到自身的距离)
        for i in range(N):
            g[i][i] = 0
            dis[i][i] = 0
    
        # 根据输入的边构建邻接矩阵 (无向图)
        for u, v, w in edges:
            # 将 1-based 索引转换为 0-based
            u -= 1
            v -= 1
            # 对于无向图，边是双向的
            g[u][v] = min(g[u][v], w)
            g[v][u] = min(g[v][u], w)
            dis[u][v] = min(dis[u][v], w)
            dis[v][u] = min(dis[v][u], w)
    
        # 初始化最小环长度为无穷大
        min_cycle_len = INF
        # 初始化最小环路径
        min_cycle_path = []
    
        # Floyd-Warshall 算法核心部分
        # k 作为中间节点 (0-based index)
        for k in range(N):
            # 在更新 dis[i][j] 之前，检查通过节点 k 是否能形成更小的环
            # 环由 i -> k -> j -> ... -> i 组成
            # 这里的 dis[i][j] 是在考虑节点 0 到 k-1 作为中间节点时的最短路径
            # C++ 代码中使用 i < k 和 j < i 的循环顺序，这里也遵循这个逻辑 (0-based)
            for i in range(k):  # 0 <= i < k
                for j in range(i):  # 0 <= j < i
                    # 检查 i, k, j 是否构成一个环，并且通过 dis[i][j] 连接
                    # 确保原始边 g[i][k] 和 g[k][j] 存在 (不为 INF)
                    # 并且 i 到 j 的最短路径 dis[i][j] 存在 (不为 INF)
                    if g[i][k] != INF and g[k][j] != INF and dis[i][j] != INF:
                        current_cycle_len = g[i][k] + g[k][j] + dis[i][j]
                        if current_cycle_len < min_cycle_len:
                            min_cycle_len = current_cycle_len
                            # 重构路径
                            path = [0] * (N + 5)  # 临时存储路径的数组，长度足够大
                            cnt = 0
                            # 按照 i, k, j 的顺序加入路径
                            path[cnt] = i
                            cnt += 1
                            path[cnt] = k
                            cnt += 1
                            path[cnt] = j
                            cnt += 1
                            # 获取 j 到 i 的最短路径上的中间节点 (使用之前计算的 dis 和 pos)
                            cnt = get_path(j, i, pos, path, cnt)
                            # 提取实际路径节点 (去除未使用的部分)
                            # 将 0-based 索引转换为 1-based
                            min_cycle_path = [node + 1 for node in path[:cnt]]
    
            # 标准 Floyd-Warshall 更新最短路径
            for i in range(N):
                for j in range(N):
                    if (
                        dis[i][k] != INF
                        and dis[k][j] != INF
                        and dis[i][j] > dis[i][k] + dis[k][j]
                    ):
                        dis[i][j] = dis[i][k] + dis[k][j]
                        # 记录从 i 到 j 的最短路径经过 k
                        pos[i][j] = k
    
        return min_cycle_len, min_cycle_path
    ```

## 模板题

??? "[AcWing 344 观光之旅](https://www.acwing.com/problem/content/346)"
    给定一张 $n$ 个点无向图，求图中一个至少包含 $3$ 个点的环，环上的节点不重复，并且环上的边的长度之和最小。
    
    该问题称为无向图的最小环问题。
    
    你需要输出最小环的方案，若最小环不唯一，输出任意一个均可。
    
    $n \le 100$

时间复杂度接受 $O(n^3)$ 的做法，套用 Floyd 求最小环的做法即可。

=== "C++"
    ```cpp
    #include <bits/stdc++.h>
    using lint = long long;
    // 定义一个足够大的常量，用于表示图的最大节点数
    const int MAXN = 110;
    
    // 定义一个足够大的值，用于表示无穷大，初始化最小环长度
    lint ans = 1e9;  // lint 是 long long 的别名
    
    // 图的节点数 n，边数 m
    // cnt 记录最小环路径中的节点数量
    // path 存储最小环的路径节点
    int n, m, cnt, path[MAXN];
    
    // g 存储原始图的邻接矩阵
    // dis 存储最短路径矩阵 (Floyd-Warshall 算法计算过程中更新)
    // pos 记录最短路径的中间节点，pos[i][j] = k 表示从 i 到 j 的最短路径经过 k
    int g[MAXN][MAXN], dis[MAXN][MAXN], pos[MAXN][MAXN];
    
    // 递归函数：获取从节点 u 到节点 v 的最短路径上的中间节点
    // 根据 pos 矩阵重构路径
    void get_path(int u, int v) {
      // 如果 pos[u][v] 为 0，表示 u 到 v 没有中间节点，直接返回
      if (pos[u][v] == 0) return;
    
      // 获取中间节点 k
      int k = pos[u][v];
      // 递归获取 u 到 k 的路径
      get_path(u, k);
      // 将中间节点 k 加入路径
      path[++cnt] = k;
      // 递归获取 k 到 v 的路径
      get_path(k, v);
    }
    
    // Floyd-Warshall 算法函数：查找图中的最小环
    void Floyd() {
      // 外层循环：k 作为中间节点 (1 到 n)
      for (int k = 1; k <= n; ++k) {
        // 内层循环：i 和 j，用于检查通过节点 k 是否能形成更小的环
        // 这里循环顺序是 i 从 1 到 k-1，j 从 1 到 i-1
        // 这样可以检查由 i -> k -> j -> ... -> i 构成的环
        for (int i = 1; i < k; ++i)
          for (int j = 1; j < i; ++j)
            // 检查通过节点 k 连接 i 和 j 是否形成更小的环
            // 环的长度是 i 到 k 的原始边权重 g[i][k] + k 到 j 的原始边权重 g[k][j]
            // + i 到 j 的当前最短路径 dis[i][j]
            if (ans > (long long)g[i][k] + g[k][j] + dis[i][j]) {
              // 发现了更小的环
              ans = g[i][k] + g[k][j] + dis[i][j];  // 更新最小环长度
              cnt = 0;                              // 重置路径计数
              // 将 i, k, j 依次加入路径
              path[++cnt] = i, path[++cnt] = k, path[++cnt] = j;
              // 获取 j 到 i 的最短路径上的中间节点，加入路径
              get_path(j, i);
            }
    
        // 标准 Floyd-Warshall 更新最短路径
        // i 从 1 到 n，j 从 1 到 n
        for (int i = 1; i <= n; ++i)
          for (int j = 1; j <= n; ++j) {
            // 如果通过中间节点 k 可以获得更短的从 i 到 j 的路径
            if (dis[i][j] > dis[i][k] + dis[k][j]) {
              // 更新最短路径
              dis[i][j] = dis[i][k] + dis[k][j];
              // 记录从 i 到 j 的最短路径经过 k
              pos[i][j] = k;
            }
          }
      }
    }
    
    // 主函数
    int main() {
      // 读取节点数 n 和边数 m
      std::cin >> n >> m;
      // 初始化原始邻接矩阵 g，所有边的权重设为无穷大 (0x3f 通常表示一个很大的值)
      memset(g, 0x3f, sizeof(g));
      // 将节点到自身的距离设为 0
      for (int i = 1; i <= n; ++i) g[i][i] = 0;
      // 读取 m 条边，构建原始邻接矩阵 g
      // 对于无向图，边是双向的，取较小的权重
      for (int i = 0, u, v, w; i < m; ++i) {
        std::cin >> u >> v >> w;
        g[u][v] = g[v][u] = std::min(g[u][v], w);
      }
      // 将原始邻接矩阵 g 复制到最短路径矩阵 dis
      memcpy(dis, g, sizeof(g));
      // 调用 Floyd 算法查找最小环
      Floyd();
      // 根据最小环长度判断是否存在环
      if (ans == 1e9) {  // 如果最小环长度仍为无穷大，表示不存在环
        puts("No solution.");
      } else {
        // 如果存在环，打印路径节点
        // std::cout << "ans = " << ans << std::endl; // 打印最小环长度 (注释掉)
        // 打印路径节点，用空格分隔
        for (int i = 1; i <= cnt; ++i)
          std::cout << path[i]
                    << (i == cnt ? "" : " ");  // 最后一个节点后面没有空格
        std::cout << std::endl;                // 路径打印完后换行
      }
      return 0;
    }
    ```

=== "Python"
    ```python
    import copy
    import sys
    
    # 定义一个足够大的值表示无穷大
    INF = sys.maxsize
    
    
    def get_path(i, j, pos, path, cnt):
        """
        递归地获取从节点 i 到节点 j 的最短路径上的中间节点。
    
        Args:
            i (int): 起始节点 (0-based index).
            j (int): 结束节点 (0-based index).
            pos (list[list[int]]): 记录最短路径中间节点的矩阵. pos[i][j] = k 表示从 i 到 j 的最短路径经过 k.
            path (list[int]): 存储路径节点的列表 (使用 0-based index).
            cnt (int): 当前路径节点的数量.
    
        Returns:
            int: 更新后的路径节点数量.
        """
        # 如果 pos[i][j] 为 -1，表示 i 到 j 没有中间节点
        if pos[i][j] == -1:
            return cnt
    
        # 获取中间节点 k
        k = pos[i][j]
        # 递归获取 i 到 k 的路径
        cnt = get_path(i, k, pos, path, cnt)
        # 将中间节点 k 加入路径
        path[cnt] = k
        cnt += 1
        # 递归获取 k 到 j 的路径
        cnt = get_path(k, j, pos, path, cnt)
        return cnt
    
    
    def find_minimum_cycle_undirected(n, edges):
        """
        使用 Floyd-Warshall 算法查找无向图中的最小环。
    
        Args:
            n (int): 图的节点数 (1 到 n).
            edges (list[tuple]): 边的列表，每个元素是 (u, v, w)，表示节点 u 和 v 之间有一条权重为 w 的边。
                                 节点索引是 1 到 n。
    
        Returns:
            tuple: 包含最小环的长度和路径。
                   如果不存在环，返回 (INF, []).
                   路径是一个节点索引列表 (1-based index)。
        """
        # 内部使用 0-based indexing
        N = n
        # 初始化邻接矩阵 g，表示原始边的权重
        g = [[INF for _ in range(N)] for _ in range(N)]
        # 初始化最短路矩阵 dis，开始时与 g 相同
        dis = [[INF for _ in range(N)] for _ in range(N)]
        # 初始化 pos 矩阵，记录最短路径的中间节点
        pos = [[-1 for _ in range(N)] for _ in range(N)]
    
        # 初始化对角线为 0 (节点到自身的距离)
        for i in range(N):
            g[i][i] = 0
            dis[i][i] = 0
    
        # 根据输入的边构建邻接矩阵 (无向图)
        for u, v, w in edges:
            # 将 1-based 索引转换为 0-based
            u -= 1
            v -= 1
            # 对于无向图，边是双向的
            g[u][v] = min(g[u][v], w)
            g[v][u] = min(g[v][u], w)
            dis[u][v] = min(dis[u][v], w)
            dis[v][u] = min(dis[v][u], w)
    
        # 初始化最小环长度为无穷大
        min_cycle_len = INF
        # 初始化最小环路径
        min_cycle_path = []
    
        # Floyd-Warshall 算法核心部分
        # k 作为中间节点 (0-based index)
        for k in range(N):
            # 在更新 dis[i][j] 之前，检查通过节点 k 是否能形成更小的环
            # 环由 i -> k -> j -> ... -> i 组成
            # 这里的 dis[i][j] 是在考虑节点 0 到 k-1 作为中间节点时的最短路径
            # C++ 代码中使用 i < k 和 j < i 的循环顺序，这里也遵循这个逻辑 (0-based)
            for i in range(k):  # 0 <= i < k
                for j in range(i):  # 0 <= j < i
                    # 检查 i, k, j 是否构成一个环，并且通过 dis[i][j] 连接
                    # 确保原始边 g[i][k] 和 g[k][j] 存在 (不为 INF)
                    # 并且 i 到 j 的最短路径 dis[i][j] 存在 (不为 INF)
                    if g[i][k] != INF and g[k][j] != INF and dis[i][j] != INF:
                        current_cycle_len = g[i][k] + g[k][j] + dis[i][j]
                        if current_cycle_len < min_cycle_len:
                            min_cycle_len = current_cycle_len
                            # 重构路径
                            path = [0] * (N + 5)  # 临时存储路径的数组，长度足够大
                            cnt = 0
                            # 按照 i, k, j 的顺序加入路径
                            path[cnt] = i
                            cnt += 1
                            path[cnt] = k
                            cnt += 1
                            path[cnt] = j
                            cnt += 1
                            # 获取 j 到 i 的最短路径上的中间节点 (使用之前计算的 dis 和 pos)
                            cnt = get_path(j, i, pos, path, cnt)
                            # 提取实际路径节点 (去除未使用的部分)
                            # 将 0-based 索引转换为 1-based
                            min_cycle_path = [node + 1 for node in path[:cnt]]
    
            # 标准 Floyd-Warshall 更新最短路径
            for i in range(N):
                for j in range(N):
                    if (
                        dis[i][k] != INF
                        and dis[k][j] != INF
                        and dis[i][j] > dis[i][k] + dis[k][j]
                    ):
                        dis[i][j] = dis[i][k] + dis[k][j]
                        # 记录从 i 到 j 的最短路径经过 k
                        pos[i][j] = k
    
        return min_cycle_len, min_cycle_path
    
    
    # --- 主程序入口 ---
    if __name__ == "__main__":
        # 读取节点数 n 和边数 m
        n, m = map(int, sys.stdin.readline().split())
    
        # 读取边信息
        edges = []
        for _ in range(m):
            u, v, w = map(int, sys.stdin.readline().split())
            edges.append((u, v, w))
    
        # 查找最小环
        min_len, path = find_minimum_cycle_undirected(n, edges)
    
        # 输出结果
        if min_len == INF:
            print("No solution.")
        else:
            # 打印路径节点 (1-based index)，用空格分隔
            print(" ".join(map(str, path)))
    ```

## 例题 2

GDOI2018 Day2 巡逻

给出一张 $n$ 个点的无负权边无向图，要求执行 $q$ 个操作，三种操作

1.  删除一个图中的点以及与它有关的边
2.  恢复一个被删除点以及与它有关的边
3.  询问点 $x$ 所在的最小环大小

对于 $50\%$ 的数据，有 $n,q \le 100$

对于每一个点 $x$ 所在的简单环，都存在两条与 $x$ 相邻的边，删去其中的任意一条，简单环将变为简单路径。

那么枚举所有与 $x$ 相邻的边，每次删去其中一条，然后跑一次 Dijkstra。

或者直接对每次询问跑一遍 Floyd 求最小环，$O(qn^3)$

对于 $100\%$ 的数据，有 $n,q \le 400$。

还是利用 Floyd 求最小环的算法。

若没有删除，删去询问点将简单环裂开成为一条简单路。

然而第二步的求解改用 Floyd 来得出。

那么答案就是要求出不经过询问点 $x$ 的情况下任意两点之间的距离。

怎么在线？

强行离线，利用离线的方法来避免删除操作。

将询问按照时间顺序排列，对这些询问建立一个线段树。

每个点的出现时间覆盖所有除去询问该点的时刻外的所有询问，假设一个点被询问 $x$ 次，则它的出现时间可以视为 $x + 1$ 段区间，插入到线段树上。

完成之后遍历一遍整棵线段树，在经过一个点时存储一个 Floyd 数组的备份，然后加入被插入在这个区间上的所有点，在离开时利用备份数组退回去即可。

这个做法的时间复杂度为 $O(qn^2\log q)$。

还有一个时间复杂度更优秀的在线做法。

对于一个对点 $x$ 的询问，我们以 $x$ 为起点跑一次最短路，然后把最短路树建出来，顺便处理出每个点是在 $x$ 的哪棵子树内。

那么一定能找出一条非树边，满足这条非树边的两个端点在根的不同子树中，使得这条非树边 $+$ 两个端点到根的路径就是最小环。

证明：

显然最小环包含至少两个端点在根的不同子树中一条非树边。

假设这条边为 $(u,v)$，那么最短路树上 $x$ 到 $u$ 的路径是所有 $x$ 到 $u$ 的路径中最短的那条，$x$ 到 $v$ 的路径也是最短的那条，那么 $x\to u\to v\to x$ 这个环肯定不会比最小环要长。

那么就可以枚举所有非树边，更新答案。

每次询问的复杂度为跑一次单源最短路的复杂度，为 $O(n^2)$。

总时间复杂度为 $O(qn^2)$。
