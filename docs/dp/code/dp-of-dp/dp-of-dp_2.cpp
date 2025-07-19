#include <algorithm>
#include <cstdio>
#include <iostream>
#include <map>
#include <unordered_map>
using namespace std;

#define umap unordered_map
#define pr pair
#define fst first
#define snd second
#define pc putchar
#define pb push_back
#define REP(i, x, y) for (int i = x; i <= y; i++)
#define PER(i, x, y) for (int i = y; i >= x; i--)
#define ws(x) (write(x), pc(' '))
#define we(x) (write(x), pc('\n'))

const int N = 100, M = 400, mod = 998244353;

inline void read(int& a) {
  a = 0;
  char c;
  int f = 1;
  while ((c = getchar()) < '0')
    if (c == '-') f = -1;
  do a = (a << 3) + (a << 1) + (c ^ 48);
  while ((c = getchar()) >= '0');
  a *= f;
}

inline void write(int x) {
  if (x < 0) putchar('-'), x = -x;
  if (x > 9) write(x / 10);
  putchar(x % 10 + '0');
}

int n, m, a[N + 5], fact[M + 5], inv[M + 5];

inline int C(int x, int y) {
  return 1LL * fact[x] * inv[y] % mod * inv[x - y] % mod;
}

class HuAutomation {
 private:
  class Mat {
   private:
    int f[3][3];

   public:
    Mat() { REP(i, 0, 2) REP(j, 0, 2) f[i][j] = -1; }

    int* operator[](const int& x) { return f[x]; }

    inline bool operator==(Mat x) const {
      REP(i, 0, 2) REP(j, 0, 2) if (f[i][j] != x[i][j]) return 0;
      return 1;
    }

    inline bool operator<(Mat x) const {
      REP(i, 0, 2)
      REP(j, 0, 2) if (f[i][j] != x[i][j]) return f[i][j] < x[i][j];
      return 0;
    }

    inline bool Check() {
      REP(i, 0, 2) REP(j, 0, 2) if (f[i][j] > 3) return 1;
      return 0;
    }

    inline void Upd(Mat x, int t) {
      REP(i, 0, 2)
      REP(j, 0, 2)
      if (x[i][j] != -1) for (int k = 0; k < 3 && i + j + k <= t; k++) f[j][k] =
          max(f[j][k], min(i + x[i][j] + (t - i - j - k) / 3, 4));
    }
  };

  struct node {
    int t, state[5];
    Mat F[2];

    node() {
      REP(i, 0, 4) state[i] = 0;
      t = 0;
      REP(i, 0, 1) F[i] = Mat();
    }

    inline bool Check() { return t == -1 || t >= 7 || F[1].Check(); }

    node Hu() {
      node x;
      x.t = -1;
      return x;
    }

    bool operator<(const node& x) const {
      if (t == x.t) {
        if (F[0] == x.F[0]) return F[1] < x.F[1];
        return F[0] < x.F[0];
      }
      return t < x.t;
    }

    node operator+(int x) {
      if (Check()) return Hu();
      node res;
      res.F[0].Upd(F[0], x), res.F[1].Upd(F[1], x);
      res.t = t;
      if (x > 1) res.F[1].Upd(F[0], x - 2), ++res.t;
      if (res.Check()) res = Hu();
      return res;
    }
  } A[2100];

  map<node, int> mp;

  inline int Get(node x) {
    if (mp.count(x)) return mp[x];
    mp[x] = ++tot;
    A[tot] = x;
    return tot;
  }

  inline void Expend(int x) { REP(i, 0, 4) A[x].state[i] = Get(A[x] + i); }

  inline node Hu() {
    node x;
    x.t = -1;
    return x;
  }

  inline node Emp() {
    node x;
    x.F[0][0][0] = 0;
    return x;
  }

 public:
  int tot, f[N + 5][M + 5][2100];

  inline void Build() {
    A[1] = Emp(), A[2] = Hu();
    mp[A[1]] = 1, mp[A[2]] = 2;
    tot = 2;
    Expend(1);
    for (int i = 3; i <= tot; i++) Expend(i);
  }

  void DP() {
    f[0][0][1] = 1;
    REP(i, 1, n)
    PER(j, 0, m) REP(k, 1, tot) if (f[i - 1][j][k])
        REP(t, 0, 4 - a[i])(f[i][j + t][A[k].state[a[i] + t]] +=
                            1LL * f[i - 1][j][k] * C(4 - a[i], t) % mod) %= mod;
  }
} Hfu;

inline long long qpow(long long x, int y) {
  long long res = 1;
  while (y) {
    if (y & 1) res = res * x % mod;
    x = x * x % mod;
    y >>= 1;
  }
  return res;
}

void init(int n) {
  fact[0] = 1;
  REP(i, 1, n) fact[i] = 1LL * fact[i - 1] * i % mod;
  inv[n] = qpow(fact[n], mod - 2);
  PER(i, 0, n - 1) inv[i] = 1LL * inv[i + 1] * (i + 1) % mod;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int ans = 0;
  Hfu.Build();
  read(n);
  REP(i, 1, 13) {
    int x, y;
    read(x), read(y);
    ++a[x];
  }
  m = (n << 2) - 13;
  init(m);
  Hfu.DP();
  REP(i, 1, m) {
    (ans += 1LL * Hfu.f[n][i][1] * fact[i] % mod * fact[m - i] % mod) %= mod;
    REP(j, 3, Hfu.tot)
    (ans += 1LL * Hfu.f[n][i][j] * fact[i] % mod * fact[m - i] % mod) %= mod;
  }
  we(1LL * ans * inv[m] % mod + 1);
  return 0;
}