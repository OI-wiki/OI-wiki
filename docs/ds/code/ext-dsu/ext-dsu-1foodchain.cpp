#include <bits/stdc++.h>
using namespace std;
const int N = 5e4;
int n, m, fa[N * 3 + 5], sz[N * 3 + 5], ans;

int query(int x) { return fa[x] == x ? x : (fa[x] = query(fa[x])); }

void merge(int x, int y) {
  x = query(x);
  y = query(y);
  if (x == y) return;
  if (sz[x] < sz[y]) swap(x, y);
  sz[x] += sz[y];
  fa[y] = x;
}

int main() {
  int op, x, y;
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  cin >> n >> m;
  iota(fa + 1, fa + n * 3, 1);
  fill(sz + 1, sz + n * 3, 1);
  while(m--) {
    cin >> op >> x >> y;
    if(x > n || y > n)
		++ ans;
    else if(op == 1) {
      if(query(x) == query(y + n) || query(x) == query(y + (n << 1)))
	  	++ ans;
      else {
        merge(x, y);
        merge(x + n, y + n);
        merge(x + (n << 1), y + (n << 1));
      }
    }
    else {
      if(query(x) == query(y) || query(x) == query(y + n))
	  	++ ans;
      else {
        merge(x, y + (n << 1));
        merge(x + n, y);
        merge(x + (n << 1), y + n);
      }
    }
  }
  cout << ans;
}
