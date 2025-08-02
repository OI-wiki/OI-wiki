// --8<-- [start:full-text]
#include <iostream>
#include <queue>
#include <vector>
constexpr int N = 100010, M = 200, P = 998244353;
using ll = long long;
using namespace std;
int n, k, r, tot, ans[N], nxt[1 << 20][2], trans[M][2], isF[1 << 20];
int belong[1 << 20], cnt, sz[M], ac[M];
ll f[N][M], g[N][M];
vector<int> pre[1 << 20][2], Q[M], S[M], pre_trans[M][2];
bool vis[1 << 20], tag[1 << 20];
char a[N];

inline int lowbit(int x) { return x & -x; }

int dfs(int x) {
  if (vis[x]) return x;
  vis[x] = 1;
  nxt[x][0] = dfs(x - lowbit(x));
  pre[x - lowbit(x)][0].push_back(x);
  nxt[x][1] = dfs(x + lowbit((1 << k) - 1 - x));
  pre[x + lowbit((1 << k) - 1 - x)][1].push_back(x);
  return x;
}

// --8<-- [start:core]
void hopcroft() {
  queue<int> W;
  W.push(1);
  cnt = 2;
  for (int i = 0; i < tot; i++) {
    Q[belong[i] = isF[i] ? 1 : 2].push_back(i);
  }
  sz[1] = Q[1].size(), sz[2] = Q[2].size(), ac[1] = 1;
  while (!W.empty()) {
    int u = W.front();
    W.pop();
    for (int c = 0; c <= 1; c++) {
      vector<int> td;
      for (auto x : Q[u]) {
        for (auto y : pre[x][c]) {
          if (S[belong[y]].empty()) td.push_back(belong[y]);
          S[belong[y]].push_back(y);
          tag[y] = 1;
        }
      }
      for (auto i : td) {
        if (S[i].size() < sz[i]) {
          ac[++cnt] = ac[i];
          vector<int> tmp;
          if (S[i].size() * 2 <= sz[i]) {
            for (auto j : Q[i]) {
              if (tag[j])
                Q[belong[j] = cnt].push_back(j);
              else
                tmp.push_back(j);
            }
          } else {
            for (auto j : Q[i]) {
              if (tag[j])
                tmp.push_back(j);
              else
                Q[belong[j] = cnt].push_back(j);
            }
          }
          swap(Q[i], tmp);
          sz[i] = Q[i].size();
          sz[cnt] = Q[cnt].size();
          W.push(cnt);
        }
        for (auto j : S[i]) tag[j] = 0;
        S[i].clear();
      }
    }
  }

  for (int i = 0; i < tot; i++)
    for (int c = 0; c <= 1; c++) trans[belong[i]][c] = belong[nxt[i][c]];
  for (int i = 1; i <= cnt; i++)
    for (int c = 0; c <= 1; c++) pre_trans[trans[i][c]][c].push_back(i);
}

// --8<-- [end:core]
int main() {
  scanf("%d %d %d %s", &n, &k, &r, a + 1);
  dfs(0);
  for (int i = 0; i <= r; i++) isF[i] = 1;
  tot = 1 << k;

  hopcroft();

  f[0][belong[0]] = 1;
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= cnt; j++) {
      for (int c = 0; c <= 1; c++) {
        if (a[i] == '?' || (a[i] - '0' == c))
          (f[i][trans[j][c]] += f[i - 1][j]) %= P;
      }
    }
  for (int i = 1; i <= cnt; i++)
    if (ac[i]) g[n + 1][i]++;
  for (int i = n; i >= 1; i--)
    for (int j = 1; j <= cnt; j++) {
      for (int c = 0; c <= 1; c++) {
        if (a[i] == '?' || (a[i] - '0' == c))
          for (int k : pre_trans[j][c]) {
            (g[i][k] += g[i + 1][j]) %= P;
          }
      }
    }
  for (int i = 1; i <= n; i++)
    if (a[i] == '1')
      printf("0\n");
    else {
      ll ans = 0;
      for (int j = 1; j <= cnt; j++) {
        ans = (ans + f[i - 1][j] * g[i + 1][trans[j][0]]) % P;
      }
      printf("%lld\n", ans);
    }
  return 0;
}

// --8<-- [end:full-text]
