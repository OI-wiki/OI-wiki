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

// Find [ah, ph, qh] such that points r[i]=(ph[i], qh[i]) constitute
// upper convex hull of lattice points on 0 <= x <= N and 0 <= y <= r * x,
// where r = [a0, a1, a2, ...] and there are ah[i]-1 integer points on the
// segment between r[i] and r[i+1].
auto hull(std::vector<int> a, int N) {
  std::vector<int> p, q;
  std::tie(p, q) = convergents(a);
  int t = N / q.back();
  std::vector<int> ah = {t};
  std::vector<int> ph = {0, t * p.back()};
  std::vector<int> qh = {0, t * q.back()};

  for (int i = q.size() - 1; i; --i) {
    if (i % 2) {
      while (qh.back() + q[i - 1] <= N) {
        t = (N - qh.back() - q[i - 1]) / q[i];
        int dp = p[i - 1] + t * p[i];
        int dq = q[i - 1] + t * q[i];
        int k = (N - qh.back()) / dq;
        ah.push_back(k);
        ph.push_back(ph.back() + k * dp);
        qh.push_back(qh.back() + k * dq);
      }
    }
  }
  return make_tuple(ah, ph, qh);
}

// Find sum of floor(k * x) for k in [1, N] and x = [a0; a1, a2, ...]
int sum_floor(std::vector<int> a, int N) {
  N++;
  std::vector<int> ah, ph, qh;
  std::tie(ah, ph, qh) = hull(a, N);

  // The number of lattice points within a vertical right trapezoid
  // on points (0; 0) - (0; y1) - (dx; y2) - (dx; 0) that has
  // a+1 integer points on the segment (0; y1) - (dx; y2).
  auto picks = [](int y1, int y2, int dx, int a) -> int {
    int b = y1 + y2 + a + dx;
    int A = (y1 + y2) * dx;
    return (A + b) / 2 - y2;  // = (A - b + 2) // 2 + b - (y2 + 1)
  };

  int ans = 0;
  for (size_t i = 1; i < qh.size(); i++) {
    ans += picks(ph[i - 1], ph[i], qh[i] - qh[i - 1], ah[i - 1]);
  }
  return ans - N;
}

// --8<-- [start:core]
int solve(int p, int q, int n) {
  return p * n * (n + 1) / 2 - q * sum_floor(fraction(p, q), n);
}

// --8<-- [end:core]
int main() {
  int t;
  std::cin >> t;
  for (; t; --t) {
    int p, q, n;
    std::cin >> p >> q >> n;
    std::cout << solve(p, q, n) << '\n';
  }
  return 0;
}
