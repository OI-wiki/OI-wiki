// Sample source: https://www.luogu.com.cn/problem/P4597
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <utility>
#include <vector>
using namespace std;

// --8<-- [start:core]
int a[500005], ans[500005];  // a:原序列 ans:构造的序列

void overall_binary(int l, int r, int ql, int qr) {
  if (l > r) return;
  if (ql == qr) {
    for (int i = l; i <= r; i++) ans[i] = ql;
    return;
  }
  int cnt = 0,
      mid = ql + ((qr - ql) >> 1);  // 默认开始都填 mid+1 全部划分到右区间
  long long res = 0ll, sum = 0ll;
  for (int i = l; i <= r; i++) sum += abs(1LL * a[i] - (mid + 1));
  res = sum;
  for (int i = l; i <= r;
       i++) {  // 尝试把 [l,i] 从 mid+1 换成 mid 并且划分到左区间
    sum -= abs(1LL * a[i] - (mid + 1));
    sum += abs(1LL * a[i] - mid);
    if (sum < res) cnt = i - l + 1, res = sum;  // 发现 [l,i] 取 mid 更优,更新
  }
  overall_binary(l, l + cnt - 1, ql, mid);
  overall_binary(l + cnt, r, mid + 1, qr);
}

// --8<-- [end:core]

int main() {
  int n;
  if (!(cin >> n)) return 0;
  for (int i = 1; i <= n; ++i) cin >> a[i];
  int low = *min_element(a + 1, a + n + 1);
  int high = *max_element(a + 1, a + n + 1);
  overall_binary(1, n, low, high);
  long long cost = 0;
  for (int i = 1; i <= n; ++i) cost += abs(1LL * a[i] - ans[i]);
  cout << cost << '\n';
}
