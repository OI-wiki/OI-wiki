#include <cassert>
#include <iostream>
#include <vector>
using namespace std;

int main() {
  int m, n;
  cin >> m >> n;
  vector<int> a, b, c;
  long long count = 0;

  {
    // --8<-- [start:while-prefix]
    // 降序遍历 m 的非空子集
    int s = m;
    while (s > 0) {
      // s 是 m 的一个非空子集
      // --8<-- [end:while-prefix]
      a.push_back(s);
      // --8<-- [start:while-suffix]
      s = (s - 1) & m;
    }
    // --8<-- [end:while-suffix]
  }

  {
    // --8<-- [start:for]
    // 降序遍历 m 的非空子集
    for (int s = m; s; s = (s - 1) & m)
      // s 是 m 的一个非空子集
      // --8<-- [end:for]
      b.push_back(s);
  }

  {
    // --8<-- [start:zero-prefix]
    // 降序遍历 m 的子集
    for (int s = m;; s = (s - 1) & m) {
      // s 是 m 的一个子集
      // --8<-- [end:zero-prefix]
      c.push_back(s);
      // --8<-- [start:zero-suffix]
      if (s == 0) break;
    }
    // --8<-- [end:zero-suffix]
  }

  {
    // --8<-- [start:all]
    for (int m = 0; m < (1 << n); ++m)
      // 降序遍历 m 的非空子集
      for (int s = m; s; s = (s - 1) & m)
        // s 是 m 的一个非空子集
        // --8<-- [end:all]
        ++count;
  }
  assert(a == b);
  assert(c.back() == 0);
  assert(vector<int>(c.begin(), c.end() - 1) == a);
  for (size_t i = 0; i < c.size(); ++i)
    cout << c[i] << (i + 1 == c.size() ? '\n' : ' ');
  cout << count << "\n";
}
