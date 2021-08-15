## 点分治

点分治适合处理大规模的树上路径信息问题。

??? note " 例题 [luogu P3806【模板】点分治 1](https://www.luogu.com.cn/problem/P3806)"
    给定一棵有 $n$ 个点的带边权树，$m$ 次询问，每次询问给出 $k$，询问树上距离为 $k$ 的点对是否存在。
    
    $n\le 10000,m\le 100,k\le 10000000$

我们先随意选择一个节点作为根节点 $\mathit{rt}$，所有完全位于其子树中的路径可以分为两种，一种是经过当前根节点的路径，一种是不经过当前根节点的路径。对于经过当前根节点的路径，又可以分为两种，一种是以根节点为一个端点的路径，另一种是两个端点都不为根节点的路径。而后者又可以由两条属于前者链合并得到。所以，对于枚举的根节点 $rt$，我们先计算在其子树中且经过该节点的路径对答案的贡献，再递归其子树对不经过该节点的路径进行求解。

在本题中，对于经过根节点 $\mathit{rt}$ 的路径，我们先枚举其所有子节点 $\mathit{ch}$，以 $\mathit{ch}$ 为根计算 $\mathit{ch}$ 子树中所有节点到 $\mathit{rt}$ 的距离。记节点 $i$ 到当前根节点 $rt$ 的距离为 $\mathit{dist}_i$，$\mathit{tf}_{d}$ 表示之前处理过的子树中是否存在一个节点 $v$ 使得 $\mathit{dist}_v=d$。若一个询问的 $k$ 满足 $tf_{k-\mathit{dist}_i}=true$，则存在一条长度为 $k$ 的路径。在计算完 $\mathit{ch}$ 子树中所连的边能否成为答案后，我们将这些新的距离加入 $\mathit{tf}$ 数组中。

注意在清空 $\mathit{tf}$ 数组的时候不能直接用 `memset`，而应将之前占用过的 $\mathit{tf}$ 位置加入一个队列中，进行清空，这样才能保证时间复杂度。

点分治过程中，每一层的所有递归过程合计对每个点处理一次，假设共递归 $h$ 层，则总时间复杂度为 $O(hn)$。

若我们 **每次选择子树的重心作为根节点**，可以保证递归层数最少，时间复杂度为 $O(n\log n)$。

请注意在重新选择根节点之后一定要重新计算子树的大小，否则一点看似微小的改动就可能会使时间复杂度错误或正确性难以保证。

???+ note "参考代码"


```cpp
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;
const int maxn = 20010;
const int inf = 2e9;
int n, m, a, b, c, q[maxn], rt, siz[maxn], maxx[maxn], dist[maxn];
int cur, h[maxn], nxt[maxn], p[maxn], w[maxn];
bool tf[10000010], ret[maxn], vis[maxn];
void add_edge(int x, int y, int z) {
  cur++;
  nxt[cur] = h[x];
  h[x] = cur;
  p[cur] = y;
  w[cur] = z;
}
int sum;
void calcsiz(int x, int fa) {
  siz[x] = 1;
  maxx[x] = 0;
  for (int j = h[x]; j; j = nxt[j])
    if (p[j] != fa && !vis[p[j]]) {
      calcsiz(p[j], x);
      maxx[x] = max(maxx[x], siz[p[j]]);
      siz[x] += siz[p[j]];
    }
  maxx[x] = max(maxx[x], sum - siz[x]);
  if (maxx[x] < maxx[rt]) rt = x;
}
int dd[maxn], cnt;
void calcdist(int x, int fa) {
  dd[++cnt] = dist[x];
  for (int j = h[x]; j; j = nxt[j])
    if (p[j] != fa && !vis[p[j]])
      dist[p[j]] = dist[x] + w[j], calcdist(p[j], x);
}
queue<int> tag;
void dfz(int x, int fa) {
  tf[0] = true;
  tag.push(0);
  vis[x] = true;
  for (int j = h[x]; j; j = nxt[j])
    if (p[j] != fa && !vis[p[j]]) {
      dist[p[j]] = w[j];
      calcdist(p[j], x);
      for (int k = 1; k <= cnt; k++)
        for (int i = 1; i <= m; i++)
          if (q[i] >= dd[k]) ret[i] |= tf[q[i] - dd[k]];
      for (int k = 1; k <= cnt; k++)
        if (dd[k] < 10000010) tag.push(dd[k]), tf[dd[k]] = true;
      cnt = 0;
    }
  while (!tag.empty()) tf[tag.front()] = false, tag.pop();
  for (int j = h[x]; j; j = nxt[j])
    if (p[j] != fa && !vis[p[j]]) {
      sum = siz[p[j]];
      rt = 0;
      maxx[rt] = inf;
      calcsiz(p[j], x);
      calcsiz(rt, -1);
      dfz(rt, x);
    }
}
int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1; i < n; i++)
    scanf("%d%d%d", &a, &b, &c), add_edge(a, b, c), add_edge(b, a, c);
  for (int i = 1; i <= m; i++) scanf("%d", q + i);
  rt = 0;
  maxx[rt] = inf;
  sum = n;
  calcsiz(1, -1);
  calcsiz(rt, -1);
  dfz(rt, -1);
  for (int i = 1; i <= m; i++)
    if (ret[i])
      printf("AYE\n");
    else
      printf("NAY\n");
  return 0;
}
```

