#include <cstdint>
#include <iostream>

// Check whether a working __int128 type is available.
// Clang-cl on Windows may fail to link when using mod/div with __int128.
#if defined(__SIZEOF_INT128__) && !(defined(__clang__) && defined(_MSC_VER))
#define HAS_WORKING_INT128 1
#else
#define HAS_WORKING_INT128 0
#endif

#if HAS_WORKING_INT128
// --8<-- [start:barrett]
// Modular multiplication of int32_t using Barrett reduction.
class Barrett {
  int32_t m;
  uint64_t r;

 public:
  Barrett(int32_t m) : m(m), r((uint64_t)(-m) / m + 1) {}

  // Barrett reduction: a % m.
  int32_t reduce(int64_t a) const {
    int64_t q = (__int128)a * r >> 64;
    a -= q * m;
    return a >= m ? a - m : a;
  }

  // Modular multiplication: (a * b) % m;
  // Assume that 0 <= a, b < m.
  int32_t mul(int32_t a, int32_t b) const { return reduce((int64_t)a * b); }
};

// --8<-- [end:barrett]
#endif

// --8<-- [start:montgomery]
// Montgomery modular multiplication.
// The modulus m must be odd. The constant r is 2^32.
class Montgomery {
  int32_t m;
  uint32_t mm, r2;

 public:
  Montgomery(int32_t m) : m(m), mm(1), r2(-m) {
    // Compute mm as inv(m) mod r.
    for (int i = 0; i < 5; ++i) {
      mm *= 2 - mm * m;
    }
    // Compute r2 as r * r mod m.
    // If allowed to use modular operation for uint64_t, simply use:
    //   r2 = (uint64_t)(-m) % m;
    r2 %= m;
    r2 <<= 1;
    if (r2 >= (uint32_t)m) r2 -= m;
    for (int i = 0; i < 5; ++i) {
      r2 = mul(r2, r2);
    }
  }

  // Montgomery reduction: x * inv(r) % m.
  // Also used to transform x from Montgomery space to the normal space.
  int32_t reduce(int64_t x) {
    uint32_t u = (uint32_t)x * mm;
    int32_t ans = (x - (int64_t)m * u) >> 32;
    return ans < 0 ? ans + m : ans;
  }

  // Multiplication in Montgomery space: x * y * inv(r) % m.
  int32_t mul(int32_t x, int32_t y) { return reduce((int64_t)x * y); }

  // Transform x from the normal space to Montgomery space.
  int32_t init(int32_t x) { return mul(x, r2); }
};

// --8<-- [end:montgomery]
int main() {
  int t;
  std::cin >> t;
  for (; t; --t) {
    int n, m;
    std::cin >> n >> m;
    int ans0 = 1;
    for (int i = 1; i <= n; ++i) {
      ans0 = (long long)ans0 * i % m;
    }
#if HAS_WORKING_INT128
    Barrett barrett(m);
    int ans1 = 1;
    for (int i = 1; i <= n; ++i) {
      ans1 = barrett.mul(ans1, i);
    }
#else
    // skip the check if no int128_t is available.
    int ans1 = ans0;
#endif
    Montgomery montgomery(m);
    int ans2 = montgomery.init(1);
    for (int i = 1; i <= n; ++i) {
      ans2 = montgomery.mul(ans2, montgomery.init(i));
    }
    ans2 = montgomery.reduce(ans2);
    std::cout << (ans0 == ans1) << (ans0 == ans2) << '\n';
  }
  return 0;
}
