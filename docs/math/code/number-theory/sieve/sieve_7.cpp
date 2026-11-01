#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>
using namespace std;
// --8<-- [start:core]
vector<int> pri;
vector<bool> not_prime;
vector<int> d, num;

void pre(int n) {
  d[1] = 1;
  for (int i = 2; i <= n; ++i) {
    if (!not_prime[i]) {
      pri.push_back(i);
      d[i] = 2;
      num[i] = 1;
    }
    for (int pri_j : pri) {
      if (pri_j > n / i) break;
      not_prime[i * pri_j] = true;
      if (i % pri_j == 0) {
        num[i * pri_j] = num[i] + 1;
        d[i * pri_j] = d[i] / num[i * pri_j] * (num[i * pri_j] + 1);
        break;
      }
      num[i * pri_j] = 1;
      d[i * pri_j] = d[i] * 2;
    }
  }
}

// --8<-- [end:core]
int main() {
  int n;
  cin >> n;
  not_prime.resize(max(2, n + 1));
  d.resize(max(2, n + 1));
  num.resize(max(2, n + 1));
  pre(n);
  cout << d[n] << "\n";
}
