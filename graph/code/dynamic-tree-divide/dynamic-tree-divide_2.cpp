#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;
const int maxn = 100010;
const int inf = 2e9;
const int ddd = 6000010;

struct Segtree {
  int cnt, rt[maxn], sum[ddd], lc[ddd], rc[ddd];

  void update(int& o, int l, int r, int x, int v) {
    if (!o) o = ++cnt;
    if (l == r) {
      sum[o] += v;
      return;
    }
    int mid = (l + r) >> 1;
    if (x <= mid)
      update(lc[o], l, mid, x, v);
    else
      update(rc[o], mid + 1, r, x, v);
    sum[o] = sum[lc[o]] + sum[rc[o]];
  }

  int query(int o, int l, int r, int ql, int qr) {
    if (!o || r < ql || l > qr) return 0;
    if (ql <= l && r <= qr) return sum[o];
    int mid = (l + r) >> 1;
    return query(lc[o], l, mid, ql, qr) + query(rc[o], mid + 1, r, ql, qr);
  }
} dist, ch;

int n, m, val[maxn], u, v, op, x, y, lstans;
int cur, h[maxn * 2], nxt[maxn * 2], p[maxn * 2];

void add_edge(int x, int y) {
  cur++;
  nxt[cur] = h[x];
  h[x] = cur;
  p[cur] = y;
}

struct LCA {
  int dep[maxn], lg[maxn], fa[maxn][20];

  void dfs(int x, int f) {
    for (int j = h[x]; j; j = nxt[j])
      if (p[j] != f) dep[p[j]] = dep[x] + 1, fa[p[j]][0] = x, dfs(p[j], x);
  }

  void init() {
    dep[1] = 1;
    dfs(1, -1);
    for (int i = 2; i <= n; i++) lg[i] = lg[i / 2] + 1;
    for (int j = 1; j <= lg[n]; j++)
      for (int i = 1; i <= n; i++) fa[i][j] = fa[fa[i][j - 1]][j - 1];
  }

  int query(int x, int y) {
    if (dep[x] > dep[y]) swap(x, y);
    int k = dep[y] - dep[x];
    for (int i = 0; k; k = k / 2, i++)
      if (k & 1) y = fa[y][i];
    if (x == y) return x;
    k = dep[x];
    for (int i = lg[k]; i >= 0; i--)
      if (fa[x][i] != fa[y][i]) x = fa[x][i], y = fa[y][i];
    return fa[x][0];
  }

  int dist(int x, int y) { return dep[x] + dep[y] - 2 * dep[query(x, y)]; }
} lca;

int rt, sum, siz[maxn], maxx[maxn], fa[maxn];
int d[maxn][20], dep[maxn];
bool vis[maxn];

void calcsiz(int x, int fa) {
  siz[x] = 1;
  maxx[x] = 0;
  for (int j = h[x]; j; j = nxt[j])
    if (p[j] != fa && !vis[p[j]]) {
      calcsiz(p[j], x);
      siz[x] += siz[p[j]];
      maxx[x] = max(maxx[x], siz[p[j]]);
    }
  maxx[x] =
      max(maxx[x], sum - siz[x]);  // maxx[x] 表示以 x 为根时的最大子树大小
  if (maxx[x] < maxx[rt])
    rt = x;  // 这里不能写 <= ，保证在第二次 calcsiz 时 rt 不改变
}

void dfs1(int x, int fa, int y, int d) {
  ch.update(ch.rt[y], 0, n, d, val[x]);
  for (int j = h[x]; j; j = nxt[j])
    if (p[j] != fa && !vis[p[j]]) dfs1(p[j], x, y, d + 1);
}

void dfs2(int x, int fa, int y, int d) {
  dist.update(dist.rt[y], 0, n, d, val[x]);
  for (int j = h[x]; j; j = nxt[j])
    if (p[j] != fa && !vis[p[j]]) dfs2(p[j], x, y, d + 1);
}

void pre(int x) {
  vis[x] = true;  // 表示在之后的过程中不考虑 x 这个点
  dfs2(x, -1, x, 0);
  for (int j = h[x]; j; j = nxt[j])
    if (!vis[p[j]]) {
      rt = 0;
      maxx[rt] = inf;
      sum = siz[p[j]];
      calcsiz(p[j], -1);
      calcsiz(rt, -1);  // 计算两次，第二次求出以 rt 为根时的各子树大小
      dfs1(p[j], -1, rt, 1);
      fa[rt] = x;
      dep[rt] = dep[x] + 1;
      pre(rt);  // 记录点分树上的父亲
    }
}

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; i++) scanf("%d", val + i);
  for (int i = 1; i < n; i++)
    scanf("%d%d", &u, &v), add_edge(u, v), add_edge(v, u);
  lca.init();
  rt = 0;
  maxx[rt] = inf;
  sum = n;
  calcsiz(1, -1);
  calcsiz(rt, -1);
  pre(rt);
  // for(int i=1;i<=n;i++)printf("%d ",fa[i]);printf("\n");
  for (int i = 1; i <= n; i++)
    for (int j = i; j; j = fa[j]) d[i][dep[i] - dep[j]] = lca.dist(i, j);
  while (m--) {
    scanf("%d%d%d", &op, &x, &y);
    x ^= lstans;
    y ^= lstans;
    if (op == 0) {
      lstans = dist.query(dist.rt[x], 0, n, 0, y);
      int nww = 0;
      for (int i = x; fa[i]; i = fa[i]) {
        nww = d[x][dep[x] - dep[fa[i]]];  // lca.dist(x,fa[i]);
        lstans += dist.query(dist.rt[fa[i]], 0, n, 0, y - nww);
        lstans -= ch.query(ch.rt[i], 0, n, 0, y - nww);
      }
      printf("%d\n", lstans);
    }
    if (op == 1) {
      int nww = 0;
      dist.update(dist.rt[x], 0, n, 0, y - val[x]);
      for (int i = x; fa[i]; i = fa[i]) {
        nww = d[x][dep[x] - dep[fa[i]]];  // lca.dist(x,fa[i]);
        dist.update(dist.rt[fa[i]], 0, n, nww, y - val[x]);
        ch.update(ch.rt[i], 0, n, nww, y - val[x]);
      }
      val[x] = y;
    }
  }
  return 0;
}