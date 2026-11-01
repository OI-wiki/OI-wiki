#include <cstdlib>
#include <iostream>
using namespace std;

// --8<-- [start:core]
struct Node {
  int child[2];
  long long val;
} nd[100010];

int root[100010];

int merge(int u, int v) {
  if (!(u && v)) return u | v;
  int x = rand() & 1, p = nd[u].val > nd[v].val ? u : v;
  nd[p].child[x] = merge(nd[p].child[x], u + v - p);
  return p;
}

void pop(int &now) { now = merge(nd[now].child[0], nd[now].child[1]); }

// --8<-- [end:core]

int main() {
  int n;
  if (!(cin >> n)) return 0;
  srand(1);
  int heap = 0;
  for (int i = 1; i <= n; ++i) {
    cin >> nd[i].val;
    heap = merge(heap, i);
  }
  bool first = true;
  while (heap) {
    if (!first) cout << ' ';
    first = false;
    cout << nd[heap].val;
    pop(heap);
  }
  cout << '\n';
}
