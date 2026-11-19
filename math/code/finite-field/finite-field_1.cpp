#include <iostream>
#include <random>
#include <vector>

class FiniteField {
  int p, k;
  std::vector<int> mod;  // Monic.

  // Remove leadings zeros of a polynomial.
  static void trim(std::vector<int>& poly) {
    int m = poly.size();
    for (; m && !poly[m - 1]; --m);
    poly.resize(m);
  }

  // Binary exponentiation mod p.
  int pow(int a, int b) const {
    int res = 1, po = a;
    while (b) {
      if (b & 1) res = (long long)res * po % p;
      po = (long long)po * po % p;
      b >>= 1;
    }
    return res;
  }

  // Multiplicative inverse mod p.
  int inv(int a) const { return pow(a, p - 2); }

  // Polynomial GCD. Inputs are supposed to have no leading zeros.
  std::vector<int> poly_gcd(const std::vector<int>& lhs,
                            const std::vector<int>& rhs) const {
    if (lhs.size() < rhs.size()) {
      return poly_gcd(rhs, lhs);
    } else if (rhs.size()) {
      auto rem = lhs;  // remainder.
      long long v = inv(rhs.back());
      for (int i = rem.size() - rhs.size(); i >= 0; --i) {
        auto d = v * (p - rem[i + rhs.size() - 1]) % p;
        for (int j = 0; j < rhs.size(); ++j) {
          rem[i + j] = (rem[i + j] + d * rhs[j]) % p;
        }
      }
      trim(rem);  // Remove leading zeros.
      return poly_gcd(rhs, rem);
    } else {
      return lhs;
    }
  }

  // Polynomials Ex-GCD. Inputs are supposed to have no leading zeros.
  void poly_ex_gcd(const std::vector<int>& lhs, const std::vector<int>& rhs,
                   std::vector<int>& x, std::vector<int>& y) const {
    if (lhs.size() < rhs.size()) {
      poly_ex_gcd(rhs, lhs, y, x);
    } else if (rhs.size()) {
      std::vector<int> quo(lhs.size() - rhs.size() + 1);  // quotient.
      auto rem = lhs;                                     // remainder.
      long long v = inv(rhs.back());
      for (int i = rem.size() - rhs.size(); i >= 0; --i) {
        quo[i] = v * rem[i + rhs.size() - 1] % p;
        long long d = p - quo[i];  // d = -quo[i].
        for (int j = 0; j < rhs.size(); ++j) {
          rem[i + j] = (rem[i + j] + d * rhs[j]) % p;
        }
      }
      trim(rem);  // Remove leading zeros.
      // Recursively ex_gcd.
      poly_ex_gcd(rhs, rem, y, x);
      // y -= a/b*x.
      if (y.size() < quo.size() + x.size() - 1) {
        y.resize(quo.size() + x.size() - 1, 0);
      }
      for (int i = 0; i < quo.size(); ++i) {
        for (int j = 0; j < x.size(); ++j) {
          y[i + j] = (y[i + j] - (long long)quo[i] * x[j]) % p;
          if (y[i + j] < 0) y[i + j] += p;
        }
      }
      trim(y);  // Remove leading zeros.
    } else {
      // x = 1, y = 0.
      x.assign(1, inv(lhs.back()));
      y.clear();
    }
  }

 public:
  // Class for Finite Field Elements.
  struct Element {
    const FiniteField* gf;
    std::vector<int> a;

    // Element initialization as zero.
    Element(const FiniteField* gf) : gf(gf), a(gf->k) {}

    // Element initialization from the numeric representation.
    Element(const FiniteField* gf, int id) : gf(gf), a(gf->k) {
      for (int i = 0; i < gf->k; ++i) {
        a[i] = id % gf->p;
        id /= gf->p;
      }
    }

    // Generate the numeric representation from an element.
    int idx() const {
      int id = 0;
      for (int i = gf->k - 1; i >= 0; --i) {
        id = id * gf->p + a[i];
      }
      return id;
    }

    // Access the i-th coefficient.
    int& operator[](int i) { return a[i]; }

