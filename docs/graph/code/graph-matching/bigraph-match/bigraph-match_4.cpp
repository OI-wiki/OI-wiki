#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int n, m, vis[220], dis[220], t[220], r[220], ans, u, v;
vector<int> to[220];
queue<int> q;

// There was a delta here...
int DFS(int x) {
  if (vis[x]) {
    return 0;
  }
  vis[x] = 1;
  for (auto i : to[x]) {
    if (!r[i]) {
      r[i] = x;
      t[x] = i;
      return 1;
    }
    if (dis[r[i]] == dis[x] + 1 && DFS(r[i])) {
      r[i] = x;
      t[x] = i;
      return 1;
    }
  }
  return 0;
}

int BFS() {
  fill(vis + 1, vis + n + 1, 0);
  fill(dis + 1, dis + n + 1, 0);
  for (int i = 1; i <= n; i++) {
    if (!t[i]) {
      q.push(i);
      dis[i] = 1;
    }
  }
  int f = 0;
  for (; q.size(); q.pop()) {
    int tmp = q.front();
    for (auto i : to[tmp]) {
      if (!r[i]) {
        f = 1;
      }
      if (r[i]) {
        if (!dis[r[i]]) {
          dis[r[i]] = dis[tmp] + 1;
          q.push(r[i]);
        }
      }
    }
  }
  return f;
}

void mxf() {
  for (; BFS();) {
    for (int i = 1; i <= n; i++) {
      if (!t[i] && DFS(i)) {
        ans++;
      }
    }
  }
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);
  cin >> n >> m;
  for (int i = 1; i <= m; i++) {
    cin >> u >> v;
    to[v].push_back(u);
  }
  mxf();
  for (int i = 1; i <= n; i++) {
    if (!t[i]) {
      cout << i << ' ';
      for (int j = r[i]; j; j = r[j]) {
        cout << j << ' ';
      }
      cout << '\n';
    }
  }
  cout << n - ans << '\n';
  return 0;
}
