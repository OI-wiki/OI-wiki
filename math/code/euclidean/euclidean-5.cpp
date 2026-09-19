#include <iostream>

template <typename T>
T pow(T a, int b) {
  T res;
  for (; b; b >>= 1) {
    if (b & 1) res = res * a;
    a = a * a;
  }
  return res;
}

template <typename T>
T euclid(int a, int b, int c, int n, T U, T R) {
  if (b >= c) return pow(U, b / c) * euclid(a, b % c, c, n, U, R);
  if (a >= c) return euclid(a % c, b, c, n, U, pow(U, a / c) * R);
  auto m = ((long long)a * n + b) / c;
  if (!m) return pow(R, n);
  return pow(R, (c - b - 1) / a) * U *
         euclid(c, (c - b - 1) % a, a, m - 1, R, U) *
         pow(R, n - (c * m - b - 1) / a);
}

constexpr int M = 998244353;

struct Info {
  long long x, y, s, t, u;

  Info() : x(0), y(0), s(0), t(0), u(0) {}

  Info operator*(const Info& rhs) const {
    Info res;
    res.x = (x + rhs.x) % M;
    res.y = (y + rhs.y) % M;
    res.s = (s + rhs.s + rhs.x * y) % M;
    auto tmp = (rhs.x * (rhs.x + 1) / 2 + x * rhs.x) % M;
    res.t = (t + rhs.t + x * rhs.s + tmp * y) % M;
    res.u = (u + rhs.u + 2 * y * rhs.s + rhs.x * y % M * y) % M;
    return res;
  }
};

void solve(int a, int b, int c, int n) {
  Info U, R;
  U.y = 1;
  R.x = 1;
  auto res = euclid(a, b, c, n, U, R);
  auto f = (res.s + b / c) % M;
  auto g = res.t;
  auto h = (res.u + (long long)(b / c) * (b / c)) % M;
  std::cout << f << ' ' << h << ' ' << g << '\n';
}

int main() {
  int t;
  std::cin >> t;
  for (; t; --t) {
    int a, b, c, n;
    std::cin >> n >> a >> b >> c;
    solve(a, b, c, n);
  }
  return 0;
}
