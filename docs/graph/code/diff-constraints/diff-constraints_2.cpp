// Sample source: https://www.luogu.com.cn/problem/P1993
#include <iostream>
#include <vector>
using namespace std;
int n;
vector<int> h, nxt, p, w;
vector<long long> dist;

void add(int target, int source, int weight) {
  nxt.push_back(h[target]);
  p.push_back(source);
  w.push_back(weight);
  h[target] = static_cast<int>(p.size()) - 1;
}

// --8<-- [start:core]
bool Bellman_Ford() {
  for (int i = 0; i < n; i++) {
    bool jud = false;
    for (int j = 1; j <= n; j++)
      for (int k = h[j]; ~k; k = nxt[k])
        if (dist[j] > dist[p[k]] + w[k])
          dist[j] = dist[p[k]] + w[k], jud = true;
    if (!jud) break;
  }
  for (int i = 1; i <= n; i++)
    for (int j = h[i]; ~j; j = nxt[j])
      if (dist[i] > dist[p[j]] + w[j]) return false;
  return true;
}

// --8<-- [end:core]

int main() {
  int m;
  cin >> n >> m;
  h.assign(n + 1, -1);
  dist.resize(n + 1);
  while (m--) {
    int type, a, b, c;
    cin >> type >> a >> b;
    if (type == 1) {
      cin >> c;
      add(b, a, -c);
    } else if (type == 2) {
      cin >> c;
      add(a, b, c);
    } else {
      add(a, b, 0);
      add(b, a, 0);
    }
  }
  cout << (Bellman_Ford() ? "Yes" : "No") << '\n';
}
