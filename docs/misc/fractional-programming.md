!!! note " 例题[luogu P4322\[JSOI2016\]最佳团体](https://www.luogu.org/problemnew/show/P4322)"
    题目大意：有一棵 $n+1$ 个节点的树，根为 $0$ 号节点。每个节点 $i$ 有一个价值 $p_i$ 和费用 $s_i$ 。你需要选择 $k$ 个节点 $a_1,a_2,\ldots,a_k$ （不包括 $0$ 号节点），使得

    $$
    \frac{\sum_{i=1}^k p_{a_i}}{\sum_{i=1}^k s_{a_i}}
    $$

    最大。你需要保证对于你选择的一个树上节点，它的父亲一定被选中。求出这个最大的比值。

如果每个点都只有一个价值（设为 $v_i$ ），我们要做的只是最大化这个最后能得到的价值，那么我们可以用树形动态规划解决这个问题。

定义 $f(i,j)$ 表示以 $i$ 为根的子树中选择 $j$ 个节点的最大价值。由于要满足如果一个点被选择，其父亲也一定被选择，如果 $j\ge 1$ ，那么当前节点 $i$ 一定是已经被选中的。利用树上背包进行合并。写出状态转移方程：

$$
f(i,j)=\left\{
\begin{aligned}
& 0, & j=0, \\
& \max\left\{\sum f(son,k)\right\}+v(i),\quad\text{where }\sum k=j-1, & j\neq 0
\end{aligned} \right
.
$$

如果 **合并方式得当** ，则可以在 $O(n^2)$ 的时间复杂度内完成状态转移，具体细节参见代码。

但是，我们是让一个分式的值最大化，然而这个分式的分母又不确定，怎么办呢？

首先我们明确一个性质：设最后最大化的答案为 $ans$ ，那么对于任意一个小于等于 $ans$ 的实数 $a$ ，都有 $v_i=p_i-a\times s_i$ ，这样的 $v$ 数组算出的 $f(0,k+1)$ 的值都大于零。该式等于零当且仅当 $a=ans$ 。

那么，我们就可以用二分的思想解决这个问题。每次选择一个 $mid$ ，令 $v_i=p_i-mid\times s_i$ ，算出 $f(0,k+1)$ 的值，如果大于零则选择右区间，反之选择左区间。最后当区间 $[l,r]$ 的大小 $r-l$ 在可以容许的范围内时，输出最后的答案。时间复杂度为 $O(n^2\log ans)$ 。

这就是分数规划的基本思想。

代码：

```cpp
// luogu-judger-enable-o2
#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;
const int maxn = 2510;
int k, n, rr, cur, h[maxn], nxt[maxn * 2], p[maxn * 2], siz[maxn];
double s[maxn], pp[maxn], l, r, mid, v[maxn], f[maxn][maxn];
void add_edge(int x, int y) {
  cur++;
  nxt[cur] = h[x];
  h[x] = cur;
  p[cur] = y;
}
void dfs(int x, int fa) {
  siz[x] = 1;
  f[x][0] = 0;
  f[x][1] = v[x];
  for (int i = h[x]; i != -1; i = nxt[i])
    if (p[i] != fa) {
      dfs(p[i], x);
      for (int j = siz[x]; j >= 1; j--)
        for (int k = 0; k <= siz[p[i]]; k++)
          f[x][j + k] = max(f[x][j + k], f[x][j] + f[p[i]][k]);
      siz[x] += siz[p[i]];
    }
}
int main() {
  memset(h, -1, sizeof h);
  scanf("%d%d", &k, &n);
  for (int i = 1; i <= n; i++)
    scanf("%lf%lf%d", s + i, pp + i, &rr), add_edge(rr, i), add_edge(i, rr);
  r = 10000.0;
  while (r - l > 1e-4) {
    mid = (l + r) * 0.5;
    for (int i = 1; i <= n; i++) v[i] = pp[i] - mid * s[i];
    for (int i = 0; i < maxn; i++)
      for (int j = 0; j < maxn; j++) f[i][j] = -2e9;
    dfs(0, -1);
    if (f[0][k + 1] > 0)
      l = mid;
    else
      r = mid;
  }
  printf("%.3lf\n", l);
  return 0;
}
```

## 习题

[luogu P3705\[SDOI2017\]新生舞会](https://www.luogu.org/problemnew/show/P3705)

[luogu P3288\[SCOI2014\]方伯伯运椰子](https://www.luogu.org/problemnew/show/P3288)

[luogu P3199\[HNOI2009\]最小圈](https://www.luogu.org/problemnew/show/P3199)
