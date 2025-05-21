// --8<-- [start:full-text]
#include <iostream>
#include <tuple>

// Change here to use different strategies to balance and to merge.
#define BALANCE_BY_ROTATING 1
#define ROTATE_BY_JOINING 0

constexpr int N = 2e6;
constexpr double ALPHA = 0.292;

int id, rt, ch[N][2], sz[N], val[N];
int pool[N], top;

// --8<-- [start:push-up]
void push_up(int x) {
  sz[x] = sz[ch[x][0]] + sz[ch[x][1]];
  val[x] = val[ch[x][1]];
}

// --8<-- [end:push-up]
// --8<-- [start:helper]
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
  int y = ch[x][0];
  int z = ch[x][1];
  del_node(x);
  return std::make_pair(y, z);
}

// --8<-- [end:helper]
// --8<-- [start:too-heavy]
// Check whether a subtree of weight SX is too heavy
//     in a tree of weight SX + SY.
bool too_heavy(int sx, int sy) {
  // or sx > sy * 3;
  return sy < ALPHA * (sx + sy);
}

// --8<-- [end:too-heavy]
#if BALANCE_BY_ROTATING

#if ROTATE_BY_JOINING

// --8<-- [start:rotate-by-joining]
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

// --8<-- [end:rotate-by-joining]
#else

// --8<-- [start:rotate-not-by-joining]
// Rotate the subtree at x such that ch[x][r] is the new root.
void rotate(int& x, bool r) {
  int y = ch[x][r];
  ch[x][r] = ch[y][!r];
  ch[y][!r] = x;
  push_up(x);
  push_up(y);
  x = y;
}

// --8<-- [end:rotate-not-by-joining]
#endif

// --8<-- [start:balance]
// Check if ch[x][!r] is too heavy so that a double rotation is needed.
bool need_double_rotation(int x, bool r) {
  // or sz[ch[x][!r]] > sz[ch[x][r]] * 2;
  return sz[ch[x][!r]] > sz[x] / (2 - ALPHA);
}

// Balance the subtree at x;
void balance(int& x) {
  if (sz[x] == 1) return;
  bool r = sz[ch[x][1]] > sz[ch[x][0]];
  if (!too_heavy(sz[ch[x][r]], sz[ch[x][!r]])) return;
  if (need_double_rotation(ch[x][r], r)) {
    rotate(ch[x][r], !r);
  }
  rotate(x, r);
}

// --8<-- [end:balance]
// --8<-- [start:merge-by-balancing]
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

// --8<-- [end:merge-by-balancing]
#else

// --8<-- [start:merge]
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

// --8<-- [end:merge]
// --8<-- [start:balance-by-merging]
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

// --8<-- [end:balance-by-merging]
#endif

// --8<-- [start:insert-remove]
// Insert v to the subtree at x.
void insert(int& x, int v) {
  if (!x) {
    x = new_leaf(v);
  } else if (sz[x] == 1) {
    bool r = v >= val[x];
    ch[x][r] = new_leaf(v);
    ch[x][!r] = new_leaf(val[x]);
    push_up(x);
  } else {
    bool r = v > val[ch[x][0]];
    insert(ch[x][r], v);
    push_up(x);
    balance(x);
  }
}

// Insert v.
void insert(int v) { insert(rt, v); }

// Remove v from the subtree at x.
bool remove(int& x, int v) {
  if (!x) return false;
  if (sz[x] == 1) {
    if (val[x] == v) {
      del_node(x);
      return true;
    } else {
      return false;
    }
  } else {
    bool r = v > val[ch[x][0]];
    bool succ = remove(ch[x][r], v);
    if (!ch[x][r]) {
      x = ch[x][!r];
    } else {
      push_up(x);
      balance(x);
    }
    return succ;
  }
}

// Remove v.
bool remove(int v) { return remove(rt, v); }

// --8<-- [end:insert-remove]
// --8<-- [start:rank]
// Count the number of nodes less than v in the subtree at x.
int count_less_than(int x, int v) {
  if (!x) return 0;
  int res = 0;
  while (sz[x] > 1) {
    if (val[ch[x][0]] < v) {
      res += sz[ch[x][0]];
      x = ch[x][1];
    } else {
      x = ch[x][0];
    }
  }
  return res + (val[x] < v ? 1 : 0);
}

// Find the rank of v.
int find_rank(int v) { return count_less_than(rt, v) + 1; }

// --8<-- [end:rank]
// --8<-- [start:kth-element]
// Find the k-th element in the subtree at x.
// It is guaranteed that such an element exists.
int find_kth(int x, int k) {
  while (sz[x] > 1) {
    if (sz[ch[x][0]] >= k) {
      x = ch[x][0];
    } else {
      k -= sz[ch[x][0]];
      x = ch[x][1];
    }
  }
  return val[x];
}

// Find the k-th element.
int find_kth(int k) { return k > sz[rt] || k <= 0 ? -1 : find_kth(rt, k); }

// --8<-- [end:kth-element]
// --8<-- [start:prev-next]
// Find the predecessor of v.
int find_prev(int v) { return find_kth(find_rank(v) - 1); }

// Find the successor of v.
int find_next(int v) { return find_kth(find_rank(v + 1)); }

// --8<-- [end:prev-next]
int main() {
  int n;
  std::cin >> n;
  for (; n; --n) {
    int op, x;
    std::cin >> op >> x;
    switch (op) {
      case 1:
        insert(x);
        break;
      case 2:
        remove(x);
        break;
      case 3:
        std::cout << find_rank(x) << '\n';
        break;
      case 4:
        std::cout << find_kth(x) << '\n';
        break;
      case 5:
        std::cout << find_prev(x) << '\n';
        break;
      case 6:
        std::cout << find_next(x) << '\n';
        break;
    }
  }
  return 0;
}

// --8<-- [end:full-text]
