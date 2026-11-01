#include <cstdlib>
#include <iostream>
using namespace std;
constexpr int test_time = 10;

int quickPow(int a, int b, int mod) {
  int ans = 1;
  for (; b; b >>= 1, a = 1LL * a * a % mod)
    if (b & 1) ans = 1LL * ans * a % mod;
  return ans;
}

// --8<-- [start:core]
bool fermat(int n) {
  if (n < 3) return n == 2;
  // test_time 为测试次数,建议设为不小于 8
  // 的整数以保证正确率,但也不宜过大,否则会影响效率
  for (int i = 1; i <= test_time; ++i) {
    int a = rand() % (n - 2) + 2;
    if (quickPow(a, n - 1, n) != 1) return false;
  }
  return true;
}

// --8<-- [end:core]
int main() {
  srand(1);
  int n, a, ans = 0;
  cin >> n;
  while (n--) {
    cin >> a;
    ans += fermat(a);
  }
  cout << ans << "\n";
}
