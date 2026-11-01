#define REP(i, n) for (int i = 0; i < (n); ++i)
#include <cassert>
#include <cstring>
#include <iostream>
using namespace std;
constexpr int M = 10;
constexpr int offset = 3, mask = (1 << offset) - 1;
int n, m;
long long ans, d;
// --8<-- [start:hash]
constexpr int MaxSZ = 16796, Prime = 9973;

struct hashTable {
  int head[Prime], next[MaxSZ], sz;
  int state[MaxSZ];
  long long key[MaxSZ];

  void clear() {
    sz = 0;
    memset(head, -1, sizeof(head));
  }

  void push(int s) {
    int x = s % Prime;
    for (int i = head[x]; ~i; i = next[i]) {
      if (state[i] == s) {
        key[i] += d;
        return;
      }
    }
    state[sz] = s, key[sz] = d;
    next[sz] = head[x];
    head[x] = sz++;
  }

  void roll() { REP(i, sz) state[i] <<= offset; }
} H[2], *H0, *H1;

// --8<-- [end:hash]

// --8<-- [start:encoding]
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

// --8<-- [end:encoding]

void push(int j, int dn, int rt) {
  b[j] = dn;
  b[j + 1] = rt;
  H1->push(encode());
}

int main() {
  cin >> n >> m;
  if (m > n) swap(n, m);
  H0 = H, H1 = H + 1;
  H1->clear();
  d = 1;
  H1->push(0);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      swap(H0, H1);
      H1->clear();
      // --8<-- [start:transition]
      REP(ii, H0->sz) {
        decode(H0->state[ii]);                  // 取出状态，并解码
        d = H0->key[ii];                        // 得到增量 delta
        int lt = b[j], up = b[j + 1];           // 左插头，上插头
        bool dn = i != n - 1, rt = j != m - 1;  // 下插头，右插头
        if (lt && up) {                         // 如果左、上均有插头
          if (lt == up) {                       // 来自同一个连通块
            if (i == n - 1 &&
                j == m - 1) {  // 只有在最后一个格子时，才能合并，封闭回路．
              push(j, 0, 0);
            }
          } else {  // 否则，必须合并这两个连通块，因为本题中需要回路覆盖
            REP(i, m + 1) if (b[i] == lt) b[i] = up;
            push(j, 0, 0);
          }
        } else if (lt || up) {  // 如果左、上之中有一个插头
          int t = lt | up;      // 得到这个插头
          if (dn) {             // 如果可以向下延伸
            push(j, t, 0);
          }
          if (rt) {  // 如果可以向右延伸
            push(j, 0, t);
          }
        } else {           // 如果左、上均没有插头
          if (dn && rt) {  // 生成一对新插头
            push(j, m, m);
          }
        }
      }
      // --8<-- [end:transition]
    }
    H1->roll();
  }
  assert(H1->sz <= 1);
  cout << (H1->sz == 1 ? H1->key[0] : 0) << endl;
}