??? note " 例题 1 [luogu  P4178 Tree](https://www.luogu.com.cn/problem/P4178)"
    给定一棵有 $n$ 个点的带权树，给出 $k$，询问树上距离为 $k$ 的点对数量。
    
    $n\le 40000,k\le 20000,w_i\le 1000$

由于这里查询的是树上距离为 $[0,k]$ 的点对数量，所以我们用线段树来支持维护和查询。
??? note "参考代码"

```cpp
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>
#define int long long
using namespace std;
const int maxn = 2000010;
const int inf = 2e9;
int n, a, b, c, q, rt, siz[maxn], maxx[maxn], dist[maxn];
int cur, h[maxn], nxt[maxn], p[maxn], w[maxn], ret;
bool vis[maxn];
void add_edge(int x, int y, int z) {
  cur++;
  nxt[cur] = h[x];
  h[x] = cur;
  p[cur] = y;
  w[cur] = z;
}
int sum;
void calcsiz(int x, int fa) {
  siz[x] = 1;
  maxx[x] = 0;
  for (int j = h[x]; j; j = nxt[j])
    if (p[j] != fa && !vis[p[j]]) {
      calcsiz(p[j], x);
      maxx[x] = max(maxx[x], siz[p[j]]);
      siz[x] += siz[p[j]];
    }
  maxx[x] = max(maxx[x], sum - siz[x]);
  if (maxx[x] < maxx[rt]) rt = x;
}
int dd[maxn], cnt;
void calcdist(int x, int fa) {
  dd[++cnt] = dist[x];
  for (int j = h[x]; j; j = nxt[j])
    if (p[j] != fa && !vis[p[j]])
      dist[p[j]] = dist[x] + w[j], calcdist(p[j], x);
}
queue<int> tag;
struct segtree {
  int cnt, rt, lc[maxn], rc[maxn], sum[maxn];
  void clear() {
    while (!tag.empty()) update(rt, 1, 20000000, tag.front(), -1), tag.pop();
    cnt = 0;
  }
  void print(int o, int l, int r) {
    if (!o || !sum[o]) return;
    if (l == r) {
      printf("%lld %lld\n", l, sum[o]);
      return;
    }
    int mid = (l + r) >> 1;
    print(lc[o], l, mid);
    print(rc[o], mid + 1, r);
  }
  void update(int& o, int l, int r, int x, int v) {
    if (!o) o = ++cnt;
    if (l == r) {
      sum[o] += v;
      if (!sum[o]) o = 0;
      return;
    }
    int mid = (l + r) >> 1;
    if (x <= mid)
      update(lc[o], l, mid, x, v);
    else
      update(rc[o], mid + 1, r, x, v);
    sum[o] = sum[lc[o]] + sum[rc[o]];
    if (!sum[o]) o = 0;
  }
  int query(int o, int l, int r, int ql, int qr) {
    if (!o) return 0;
    if (r < ql || l > qr) return 0;
    if (ql <= l && r <= qr) return sum[o];
    int mid = (l + r) >> 1;
    return query(lc[o], l, mid, ql, qr) + query(rc[o], mid + 1, r, ql, qr);
  }
} st;
void dfz(int x, int fa) {
  // tf[0]=true;tag.push(0);
  st.update(st.rt, 1, 20000000, 1, 1);
  tag.push(1);
  vis[x] = true;
  for (int j = h[x]; j; j = nxt[j])
    if (p[j] != fa && !vis[p[j]]) {
      dist[p[j]] = w[j];
      calcdist(p[j], x);
      for (int k = 1; k <= cnt; k++)
        if (q - dd[k] >= 0)
          ret += st.query(st.rt, 1, 20000000, max(0ll, 1 - dd[k]) + 1,
                          max(0ll, q - dd[k]) + 1);
      for (int k = 1; k <= cnt; k++)
        st.update(st.rt, 1, 20000000, dd[k] + 1, 1), tag.push(dd[k] + 1);
      cnt = 0;
    }
  st.clear();
  for (int j = h[x]; j; j = nxt[j])
    if (p[j] != fa && !vis[p[j]]) {
      sum = siz[p[j]];
      rt = 0;
      maxx[rt] = inf;
      calcsiz(p[j], x);
      calcsiz(rt, -1);
      dfz(rt, x);
    }
}
int main() {
  scanf("%lld", &n);
  for (int i = 1; i < n; i++)
    scanf("%lld%lld%lld", &a, &b, &c), add_edge(a, b, c), add_edge(b, a, c);
  scanf("%lld", &q);
  rt = 0;
  maxx[rt] = inf;
  sum = n;
  calcsiz(1, -1);
  calcsiz(rt, -1);
  dfz(rt, -1);
  printf("%lld\n", ret);
  return 0;
}
```

