#include <iostream>

struct Data {
  int f, g, h;
};

Data solve(long long a, long long b, long long c, long long n) {
  constexpr long long M = 998244353;
  constexpr long long i2 = (M + 1) / 2;
  constexpr long long i6 = (M + 1) / 6;
  long long n2 = (n + 1) * n % M * i2 % M;
  long long n3 = (2 * n + 1) * (n + 1) % M * n % M * i6 % M;
  Data res = {0, 0, 0};
  if (a >= c || b >= c) {
    auto tmp = solve(a % c, b % c, c, n);
    long long aa = a / c, bb = b / c;
    res.f = (tmp.f + aa * n2 + bb * (n + 1)) % M;
    res.g = (tmp.g + aa * n3 + bb * n2) % M;
    res.h = (tmp.h + 2 * bb * tmp.f % M + 2 * aa * tmp.g % M +
             aa * aa % M * n3 % M + bb * bb % M * (n + 1) % M +
             2 * aa * bb % M * n2 % M) %
            M;
    return res;
  }
  long long m = (a * n + b) / c;
  if (!m) return res;
  auto tmp = solve(c, c - b - 1, a, m - 1);
  res.f = (m * n - tmp.f + M) % M;
  res.g = (m * n2 + (M - tmp.f) * i2 + (M - tmp.h) * i2) % M;
  res.h = (n * m % M * m - tmp.f - tmp.g * 2 + 3 * M) % M;
  return res;
}

int main() {
  int t;
  std::cin >> t;
  for (; t; --t) {
    int n, a, b, c;
    std::cin >> n >> a >> b >> c;
    auto res = solve(a, b, c, n);
    std::cout << res.f << ' ' << res.h << ' ' << res.g << '\n';
  }
  return 0;
}
