#include "newton_3.h"

#include <iostream>
#include <string>

// --8<-- [start:core]
BigInteger isqrtNewton(const BigInteger& n) {
  if (n.signum() == 0) return BigInteger(0);
  BigInteger a = BigInteger(1).shiftLeft(n.bitLength() / 2);
  bool p_dec = false;
  for (;;) {
    BigInteger b = n.divide(a).add(a).shiftRight(1);
    if (a.compareTo(b) == 0 || (a.compareTo(b) < 0 && p_dec)) break;
    p_dec = a.compareTo(b) > 0;
    a = b;
  }
  return a;
}

// --8<-- [end:core]

int main() {
  std::string n;
  std::cin >> n;
  std::cout << isqrtNewton(BigInteger(n)).toString() << '\n';
}
