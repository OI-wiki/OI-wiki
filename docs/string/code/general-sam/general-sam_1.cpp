#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

#include <queue>
#include <utility>

// --8<-- [start:trie]
constexpr int MAXN = 2000000;
constexpr int CHAR_NUM = 30;

struct Trie {
  int next[MAXN][CHAR_NUM];  // 转移
  int tot;                   // 节点总数：[0, tot)

  void init() { tot = 1; }

  int insertTrie(int cur, int c) {
    if (next[cur][c]) return next[cur][c];
    return next[cur][c] = tot++;
  }

  void insert(const string &s) {
    int root = 0;
    for (auto ch : s) root = insertTrie(root, ch - 'a');
  }
};

// --8<-- [end:trie]

// --8<-- [start:gsa]
struct GSA {
  int len[MAXN];             // 节点长度
  int link[MAXN];            // 后缀链接，link
  int next[MAXN][CHAR_NUM];  // 转移
  int tot;                   // 节点总数：[0, tot)

  int insertSAM(int last, int c) {
    int cur = next[last][c];
    if (len[cur]) return cur;
    len[cur] = len[last] + 1;
    int p = link[last];
    while (p != -1) {
      if (!next[p][c])
        next[p][c] = cur;
      else
        break;
      p = link[p];
    }
    if (p == -1) {
      link[cur] = 0;
      return cur;
    }
    int q = next[p][c];
    if (len[p] + 1 == len[q]) {
      link[cur] = q;
      return cur;
    }
    int clone = tot++;
    for (int i = 0; i < CHAR_NUM; ++i)
      next[clone][i] = len[next[q][i]] != 0 ? next[q][i] : 0;
    len[clone] = len[p] + 1;
    while (p != -1 && next[p][c] == q) {
      next[p][c] = clone;
      p = link[p];
    }
    link[clone] = link[q];
    link[cur] = clone;
    link[q] = clone;
    return cur;
  }

  void build() {
    queue<pair<int, int>> q;
    for (int i = 0; i < CHAR_NUM; ++i)
      if (next[0][i]) q.push({i, 0});
    while (!q.empty()) {
      auto item = q.front();
      q.pop();
      auto last = insertSAM(item.second, item.first);
      for (int i = 0; i < CHAR_NUM; ++i)
        if (next[last][i]) q.push({i, last});
    }
  }
};

// --8<-- [end:gsa]

Trie trie;
GSA gsa;

int main() {
  int n;
  cin >> n;
  trie.init();
  for (int i = 0; i < n; ++i) {
    string s;
    cin >> s;
    trie.insert(s);
  }
  gsa.tot = trie.tot;
  gsa.link[0] = -1;
  for (int i = 0; i < trie.tot; ++i)
    copy(trie.next[i], trie.next[i] + CHAR_NUM, gsa.next[i]);
  gsa.build();
  long long ans = 0;
  for (int i = 1; i < gsa.tot; ++i) ans += gsa.len[i] - gsa.len[gsa.link[i]];
  cout << ans << '\n' << gsa.tot << '\n';
}
