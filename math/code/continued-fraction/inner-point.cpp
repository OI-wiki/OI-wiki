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
  // Deal with empty continued fraction for 1/0.
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

int main() {
  int t;
  std::cin >> t;
  for (; t; --t) {
    int p0, q0, p1, q1;
    std::cin >> p0 >> q0 >> p1 >> q1;
    auto pq = middle(p0, q0, p1, q1);
    std::cout << pq.first << '/' << pq.second << '\n';
  }
  return 0;
}
