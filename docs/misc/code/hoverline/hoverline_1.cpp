#include <algorithm>
#include <iostream>
using std::max;
constexpr int N = 100010;
int n, a[N];
int l[N], r[N];
long long ans;
using std::cin;
using std::cout;

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  while (cin >> n, n) {
    ans = 0;
    for (int i = 1; i <= n; i++) cin >> a[i], l[i] = r[i] = i;
    for (int i = 1; i <= n; i++)
      while (l[i] > 1 && a[i] <= a[l[i] - 1]) l[i] = l[l[i] - 1];
    for (int i = n; i >= 1; i--)
      while (r[i] < n && a[i] <= a[r[i] + 1]) r[i] = r[r[i] + 1];
    for (int i = 1; i <= n; i++)
      ans = max(ans, (long long)(r[i] - l[i] + 1) * a[i]);
    cout << ans << '\n';
  }
  return 0;
}