#include <algorithm>
#include <array>
#include <deque>
#include <iostream>
#include <tuple>
#include <vector>
using std::array;
using std::cin;
using std::cout;
using std::deque;
using std::sort;
using std::tie;
using std::vector;

struct Point {
  int x, y, z;
};

vector<Point> sec;
int p, ou_tot, tot;
deque<array<int, 2>> ou_ch(1), ch(1);
deque<int> ou_root(1), data(1);
int vec_query(int, int, int, int, int);
void vec_insert(int &, int, int, int);

// --8<-- [start:example148]
int tree_query(int k, int l, int r, int x) {
  if (k == 0) return 0;
  if (1 <= l && r <= sec[x].y) return vec_query(ou_root[k], 1, p, 1, sec[x].z);
  int mid = l + r >> 1, res = 0;
  if (1 <= mid) res += tree_query(ou_ch[k][0], l, mid, x);
  if (sec[x].y > mid) res += tree_query(ou_ch[k][1], mid + 1, r, x);
  return res;
}

// --8<-- [end:example148]
// --8<-- [start:example149]
void tree_insert(int &k, int l, int r, int x) {
  if (k == 0) {
    k = ++ou_tot;
    ou_ch.push_back({0, 0});
    ou_root.push_back(0);
  }
  vec_insert(ou_root[k], 1, p, sec[x].z);
  if (l == r) return;
  int mid = l + r >> 1;
  if (sec[x].y <= mid)
    tree_insert(ou_ch[k][0], l, mid, x);
  else
    tree_insert(ou_ch[k][1], mid + 1, r, x);
}

// --8<-- [end:example149]
// --8<-- [start:example150]
int vec_query(int k, int l, int r, int x, int y) {
  if (k == 0) return 0;
  if (x <= l && r <= y) return data[k];
  int mid = l + r >> 1, res = 0;
  if (x <= mid) res += vec_query(ch[k][0], l, mid, x, y);
  if (y > mid) res += vec_query(ch[k][1], mid + 1, r, x, y);
  return res;
}

// --8<-- [end:example150]
// --8<-- [start:example151]
void vec_insert(int &k, int l, int r, int loc) {
  if (k == 0) {
    k = ++tot;
    ch.push_back({0, 0});
    data.push_back(0);
  }
  data[k]++;
  if (l == r) return;
  int mid = l + r >> 1;
  if (loc <= mid) vec_insert(ch[k][0], l, mid, loc);
  if (loc > mid) vec_insert(ch[k][1], mid + 1, r, loc);
}

// --8<-- [end:example151]
int main() {
  int n, root = 0;
  cin >> n >> p;
  sec.resize(n);
  for (auto &v : sec) cin >> v.x >> v.y >> v.z;
  sort(sec.begin(), sec.end(), [](Point a, Point b) {
    return tie(a.x, a.y, a.z) < tie(b.x, b.y, b.z);
  });
  vector<int> ans(n);
  for (int i = 0; i < n;) {
    int j = i + 1;
    while (j < n && tie(sec[j].x, sec[j].y, sec[j].z) ==
                        tie(sec[i].x, sec[i].y, sec[i].z))
      ++j;
    for (int k = i; k < j; ++k) tree_insert(root, 1, p, k);
    ans[tree_query(root, 1, p, i) - 1] += j - i;
    i = j;
  }
  for (int x : ans) cout << x << "\n";
}
