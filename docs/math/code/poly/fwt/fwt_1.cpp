#include <iostream>
#include <vector>
using namespace std;
using ll = long long;
constexpr ll P = 998244353;
int n;

// --8<-- [start:or]
void Or(ll *a, ll type) {  // 迭代实现，常数更小
  for (ll x = 2; x <= n; x <<= 1) {
    ll k = x >> 1;
    for (ll i = 0; i < n; i += x) {
      for (ll j = 0; j < k; j++) {
        (a[i + j + k] += a[i + j] * type) %= P;
      }
    }
  }
}

// --8<-- [end:or]
// --8<-- [start:and]
void And(ll *a, ll type) {
  for (ll x = 2; x <= n; x <<= 1) {
    ll k = x >> 1;
    for (ll i = 0; i < n; i += x) {
      for (ll j = 0; j < k; j++) {
        (a[i + j] += a[i + j + k] * type) %= P;
      }
    }
  }
}

// --8<-- [end:and]
// --8<-- [start:xor]
void Xor(ll *a, ll type) {
  for (ll x = 2; x <= n; x <<= 1) {
    ll k = x >> 1;
    for (ll i = 0; i < n; i += x) {
      for (ll j = 0; j < k; j++) {
        (a[i + j] += a[i + j + k]) %= P;
        (a[i + j + k] = a[i + j] - a[i + j + k] * 2) %= P;
        (a[i + j] *= type) %= P;
        (a[i + j + k] *= type) %= P;
      }
    }
  }
}

// --8<-- [end:xor]
int main() {
  int bits;
  cin >> bits;
  n = 1 << bits;
  vector<ll> a(n), b(n);
  for (auto &x : a) cin >> x;
  for (auto &x : b) cin >> x;
  using Transform = void (*)(ll *, ll);
  Transform transforms[] = {Or, And, Xor};
  for (int k = 0; k < 3; ++k) {
    auto x = a, y = b;
    auto transform = transforms[k];
    transform(x.data(), 1);
    transform(y.data(), 1);
    for (int i = 0; i < n; ++i) x[i] = x[i] * y[i] % P;
    transform(x.data(), k == 2 ? (P + 1) / 2 : -1);
    for (int i = 0; i < n; ++i)
      cout << (x[i] + P) % P << (i + 1 == n ? '\n' : ' ');
  }
}
