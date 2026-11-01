#include <algorithm>
#include <cstddef>
#include <iostream>
#include <numeric>
#include <vector>
using namespace std;

int n, i, t;
vector<int> h;

// --8<-- [start:example4]
void up(int x) {
  while (x > 1 && h[x] > h[x / 2]) {
    std::swap(h[x], h[x / 2]);
    x /= 2;
  }
}

void down(int x) {
  while (x * 2 <= n) {
    t = x * 2;
    if (t + 1 <= n && h[t + 1] > h[t]) t++;
    if (h[t] <= h[x]) break;
    std::swap(h[x], h[t]);
    x = t;
  }
}

// --8<-- [end:example4]
// --8<-- [start:example5]
void build_heap_1() {
  for (i = 1; i <= n; i++) up(i);
}

// --8<-- [end:example5]
// --8<-- [start:example6]
void build_heap_2() {
  for (i = n; i >= 1; i--) down(i);
}

// --8<-- [end:example6]

int main() {
  cin >> n;
  h.resize(n + 1);
  for (int j = 1; j <= n; ++j) cin >> h[j];
  const vector<int> initial = h;
  for (int method = 0; method < 2; ++method) {
    h = initial;
    n = static_cast<int>(h.size()) - 1;
    if (method == 0)
      build_heap_1();
    else
      build_heap_2();
    bool first = true;
    while (n) {
      cout << (first ? "" : " ") << h[1];
      first = false;
      h[1] = h[n--];
      down(1);
    }
    cout << '\n';
  }
}
