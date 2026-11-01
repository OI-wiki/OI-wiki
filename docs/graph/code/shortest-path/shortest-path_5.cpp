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
int cnt[MAXN], vis[MAXN];
queue<int> q;

bool spfa(int n, int s) {
  fill(dis, dis + n + 1, INF);
  dis[s] = 0, vis[s] = 1;
  q.push(s);
  while (!q.empty()) {
    int u = q.front();
    q.pop(), vis[u] = 0;
    for (auto ed : e[u]) {
      int v = ed.v, w = ed.w;
      if (dis[v] > dis[u] + w) {
        dis[v] = dis[u] + w;
        cnt[v] = cnt[u] + 1;  // 记录最短路经过的边数
        if (cnt[v] >= n) return false;
        // 在不经过负环的情况下，最短路至多经过 n - 1 条边
        // 因此如果经过了多于 n 条边，一定说明经过了负环
        if (!vis[v]) q.push(v), vis[v] = 1;
      }
    }
  }
  return true;
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
  if (!spfa(n, s)) {
    cout << "NEGATIVE CYCLE\n";
    return 0;
  }
  for (int u = 1; u <= n; ++u)
    cout << (dis[u] == INF ? 2147483647LL : dis[u]) << (u == n ? '\n' : ' ');
}
