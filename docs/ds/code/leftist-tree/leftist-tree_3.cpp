#include <algorithm>
#include <cstdlib>
#include <iostream>
using namespace std;

struct Node {
  int val = 0, ch[2] = {0, 0}, d = 0, fa = 0, ls = 0, rs = 0;
} t[100005];

// --8<-- [start:example96]
int& rs(int x) { return t[x].ch[t[t[x].ch[1]].d < t[t[x].ch[0]].d]; }

// 有了 pushup，直接 merge 左右儿子就实现了删除节点并保持左偏性质
int merge(int x, int y) {
  if (!x || !y) return x | y;
  if (t[x].val < t[y].val) swap(x, y);
  int& rs_ref = rs(x);
  rs_ref = merge(rs_ref, y);
  t[rs_ref].fa = x;
  t[x].d = t[rs(x)].d + 1;
  return x;
}

void pushup(int x) {
  if (!x) return;
  if (t[x].d != t[rs(x)].d + 1) {
    t[x].d = t[rs(x)].d + 1;
    pushup(t[x].fa);
  }
}

void erase(int x) {
  int y = merge(t[x].ch[0], t[x].ch[1]);
  t[y].fa = t[x].fa;
  if (t[t[x].fa].ch[0] == x)
    t[t[x].fa].ch[0] = y;
  else if (t[t[x].fa].ch[1] == x)
    t[t[x].fa].ch[1] = y;
  pushup(t[y].fa);
}

// --8<-- [end:example96]
int main() {
  int n, root = 0;
  cin >> n;
  t[0].d = -1;
  for (int i = 1; i <= n; ++i) {
    cin >> t[i].val;
    root = merge(root, i);
  }
  int removed;
  cin >> removed;
  if (removed == root)
    root = merge(t[removed].ch[0], t[removed].ch[1]), t[root].fa = 0;
  else
    erase(removed);
  while (root) {
    cout << t[root].val;
    root = merge(t[root].ch[0], t[root].ch[1]);
    cout << (root ? " " : "\n");
  }
}
