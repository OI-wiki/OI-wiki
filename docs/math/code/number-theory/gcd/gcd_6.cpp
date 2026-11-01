#include <algorithm>
#include <cassert>
#include <cstdint>
#include <iostream>
#include <tuple>
#include <vector>
using namespace std;

// --8<-- [start:core]
int exgcd(int a, int b, int &x, int &y) {
  int x1 = 1, x2 = 0, x3 = 0, x4 = 1;
  while (b != 0) {
    int c = a / b;
    std::tie(x1, x2, x3, x4, a, b) =
        std::make_tuple(x3, x4, x1 - x3 * c, x2 - x4 * c, b, a - b * c);
  }
  x = x1, y = x2;
  return a;
}

// --8<-- [end:core]
int main() {
  int a, b;
  if (!(cin >> a >> b)) return 0;
  int x, y;
  int d = exgcd(a, b, x, y);
  assert(1LL * a * x + 1LL * b * y == d);
  cout << d << "\n";
}
