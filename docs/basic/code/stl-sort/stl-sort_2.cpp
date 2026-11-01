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
  int* nth = first + k;
  // --8<-- [start:core]
  std::nth_element(first, nth, last);
  std::nth_element(first, nth, last, cmp);
  // --8<-- [end:core]
  std::cout << *nth << "\n";
}
