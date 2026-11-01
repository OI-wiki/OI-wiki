#include <iostream>
#include <vector>

int n;
std::vector<int> a;

// --8<-- [start:core]
int binary_search(int x, int l = 1, int r = n) {  // 在升序数组中查找数 x 的下标
  int ret = -1;                                   // 未找到时返回 -1
  while (l <= r) {
    int mid = (l + r) >> 1;  // l + r 可能溢出，详见下方 Note
    if (a[mid] < x)
      l = mid + 1;
    else if (a[mid] > x)
      r = mid - 1;
    else {  // 最后检测相等是因为多数搜索情况不是大于就是小于
      ret = mid;
      break;
    }
  }
  return ret;
}

// --8<-- [end:core]

int main() {
  std::cin >> n;
  a.resize(n + 1);
  for (int i = 1; i <= n; ++i) std::cin >> a[i];
  int q;
  std::cin >> q;
  while (q--) {
    int x;
    std::cin >> x;
    std::cout << binary_search(x) << "\n";
  }
}
