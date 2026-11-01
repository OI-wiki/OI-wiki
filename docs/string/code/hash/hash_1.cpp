#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// --8<-- [start:core]
using std::string;

constexpr int M = 1e9 + 7;
constexpr int B = 233;

using ll = long long;

int get_hash(const string& s) {
  int res = 0;
  for (int i = 0; i < s.size(); ++i) {
    res = ((ll)res * B + s[i]) % M;
  }
  return res;
}

bool cmp(const string& s, const string& t) {
  return get_hash(s) == get_hash(t);
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
    for (const auto& t : unique)
      if (cmp(s, t)) found = true;
    if (!found) unique.push_back(s);
  }
  cout << unique.size() << '\n';
}
