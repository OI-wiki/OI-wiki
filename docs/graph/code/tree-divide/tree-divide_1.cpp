#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;
const int maxn = 20010;
const int inf = 2e9;
int n, m, a, b, c, q[maxn], rt, siz[maxn], maxx[maxn], dist[maxn];
int cur, h[maxn], nxt[maxn], p[maxn], w[maxn];
bool tf[10000010], ret[maxn], vis[maxn];

void add_edge(int x, int y, int z) {
  cur++;
  nxt[cur] = h[x];
  h[x] = cur;
  p[cur] = y;
  w[cur] = z;
}

int sum;

void calcsiz(int x, int fa) {
  siz[x] = 1;
  maxx[x] = 0;
  for (int j = h[x]; j; j = nxt[j])
    if (p[j] != fa && !vis[p[j]]) {
      calcsiz(p[j], x);
      maxx[x] = max(maxx[x], siz[p[j]]);
      siz[x] += siz[p[j]];
    }
  maxx[x] = max(maxx[x], sum - siz[x]);
  if (maxx[x] < maxx[rt]) rt = x;
}

int dd[maxn], cnt;

void calcdist(int x, int fa) {
  dd[++cnt] = dist[x];
  for (int j = h[x]; j; j = nxt[j])
    if (p[j] != fa && !vis[p[j]])
      dist[p[j]] = dist[x] + w[j], calcdist(p[j], x);
}

queue<int> tag;

void dfz(int x, int fa) {
  tf[0] = true;
  tag.push(0);
  vis[x] = true;
  for (int j = h[x]; j; j = nxt[j])
    if (p[j] != fa && !vis[p[j]]) {
      dist[p[j]] = w[j];
      calcdist(p[j], x);
      for (int k = 1; k <= cnt; k++)
        for (int i = 1; i <= m; i++)
          if (q[i] >= dd[k]) ret[i] |= tf[q[i] - dd[k]];
      for (int k = 1; k <= cnt; k++)
        if (dd[k] < 10000010) tag.push(dd[k]), tf[dd[k]] = true;
      cnt = 0;
    }
  while (!tag.empty()) tf[tag.front()] = false, tag.pop();
  for (int j = h[x]; j; j = nxt[j])
    if (p[j] != fa && !vis[p[j]]) {
      sum = siz[p[j]];
      rt = 0;
      maxx[rt] = inf;
      calcsiz(p[j], x);
      calcsiz(rt, -1);
      dfz(rt, x);
    }
}

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1; i < n; i++)
    scanf("%d%d%d", &a, &b, &c), add_edge(a, b, c), add_edge(b, a, c);
  for (int i = 1; i <= m; i++) scanf("%d", q + i);
  rt = 0;
  maxx[rt] = inf;
  sum = n;
  calcsiz(1, -1);
  calcsiz(rt, -1);
  dfz(rt, -1);
  for (int i = 1; i <= m; i++)
    if (ret[i])
      printf("AYE\n");
    else
      printf("NAY\n");
  return 0;
}