#include <algorithm>
#include <cstring>
#include <iostream>
#include <tuple>
#include <vector>

int main() {
  int n, m;
  std::cin >> n >> m;
  std::vector<int> a(n + 1);
  for (int i = 1; i <= n; ++i) std::cin >> a[i];
  // Calculate h(k) = max_x f(x) - k * g(x).
  // Meanwhile, obtain the maximum value g(x) of the optimizer x.
  auto calc = [&](int k) -> std::pair<long long, int> {
    long long dp[2] = {0, -0x3f3f3f3f3f3f3f3f};
    int opt[2] = {0, 0};
    for (int i = 1; i <= n; ++i) {
      long long tmp_dp[2];
      int tmp_opt[2];
      if (dp[0] > dp[1]) {
        tmp_dp[0] = dp[0];
        tmp_opt[0] = opt[0];
      } else if (dp[1] > dp[0]) {
        tmp_dp[0] = dp[1];
        tmp_opt[0] = opt[1];
      } else {
        tmp_dp[0] = dp[0];
        tmp_opt[0] = std::max(opt[0], opt[1]);
      }
      tmp_dp[1] = dp[0] + a[i] - k;
      tmp_opt[1] = opt[0] + 1;
      std::memcpy(dp, tmp_dp, sizeof(dp));
      std::memcpy(opt, tmp_opt, sizeof(opt));
    }
    long long val;
    int opt_m;
    if (dp[0] > dp[1]) {
      val = dp[0];
      opt_m = opt[0];
    } else if (dp[1] > dp[0]) {
      val = dp[1];
      opt_m = opt[1];
    } else {
      val = dp[0];
      opt_m = std::max(opt[0], opt[1]);
    }
    return {val, opt_m};
  };
  // WQS binary search.
  long long val, tar_val;
  int opt_m, tar_k;
  std::tie(val, opt_m) = calc(0);
  if (opt_m <= m) {
    // Have already reached the peak.
    tar_k = 0;
    tar_val = val;
  } else {
    // Find the maximum k such that g(x) >= m.
    int ll = 0, rr = 1000000;
    while (ll <= rr) {
      int mm = (ll + rr) / 2;
      std::tie(val, opt_m) = calc(mm);
      if (opt_m >= m) {
        tar_k = mm;
        tar_val = val;
        ll = mm + 1;
      } else {
        rr = mm - 1;
      }
    }
  }
  long long res = tar_val + (long long)tar_k * m;
  std::cout << res << std::endl;
  return 0;
}
