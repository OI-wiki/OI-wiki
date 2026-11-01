#include <iostream>
#include <vector>

int main() {
  int n;
  std::cin >> n;
  std::vector<int> a(n);
  for (int& x : a) std::cin >> x;
  int ans = 0;
  // --8<-- [start:core]
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < n; ++j)
      if (a[i] + a[j] == 0) ++ans;
  // --8<-- [end:core]
  std::cout << ans << "\n";
}
