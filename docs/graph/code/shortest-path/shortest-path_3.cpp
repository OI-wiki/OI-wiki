// Sample provenance: Reflexive transitive-closure demonstration; no original
// judge problem in this section.
#include <algorithm>
#include <bitset>
#include <functional>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;
constexpr long long INF = 1LL << 60;
constexpr int MAXN = 100005;

constexpr int SIZE = 1005;
bitset<SIZE> f[SIZE];

int main() {
  int n, m;
  cin >> n >> m;
  for (int u = 1; u <= n; ++u) f[u][u] = true;
  while (m--) {
    int u, v;
    cin >> u >> v;
    f[u][v] = true;
  }
  int k, i;
  // --8<-- [start:core]
  // std::bitset<SIZE> f[SIZE];
  for (k = 1; k <= n; k++)
    for (i = 1; i <= n; i++)
      if (f[i][k]) f[i] = f[i] | f[k];
  // --8<-- [end:core]
  for (int u = 1; u <= n; ++u) {
    for (int v = 1; v <= n; ++v) cout << f[u][v] << (v == n ? '\n' : ' ');
  }
}
