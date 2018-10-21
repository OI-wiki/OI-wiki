 ** 差分约束系统 ** 是一种特殊的 $n$ 元一次不等式组，它包含 $n$ 个变量 $x_1,x_2,...,x_n$ 以及 $m$ 个约束条件，每个约束条件是由两个其中的变量做差构成的，形如 $x_i-x_j\le c_k$ ，其中 $c_k$ 是常数（可以是非负数，也可以是负数）。我们要解决的问题是：求一组解 $x_1=a_1,x_2=a_2,...,x_n=a_n$ ，使得所有的约束条件得到满足，否则判断出无解。

差分约束系统中的每个约束条件 $x_i-x_j\le c_k$ 都可以变形成 $x_i\le x_j+c_k$ ，这与单源最短路中的三角形不等式 $dist[y]\le dist[x]+z$ 非常相似。因此，我们可以把每个变量 $x_i$ 看做图中的一个结点，对于每个约束条件 $x_i-x_j\le c_k$ ，从结点 $j$ 向结点 $i$ 连一条长度为 $c_k$ 的有向边。 

注意到，如果 $\{a_1,a_2,...,a_n\}$ 是该差分约束系统的一组解，那么对于任意的常数 $d$ ， $\{a_1+d,a_2+d,...,a_n+d\}$ 显然也是该差分约束系统的一组解，因为这样做差后 $d$ 刚好被消掉。

设 $dist[0]=0$ 并向每一个点连一条边，跑单源最短路，若图中存在负环，则给定的差分约束系统误解，否则， $x_i=dist[i]$ 为该差分约束系统的一组解。

一般使用 Bellman-Ford 或队列优化的 Bellman-Ford 判断图中是否存在负环，时间复杂度为 $O(nm)$ 。 

## 常用变形技巧

### 例题 [ luogu P1993 小 K 的农场 ](https://www.luogu.org/problemnew/show/P1993)

题目大意：求解差分约束系统，有 $m$ 条约束条件， 每条都为形如 $x_a-x_b\ge c_k$ ， $x_a-x_b\le c_k$ 或 $x_a=x_b$ 的形式，判断该差分约束系统有没有解。

对于 $x_a-x_b\ge c_k$ ，我们可以将其变形为 $x_b-x_a\le -c_k$ 的形式；

对于 $x_a=x_b$ ，我们将其拆分为两个式子， $x_a-x_b\ge 0$ （根据上一行所推导的，等价于 $x_b-x_a\le 0$） 和 $x_a-x_b\le 0$ 。

跑判断负环，如果不存在负环，输出 `Yes` ，否则输出 `No`。

给出一种用 DFS-SPFA 实现的判负环（时间复杂度极度不稳定）：

```cpp
#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;
const int maxn = 400010;
int n, m, op, u, v, we, cur, h[maxn], nxt[maxn], p[maxn], w[maxn], dist[maxn];
bool tf[maxn], ans;
inline void add_edge(int x, int y, int z) {
  cur++;
  nxt[cur] = h[x];
  h[x] = cur;
  p[cur] = y;
  w[cur] = z;
}
void dfs(int x) {
  tf[x] = true;
  for (int j = h[x]; j != -1; j = nxt[j])
    if (dist[p[j]] > dist[x] + w[j]) {
      if (tf[p[j]] || ans) {
        ans = 1;
        break;
      }
      dist[p[j]] = dist[x] + w[j];
      dfs(p[j]);
    }
  tf[x] = false;
}
int main() {
  cur = 0;
  ans = false;
  memset(h, -1, sizeof h);
  memset(dist, 127, sizeof dist);
  scanf("%d%d", &n, &m);
  while (m--) {
    scanf("%d%d%d", &op, &u, &v);
    if (op == 1)
      scanf("%d", &we), add_edge(u, v, -we);
    else if (op == 2)
      scanf("%d", &we), add_edge(v, u, we);
    else if (op == 3)
      add_edge(u, v, 0), add_edge(v, u, 0);
  }
  for (int i = 1; i <= n; i++) {
    dfs(i);
    if (ans) break;
  }
  if (ans)
    printf("No\n");
  else
    printf("Yes\n");
  return 0;
}
```

### 例题 [P4926 \[1007\] 倍杀测量者](https://www.luogu.org/problemnew/show/P4926)

不考虑二分等其他的东西，这里只论述差分系统 $\frac{x_i}{x_j}\le c_k$  的求解方法。

对每个 $x_i,x_j$ 和 $c_k$ 取一个 $\log$ 就可以把乘法变成加法运算，即 $\log x_i-\log x_j \le \log c_k$  ，这样就可以用差分约束解决了。

## Bellman-Ford 判负环代码实现

下面是用 Bellman-Ford 算法判断图中是否存在负环的代码实现，请在调用前先保证图是联通的。

```cpp
bool Bellman_Ford() {
  for (int i = 0; i < n; i++) {
    bool jud = false;
    for (int j = 1; j <= n; j++)
      for (int k = h[j]; ~k; k = nxt[k])
        if (dist[j] > dist[p[k]] + w[k])
          dist[j] = dist[p[k]] + w[k], jud = true;
    if (!jud) break;
  }
  for (int i = 1; i <= n; i++)
    for (int j = h[i]; ~j; j = nxt[j])
      if (dist[i] > dist[p[j]] + w[j]) return false;
  return true;
}
```

## 习题

[ bzoj 1715: \[Usaco2006 Dec\]Wormholes 虫洞 ](https://www.lydsy.com/JudgeOnline/problem.php?id=1715) 

[ bzoj 2330: \[SCOI2011\]糖果 ](https://www.lydsy.com/JudgeOnline/problem.php?id=2330)

[ POJ 1364 King ](http://poj.org/problem?id=1364)

[ POJ 2983 Is the Information Reliable? ](http://poj.org/problem?id=2983)
