#include <algorithm>
#include <cstdio>

using i64 = long long;
using u64 = unsigned long long;

constexpr int maxT = 50;
constexpr int maxn = 50;
constexpr int SEED = 98243;
constexpr int inf = 2147483647;

inline int io() {
  static int _;
  return scanf("%d", &_), _;
}

template <class _Tp>
inline _Tp Max(const _Tp x, const _Tp y) {
  return x > y ? x : y;
}

template <class _Tp>
inline void chkMax(_Tp &x, const _Tp y) {
  (x < y) && (x = y);
}

template <class _Tp>
inline void chkMin(_Tp &x, const _Tp y) {
  (x > y) && (x = y);
}

template <class _Tp>
inline void swap(_Tp &x, _Tp &y) {
  _Tp z = x;
  x = y;
  y = z;
}

struct Edge {
  int v;
  Edge *las;

  inline Edge *init(const int to, Edge *const ls) {
    return v = to, las = ls, this;
  }
} * las[maxn + 1], pool[maxn << 1], *alc = pool - 1;

inline void lnk(const int u, const int v) {
  if (u == 0) return;
  las[u] = (++alc)->init(v, las[u]);
  las[v] = (++alc)->init(u, las[v]);
}

u64 hval[maxn + 1];

void calc(const int u, const int fa) {
  static u64 lis[maxn + 1];
  static int sz[maxn + 1];

  /* DFS 时计算 size */
  sz[u] = 1;
  for (Edge *o = las[u]; o; o = o->las)
    if (o->v != fa) calc(o->v, u), sz[u] += sz[o->v];

  /* 将 u 各个儿子的哈希值排序 */
  int cnt = 0;
  for (Edge *o = las[u]; o; o = o->las)
    if (o->v != fa) lis[++cnt] = hval[o->v];
  std::sort(lis + 1, lis + cnt + 1);

  /* 计算 u 的哈希值 */
  u64 val = 0;
  for (int i = 1; i <= cnt; ++i) val = val * SEED + lis[i];
  hval[u] = val ? val * sz[u] : 1;
}

int sz[maxn + 1], mxsz[maxn + 1];

void precalc(const int u, const int fa) {
  /* 找树的重心 */
  sz[u] = 1;
  mxsz[u] = 0;
  for (Edge *o = las[u]; o; o = o->las)
    if (o->v != fa) {
      precalc(o->v, u);
      sz[u] += sz[o->v];
      chkMax(mxsz[u], sz[o->v]);
    }
}

int main() {
  static int n[maxT + 1];
  static u64 val[maxT + 1][2];

  const int T = io();
  for (int i = 1; i <= T; ++i) {
    n[i] = io();
    for (int u = 1; u <= n[i]; ++u) lnk(io(), u);

    precalc(1, 0);
    int rtsz = inf, cnt = 0;
    for (int u = 1; u <= n[i]; ++u) chkMin(rtsz, Max(mxsz[u], n[i] - sz[u]));
    for (int u = 1; u <= n[i]; ++u)
      if (rtsz == Max(mxsz[u], n[i] - sz[u]))
        calc(u, 0), val[i][cnt++] = hval[u];
    /* 如果这个点是重心就计算其哈希值 */

    if (cnt == 2 && val[i][0] > val[i][1]) swap(val[i][0], val[i][1]);

    /* 清空数组 */
    for (int u = 1; u <= n[i]; ++u) las[u] = nullptr;
    alc = pool - 1;
  }

  for (int i = 1; i <= T; ++i) {
    bool flag = true;
    for (int j = 1; j != i; ++j)
      if (n[i] == n[j] && val[i][0] == val[j][0] && val[i][1] == val[j][1]) {
        /* 若树 j 与树 i 点数相同且重心哈希值相同，则其同构 */
        flag = false;
        printf("%d\n", j);
        break;
      }
    if (flag) printf("%d\n", i);
  }

  return 0;
}