#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

constexpr int _ = 100005;

// --8<-- [start:trie]
namespace trie {
constexpr int MAXH = 21;
int ch[_ * (MAXH + 1)][2], w[_ * (MAXH + 1)], xorv[_ * (MAXH + 1)];
int tot = 0;

int mknode() {
  ++tot;
  ch[tot][1] = ch[tot][0] = w[tot] = xorv[tot] = 0;
  return tot;
}

// --8<-- [start:maintain]
void maintain(int o) {
  w[o] = xorv[o] = 0;
  if (ch[o][0]) {
    w[o] += w[ch[o][0]];
    xorv[o] ^= xorv[ch[o][0]] << 1;
  }
  if (ch[o][1]) {
    w[o] += w[ch[o][1]];
    xorv[o] ^= (xorv[ch[o][1]] << 1) | (w[ch[o][1]] & 1);
  }
  // w[o] = w[o] & 1;
  // 只需知道奇偶性即可，不需要具体的值．当然这句话删掉也可以，因为上文就只利用了他的奇偶性．
}

// --8<-- [end:maintain]

void insert(int &o, int x, int dp) {
  if (!o) o = mknode();
  if (dp > MAXH) return (void)(w[o]++);
  insert(ch[o][x & 1], x >> 1, dp + 1);
  maintain(o);
}

void erase(int o, int x, int dp) {
  if (dp > MAXH) return (void)(w[o]--);
  erase(ch[o][x & 1], x >> 1, dp + 1);
  maintain(o);
}

// --8<-- [start:addall]
void addall(int o) {
  if (!o || (!ch[o][0] && !ch[o][1])) return;
  swap(ch[o][0], ch[o][1]);
  if (ch[o][0]) addall(ch[o][0]);
  maintain(o);
}

// --8<-- [end:addall]

// --8<-- [start:merge]
int merge(int a, int b) {
  if (!a) return b;  // 如果 a 没有这个位置上的结点，返回 b
  if (!b) return a;  // 如果 b 没有这个位置上的结点，返回 a
  /*
    如果 `a`, `b` 都存在，
    那就把 `b` 的信息合并到 `a` 上．
  */
  w[a] = w[a] + w[b];
  xorv[a] ^= xorv[b];
  /* 不要使用 maintain()，
    maintain() 是合并a的两个儿子的信息
    而这里需要 a b 两个节点进行信息合并
   */
  ch[a][0] = merge(ch[a][0], ch[b][0]);
  ch[a][1] = merge(ch[a][1], ch[b][1]);
  return a;
}

// --8<-- [end:merge]
}  // namespace trie

// --8<-- [end:trie]

// Article demonstrations: insert, erase, add one to every value, and merge.
int main() {
  int q, roots[2] = {};
  cin >> q;
  while (q--) {
    int op, root, value;
    cin >> op >> root;
    if (op == 1) {
      cin >> value;
      trie::insert(roots[root], value, 0);
    }
    if (op == 2) {
      cin >> value;
      trie::erase(roots[root], value, 0);
    }
    if (op == 3) trie::addall(roots[root]);
    if (op == 4) {
      roots[root] = trie::merge(roots[root], roots[1 - root]);
      roots[1 - root] = 0;
    }
    cout << trie::xorv[roots[root]] << '\n';
  }
}
