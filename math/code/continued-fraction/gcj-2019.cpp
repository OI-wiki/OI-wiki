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

// Expand [..., n] to [..., n-1, 1] if needed.
void expand(std::vector<int>& a) {
  if (a.back() > 1 || a.size() == 1) {
    --a.back();
    a.push_back(1);
  }
}

// Check if a is smaller than b.
bool less_than(std::vector<int> a, std::vector<int> b) {
  expand(a);
  expand(b);
  for (int i = 0; i < a.size() - 1 || i < b.size() - 1; ++i) {
    int d = (i < a.size() - 1 ? a[i] : 0) - (i < b.size() - 1 ? b[i] : 0);
    if (i & 1) d = -d;
    if (d < 0) {
      return true;
    } else if (d > 0) {
      return false;
    }
  }
  return false;
}

// Get X +- EPSILON.
auto pm_eps(std::vector<int> a) {
  constexpr int inf = 0x3f3f3f3f;
  if (a.empty()) {
    a.emplace_back(inf);
  }
  auto b = a;
  expand(b);
  a.emplace_back(inf);
  b.emplace_back(inf);
  return less_than(a, b) ? std::make_pair(a, b) : std::make_pair(b, a);
}

// Find the lexicographically smallest (q, p)
//   such that p0/q0 < p/q < p1/q1.
auto middle(int p0, int q0, int p1, int q1) {
  auto a0 = pm_eps(fraction(p0, q0)).second;
  auto a1 = pm_eps(fraction(p1, q1)).first;
  std::vector<int> a;
  for (int i = 0; i < a0.size() || i < a1.size(); ++i) {
    if (a0[i] == a1[i]) {
      a.emplace_back(a0[i]);
    } else {
      a.emplace_back(std::min(a0[i], a1[i]) + 1);
      break;
    }
  }
  auto pq = convergents(a);
  return std::make_pair(pq.first.back(), pq.second.back());
}

// --8<-- [start:core]
void solve() {
  int n;
  std::cin >> n;
  std::vector<int> C(n), J(n);
  // p0/q0 < y/x < p1/q1
  int p0 = 0, q0 = 1, p1 = 1, q1 = 0;
  bool fail = false;
  for (int i = 0; i < n; ++i) {
    std::cin >> C[i] >> J[i];
    if (i) {
      int A = C[i] - C[i - 1];
      int B = J[i] - J[i - 1];
      if (A <= 0 && B <= 0) {
        fail = true;
        break;
      } else if (B > 0 && A < 0) {  // y/x > (-A)/B if B > 0
        if ((-A) * q0 > p0 * B) {
          p0 = -A;
          q0 = B;
        }
      } else if (B < 0 && A > 0) {  // y/x < A/(-B) if B < 0
        if (A * q1 < p1 * (-B)) {
          p1 = A;
          q1 = -B;
        }
      }
    }
  }
  if (fail || p0 * q1 >= p1 * q0) {
    printf("IMPOSSIBLE\n");
  } else {
    auto pq = middle(p0, q0, p1, q1);
    printf("%d %d\n", pq.first, pq.second);
  }
}

// --8<-- [end:core]
int main() {
  int t;
  std::cin >> t;
  for (; t; --t) {
    solve();
  }
  return 0;
}
