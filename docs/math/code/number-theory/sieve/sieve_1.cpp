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
  for (int i = 2; i <= n; ++i) {
    if (is_prime[i]) {
      prime.push_back(i);
      if ((long long)i * i > n) continue;
      for (int j = i * i; j <= n; j += i)
        // 因为从 2 到 i - 1 的倍数我们之前筛过了，这里直接从 i
        // 的倍数开始，提高了运行速度
        is_prime[j] = false;  // 是 i 的倍数的均不是素数
    }
  }
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
