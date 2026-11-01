#include <algorithm>
#include <cassert>
#include <climits>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <limits>
#include <list>
#include <numeric>
#include <queue>
#include <random>
#include <utility>
#include <vector>
using namespace std;
constexpr int MAXN = 505, p = 1000000007;
int n;
bool row_marked[MAXN], col_marked[MAXN];

int quick_power(int a, int b) {
  int x = 1;
  for (; b; b >>= 1, a = static_cast<long long>(a) * a % p)
    if (b & 1) x = static_cast<long long>(x) * a % p;
  return x;
}

// --8<-- [start:core]
void eliminate(int A[][MAXN], int r, int c) {  // 消去第 r 行第 c 列
  row_marked[r] = col_marked[c] = true;        // 已经被消掉

  int inv = quick_power(A[r][c], p - 2);  // 逆元

  for (int i = 1; i <= n; i++)
    if (!row_marked[i] && A[i][c]) {
      int tmp = (long long)A[i][c] * inv % p;

      for (int j = 1; j <= n; j++)
        if (!col_marked[j] && A[r][j])
          A[i][j] = (A[i][j] - (long long)tmp * A[r][j]) % p;
    }
}

// --8<-- [end:core]
int main() {
  int r, c;
  cin >> n >> r >> c;
  static int a[MAXN][MAXN];
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= n; ++j) cin >> a[i][j];
  eliminate(a, r, c);
  for (int i = 1; i <= n; ++i)
    if (!row_marked[i]) {
      for (int j = 1; j <= n; ++j)
        if (!col_marked[j]) cout << (a[i][j] + p) % p << " ";
      cout << "\n";
    }
}
