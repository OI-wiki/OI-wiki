// Sample provenance: https://www.luogu.com.cn/problem/P2495; added
// repeated-query and ancestor-key regression.
#include <algorithm>
#include <climits>
#include <iostream>
#include <utility>
#include <vector>
using namespace std;
constexpr int MAXN = 250005, LOG = 19;
int n, up[MAXN][LOG], minimum[MAXN][LOG], depth[MAXN];
extern int dfn[MAXN];
vector<pair<int, int>> tree[MAXN];
bool key[MAXN];
long long dp[MAXN];

void prepare() {
  vector<int> pending{1};
  int timer = 0;
  for (int j = 0; j < LOG; ++j) {
    up[1][j] = 1;
    minimum[1][j] = INT_MAX;
  }
  while (!pending.empty()) {
    int u = pending.back();
    pending.pop_back();
    dfn[u] = ++timer;
    for (auto edge : tree[u]) {
      int v = edge.first;
      if (v == up[u][0]) continue;
      up[v][0] = u;
      minimum[v][0] = edge.second;
      depth[v] = depth[u] + 1;
      for (int j = 1; j < LOG; ++j) {
        up[v][j] = up[up[v][j - 1]][j - 1];
        minimum[v][j] = min(minimum[v][j - 1], minimum[up[v][j - 1]][j - 1]);
      }
      pending.push_back(v);
    }
  }
}

int lca(int u, int v) {
  if (depth[u] < depth[v]) swap(u, v);
  int difference = depth[u] - depth[v];
  for (int j = 0; j < LOG; ++j)
    if ((difference >> j) & 1) u = up[u][j];
  if (u == v) return u;
  for (int j = LOG - 1; j >= 0; --j)
    if (up[u][j] != up[v][j]) {
      u = up[u][j];
      v = up[v][j];
    }
  return up[u][0];
}

int path_minimum(int ancestor, int descendant) {
  int answer = INT_MAX, difference = depth[descendant] - depth[ancestor];
  for (int j = 0; j < LOG; ++j)
    if ((difference >> j) & 1) {
      answer = min(answer, minimum[descendant][j]);
      descendant = up[descendant][j];
    }
  return answer;
}

struct VirtualGraph {
  int head[MAXN], to[MAXN], next[MAXN], weight[MAXN], sz = 0;

  void push(int u, int v) {
    to[sz] = v;
    next[sz] = head[u];
    weight[sz] = path_minimum(u, v);
    head[u] = sz++;
  }
} g;

void conn(int u, int v) { g.push(u, v); }

long long solve() {
  vector<int> order{1};
  for (size_t i = 0; i < order.size(); ++i)
    for (int edge = g.head[order[i]]; edge != -1; edge = g.next[edge])
      order.push_back(g.to[edge]);
  for (auto it = order.rbegin(); it != order.rend(); ++it) {
    int u = *it;
    dp[u] = 0;
    for (int edge = g.head[u]; edge != -1; edge = g.next[edge])
      dp[u] += min(dp[g.to[edge]], static_cast<long long>(g.weight[edge]));
    if (key[u]) dp[u] = 1LL << 60;
  }
  return dp[1];
}

// --8<-- [start:core]
int dfn[MAXN];
int h[MAXN], m, a[MAXN * 2], len;  // 存储关键点

bool cmp(int x, int y) {
  return dfn[x] < dfn[y];  // 按照 dfs 序排序
}

void build_virtual_tree() {
  len = 0;
  g.sz = 0;
  sort(h + 1, h + m + 1, cmp);  // 把关键点按照 dfs 序排序
  for (int i = 1; i < m; ++i) {
    a[++len] = h[i];
    a[++len] = lca(h[i], h[i + 1]);  // 插入 lca
  }
  a[++len] = h[m];
  sort(a + 1, a + len + 1, cmp);  // 把所有虚树上的点按照 dfs 序排序
  len = unique(a + 1, a + len + 1) - a - 1;  // 去重
  for (int i = 1; i <= len; ++i) g.head[a[i]] = -1;
  for (int i = 1, lc; i < len; ++i) {
    lc = lca(a[i], a[i + 1]);
    conn(lc, a[i + 1]);  // 连边，如有边权 就是 distance(lc,a[i+1])
  }
}

// --8<-- [end:core]

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  cin >> n;
  for (int i = 1; i < n; ++i) {
    int u, v, w;
    cin >> u >> v >> w;
    tree[u].emplace_back(v, w);
    tree[v].emplace_back(u, w);
  }
  prepare();
  int queries;
  cin >> queries;
  while (queries--) {
    int count;
    cin >> count;
    vector<int> keys(count);
    for (int i = 0; i < count; ++i) {
      cin >> keys[i];
      h[i + 1] = keys[i];
      key[keys[i]] = true;
    }
    m = count;
    h[++m] = 1;
    build_virtual_tree();
    cout << solve() << '\n';
    for (int v : keys) key[v] = false;
  }
}
