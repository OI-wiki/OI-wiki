#include <algorithm>
#include <cmath>
#include <iostream>
#include <limits>
#include <vector>
using namespace std;
constexpr int MAXN = 1000005;
int n;
vector<int> a, c, sum;
vector<int>& t = c;

int lowbit(int x) {
  // x 的二进制中，最低位的 1 以及后面所有 0 组成的数．
  // lowbit(0b01011000) == 0b00001000
  //          ~~~~^~~~
  // lowbit(0b01110010) == 0b00000010
  //          ~~~~~~^~
  return x & -x;
}

int getsum(int x) {  // a[1]..a[x]的和
  int ans = 0;
  while (x > 0) {
    ans = ans + c[x];
    x = x - lowbit(x);
  }
  return ans;
}

void add(int x, int k) {
  while (x <= n) {  // 不能越界
    c[x] = c[x] + k;
    x = x + lowbit(x);
  }
}

// --8<-- [start:example57]
// Θ(n) 建树
void init() {
  for (int i = 1; i <= n; ++i) {
    t[i] += a[i];
    int j = i + lowbit(i);
    if (j <= n) t[j] += t[i];
  }
}

// --8<-- [end:example57]

int main() {
  int q;
  cin >> n >> q;
  c.resize(n + 1);
  a.resize(n + 1);
  sum.resize(n + 1);
  for (int j = 1; j <= n; ++j) {
    cin >> a[j];
    sum[j] = sum[j - 1] + a[j];
  }
  init();
  while (q--) {
    int op, x, y;
    cin >> op >> x >> y;
    if (op == 1)
      add(x, y);
    else
      cout << getsum(y) - getsum(x - 1) << '\n';
  }
}