??? + note "[例题 2 P2664 树上游戏](https://www.luogu.com.cn/problem/P2664)"

一棵每个节点都给定颜色的树，定义 $s(i,j)$ 为 $\mathit{i}$ 到 $\mathit{j}$ 的颜色数量，$sum_{i}=\sum_{j=1}^n s(i,j)$

求出所有的 $sum_i$  $1≤n,c_i≤10^5$

这道题很考验对点分治思想的理解和应用，适合作为点分治的难度较高的例题和练习题。

首先，我们需要想明白一个转化。题目定义 $sum_i$ 是 $i$ 到所有节点路径上的颜色数量之和，可是如果用这个方法，在点分治中是不好统计答案的，因为这样很难合并从当前根出发的两棵子树的信息。所以我们想到将 $sum_i$ 的意义转化。对于每个颜色 $j$, 其中一个端点为 $i$ 且含有颜色 $j$ 的路径数量记为 $cnt[j]$，$sum_i$ 其实就是 $\sum cnt[j]$。这一步转化其实就是换了个观察对象，考虑的是每个颜色对 $sum_i$ 的 贡献。而 $cnt[j]$ 其实很好处理出来，只需要每遇到一个新颜色，就 $cnt[col[u]]+=siz[u]$ 即可，其中 $siz[u]$ 为 u 的子树大小，意味着这个子树里的所有节点都在这个颜色上对 $u$ 的答案有一个贡献。

考虑到点分治过程中，我们只需要分别考虑统计：

1. 子树中以当前根节点为端点的路径对根的贡献
2. lca 为当前根节点的路径对子树内每个点的贡献

1 部分比较好办，由于点分治中，递归层数不超过 $log(n)$，每一层我们都可以遍历全部子树，这个时候就可以使用 $sum_i$ 的定义式来在遍历子树的过程中顺便统计了。

而针对 2 部分，设当前根节点 $u$ 的一个子节点为 $d$,$d$ 的子树里任取一个点为 $v$，那么 $v$ 的答案可以分为两部分：

1. $u->v$ 路径上出现过的颜色，数量设为 $num$，$u$ 除了 $d$ 以外的其他所有子树的总大小设为 $siz1$, 那么这些出现过的颜色对 $v$ 的答案贡献为 $num\times siz1$。
2. $u->v$ 路径上没有出现过的颜色 $j$，它们的贡献来自于 $u$ 除了 $d$ 以外的其他所有子树的 $cnt[j]$，这部分答案为 $\sum_{j不在u->v上}cnt[j]$。

