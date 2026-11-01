#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

#include <set>

// --8<-- [start:core]
int count_unique_substrings(string const& s) {
  int n = s.size();

  constexpr static int b = 31;
  constexpr static int m = 1e9 + 9;
  vector<long long> b_pow(n);
  b_pow[0] = 1;
  for (int i = 1; i < n; i++) b_pow[i] = (b_pow[i - 1] * b) % m;

  vector<long long> h(n + 1, 0);
  for (int i = 0; i < n; i++)
    h[i + 1] = (h[i] + (s[i] - 'a' + 1) * b_pow[i]) % m;

  int cnt = 0;
  for (int l = 1; l <= n; l++) {
    set<long long> hs;
    for (int i = 0; i <= n - l; i++) {
      long long cur_h = (h[i + l] + m - h[i]) % m;
      cur_h = (cur_h * b_pow[n - i - 1]) % m;
      hs.insert(cur_h);
    }
    cnt += hs.size();
  }
  return cnt;
}

// --8<-- [end:core]

int main() {
  string s;
  cin >> s;
  cout << count_unique_substrings(s) << "\n";
}
