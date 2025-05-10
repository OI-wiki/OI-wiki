/* Verified by Library Checker.                             */
/* Submission: https://judge.yosupo.jp/submission/283823    */
// --8<-- [start:full-text]
#include <iostream>

long long solve(long long a, long long b, long long c, long long n) {
  long long n2 = n * (n + 1) / 2;
  if (a >= c || b >= c) {
    long long aa = a / c, bb = b / c;
    return solve(a % c, b % c, c, n) + aa * n2 + bb * (n + 1);
  } else if (a) {
    long long m = (a * n + b) / c;
    return m * n - solve(c, c - b - 1, a, m - 1);
  } else {
    return 0;
  }
}

int main() {
  int t;
  std::cin >> t;
  for (; t; --t) {
    int a, b, c, n;
    std::cin >> n >> c >> a >> b;
    std::cout << solve(a, b, c, n - 1) << '\n';
  }
  return 0;
}

// --8<-- [end:full-text]
