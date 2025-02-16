#include <iostream>
#include <vector>

// Calculate (n!)_p mod pa.
int factmod(int n, int p, int pa) {
  // Pretreatment.
  std::vector<int> f(pa);
  f[0] = 1;
  for (int i = 1; i < pa; ++i) {
    f[i] = i % p ? (long long)f[i - 1] * i % pa : f[i - 1];
  }
  // Recursion.
  bool neg = p != 2 || pa <= 4;
  int res = 1;
  while (n > 1) {
    if ((n / pa) & neg) res = pa - res;
    res = (long long)res * f[n % pa] % pa;
    n /= p;
  }
  return res;
}

int main() {
  int t;
  std::cin >> t;
  for (; t; --t) {
    int n, p, pa;
    std::cin >> n >> p >> pa;
    std::cout << factmod(n, p, pa) << '\n';
  }
  return 0;
}
