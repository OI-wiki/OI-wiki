#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;

constexpr int N = 150 + 6;
constexpr int LEN = 1e6 + 6;
constexpr int SIZE = N * 70 + 6;

int n;

namespace AC {
struct Node {
  int son[26];
  int fail;
  int idx;

  void init() {
    memset(son, 0, sizeof(son));
    idx = fail = 0;
  }
} tr[SIZE];

int tot;

void init() {
  tot = 0;
  tr[0].init();
}

void insert(char s[], int idx) {  // 将第 idx 个字符串 s 插入
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
    if (tr[0].son[i]) q.push(tr[0].son[i]);
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    for (int i = 0; i < 26; i++) {
      if (tr[u].son[i]) {
        tr[tr[u].son[i]].fail = tr[tr[u].fail].son[i];
        q.push(tr[u].son[i]);
      } else
        tr[u].son[i] = tr[tr[u].fail].son[i];
    }
  }
}

int query(char t[], int cnt[]) {
  int u = 0, res = 0;
  for (int i = 1; t[i]; i++) {
    u = tr[u].son[t[i] - 'a'];
    for (int j = u; j; j = tr[j].fail)
      ++cnt[tr[j].idx];  // 统计每个字符串出现的次数
  }
  for (int i = 0; i <= tot; ++i)
    if (tr[i].idx) res = max(res, cnt[tr[i].idx]);
  return res;
}
}  // namespace AC

char s[N][75], t[LEN];
int cnt[N];  // 每一个字符串出现的次数

int main() {
  while (scanf("%d", &n) != EOF && n != 0) {
    AC::init();
    for (int i = 1; i <= n; i++) {
      scanf("%s", s[i] + 1);
      AC::insert(s[i], i);
      cnt[i] = 0;
    }
    AC::build();
    scanf("%s", t + 1);
    int x = AC::query(t, cnt);
    printf("%d\n", x);
    for (int i = 1; i <= n; i++)
      if (cnt[i] == x) printf("%s\n", s[i] + 1);
  }
  return 0;
}
