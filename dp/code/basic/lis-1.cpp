#include <algorithm>
#include <iostream>

constexpr int MAXN = 100;
// --8<-- [start:core]
int n, a[MAXN], d[MAXN];

int dp() {
  d[1] = 1;
  int ans = 1;
  for (int i = 2; i <= n; i++) {
    d[i] = 1;
    for (int j = 1; j < i; j++)
      if (a[j] <= a[i]) {
        d[i] = std::max(d[i], d[j] + 1);
        ans = std::max(ans, d[i]);
      }
  }
  return ans;
}

// --8<-- [end:core]
int main() {
  int t;
  std::cin >> t;
  while (t--) {
    std::cin >> n;
    for (int i = 1; i <= n; i++) std::cin >> a[i];
    std::cout << dp() << std::endl;
  }
}
