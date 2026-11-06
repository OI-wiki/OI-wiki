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

map<int, int> mp;

// --8<-- [start:split]
auto split(int pos) {
  auto it = prev(mp.upper_bound(pos));  // 找到左端点小于等于 x 的区间．
  return mp.insert(it, make_pair(pos, it->second));
  // 设立新的区间，并将上一个区间储存的值复制给本区间．
}

// --8<-- [end:split]
// --8<-- [start:assign]
void assign(int l, int r, int v) {  // 注意，这里的r是区间右端点+1
  split(l);
  split(r);
  auto it = mp.find(l);
  while (it->first != r) {
    it = mp.erase(it);
  }
  mp[l] = v;
}

// --8<-- [end:assign]
// --8<-- [start:perform]
void perform(int l, int r) {  // 注意，这里的r是区间右端点+1
  split(l);
  split(r);
  auto it = mp.find(l);
  while (it->first != r) {
    remaining -= (next(it)->first - it->first) * it->second;
    it = next(it);
  }
}

// --8<-- [end:perform]

int main() {
  int n, m;
  if (!(cin >> n >> m)) return 0;
  remaining = n;
  mp[1] = 1;
  mp[n + 1] = 0;
  while (m--) {
    int l, r;
    cin >> l >> r;
    perform(l, r + 1);
    assign(l, r + 1, 0);
    cout << remaining << '\n';
  }
}
