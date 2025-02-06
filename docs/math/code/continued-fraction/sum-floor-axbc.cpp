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

// Find convex hull of lattice (x, y) such that C*y <= A*x+B.
auto hull(int A, int B, int C, int N) {
  auto diff = [&](int x, int y) -> int { return C * y - A * x; };
  auto a = fraction(A, C);
  std::vector<int> p, q;
  std::tie(p, q) = convergents(a);
  std::vector<int> ah(0), ph(1, B / C), qh(1, 0);
  auto insert = [&](int dq, int dp) -> void {
    int k = (N - qh.back()) / dq;
    if (diff(dq, dp) > 0) {
      k = std::min((int)k, (B - diff(qh.back(), ph.back())) / diff(dq, dp));
    }
    ah.emplace_back(k);
    qh.emplace_back(qh.back() + k * dq);
    ph.emplace_back(ph.back() + k * dp);
  };
  for (int i = 1; i < q.size() - 1; ++i) {
    if (i % 2 == 0) {
      while (diff(qh.back() + q[i + 1], ph.back() + p[i + 1]) <= B) {
        int t = (B - diff(qh.back() + q[i + 1], ph.back() + p[i + 1])) /
                (-diff(q[i], p[i]));
        int dp = p[i + 1] - t * p[i];
        int dq = q[i + 1] - t * q[i];
        if (dq < 0 || qh.back() + dq > N) break;
        insert(dq, dp);
      }
    }
  }
  insert(q.back(), p.back());
  for (int i = q.size() - 1; i; --i) {
    if (i % 2 == 1) {
      while (qh.back() + q[i - 1] <= N) {
        int t = (N - qh.back() - q[i - 1]) / q[i];
        int dp = p[i - 1] + t * p[i];
        int dq = q[i - 1] + t * q[i];
        insert(dq, dp);
      }
    }
  }
  return std::make_tuple(ah, ph, qh);
}

// Sum of floor (Ax+B)/M from 0 to N-1.
auto solve(int N, int M, int A, int B) {
  std::vector<int> ah, ph, qh;
  std::tie(ah, ph, qh) = hull(A, B, M, N);
  // The number of lattice points within a vertical right trapezoid
  // on points (0; 0) - (0; y1) - (dx; y2) - (dx; 0) that has
  // a+1 integer points on the segment (0; y1) - (dx; y2) but with
  // the number of points on the vertical right line excluded.
  auto picks = [&](int y1, int y2, int dx, int a) -> int {
    int b = y1 + y2 + a + dx;
    int A = (y1 + y2) * dx;
    return (A + b) / 2 - y2;  // = (A - b + 2) // 2 + b - (y2 + 1)
  };
  int ans = 0;
  for (int i = 1; i < qh.size(); ++i) {
    ans += picks(ph[i - 1], ph[i], qh[i] - qh[i - 1], ah[i - 1]);
  }
  return ans - N;
}

int main() {
  int t;
  std::cin >> t;
  for (; t; --t) {
    int n, m, a, b;
    std::cin >> n >> m >> a >> b;
    std::cout << solve(n, m, a, b) << '\n';
  }
  return 0;
}
