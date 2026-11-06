#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>

int main() {
  int n;
  std::cin >> n;
  std::vector<int> values(n);
  for (int& x : values) std::cin >> x;
  int* a = values.data();
  int* first = a;
  int* last = a + n;
  auto cmp = std::less<int>();
  // --8<-- [start:core]
  std::stable_sort(first, last);
  std::stable_sort(first, last, cmp);
  // --8<-- [end:core]
  for (int i = 0; i < n; ++i) std::cout << (i ? " " : "") << a[i];
  std::cout << "\n";
}
