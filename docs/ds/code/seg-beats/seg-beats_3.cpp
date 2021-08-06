#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
char nc() {
  static char buf[1000000], *p = buf, *q = buf;
  return p == q && (q = (p = buf) + fread(buf, 1, 1000000, stdin), p == q)
             ? EOF
             : *p++;
}
inline ll rd() {  // LLONG_MIN LMAX=9,223,372,036,854,775,807
  ll s = 0, w = 1;
  char ch = nc();
  while (ch < '0' || ch > '9') {
    if (ch == '-') w = -1;
    ch = nc();
  }
  while (ch >= '0' && ch <= '9') s = s * 10 + ch - '0', ch = nc();
  return s * w;
}
const int N = 1e5 + 7;
struct Tree {
  int mx, _mx;
  int ad, _ad;
  int st, _st;
} g[N * 4];
int a[N];
int n, m;
#define ls u * 2
#define rs u * 2 + 1
#define mid (l + r) / 2
inline void pushup(int u) {
  g[u].mx = max(g[ls].mx, g[rs].mx);
  g[u]._mx = max(g[ls]._mx, g[rs]._mx);
}
inline void pushadd(int u, int v, int _v) {
  g[u]._mx = max(g[u]._mx, g[u].mx + _v), g[u].mx += v;
  if (g[u].st == INT_MIN)
    g[u]._ad = max(g[u]._ad, g[u].ad + _v), g[u].ad += v;
  else
    g[u]._st = max(g[u]._st, g[u].st + _v), g[u].st += v;
}
inline void pushset(int u, int v, int _v) {
  g[u]._mx = max(g[u]._mx, _v), g[u].mx = v;
  g[u]._st = max(g[u]._st, _v), g[u].st = v;
}
inline void pushdown(int u, int l, int r) {
  if (g[u].ad)
    pushadd(ls, g[u].ad, g[u]._ad), pushadd(rs, g[u].ad, g[u]._ad),
        g[u].ad = g[u]._ad = 0;
  if (g[u].st != INT_MIN)
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
  n = rd();
  for (int i = 1; i <= n; ++i) a[i] = rd();
  build();
  int m = rd(), z;
  for (int i = 1; i <= m; ++i) {
    char op = nc();
    while (op == ' ' || op == '\r' || op == '\n') op = nc();
    L = rd(), R = rd();
    if (op == 'Q')
      printf("%d\n", qmax());
    else if (op == 'A')
      printf("%d\n", qmaxh());
    else if (op == 'P')
      add(rd());
    else
      tset(rd());
  }
  return 0;
}