#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// --8<-- [start:core]
// duval_algorithm
vector<string> duval(string const& s) {
  int n = s.size(), i = 0;
  vector<string> factorization;
  while (i < n) {
    int j = i + 1, k = i;
    while (j < n && s[k] <= s[j]) {
      if (s[k] < s[j])
        k = i;
      else
        k++;
      j++;
    }
    while (i <= k) {
      factorization.push_back(s.substr(i, j - k));
      i += j - k;
    }
  }
  return factorization;
}

// --8<-- [end:core]

int main() {
  string s;
  cin >> s;
  for (const auto& factor : duval(s)) cout << factor << "\n";
}
