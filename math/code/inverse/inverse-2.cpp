#include <iostream>

// --8<-- [start:core]
// Binary exponentiation.
int pow(int a, int b, int m) {
  long long res = 1, po = a;
  for (; b; b >>= 1) {
    if (b & 1) res = res * po % m;
    po = po * po % m;
  }
  return res;
}

// Returns the modular inverse of a prime modulo p.
int inverse(int a, int p) { return pow(a, p - 2, p); }

// --8<-- [end:core]
int main() {
  int t;
  std::cin >> t;
  for (; t; --t) {
    int a, p;
    std::cin >> a >> p;
    std::cout << inverse(a, p) << std::endl;
  }
}
