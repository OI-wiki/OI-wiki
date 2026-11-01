#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>
using namespace std;
// --8<-- [start:core]
vector<int> pri;
vector<bool> not_prime;
vector<int> mu;

void pre(int n) {
  mu[1] = 1;
  for (int i = 2; i <= n; ++i) {
    if (!not_prime[i]) {
      mu[i] = -1;
      pri.push_back(i);
    }
    for (int pri_j : pri) {
      if (pri_j > n / i) break;
      not_prime[i * pri_j] = true;
      if (i % pri_j == 0) {
        mu[i * pri_j] = 0;
        break;
      }
      mu[i * pri_j] = -mu[i];
    }
  }
}

// --8<-- [end:core]
int main() {
  int n;
  cin >> n;
  not_prime.resize(max(2, n + 1));
  mu.resize(max(2, n + 1));
  pre(n);
  cout << mu[n] << "\n";
}
