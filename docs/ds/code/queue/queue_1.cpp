#include <algorithm>
#include <cctype>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <vector>
using namespace std;
/******************heading******************/
const int M = 5e4 + 5, P = 505;  // 定义常数
int I, m, p;

inline int _(int d) { return (d + p) % p; }  // 用于取模

namespace DQ {                // 双栈模拟双端队列
pair<int, int> fr[M], bc[M];  // 二元组，详见题目3.4
int tf = 0, tb = 0;           // 一端的top,因为是双端队列所以有俩
int ff[M][P], fb[M][P];

void update(pair<int, int> *s, int f[][P], int i) {  // 用f[i-1]更新f[i]
  for (int j = 0; j <= (p - 1); j++) {
    f[i][j] = f[i - 1][j];
    if (~f[i - 1][_(j - s[i].first)])  // 按位取反
      f[i][j] = max(f[i][j], f[i - 1][_(j - s[i].first)] + s[i].second);
  }
}

// 以下两行代码表示push入队列，很好理解
void push_front(pair<int, int> x) { fr[++tf] = x, update(fr, ff, tf); }

void push_back(pair<int, int> x) { bc[++tb] = x, update(bc, fb, tb); }

// 以下两行代码表示从队列pop出元素
void pop_front() {
  if (tf) {
    --tf;
    return;
  }
  int mid = (tb + 1) / 2, top = tb;
  for (int i = mid; i >= 1; i--) push_front(bc[i]);
  tb = 0;
  for (int i = (mid + 1); i <= top; i++) push_back(bc[i]);
  --tf;
  // 上面的代码，逻辑和普通队列是一样的
}

void pop_back() {
  if (tb) {
    --tb;
    return;
  }
  int mid = (tf + 1) / 2, top = tf;
  for (int i = mid; i >= 1; i--) push_back(fr[i]);
  tf = 0;
  for (int i = (mid + 1); i <= top; i++) push_front(fr[i]);
  --tb;
  // 上面的代码，逻辑和普通队列是一样的
}

int q[M], ql, qr;  // 题目任务5要求的

int query(int l, int r) {
  const int *const f = ff[tf], *const g = fb[tb];
  int ans = -1;
  ql = 1, qr = 0;
  for (int i = (l - p + 1); i <= (r - p + 1); i++) {
    int x = g[_(i)];
    while (ql <= qr && g[q[qr]] <= x) --qr;
    q[++qr] = _(i);
  }
  for (int i = (p - 1); i >= 0; i--) {
    if (ql <= qr && ~f[i] && ~g[q[ql]]) ans = max(ans, f[i] + g[q[ql]]);
    // 删 l-i，加 r-i+1
    if (ql <= qr && _(l - i) == q[ql]) ++ql;
    int x = g[_(r - i + 1)];
    while (ql <= qr && g[q[qr]] <= x) --qr;
    q[++qr] = _(r - i + 1);
  }
  return ans;
}

void init() {
  for (int i = 1; i <= (P - 1); i++) ff[0][i] = fb[0][i] = -1;
}  // 初始化
}  // namespace DQ

int main() {
  DQ::init();
  scanf("%d%d%d", &I, &m, &p);
  for (int i = 1; i <= m; i++) {
    char op[5];
    int x, y;
    scanf("%s%d%d", op, &x, &y);
    if (op[0] == 'I' && op[1] == 'F')
      DQ::push_front(make_pair(_(x), y));
    else if (op[0] == 'I' && op[1] == 'G')
      DQ::push_back(make_pair(_(x), y));
    else if (op[0] == 'D' && op[1] == 'F')
      DQ::pop_front();
    else if (op[0] == 'D' && op[1] == 'G')
      DQ::pop_back();
    else
      printf("%d\n", DQ::query(x, y));
  }
  return 0;
}

/* example.in
0
11 10
QU 0 0
QU 1 9
IG 14 7
IF 3 5
QU 0 9
IG 1 8
DF
QU 0 4
IF 1 2
DG
QU 2 9
 */
/* example.out
0
-1
12
8
9
 */
/* LOJ:https://loj.ac/s/1149797*/