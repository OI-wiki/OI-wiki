#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>
using namespace std;
// --8<-- [start:core]
vector<int> pri;
vector<bool> not_prime;

void pre(int n) {
  for (int i = 2; i <= n; ++i) {
    if (!not_prime[i]) {
      pri.push_back(i);
    }
    for (int pri_j : pri) {
      if (pri_j > n / i) break;
      not_prime[i * pri_j] = true;
      if (i % pri_j == 0) {
        // i % pri_j == 0
        // 换言之，i 之前被 pri_j 筛过了
        // 由于 pri 里面质数是从小到大的，所以 i 乘上其他的质数的结果一定会被
        // pri_j 的倍数筛掉，就不需要在这里先筛一次，所以这里直接 break
        // 掉就好了
        break;
      }
    }
  }
}

// --8<-- [end:core]
int main() {
  int n;
  cin >> n;
  not_prime.resize(max(2, n + 1));
  pre(n);
  int q, k;
  cin >> q;
  while (q--) {
    cin >> k;
    cout << pri[k - 1] << "\n";
  }
}
