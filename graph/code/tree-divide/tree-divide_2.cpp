#include <algorithm>
#include <cstring>
#include <iostream>
#include <queue>
using namespace std;
constexpr long long MAXN = 2000010;
constexpr long long inf = 2e9;
long long n, a, b, c, q, rt, siz[MAXN], maxx[MAXN], dist[MAXN];
long long cur, h[MAXN], nxt[MAXN], p[MAXN], w[MAXN], ret;
bool vis[MAXN];

void add_edge(long long x, long long y, long long z) {
  cur++;
  nxt[cur] = h[x];
  h[x] = cur;
  p[cur] = y;
  w[cur] = z;
}

long long sum;

void calcsiz(long long x, long long fa) {
  siz[x] = 1;
  maxx[x] = 0;
  for (long long j = h[x]; j; j = nxt[j])
    if (p[j] != fa && !vis[p[j]]) {
      calcsiz(p[j], x);
      maxx[x] = max(maxx[x], siz[p[j]]);
      siz[x] += siz[p[j]];
    }
  maxx[x] = max(maxx[x], sum - siz[x]);
  if (maxx[x] < maxx[rt]) rt = x;
}

long long dd[MAXN], cnt;

void calcdist(long long x, long long fa) {
  dd[++cnt] = dist[x];
  for (long long j = h[x]; j; j = nxt[j])
    if (p[j] != fa && !vis[p[j]])
      dist[p[j]] = dist[x] + w[j], calcdist(p[j], x);
}

queue<long long> tag;

struct segtree {
  long long cnt, rt, lc[MAXN], rc[MAXN], sum[MAXN];

  void clear() {
    while (!tag.empty()) update(rt, 1, 20000000, tag.front(), -1), tag.pop();
    cnt = 0;
  }

  void print(long long o, long long l, long long r) {
    if (!o || !sum[o]) return;
    if (l == r) {
      cout << l << ' ' << sum[o] << '\n';
      return;
    }
    long long mid = (l + r) >> 1;
    print(lc[o], l, mid);
    print(rc[o], mid + 1, r);
  }

  void update(long long& o, long long l, long long r, long long x,
              long long v) {
    if (!o) o = ++cnt;
    if (l == r) {
      sum[o] += v;
      if (!sum[o]) o = 0;
      return;
    }
    long long mid = (l + r) >> 1;
    if (x <= mid)
      update(lc[o], l, mid, x, v);
    else
      update(rc[o], mid + 1, r, x, v);
    sum[o] = sum[lc[o]] + sum[rc[o]];
    if (!sum[o]) o = 0;
  }

  long long query(long long o, long long l, long long r, long long ql,
                  long long qr) {
    if (!o) return 0;
    if (r < ql || l > qr) return 0;
    if (ql <= l && r <= qr) return sum[o];
    long long mid = (l + r) >> 1;
    return query(lc[o], l, mid, ql, qr) + query(rc[o], mid + 1, r, ql, qr);
  }
} st;

void dfz(long long x, long long fa) {
  // tf[0]=true;tag.push(0);
  st.update(st.rt, 1, 20000000, 1, 1);
  tag.push(1);
  vis[x] = true;
  for (long long j = h[x]; j; j = nxt[j])
    if (p[j] != fa && !vis[p[j]]) {
      dist[p[j]] = w[j];
      calcdist(p[j], x);
      for (long long k = 1; k <= cnt; k++)
        if (q - dd[k] >= 0)
          ret += st.query(st.rt, 1, 20000000, max(0ll, 1 - dd[k]) + 1,
                          max(0ll, q - dd[k]) + 1);
      for (long long k = 1; k <= cnt; k++)
        st.update(st.rt, 1, 20000000, dd[k] + 1, 1), tag.push(dd[k] + 1);
      cnt = 0;
    }
  st.clear();
  for (long long j = h[x]; j; j = nxt[j])
    if (p[j] != fa && !vis[p[j]]) {
      sum = siz[p[j]];
      rt = 0;
      maxx[rt] = inf;
      calcsiz(p[j], x);
      calcsiz(rt, -1);
      dfz(rt, x);
    }
}

signed main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  cin >> n;
  for (long long i = 1; i < n; i++)
    cin >> a >> b >> c, add_edge(a, b, c), add_edge(b, a, c);
  cin >> q;
  rt = 0;
  maxx[rt] = inf;
  sum = n;
  calcsiz(1, -1);
  calcsiz(rt, -1);
  dfz(rt, -1);
  cout << ret << '\n';
  return 0;
}
