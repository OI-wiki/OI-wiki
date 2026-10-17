#include <algorithm>
#include <iostream>

int n, m;
int x[500010], y[500010], ans[500010];
int ax[1500010], ay[1500010], tx, ty;  // 离散化

struct query {
  int a, b, c, d;
} q[500010];  // 保存查询操作方便离散化

struct ope {
  int type, x, y, id;

  ope(int type = 0, int x = 0, int y = 0, int id = 0) {
    this->type = type, this->x = x, this->y = y, this->id = id;
  }

  bool operator<(const ope& rhs) const {
    if (x == rhs.x) return type < rhs.type;
    return x < rhs.x;
  }
};

ope op[2500010];
int tot;  // 操作总数

int sum[1500010];  // 树状数组

int lowbit(int x) { return x & (-x); }

void add(int x, int k) {
  while (x <= 1500000) {
    sum[x] = sum[x] + k;
    x = x + lowbit(x);
  }
}

int getsum(int x) {
  int ret = 0;
  while (x > 0) {
    ret = ret + sum[x];
    x = x - lowbit(x);
  }
  return ret;
}

using std::cin;
using std::cout;

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  cin >> n >> m, tx = n, ty = n;
  for (int i = 1; i <= n; i++) cin >> x[i] >> y[i], ax[i] = x[i], ay[i] = y[i];
  for (int i = 1, l, r; i <= m; i++) {
    cin >> q[i].a >> q[i].b >> q[i].c >> q[i].d;
    ax[++tx] = q[i].a, ay[++ty] = q[i].b, ax[++tx] = q[i].c, ay[++ty] = q[i].d;
  }
  std::sort(ax + 1, ax + tx + 1), std::sort(ay + 1, ay + ty + 1);
  tx = std::unique(ax + 1, ax + tx + 1) - ax - 1;
  ty = std::unique(ay + 1, ay + ty + 1) - ay - 1;
  for (int i = 1; i <= n; i++) {
    x[i] = std::lower_bound(ax + 1, ax + tx + 1, x[i]) - ax;
    y[i] = std::lower_bound(ay + 1, ay + ty + 1, y[i]) - ay;
    op[++tot] = ope(0, x[i], y[i], i);  // 加点操作
  }
  for (int i = 1; i <= m; i++) {
    q[i].a = std::lower_bound(ax + 1, ax + tx + 1, q[i].a) - ax;
    q[i].b = std::lower_bound(ay + 1, ay + ty + 1, q[i].b) - ay;
    q[i].c = std::lower_bound(ax + 1, ax + tx + 1, q[i].c) - ax;
    q[i].d = std::lower_bound(ay + 1, ay + ty + 1, q[i].d) - ay;
    op[++tot] = ope(1, q[i].c, q[i].d, i);  // 将查询差分
    op[++tot] = ope(1, q[i].a - 1, q[i].b - 1, i);
    op[++tot] = ope(2, q[i].a - 1, q[i].d, i);
    op[++tot] = ope(2, q[i].c, q[i].b - 1, i);
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
  for (int i = 1; i <= m; i++) cout << ans[i] << '\n';
  return 0;
}