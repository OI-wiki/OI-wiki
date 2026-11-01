#include <iostream>
#include <queue>
#include <vector>
using namespace std;
constexpr int N = 100005;

// --8<-- [start:adj]
std::vector<int> adj[N];
// --8<-- [end:adj]
vector<int> order;

// --8<-- [start:dfs]
void dfs(int u, int from) {
  // --8<-- [end:dfs]
  order.push_back(u);
  // --8<-- [start:dfs_body]
  // 递归进入除了 from 之外的所有子结点
  // 对于出发结点，from 为空，故会访问所有相邻结点，这与期望一致
  for (int v : adj[u])
    if (v != from) {
      dfs(v, u);
    }
}

// --8<-- [end:dfs_body]

int main() {
  int n;
  cin >> n;
  for (int i = 1; i < n; ++i) {
    int u, v;
    cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }
  // --8<-- [start:start]
  // 开始遍历时
  int EMPTY_NODE = -1;  // 一个不存在的编号
  int root = 0;         // 任取一个结点作为出发点
  dfs(root, EMPTY_NODE);
  // --8<-- [end:start]

  for (int i = 0; i < n; ++i) {
    if (i) cout << ' ';
    cout << order[i];
  }
  cout << '\n';
}
