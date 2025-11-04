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

std::vector<uint> Deriv(const std::vector<uint>& f) {
  const int m = (int)f.size() - 1;
  if (m <= 0) return {};
  std::vector<uint> res(m);
  for (int i = 1; i <= m; ++i) res[i - 1] = (ull)f[i] * i % MOD;
  return res;
}

std::vector<uint> Product(std::vector<uint> f, std::vector<uint> g) {
  const int m = f.size();
  const int n = g.size();
  int len = 1;
  while (len < n + m - 1) len *= 2;
  f.resize(len);
  g.resize(len);
  std::vector<uint> root, inv_root;
  std::tie(root, inv_root) = GetFFTRoot(len);
  FFT(len, f.data(), root.data());
  FFT(len, g.data(), root.data());
  for (int i = 0; i < len; ++i) f[i] = (ull)f[i] * g[i] % MOD;
  InvFFT(len, f.data(), inv_root.data());
  f.resize(n + m - 1);
  return f;
}

// Guillaume Hanrot, Michel Quercia, Paul Zimmermann.
// The Middle Product Algorithm I.
// Appl. Algebra Eng. Commun. Comput. 14(6): 415-438 (2004)
// url: https://inria.hal.science/inria-00071921/document
// 与论文中稍微不同的是我们令 f 的长度大于等于 g 的长度，
// 然后计算出 fg 的高位系数，这就是在计算 fg mod x^m，
// 然后丢掉系数“混乱”的部分。
std::vector<uint> MiddleProduct(std::vector<uint> f, std::vector<uint> g) {
  assert(!g.empty());
  const int m = f.size();
  const int n = g.size();
  assert(m >= n);
  int len = 1;
  while (len < m) len *= 2;
  f.resize(len);
  g.resize(len);
  std::vector<uint> root, inv_root;
  std::tie(root, inv_root) = GetFFTRoot(len);
  FFT(len, f.data(), root.data());
  FFT(len, g.data(), root.data());
  for (int i = 0; i < len; ++i) f[i] = (ull)f[i] * g[i] % MOD;
  InvFFT(len, f.data(), inv_root.data());
  f.resize(m);
  f.erase(f.begin(), f.begin() + (n - 1));
  return f;
}

std::vector<uint> CZT(const std::vector<uint>& f, uint q, int n) {
  if (f.empty() || n == 0) return std::vector<uint>(n);
  const int m = f.size();
  if (q == 0) {
    std::vector<uint> res(n, f[0]);
    for (int i = 1; i < m; ++i)
      if ((res[0] += f[i]) >= MOD) res[0] -= MOD;
    return res;
  }
  // H[i] = q^(binom(i + 1, 2))
  std::vector<uint> H(std::max(m, n - 1));
  H[0] = 1;     // H[0] = q^0
  uint qi = 1;  // qi = q^i
  for (int i = 1; i < (int)H.size(); ++i) {
    qi = (ull)qi * q % MOD;
    // H[i] = q^(binom(i, 2)) * q^i
    H[i] = (ull)H[i - 1] * qi % MOD;
  }
  // F[i] = f[i] * q^(binom(i + 1, 2))
  std::vector<uint> F(m);
  for (int i = 0; i < m; ++i) F[i] = (ull)f[i] * H[i] % MOD;
  std::vector<uint> G_p(m + n - 1);
  // G[i] = q^(-binom(i, 2)), -(m - 1) ≤ i < n
  uint* const G = G_p.data() + (m - 1);
  const uint iq = InvMod(q);
  // G[-(m - 1)] = q^(-binom(-(m - 1), 2)),
  // binom(-(m - 1), 2) = (-(m - 1)) * (-(m - 1) - 1) / 2
  //                    = (m - 1) * m / 2
  G[-(m - 1)] = PowMod(iq, (ull)(m - 1) * m / 2);
  uint qmi = PowMod(q, m - 1);  // q^(-i), -(m - 1) ≤ i < n
  for (int i = -(m - 1) + 1; i < n; ++i) {
    // q^(-binom(i, 2)) = q^(-binom(i - 1, 2)) * q^(-(i - 1))
    G[i] = (ull)G[i - 1] * qmi % MOD;
    // q^(-i) = q^(-(i - 1)) * q^(-1)
    qmi = (ull)qmi * iq % MOD;
  }
  // res[i] = q^(-binom(i, 2)) * f(q^i), 0 ≤ i < n
  std::vector<uint> res = MiddleProduct(G_p, F);
  for (int i = 1; i < n; ++i) res[i] = (ull)res[i] * H[i - 1] % MOD;
  return res;
}

