#include <iostream>
#include <queue>
#include <vector>
using namespace std;
constexpr int N = 100005;

constexpr int EMPTY_NODE = -1;
int child[N], sib[N], last[N];
bool first;

void visit(int v) {
  if (!first) cout << ' ';
  first = false;
  cout << v;
}

void by_while(int u) {
  // --8<-- [start:while]
  int v = child[u];  // 从第一个子结点开始
  while (v != EMPTY_NODE) {
    // ...
    // 处理子结点 v
    // ...
    // --8<-- [end:while]
    visit(v);
    // --8<-- [start:while_end]
    v = sib[v];  // 转至下一个子结点，即 v 的一个兄弟
  }
  // --8<-- [end:while_end]
}

void by_for(int u) {
  // --8<-- [start:for]
  for (int v = child[u]; v != EMPTY_NODE; v = sib[v]) {
    // ...
    // 处理子结点 v
    // ...
    // --8<-- [end:for]
    visit(v);
    // --8<-- [start:for_end]
  }
  // --8<-- [end:for_end]
}

int main() {
  int n;
  cin >> n;
  for (int i = 0; i < n; ++i) child[i] = sib[i] = last[i] = EMPTY_NODE;
  for (int i = 1; i < n; ++i) {
    int u, v;
    cin >> u >> v;
    if (last[u] == EMPTY_NODE)
      child[u] = v;
    else
      sib[last[u]] = v;
    last[u] = v;
  }
  first = true;
  by_while(0);
  cout << '\n';
  first = true;
  by_for(0);
  cout << '\n';
}
