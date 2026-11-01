#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// --8<-- [start:core]
using ull = unsigned long long;
ull base = 131;
ull mod1 = 212370440130137957, mod2 = 1e9 + 7;

ull get_hash1(std::string s) {
  int len = s.size();
  ull ans = 0;
  for (int i = 0; i < len; i++) ans = (ans * base + (ull)s[i]) % mod1;
  return ans;
}

ull get_hash2(std::string s) {
  int len = s.size();
  ull ans = 0;
  for (int i = 0; i < len; i++) ans = (ans * base + (ull)s[i]) % mod2;
  return ans;
}

bool cmp(const std::string s, const std::string t) {
  bool f1 = get_hash1(s) != get_hash1(t);
  bool f2 = get_hash2(s) != get_hash2(t);
  return f1 || f2;
}

// --8<-- [end:core]

int main() {
  int n;
  cin >> n;
  vector<string> unique;
  while (n--) {
    string s;
    cin >> s;
    bool found = false;
    for (const auto &t : unique)
      if (!cmp(s, t)) found = true;
    if (!found) unique.push_back(s);
  }
  cout << unique.size() << '\n';
}
