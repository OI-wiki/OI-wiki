#include <algorithm>
#include <functional>
#include <iostream>

using namespace std;

// --8<-- [start:declarations]
int a[1009], n = 10;

// ...
// --8<-- [end:declarations]

int main() {
  for (int i = 1; i <= n; ++i) cin >> a[i];
  // --8<-- [start:sort]
  std::sort(a + 1, a + 1 + n);                  // 从小到大排序
  std::sort(a + 1, a + 1 + n, greater<int>());  // 从大到小排序
  // --8<-- [end:sort]
  for (int i = 1; i <= n; ++i) cout << (i > 1 ? " " : "") << a[i];
  cout << "\n";
}
