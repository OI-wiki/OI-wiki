#include <cmath>
#include <iostream>

long long r;
long double sqrt_r;

long long gcd(long long a, long long b) { return b ? gcd(b, a % b) : a; }

unsigned long long f(long long a, long long b, long long c, long long n) {
  if (!n) return 0;
  auto d = gcd(a, gcd(b, c));
  a /= d;
  b /= d;
  c /= d;
  unsigned long long k = (a * sqrt_r + b) / c;
  if (k) {
    return n * (n + 1) / 2 * k + f(a, b - c * k, c, n);
  } else {
    unsigned long long m = n * (a * sqrt_r + b) / c;
    return n * m - f(c * a, -c * b, a * a * r - b * b, m);
  }
}

unsigned long long solve(long long n, long long r) {
  long long sqr = sqrt_r = sqrtl(r);
  if (r == sqr * sqr) return r % 2 ? (n % 2 ? -1 : 0) : n;
  return n - 2 * f(1, 0, 1, n) + 4 * f(1, 0, 2, n);
}

int main() {
  int t;
  std::cin >> t;
  for (; t; --t) {
    int n;
    std::cin >> n >> r;
    long long res = solve(n, r);
    std::cout << res << '\n';
  }
  return 0;
}
