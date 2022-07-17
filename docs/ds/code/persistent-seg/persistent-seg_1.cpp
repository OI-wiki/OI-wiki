#include <algorithm>
#include <cstdio>
const int N = 1e5, M = 2e5;  // 数据范围

struct node {
  int val, rank, lchild, rchild;
} tree[4 * N + M * 19];  // 每次操作增加节点数最多为 log2(4 * N) = 19

int init[N + 1], root[M + 1], tot;

int build(int l, int r) {  // 建树
  int now = ++tot;
  if (l == r) {
    tree[now].val = init[l];
    tree[now].rank = 1;
    return now;
  }
  int mid = l + r >> 1;
  tree[now].lchild = build(l, mid);
  tree[now].rchild = build(mid + 1, r);
  return now;
}

int update(int x, int l, int r, int target,
           int newroot) {  // 合并操作-更新父亲节点信息
  int now = ++tot;
  tree[now] = tree[x];
  if (l == r) {
    tree[now].val = newroot;
    tree[newroot].rank = std::max(tree[newroot].rank, tree[now].rank + 1);
    return now;
  }
  int mid = l + r >> 1;
  if (target <= mid)
    tree[now].lchild = update(tree[x].lchild, l, mid, target, newroot);
  else
    tree[now].rchild = update(tree[x].rchild, mid + 1, r, target, newroot);
  return now;
}

int query(int x, int l, int r, int target) {  // 查询父亲节点
  if (l == r) return tree[x].val;
  int mid = l + r >> 1;
  if (target <= mid)
    return query(tree[x].lchild, l, mid, target);
  else
    return query(tree[x].rchild, mid + 1, r, target);
}

int getroot(int x, int l, int r, int target) {  // 查询根节点
  int ans = query(x, l, r, target);
  if (ans == target)
    return ans;
  else
    return getroot(x, l, r, ans);
}

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; i++) init[i] = i;
  root[0] = build(1, n);
  int op, a, b, k;
  for (int i = 1; i <= m; i++) {
    scanf("%d", &op);
    if (op == 1) {
      scanf("%d%d", &a, &b);
      int root_a = getroot(root[i - 1], 1, n, a);
      int root_b = getroot(root[i - 1], 1, n, b);
      if (tree[root_a].rank < tree[root_b].rank)  // 按秩合并
        root[i] = update(root[i - 1], 1, n, root_a, root_b);
      else
        root[i] = update(root[i - 1], 1, n, root_b, root_a);
    } else if (op == 2) {
      scanf("%d", &k);
      root[i] = root[k];
    } else {
      scanf("%d%d", &a, &b);
      root[i] = root[i - 1];
      printf("%d\n", getroot(root[i], 1, n, a) == getroot(root[i], 1, n, b));
    }
  }
}
