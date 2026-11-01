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
vector<int> g[N], g2[N];
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
int dfn[N], low[N], dfncnt, s[N], in_stack[N], tp;
int scc[N], sc;  // 结点 i 所在 SCC 的编号
int sz[N];       // 强连通 i 的大小

void tarjan(int u) {
  low[u] = dfn[u] = ++dfncnt, s[++tp] = u, in_stack[u] = 1;
  for (int i = h[u]; i; i = e[i].nex) {
    const int &v = e[i].t;
    if (!dfn[v]) {
      tarjan(v);
      low[u] = min(low[u], low[v]);
    } else if (in_stack[v]) {
      low[u] = min(low[u], dfn[v]);
    }
  }
  if (dfn[u] == low[u]) {
    ++sc;
    do {
      scc[s[tp]] = sc;
      sz[sc]++;
      in_stack[s[tp]] = 0;
    } while (s[tp--] != u);
  }
}

// --8<-- [end:core]

int main() {
  read_graph();
  for (int u = 1; u <= n; ++u)
    if (!dfn[u]) tarjan(u);
  answer(scc, sc);
}
