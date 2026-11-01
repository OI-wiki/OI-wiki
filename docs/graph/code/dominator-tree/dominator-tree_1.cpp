#include <algorithm>
#include <bitset>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <stack>
#include <vector>

using namespace std;

constexpr int N = 200005;
int n;
// --8<-- [start:core]
// 假设图中有 n 个结点, 起始点 s = 1
std::bitset<N> vis;
std::vector<int> edge[N];
std::vector<int> dom[N];

void dfs(int u, int del) {
  vis[u] = true;
  for (int v : edge[u]) {
    if (v == del or vis[v]) {
      continue;
    }
    dfs(v, del);
  }
}

void getdom() {
  for (int u = 1; u <= n; ++u) dom[u].push_back(1);
  for (int i = 2; i <= n; ++i) {
    vis.reset();
    dfs(1, i);
    for (int j = 1; j <= n; ++j) {
      if (!vis[j]) {
        dom[j].push_back(i);
      }
    }
  }
}

// --8<-- [end:core]

int main() {
  int m;
  cin >> n >> m;
  for (int i = 0, u, v; i < m; ++i) {
    cin >> u >> v;
    edge[u].push_back(v);
  }
  getdom();
  vector<int> count(n + 1);
  for (int u = 1; u <= n; ++u)
    for (int v : dom[u]) ++count[v];
  for (int u = 1; u <= n; ++u) cout << count[u] << (u == n ? '\n' : ' ');
}
