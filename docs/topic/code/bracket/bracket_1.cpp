#include <iostream>
#include <string>
using std::string;

// --8<-- [start:core]
bool next_balanced_sequence(string& s) {
  int n = s.size();
  int depth = 0;
  for (int i = n - 1; i >= 0; i--) {
    if (s[i] == '(')
      depth--;
    else
      depth++;

    if (s[i] == '(' && depth > 0) {
      depth--;
      int open = (n - i - 1 - depth) / 2;
      int close = n - i - 1 - open;
      string next =
          s.substr(0, i) + ')' + string(open, '(') + string(close, ')');
      s.swap(next);
      return true;
    }
  }
  return false;
}

// --8<-- [end:core]

int main() {
  string s;
  std::cin >> s;
  if (next_balanced_sequence(s))
    std::cout << s;
  else
    std::cout << "NONE";
}
