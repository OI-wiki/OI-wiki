// Sample provenance: https://www.luogu.com.cn/problem/P2341 (same Popular Cows
// exercise linked in the article); additional disconnected/singleton cases.
#include <algorithm>
#include <cstring>
#include <iostream>
#include <utility>
#include <vector>
using namespace std;
constexpr int N = 100005;
int n, h[N], head[N];

struct Edge {
  int t, nex, to, next;
};

vector<Edge> e(1);
vector<pair<int, int>> edges;
vector<int> g[N], g2[N], s;
bool vis[N];
int color[N], sccCnt;

void read_graph() {
  int m;
  cin >> n >> m;
  while (m--) {
    int u, v;
    cin >> u >> v;
    edges.emplace_back(u, v);
    e.push_back({v, h[u], v, h[u]});
    h[u] = head[u] = static_cast<int>(e.size()) - 1;
    g[u].push_back(v);
    g2[v].push_back(u);
  }
}

void answer(const int component[], int count) {
  vector<int> sizes(count + 1), outgoing(count + 1);
  for (int u = 1; u <= n; ++u) ++sizes[component[u]];
  for (auto edge : edges)
    if (component[edge.first] != component[edge.second])
      outgoing[component[edge.first]] = 1;
  int sink = 0;
  for (int c = 1; c <= count; ++c)
    if (!outgoing[c]) {
      if (sink) {
        cout << 0 << '\n';
        return;
      }
      sink = c;
    }
  cout << sizes[sink] << '\n';
}

// --8<-- [start:core]
// g 是原图，g2 是反图

void dfs1(int u) {
  vis[u] = true;
  for (int v : g[u])
    if (!vis[v]) dfs1(v);
  s.push_back(u);
}

void dfs2(int u) {
  color[u] = sccCnt;
  for (int v : g2[u])
    if (!color[v]) dfs2(v);
}

void kosaraju() {
  sccCnt = 0;
  for (int i = 1; i <= n; ++i)
    if (!vis[i]) dfs1(i);
  for (int i = n - 1; i >= 0; --i)
    if (!color[s[i]]) {
      ++sccCnt;
      dfs2(s[i]);
    }
}

// --8<-- [end:core]

int main() {
  read_graph();
  kosaraju();
  answer(color, sccCnt);
}
