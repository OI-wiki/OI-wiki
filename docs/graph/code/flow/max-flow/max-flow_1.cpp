#include <algorithm>
#include <cassert>
#include <climits>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <limits>
#include <list>
#include <numeric>
#include <queue>
#include <random>
#include <utility>
#include <vector>
using namespace std;
// --8<-- [start:core]
constexpr int MAXN = 250;
constexpr int INF = 0x3f3f3f3f;

struct Edge {
  int from, to, cap, flow;

  Edge(int u, int v, int c, int f) : from(u), to(v), cap(c), flow(f) {}
};

struct EK {
  int n, m;             // n：点数，m：边数
  vector<Edge> edges;   // edges：所有边的集合
  vector<int> G[MAXN];  // G：点 x -> x 的所有边在 edges 中的下标
  int a[MAXN], p[MAXN];  // a：点 x -> BFS 过程中最近接近点 x 的边给它的最大流
                         // p：点 x -> BFS 过程中最近接近点 x 的边

  void init(int n) {
    for (int i = 0; i < n; i++) G[i].clear();
    edges.clear();
  }

  void AddEdge(int from, int to, int cap) {
    edges.push_back(Edge(from, to, cap, 0));
    edges.push_back(Edge(to, from, 0, 0));
    m = edges.size();
    G[from].push_back(m - 2);
    G[to].push_back(m - 1);
  }

  long long Maxflow(int s, int t) {
    long long flow = 0;
    for (;;) {
      memset(a, 0, sizeof(a));
      queue<int> Q;
      Q.push(s);
      a[s] = INF;
      while (!Q.empty()) {
        int x = Q.front();
        Q.pop();
        for (int i = 0; i < G[x].size(); i++) {  // 遍历以 x 作为起点的边
          Edge& e = edges[G[x][i]];
          if (!a[e.to] && e.cap > e.flow) {
            p[e.to] = G[x][i];  // G[x][i] 是最近接近点 e.to 的边
            a[e.to] =
                min(a[x], e.cap - e.flow);  // 最近接近点 e.to 的边赋给它的流
            Q.push(e.to);
          }
        }
        if (a[t]) break;  // 如果汇点接受到了流，就退出 BFS
      }
      if (!a[t])
        break;  // 如果汇点没有接受到流，说明源点和汇点不在同一个连通分量上
      for (int u = t; u != s;
           u = edges[p[u]].from) {  // 通过 u 追寻 BFS 过程中 s -> t 的路径
        edges[p[u]].flow += a[t];      // 增加路径上边的 flow 值
        edges[p[u] ^ 1].flow -= a[t];  // 减小反向路径的 flow 值
      }
      flow += a[t];
    }
    return flow;
  }
};

// --8<-- [end:core]
int main() {
  int n, m, s, t;
  cin >> n >> m >> s >> t;
  EK solver;
  solver.init(n);
  while (m--) {
    int u, v, w;
    cin >> u >> v >> w;
    solver.AddEdge(u - 1, v - 1, w);
  }
  cout << solver.Maxflow(s - 1, t - 1);
}
