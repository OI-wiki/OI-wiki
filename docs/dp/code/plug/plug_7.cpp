#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
#define REP(i, n) for (int i = 0; i < n; ++i)

template <class T>
bool checkMin(T &a, const T b) {
  return b < a ? a = b, true : false;
}

constexpr int N = 10, M = N;
constexpr int offset = 3, mask = (1 << offset) - 1;
int n, m;
int d;
constexpr int INF = 0x3f3f3f3f;
int b[M + 1], bb[M + 1];

int encode() {
  int s = 0;
  memset(bb, -1, sizeof(bb));
  int bn = 1;
  bb[0] = 0;
  for (int i = m; i >= 0; --i) {
#define bi bb[b[i]]
    if (!~bi) bi = bn++;
    s <<= offset;
    s |= bi;
  }
  return s;
}

void decode(int s) {
  REP(i, m + 1) {
    b[i] = s & mask;
    s >>= offset;
  }
}

constexpr int MaxSZ = 16796, Prime = 9973;

struct hashTable {
  int head[Prime], next[MaxSZ], sz;
  int state[MaxSZ];
  int key[MaxSZ];

  void clear() {
    sz = 0;
    memset(head, -1, sizeof(head));
  }

  void push(int s) {
    int x = s % Prime;
    for (int i = head[x]; ~i; i = next[i]) {
      if (state[i] == s) {
        checkMin(key[i], d);
        return;
      }
    }
    state[sz] = s, key[sz] = d;
    next[sz] = head[x];
    head[x] = sz++;
  }

  void roll() { REP(i, sz) state[i] <<= offset; }
} H[2], *H0, *H1;

char A[N + 1][M + 1];

void push(int i, int j, int dn, int rt) {
  b[j] = dn;
  b[j + 1] = rt;
  if (A[i][j] != '.') {
    bool bad = A[i][j] == 'o';
    REP(jj, j + 1) if (b[jj]) bad ^= 1;
    if (bad) return;
  }
  H1->push(encode());
}

int solve() {
  cin >> n >> m;
  int ti = 0, tj = 0;
  REP(i, n) {
    scanf("%s", A[i]);
    REP(j, m) if (A[i][j] == 'o') ti = i, tj = j;
    A[i][m] = '.';
  }
  REP(j, m + 1) A[n][j] = '.';
  ++n, ++m, ++ti, ++tj;
  H0 = H, H1 = H + 1;
  H1->clear();
  d = 0;
  H1->push(0);
  int z = INF;
  REP(i, n) {
    REP(j, m) {
      swap(H0, H1);
      H1->clear();
      REP(ii, H0->sz) {
        decode(H0->state[ii]);
        d = H0->key[ii] + 1;
        int lt = b[j], up = b[j + 1];
        bool dn = i != n - 1, rt = j != m - 1;
        if (lt && up) {
          if (lt == up) {
            int cnt = 0;
            REP(i, m + 1) if (b[i])++ cnt;
            if (cnt == 2 && i == ti && j == tj) {
              checkMin(z, d);
            }
          } else {
            REP(i, m + 1) if (b[i] == lt) b[i] = up;
            push(i, j, 0, 0);
          }
        } else if (lt || up) {
          int t = lt | up;
          if (dn) {
            push(i, j, t, 0);
          }
          if (rt) {
            push(i, j, 0, t);
          }
        } else {
          --d;
          push(i, j, 0, 0);
          ++d;
          if (dn && rt) {
            push(i, j, m, m);
          }
        }
      }
    }
    H1->roll();
  }
  if (z == INF) z = -1;
  return z;
}

int main() {
  int T;
  cin >> T;
  for (int Case = 1; Case <= T; ++Case) {
    printf("Case #%d: %d\n", Case, solve());
  }
}
