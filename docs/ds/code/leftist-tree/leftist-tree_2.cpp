#include <algorithm>
#include <cstdlib>
#include <iostream>
using namespace std;

struct Node {
  int val = 0, ch[2] = {0, 0}, d = 0, fa = 0, ls = 0, rs = 0;
} t[100005];

// --8<-- [start:example95]
int& rs(int x) { return t[x].ch[t[t[x].ch[1]].d < t[t[x].ch[0]].d]; }

int merge(int x, int y) {
  if (!x || !y) return x | y;
  if (t[x].val < t[y].val) swap(x, y);
  int& rs_ref = rs(x);
  rs_ref = merge(rs_ref, y);
  t[x].d = t[rs(x)].d + 1;
  return x;
}

// --8<-- [end:example95]
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
    root = merge(t[root].ch[0], t[root].ch[1]);
    cout << (root ? " " : "\n");
  }
}
