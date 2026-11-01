#include <algorithm>
#include <cstddef>
#include <iostream>
#include <numeric>
#include <vector>
using namespace std;

constexpr int N = 100005;
int lc[N], rc[N], v[N], dist[N], cnt;

// --8<-- [start:example131]
int merge(int x, int y) {
  if (!x || !y) return x + y;
  if (v[x] > v[y]) swap(x, y);
  int p = ++cnt;
  lc[p] = lc[x];
  v[p] = v[x];
  rc[p] = merge(rc[x], y);
  if (dist[lc[p]] < dist[rc[p]]) swap(lc[p], rc[p]);
  dist[p] = dist[rc[p]] + 1;
  return p;
}

// --8<-- [end:example131]
void print(int root) {
  bool first = true;
  while (root) {
    cout << (first ? "" : " ") << v[root];
    first = false;
    root = merge(lc[root], rc[root]);
  }
  cout << "\n";
}

int main() {
  int n, root = 0;
  cin >> n;
  dist[0] = -1;
  vector<int> versions(1, 0);
  for (int i = 0; i < n; ++i) {
    int x;
    cin >> x;
    int p = ++cnt;
    v[p] = x;
    root = merge(root, p);
    versions.push_back(root);
  }
  for (int x : versions) print(x);
}
