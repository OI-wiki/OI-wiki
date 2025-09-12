#include <iostream>
#include <queue>
using namespace std;
const int N = 210;
int n, a, b, k[N], d[N];

int main() {
  cin >> n >> a >> b;
  for (int i = 1; i <= n; ++i) cin >> k[i];
  queue<int> q;
  q.push(a);
  while (!q.empty()) {
    int x = q.front();
    q.pop();
    if (x == b) {
      cout << d[x] << endl;
      return 0;
    }
    int y = x + k[x];
    if (y <= n) {
      d[y] = d[x] + 1;
      q.push(y);
    }
    y = x - k[x];
    if (y >= 1) {
      d[y] = d[x] + 1;
      q.push(y);
    }
  }
  cout << -1 << endl;
  return 0;
}
