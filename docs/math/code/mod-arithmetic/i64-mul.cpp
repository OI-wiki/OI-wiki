#include <iostream>
#include <cfloat>

namespace LongDoubleMul {

#if LDBL_MANT_DIG >= 64 // Test this only if long double has at least 80 bits.

// --8<-- [start:ld-mul]
long long mul(long long a, long long b, long long m) {
  long long c =
    (unsigned long long)a * b -
    (unsigned long long)((long double)a / m * b + 0.5L) * m;
  return c < 0 ? c + m : c;
}

// --8<-- [end:ld-mul]
#else

long long mul(long long a, long long b, long long m) {
  return -1;
}

#endif

};

namespace Int128Mul {

#if defined(__SIZEOF_INT128__) // Test this only if __int128 is available.

// --8<-- [start:i128-mul]
long long mul(long long a, long long b, long long m) {
  return (__int128)a * b % m;
}

// --8<-- [end:i128-mul]
#else

long long mul(long long a, long long b, long long m) {
  return -1;
}

#endif

};

bool check(long long output, long long answer) {
  return output == -1 || output == answer;
}

int main() {
  int t;
  std::cin >> t;
  for (; t; --t) {
    long long a, b, m, c;
    std::cin >> a >> b >> m >> c;
    std::cout
      << check(LongDoubleMul::mul(a, b, m), c)
      << check(Int128Mul::mul(a, b, m), c)
      << '\n';
  }
  return 0;
}
