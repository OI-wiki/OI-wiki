#include <cstdint>
#include <iostream>
#include <iterator>
#include <map>
#include <set>
#include <utility>
using namespace std;

// Sample source: https://www.luogu.com.cn/problem/P1840
// Maintain black (1) and white (0) intervals.
int remaining;

// --8<-- [start:node]
struct Node_t {
  int l, r;
  mutable int v;

  Node_t(const int &il, const int &ir, const int &iv) : l(il), r(ir), v(iv) {}

  bool operator<(const Node_t &o) const { return l < o.l; }
};

// --8<-- [end:node]

set<Node_t> odt;

// --8<-- [start:split]
auto split(int x) {
  auto it = odt.lower_bound(Node_t(x, 0, 0));
  if (it != odt.end() && it->l == x) return it;
  --it;
  int l = it->l, r = it->r, v = it->v;
  odt.erase(it);
  odt.insert(Node_t(l, x - 1, v));
  return odt.insert(Node_t(x, r, v)).first;
}

// --8<-- [end:split]
// --8<-- [start:assign]
void assign(int l, int r, int v) {
  auto itr = split(r + 1), itl = split(l);
  odt.erase(itl, itr);
  odt.insert(Node_t(l, r, v));
}

// --8<-- [end:assign]
// --8<-- [start:perform]
void perform(int l, int r) {
  auto itr = split(r + 1), itl = split(l);
  for (; itl != itr; ++itl) {
    remaining -= (itl->r - itl->l + 1) * itl->v;
  }
}

// --8<-- [end:perform]

int main() {
  int n, m;
  if (!(cin >> n >> m)) return 0;
  remaining = n;
  odt.insert(Node_t(1, n + 1, 1));
  while (m--) {
    int l, r;
    cin >> l >> r;
    perform(l, r);
    assign(l, r, 0);
    cout << remaining << '\n';
  }
}
