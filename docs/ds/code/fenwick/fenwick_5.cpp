#include <algorithm>
#include <cmath>
#include <iostream>
#include <limits>
#include <vector>
using namespace std;
constexpr int MAXN = 1000005;
int n;
vector<int> t;

// --8<-- [start:example53]
// 权值树状数组查询第 k 小
int kth(int k) {
  int sum = 0, x = 0;
  for (int i = log2(n); ~i; --i) {
    x += 1 << i;                   // 尝试扩展
    if (x > n || sum + t[x] >= k)  // 如果扩展失败
      x -= 1 << i;
    else
      sum += t[x];
  }
  return x + 1;  // 找不到就返回 n + 1
}

// --8<-- [end:example53]

int main() {
  int q;
  cin >> n >> q;
  t.assign(n + 1, 0);
  for (int j = 1, count; j <= n; ++j) {
    cin >> count;
    for (int k = j; k <= n; k += k & -k) t[k] += count;
  }
  while (q--) {
    int k;
    cin >> k;
    cout << kth(k) << '\n';
  }
}
