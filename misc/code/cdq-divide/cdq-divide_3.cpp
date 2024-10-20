// 一道二维最长上升子序列的题
// 为了确定某一个元素是否在最长上升子序列中可以正反跑两遍 CDQ
#include <algorithm>
#include <iomanip>
#include <iostream>
using namespace std;
using db = double;
constexpr int N = 1e6 + 10;

struct data_ {
  int h;
  int v;
  int p;
  int ma;
  db ca;
} a[2][N];

int n;
bool tr;

// 底下是重写比较
bool cmp1(const data_& a, const data_& b) {
  if (tr)
    return a.h > b.h;
  else
    return a.h < b.h;
}

bool cmp2(const data_& a, const data_& b) {
  if (tr)
    return a.v > b.v;
  else
    return a.v < b.v;
}

bool cmp3(const data_& a, const data_& b) {
  if (tr)
    return a.p < b.p;
  else
    return a.p > b.p;
}

bool cmp4(const data_& a, const data_& b) { return a.v == b.v; }

struct treearray {
  int ma[2 * N];
  db ca[2 * N];

  void c(int x, int t, db c) {
    for (; x <= n; x += x & (-x)) {
      if (ma[x] == t) {
        ca[x] += c;
      } else if (ma[x] < t) {
        ca[x] = c;
        ma[x] = t;
      }
    }
  }

  void d(int x) {
    for (; x <= n; x += x & (-x)) {
      ma[x] = 0;
      ca[x] = 0;
    }
  }

  void q(int x, int& m, db& c) {
    for (; x > 0; x -= x & (-x)) {
      if (ma[x] == m) {
        c += ca[x];
      } else if (m < ma[x]) {
        c = ca[x];
        m = ma[x];
      }
    }
  }
} ta;

int rk[2][N];

void solve(int l, int r, int t) {  // 递归跑
  if (r - l == 1) {
    return;
  }
  int mid = (l + r) / 2;
  solve(l, mid, t);
  sort(a[t] + mid + 1, a[t] + r + 1, cmp1);
  int p = l + 1;
  for (int i = mid + 1; i <= r; i++) {
    for (; (cmp1(a[t][p], a[t][i]) || a[t][p].h == a[t][i].h) && p <= mid;
         p++) {
      ta.c(a[t][p].v, a[t][p].ma, a[t][p].ca);
    }
    db c = 0;
    int m = 0;
    ta.q(a[t][i].v, m, c);
    if (a[t][i].ma < m + 1) {
      a[t][i].ma = m + 1;
      a[t][i].ca = c;
    } else if (a[t][i].ma == m + 1) {
      a[t][i].ca += c;
    }
  }
  for (int i = l + 1; i <= mid; i++) {
    ta.d(a[t][i].v);
  }
  sort(a[t] + mid, a[t] + r + 1, cmp3);
  solve(mid, r, t);
  sort(a[t] + l + 1, a[t] + r + 1, cmp1);
}

void ih(int t) {
  sort(a[t] + 1, a[t] + n + 1, cmp2);
  rk[t][1] = 1;
  for (int i = 2; i <= n; i++) {
    rk[t][i] = (cmp4(a[t][i], a[t][i - 1])) ? rk[t][i - 1] : i;
  }
  for (int i = 1; i <= n; i++) {
    a[t][i].v = rk[t][i];
  }
  sort(a[t] + 1, a[t] + n + 1, cmp3);
  for (int i = 1; i <= n; i++) {
    a[t][i].ma = 1;
    a[t][i].ca = 1;
  }
}

int len;
db ans;

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[0][i].h >> a[0][i].v;
    a[0][i].p = i;
    a[1][i].h = a[0][i].h;
    a[1][i].v = a[0][i].v;
    a[1][i].p = i;
  }
  ih(0);
  solve(0, n, 0);
  tr = true;
  ih(1);
  solve(0, n, 1);
  tr = true;
  sort(a[0] + 1, a[0] + n + 1, cmp3);
  sort(a[1] + 1, a[1] + n + 1, cmp3);
  for (int i = 1; i <= n; i++) {
    len = max(len, a[0][i].ma);
  }
  cout << len << '\n';
  for (int i = 1; i <= n; i++) {
    if (a[0][i].ma == len) {
      ans += a[0][i].ca;
    }
  }
  cout << fixed << setprecision(5);
  for (int i = 1; i <= n; i++) {
    if (a[0][i].ma + a[1][i].ma - 1 == len) {
      cout << (a[0][i].ca * a[1][i].ca) / ans << ' ';
    } else {
      cout << "0.00000 ";
    }
  }
  return 0;
}
