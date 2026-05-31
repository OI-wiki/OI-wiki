#include <iostream>

// --8<-- [start:core]
// Binary exponentiation.
long long pow(long long a, long long b, long long m) {
  long long res = 1, po = a;
  for (; b; b >>= 1) {
    if (b & 1) res = res * po % m;
    po = po * po % m;
  }
  return res;
}

// Returns the modular inverse of a prime modulo p.
long long inverse(long long a, long long p) { return pow(a, p - 2, p); }

// --8<-- [end:core]
int main() {
  long long t;
  std::cin >> t;
  for (; t; --t) {
    long long a, p;
    std::cin >> a >> p;
    std::cout << inverse(a, p) << std::endl;
  }
}
