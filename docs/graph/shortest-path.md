## 定义

（还记得这些定义吗？在阅读下列内容之前，请务必了解[图论基础](/graph/basic)部分。）

-   路径
-   最短路
-   有向图中的最短路、无向图中的最短路
-   单源最短路、每对结点之间的最短路

## 性质

对于边权为正的图，任意两个结点之间的最短路，不会经过重复的结点。

对于边权为正的图，任意两个结点之间的最短路，不会经过重复的边。

对于边权为正的图，任意两个结点之间的最短路，任意一条的结点数不会超过 $n$ ，边数不会超过 $n-1$ 。

## Floyd 算法

是用来求任意两个结点之间的最短路的。

复杂度比较高，但是常数小，容易实现。（我会说只有三个 `for` 吗？）

适用于任何图，不管有向无向，边权正负，但是最短路必须存在。（不能有个负环）

### 实现

我们定义一个数组 `f[k][x][y]` ，表示只允许经过结点 $1$ 到 $k$ ，结点 $x$ 到结点 $y$ 的最短路长度。

很显然， `f[n][x][y]` 就是结点 $x$ 到结点 $y$ 的最短路长度。

我们来考虑怎么求这个数组

 `f[0][x][y]` ：边权，或者 $0$ ，或者 $+\infty$ （ `f[0][x][x]` 什么时候应该是 $+\infty$ ？）

 `f[k][x][y] = min(f[k-1][x][y], f[k-1][x][k]+f[k-1][k][y])` 

上面两行都显然是对的，然而这个做法空间是 $O(N^3)$ 。

但我们发现数组的第一维是没有用的，于是可以直接改成 `f[x][y] = min(f[x][y], f[x][k]+f[k][y])` ，

```c++
for (k = 1; k <= n; k++) {
  for (i = 1; i <= n; i++) {
    for (j = 1; j <= n; j++) {
      f[i][j] = min(f[i][j], f[i][k] + f[k][j]);
    }
  }
}
```

时间复杂度是 $O(N^3)$ ，空间复杂度是 $O(N^2)$ 。

### 应用

???+ question "给一个正权无向图，找一个最小权值和的环。"
    首先这一定是一个简单环。

    想一想这个环是怎么构成的。

    考虑环上编号最大的结点 u。

    `f[u-1][x][y]` 和 (u,x), (u,y)共同构成了环。

    在Floyd的过程中枚举u，计算这个和的最小值即可。

    $O(n^3)$。

???+question "已知一个有向图中任意两点之间是否有连边，要求判断任意两点是否联通。"

    该问题即是求**图的传递闭包**。

    我们只需要按照 Floyd 的过程，逐个加入点判断一下。

    只是此时的边的边权变为 $1/0$， 而取 $\min$ 变成了**与**运算。

    再进一步用 bitset 优化，复杂度可以到 $O(\frac{n^3}{w})$。

    ```c++
    //std::bitset<SIZE> f[SIZE];
    for (k = 1; k <= n; k++)
    	for (i = 1; i <= n; i++)
    	    if(f[i][k]) f[i] = f[i] & f[k];
    ```

* * *

## Bellman-Ford 算法

一种基于松弛（relax）操作的最短路算法。

支持负权。

能找到某个结点出发到所有结点的最短路，或者报告某些最短路不存在。

在国内 OI 界，你可能听说过的“SPFA”，就是 Bellman-Ford 算法的一种实现。（优化）

### 实现

假设结点为 $S$ 。

先定义 $dist(u)$ 为 $S$ 到 $u$ （当前）的最短路径长度。

 $relax(u,v)$ : $dist(v) = min(dist(v), dist(u) + edge\_len(u, v))$ .

 $relax$ 是从哪里来的呢？

三角形不等式： $dist(v) \leq dist(u) + edge\_len(u, v)$ 。

证明：反证法，如果不满足，那么可以用 $relax$ 操作来更新 $dist(v)$ 的值。

Bellman-Ford 算法如下：

```text
while (1) for each edge(u, v) relax(u, v);
```

当一次循环中没有 $relax$ 操作成功时停止。

每次循环是 $O(m)$ 的，那么最多会循环多少次呢？

答案是 $\infty$ ！（如果有一个 $S$ 能走到的负环就会这样）

但是此时某些结点的最短路不存在。

