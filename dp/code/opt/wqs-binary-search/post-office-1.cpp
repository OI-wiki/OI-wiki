#include <cmath>
#include <deque>
#include <iostream>
#include <tuple>
#include <type_traits>
#include <vector>

// Monotone decision DP.
// This solves f(i) = min f(j-1) + w(j,i) s.t. 1 <= j <= i.
// Also records the minimal optimal decision j for each f(i).
template <typename W>
std::pair<std::vector<decltype(std::declval<W>()(0, 0))>, std::vector<int>>
monotone_decision_opt_dp(int n, W ww) {
  using ValueT = decltype(std::declval<W>()(0, 0));
  std::vector<ValueT> f(n + 1);
  std::vector<int> opt(n + 1), lt(n + 1), rt(n + 1);
  std::deque<int> dq;
  auto w = [&](int j, int i) -> ValueT { return ww(j, i) + f[j - 1]; };
  for (int j = 1; j <= n; ++j) {
    if (!dq.empty() && rt[dq.front()] < j) dq.pop_front();
    if (!dq.empty()) lt[dq.front()] = j;
    while (!dq.empty() && w(j, lt[dq.back()]) < w(dq.back(), lt[dq.back()])) {
      dq.pop_back();
    }
    if (dq.empty()) {
      lt[j] = j;
      rt[j] = n;
      dq.emplace_back(j);
    } else if (w(j, rt[dq.back()]) >= w(dq.back(), rt[dq.back()])) {
      if (rt[dq.back()] < n) {
        lt[j] = rt[dq.back()] + 1;
        rt[j] = n;
        dq.emplace_back(j);
      }
    } else {
      int ll = lt[dq.back()], rr = rt[dq.back()], i = rr;
      while (ll <= rr) {
        int mm = (ll + rr) / 2;
        if (w(j, mm) < w(dq.back(), mm)) {
          i = mm;
          rr = mm - 1;
        } else {
          ll = mm + 1;
        }
      }
      rt[dq.back()] = i - 1;
      lt[j] = i;
      rt[j] = n;
      dq.emplace_back(j);
    }
    f[j] = w(dq.front(), j);
    opt[j] = dq.front();
  }
  return {f, opt};
}

int main() {
  int n, m;
  std::cin >> n >> m;
  std::vector<long long> a(n + 1), ps(n + 1);
  for (int i = 1; i <= n; ++i) {
    std::cin >> a[i];
    ps[i] = ps[i - 1] + a[i];
  }
  // Cost function for interval [l,r].
  auto w = [&](int j, int i) -> long long {
    int mm = j + (i - j) / 2;
    return ps[i] + ps[j - 1] - 2 * ps[mm] + (2 * mm - j - i + 1) * a[mm];
  };
  // Calculate h(k) = min_x f(x) - k * g(x).
  // Also record the minimum of optimal number of segments.
  auto calc = [&](long long k) -> std::pair<long long, int> {
    auto res = monotone_decision_opt_dp(
        n, [&](int j, int i) -> long long { return w(j, i) - k; });
    auto val = res.first[n];
    int cnt = 0;
    for (int i = n; i; i = res.second[i] - 1) {
      ++cnt;
    }
    return {val, cnt};
  };
  // WQS binary search.
  // Find the largest k such that g(x) <= m.
  long long val, tar_val;
  int opt_m, tar_k;
  long long ll = -(1LL << 32), rr = 0;
  while (ll <= rr) {
    long long mm = ll + (rr - ll) / 2;
    std::tie(val, opt_m) = calc(mm);
    if (opt_m <= m) {
      tar_val = val;
      tar_k = mm;
      ll = mm + 1;
    } else {
      rr = mm - 1;
    }
  }
  long long res = tar_val + (long long)tar_k * m;
  std::cout << res << std::endl;
  return 0;
}
