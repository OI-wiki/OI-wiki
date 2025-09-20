#include <iostream>
#include <tuple>
#include <vector>

// --8<-- [start:core]
// Locate a given fraction in the Stern-Brocot tree.
auto find(int x, int y) {
  std::vector<std::pair<int, char>> res;
  bool right = true;
  while (y) {
    res.emplace_back(x / y, right ? 'R' : 'L');
    x %= y;
    std::swap(x, y);
    right ^= 1;
  }
  --res.back().first;
  return res;
}

// --8<-- [end:core]
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
