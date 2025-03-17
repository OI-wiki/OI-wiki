#include <iostream>
#include <tuple>
#include <vector>

// Locate a given fraction in the Stern-Brocot tree.
auto find(int x, int y) {
  std::vector<std::pair<int, char>> res;
  int a = 0, b = 1, c = 1, d = 0;
  bool right = true;
  while (x != a + c || y != b + d) {
    if (right) {
      auto t = (b * x - a * y - 1) / (y * c - x * d);
      res.emplace_back(t, 'R');
      a += t * c;
      b += t * d;
    } else {
      auto t = (y * c - x * d - 1) / (b * x - a * y);
      res.emplace_back(t, 'L');
      c += t * a;
      d += t * b;
    }
    right ^= 1;
  }
  return res;
}

int main() {
  int x, y;
  std::cin >> x >> y;
  for (auto cr : find(x, y)) {
    for (; cr.first; --cr.first) {
      std::cout << cr.second;
    }
  }
  return 0;
}
