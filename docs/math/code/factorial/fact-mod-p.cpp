#include <iostream>
#include <vector>

// Calculate (n!)_p mod p.
int factmod(int n, int p) {
  // Pretreatment.
  std::vector<int> f(p);
  f[0] = 1;
  for (int i = 1; i < p; ++i) {
    f[i] = (long long)f[i - 1] * i % p;
  }
  // Recursion.
  int res = 1;
  while (n > 1) {
    if ((n / p) & 1) res = p - res;
    res = (long long)res * f[n % p] % p;
    n /= p;
  }
  return res;
}

int main() {
  int t;
  std::cin >> t;
  for (; t; --t) {
    int n, p;
    std::cin >> n >> p;
    std::cout << factmod(n, p) << '\n';
  }
  return 0;
}
