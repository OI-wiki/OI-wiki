#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

constexpr int MN = 100005;
constexpr int MS = 524288;
constexpr int Inf = 0x7fffffff;

int N, M, Q, cnt;
int w[MN * 2];
std::vector<int> G[MN], T[MN * 2];
std::multiset<int> S[MN * 2];

int dfn[MN * 2], low[MN], dfc;
int stk[MN], tp;

void Tarjan(int u) {
  low[u] = dfn[u] = ++dfc;
  stk[++tp] = u;
  for (int v : G[u]) {
    if (!dfn[v]) {
      Tarjan(v);
      low[u] = std::min(low[u], low[v]);
      if (low[v] == dfn[u]) {
        ++cnt;
        for (int x = 0; x != v; --tp) {
          x = stk[tp];
          T[cnt].push_back(x);
          T[x].push_back(cnt);
        }
        T[cnt].push_back(u);
        T[u].push_back(cnt);
      }
    } else
      low[u] = std::min(low[u], dfn[v]);
  }
}

int idf[MN * 2], faz[MN * 2], siz[MN * 2], dep[MN * 2], son[MN * 2],
    top[MN * 2];

void DFS0(int u, int fz) {
  faz[u] = fz, dep[u] = dep[fz] + 1, siz[u] = 1;
  for (int v : T[u])
    if (v != fz) {
      DFS0(v, u);
      siz[u] += siz[v];
      if (siz[son[u]] < siz[v]) son[u] = v;
    }
}

void DFS1(int u, int fz, int tp) {
  dfn[u] = ++dfc, idf[dfc] = u, top[u] = tp;
  if (son[u]) DFS1(son[u], u, tp);
  for (int v : T[u])
    if (v != fz && v != son[u]) DFS1(v, u, v);
}

#define li (i << 1)
#define ri (i << 1 | 1)
#define mid ((l + r) >> 1)
#define ls li, l, mid
#define rs ri, mid + 1, r

int dat[MS];

void Build(int i, int l, int r) {  // 建树
  if (l == r) {
    dat[i] = w[idf[l]];
    return;
  }
  Build(ls), Build(rs);
  dat[i] = std::min(dat[li], dat[ri]);
}

void Mdf(int i, int l, int r, int p, int x) {  // 获取最小值
  if (l == r) {
    dat[i] = x;
    return;
  }
  if (p <= mid)
    Mdf(ls, p, x);
  else
    Mdf(rs, p, x);
  dat[i] = std::min(dat[li], dat[ri]);
}

int Qur(int i, int l, int r, int a, int b) {  // 查询
  if (r < a || b < l) return Inf;
  if (a <= l && r <= b) return dat[i];
  return std::min(Qur(ls, a, b), Qur(rs, a, b));
}

using std::cin;
using std::cout;

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  cin >> N >> M >> Q;
  for (int i = 1; i <= N; ++i) cin >> w[i];
  cnt = N;
  for (int i = 1; i <= M; ++i) {
    int u, v;
    cin >> u >> v;
    G[u].push_back(v);
    G[v].push_back(u);
  }
  Tarjan(1), DFS0(1, 0), dfc = 0, DFS1(1, 0, 1);
  for (int i = 1; i <= N; ++i)
    if (faz[i]) S[faz[i]].insert(w[i]);
  for (int i = N + 1; i <= cnt; ++i) w[i] = *S[i].begin();
  Build(1, 1, cnt);
  for (int q = 1; q <= Q; ++q) {
    char opt[3];
    int x, y;
    cin >> opt >> x >> y;
    if (*opt == 'C') {
      Mdf(1, 1, cnt, dfn[x], y);
      if (faz[x]) {
        int u = faz[x];
        S[u].erase(S[u].lower_bound(w[x]));
        S[u].insert(y);
        if (w[u] != *S[u].begin()) {
          w[u] = *S[u].begin();
          Mdf(1, 1, cnt, dfn[u], w[u]);
        }
      }
      w[x] = y;
    } else {
      int Ans = Inf;
      while (top[x] != top[y]) {
        if (dep[top[x]] < dep[top[y]]) std::swap(x, y);
        Ans = std::min(Ans, Qur(1, 1, cnt, dfn[top[x]], dfn[x]));
        x = faz[top[x]];
      }
      if (dfn[x] > dfn[y]) std::swap(x, y);
      Ans = std::min(Ans, Qur(1, 1, cnt, dfn[x], dfn[y]));
      if (x > N) Ans = std::min(Ans, w[faz[x]]);
      cout << Ans << '\n';
    }
  }
  return 0;
}