#include <iostream>
#include <queue>
#include <vector>
using namespace std;
constexpr int N = 100005;

struct Node {
  int val;
  vector<Node*> children;
};

// --8<-- [start:core]
vector<vector<int>> levelOrder(Node* root) {
  if (!root) {
    return {};
  }
  vector<vector<int>> res;
  queue<Node*> q;
  q.push(root);
  while (!q.empty()) {
    int currentLevelSize = q.size();  // 当前层的节点个数
    res.push_back(vector<int>());
    for (int i = 0; i < currentLevelSize; ++i) {
      Node* cur = q.front();
      q.pop();
      res.back().push_back(cur->val);
      for (Node* child : cur->children) {  // 把子节点都加入
        q.push(child);
      }
    }
  }
  return res;
}

// --8<-- [end:core]

int main() {
  int n;
  cin >> n;
  vector<Node> nodes(n);
  for (int i = 0; i < n; ++i) nodes[i].val = i + 1;
  for (int i = 1; i < n; ++i) {
    int u, v;
    cin >> u >> v;
    nodes[u].children.push_back(&nodes[v]);
  }
  for (const auto& level : levelOrder(n ? &nodes[0] : nullptr)) {
    for (int i = 0; i < static_cast<int>(level.size()); ++i) {
      if (i) cout << ' ';
      cout << level[i];
    }
    cout << '\n';
  }
}
