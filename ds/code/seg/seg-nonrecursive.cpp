#include <iostream>
#include <vector>

constexpr int M = 998244353;

// --8<-- [start:info]
// Affine function: f(x) = ax + b.
// Composition: (f1 + f2)(x) = f2(f1(x)).
// Identity: e(x) = x.
struct Info {
  int a, b;

  Info(int _a = 1, int _b = 0) : a(_a), b(_b) {}

  Info operator+(const Info& o) const {
    return Info((long long)o.a * a % M, ((long long)o.a * b + o.b) % M);
  }

  Info& operator+=(const Info& o) { return *this = *this + o; }
};

// --8<-- [end:info]
// --8<-- [start:seg-tree]
// Segment Tree Implementation. Nonrecursive. No lazy tag.
// --8<-- [start:build]
// Nonrecursive structure, embedded in a perfect binary tree.
int n, L, R;
std::vector<Info> val;

void push_up(int cr) { val[cr] = val[cr << 1] + val[(cr << 1) | 1]; }

// Build the tree based on info stored in vec (0-indexed).
void build(int l, int r, const std::vector<Info>& vec) {
  L = l, R = r;
  for (n = 1; n < r - l + 1; n <<= 1);
  val.resize(n << 1);
  std::copy(vec.begin(), vec.end(), val.begin() + n);
  for (int i = n - 1; i; --i) push_up(i);
}

// --8<-- [end:build]
// --8<-- [start:point-get]
// Query info at x.
Info query(int x) { return val[n + x - L]; }

// --8<-- [end:point-get]
// --8<-- [start:point-set]
// Modify info at x to v.
void modify(int x, const Info& v) {
  x = x - L + n;
  val[x] = v;
  for (x >>= 1; x; x >>= 1) push_up(x);
}

// --8<-- [end:point-set]
// --8<-- [start:range-get]
// Query info in [l, r].
Info query(int l, int r) {
  Info la, ra;
  for (l = l - L + n, r = r - L + n; l <= r; l >>= 1, r >>= 1) {
    if (l & 1) la += val[l++];
    if (~r & 1) ra = val[r--] + ra;
  }
  return la + ra;
}

// --8<-- [end:range-get]
// --8<-- [end:seg-tree]
int main() {
  std::ios::sync_with_stdio(false), std::cin.tie(nullptr);
  int n, q;
  std::cin >> n >> q;
  std::vector<Info> vec;
  for (int a, b, i = 0; i < n; ++i) {
    std::cin >> a >> b;
    vec.emplace_back(a, b);
  }
  build(0, n - 1, vec);
  for (; q; --q) {
    int op;
    std::cin >> op;
    if (op == 0) {
      int p, c, d;
      std::cin >> p >> c >> d;
      modify(p, Info(c, d));
    } else {
      int l, r, x;
      std::cin >> l >> r >> x;
      auto res = query(l, r - 1);
      std::cout << (((long long)res.a * x + res.b) % M) << '\n';
    }
  }
  return 0;
}
