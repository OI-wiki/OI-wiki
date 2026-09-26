#include <iostream>

// --8<-- [start:core]
// Extended Euclidean Algorithm.
// Finds integers x, y such that a*x + b*y = gcd(a, b),
// and returns gcd(a, b).
int ex_gcd(int a, int b, int& x, int& y) {
  if (!b) {
    x = 1;
    y = 0;
    return a;
  } else {
    int d = ex_gcd(b, a % b, y, x);
    y -= a / b * x;
    return d;
  }
}

// Solves the linear congruence equation:
//     a * x ≡ b (mod n), where n > 0.
// Returns the smallest non-negative solution x,
// or -1 if there is no solution.
int solve_linear_congruence_equation(int a, int b, int n) {
  int x, y;
  int d = ex_gcd(a, n, x, y);
  if (b % d) return -1;
  n /= d;
  return ((long long)x * (b / d) % n + n) % n;
}

// --8<-- [end:core]
int main() {
  int t;
  std::cin >> t;
  for (; t; --t) {
    int a, b, n;
    std::cin >> a >> b >> n;
    std::cout << solve_linear_congruence_equation(a, b, n) << '\n';
  }
  return 0;
}
