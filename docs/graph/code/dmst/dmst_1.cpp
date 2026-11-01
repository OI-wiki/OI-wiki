#include <algorithm>
#include <bitset>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <stack>
#include <vector>

using namespace std;

constexpr int N = 105;

struct Edge {
  int s, t;
  double w;
};

vector<Edge> e;
int n, m, root, pre[N], id[N], vis[N];
double ans, in[N];

#define f(i, a, b) for (int i = (a); i < (b); ++i)

#define f(i, a, b) for (int i = (a); i < (b); ++i)

#define f(i, a, b) for (int i = (a); i < (b); ++i)

// --8<-- [start:core]
bool solve() {
  ans = 0;
  int u, v;
  for (;;) {
    f(i, 0, n) in[i] = 1e100;
    f(i, 0, m) {
      u = e[i].s;
      v = e[i].t;
      if (u != v && e[i].w < in[v]) {
        in[v] = e[i].w;
        pre[v] = u;
      }
    }
    f(i, 0, n) if (i != root && in[i] > 1e50) return 0;
    int tn = 0;
    memset(id, -1, sizeof id);
    memset(vis, -1, sizeof vis);
    in[root] = 0;
    f(i, 0, n) {
      ans += in[i];
      v = i;
      while (vis[v] != i && id[v] == -1 && v != root) {
        vis[v] = i;
        v = pre[v];
      }
      if (v != root && id[v] == -1) {
        for (int u = pre[v]; u != v; u = pre[u]) id[u] = tn;
        id[v] = tn++;
      }
    }
    if (tn == 0) break;
    f(i, 0, n) if (id[i] == -1) id[i] = tn++;
    f(i, 0, m) {
      u = e[i].s;
      v = e[i].t;
      e[i].s = id[u];
      e[i].t = id[v];
      if (e[i].s != e[i].t) e[i].w -= in[v];
    }
    n = tn;
    root = id[root];
  }
  return true;
}

// --8<-- [end:core]

int main() {
  cin >> n >> m >> root;
  --root;
  for (int i = 0; i < m; ++i) {
    int u, v;
    double w;
    cin >> u >> v >> w;
    e.push_back({u - 1, v - 1, w});
  }
  if (solve())
    cout << fixed << setprecision(0) << ans << "\n";
  else
    cout << -1 << "\n";
}
