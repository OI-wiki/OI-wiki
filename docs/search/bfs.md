BFS 是图论中的一种遍历算法，详见 [BFS](../graph/bfs.md)。

BFS 在搜索中也很常用，将每个状态对应为图中的一个点即可。从初始状态出发，先访问所有距离初始状态最近的节点，然后再依次扩展到更远的节点。由于搜索过程是逐层扩展，BFS 常用于解决 **无权图** 中的最短路径问题，并能保证找到最优解（步数最少）。
在状态空间搜索中，BFS 能够枚举所有可能状态，当状态数目不大时可以保证搜索的全面性和正确性。常见应用包括迷宫求解、棋盘问题、网络连通性判断等。

## 流程

1.  **初始化**：
    -   设定起始状态，将其标记为已访问。
    -   将起始状态加入队列。

2.  **循环扩展**：
    -   当队列不为空时，取出队头状态作为当前状态。
    -   判断当前状态是否为目标状态，如是则结束搜索。
    -   否则，对当前状态进行扩展，生成所有可能的后继状态，未访问状态标记为已访问并入队。

3.  **搜索结束**：
    -   如果队列为空仍未找到目标，则说明目标状态不可达。

## 伪代码

    function BFS_Search(initial_state):
        初始化队列 Q
        标记 initial_state 为已访问，并将 initial_state 入队 Q
        while Q 非空:
            current_state = Q.dequeue()
            if current_state 为目标状态:
                返回 current_state（或路径信息）
            for each next_state in 扩展(current_state):
                if next_state 未被访问:
                    标记 next_state 为已访问
                    Q.enqueue(next_state)
        返回 "目标不可达"

## 下面举一些例子，其实 oi 中经常出现的就是各种迷宫问题了

### C++ 示例

下面的 C++ 代码展示了如何在一个迷宫问题中利用 BFS 搜索最短路径。迷宫中 0 表示通路，1 表示障碍。

```cpp
#include <algorithm>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>
using namespace std;

const int N = 5;  // 迷宫行数
const int M = 5;  // 迷宫列数

// 迷宫地图：0 为通路，1 为障碍
int maze[N][M] = {{0, 0, 1, 0, 0},
                  {1, 0, 1, 0, 1},
                  {0, 0, 0, 0, 0},
                  {0, 1, 1, 1, 0},
                  {0, 0, 0, 1, 0}};

bool visited[N][M] = {false};
pair<int, int> parent[N][M];  // 用于记录路径

// 四个方向：上、下、左、右
int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};

bool isValid(int x, int y) {
  return x >= 0 && x < N && y >= 0 && y < M && maze[x][y] == 0;
}

void bfs(pair<int, int> start, pair<int, int> target) {
  queue<pair<int, int>> q;
  q.push(start);
  visited[start.first][start.second] = true;
  parent[start.first][start.second] = {-1, -1};

  while (!q.empty()) {
    auto current = q.front();
    q.pop();
    if (current == target) {
      cout << "目标已找到!" << endl;
      return;
    }
    for (int i = 0; i < 4; i++) {
      int nx = current.first + dx[i];
      int ny = current.second + dy[i];
      if (isValid(nx, ny) && !visited[nx][ny]) {
        visited[nx][ny] = true;
        parent[nx][ny] = current;
        q.push({nx, ny});
      }
    }
  }
  cout << "目标不可达." << endl;
}

void printPath(pair<int, int> target) {
  vector<pair<int, int>> path;
  for (pair<int, int> cur = target; cur.first != -1;
       cur = parent[cur.first][cur.second])
    path.push_back(cur);
  reverse(path.begin(), path.end());
  cout << "最短路径: ";
  for (auto p : path) cout << "(" << p.first << "," << p.second << ") ";
  cout << endl;
}

int main() {
  pair<int, int> start = {0, 0};
  pair<int, int> target = {4, 4};
  bfs(start, target);
  if (visited[target.first][target.second]) printPath(target);
  return 0;
}
```

### Python 示例

以下 Python 示例展示了如何利用 BFS 在迷宫中搜索目标，并输出最短路径。代码中使用 `deque` 实现队列以提高性能。

```python
from collections import deque


def bfs_search(maze, start, target):
    n, m = len(maze), len(maze[0])
    visited = [[False] * m for _ in range(n)]
    parent = [[None] * m for _ in range(n)]

    # 定义四个方向：上、下、左、右
    directions = [(-1, 0), (1, 0), (0, -1), (0, 1)]

    queue = deque([start])
    visited[start[0]][start[1]] = True
    parent[start[0]][start[1]] = (-1, -1)

    while queue:
        x, y = queue.popleft()
        if (x, y) == target:
            return parent  # 找到目标，返回路径记录信息
        for dx, dy in directions:
            nx, ny = x + dx, y + dy
            if (
                0 <= nx < n
                and 0 <= ny < m
                and maze[nx][ny] == 0
                and not visited[nx][ny]
            ):
                visited[nx][ny] = True
                parent[nx][ny] = (x, y)
                queue.append((nx, ny))
    return None  # 目标不可达


def reconstruct_path(parent, target):
    path = []
    cur = target
    while cur != (-1, -1):
        path.append(cur)
        cur = parent[cur[0]][cur[1]]
    return path[::-1]


if __name__ == "__main__":
    maze = [
        [0, 0, 1, 0, 0],
        [1, 0, 1, 0, 1],
        [0, 0, 0, 0, 0],
        [0, 1, 1, 1, 0],
        [0, 0, 0, 1, 0],
    ]
    start = (0, 0)
    target = (4, 4)

    parent = bfs_search(maze, start, target)
    if parent and parent[target[0]][target[1]] is not None:
        path = reconstruct_path(parent, target)
        print("最短路径:", path)
    else:
        print("目标不可达")
```

\## 注意

搜索过程中需对已访问的状态进行标记，避免重复访问和陷入死循环。BFS 需要存储当前层所有状态，对于大规模状态空间问题，需要评估内存占用。在某些问题中可结合剪枝或启发式策略（如 A\* 算法）对 BFS 进行优化，但会破坏层次遍历的纯粹性。

\## 参考

-   [GeeksforGeeks - Breadth First Search](https://www.geeksforgeeks.org/breadth-first-search-or-bfs-for-a-graph/)
