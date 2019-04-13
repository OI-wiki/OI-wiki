BFS 全称是 [Breadth First Search](https://en.wikipedia.org/wiki/Breadth-first_search)，中文名是宽度优先搜索，也叫广度优先搜索。

是图上最基础、最重要的搜索算法之一。

所谓宽度优先。就是每次都尝试访问同一层的节点。
如果同一层都访问完了，再访问下一层。

这样做的结果是，BFS 算法找到的路径是从起点开始的 **最短** 合法路径。换言之，这条路所包含的边数最小。

在 BFS 结束时，每个节点都是通过从起点到该点的最短路径访问的。

算法过程可以看做是图上火苗传播的过程：最开始只有起点着火了，在每一时刻，有火的节点都向它相邻的所有节点传播火苗。

## 实现

伪代码：

```text
bfs(s) {
  q = new queue()
  q.push(s)), visited[s] = true
  while (!q.empty()) {
    u = q.pop()
    for each edge(u, v) {
      if (!visited[v]) {
        q.push(v)
        visited[v] = true
      }
    }
  }
}
```

C++：

```c++
void bfs(int u) {
  while (!Q.empty()) Q.pop();
  Q.push(u);
  vis[u] = 1;
  d[u] = 0;
  p[u] = -1;
  while (!Q.empty()) {
    u = Q.pop() {
      for (int i = head[u]; i; i = e[i].x) {
        if (!vis[e[i].t]) {
          Q.push(e[i].t);
          vis[e[i].t] = 1;
          d[e[i].t] = d[u] + 1;
          p[e[i].t] = u;
        }
      }
    }
  }
}
void restore(int x) {
  vector<int> res;
  for (int v = x; v != -1; v = p[v]) {
    res.push_back(v);
  }
  std::reverse(res.begin(), res.end());
  for (int i = 0; i < res.size(); ++i) printf("%d", res[i]);
  puts("");
}
```

具体来说，我们用一个队列 Q 来记录要处理的节点，然后开一个 $vis[]$ 布尔数组来标记某个节点是否已经访问过了。

开始的时候，我们把起点 s 以外的节点的 vis 值设为 0，意思是没有访问过。然后把起点 s 放入队列 Q 中。

之后，我们每次从队列 Q 中取出队首的点 u，把 u 相邻的所有点 v 标记为已经访问过了并放入队列 Q。

直到某一时刻，队列 Q 为空，这时 BFS 结束。

在 BFS 的过程中，也可以记录一些额外的信息。比如上面的代码中，d 数组是用来记录某个点到起点的距离（要经过的最少边数），p 数组是记录从起点到这个点的最短路上的上一个点。

有了 d 数组，可以方便地得到起点到一个点的距离。

有了 p 数组，可以方便地还原出起点到一个点的最短路径。上面的 restore 函数就是在做这件事：restore(x) 输出的是从起点到 x 这个点所经过的点。

时间复杂度 $O(n + m)$ 

空间复杂度 $O(n)$ （vis 数组和队列）

## open-closed 表

在实现 BFS 的时候，我们把未被访问过的节点放在一个称为 open 的容器中，而把已经访问过了的节点放在 closed 容器中。

## [在树/图上 BFS](/graph/traverse)

## 应用

-   在一个无权图上求从起点到其他所有点的最短路径。
-   在 $O(n+m)$ 时间内求出所有连通块。（我们只需要从每个没有被访问过的节点开始做 BFS，显然每次 BFS 会走完一个连通块）
-   如果把一个游戏的动作看做是状态图上的一条边（一个转移），那么 BFS 可以用来找到在游戏中从一个状态到达另一个状态所需要的最小步骤。
-   在一个边权为 0/1 的图上求最短路。（需要修改入队的过程，如果某条边权值为 0，且可以减小边的终点到图的起点的距离，那么把边的起点加到队列首而不是队列尾）
-   在一个有向无权图中找最小环。（从每个点开始 BFS，在我们即将抵达一个之前访问过的点开始的时候，就知道遇到了一个环。图的最小环是每次 BFS 得到的最小环的平均值。）
-   找到一定在 $(a, b)$ 最短路上的边。（分别从 a 和 b 进行 BFS，得到两个 d 数组。之后对每一条边 $(u, v)$ ，如果 $d_a[u]+1+d_b[v]=d_a[b]$ ，则说明该边在最短路上）
-   找到一定在 $(a, b)$ 最短路上的点。（分别从 a 和 b 进行 BFS，得到两个 d 数组。之后对每一个点 v，如果 $d_a[u]+d_b[v]=d_a[b]$ ，则说明该点在最短路上）
-   找到一条长度为偶数的最短路。（我们需要一个构造一个新图，把每个点拆成两个新点，原图的边 $(u, v)$ 变成 $((u, 0), (v, 1))$ 和 $((u, 1), (v, 0))$ 。对新图做 BFS， $(s, 0)$ 和 $(t, 0)$ 之间的最短路即为所求）

## 例题

-   [LOJ#2317.「NOIP2017」奶酪](https://loj.ac/problem/2317)

## 参考

<https://cp-algorithms.com/graph/breadth-first-search.html>

## 双端队列 BFS

如果你不了解双端队列 `deque` 的话，请到 STL-queue 中学习。

双端队列 BFS 又称 0-1 BFS

### 适用范围

边权值为可能有，也可能没有（由于 BFS 适用于权值为 1 的图，所以一般是 0 or 1），或者能够转化为这种边权值的最短路问题。

例如在走迷宫问题中，你可以花 1 个金币走 5 步，也可以不花金币走 1 步，这就可以用 0-1 BFS 解决。

### 实现

一般情况下，我们把没有权值的边扩展到的点放到队首，有权值的边扩展到的点放到队尾。这样即可保证在整个队列中，像普通 BFS 一样，越靠近队首，权值越小，且权值零一之间有分隔。

下面是伪代码：

```cpp
while (队列不为空) {
  int u = 队首;
  弹出队首;
  for (枚举 u 的邻居) {
    更新数据
    if (...)
      添加到队首;
    else
      添加到队尾;
  }
}
```

### 例题

### [Codeforces 173B](http://codeforces.com/problemset/problem/173/B)

一个 $n \times m$ 的图，现在有一束激光从左上角往右边射出，每遇到 '#'，你可以选择光线往四个方向射出，或者什么都不做，问最少需要多少个 '#' 往四个方向射出才能使光线在第 $n$ 行往右边射出。

此题目正解不是 0-1 BFS 但是适用 0-1 BFS 可以不需要思考过程，赛时许多大佬都是这么做的。

做法很简单，一个方向射出不需要花费（0），而往四个方向射出需要花费（1），然后直接来就可以了。

#### Code

```cpp
#include <bits/stdc++.h>
using namespace std;
#define INF (1 << 29)
int n, m;
char grid[1001][1001];
int dist[1001][1001][4];
int vis[1001][1001][4];
int fx[] = {1, -1, 0, 0};
int fy[] = {0, 0, 1, -1};
deque<int> q;
void add_front(int x, int y, int dir, int d) {
  if (d < dist[x][y][dir]) {
    dist[x][y][dir] = d;
    q.push_front(dir);
    q.push_front(y);
    q.push_front(x);
  }
}
void add_back(int x, int y, int dir, int d) {
  if (d < dist[x][y][dir]) {
    dist[x][y][dir] = d;
    q.push_back(x);
    q.push_back(y);
    q.push_back(dir);
  }
}
int main() {
  cin >> n >> m;
  for (int i = 0; i < n; i++) cin >> grid[i];

  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++)
      for (int k = 0; k < 4; k++) dist[i][j][k] = INF;

  add_front(n - 1, m - 1, 3, 0);

  while (!q.empty()) {
    int x = q[0], y = q[1], dir = q[2];
    q.pop_front();
    q.pop_front();
    q.pop_front();
    if (vis[x][y][dir]) continue;
    vis[x][y][dir] = true;
    int d = dist[x][y][dir];
    int nx = x + fx[dir], ny = y + fy[dir];
    if (nx >= 0 && nx < n && ny >= 0 && ny < m) add_front(nx, ny, dir, d);
    if (grid[x][y] == '#')
      for (int i = 0; i < 4; i++)
        if (i != dir) add_back(x, y, i, d + 1);
  }
  if (dist[0][0][3] == INF)
    cout << -1 << endl;
  else
    cout << dist[0][0][3] << endl;
  return 0;
}
```

## 优先队列 BFS

优先队列，相当于一个二叉堆，STL 中提供了[ `std::priority_queue` ](/ds/stl/priority_queue/)，可以方便我们使用优先队列。

在基于优先队列的 BFS 中，我们每次从队首取出代价最小的结点进行进一步搜索。容易证明这个贪心思想是正确的，因为从这个结点开始扩展的搜索，一定不会更新原来那些代价更高的结点。换句话说，其余那些代价更高的结点，我们不回去考虑更新它。

当然，每个结点可能会被入队多次，只是每次入队的代价不同。当该结点第一次从优先队列中取出，以后便无需再在该结点进行搜索，直接忽略即可。所以，优先队列的 BFS 当中，每个结点只会被处理一次。

相对于普通队列的 BFS，时间复杂度多了一个 $\log$ ，毕竟要维护这个优先队列嘛。不过普通 BFS 有可能每个结点入队、出队多次，时间复杂度会达到 $O(n^2)$ ，不是 $O(n)$ 。所以优先队列 BFS 通常还是快的。

诶？这怎么听起来这么像堆优化的 [Dijkstra](/graph/shortest-path/#dijkstra) 算法呢？事实上，堆优化 Dijkstra 就是优先队列 BFS。
