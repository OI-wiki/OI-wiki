#include <algorithm>
#include <cstdio>
#include <deque>
#include <random>
#include <vector>
using namespace std;
constexpr int neg_inf = -2147483647, pos_inf = 2147483647;
mt19937 rng(0);

// The supporting randomized balanced trees retain duplicates and subtree sizes.
struct Tree {
  struct Node {
    int key = 0, count = 0, size = 0, left = 0, right = 0;
    unsigned priority = 0;
  };

  deque<Node> nodes{Node{}};
  int root = 0;

  void pull(int x) {
    nodes[x].size =
        nodes[nodes[x].left].size + nodes[nodes[x].right].size + nodes[x].count;
  }

  int join(int a, int b) {
    if (!a || !b) return a + b;
    if (nodes[a].priority < nodes[b].priority) {
      nodes[a].right = join(nodes[a].right, b);
      pull(a);
      return a;
    }
    nodes[b].left = join(a, nodes[b].left);
    pull(b);
    return b;
  }

  void rotate(int& x, bool right) {
    int y = right ? nodes[x].left : nodes[x].right;
    if (right) {
      nodes[x].left = nodes[y].right;
      nodes[y].right = x;
    } else {
      nodes[x].right = nodes[y].left;
      nodes[y].left = x;
    }
    pull(x);
    pull(y);
    x = y;
  }

  void insert_at(int& x, int key) {
    if (!x) {
      x = static_cast<int>(nodes.size());
      nodes.push_back({key, 1, 1, 0, 0, rng()});
      return;
    }
    if (key == nodes[x].key)
      ++nodes[x].count;
    else if (key < nodes[x].key) {
      insert_at(nodes[x].left, key);
      if (nodes[nodes[x].left].priority < nodes[x].priority) rotate(x, true);
    } else {
      insert_at(nodes[x].right, key);
      if (nodes[nodes[x].right].priority < nodes[x].priority) rotate(x, false);
    }
    pull(x);
  }

  void erase_at(int& x, int key) {
    if (!x) return;
    if (key == nodes[x].key) {
      if (nodes[x].count > 1)
        --nodes[x].count;
      else {
        x = join(nodes[x].left, nodes[x].right);
        return;
      }
    } else
      erase_at(key < nodes[x].key ? nodes[x].left : nodes[x].right, key);
    pull(x);
  }

  void insert(int key) { insert_at(root, key); }

  int find(int key) { return key; }

  void dele(int key) { erase_at(root, key); }

  int chk_rank(int key) {
    int x = root, rank = 1;
    while (x) {
      if (nodes[x].key < key)
        rank += nodes[nodes[x].left].size + nodes[x].count, x = nodes[x].right;
      else
        x = nodes[x].left;
    }
    return rank;
  }

  int chk_front(int key) {
    int x = root, answer = neg_inf;
    while (x) {
      if (nodes[x].key < key)
        answer = nodes[x].key, x = nodes[x].right;
      else
        x = nodes[x].left;
    }
    return answer;
  }

  int chk_next(int key) {
    int x = root, answer = pos_inf;
    while (x) {
      if (nodes[x].key > key)
        answer = nodes[x].key, x = nodes[x].left;
      else
        x = nodes[x].right;
    }
    return answer;
  }
};

vector<Tree> spy;
vector<int> dat;

// --8<-- [start:example0]
int vec_rank(int k, int l, int r, int x, int y, int t) {
  if (x <= l && r <= y) {
    return spy[k].chk_rank(t);
  }
  int mid = (l + r) >> 1;
  int res = 0;
  if (x <= mid) res += vec_rank(k << 1, l, mid, x, y, t);
  if (y > mid) res += vec_rank(k << 1 | 1, mid + 1, r, x, y, t);
  if (x <= mid && y > mid) res--;
  return res;
}

// --8<-- [end:example0]
// --8<-- [start:example2]
void vec_chg(int k, int l, int r, int loc, int x) {
  int t = spy[k].find(dat[loc]);
  spy[k].dele(t);
  spy[k].insert(x);
  if (l == r) return;
  int mid = (l + r) >> 1;
  if (loc <= mid) vec_chg(k << 1, l, mid, loc, x);
  if (loc > mid) vec_chg(k << 1 | 1, mid + 1, r, loc, x);
}

// --8<-- [end:example2]
// --8<-- [start:example3]
int vec_front(int k, int l, int r, int x, int y, int t) {
  if (x <= l && r <= y) return spy[k].chk_front(t);
  int mid = (l + r) >> 1;
  int res = neg_inf;
  if (x <= mid) res = max(res, vec_front(k << 1, l, mid, x, y, t));
  if (y > mid) res = max(res, vec_front(k << 1 | 1, mid + 1, r, x, y, t));
  return res;
}

// --8<-- [end:example3]
void build(int k, int l, int r) {
  for (int i = l; i <= r; ++i) spy[k].insert(dat[i]);
  if (l == r) return;
  int m = (l + r) / 2;
  build(k * 2, l, m);
  build(k * 2 + 1, m + 1, r);
}

int vec_next(int k, int l, int r, int x, int y, int t) {
  if (x <= l && r <= y) return spy[k].chk_next(t);
  int m = (l + r) / 2, res = pos_inf;
  if (x <= m) res = min(res, vec_next(k * 2, l, m, x, y, t));
  if (y > m) res = min(res, vec_next(k * 2 + 1, m + 1, r, x, y, t));
  return res;
}

int main() {
  int n, q;
  if (scanf("%d%d", &n, &q) != 2) return 0;
  dat.resize(n + 1);
  spy.resize(4 * n + 4);
  for (int i = 1; i <= n; ++i) scanf("%d", &dat[i]);
  build(1, 1, n);
  while (q--) {
    int op, tl, tr, tk;
    scanf("%d", &op);
    if (op == 3) {
      scanf("%d%d", &tl, &tk);
      vec_chg(1, 1, n, tl, tk);
      dat[tl] = tk;
      continue;
    }
    scanf("%d%d%d", &tl, &tr, &tk);
    if (op == 1)
      printf("%d\n", vec_rank(1, 1, n, tl, tr, tk));
    else if (op == 2) {
      // --8<-- [start:example1]
      int el = 0, er = 100000001, emid;
      while (el != er) {
        emid = (el + er) >> 1;
        if (vec_rank(1, 1, n, tl, tr, emid) - 1 < tk)
          el = emid + 1;
        else
          er = emid;
      }
      printf("%d\n", el - 1);
      // --8<-- [end:example1]
    } else if (op == 4)
      printf("%d\n", vec_front(1, 1, n, tl, tr, tk));
    else
      printf("%d\n", vec_next(1, 1, n, tl, tr, tk));
  }
}
