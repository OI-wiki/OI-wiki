#include <iostream>

// In-Order Transversal of Stern-Brocot Tree till Layer N.
void build(int n, int a = 0, int b = 1, int c = 1, int d = 0, int level = 1) {
  if (level > n) return;  // Only first n layers.
  int x = a + c, y = b + d;
  build(n, a, b, x, y, level + 1);
  std::cout << x << '/' << y << ' ';  // Output the current fraction.
  build(n, x, y, c, d, level + 1);
}

int main() {
  int n;
  std::cin >> n;
  build(n);
  std::cout << '\n';
  return 0;
}
