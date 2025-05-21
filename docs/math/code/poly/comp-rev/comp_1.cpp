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

// 返回做 n 长 FFT 所需的单位根数组，长度为一半
std::pair<std::vector<uint>, std::vector<uint>> GetFFTRoot(int n) {
  assert((n & (n - 1)) == 0);
  if (n / 2 == 0) return {};
  std::vector<uint> root(n / 2), inv_root(n / 2);
  root[0] = inv_root[0] = 1;
  for (int i = 0; (1 << i) < n / 2; ++i)
    root[1 << i] = PowMod(ZETA, 1LL << (LOG2_ORD - i - 2)),
              inv_root[1 << i] = PowMod(INV_ZETA, 1LL << (LOG2_ORD - i - 2));
  for (int i = 1; i < n / 2; ++i)
    root[i] = (ull)root[i - (i & (i - 1))] * root[i & (i - 1)] % MOD,
    inv_root[i] =
        (ull)inv_root[i - (i & (i - 1))] * inv_root[i & (i - 1)] % MOD;
  return {root, inv_root};
}

void Butterfly(int n, uint a[], const uint root[]) {
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

void InvButterfly(int n, uint a[], const uint root[]) {
  assert((n & (n - 1)) == 0);
  for (int i = 2; i <= n; i *= 2)
    for (int j = 0; j < n; j += i)
      for (int k = j; k < j + i / 2; ++k) {
        const uint u = a[k];
        if ((a[k] += a[k + i / 2]) >= MOD) a[k] -= MOD;
        a[k + i / 2] = (ull)(u + MOD - a[k + i / 2]) * root[j / i] % MOD;
      }
}

void FFT(int n, uint a[], const uint root[]) { Butterfly(n, a, root); }

void InvFFT(int n, uint a[], const uint root[]) {
  InvButterfly(n, a, root);
  const uint inv_n = InvMod(n);
  for (int i = 0; i < n; ++i) a[i] = (ull)a[i] * inv_n % MOD;
}

// 形式幂级数复合，求出 f(g) mod x^n 要求 g(0) = 0
std::vector<uint> FPSComposition(std::vector<uint> f, std::vector<uint> g,
                                 int n) {
  assert(g.empty() || g[0] == 0);
  int len = 1;
  while (len < n) len *= 2;
  std::vector<uint> root, inv_root;
  std::tie(root, inv_root) = GetFFTRoot(len * 4);
  // [y^(-1)] (f(y) / (-g(x) + y)) mod x^n in R[x]((y^(-1)))
  auto KinoshitaLi = [&](auto &&KinoshitaLi, const std::vector<uint> &P,
                         const std::vector<uint> &Q, int d, int n) {
    assert((int)P.size() == d * n);
    assert((int)Q.size() == d * n);
    if (n == 1) return P;
    std::vector<uint> dftQ(d * n * 4);
    for (int i = 0; i < d; ++i)
      for (int j = 0; j < n; ++j) dftQ[i * n * 2 + j] = Q[i * n + j];
    dftQ[d * n * 2] = 1;
    FFT(d * n * 4, dftQ.data(), root.data());
    std::vector<uint> V(d * n * 2);
    for (int i = 0; i < d * n * 4; i += 2)
      V[i / 2] = (ull)dftQ[i] * dftQ[i + 1] % MOD;
    InvFFT(d * n * 2, V.data(), inv_root.data());
    if ((V[0] += MOD - 1) >= MOD) V[0] -= MOD;
    for (int i = 1; i < d * 2; ++i)
      for (int j = 0; j < n / 2; ++j) V[i * (n / 2) + j] = V[i * n + j];
    V.resize(d * n);
    const std::vector<uint> T = KinoshitaLi(KinoshitaLi, P, V, d * 2, n / 2);
    std::vector<uint> dftT(d * n * 2);
    for (int i = 0; i < d * 2; ++i)
      for (int j = 0; j < n / 2; ++j) dftT[i * n + j] = T[i * (n / 2) + j];
    FFT(d * n * 2, dftT.data(), root.data());
    for (int i = 0; i < d * n * 4; i += 2) {
      const uint u = dftQ[i];
      dftQ[i] = (ull)dftT[i / 2] * dftQ[i + 1] % MOD;
      dftQ[i + 1] = (ull)dftT[i / 2] * u % MOD;
    }
    InvFFT(d * n * 4, dftQ.data(), inv_root.data());
    for (int i = 0; i < d; ++i)
      for (int j = 0; j < n; ++j) dftQ[i * n + j] = dftQ[(i + d) * (n * 2) + j];
    dftQ.resize(d * n);
    return dftQ;
  };
  f.resize(len);
  g.resize(len);
  for (int i = 0; i < len; ++i) g[i] = (g[i] != 0 ? MOD - g[i] : 0);
  std::vector<uint> res = KinoshitaLi(KinoshitaLi, f, g, 1, len);
  res.resize(n);
  return res;
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
  const int n = f.size();
  std::vector<uint> factorial, inv_factorial;
  std::tie(factorial, inv_factorial) = GetFactorial(n);
  for (int i = 0; i < n; ++i) f[i] = (ull)f[i] * factorial[i] % MOD;
  std::vector<uint> g(n);
  uint cp = 1;
  for (int i = 0; i < n; ++i)
    g[i] = (ull)cp * inv_factorial[i] % MOD, cp = (ull)cp * c % MOD;
  int len = 1;
  while (len < n * 2 - 1) len *= 2;
  std::vector<uint> root, inv_root;
  std::tie(root, inv_root) = GetFFTRoot(len);
  f.resize(len);
  g.resize(len);
  FFT(len, f.data(), inv_root.data());
  FFT(len, g.data(), root.data());
  for (int i = 0; i < len; ++i) f[i] = (ull)f[i] * g[i] % MOD;
  InvFFT(len, f.data(), root.data());
  f.resize(n);
  for (int i = 0; i < n; ++i) f[i] = (ull)f[i] * inv_factorial[i] % MOD;
  return f;
}

// 多项式复合，求出 f(g) mod x^n
std::vector<uint> PolyComposition(const std::vector<uint> &f,
                                  const std::vector<uint> &g, int n) {
  if (g.empty() || g[0] == 0) return FPSComposition(f, g, n);
  std::vector<uint> gg = g;
  gg[0] = 0;
  return FPSComposition(TaylorShift(f, g[0]), gg, n);
}

int main() {
  int n, m;
  std::scanf("%d%d", &n, &m);
  std::vector<uint> f(n + 1), g(m + 1);
  for (int i = 0; i <= n; ++i) std::scanf("%u", &f[i]);
  for (int i = 0; i <= m; ++i) std::scanf("%u", &g[i]);
  const std::vector<uint> res = PolyComposition(f, g, n + 1);
  for (int i = 0; i <= n; ++i) std::printf("%u%c", res[i], " \n"[i == n]);
  return 0;
}
