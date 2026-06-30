#include <iostream>
#include <vector>

int g(int i, int j) {
  return i % 2 == 0 && j % 2 == 0 ? 0 : g(i / 2, j / 2) + 1;
}

int f(int i, int j) { return g(i - 1, j - 1); }

int main() {
  int t;
  std::cin >> t;
  for (; t; --t) {
    int n;
    std::cin >> n;
    int v = 0;
    for (int i = 0; i < n / 2; ++i) {
      int x, y;
      std::cin >> x >> y;
      v ^= f(x, y);
    }
    std::cout << (v ? "YES" : "NO") << '\n';
  }
  return 0;
}