我们考虑最短路存在的时候。

由于一次 $relax$ 会使（被 $relax$ 的）最短路的边数至少 $+1$ ，而最短路的边数最多为 $n-1$ 。

所以最多（连续） $relax$  $n-1$ 次……（ $relax$ 一定是环环相扣的，不然之前就能被 $relax$ 掉）

所以最多循环 $n-1$ 次。

总时间复杂度 $O(NM)$ 。**（对于最短路存在的图）**

```text
relax(u, v) {
	dist[v] = min(dist[v], dist[u] + edge_len(u, v));
}
for (i = 1; i <= n; i++) {
	dist[i] = edge_len(S, i);
}
for (i = 1; i < n; i++) {
	for each edge(u, v) {
		relax(u, v);
	}
}
```

注：这里的 $edge\_len(u, v)$ 表示边的权值，如果该边不存在则为 $+\infty$ ， $u=v$ 则为 $0$ 。

### 应用

给一张有向图，问是否存在负权环。

做法很简单，跑 Bellman-Ford 算法，如果有个点被 $relax$ 成功了 $n$ 次，那么就一定存在。

如果 $n-1$ 次之内算法结束了，就一定不存在。

### 队列优化：SPFA

即 Shortest Path Faster Algorithm。

很多时候我们并不需要那么多无用的 $relax$ 操作。

很显然，只有上一次被 $relax$ 的结点，所连接的边，才有可能引起下一次的 $relax$ 。

那么我们用队列来维护“哪些结点可能会引起 $relax$ ”，就能只访问必要的边了。

```text
q = new queue();
q.push(S);
in_queue[S] = true;
while (!q.empty()) {
	u = q.pop();
	in_queue[u] = false;
	for each edge(u, v) {
		if (relax(u, v) && !in_queue[v]) {
			q.push(v);
			in_queue[v] = true;
		}
	}
}
```

SPFA 的时间复杂度为 $O(kM)~ (k\approx 2)$ （玄学），但**理论上界**为 $O(NM)$ ，精心设计的稠密图可以随便卡掉 SPFA，所以考试时谨慎使用（NOI 2018 卡 SPFA）。

#### SPFA 的优化之 SLF

即 Small Label First。

即在新元素加入队列时，如果队首元素权值大于新元素权值，那么就把新元素加入队首，否则依然加入队尾。

该优化在确实在一些图上有显著效果，其复杂度也有保证，但是如果有负权边的话，可以直接卡到指数级。

* * *

## Dijkstra 算法

Dijkstra 是个人名（荷兰姓氏）。

IPA:/ˈdikstrɑ/或/ˈdɛikstrɑ/。

这种算法只适用于非负权图，但是时间复杂度非常优秀。

也是用来求单源最短路径的算法。

### 实现

主要思想是，将结点分成两个集合：已确定最短路长度的，未确定的。

一开始第一个集合里只有 $S$ 。

然后重复这些操作：

（1） $relax$ 那些刚刚被加入第一个集合的结点的所有出边。

（2）从第二个集合中，选取一个最短路长度最小的结点，移到第一个集合中。

直到第二个集合为空，算法结束。

时间复杂度：只用分析集合操作， $n$ 次 `delete-min` ， $m$ 次 `decrease-key` 。

如果用暴力： $O(n^2 + m)$ 。

如果用堆： $O((n+m) \log m)$ 。

如果用线段树（ZKW 线段树）： $(O(n+m)\log n)$ 

如果用 Fibonacci 堆： $O(n \log n + m)$ （这就是为啥优秀了）。

等等，还没说正确性呢！

分两步证明：先证明任何时候第一个集合中的元素的 $dist$ 一定不大于第二个集合中的。

再证明第一个集合中的元素的最短路已经确定。

第一步，一开始时成立（基础），在每一步中，加入集合的元素一定是最大值，且是另一边最小值， $relax$ 又是加上非负数，所以仍然成立。（归纳）（利用非负权值的性质）

第二步，考虑每次加进来的结点，到他的最短路，上一步必然是第一个集合中的元素（否则他不会是第二个集合中的最小值，而且有第一步的性质），又因为第一个集合已经全部 $relax$ 过了，所以最短路显然确定了。

