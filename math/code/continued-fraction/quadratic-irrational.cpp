#include <algorithm>
#include <cmath>
#include <iostream>
#include <tuple>
#include <unordered_map>
#include <vector>

// --8<-- [start:core]
// Return the continued fraction and minimal positive period
//   of a quadratic irrational (x + y * sqrt(n)) / z.
auto quadratic_irrational(int x, int y, int z, int n) {
  int p = x * z;
  int d = n * y * y * z * z;
  int q = z * z;
  int dd = (int)sqrt(n) * y * z;
  int i = 0;
  std::vector<int> a;
  std::unordered_map<size_t, int> used;
  while (!used.count(((1LL << 32) * p) | q)) {
    a.emplace_back((p + dd) / q);
    used[((1LL << 32) * p) | q] = i++;
    p = a.back() * q - p;
    q = (d - p * p) / q;
  }
  return std::make_pair(a, i - used[((1LL << 32) * p) | q]);
}

// --8<-- [end:core]
int main() {
  int x, y, z, n;
  std::cin >> x >> y >> z >> n;
  auto res = quadratic_irrational(x, y, z, n);
  printf("%d\n", res.second);
  for (int x : res.first) printf("%d ", x);
  printf("\n");
  return 0;
}
