#include <algorithm>
#include <iostream>
#include <string>
using namespace std;
constexpr int N = 100005, std_tag = 0;
int ch[N][2], f[N], siz[N], tag[N];
#define ls ch[p][0]
#define rs ch[p][1]
// --8<-- [start:example78]
// 在前面我们已经说过，LCT 具有 如果一个儿子不是实儿子，他的父亲找不到它的性质
// 所以当一个点既不是它父亲的左儿子，又不是它父亲的右儿子，它就是当前 Splay 的根
#define isRoot(x) (ch[f[x]][0] != x && ch[f[x]][1] != x)

// --8<-- [end:example78]
// --8<-- [start:example75]
void PushUp(int p) {
  // maintain other variables
  siz[p] = siz[ls] + siz[rs] + 1;
}

// --8<-- [end:example75]
// --8<-- [start:example76]
void PushDown(int p) {
  if (tag[p] != std_tag) {
    if (ls) {
      swap(ch[ls][0], ch[ls][1]);
      tag[ls] ^= 1;
    }
    if (rs) {
      swap(ch[rs][0], ch[rs][1]);
      tag[rs] ^= 1;
    }
    tag[p] = std_tag;
  }
}

// --8<-- [end:example76]
// --8<-- [start:example81]
// 从上到下一层一层 pushDown 即可
void Update(int p) {
  if (!isRoot(p)) Update(f[p]);
  PushDown(p);
}

// --8<-- [end:example81]
// --8<-- [start:example77]
#define Get(x) (ch[f[x]][1] == x)

void Rotate(int x) {
  int y = f[x], z = f[y], k = Get(x);
  if (!isRoot(y)) ch[z][ch[z][1] == y] = x;
  // 上面这句一定要写在前面，普通的 Splay 是不用的，因为 isRoot  (后面会讲)
  ch[y][k] = ch[x][!k], f[ch[x][!k]] = y;
  ch[x][!k] = y, f[y] = x, f[x] = z;
  PushUp(y), PushUp(x);
}

void Splay(int x) {
  Update(
      x);  // 马上就能看到啦．在 Splay 之前要把旋转会经过的路径上的点都 PushDown
  for (int fa; fa = f[x], !isRoot(x); Rotate(x)) {
    if (!isRoot(fa)) Rotate(Get(fa) == Get(x) ? fa : x);
  }
}

// --8<-- [end:example77]
// --8<-- [start:example79]
// 回顾一下代码
int Access(int x) {
  int p;
  for (p = 0; x; p = x, x = f[x]) {
    Splay(x), ch[x][1] = p, PushUp(x);
  }
  return p;
}

// --8<-- [end:example79]
// --8<-- [start:example82]
void makeRoot(int p) {
  p = Access(p);
  swap(ch[p][0], ch[p][1]);
  tag[p] ^= 1;
}

// --8<-- [end:example82]
// --8<-- [start:example83]
void Link(int x, int p) {
  makeRoot(x);
  Splay(x);
  f[x] = p;
}

// --8<-- [end:example83]
// --8<-- [start:example84]
void Cut(int x, int p) { makeRoot(x), Access(p), Splay(p), ls = f[x] = 0; }

// --8<-- [end:example84]
// --8<-- [start:example85]
int Find(int p) {
  Access(p);
  Splay(p);
  PushDown(p);
  while (ls) p = ls, PushDown(p);
  Splay(p);
  return p;
}

// --8<-- [end:example85]
int main() {
  int n, q;
  cin >> n >> q;
  for (int i = 1; i <= n; ++i) siz[i] = 1;
  while (q--) {
    string op;
    int x, y;
    cin >> op >> x >> y;
    if (op[0] == 'C') {
      if (Find(x) != Find(y)) Link(x, y);
    } else if (op[0] == 'D')
      Cut(x, y);
    else
      cout << (Find(x) == Find(y) ? "Yes" : "No") << "\n";
  }
}
