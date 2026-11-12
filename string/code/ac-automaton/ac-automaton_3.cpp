#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
using namespace std;

constexpr int N = 2e5 + 6;
constexpr int LEN = 2e6 + 6;
constexpr int SIZE = 2e5 + 6;

int n;

namespace AC {
struct Node {
  int son[26];
  int ans;
  int fail;
  int idx;

  void init() {
    memset(son, 0, sizeof(son));
    ans = idx = 0;
  }
} tr[SIZE];

int tot;
int ans[N], pidx;

vector<int> g[SIZE];  // fail 树

void init() {
  tot = pidx = 0;
  tr[0].init();
}

void insert(char s[], int &idx) {
  int u = 0;
  for (int i = 1; s[i]; i++) {
    int &son = tr[u].son[s[i] - 'a'];
    if (!son) son = ++tot, tr[son].init();
    u = son;
  }
  // 由于有可能出现相同的模式串，需要将相同的映射到同一个编号
  if (!tr[u].idx) tr[u].idx = ++pidx;  // 第一次出现，新增编号
  idx = tr[u].idx;  // 这个模式串的编号对应这个结点的编号
}

void build() {
  queue<int> q;
  for (int i = 0; i < 26; i++)
    if (tr[0].son[i]) {
      q.push(tr[0].son[i]);
      g[0].push_back(tr[0].son[i]);  // 不要忘记这里的 fail
    }
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    for (int i = 0; i < 26; i++) {
      if (tr[u].son[i]) {
        tr[tr[u].son[i]].fail = tr[tr[u].fail].son[i];
        g[tr[tr[u].fail].son[i]].push_back(tr[u].son[i]);  // 记录 fail 树
        q.push(tr[u].son[i]);
      } else
        tr[u].son[i] = tr[tr[u].fail].son[i];
    }
  }
}

void query(char t[]) {
  int u = 0;
  for (int i = 1; t[i]; i++) {
    u = tr[u].son[t[i] - 'a'];
    tr[u].ans++;
  }
}

void dfs(int u) {
  for (int v : g[u]) {
    dfs(v);
    tr[u].ans += tr[v].ans;
  }
  ans[tr[u].idx] = tr[u].ans;
}
}  // namespace AC

char s[LEN];
int idx[N];

int main() {
  AC::init();
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%s", s + 1);
    AC::insert(s, idx[i]);
    AC::ans[i] = 0;
  }
  AC::build();
  scanf("%s", s + 1);
  AC::query(s);
  AC::dfs(0);
  for (int i = 1; i <= n; i++) {
    printf("%d\n", AC::ans[idx[i]]);
  }
  return 0;
}
