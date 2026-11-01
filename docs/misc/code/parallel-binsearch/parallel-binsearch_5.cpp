// Sample source: https://www.luogu.com.cn/problem/P3834
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <utility>
#include <vector>
using namespace std;

// --8<-- [start:core]
struct Query {
  int i, l, r, k;
};  // 第 i 次询问查询区间 [l,r] 的第 k 小值

Query s[200005], t1[200005], t2[200005];
int n, m, cnt, pos, p[200005], ans[200005];
pair<int, int> a[200005];

void add(int x, int y);  // 树状数组 位置 x 加 y
int sum(int x);          // 树状数组 [1,x] 前缀和

// 当前处理的询问为 [l,r],答案值域为 [ql,qr]
void overall_binary(int l, int r, int ql, int qr) {
  if (l > r) return;
  if (ql == qr) {
    for (int i = l; i <= r; i++) ans[s[i].i] = ql;
    return;
  }
  int cnt1 = 0, cnt2 = 0, mid = (ql + qr) >> 1;
  // 追踪分治中心,认为 [1,pos] 的值已经载入树状数组
  while (pos <= n - 1 && a[pos + 1].first <= mid)
    add(a[pos + 1].second, 1), ++pos;
  while (pos >= 1 && a[pos].first > mid) add(a[pos].second, -1), --pos;

  for (int i = l; i <= r; i++) {
    int now = sum(s[i].r) - sum(s[i].l - 1);
    if (s[i].k <= now)
      t1[++cnt1] = s[i];
    else
      t2[++cnt2] = s[i];  // 注意 不应修改询问信息
  }
  for (int i = 1; i <= cnt1; i++) s[l + i - 1] = t1[i];
  for (int i = 1; i <= cnt2; i++) s[l + cnt1 + i - 1] = t2[i];

  overall_binary(l, l + cnt1 - 1, ql, mid);
  overall_binary(l + cnt1, r, mid + 1, qr);
}

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; i++) {
    scanf("%d", &a[i].first);
    a[i].second = i;
    p[++cnt] = a[i].first;
  }
  sort(a + 1, a + n + 1);  // 对序列排序 离散化
  sort(p + 1, p + n + 1);
  cnt = unique(p + 1, p + n + 1) - p - 1;
  for (int i = 1; i <= n; i++)
    a[i].first = lower_bound(p + 1, p + cnt + 1, a[i].first) - p;
  for (int i = 1; i <= m; ++i) {
    scanf("%d%d%d", &s[i].l, &s[i].r, &s[i].k);
    s[i].i = i;
  }
  overall_binary(1, m, 1, cnt);
  for (int i = 1; i <= m; i++) printf("%d\n", p[ans[i]]);
  return 0;
}

// --8<-- [end:core]

int bit[200005];

void add(int x, int y) {
  for (; x <= n; x += x & -x) bit[x] += y;
}

int sum(int x) {
  int result = 0;
  for (; x; x -= x & -x) result += bit[x];
  return result;
}
