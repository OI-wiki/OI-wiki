#include <cstdio>
#include <vector>
using namespace std;
vector<int> graph[100010];
int n, m, son[100010], siz[100010], fa[100010], dep[100010], dfn[100010],
    rep[100010], top[100010], cnt, num[100010], tree[400010], lazy[400010];

void dfs1(int now, int father, int depth) {
  num[now] = 0;
  fa[now] = father;
  dep[now] = depth;
  siz[now] = 1;
  int tmp = 0;
  for (auto to : graph[now]) {
    if (to == father) continue;
    dfs1(to, now, depth + 1);
    siz[now] += siz[to];
    if (siz[to] > tmp) {
      siz[to] = tmp;
      son[now] = to;
    }
  }
}

void dfs2(int now, int root) {
  dfn[now] = ++cnt;
  rep[cnt] = now;
  top[now] = root;
  if (!son[now]) return;
  dfs2(son[now], root);
  for (auto to : graph[now]) {
    if (to == fa[now] || to == son[now]) continue;
    dfs2(to, to);
  }
}

void push_down(int now, int l, int r) {
  int mid = (l + r) >> 1;
  tree[now << 1] += lazy[now] * (mid - l + 1);
  lazy[now << 1] += lazy[now];
  tree[now << 1 | 1] += lazy[now] * (r - mid);
  lazy[now << 1 | 1] += lazy[now];
  lazy[now] = 0;
}

void change(int now, int l, int r, int x, int y, int k) {
  if (r < x || l > y) return;
  if (x <= l && r <= y) {
    tree[now] += (r - l + 1) * k;
    lazy[now] += k;
    return;
  }
  push_down(now, l, r);
  int mid = (l + r) >> 1;
  if (x <= mid) change(now << 1, l, mid, x, y, k);
  if (y > mid) change(now << 1 | 1, mid + 1, r, x, y, k);
  tree[now] = tree[now << 1] + tree[now << 1 | 1];
}

int find(int now, int l, int r, int x, int y) {
  if (r < x || l > y) return 0;
  if (x <= l && r <= y) return tree[now];
  push_down(now, l, r);
  int mid = (l + r) >> 1, sum = 0;
  if (x <= mid) sum += find(now << 1, l, mid, x, y);
  if (y > mid) sum += find(now << 1 | 1, mid + 1, r, x, y);
  return sum;
}

void opt_change(int x, int y) {
  while (top[x] != top[y]) {
    if (dfn[top[x]] < dfn[top[y]]) swap(x, y);
    change(1, 1, n, dfn[top[x]], dfn[x], 1);
    x = fa[top[x]];
  }
  if (dfn[x] > dfn[y]) swap(x, y);
  change(1, 1, n, dfn[x], dfn[y], 1);
  change(1, 1, n, dfn[x], dfn[x], -1);
}

int opt_find(int x, int y) {
  int sum = 0;
  while (top[x] != top[y]) {
    if (dfn[top[x]] < dfn[top[y]]) swap(x, y);
    sum += find(1, 1, n, dfn[top[x]], dfn[x]);
    x = fa[top[x]];
  }
  if (dfn[x] > dfn[y]) swap(x, y);
  sum += find(1, 1, n, dfn[x], dfn[y]);
  sum -= find(1, 1, n, dfn[x], dfn[x]);
  return sum;
}

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1; i < n; i++) {
    int from, to;
    scanf("%d%d", &from, &to);
    graph[from].push_back(to);
    graph[to].push_back(from);
  }
  dfs1(1, 1, 1);
  dfs2(1, 1);
  for (int i = 1; i <= m; i++) {
    char opt = getchar();
    while (opt != 'P' && opt != 'Q') opt = getchar();
    if (opt == 'P') {
      int x, y;
      scanf("%d%d", &x, &y);
      opt_change(x, y);
    } else {
      int x, y;
      scanf("%d%d", &x, &y);
      printf("%d\n", opt_find(x, y));
    }
  }
}
