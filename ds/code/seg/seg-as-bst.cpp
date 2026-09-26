#include <iostream>
#include <vector>

// --8<-- [start:seg-tree]
// Segment tree on values, supporting the ordered-set operations of a BST.
int rt, id, L, R;
std::vector<int> lc, rc;
std::vector<int> cnt;

void build(int l, int r, int n) {
  rt = 0, id = 0, L = l, R = r;
  lc.resize(n), rc.resize(n), cnt.resize(n);
}

// Insert v.
void insert(int& cr, int ll, int rr, int v) {
  if (!cr) cr = ++id;
  ++cnt[cr];
  if (ll == rr) return;
  int mm = ll + ((rr - ll) >> 1);
  if (v <= mm)
    insert(lc[cr], ll, mm, v);
  else
    insert(rc[cr], mm + 1, rr, v);
}

void insert(int v) { insert(rt, L, R, v); }

// Remove v.
// If there are multiple, remove once.
// Return true if there is any, return false if there is none.
bool remove(int cr, int ll, int rr, int v) {
  if (!cnt[cr]) return false;
  if (ll == rr) return cnt[cr]--;
  int mm = ll + ((rr - ll) >> 1);
  auto succ = false;
  if (v <= mm)
    succ = remove(lc[cr], ll, mm, v);
  else
    succ = remove(rc[cr], mm + 1, rr, v);
  return succ && cnt[cr]--;
}

bool remove(int v) { return remove(rt, L, R, v); }

// Count values within range [l, r].
int count(int cr, int ll, int rr, int tl, int tr) {
  if (!cr) return 0;
  if (tl <= ll && rr <= tr) return cnt[cr];
  int mm = ll + ((rr - ll) >> 1);
  int res = 0;
  if (tl <= mm) res = count(lc[cr], ll, mm, tl, tr);
  if (mm < tr) res += count(rc[cr], mm + 1, rr, tl, tr);
  return res;
}

int count(int l, int r) { return count(rt, L, R, l, r); }

// Find the rank of v, i.e., one plus the count of numbers less than v.
int find_rank(int v) { return v > L ? count(L, v - 1) + 1 : 1; }

// Find the k-th element.
int find_kth(int cr, int ll, int rr, int k) {
  if (ll == rr) return ll;
  int mm = ll + ((rr - ll) >> 1);
  if (k <= cnt[lc[cr]])
    return find_kth(lc[cr], ll, mm, k);
  else
    return find_kth(rc[cr], mm + 1, rr, k - cnt[lc[cr]]);
}

int find_kth(int k) {
  return k > cnt[rt] || k <= 0 ? -1 : find_kth(rt, L, R, k);
}

// Find the predecessor of v.
int find_prev(int x) { return find_kth(find_rank(x) - 1); }

// Find the successor of v.
int find_next(int x) { return find_kth(find_rank(x + 1)); }

// --8<-- [end:seg-tree]
int main() {
  std::ios::sync_with_stdio(false), std::cin.tie(nullptr);
  int n;
  std::cin >> n;
  build(-1e7, 1e7, n << 5);
  for (; n; --n) {
    int op, x;
    std::cin >> op >> x;
    if (op == 1) {
      insert(x);
    } else if (op == 2) {
      remove(x);
    } else if (op == 3) {
      std::cout << find_rank(x) << '\n';
    } else if (op == 4) {
      std::cout << find_kth(x) << '\n';
    } else if (op == 5) {
      std::cout << find_prev(x) << '\n';
    } else if (op == 6) {
      std::cout << find_next(x) << '\n';
    }
  }
  return 0;
}
