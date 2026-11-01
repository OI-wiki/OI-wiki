#include <cstdlib>
#include <iostream>
using namespace std;

// --8<-- [start:core]
bool isPrime(int a) {
  if (a < 2) return 0;
  for (int i = 2; (long long)i * i <= a; ++i)  // 防溢出
    if (a % i == 0) return 0;
  return 1;
}

// --8<-- [end:core]
int main() {
  srand(1);
  int n, a, ans = 0;
  cin >> n;
  while (n--) {
    cin >> a;
    ans += isPrime(a);
  }
  cout << ans << "\n";
}
