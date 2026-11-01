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
  vector<vector<long long>> f(n + 1, vector<long long>(n + 1, INF));
  for (int u = 1; u <= n; ++u) f[u][u] = 0;
  while (m--) {
    int u, v;
    long long w;
    cin >> u >> v >> w;
    f[u][v] = min(f[u][v], w);
  }
  int k, x, y;
  // --8<-- [start:core]
  for (k = 1; k <= n; k++) {
    for (x = 1; x <= n; x++) {
      for (y = 1; y <= n; y++) {
        f[x][y] =
            min(f[x][y],
                (f[x][k] == INF || f[k][y] == INF ? INF : f[x][k] + f[k][y]));
      }
    }
  }
  // --8<-- [end:core]
  for (int u = 1; u <= n; ++u) {
    for (int v = 1; v <= n; ++v) {
      if (v > 1) cout << ' ';
      if (f[u][v] == INF)
        cout << "INF";
      else
        cout << f[u][v];
    }
    cout << '\n';
  }
}
