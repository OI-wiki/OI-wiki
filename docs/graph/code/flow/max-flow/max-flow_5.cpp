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
constexpr int N = 1e4 + 4, M = 1e5 + 5, INF = 0x3f3f3f3f;
int n, m, s, t, maxflow, tot;
int ht[N];
long long ex[N];

// --8<-- [end:core]

struct Edge {
  int nex, t;
  long long v;
};

Edge e[M * 2];
int h[N], cnt = 1;

// --8<-- [start:core_body]

void init() {  // 初始化
  for (int i = h[s]; i; i = e[i].nex) {
    const int &v = e[i].t;
    ex[v] += e[i].v, ex[s] -= e[i].v, e[i ^ 1].v += e[i].v, e[i].v = 0;
  }
  ht[s] = n;
}

bool push(int ed) {
  const int &u = e[ed ^ 1].t, &v = e[ed].t;
  long long flow = min(ex[u], e[ed].v);
  ex[u] -= flow, ex[v] += flow, e[ed].v -= flow, e[ed ^ 1].v += flow;
  return ex[u];  // 如果 u 仍溢出，返回 1
}

void relabel(int u) {
  ht[u] = INF;
  for (int i = h[u]; i; i = e[i].nex)
    if (e[i].v) ht[u] = min(ht[u], ht[e[i].t]);
  ++ht[u];
}

// --8<-- [end:core_body]
void add(int u, int v, int w) {
  e[++cnt] = {h[u], v, w};
  h[u] = cnt;
  e[++cnt] = {h[v], u, 0};
  h[v] = cnt;
}

int main() {
  cin >> n >> m >> s >> t;
  while (m--) {
    int u, v, w;
    cin >> u >> v >> w;
    if (u != v) add(u, v, w);
  }
  init();
  for (;;) {
    int u = 1;
    while (u <= n && (u == s || u == t || ex[u] == 0)) ++u;
    if (u > n) break;
    while (ex[u] > 0) {
      for (int i = h[u]; i && ex[u] > 0; i = e[i].nex)
        if (e[i].v > 0 && ht[u] == ht[e[i].t] + 1) push(i);
      if (ex[u] > 0) relabel(u);
    }
  }
  cout << ex[t];
}
