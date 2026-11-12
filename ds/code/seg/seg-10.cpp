#include <algorithm>
#include <array>
#include <iostream>
#include <unordered_map>
#include <vector>

using u64 = unsigned long long;

// --8<-- [start:info]
// Interval length and sum of elements.
struct Info {
  u64 len, sum;

  Info(u64 _len = 0, u64 _sum = 0) : len(_len), sum(_sum) {}

  Info operator+(const Info& o) const { return Info(len + o.len, sum + o.sum); }

  Info& operator+=(const Info& o) { return *this = *this + o; }
};

// --8<-- [end:info]
// --8<-- [start:transform]
// Range add.
struct Transform {
  u64 a;

  Transform(u64 _a = 0) : a(_a) {}

  explicit operator bool() const { return a != 0; }

  Transform operator+(const Transform& o) const { return Transform(a + o.a); }

  Transform& operator+=(const Transform& o) { return *this = *this + o; }

  Info operator()(const Info& v) const {
    return Info(v.len, v.sum + a * v.len);
  }
};

// --8<-- [end:transform]
// --8<-- [start:seg-tree]
// Segment Tree.
// --8<-- [start:build]
// Recursive structure, stored in a full binary tree.
#define lc(x) ch[(x)][0]
#define rc(x) ch[(x)][1]

int rt, id, L, R;
std::vector<std::array<int, 2>> ch;
std::vector<Info> val;
std::vector<Transform> lazy;

void push_up(int cr) { val[cr] = val[lc(cr)] + val[rc(cr)]; }

// Build the tree based on info stored in vec (0-indexed).
void build(int cr, int ll, int rr, const std::vector<Info>& vec) {
  if (ll == rr) return (void)(val[cr] = vec[ll - L]);
  int mm = ll + ((rr - ll) >> 1);
  build(lc(cr) = ++id, ll, mm, vec);
  build(rc(cr) = ++id, mm + 1, rr, vec);
  push_up(cr);
}

void build(int l, int r, const std::vector<Info>& vec) {
  rt = 1, id = 0, L = l, R = r;
  int n = R - L + 1;
  ch.resize(n << 1), val.resize(n << 1), lazy.resize(n << 1);
  build(rt = ++id, L, R, vec);
}

// --8<-- [end:build]
// --8<-- [start:tag]
// Lazy update.
void lazy_update(int cr, const Transform& f) {
  val[cr] = f(val[cr]);
  lazy[cr] += f;
}

// Push down lazy tag.
void push_down(int cr) {
  if (!lazy[cr]) return;
  lazy_update(lc(cr), lazy[cr]);
  lazy_update(rc(cr), lazy[cr]);
  lazy[cr] = Transform();
}

// --8<-- [end:tag]
// --8<-- [start:range-get]
// Query info in [l, r].
Info query(int cr, int ll, int rr, int tl, int tr) {
  if (tl <= ll && rr <= tr) return val[cr];
  push_down(cr);
  int mm = ll + ((rr - ll) >> 1);
  Info res;
  if (tl <= mm) res = query(lc(cr), ll, mm, tl, tr);
  if (mm < tr) res += query(rc(cr), mm + 1, rr, tl, tr);
  return res;
}

Info query(int l, int r) { return query(rt, L, R, l, r); }

// --8<-- [end:range-get]
// --8<-- [start:range-set]
// Apply transformation f to the range [l, r].
void modify(int cr, int ll, int rr, int tl, int tr, const Transform& f) {
  if (tl <= ll && rr <= tr) return lazy_update(cr, f);
  push_down(cr);
  int mm = ll + ((rr - ll) >> 1);
  if (tl <= mm) modify(lc(cr), ll, mm, tl, tr, f);
  if (mm < tr) modify(rc(cr), mm + 1, rr, tl, tr, f);
  push_up(cr);
}

void modify(int l, int r, const Transform& f) { modify(rt, L, R, l, r, f); }

// --8<-- [end:range-set]
// --8<-- [end:seg-tree]
int main() {
  std::ios::sync_with_stdio(false), std::cin.tie(nullptr);
  int n, m;
  std::cin >> n >> m;
  // Offline queries and discretization.
  std::vector<std::array<int, 4>> queries(m);
  std::vector<int> loc;
  loc.reserve((m << 1) | 1);
  loc.push_back(0);
  for (auto& q : queries) {
    std::cin >> q[0] >> q[1] >> q[2];
    if (q[0] == 1) std::cin >> q[3];
    loc.push_back(q[1] - 1);
    loc.push_back(q[2]);
  }
  std::sort(loc.begin(), loc.end());
  loc.erase(std::unique(loc.begin(), loc.end()), loc.end());
  int sz = loc.size();
  std::unordered_map<int, int> ids;
  for (int i = 0; i < sz; ++i) ids[loc[i]] = i;
  std::vector<Info> vec(sz);
  for (int i = 1; i < sz; ++i) {
    vec[i].len = loc[i] - loc[i - 1];
    vec[i].sum = vec[i].len * (loc[i] + loc[i - 1] + 1ULL) / 2;
  }
  // Ordinary seg tree operations.
  build(0, sz - 1, vec);
  for (auto q : queries) {
    if (q[0] == 1) {
      modify(ids[q[1] - 1] + 1, ids[q[2]], Transform(q[3]));
    } else if (q[0] == 2) {
      std::cout << query(ids[q[1] - 1] + 1, ids[q[2]]).sum << '\n';
    }
  }
  return 0;
}
