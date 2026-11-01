#include <algorithm>
#include <bitset>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <stack>
#include <vector>

using namespace std;

constexpr int N = 65537;
int tot;
// --8<-- [start:core]
std::stack<int> sta;
std::vector<int> e[N], g[N], tree[N];  // g 是原图的反图，tree 是支配树
int n, s, in[N], tpn[N], dep[N], idom[N];  // n 为总点数，s 为起始点，in 为入度
int fth[N][17];

void topo(int s) {
  sta.push(s);
  while (!sta.empty()) {
    int u = sta.top();
    sta.pop();
    tpn[++tot] = u;
    for (int v : e[u]) {
      --in[v];
      if (!in[v]) {
        sta.push(v);
      }
    }
  }
}

int lca(int u, int v) {
  if (dep[u] < dep[v]) {
    std::swap(u, v);
  }
  for (int i = 15; i >= 0; --i) {
    if (dep[fth[u][i]] >= dep[v]) {
      u = fth[u][i];
    }
  }
  if (u == v) {
    return u;
  }
  for (int i = 15; i >= 0; --i) {
    if (fth[u][i] != fth[v][i]) {
      u = fth[u][i];
      v = fth[v][i];
    }
  }
  return fth[u][0];
}

void build() {
  topo(s);
  for (int i = 1; i <= n; ++i)
    for (int j = 0; j <= 15; ++j) fth[i][j] = s;
  for (int i = 1; i <= n; ++i) {
    int u = tpn[i];
    if (g[u].size()) {
      int v = g[u][0];
      for (int j = 1, q = g[u].size(); j < q; ++j) {
        v = lca(v, g[u][j]);
      }
      tree[v].push_back(u);
      fth[u][0] = v;
      dep[u] = dep[v] + 1;
      for (int i = 1; i <= 15; ++i) {
        fth[u][i] = fth[fth[u][i - 1]][i - 1];
      }
    }
  }
}

// --8<-- [end:core]

int main() {
  cin >> n;
  int original_n = n;
  s = ++n;
  for (int u = 1; u <= original_n; ++u) {
    int v;
    bool has_food = false;
    while (cin >> v && v) {
      e[v].push_back(u);
      g[u].push_back(v);
      ++in[u];
      has_food = true;
    }
    if (!has_food) {
      e[s].push_back(u);
      g[u].push_back(s);
      ++in[u];
    }
  }
  build();
  vector<int> size(n + 1, 1);
  for (int i = n; i >= 1; --i) {
    int u = tpn[i];
    if (u != s) size[fth[u][0]] += size[u];
  }
  for (int u = 1; u <= original_n; ++u) cout << size[u] - 1 << "\n";
}
