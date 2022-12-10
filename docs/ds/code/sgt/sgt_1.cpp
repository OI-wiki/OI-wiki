#include <bits/stdc++.h>
#define int long long
using namespace std;

namespace ScapegoatTree {
#define ls (t[i].l)
#define rs (t[i].r)

struct node {
  int s, sz, sd, cnt, l, r, w;

  void init(int weight) {
    w = weight;
    l = r = 0;
    s = sz = sd = cnt = 1;
  }
} t[10000005];

int root, tot;
const double alpha = 0.7;

void pushup(int i) {
  t[i].s = t[ls].s + t[rs].s + 1;
  t[i].sz = t[ls].sz + t[rs].sz + t[i].cnt;
  t[i].sd = t[ls].sd + t[rs].sd + (t[i].cnt > 0);
}

bool need_rebuild(int i) {
  if (t[i].cnt == 0) return false;
  if (alpha * t[i].s <= (double)(max(t[ls].s, t[rs].s))) return true;
  if ((double)t[i].sd <= alpha * t[i].s) return true;
  return false;
}

namespace Rebuild {
void flatten(int i, vector<int> &seq) {
  if (!i) return;
  flatten(ls, seq);
  if (t[i].cnt) seq.push_back(i);
  flatten(rs, seq);
}

int build(int l, int r, const vector<int> &seq) {
  if (l == r) return 0;
  int mid = (l + r) >> 1;
  int i = seq[mid];
  ls = build(l, mid, seq);
  rs = build(mid + 1, r, seq);
  pushup(i);
  return i;
}
}  // namespace Rebuild

void rebuild(int &i) {
  vector<int> seq;
  seq.push_back(0);
  Rebuild::flatten(i, seq);
  i = Rebuild::build(1, seq.size(), seq);
}

void newnode(int &i, int v) {
  i = (++tot);
  if (!root) root = i;
  t[i].init(v);
}

void insert(int &i, int v) {
  if (!i) {
    newnode(i, v);
    return;
  }
  if (t[i].w == v)
    t[i].cnt++;
  else if (t[i].w > v)
    insert(ls, v);
  else
    insert(rs, v);
  pushup(i);
  if (need_rebuild(i)) rebuild(i);
}

void remove(int &i, int v) {
  if (!i) return;
  t[i].sz--;
  if (t[i].w == v) {
    if (t[i].cnt > 0) t[i].cnt--;
    return;
  }
  if (t[i].w > v)
    remove(ls, v);
  else
    remove(rs, v);
  pushup(i);
  if (need_rebuild(i)) rebuild(i);
}

int kth(int &i, int k) {
  if (!i) return 0;
  if (t[ls].sz >= k) return kth(ls, k);
  if (t[ls].sz < k - t[i].cnt) return kth(rs, k - t[ls].sz - t[i].cnt);
  return t[i].w;
}

int rnk(int &i, int v) {
  if (!i) return 1;
  if (t[i].w > v) return rnk(ls, v);
  if (t[i].w < v) return rnk(rs, v) + t[ls].sz + t[i].cnt;
  return t[ls].sz + 1;
}

int upper_bound(int &i, int v, bool great = 0) {
  if (!i) return !great;
  if (t[i].w == v && t[i].cnt > 0) return t[ls].sz + (!great) * (t[i].cnt + 1);
  if (!great) {
    if (v < t[i].w) return upper_bound(ls, v);
    return upper_bound(rs, v) + t[ls].sz + t[i].cnt;
  }
  if (t[i].w < v) return upper_bound(rs, v, 1) + t[ls].sz + t[i].cnt;
  return upper_bound(ls, v, 1);
}

int pre(int &i, int v) { return kth(i, upper_bound(i, v, 1)); }

int next(int &i, int v) { return kth(i, upper_bound(i, v)); }
}  // namespace ScapegoatTree

int last = 0, ans = 0;

signed main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  int m, n;
  cin >> m >> n;
  while (m--) {
    int v;
    cin >> v;
    ScapegoatTree::insert(ScapegoatTree::root, v);
  }
  while (n--) {
    int op, x;
    cin >> op >> x;
    x ^= last;
    if (op == 1) ScapegoatTree::insert(ScapegoatTree::root, x);
    if (op == 2) ScapegoatTree::remove(ScapegoatTree::root, x);
    if (op == 3) last = ScapegoatTree::rnk(ScapegoatTree::root, x);
    if (op == 4) last = ScapegoatTree::kth(ScapegoatTree::root, x);
    if (op == 5) last = ScapegoatTree::pre(ScapegoatTree::root, x);
    if (op == 6) last = ScapegoatTree::next(ScapegoatTree::root, x);
    if (op == 3 || op == 4 || op == 5 || op == 6) {
      ans ^= last;
    }
  }
  cout << ans;
  return 0;
}
