author: Ir1d, greyqz, yjl9903, Anguei, Marcythm, ChungZH, Xeonacid, ylxmf2005

BFS 全称是 [Breadth First Search](https://en.wikipedia.org/wiki/Breadth-first_search)，中文名是宽度优先搜索，也叫广度优先搜索。

是图上最基础、最重要的搜索算法之一。

所谓宽度优先。就是每次都尝试访问同一层的节点。
如果同一层都访问完了，再访问下一层。

这样做的结果是，BFS 算法找到的路径是从起点开始的 **最短** 合法路径。换言之，这条路径所包含的边数最小。

在 BFS 结束时，每个节点都是通过从起点到该点的最短路径访问的。

算法过程可以看做是图上火苗传播的过程：最开始只有起点着火了，在每一时刻，有火的节点都向它相邻的所有节点传播火苗。

## 实现

下文中 C++ 与 Python 的代码实现是基于链式前向星的存图方式，其实现可参考 [图的存储](./save.md) 页面。

=== "伪代码"
    ```text
    bfs(s) {
      q = new queue()
      q.push(s), visited[s] = true
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

=== "C++"
    ```cpp
    void bfs(int u) {
      while (!Q.empty()) Q.pop();
      Q.push(u);
      vis[u] = 1;
      d[u] = 0;
      p[u] = -1;
      while (!Q.empty()) {
        u = Q.front();
        Q.pop();
        for (int i = head[u]; i; i = e[i].nxt) {
          if (!vis[e[i].to]) {
            Q.push(e[i].to);
            vis[e[i].to] = 1;
            d[e[i].to] = d[u] + 1;
            p[e[i].to] = u;
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

=== "Python"
    ```python
    from queue import Queue
    
    def bfs(u):
        Q = Queue()
        Q.put(u)
        vis[u] = True
        d[u] = 0
        p[u] = -1
        while Q.qsize() != 0:
            u = Q.get()
            i = head[u]
            while i:
                if vis[e[i].to] == False:
                    Q.put(e[i].to)
                    vis[e[i].to] = True
                    d[e[i].to] = d[u] + 1
                    p[e[i].to] = u
                i = e[i].nxt
    
    def restore(x):
        res = []
        v = x
        while v != -1:
            res.append(v)
            v = p[v]
        res.reverse()
        for i in range(0, len(res)):
            print(res[i])
    ```

具体来说，我们用一个队列 Q 来记录要处理的节点，然后开一个布尔数组 `vis[]` 来标记是否已经访问过某个节点。

开始的时候，我们将所有节点的 `vis` 值设为 0，表示没有访问过；然后把起点 s 放入队列 Q 中并将 `vis[s]` 设为 1。

之后，我们每次从队列 Q 中取出队首的节点 u，然后把与 u 相邻的所有节点 v 标记为已访问过并放入队列 Q。

循环直至当队列 Q 为空，表示 BFS 结束。

在 BFS 的过程中，也可以记录一些额外的信息。例如上述代码中，d 数组用于记录起点到某个节点的最短距离（要经过的最少边数），p 数组记录是从哪个节点走到当前节点的。

有了 d 数组，可以方便地得到起点到一个节点的距离。

有了 p 数组，可以方便地还原出起点到一个点的最短路径。上述代码中的 `restore` 函数使用该数组依次输出从起点到节点 x 的最短路径所经过的节点。

时间复杂度 $O(n + m)$

空间复杂度 $O(n)$（`vis` 数组和队列）

## open-closed 表

在实现 BFS 的时候，本质上我们把未被访问过的节点放在一个称为 open 的容器中，而把已经访问过了的节点放在一个称为 closed 容器中。

## 在树/图上 BFS

### BFS 序列

类似 DFS 序列，BFS 序列是指在 BFS 过程中访问的节点编号的序列。

### 一般图上 BFS

如果原图不连通，只能访问到从起点出发能够到达的点。

BFS 序列通常也不唯一。

类似的我们也可以定义 BFS 树：在 BFS 过程中，通过记录每个节点从哪个点访问而来，可以建立一个树结构，即为 BFS 树。

## 应用

-   在一个无权图上求从起点到其他所有点的最短路径。
-   在 $O(n+m)$ 时间内求出所有连通块。（我们只需要从每个没有被访问过的节点开始做 BFS，显然每次 BFS 会走完一个连通块）
-   如果把一个游戏的动作看做是状态图上的一条边（一个转移），那么 BFS 可以用来找到在游戏中从一个状态到达另一个状态所需要的最小步骤。
-   在一个有向无权图中找最小环。（从每个点开始 BFS，在我们即将抵达一个之前访问过的点开始的时候，就知道遇到了一个环。图的最小环是每次 BFS 得到的最小环的平均值。）
-   找到一定在 $(a, b)$ 最短路上的边。（分别从 a 和 b 进行 BFS，得到两个 d 数组。之后对每一条边 $(u, v)$，如果 $d_a[u]+1+d_b[v]=d_a[b]$，则说明该边在最短路上）
-   找到一定在 $(a, b)$ 最短路上的点。（分别从 a 和 b 进行 BFS，得到两个 d 数组。之后对每一个点 v，如果 $d_a[v]+d_b[v]=d_a[b]$，则说明该点在某条最短路上）
-   找到一条长度为偶数的最短路。（我们需要一个构造一个新图，把每个点拆成两个新点，原图的边 $(u, v)$ 变成 $((u, 0), (v, 1))$ 和 $((u, 1), (v, 0))$。对新图做 BFS，$(s, 0)$ 和 $(t, 0)$ 之间的最短路即为所求）
-   在一个边权为 0/1 的图上求最短路，见下方双端队列 BFS。

## 双端队列 BFS

如果你不了解双端队列 `deque` 的话，请参阅 [deque 相关章节](../../lang/csl/sequence-container/#deque)。

双端队列 BFS 又称 0-1 BFS。

### 适用范围

边权值为可能有，也可能没有（由于 BFS 适用于权值为 1 的图，所以一般权值是 0 或 1），或者能够转化为这种边权值的最短路问题。

例如在走迷宫问题中，你可以花 1 个金币走 5 步，也可以不花金币走 1 步，这就可以用 0-1 BFS 解决。

### 实现

一般情况下，我们把没有权值的边扩展到的点放到队首，有权值的边扩展到的点放到队尾。这样即可保证像普通 BFS 一样整个队列队首到队尾权值单调不下降。

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

此题目正解不是 0-1 BFS，但是适用 0-1 BFS，减小思维强度，赛时许多大佬都是这么做的。

做法很简单，一个方向射出不需要花费（0），而往四个方向射出需要花费（1），然后直接来就可以了。

#### 代码

```cpp
--8<-- "docs/graph/code/bfs/bfs_1.cpp"
```

## 优先队列 BFS

优先队列，相当于一个二叉堆，STL 中提供了 [`std::priority_queue`](../lang/csl/container-adapter.md)，可以方便我们使用优先队列。

在基于优先队列的 BFS 中，我们每次从队首取出代价最小的结点进行进一步搜索。容易证明这个贪心思想是正确的，因为从这个结点开始扩展的搜索，一定不会更新原来那些代价更高的结点。换句话说，其余那些代价更高的结点，我们不回去考虑更新它。

当然，每个结点可能会被入队多次，只是每次入队的代价不同。当该结点第一次从优先队列中取出，以后便无需再在该结点进行搜索，直接忽略即可。所以，优先队列的 BFS 当中，每个结点只会被处理一次。

相对于普通队列的 BFS，时间复杂度多了一个 $\log n$，毕竟要维护这个优先队列嘛。不过普通 BFS 有可能每个结点入队、出队多次，时间复杂度会达到 $O(n^2)$，不是 $O(n)$。所以优先队列 BFS 通常还是快的。

诶？这怎么听起来这么像堆优化的 [Dijkstra](./shortest-path.md#dijkstra-算法) 算法呢？事实上，堆优化 Dijkstra 就是优先队列 BFS。

## 习题

-   [「NOIP2017」奶酪](https://uoj.ac/problem/332)

双端队列 BFS：

-   [CF1063B. Labyrinth](https://codeforces.com/problemset/problem/1063/B)
-   [CF173B. Chamber of Secrets](https://codeforces.com/problemset/problem/173/B)
-   [「BalticOI 2011 Day1」打开灯泡 Switch the Lamp On](https://loj.ac/p/2632)

## 参考

<https://cp-algorithms.com/graph/breadth-first-search.html>
