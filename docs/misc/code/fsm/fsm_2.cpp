#include <bits/stdc++.h>
using namespace std;
// 0:0
// 1:1
// 00:2
// 01:3
// 10:4
// 11:5
char op[9];
int q, n;
char a[100010];

struct node {
  vector<bool> sta;
  int x, y;
} l[1 << 10];

int len = 0;

struct DFA {
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

  inline void init() {
    for (int i = 1; i <= cnt; i++) {
      for (int j = 1; j <= (n >> 5); j++) {
        int x = i;
        for (int k = (j << 5); k < ((j + 1) << 5); k++) {
          auto [l, s] = pm[x];
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

  inline bool check(int l, int r) {
    int x = mp[1][a[l]];
    l++;
    while (l <= r && (l & 31)) {
      auto [i, s] = pm[x];
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
      auto [i, s] = pm[x];
      x = mp[i + 1][(s << 1) | a[l]];
      l++;
    }
    return acc[x];
  }
} d[6];

void solve(int l, int r, int type) {
  if (l == r) {
    putchar(a[l] + '0');
    return;
  }
  if (type <= 1) {
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