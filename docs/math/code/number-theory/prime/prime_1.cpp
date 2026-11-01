#include <cstdlib>
#include <iostream>
using namespace std;

// --8<-- [start:core]
bool isPrime(int a) {
  if (a < 2) return false;
  for (int i = 2; i < a; ++i)
    if (a % i == 0) return false;
  return true;
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
