#include <cassert>
#include <iostream>
#include <utility>
using namespace std;

// Exact Fibonacci values for 0 <= n <= 92.
// --8<-- [start:core]
pair<unsigned long long, unsigned long long> fib(int n) {
  if (n == 0) return {0, 1};
  auto p = fib(n >> 1);
  auto c = p.first * (2 * p.second - p.first);
  auto d = p.first * p.first + p.second * p.second;
  if (n & 1)
    return {d, c + d};
  else
    return {c, d};
}

// --8<-- [end:core]
int main() {
  int n;
  cin >> n;
  assert(n >= 0 && n <= 92);
  cout << fib(n).first << "\n";
}
