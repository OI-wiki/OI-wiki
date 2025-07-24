#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <vector>
#define ll long long
#define ull unsigned long long
using namespace std;

struct node {
  ull a1, a2;

  node() { a1 = a2 = 0; }

  int get(int x) {
    if (x <= 63) return (a1 >> x) & 1;
    return (a2 >> (x - 64)) & 1;
  }

  void upd(int x, int v) {
    if (x <= 63) {
      if (v == 0)
        a1 &= ~(1ULL << x);
      else
        a1 |= 1ULL << x;
    } else {
      if (v == 0)
        a2 &= ~(1ULL << (x - 64));
      else
        a2 |= 1ULL << (x - 64);
    }
  }

  friend bool operator<(const node &x, const node &y) {
    return x.a1 < y.a1 || (x.a1 == y.a1 && x.a2 < y.a2);
  }
};

map<node, int> mp;
int tot, cnt, T;
int nxt[20000][10], type[20000], belong[20000], tag[20000], sz[20000],
    trans[20000][10], ans[20000];
vector<int> pre[20000][10], Q[20000], S[20000];

int dfs(node &st) {
  if (mp.count(st)) return mp[st];
  int res = mp[st] = ++tot;
  for (int i = 0; i <= 90; i++)
    if (st.get(i)) {
      type[res] = i;
      break;
    }
  for (int v = 0; v <= 9; v++) {
    node nw;
    for (int i = 0; i <= 90; i++)
      if (st.get(i)) {
        if (i + v <= 90) nw.upd(i + v, 1);
        if (i - v >= 0)
          nw.upd(i - v, 1);
        else
          nw.upd(v - i, 1);
      }
    int t = dfs(nw);
    nxt[res][v] = t;
    pre[t][v].push_back(res);
  }
  return res;
}

void hopcroft() {
  const auto rebuild = [&](int u) {
    vector<int> tmp;
    for (auto i : Q[u])
      if (belong[i] == u) tmp.push_back(i);
    swap(Q[u], tmp);
  };
  queue<int> W;
  W.push(1);
  cnt = 10;
  for (int i = 0; i < tot; i++) {
    Q[belong[i] = type[i] + 1].push_back(i);
  }
  for (int i = 1; i <= 10; i++) {
    sz[i] = Q[i].size();
    ans[i] = i - 1;
  }
  while (!W.empty()) {
    int u = W.front();
    W.pop();
    rebuild(u);
    for (int c = 0; c <= 9; c++) {
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
          ans[++cnt] = ans[i];
          if (S[i].size() * 2 <= sz[i]) {
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
          W.push(cnt);
        }
        for (auto j : S[i]) tag[j] = 0;
        S[i].clear();
      }
    }
  }

  for (int i = 0; i < tot; i++)
    for (int c = 0; c <= 9; c++) trans[belong[i]][c] = belong[nxt[i][c]];
}

int a[20], len;
ll f[20][718][10];

ll F(int len, int lim, int x, int k) {
  if (!lim && f[len][x][k] != -1) return f[len][x][k];
  if (len == 0) return f[len][x][k] = (ans[x] <= k);
  if (lim) {
    ll res = 0;
    for (int i = 0; i < a[len]; i++) res += F(len - 1, 0, trans[x][i], k);
    res += F(len - 1, 1, trans[x][a[len]], k);
    return res;
  }
  ll res = 0;
  for (int i = 0; i <= 9; i++) res += F(len - 1, 0, trans[x][i], k);
  return f[len][x][k] = res;
}

ll calc(ll x, int k) {
  len = 0;
  while (x) {
    a[++len] = x % 10;
    x /= 10;
  }
  return F(len, 1, belong[1], k);
}

int main() {
  memset(f, -1, sizeof f);
  node st;
  st.upd(0, 1);
  dfs(st);
  hopcroft();
  scanf("%d", &T);
  while (T--) {
    ll l, r;
    int k;
    scanf("%lld%lld%d", &l, &r, &k);
    printf("%lld\n", calc(r, k) - calc(l - 1, k));
  }
}