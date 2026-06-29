#include <algorithm>
#include <iostream>
using namespace std;
#define rep(i, a, b) for (int i = (a); i <= (b); ++i)
constexpr int N = 200005;
int h[N], nxt[N * 2], to[N * 2], c[N], gr;

void tu(int x, int y) { to[++gr] = y, nxt[gr] = h[x], h[x] = gr; }

using ll = long long;
int n, nn, siz[N], mn, rt;
bool vis[N];

void get_root(int u, int f) {
  siz[u] = 1;
  int mx = 0;
  for (int i = h[u]; i; i = nxt[i]) {
    int d = to[i];
    if (vis[d] || d == f) continue;
    get_root(d, u);
    siz[u] += siz[d];
    mx = max(mx, siz[d]);
  }
  mx = max(mx, nn - siz[u]);
  if (mx < mn) mn = mx, rt = u;
}

ll ans[N], sum;
int cnt[N], v[N];
// sum实时统计的是cnt[i]的和
int nowrt;

void get_dis(int u, int f, int now) {  // now为当前树链上的颜色数量(不含u)
  siz[u] = 1;
  if (!v[c[u]]) {
    sum -= cnt[c[u]];  // 减去在之前子树中已经出现过的颜色信息
    now++;
  }
  v[c[u]]++;
  ans[u] += sum + now * siz[nowrt];  // 统计过u点的路径对u的贡献
  for (int i = h[u]; i; i = nxt[i]) {
    int d = to[i];
    if (d == f || vis[d]) continue;
    get_dis(d, u, now);
    siz[u] += siz[d];
  }
  v[c[u]]--;
  if (!v[c[u]]) {
    sum += cnt[c[u]];  // 回溯
  }
}

void get_cnt(int u, int f) {
  if (!v[c[u]]) {
    cnt[c[u]] += siz[u];
    sum += siz[u];  // 将刚遍历过的子树的信息整合到cnt[i]和sum上去
  }
  v[c[u]]++;
  for (int i = h[u]; i; i = nxt[i]) {
    int d = to[i];
    if (vis[d] || d == f) continue;
    get_cnt(d, u);
  }
  v[c[u]]--;
}

void clear(int u, int f, int now) {
  if (!v[c[u]]) now++;
  v[c[u]]++;
  ans[u] -= now;
  ans[nowrt] += now;
  for (int i = h[u]; i; i = nxt[i]) {
    int d = to[i];
    if (vis[d] || d == f) continue;
    clear(d, u, now);
  }
  v[c[u]]--;
  cnt[c[u]] = 0;
}

void clear2(int u, int f) {
  cnt[c[u]] = 0;
  for (int i = h[u]; i; i = nxt[i]) {
    int d = to[i];
    if (vis[d] || d == f) continue;
    clear2(d, u);
  }
}

int son[N];

void divid(int u) {
  vis[u] = true;
  int tot = 0;
  nowrt = u;
  ans[u]++;
  for (int i = h[u]; i; i = nxt[i]) {
    if (vis[to[i]]) continue;
    son[++tot] = to[i];
  }
  siz[u] = sum = cnt[c[u]] = 1;
  v[c[u]]++;
  rep(i, 1, tot) {  // 统计每个子树和它之前的所有子树中节点组合产生的贡献
    int d = son[i];
    get_dis(d, u, 0);
    get_cnt(d, u);
    siz[u] += siz[d];
    cnt[c[u]] += siz[d];
    sum += siz[d];
  }
  clear2(u, 0);  // 清空数组，记得不可以用memset
  siz[u] = sum = cnt[c[u]] = 1;
  for (int i = tot; i >= 1;
       --i) {  // 统计每个子树和它之后的所有子树中节点组合产生的贡献
    int d = son[i];
    get_dis(d, u, 0);
    get_cnt(d, u);
    siz[u] += siz[d];
    cnt[c[u]] += siz[d];
    sum += siz[d];
  }
  v[c[u]]--;
  clear(u, 0, 0);                      // 清空的同时统计答案
  for (int i = h[u]; i; i = nxt[i]) {  // 继续向下进行点分治
    int d = to[i];
    if (vis[d]) continue;
    nn = siz[d], mn = n + 1, rt = 0;
    get_root(d, u);
    divid(rt);
  }
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  cin >> n;
  int u, v;
  rep(i, 1, n) cin >> c[i];
  rep(i, 2, n) cin >> u >> v, tu(u, v), tu(v, u);
  rt = 0, nn = n, mn = n + 1;
  get_root(1, 0);
  divid(rt);
  rep(i, 1, n) cout << ans[i] << '\n';
  return 0;
}