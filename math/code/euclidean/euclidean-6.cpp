#include <algorithm>
#include <cmath>
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

struct LinearTransform {
  int u, v;

  LinearTransform() : u(0), v(1) {}

  LinearTransform operator*(const LinearTransform& rhs) const {
    LinearTransform res;
    res.u = u + v * rhs.u;
    res.v = v * rhs.v;
    return res;
  }

  int eval(int x) const { return u + v * x; }
};

int solve(int n, int r) {
  long double sqrt_r = sqrtl(r);
  int sqr = sqrt_r;
  if (r == sqr * sqr) return sqr % 2 ? (n % 2 ? -1 : 0) : n;
  int P = 0, Q = 1, D = r, val = 0;
  LinearTransform U, R;
  U.v = -1;
  R.u = 1;
  while (n) {
    int a = (P + sqr) / Q;
    R = pow(U, a) * R;
    int m = ((P + sqrt_r) / Q - a) * n;
    P = a * Q - P;
    Q = (D - P * P) / Q;
    int rem = n - (int)(m * (P + sqrt_r) / Q);
    val = pow(R, rem).eval(val);
    std::swap(U, R);
    n = m;
  }
  return val;
}

int main() {
  int t;
  std::cin >> t;
  for (; t; --t) {
    int n, r;
    std::cin >> n >> r;
    std::cout << solve(n, r) << '\n';
  }
  return 0;
}
