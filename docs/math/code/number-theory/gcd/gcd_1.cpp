#include <algorithm>
#include <cassert>
#include <cstdint>
#include <iostream>
#include <tuple>
#include <vector>
using namespace std;

namespace version1 {
// --8<-- [start:core-first]
// Version 1
int gcd(int a, int b) {
  if (b == 0) return a;
  return gcd(b, a % b);
}

// --8<-- [end:core-first]
}  // namespace version1

namespace version2 {
// --8<-- [start:core-second]
// Version 2
int gcd(int a, int b) { return b == 0 ? a : gcd(b, a % b); }

// --8<-- [end:core-second]
}  // namespace version2

int main() {
  int a, b;
  if (!(cin >> a >> b)) return 0;
  int d = version1::gcd(a, b);
  assert(d == version2::gcd(a, b));
  cout << d << "\n";
}
