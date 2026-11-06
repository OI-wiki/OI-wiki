// Sample provenance: https://www.luogu.com.cn/problem/P3371; additional
// overflow, unreachable, and applicable negative-edge/cycle cases.
#include <algorithm>
#include <bitset>
#include <cstring>
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

struct node {
  long long dis;
  int u;

  bool operator>(const node& a) const { return dis > a.dis; }
};

vector<edge> e[MAXN];
long long dis[MAXN];
int vis[MAXN];
priority_queue<node, vector<node>, greater<node>> q;

void dijkstra(int n, int s) {
  fill(dis, dis + n + 1, INF);
  memset(vis, 0, (n + 1) * sizeof(int));
  dis[s] = 0;
  q.push({0, s});
  while (!q.empty()) {
    int u = q.top().u;
    q.pop();
    if (vis[u]) continue;
    vis[u] = 1;
    for (auto ed : e[u]) {
      int v = ed.v, w = ed.w;
      if (dis[v] > dis[u] + w) {
        dis[v] = dis[u] + w;
        q.push({dis[v], v});
      }
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
