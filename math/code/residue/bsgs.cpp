#include <algorithm>
#include <cmath>
#include <iostream>
#include <tuple>
#include <unordered_map>
#include <vector>

struct PrimePower {
  int p, e, pe;

  PrimePower(int p, int e, int pe) : p(p), e(e), pe(pe) {}
};

// Factorization.
auto factorize(int n) {
  std::vector<PrimePower> ans;
  for (int x = 2; x * x <= n; ++x) {
    int e = 0, pe = 1;
    for (; n % x == 0; n /= x, ++e, pe *= x);
    if (e) ans.emplace_back(x, e, pe);
  }
  if (n > 1) ans.emplace_back(n, 1, n);
  return ans;
}

// Binary exponentiation.
int pow(int a, int b, int m = 0) {
  int res = 1;
  for (; b; b >>= 1) {
    if (b & 1) res = m ? (long long)res * a % m : res * a;
    a = m ? (long long)a * a % m : a * a;
  }
  return res;
}

// Find a primitive root modulo odd prime power.
int primitive_root(PrimePower pp) {
  std::vector<int> exp;
  int phi = pp.pe / pp.p * (pp.p - 1);
  for (auto factor : factorize(pp.p - 1)) {
    exp.push_back(phi / factor.p);
  }
  if (pp.e != 1) exp.push_back(phi / pp.p);
  int ans = 0;
  bool succ = false;
  while (!succ) {
    ++ans;
    succ = true;
    for (int b : exp) {
      if (pow(ans, b, pp.pe) == 1) {
        succ = false;
        break;
      }
    }
  }
  return ans;
}

// Discrete logarithm. (BSGS Algorithm)
int log(int g, int a, int m) {
  int b = std::sqrt(m + 0.25l) + 1;
  std::unordered_map<int, int> mp;
  int po0 = a % m, po1 = 1;
  for (int i = 0; i < b; ++i) {
    mp[po0] = i;
    po0 = (long long)po0 * g % m;
  }
  po0 = pow(g, b, m);
  for (int j = 1; j <= b; ++j) {
    po1 = (long long)po1 * po0 % m;
    if (mp.count(po1)) return j * b - mp[po1];
  }
  return -1;
}

// Extended Euclidean Algorithm.
int ex_gcd(int a, int b, int& x, int& y) {
  if (!b) {
    x = 1;
    y = 0;
    return a;
  } else {
    int d = ex_gcd(b, a % b, y, x);
    y -= a / b * x;
    return d;
  }
}

// Returns the modular inverse of A modulo M.
// Assumes that gcd(A, M) = 1, so the inverse exists.
int inv(int a, int m) {
  int x, y;
  ex_gcd(a, m, x, y);
  return (x % m + m) % m;
}

// Solves the linear congruence equation: Ax = B mod N.
// Return the least nonnegative solution and the common difference.
std::pair<int, int> solve_linear(int a, int b, int n) {
  int x, y;
  int d = ex_gcd(a, n, x, y);
  if (b % d) return {-1, -1};
  n /= d;
  x = ((long long)x * (b / d) % n + n) % n;
  return {x, n};
}

// Subroutine: Find all the K-th roots with a primitive root G known.
std::vector<int> calc(int g, int k, int a, int p, int pe) {
  int ind = log(g, a, pe);
  if (ind == -1) return {};
  int mm = p == 2 ? pe / 4 : pe / p * (p - 1);
  int y0, d;
  std::tie(y0, d) = solve_linear(k, ind, mm);
  if (y0 == -1) return {};
  int ans = pow(g, y0, pe), po = pow(g, d, pe);
  std::vector<int> res(mm / d);
  for (auto& x : res) {
    x = ans;
    ans = (long long)ans * po % pe;
  }
  return res;
}

// Find all the K-th roots of A modulo prime power P^E.
std::vector<int> kth_roots_mod_pe(int k, int a, PrimePower pp) {
  int p = pp.p, e = pp.e, pe = pp.pe;
  a %= pe;
  if (a == 0) {
    int d = pow(p, (e - 1) / k + 1);
    std::vector<int> res(pe / d);
    for (int i = 0; i < pe / d; ++i) {
      res[i] = i * d;
    }
    return res;
  }
  int s = 0;
  for (; a % p == 0; a /= p, ++s);
  if (s % k) return {};
  int psk = pow(p, s / k), pss = pow(p, s - s / k), pes = pow(p, e - s);
  std::vector<int> res;
  if (p != 2) {
    int g = primitive_root(PrimePower(p, e - s, pes));
    res = calc(g, k, a, p, pes);
  } else if (pes == 2) {
    res.push_back(a);
  } else if (k & 1) {
    int z = a % 4 == 3;
    a = z ? pes - a : a;
    res = calc(5, k, a, p, pes);
    if (z) {
      for (auto& x : res) x = pes - x;
    }
  } else {
    if (a % 4 == 3) return {};
    res = calc(5, k, a, p, pes);
    int m = res.size();
    res.reserve(m * 2);
    for (int i = 0; i < m; ++i) {
      res.push_back(pes - res[i]);
    }
  }
  int m = res.size();
  res.reserve(m * pss);
  for (int j = 1; j < pss; ++j) {
    for (int i = 0; i < m; ++i) {
      res.push_back(res.end()[-m] + pes);
    }
  }
  for (auto& x : res) x *= psk;
  return res;
}

// Find all the K-th roots of A modulo positive integer M.
std::vector<int> kth_roots_mod_m(int k, int a, int m) {
  auto factors = factorize(m);
  int m0 = 0;
  std::vector<std::vector<int>> sols;
  for (const auto& pp : factors) {
    sols.push_back(kth_roots_mod_pe(k, a, pp));
    if (sols.back().empty()) return {};
  }
  std::vector<int> ans;
  for (int i = 0; i < (int)factors.size(); ++i) {
    auto pp = factors[i];
    if (!i) {
      m0 = pp.pe;
      ans = sols[i];
    } else {
      long long m1 = pp.pe * inv(pp.pe, m0);
      long long m2 = m0 * inv(m0, pp.pe);
      m0 *= pp.pe;
      std::vector<int> _ans;
      _ans.reserve(ans.size() * sols[i].size());
      for (auto x : ans) {
        for (auto y : sols[i]) {
          _ans.push_back((m1 * x + m2 * y) % m0);
        }
      }
      ans.swap(_ans);
    }
  }
  return ans;
}

void solve() {
  int n, m, k;
  std::cin >> n >> m >> k;
  auto ans = kth_roots_mod_m(n, k, m);
  if (ans.empty()) {
    std::cout << 0 << '\n';
    return;
  }
  std::cout << ans.size() << '\n';
  std::sort(ans.begin(), ans.end());
  for (auto x : ans) std::cout << x << ' ';
  std::cout << '\n';
}

int main() {
  int t;
  std::cin >> t;
  for (; t; --t) {
    solve();
  }
}
