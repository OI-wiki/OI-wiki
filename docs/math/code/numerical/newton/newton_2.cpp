#include <iostream>

// --8<-- [start:core]
int isqrt_newton(int n) {
  if (n == 0) return 0;
  int x = 1;
  bool decreased = false;
  for (;;) {
    int nx = (1LL * x + n / x) >> 1;
    if (x == nx || (nx > x && decreased)) break;
    decreased = nx < x;
    x = nx;
  }
  return x;
}

// --8<-- [end:core]
int main() {
  int n;
  std::cin >> n;
  std::cout << isqrt_newton(n) << "\n";
}
