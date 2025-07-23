// --8<-- [start:full-text]
#include <iostream>
#include <queue>
#include <vector>
#define N 100010
#define M 200
#define int long long
#define P 998244353
using namespace std;
int n, k, r, ans[N], nxt[1 << 20][2], trans[M][2], isF[1 << 20];
int belong[1 << 20], cnt, sz[M], ac[M], f[N][M], g[N][M];
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
  const auto rebuild = [&](int u) {
    vector<int> tmp;
    for (auto i : Q[u])
      if (belong[i] == u) tmp.push_back(i);
    swap(Q[u], tmp);
  };
  queue<int> que;
  que.push(1);
  cnt = 2;
  for (int i = 0; i < (1 << k); i++) {
    Q[belong[i] = isF[i] ? 1 : 2].push_back(i);
  }
  sz[1] = Q[1].size(), sz[2] = Q[2].size(), ac[1] = 1;
  while (!que.empty()) {
    int u = que.front();
    que.pop();
    rebuild(u);
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
          if (S[i].size() * 2 <= sz[i]) {
            // 为了复杂度正确，这里没有从 Q[i] 中删除 S[i]，而是改变它们的
            // belong 注意实现时，如果需要取用 Q 中的内容，必须先 rebuild
            // 以及注意 sz 中的值是真正的等价类的大小，sz[i] 不一定等于
            // Q[i].size()
            for (auto j : S[i]) Q[belong[j] = cnt].push_back(j);
            sz[cnt] = S[i].size();
            sz[i] -= S[i].size();
          } else {
            rebuild(i);
            vector<int> tmp;
            for (auto j : Q[i]) {
              if (tag[j])
                tmp.push_back(j);
              else
                Q[belong[j] = cnt].push_back(j);
            }
            swap(Q[i], tmp);
            sz[i] = Q[i].size();
            sz[cnt] = Q[cnt].size();
          }
          que.push(cnt);
        }
        for (auto j : S[i]) tag[j] = 0;
        S[i].clear();
      }
    }
  }

  for (int i = 0; i < (1 << k); i++)
    for (int c = 0; c <= 1; c++) trans[belong[i]][c] = belong[nxt[i][c]];
  for (int i = 1; i <= cnt; i++)
    for (int c = 0; c <= 1; c++) pre_trans[trans[i][c]][c].push_back(i);
}

// --8<-- [end:core]
signed main() {
  scanf("%lld %lld %lld %s", &n, &k, &r, a + 1);
  dfs(0);
  for (int i = 0; i <= r; i++) isF[i] = 1;

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
      int ans = 0;
      for (int j = 1; j <= cnt; j++) {
        ans = (ans + f[i - 1][j] * g[i + 1][trans[j][0]]) % P;
      }
      printf("%lld\n", ans);
    }
}

// --8<-- [end:full-text]