#include <iostream>
#include <random>
#include <vector>

class FiniteField {
  int p, k;
  std::vector<int> mod;  // Monic. Leading term omitted.

  // Modular arithmetic.
  int pow(int a, int b) const {
    int res = 1, po = a;
    while (b) {
      if (b & 1) res = (long long)res * po % p;
      po = (long long)po * po % p;
      b >>= 1;
    }
    return res;
  }

  int inv(int a) const { return pow(a, p - 2); }

  // Polynomial GCD. Inputs and outputs are supposed to be monic.
  std::vector<int> poly_mod(const std::vector<int>& lhs,
                            const std::vector<int>& rhs) const {
    if (lhs.size() < rhs.size()) return lhs;
    auto tmp = lhs;
    for (int i = tmp.size() - rhs.size(); i >= 0; --i) {
      long long d = p - tmp[i + rhs.size() - 1];  // d = -tmp[i+rhs.size()-1]
      for (int j = 0; j < rhs.size(); ++j) {
        tmp[i + j] = (tmp[i + j] + d * rhs[j]) % p;
      }
    }
    int m = tmp.size();
    for (; m && !tmp[m - 1]; --m);
    tmp.resize(m);
    if (m && tmp[m - 1] != 1) {
      long long d = inv(tmp[m - 1]);
      for (int i = 0; i < m; ++i) {
        tmp[i] = d * tmp[i] % p;
      }
    }
    return tmp;
  }

  std::vector<int> poly_gcd(std::vector<int> lhs, std::vector<int> rhs) const {
    if (rhs.size()) {
      return poly_gcd(rhs, poly_mod(lhs, rhs));
    } else {
      return lhs;
    }
  }

 public:
  // Class for Finite Field Elements.
  class Element {
    const FiniteField* gf;
    std::vector<int> a;

   public:
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
  };

 private:
  // Check whether the current MOD is irreducible.
  bool checkIrreducible() const {
    Element f(this, p);
    for (int j = 1; j < k; ++j) {
      // F = X^{p^j} mod MOD.
      f = f.pow(p);
      // G = X^{p^j}-X mod MOD.
      std::vector<int> g(k);
      int m = 0;
      for (int i = 0; i < k; ++i) {
        g[i] = f[i];
        if (i == 1) g[i] = g[i] ? g[i] - 1 : p - 1;
        if (g[i]) m = i + 1;
      }
      if (!m) return false;
      g.resize(m);
      // Make G monic.
      long long d = inv(g[m - 1]);
      for (int i = 0; i < k; ++i) {
        g[i] = d * g[i] % p;
      }
      // H = MOD.
      auto h = mod;
      h.resize(k + 1, 1);
      // Reducible if deg(GCD(G,H))>1.
      if (poly_gcd(h, g).size() > 1) return false;
    }
    return true;
  }

 public:
  FiniteField(int p, int k) : p(p), k(k), mod(k) {
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
  // Test Frobenius endomorphism.
  FiniteField::Element e1(&gf, rand());
  FiniteField::Element e2(&gf, rand());
  FiniteField::Element e3(&gf, rand());
  std::cout << ((e1 * e2 + e3).pow(p) - e1.pow(p) * e2.pow(p) - e3.pow(p)).idx();
  return 0;
}