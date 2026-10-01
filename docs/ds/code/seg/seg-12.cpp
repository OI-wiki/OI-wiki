#include <algorithm>
#include <array>
#include <climits>
#include <iostream>
#include <unordered_map>
#include <vector>

struct Info {
  int cnt;  // Minimum cover count over this interval.
  int len;  // Total length of the parts attaining that minimum.

  Info(int _cnt = INT_MAX, int _len = 0) : cnt(_cnt), len(_len) {}

  Info operator+(const Info& o) const {
    return cnt < o.cnt ? *this : (cnt > o.cnt ? o : Info(cnt, len + o.len));
  }

  Info& operator+=(const Info& o) { return *this = *this + o; }
};

struct Transform {
  int v;

  Transform(int _v = 0) : v(_v) {}

  explicit operator bool() const { return v != 0; }

  Transform operator+(const Transform& o) const { return Transform(v + o.v); }

  Transform& operator+=(const Transform& o) { return *this = *this + o; }

  Info operator()(const Info& x) const {
    return Info(x.cnt == INT_MAX ? INT_MAX : x.cnt + v, x.len);
  }
};

class SegmentTree {
  int rt, id, L, R;
  std::vector<int> lc, rc;
  std::vector<Info> val;
  std::vector<Transform> lz;

  void push_up(int cr) { val[cr] = val[lc[cr]] + val[rc[cr]]; }

  void lazy_update(int cr, const Transform& f) {
    val[cr] = f(val[cr]);
    lz[cr] += f;
  }

  void push_down(int cr) {
    if (!lz[cr]) return;
    lazy_update(lc[cr], lz[cr]);
    lazy_update(rc[cr], lz[cr]);
    lz[cr] = Transform();
  }

  void build(int cr, int ll, int rr, const std::vector<int>& locs) {
    if (ll == rr)
      return (void)(val[cr] = Info(0, ll ? locs[ll] - locs[ll - 1] : 0));
    int mm = ll + ((rr - ll) >> 1);
    build(lc[cr] = ++id, ll, mm, locs);
    build(rc[cr] = ++id, mm + 1, rr, locs);
    push_up(cr);
  }

  void modify(int cr, int ll, int rr, int tl, int tr, const Transform& f) {
    if (tl <= ll && rr <= tr) return lazy_update(cr, f);
    push_down(cr);
    int mm = ll + ((rr - ll) >> 1);
    if (tl <= mm) modify(lc[cr], ll, mm, tl, tr, f);
    if (mm < tr) modify(rc[cr], mm + 1, rr, tl, tr, f);
    push_up(cr);
  }

 public:
  SegmentTree(int n, const std::vector<int>& locs) {
    rt = 0, id = 0, L = 0, R = n - 1;
    lc.resize(n << 1), rc.resize(n << 1), val.resize(n << 1), lz.resize(n << 1);
    build(rt = ++id, L, R, locs);
  }

  void modify(int l, int r, const Transform& f) { modify(rt, L, R, l, r, f); }

  Info query() const { return val[rt]; }
};

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
  long long all = locs.back() - locs[0];
  SegmentTree seg(m, locs);
  long long res = 0;
  for (int l = 0, r; l < (n << 1); l = r) {
    for (r = l; r < (n << 1) && ops[r][0] == ops[l][0]; ++r) {
      seg.modify(ids[ops[r][1]] + 1, ids[ops[r][2]], Transform(ops[r][3]));
    }
    if (r < (n << 1)) res += (ops[r][0] - ops[l][0]) * (all - seg.query().len);
  }
  std::cout << res << std::endl;
  return 0;
}
