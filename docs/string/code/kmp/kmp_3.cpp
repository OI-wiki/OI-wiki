#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// --8<-- [start:core]
vector<int> prefix_function(string s) {
  int n = (int)s.length();
  vector<int> pi(n);
  for (int i = 1; i < n; i++) {
    int j = pi[i - 1];
    while (j > 0 && s[i] != s[j]) j = pi[j - 1];
    if (s[i] == s[j]) j++;
    pi[i] = j;
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
