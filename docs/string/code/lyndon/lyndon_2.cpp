#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// --8<-- [start:core]
// smallest_cyclic_string
string min_cyclic_string(string s) {
  s += s;
  int n = s.size();
  int i = 0, ans = 0;
  while (i < n / 2) {
    ans = i;
    int j = i + 1, k = i;
    while (j < n && s[k] <= s[j]) {
      if (s[k] < s[j])
        k = i;
      else
        k++;
      j++;
    }
    while (i <= k) i += j - k;
  }
  return s.substr(ans, n / 2);
}

// --8<-- [end:core]

// Problem: https://onlinejudge.org/external/7/719.pdf
int main() {
  int t;
  cin >> t;
  while (t--) {
    string s;
    cin >> s;
    cout << (s + s).find(min_cyclic_string(s)) + 1 << "\n";
  }
}
