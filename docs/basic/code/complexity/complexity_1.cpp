#include <iostream>

int main() {
  // --8<-- [start:core]
  int n, m;
  std::cin >> n >> m;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      for (int k = 0; k < m; ++k) {
        std::cout << "hello world\n";
      }
    }
  }
  // --8<-- [end:core]
}
