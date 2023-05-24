#include <bits/stdc++.h>
#define SZ (10005)
using namespace std;

template <typename _Tp>
void IN(_Tp& dig) {
  char c;
  dig = 0;
  while (c = getchar(), !isdigit(c))
    ;
  while (isdigit(c)) dig = dig * 10 + c - '0', c = getchar();
}

int n, m, sqn, c[SZ], ct[SZ], c1, c2, mem[SZ][3], ans, tot[1000005], nal[SZ];

struct query {
  int l, r, i, c;

  bool operator<(const query another) const {
    if (l / sqn == another.l / sqn) {
      if (r / sqn == another.r / sqn) return i < another.i;
      return r < another.r;
    }
    return l < another.l;
  }
} Q[SZ];

void add(int a) {
  if (!tot[a]) ans++;
  tot[a]++;
}

void del(int a) {
  tot[a]--;
  if (!tot[a]) ans--;
}

char opt[10];

int main() {
  IN(n), IN(m), sqn = pow(n, (double)2 / (double)3);
  for (int i = 1; i <= n; i++) IN(c[i]), ct[i] = c[i];
  for (int i = 1, a, b; i <= m; i++)
    if (scanf("%s", opt), IN(a), IN(b), opt[0] == 'Q')
      Q[c1].l = a, Q[c1].r = b, Q[c1].i = c1, Q[c1].c = c2, c1++;
    else
      mem[c2][0] = a, mem[c2][1] = ct[a], mem[c2][2] = ct[a] = b, c2++;
  sort(Q, Q + c1), add(c[1]);
  int l = 1, r = 1, lst = 0;
  for (int i = 0; i < c1; i++) {
    for (; lst < Q[i].c; lst++) {
      if (l <= mem[lst][0] && mem[lst][0] <= r)
        del(mem[lst][1]), add(mem[lst][2]);
      c[mem[lst][0]] = mem[lst][2];
    }
    for (; lst > Q[i].c; lst--) {
      if (l <= mem[lst - 1][0] && mem[lst - 1][0] <= r)
        del(mem[lst - 1][2]), add(mem[lst - 1][1]);
      c[mem[lst - 1][0]] = mem[lst - 1][1];
    }
    for (++r; r <= Q[i].r; r++) add(c[r]);
    for (--r; r > Q[i].r; r--) del(c[r]);
    for (--l; l >= Q[i].l; l--) add(c[l]);
    for (++l; l < Q[i].l; l++) del(c[l]);
    nal[Q[i].i] = ans;
  }
  for (int i = 0; i < c1; i++) printf("%d\n", nal[i]);
  return 0;
}