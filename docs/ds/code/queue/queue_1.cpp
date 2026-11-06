#include <iostream>
constexpr int SIZE = 100005;
// --8<-- [start:example134]
int q[SIZE], ql = 1, qr;

// --8<-- [end:example134]

int main() {
  int n;
  std::cin >> n;
  for (int j = 0, value; j < n; ++j) {
    std::cin >> value;
    q[++qr] = value;
  }
  while (ql <= qr) {
    if (ql != 1) std::cout << ' ';
    std::cout << q[ql++];
  }
  std::cout << '\n';
}
