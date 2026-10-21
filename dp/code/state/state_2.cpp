#include <iostream>
#include <limits>
#include <vector>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int W, n;
  cin >> W >> n;
  const int S = (1 << n) - 1;
  vector<int> ts(S + 1), ws(S + 1);
  for (int j = 0, t, w; j < n; ++j) {
    cin >> t >> w;
    for (int i = 0; i <= S; ++i)
      if (i & (1 << j)) {
        ts[i] = max(ts[i], t);
        ws[i] += w;
      }
  }
  vector<int> dp(S + 1, numeric_limits<int>::max() / 2);
  for (int i = 0; i <= S; ++i) {
    if (ws[i] <= W) dp[i] = ts[i];
    for (int j = i; j; j = i & (j - 1))
      if (ws[i ^ j] <= W) dp[i] = min(dp[i], dp[j] + ts[i ^ j]);
  }
  cout << dp[S] << '\n';
  return 0;
}
