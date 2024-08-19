#include <iostream>

using namespace std;

using ll = long long;

const int N = 300010;

struct Node {
  int ls, rs, d;
  ll val, add, mul;

  Node() {
    ls = rs = 0;
    d = -1;
    val = add = 0;
    mul = 1;
  }

  Node(int v) {
    ls = rs = d = 0;
    val = v;
    add = 0;
    mul = 1;
  }
} t[N];

int head[N], nxt[N], to[N], cnt;
int n, m, p[N], f[N], a[N], dep[N], c[N], ans1[N],
    ans2[N];  // p 是树上每个点对应的堆顶
ll h[N], b[N];

void add(int u, int v) {
  nxt[++cnt] = head[u];
  head[u] = cnt;
  to[cnt] = v;
}

void madd(int u, ll x) {
  t[u].val += x;
  t[u].add += x;
}

void mmul(int u, ll x) {
  t[u].val *= x;
  t[u].add *= x;
  t[u].mul *= x;
}

void pushdown(int x) {  // 类似线段树下传标记
  mmul(t[x].ls, t[x].mul);
  madd(t[x].ls, t[x].add);
  mmul(t[x].rs, t[x].mul);
  madd(t[x].rs, t[x].add);
  t[x].add = 0;
  t[x].mul = 1;
}

int merge(int x, int y) {
  if (!x || !y) return x | y;
  if (t[x].val > t[y].val) swap(x, y);
  pushdown(x);
  t[x].rs = merge(t[x].rs, y);
  if (t[t[x].rs].d > t[t[x].ls].d) swap(t[x].ls, t[x].rs);
  t[x].d = t[t[x].rs].d + 1;
  return x;
}

int pop(int x) {
  pushdown(x);
  return merge(t[x].ls, t[x].rs);
}

void dfs(int u) {
  for (int i = head[u]; i; i = nxt[i]) {
    int v = to[i];
    dep[v] = dep[u] + 1;
    dfs(v);
  }
  while (p[u] && t[p[u]].val < h[u]) {
    ++ans1[u];
    ans2[p[u]] = dep[c[p[u]]] - dep[u];
    p[u] = pop(p[u]);
  }
  if (a[u])
    mmul(p[u], b[u]);
  else
    madd(p[u], b[u]);
  if (u > 1)
    p[f[u]] = merge(p[u], p[f[u]]);
  else
    while (p[u]) {
      ans2[p[u]] = dep[c[p[u]]] + 1;
      p[u] = pop(p[u]);
    }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n >> m;

  for (int i = 1; i <= n; ++i) cin >> h[i];

  for (int i = 2; i <= n; ++i) {
    cin >> f[i] >> a[i] >> b[i];
    add(f[i], i);
  }

  for (int i = 1; i <= m; ++i) {
    int v;
    cin >> v >> c[i];
    t[i] = Node(v);
    p[c[i]] = merge(i, p[c[i]]);
  }

  dfs(1);

  for (int i = 1; i <= n; ++i) cout << ans1[i] << '\n';
  for (int i = 1; i <= m; ++i) cout << ans2[i] << '\n';

  return 0;
}
