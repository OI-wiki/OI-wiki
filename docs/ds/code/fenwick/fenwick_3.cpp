#include <algorithm>
#include <cmath>
#include <iostream>
#include <limits>
#include <vector>
using namespace std;
constexpr int MAXN = 1000005;
int n, m;
vector<vector<int>> c;

int lowbit(int x) { return x & -x; }

// --8<-- [start:example50]
void add(int x, int y, int v) {
  for (int i = x; i <= n; i += lowbit(i)) {
    for (int j = y; j <= m; j += lowbit(j)) {
      // 注意这里必须得建循环变量，不能像一维数组一样直接 while (x <= n) 了
      c[i][j] += v;
    }
  }
}

// --8<-- [end:example50]
// --8<-- [start:example51]
int sum(int x, int y) {
  int res = 0;
  for (int i = x; i > 0; i -= lowbit(i)) {
    for (int j = y; j > 0; j -= lowbit(j)) {
      res += c[i][j];
    }
  }
  return res;
}

int ask(int x1, int y1, int x2, int y2) {
  // 查询子矩阵和
  return sum(x2, y2) - sum(x2, y1 - 1) - sum(x1 - 1, y2) + sum(x1 - 1, y1 - 1);
}

// --8<-- [end:example51]

int main() {
  int q;
  cin >> n >> m >> q;
  c.assign(n + 1, vector<int>(m + 1));
  while (q--) {
    int op, x, y, a, b;
    cin >> op >> x >> y >> a;
    if (op == 1)
      add(x, y, a);
    else {
      cin >> b;
      cout << ask(x, y, a, b) << '\n';
    }
  }
}
