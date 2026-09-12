#include <algorithm>
#include <iostream>
#include <vector>

// --8<-- [start:info]
// Minimum.
struct Info {
  long long mi;

  Info(long long _mi = 2e18) : mi(_mi) {}

  Info operator+(const Info& o) const { return Info(std::min(mi, o.mi)); }

  Info& operator+=(const Info& o) { return *this = *this + o; }
};

// --8<-- [end:info]
// --8<-- [start:transform]
// Addition.
struct Transform {
  long long x;

  Transform(long long _x = 0) : x(_x) {}

  explicit operator bool() const { return x != 0; }

  Transform operator+(const Transform& o) const { return Transform(x + o.x); }

  Transform& operator+=(const Transform& o) { return *this = *this + o; }

  Info operator()(const Info& v) const { return Info(v.mi + x); }
};

// --8<-- [end:transform]
// --8<-- [start:seg-tree]
// Segment Tree Implementation. Nonrecursive. With lazy tag.
// --8<-- [start:build]
// Nonrecursive structure, embedded in a perfect binary tree.
int n, h, L, R;
std::vector<Info> val;
std::vector<Transform> lazy;

void push_up(int cr) { val[cr] = lazy[cr](val[cr << 1] + val[(cr << 1) | 1]); }

// Build the tree based on info stored in vec (0-indexed).
void build(int l, int r, const std::vector<Info>& vec) {
  L = l, R = r, n = r - l + 1;
  for (h = 0; (1 << h) < n; ++h);
  n = 1 << h;
  val.resize(n << 1), lazy.resize(n);
  std::copy(vec.begin(), vec.end(), val.begin() + n);
  for (int i = n - 1; i; --i) push_up(i);
}

// --8<-- [end:build]
// --8<-- [start:tag]
// Lazy update.
void lazy_update(int cr, const Transform& f) {
  val[cr] = f(val[cr]);
  if (cr < n) lazy[cr] += f;
}

// --8<-- [end:tag]
// --8<-- [start:point-get]
// Query info at x.
Info query(int x) {
  x = x - L + n;
  auto res = val[x];
  for (int i = 1; i <= h; ++i) res = lazy[x >> i](res);
  return res;
}

// --8<-- [end:point-get]
// --8<-- [start:point-set]
// Apply transformation f to the value at x.
void modify(int x, const Transform& f) {
  x = x - L + n;
  val[x] = f(val[x]);
  for (int i = 1; i <= h; ++i) push_up(x >> i);
}

// --8<-- [end:point-set]
// --8<-- [start:range-get]
// Query info in [l, r].
Info query(int l, int r) {
  l = l - L + n, r = r - L + n;
  Info la, ra;
  for (int i = 0, ll = l, rr = r; i <= h; ++i) {
    if (i) la = lazy[l >> i](la), ra = lazy[r >> i](ra);
    if (ll <= rr) {
      if (ll & 1) la += val[ll++];
      if (~rr & 1) ra = val[rr--] + ra;
      ll >>= 1, rr >>= 1;
    }
  }
  return la + ra;
}

// --8<-- [end:range-get]
// --8<-- [start:range-set]
// Apply transformation f to the range [l, r].
void modify(int l, int r, const Transform& f) {
  l = l - L + n, r = r - L + n;
  for (int ll = l, rr = r; ll <= rr; ll >>= 1, rr >>= 1) {
    if (ll & 1) lazy_update(ll++, f);
    if (~rr & 1) lazy_update(rr--, f);
  }
  for (int i = 1, m = 1; i <= h; ++i, m = (m << 1) | 1) {
    if (l & m) push_up(l >> i);
    if (~r & m) push_up(r >> i);
  }
}

// --8<-- [end:range-set]
// --8<-- [end:seg-tree]
int main() {
  std::ios::sync_with_stdio(false), std::cin.tie(nullptr);
  int n, q;
  std::cin >> n >> q;
  std::vector<Info> vec;
  for (int x, i = 0; i < n; ++i) {
    std::cin >> x;
    vec.emplace_back(x);
  }
  build(0, n - 1, vec);
  for (; q; --q) {
    int op;
    std::cin >> op;
    if (op == 0) {
      int l, r, x;
      std::cin >> l >> r >> x;
      modify(l, r - 1, Transform(x));
    } else {
      int l, r;
      std::cin >> l >> r;
      std::cout << query(l, r - 1).mi << '\n';
    }
  }
  return 0;
}
