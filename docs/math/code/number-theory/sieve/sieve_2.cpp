#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>
using namespace std;
// --8<-- [start:core]
vector<int> prime;
vector<bool> is_prime;

void Eratosthenes(int n) {
  is_prime[0] = is_prime[1] = false;
  for (int i = 2; i <= n; ++i) is_prime[i] = true;
  // 1LL * i * i <= n 说明 i <= sqrt(n)
  for (int i = 2; 1LL * i * i <= n; ++i) {
    if (is_prime[i])
      for (int j = i * i; j <= n; j += i) is_prime[j] = false;
  }
  for (int i = 2; i <= n; ++i)
    if (is_prime[i]) prime.push_back(i);
}

// --8<-- [end:core]
int main() {
  int n;
  cin >> n;
  is_prime.resize(max(2, n + 1));
  Eratosthenes(n);
  int q, k;
  cin >> q;
  while (q--) {
    cin >> k;
    cout << prime[k - 1] << "\n";
  }
}
