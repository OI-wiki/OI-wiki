#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;
using ll = long long;
constexpr int N = 1505;
constexpr int mod = 1000000007;
int n, m;
char s[N], c[N];
int ch[N][10], fail[N], ed[N], tot, len;

void insert() {
  int now = 0;
  int L = strlen(s);
  for (int i = 0; i < L; ++i) {
    if (!ch[now][s[i] - '0']) ch[now][s[i] - '0'] = ++tot;
    now = ch[now][s[i] - '0'];
  }
  ed[now] = 1;
}

queue<int> q;

void build() {
  for (int i = 0; i < 10; ++i)
    if (ch[0][i]) q.push(ch[0][i]);
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    for (int i = 0; i < 10; ++i) {
      if (ch[u][i]) {
        fail[ch[u][i]] = ch[fail[u]][i], q.push(ch[u][i]),
        ed[ch[u][i]] |= ed[fail[ch[u][i]]];
      } else
        ch[u][i] = ch[fail[u]][i];
    }
  }
}

// 最后一维表示是否已经填入非前导零，避免把前导零送入自动机．
ll f[N][N][2][2], ans;

void add(ll &x, ll y) { x = (x + y) % mod; }

int main() {
  scanf("%s", c);
  n = strlen(c);
  scanf("%d", &m);
  for (int i = 1; i <= m; ++i) scanf("%s", s), insert();
  build();
  f[0][0][1][0] = 1;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j <= tot; ++j) {
      if (ed[j]) continue;
      for (int tight = 0; tight < 2; ++tight) {
        for (int started = 0; started < 2; ++started) {
          int upper = tight ? c[i] - '0' : 9;
          for (int k = 0; k <= upper; ++k) {
            int next_started = started || k != 0;
            int next = next_started ? ch[j][k] : 0;
            if (ed[next]) continue;
            add(f[i + 1][next][tight && k == upper][next_started],
                f[i][j][tight][started]);
          }
        }
      }
    }
  }
  for (int j = 0; j <= tot; ++j) {
    add(ans, f[n][j][0][1]);
    add(ans, f[n][j][1][1]);
  }
  printf("%lld\n", ans);
  return 0;
}
