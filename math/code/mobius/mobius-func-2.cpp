#include <iostream>
#include <vector>

// --8<-- [start:core]
std::vector<int> get_mu(int n) {
  std::vector<int> mu(n + 1), primes;
  std::vector<bool> not_prime(n + 1);
  primes.reserve(n);
  mu[1] = 1;
  for (int x = 2; x <= n; ++x) {
    if (!not_prime[x]) {
      primes.push_back(x);
      mu[x] = -1;
    }
    for (int p : primes) {
      if (x * p > n) break;
      not_prime[x * p] = true;
      if (x % p == 0) {
        mu[x * p] = 0;
        break;
      } else {
        mu[x * p] = -mu[x];
      }
    }
  }
  return mu;
}

// --8<-- [end:core]
int main() {
  int n;
  std::cin >> n;
  auto mu = get_mu(n);
  for (int i = 1; i <= n; ++i) {
    std::cout << mu[i] << '\n';
  }
  return 0;
}
