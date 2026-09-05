#include <iostream>
#include <vector>

// --8<-- [start:core]
int n;
std::vector<int> diff, a;

// Add v to each element in [l, r].
void add(int l, int r, int v) {
  diff[l] += v;
  if (r < n) diff[r + 1] -= v;
}

// Execute this after all modifications and before all queries.
void prefix_sum() {
  for (int i = 1; i <= n; ++i) a[i] = a[i - 1] + diff[i];
}

// --8<-- [end:core]
int main() {
  std::cin >> n;
  diff.resize(n + 1);
  a.resize(n + 1);
  int t;
  std::cin >> t;
  for (; t; --t) {
    int l, r, v;
    std::cin >> l >> r >> v;
    add(l, r, v);
  }
  prefix_sum();
  for (int i = 1; i <= n; ++i) {
    std::cout << a[i] << '\n';
  }
  return 0;
}
