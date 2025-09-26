#include <iostream>

// --8<-- [start:core]
int mu(int n) {
  int res = 1;
  for (int i = 2; i * i <= n; ++i) {
    if (n % i == 0) {
      n /= i;
      // Check if square-free.
      if (n % i == 0) return 0;
      res = -res;
    }
  }
  // The remaining factor must be prime.
  if (n > 1) res = -res;
  return res;
}

// --8<-- [end:core]
int main() {
  int n;
  std::cin >> n;
  for (int i = 1; i <= n; ++i) {
    std::cout << mu(i) << '\n';
  }
  return 0;
}
