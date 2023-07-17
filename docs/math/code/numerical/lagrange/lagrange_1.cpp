#include <exception>
#include <iostream>
#include <optional>
#include <tuple>
#include <utility>
#include <vector>

template <unsigned int Mod>
class Fp {
  static_assert(static_cast<int>(Mod) > 1);

 public:
  Fp() : v_() {}

  Fp(int v) : v_(safe_mod(v)) {}

  static unsigned int safe_mod(int v) {
    v %= static_cast<int>(Mod);
    return v < 0 ? v + static_cast<int>(Mod) : v;
  }

  unsigned int value() const { return v_; }

  Fp operator-() const { return Fp(Mod - v_); }

  Fp pow(int e) const {
    if (e < 0) return inv().pow(-e);
    for (Fp x(*this), res(1);; x *= x) {
      if (e & 1) res *= x;
      if ((e >>= 1) == 0) return res;
    }
  }

  Fp inv() const {
    int x1 = 1, x3 = 0, a = v_, b = Mod;
    while (b != 0) {
      int q = a / b, x1_old = x1, a_old = a;
      x1 = x3, x3 = x1_old - x3 * q, a = b, b = a_old - b * q;
    }
    return Fp(x1);
  }

  Fp &operator+=(const Fp &rhs) {
    if ((v_ += rhs.v_) >= Mod) v_ -= Mod;
    return *this;
  }

  Fp &operator-=(const Fp &rhs) {
    if ((v_ += Mod - rhs.v_) >= Mod) v_ -= Mod;
    return *this;
  }

  Fp &operator*=(const Fp &rhs) {
    v_ = static_cast<unsigned long long>(v_) * rhs.v_ % Mod;
    return *this;
  }

  Fp &operator/=(const Fp &rhs) { return operator*=(rhs.inv()); }

  void swap(Fp &rhs) {
    unsigned int v = v_;
    v_ = rhs.v_, rhs.v_ = v;
  }

  friend Fp operator+(const Fp &lhs, const Fp &rhs) { return Fp(lhs) += rhs; }

  friend Fp operator-(const Fp &lhs, const Fp &rhs) { return Fp(lhs) -= rhs; }

  friend Fp operator*(const Fp &lhs, const Fp &rhs) { return Fp(lhs) *= rhs; }

  friend Fp operator/(const Fp &lhs, const Fp &rhs) { return Fp(lhs) /= rhs; }

  friend bool operator==(const Fp &lhs, const Fp &rhs) {
    return lhs.v_ == rhs.v_;
  }

  friend bool operator!=(const Fp &lhs, const Fp &rhs) {
    return lhs.v_ != rhs.v_;
  }

  friend std::istream &operator>>(std::istream &lhs, Fp &rhs) {
    int v;
    lhs >> v;
    rhs = Fp(v);
    return lhs;
  }

  friend std::ostream &operator<<(std::ostream &lhs, const Fp &rhs) {
    return lhs << rhs.v_;
  }

 private:
  unsigned int v_;
};

template <typename T>
class Poly : public std::vector<T> {
 public:
  using std::vector<T>::vector;  // 使用继承的构造函数

  bool is_zero() const { return deg() == -1; }

  void shrink() { this->resize(std::max(deg() + 1, 1)); }

  int deg()
      const {  // 多项式的次数，当多项式为零时度数为 -1 而不是一般定义的负无穷
    int d = static_cast<int>(this->size()) - 1;
    const T z;
    while (d >= 0 && this->operator[](d) == z) --d;
    return d;
  }

  T leading_coeff() const {
    int d = deg();
    return d == -1 ? T() : this->operator[](d);
  }

  Poly operator-() const {
    Poly res;
    res.reserve(this->size());
    for (auto &&i : *this) res.emplace_back(-i);
    res.shrink();
    return res;
  }

  Poly &operator+=(const Poly &rhs) {
    if (this->size() < rhs.size()) this->resize(rhs.size());
    for (int i = 0, e = static_cast<int>(rhs.size()); i != e; ++i)
      this->operator[](i) += rhs[i];
    shrink();
    return *this;
  }

  Poly &operator-=(const Poly &rhs) {
    if (this->size() < rhs.size()) this->resize(rhs.size());
    for (int i = 0, e = static_cast<int>(rhs.size()); i != e; ++i)
      this->operator[](i) -= rhs[i];
    shrink();
    return *this;
  }

