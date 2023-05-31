#include <bits/stdc++.h>
#define update(u) \
  if (u->lf->size) u->size = u->lf->size + u->rf->size, u->val = u->rf->val
#define new_Node(a, b, c, d) (&(*st[cnt++] = Node(a, b, c, d)))
#define merge(a, b) new_Node(a->size + b->size, b->val, a, b)
#define ratio 4
using namespace std;

int Min(const int x, const int y) { return x < y ? x : y; }

int Max(const int x, const int y) { return x > y ? x : y; }

int n, cnt;

struct Node {
  int size, val;
  Node *lf, *rf;

  Node(int a, int b, Node *l, Node *r) : size(a), val(b), lf(l), rf(r) {}

  Node() {}
};

Node *root, *null, *st[200010], t[200010];

void rotate(Node *u) {
  if (u->lf->size > u->rf->size * ratio)
    u->rf = merge(u->lf->rf, u->rf), st[--cnt] = u->lf, u->lf = u->lf->lf;
  if (u->rf->size > u->lf->size * ratio)
    u->lf = merge(u->lf, u->rf->lf), st[--cnt] = u->rf, u->rf = u->rf->rf;
}

void insert(Node *u, int x) {
  if (u->size == 1)
    u->lf = new_Node(1, Min(u->val, x), null, null),
    u->rf = new_Node(1, Max(u->val, x), null, null);
  else
    insert(x > u->lf->val ? u->rf : u->lf, x);
  update(u), rotate(u);
}

void erase(Node *u, int x) {
  if (u->lf->size == 1 && u->lf->val == x)
    st[--cnt] = u->lf, st[--cnt] = u->rf, *u = *u->rf;
  else if (u->rf->size == 1 && u->rf->val == x)
    st[--cnt] = u->lf, st[--cnt] = u->rf, *u = *u->lf;
  else
    erase(x > u->lf->val ? u->rf : u->lf, x);
  update(u), rotate(u);
}

int find(Node *u, int x) {
  if (u->size == 1) return u->val;
  return u->lf->size < x ? find(u->rf, x - u->lf->size) : find(u->lf, x);
}

int Rank(Node *u, int x) {
  if (u->size == 1) return 1;
  return u->lf->val < x ? u->lf->size + Rank(u->rf, x) : Rank(u->lf, x);
}

int pre(int x) { return find(root, Rank(root, x) - 1); }

int nxt(int x) { return find(root, Rank(root, x + 1)); }

void debug(Node *u) {
  if (u->lf != null) debug(u->lf);
  if (u->size == 1) printf(" %d", u->val);
  if (u->rf != null) debug(u->rf);
}

int main() {
  scanf("%d", &n);
  cnt = 0;
  null = new Node(0, 0, 0, 0);
  root = new Node(1, INT_MAX, null, null);
  for (int i = 0; i <= 200000; i++) st[i] = &t[i];
  for (int i = 1; i <= n; i++) {
    int t, a;
    scanf("%d%d", &t, &a);
    if (t == 1)
      insert(root, a);
    else if (t == 2)
      erase(root, a);
    else if (t == 3)
      printf("%d\n", Rank(root, a));
    else if (t == 4)
      printf("%d\n", find(root, a));
    else if (t == 5)
      printf("%d\n", pre(a));
    else if (t == 6)
      printf("%d\n", nxt(a));
  }
  return 0;
}
