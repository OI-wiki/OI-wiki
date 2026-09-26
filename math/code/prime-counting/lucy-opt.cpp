#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

// --8<-- [start:core]
// Modified from 渐变色's codes:
//   https://www.luogu.com.cn/article/q4d4jl20
// Submission:
// * https://judge.yosupo.jp/submission/398981 (1e11)
// * https://www.luogu.com.cn/record/296415705 (1e13)
long long count_pi(long long n) {
  if (n <= 1) return 0;
  // Constants.
  int v = std::sqrt(n + 0.25l);                // x^{1/2}.
  int w = std::sqrt(v + 0.25l);                // x^{1/4}. Phase II stops here.
  int z = std::min(w, (int)std::sqrt(w) * 2);  // ~x^{1/8}. Phase I stops here.
  int y = std::pow(n, 0.625l) / std::log(n) * 2;  // ~x^{5/8}/log(x). BIT size.
  y = std::min<long long>(std::max(y, v), n);
  int B = n / y;  // the largest j such that n/j >= y.
  B = std::min<long long>(n / (n / B), y);
  // Initialize.
  std::vector<long long> l(v + 1);  // l[i] = S(n/i, .)
  std::vector<int> s(y + 1);        // phase I: S(i, .); phase II: BIT.
  std::vector<bool> e(y + 1);       // e[i] == true once i has been crossed out.
  std::vector<int> pi(y + 1);       // prefix for e; then pi(.) for O(1) query.
  for (int i = 1; i <= v; ++i) l[i] = n / i - 1;  // Lucy DP initialization.
  for (int i = 1; i <= v; ++i) s[i] = i - 1;

  // ============ PHASE I: plain Lucy DP, p <= z ~ n^(1/8) ===================
  int p;
  for (p = 2; p <= z; ++p) {
    if (s[p] != s[p - 1]) {  // when p is prime.
      auto m = n / p;
      int t0 = s[p - 1];  // the number of primes < p.
      int t = v / p;      // splitting point by where n/(i*p) lands.
      // S(u, .) -= (S(u / p) - t0), case by case.
      for (int i = 1; i <= t; ++i) l[i] -= l[i * p] - t0;
      for (int i = t + 1; i <= v; ++i) l[i] -= s[m / i] - t0;
      for (int i = v, j = t; j >= p; --j)
        for (int k = j * p; i >= k; --i) s[i] -= s[j] - t0;
      // Sieve.
      for (int i = p * p; i <= y; i += p) e[i] = 1;
    }
  }
  // Obtain z-rough number list for [2,B].
  e[1] = 1;
  int id = 1;
  std::vector<int> roughs(B + 1);
  for (int i = 1; i <= B; ++i)
    if (!e[i]) roughs[id++] = i;
  roughs[id] = 0x7fffffff;  // sentinel: terminates every walk.
  // Build the BIT (i.e., Fenwick tree).
  for (int i = 1; i <= y; ++i) pi[i] = pi[i - 1] + e[i];
  for (int i = 1; i <= y; ++i) s[i] = pi[i] - pi[i & (i - 1)];
  // BIT query: obtain S(x,.).
  const auto query = [&](int x) -> int {
    int sum = x;
    for (; x; x &= x - 1) sum -= s[x];
    return sum;
  };
  // BIT modify: mark composite and add 1 in the BIT.
  const auto add = [&](int x) -> void {
    e[x] = 1;
    for (; x <= y; x += x & -x) ++s[x];
  };

  // ============ PHASE II: Lucy DP with BIT sieve, z < p <= n^(1/4) =========
  id = 1;
  for (; p <= w; ++p) {
    if (e[p]) continue;
    auto q = (long long)p * p;
    auto m = n / p;
    int t0 = query(p - 1);  // the number of primes < p.
    // freeze finalized values for O(1) query.
    // the frozen S(i, .) is actually pi(i).
    for (; id < q; ++id) pi[id] = query(id);
    // splitting point by where n/(i*p) lands.
    int t1 = B / p;
    int t2 = std::min<long long>(B, m / q);
    // S(u, .) -= (S(u / p) - t0), case by case.
    int i = 1, j = 1;
    for (; i <= t1; i = roughs[++j]) l[i] -= l[i * p] - t0;
    for (; i <= t2; i = roughs[++j]) l[i] -= query(m / i) - t0;
    for (; i <= B; i = roughs[++j]) l[i] -= pi[m / i] - t0;
    // Sieve (with BIT).
    for (int i = q; i <= y; i += p)
      if (!e[i]) add(i);
  }
  // freeze value till v=x^{1/2}.
  for (; id <= v; ++id) pi[id] = query(id);
  // prime list till v=x^{1/2}.
  std::vector<int> primes;
  primes.push_back(1);  // dummy, p_0=1.
  for (int i = 2; i <= v; ++i)
    if (!e[i]) primes.push_back(i);

  // ============ PHASE III: stop early, correct with P2 and P3 ==============
  // ---- -P2, part 1: the triangular part.
  l[1] += (pi[v] + pi[w] - 1LL) * (pi[v] - pi[w]) / 2;
  // ---- -P2, part 2: the sum of S(n/p,a).
  for (int i = pi[w] + 1; i <= pi[B]; ++i) l[1] -= l[primes[i]];
  for (int i = pi[B] + 1; i <= pi[v]; ++i) l[1] -= query(n / primes[i]);
  // ---- +Delta(n).
  for (int i = pi[w] + 1; i <= pi[v]; ++i) {
    int p = primes[i];
    auto m = n / p;
    int e = pi[m / p];  // pi(n/p^2).
    if (e <= i) break;  // i.e., p^3 > n.
    l[1] += e - i;
    long long t = 0;
    auto s = pi[(int)std::sqrt(m + 0.25l)];  // pi(sqrt(n/p)).
    for (int k = i + 1; k <= s; ++k) t += pi[m / primes[k]];
    l[1] += 2 * t - (long long)(i + s) * (s - i);
  }

  return l[1];
}

// --8<-- [end:core]
int main() {
  long long n;
  std::cin >> n;
  std::cout << count_pi(n) << std::endl;
  return 0;
}
