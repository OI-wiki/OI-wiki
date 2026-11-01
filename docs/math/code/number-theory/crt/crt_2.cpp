#include <iostream>
#include <vector>
using namespace std;
using LL = long long;

LL exgcd(LL a, LL b, LL &x, LL &y) {
  if (!b) {
    x = 1;
    y = 0;
    return a;
  }
  LL d = exgcd(b, a % b, y, x);
  y -= a / b * x;
  return d;
}

int main() {
  int k;
  cin >> k;
  vector<LL> a(k), p(k), x(k);
  vector<vector<LL>> r(k, vector<LL>(k));
  for (int i = 0; i < k; ++i) cin >> p[i] >> a[i];
  for (int i = 0; i < k; ++i)
    for (int j = i + 1; j < k; ++j) {
      LL y;
      exgcd(p[i], p[j], r[i][j], y);
      r[i][j] = (r[i][j] % p[j] + p[j]) % p[j];
    }
  // --8<-- [start:core]
  for (int i = 0; i < k; ++i) {
    x[i] = a[i];
    for (int j = 0; j < i; ++j) {
      x[i] = r[j][i] * (x[i] - x[j]);
      x[i] = x[i] % p[i];
      if (x[i] < 0) x[i] += p[i];
    }
  }
  // --8<-- [end:core]
  LL ans = 0, product = 1;
  for (int i = 0; i < k; ++i) {
    ans += product * x[i];
    product *= p[i];
  }
  cout << ans << "\n";
}
