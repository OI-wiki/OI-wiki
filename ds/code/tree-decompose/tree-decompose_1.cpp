#include <bitset>
#include <cctype>
#include <iostream>

#if defined(_MSC_VER) && !defined(__clang__)
#include <immintrin.h>
#endif

using namespace std;

constexpr int N = 100010;
constexpr int B = 666;
constexpr int C = 30000;

void add(int u, int v);
void dfs(int u);

int head[N], nxt[N << 1], to[N << 1], cnt;
int n, m, type, c[N], fa[N], dep[N], sta[N], top, tot, bl[N], key[N / B + 5],
    p[N], keyid[N];
bool vis[N];
bitset<C> bs[N / B + 5][N / B + 5], temp;

template <size_t N>
size_t find_first(std::bitset<N> b) {
#if defined(__GNUC__) && !defined(__clang__)
  return b._Find_first();
#elif defined(_MSC_VER) && !defined(__clang__)
  using word_t = decltype(b._Getword(0));
  constexpr ptrdiff_t word_len = CHAR_BIT * sizeof(word_t);
  constexpr ptrdiff_t words = N == 0 ? 0 : (N - 1) / word_len;
  size_t ans = 0;
  for (size_t i = 0; i <= words; ++i)
    if (b._Getword(i) != 0) {
      if (sizeof(word_t) == sizeof(unsigned int))
        return i * word_len + _tzcnt_u32(b._Getword(i));
      else
        return i * word_len + _tzcnt_u64(b._Getword(i));
    }
  return N;
#else
  auto s = b.to_string();
  for (size_t i = s.size() - 1; ~i; --i)
    if (s[i] & 1) return s.size() - 1 - i;
  return N;
#endif
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  int i, u, v, x, y, k, lastans = 0;
  cin >> n >> m >> type;

  for (i = 1; i <= n; ++i) cin >> c[i];

  for (i = 1; i < n; ++i) {
    cin >> u >> v;
    add(u, v);
    add(v, u);
  }

  dfs(1);

  if (!tot) ++tot;
  if (keyid[key[tot]] == tot) keyid[key[tot]] = 0;
  key[tot] = 1;
  keyid[1] = tot;
  while (top) bl[sta[top--]] = tot;

  for (i = 1; i <= tot; ++i) {  // 预处理
    if (vis[key[i]]) continue;
    vis[key[i]] = true;
    temp.reset();
    for (u = key[i]; u; u = fa[u]) {
      temp[c[u]] = 1;
      if (keyid[u]) {
        if (!p[key[i]] && u != key[i]) p[key[i]] = u;
        bs[keyid[key[i]]][keyid[u]] = temp;
      }
    }
  }

  while (m--) {
    cin >> k;
    temp.reset();
    while (k--) {
      cin >> x >> y;
      u = x ^= lastans;
      v = y ^= lastans;

      while (key[bl[x]] != key[bl[y]]) {
        if (dep[key[bl[x]]] > dep[key[bl[y]]]) {
          if (x == u) {  // 若是第一次跳先暴力跳到关键点
            while (x != key[bl[u]]) {
              temp[c[x]] = 1;
              x = fa[x];
            }
          } else
            x = p[x];  // 否则跳一整块
        } else {
          if (y == v) {
            while (y != key[bl[v]]) {
              temp[c[y]] = 1;
              y = fa[y];
            }
          } else
            y = p[y];
        }
      }

      if (keyid[x]) temp |= bs[keyid[key[bl[u]]]][keyid[x]];
      if (keyid[y]) temp |= bs[keyid[key[bl[v]]]][keyid[y]];

      while (x != y) {
        if (dep[x] > dep[y]) {
          temp[c[x]] = 1;
          x = fa[x];
        } else {
          temp[c[y]] = 1;
          y = fa[y];
        }
      }
      temp[c[x]] = true;
    }
    int ans1 = temp.count(), ans2 = find_first(~temp);
    cout << ans1 << ' ' << ans2 << '\n';
    lastans = (ans1 + ans2) * type;
  }

  return 0;
}

void dfs(int u) {  // 根据题意找点
  int i, v, t = top;
  for (i = head[u]; i; i = nxt[i]) {
    v = to[i];
    if (v == fa[u]) continue;
    fa[v] = u;
    dep[v] = dep[u] + 1;
    dfs(v);
    if (top - t >= B) {
      key[++tot] = u;
      if (!keyid[u]) keyid[u] = tot;
      while (top > t) bl[sta[top--]] = tot;
    }
  }
  sta[++top] = u;
}

void add(int u, int v) {
  nxt[++cnt] = head[u];
  head[u] = cnt;
  to[cnt] = v;
}