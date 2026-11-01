#include <algorithm>
#include <array>
#include <iostream>
#include <unordered_map>
#include <vector>

struct Info {
  int len;  // Length of this interval.
  int cnt;  // Number of operations that cover this interval exactly.
  int tot;  // Length covered by operations recorded in the descendants.
};

// Segment tree.
int rt, id, L, R;
std::vector<int> lc, rc;
std::vector<Info> val;

// Build the tree.
void build(int cr, int ll, int rr, const std::vector<int>& vec) {
  if (ll == rr) return (void)(val[cr].len = (ll ? vec[ll] - vec[ll - 1] : 0));
  int mm = ll + ((rr - ll) >> 1);
  build(lc[cr] = ++id, ll, mm, vec);
  build(rc[cr] = ++id, mm + 1, rr, vec);
  val[cr].len = val[lc[cr]].len + val[rc[cr]].len;
}

void build(int n, const std::vector<int>& vec) {
  rt = 0, id = 0, L = 0, R = n - 1;
  lc.resize(n << 1), rc.resize(n << 1), val.resize(n << 1);
  build(rt = ++id, 0, n - 1, vec);
}

// Query.
int query(int cr) { return val[cr].cnt ? val[cr].len : val[cr].tot; }

int query() { return query(rt); }

// Cover.
void cover(int cr, int ll, int rr, int tl, int tr, int v) {
  if (tl <= ll && rr <= tr) return (void)(val[cr].cnt += v);
  int mm = ll + ((rr - ll) >> 1);
  if (tl <= mm) cover(lc[cr], ll, mm, tl, tr, v);
  if (mm < tr) cover(rc[cr], mm + 1, rr, tl, tr, v);
  val[cr].tot = query(lc[cr]) + query(rc[cr]);
}

void cover(int l, int r, int v) { cover(rt, L, R, l, r, v); }

int main() {
  std::ios::sync_with_stdio(false), std::cin.tie(nullptr);
  int n;
  std::cin >> n;
  // Scanning and discretizing.
  std::vector<std::array<int, 4>> ops;
  ops.reserve(n << 1);
  std::vector<int> locs;
  locs.reserve(n << 1);
  for (int i = 0; i < n; ++i) {
    int x1, y1, x2, y2;
    std::cin >> x1 >> y1 >> x2 >> y2;
    ops.push_back({x1, y1, y2, 1});
    ops.push_back({x2, y1, y2, -1});
    locs.push_back(y1);
    locs.push_back(y2);
  }
  std::sort(ops.begin(), ops.end());
  std::sort(locs.begin(), locs.end());
  locs.erase(std::unique(locs.begin(), locs.end()), locs.end());
  int m = locs.size();
  std::unordered_map<int, int> ids;
  for (int i = 0; i < m; ++i) ids[locs[i]] = i;
  // Segment tree operations.
  build(m, locs);
  long long res = 0;
  for (int l = 0, r; l < (n << 1); l = r) {
    for (r = l; r < (n << 1) && ops[r][0] == ops[l][0]; ++r) {
      cover(ids[ops[r][1]] + 1, ids[ops[r][2]], ops[r][3]);
    }
    if (r < (n << 1)) res += (long long)(ops[r][0] - ops[l][0]) * query();
  }
  std::cout << res << std::endl;
  return 0;
}
