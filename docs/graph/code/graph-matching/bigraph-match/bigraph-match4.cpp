#include <bits/stdc++.h>
using namespace std;

int n, m, belr[220][220], beld[220][220], dcnt, rcnt, vis[100010], dis[100010], t[100010], r[100010], cnt;
char c[220][220];
vector<int> to[100010];
queue<int> q;

int DFS(int x) {
  //cout << x << '\n';
  if(vis[x]) {
    return 0;
  }
  vis[x] = 1;
  for(auto i : to[x]) {
    //cout << x << ' ' << i << '\n';
    if(!r[i]) {
      r[i] = x;
      t[x] = i;
      return 1;
    }
    if(dis[r[i]] == dis[x] + 1 && DFS(r[i])) {
      r[i] = x;
      t[x] = i;
      return 1;
    }
  }
  return 0;
}

int BFS() {
  fill(vis + 1, vis + rcnt + 1, 0);
  fill(dis + 1, dis + rcnt + 1, 0);
  for(int i = 1; i <= rcnt; i++) {
    if(!t[i]) {
      q.push(i);
      dis[i] = 1;
    }
  }
  int f = 0;
  for(; q.size(); q.pop()) {
    int tmp = q.front();
    for(auto i : to[tmp]) {
      if(!r[i]) {
        f = 1;
      }
      if(r[i]) {
        if(!dis[r[i]]) {
          dis[r[i]] = dis[tmp] + 1;
          q.push(r[i]);
        }
      }
    }
  }
  return f;
}

int solve() {
  int rt = 0;
  for(; BFS(); ) {
    for(int i = 1; i <= rcnt; i++) {
      if(!t[i] && DFS(i)) {
        rt++;
      }
      //cout << '\n';
    }
  }
  return rt;
}

int main() {
  cin >> n >> m;
  for(int i = 1; i <= n; i++) {
    for(int j = 1; j <= m; j++) {
      cin >> c[i][j];
    }
  }
  for(int i = 1; i <= n; i++) {
    for(int j = 1; j <= m; j++) {
      if(c[i][j] == '#') {
        cnt++;
        if(c[i + 1][j] == '#') {
          beld[i][j] = ++dcnt;
        }
        if(c[i][j + 1] == '#') {
          belr[i][j] = ++rcnt;
        }
      }
    }
  }
  for(int i = 1; i <= n; i++) {
    for(int j = 1; j <= m; j++) {
      if(c[i][j] == '#') {
        if(c[i - 1][j] == '#' && c[i][j - 1] == '#') {
          to[belr[i][j - 1]].push_back(beld[i - 1][j]);
        }
        if(c[i + 1][j] == '#' && c[i][j + 1] == '#') {
          to[belr[i][j]].push_back(beld[i][j]);
        }
        if(c[i + 1][j] == '#' && c[i][j - 1] == '#') {
          to[belr[i][j - 1]].push_back(beld[i][j]);
        }
        if(c[i - 1][j] == '#' && c[i][j + 1] == '#') {
          to[belr[i][j]].push_back(beld[i - 1][j]);
        }
      }
    }
  }
  /*
  for(int i = 1; i <= rcnt; i++) {
    cout << i << ": ";
    for(auto j : to[i]) {
      cout << j << ' ';
    }
    cout << '\n';
  }
  */
  //cout << rcnt << ' ' << dcnt << '\n';
  cout << cnt - rcnt - dcnt + solve() << '\n';
  /*
  for(int i = 1; i <= rcnt; i++) {
    cout << t[i] << ' ';
  }
  cout << '\n';
  */
  return 0;
}