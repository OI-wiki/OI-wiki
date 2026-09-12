#include <iostream>

// --8<-- [start:core]
// A simple ModInt implementation.
template <int M>
struct ModInt {
  struct skip_mod {};

  ModInt(int v, skip_mod) : v(v) {}

  int v;

  ModInt() : v(0) {}

  // Initialization: find remainder.
  // Equivalent to: v = int((x % M + M) % M)
  ModInt(long long x) {
    x %= M;
    if (x < 0) x += M;
    v = int(x);
  }

  // Addition.
  // Equivalent to: ModInt((l.v + r.v) % M)
  friend ModInt operator+(ModInt l, ModInt r) {
    int res = l.v + r.v;
    if (res >= M) res -= M;
    return ModInt(res, skip_mod{});
  }

  // Subtraction.
  // Equivalent to: ModInt((l.v - r.v + M) % M)
  friend ModInt operator-(ModInt l, ModInt r) {
    int res = l.v - r.v;
    if (res < 0) res += M;
    return ModInt(res, skip_mod{});
  }

  // Multiplication.
  friend ModInt operator*(ModInt l, ModInt r) {
    return ModInt(1LL * l.v * r.v % M, skip_mod{});
  }

  // Exponentiation.
  ModInt pow(long long b) const {
    ModInt res{1}, po{*this};
    for (; b; b >>= 1) {
      if (b & 1) res = res * po;
      po = po * po;
    }
    return res;
  }
};

// --8<-- [end:core]
template <int M>
std::ostream& operator<<(std::ostream& os, const ModInt<M>& m) {
  return os << m.v;
}

using mint = ModInt<1000000007>;

int main() {
  // Test constructor normalization
  std::cout << mint(10) << "\n";
  std::cout << mint(-10) << "\n";
  std::cout << mint(1000000007) << "\n";
  std::cout << mint(-1000000007) << "\n";

  // Test addition
  std::cout << (mint(1000000006) + mint(2)) << "\n";

  // Test subtraction
  std::cout << (mint(3) - mint(5)) << "\n";

  // Test multiplication
  std::cout << (mint(123456) * mint(789012)) << "\n";

  // Test pow
  std::cout << mint(2).pow(10) << "\n";
  std::cout << mint(2).pow(0) << "\n";
  std::cout << mint(2).pow(1000000006) << "\n";

  return 0;
}
