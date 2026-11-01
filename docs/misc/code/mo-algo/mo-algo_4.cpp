// Sample source: https://www.luogu.com.cn/problem/P1494
#include <algorithm>
#include <cmath>
#include <iostream>
using namespace std;
constexpr int N = 50005;
int n, m, l = 1, r, BLOCK_SIZE, unit;
int values[N], counts[N];
long long nowAns, ans[N], denominator[N];

// --8<-- [start:comparator]
struct node {
  int l, r, id;

  bool operator<(const node &x) const {
    if (l / unit != x.l / unit) return l < x.l;
    // 注意下面两行不能写小于（大于）等于，否则会出错（详见下面的小细节）
    if ((l / unit) & 1) return r < x.r;
    return r > x.r;
  }
};

// --8<-- [end:comparator]
node queries[N];

void move(int pos, int sign) {
  if (sign == 1) {
    nowAns += counts[values[pos]]++;
  } else {
    nowAns -= --counts[values[pos]];
  }
}

void solve() {
  BLOCK_SIZE = unit = int(ceil(pow(n, 0.5)));
  sort(queries, queries + m);
  for (int i = 0; i < m; ++i) {
    const node &q = queries[i];
    while (l > q.l) move(--l, 1);
    while (r < q.r) move(++r, 1);
    while (l < q.l) move(l++, -1);
    while (r > q.r) move(r--, -1);
    ans[q.id] = nowAns;
  }
}

long long gcd(long long a, long long b) { return b ? gcd(b, a % b) : a; }

int main() {
  if (!(cin >> n >> m)) return 0;
  for (int i = 1; i <= n; ++i) cin >> values[i];
  for (int i = 0; i < m; ++i) {
    cin >> queries[i].l >> queries[i].r;
    queries[i].id = i;
    long long len = queries[i].r - queries[i].l + 1;
    denominator[i] = len * (len - 1) / 2;
  }
  solve();
  for (int i = 0; i < m; ++i) {
    if (ans[i] == 0)
      cout << "0/1\n";
    else {
      long long divisor = gcd(ans[i], denominator[i]);
      cout << ans[i] / divisor << '/' << denominator[i] / divisor << '\n';
    }
  }
}
