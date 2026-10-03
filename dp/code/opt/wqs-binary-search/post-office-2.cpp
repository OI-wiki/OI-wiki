#include <cmath>
#include <deque>
#include <iostream>
#include <type_traits>
#include <utility>
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

// Golden section search on integer domain (unimodal function)
template <typename T, typename F>
typename std::enable_if<
    std::is_integral<T>::value,
    std::pair<T, decltype(std::declval<F>()(std::declval<T>()))>>::type
golden_section_search(T ll, T rr, F func) {
  constexpr long double phi = 0.618033988749894848204586834L;
  T ml = ll + static_cast<T>((rr - ll) * (1 - phi));
  T mr = ll + static_cast<T>((rr - ll) * phi);
  auto fl = func(ml), fr = func(mr);
  while (ml < mr) {
    if (fl > fr) {
      rr = mr;
      mr = ml;
      fr = fl;
      ml = ll + static_cast<T>((rr - ll) * (1 - phi));
      fl = func(ml);
    } else {
      ll = ml;
      ml = mr;
      fl = fr;
      mr = ll + static_cast<T>((rr - ll) * phi);
      fr = func(mr);
    }
  }
  T best_x = ll;
  auto best_val = func(ll);
  for (T i = ll + 1; i <= rr; ++i) {
    auto val = func(i);
    if (val > best_val) {
      best_val = val;
      best_x = i;
    }
  }
  return {best_x, best_val};
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
  auto solve = [&](long long k) -> long long {
    return monotone_decision_opt_dp(
               n, [&](int j, int i) -> long long { return w(j, i) - k; })
               .first[n] +
           k * m;
  };
  // Solve the dual problem to find v(m).
  auto res = golden_section_search(-(1LL << 32), 0LL, solve).second;
  std::cout << res << std::endl;
  return 0;
}