```text
H = new heap();
H.insert(S, 0);
dist[S] = 0;
for (i = 1; i <= n; i++) {
	u = H.delete_min();
	for each edge(u, v) {
		if (relax(u, v)) {
			H.decrease_key(v, dist[v]);
		}
	}
}
```

* * *

## 不同方法的比较

| Floyd      | Bellman-Ford | Dijkstra           |
| ---------- | ------------ | ------------------ |
| 每对结点之间的最短路 | 单源最短路        | 单源最短路              |
| 没有负环的图     | 任意图          | 非负权图               |
|  $O(N^3)$  |  $O(NM)$     |  $O((N+M)\log M)$  |

## 输出方案

开一个 `pre` 数组，在更新距离的时候记录下来后面的点是如何转移过去的，算法结束前再递归地输出路径即可。

比如 Floyd 就要记录 `pre[i][j] = k;` ，Bellman-Ford 和 Dijkstra 一般记录 `pre[v] = u` 。

## 拓展：分层图最短路

分层图最短路，一般模型为有 $k$ 次零代价通过一条路径，求总的最小花费。对于这种题目，我们可以采用 DP 相关的思想，设 $\text{dis}_{i, j}$ 表示当前从起点 $i$ 号结点，使用了 $j$ 次免费通行权限后的最短路径。显然， $\text{dis}$ 数组可以这么转移：

 $\text{dis}_{i, j} = \min\{\min\{\text{dis}_{from, j - 1}\}, \min\{\text{dis}_{from,j} + w\}\}$ 

其中， $from$ 表示 $i$ 的父亲节点， $w$ 表示当前所走的边的边权。当 $j - 1 \geq k$ 时， $\text{dis}_{from, j}$ = $\infty$ 。

事实上，这个 DP 就相当于把每个结点拆分成了 $k+1$ 个结点，每个新结点代表使用不同多次免费通行后到达的原图结点。换句话说，就是每个结点 $u_i$ 表示使用 $i$ 次免费通行权限后到达 $u$ 结点。

### 模板题：[\[JLOI2011\]飞行路线](https://www.luogu.org/problemnew/show/P4568)

题意：有一个 $n$ 个点 $m$ 条边的无向图，你可以选择 $k$ 条道路以零代价通行，求 $s$ 到 $t$ 的最小花费。

参考核心代码：

```cpp
struct State {    // 优先队列的结点结构体
  int v, w, cnt;  // cnt 表示已经使用多少次免费通行权限
  State() {}
  State(int v, int w, int cnt) : v(v), w(w), cnt(cnt) {}
  bool operator<(const State &rhs) const { return w > rhs.w; }
};

void dijkstra() {
  memset(dis, 0x3f, sizeof dis);
  dis[s][0] = 0;
  pq.push(State(s, 0, 0));  // 到起点不需要使用免费通行权，距离为零
  while (!pq.empty()) {
    const State top = pq.top();
    pq.pop();
    int u = top.v, nowCnt = top.cnt;
    if (done[u][nowCnt]) continue;
    done[u][nowCnt] = true;
    for (int i = head[u]; i; i = edge[i].next) {
      int v = edge[i].v, w = edge[i].w;
      if (nowCnt < k && dis[v][nowCnt + 1] > dis[u][nowCnt]) {  // 可以免费通行
        dis[v][nowCnt + 1] = dis[u][nowCnt];
        pq.push(State(v, dis[v][nowCnt + 1], nowCnt + 1));
      }
      if (dis[v][nowCnt] > dis[u][nowCnt] + w) {  // 不可以免费通行
        dis[v][nowCnt] = dis[u][nowCnt] + w;
        pq.push(State(v, dis[v][nowCnt], nowCnt));
      }
    }
  }
}

int main() {
  n = read(), m = read(), k = read();
  // 笔者习惯从 1 到 n 编号，而这道题是从 0 到 n - 1，所以要处理一下
  s = read() + 1, t = read() + 1;
  while (m--) {
    int u = read() + 1, v = read() + 1, w = read();
    add(u, v, w), add(v, u, w);  // 这道题是双向边
  }
  dijkstra();
  int ans = std::numeric_limits<int>::max();  // ans 取 int 最大值为初值
  for (int i = 0; i <= k; ++i)
    ans = std::min(ans, dis[t][i]);  // 对到达终点的所有情况取最优值
  println(ans);
}
```
