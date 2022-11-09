#define _USE_MATH_DEFINES
#include <bits/stdc++.h>

#define PI M_PI
#define E M_E
#define npt nullptr
#define SON i->to
#define siz(p) (p ? p->siz : 0)

using namespace std;

mt19937 rnd(random_device{}());

int rndd(int l, int r) { return rnd() % (r - l + 1) + l; }

typedef unsigned int uint;
typedef unsigned long long unll;
typedef long long ll;

struct Node;

struct Edge {
  Edge* nxt;
  Node* to;
  void* operator new(size_t);

  Edge(Edge* nxt, Node* to) : nxt(nxt), to(to) { ; }

  Edge(void) = default;
} eData[210000];

void* Edge::operator new(size_t) {
  static Edge* P = eData;
  return ++P;
}

int N, M, R, MOD;

struct Node {
#define dep(p) (p ? p->dep : 0)
  int val;
  int dfn;
  int dep;
  int siz;
  Node* fa;
  Node* top;
  Node* hson;
  Edge* head;

  Node(int val) : val(val) { ; }

  Node(void) = default;
  void* operator new(size_t);
} nData[110000];

void* Node::operator new(size_t) {
  static Node* P = nData;
  return ++P;
}

Node* tr[110000];
Node* idx[110000];

template <typename T = int>
inline T read(void);

void dfs_pretreat(Node* p, Node* fa) {
  p->fa = fa;
  p->dep = dep(p->fa) + 1;
  p->siz = 1;
  for (auto i = p->head; i; i = i->nxt) {
    if (SON == fa) continue;
    dfs_pretreat(SON, p);
    p->siz += SON->siz;
    if (siz(SON) > siz(p->hson)) p->hson = SON;
  }
}

void dfs_build(Node* p, Node* top) {
  static int dfn(0);
  p->dfn = ++dfn;
  idx[p->dfn] = p;
  p->top = top;
  if (p->hson) dfs_build(p->hson, top);
  for (auto i = p->head; i; i = i->nxt) {
    if (SON != p->hson && SON != p->fa) {
      dfs_build(SON, SON);
    }
  }
}

class SegTree {
 private:
  ll st[110000 << 2], lt[110000 << 2];
#define LS (p << 1)
#define RS ((p << 1) + 1)
#define MID ((gl + gr) >> 1)
#define SIZ (gr - gl + 1)
#define SIZL (MID - gl + 1)
#define SIZR (gr - MID - 1 + 1)
 public:
  void Pushdown(int p, int gl, int gr) {
    st[LS] = (st[LS] + SIZL * lt[p] % MOD) % MOD,
    st[RS] = (st[RS] + SIZR * lt[p] % MOD) % MOD,
    lt[LS] = (lt[LS] + lt[p]) % MOD, lt[RS] = (lt[RS] + lt[p]) % MOD;
    lt[p] = 0;
  }

  void Pushup(int p) { st[p] = (st[LS] + st[RS]) % MOD; }

  void Build(int p = 1, int gl = 1, int gr = N) {
    if (gl == gr) {
      // printf("st[%d] <- idx[%d] = %d\n", p, gl, idx[gl]->val);
      return (void)(st[p] = idx[gl = gr]->val);
    }
    Build(LS, gl, MID);
    Build(RS, MID + 1, gr);
    Pushup(p);
  }

  void Modify(int l, int r, int val, int p = 1, int gl = 1, int gr = N) {
    if (l <= gl && gr <= r)
      return (void)(st[p] = (st[p] + SIZ * val) % MOD,
                    lt[p] = (lt[p] + val) % MOD);
    if (lt[p]) Pushdown(p, gl, gr);
    if (l <= MID) Modify(l, r, val, LS, gl, MID);
    if (r >= MID + 1) Modify(l, r, val, RS, MID + 1, gr);
    Pushup(p);
  }

  ll Query(int l, int r, int p = 1, int gl = 1, int gr = N) {
    if (l <= gl && gr <= r) return st[p];
    if (lt[p]) Pushdown(p, gl, gr);
    return ((l <= MID ? Query(l, r, LS, gl, MID) : 0) +
            (r >= MID + 1 ? Query(l, r, RS, MID + 1, gr) : 0)) %
           MOD;
  }

  void Desc(void) {
    int cur(0);
    for (int i = 1; i <= 1 << 4; i <<= 1)
      for (int j = 1; j <= i; ++j)
        printf("%lld%c", st[++cur], j == i ? '\n' : ' ');
  }
} st;

#define top(p) (p ? p->top : npt)
#define dfn(p) (p ? p->dfn : 0)

void ModifyTree(Node* from, Node* to, int val) {
  while (top(from) != top(to)) {
    if (dep(top(from)) < dep(top(to))) swap(from, to);
    st.Modify(dfn(from->top), dfn(from), val);
    from = from ? from->top->fa : npt;
  }
  if (dep(from) < dep(to)) swap(from, to);
  st.Modify(dfn(to), dfn(from), val);
}

ll QueryTree(Node* from, Node* to) {
  ll ret(0);
  while (top(from) != top(to)) {
    if (dep(top(from)) < dep(top(to))) swap(from, to);
    ret = (ret + st.Query(dfn(from->top), dfn(from))) % MOD;
    from = from ? from->top->fa : npt;
  }
  if (dep(from) < dep(to)) swap(from, to);
  ret = (ret + st.Query(dfn(to), dfn(from))) % MOD;
  return ret;
}

int main() {
  N = read(), M = read(), R = read(), MOD = read();
  for (int i = 1; i <= N; ++i) tr[i] = new Node(read());
  for (int i = 1; i <= N - 1; ++i) {
    int f = read(), t = read();
    tr[f]->head = new Edge(tr[f]->head, tr[t]);
    tr[t]->head = new Edge(tr[t]->head, tr[f]);
  }
  dfs_pretreat(tr[R], npt);
  dfs_build(tr[R], tr[R]);
  st.Build();
  while (M--) {
    int opt = read();
    switch (opt) {
      case 1: {
        int f = read(), t = read(), val = read() % MOD;
        ModifyTree(tr[f], tr[t], val);
        break;
      }
      case 2: {
        int f = read(), t = read();
        printf("%lld\n", QueryTree(tr[f], tr[t]));
        break;
      }
      case 3: {
        int x = read(), val = read() % MOD;
        st.Modify(tr[x]->dfn, tr[x]->dfn + tr[x]->siz - 1, val);
        break;
      }
      case 4: {
        int x = read();
        printf("%lld\n", st.Query(tr[x]->dfn, tr[x]->dfn + tr[x]->siz - 1));
        break;
      }
    }
  }
  // fprintf(stderr, "Time: %.6lf\n", (double)clock() / CLOCKS_PER_SEC);
  return 0;
}

template <typename T>
inline T read(void) {
  T ret(0);
  short flag(1);
  char c = getchar();
  while (c != '-' && !isdigit(c)) c = getchar();
  if (c == '-') flag = -1, c = getchar();
  while (isdigit(c)) {
    ret *= 10;
    ret += int(c - '0');
    c = getchar();
  }
  ret *= flag;
  return ret;
}