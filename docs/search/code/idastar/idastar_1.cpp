#include <cmath>
#include <iostream>
#include <numeric>
#include <vector>

int max_e = 1e7;
std::vector<int> ans;
std::vector<int> current;

long long gcd(long long x, long long y) { return y ? gcd(y, x % y) : x; }

bool dfs(int d, long long a, long long b, int e) {
  long long _gcd = gcd(a, b);
  a /= _gcd;
  b /= _gcd;

  bool solved = false;
  if (d == 2) {
    for (int k = 4 * b / (a * a) + 1;; ++k) {
      long long delta = a * a * k * k - 4 * b * k;
      long long t = std::sqrt(delta + 0.5l);
      long long x = (a * k - t) / 2;
      long long y = (a * k + t) / 2;
      if (y > max_e) break;
      if (!t || t * t != delta || (a * k - t) % 2 != 0) continue;
      ans = current;
      ans.push_back(x);
      ans.push_back(y);
      max_e = y - 1;
      solved = true;
    }
  } else {
    int e1 = std::max(e + 1, int((b + a - 1) / a));
    for (; e1 <= d * b / a && e1 <= max_e; e1++) {
      current.push_back(e1);
      // a/b - 1/e
      solved |= dfs(d - 1, a * e1 - b, b * e1, e1);
      current.pop_back();
    }
  }
  return solved;
}

int solve(int a, int b) {
  if (b % a == 0) {
    ans.push_back(b / a);
    return 1;
  }
  for (int lim = 2; lim <= 100; lim++)
    if (dfs(lim, a, b, 1)) return lim;
  return -1;
}

int main() {
  int a, b;
  std::cin >> a >> b;
  solve(a, b);
  for (auto x : ans) std::cout << x << ' ';
  std::cout << std::endl;
  return 0;
}
