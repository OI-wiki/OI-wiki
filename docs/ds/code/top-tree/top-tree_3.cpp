#include <algorithm>
#include <iostream>
#include <map>
#include <utility>
#define ls(x) son[x][0]
#define rs(x) son[x][1]
#define ms(x) son[x][2]
using namespace std;

constexpr int MAXN = 300005;

int son[MAXN][3], s[MAXN][2], tot, val[MAXN], r[MAXN], top, Stack[MAXN],
    father[MAXN];

// --8<-- [start:example169a]
// ls 一个SATT节点的左儿子
// rs 一个SATT节点的右儿子
// ms 一个SATT节点的中儿子
// son[x][0] ls
// son[x][1] rs
// son[x][2] ms
// type==1 在 Rake Tree中
// type==0 在 Compress Tree中
int new_node() {
  if (top) {
    top--;
    return Stack[top + 1];
  }
  return ++tot;
}

// --8<-- [end:example169a]

// --8<-- [start:example167a]
// 是一个节点的中儿子或无父亲
// ls 一个SATT节点的左儿子
// rs 一个SATT节点的右儿子
// ms 一个SATT节点的中儿子
// type==1 在 Rake Tree中
// type==0 在 Compress Tree中
bool isroot(int x) { return rs(father[x]) != x && ls(father[x]) != x; }

// --8<-- [end:example167a]

// --8<-- [start:example167b]
bool direction(int x) { return rs(father[x]) == x; }

// --8<-- [end:example167b]

void pushup(int x, int ty) {
  if (ty) {
    s[x][1] = s[ls(x)][1] ^ s[rs(x)][1] ^ s[ms(x)][1];
    return;
  }
  s[x][0] = s[ls(x)][0] ^ val[x] ^ s[rs(x)][0];
  s[x][1] = s[ls(x)][1] ^ s[ms(x)][1] ^ s[rs(x)][1] ^ val[x];
}

void push_rev(int x) {
  if (!x) return;
  r[x] ^= 1;
  swap(ls(x), rs(x));
}

void pushdown(int x, int ty) {
  if (ty) return;
  if (r[x]) {
    push_rev(ls(x));
    push_rev(rs(x));
    r[x] = 0;
  }
}

void pushall(int x, int ty) {
  if (!isroot(x)) pushall(father[x], ty);
  pushdown(x, ty);
}

// --8<-- [start:example169b]
void setfather(int x, int fa, int type) {
  if (x) father[x] = fa;
  son[fa][type] = x;
}

// --8<-- [end:example169b]

// --8<-- [start:example167c]
void rotate(int x, int type) {
  int y = father[x], z = father[y], d = direction(x), w = son[x][d ^ 1];
  if (z) son[z][ms(z) == y ? 2 : direction(y)] = x;
  son[x][d ^ 1] = y;
  son[y][d] = w;
  if (w) father[w] = y;
  father[y] = x;
  father[x] = z;
  pushup(y, type);
  pushup(x, type);
  return;
}

// --8<-- [end:example167c]

// --8<-- [start:example167d]
void splay(int x, int type, int goal = 0) {
  pushall(x, type);  // 下传标记
  for (int y; y = father[x], (!isroot(x)) && y != goal; rotate(x, type)) {
    if (father[y] != goal && (!isroot(y))) {
      rotate(direction(x) ^ direction(y) ? x : y, type);
    }
  }
  return;
}

// --8<-- [end:example167d]

void Clear(int x) {
  father[x] = 0;
  ls(x) = ms(x) = rs(x) = s[x][0] = s[x][1] = r[x] = val[x] = 0;
  Stack[++top] = x;
}

// --8<-- [start:example169c]
void Delete(int x) {
  setfather(ms(x), father[x], 1);
  if (ls(x)) {
    int p = ls(x);
    pushdown(p, 1);
    while (rs(p)) p = rs(p), pushdown(p, 1);
    splay(p, 1, x);
    setfather(rs(x), p, 1);
    setfather(p, father[x], 2);
    pushup(p, 1);
    pushup(father[x], 0);
  } else
    setfather(rs(x), father[x], 2);
  Clear(x);
}

// --8<-- [end:example169c]

// --8<-- [start:example169d]
void splice(int x) {
  // local splay
  splay(x, 1);
  int y = father[x];
  splay(y, 0);
  pushdown(x, 1);
  // splice
  if (rs(y)) {
    swap(father[ms(x)], father[rs(y)]);
    swap(ms(x), rs(y));
    pushup(x, 1);
  } else
    Delete(x);
  pushup(rs(y), 0);
  pushup(y, 0);
}

// --8<-- [end:example169d]

// --8<-- [start:example169e]
void access(int x) {
  splay(x, 0);
  int ys = x;
  // --8<-- [start:example168]
  if (rs(x)) {
    int y = new_node();
    setfather(ms(x), y, 0);
    setfather(rs(x), y, 2);
    rs(x) = 0;
    setfather(y, x, 2);
    pushup(y, 1);
    pushup(x, 0);
  }
  // --8<-- [end:example168]

  while (father[x]) {
    splice(father[x]);
    x = father[x];
  }
  splay(ys, 0);  // global splay
}

// --8<-- [end:example169e]

int findroot(int x) {
  access(x);
  pushdown(x, 0);
  while (ls(x)) x = ls(x), pushdown(x, 0);
  splay(x, 0);
  return x;
}

// --8<-- [start:example170]
void makeroot(int x) {
  access(x);
  push_rev(x);
}

// --8<-- [end:example170]

// --8<-- [start:example171]
void expose(int x, int y) {
  makeroot(x);
  access(y);
}

// --8<-- [end:example171]

void link_vertices(int x, int y) {
  if (findroot(x) == findroot(y)) return;
  access(x);
  makeroot(y);
  setfather(y, x, 1);
  pushup(x, 0);
  pushup(y, 0);
}

void cut_vertices(int x, int y) {
  expose(x, y);
  if (ls(y) != x || rs(x)) return;
  father[x] = ls(y) = 0;
  pushup(y, 0);
}

map<pair<int, int>, int> edge_nodes;

// --8<-- [start:example172]
void Link(int x, int y, int z) {
  // z代表连接 x, y的边
  if (findroot(x) == findroot(y)) return;
  val[z] = 0;
  pushup(z, 0);
  link_vertices(x, z);
  link_vertices(z, y);
  edge_nodes[minmax(x, y)] = z;
}

// --8<-- [end:example172]
// --8<-- [start:example173]
void cut(int x, int y) {
  auto it = edge_nodes.find(minmax(x, y));
  if (it == edge_nodes.end()) return;
  int z = it->second;
  cut_vertices(x, z);
  cut_vertices(z, y);
  father[z] = 0;
  Clear(z);
  edge_nodes.erase(it);
}

// --8<-- [end:example173]
int main() {
  int n, m;
  cin >> n >> m;
  tot = n;
  for (int i = 1; i <= n; ++i) {
    cin >> val[i];
    pushup(i, 0);
  }
  while (m--) {
    int op, x, y;
    cin >> op >> x >> y;
    if (op == 0) {
      expose(x, y);
      cout << s[y][0] << "\n";
    } else if (op == 1) {
      if (findroot(x) != findroot(y)) Link(x, y, new_node());
    } else if (op == 2)
      cut(x, y);
    else {
      access(x);
      val[x] = y;
      pushup(x, 0);
    }
  }
}