    // Addition.
    Element& operator+=(const Element& rhs) {
      for (int i = 0; i < gf->k; ++i) {
        a[i] += rhs.a[i];
        if (a[i] >= gf->p) a[i] -= gf->p;
      }
      return *this;
    }

    // Addition.
    Element operator+(const Element& rhs) const {
      Element res(*this);
      res += rhs;
      return res;
    }

    // Subtraction.
    Element& operator-=(const Element& rhs) {
      for (int i = 0; i < gf->k; ++i) {
        a[i] -= rhs.a[i];
        if (a[i] < 0) a[i] += gf->p;
      }
      return *this;
    }

    // Subtraction.
    Element operator-(const Element& rhs) const {
      Element res(*this);
      res -= rhs;
      return res;
    }

    // Multiplication by a scalar.
    Element& operator*=(int x) {
      for (int i = 0; i < gf->k; ++i) {
        a[i] = (long long)a[i] * x % gf->p;
      }
      return *this;
    }

    // Multiplication by a scalar.
    Element operator*(int x) const {
      Element res(*this);
      res *= x;
      return res;
    }

    // Multiplication by x.
    Element& shift() {
      long long d = gf->p - a.back();  // d = -a[k-1].
      for (int i = gf->k - 1; i >= 0; --i) {
        a[i] = ((i ? a[i - 1] : 0) + d * gf->mod[i]) % gf->p;
      }
      return *this;
    }

    // Multiplication.
    Element& operator*=(const Element& rhs) {
      Element prod(*this);
      *this *= rhs.a[0];
      for (int j = 1; j < gf->k; ++j) {
        prod.shift();
        *this += prod * rhs.a[j];
      }
      return *this;
    }

    // Multiplication.
    Element operator*(const Element& rhs) const {
      Element res(*this);
      res *= rhs;
      return res;
    }

    // Binary exponentiation.
    Element pow(int b) const {
      Element res(gf, 1);
      Element po(*this);
      while (b) {
        if (b & 1) res *= po;
        po = po * po;
        b >>= 1;
      }
      return res;
    }

    // Multiplicative inverse.
    Element inv() const {
      Element res(gf);
      auto& x = res.a;
      std::vector<int> y;
      auto lhs = a;
      trim(lhs);
      auto rhs = gf->mod;
      gf->poly_ex_gcd(lhs, rhs, x, y);
      x.resize(gf->k);
      return res;
    }

    // Division.
    Element& operator/=(const Element& rhs) {
      *this *= rhs.inv();
      return *this;
    }

    // Division.
    Element operator/(const Element& rhs) const {
      Element res(*this);
      res /= rhs;
      return res;
    }
  };

 private:
  // Check whether the current MOD is irreducible.
  bool checkIrreducible() const {
    Element f(this, p);
    for (int j = 1; j < k; ++j) {
      // F = X^{p^j} mod MOD.
      f = f.pow(p);
      // G = X^{p^j}-X mod MOD.
      auto g = f.a;
      g[1] = g[1] ? g[1] - 1 : p - 1;
      trim(g);
      // H = MOD.
      auto h = mod;
      // Reducible if deg(GCD(G,H))>0.
      if (poly_gcd(h, g).size() > 1) return false;
    }
    return true;
  }

 public:
  FiniteField(int p, int k) : p(p), k(k), mod(k + 1, 1) {
    do {  // Randomly generate a polynomial.
      for (int i = 0; i < k; ++i) {
        mod[i] = rand() % p;
      }
    } while (!checkIrreducible());
  }
};

int main() {
  int p = 13331, k = 50;
  FiniteField gf(p, k);
  FiniteField::Element e1(&gf, rand() + 1);
  FiniteField::Element e2(&gf, rand() + 1);
  FiniteField::Element e3(&gf, rand() + 1);
  // Test Frobenius endomorphism.
  std::cout
      << ((e1 * e2 + e3).pow(p) - e1.pow(p) * e2.pow(p) - e3.pow(p)).idx();
  // Test inverse.
  std::cout << ((e1 * e2).inv() - e1.inv() / e2).idx();
  return 0;
}
