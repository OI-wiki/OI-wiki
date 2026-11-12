#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;

constexpr int N = 1e6 + 6;
constexpr int LEN = 1e6 + 6;
constexpr int SIZE = 1e6 + 6;

int n;

namespace AC {
struct Node {
  int son[26];  // 子结点
  int cnt;      // 尾为该结点的串的个数
  int fail;     // fail 指针

  void init() {  // 结点初始化
    memset(son, 0, sizeof(son));
    cnt = fail = 0;
  }
} tr[SIZE];

int tot;  // 结点总数

void init() {
  tot = 0;
  tr[0].init();
}

void insert(char s[]) {
  int u = 0;
  for (int i = 1; s[i]; i++) {
    int &son = tr[u].son[s[i] - 'a'];  // 下一个子结点的引用
    if (!son) son = ++tot, tr[son].init();  // 如果没有则插入新结点，并初始化
    u = son;                                // 从下一个结点继续
  }
  tr[u].cnt++;
}

void build() {
  queue<int> q;
  for (int i = 0; i < 26; i++)
    if (tr[0].son[i]) q.push(tr[0].son[i]);
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    for (int i = 0; i < 26; i++) {
      if (tr[u].son[i]) {                               // 存在对应子结点
        tr[tr[u].son[i]].fail = tr[tr[u].fail].son[i];  // 只用跳一次 fail 指针
        q.push(tr[u].son[i]);                           // 并加入队列
      } else
        tr[u].son[i] =
            tr[tr[u].fail]
                .son[i];  // 将不存在的字典树的状态链接到了失配指针的对应状态
    }
  }
}

int query(char t[]) {
  int u = 0, res = 0;
  for (int i = 1; t[i]; i++) {
    u = tr[u].son[t[i] - 'a'];  // 转移
    for (int j = u; j && tr[j].cnt != -1; j = tr[j].fail) {
      res += tr[j].cnt, tr[j].cnt = -1;
    }
  }
  return res;
}
}  // namespace AC

char s[LEN];

int main() {
  AC::init();
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%s", s + 1);
    AC::insert(s);
  }
  AC::build();
  scanf("%s", s + 1);
  printf("%d", AC::query(s));
  return 0;
}
