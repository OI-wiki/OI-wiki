#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <utility>
#include <vector>
using namespace std;

constexpr int N = 200005;

// --8<-- [start:core]
struct Query {
  int id, k;  // 这个询问的编号, 这个询问的 k
};

int ans[N], a[N];  // ans[i] 表示编号为i的询问的答案，a 为原数列
int val[N], cnt[N];  // 离散化后，记录对应的值及其计数（假设已经处理好）

// 返回原数列中值域在 [l,r] 中的数的个数
int check(int l, int r) {
  int res = 0;
  for (int i = l; i <= r; i++) {
    res += cnt[i];
  }
  return res;
}

// 整体二分
void solve(int l, int r, vector<Query> q) {
  if (q.empty()) return;
  int m = (l + r) / 2;
  if (l == r) {
    for (unsigned i = 0; i < q.size(); i++) ans[q[i].id] = val[l];
    return;
  }
  vector<Query> q1, q2;
  int t = check(l, m);
  for (unsigned i = 0; i < q.size(); i++) {
    if (q[i].k <= t)
      q1.push_back(q[i]);
    else
      q[i].k -= t, q2.push_back(q[i]);
  }
  solve(l, m, q1), solve(m + 1, r, q2);
  return;
}

// --8<-- [end:core]

int main() {
  int n, m;
  if (!(cin >> n >> m)) return 0;
  for (int i = 1; i <= n; ++i) cin >> a[i], val[i] = a[i];
  sort(val + 1, val + n + 1);
  int size = unique(val + 1, val + n + 1) - val - 1;
  for (int i = 1; i <= n; ++i)
    ++cnt[lower_bound(val + 1, val + size + 1, a[i]) - val];
  vector<Query> queries(m);
  for (int i = 0; i < m; ++i) cin >> queries[i].k, queries[i].id = i;
  solve(1, size, queries);
  for (int i = 0; i < m; ++i) cout << ans[i] << '\n';
}
