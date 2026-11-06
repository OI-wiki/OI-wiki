#include <algorithm>
#include <cassert>
#include <iostream>
// --8<-- [start:declarations]
constexpr int MAXN = 262144;
constexpr int mod = 998244353;
using i64 = long long;
using poly_t = int[MAXN];
using poly = int *const;
// --8<-- [end:declarations]
int inv[MAXN];

int pls(int a, int b) { return (a + b) % mod; }

int sub(int a, int b) { return (a - b + mod) % mod; }

int sqr(int a) { return i64(a) * a % mod; }

void inc(int &a, int b) { a = pls(a, b); }

int div2(int a) { return (a + (a & 1 ? mod : 0)) / 2; }

int fpow(int a, int b) {
  int r = 1;
  for (; b; b >>= 1, a = sqr(a))
    if (b & 1) r = i64(r) * a % mod;
  return r;
}

void DFT(int *a, int n) {
  for (int i = 1, j = 0; i < n; ++i) {
    int bit = n >> 1;
    for (; j & bit; bit >>= 1) j ^= bit;
    j ^= bit;
    if (i < j) std::swap(a[i], a[j]);
  }
  for (int len = 2; len <= n; len <<= 1) {
    int wn = fpow(3, (mod - 1) / len);
    for (int i = 0; i < n; i += len) {
      int w = 1;
      for (int j = 0; j < len / 2; ++j) {
        int u = a[i + j], v = i64(a[i + j + len / 2]) * w % mod;
        a[i + j] = pls(u, v);
        a[i + j + len / 2] = sub(u, v);
        w = i64(w) * wn % mod;
      }
    }
  }
}

void IDFT(int *a, int n) {
  DFT(a, n);
  std::reverse(a + 1, a + n);
  int scale = fpow(n, mod - 2);
  for (int i = 0; i < n; ++i) a[i] = i64(a[i]) * scale % mod;
}

// --8<-- [start:core]
void polyinv(const poly &h, const int n, poly &f) {
  /* f = 1 / h = f_0 (2 - f_0 h) */
  static poly_t inv_t;
  std::fill(f, f + n + n, 0);
  f[0] = fpow(h[0], mod - 2);
  for (int t = 2; t <= n; t <<= 1) {
    const int t2 = t << 1;
    std::copy(h, h + t, inv_t);
    std::fill(inv_t + t, inv_t + t2, 0);

    DFT(f, t2);
    DFT(inv_t, t2);
    for (int i = 0; i != t2; ++i)
      f[i] = (i64)f[i] * sub(2, (i64)f[i] * inv_t[i] % mod) % mod;
    IDFT(f, t2);

    std::fill(f + t, f + t2, 0);
  }
}

// --8<-- [end:core]
int main() {
  int count;
  std::cin >> count;
  int n = 1;
  while (n < count) n <<= 1;
  assert(2 * n <= MAXN);
  static poly_t a, b;
  for (int i = 0; i < count; ++i) {
    std::cin >> a[i];
    a[i] %= mod;
  }
  inv[1] = 1;
  for (int i = 2; i < 2 * n; ++i)
    inv[i] = i64(mod - mod / i) * inv[mod % i] % mod;
  polyinv(a, n, b);
  for (int i = 0; i < count; ++i)
    std::cout << b[i] << (i + 1 == count ? '\n' : ' ');
}
