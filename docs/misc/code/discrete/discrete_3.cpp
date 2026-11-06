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

  // --8<-- [start:core]
  struct Data {
    int idx, val;

    bool operator<(const Data& o) const {
      if (val == o.val)
        return idx < o.idx;  // 当值相同时，先出现的元素离散化后的值更小
      return val < o.val;
    }
  };  // 也可以使用 std::pair

  std::vector<Data> tmp(n + 1);

  for (int i = 1; i <= n; ++i) tmp[i] = Data{i, arr[i]};
  std::sort(tmp.begin() + 1, tmp.end());
  for (int i = 1; i <= n; ++i) arr[tmp[i].idx] = i;
  // --8<-- [end:core]
  for (int i = 1; i <= n; ++i) {
    if (i > 1) std::cout << ' ';
    std::cout << arr[i];
  }
  std::cout << '\n';
}
