#include <algorithm>
#include <cassert>
#include <cstdint>
#include <iostream>
#include <tuple>
#include <vector>
using namespace std;

// --8<-- [start:core]
int gcd(int a, int b) {
  while (b != 0) {
    int tmp = a;
    a = b;
    b = tmp % b;
  }
  return a;
}

// --8<-- [end:core]
int main() {
  int a, b;
  if (!(cin >> a >> b)) return 0;
  int d = gcd(a, b);
  cout << d << "\n";
}
