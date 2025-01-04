#include <iostream>
#include <string>

// Locate a given fraction in the Stern-Brocot tree.
std::string find(int x, int y, int a = 0, int b = 1, int c = 1, int d = 0) {
  int m = a + c, n = b + d;
  if (x == m && y == n) return "";
  if (x * n < y * m) {
    return 'L' + find(x, y, a, b, m, n);
  } else {
    return 'R' + find(x, y, m, n, c, d);
  }
}

int main() {
  int x, y;
  std::cin >> x >> y;
  std::cout << find(x, y);
  return 0;
}