  Poly &operator*=(const Poly &rhs) {
    int n = deg(), m = rhs.deg();
    if (n == -1 || m == -1) return operator=(Poly{0});
    Poly res(n + m + 1);
    for (int i = 0; i <= n; ++i)
      for (int j = 0; j <= m; ++j) res[i + j] += this->operator[](i) * rhs[j];
    return operator=(res);
  }

  Poly &operator/=(const Poly &rhs) {
    int n = deg(), m = rhs.deg(), q = n - m;
    if (m == -1) throw std::runtime_error("Division by zero");
    if (q <= -1) return operator=(Poly{0});
    Poly res(q + 1);
    const T iv = 1 / rhs.leading_coeff();
    for (int i = q; i >= 0; --i)
      if ((res[i] = this->operator[](n--) * iv) != T())
        for (int j = 0; j != m; ++j) this->operator[](i + j) -= res[i] * rhs[j];
    return operator=(res);
  }

  Poly &operator%=(const Poly &rhs) {
    int n = deg(), m = rhs.deg(), q = n - m;
    if (m == -1) throw std::runtime_error("Division by zero");
    const T iv = 1 / rhs.leading_coeff();
    for (int i = q; i >= 0; --i)
      if (T res = this->operator[](n--) * iv; res != T())
        for (int j = 0; j <= m; ++j) this->operator[](i + j) -= res * rhs[j];
    shrink();
    return *this;
  }

  std::pair<Poly, Poly> div_mod(const Poly &rhs) const {
    int n = deg(), m = rhs.deg(), q = n - m;
    if (m == -1) throw std::runtime_error("Division by zero");
    if (q <= -1) return std::make_pair(Poly{0}, Poly(*this));
    const T iv = 1 / rhs.leading_coeff();
    Poly quo(q + 1), rem(*this);
    for (int i = q; i >= 0; --i)
      if ((quo[i] = rem[n--] * iv) != T())
        for (int j = 0; j <= m; ++j) rem[i + j] -= quo[i] * rhs[j];
    rem.shrink();
    return std::make_pair(quo, rem);  // (quotient, remainder)
  }

  T eval(const T &pt) const {
    T res;
    for (int i = deg(); i >= 0; --i) res = res * pt + this->operator[](i);
    return res;
  }

  friend Poly operator+(const Poly &lhs, const Poly &rhs) {
    return Poly(lhs) += rhs;
  }

  friend Poly operator-(const Poly &lhs, const Poly &rhs) {
    return Poly(lhs) -= rhs;
  }

  friend Poly operator*(const Poly &lhs, const Poly &rhs) {
    return Poly(lhs) *= rhs;
  }

  friend Poly operator/(const Poly &lhs, const Poly &rhs) {
    return Poly(lhs) /= rhs;
  }

  friend Poly operator%(const Poly &lhs, const Poly &rhs) {
    return Poly(lhs) %= rhs;
  }

  friend bool operator==(const Poly &lhs, const Poly &rhs) {
    int d = lhs.deg();
    if (d != rhs.deg()) return false;
    for (; d >= 0; --d)
      if (lhs[d] != rhs[d]) return false;
    return true;
  }

  friend bool operator!=(const Poly &lhs, const Poly &rhs) {
    return !(lhs == rhs);
  }

  friend std::ostream &operator<<(std::ostream &lhs, const Poly &rhs) {
    int s = 0, e = static_cast<int>(rhs.size());
    lhs << '[';
    for (auto &&i : rhs) {
      lhs << i;
      if (s >= 1) lhs << 'x';
      if (s > 1) lhs << '^' << s;
      if (++s != e) lhs << " + ";
    }
    return lhs << ']';
  }
};

template <typename T>
Poly<T> lagrange_interpolation(const std::vector<T> &x,
                               const std::vector<T> &y) {
  if (x.size() != y.size()) throw std::runtime_error("x.size() != y.size()");
  const int n = static_cast<int>(x.size());
  Poly<T> M = {T(1)}, f;
  for (int i = 0; i != n; ++i) M *= Poly<T>{-x[i], T(1)};
  for (int i = 0; i != n; ++i) {
    auto m = M / Poly<T>{-x[i], T(1)};
    f += Poly<T>{y[i] / m.eval(x[i])} * m;
  }
  return f;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  using Z = Fp<998244353>;
  int n;
  Z k;
  std::cin >> n >> k;
  std::vector<Z> x(n), y(n);
  for (int i = 0; i != n; ++i) std::cin >> x[i] >> y[i];
  std::cout << lagrange_interpolation(x, y).eval(k) << std::endl;
  return 0;
}
