#include <algorithm>
#include <cstdlib>
#include <iostream>
using namespace std;

struct Node {
  int val = 0, ch[2] = {0, 0}, d = 0, fa = 0, ls = 0, rs = 0;
} t[100005];

// --8<-- [start:example98]
int merge(int x, int y) {
  if (!x || !y) return x | y;
  if (t[y].val < t[x].val) swap(x, y);
  if (rand() & 1)  // 随机选择是否交换左右子节点
    swap(t[x].ls, t[x].rs);
  t[x].ls = merge(t[x].ls, y);
  return x;
}

// --8<-- [end:example98]
int main() {
  int n, root = 0;
  cin >> n;
  t[0].d = -1;
  for (int i = 1; i <= n; ++i) {
    cin >> t[i].val;
    root = merge(root, i);
  }
  while (root) {
    cout << t[root].val;
    root = merge(t[root].ls, t[root].rs);
    cout << (root ? " " : "\n");
  }
}
