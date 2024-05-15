#include <bits/stdc++.h>

int n, m, a[1000010], ans[1000010];
int pre[1000010], lst[1000010];  // 处理 pre

struct ope {
  int type, x, y, id;

  inline ope(int type = 0, int x = 0, int y = 0, int id = 0) {
    this->type = type, this->x = x, this->y = y, this->id = id;
  }

  inline bool operator<(const ope& rhs) const {
    if (x == rhs.x) return type < rhs.type;
    return x < rhs.x;
  }
};

ope op[2500010];
int tot;  // 操作总数

int sum[1000010];  // 树状数组

int lowbit(int x) { return x & (-x); }

void add(int x, int k) {
  x++;  // 位置 0 也要进行修改，所以树状数组下标均加 1
  while (x <= n) {
    sum[x] = sum[x] + k;
    x = x + lowbit(x);
  }
}

int getsum(int x) {
  x++;
  int ret = 0;
  while (x > 0) {
    ret = ret + sum[x];
    x = x - lowbit(x);
  }
  return ret;
}

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%d", &a[i]);
    pre[i] = lst[a[i]], lst[a[i]] = i;   // 处理 pre
    op[++tot] = (ope){0, i, pre[i], i};  // 加点操作
  }
  scanf("%d", &m);
  for (int i = 1, l, r; i <= m; i++) {
    scanf("%d%d", &l, &r);
    op[++tot] = (ope){1, r, l - 1, i};  // 将查询差分
    op[++tot] = (ope){2, l - 1, l - 1, i};
  }
  std::sort(op + 1, op + tot + 1);  // 将操作按横坐标排序，且优先执行加点操作
  for (int i = 1; i <= tot; i++) {
    if (op[i].type == 0)
      add(op[i].y, 1);
    else if (op[i].type == 1)
      ans[op[i].id] += getsum(op[i].y);
    else
      ans[op[i].id] -= getsum(op[i].y);
  }
  for (int i = 1; i <= m; i++) printf("%d\n", ans[i]);
  return 0;
}