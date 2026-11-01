#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

#include <cstdio>

constexpr int _ = 526010;
int n;
int V[_];
int debug = 0;

namespace trie {
constexpr int MAXH = 21;
int ch[_ * (MAXH + 1)][2], w[_ * (MAXH + 1)], xorv[_ * (MAXH + 1)];
int tot = 0;

int mknode() {
  ++tot;
  ch[tot][1] = ch[tot][0] = w[tot] = xorv[tot] = 0;
  return tot;
}

void maintain(int o) {
  w[o] = xorv[o] = 0;
  if (ch[o][0]) {
    w[o] += w[ch[o][0]];
    xorv[o] ^= xorv[ch[o][0]] << 1;
  }
  if (ch[o][1]) {
    w[o] += w[ch[o][1]];
    xorv[o] ^= (xorv[ch[o][1]] << 1) | (w[ch[o][1]] & 1);
  }
  w[o] = w[o] & 1;
}

void insert(int &o, int x, int dp) {
  if (!o) o = mknode();
  if (dp > MAXH) return (void)(w[o]++);
  insert(ch[o][x & 1], x >> 1, dp + 1);
  maintain(o);
}

int merge(int a, int b) {
  if (!a) return b;
  if (!b) return a;
  w[a] = w[a] + w[b];
  xorv[a] ^= xorv[b];
  ch[a][0] = merge(ch[a][0], ch[b][0]);
  ch[a][1] = merge(ch[a][1], ch[b][1]);
  return a;
}

void addall(int o) {
  if (!o || (!ch[o][0] && !ch[o][1])) return;
  swap(ch[o][0], ch[o][1]);
  if (ch[o][0]) addall(ch[o][0]);
  maintain(o);
}
}  // namespace trie

int rt[_];
long long Ans = 0;
vector<int> E[_];

void dfs0(int o) {
  for (int i = 0; i < E[o].size(); i++) {
    int node = E[o][i];
    dfs0(node);
    rt[o] = trie::merge(rt[o], rt[node]);
  }
  trie::addall(rt[o]);
  trie::insert(rt[o], V[o], 0);
  Ans += trie::xorv[rt[o]];
}

int main() {
  cin >> n;
  for (int i = 1; i <= n; i++) cin >> V[i];
  for (int i = 2; i <= n; i++) {
    int parent;
    cin >> parent;
    E[parent].push_back(i);
  }
  dfs0(1);
  printf("%lld", Ans);
  return 0;
}
