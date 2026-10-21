#include <algorithm>
#include <iostream>
#include <vector>

constexpr int MN = 100005;

int N, M, cnt;
std::vector<int> G[MN], T[MN * 2];
long long Ans;

int dfn[MN], low[MN], dfc, num;
int stk[MN], tp;

int wgh[MN * 2];

void Tarjan(int u) {  // 求点双
  low[u] = dfn[u] = ++dfc;
  stk[++tp] = u;
  ++num;
  for (int v : G[u]) {
    if (!dfn[v]) {
      Tarjan(v);
      low[u] = std::min(low[u], low[v]);
      if (low[v] == dfn[u]) {
        wgh[++cnt] = 0;
        for (int x = 0; x != v; --tp) {
          x = stk[tp];
          T[cnt].push_back(x);
          T[x].push_back(cnt);
          ++wgh[cnt];
        }
        T[cnt].push_back(u);
        T[u].push_back(cnt);
        ++wgh[cnt];
      }
    } else
      low[u] = std::min(low[u], dfn[v]);
  }
}

int vis[MN * 2], siz[MN * 2];

void DFS(int u, int fz) {  // dfs求值
  vis[u] = 1;
  siz[u] = (u <= N);
  for (int v : T[u])
    if (v != fz) {
      DFS(v, u);
      Ans += 2ll * wgh[u] * siz[u] * siz[v];
      siz[u] += siz[v];
    }
  Ans += 2ll * wgh[u] * siz[u] * (num - siz[u]);
}

using std::cin;
using std::cout;

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  cin >> N >> M;
  for (int u = 1; u <= N; ++u) wgh[u] = -1;
  cnt = N;
  for (int i = 1; i <= M; ++i) {
    int u, v;
    cin >> u >> v;
    G[u].push_back(v);
    G[v].push_back(u);
  }
  for (int u = 1; u <= N; ++u)
    if (!dfn[u]) {
      num = 0;
      Tarjan(u), --tp;
      DFS(u, 0);
    }
  cout << Ans << '\n';
  return 0;
}