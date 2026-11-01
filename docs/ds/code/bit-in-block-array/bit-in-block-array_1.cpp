#include <algorithm>
#include <cmath>
#include <cstdio>
using namespace std;
constexpr int N = 2e5 + 5;
constexpr int M = 447 + 5;  // sqrt(N) + 5

int n, m, pa[N], pb[N];

int nn, block_size, block_cnt, block_id[N], L[N], R[N], T[M][N];

void build(int n) {
  nn = n;
  block_size = sqrt(nn);
  block_cnt = nn / block_size;
  for (int i = 1; i <= block_cnt; ++i) {
    L[i] = R[i - 1] + 1;
    R[i] = i * block_size;
  }
  if (R[block_cnt] < nn) {
    ++block_cnt;
    L[block_cnt] = R[block_cnt - 1] + 1;
    R[block_cnt] = nn;
  }
  for (int j = 1; j <= block_cnt; ++j)
    for (int i = L[j]; i <= R[j]; ++i) block_id[i] = j;
}

int lb(int x) { return x & -x; }

void add(int p, int v, int d) {
  for (int i = block_id[p]; i <= block_cnt; i += lb(i))
    for (int j = v; j <= nn; j += lb(j)) T[i][j] += d;
}

int getsum(int p, int v) {
  if (!p) return 0;
  int res = 0;
  int id = block_id[p];
  for (int i = L[id]; i <= p; ++i)
    if (pb[i] <= v) ++res;
  for (int i = id - 1; i; i -= lb(i))
    for (int j = v; j; j -= lb(j)) res += T[i][j];
  return res;
}

void update(int x, int y) {
  add(x, pb[x], -1);
  add(y, pb[y], -1);
  swap(pb[x], pb[y]);
  add(x, pb[x], 1);
  add(y, pb[y], 1);
}

int query(int la, int ra, int lb, int rb) {
  int res = getsum(rb, ra) - getsum(rb, la - 1) - getsum(lb - 1, ra) +
            getsum(lb - 1, la - 1);
  return res;
}

int main() {
  scanf("%d %d", &n, &m);
  int v;
  for (int i = 1; i <= n; ++i) scanf("%d", &v), pa[v] = i;
  for (int i = 1; i <= n; ++i) scanf("%d", &v), pb[i] = pa[v];

  build(n);
  for (int i = 1; i <= n; ++i) add(i, pb[i], 1);

  int op, la, lb, ra, rb, x, y;
  for (int i = 1; i <= m; ++i) {
    scanf("%d", &op);
    if (op == 1) {
      scanf("%d %d %d %d", &la, &ra, &lb, &rb);
      printf("%d\n", query(la, ra, lb, rb));
    } else if (op == 2) {
      scanf("%d %d", &x, &y);
      update(x, y);
    }
  }
  return 0;
}
