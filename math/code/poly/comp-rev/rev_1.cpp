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

// Power Projection: [x^(n-1)] (fg^i) for i=0,..,n-1 要求 g(0) = 0
std::vector<uint> PowerProjection(std::vector<uint> f, std::vector<uint> g,
                                  int n) {
  assert(g.empty() || g[0] == 0);
  int len = 1;
  while (len < n) len *= 2;
  std::vector<uint> root, inv_root;
  std::tie(root, inv_root) = GetFFTRoot(len * 4);
  // [x^(n-1)] (f(x) / (-g(x) + y)) in R[x]((y^(-1)))
  auto KinoshitaLi = [&](auto &&KinoshitaLi, std::vector<uint> P,
                         std::vector<uint> Q, int d,
                         int n) -> std::vector<uint> {
    assert((int)P.size() == d * n);
    assert((int)Q.size() == d * n);
    if (n == 1) return P;
    std::vector<uint> dftQ(d * n * 4), dftP(d * n * 4);
    for (int i = 0; i < d; ++i)
      for (int j = 0; j < n; ++j)
        dftP[i * n * 2 + j] = P[i * n + j], dftQ[i * n * 2 + j] = Q[i * n + j];
    dftQ[d * n * 2] = 1;
    FFT(d * n * 4, dftP.data(), root.data());
    FFT(d * n * 4, dftQ.data(), root.data());
    P.resize(d * n * 2);
    Q.resize(d * n * 2);
    for (int i = 0; i < d * n * 4; i += 2) {
      const uint u = (ull)dftP[i] * dftQ[i + 1] % MOD;
      const uint v = (ull)dftP[i + 1] * dftQ[i] % MOD;
      P[i / 2] = (ull)(u + MOD - v) * inv_root[i / 2] % MOD;
      if (P[i / 2] & 1) P[i / 2] += MOD;
      P[i / 2] /= 2;
      Q[i / 2] = (ull)dftQ[i] * dftQ[i + 1] % MOD;
    }
    InvFFT(d * n * 2, P.data(), inv_root.data());
    InvFFT(d * n * 2, Q.data(), inv_root.data());
    if ((Q[0] += MOD - 1) >= MOD) Q[0] -= MOD;
    for (int i = 1; i < d * 2; ++i)
      for (int j = 0; j < n / 2; ++j)
        P[i * (n / 2) + j] = P[i * n + j], Q[i * (n / 2) + j] = Q[i * n + j];
    P.resize(d * n);
    Q.resize(d * n);
    return KinoshitaLi(KinoshitaLi, P, Q, d * 2, n / 2);
  };
  f.insert(f.begin(), len - n, 0);
  f.resize(len);
  g.resize(len);
  for (int i = 0; i < len; ++i) g[i] = (g[i] != 0 ? MOD - g[i] : 0);
  std::vector<uint> res = KinoshitaLi(KinoshitaLi, f, g, 1, len);
  std::reverse(res.begin(), res.end());
  res.resize(n);
  return res;
}

// 形式幂级数幂函数，计算 g^e mod x^n 要求 g(0) = 1
std::vector<uint> FPSPow1(std::vector<uint> g, uint e, int n) {
  assert(!g.empty() && g[0] == 1);
  if (n == 1) return std::vector<uint>{1u};
  std::vector<uint> inv(n), f(n);
  inv[1] = f[0] = 1;
  for (int i = 2; i < n; ++i)
    inv[i] = (ull)(MOD - MOD / i) * inv[MOD % i] % MOD;
  for (int i = 1; i < n; ++i)
    f[i] = (ull)f[i - 1] * (e + MOD + 1 - i) % MOD * inv[i] % MOD;
  g[0] = 0;
  return FPSComposition(f, g, n);
}

// 形式幂级数复合逆
// 计算 g mod x^n 满足 g(f) = f(g) = x 要求 g(0) = 0 且 g'(0) ≠ 0
std::vector<uint> FPSReversion(std::vector<uint> f, int n) {
  assert(f.size() >= 2 && f[0] == 0 && f[1] != 0);
  if (n == 1) return std::vector<uint>{0u};
  f.resize(n);
  const uint invf1 = InvMod(f[1]);
  uint invf1p = 1;
  for (int i = 0; i < n; ++i)
    f[i] = (ull)f[i] * invf1p % MOD, invf1p = (ull)invf1p * invf1 % MOD;
  std::vector<uint> inv(n);
  inv[1] = 1;
  for (int i = 2; i < n; ++i)
    inv[i] = (ull)(MOD - MOD / i) * inv[MOD % i] % MOD;
  std::vector<uint> proj = PowerProjection(std::vector<uint>{1u}, f, n);
  for (int i = 1; i < n; ++i)
    proj[i] = (ull)proj[i] * (n - 1) % MOD * inv[i] % MOD;
  std::reverse(proj.begin(), proj.end());
  std::vector<uint> res = FPSPow1(proj, InvMod(MOD + 1 - n), n - 1);
  for (int i = 0; i < n - 1; ++i) res[i] = (ull)res[i] * invf1 % MOD;
  res.insert(res.begin(), 0);
  return res;
}

int main() {
  int n;
  std::scanf("%d", &n);
  std::vector<uint> f(n);
  for (int i = 0; i < n; ++i) std::scanf("%u", &f[i]);
  const std::vector<uint> res = FPSReversion(f, n);
  for (int i = 0; i < n; ++i) std::printf("%u%c", res[i], " \n"[i + 1 == n]);
  return 0;
}
