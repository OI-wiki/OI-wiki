#include <algorithm>
#include <cstdint>
#include <cstring>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

constexpr int MAXN = 100005;

// --8<-- [start:core]
int n, m;
vector<int> G[MAXN];
int in[MAXN];  // 存储每个结点的入度

bool toposort() {
  vector<int> L;
  queue<int> S;
  for (int i = 1; i <= n; i++)
    if (in[i] == 0) S.push(i);
  while (!S.empty()) {
    int u = S.front();
    S.pop();
    L.push_back(u);
    for (auto v : G[u]) {
      if (--in[v] == 0) {
        S.push(v);
      }
    }
  }
  if (L.size() == n) {
    for (auto i : L) cout << i << ' ';
    return true;
  }
  return false;
}

// --8<-- [end:core]

int main() {
  cin >> n >> m;
  for (int i = 0; i < m; ++i) {
    int u, v;
    cin >> u >> v;
    G[u].push_back(v);
    ++in[v];
  }
  if (!toposort()) cout << "cycle\n";
}
