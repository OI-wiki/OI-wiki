#include <algorithm>
#include <cstdio>
#include <vector>

const int MN = 100005;

int N, M, Q, cnt;
std::vector<int> G[MN], T[MN * 2];

int dfn[MN * 2], low[MN], dfc;
int stk[MN], tp;

void Tarjan(int u) {  // 求点双，准备建树
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

int dep[MN * 2], faz[MN * 2][18], dis[MN * 2];

void DFS(int u, int fz) {
  dfn[u] = ++dfc;
  dep[u] = dep[faz[u][0] = fz] + 1;
  dis[u] = dis[fz] + (u <= N);
  for (int j = 0; j < 17; ++j) faz[u][j + 1] = faz[faz[u][j]][j];
  for (int v : T[u])
    if (v != fz) DFS(v, u);
}

int LCA(int x, int y) {  // 最近公共祖先
  if (dep[x] < dep[y]) std::swap(x, y);
  for (int j = 0, d = dep[x] - dep[y]; d; ++j, d >>= 1)
    if (d & 1) x = faz[x][j];
  if (x == y) return x;
  for (int j = 17; ~j; --j)
    if (faz[x][j] != faz[y][j]) x = faz[x][j], y = faz[y][j];
  return faz[x][0];
}

int main() {
  int Ti;
  scanf("%d", &Ti);
  while (Ti--) {
    scanf("%d%d", &N, &M);
    for (int i = 1; i <= N; ++i) {
      G[i].clear();
      dfn[i] = low[i] = 0;
    }
    for (int i = 1; i <= N * 2; ++i) T[i].clear();
    for (int i = 1, x, y; i <= M; ++i) {
      scanf("%d%d", &x, &y);
      G[x].push_back(y);
      G[y].push_back(x);
    }
    cnt = N;
    dfc = 0, Tarjan(1), --tp;
    dfc = 0, DFS(1, 0);
    scanf("%d", &Q);
    while (Q--) {
      static int S, A[MN];
      scanf("%d", &S);
      int Ans = -2 * S;
      for (int i = 1; i <= S; ++i) scanf("%d", &A[i]);
      std::sort(A + 1, A + S + 1, [](int i, int j) { return dfn[i] < dfn[j]; });
      for (int i = 1; i <= S; ++i) {
        int u = A[i], v = A[i % S + 1];
        Ans += dis[u] + dis[v] - 2 * dis[LCA(u, v)];
      }
      if (LCA(A[1], A[S]) <= N) Ans += 2;
      printf("%d\n", Ans / 2);
    }
  }
  return 0;
}