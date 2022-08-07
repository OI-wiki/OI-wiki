// Tree Isomorphism, O(nlogn)
// replace quick sort with radix sort ==> O(n)
// Author: _Backl1ght
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e5 + 5;
const int maxn = N << 1;

int n;

struct Edge {
  int v, nxt;
} e[maxn << 1];

int head[maxn], sz[maxn], f[maxn], maxv[maxn], tag[maxn], tot, Max;
vector<int> center[2], L[maxn], subtree_tags[maxn];

void addedge(int u, int v) {  // 建图
  e[tot].v = v;
  e[tot].nxt = head[u];
  head[u] = tot++;
  e[tot].v = u;
  e[tot].nxt = head[v];
  head[v] = tot++;
}

void dfs_size(int u, int fa) {  // 找到 size 值
  sz[u] = 1;
  maxv[u] = 0;
  for (int i = head[u]; i; i = e[i].nxt) {
    int v = e[i].v;
    if (v == fa) continue;
    dfs_size(v, u);
    sz[u] += sz[v];
    maxv[u] = max(maxv[u], sz[v]);
  }
}

void dfs_center(int rt, int u, int fa, int id) {
  maxv[u] = max(maxv[u], sz[rt] - sz[u]);
  if (Max > maxv[u]) {
    center[id].clear();
    Max = maxv[u];
  }
  if (Max == maxv[u]) center[id].push_back(u);  // 如果相等就 push_back
  for (int i = head[u]; i; i = e[i].nxt) {
    int v = e[i].v;
    if (v == fa) continue;
    dfs_center(rt, v, u, id);
  }
}

int dfs_height(int u, int fa, int depth) {  // 递归查找 height
  L[depth].push_back(u);
  f[u] = fa;
  int h = 0;
  for (int i = head[u]; i; i = e[i].nxt) {
    int v = e[i].v;
    if (v == fa) continue;
    h = max(h, dfs_height(v, u, depth + 1));
  }
  return h + 1;
}

void init(int n) {  // 一开始的处理
  for (int i = 1; i <= 2 * n; i++) head[i] = 0;
  tot = 1;
  center[0].clear();
  center[1].clear();

  int u, v;
  for (int i = 1; i <= n - 1; i++) {
    scanf("%d %d", &u, &v);
    addedge(u, v);
  }
  dfs_size(1, -1);
  Max = n;
  dfs_center(1, 1, -1, 0);

  for (int i = 1; i <= n - 1; i++) {
    scanf("%d %d", &u, &v);
    addedge(u + n, v + n);
  }
  dfs_size(1 + n, -1);
  Max = n;
  dfs_center(1 + n, 1 + n, -1, 1);
}

bool cmp(int u, int v) { return subtree_tags[u] < subtree_tags[v]; }

bool rootedTreeIsomorphism(int rt1, int rt2) {
  for (int i = 0; i <= 2 * n + 1; i++) L[i].clear(), subtree_tags[i].clear();
  int h1 = dfs_height(rt1, -1, 0);
  int h2 = dfs_height(rt2, -1, 0);
  if (h1 != h2) return false;
  int h = h1 - 1;
  for (int j = 0; j < (int)L[h].size(); j++) tag[L[h][j]] = 0;
  for (int i = h - 1; i >= 0; i--) {
    for (int j = 0; j < (int)L[i + 1].size(); j++) {
      int v = L[i + 1][j];
      subtree_tags[f[v]].push_back(tag[v]);
    }

    sort(L[i].begin(), L[i].end(), cmp);

    for (int j = 0, cnt = 0; j < (int)L[i].size(); j++) {
      if (j && subtree_tags[L[i][j]] != subtree_tags[L[i][j - 1]]) ++cnt;
      tag[L[i][j]] = cnt;
    }
  }
  return subtree_tags[rt1] == subtree_tags[rt2];
}

bool treeIsomorphism() {
  if (center[0].size() == center[1].size()) {
    if (rootedTreeIsomorphism(center[0][0], center[1][0])) return true;
    if (center[0].size() > 1)
      return rootedTreeIsomorphism(center[0][0], center[1][1]);
  }
  return false;
}

int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    scanf("%d", &n);
    init(n);
    puts(treeIsomorphism() ? "YES" : "NO");
  }
  return 0;
}