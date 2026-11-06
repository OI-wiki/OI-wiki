#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

const int kD[8][2] = {{-2, -1}, {-1, -2}, {1, -2}, {2, -1},
                      {2, 1},   {1, 2},   {-1, 2}, {-2, 1}};

int n, m, ib;
int vis[200020], dis[200020], t[200020], r[200020], ans, u, v, cnta,
    x[220][220], cl[220][220], idx, bel[220][220];
vector<int> to[200020];
queue<int> q;

int DFS(int x) {
  if (vis[x]) {
    return false;
  }
  vis[x] = true;
  for (auto i : to[x]) {
    if (!r[i]) {
      r[i] = x;
      t[x] = i;
      return true;
    }
    if (dis[r[i]] == dis[x] + 1 && DFS(r[i])) {
      r[i] = x;
      t[x] = i;
      return true;
    }
  }
  return false;
}

int BFS() {
  fill(vis + 1, vis + cnta + 1, false);
  fill(dis + 1, dis + cnta + 1, 0);
  for (int i = 1; i <= cnta; i++) {
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

void din() {
  for (; BFS();) {
    for (int i = 1; i <= cnta; i++) {
      if (!t[i] && DFS(i)) {
        ans++;
      }
    }
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr), cout.tie(nullptr);
  cin >> n >> m;
  for (int i = 1; i <= m; i++) {
    cin >> u >> v;
    x[u][v] = true;
  }
  cl[1][1] = 1;
  if (!x[1][1]) {
    bel[1][1] = ++idx;
  }
  for (int i = 2; i <= n; i++) {
    cl[1][i] = cl[1][i - 1] ^ 1;
    if (!x[1][i] && cl[1][i]) {
      bel[1][i] = ++idx;
    } else {
      if (!x[1][i]) {
        bel[1][i] = ++ib;
      }
    }
  }
  for (int i = 2; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      cl[i][j] = cl[i - 1][j] ^ 1;
      if (!x[i][j] && cl[i][j]) {
        bel[i][j] = ++idx;
      } else {
        if (!x[i][j]) {
          bel[i][j] = ++ib;
        }
      }
    }
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      if (!x[i][j]) {
        cnta += cl[i][j];
        for (int k = 0; k < 8; k++) {
          if (i + kD[k][0] > 0 && j + kD[k][1] > 0 &&
              bel[i + kD[k][0]][j + kD[k][1]] &&
              !x[i + kD[k][0]][j + kD[k][1]]) {
            if (cl[i + kD[k][0]][j + kD[k][1]]) {
              to[bel[i + kD[k][0]][j + kD[k][1]]].push_back(bel[i][j]);
            } else {
              to[bel[i][j]].push_back(bel[i + kD[k][0]][j + kD[k][1]]);
            }
          }
        }
      }
    }
  }
  din();
  cout << n * n - m - ans << '\n';
  return 0;
}
