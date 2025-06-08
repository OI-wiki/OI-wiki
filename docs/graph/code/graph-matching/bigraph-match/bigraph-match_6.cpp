#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

struct node {
  int u, v;
} arr[5050];

int n, m, t[5050], r[5050], d, ot[5050], kil[5050], vis[5050], ans, out[5050];
vector<int> to[5050];

int DFS(int x) {
  if (vis[x]) {
    return 0;
  }
  vis[x] = 1;
  for (auto i : to[x]) {
    if (r[i] == -1) {
      r[i] = x;
      t[x] = i;
      return 1;
    }
    if (DFS(r[i])) {
      r[i] = x;
      t[x] = i;
      return 1;
    }
  }
  return 0;
}

int main() {
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    cin >> arr[i].u;
    if (arr[i].u > m) {
      arr[i].u = m + 1;
    }
  }
  for (int i = 1; i <= n; i++) {
    cin >> arr[i].v;
  }
  cin >> d;
  for (int i = 1; i <= d; i++) {
    cin >> ot[i];
    kil[ot[i]] = 1;
  }
  for (int i = 1; i <= n; i++) {
    if (!kil[i]) {
      to[arr[i].u].push_back(arr[i].v);
    }
  }
  fill(r + 1, r + m + 1, -1);
  for (; ans <= m;) {
    fill(vis, vis + m + 2, 0);
    if (DFS(ans)) {
      ans++;
    } else {
      break;
    }
  }
  out[d] = ans;
  for (int i = d; i > 1; i--) {
    to[arr[ot[i]].u].push_back(arr[ot[i]].v);
    for (; ans <= m;) {
      fill(vis, vis + m + 2, 0);
      if (DFS(ans)) {
        ans++;
      } else {
        break;
      }
    }
    out[i - 1] = ans;
  }
  for (int i = 1; i <= d; i++) {
    cout << out[i] << '\n';
  }
  return 0;
}
