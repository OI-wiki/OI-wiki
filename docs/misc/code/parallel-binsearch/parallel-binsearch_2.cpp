// Sample source: https://www.luogu.com.cn/problem/P3834
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <utility>
#include <vector>
using namespace std;

constexpr int N = 200005;

// --8<-- [start:core]
struct Num {
  int p, x;
};  // 位于数列中第 p 项的数的值为 x

struct Query {
  int l, r, k, id;
};  // 一个编号为 id, 询问 [l,r] 中第 k 小数的询问

int ans[N];
void add(int p, int x);  // 树状数组, 在 p 位置加上 x
int query(int p);        // 树状数组, 求 [1,p] 的和
void clear();            // 树状数组, 清空

void solve(int l, int r, vector<Num> a, vector<Query> q)
// a中为给定数列中值在值域区间 [l,r] 中的数
{
  if (q.empty()) return;
  int m = l + (r - l) / 2;
  if (l == r) {
    for (unsigned i = 0; i < q.size(); i++) ans[q[i].id] = l;
    return;
  }
  vector<Num> a1, a2;
  vector<Query> q1, q2;
  for (unsigned i = 0; i < a.size(); i++)
    if (a[i].x <= m)
      a1.push_back(a[i]), add(a[i].p, 1);
    else
      a2.push_back(a[i]);
  for (unsigned i = 0; i < q.size(); i++) {
    int t = query(q[i].r) - query(q[i].l - 1);
    if (q[i].k <= t)
      q1.push_back(q[i]);
    else
      q[i].k -= t, q2.push_back(q[i]);
  }
  for (const Num& number : a1) add(number.p, -1);
  solve(l, m, a1, q1), solve(m + 1, r, a2, q2);
  return;
}

// --8<-- [end:core]

int n, bit[N];

void add(int p, int x) {
  for (; p <= n; p += p & -p) bit[p] += x;
}

int query(int p) {
  int result = 0;
  for (; p; p -= p & -p) result += bit[p];
  return result;
}

void clear() { fill(bit, bit + n + 1, 0); }

int main() {
  int m;
  if (!(cin >> n >> m)) return 0;
  vector<Num> values(n);
  for (int i = 0; i < n; ++i) cin >> values[i].x, values[i].p = i + 1;
  vector<Query> queries(m);
  for (int i = 0; i < m; ++i) {
    cin >> queries[i].l >> queries[i].r >> queries[i].k;
    queries[i].id = i;
  }
  solve(0, 1000000000, values, queries);
  for (int i = 0; i < m; ++i) cout << ans[i] << '\n';
}
