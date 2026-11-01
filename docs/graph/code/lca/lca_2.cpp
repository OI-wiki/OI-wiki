// Sample source: https://www.luogu.com.cn/problem/P3379
#include <algorithm>
#include <iostream>
constexpr int N = 500005;
int head[N], depth[(N << 1) + 2], lg[(N << 1) + 2], count_edges;

struct Edge {
  int to, next;
} side[N << 1];

void add(int u, int v) {
  side[++count_edges] = Edge{v, head[u]};
  head[u] = count_edges;
}

// --8<-- [start:core]
int dfn[N << 1], pos[N], tot, st[30][(N << 1) + 2],
    rev[30][(N << 1) + 2];  // rev表示最小深度对应的节点编号

void dfs(int cur, int dep) {
  dfn[++tot] = cur;
  depth[tot] = dep;
  pos[cur] = tot;
  for (int i = head[cur]; i; i = side[i].next) {
    int v = side[i].to;
    if (!pos[v]) {
      dfs(v, dep + 1);
      dfn[++tot] = cur, depth[tot] = dep;
    }
  }
}

void init() {
  for (int i = 2; i <= tot + 1; ++i)
    lg[i] = lg[i >> 1] + 1;  // 预处理 lg 代替库函数 log2 来优化常数
  for (int i = 1; i <= tot; i++) st[0][i] = depth[i], rev[0][i] = dfn[i];
  for (int i = 1; i <= lg[tot]; i++)
    for (int j = 1; j + (1 << i) - 1 <= tot; j++)
      if (st[i - 1][j] < st[i - 1][j + (1 << i - 1)])
        st[i][j] = st[i - 1][j], rev[i][j] = rev[i - 1][j];
      else
        st[i][j] = st[i - 1][j + (1 << i - 1)],
        rev[i][j] = rev[i - 1][j + (1 << i - 1)];
}

int query(int l, int r) {
  int k = lg[r - l + 1];
  return st[k][l] < st[k][r + 1 - (1 << k)] ? rev[k][l]
                                            : rev[k][r + 1 - (1 << k)];
}

// --8<-- [end:core]

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int n, m, root;
  std::cin >> n >> m >> root;
  for (int i = 1; i < n; ++i) {
    int u, v;
    std::cin >> u >> v;
    add(u, v);
    add(v, u);
  }
  dfs(root, 0);
  init();
  while (m--) {
    int u, v;
    std::cin >> u >> v;
    int left = pos[u], right = pos[v];
    if (left > right) std::swap(left, right);
    std::cout << query(left, right) << '\n';
  }
}
