#include <iostream>
#include <queue>
using namespace std;
const int N = 210;
int n, a, b, k[N], d[N];

int main() {
  cin >> n >> a >> b;
  for (int i = 1; i <= n; ++i) cin >> k[i];
  for (int i = 1; i <= n; ++i) d[i] = -1;
  queue<int> q;
  d[a] = 0;
  q.push(a);
  while (!q.empty()) {
    int x = q.front();
    q.pop();
    if (x == b) {
      break;
    }
    int y = x + k[x];
    if (y <= n && d[y] == -1) {
      d[y] = d[x] + 1;
      q.push(y);
    }
    y = x - k[x];
    if (y >= 1 && d[y] == -1) {
      d[y] = d[x] + 1;
      q.push(y);
    }
  }
  cout << d[b] << endl;
  return 0;
}
