#include <iostream>
#include <string>
#define MOD1 39989
#define MOD2 1000000000
#define MAXT 40000
using namespace std;
typedef pair<double, int> pdi;
struct line {
  double k, b;
} p[100005];
int s[160005];
int cnt;
double calc(int id, int d) { return p[id].b + p[id].k * d; }
void add(int x0, int y0, int x1, int y1) {
  cnt++;
  if (x0 == x1)  // 特判直线斜率不存在的情况
    p[cnt].k = 0, p[cnt].b = max(y0, y1);
  else
    p[cnt].k = 1.0 * (y1 - y0) / (x1 - x0), p[cnt].b = y0 - p[cnt].k * x0;
}
void update(int root, int cl, int cr, int l, int r, int u) {  //更新值
  int v = s[root], mid = (cl + cr) >> 1;
  int ls = root << 1, rs = root << 1 | 1;
  double resu = calc(u, mid), resv = calc(v, mid);
  if (r < cl || cr < l) return;  //区间问题
  if (l <= cl && cr <= r) {
    if (cl == cr) {
      if (resu > resv) s[root] = u;
      return;
    }  //从此之下都是分段更新
    if (p[v].k < p[u].k) {
      if (resu > resv) {
        s[root] = u;
        update(ls, cl, mid, l, r, v);
      } else
        update(rs, mid + 1, cr, l, r, u);
    } else if (p[v].k > p[u].k) {
      if (resu > resv) {
        s[root] = u;
        update(rs, mid + 1, cr, l, r, v);
      } else
        update(ls, cl, mid, l, r, u);
    } else {
      if (p[u].b > p[v].b) s[root] = u;
    }
    return;
  }
  update(ls, cl, mid, l, r, u);
  update(rs, mid + 1, cr, l, r, u);
}
pdi pmax(pdi x, pdi y) {  // pair max函数
  if (x.first < y.first)
    return y;
  else if (x.first > y.first)
    return x;
  else
    return x.second < y.second ? x : y;
}
pdi query(int root, int l, int r, int d) {  //查询
  if (r < d || d < l) return {0, 0};
  int mid = (l + r) >> 1;
  double res = calc(s[root], d);
  if (l == r) return {res, s[root]};
  return pmax({res, s[root]}, pmax(query(root << 1, l, mid, d),
                                   query(root << 1 | 1, mid + 1, r, d)));
}
int main() {
  ios::sync_with_stdio(false);
  int n, lastans = 0;
  cin >> n;
  while (n--) {
    int op;
    cin >> op;
    if (op == 1) {
      int x0, y0, x1, y1;
      cin >> x0 >> y0 >> x1 >> y1;
      x0 = (x0 + lastans - 1 + MOD1) % MOD1 + 1,
      x1 = (x1 + lastans - 1 + MOD1) % MOD1 + 1;
      y0 = (y0 + lastans - 1 + MOD2) % MOD2 + 1,
      y1 = (y1 + lastans - 1 + MOD2) % MOD2 + 1;
      if (x0 > x1) swap(x0, x1), swap(y0, y1);
      add(x0, y0, x1, y1);
      update(1, 1, MOD1, x0, x1, cnt);
    } else {
      int x;
      cin >> x;
      x = (x + lastans - 1 + MOD1) % MOD1 + 1;
      cout << (lastans = query(1, 1, MOD1, x).second) << endl;
    }
  }
  return 0;
}