#include <algorithm>
#include <iostream>
#include <tuple>
#include <vector>

// --8<-- [start:core]
// Expand [..., n] to [..., n-1, 1] if needed.
void expand(std::vector<int>& a) {
  if (a.size() == 1 || a.back() > 1) {
    --a.back();
    a.push_back(1);
  }
}

// Check if a is smaller than b.
bool less_than(std::vector<int> a, std::vector<int> b) {
  expand(a);
  expand(b);
  for (int i = 0; i < a.size() - 1 || i < b.size() - 1; ++i) {
    int d = (i < a.size() - 1 ? a[i] : 0) - (i < b.size() - 1 ? b[i] : 0);
    if (i & 1) d = -d;
    if (d < 0) {
      return true;
    } else if (d > 0) {
      return false;
    }
  }
  return false;
}

// --8<-- [end:core]
int main() {
  int t;
  std::cin >> t;
  for (; t; --t) {
    int na, nb;
    std::cin >> na >> nb;
    std::vector<int> a(na), b(nb);
    for (int& x : a) std::cin >> x;
    for (int& x : b) std::cin >> x;
    std::cout << less_than(a, b) << ' ' << less_than(b, a) << std::endl;
  }
  return 0;
}
