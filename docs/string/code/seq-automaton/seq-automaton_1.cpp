#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;

const int N = 2005;

char s[N], t[N];
int na[N][26], nb[N][26], nxt[26];
int n, m, a[N], b[N], tot = 1, p = 1, f[N][N << 1];

struct SAM {
  int par, ch[26], len;
} sam[N << 1];

void insert(int x) {
  int np = ++tot;  // 新节点
  sam[np].len = sam[p].len + 1;
  while (p && !sam[p].ch[x]) {
    sam[p].ch[x] = np;
    p = sam[p].par;
  }
  if (p == 0)
    sam[np].par = 1;
  else {
    int q = sam[p].ch[x];
    if (sam[q].len == sam[p].len + 1)
      sam[np].par = q;
    else {
      int nq = ++tot;
      sam[nq].len = sam[p].len + 1;
      memcpy(sam[nq].ch, sam[q].ch, sizeof(sam[q].ch));
      sam[nq].par = sam[q].par;
      sam[q].par = sam[np].par = nq;
      while (p && sam[p].ch[x] == q) {
        sam[p].ch[x] = nq;
        p = sam[p].par;
      }
    }
  }
  p = np;
}

int main() {
  scanf("%s%s", s + 1, t + 1);

  n = strlen(s + 1);
  m = strlen(t + 1);

  for (int i = 1; i <= n; ++i) a[i] = s[i] - 'a';
  for (int i = 1; i <= m; ++i) b[i] = t[i] - 'a';

  for (int i = 1; i <= m; ++i) insert(b[i]);

  // nxt[S[i]]<-i
  for (int i = 0; i < 26; ++i) nxt[i] = n + 1;
  for (int i = n; i >= 0; --i) {
    memcpy(na[i], nxt, sizeof(nxt));
    nxt[a[i]] = i;
  }

  for (int i = 0; i < 26; ++i) nxt[i] = m + 1;
  for (int i = m; i >= 0; --i) {
    memcpy(nb[i], nxt, sizeof(nxt));
    nxt[b[i]] = i;
  }

  // 四种情况计算答案
  //  1
  int ans = N;
  for (int l = 1; l <= n; ++l) {
    for (int r = l, u = 1; r <= n; ++r) {
      u = sam[u].ch[a[r]];
      if (!u) {
        ans = min(ans, r - l + 1);
        break;
      }
    }
  }

  printf("%d\n", ans == N ? -1 : ans);

  // 2
  ans = N;

  for (int l = 1; l <= n; ++l) {
    for (int r = l, u = 0; r <= n; ++r) {
      u = nb[u][a[r]];
      if (u == m + 1) {
        ans = min(ans, r - l + 1);
        break;
      }
    }
  }

  printf("%d\n", ans == N ? -1 : ans);

  // 3
  for (int i = n; i >= 0; --i) {
    for (int j = 1; j <= tot; ++j) {
      f[i][j] = N;
      for (int c = 0; c < 26; ++c) {
        int u = na[i][c];
        int v = sam[j].ch[c];
        if (u <= n) f[i][j] = min(f[i][j], f[u][v] + 1);
      }
    }
  }

  printf("%d\n", f[0][1] == N ? -1 : f[0][1]);

  // 4
  memset(f, 0, sizeof(f));

  for (int i = n; i >= 0; --i) {
    for (int j = 0; j <= m; ++j) {
      f[i][j] = N;
      for (int c = 0; c < 26; ++c) {
        int u = na[i][c];
        int v = nb[j][c];
        if (u <= n) f[i][j] = min(f[i][j], f[u][v] + 1);
      }
    }
  }

  printf("%d\n", f[0][0] == N ? -1 : f[0][0]);

  return 0;
}
