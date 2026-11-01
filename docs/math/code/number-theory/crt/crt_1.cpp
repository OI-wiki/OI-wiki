#include <iostream>
#include <vector>
using namespace std;
using LL = long long;

LL exgcd(LL a, LL b, LL& x, LL& y) {
  if (!b) {
    x = 1;
    y = 0;
    return a;
  }
  LL d = exgcd(b, a % b, y, x);
  y -= a / b * x;
  return d;
}

LL mul(LL a, LL b, LL mod) {
  LL ans = 0;
  for (; b; b >>= 1, a = (a + a) % mod)
    if (b & 1) ans = (ans + a) % mod;
  return ans;
}

// --8<-- [start:core]
LL CRT(int k, LL* a, LL* r) {
  LL n = 1, ans = 0;
  for (int i = 1; i <= k; i++) n = n * r[i];
  for (int i = 1; i <= k; i++) {
    LL m = n / r[i], b, y;
    exgcd(m, r[i], b, y);  // b * m mod r[i] = 1
    ans = (ans + mul(mul(a[i], m, n), (b % n + n) % n, n)) % n;
  }
  return (ans % n + n) % n;
}

// --8<-- [end:core]
int main() {
  int k;
  cin >> k;
  vector<LL> a(k + 1), r(k + 1);
  for (int i = 1; i <= k; ++i) cin >> r[i] >> a[i];
  cout << CRT(k, a.data(), r.data()) << "\n";
}
