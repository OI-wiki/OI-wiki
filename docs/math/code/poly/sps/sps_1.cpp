#include <bit>
#include <cassert>
#include <iostream>
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
  friend bool operator==(const Fp &lhs, const Fp &rhs) { return lhs.v_ == rhs.v_; }
  friend bool operator!=(const Fp &lhs, const Fp &rhs) { return lhs.v_ != rhs.v_; }
  friend std::istream &operator>>(std::istream &lhs, Fp &rhs) {
    int v;
    lhs >> v;
    rhs = Fp(v);
    return lhs;
  }
  friend std::ostream &operator<<(std::ostream &lhs, const Fp &rhs) { return lhs << rhs.v_; }

private:
  unsigned int v_;
};

template <typename T>
void zeta_n(T x, int n) {
  for (int i = 1; i < n; i <<= 1)
    for (int j = i; j < n; j = (j + 1) | i) x[j] += x[j ^ i];
}

template <typename T>
void zeta(std::vector<T> &x) {
  zeta_n(x.begin(), x.size());
}

template <typename T>
void moebius_n(T x, int n) {
  for (int i = n >> 1; i != 0; i >>= 1)
    for (int j = i; j < n; j = (j + 1) | i) x[j] -= x[j ^ i];
}

template <typename T>
void moebius(std::vector<T> &x) {
  moebius_n(x.begin(), x.size());
}

template <typename T>
std::vector<T> subset_convolution(const std::vector<T> &x, const std::vector<T> &y) {
  assert(x.size() == y.size());
  const int len = x.size();
  const int n   = std::countr_zero<unsigned>(len);
  std::vector zx(n + 1, std::vector<T>(len)), zy(n + 1, std::vector<T>(len));
  for (int i = 0; i != len; ++i) {
    const auto p = std::popcount<unsigned>(i);
    zx[p][i]     = x[i];
    zy[p][i]     = y[i];
  }
  for (int i = 0; i <= n; ++i) {
    zeta(zx[i]);
    zeta(zy[i]);
  }
  std::vector zxy(n + 1, std::vector<T>(len));
  for (int i = 0; i <= n; ++i)
    for (int j = 0; j <= i; ++j)
      for (int k = 0; k != len; ++k) zxy[i][k] += zx[j][k] * zy[i - j][k];
  for (int i = 0; i <= n; ++i) moebius(zxy[i]);
  std::vector<T> res(len);
  for (int i = 0; i != len; ++i) res[i] = zxy[std::popcount<unsigned>(i)][i];
  return res;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  using mint = Fp<998244353>;
  int n;
  std::cin >> n;
  std::vector<mint> a(1 << n), b(1 << n);
  for (auto &&i : a) std::cin >> i;
  for (auto &&i : b) std::cin >> i;
  for (auto &&i : subset_convolution(a, b)) std::cout << i << ' ';
  return 0;
}
