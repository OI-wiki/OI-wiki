BFS 是图论中的一种遍历算法，详见 [BFS](../graph/bfs.md)。

BFS 在搜索中也很常用，将每个状态对应为图中的一个点即可。其主要思想是从起始节点出发，逐层向外扩展，先访问离起点较近的节点，再访问较远的节点。BFS 常用于求最短路径、判断连通性等问题。

## 2. 算法原理

BFS 使用队列存储待访问的节点，其基本流程如下：

1.  **初始化**：将起始节点标记为已访问并入队。
2.  **循环处理**：只要队列不为空，就重复以下操作：
    -   从队列中取出一个节点作为当前节点。
    -   遍历当前节点的所有邻接节点，若该节点未被访问，则标记为已访问并加入队列。

这种策略确保了节点是按距离递增的顺序被访问。

***

## 3. 伪代码

    function BFS(Graph, start):
        创建队列 Q
        将 start 标记为已访问，并将 start 入队 Q
        while Q 不为空:
            current = Q.dequeue()
            for each neighbor of current:
                if neighbor 未访问:
                    标记 neighbor 为已访问
                    Q.enqueue(neighbor)

***

## 4. 示例代码

### 4.1 C++ 示例

下面是一段 C++ 实现 BFS 的代码示例，适用于无权图求最短路径问题：

```cpp
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

const int MAXN = 1000;
vector<int> adj[MAXN];  // 邻接表表示图
bool visited[MAXN] = {false};
int dist[MAXN] = {0};

void bfs(int start) {
  queue<int> q;
  visited[start] = true;
  dist[start] = 0;
  q.push(start);

  while (!q.empty()) {
    int u = q.front();
    q.pop();
    // 遍历节点 u 的所有邻接节点
    for (int v : adj[u]) {
      if (!visited[v]) {
        visited[v] = true;
        dist[v] = dist[u] + 1;
        q.push(v);
      }
    }
  }
}

int main() {
  int n, m;
  cout << "请输入节点数和边数:" << endl;
  cin >> n >> m;
  cout << "请输入每条边的两个端点 (节点编号从 0 到 n-1):" << endl;
  for (int i = 0; i < m; i++) {
    int u, v;
    cin >> u >> v;
    // 对于无向图，将边加入双向邻接表；若为有向图，请去掉其中一行
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  int start;
  cout << "请输入起始节点:" << endl;
  cin >> start;
  bfs(start);

  cout << "各节点到起始节点的最短距离:" << endl;
  for (int i = 0; i < n; i++) {
    cout << "节点 " << i << ": " << dist[i] << endl;
  }
  return 0;
}
```

### 4.2 Python 示例

以下是使用 Python 实现 BFS 的示例代码，利用 `deque` 提高队列操作效率：

```python
from collections import deque


def bfs(graph, start):
    visited = set()
    queue = deque([start])
    visited.add(start)
    dist = {start: 0}

    while queue:
        u = queue.popleft()
        for v in graph.get(u, []):
            if v not in visited:
                visited.add(v)
                dist[v] = dist[u] + 1
                queue.append(v)
    return dist


if __name__ == "__main__":
    # 使用字典来表示图的邻接表
    graph = {0: [1, 2], 1: [0, 3, 4], 2: [0, 4], 3: [1, 5], 4: [1, 2, 5], 5: [3, 4]}
    start = 0
    distances = bfs(graph, start)
    for node, d in distances.items():
        print(f"节点 {node} 到起始节点 {start} 的距离为: {d}")
```

参考资料

[GeeksforGeeks: BFS for Graph](https://www.geeksforgeeks.org/breadth-first-search-or-bfs-for-a-graph/)
