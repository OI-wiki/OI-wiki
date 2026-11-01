#include <iostream>
#include <queue>
#include <vector>
using namespace std;
constexpr int N = 100005;

// --8<-- [start:core]
std::vector<int> children[N];
int parent[N];

// --8<-- [end:core]

int main() {
  int n;
  cin >> n;
  parent[0] = -1;
  for (int i = 1; i < n; ++i) {
    int u, v;
    cin >> u >> v;
    children[u].push_back(v);
    parent[v] = u;
  }
  for (int i = 0; i < n; ++i) {
    if (i) cout << ' ';
    cout << parent[i];
  }
  cout << '\n';
  for (int i = 0; i < static_cast<int>(children[0].size()); ++i) {
    if (i) cout << ' ';
    cout << children[0][i];
  }
  cout << '\n';
}
