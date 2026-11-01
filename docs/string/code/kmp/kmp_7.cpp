#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

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

// --8<-- [start:core]
void compute_automaton(string s, vector<vector<int>>& aut) {
  s += '#';
  int n = s.size();
  vector<int> pi = prefix_function(s);
  aut.assign(n, vector<int>(26));
  for (int i = 0; i < n; i++) {
    for (int c = 0; c < 26; c++) {
      if (i > 0 && 'a' + c != s[i])
        aut[i][c] = aut[pi[i - 1]][c];
      else
        aut[i][c] = i + ('a' + c == s[i]);
    }
  }
}

// --8<-- [end:core]

// The transition table uses lowercase English letters.
int main() {
  string text, pattern;
  cin >> text >> pattern;
  vector<vector<int>> aut;
  compute_automaton(pattern, aut);
  int state = 0;
  for (int i = 0; i < (int)text.size(); ++i) {
    state = aut[state][text[i] - 'a'];
    if (state == (int)pattern.size()) cout << i - state + 1 << "\n";
  }
}
