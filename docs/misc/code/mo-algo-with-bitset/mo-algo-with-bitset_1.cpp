#include <algorithm>
#include <bitset>
#include <cmath>
#include <cstring>
#include <iostream>
using namespace std;
constexpr int N = 100005, M = N / 3 + 10;
int n, m, maxn;
int a[N], ans[M], cnt[N];
bitset<N> sum[M], now;

struct query {
  int l, r, id;

  bool operator<(const query& x) const {
    if (l / maxn != x.l / maxn) return l < x.l;
    return (l / maxn) & 1 ? r < x.r : r > x.r;
  }
} q[M * 3];

void static_set() {
  static int tmp[N];
  memcpy(tmp, a, sizeof(a));
  sort(tmp + 1, tmp + n + 1);
  for (int i = 1; i <= n; i++)
    a[i] = lower_bound(tmp + 1, tmp + n + 1, a[i]) - tmp;
}

void add(int x) {
  now.set(x + cnt[x]);
  cnt[x]++;
}

void del(int x) {
  cnt[x]--;
  now.reset(x + cnt[x]);
}

void solve() {
  int cnt = 0, tot = 0;
  now.reset();
  for (tot = 0; tot < M - 5 && m; tot++) {
    m--;
    ans[tot] = 0;
    sum[tot].set();
    for (int j = 0; j < 3; j++) {
      cin >> q[cnt].l >> q[cnt].r;
      q[cnt].id = tot;
      ans[tot] += q[cnt].r - q[cnt].l + 1;
      cnt++;
    }
  }
  sort(q, q + cnt);
  for (int i = 0, l = 1, r = 0; i < cnt; i++) {
    while (l > q[i].l) add(a[--l]);
    while (r < q[i].r) add(a[++r]);
    while (l < q[i].l) del(a[l++]);
    while (r > q[i].r) del(a[r--]);
    sum[q[i].id] &= now;
  }
  for (int i = 0; i < tot; i++)
    cout << ans[i] - (int)sum[i].count() * 3 << '\n';
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  cin >> n >> m;
  for (int i = 1; i <= n; i++) cin >> a[i];
  static_set();
  maxn = sqrt(n);
  solve();
  memset(cnt, 0, sizeof(cnt));
  solve();
  memset(cnt, 0, sizeof(cnt));
  solve();
  return 0;
}