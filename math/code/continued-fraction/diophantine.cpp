#include <algorithm>
#include <iostream>
#include <tuple>
#include <vector>

// --8<-- [start:fraction]
// Find the continued fraction representation of P/Q.
auto fraction(int p, int q) {
  std::vector<int> a;
  while (q) {
    a.push_back(p / q);
    std::tie(p, q) = std::make_pair(q, p % q);
  }
  return a;
}

// --8<-- [end:fraction]
// --8<-- [start:convergents]
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

// --8<-- [end:convergents]
// --8<-- [start:dio]
// Return (x,y) such that Ax+By=C.
// Assume that such (x,y) exists.
auto dio(int A, int B, int C) {
  std::vector<int> p, q;
  std::tie(p, q) = convergents(fraction(A, B));
  C /= A / p.back();
  int t = p.size() % 2 ? -1 : 1;
  return std::make_pair(t * C * q.end()[-2], -t * C * p.end()[-2]);
}

// --8<-- [end:dio]
int main() {
  int A, B, C, x, y;
  std::cin >> A >> B >> C;
  std::tie(x, y) = dio(A, B, C);
  std::cout << A * x + B * y - C;  // Should be 0.
  return 0;
}
