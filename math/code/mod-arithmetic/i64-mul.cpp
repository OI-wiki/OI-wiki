#include <cfloat>
#include <iostream>

// Check whether a working __int128 type is available.
// Clang-cl on Windows may fail to link when using mod/div with __int128.
#if defined(__SIZEOF_INT128__) && !(defined(__clang__) && defined(_MSC_VER))
#define HAS_WORKING_INT128 1
#else
#define HAS_WORKING_INT128 0
#endif

namespace LongDoubleMul {

#if LDBL_MANT_DIG >= 64  // Test this only if long double has at least 80 bits.

// --8<-- [start:ld-mul]
long long mul(long long a, long long b, long long m) {
  long long c = (unsigned long long)a * b -
                (unsigned long long)((long double)a / m * b + 0.5L) * m;
  return c < 0 ? c + m : c;
}

// --8<-- [end:ld-mul]
#else

long long mul(long long a, long long b, long long m) { return -1; }

#endif

};  // namespace LongDoubleMul

namespace Int128Mul {

#if HAS_WORKING_INT128  // Test this only if __int128 is available.

// --8<-- [start:i128-mul]
long long mul(long long a, long long b, long long m) {
  return (__int128)a * b % m;
}

// --8<-- [end:i128-mul]
#else

long long mul(long long a, long long b, long long m) { return -1; }

#endif

};  // namespace Int128Mul

bool check(long long output, long long answer) {
  return output == -1 || output == answer;
}

int main() {
  int t;
  std::cin >> t;
  for (; t; --t) {
    long long a, b, m, c;
    std::cin >> a >> b >> m >> c;
    std::cout << check(LongDoubleMul::mul(a, b, m), c)
              << check(Int128Mul::mul(a, b, m), c) << '\n';
  }
  return 0;
}
