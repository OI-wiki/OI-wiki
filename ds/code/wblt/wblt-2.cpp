// --8<-- [start:full-text]
#include <iostream>
#include <tuple>

// Change here to use different strategies to balance and to merge.
#define BALANCE_BY_ROTATING 0
#define ROTATE_BY_JOINING 1

constexpr int N = 2e5;
constexpr double ALPHA = 0.292;

int id, rt, ch[N][2], sz[N], val[N], lz[N];
int pool[N], top;

void push_up(int x) { sz[x] = sz[ch[x][0]] + sz[ch[x][1]]; }

void lazy_reverse(int x) {
  if (!x) return;
  std::swap(ch[x][0], ch[x][1]);
  lz[x] ^= 1;
}

void push_down(int x) {
  if (lz[x]) {
    lazy_reverse(ch[x][0]);
    lazy_reverse(ch[x][1]);
    lz[x] = 0;
  }
}

// Return a new empty node.
int new_node() {
  int x = top ? pool[--top] : ++id;
  sz[x] = val[x] = ch[x][0] = ch[x][1] = 0;
  return x;
}

// Release a node for later use.
void del_node(int& x) {
  pool[top++] = x;
  x = 0;
}

// Return a new leaf node of value v.
int new_leaf(int v) {
  int x = new_node();
  val[x] = v;
  sz[x] = 1;
  return x;
}

// Return a new node with subtrees x and y.
int join(int x, int y) {
  int z = new_node();
  ch[z][0] = x;
  ch[z][1] = y;
  push_up(z);
  return z;
}

// Return subtrees of x and release x.
auto cut(int& x) {
  push_down(x);
  int y = ch[x][0];
  int z = ch[x][1];
  del_node(x);
  return std::make_pair(y, z);
}

// Check whether a subtree of weight SX is too heavy
//     in a tree of weight SX + SY.
bool too_heavy(int sx, int sy) {
  // or sx > sy * 3;
  return sy < ALPHA * (sx + sy);
}

#if BALANCE_BY_ROTATING

#if ROTATE_BY_JOINING

// Rotate the subtree at x such that ch[x][r] is the new root.
void rotate(int& x, bool r) {
  int a, b, c, d;
  std::tie(a, b) = cut(x);
  if (r) {
    std::tie(c, d) = cut(b);
    x = join(join(a, c), d);
  } else {
    std::tie(c, d) = cut(a);
    x = join(c, join(d, b));
  }
}

#else

// Rotate the subtree at x such that ch[x][r] is the new root.
void rotate(int& x, bool r) {
  int y = ch[x][r];
  ch[x][r] = ch[y][!r];
  ch[y][!r] = x;
  push_up(x);
  push_up(y);
  x = y;
}

#endif

// Check if ch[x][!r] is too heavy so that a double rotation is needed.
bool need_double_rotation(int x, bool r) {
  // or sz[ch[x][!r]] > sz[ch[x][r]] * 2;
  return sz[ch[x][!r]] > sz[x] / (2 - ALPHA);
}

// Balance the subtree at x;
void balance(int& x) {
  if (sz[x] == 1) return;
  push_down(x);
  bool r = sz[ch[x][1]] > sz[ch[x][0]];
  if (!too_heavy(sz[ch[x][r]], sz[ch[x][!r]])) return;
  push_down(ch[x][r]);
  if (need_double_rotation(ch[x][r], r)) {
    push_down(ch[ch[x][r]][!r]);
    rotate(ch[x][r], !r);
  }
  rotate(x, r);
}

// Merge two subtrees.
int merge(int x, int y) {
  if (!x || !y) return x | y;
  int a, b;
  if (too_heavy(sz[x], sz[y])) {
    std::tie(a, b) = cut(x);
    int z = join(a, merge(b, y));
    balance(z);
    return z;
  } else if (too_heavy(sz[y], sz[x])) {
    std::tie(a, b) = cut(y);
    int z = join(merge(x, a), b);
    balance(z);
    return z;
  } else {
    return join(x, y);
  }
}

#else

// Merge two subtrees.
int merge(int x, int y) {
  if (!x || !y) return x | y;
  int a, b, c, d;
  if (too_heavy(sz[x], sz[y])) {
    std::tie(a, b) = cut(x);
    if (too_heavy(sz[b] + sz[y], sz[a])) {
      std::tie(c, d) = cut(b);
      return merge(merge(a, c), merge(d, y));
    } else {
      return merge(a, merge(b, y));
    }
  } else if (too_heavy(sz[y], sz[x])) {
    std::tie(a, b) = cut(y);
    if (too_heavy(sz[a] + sz[x], sz[b])) {
      std::tie(c, d) = cut(a);
      return merge(merge(x, c), merge(d, b));
    } else {
      return merge(merge(x, a), b);
    }
  } else {
    return join(x, y);
  }
}

// Balance the subtree at x;
void balance(int& x) {
  if (sz[x] == 1) return;
  if (too_heavy(sz[ch[x][0]], sz[ch[x][1]]) ||
      too_heavy(sz[ch[x][1]], sz[ch[x][0]])) {
    int a, b;
    std::tie(a, b) = cut(x);
    x = merge(a, b);
  }
}

#endif

// --8<-- [start:split]
// Split the subtree at x.
// The left half will have k elements.
std::pair<int, int> split(int x, int k) {
  if (!x) return {0, 0};
  if (!k) return {0, x};
  if (k == sz[x]) return {x, 0};
  int a, b;
  std::tie(a, b) = cut(x);
  if (k <= sz[a]) {
    int ll, rr;
    std::tie(ll, rr) = split(a, k);
    return {ll, merge(rr, b)};
  } else {
    int ll, rr;
    std::tie(ll, rr) = split(b, k - sz[a]);
    return {merge(a, ll), rr};
  }
}

// --8<-- [end:split]
// Reverse the interval [l, r].
void reverse(int l, int r) {
  int ll, rr;
  std::tie(rt, rr) = split(rt, r);
  std::tie(ll, rt) = split(rt, l - 1);
  lazy_reverse(rt);
  rt = merge(ll, merge(rt, rr));
}

// Output the subtree at x.
void print(int x) {
  if (sz[x] == 1) {
    std::cout << val[x] << ' ';
  } else {
    push_down(x);
    print(ch[x][0]);
    print(ch[x][1]);
  }
}

// Output the tree.
void print() {
  print(rt);
  std::cout << '\n';
}

// --8<-- [start:build]
// Build the tree for the interval [ll, rr].
int build(int ll, int rr) {
  if (ll == rr) return new_leaf(ll);
  int mm = (ll + rr) / 2;
  return join(build(ll, mm), build(mm + 1, rr));
}

// --8<-- [end:build]
int main() {
  int n, m;
  std::cin >> n >> m;
  rt = build(1, n);
  for (; m; --m) {
    int l, r;
    std::cin >> l >> r;
    reverse(l, r);
  }
  print();
  return 0;
}

// --8<-- [end:full-text]
