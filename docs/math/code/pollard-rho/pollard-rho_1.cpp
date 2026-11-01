#include <iostream>
#include <vector>
using namespace std;
using ll = long long;

// --8<-- [start:core]
vector<ll> breakdown(ll N) {
  vector<ll> result;
  for (ll i = 2; i <= N / i; i++) {
    if (N % i == 0) {  // 如果 i 能够整除 N，说明 i 为 N 的一个质因子．
      while (N % i == 0) N /= i;
      result.push_back(i);
    }
  }
  if (N != 1) {  // 说明再经过操作之后 N 留下了一个素数
    result.push_back(N);
  }
  return result;
}

// --8<-- [end:core]
int main() {
  int t;
  cin >> t;
  while (t--) {
    ll n;
    cin >> n;
    auto a = breakdown(n);
    if (a.back() == n)
      cout << "Prime\n";
    else
      cout << a.back() << "\n";
  }
}
