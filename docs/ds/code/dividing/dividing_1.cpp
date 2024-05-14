#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;
typedef long long lld;

int getint()  // 本题没有负数输入，因此快读不需判断负号。
{
  char ch;
  while ((ch = getchar()) < '!');
  int x = ch ^ '0';
  while ((ch = getchar()) > '!') x = (x * 10) + (ch ^ '0');
  return x;
}

void putll(lld x) {  // 输出long long
  if (x / 10) putll(x / 10);
  putchar((x % 10) ^ '0');
}

int ti[2][17][131073];

int lowbit(int x) { return x & (-x); }

void fixup(int k, int x) {
  for (; lowbit(x) < 1 << k; x += lowbit(x)) {
    ++ti[0][k - 1][x];
  }
  ++ti[0][k - 1][x];
}

void fixdown(int k, int x) {
  for (; ((x ^ lowbit(x)) - 1) >> k == (x - 1) >> k; x ^= lowbit(x)) {
    ++ti[1][k - 1][x];
  }
  ++ti[1][k - 1][x];
}

int queryup(int k, int x) {
  int res = 0;
  for (; lowbit(x) < 1 << k; x += lowbit(x)) {
    res += ti[1][k - 1][x];
  }
  return res + ti[1][k - 1][x];
}

int querydown(int k, int x) {
  int res = 0;
  for (; ((x ^ lowbit(x)) - 1) >> k == (x - 1) >> k; x ^= lowbit(x)) {
    res += ti[0][k - 1][x];
  }
  return res + ti[0][k - 1][x];
}

int ai[100005];
int tx[100005];

lld mgx(int* npi, int* nai, int* rxi, int* lxi, int al, int ar, int bl,
        int br) {
  int rx = 1;
  int lx = ar - al;
  lld res = 0;
  for (; al != ar || bl != br; ++npi, ++nai, ++rxi, ++lxi) {
    if (al != ar && (bl == br || tx[al] < tx[bl])) {
      --lx;
      *rxi = rx;
      *nai = tx[al];
      *npi = al;
      ++al;
    } else {
      ++rx;
      *lxi = lx;
      res += ar - al;
      *nai = tx[bl];
      *npi = bl;
      ++bl;
    }
  }
  return res;
}

int npi[1700005];
int nri[1700005];
int nli[1700005];

int main() {
  const int n = getint();
  const int m = getint();
  for (int i = 1; i <= n; ++i) {
    ai[i] = getint();
  }

  if (n == 1) {
    for (int i = 1; i <= m; ++i) {
      putchar('0');
      putchar('\n');
    }
    return 0;
  }

  const int logn = 31 - __builtin_clz(n - 1);

  lld ans = 0;
  for (int i = logn; i >= 0; --i) {
    memcpy(tx, ai, (n + 1) * sizeof(int));
    for (int j = 1; j <= n; j += 1 << (logn - i + 1)) {
      ans += mgx(npi + n * i + j, ai + j, nri + n * i + j, nli + n * i + j, j,
                 min(n + 1, j + (1 << (logn - i))),
                 min(n + 1, j + (1 << (logn - i))),
                 min(n + 1, j + (1 << (logn - i + 1))));
    }
  }

  putll(ans);
  putchar('\n');

  for (int asdf = 1; asdf < m; ++asdf) {
    int x = getint();
    for (int i = 0, p = 0; i <= logn; ++i, p += n) {
      if (nri[p + x]) {
        ans -= nri[p + x] - querydown(logn - i + 1, x) - 1;
        fixdown(logn - i + 1, x);
      } else {
        ans -= nli[p + x] - queryup(logn - i + 1, x);
        fixup(logn - i + 1, x);
      }
      x = npi[p + x];
    }
    putll(ans);
    putchar('\n');
  }
}