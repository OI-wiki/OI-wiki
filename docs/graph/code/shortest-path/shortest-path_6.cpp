// Sample provenance: https://www.luogu.com.cn/problem/P3371; additional
// overflow, unreachable, and applicable negative-edge/cycle cases.
#include <algorithm>
#include <bitset>
#include <functional>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;
constexpr long long INF = 1LL << 60;
constexpr int MAXN = 100005;

// --8<-- [start:core]
struct edge {
  int v, w;
};

vector<edge> e[MAXN];
long long dis[MAXN];
int vis[MAXN];

void dijkstra(int n, int s) {
  fill(dis, dis + n + 1, INF);
  dis[s] = 0;
  for (int i = 1; i <= n; i++) {
    int u = 0;
    long long mind = INF;
    for (int j = 1; j <= n; j++)
      if (!vis[j] && dis[j] < mind) u = j, mind = dis[j];
    if (!u) break;
    vis[u] = true;
    for (auto ed : e[u]) {
      int v = ed.v, w = ed.w;
      if (dis[v] > dis[u] + w) dis[v] = dis[u] + w;
    }
  }
}

// --8<-- [end:core]

int main() {
  int n, m, s;
  cin >> n >> m >> s;
  while (m--) {
    int u, v, w;
    cin >> u >> v >> w;
    e[u].push_back({v, w});
  }
  dijkstra(n, s);
  for (int u = 1; u <= n; ++u)
    cout << (dis[u] == INF ? 2147483647LL : dis[u]) << (u == n ? '\n' : ' ');
}
