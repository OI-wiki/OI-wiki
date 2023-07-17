#include <algorithm>
#include <iostream>
#include <vector>

typedef long long lxl;

const int maxN = 5e5;
const int maxM = 5e5;
const int maxA = 1e5;
const int sqrN = 708;
const int sqrA = 317;

int n, m;
int a[maxN + 10];
int b[maxN + 10];
int l, r;
lxl f[maxN + 10];
lxl g[maxN + 10];
lxl ans[maxM + 10];

typedef struct SegmentTree {
  struct Node {
    lxl val;
    lxl tag;
  } node[4 * maxA + 10];

  void MakeTag(int u, int l, int r, lxl val) {
    node[u].val += val * (r - l + 1);
    node[u].tag += val;
    return;
  }

  void PushDown(int u, int l, int r) {
    if (!node[u].tag) return;
    int mid = (l + r) / 2;
    MakeTag(2 * u, l, mid, node[u].tag);
    MakeTag(2 * u + 1, mid + 1, r, node[u].tag);
    node[u].tag = 0;
    return;
  }

  void PushUp(int u) {
    node[u].val = node[2 * u].val + node[2 * u + 1].val;
    return;
  }

  void Add(int u, int l, int r, int s, int t, lxl val) {
    if (s > t) return;
    if (s <= l && r <= t) {
      MakeTag(u, l, r, val);
      return;
    }
    PushDown(u, l, r);
    int mid = (l + r) / 2;
    if (s <= mid) Add(2 * u, l, mid, s, t, val);
    if (t >= mid + 1) Add(2 * u + 1, mid + 1, r, s, t, val);
    PushUp(u);
    return;
  }

  void Add(int u, int l, int r, int pos, lxl val) {
    Add(u, l, r, pos, pos, val);
    return;
  }

  lxl Ask(int u, int l, int r, int s, int t) {
    if (s > t) return 0;
    if (s <= l && r <= t) {
      return node[u].val;
    }
    PushDown(u, l, r);
    int mid = (l + r) / 2;
    if (t <= mid) return Ask(2 * u, l, mid, s, t);
    if (s >= mid + 1) return Ask(2 * u + 1, mid + 1, r, s, t);
    return Ask(2 * u, l, mid, s, t) + Ask(2 * u + 1, mid + 1, r, s, t);
  }
} sgt;

typedef struct BlockArray {
  struct Block {
    int l, r;
    lxl tag;
  } block[sqrA + 10];

  struct Array {
    int bel;
    lxl val;
  } array[maxA + 10];

  void Build() {
    for (int i = 1; i <= maxA; i++) array[i].bel = (i - 1) / sqrA + 1;
    for (int i = 1; i <= maxA; i++) block[array[i].bel].r = i;
    for (int i = maxA; i >= 1; i--) block[array[i].bel].l = i;
    return;
  }

  void Add(int pos, lxl val) {
    for (int i = array[pos].bel + 1; i <= array[maxA].bel; i++)
      block[i].tag += val;
    for (int i = pos; i <= block[array[pos].bel].r; i++) array[i].val += val;
    return;
  }

  lxl Ask(int pos) { return array[pos].val + block[array[pos].bel].tag; }

  lxl Ask(int l, int r) {
    if (l > r) return 0;
    return Ask(r) - Ask(l - 1);
  }
} dba;

namespace captainMoSecondaryOffline {
namespace offline2 {
struct Query {
  int i;
  int l, r;
  int k;
};

std::vector<Query> query[maxN + 10];

dba sum, cnt;

void solve() {
  sum.Build();
  cnt.Build();
  for (int i = 1; i <= n; i++) {
    sum.Add(a[i], a[i]);
    cnt.Add(a[i], 1);
    for (int j = 0; j < query[i].size(); j++) {
      for (int k = query[i][j].l; k <= query[i][j].r; k++) {
        ans[query[i][j].i] +=
            1ll * query[i][j].k *
            (sum.Ask(a[k] + 1, maxA) + cnt.Ask(1, a[k] - 1) * a[k]);
      }
    }
  }
  return;
}
}  // namespace offline2

namespace offline1 {
struct Query {
  int i;
  int l, r;

  bool operator<(const Query &other) const {
    if (b[l] != b[other.l]) return l < other.l;
    return r < other.r;
  }
};

std::vector<Query> query;

sgt sum, cnt;

void solve() {
  std::sort(query.begin(), query.end());
  for (int i = 1; i <= n; i++) {
    f[i] = sum.Ask(1, 1, maxA, a[i] + 1, maxA);
    g[i] = cnt.Ask(1, 1, maxA, 1, a[i] - 1);
    sum.Add(1, 1, maxA, a[i], a[i]);
    cnt.Add(1, 1, maxA, a[i], 1);
  }
  for (int i = 0, l = 1, r = 0; i < query.size(); i++) {
    if (l > query[i].l) {
      offline2::query[r].push_back(
          (offline2::Query){query[i].i, query[i].l, l - 1, 1});
      while (l > query[i].l) {
        l--;
        ans[query[i].i] -= f[l] + (g[l] - 1) * a[l];
      }
    }
    if (r < query[i].r) {
      offline2::query[l - 1].push_back(
          (offline2::Query){query[i].i, r + 1, query[i].r, -1});
      while (r < query[i].r) {
        r++;
        ans[query[i].i] += f[r] + (g[r] + 1) * a[r];
      }
    }
    if (l < query[i].l) {
      offline2::query[r].push_back(
          (offline2::Query){query[i].i, l, query[i].l - 1, -1});
      while (l < query[i].l) {
        ans[query[i].i] += f[l] + (g[l] - 1) * a[l];
        l++;
      }
    }
    if (r > query[i].r) {
      offline2::query[l - 1].push_back(
          (offline2::Query){query[i].i, query[i].r + 1, r, 1});
      while (r > query[i].r) {
        ans[query[i].i] -= f[r] + (g[r] + 1) * a[r];
        r--;
      }
    }
  }
  return;
}
}  // namespace offline1

void solve() {
  offline1::solve();
  offline2::solve();
  for (int i = 0; i < m; i++)
    ans[offline1::query[i].i] += ans[offline1::query[i - 1].i];
  return;
}
}  // namespace captainMoSecondaryOffline

int main() {
  std::cin >> n >> m;
  for (int i = 1; i <= n; i++) std::cin >> a[i];
  for (int i = 1; i <= n; i++) b[i] = (i - 1) / sqrN + 1;
  for (int i = 1; i <= m; i++)
    std::cin >> l >> r,
        captainMoSecondaryOffline::offline1::query.push_back(
            (captainMoSecondaryOffline::offline1::Query){i, l, r});
  captainMoSecondaryOffline::solve();
  for (int i = 1; i <= m; i++) std::cout << ans[i] << '\n';
  return 0;
}