#include <algorithm>
#include <cstring>
#include <iostream>
constexpr int MAXN = 2018;
constexpr int MAXM = 4000400;
using namespace std;
int Index, instack[MAXN], DFN[MAXN], LOW[MAXN];
int tot, color[MAXN];
int numedge, head[MAXN];

struct Edge {
  int nxt, to;
} edge[MAXM];

int sta[MAXN], top;
int n, m;

void add(int x, int y) {
  edge[++numedge].to = y;
  edge[numedge].nxt = head[x];
  head[x] = numedge;
}

void tarjan(int x) {  // 缩点看不懂请移步强连通分量上面有一个链接可以点。
  sta[++top] = x;
  instack[x] = 1;
  DFN[x] = LOW[x] = ++Index;
  for (int i = head[x]; i; i = edge[i].nxt) {
    int v = edge[i].to;
    if (!DFN[v]) {
      tarjan(v);
      LOW[x] = min(LOW[x], LOW[v]);
    } else if (instack[v])
      LOW[x] = min(LOW[x], DFN[v]);
  }
  if (DFN[x] == LOW[x]) {
    tot++;
    do {
      color[sta[top]] = tot;  // 染色
      instack[sta[top]] = 0;
    } while (sta[top--] != x);
  }
}

bool solve() {
  for (int i = 0; i < 2 * n; i++)
    if (!DFN[i]) tarjan(i);
  for (int i = 0; i < 2 * n; i += 2)
    if (color[i] == color[i + 1]) return false;
  return true;
}

void init() {
  top = 0;
  tot = 0;
  Index = 0;
  numedge = 0;
  memset(sta, 0, sizeof(sta));
  memset(DFN, 0, sizeof(DFN));
  memset(instack, 0, sizeof(instack));
  memset(LOW, 0, sizeof(LOW));
  memset(color, 0, sizeof(color));
  memset(head, 0, sizeof(head));
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  while (cin >> n >> m) {
    init();
    for (int i = 1; i <= m; i++) {
      int a1, a2, c1, c2;
      cin >> a1 >> a2 >> c1 >> c2;
      add(2 * a1 + c1, 2 * a2 + 1 - c2);
      // 对于第 i 对夫妇，我们用 2i+1 表示丈夫，2i 表示妻子。
      add(2 * a2 + c2, 2 * a1 + 1 - c1);
    }
    if (solve())
      cout << "YES\n";
    else
      cout << "NO\n";
  }
  return 0;
}