以上是全部统计思路，实现细节详见参考代码。

??? +note "参考代码"

```c++
#include <bits/stdc++.h>  //by Alphnia
using namespace std;
#define rep(i, a, b) for (register int i = (a); i <= (b); ++i)
const int N = 200005;
int h[N], nxt[N * 2], to[N * 2], c[N], gr;
#define il inline
il void tu(int x, int y) { to[++gr] = y, nxt[gr] = h[x], h[x] = gr; }
typedef long long ll;
int n, nn, siz[N], mn, rt;
bool vis[N];
void get_root(int u, int f) {
  siz[u] = 1;
  int mx = 0;
  for (int i = h[u]; i; i = nxt[i]) {
    int d = to[i];
    if (vis[d] || d == f) continue;
    get_root(d, u);
    siz[u] += siz[d];
    mx = max(mx, siz[d]);
  }
  mx = max(mx, nn - siz[u]);
  if (mx < mn) mn = mx, rt = u;
}
ll ans[N], sum;
int cnt[N], v[N];
// sum实时统计的是cnt[i]的和
int nowrt;
void get_dis(int u, int f, int now) {  // now为当前树链上的颜色数量(不含u)
  siz[u] = 1;
  if (!v[c[u]]) {
    sum -= cnt[c[u]];  // 减去在之前子树中已经出现过的颜色信息
    now++;
  }
  v[c[u]]++;
  ans[u] += sum + now * siz[nowrt];  // 统计过u点的路径对u的贡献
  for (int i = h[u]; i; i = nxt[i]) {
    int d = to[i];
    if (d == f || vis[d]) continue;
    get_dis(d, u, now);
    siz[u] += siz[d];
  }
  v[c[u]]--;
  if (!v[c[u]]) {
    sum += cnt[c[u]];  //回溯
  }
}
void get_cnt(int u, int f) {
  if (!v[c[u]]) {
    cnt[c[u]] += siz[u];
    sum += siz[u];  // 将刚遍历过的子树的信息整合到cnt[i]和sum上去
  }
  v[c[u]]++;
  for (int i = h[u]; i; i = nxt[i]) {
    int d = to[i];
    if (vis[d] || d == f) continue;
    get_cnt(d, u);
  }
  v[c[u]]--;
}

void clear(int u, int f, int now) {
  if (!v[c[u]]) now++;
  v[c[u]]++;
  ans[u] -= now;
  ans[nowrt] += now;
  for (int i = h[u]; i; i = nxt[i]) {
    int d = to[i];
    if (vis[d] || d == f) continue;
    clear(d, u, now);
  }
  v[c[u]]--;
  cnt[c[u]] = 0;
}
void clear2(int u, int f) {
  cnt[c[u]] = 0;
  for (int i = h[u]; i; i = nxt[i]) {
    int d = to[i];
    if (vis[d] || d == f) continue;
    clear2(d, u);
  }
}
int son[N];
void divid(int u) {
  vis[u] = 1;
  int tot = 0;
  nowrt = u;
  ans[u]++;
  for (int i = h[u]; i; i = nxt[i]) {
    if (vis[to[i]]) continue;
    son[++tot] = to[i];
  }
  siz[u] = sum = cnt[c[u]] = 1;
  v[c[u]]++;
  rep(i, 1, tot) {  // 统计每个子树和它之前的所有子树中节点组合产生的贡献
    int d = son[i];
    get_dis(d, u, 0);
    get_cnt(d, u);
    siz[u] += siz[d];
    cnt[c[u]] += siz[d];
    sum += siz[d];
  }
  clear2(u, 0);  // 清空数组，记得不可以用memset
  siz[u] = sum = cnt[c[u]] = 1;
  for (int i = tot; i >= 1;
       --i) {  // 统计每个子树和它之后的所有子树中节点组合产生的贡献
    int d = son[i];
    get_dis(d, u, 0);
    get_cnt(d, u);
    siz[u] += siz[d];
    cnt[c[u]] += siz[d];
    sum += siz[d];
  }
  v[c[u]]--;
  clear(u, 0, 0);                      //清空的同时统计答案
  for (int i = h[u]; i; i = nxt[i]) {  // 继续向下进行点分治
    int d = to[i];
    if (vis[d]) continue;
    nn = siz[d], mn = n + 1, rt = 0;
    get_root(d, u);
    divid(rt);
  }
}
int main() {
  scanf("%d", &n);
  int u, v;
  rep(i, 1, n) scanf("%d", &c[i]);
  rep(i, 2, n) scanf("%d%d", &u, &v), tu(u, v), tu(v, u);
  rt = 0, nn = n, mn = n + 1;
  get_root(1, 0);
  divid(rt);
  rep(i, 1, n) printf("%lld\n", ans[i]);
  return 0;
}
```

