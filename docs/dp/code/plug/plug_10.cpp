#include <cstdio>
#define REP(i, n) for (int i = 0; i < (n); ++i)
#define DWN(i, n, low) for (int i = (n) - 1; i >= (low); --i)
#include <algorithm>
#include <cassert>
#include <cstring>
#include <iostream>
using namespace std;
using T_state = long long;
using T_key = int;
constexpr int N = 8;
int n, m;
char A[N + 1][N + 1], B[N + 1][N + 1];
// --8<-- [start:encoding]
constexpr int Offset = 5, Mask = (1 << Offset) - 1;
int c[N + 2];
int b[N + 2], bb[N + 3];

T_state encode() {
  T_state s = 0;
  memset(bb, -1, sizeof(bb));
  int bn = 1;
  bb[0] = 0;
  for (int i = m; i >= 0; --i) {
#define bi bb[b[i]]
    if (!~bi) bi = bn++;
    s <<= Offset;
    s |= (bi << 1) | c[i];
  }
  return s;
}

void decode(T_state s) {
  REP(i, m + 1) {
    b[i] = s & Mask;
    c[i] = b[i] & 1;
    b[i] >>= 1;
    s >>= Offset;
  }
}

// --8<-- [end:encoding]

// --8<-- [start:hash]
constexpr int Prime = 9979, MaxSZ = 1 << 20;

template <class T_state, class T_key>
struct hashTable {
  int head[Prime];
  int next[MaxSZ], sz;
  T_state state[MaxSZ];
  T_key key[MaxSZ];
  int pre[MaxSZ];

  void clear() {
    sz = 0;
    memset(head, -1, sizeof(head));
  }

  void push(T_state s, T_key d, T_state u) {
    int x = s % Prime;
    for (int i = head[x]; ~i; i = next[i]) {
      if (state[i] == s) {
        key[i] += d;
        return;
      }
    }
    state[sz] = s, key[sz] = d, pre[sz] = u;
    next[sz] = head[x], head[x] = sz++;
  }

  void roll() { REP(ii, sz) state[ii] <<= Offset; }
};

hashTable<T_state, T_key> _H, H[N][N], *H0, *H1;

// --8<-- [end:hash]

// --8<-- [start:connectivity]
bool ok(int i, int j, int cc) {
  if (cc == c[j + 1]) return true;
  int up = b[j + 1];
  if (!up) return true;
  int c1 = 0, c2 = 0;
  REP(i, m + 1) if (i != j + 1) {
    if (b[i] == b[j + 1]) {  // 连通性相同，颜色一定相同
      assert(c[i] == c[j + 1]);
    }
    if (c[i] == c[j + 1] && b[i] == b[j + 1]) ++c1;
    if (c[i] == c[j + 1]) ++c2;
  }
  if (!c1) {               // 如果会生成新的封闭连通块
    if (c2) return false;  // 如果轮廓线上还有相同的颜色
    if (i < n - 1 || j < m - 2) return false;
  }
  return true;
}

// --8<-- [end:connectivity]

// --8<-- [start:transition]
void trans(int i, int j, int u, int cc) {
  decode(H0->state[u]);
  int lf = j ? c[j - 1] : -1, lu = b[j] ? c[j] : -1,
      up = b[j + 1] ? c[j + 1] : -1;  // 没有颜色也是颜色的一种！
  if (lf == cc && up == cc) {         // 合并
    if (lu == cc) return;             // 2x2 子矩形相同的情况
    int lf_b = b[j - 1], up_b = b[j + 1];
    REP(i, m + 1) if (b[i] == up_b) { b[i] = lf_b; }
    b[j] = lf_b;
  } else if (lf == cc || up == cc) {  // 继承
    if (lf == cc)
      b[j] = b[j - 1];
    else
      b[j] = b[j + 1];
  } else {                                             // 生成
    if (i == n - 1 && j == m - 1 && lu == cc) return;  // 特判
    b[j] = m + 2;
  }
  c[j] = cc;
  if (!ok(i, j, cc)) return;  // 判断是否会因生成封闭的连通块导致不合法
  H1->push(encode(), H0->key[u], u);
}

// --8<-- [end:transition]

void init() {
  cin >> n >> m;
  for (int i = 0; i < n; i++) cin >> A[i];
}

void solve() {
  H1 = &_H, H1->clear(), H1->push(0, 1, 0);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      H0 = H1, H1 = &H[i][j], H1->clear();
      for (int u = 0; u < H0->sz; u++) {
        if (A[i][j] == '.' || A[i][j] == '#') trans(i, j, u, 0);
        if (A[i][j] == '.' || A[i][j] == 'o') trans(i, j, u, 1);
      }
    }
    H1->roll();
  }
}

// --8<-- [start:reconstruction]
void print() {
  T_key z = 0;
  int u = 0;
  REP(i, H1->sz) {
    decode(H1->state[i]);
    if (*max_element(b + 1, b + m + 1) <= 2) {
      z += H1->key[i];
      u = i;
    }
  }
  cout << z << endl;
  if (z) {
    DWN(i, n, 0) {
      B[i][m] = 0;
      DWN(j, m, 0) {
        decode(H[i][j].state[u]);
        int cc = j == m - 1 ? c[j + 1] : c[j];
        B[i][j] = cc ? 'o' : '#';
        u = H[i][j].pre[u];
      }
    }
    REP(i, n) puts(B[i]);
  }
  puts("");
}

// --8<-- [end:reconstruction]

int main() {
  int T;
  cin >> T;
  while (T--) {
    init();
    solve();
    print();
  }
}