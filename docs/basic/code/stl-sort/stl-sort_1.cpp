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
  auto cmp = std::less<int>();
  // --8<-- [start:core]
  // a[0] .. a[n - 1] 为需要排序的数列
  // 对 a 原地排序，将其按从小到大的顺序排列
  std::sort(a, a + n);

  // cmp 为自定义的比较函数
  std::sort(a, a + n, cmp);
  // --8<-- [end:core]
  for (int i = 0; i < n; ++i) std::cout << (i ? " " : "") << a[i];
  std::cout << "\n";
}
