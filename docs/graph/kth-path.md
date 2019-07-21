## 问题描述

给定一个有 $n$ 个结点， $m$ 条边的有向图，求从 $s$ 到 $t$ 的所有不同路径中的第 $k$ 短路径的长度。

## A\* 算法

A\* 算法通过定义一个对当前状态 $x$ 的估价函数 $f(x)=g(x)+h(x)$ ，其中 $g(x)$ 为从初始状态到达当前状态的实际代价， $h(x)$ 为从当前状态到达目标状态的最佳路径的估计代价。每次取出 $f(x)$ 最优的状态 $x$ ，扩展其所有子状态，可以用 **优先队列** 来维护这个值。

在求解 $k$ 短路问题时，令 $h(x)$ 为从当前结点到达终点 $t$ 的最短路径长度。可以通过在反向图上对结点 $t$ 跑单源最短路预处理出对每个结点的这个值。

由于设计的距离函数和估价函数，对于每个状态需要记录两个值，为当前到达的结点 $x$ 和已经走过的距离 $g(x)$ ，将这种状态记为 $(x,g(x))$ 。

开始我们将初始状态 $(s,0)$ 加入优先队列。每次我们取出估价函数 $f(x)=g(x)+h(x)$ 最小的一个状态，枚举该状态到达的结点 $x$ 的所有出边，将对应的子状态加入优先队列。当我们访问到一个结点第 $k$ 次时，对应的状态的 $g(x)$ 就是从 $x$ 到该结点的第 $k$ 短路。

优化：由于只需要求出从初始结点到目标结点的第 $k$ 短路，所以已经取出的状态到达一个结点的次数大于 $k$ 次时，可以不扩展其子状态。因为之前 $k$ 次已经形成了 $k$ 条合法路径，当前状态不会影响到最后的答案。

当图的形态是一个 $n$ 元环的时候，该算法最坏是 $O(nk\log_2 n)$ 的。但是这种算法可以在相同的复杂度内求出从起始点 $s$ 到每个结点的前 $k$ 短路。

### 参考实现

```cpp
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;
const int maxn = 5010;
const int maxm = 400010;
const int inf = 2e9;
int n, m, k, u, v, ww, H[maxn], cnt[maxn], ans;
int cur, h[maxn], nxt[maxm], p[maxm], w[maxm];
int cur1, h1[maxn], nxt1[maxm], p1[maxm], w1[maxm];
bool tf[maxn];
void add_edge(int x, int y, double z) {
  cur++;
  nxt[cur] = h[x];
  h[x] = cur;
  p[cur] = y;
  w[cur] = z;
}
void add_edge1(int x, int y, double z) {
  cur1++;
  nxt1[cur1] = h1[x];
  h1[x] = cur1;
  p1[cur1] = y;
  w1[cur1] = z;
}
struct node {
  int x, v;
  bool operator<(node a) const { return v + H[x] > a.v + H[a.x]; }
};
priority_queue<node> q;
struct node2 {
  int x, v;
  bool operator<(node2 a) const { return v > a.v; }
} x;
priority_queue<node2> Q;
int main() {
  scanf("%d%d%d", &n, &m, &k);
  while (m--) {
    scanf("%d%d%d", &u, &v, &ww);
    add_edge(u, v, ww);
    add_edge1(v, u, ww);
  }
  for (int i = 1; i < n; i++) H[i] = inf;
  Q.push({n, 0});
  while (!Q.empty()) {
    x = Q.top();
    Q.pop();
    if (tf[x.x]) continue;
    tf[x.x] = true;
    H[x.x] = x.v;
    for (int j = h1[x.x]; j; j = nxt1[j]) Q.push({p1[j], x.v + w1[j]});
  }
  q.push({1, 0});
  while (!q.empty()) {
    node x = q.top();
    q.pop();
    cnt[x.x]++;
    if (x.x == n && cnt[x.x] == k) {
      printf("%d\n", ans);
      return 0;
      ans++;
    }
    if (cnt[x.x] > k) continue;
    for (int j = h[x.x]; j; j = nxt[j]) q.push({p[j], x.v + w[j]});
  }
  printf("%d\n", ans);
  return 0;
}
```
