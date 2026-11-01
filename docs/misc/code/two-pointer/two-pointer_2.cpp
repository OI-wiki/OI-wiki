#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Sample source:
// https://leetcode.com/problems/longest-word-in-dictionary-through-deleting/
// Input: source string, dictionary size, then dictionary words.
// --8<-- [start:core]
string findLongestWord(string s, vector<string>& dictionary) {
  sort(dictionary.begin(), dictionary.end());
  int mx = 0, r = 0;
  string ans = "";
  for (int i = dictionary.size() - 1; i >= 0; i--) {
    r = 0;
    for (int j = 0; j < s.length(); ++j) {
      if (r < static_cast<int>(dictionary[i].size()) &&
          s[j] == dictionary[i][r])
        r++;
    }
    if (r == dictionary[i].length()) {
      if (r >= mx) {
        mx = r;
        ans = dictionary[i];
      }
    }
  }
  return ans;
}

// --8<-- [end:core]

int main() {
  string s;
  int n;
  if (!(cin >> s >> n)) return 0;
  vector<string> dictionary(n);
  for (string& word : dictionary) cin >> word;
  cout << findLongestWord(s, dictionary) << '\n';
}
