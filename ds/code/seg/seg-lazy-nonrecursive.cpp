#include <array>
#include <iostream>
#include <vector>

constexpr int M = 998244353;

// --8<-- [start:info]
// Interval length and sum of elements.
struct Info {
  int len, sum;

  Info(int _len = 0, int _sum = 0) : len(_len), sum(_sum) {}

  Info operator+(const Info& o) const {
    return Info(len + o.len, (sum + o.sum) % M);
  }

  Info& operator+=(const Info& o) { return *this = *this + o; }
};

// --8<-- [end:info]
// --8<-- [start:transform]
// Affine transformation: f(x) = ax + b.
struct Transform {
  int a, b;

  Transform(int _a = 1, int _b = 0) : a(_a), b(_b) {}

  explicit operator bool() const { return a != 1 || b != 0; }

  Transform operator+(const Transform& o) const {
    return Transform((long long)o.a * a % M, ((long long)o.a * b + o.b) % M);
  }

  Transform& operator+=(const Transform& o) { return *this = *this + o; }

  Info operator()(const Info& v) const {
    return Info(v.len, ((long long)a * v.sum + (long long)b * v.len) % M);
  }
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
// --8<-- [end:seg-tree]
int main() {
  std::ios::sync_with_stdio(false), std::cin.tie(nullptr);
  int n, q;
  std::cin >> n >> q;
  std::vector<Info> vec;
  for (int x, i = 0; i < n; ++i) {
    std::cin >> x;
    vec.emplace_back(1, x);
  }
  build(0, n - 1, vec);
  for (; q; --q) {
    int op;
    std::cin >> op;
    if (op == 0) {
      int l, r, b, c;
      std::cin >> l >> r >> b >> c;
      modify(l, r - 1, Transform(b, c));
    } else {
      int l, r;
      std::cin >> l >> r;
      std::cout << query(l, r - 1).sum << '\n';
    }
  }
  return 0;
}
