#include <cstdio>
#include <cstring>

using std::memset;

// --8<-- [start:iteration]
#define IT(i, A, x) for (i = A[x]; i != x; i = A[i])
// --8<-- [end:iteration]

// --8<-- [start:data]
constexpr int MS = 1e5 + 5;
int n, m, idx, first[MS], siz[MS];
int L[MS], R[MS], U[MS], D[MS];
int col[MS], row[MS];

// --8<-- [end:data]

// --8<-- [start:remove]
void remove(const int &c) {
  int i, j;
  L[R[c]] = L[c], R[L[c]] = R[c];
  // 顺着这一列从上往下遍历
  IT(i, D, c)
  // 顺着这一行从左往右遍历
  IT(j, R, i)
  U[D[j]] = U[j], D[U[j]] = D[j], --siz[col[j]];
}

// --8<-- [end:remove]

// --8<-- [start:recover]
void recover(const int &c) {
  int i, j;
  IT(i, U, c) IT(j, L, i) U[D[j]] = D[U[j]] = j, ++siz[col[j]];
  L[R[c]] = R[L[c]] = c;
}

// --8<-- [end:recover]

// --8<-- [start:build]
void build(const int &r, const int &c) {
  n = r, m = c;
  for (int i = 0; i <= c; ++i) {
    L[i] = i - 1, R[i] = i + 1;
    U[i] = D[i] = i;
  }
  L[0] = c, R[c] = 0, idx = c;
  memset(first, 0, sizeof(first));
  memset(siz, 0, sizeof(siz));
}

// --8<-- [end:build]

// --8<-- [start:insert]
void insert(const int &r, const int &c) {
  // --8<-- [start:insert-column]
  col[++idx] = c, row[idx] = r, ++siz[c];
  U[idx] = c, D[idx] = D[c], U[D[c]] = idx, D[c] = idx;
  // --8<-- [end:insert-column]
  if (!first[r])
    first[r] = L[idx] = R[idx] = idx;
  else {
    // --8<-- [start:insert-row]
    L[idx] = first[r], R[idx] = R[first[r]];
    L[R[first[r]]] = idx, R[first[r]] = idx;
    // --8<-- [end:insert-row]
  }
}

// --8<-- [end:insert]

int ans, stk[MS];

// --8<-- [start:dance]
bool dance(int dep) {
  int i, j, c = R[0];
  if (!R[0]) {
    ans = dep;
    return true;
  }
  IT(i, R, 0) if (siz[i] < siz[c]) c = i;
  remove(c);
  IT(i, D, c) {
    stk[dep] = row[i];
    IT(j, R, i) remove(col[j]);
    if (dance(dep + 1)) return true;
    IT(j, L, i) recover(col[j]);
  }
  recover(c);
  return false;
}

// --8<-- [end:dance]

int main() {
  if (scanf("%d%d", &n, &m) != 2) return 0;
  build(n, m);
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= m; ++j) {
      int x;
      scanf("%d", &x);
      if (x) insert(i, j);
    }
  if (dance(1)) {
    for (int i = 1; i < ans; ++i) printf("%s%d", i == 1 ? "" : " ", stk[i]);
    puts("");
  } else {
    puts("No Solution!");
  }
}
