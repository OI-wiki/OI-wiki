#include <algorithm>
#include <cassert>
#include <iostream>
// --8<-- [start:declarations]
constexpr int MAXN = 262144;
constexpr int mod = 998244353;
constexpr int imgunit = 86583718; /* sqrt(-1) = sqrt(998233452) */
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

void derivative(const poly &h, const int n, poly &f) {
  for (int i = 1; i != n; ++i) f[i - 1] = (i64)h[i] * i % mod;
  f[n - 1] = 0;
}

void integrate(const poly &h, const int n, poly &f) {
  for (int i = n - 1; i; --i) f[i] = (i64)h[i - 1] * inv[i] % mod;
  f[0] = 0; /* C */
}

void polyln(const poly &h, const int n, poly &f) {
  /* f = ln h = ∫ h' / h dx */
  assert(h[0] == 1);
  static poly_t ln_t;
  const int t = n << 1;

  derivative(h, n, ln_t);
  std::fill(ln_t + n, ln_t + t, 0);
  polyinv(h, n, f);

  DFT(ln_t, t);
  DFT(f, t);
  for (int i = 0; i != t; ++i) ln_t[i] = (i64)ln_t[i] * f[i] % mod;
  IDFT(ln_t, t);

  integrate(ln_t, n, f);
}

void polyexp(const poly &h, const int n, poly &f) {
  /* f = exp(h) = f_0 (1 - ln f_0 + h) */
  assert(h[0] == 0);
  static poly_t exp_t;
  std::fill(f, f + n + n, 0);
  f[0] = 1;
  for (int t = 2; t <= n; t <<= 1) {
    const int t2 = t << 1;

    polyln(f, t, exp_t);
    exp_t[0] = sub(pls(h[0], 1), exp_t[0]);
    for (int i = 1; i != t; ++i) exp_t[i] = sub(h[i], exp_t[i]);
    std::fill(exp_t + t, exp_t + t2, 0);

    DFT(f, t2);
    DFT(exp_t, t2);
    for (int i = 0; i != t2; ++i) f[i] = (i64)f[i] * exp_t[i] % mod;
    IDFT(f, t2);

    std::fill(f + t, f + t2, 0);
  }
}

// --8<-- [start:core]
void polytri(const poly &h, const int n, poly &sin_t, poly &cos_t) {
  /* sin(f) = (exp(i * f) - exp(- i * f)) / 2i */
  /* cos(f) = (exp(i * f) + exp(- i * f)) / 2 */
  /* tan(f) = sin(f) / cos(f) */
  assert(h[0] == 0);
  static poly_t tri1_t, tri2_t;

  for (int i = 0; i != n; ++i) tri2_t[i] = (i64)h[i] * imgunit % mod;
  polyexp(tri2_t, n, tri1_t);
  polyinv(tri1_t, n, tri2_t);

  if (sin_t != nullptr) {
    const int invi = fpow(pls(imgunit, imgunit), mod - 2);
    for (int i = 0; i != n; ++i)
      sin_t[i] = (i64)(tri1_t[i] - tri2_t[i] + mod) * invi % mod;
  }
  if (cos_t != nullptr) {
    for (int i = 0; i != n; ++i) cos_t[i] = div2(pls(tri1_t[i], tri2_t[i]));
  }
}

// --8<-- [end:core]
int main() {
  int count;
  std::cin >> count;
  int n = 1;
  while (n < count) n <<= 1;
  assert(2 * n <= MAXN);
  static poly_t a, b, c;
  for (int i = 0; i < count; ++i) {
    std::cin >> a[i];
    a[i] %= mod;
  }
  inv[1] = 1;
  for (int i = 2; i < 2 * n; ++i)
    inv[i] = i64(mod - mod / i) * inv[mod % i] % mod;
  polytri(a, n, b, c);
  for (int i = 0; i < count; ++i)
    std::cout << b[i] << (i + 1 == count ? '\n' : ' ');
  std::copy(c, c + count, b);
  for (int i = 0; i < count; ++i)
    std::cout << b[i] << (i + 1 == count ? '\n' : ' ');
}
