#include <algorithm>
#include <cassert>
#include <cstdint>
#include <iostream>
#include <tuple>
#include <vector>
using namespace std;

// --8<-- [start:core]
int gcd(int a, int b, int& x, int& y) {
  x = 1, y = 0;
  int x1 = 0, y1 = 1, a1 = a, b1 = b;
  while (b1) {
    int q = a1 / b1;
    tie(x, x1) = make_tuple(x1, x - q * x1);
    tie(y, y1) = make_tuple(y1, y - q * y1);
    tie(a1, b1) = make_tuple(b1, a1 - q * b1);
  }
  return a1;
}

// --8<-- [end:core]
int main() {
  int a, b;
  if (!(cin >> a >> b)) return 0;
  int x, y;
  int d = gcd(a, b, x, y);
  assert(1LL * a * x + 1LL * b * y == d);
  cout << d << "\n";
}
