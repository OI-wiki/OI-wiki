#include <algorithm>
#include <array>
#include <iostream>
#include <vector>

// --8<-- [start:info]
// Range max.
struct Info {
  int ma;

  Info(int _ma = 0) : ma(_ma) {}

  Info operator+(const Info& o) const { return Info(std::max(ma, o.ma)); }

  Info& operator+=(const Info& o) { return *this = *this + o; }
};

// --8<-- [end:info]
// --8<-- [start:transform]
// Assignment; -1 for identity.
struct Transform {
  int x;

  Transform(int _x = -1) : x(_x) {}

  explicit operator bool() const { return x != -1; }

  Transform operator+(const Transform& o) const { return o ? o : *this; }

  Transform& operator+=(const Transform& o) { return *this = *this + o; }

  Info operator()(const Info& v) const { return *this ? Info(x) : v; }
};

// --8<-- [end:transform]
// --8<-- [start:seg-tree]
// Segment Tree Implementation. Nonrecursive. With lazy tag.
// --8<-- [start:build]
// Nonrecursive structure, embedded in a perfect binary tree.
int n, h, L, R;
std::vector<Info> val;
std::vector<Transform> lazy;

void push_up(int cr) { val[cr] = val[cr << 1] + val[(cr << 1) | 1]; }

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

// Push down lazy tag.
void push_down(int cr) {
  if (!lazy[cr]) return;
  lazy_update(cr << 1, lazy[cr]);
  lazy_update((cr << 1) | 1, lazy[cr]);
  lazy[cr] = Transform();
}

// --8<-- [end:tag]
// --8<-- [start:point-get]
// Query info at x.
Info query(int x) {
  x = x - L + n;
  for (int i = h; i; --i) push_down(x >> i);
  return val[x];
}

// --8<-- [end:point-get]
// --8<-- [start:point-set]
// Apply transformation f to the value at x.
void modify(int x, const Transform& f) {
  x = x - L + n;
  for (int i = h; i; --i) push_down(x >> i);
  val[x] = f(val[x]);
  for (int i = 1; i <= h; ++i) push_up(x >> i);
}

// --8<-- [end:point-set]
// --8<-- [start:range-get]
// Query info in [l, r].
Info query(int l, int r) {
  l = l - L + n, r = r - L + n;
  for (int i = h, m = (1 << h) - 1; i; --i, m >>= 1) {
    if (l & m) push_down(l >> i);
    if (~r & m) push_down(r >> i);
  }
  Info la, ra;
  for (; l <= r; l >>= 1, r >>= 1) {
    if (l & 1) la += val[l++];
    if (~r & 1) ra = val[r--] + ra;
  }
  return la + ra;
}

// --8<-- [end:range-get]
// --8<-- [start:range-set]
// Apply transformation f to the range [l, r].
void modify(int l, int r, const Transform& f) {
  l = l - L + n, r = r - L + n;
  for (int i = h, m = (1 << h) - 1; i; --i, m >>= 1) {
    if (l & m) push_down(l >> i);
    if (~r & m) push_down(r >> i);
  }
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
// --8<-- [start:max-right]
// Find max r in [l, R] such that g(info([l, r])) is true.
// Return l - 1 if no such r exists.
template <typename G>
int max_right(int l, const G& g) {
  l = l - L + n;
  for (int i = h; i; --i) push_down(l >> i);
  Info acc;
  for (;;) {
    while (~l & 1) l >>= 1;
    auto nxt = acc + val[l];
    if (!g(nxt)) {
      while (l < n) {
        push_down(l);
        l <<= 1;
        nxt = acc + val[l];
        if (g(nxt)) acc = nxt, ++l;
      }
      return l - n + L - 1;
    }
    acc = nxt, ++l;
    if ((l & -l) == l) break;
  }
  return R;
}

// --8<-- [end:max-right]
// --8<-- [start:min-left]
// Find min l in [L, r] such that g(info([l, r])) is true.
// Return r + 1 if no such l exists.
template <typename G>
int min_left(int r, const G& g) {
  r = r - L + n;
  for (int i = h; i; --i) push_down(r >> i);
  Info acc;
  for (;;) {
    while ((r & 1) && (r ^ 1)) r >>= 1;
    auto nxt = val[r] + acc;
    if (!g(nxt)) {
      while (r < n) {
        push_down(r);
        r = (r << 1) | 1;
        nxt = val[r] + acc;
        if (g(nxt)) acc = nxt, --r;
      }
      return r - n + L + 1;
    }
    if ((r & -r) == r) break;
    acc = nxt, --r;
  }
  return L;
}

// --8<-- [end:min-left]
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
  build(1, n, vec);
  for (; q; --q) {
    int op;
    std::cin >> op;
    if (op == 1) {
      int x, v;
      std::cin >> x >> v;
      modify(x, Transform(v));
    } else if (op == 2) {
      int l, r;
      std::cin >> l >> r;
      std::cout << query(l, r).ma << '\n';
    } else if (op == 3) {
      int x, v;
      std::cin >> x >> v;
      std::cout
          << (max_right(x, [&](const Info& a) -> bool { return a.ma < v; }) + 1)
          << '\n';
    }
  }
  return 0;
}
