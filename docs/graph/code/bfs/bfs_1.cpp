#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>
using namespace std;

#include <cstdio>
#include <queue>

struct Edge {
  int to, nxt;
};

vector<Edge> e(1);
vector<int> head, d, p;
vector<bool> vis;
queue<int> Q;

// --8<-- [start:core]
void bfs(int u) {
  while (!Q.empty()) Q.pop();
  Q.push(u);
  vis[u] = 1;
  d[u] = 0;
  p[u] = -1;
  while (!Q.empty()) {
    u = Q.front();
    Q.pop();
    for (int i = head[u]; i; i = e[i].nxt) {
      if (!vis[e[i].to]) {
        Q.push(e[i].to);
        vis[e[i].to] = 1;
        d[e[i].to] = d[u] + 1;
        p[e[i].to] = u;
      }
    }
  }
}

void restore(int x) {
  vector<int> res;
  for (int v = x; v != -1; v = p[v]) {
    res.push_back(v);
  }
  std::reverse(res.begin(), res.end());
  for (int i = 0; i < res.size(); ++i) {
    if (i) printf(" ");
    printf("%d", res[i]);
  }
  puts("");
}

// --8<-- [end:core]

int main() {
  int n, m, start, target;
  cin >> n >> m;
  head.resize(n + 1);
  vis.resize(n + 1);
  d.assign(n + 1, -1);
  p.assign(n + 1, -1);
  for (int i = 0; i < m; ++i) {
    int u, v;
    cin >> u >> v;
    e.push_back(Edge{v, head[u]});
    head[u] = static_cast<int>(e.size()) - 1;
  }
  cin >> start >> target;
  bfs(start);
  cout << d[target] << '\n';
  if (vis[target]) restore(target);
}
