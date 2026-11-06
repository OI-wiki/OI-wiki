#include <algorithm>
#include <iostream>
#include <utility>
using namespace std;
constexpr int N = 100005;
int s[N], ls[N], rs[N];

struct Line {
  double k, b;
} p[N];

double calc(int id, int x) { return id ? p[id].k * x + p[id].b : -1e100; }

constexpr double eps = 1e-9;

int cmp(double x, double y) {  // 因为用到了浮点数，所以会有精度误差
  if (x - y > eps) return 1;
  if (y - x > eps) return -1;
  return 0;
}

// --8<-- [start:example102]
void upd(int &root, int cl, int cr,
         int u) {  // 涉及多棵李超线段树合并，使用动态开点．
  static int idx = 0;
  if (!root) {
    s[root = ++idx] = u;
    return;
  }
  int &v = s[root], mid = (cl + cr) >> 1;
  int bmid = cmp(calc(u, mid), calc(v, mid));
  if (bmid == 1 || (!bmid && u < v)) swap(u, v);
  int bl = cmp(calc(u, cl), calc(v, cl)), br = cmp(calc(u, cr), calc(v, cr));
  if (bl == 1 || (!bl && u < v)) upd(ls[root], cl, mid, u);
  if (br == 1 || (!br && u < v)) upd(rs[root], mid + 1, cr, u);
}

int merge(int &u, int &v, int l, int r) {
  if (!u || !v) {
    return u + v;
  }
  if (l == r) {
    int b = cmp(calc(s[v], l), calc(s[u], l));
    if (b == 1 || (!b && s[v] < s[u])) return v;
    return u;
  }
  upd(u, l, r, s[v]);
  int mid = (l + r) >> 1;
  ls[u] = merge(ls[u], ls[v], l, mid);
  rs[u] = merge(rs[u], rs[v], mid + 1, r);
  return u;
}

// --8<-- [end:example102]
pair<double, int> query(int root, int l, int r, int x) {
  if (!root) return {-1e100, 0};
  pair<double, int> a{calc(s[root], x), -s[root]};
  if (l == r) return a;
  int mid = (l + r) / 2;
  return max(a, x <= mid ? query(ls[root], l, mid, x)
                         : query(rs[root], mid + 1, r, x));
}

int main() {
  int n, m, a = 0, b = 0;
  cin >> n >> m;
  for (int i = 1; i <= n; ++i) {
    int tree;
    cin >> tree >> p[i].k >> p[i].b;
    upd(tree == 1 ? a : b, 1, m, i);
  }
  a = merge(a, b, 1, m);
  for (int x = 1; x <= m; ++x)
    cout << -query(a, 1, m, x).second << (x == m ? "\n" : " ");
}
