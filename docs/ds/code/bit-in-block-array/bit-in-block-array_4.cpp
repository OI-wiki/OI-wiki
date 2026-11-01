#include <algorithm>
#include <cstdio>
#include <random>
#include <vector>
using namespace std;
constexpr int N = 1e5 + 5;

vector<int> g[N];
int n, a[N];

mt19937 rng(random_device{}());

struct Treap {
  struct node {
    node *l, *r;
    unsigned rnd;
    int sz, v;

    node(int _v) : l(NULL), r(NULL), rnd(rng()), sz(1), v(_v) {}
  };

  int get_size(node*& p) { return p ? p->sz : 0; }

  void push_up(node*& p) {
    if (!p) return;
    p->sz = get_size(p->l) + get_size(p->r) + 1;
  }

  node* root;

  node* merge(node* a, node* b) {
    if (!a) return b;
    if (!b) return a;
    if (a->rnd < b->rnd) {
      a->r = merge(a->r, b);
      push_up(a);
      return a;
    } else {
      b->l = merge(a, b->l);
      push_up(b);
      return b;
    }
  }

  void split_val(node* p, const int& k, node*& a, node*& b) {
    if (!p)
      a = b = NULL;
    else {
      if (p->v <= k) {
        a = p;
        split_val(p->r, k, a->r, b);
        push_up(a);
      } else {
        b = p;
        split_val(p->l, k, a, b->l);
        push_up(b);
      }
    }
  }

  void split_size(node* p, int k, node*& a, node*& b) {
    if (!p)
      a = b = NULL;
    else {
      if (get_size(p->l) <= k) {
        a = p;
        split_size(p->r, k - get_size(p->l), a->r, b);
        push_up(a);
      } else {
        b = p;
        split_size(p->l, k, a, b->l);
        push_up(b);
      }
    }
  }

  void insert(int val) {
    node *a, *b;
    split_val(root, val, a, b);
    a = merge(a, new node(val));
    root = merge(a, b);
  }

  int query(int val) {
    node *a, *b;
    split_val(root, val, a, b);
    int res = get_size(a);
    root = merge(a, b);
    return res;
  }

  int qry(int l, int r) { return query(r) - query(l - 1); }
};

// Segment Tree
Treap T[N << 2];

void insert(int x, int l, int r, int p, int val) {
  T[x].insert(val);
  if (l == r) return;
  int mid = (l + r) >> 1;
  if (p <= mid)
    insert(x << 1, l, mid, p, val);
  else
    insert(x << 1 | 1, mid + 1, r, p, val);
}

int query(int x, int l, int r, int L, int R, int val) {
  if (l == L && r == R) return T[x].query(val);
  int mid = (l + r) >> 1;
  if (R <= mid) return query(x << 1, l, mid, L, R, val);
  if (L > mid) return query(x << 1 | 1, mid + 1, r, L, R, val);
  return query(x << 1, l, mid, L, mid, val) +
         query(x << 1 | 1, mid + 1, r, mid + 1, R, val);
}

int query(int l, int r, int val) {
  if (l > r) return -1;
  return query(1, 1, n, l, r, val);
}

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) scanf("%d", &a[i]);
  for (int i = 1; i <= n; ++i) g[a[i]].push_back(i);

  // a_0 和 a_{n+1}为哨兵节点
  int ans = n + 2, lst, ok;
  for (int i = 1; i <= n + 1; ++i) {
    g[i].push_back(n + 1);

    lst = 0;
    ok = 0;
    for (int pos : g[i]) {
      if (query(lst + 1, pos - 1, lst) == i - 1) {
        ok = 1;
        break;
      }
      lst = pos;
    }

    if (!ok) {
      ans = i;
      break;
    }

    lst = 0;
    g[i].pop_back();
    for (int pos : g[i]) {
      insert(1, 1, n, pos, lst);
      lst = pos;
    }
  }
  printf("%d\n", ans);
  return 0;
}
