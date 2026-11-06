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

int dfn[MAXN];
int (&id)[MAXN] = dfn;
int h[MAXN], k, sta[MAXN], top;

// --8<-- [start:core]
bool cmp(const int x, const int y) { return id[x] < id[y]; }

void build() {
  sort(h + 1, h + k + 1, cmp);
  sta[top = 1] = 1, g.sz = 0, g.head[1] = -1;
  // 1 号节点入栈，清空 1 号节点对应的邻接表，设置邻接表边数为 0
  for (int i = 1, l; i <= k; ++i)
    if (h[i] != 1) {
      // 如果 1 号节点是关键节点就不要重复添加
      l = lca(h[i], sta[top]);
      // 计算当前节点与栈顶节点的 LCA
      if (l != sta[top]) {
        // 如果 LCA 和栈顶元素不同，则说明当前节点不在当前栈所存的链上
        while (id[l] < id[sta[top - 1]])
          // 当次大节点的 Dfs 序大于 LCA 的 Dfs 序
          g.push(sta[top - 1], sta[top]), top--;
        // 把与当前节点所在的链不重合的链连接掉并且弹出
        if (id[l] > id[sta[top - 1]])
          // 如果 LCA 不等于次大节点（这里的大于其实和不等于没有区别）
          g.head[l] = -1, g.push(l, sta[top]), sta[top] = l;
        // 说明 LCA 是第一次入栈，清空其邻接表，连边后弹出栈顶元素，并将 LCA
        // 入栈
        else
          g.push(l, sta[top--]);
        // 说明 LCA 就是次大节点，直接弹出栈顶元素
      }
      g.head[h[i]] = -1, sta[++top] = h[i];
      // 当前节点必然是第一次入栈，清空邻接表并入栈
    }
  for (int i = 1; i < top; ++i)
    g.push(sta[i], sta[i + 1]);  // 剩余的最后一条链连接一下
  return;
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
    k = count;
    build();
    cout << solve() << '\n';
    for (int v : keys) key[v] = false;
  }
}
