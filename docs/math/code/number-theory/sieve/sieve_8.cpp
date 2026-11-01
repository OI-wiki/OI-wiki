#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>
using namespace std;
// --8<-- [start:core]
vector<int> pri;
vector<bool> not_prime;
vector<long long> g, f;

void pre(int n) {
  g[1] = f[1] = 1;
  for (int i = 2; i <= n; ++i) {
    if (!not_prime[i]) {
      pri.push_back(i);
      g[i] = i + 1;
      f[i] = i + 1;
    }
    for (int pri_j : pri) {
      if (pri_j > n / i) break;
      not_prime[i * pri_j] = true;
      if (i % pri_j == 0) {
        g[i * pri_j] = g[i] * pri_j + 1;
        f[i * pri_j] = f[i] / g[i] * g[i * pri_j];
        break;
      }
      f[i * pri_j] = f[i] * f[pri_j];
      g[i * pri_j] = 1 + pri_j;
    }
  }
}

// --8<-- [end:core]
int main() {
  int n;
  cin >> n;
  not_prime.resize(max(2, n + 1));
  g.resize(max(2, n + 1));
  f.resize(max(2, n + 1));
  pre(n);
  cout << f[n] << "\n";
}
