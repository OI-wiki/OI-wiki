// Sample source: https://www.luogu.com.cn/problem/P2617
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <utility>
#include <vector>
using namespace std;

constexpr int N = 300005;

// --8<-- [start:core]
struct Opt {
  int x, y, k, type, id;
  // 对于询问, type = 1, x, y 表示区间左右边界, k 表示询问第 k 小
  // 对于修改, type = 0, x 表示修改位置, y 表示修改后的值,
  // k 表示当前操作是插入(1)还是擦除(-1), 更新树状数组时使用.
  // id 记录每个操作原先的编号, 因二分过程中操作顺序会被打散
};

Opt q[N], q1[N], q2[N];
// q 为所有操作,
// 二分过程中, 分到左边的操作存到 q1 中, 分到右边的操作存到 q2 中.
int ans[N];
void add(int p, int x);
int query(int p);  // 树状数组函数, 含义见题3

void solve(int l, int r, int L, int R)
// 当前的值域范围为 [l,r], 处理的操作的区间为 [L,R]
{
  if (l > r || L > R) return;
  int cnt1 = 0, cnt2 = 0, m = (l + r) / 2;
  // cnt1, cnt2 分别为分到左边, 分到右边的操作数
  if (l == r) {
    for (int i = L; i <= R; i++)
      if (q[i].type == 1) ans[q[i].id] = l;
    return;
  }
  for (int i = L; i <= R; i++)
    if (q[i].type == 1) {  // 是询问: 进行分类
      int t = query(q[i].y) - query(q[i].x - 1);
      if (q[i].k <= t)
        q1[++cnt1] = q[i];
      else
        q[i].k -= t, q2[++cnt2] = q[i];
    } else
      // 是修改: 更新树状数组 & 分类
      if (q[i].y <= m)
        add(q[i].x, q[i].k), q1[++cnt1] = q[i];
      else
        q2[++cnt2] = q[i];
  for (int i = 1; i <= cnt1; i++)
    if (q1[i].type == 0) add(q1[i].x, -q1[i].k);  // 清空树状数组
  for (int i = 1; i <= cnt1; i++) q[L + i - 1] = q1[i];
  for (int i = 1; i <= cnt2; i++)
    q[L + cnt1 + i - 1] = q2[i];  // 将临时数组中的元素合并回原数组
  solve(l, m, L, L + cnt1 - 1), solve(m + 1, r, L + cnt1, R);
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
  vector<int> values(n + 1);
  int total = 0, queries = 0;
  for (int i = 1; i <= n; ++i) {
    cin >> values[i];
    q[++total] = Opt{i, values[i], 1, 0, 0};
  }
  while (m--) {
    char type;
    int x, y, k;
    cin >> type >> x >> y;
    if (type == 'Q') {
      cin >> k;
      q[++total] = Opt{x, y, k, 1, ++queries};
    } else {
      q[++total] = Opt{x, values[x], -1, 0, 0};
      q[++total] = Opt{x, y, 1, 0, 0};
      values[x] = y;
    }
  }
  solve(0, 1000000000, 1, total);
  for (int i = 1; i <= queries; ++i) cout << ans[i] << '\n';
}