std::vector<uint> InvModBatch(const std::vector<uint>& a) {
  const int n = a.size();
  std::vector<uint> b(n);
  uint v = 1;
  for (int i = 0; i < n; ++i) b[i] = v, v = (ull)v * a[i] % MOD;
  assert(v != 0);
  v = InvMod(v);
  for (int i = n - 1; i >= 0; --i)
    b[i] = (ull)b[i] * v % MOD, v = (ull)v * a[i] % MOD;
  return b;
}

// --8<-- [start:core]
std::vector<uint> InvCZT(const std::vector<uint>& f, uint q) {
  if (f.empty()) return {};
  const int n = f.size();
  if (q == 0) {
    // f[0] = f(1), f[1] = f(0)
    assert(n <= 2);
    if (n == 1) return {f[0]};                 // deg(f) < 1
    return {f[1], (f[0] + MOD - f[1]) % MOD};  // deg(f) < 2
  }
  // prod[0 ≤ i < n] (x - q^i)
  const auto DaC = [q](auto&& DaC, int n) -> std::vector<uint> {
    if (n == 1) return {MOD - 1, 1u};
    // H = prod[0 ≤ i < ⌊n/2⌋] (x - q^i)
    const std::vector<uint> H = DaC(DaC, n / 2);
    // HH = H(x / q^(⌊n/2⌋)) * q^(⌊n/2⌋^2)
    std::vector<uint> HH = H;
    const uint iqn = InvMod(PowMod(q, n / 2));
    uint qq = PowMod(q, (ull)(n / 2) * (n / 2));
    for (int i = 0; i <= n / 2; ++i)
      HH[i] = (ull)HH[i] * qq % MOD, qq = (ull)qq * iqn % MOD;
    std::vector<uint> res = Product(H, HH);
    if (n & 1) {
      res.resize(n + 1);
      const uint qnm1 = MOD - PowMod(q, n - 1);
      for (int i = n; i > 0; --i) {
        if ((res[i] += res[i - 1]) >= MOD) res[i] -= MOD;
        res[i - 1] = (ull)res[i - 1] * qnm1 % MOD;
      }
    }
    return res;
  };
  const std::vector<uint> M = DaC(DaC, n);
  // C[i] = (M'(q^i))^(-1)
  std::vector<uint> C = InvModBatch(CZT(Deriv(M), q, n));
  // C[i] = f(q^i) / M'(q^i)
  for (int i = 0; i < n; ++i) C[i] = (ull)f[i] * C[i] % MOD;
  // C(x) ← C(q^(-1)x)
  const uint iq = InvMod(q);
  uint qmi = 1;
  for (int i = 0; i < n; ++i)
    C[i] = (ull)C[i] * qmi % MOD, qmi = (ull)qmi * iq % MOD;
  C = CZT(C, iq, n);
  for (int i = 0; i < n; ++i)
    if (C[i] != 0) C[i] = MOD - C[i];
  std::vector<uint> res = Product(M, C);
  res.resize(n);
  return res;
}

// --8<-- [end:core]

int main() {
  int n;
  uint a, q;
  std::scanf("%d%u%u", &n, &a, &q);
  std::vector<uint> f(n);
  for (int i = 0; i < n; ++i) std::scanf("%u", &f[i]);
  if (a == 0) {
    if (n) std::printf("%u", f[0]);
  } else {
    std::vector<uint> res = InvCZT(f, q);
    if (a != 1) {
      const uint ia = InvMod(a);
      uint aa = 1;
      for (int i = 0; i < n; ++i)
        res[i] = (ull)res[i] * aa % MOD, aa = (ull)aa * ia % MOD;
    }
    for (int i = 0; i < n; ++i) {
      if (i) std::printf(" ");
      std::printf("%u", res[i]);
    }
  }
  std::puts("");
  return 0;
}