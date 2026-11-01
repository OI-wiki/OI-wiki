#include <algorithm>
#include <cassert>
#include <cstdint>
#include <iostream>
#include <tuple>
#include <vector>
using namespace std;

// --8<-- [start:core]
int Exgcd(int a, int b, int &x, int &y) {
  if (!b) {
    x = 1;
    y = 0;
    return a;
  }
  int d = Exgcd(b, a % b, x, y);
  int t = x;
  x = y;
  y = t - (a / b) * y;
  return d;
}

// --8<-- [end:core]
int main() {
  int a, b;
  if (!(cin >> a >> b)) return 0;
  int x, y;
  int d = Exgcd(a, b, x, y);
  assert(1LL * a * x + 1LL * b * y == d);
  cout << d << "\n";
}
