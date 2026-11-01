#include <iostream>
#include <stack>
#include <vector>
using namespace std;
constexpr int N = 100005;
using Object = long long;

Object Merge(Object a, Object b) { return a + b; }

// --8<-- [start:core]
#define ls (i << 1)
#define rs (i << 1 | 1)
#define mid ((l + r) >> 1)

vector<Object> tree[N << 2];  // 线段树

void update(int ql, int qr, Object obj, int i, int l, int r) {  // 插入
  if (ql <= l && r <= qr) {
    tree[i].push_back(obj);
    return;
  }
  if (ql <= mid) update(ql, qr, obj, ls, l, mid);
  if (qr > mid) update(ql, qr, obj, rs, mid + 1, r);
}

stack<Object> sta;  // 用于撤销的栈
Object now;         // 当前的信息并
Object ans[N];      // 答案

void solve(int i, int l, int r) {
  auto lvl = sta.size();  // 记录一下应当撤销到第几个
  for (Object x : tree[i]) sta.push(now), now = Merge(now, x);  // 合并信息
  if (l == r)
    ans[l] = now;  // 记录一下答案
  else
    solve(ls, l, mid), solve(rs, mid + 1, r);  // 分治
  while (sta.size() != lvl) {                  // 撤销信息
    now = sta.top();
    sta.pop();
  }
}

// --8<-- [end:core]

int main() {
  int n, q;
  cin >> n >> q;
  while (q--) {
    int l, r;
    long long x;
    cin >> l >> r >> x;
    update(l, r, x, 1, 1, n);
  }
  solve(1, 1, n);
  for (int j = 1; j <= n; ++j) cout << ans[j] << (j == n ? "\n" : " ");
}
