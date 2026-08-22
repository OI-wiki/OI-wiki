#include <algorithm>
#include <bitset>
#include <iostream>
#include <stack>
#include <vector>
#define ls (i << 1)
#define rs (i << 1 | 1)
#define mid ((l + r) >> 1)
using namespace std;

constexpr int N = 5e5 + 5, M = 5e5 + 5;

int siz[N], dep[N], father[N], top[N], son[N];
int n, q;

struct edge {
  int nxt, to;
} g[N << 1];

int head[N], ec;

void add(int u, int v) {
  g[++ec].nxt = head[u];
  g[ec].to = v;
  head[u] = ec;
}

void dfs1(int u, int fa) {
  dep[u] = dep[fa] + 1;
  siz[u] = 1;
  father[u] = fa;
  for (int i = head[u]; i; i = g[i].nxt) {
    int v = g[i].to;
    if (v == fa) continue;
    dfs1(v, u);
    siz[u] += siz[v];
    if (siz[son[u]] < siz[v]) son[u] = v;
  }
}

void dfs2(int u, int fa) {
  if (son[u]) {
    top[son[u]] = top[u];
    dfs2(son[u], u);
  }
  for (int i = head[u]; i; i = g[i].nxt) {
    int v = g[i].to;
    if (v == fa || v == son[u]) continue;
    top[v] = v;
    dfs2(v, u);
  }
}

int lca(int x, int y) {
  while (top[x] != top[y]) {
    if (dep[top[x]] < dep[top[y]]) swap(x, y);
    x = father[top[x]];
  }
  return dep[x] < dep[y] ? x : y;
}

int dis(int x, int y) { return dep[x] + dep[y] - (dep[lca(x, y)] << 1); }

vector<int> t[N << 2];

void update(int ql, int qr, int v, int i, int l, int r) {
  if (ql <= l && r <= qr) {
    t[i].push_back(v);
    return;
  }
  if (ql <= mid) update(ql, qr, v, ls, l, mid);
  if (qr > mid) update(ql, qr, v, rs, mid + 1, r);
}

stack<pair<int, int>> stk;
int u, v;
int ans[M];

void solve(int i, int l, int r) {
  auto lvl = stk.size();
  for (int x : t[i]) {
    stk.push(make_pair(u, v));
    if (!u && !v)
      u = x, v = x;
    else {
      vector<int> vct = {dis(u, v), dis(u, x), dis(v, x)};
      sort(vct.begin(), vct.end(), greater<int>());
      if (vct[0] == dis(u, x))
        v = x;
      else if (vct[0] == dis(x, v))
        u = x;
    }
  }
  if (l == r)
    ans[l] = (!u || !v) ? -1 : dis(u, v);
  else
    solve(ls, l, mid), solve(rs, mid + 1, r);
  while (stk.size() != lvl) {
    auto top = stk.top();
    u = top.first, v = top.second;
    stk.pop();
  }
}

int lst[N];
bitset<N> col;
bitset<M> haveq;

signed main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> n;
  for (int i = 1; i < n; i++) {
    int u, v;
    cin >> u >> v;
    add(u, v);
    add(v, u);
  }
  top[1] = 1;
  dfs1(1, 0);
  dfs2(1, 0);
  for (int i = 1; i <= n; i++) lst[i] = 1;
  cin >> q;
  for (int i = 2; i <= (q + 1); i++) {
    char c;
    int x;
    cin >> c;
    if (c == 'C') {
      cin >> x;
      if (!col[x]) {
        col[x] = 1;
        update(lst[x], i, x, 1, 1, q + 2);
      } else
        col[x] = 0, lst[x] = i;
    } else
      haveq[i] = 1;
  }
  for (int i = 1; i <= n; i++) {
    if (!col[i]) update(lst[i], q + 2, i, 1, 1, q + 2);
  }
  solve(1, 1, q + 2);
  for (int i = 1; i <= (q + 2); i++) {
    if (haveq[i]) cout << ans[i] << '\n';
  }
  return 0;
}
