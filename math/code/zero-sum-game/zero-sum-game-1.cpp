#include <algorithm>
#include <iostream>
#include <vector>

int main() {
  int n;
  std::cin >> n;
  std::vector<int> a(n);
  for (int& x : a) std::cin >> x;
  std::vector<int> ans(n), tmp;
  tmp = a;
  for (int i = 0; i < n - 1; ++i) {
    tmp[i] = std::max(tmp[i], tmp[i + 1]);
  }
  for (int l = n / 2 - 1, r = (n - 1) / 2, ma = 0; l >= 0; --l, ++r) {
    ma = std::max({ma, tmp[l], tmp[r]});
    ans[r - l] = ma;
  }
  tmp = a;
  for (int i = 0; i < n - 1; ++i) {
    tmp[i] = std::min(tmp[i], tmp[i + 1]);
  }
  for (int i = 0; i < n - 2; ++i) {
    tmp[i] = std::max(tmp[i], tmp[i + 1]);
  }
  for (int l = (n - 3) / 2, r = n / 2 - 1, ma = 0; l >= 0; --l, ++r) {
    ma = std::max({ma, tmp[l], tmp[r]});
    ans[r - l] = ma;
  }
  ans[n - 1] = *std::max_element(a.begin(), a.end());
  for (auto x : ans) std::cout << x << ' ';
  std::cout << std::endl;
  return 0;
}
