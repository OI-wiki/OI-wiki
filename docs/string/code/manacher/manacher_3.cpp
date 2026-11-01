#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
  string s;
  cin >> s;
  int n = s.size();
  // --8<-- [start:core]
  vector<int> d2(n);
  for (int i = 0, l = 0, r = -1; i < n; i++) {
    int k = (i > r) ? 0 : min(d2[l + r - i + 1], r - i + 1);
    while (0 <= i - k - 1 && i + k < n && s[i - k - 1] == s[i + k]) {
      k++;
    }
    d2[i] = k--;
    if (i + k > r) {
      l = i - k - 1;
      r = i + k;
    }
  }
  // --8<-- [end:core]
  for (int i = 0; i < n; ++i) cout << (i ? " " : "") << d2[i];
  cout << "\n";
}
