#include <algorithm>
#include <cstddef>
#include <iostream>
#include <numeric>
#include <vector>
using namespace std;

constexpr int N = 100005;
// --8<-- [start:example63]
std::vector<int> G[N];
int n, fa[N], son[N], sz[N];

void dfsS(int u) {
  sz[u] = 1;
  for (int v : G[u]) {
    dfsS(v);
    sz[u] += sz[v];
    if (sz[v] > sz[son[u]]) son[u] = v;
  }
}

int b[N], bs[N], l[N], r[N], f[N], ss[N];

// 给b中[bl,br)内的点建二叉树，返回二叉树的根
int cbuild(int bl, int br) {
  int x = bl, y = br;
  while (y - x > 1) {
    int mid = (x + y) >> 1;
    if (2 * (bs[mid] - bs[bl]) <= bs[br] - bs[bl])
      x = mid;
    else
      y = mid;
  }
  // 二分求出按bs加权的中点
  y = b[x];
  ss[y] = br - bl;  // ss：二叉树中重子树的大小
  if (bl < x) {
    l[y] = cbuild(bl, x);
    f[l[y]] = y;
  }
  if (x + 1 < br) {
    r[y] = cbuild(x + 1, br);
    f[r[y]] = y;
  }
  return y;
}

int build(int x) {
  int y = x;
  do
    for (int v : G[y])
      if (v != son[y])
        f[build(v)] =
            y;  // 递归建树并连轻边，注意要从二叉树的根连边，不是从儿子连边
  while (y = son[y]);
  y = 0;
  do {
    b[y++] = x;                              // 存放重链中的点
    bs[y] = bs[y - 1] + sz[x] - sz[son[x]];  // bs：轻儿子size和+1，求前缀和
  } while (x = son[x]);
  return cbuild(0, y);
}

// --8<-- [end:example63]
// --8<-- [start:example64]
// a：子树加标记
// s：子树和（不算加标记的）
int a[N], s[N];

void add(int x) {
  bool t = true;
  int z = 0;
  while (x) {
    s[x] += z;
    if (t) {
      a[x]++;
      if (r[x]) a[r[x]]--;
      z += 1 + ss[l[x]];
      s[x] -= ss[r[x]];
    }
    t = (x != l[f[x]]);
    if (t && x != r[f[x]]) z = 0;  // 跳过轻边要清空
    x = f[x];
  }
}

int query(int x) {
  int ret = 0;
  bool t = true;
  int z = 0;
  while (x) {
    if (t) {
      ret += s[x] - s[r[x]];
      ret -= 1ll * ss[r[x]] * a[r[x]];
      z += 1 + ss[l[x]];
    }
    ret += 1ll * z * a[x];
    t = (x != l[f[x]]);
    if (t && x != r[f[x]]) z = 0;  // 跳过轻边要清空
    x = f[x];
  }
  return ret;
}

// --8<-- [end:example64]
int main() {
  int q;
  cin >> n >> q;
  for (int i = 2; i <= n; ++i) {
    cin >> fa[i];
    G[fa[i]].push_back(i);
  }
  dfsS(1);
  build(1);
  while (q--) {
    int op, x;
    cin >> op >> x;
    if (op == 1)
      add(x);
    else
      cout << query(x) << "\n";
  }
}
