#include <algorithm>
#include <iostream>
#include <map>
#include <queue>
#include <utility>
#include <vector>
using namespace std;

int n, k, u, v, t[200020], r[200020], ans, vis[200020], dis[200020], c;
map<pair<int, int>, int> mp;
vector<int> to[200020];
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
  ios::sync_with_stdio(false);
  cin.tie(nullptr), cout.tie(nullptr);
  cin >> n >> k;
  for (int i = 1; i <= k; i++) {
    cin >> u >> v;
    if (mp.find({u, v}) == mp.end()) {
      mp[{u, v}] = mp[{v, u}] = ++c;
    }
    to[v].push_back({mp[{u, v}]});
  }
  mxf();
  cout << (ans == n ? "YES" : "NO") << '\n';
  ans = 0;
  return 0;
}
