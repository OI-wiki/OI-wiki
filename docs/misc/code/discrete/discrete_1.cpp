#include <algorithm>
#include <iostream>
#include <vector>

// Demonstration fixture: repeated values, negative value, and stable tie order.
int main() {
  int n;
  if (!(std::cin >> n)) return 0;
  std::vector<int> storage(n + 1);
  int* arr = storage.data();
  for (int i = 1; i <= n; ++i) std::cin >> arr[i];
  std::vector<int> temporary(n + 1);
  int* tmp = temporary.data();
  // --8<-- [start:core]
  // arr[i] 为初始数组,下标范围为 [1, n]

  for (int i = 1; i <= n; ++i)  // step 1
    tmp[i] = arr[i];
  std::sort(tmp + 1, tmp + n + 1);                          // step 2
  int len = std::unique(tmp + 1, tmp + n + 1) - (tmp + 1);  // step 3
  for (int i = 1; i <= n; ++i)                              // step 4
    arr[i] = std::lower_bound(tmp + 1, tmp + len + 1, arr[i]) - tmp;
  // --8<-- [end:core]
  for (int i = 1; i <= n; ++i) {
    if (i > 1) std::cout << ' ';
    std::cout << arr[i];
  }
  std::cout << '\n';
}
