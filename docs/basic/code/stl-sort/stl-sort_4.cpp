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
  int k;
  std::cin >> k;
  int* mid = first + k;
  // --8<-- [start:core]
  // mid = first + k
  std::partial_sort(first, mid, last);
  std::partial_sort(first, mid, last, cmp);
  // --8<-- [end:core]
  for (int i = 0; i < k; ++i) std::cout << (i ? " " : "") << a[i];
  std::cout << "\n";
}
