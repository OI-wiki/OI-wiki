#include <cstdint>
#include <iostream>
#if defined(_MSC_VER) && !defined(__clang__)
#include <immintrin.h>
#define __builtin_ctz _tzcnt_u32
#endif

namespace UInt32Test {
// Compute x*a^b mod 2^32.
uint32_t pow_mod_2_32(uint32_t a, uint32_t b, uint32_t x) {
  uint32_t ans = x;
  for (uint32_t po = a; b; b >>= 1) {
    if (b & 1) ans *= po;
    po *= po;
  }
  return ans;
}

// Compute 1/v mod 2^32 for odd v.
uint32_t inv_mod_2_32(uint32_t v) { return pow_mod_2_32(v, (1 << 30) - 1, 1); }
};  // namespace UInt32Test

namespace UInt32 {
// --8<-- [start:inv]
// Compute 1/v mod 2^32 for odd v.
uint32_t inv_mod_2_32(uint32_t v) {
  uint32_t x = 1;
  for (int i = 0; i != 5; ++i) {
    x *= 2 - v * x;
  }
  return x;
}

// --8<-- [end:inv]
// --8<-- [start:pow]
// Store 4L(a) for a = 2^d + 1, where L(a) is disc. log. base 388251981.
// The first two values are never used and thus set to zero.
// The base is chosen such that 4L(2^16+1) = 2^16.
constexpr uint32_t log_table[16] = {
    0x00000000, 0x00000000, 0xbba0267c, 0x49b9d1e8, 0xf0026f90, 0xd6e17e20,
    0xe78bf840, 0x039fe080, 0xaf7f8100, 0x60fe0200, 0xd1f80400, 0x23e00800,
    0x47801000, 0x8e002000, 0x18004000, 0x20008000,
};

// Compute 4L(v).
uint32_t log_mod_2_32(uint32_t x, uint32_t v) {
  for (int i = 2; i != 16; ++i) {
    if ((v >> i) & 1) {
      v += v << i;
      x -= log_table[i];
    }
  }
  x += v ^ 1;
  return x;
}

// Compute x*a for 4L(a) = v.
uint32_t exp_mod_2_32(uint32_t x, uint32_t v) {
  for (int i = 2; i != 16; ++i) {
    if ((v >> i) & 1) {
      x += x << i;
      v -= log_table[i];
    }
  }
  x *= v ^ 1;
  return x;
}

// Compute x*a^b for odd a.
uint32_t pow_odd_mod_2_32(uint32_t a, uint32_t b, uint32_t x) {
  if (a & 2) {
    a = -a;
    if (b & 1) {
      x = -x;
    }
  }
  return exp_mod_2_32(x, log_mod_2_32(0, a) * b);
}

// Compute x*a^b mod 2^32.
uint32_t pow_mod_2_32(uint32_t a, uint32_t b, uint32_t x = 1) {
  if (!a) return b == 0 ? x : 0;
  auto d = __builtin_ctz(a);
  if ((uint64_t)d * b >= 32) return 0;
  return pow_odd_mod_2_32(a >> d, b, x) << (d * b);
}

// --8<-- [end:pow]
};  // namespace UInt32

int main() {
  int t;
  std::cin >> t;
  for (; t; --t) {
    char op;
    std::cin >> op;
    switch (op) {
      case 'I': {
        uint32_t x;
        std::cin >> x;
        std::cout << (UInt32::inv_mod_2_32(x) == UInt32Test::inv_mod_2_32(x))
                  << '\n';
        break;
      }
      case 'E': {
        uint32_t x, a, b;
        std::cin >> x >> a >> b;
        std::cout << (UInt32::pow_mod_2_32(a, b, x) ==
                      UInt32Test::pow_mod_2_32(a, b, x))
                  << '\n';
        break;
      }
    }
  }
  return 0;
}
