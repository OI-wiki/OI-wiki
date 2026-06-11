#include <iostream>
#include <vector>

// Extended Euclid.
void ex_gcd(int a, int b, int& x, int& y) {
  if (!b) {
    x = 1;
    y = 0;
  } else {
    ex_gcd(b, a % b, y, x);
    y -= a / b * x;
  }
}

// Inverse of a mod m.
int inverse(int a, int m) {
  int x, y;
  ex_gcd(a, m, x, y);
  return (x % m + m) % m;
}

// Coefficient in CRT.
int crt_coeff(int m_i, int m) {
  long long mm = m / m_i;
  mm *= inverse(mm, m_i);
  return mm % m;
}

// Binominal Coefficient Calculator Modulo Prime Power.
class BinomModPrimePower {
  int p, a, pa;
  std::vector<int> f;

  // Obtain multiplicity of p in n!.
  long long nu(long long n) {
    long long count = 0;
    do {
      n /= p;
      count += n;
    } while (n);
    return count;
  }

  // Calculate (n!)_p mod pa.
  long long fact_mod(long long n) {
    bool neg = p != 2 || pa <= 4;
    long long res = 1;
    while (n > 1) {
      if ((n / pa) & neg) res = pa - res;
      res = res * f[n % pa] % pa;
      n /= p;
    }
    return res;
  }

 public:
  BinomModPrimePower(int p, int a, int pa) : p(p), a(a), pa(pa), f(pa) {
    // Pretreatment.
    f[0] = 1;
    for (int i = 1; i < pa; ++i) {
      f[i] = i % p ? (long long)f[i - 1] * i % pa : f[i - 1];
    }
  }

  // Calculate Binom(n, k) mod pa.
  int binomial(long long n, long long k) {
    long long v = nu(n) - nu(n - k) - nu(k);
    if (v >= a) return 0;
    auto res = fact_mod(n - k) * fact_mod(k) % pa;
    res = fact_mod(n) * inverse(res, pa) % pa;
    for (; v; --v) res *= p;
    return res % pa;
  }
};

// Binominal Coefficient Calculator.
class BinomMod {
  int m;
  std::vector<BinomModPrimePower> bp;
  std::vector<long long> crt_m;

 public:
  BinomMod(int n) : m(n) {
    // Factorize.
    for (int p = 2; p * p <= n; ++p) {
      if (n % p == 0) {
        int a = 0, pa = 1;
        for (; n % p == 0; n /= p, ++a, pa *= p);
        bp.emplace_back(p, a, pa);
        crt_m.emplace_back(crt_coeff(pa, m));
      }
    }
    if (n > 1) {
      bp.emplace_back(n, 1, n);
      crt_m.emplace_back(crt_coeff(n, m));
    }
  }

  // Calculate Binom(n, k) mod m.
  int binomial(long long n, long long k) {
    long long res = 0;
    for (size_t i = 0; i != bp.size(); ++i) {
      res = (bp[i].binomial(n, k) * crt_m[i] + res) % m;
    }
    return res;
  }
};

int main() {
  int t, m;
  std::cin >> t >> m;
  BinomMod bm(m);
  for (; t; --t) {
    long long n, k;
    std::cin >> n >> k;
    std::cout << bm.binomial(n, k) << '\n';
  }
  return 0;
}
