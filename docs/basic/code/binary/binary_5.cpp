#include <iomanip>
#include <iostream>

double threshold;

bool check(double x) { return x >= threshold; }

// --8<-- [start:core]
double binary_search_iter(double L, double R) {  // 固定迭代次数实现
  double l = L, r = R;
  for (int i = 0; i < 100; ++i) {
    double mid = (l + r) / 2;
    if (check(mid))
      r = mid;
    else
      l = mid;
  }
  return r;
}

const double eps = 1e-7;  // 精度要求，通常取题目要求精度的 1/100 或更小

double binary_search_eps(double L, double R) {  // eps 实现
  double l = L, r = R;
  while (r - l > eps) {
    double mid = (l + r) / 2;
    if (check(mid))
      r = mid;
    else
      l = mid;
  }
  return r;
}

// --8<-- [end:core]

int main() {
  double l, r;
  std::cin >> l >> r >> threshold;
  std::cout << std::fixed << std::setprecision(5) << binary_search_iter(l, r)
            << " " << binary_search_eps(l, r) << "\n";
}
