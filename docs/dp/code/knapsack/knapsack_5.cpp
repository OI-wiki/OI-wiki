#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

struct Item {
  int w, v;
};

int main() {
  int m, W, index;
  cin >> m >> W;
  vector<Item> list(100001);
  // --8<-- [start:core]
  index = 0;
  for (int i = 1; i <= m; i++) {
    int c = 1, p, h, k;
    cin >> h >> p >> k;
    while (k > c) {
      k -= c;
      list[++index].w = c * p;
      list[index].v = c * h;
      c *= 2;
    }
    list[++index].w = p * k;
    list[index].v = h * k;
  }
  // --8<-- [end:core]
  vector<int> f(W + 1);
  for (int i = 1; i <= index; ++i)
    for (int weight = W; weight >= list[i].w; --weight)
      f[weight] = max(f[weight], f[weight - list[i].w] + list[i].v);
  cout << f[W] << '\n';
}
