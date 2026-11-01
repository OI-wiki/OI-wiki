#include <algorithm>
#include <cmath>
#include <iostream>
#include <limits>
#include <vector>
using namespace std;
constexpr int MAXN = 1000005;
int n;
vector<int> a, C;

int lowbit(int x) { return x & -x; }

// --8<-- [start:example55]
int getmax(int l, int r) {
  int ans = numeric_limits<int>::lowest();
  while (r >= l) {
    ans = max(ans, a[r]);
    --r;
    for (; r - lowbit(r) >= l; r -= lowbit(r)) {
      // 注意，循环条件不要写成 r - lowbit(r) + 1 >= l
      // 否则 l = 1 时，r 跳到 0 会死循环
      ans = max(ans, C[r]);
    }
  }
  return ans;
}

// --8<-- [end:example55]
// --8<-- [start:example56]
void update(int x, int v) {
  a[x] = v;
  for (int i = x; i <= n; i += lowbit(i)) {
    // 枚举受影响的区间
    C[i] = a[i];
    for (int j = 1; j < lowbit(i); j *= 2) {
      C[i] = max(C[i], C[i - j]);
    }
  }
}

// --8<-- [end:example56]

int main() {
  int q;
  cin >> n >> q;
  a.resize(n + 1);
  C.resize(n + 1);
  for (int j = 1, x; j <= n; ++j) {
    cin >> x;
    update(j, x);
  }
  while (q--) {
    int op, x, y;
    cin >> op >> x >> y;
    if (op == 1)
      update(x, y);
    else
      cout << getmax(x, y) << '\n';
  }
}