## 边分治

与上面的点分治类似，我们选取一条边，把树尽量均匀地分成两部分（使边连接的两个子树的 $\mathit{size}$ 尽量接近）。然后递归处理左右子树，统计信息。

ちょっとまって，这不行吧……

考虑一个菊花图

![菊花图](./images/tree-divide1.svg)

我们发现当一个点下有多个 $size$ 接近的儿子时，应用边分治的时间复杂度是无法接受的。

如果这个图是个二叉树，就可以避免上面菊花图中应用边分治的弊端。因此我们考虑把一个多叉树转化成二叉树。

显然，我们只需像线段树那样建树就可以了。就像这样

![建树](./images/tree-divide2.svg)

新建出来的点根据题目要求给予恰当的信息即可。例如：统计路径长度时，将原边边权赋为 $1$, 将新建的边边权赋为 $0$ 即可。

分析复杂度，发现最多会增加 $O(n)$ 个点，则总复杂度为 $O(n\log n)$

几乎所有点分治的题边分都能做（常数上有差距，但是不卡），所以就不放例题了。

## 点分树

点分树是通过更改原树形态使树的层数变为稳定 $\log n$ 的一种重构树。

常用于解决与树原形态无关的带修改问题。

### 算法分析

我们通过点分治每次找重心的方式来对原树进行重构。

将每次找到的重心与上一层的重心缔结父子关系，这样就可以形成一棵 $\log n$ 层的树。

由于树是 $\log n$ 层的，很多原来并不对劲的暴力在点分树上均有正确的复杂度。

### 代码实现

有一个小技巧：每次用递归上一层的总大小 $\mathit{tot}$ 减去上一层的点的重儿子大小，得到的就是这一层的总大小。这样求重心就只需一次 DFS 了
???+note "参考代码"

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef vector<int>::iterator IT;

struct Edge {
  int to, nxt, val;

  Edge() {}
  Edge(int to, int nxt, int val) : to(to), nxt(nxt), val(val) {}
} e[300010];
int head[150010], cnt;

void addedge(int u, int v, int val) {
  e[++cnt] = Edge(v, head[u], val);
  head[u] = cnt;
}

int siz[150010], son[150010];
bool vis[150010];

int tot, lasttot;
int maxp, root;

void getG(int now, int fa) {
  siz[now] = 1;
  son[now] = 0;
  for (int i = head[now]; i; i = e[i].nxt) {
    int vs = e[i].to;
    if (vs == fa || vis[vs]) continue;
    getG(vs, now);
    siz[now] += siz[vs];
    son[now] = max(son[now], siz[vs]);
  }
  son[now] = max(son[now], tot - siz[now]);
  if (son[now] < maxp) {
    maxp = son[now];
    root = now;
  }
}

struct Node {
  int fa;
  vector<int> anc;
  vector<int> child;
} nd[150010];

int build(int now, int ntot) {
  tot = ntot;
  maxp = 0x7f7f7f7f;
  getG(now, 0);
  int g = root;
  vis[g] = 1;
  for (int i = head[g]; i; i = e[i].nxt) {
    int vs = e[i].to;
    if (vis[vs]) continue;
    int tmp = build(vs, ntot - son[vs]);
    nd[tmp].fa = now;
    nd[now].child.push_back(tmp);
  }
  return g;
}

int virtroot;

int main() {
  int n;
  cin >> n;
  for (int i = 1; i < n; i++) {
    int u, v, val;
    cin >> u >> v >> val;
    addedge(u, v, val);
    addedge(v, u, val);
  }
  virtroot = build(1, n);
}
```
