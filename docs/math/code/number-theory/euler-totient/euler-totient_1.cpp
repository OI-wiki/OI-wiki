#include <iostream>
// --8<-- [start:core]
#include <cmath>

int euler_phi(int n) {
  int ans = n;
  for (int i = 2; 1LL * i * i <= n; i++)
    if (n % i == 0) {
      ans = ans / i * (i - 1);
      while (n % i == 0) n /= i;
    }
  if (n > 1) ans = ans / n * (n - 1);
  return ans;
}

// --8<-- [end:core]
int main() {
  int n;
  std::cin >> n;
  std::cout << euler_phi(n) << "\n";
}
