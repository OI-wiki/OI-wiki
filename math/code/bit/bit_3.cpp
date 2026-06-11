#include <iostream>

namespace main1 {
void main(int x) {
  // --8<-- [start:hamming1]
  int t = x + (x & -x);
  x = t | ((((t & -t) / (x & -x)) >> 1) - 1);
  // --8<-- [end:hamming1]
  std::cout << x << '\n';
}
}  // namespace main1

namespace main2 {
void main(int n) {
  // --8<-- [start:hamming2_begin]
  for (int i = 0; (1 << i) - 1 <= n; i++) {
    for (int x = (1 << i) - 1, t; x <= n; t = x + (x & -x),
             x = x ? (t | ((((t & -t) / (x & -x)) >> 1) - 1)) : (n + 1)) {
      // 写下需要完成的操作
      // --8<-- [end:hamming2_begin]
      std::cout << x << ' ';
      // --8<-- [start:hamming2_end]
    }
  }
  // --8<-- [end:hamming2_end]
}
}  // namespace main2

int main() {
  int x, n;
  std::cin >> x >> n;

  main1::main(x);
  main2::main(n);

  std::cout << std::endl;

  return 0;
}
