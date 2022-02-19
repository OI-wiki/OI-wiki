#include <bits/stdc++.h>
const int N = 500 + 10;
int n, m, idx, ans;
int first[N], siz[N], stk[N];
struct DLXNODE {
  int lc, rc, up, dn, r, c;
};
inline int read() {  //快读
  register int x = 0, f = 0, ch;
  while (!isdigit(ch = getchar())) f |= ch == '-';
  while (isdigit(ch)) x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar();
  return f ? -x : x;
}
struct DLX {
  static const int MAXSIZE = 1e5 + 10;
  int n, m, tot, first[MAXSIZE + 10], siz[MAXSIZE + 10];
  int L[MAXSIZE + 10], R[MAXSIZE + 10], U[MAXSIZE + 10], D[MAXSIZE + 10];
  int col[MAXSIZE + 10], row[MAXSIZE + 10];
  void build(const int &r, const int &c) {  //进行build操作
    n = r, m = c;
    for (register int i = 0; i <= c; ++i) {
      L[i] = i - 1, R[i] = i + 1;
      U[i] = D[i] = i;
    }
    L[0] = c, R[c] = 0, tot = c;
    memset(first, 0, sizeof(first));
    memset(siz, 0, sizeof(siz));
  }
  void insert(const int &r, const int &c) {  //进行insert操作
    col[++tot] = c, row[tot] = r, ++siz[c];
    D[tot] = D[c], U[D[c]] = tot, U[tot] = c, D[c] = tot;
    if (!first[r])
      first[r] = L[tot] = R[tot] = tot;
    else {
      R[tot] = R[first[r]], L[R[first[r]]] = tot;
      L[tot] = first[r], R[first[r]] = tot;
    }
  }
  void remove(const int &c) {  //进行remove操作
    register int i, j;
    L[R[c]] = L[c], R[L[c]] = R[c];
    for (i = D[c]; i != c; i = D[i])
      for (j = R[i]; j != i; j = R[j])
        U[D[j]] = U[j], D[U[j]] = D[j], --siz[col[j]];
  }
  void recover(const int &c) {  //进行recover操作
    register int i, j;
    for (i = U[c]; i != c; i = U[i])
      for (j = L[i]; j != i; j = L[j]) U[D[j]] = D[U[j]] = j, ++siz[col[j]];
    L[R[c]] = R[L[c]] = c;
  }
  bool dance(int dep) {  // dance
    if (!R[0]) {
      ans = dep;
      return 1;
    }
    register int i, j, c = R[0];
    for (i = R[0]; i != 0; i = R[i])
      if (siz[i] < siz[c]) c = i;
    remove(c);
    for (i = D[c]; i != c; i = D[i]) {
      stk[dep] = row[i];
      for (j = R[i]; j != i; j = R[j]) remove(col[j]);
      if (dance(dep + 1)) return 1;
      for (j = L[i]; j != i; j = L[j]) recover(col[j]);
    }
    recover(c);
    return 0;
  }
} solver;
int main() {
  n = read(), m = read();
  solver.build(n, m);
  for (register int i = 1; i <= n; ++i)
    for (register int j = 1; j <= m; ++j) {
      int x = read();
      if (x) solver.insert(i, j);
    }
  solver.dance(1);
  if (ans)
    for (register int i = 1; i < ans; ++i) printf("%d ", stk[i]);
  else
    puts("No Solution!");
  return 0;
}
