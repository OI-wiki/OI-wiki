#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// --8<-- [start:core]
vector<int> z_function_trivial(string s) {
  int n = (int)s.length();
  vector<int> z(n);
  for (int i = 1; i < n; ++i)
    while (i + z[i] < n && s[z[i]] == s[i + z[i]]) ++z[i];
  return z;
}

// --8<-- [end:core]

int main() {
  string s;
  if (!(cin >> s)) return 0;
  auto z = z_function_trivial(s);
  for (int i = 0; i < (int)z.size(); ++i) cout << (i ? " " : "") << z[i];
  cout << "\n";
}
