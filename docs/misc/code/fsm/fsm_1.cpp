#include <algorithm>
#include <cstring>
#include <iostream>
#include <vector>
using namespace std;
// 6 种需要用到的串所对应的 type 编号
// 0:0
// 1:1
// 00:2
// 01:3
// 10:4
// 11:5
char op[9];
int q, n;
char a[100010];

// l 表示每个字符串的后接字符串的接受状态
// l.x, l.y 表示字符串的长度和内容
// l.sta 表示字符串的后接字符串的接受状态
struct node {
  vector<bool> sta;
  int x, y;
} l[1 << 10];

int len = 0;

struct DFA {
  // ac[i][s] 表示长度为 i 的串 s 是否可以接受
  // acc[s] 表示最小化 dfa 后的状态 s 是否可以接受
  // pm[s] 表示状态 s 的所对应等价类中长度最小的字符串的长度与内容
  // mp[l][s] 表示长度为 l 的串 s 所对应的等价类编号
  // f 是倍增数组，底层使用分块减小常数
  // cnt 表示等价类个数
  bool ac[16][1 << 15], acc[60];
  pair<int, int> pm[60];
  int mp[10][1 << 9];
  unsigned char f[60][100010][12];
  int cnt = 0;

  inline void build(int x) {
    if (x <= 1)
      ac[1][x] = 1;
    else
      ac[2][x - 2] = 1;

    // 跑出所有长度 <= 15 的串的接受状态
    for (int i = 3; i <= 15; i++) {
      for (int s = 0; s < (1 << i); s++) {
        int s1 = 0, s2 = s;
        for (int j = 0; j <= i - 3; j++) {
          int v = op[s2 & 7];
          int t = ((((s2 >> 3) << 1) | op[s2 & 7]) << j) | s1;
          ac[i][s] |= ac[i - 2][t];
          s1 |= (s2 & 1) << j;
          s2 >>= 1;
        }
      }
    }

    // 跑出所有长度 <= 9 的串的后接长度 <= 6 的串的接受状态
    len = 0;
    for (int i = 1; i <= 9; i++) {
      for (int s = 0; s < (1 << i); s++) {
        l[++len].sta.clear();
        l[len].x = i, l[len].y = s, l[len].sta.push_back(ac[i][s]);
        for (int j = 1; j <= 6; j++) {
          for (int t = 0; t < (1 << j); t++) {
            l[len].sta.push_back(ac[i + j][(s << j) | t]);
          }
        }
      }
    }

    sort(l + 1, l + len + 1, [](node a, node b) {
      if (a.sta != b.sta) return a.sta < b.sta;
      return a.x < b.x;
    });

    for (int i = 1; i <= len; i++) {
      if (i == 1 || l[i].sta != l[i - 1].sta) {
        mp[l[i].x][l[i].y] = ++cnt;
        pm[cnt] = make_pair(l[i].x, l[i].y);
        acc[cnt] = ac[l[i].x][l[i].y];
      } else {
        mp[l[i].x][l[i].y] = cnt;
      }
    }
  }

  // 预处理倍增
  inline void init() {
    for (int i = 1; i <= cnt; i++) {
      for (int j = 1; j <= (n >> 5); j++) {
        int x = i;
        for (int k = (j << 5); k < ((j + 1) << 5); k++) {
          int l = pm[x].first, s = pm[x].second;
          x = mp[l + 1][(s << 1) | a[k]];
        }
        f[i][j][0] = x;
      }
    }
    for (int k = 1; k <= 11; k++) {
      for (int j = 1; j + (1 << k) - 1 <= (n >> 5); j++) {
        for (int i = 1; i <= cnt; i++) {
          f[i][j][k] = f[f[i][j][k - 1]][j + (1 << (k - 1))][k - 1];
        }
      }
    }
  }

  // 检查区间 [l, r] 是否可以接受
  inline bool check(int l, int r) {
    int x = mp[1][a[l]];
    l++;
    while (l <= r && (l & 31)) {
      int i = pm[x].first, s = pm[x].second;
      x = mp[i + 1][(s << 1) | a[l]];
      l++;
    }
    for (int k = 11; k >= 0; k--) {
      if (l + (1 << (k + 5)) - 1 <= r) {
        x = f[x][l >> 5][k];
        l += (1 << (k + 5));
      }
    }
    while (l <= r) {
      int i = pm[x].first, s = pm[x].second;
      x = mp[i + 1][(s << 1) | a[l]];
      l++;
    }
    return acc[x];
  }
} d[6];

// 分治递归求解，solve(l, r, type) 表示区间 [l, r] 内的串的表示 type 的方案
void solve(int l, int r, int type) {
  if (l == r) {
    putchar(a[l] + '0');
    return;
  }
  if (type <= 1) {
    // 启发式分裂，维护两个指针，一个从左往右扫，一个从右往左扫，以枚举断点
    for (int i = l, j = r; i <= j; i += 2, j -= 2) {
      for (int k = 7; k >= 0; k--) {
        if (op[k] == type && d[k >> 2].check(l, i) &&
            d[(k & 3) + 2].check(i + 1, r)) {
          putchar('(');
          solve(l, i, k >> 2);
          solve(i + 1, r, (k & 3) + 2);
          putchar(')');
          return;
        }
        if (op[k] == type && d[(k >> 1) + 2].check(l, j - 1) &&
            d[k & 1].check(j, r)) {
          putchar('(');
          solve(l, j - 1, (k >> 1) + 2);
          solve(j, r, k & 1);
          putchar(')');
          return;
        }
      }
    }
  } else {
    int k = type - 2;
    for (int i = l, j = r; i <= j; i += 2, j -= 2) {
      if (d[k >> 1].check(l, i) && d[k & 1].check(i + 1, r)) {
        solve(l, i, k >> 1);
        solve(i + 1, r, k & 1);
        return;
      }
      if (d[k >> 1].check(l, j - 1) && d[k & 1].check(j, r)) {
        solve(l, j - 1, k >> 1);
        solve(j, r, k & 1);
        return;
      }
    }
  }
}

int main() {
  scanf("%s %d", op, &q);
  swap(op[1], op[4]);
  swap(op[3], op[6]);
  for (int i = 0; i < 8; i++) op[i] -= '0';
  for (int i = 0; i < 6; i++) d[i].build(i);
  while (q--) {
    scanf("%s", a + 1);
    n = strlen(a + 1);
    for (int i = 1; i <= n; i++) a[i] -= '0';
    for (int i = 0; i < 6; i++) d[i].init();
    if (!d[1].check(1, n)) {
      putchar('-');
      putchar('1');
      putchar('\n');
      continue;
    }
    solve(1, n, 1);
    putchar('\n');
  }
}
