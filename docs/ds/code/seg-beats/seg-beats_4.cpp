#include <algorithm>
#include <climits>
#include <iostream>
using namespace std;
using ll = long long;

constexpr int N = 1e5 + 7;

struct Tree {
  int mx, _mx;  // 区间最大值 区间历史最大值
  int ad, _ad;  // 区间加标记 区间阶段历史最大加标记
  int st, _st;  // 区间修改值 区间阶段历史最大修改标记
} g[N * 4];

int a[N];
int n, m;
#define ls u * 2
#define rs u * 2 + 1
#define mid (l + r) / 2

void pushup(int u) {
  g[u].mx = max(g[ls].mx, g[rs].mx);
  g[u]._mx = max(g[ls]._mx, g[rs]._mx);
}

void pushadd(int u, int v, int _v) {
  g[u]._mx = max(g[u]._mx, g[u].mx + _v), g[u].mx += v;
  if (g[u].st == INT_MIN)
    g[u]._ad = max(g[u]._ad, g[u].ad + _v), g[u].ad += v;
  else
    g[u]._st = max(g[u]._st, g[u].st + _v), g[u].st += v;
}

void pushset(int u, int v, int _v) {
  g[u]._mx = max(g[u]._mx, _v), g[u].mx = v;
  g[u]._st = max(g[u]._st, _v), g[u].st = v;
}

void pushdown(int u, int l, int r) {
  if (g[u].ad || g[u]._ad)
    pushadd(ls, g[u].ad, g[u]._ad), pushadd(rs, g[u].ad, g[u]._ad),
        g[u].ad = g[u]._ad = 0;
  if (g[u].st != INT_MIN || g[u]._st != INT_MIN)
    pushset(ls, g[u].st, g[u]._st), pushset(rs, g[u].st, g[u]._st),
        g[u].st = g[u]._st = INT_MIN;
}

void build(int u = 1, int l = 1, int r = n) {
  g[u]._st = g[u].st = INT_MIN;
  if (l == r) {
    g[u].mx = a[l];
    g[u]._mx = a[l];
    return;
  }
  build(ls, l, mid), build(rs, mid + 1, r);
  pushup(u);
}

int L, R;

void add(int v, int u = 1, int l = 1, int r = n) {
  if (R < l || r < L) return;
  if (L <= l && r <= R) return pushadd(u, v, max(v, 0));
  pushdown(u, l, r);
  add(v, ls, l, mid), add(v, rs, mid + 1, r);
  pushup(u);
}

void tset(int v, int u = 1, int l = 1, int r = n) {
  if (R < l || r < L) return;
  if (L <= l && r <= R) return pushset(u, v, v);
  pushdown(u, l, r);
  tset(v, ls, l, mid), tset(v, rs, mid + 1, r);
  pushup(u);
}

int qmax(int u = 1, int l = 1, int r = n) {
  if (R < l || r < L) return INT_MIN;
  if (L <= l && r <= R) return g[u].mx;
  pushdown(u, l, r);
  return max(qmax(ls, l, mid), qmax(rs, mid + 1, r));
}

int qmaxh(int u = 1, int l = 1, int r = n) {
  if (R < l || r < L) return INT_MIN;
  if (L <= l && r <= R) return g[u]._mx;
  pushdown(u, l, r);
  return max(qmaxh(ls, l, mid), qmaxh(rs, mid + 1, r));
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  cin >> n;
  for (int i = 1; i <= n; ++i) cin >> a[i];
  build();
  int m, z;
  cin >> m;
  for (int i = 1; i <= m; ++i) {
    char op;
    cin >> op;
    while (op == ' ' || op == '\r' || op == '\n') cin >> op;
    cin >> L >> R;
    int x;
    if (op == 'Q')
      cout << qmax() << '\n';
    else if (op == 'A')
      cout << qmaxh() << '\n';
    else if (op == 'P')
      cin >> x, add(x);
    else
      cin >> x, tset(x);
  }
  return 0;
}
