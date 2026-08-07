#include <cstdint>
#include <iostream>
#include <tuple>
#include <vector>

auto factorize(uint32_t m) {
  std::vector<std::pair<uint32_t, int>> factors;
  for (uint32_t x = 2; x * x <= m; ++x) {
    if (m % x == 0) {
      int e = 0;
      while (m % x == 0) {
        ++e;
        m /= x;
      }
      factors.emplace_back(x, e);
    }
  }
  if (m > 1) factors.emplace_back(m, 1);
  return factors;
}

uint64_t gcd(uint64_t x, uint64_t y) { return y ? gcd(y, x % y) : x; }

uint64_t lcm(uint64_t x, uint64_t y) { return x / gcd(x, y) * y; }

uint64_t pow(uint64_t x, uint64_t y) {
  uint64_t res = 1;
  while (y) {
    if (y & 1) res *= x;
    x *= x;
    y >>= 1;
  }
  return res;
}

// --8<-- [start:pisano]
// Get a period of Fibonacci sequence mod m.
// Not necessarily be the exact Pisano period.
uint32_t calc_cycle_from_mod(uint32_t m) {
  uint32_t res = 1;
  for (auto pe : factorize(m)) {
    auto p = pe.first;
    auto e = pe.second;
    uint64_t cur = pow(p, e - 1);
    if (p == 2) {
      cur *= 3;
    } else if (p == 5) {
      cur *= 20;
    } else if (p % 5 == 1 || p % 5 == 4) {
      cur *= p - 1;
    } else {
      cur *= 2 * (p + 1);
    }
    res = lcm(res, cur);
  }
  return res;
}

// --8<-- [end:pisano]
int main() {
  int t;
  std::cin >> t;
  for (; t; --t) {
    int m;
    std::cin >> m;
    std::cout << calc_cycle_from_mod(m) << '\n';
  }
  return 0;
}
