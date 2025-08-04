#include <algorithm>
#include <iostream>
#include <tuple>
#include <type_traits>
#include <vector>

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
  std::vector<int> a(n + 1);
  for (int i = 1; i <= n; ++i) std::cin >> a[i];
  // Calculate h(k) = max_x f(x) + k * g(x).
  auto calc = [&](int k) -> long long {
    long long dp[2] = {0, -0x3f3f3f3f3f3f3f3f};
    for (int i = 1; i <= n; ++i) {
      std::tie(dp[0], dp[1]) =
          std::make_pair(std::max(dp[0], dp[1]), dp[0] + a[i] + k);
    }
    return std::max(dp[0], dp[1]);
  };
  // Solve the dual problem to find v(m).
  // Implemented as a minimization problem by adding negative signs.
  // Only consider tangent lines of negative slopes to ignore the part
  //     of the curve after the peak.
  auto res = -golden_section_search(-1000000, 0, [&](int k) -> long long {
                return -calc(k) + (long long)k * m;
              }).second;
  std::cout << res << std::endl;
  return 0;
}
