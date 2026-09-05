#include <algorithm>
#include <iostream>
#include <tuple>
#include <vector>

// Find the continued fraction representation of P/Q.
auto fraction(int p, int q) {
  std::vector<int> a;
  while (q) {
    a.push_back(p / q);
    std::tie(p, q) = std::make_pair(q, p % q);
  }
  return a;
}

// Find the convergents of a continued fraction A.
// Numerators and denominators stored separately in P and Q.
auto convergents(std::vector<int> a) {
  std::vector<int> p = {0, 1};
  std::vector<int> q = {1, 0};
  for (auto it : a) {
    p.push_back(p.back() * it + p.end()[-2]);
    q.push_back(q.back() * it + q.end()[-2]);
  }
  return std::make_pair(p, q);
}

// --8<-- [start:core]
// Find Q that minimizes Q*r mod m for 1 <= k <= n < m.
int mod_min(int r, int n, int m) {
  auto a = fraction(r, m);
  std::vector<int> p, q;
  std::tie(p, q) = convergents(a);
  for (int i = 2; i < q.size(); ++i) {
    if (i % 2 == 1 && (i + 1 == q.size() || q[i + 1] > n)) {
      int t = (n - q[i - 1]) / q[i];
      return q[i - 1] + t * q[i];
    }
  }
  return 0;
}

// --8<-- [end:core]
int main() {
  int r, n, m;
  std::cin >> r >> n >> m;
  int q = mod_min(r, n, m);
  int p = ((long long)r * q) % m;
  std::cout << p << ' ' << q;
  return 0;
}
