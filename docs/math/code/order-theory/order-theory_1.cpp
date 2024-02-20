#include <bits/stdc++.h>
using namespace std;

int main() {
  vector<int> a;
  int x;
  while (cin >> x) a.push_back(x);
  vector<int> f, g;
  for (int i : a) {
    if (f.empty() || -i >= f.back())
      f.push_back(-i);
    else
      *upper_bound(f.begin(), f.end(), -i) = -i;
    if (g.empty() || i > g.back())
      g.push_back(i);
    else
      *lower_bound(g.begin(), g.end(), i) = i;
  }
  cout << f.size() << '\n' << g.size() << '\n';
  return 0;
}