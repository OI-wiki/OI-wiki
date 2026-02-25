#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int ct, n, t[100010], x, r[100010], ans, vis[100010], dis[100010];
vector<int> to[100010];
queue<int> q;

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

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr), cout.tie(nullptr);
  for (cin >> ct; ct--;) {
    cin >> n;
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= n; j++) {
        cin >> x;
        if (x) {
          to[i].push_back(j);
        }
      }
    }
    for (; BFS();) {
      for (int i = 1; i <= n; i++) {
        if (!t[i] && DFS(i)) {
          ans++;
        }
      }
    }
    cout << (ans == n ? "Yes" : "No") << '\n';
    for (int i = 1; i <= n; i++) {
      t[i] = r[i] = 0;
      to[i].clear();
    }
    ans = 0;
  }
  return 0;
}
