#include <iostream>

// Input: n people and step k; output uses the article's zero-based numbering.
// --8<-- [start:core]
int josephus(int n, int k) {
  int res = 0;
  for (int i = 1; i <= n; ++i) res = (res + k) % i;
  return res;
}

// --8<-- [end:core]

int main() {
  int n, k;
  while (std::cin >> n >> k) std::cout << josephus(n, k) << '\n';
}
