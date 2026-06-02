#include <cstring>
#include <iostream>
using namespace std;
constexpr int MAXN = 130;
bool mp[MAXN][MAXN];
int some[MAXN][MAXN], none[MAXN][MAXN], all[MAXN][MAXN];
int n, m, ans;

void dfs(int d, int an, int sn, int nn) {
  if (!sn && !nn) ++ans;
  int u = some[d][0];
  for (int i = 0; i < sn; ++i) {
    int v = some[d][i];
    if (mp[u][v]) continue;
    for (int j = 0; j < an; ++j) all[d + 1][j] = all[d][j];
    all[d + 1][an] = v;
    int tsn = 0, tnn = 0;
    for (int j = 0; j < sn; ++j)
      if (mp[v][some[d][j]]) some[d + 1][tsn++] = some[d][j];
    for (int j = 0; j < nn; ++j)
      if (mp[v][none[d][j]]) none[d + 1][tnn++] = none[d][j];
    dfs(d + 1, an + 1, tsn, tnn);
    some[d][i] = 0, none[d][nn++] = v;
    if (ans > 1000) return;
  }
}

int work() {
  ans = 0;
  for (int i = 0; i < n; ++i) some[1][i] = i + 1;
  dfs(1, 0, n, 0);
  return ans;
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  while (cin >> n >> m) {
    memset(mp, 0, sizeof mp);
    for (int i = 1; i <= m; ++i) {
      int u, v;
      cin >> u >> v;
      mp[u][v] = mp[v][u] = true;
    }
    int tmp = work();
    if (tmp > 1000)
      cout << "Too many maximal sets of friends.\n";
    else
      cout << tmp << '\n';
  }
  return 0;
}
