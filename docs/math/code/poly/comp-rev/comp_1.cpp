#include <algorithm>
#include <cassert>
#include <cstdio>
#include <tuple>
#include <utility>
#include <vector>

using uint = unsigned;
using ull = unsigned long long;
constexpr uint MOD = 998244353;

constexpr uint PowMod(uint a, ull e) {
  for (uint res = 1;; a = (ull)a * a % MOD) {
    if (e & 1) res = (ull)res * a % MOD;
    if ((e /= 2) == 0) return res;
  }
}

constexpr uint InvMod(uint a) { return PowMod(a, MOD - 2); }

constexpr uint QUAD_NONRESIDUE = 3;
constexpr int LOG2_ORD = 23;  // __builtin_ctz(MOD - 1)
constexpr uint ZETA = PowMod(QUAD_NONRESIDUE, (MOD - 1) >> LOG2_ORD);
constexpr uint INV_ZETA = InvMod(ZETA);

std::vector<uint> GetFFTRoot(int n) {
  assert((n & (n - 1)) == 0);
  if (n / 2 == 0) return {};
  std::vector<uint> root(n / 2);
  root[0] = 1;
  for (int i = 0; (1 << i) < n / 2; ++i)
    root[1 << i] = PowMod(ZETA, 1LL << (LOG2_ORD - i - 2));
  for (int i = 1; i < n / 2; ++i)
    root[i] = (ull)root[i - (i & (i - 1))] * root[i & (i - 1)] % MOD;
  return root;
}

void Butterfly(uint a[], int n, const uint root[]) {
  assert((n & (n - 1)) == 0);
  for (int i = n; i >= 2; i /= 2)
    for (int j = 0; j < n; j += i)
      for (int k = j; k < j + i / 2; ++k) {
        const uint u = a[k];
        a[k + i / 2] = (ull)a[k + i / 2] * root[j / i] % MOD;
        if ((a[k] += a[k + i / 2]) >= MOD) a[k] -= MOD;
        if ((a[k + i / 2] = u + MOD - a[k + i / 2]) >= MOD) a[k + i / 2] -= MOD;
      }
}

void InvButterfly(uint a[], int n, const uint root[]) {
  assert((n & (n - 1)) == 0);
  for (int i = 2; i <= n; i *= 2)
    for (int j = 0; j < n; j += i)
      for (int k = j; k < j + i / 2; ++k) {
        const uint u = a[k];
        if ((a[k] += a[k + i / 2]) >= MOD) a[k] -= MOD;
        a[k + i / 2] = (ull)(u + MOD - a[k + i / 2]) * root[j / i] % MOD;
      }
}

void FFT(uint a[], int n, const uint root[]) { Butterfly(a, n, root); }

void InvFFT(uint a[], int n, const uint root[]) {
  InvButterfly(a, n, root);
  std::reverse(a + 1, a + n);
  const uint invn = InvMod(n);
  for (int i = 0; i < n; ++i) a[i] = (ull)a[i] * invn % MOD;
}

void TransposedFFT(uint a[], int n, const uint root[]) {
  InvButterfly(a, n, root);
}

void TransposedInvFFT(uint a[], int n, const uint root[]) {
  const uint invn = InvMod(n);
  for (int i = 0; i < n; ++i) a[i] = (ull)a[i] * invn % MOD;
  std::reverse(a + 1, a + n);
  Butterfly(a, n, root);
}

