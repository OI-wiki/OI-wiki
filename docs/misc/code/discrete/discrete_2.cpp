#include <algorithm>
#include <iostream>
#include <vector>

// Demonstration fixture: repeated values, negative value, and stable tie order.
int main() {
  int n;
  if (!(std::cin >> n)) return 0;
  std::vector<int> arr(n);
  for (int& value : arr) std::cin >> value;
  // --8<-- [start:core]
  // std::vector<int> arr;
  std::vector<int> tmp(arr);  // tmp 是 arr 的一个副本
  std::sort(tmp.begin(), tmp.end());
  tmp.erase(std::unique(tmp.begin(), tmp.end()), tmp.end());
  for (int i = 0; i < n; ++i)
    arr[i] = std::lower_bound(tmp.begin(), tmp.end(), arr[i]) - tmp.begin();
  // --8<-- [end:core]
  for (int i = 0; i < n; ++i) {
    if (i) std::cout << ' ';
    std::cout << arr[i];
  }
  std::cout << '\n';
}
