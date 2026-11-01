// Sample source: https://www.luogu.com.cn/problem/P1494
#include <algorithm>
#include <cmath>
#include <iostream>
using namespace std;
constexpr int N = 50005;
int n, m, l = 1, r, BLOCK_SIZE, unit;
int values[N], counts[N];
long long nowAns, ans[N], denominator[N];

struct query {
  int l, r, id;

  bool operator<(const query& other) const {
    if (l / BLOCK_SIZE != other.l / BLOCK_SIZE) return l < other.l;
    return r < other.r;
  }
};

query queries[N];

// --8<-- [start:core]
void move(int pos, int sign) {
  if (sign == 1) {
    nowAns += counts[values[pos]]++;
  } else {
    nowAns -= --counts[values[pos]];
  }
}

void solve() {
  BLOCK_SIZE = int(ceil(pow(n, 0.5)));
  sort(queries, queries + m);
  for (int i = 0; i < m; ++i) {
    const query& q = queries[i];
    while (l > q.l) move(--l, 1);
    while (r < q.r) move(++r, 1);
    while (l < q.l) move(l++, -1);
    while (r > q.r) move(r--, -1);
    ans[q.id] = nowAns;
  }
}

// --8<-- [end:core]

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
