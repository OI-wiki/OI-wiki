#include <algorithm>
#include <cmath>
#include <iostream>
#include <limits>
#include <vector>
using namespace std;
constexpr int MAXN = 1000005;
int n;
vector<int> c;

// --8<-- [start:example42]
int lowbit(int x) {
  // x 的二进制中，最低位的 1 以及后面所有 0 组成的数．
  // lowbit(0b01011000) == 0b00001000
  //          ~~~~^~~~
  // lowbit(0b01110010) == 0b00000010
  //          ~~~~~~^~
  return x & -x;
}

// --8<-- [end:example42]
// --8<-- [start:example44]
int getsum(int x) {  // a[1]..a[x]的和
  int ans = 0;
  while (x > 0) {
    ans = ans + c[x];
    x = x - lowbit(x);
  }
  return ans;
}

// --8<-- [end:example44]
// --8<-- [start:example46]
void add(int x, int k) {
  while (x <= n) {  // 不能越界
    c[x] = c[x] + k;
    x = x + lowbit(x);
  }
}

// --8<-- [end:example46]

int main() {
  int q;
  cin >> n >> q;
  c.resize(n + 1);
  for (int j = 1, x; j <= n; ++j) {
    cin >> x;
    add(j, x);
  }
  while (q--) {
    int op, x, y;
    cin >> op >> x >> y;
    if (op == 1)
      add(x, y);
    else
      cout << getsum(y) - getsum(x - 1) << '\n';
  }
}
