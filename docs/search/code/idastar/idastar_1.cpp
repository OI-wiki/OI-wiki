#include <bits/stdc++.h>

using namespace std;

const int MAX_E = 1e7;
int a, b;
vector<int> ans;
vector<int> current;

inline bool better() { return ans.empty() || current.back() < ans.back(); }

bool dfs(int d, long a, long b, int e) {
  if (d == 0) {
    if (a == 0 && better()) ans = current;
    return a == 0;
  }

  long _gcd = gcd(a, b);
  a /= _gcd;
  b /= _gcd;

  bool solved = false;
  // the min value of e:
  // a/b - 1/e >= 0
  // e >= b/a
  int e1 = max(e + 1, int((b + a - 1) / a));
  // b/a <= e <= MAX_E
  // b/a <= MAX_E
  if (b > a * MAX_E) {
    return false;
  }
  for (;; e1++) {
    // the max value of e:
    // d * (1/e) >= a/b
    // d/e >= a/b
    if (d * b < a * e1) {
      return solved;
    }
    current.push_back(e1);
    // a/b - 1/e
    solved |= dfs(d - 1, a * e1 - b, b * e1, e1);
    current.pop_back();
  }
  return solved;
}

int solve() {
  ans.clear();
  current.clear();
  for (int maxd = 1; maxd <= 100; maxd++)
    if (dfs(maxd, a, b, 1)) return maxd;
  return -1;
}

int main() {
  int kase = 0;
  while (cin >> a >> b) {
    int maxd = solve();
    cout << "Case " << ++kase << ": ";
    if (maxd > 0) {
      cout << a << "/" << b << "=";
      for (int i = 0; i < maxd - 1; i++) cout << "1/" << ans[i] << "+";
      cout << "1/" << ans[maxd - 1] << "\n";
    } else
      cout << "No solution.\n";
  }
  return 0;
}
