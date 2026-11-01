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

int stack1[N], stack2[N], p1, p2, low[N], dfs_clock, sccno[N], scc_cnt;

// --8<-- [start:core]
int garbow(int u) {
  stack1[++p1] = u;
  stack2[++p2] = u;
  low[u] = ++dfs_clock;
  for (int i = head[u]; i; i = e[i].next) {
    int v = e[i].to;
    if (!low[v])
      garbow(v);
    else if (!sccno[v])
      while (low[stack2[p2]] > low[v]) p2--;
  }
  if (stack2[p2] == u) {
    p2--;
    scc_cnt++;
    do {
      sccno[stack1[p1]] = scc_cnt;
      // all_scc[scc_cnt] ++;
    } while (stack1[p1--] != u);
  }
  return 0;
}

void find_scc(int n) {
  dfs_clock = scc_cnt = 0;
  p1 = p2 = 0;
  memset(sccno, 0, sizeof(sccno));
  memset(low, 0, sizeof(low));
  for (int i = 1; i <= n; i++)
    if (!low[i]) garbow(i);
}

// --8<-- [end:core]

int main() {
  read_graph();
  find_scc(n);
  answer(sccno, scc_cnt);
}
