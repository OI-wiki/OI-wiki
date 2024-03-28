#include <bits/stdc++.h>
int numcol, numrow;
int dfn[3000], tx[2], nxt[2], num[50][50], vis[50];
char ans[50][50];
const int f[2] = {-1, 1};
const int table[12][5][2] = {
    // directions of shapes
    {{0, 0}, {1, 0}, {0, 1}},                   // A
    {{0, 0}, {0, 1}, {0, 2}, {0, 3}},           // B
    {{0, 0}, {1, 0}, {0, 1}, {0, 2}},           // C
    {{0, 0}, {1, 0}, {0, 1}, {1, 1}},           // D
    {{0, 0}, {1, 0}, {2, 0}, {2, 1}, {2, 2}},   // E
    {{0, 0}, {0, 1}, {1, 1}, {0, 2}, {0, 3}},   // F
    {{0, 0}, {1, 0}, {0, 1}, {0, 2}, {1, 2}},   // G
    {{0, 0}, {1, 0}, {0, 1}, {1, 1}, {0, 2}},   // H
    {{0, 0}, {0, 1}, {0, 2}, {1, 2}, {1, 3}},   // I
    {{0, 0}, {-1, 1}, {0, 1}, {1, 1}, {0, 2}},  // J
    {{0, 0}, {1, 0}, {1, 1}, {2, 1}, {2, 2}},   // K
    {{0, 0}, {1, 0}, {0, 1}, {0, 2}, {0, 3}},   // L
};
const int len[12] = {3, 4, 4, 4, 5, 5, 5, 5, 5, 5, 5, 5};
const int getx[] = {0,  1,  2,  2,  3,  3,  3,  4,  4,  4,  4,  5,  5,  5,  5,
                    5,  6,  6,  6,  6,  6,  6,  7,  7,  7,  7,  7,  7,  7,  8,
                    8,  8,  8,  8,  8,  8,  8,  9,  9,  9,  9,  9,  9,  9,  9,
                    9,  10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 11, 11, 11, 11,
                    11, 11, 11, 11, 11, 11, 11, 12, 12, 12, 12, 12, 12, 12, 12,
                    12, 12, 12, 12, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13,
                    13, 13, 14, 14, 14, 14, 14, 14, 14, 14, 14};
const int gety[] = {0, 1, 1, 2,  1,  2,  3,  1, 2,  3,  4,  1, 2, 3, 4,  5,  1,
                    2, 3, 4, 5,  6,  1,  2,  3, 4,  5,  6,  7, 1, 2, 3,  4,  5,
                    6, 7, 8, 1,  2,  3,  4,  5, 6,  7,  8,  9, 1, 2, 3,  4,  5,
                    6, 7, 8, 9,  10, 1,  2,  3, 4,  5,  6,  7, 8, 9, 10, 11, 1,
                    2, 3, 4, 5,  6,  7,  8,  9, 10, 11, 12, 1, 2, 3, 4,  5,  6,
                    7, 8, 9, 10, 11, 12, 13, 1, 2,  3,  4,  5, 6, 7, 8,  9};

struct DLX {
  static const int MS = 1e5 + 10;
  int n, m, tot, first[MS], siz[MS];
  int L[MS], R[MS], U[MS], D[MS];
  int col[MS], row[MS];

  void build(const int &r, const int &c) {
    n = r, m = c;
    for (int i = 0; i <= c; ++i) {
      L[i] = i - 1, R[i] = i + 1;
      U[i] = D[i] = i;
    }
    L[0] = c, R[c] = 0, tot = c;
    memset(first, 0, sizeof(first));
    memset(siz, 0, sizeof(siz));
  }

  void insert(const int &r, const int &c) {  // insert
    col[++tot] = c, row[tot] = r, ++siz[c];
    D[tot] = D[c], U[D[c]] = tot, U[tot] = c, D[c] = tot;
    if (!first[r])
      first[r] = L[tot] = R[tot] = tot;
    else
      R[tot] = R[first[r]], L[R[first[r]]] = tot, L[tot] = first[r],
      R[first[r]] = tot;  // !
  }

  void remove(const int &c) {  // remove
    int i, j;
    L[R[c]] = L[c], R[L[c]] = R[c];
    for (i = D[c]; i != c; i = D[i])
      for (j = R[i]; j != i; j = R[j])
        U[D[j]] = U[j], D[U[j]] = D[j], --siz[col[j]];
  }

  void recover(const int &c) {  // recover
    int i, j;
    for (i = U[c]; i != c; i = U[i])
      for (j = L[i]; j != i; j = L[j]) U[D[j]] = D[U[j]] = j, ++siz[col[j]];
    L[R[c]] = R[L[c]] = c;
  }

  bool dance() {  // dance
    if (!R[0]) return 1;
    int i, j, c = R[0];
    for (i = R[0]; i != 0; i = R[i])
      if (siz[i] < siz[c]) c = i;
    remove(c);
    for (i = D[c]; i != c; i = D[i]) {
      if (col[i] <= 55) ans[getx[col[i]]][gety[col[i]]] = dfn[row[i]] + 'A';
      for (j = R[i]; j != i; j = R[j]) {
        remove(col[j]);
        if (col[j] <= 55) ans[getx[col[j]]][gety[col[j]]] = dfn[row[j]] + 'A';
      }
      if (dance()) return 1;
      for (j = L[i]; j != i; j = L[j]) recover(col[j]);
    }
    recover(c);
    return 0;
  }
} solver;

int main() {
  for (int i = 1; i <= 10; ++i) scanf("%s", ans[i] + 1);
  for (int i = 1; i <= 10; ++i)
    for (int j = 1; j <= i; ++j) {
      if (ans[i][j] != '.') vis[ans[i][j] - 'A'] = 1;
      num[i][j] = ++numcol;
    }
  solver.build(2730, numcol + 12);
  /*******build*******/
  for (int id = 0, op; id < 12; ++id) {  // every block
    for (++numcol, op = 0; op <= 1; ++op) {
      for (int dx = 0; dx <= 1; ++dx) {
        for (int dy = 0; dy <= 1; ++dy) {
          for (tx[0] = 1; tx[0] <= 10; ++tx[0]) {
            for (tx[1] = 1; tx[1] <= tx[0]; ++tx[1]) {
              bool flag = 1;
              for (int k = 0; k < len[id]; ++k) {
                nxt[op] = tx[op] + f[dx] * table[id][k][0];
                nxt[op ^ 1] = tx[op ^ 1] + f[dy] * table[id][k][1];
                if (vis[id]) {
                  if (ans[nxt[0]][nxt[1]] != id + 'A') {
                    flag = 0;
                    break;
                  }
                } else if (ans[nxt[0]][nxt[1]] != '.') {
                  flag = 0;
                  break;
                }
              }
              if (!flag) continue;
              dfn[++numrow] = id;
              solver.insert(numrow, numcol);
              for (int k = 0; k < len[id]; ++k) {
                nxt[op] = tx[op] + f[dx] * table[id][k][0];
                nxt[op ^ 1] = tx[op ^ 1] + f[dy] * table[id][k][1];
                solver.insert(numrow, num[nxt[0]][nxt[1]]);
              }
            }
          }
        }
      }
    }
  }
  /********end********/
  if (!solver.dance())
    puts("No solution");
  else
    for (int i = 1; i <= 10; ++i, puts(""))
      for (int j = 1; j <= i; ++j) putchar(ans[i][j]);
  return 0;
}
