// Sample provenance: Centroid-tree construction demonstration: chain, star,
// singleton; no original judge problem for this preliminary fragment.
#include <algorithm>
#include <iostream>
using namespace std;
constexpr int N = 100005, inf = 1000000000;
int n, h[N], nxt[N * 2], p[N * 2], edges;
int siz[N], maxx[N], sum, rt, fa[N];
bool vis[N];

void add(int u, int v) {
  ++edges;
  p[edges] = v;
  nxt[edges] = h[u];
  h[u] = edges;
}

// --8<-- [start:core]
void calcsiz(int x, int f) {
  siz[x] = 1;
  maxx[x] = 0;
  for (int j = h[x]; j; j = nxt[j])
    if (p[j] != f && !vis[p[j]]) {
      calcsiz(p[j], x);
      siz[x] += siz[p[j]];
      maxx[x] = max(maxx[x], siz[p[j]]);
    }
  maxx[x] =
      max(maxx[x], sum - siz[x]);  // maxx[x] 表示以 x 为根时的最大子树大小
  if (maxx[x] < maxx[rt])
    rt = x;  // 这里不能写 <= ，保证在第二次 calcsiz 时 rt 不改变
}

void pre(int x) {
  vis[x] = true;  // 表示在之后的过程中不考虑 x 这个点
  for (int j = h[x]; j; j = nxt[j])
    if (!vis[p[j]]) {
      sum = siz[p[j]];
      rt = 0;
      maxx[rt] = inf;
      calcsiz(p[j], -1);
      calcsiz(rt, -1);  // 计算两次，第二次求出以 rt 为根时的各子树大小
      fa[rt] = x;
      pre(rt);  // 记录点分树上的父亲
    }
}

// --8<-- [end:core]

// Demonstration input: n and n-1 unweighted tree edges.
// Output: centroid-tree root and parent array.
// --8<-- [start:main_head]
int main() {
  // --8<-- [end:main_head]
  cin >> n;
  for (int i = 1; i < n; ++i) {
    int u, v;
    cin >> u >> v;
    add(u, v);
    add(v, u);
  }
  // --8<-- [start:main_init]
  sum = n;
  rt = 0;
  maxx[rt] = inf;
  calcsiz(1, -1);
  calcsiz(rt, -1);
  // --8<-- [end:main_init]
  int root = rt;
  // --8<-- [start:main_call]
  pre(rt);
  // --8<-- [end:main_call]
  cout << root << '\n';
  for (int u = 1; u <= n; ++u) cout << fa[u] << (u == n ? '\n' : ' ');
  // --8<-- [start:main_end]
}

// --8<-- [end:main_end]