// 形式幂级数复合，求出 f(g) mod x^n 要求 g(0) = 0
std::vector<uint> FPSComp(std::vector<uint> f, std::vector<uint> g, int n) {
  assert(g.empty() || g[0] == 0);
  int N = 1;
  while (N < n) N *= 2;
  const std::vector<uint> root = GetFFTRoot(N * 4);
  // [y^(-1)] (f(y) / (-g(x) + y)) mod x^n in R[x]((y^(-1)))
  const auto KinoshitaLi = [&N, &root](auto&& KinoshitaLi, std::vector<uint>& P,
                                       std::vector<uint> Q, int d, int n) {
    assert((int)P.size() == N * 2);
    assert((int)Q.size() == N * 2);
    if (n == 1) return;
    Q.resize(N * 4);
    Q[N * 2] = 1;
    FFT(Q.data(), N * 4, root.data());
    if (n > 2) {
      std::vector<uint> V(N * 2);
      for (int i = 0; i < N * 4; i += 2) V[i / 2] = (ull)Q[i] * Q[i + 1] % MOD;
      InvFFT(V.data(), N * 2, root.data());
      assert(V[0] == 1);
      V[0] = 0;
      for (int i = 0; i < d * 2; ++i)
        fill_n(begin(V) + (i * n + n / 2), n / 2, 0u);
      KinoshitaLi(KinoshitaLi, P, std::move(V), d * 2, n / 2);
    }
    FFT(P.data(), N * 2, root.data());
    for (int i = 0; i < N * 4; i += 2)
      std::swap(Q[i] = (ull)Q[i] * P[i / 2] % MOD,
                Q[i + 1] = (ull)Q[i + 1] * P[i / 2] % MOD);
    InvFFT(Q.data(), N * 4, root.data());
    for (int i = 0; i < d; ++i)
      fill_n(copy_n(begin(Q) + (i + d) * n * 2, n, begin(P) + i * n * 2), n,
             0u);
  };
  f.resize(N * 2);
  g.resize(N * 2);
  for (int i = N - 1; i >= 0; --i) f[i * 2] = f[i], f[i * 2 + 1] = 0;
  for (int i = 0; i < N; ++i) g[i] = (g[i] != 0 ? MOD - g[i] : 0);
  fill_n(begin(g) + N, N, 0u);
  KinoshitaLi(KinoshitaLi, f, std::move(g), 1, N);
  f.resize(n);
  return f;
}

std::pair<std::vector<uint>, std::vector<uint>> GetFactorial(int n) {
  if (n == 0) return {};
  std::vector<uint> factorial(n), inv_factorial(n);
  factorial[0] = inv_factorial[0] = 1;
  if (n == 1) return {factorial, inv_factorial};
  std::vector<uint> inv(n);
  inv[1] = 1;
  for (int i = 2; i < n; ++i)
    inv[i] = (ull)(MOD - MOD / i) * inv[MOD % i] % MOD;
  for (int i = 1; i < n; ++i)
    factorial[i] = (ull)factorial[i - 1] * i % MOD,
    inv_factorial[i] = (ull)inv_factorial[i - 1] * inv[i] % MOD;
  return {factorial, inv_factorial};
}

// f(x) |-> f(x + c)
std::vector<uint> TaylorShift(std::vector<uint> f, uint c) {
  if (f.empty() || c == 0) return f;
  const int n = (int)f.size();
  std::vector<uint> factorial, inv_factorial;
  tie(factorial, inv_factorial) = GetFactorial(n);
  for (int i = 0; i < n; ++i) f[i] = (ull)f[i] * factorial[i] % MOD;
  std::vector<uint> g(n);
  uint cp = 1;
  for (int i = 0; i < n; ++i)
    g[i] = (ull)cp * inv_factorial[i] % MOD, cp = (ull)cp * c % MOD;
  int N = 1;
  while (N < n * 2 - 1) N *= 2;
  const std::vector<uint> root = GetFFTRoot(N);
  f.resize(N);
  g.resize(N);
  TransposedInvFFT(f.data(), N, root.data());
  FFT(g.data(), N, root.data());
  for (int i = 0; i < N; ++i) f[i] = (ull)f[i] * g[i] % MOD;
  TransposedFFT(f.data(), N, root.data());
  f.resize(n);
  for (int i = 0; i < n; ++i) f[i] = (ull)f[i] * inv_factorial[i] % MOD;
  return f;
}

// 多项式复合，求出 f(g) mod x^n
std::vector<uint> PolyComp(const std::vector<uint>& f,
                           const std::vector<uint>& g, int n) {
  if (g.empty() || g[0] == 0) return FPSComp(f, g, n);
  std::vector<uint> gg = g;
  gg[0] = 0;
  return FPSComp(TaylorShift(f, g[0]), std::move(gg), n);
}

int main() {
  int n, m;
  std::scanf("%d%d", &n, &m);
  std::vector<uint> f(n + 1), g(m + 1);
  for (int i = 0; i <= n; ++i) std::scanf("%u", &f[i]);
  for (int i = 0; i <= m; ++i) std::scanf("%u", &g[i]);
  const std::vector<uint> res = PolyComp(f, g, n + 1);
  for (int i = 0; i <= n; ++i) {
    if (i != 0) std::printf(" ");
    std::printf("%u", res[i]);
  }
  std::puts("");
  return 0;
}
