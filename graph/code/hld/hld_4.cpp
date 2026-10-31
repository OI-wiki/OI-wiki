#include <iostream>
#include <vector>

using lint = long long;
constexpr int N = 1e5 + 10;

int n, m, root, a[N];
std::vector<int> G[N];

int idx, fa[N], dep[N], siz[N], son[N], top[N], dfn[N], rnk[N];

struct SegmentTree {  // 区间加，区间求和的线段树实现
  lint sum[N << 2], lzy[N << 2];

  void maketag(int u, int l, int r, lint x) {
    sum[u] += (r - l + 1) * x;
    lzy[u] += x;
  }

  void pushup(int u) { sum[u] = sum[u << 1] + sum[u << 1 | 1]; }

  void pushdown(int u, int l, int r) {
    int mid = l + r >> 1;
    maketag(u << 1, l, mid, lzy[u]);
    maketag(u << 1 | 1, mid + 1, r, lzy[u]);
    lzy[u] = 0;
  }

  void build(int u, int l, int r) {
    if (l == r) {
      sum[u] = a[rnk[l]];
      return;
    }
    int mid = l + r >> 1;
    build(u << 1, l, mid), build(u << 1 | 1, mid + 1, r);
    pushup(u);
  }

  void upd(int u, int l, int r, int ql, int qr, lint x) {
    if (ql <= l && r <= qr) {
      maketag(u, l, r, x);
      return;
    }
    int mid = l + r >> 1;
    pushdown(u, l, r);
    if (ql <= mid) upd(u << 1, l, mid, ql, qr, x);
    if (qr > mid) upd(u << 1 | 1, mid + 1, r, ql, qr, x);
    pushup(u);
  }

  lint ask(int u, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr) return sum[u];
    int mid = l + r >> 1;
    pushdown(u, l, r);
    if (qr <= mid) return ask(u << 1, l, mid, ql, qr);
    if (ql > mid) return ask(u << 1 | 1, mid + 1, r, ql, qr);
    return ask(u << 1, l, mid, ql, qr) + ask(u << 1 | 1, mid + 1, r, ql, qr);
  }
} T;

void dfs1(int u, int f) {  // 树剖预处理 1
  fa[u] = f, dep[u] = dep[f] + 1, siz[u] = 1;
  for (auto v : G[u]) {
    if (v == f) continue;
    dfs1(v, u);
    siz[u] += siz[v];
    if (siz[v] > siz[son[u]]) son[u] = v;
  }
}

void dfs2(int u, int tp) {  // 树剖预处理 2
  top[u] = tp, dfn[u] = ++idx, rnk[idx] = u;
  if (son[u]) dfs2(son[u], tp);
  for (auto v : G[u])
    if (v != fa[u] && v != son[u]) dfs2(v, v);
}

void modify_path(int u, int v, int w) {  // 正常树剖
  while (top[u] != top[v]) {
    if (dep[top[u]] < dep[top[v]]) std::swap(u, v);
    T.upd(1, 1, n, dfn[top[u]], dfn[u], w);
    u = fa[top[u]];
  }
  if (dep[u] < dep[v]) std::swap(u, v);
  T.upd(1, 1, n, dfn[v], dfn[u], w);
}

void modify_subtree(int u, int w) {
  if (u == root)
    T.maketag(1, 1, n, w);
  else if (dfn[u] <= dfn[root] && dfn[root] <= dfn[u] + siz[u] - 1) {
    int v = root;
    while (dep[top[v]] > dep[u] + 1) v = fa[top[v]];  // 向上跳
    v = rnk[dfn[top[v]] + dep[u] + 1 - dep[top[v]]];  // 计算 v
    // 上面这一句可以替换为如下两句：
    // if (dep[top[v]] == dep[u] + 1) v = top[v];
    // else if (dep[top[v]] < dep[u] + 1) v = rnk[dfn[u] + 1];
    if (1 <= dfn[v] - 1) T.upd(1, 1, n, 1, dfn[v] - 1, w);
    if (dfn[v] + siz[v] <= n) T.upd(1, 1, n, dfn[v] + siz[v], n, w);
  } else
    T.upd(1, 1, n, dfn[u], dfn[u] + siz[u] - 1, w);
}

lint query_path(int u, int v) {  // 正常树剖
  lint res = 0;
  while (top[u] != top[v]) {
    if (dep[top[u]] < dep[top[v]]) std::swap(u, v);
    res += T.ask(1, 1, n, dfn[top[u]], dfn[u]);
    u = fa[top[u]];
  }
  if (dep[u] < dep[v]) std::swap(u, v);
  res += T.ask(1, 1, n, dfn[v], dfn[u]);
  return res;
}

lint query_subtree(int u) {
  if (u == root) return T.sum[1];
  if (dfn[u] <= dfn[root] && dfn[root] <= dfn[u] + siz[u] - 1) {
    int v = root;
    while (dep[top[v]] > dep[u] + 1) v = fa[top[v]];
    v = rnk[dfn[top[v]] + dep[u] + 1 - dep[top[v]]];
    lint res = 0;
    if (1 <= dfn[v] - 1) res += T.ask(1, 1, n, 1, dfn[v] - 1);
    if (dfn[v] + siz[v] <= n) res += T.ask(1, 1, n, dfn[v] + siz[v], n);
    return res;
  }
  return T.ask(1, 1, n, dfn[u], dfn[u] + siz[u] - 1);
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  std::cin >> n, root = 1;
  for (int i = 1; i <= n; ++i) std::cin >> a[i];
  for (int i = 2, f; i <= n; ++i) {
    std::cin >> f;
    G[i].emplace_back(f);
    G[f].emplace_back(i);
  }
  dfs1(1, 0), dfs2(1, 1), T.build(1, 1, n);  // 预处理
  for (std::cin >> m; m; --m) {
    int op, u, v, w;
    std::cin >> op >> u;
    if (op == 1)
      root = u;  // 换根
    else if (op == 2)
      std::cin >> v >> w, modify_path(u, v, w);  // 修改路径
    else if (op == 3)
      std::cin >> w, modify_subtree(u, w);  // 修改子树
    else if (op == 4)
      std::cin >> v, std::cout << query_path(u, v) << "\n";  // 查询路径
    else
      std::cout << query_subtree(u) << "\n";  // 查询子树
  }
  std::cout.flush();
  return 0;
}
