#include <algorithm>
#include <cmath>
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

// Golden section search on floating-point domain (unimodal function)
template <typename T, typename F>
typename std::enable_if<
    std::is_floating_point<T>::value,
    std::pair<T, decltype(std::declval<F>()(std::declval<T>()))>>::type
golden_section_search(T ll, T rr, F func, T eps) {
  constexpr long double phi = 0.618033988749894848204586834L;
  T ml = ll + (rr - ll) * (1 - phi);
  T mr = ll + (rr - ll) * phi;
  auto fl = func(ml), fr = func(mr);
  while ((rr - ll) > eps) {
    if (fl > fr) {
      rr = mr;
      mr = ml;
      fr = fl;
      ml = ll + (rr - ll) * (1 - phi);
      fl = func(ml);
    } else {
      ll = ml;
      ml = mr;
      fl = fr;
      mr = ll + (rr - ll) * phi;
      fr = func(mr);
    }
  }
  T mid = (ll + rr) / 2;
  return {mid, func(mid)};
}

int main() {
  int n;
  std::cin >> n;
  std::vector<int> a(n + 1);
  for (int i = 1; i <= n; ++i) std::cin >> a[i];
  for (int i = n; i >= 1; --i) a[i] -= a[i - 1];
  long long v;
  std::cin >> v;
  // Cost of adding M more teleporters to a segment of length LEN.
  auto f = [&](int len, int m) -> long long {
    long long rem = len % (m + 1);
    int q = len / (m + 1);
    return (m + 1 - rem) * q * q + rem * (q + 1) * (q + 1);
  };
  // Calculate h(k) = min_x f(x) - k * g(x).
  auto calc = [&](long double k) -> long double {
    long double res = 0;
    for (int i = 1; i <= n; ++i) {
      res += -golden_section_search(0, a[i], [&](int m) -> long double {
                return -m + k * f(a[i], m);
              }).second;
    }
    return res;
  };
  // Solve the dual problem.
  auto res =
      golden_section_search(
          -1.0l, 0.0l,
          [&](long double k) -> long double { return calc(k) + k * v; }, 1e-12l)
          .second;
  std::cout << (int)ceill(res) << std::endl;
  return 0;
}
