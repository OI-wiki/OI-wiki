#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;

constexpr int N = 20 + 6, M = 50 + 6;
constexpr int LEN = 2e6 + 6;
constexpr int SIZE = 450 + 6;

int n, m;

namespace AC {
struct Node {
  int son[26];
  int fail;
  int idx;
  int depth;
  unsigned stat;

  void init() {
    memset(son, 0, sizeof(son));
    fail = idx = depth = 0;
  }
} tr[SIZE];

int tot;

void init() {
  tot = 0;
  tr[0].init();
}

void insert(char s[], int idx) {
  int u = 0;
  for (int i = 1; s[i]; i++) {
    int &son = tr[u].son[s[i] - 'a'];
    if (!son) son = ++tot, tr[son].init();
    u = son;
  }
  tr[u].idx = idx;
}

void build() {
  queue<int> q;
  for (int i = 0; i < 26; i++)
    if (tr[0].son[i]) {
      q.push(tr[0].son[i]);
      tr[tr[0].son[i]].depth = 1;
    }
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    int v = tr[u].fail;
    // 对状态的更新在这里
    tr[u].stat = tr[v].stat;
    if (tr[u].idx) tr[u].stat |= 1 << tr[u].depth;
    for (int i = 0; i < 26; i++) {
      if (tr[u].son[i]) {
        tr[tr[u].son[i]].fail = tr[tr[u].fail].son[i];
        tr[tr[u].son[i]].depth = tr[u].depth + 1;  // 记录深度
        q.push(tr[u].son[i]);
      } else
        tr[u].son[i] = tr[tr[u].fail].son[i];
    }
  }
}

int query(char t[]) {
  int u = 0, mx = 0;
  unsigned st = 1;
  for (int i = 1; t[i]; i++) {
    u = tr[u].son[t[i] - 'a'];
    st <<= 1;
    if (tr[u].stat & st) st |= 1, mx = i;
  }
  return mx;
}
}  // namespace AC

char s[LEN];

int main() {
  AC::init();
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; i++) {
    scanf("%s", s + 1);
    AC::insert(s, i);
  }
  AC::build();
  for (int i = 1; i <= m; i++) {
    scanf("%s", s + 1);
    printf("%d\n", AC::query(s));
  }
  return 0;
}
