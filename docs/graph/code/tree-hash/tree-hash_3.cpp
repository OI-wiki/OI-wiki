#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <set>
#include <utility>
#include <vector>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 100000 + 5;

namespace sieve {
const int maxp = 2000000 + 5;
int vis[maxp], prime[maxp], tot;

void init() {
  memset(vis, 0, sizeof(vis));
  for (int i = 2; i < maxp; i++) {
    if (!vis[i]) prime[++tot] = i;
    for (int j = 1; j <= tot && prime[j] * i < maxp; j++) {
      vis[i * prime[j]] = 1;
      if (i % prime[j] == 0) break;
    }
  }
}
}  // namespace sieve

namespace MyIO {
struct fastIO {
  char s[100000];
  int it, len;

  fastIO() { it = len = 0; }

  inline char get() {
    if (it < len) return s[it++];
    it = 0;
    len = fread(s, 1, 100000, stdin);
    if (len == 0)
      return EOF;
    else
      return s[it++];
  }

  bool notend() {
    char c = get();
    while (c == ' ' || c == '\n') c = get();
    if (it > 0) it--;
    return c != EOF;
  }
} buff;

inline int gi() {
  int r = 0;
  bool ng = 0;
  char c = buff.get();
  while (c != '-' && (c < '0' || c > '9')) c = buff.get();
  if (c == '-') ng = 1, c = buff.get();
  while (c >= '0' && c <= '9') r = r * 10 + c - '0', c = buff.get();
  return ng ? -r : r;
}
}  // namespace MyIO

namespace {
inline int add(int x, int y) {
  x += y;
  return x >= mod ? x -= mod : x;
}

inline int sub(int x, int y) {
  x -= y;
  return x < 0 ? x += mod : x;
}

inline int mul(int x, int y) { return 1ll * x * y % mod; }

inline int qpow(int x, ll n) {
  int r = 1;
  while (n > 0) {
    if (n & 1) r = 1ll * r * x % mod;
    n >>= 1;
    x = 1ll * x * x % mod;
  }
  return r;
}

inline int inv(int x) { return qpow(x, mod - 2); }
}  // namespace

using MyIO::gi;
using sieve::prime;
int ping[maxn], pingv[maxn];
int n, ans, siz[maxn];
vector<int> edge[maxn];
map<ull, int> uqc[maxn];
map<ull, int>::iterator it;
ull hashval[maxn], hashrt[maxn];
ull srchashval[maxn], srchashrt[maxn];
int dp[maxn], rdp[maxn];

ull pack(ull val, int sz) { return 2ull + 3ull * val + 7ull * prime[sz + 1]; }

void predfs(int u, int ff) {
  siz[u] = dp[u] = 1;
  hashval[u] = 1;
  int sz = 0;
  for (int v : edge[u]) {
    if (v == ff) continue;
    predfs(v, u);
    sz++;
    siz[u] += siz[v];
    dp[u] = mul(dp[u], dp[v]);
    uqc[u][hashval[v]]++;
    hashval[u] += hashval[v] * prime[siz[v]];
  }
  srchashval[u] = hashval[u];
  hashval[u] = pack(hashval[u], siz[u]);
  dp[u] = mul(dp[u], ping[sz]);
  for (it = uqc[u].begin(); it != uqc[u].end(); it++) {
    dp[u] = mul(dp[u], pingv[it->second]);
  }
}

set<ull> qc;

void dfs(int u, int ff) {
  if (!qc.count(hashrt[u])) {
    qc.insert(hashrt[u]);
    ans = add(ans, rdp[u]);
  }
  for (int v : edge[u]) {
    if (v == ff) continue;
    ull tmp = srchashrt[u] - hashval[v] * prime[siz[v]];
    tmp = pack(tmp, n - siz[v]);
    uqc[v][tmp]++;
    srchashrt[v] = srchashval[v] + tmp * prime[n - siz[v]];
    hashrt[v] = pack(srchashrt[v], n);
    int tdp = mul(rdp[u], inv(dp[v]));
    tdp = mul(tdp, inv((int)edge[u].size()));
    tdp = mul(tdp, uqc[u][hashval[v]]);
    rdp[v] = mul(dp[v], tdp);
    rdp[v] = mul(rdp[v], (int)edge[v].size());
    rdp[v] = mul(rdp[v], inv(uqc[v][tmp]));
    dfs(v, u);
  }
}

int main() {
  sieve::init();
  ping[0] = pingv[0] = 1;
  for (int i = 1; i < maxn; i++) {
    ping[i] = mul(ping[i - 1], i);
    pingv[i] = mul(pingv[i - 1], inv(i));
  }
  int T = gi();
  while (T--) {
    n = gi();
    for (int i = 2, u, v; i <= n; i++) {
      u = gi();
      v = gi();
      edge[u].push_back(v);
      edge[v].push_back(u);
    }
    predfs(1, 0);
    ans = 0;
    qc.clear();
    rdp[1] = dp[1];
    hashrt[1] = hashval[1];
    srchashrt[1] = srchashval[1];
    dfs(1, 0);
    printf("%d\n", ans);
    for (int i = 1; i <= n; i++) {
      edge[i].clear();
      uqc[i].clear();
    }
  }
  return 0;
}