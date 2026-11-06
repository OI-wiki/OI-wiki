#include <cassert>
#include <iostream>
// Exact signed 64-bit demonstration: 0 <= n <= 24.
// --8<-- [start:core]
constexpr int MAXN = 2000 + 5;
long long bell[MAXN][MAXN];

void f(int n) {
  bell[0][0] = 1;
  for (int i = 1; i <= n; i++) {
    bell[i][0] = bell[i - 1][i - 1];
    for (int j = 1; j <= i; j++)
      bell[i][j] = bell[i - 1][j - 1] + bell[i][j - 1];
  }
}

// --8<-- [end:core]
int main() {
  int n;
  std::cin >> n;
  assert(n >= 0 && n <= 24);
  f(n);
  std::cout << bell[n][0] << "\n";
}
