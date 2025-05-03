## 引入

BFS（广度优先搜索）为图论中的基础算法，详见 [BFS（图论）](../graph/bfs.md) 页面。在 **搜索算法** 中，该算法通常指利用队列结构逐层扩展状态的搜索方式，与图论中的 BFS 算法思想一致，特别适合求解 **最短路径** 或 **最少步骤** 类问题。

## 解释

考虑以下经典例题：

???+ note " 例题 [洛谷 B3625 迷宫寻路](https://www.luogu.com.cn/problem/B3625)"
    在一个 $n \times m$ 的迷宫矩阵中，`.` 表示可通行区域，`#` 表示障碍物。从起点 $(1,1)$ 出发，每次可向上下左右四个方向移动，问是否能到达终点 $(n,m)$。

BFS 的核心思想是 **按层扩展**，从起点开始逐层扫描可到达的位置。首次遇到终点时的路径长度即为最短路径。这种方式保证了搜索的层次性与最优性。

在实际执行中，BFS 会从起点出发，先访问起点的所有直接可到达节点，这些可到达节点构成了搜索的第一层；接着，再以这些可到达节点为新的起点，依次访问它们的邻居，形成第二层；以此类推，不断向外扩展，直至找到目标节点或遍历完所有可达节点。这个过程中，算法会借助队列和访问数组，将每一层新发现的节点（访问数组中还没有记录过的）依次入队，确保同一层的节点按照访问顺序依次被处理，从而严格遵循「按层扩展」的逻辑。

BFS 非常擅于快速求解 **最短路径** 或 **最少步骤**。当算法在某一层首次遇到目标时，此时经过的路径长度（步骤数）必然是最短的。这是因为 BFS 算法的按层扩展机制保证了每个节点都是通过最少的步数被访问到：就像从起点出发，沿着最直接的路径不断搜索，直到抵达终点，不会出现绕路或走多余步骤的情况。在同一个问题中，BFS 通常也比 DFS 的效率更高。

实现时需要维护一个队列来存储待处理的坐标，并配合访问标记数组避免重复计算。一个节点扩展可到达节点的时候，需要向上下左右拓展，这四个方向为 $(x, y + 1)$，$(x, y - 1)$，$(x + 1, y)$，$(x - 1, y)$，在代码中使用了方向数组。

代码如下：

???+ note "实现"
    ```cpp
    #include <iostream>
    #include <queue>
    using namespace std;
    
    char a[110][110];    // 存储迷宫地图
    bool vis[110][110];  // 记录访问状态
    int n, m;            // 迷宫尺寸
    
    struct node {
      int x, y;
    };  // 定义坐标结构体
    
    int dx[] = {0, 0, 1, -1}, dy[] = {1, -1, 0, 0};  // 方向数组（右左上下）
    
    // 检查坐标是否合法
    bool chk(int x, int y) {
      return (x >= 1 && x <= n && y >= 1 && y <= m  // 边界检查
              && !vis[x][y]                         // 未访问过
              && a[x][y] != '#');                   // 不是障碍物
    }
    
    bool bfs() {
      queue<node> q;
      q.push({1, 1});  // 起点入队
      vis[1][1] = 1;   // 标记起点已访问
      while (!q.empty()) {
        node p = q.front();  // 取出队首坐标
        q.pop();
        int px = p.x, py = p.y;
        if (px == n && py == m) return true;  // 到达终点立即返回
        // 向四个方向扩展
        for (int i = 0; i < 4; ++i) {
          int nx = px + dx[i], ny = py + dy[i];
          if (chk(nx, ny)) {   // 合法性检查
            q.push({nx, ny});  // 新坐标入队
            vis[nx][ny] = 1;   // 标记已访问
          }
        }
      }
      return false;
    }
    
    // 主函数
    int main() {
      cin >> n >> m;
      for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j) cin >> a[i][j];
      cout << (bfs() ? "Yes" : "No");
      return 0;
    }
    ```

## 例题

???+ note " 例题 [洛谷 P1135 奇怪的电梯](https://www.luogu.com.cn/problem/P1135)"
    ```cpp
    #include <bits/stdc++.h>
    using namespace std;
    const int N = 210;
    int n, a, b, k[N], d[N];
    
    int main() {
      cin >> n >> a >> b;
      for (int i = 1; i <= n; ++i) cin >> k[i];
      queue<int> q;
      q.push(a);
      while (!q.empty()) {
        int x = q.front();
        q.pop();
        if (x == b) {
          cout << d[x];
          return 0;
        }
        int y = x + k[x];
        if (y <= n) {
          d[y] = d[x] + 1;
          q.push(y);
        }
        y = x - k[x];
        if (y >= 1) {
          d[y] = d[x] + 1;
          q.push(y);
        }
      }
      cout << -1;
      return 0;
    }
    ```
