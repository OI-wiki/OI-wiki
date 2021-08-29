#include <bits/stdc++.h>
using namespace std;
const int M = 10;
const int offset = 3, mask = (1 << offset) - 1;
int n, m;
long long ans, d;
const int MaxSZ = 16796, Prime = 9973;
struct hashTable {
  int head[Prime], next[MaxSZ], sz;
  int state[MaxSZ];
  long long key[MaxSZ];
  inline void clear() {
    sz = 0;
    memset(head, -1, sizeof(head));
  }
  inline void push(int s) {
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
  void roll() {
    for (int i = 0; i < sz; i++) state[i] <<= offset;
  }
} H[2], *H0, *H1;
int b[M + 1], bb[M + 1];
int encode() {
  int s = 0;
  memset(bb, -1, sizeof(bb));
  int bn = 1;
  bb[0] = 0;
  for (int i = m; i >= 0; --i) {
    if (!~bb[b[i]]) bb[b[i]] = bn++;
    s <<= offset;
    s |= bb[b[i]];
  }
  return s;
}
void decode(int s) {
  for (int i = 0; i < m + 1; i++) {
    b[i] = s & mask;
    s >>= offset;
  }
}
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
      for (int ii = 0; ii < (H0->sz); ii++) {
        decode(H0->state[ii]);
        d = H0->key[ii];
        int lt = b[j], up = b[j + 1];
        bool dn = i != n - 1, rt = j != m - 1;
        if (lt && up) {
          if (lt == up) {
            if (i == n - 1 && j == m - 1) {
              push(j, 0, 0);
            }
          } else {
            for (int i = 0; i < m + 1; i++)
              if (b[i] == lt) b[i] = up;
            push(j, 0, 0);
          }
        } else if (lt || up) {
          int t = lt | up;
          if (dn) {
            push(j, t, 0);
          }
          if (rt) {
            push(j, 0, t);
          }
        } else {
          if (dn && rt) {
            push(j, m, m);
          }
        }
      }
    }
    H1->roll();
  }
  assert(H1->sz <= 1);
  cout << (H1->sz == 1 ? H1->key[0] : 0) << endl;
}