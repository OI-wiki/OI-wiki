#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>
using namespace std;
// --8<-- [start:core]
vector<int> pri;
vector<bool> not_prime;
vector<int> phi;

void pre(int n) {
  phi[1] = 1;
  for (int i = 2; i <= n; i++) {
    if (!not_prime[i]) {
      pri.push_back(i);
      phi[i] = i - 1;
    }
    for (int pri_j : pri) {
      if (pri_j > n / i) break;
      not_prime[i * pri_j] = true;
      if (i % pri_j == 0) {
        phi[i * pri_j] = phi[i] * pri_j;
        break;
      }
      phi[i * pri_j] = phi[i] * phi[pri_j];
    }
  }
}

// --8<-- [end:core]
int main() {
  int n;
  cin >> n;
  not_prime.resize(max(2, n + 1));
  phi.resize(max(2, n + 1));
  pre(n);
  cout << phi[n] << "\n";
}
