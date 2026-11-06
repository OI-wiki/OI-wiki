#include <algorithm>
#include <cmath>
#include <cstdio>
#include <stack>
using namespace std;

int gi() {
  int x, c, op = 1;
  while (c = getchar(), c < '0' || c > '9')
    if (c == '-') op = -op;
  x = c ^ 48;
  while (c = getchar(), c >= '0' && c <= '9')
    x = (x << 3) + (x << 1) + (c ^ 48);
  return x * op;
}

int head[100002], nxt[200004], ver[200004], tot = 0;

void add(int x, int y) {
  ver[++tot] = y, nxt[tot] = head[x], head[x] = tot;
  ver[++tot] = x, nxt[tot] = head[y], head[y] = tot;
}

int top[100002], id[100002];

// --8<-- [start:declarations]
int bl[100002], bls = 0;  // 属于的块，块的数量
unsigned step;            // 块大小
int fa[100002], dp[100002], hs[100002] = {0}, sz[100002] = {0};
// 父节点，深度，重儿子，大小
stack<int> sta;

void dfs1(int x) {
  sz[x] = 1;
  unsigned ss = sta.size();
  for (int i = head[x]; i; i = nxt[i])
    if (ver[i] != fa[x]) {
      fa[ver[i]] = x;
      dp[ver[i]] = dp[x] + 1;
      dfs1(ver[i]);
      sz[x] += sz[ver[i]];
      if (sz[ver[i]] > sz[hs[x]]) hs[x] = ver[i];
      if (sta.size() - ss >= step) {
        bls++;
        while (sta.size() != ss) bl[sta.top()] = bls, sta.pop();
      }
    }
  sta.push(x);
}

// --8<-- [end:declarations]

int cnt = 0;

void dfs2(int x, int hf) {
  top[x] = hf, id[x] = ++cnt;
  if (!hs[x]) return;
  dfs2(hs[x], hf);
  for (int i = head[x]; i; i = nxt[i])
    if (ver[i] != fa[x] && ver[i] != hs[x]) dfs2(ver[i], ver[i]);
}

int lca(int x, int y) {
  while (top[x] != top[y]) {
    if (dp[top[x]] < dp[top[y]]) swap(x, y);
    x = fa[top[x]];
  }
  return dp[x] < dp[y] ? x : y;
}

struct qu {
  int x, y, t, id;

  bool operator<(const qu a) const {
    return bl[x] == bl[a.x] ? (bl[y] == bl[a.y] ? t < a.t : bl[y] < bl[a.y])
                            : bl[x] < bl[a.x];
  }
} q[100001];

int qs = 0;

struct ch {
  int x, y, b;
} upd[100001];

int ups = 0;
long long ans[100001];
int b[100001] = {0};
int a[100001];
long long w[100001];
long long v[100001];
long long now = 0;
bool vis[100001] = {false};

void back(int t) {
  if (vis[upd[t].x]) {
    now -= w[b[upd[t].y]--] * v[upd[t].y];
    now += w[++b[upd[t].b]] * v[upd[t].b];
  }
  a[upd[t].x] = upd[t].b;
}

void change(int t) {
  if (vis[upd[t].x]) {
    now -= w[b[upd[t].b]--] * v[upd[t].b];
    now += w[++b[upd[t].y]] * v[upd[t].y];
  }
  a[upd[t].x] = upd[t].y;
}

void update(int x) {
  if (vis[x])
    now -= w[b[a[x]]--] * v[a[x]];
  else
    now += w[++b[a[x]]] * v[a[x]];
  vis[x] ^= 1;
}

// --8<-- [start:move]
// 取反路径上除LCA以外的所有节点
void move(int x, int y) {
  if (dp[x] < dp[y]) swap(x, y);
  while (dp[x] > dp[y]) update(x), x = fa[x];
  while (x != y) update(x), update(y), x = fa[x], y = fa[y];
  // x!=y保证LCA没被取反
}

// --8<-- [end:move]

int main() {
  int n = gi(), m = gi(), k = gi();
  step = (int)pow(n, 0.6);
  for (int i = 1; i <= m; i++) v[i] = gi();
  for (int i = 1; i <= n; i++) w[i] = gi();
  for (int i = 1; i < n; i++) add(gi(), gi());
  for (int i = 1; i <= n; i++) a[i] = gi();
  for (int i = 1; i <= k; i++)
    if (gi())
      q[++qs].x = gi(), q[qs].y = gi(), q[qs].t = ups, q[qs].id = qs;
    else
      upd[++ups].x = gi(), upd[ups].y = gi();
  for (int i = 1; i <= ups; i++) upd[i].b = a[upd[i].x], a[upd[i].x] = upd[i].y;
  for (int i = ups; i; i--) back(i);
  fa[1] = 1;
  dfs1(1), dfs2(1, 1);
  // --8<-- [start:finish-block]
  // main
  if (!sta.empty()) {
    bls++;  // 这一行可写可不写
    while (!sta.empty()) bl[sta.top()] = bls, sta.pop();
  }
  // --8<-- [end:finish-block]

  for (int i = 1; i <= qs; i++)
    if (id[q[i].x] > id[q[i].y]) swap(q[i].x, q[i].y);
  sort(q + 1, q + qs + 1);
  int x = 1, y = 1, t = 0;
  for (int i = 1; i <= qs; i++) {
    if (x != q[i].x) move(x, q[i].x), x = q[i].x;
    if (y != q[i].y) move(y, q[i].y), y = q[i].y;
    int f = lca(x, y);
    update(f);
    while (t < q[i].t) change(++t);
    while (t > q[i].t) back(t--);
    ans[q[i].id] = now;
    update(f);
  }
  for (int i = 1; i <= qs; i++) printf("%lld\n", ans[i]);
  return 0;
}
