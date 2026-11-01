#include <algorithm>
#include <cmath>
#include <cstdio>
#include <vector>
using namespace std;
constexpr int N = 1e5 + 5;
constexpr int M = 316 + 5;  // sqrt(N) + 5

// 分块
int nn, b[N], block_size, block_cnt, block_id[N], L[N], R[N], T[M][N];

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

// d = 1: 加点(p, v)
// d = -1: 删点(p, v)
void add(int p, int v, int d) {
  for (int i = block_id[p]; i <= block_cnt; i += lb(i))
    for (int j = v; j <= nn; j += lb(j)) T[i][j] += d;
}

// 询问[1, r]内，纵坐标小于等于val的点有多少个
int getsum(int p, int v) {
  if (!p) return 0;
  int res = 0;
  int id = block_id[p];
  for (int i = L[id]; i <= p; ++i)
    if (b[i] && b[i] <= v) ++res;
  for (int i = id - 1; i; i -= lb(i))
    for (int j = v; j; j -= lb(j)) res += T[i][j];
  return res;
}

// 询问[l, r]内，纵坐标小于等于val的点有多少个
int query(int l, int r, int val) {
  if (l > r) return -1;
  int res = getsum(r, val) - getsum(l - 1, val);
  return res;
}

// 加点(p, v)
void update(int p, int v) {
  b[p] = v;
  add(p, v, 1);
}

int n, a[N];
vector<int> g[N];

int main() {
  scanf("%d", &n);

  // 为了减少讨论，加了哨兵节点
  // 因为树状数组添加的时候，为0可能会死循环，所以整体往右偏移一位
  // a_1和a_{n+2}为哨兵节点
  for (int i = 2; i <= n + 1; ++i) scanf("%d", &a[i]);
  for (int i = 2; i <= n + 1; ++i) g[a[i]].push_back(i);

  // 分块
  build(n + 2);

  int ans = n + 2, lst, ok;
  for (int i = 1; i <= n + 1; ++i) {
    g[i].push_back(n + 2);

    lst = 1;
    ok = 0;
    for (int pos : g[i]) {
      if (query(lst + 1, pos - 1, lst) == i - 1) {
        ok = 1;
        break;
      }
      lst = pos;
    }

    if (!ok) {
      ans = i;
      break;
    }

    lst = 1;
    g[i].pop_back();
    for (int pos : g[i]) {
      update(pos, lst);
      lst = pos;
    }
  }
  printf("%d\n", ans);
  return 0;
}
