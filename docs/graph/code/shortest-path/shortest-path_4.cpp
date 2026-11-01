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
struct Edge {
  int u, v, w;
};

vector<Edge> edge;

long long dis[MAXN];
int u, v, w;

bool bellmanford(int n, int s) {
  fill(dis, dis + n + 1, INF);
  dis[s] = 0;
  bool flag = false;  // 判断一轮循环过程中是否发生松弛操作
  for (int i = 1; i <= n; i++) {
    flag = false;
    for (int j = 0; j < edge.size(); j++) {
      u = edge[j].u, v = edge[j].v, w = edge[j].w;
      if (dis[u] == INF) continue;
      // 无穷大与常数加减仍然为无穷大
      // 因此最短路长度为 INF 的点引出的边不可能发生松弛操作
      if (dis[v] > dis[u] + w) {
        dis[v] = dis[u] + w;
        flag = true;
      }
    }
    // 没有可以松弛的边时就停止算法
    if (!flag) {
      break;
    }
  }
  // 第 n 轮循环仍然可以松弛时说明 s 点可以抵达一个负环
  return flag;
}

// --8<-- [end:core]

int main() {
  int n, m, s;
  cin >> n >> m >> s;
  while (m--) {
    int u, v, w;
    cin >> u >> v >> w;
    edge.push_back({u, v, w});
  }
  if (bellmanford(n, s)) {
    cout << "NEGATIVE CYCLE\n";
    return 0;
  }
  for (int u = 1; u <= n; ++u)
    cout << (dis[u] == INF ? 2147483647LL : dis[u]) << (u == n ? '\n' : ' ');
}
