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
constexpr int N = 5005, M = 100005, INF = 0x3f3f3f3f;
int n, m, s, t;

// --8<-- [start:core]
struct qxx {
  int nex, t, v, c;
};

qxx e[M];
int h[N], cnt = 1;

void add_path(int f, int t, int v, int c) {
  e[++cnt] = qxx{h[f], t, v, c}, h[f] = cnt;
}

void add_flow(int f, int t, int v, int c) {
  add_path(f, t, v, c);
  add_path(t, f, 0, -c);
}

int dis[N], pre[N], incf[N];
bool vis[N];

bool spfa() {
  memset(dis, 0x3f, sizeof(dis));
  queue<int> q;
  q.push(s), dis[s] = 0, incf[s] = INF, incf[t] = 0;
  while (q.size()) {
    int u = q.front();
    q.pop();
    vis[u] = false;
    for (int i = h[u]; i; i = e[i].nex) {
      const int &v = e[i].t, &w = e[i].v, &c = e[i].c;
      if (!w || dis[v] <= dis[u] + c) continue;
      dis[v] = dis[u] + c, incf[v] = min(w, incf[u]), pre[v] = i;
      if (!vis[v]) q.push(v), vis[v] = true;
    }
  }
  return incf[t];
}

int maxflow, mincost;

void update() {
  maxflow += incf[t];
  for (int u = t; u != s; u = e[pre[u] ^ 1].t) {
    e[pre[u]].v -= incf[t], e[pre[u] ^ 1].v += incf[t];
    mincost += incf[t] * e[pre[u]].c;
  }
}

// 调用：while(spfa())update();
// --8<-- [end:core]
int main() {
  cin >> n >> m >> s >> t;
  while (m--) {
    int u, v, w, c;
    cin >> u >> v >> w >> c;
    add_flow(u, v, w, c);
  }
  while (spfa()) update();
  cout << maxflow << " " << mincost;
}
