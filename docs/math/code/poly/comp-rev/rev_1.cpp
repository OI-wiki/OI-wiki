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

// 二项卷积
// Kinoshita--Li 算法作者之一的李白天在 2021 年的
// 集训队论文《信息学竞赛中的生成函数计算理论框架》中提到
// Taylor Shift 算法为二项卷积的转置
std::vector<uint> BinConv(std::vector<uint> f, uint c) {
  if (f.empty() || c == 0) return f;
  const int n = (int)f.size();
  std::vector<uint> factorial, inv_factorial;
  tie(factorial, inv_factorial) = GetFactorial(n);
  for (int i = 0; i < n; ++i) f[i] = (ull)f[i] * inv_factorial[i] % MOD;
  std::vector<uint> g(n);
  uint cp = 1;
  for (int i = 0; i < n; ++i)
    g[i] = (ull)cp * inv_factorial[i] % MOD, cp = (ull)cp * c % MOD;
  int N = 1;
  while (N < n * 2 - 1) N *= 2;
  const std::vector<uint> root = GetFFTRoot(N);
  f.resize(N);
  g.resize(N);
  FFT(f.data(), N, root.data());
  FFT(g.data(), N, root.data());
  for (int i = 0; i < N; ++i) f[i] = (ull)f[i] * g[i] % MOD;
  InvFFT(f.data(), N, root.data());
  f.resize(n);
  for (int i = 0; i < n; ++i) f[i] = (ull)f[i] * factorial[i] % MOD;
  return f;
}

// Power Projection: [x^(n-1)] (f g^i) for i = 0, ..., n-1
// 不难发现该算法就是 PolyComp 算法的转置
std::vector<uint> PowProj(std::vector<uint> f, std::vector<uint> g, int n) {
  const uint c = g.empty() ? 0u : g[0];
  if (!g.empty()) g[0] = 0;
  int N = 1;
  while (N < n) N *= 2;
  const std::vector<uint> root = GetFFTRoot(N * 4);
  // [x^(n-1)] (f(x) / (-g(x) + y)) in R[x]((y^(-1)))
  const auto KinoshitaLi = [&N, &root](std::vector<uint>& P,
                                       std::vector<uint>& Q, int d, int n) {
    assert((int)P.size() == N * 2);
    assert((int)Q.size() == N * 2);
    P.insert(begin(P), N * 2, 0u);
    uint* const nP = P.data() + N * 2;
    Q.resize(N * 4);
    for (; n > 1; d *= 2, n /= 2) {
      Q[N * 2] = 1;
      TransposedInvFFT(P.data(), N * 4, root.data());
      FFT(Q.data(), N * 4, root.data());
      for (int i = N * 4 - 2; i >= 0; i -= 2)
        nP[i / 2] = ((ull)P[i] * Q[i + 1] + (ull)P[i + 1] * Q[i]) % MOD;
      TransposedFFT(nP, N * 2, root.data());
      if (n == 2) break;
      for (int i = 0; i < N * 4; i += 2) Q[i / 2] = (ull)Q[i] * Q[i + 1] % MOD;
      InvFFT(Q.data(), N * 2, root.data());
      assert(Q[0] == 1);
      Q[0] = 0;
      for (int i = 0; i < d * 2; ++i) {
        std::fill_n(nP + i * n, n / 2, 0u);
        fill_n(begin(Q) + (i * n + n / 2), n / 2, 0u);
      }
      fill_n(begin(P), N * 2, 0u);
      fill_n(begin(Q) + N * 2, N * 2, 0u);
    }
    P.erase(begin(P), begin(P) + N * 2);
  };
  f.insert(begin(f), N - n, 0u);
  f.resize(N);
  reverse(begin(f), end(f));
  f.insert(begin(f), N, 0u);
  g.resize(N * 2);
  for (int i = 0; i < N; ++i) g[i] = (g[i] != 0 ? MOD - g[i] : 0);
  fill_n(begin(g) + N, N, 0u);
  KinoshitaLi(f, g, 1, N);
  for (int i = 0; i < N; ++i) f[i] = f[i * 2 + 1];
  f.resize(n);
  return BinConv(std::move(f), c);
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
  return FPSComp(std::move(f), std::move(g), n);
}

std::vector<uint> FPSRev(std::vector<uint> f, int n) {
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
  std::vector<uint> proj = PowProj(std::vector<uint>{1u}, std::move(f), n);
  for (int i = 1; i < n; ++i)
    proj[i] = (ull)proj[i] * (n - 1) % MOD * inv[i] % MOD;
  reverse(begin(proj), end(proj));
  std::vector<uint> res = FPSPow1(proj, MOD - inv[n - 1], n - 1);
  for (int i = 0; i < n - 1; ++i) res[i] = (ull)res[i] * invf1 % MOD;
  res.insert(begin(res), 0);
  return res;
}

int main() {
  int n;
  std::scanf("%d", &n);
  std::vector<uint> f(n);
  for (int i = 0; i < n; ++i) std::scanf("%u", &f[i]);
  const std::vector<uint> res = FPSRev(f, n);
  for (int i = 0; i < n; ++i) {
    if (i != 0) std::printf(" ");
    std::printf("%u", res[i]);
  }
  std::puts("");
  return 0;
}
