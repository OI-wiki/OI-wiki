#include <algorithm>
#include <cstdio>
#include <random>
using namespace std;
constexpr int N = 2e5 + 5;
mt19937 rng(random_device{}());

int n, m, pa[N], pb[N];

// Treap
struct Treap {
  struct node {
    node *l, *r;
    int sz, rnd, v;

    node(int _v) : l(NULL), r(NULL), sz(1), rnd(rng()), v(_v) {}
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

  void ins(int val) {
    node *a, *b;
    split_val(root, val, a, b);
    a = merge(a, new node(val));
    root = merge(a, b);
  }

  void del(int val) {
    node *a, *b, *c, *d;
    split_val(root, val, a, b);
    split_val(a, val - 1, c, d);
    delete d;
    root = merge(c, b);
  }

  int qry(int val) {
    node *a, *b;
    split_val(root, val, a, b);
    int res = get_size(a);
    root = merge(a, b);
    return res;
  }

  int qry(int l, int r) { return qry(r) - qry(l - 1); }
};

// Fenwick Tree
Treap T[N];

int lb(int x) { return x & -x; }

void ins(int x, int v) {
  for (; x <= n; x += lb(x)) T[x].ins(v);
}

void del(int x, int v) {
  for (; x <= n; x += lb(x)) T[x].del(v);
}

int qry(int x, int mi, int ma) {
  int res = 0;
  for (; x; x -= lb(x)) res += T[x].qry(mi, ma);
  return res;
}

int main() {
  scanf("%d %d", &n, &m);
  int v;
  for (int i = 1; i <= n; ++i) scanf("%d", &v), pa[v] = i;
  for (int i = 1; i <= n; ++i) scanf("%d", &v), pb[i] = pa[v];
  for (int i = 1; i <= n; ++i) ins(i, pb[i]);

  int op, la, lb, ra, rb, x, y;
  for (int i = 1; i <= m; ++i) {
    scanf("%d", &op);
    if (op == 1) {
      scanf("%d %d %d %d", &la, &ra, &lb, &rb);
      printf("%d\n", qry(rb, la, ra) - qry(lb - 1, la, ra));
    } else if (op == 2) {
      scanf("%d %d", &x, &y);
      del(x, pb[x]);
      del(y, pb[y]);
      swap(pb[x], pb[y]);
      ins(x, pb[x]);
      ins(y, pb[y]);
    }
  }
  return 0;
}
