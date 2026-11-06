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
  vector<int> d1(n), d2(n);
  for (int i = 0; i < n; i++) {
    d1[i] = 1;
    while (0 <= i - d1[i] && i + d1[i] < n && s[i - d1[i]] == s[i + d1[i]]) {
      d1[i]++;
    }

    d2[i] = 0;
    while (0 <= i - d2[i] - 1 && i + d2[i] < n &&
           s[i - d2[i] - 1] == s[i + d2[i]]) {
      d2[i]++;
    }
  }
  // --8<-- [end:core]
  for (int i = 0; i < n; ++i) cout << (i ? " " : "") << d1[i];
  cout << "\n";
  for (int i = 0; i < n; ++i) cout << (i ? " " : "") << d2[i];
  cout << "\n";
}
