#include <algorithm>
#include <bitset>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <stack>
#include <vector>

using namespace std;

// 小图演示：所有结点都必须能从 1 到达。
constexpr int N = 2005;
int n;
bool flag;
vector<int> e[N];
// --8<-- [start:relations]
std::vector<int> pre[N];  // 每个结点的前驱结点
std::vector<int> ord;     // 图的逆后序
// --8<-- [start:storage]
// --8<-- [start:storage]
// --8<-- [start:storage]
std::bitset<N> dom[N];
std::vector<int> Dom[N];

// --8<-- [end:storage]
// --8<-- [end:storage]
// --8<-- [end:storage]

void getdom() {
  for (int u = 2; u <= n; ++u) dom[u].set();
  dom[1][1] = true;
  flag = true;
  while (flag) {
    flag = false;
    for (int u : ord) {
      if (u == 1) continue;
      std::bitset<N> tmp;
      tmp.set();
      for (int v : pre[u]) {
        tmp &= dom[v];
      }
      tmp[u] = true;
      if (tmp != dom[u]) {
        dom[u] = tmp;
        flag = true;
      }
    }
  }
  for (int i = 2; i <= n; ++i) {
    for (int j = 1; j <= n; ++j) {
      if (dom[i][j]) {
        Dom[i].push_back(j);
      }
    }
  }
}

// --8<-- [end:relations]
// --8<-- [start:tree]
int idom[N];

void getidom() {
  for (int u = 2; u <= n; ++u) {
    for (int v : Dom[u]) {
      std::bitset<N> tmp = (dom[v] & dom[u]) ^ dom[u];
      if (tmp.count() == 1 and tmp[u]) {
        idom[u] = v;
        break;
      }
    }
  }
  for (int u = 2; u <= n; ++u) {
    e[idom[u]].push_back(u);
  }
}

// --8<-- [end:tree]

vector<int> graph[N];
bool seen[N];

void order(int u) {
  seen[u] = true;
  for (int v : graph[u])
    if (!seen[v]) order(v);
  ord.push_back(u);
}

int main() {
  int m;
  cin >> n >> m;
  if (n >= N) return 1;
  for (int i = 0, u, v; i < m; ++i) {
    cin >> u >> v;
    graph[u].push_back(v);
    pre[v].push_back(u);
  }
  order(1);
  reverse(ord.begin(), ord.end());
  getdom();
  getidom();
  vector<int> count(n + 1);
  for (int u = 1; u <= n; ++u)
    for (int v = u; v; v = idom[v]) ++count[v];
  for (int u = 1; u <= n; ++u) cout << count[u] << (u == n ? '\n' : ' ');
}
