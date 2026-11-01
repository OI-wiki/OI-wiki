// Sample provenance: All-pairs shortest-path demonstration with a negative edge
// and unreachable vertices; no original judge problem in this section.
#include <algorithm>
#include <bitset>
#include <functional>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;
constexpr long long INF = 1LL << 60;
constexpr int MAXN = 100005;

// Demonstration: n m and directed weighted edges; output all-pairs distances.
int main() {
  int n, m;
  cin >> n >> m;
  vector<vector<vector<long long>>> f(
      n + 1, vector<vector<long long>>(n + 1, vector<long long>(n + 1, INF)));
  for (int u = 1; u <= n; ++u) f[0][u][u] = 0;
  while (m--) {
    int u, v;
    long long w;
    cin >> u >> v >> w;
    f[0][u][v] = min(f[0][u][v], w);
  }
  int k, x, y;
  // --8<-- [start:core]
  for (k = 1; k <= n; k++) {
    for (x = 1; x <= n; x++) {
      for (y = 1; y <= n; y++) {
        f[k][x][y] =
            min(f[k - 1][x][y], (f[k - 1][x][k] == INF || f[k - 1][k][y] == INF
                                     ? INF
                                     : f[k - 1][x][k] + f[k - 1][k][y]));
      }
    }
  }
  // --8<-- [end:core]
  for (int u = 1; u <= n; ++u) {
    for (int v = 1; v <= n; ++v) {
      if (v > 1) cout << ' ';
      if (f[n][u][v] == INF)
        cout << "INF";
      else
        cout << f[n][u][v];
    }
    cout << '\n';
  }
}
