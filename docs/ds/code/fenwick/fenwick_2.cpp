#include <algorithm>
#include <cmath>
#include <iostream>
#include <limits>
#include <vector>
using namespace std;
constexpr int MAXN = 1000005;
// --8<-- [start:example48]
long long t1[MAXN], t2[MAXN];
int n;

int lowbit(int x) { return x & (-x); }

void add(int k, int v) {
  long long v1 = 1LL * k * v;
  while (k <= n) {
    t1[k] += v, t2[k] += v1;
    // 注意不能写成 t2[k] += k * v，因为 k 的值已经不是原数组的下标了
    k += lowbit(k);
  }
}

long long getsum(long long *t, int k) {
  long long ret = 0;
  while (k) {
    ret += t[k];
    k -= lowbit(k);
  }
  return ret;
}

void add1(int l, int r, int v) {
  add(l, v), add(r + 1, -v);  // 将区间加差分为两个前缀加
}

long long getsum1(int l, int r) {
  return (r + 1ll) * getsum(t1, r) - 1ll * l * getsum(t1, l - 1) -
         (getsum(t2, r) - getsum(t2, l - 1));
}

// --8<-- [end:example48]

int main() {
  int q;
  cin >> n >> q;
  for (int j = 1, x; j <= n; ++j) {
    cin >> x;
    add1(j, j, x);
  }
  while (q--) {
    int op, l, r, v;
    cin >> op >> l >> r;
    if (op == 1) {
      cin >> v;
      add1(l, r, v);
    } else
      cout << getsum1(l, r) << '\n';
  }
}
