#include <algorithm>
#include <bitset>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <stack>
#include <vector>

using namespace std;

constexpr int N = 505;
constexpr long long INF = 1000000000000000LL;
int n, m, rk[N][N];
long long d[N][N], val[N];

struct Edge {
  int u, v, w;
};

vector<Edge> a(1);

// --8<-- [start:core]
bool cmp(int a, int b) { return val[a] < val[b]; }

void Floyd() {
  for (int k = 1; k <= n; k++)
    for (int i = 1; i <= n; i++)
      for (int j = 1; j <= n; j++) d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
}

void solve() {
  Floyd();
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      rk[i][j] = j;
      val[j] = d[i][j];
    }
    sort(rk[i] + 1, rk[i] + 1 + n, cmp);
  }
  long long ans = INF;
  // 图的绝对中心可能在结点上
  for (int i = 1; i <= n; i++) ans = min(ans, d[i][rk[i][n]] * 2);
  // 图的绝对中心可能在边上
  for (int i = 1; i <= m; i++) {
    int u = a[i].u, v = a[i].v, w = a[i].w;
    for (int p = n, i = n - 1; i >= 1; i--) {
      if (d[v][rk[u][i]] > d[v][rk[u][p]]) {
        ans = min(ans, d[u][rk[u][i]] + d[v][rk[u][p]] + w);
        p = i;
      }
    }
  }
  // --8<-- [end:core]
  cout << fixed << setprecision(2) << ans / 2.0 << "\n";
  // --8<-- [start:core_end]
}

// --8<-- [end:core_end]

int main() {
  cin >> n >> m;
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= n; ++j) d[i][j] = i == j ? 0 : INF;
  for (int i = 0, u, v, w; i < m; ++i) {
    cin >> u >> v >> w;
    a.push_back({u, v, w});
    d[u][v] = d[v][u] = min(d[u][v], (long long)w);
  }
  solve();
}
