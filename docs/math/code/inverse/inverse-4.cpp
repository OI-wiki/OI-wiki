// LOJ Submission: https://loj.ac/s/2401204
#include <iostream>
#include <vector>

// --8<-- [start:core]
// Precomputes modular inverses of all integers from 1 to n modulo prime p.
std::vector<int> precompute_inverses(int n, int p) {
  std::vector<int> res(n + 1);
  res[1] = 1;
  for (int i = 2; i <= n; ++i) {
    res[i] = (long long)(p - p / i) * res[p % i] % p;
  }
  return res;
}

// --8<-- [end:core]
int main() {
  int n, p;
  std::cin >> n >> p;
  auto res = precompute_inverses(n, p);
  for (int i = 1; i <= n; ++i) {
    std::cout << res[i] << '\n';
  }
}
