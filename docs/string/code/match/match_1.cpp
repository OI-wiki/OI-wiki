#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// --8<-- [start:core]
/*
 * s：待匹配的主串
 * t：模式串
 * n：主串的长度
 * m：模式串的长度
 */
std::vector<int> match(char *s, char *t, int n, int m) {
  std::vector<int> ans;
  int i, j;
  for (i = 0; i < n - m + 1; i++) {
    for (j = 0; j < m; j++) {
      if (s[i + j] != t[j]) break;
    }
    if (j == m) ans.push_back(i);
  }
  return ans;
}

// --8<-- [end:core]

// Sample problem:
// https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_14_A
int main() {
  string s, t;
  cin >> s >> t;
  for (int pos : match(&s[0], &t[0], s.size(), t.size())) cout << pos << "\n";
}
