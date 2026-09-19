#include <cstring>
#include <iostream>
constexpr int N = 100010;
int n, a[N], l[N], r[N];
long long sum[N];
long long ans;
int ansl, ansr;
bool fir = true;
using std::cin;
using std::cout;

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  while (cin >> n) {
    memset(a, -1, sizeof(a));
    if (!fir)
      cout << '\n';
    else
      fir = false;
    ans = 0;
    ansl = ansr = 1;
    for (int i = 1; i <= n; i++) {
      cin >> a[i];
      sum[i] = sum[i - 1] + a[i];
      l[i] = r[i] = i;
    }
    for (int i = 1; i <= n; i++)
      while (a[l[i] - 1] >= a[i]) l[i] = l[l[i] - 1];
    for (int i = n; i >= 1; i--)
      while (a[r[i] + 1] >= a[i]) r[i] = r[r[i] + 1];
    for (int i = 1; i <= n; i++) {
      long long x = a[i] * (sum[r[i]] - sum[l[i] - 1]);
      if (ans < x || (ans == x && ansr - ansl > r[i] - l[i]))
        ans = x, ansl = l[i], ansr = r[i];
    }
    cout << ans << '\n' << ansl << ' ' << ansr << '\n';
  }
  return 0;
}