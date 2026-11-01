#include <iostream>
#include <vector>
using namespace std;

int main() {
  long long N;
  cin >> N;
  vector<long long> f(N + 1);
  // --8<-- [start:core]
  for (long long k = N; k >= 1; k--) {
    f[k] = (N / k) * (N / k);
    for (long long i = k + k; i <= N; i += k) f[k] -= f[i];
  }
  // --8<-- [end:core]
  long long ans = 0;
  for (long long k = 1; k <= N; ++k) ans += k * f[k];
  cout << ans << "\n";
}
