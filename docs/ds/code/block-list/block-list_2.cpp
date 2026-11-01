#include <iostream>
#include <list>
#include <string>
#include <vector>
using namespace std;
// --8<-- [start:example15]
list<vector<char>> orz_list;

// --8<-- [end:example15]
int main() {
  string s;
  cin >> s;
  orz_list.emplace_back(s.begin(), s.end());
  for (const auto& block : orz_list)
    for (char c : block) cout << c;
  cout << "\n";
}
