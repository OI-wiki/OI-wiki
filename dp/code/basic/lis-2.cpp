#include <algorithm>
#include <cstring>
#include <iostream>

constexpr int MAXN = 100;
// --8<-- [start:core]
int n, a[MAXN], d[MAXN], di[MAXN], pre[MAXN], res[MAXN];

int dp() {
  int ans = 0;
  for (int i = 1; i <= n; ++i) {
    int tmp = std::upper_bound(d, d + ans, a[i]) - d;
    pre[i] = tmp ? di[tmp - 1] : -1;
    d[tmp] = a[i];
    di[tmp] = i;
    if (tmp == ans) ++ans;
  }
  // Construct the subsequence.
  for (int k = ans, i = di[ans - 1]; k; --k) {
    res[k] = a[i];
    i = pre[i];
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
    int ans = dp();
    std::cout << ans << std::endl;
    for (int i = 1; i <= ans; ++i) {
      std::cout << res[i] << " \n"[i == ans];
    }
  }
}
