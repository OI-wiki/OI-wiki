#include <bits/stdc++.h>
using namespace std;
const int _ = 5e5 + 10;

namespace trie {
const int _n = _ * 25;
int rt[_];
int ch[_n][2];
int w[_n];  //`w[o]` 指节点 `o` 到其父亲节点这条边上数值的数量（权值）。
int xorv[_n];
int tot = 0;

void maintain(int o) {  // 维护w数组和xorv（权值的异或）数组
  w[o] = xorv[o] = 0;
  if (ch[o][0]) {
    w[o] += w[ch[o][0]];
    xorv[o] ^= xorv[ch[o][0]] << 1;
  }
  if (ch[o][1]) {
    w[o] += w[ch[o][1]];
    xorv[o] ^= (xorv[ch[o][1]] << 1) | (w[ch[o][1]] & 1);
  }
}

int mknode() {  // 创造一个新的节点
  ++tot;
  ch[tot][0] = ch[tot][1] = 0;
  w[tot] = 0;
  return tot;
}

void insert(int &o, int x, int dp) {  // x是权重，dp是深度
  if (!o) o = mknode();
  if (dp > 20) return (void)(w[o]++);
  insert(ch[o][x & 1], x >> 1, dp + 1);
  maintain(o);
}

void erase(int o, int x, int dp) {
  if (dp > 20) return (void)(w[o]--);
  erase(ch[o][x & 1], x >> 1, dp + 1);
  maintain(o);
}

void addall(int o) {  // 对所有节点+1即将所有节点的ch[o][1]和ch[o][0]交换
  swap(ch[o][1], ch[o][0]);
  if (ch[o][0]) addall(ch[o][0]);
  maintain(o);
}
}  // namespace trie

int head[_];

struct edges {
  int node;
  int nxt;
} edge[_ << 1];

int tot = 0;

void add(int u, int v) {
  edge[++tot].nxt = head[u];
  head[u] = tot;
  edge[tot].node = v;
}

int n, m;
int rt;
int lztar[_];
int fa[_];

void dfs0(int o, int f) {  // 得到fa数组
  fa[o] = f;
  for (int i = head[o]; i; i = edge[i].nxt) {  // 遍历子节点
    int node = edge[i].node;
    if (node == f) continue;
    dfs0(node, o);
  }
}

int V[_];

int get(int x) { return (fa[x] == -1 ? 0 : lztar[fa[x]]) + V[x]; }  // 权值函数

int main() {
  cin >> n >> m;
  for (int i = 1; i < n; i++) {
    int u, v;
    cin >> u >> v;
    add(u, v);  // 双向建边
    add(rt = v, u);
  }
  dfs0(rt, -1);  // rt是随机的一个点
  for (int i = 1; i <= n; i++) {
    cin >> V[i];
    if (fa[i] != -1) trie::insert(trie::rt[fa[i]], V[i], 0);
  }
  while (m--) {
    int opt, x;
    cin >> opt >> x;
    if (opt == 1) {
      lztar[x]++;
      if (x != rt) {
        if (fa[fa[x]] != -1) trie::erase(trie::rt[fa[fa[x]]], get(fa[x]), 0);
        V[fa[x]]++;
        if (fa[fa[x]] != -1)
          trie::insert(trie::rt[fa[fa[x]]], get(fa[x]), 0);  // 重新插入
      }
      trie::addall(trie::rt[x]);  // 对所有节点+1
    } else if (opt == 2) {
      int v;
      cin >> v;
      if (x != rt) trie::erase(trie::rt[fa[x]], get(x), 0);
      V[x] -= v;
      if (x != rt) trie::insert(trie::rt[fa[x]], get(x), 0);  // 重新插入
    } else {
      int res = 0;
      res = trie::xorv[trie::rt[x]];
      res ^= get(fa[x]);
      printf("%d\n", res);
    }
  }
  return 0;
}
