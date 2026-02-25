#include <iostream>

// --8<-- [start:core]
// Farey Sequence of Order N.
void build(int n, int a = 0, int b = 1, int c = 1, int d = 1,
           bool init = true) {
  int x = a + c, y = b + d;
  if (y > n) return;              // Only first n layers.
  if (init) std::cout << "0/1 ";  // Output 0/1;
  build(n, a, b, x, y, false);
  std::cout << x << '/' << y << ' ';  // Output the current fraction.
  build(n, x, y, c, d, false);
  if (init) std::cout << "1/1 ";  // Output 1/1;
}

// --8<-- [end:core]
int main() {
  int n;
  std::cin >> n;
  build(n);
  std::cout << '\n';
  return 0;
}
