#include <algorithm>
#include <cmath>
#include <iostream>
#include <limits>
#include <vector>
using namespace std;
constexpr int MAXN = 1000005;
int n;

int lowbit(int x) { return x & -x; }

// --8<-- [start:example61]
// 时间戳优化
int tag[MAXN], t[MAXN], Tag;

void reset() { ++Tag; }

void add(int k, int v) {
  while (k <= n) {
    if (tag[k] != Tag) t[k] = 0;
    t[k] += v, tag[k] = Tag;
    k += lowbit(k);
  }
}

int getsum(int k) {
  int ret = 0;
  while (k) {
    if (tag[k] == Tag) ret += t[k];
    k -= lowbit(k);
  }
  return ret;
}

// --8<-- [end:example61]

int main() {
  int q;
  cin >> n >> q;
  while (q--) {
    int op, x, v;
    cin >> op;
    if (op == 0)
      reset();
    else if (op == 1) {
      cin >> x >> v;
      add(x, v);
    } else {
      cin >> x;
      cout << getsum(x) << '\n';
    }
  }
}
