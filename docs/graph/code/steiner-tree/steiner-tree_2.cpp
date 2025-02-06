#include <cstring>
#include <iostream>
#include <queue>

using namespace std;

#define mp make_pair
using P = pair<int, int>;
using PP = pair<P, int>;
constexpr int INF = 0x3f3f3f3f;
constexpr int dx[] = {0, 0, -1, 1};
constexpr int dy[] = {1, -1, 0, 0};
int n, m, K, root;
int f[101][1111], a[101], ans[11][11];
bool inq[101];
PP pre[101][1111];
queue<P> q;

bool legal(P u) {
  if (u.first >= 0 && u.second >= 0 && u.first < n && u.second < m) {
    return true;
  }
  return false;
}

int num(P u) { return u.first * m + u.second; }

void spfa(int s) {
  memset(inq, 0, sizeof(inq));
  while (!q.empty()) {
    P u = q.front();
    q.pop();
    inq[num(u)] = false;
    for (int d = 0; d < 4; d++) {
      P v = mp(u.first + dx[d], u.second + dy[d]);
      int du = num(u), dv = num(v);
      if (legal(v) && f[dv][s] > f[du][s] + a[dv]) {
        f[dv][s] = f[du][s] + a[dv];
        if (!inq[dv]) {
          inq[dv] = true;
          q.push(v);
        }
        pre[dv][s] = mp(u, s);
      }
    }
  }
}

void dfs(P u, int s) {
  if (!pre[num(u)][s].second) return;
  ans[u.first][u.second] = 1;
  int nu = num(u);
  if (pre[nu][s].first == u)
    dfs(u, s ^ pre[nu][s].second);  // 通过 dfs 来找到答案
  dfs(pre[nu][s].first, pre[nu][s].second);
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  memset(f, INF, sizeof(f));
  cin >> n >> m;
  int tot = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      cin >> a[tot];
      if (!a[tot]) {
        f[tot][1 << (K++)] = 0;
        root = tot;
      }
      tot++;
    }
  }
  for (int s = 1; s < (1 << K); s++) {
    for (int i = 0; i < n * m; i++) {
      for (int subs = s & (s - 1); subs; subs = s & (subs - 1)) {
        if (f[i][s] > f[i][subs] + f[i][s ^ subs] - a[i]) {
          f[i][s] = f[i][subs] + f[i][s ^ subs] - a[i];  // 状态转移
          pre[i][s] = mp(mp(i / m, i % m), subs);
        }
      }
      if (f[i][s] < INF) q.push(mp(i / m, i % m));
    }
    spfa(s);
  }
  cout << f[root][(1 << K) - 1] << '\n';
  dfs(mp(root / m, root % m), (1 << K) - 1);
  for (int i = 0, tot = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (!a[tot++])
        cout << 'x';
      else
        cout << (ans[i][j] ? 'o' : '_');
    }
    if (i != n - 1) cout << '\n';
  }
  return 0;
}