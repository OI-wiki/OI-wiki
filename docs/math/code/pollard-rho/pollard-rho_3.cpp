#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;
using LL = long long;

ll gcd(ll a, ll b) {
  while (b) {
    ll r = a % b;
    a = b;
    b = r;
  }
  return a;
}

LL mul(LL a, LL b, LL mod) {
  LL ans = 0;
  for (; b; b >>= 1, a = (a + a) % mod)
    if (b & 1) ans = (ans + a) % mod;
  return ans;
}

ll qpow(ll a, ll b, ll mod) {
  ll r = 1;
  for (; b; b >>= 1, a = mul(a, a, mod))
    if (b & 1) r = mul(r, a, mod);
  return r;
}

bool prime(ll n) {
  if (n < 2) return false;
  ll d = n - 1;
  int s = 0;
  while (!(d & 1)) {
    d >>= 1;
    ++s;
  }
  for (ll a : {2, 325, 9375, 28178, 450775, 9780504, 1795265022}) {
    if (a % n == 0) continue;
    ll x = qpow(a % n, d, n);
    if (x == 1 || x == n - 1) continue;
    bool ok = false;
    for (int j = 1; j < s; ++j) {
      x = mul(x, x, n);
      if (x == n - 1) {
        ok = true;
        break;
      }
    }
    if (!ok) return false;
  }
  return true;
}

ll f(ll a, ll c, ll mod) { return (mul(a, a, mod) + c) % mod; }

// --8<-- [start:core]
ll Pollard_Rho(ll x) {
  ll t = 0;
  ll c = rand() % (x - 1) + 1;
  ll s = t;
  ll step = 0, goal = 1;
  ll val = 1;
  for (goal = 1;; goal <<= 1, s = t, val = 1) {
    for (step = 1; step <= goal; ++step) {
      t = f(t, c, x);
      val = mul(val, abs(t - s), x);
      // 如果 val 为 0，退出重新分解
      if (!val) return x;
      if (step % 127 == 0) {
        ll d = gcd(val, x);
        if (d > 1) return d;
      }
    }
    ll d = gcd(val, x);
    if (d > 1) return d;
  }
}

// --8<-- [end:core]
ll largest(ll n) {
  if (n == 1) return 1;
  if (prime(n)) return n;
  ll d = n;
  while (d == n) d = Pollard_Rho(n);
  return max(largest(d), largest(n / d));
}

int main() {
  srand(1);
  int t;
  cin >> t;
  while (t--) {
    ll n;
    cin >> n;
    ll a = largest(n);
    if (a == n)
      cout << "Prime\n";
    else
      cout << a << "\n";
  }
}
