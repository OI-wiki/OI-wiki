#include <bits/stdc++.h>
using namespace std;

const int maxn = 505, p = (int)1e9 + 7;

int qpow(int a, int b) {
  int ans = 1;
  while (b) {
    if (b & 1) ans = (long long)ans * a % p;
    a = (long long)a * a % p;
    b >>= 1;
  }
  return ans;
}

int A[maxn][maxn], B[maxn][maxn], t[maxn][maxn], id[maxn];

// 高斯消元 O(n^3)
// 在传入 B 时表示计算逆矩阵, 传入 nullptr 则只需计算矩阵的秩
void Gauss(int A[][maxn], int B[][maxn], int n) {
  if (B) {
    memset(B, 0, sizeof(t));
    for (int i = 1; i <= n; i++) B[i][i] = 1;
  }

  for (int i = 1; i <= n; i++) {
    if (!A[i][i]) {
      for (int j = i + 1; j <= n; j++)
        if (A[j][i]) {
          swap(id[i], id[j]);
          for (int k = i; k <= n; k++) swap(A[i][k], A[j][k]);

          if (B)
            for (int k = 1; k <= n; k++) swap(B[i][k], B[j][k]);
          break;
        }

      if (!A[i][i]) continue;
    }

    int inv = qpow(A[i][i], p - 2);

    for (int j = 1; j <= n; j++)
      if (i != j && A[j][i]) {
        int t = (long long)A[j][i] * inv % p;

        for (int k = i; k <= n; k++)
          if (A[i][k]) A[j][k] = (A[j][k] - (long long)t * A[i][k]) % p;

        if (B) {
          for (int k = 1; k <= n; k++)
            if (B[i][k]) B[j][k] = (B[j][k] - (long long)t * B[i][k]) % p;
        }
      }
  }

  if (B)
    for (int i = 1; i <= n; i++) {
      int inv = qpow(A[i][i], p - 2);

      for (int j = 1; j <= n; j++)
        if (B[i][j]) B[i][j] = (long long)B[i][j] * inv % p;
    }
}

bool row_marked[maxn] = {false}, col_marked[maxn] = {false};

int sub_n;  // 极大满秩子矩阵的大小

// 消去一行一列 O(n^2)
void eliminate(int r, int c) {
  row_marked[r] = col_marked[c] = true;  // 已经被消掉

  int inv = qpow(B[r][c], p - 2);

  for (int i = 1; i <= sub_n; i++)
    if (!row_marked[i] && B[i][c]) {
      int t = (long long)B[i][c] * inv % p;

      for (int j = 1; j <= sub_n; j++)
        if (!col_marked[j] && B[r][j])
          B[i][j] = (B[i][j] - (long long)t * B[r][j]) % p;
    }
}

int vertices[maxn], girl[maxn];  // girl 是匹配点, 用来输出方案

int main() {
  auto rng = mt19937(chrono::steady_clock::now().time_since_epoch().count());

  int n, m;
  scanf("%d%d", &n, &m);  // 点数和边数

  while (m--) {
    int x, y;
    scanf("%d%d", &x, &y);
    A[x][y] = rng() % p;
    A[y][x] = -A[x][y];  // Tutte 矩阵
  }

  for (int i = 1; i <= n; i++)
    id[i] = i;  // 输出方案用的，因为高斯消元的时候会交换列
  memcpy(t, A, sizeof(t));

  Gauss(A, nullptr, n);

  for (int i = 1; i <= n; i++)
    if (A[id[i]][id[i]]) vertices[++sub_n] = i;  // 找出一个极大满秩子矩阵

  for (int i = 1; i <= sub_n; i++)
    for (int j = 1; j <= sub_n; j++) A[i][j] = t[vertices[i]][vertices[j]];

  Gauss(A, B, sub_n);

  for (int i = 1; i <= sub_n; i++)
    if (!girl[vertices[i]])
      for (int j = i + 1; j <= sub_n; j++)
        if (!girl[vertices[j]] && t[vertices[i]][vertices[j]] && B[j][i]) {
          // 注意上面那句 if 的写法, 现在 t 是邻接矩阵的备份，
          // 逆矩阵 j 行 i 列不为 0 当且仅当这条边可行
          girl[vertices[i]] = vertices[j];
          girl[vertices[j]] = vertices[i];

          eliminate(i, j);
          eliminate(j, i);
          break;
        }

  printf("%d\n", sub_n / 2);
  for (int i = 1; i <= n; i++) printf("%d ", girl[i]);

  return 0;
}