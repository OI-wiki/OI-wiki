#include <algorithm>
#include <iostream>
#define ls(x) T[x][0]
#define rs(x) T[x][1]
#define ms(x) T[x][2]
using namespace std;

constexpr int MAXN = 600005;

int T[MAXN][3], tot, r[MAXN], top, st[MAXN], f[MAXN], maxs[MAXN], ss[MAXN];

int nnd() {
  if (top) {
    top--;
    return st[top + 1];
  }
  return ++tot;
}

bool isr(int x) { return rs(f[x]) != x && ls(f[x]) != x; }

bool dir(int x) { return rs(f[x]) == x; }

void psr(int x) {
  if (!x) return;
  r[x] ^= 1;
  swap(ls(x), rs(x));
}

void psd(int x, int ty) {
  if (ty) return;
  if (r[x]) {
    psr(ls(x));
    psr(rs(x));
    r[x] = 0;
  }
}

void psu(int x, int op) {
  psd(x, op); /*不知道哪没 psd*/
  if (op == 0) {
    ss[x] = ss[ls(x)] + ss[rs(x)] + ss[ms(x)] + 1;
  } else {
    maxs[x] = max(maxs[ls(x)], max(maxs[rs(x)], ss[ms(x)]));
    ss[x] = ss[ls(x)] + ss[rs(x)] + ss[ms(x)];
  }
}

void upd(int x, int ty) {
  if (!isr(x)) upd(f[x], ty);
  psd(x, ty);
}

void stf(int x, int fa, int ty) {
  if (x) f[x] = fa;
  T[fa][ty] = x;
}

void rtt(int x, int ty) {
  int y = f[x], z = f[y], d = dir(x), w = T[x][d ^ 1];
  if (z) T[z][ms(z) == y ? 2 : dir(y)] = x;
  T[x][d ^ 1] = y;
  T[y][d] = w;
  if (w) f[w] = y;
  f[y] = x;
  f[x] = z;
  psu(y, ty);
  psu(x, ty);
}

void spy(int x, int ty, int gl = 0) {
  upd(x, ty);
  for (int y; y = f[x], (!isr(x)) && y != gl; rtt(x, ty)) {
    if (f[y] != gl && (!isr(y))) rtt(dir(x) ^ dir(y) ? x : y, ty);
  }
}

void cle(int x) {
  ls(x) = ms(x) = rs(x) = ss[x] = r[x] = maxs[x] = f[x] = 0;
  st[++top] = x;
}

void del(int x) {
  stf(ms(x), f[x], 1);
  if (ls(x)) {
    int p = ls(x);
    psd(p, 1);
    while (rs(p)) p = rs(p), psd(p, 1);
    spy(p, 1, x);
    stf(rs(x), p, 1);
    stf(p, f[x], 2);
    psu(p, 1);
    psu(f[x], 0);
  } else
    stf(rs(x), f[x], 2);
  cle(x);
}

void spl(int x) {
  spy(x, 1);
  int y = f[x];
  spy(y, 0);
  psd(x, 1);
  if (rs(y)) {
    swap(f[ms(x)], f[rs(y)]);
    swap(ms(x), rs(y));
  } else
    del(x);
  psu(x, 1);
  psu(y, 0);
  rtt(rs(y), 0);
}

void acs(int x) {
  spy(x, 0);
  if (rs(x)) {
    int y = nnd();
    stf(ms(x), y, 0);
    stf(rs(x), y, 2);
    rs(x) = 0;
    stf(y, x, 2);
    psu(y, 1);
    psu(x, 0);
  }
  while (f[x]) spl(f[x]);
}

void mkr(int x) {
  acs(x);
  psr(x);
}

void epo(int x, int y) {
  mkr(x);
  acs(y);
}

void lnk(int x, int y) {
  acs(x);
  mkr(y);
  stf(y, x, 1);
  psu(x, 0);
}

void cu(int x, int y) {
  epo(x, y);
  f[x] = ls(y) = 0;
  psu(y, 0);
}

int ans1, ans2;

void non_local_search(int x, int lv, int rv, int op) {
  if (!x) return;
  psd(x, 0);
  if (op == 0) {
    if (maxs[ms(x)] >=
        ss[ms(x)] - maxs[ms(x)] + ss[rs(x)] + ss[ls(x)] + lv + 1 + rv) {
      if (maxs[ms(x)] ==
          ss[ms(x)] - maxs[ms(x)] + ss[rs(x)] + ss[ls(x)] + lv + 1 + rv) {
        if (ans1)
          ans2 = x;
        else
          ans1 = x;
      }
      non_local_search(
          ms(x), ss[ms(x)] - maxs[ms(x)] + ss[rs(x)] + ss[ls(x)] + 1 + lv + rv,
          0, 1);
      return;
    }
    if (ss[rs(x)] + rv >= ss[ms(x)] + ss[ls(x)] + lv + 1) {
      if (ss[rs(x)] + rv == ss[ms(x)] + ss[ls(x)] + lv + 1) {
        if (ans1)
          ans2 = x;
        else
          ans1 = x;
      }
      non_local_search(rs(x), ss[ms(x)] + 1 + ss[ls(x)] + lv, rv, 0);
      return;
    }
    if (ss[ls(x)] + lv >= ss[ms(x)] + ss[rs(x)] + 1 + rv) {
      if (ss[ls(x)] + lv == ss[ms(x)] + ss[rs(x)] + 1 + rv) {
        if (ans1)
          ans2 = x;
        else
          ans1 = x;
      }
      non_local_search(ls(x), lv, rv + ss[ms(x)] + 1 + ss[rs(x)], 0);
      return;
    }
  } else {
    if (maxs[ls(x)] == maxs[x]) {
      non_local_search(ls(x), lv, rv, 1);
      return;
    }
    if (maxs[rs(x)] == maxs[x]) {
      non_local_search(rs(x), lv, rv, 1);
      return;
    }
    non_local_search(ms(x), lv, rv, 0);
    return;
  }
  if (ans1)
    ans2 = x;
  else
    ans1 = x;
  return;
}

int qu[MAXN], qv[MAXN];

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  int TT;
  cin >> TT;
  while (TT--) {
    int n;
    cin >> n;
    tot = n;
    long long ANS = 0;
    for (int i = 1; i <= n; i++) ss[i] = 1;
    for (int i = 1; i < n; i++) {
      cin >> qu[i] >> qv[i];
      lnk(qu[i], qv[i]);
    }
    for (int i = 1; i < n; i++) {
      cu(qu[i], qv[i]);
      ans1 = 0;
      ans2 = 0;
      non_local_search(qu[i], 0, 0, 0);
      ANS += ans1 + ans2;
      if (ans1) acs(ans1);
      if (ans2) acs(ans2);
      ans1 = 0;
      ans2 = 0;
      non_local_search(qv[i], 0, 0, 0);
      ANS += ans1 + ans2;
      if (ans1) acs(ans1);
      if (ans2) acs(ans2);
      lnk(qu[i], qv[i]);
    }
    cout << ANS << '\n';
    for (int i = 1; i <= tot; i++)
      T[i][0] = T[i][1] = T[i][2] = ss[i] = r[i] = maxs[i] = f[i] = 0;
    tot = top = 0;
  }
  return 0;
}
