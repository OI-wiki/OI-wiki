#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// --8<-- [start:core]
// 注：
// string substr (size_t pos = 0, size_t len = npos) const;
vector<int> prefix_function(string s) {
  int n = (int)s.length();
  vector<int> pi(n);
  for (int i = 1; i < n; i++)
    for (int j = i; j >= 0; j--)
      if (s.substr(0, j) == s.substr(i - j + 1, j)) {
        pi[i] = j;
        break;
      }
  return pi;
}

// --8<-- [end:core]

int main() {
  string s;
  cin >> s;
  auto pi = prefix_function(s);
  for (int i = 0; i < (int)pi.size(); ++i) cout << (i ? " " : "") << pi[i];
  cout << "\n";
}
