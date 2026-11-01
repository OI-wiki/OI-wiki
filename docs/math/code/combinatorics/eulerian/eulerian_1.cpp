#include <iostream>

// --8<-- [start:core]
int eulerianNumber(int n, int m) {
  if (m >= n || n == 0) return 0;
  if (m == 0) return 1;
  return (((n - m) * eulerianNumber(n - 1, m - 1)) +
          ((m + 1) * eulerianNumber(n - 1, m)));
}

// --8<-- [end:core]
int main() {
  int n, m;
  std::cin >> n >> m;
  std::cout << eulerianNumber(n, m) << "\n";
}
