#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <vector>

using namespace std;

constexpr int MAXN = 100010;
constexpr int INF = numeric_limits<int>::max();

// --8<-- [start:sort]
int n, a[MAXN], tmp[MAXN << 1];

int winner(int pos1, int pos2) {
  int u = pos1 >= n ? pos1 : tmp[pos1];
  int v = pos2 >= n ? pos2 : tmp[pos2];
  if (tmp[u] <= tmp[v]) return u;
  return v;
}

void create_tree(int& value) {
  for (int i = 0; i < n; i++) tmp[n + i] = a[i];
  for (int i = 2 * n - 1; i > 1; i -= 2) {
    int k = i / 2;
    int j = i - 1;
    tmp[k] = winner(i, j);
  }
  value = tmp[tmp[1]];
  tmp[tmp[1]] = INF;
}

void recreate(int& value) {
  int i = tmp[1];
  while (i > 1) {
    int j, k = i / 2;
    if (i % 2 == 0)
      j = i + 1;
    else
      j = i - 1;
    tmp[k] = winner(i, j);
    i = k;
  }
  value = tmp[tmp[1]];
  tmp[tmp[1]] = INF;
}

void tournament_sort() {
  if (n <= 1) return;
  int value;
  create_tree(value);
  for (int i = 0; i < n; i++) {
    a[i] = value;
    recreate(value);
  }
}

// --8<-- [end:sort]

int main() {
  if (!(cin >> n) || n < 0 || n > MAXN) return 0;
  for (int i = 0; i < n; ++i) cin >> a[i];
  tournament_sort();
  for (int i = 0; i < n; ++i) cout << a[i] << ' ';
  cout << '\n';
}
