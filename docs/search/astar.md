A\*算法是 [BFS](./bfs.md) 的一种改进。

定义起点 $s$ ，终点 $t$ 。

从起点（初始状态）开始的距离函数 $g(x)$ 。

到终点（最终状态）的距离函数 $h(x), h*(x)$ 。

定义每个点的估价函数 $f(x)=g(x)+h(x)$ 。

A\*算法每次从 **优先队列** 中取出一个 $f$ 最小的，然后更新相邻的状态。

如果 $h\leq h*$ ，则 A\*算法能找到最优解。

上述条件下，如果 $h$  **满足三角形不等式，则 A\*算法不会将重复结点加入队列** 。

其实…… $h=0$ 时就是 [DFS](./dfs.md) 算法， $h=0$ 并且边权为 $1$ 时就是 [BFS](./bfs.md) 。

## 例题 [八数码](https://www.luogu.org/problemnew/show/P1379) 

题目大意：在 $3\times 3$ 的棋盘上，摆有八个棋子，每个棋子上标有 1 至 8 的某一数字。棋盘中留有一个空格，空格用 0 来表示。空格周围的棋子可以移到空格中，这样原来的位置就会变成空格。给出一种初始布局和目标布局（为了使题目简单，设目标状态为

    123
    804
    765

），找到一种从初始布局到目标布局最少步骤的移动方法。

 $h$ 函数可以定义为，不在应该在的位置的数字个数。

容易发现 $h$ 满足以上两个性质，此题可以使用 A\*算法求解。

代码实现：

```cpp
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>
#include <set>
using namespace std;
const int dx[4] = {1, -1, 0, 0}, dy[4] = {0, 0, 1, -1};
int fx, fy;
char ch;
struct matrix {
  int a[5][5];
  bool operator<(matrix x) const {
    for (int i = 1; i <= 3; i++)
      for (int j = 1; j <= 3; j++)
        if (a[i][j] != x.a[i][j]) return a[i][j] < x.a[i][j];
    return false;
  }
} f, st;
int h(matrix a) {
  int ret = 0;
  for (int i = 1; i <= 3; i++)
    for (int j = 1; j <= 3; j++)
      if (a.a[i][j] != st.a[i][j]) ret++;
  return ret;
}
struct node {
  matrix a;
  int t;
  bool operator<(node x) const { return t + h(a) > x.t + h(x.a); }
} x;
priority_queue<node> q;
set<matrix> s;
int main() {
  st.a[1][1] = 1;
  st.a[1][2] = 2;
  st.a[1][3] = 3;
  st.a[2][1] = 8;
  st.a[2][2] = 0;
  st.a[2][3] = 4;
  st.a[3][1] = 7;
  st.a[3][2] = 6;
  st.a[3][3] = 5;
  for (int i = 1; i <= 3; i++)
    for (int j = 1; j <= 3; j++) {
      scanf(" %c", &ch);
      f.a[i][j] = ch - '0';
    }
  q.push({f, 0});
  while (!q.empty()) {
    x = q.top();
    q.pop();
    if (!h(x.a)) {
      printf("%d\n", x.t);
      return 0;
    }
    for (int i = 1; i <= 3; i++)
      for (int j = 1; j <= 3; j++)
        if (!x.a.a[i][j]) fx = i, fy = j;
    for (int i = 0; i < 4; i++) {
      int xx = fx + dx[i], yy = fy + dy[i];
      if (1 <= xx && xx <= 3 && 1 <= yy && yy <= 3) {
        swap(x.a.a[fx][fy], x.a.a[xx][yy]);
        if (!s.count(x.a)) s.insert(x.a), q.push({x.a, x.t + 1});
        swap(x.a.a[fx][fy], x.a.a[xx][yy]);
      }
    }
  }
  return 0;
}
```

## 例题 [k 短路](https://www.luogu.org/problemnew/show/P2483) 

题目大意：按顺序求一个有向图上从结点 $s$ 到结点 $t$ 的所有路径最小的前任意多（不妨设为 $k$ ）个。

很容易发现，这个问题很容易转化成用 A\*算法解决问题的标准程式。

初始状态为处于结点 $s$ ，最终状态为处于结点 $t$ ，距离函数为从 $s$ 到当前结点已经走过的距离，估价函数为从当前结点到结点 $t$ 至少要走过的距离，也就是当前结点到结点 $t$ 的最短路。

就这样，我们在预处理的时候反向建图，计算出结点 $t$ 到所有点的最短路，然后将初始状态塞入优先队列，每次取出 $f(x)=g(x)+h(x)$ 最小的一项，计算出其所连结点的信息并将其也塞入队列。当你第 $k$ 次走到结点 $t$ 时，也就算出了结点 $s$ 到结点 $t$ 的 $k$ 短路。

由于设计的距离函数和估价函数，每个状态需要存储两个参数，当前结点 $x$ 和已经走过的距离 $v$ 。

我们可以在此基础上加一点小优化：由于只需要求出第 $k$ 短路，所以当我们第 $k+1$ 次或以上走到该结点时，直接跳过该状态。因为前面的 $k$ 次走到这个点的时候肯定能因此构造出 $k$ 条路径，所以之后在加边更无必要。

代码实现：

```cpp
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;
const int maxn = 5010;
const int maxm = 400010;
const double inf = 2e9;
int n, m, k, u, v, cur, h[maxn], nxt[maxm], p[maxm], cnt[maxn], ans;
int cur1, h1[maxn], nxt1[maxm], p1[maxm];
double e, ww, w[maxm], f[maxn];
double w1[maxm];
bool tf[maxn];
void add_edge(int x, int y, double z) {
  cur++;
  nxt[cur] = h[x];
  h[x] = cur;
  p[cur] = y;
  w[cur] = z;
}
void add_edge1(int x, int y, double z) {
  cur1++;
  nxt1[cur1] = h1[x];
  h1[x] = cur1;
  p1[cur1] = y;
  w1[cur1] = z;
}
struct node {
  int x;
  double v;
  bool operator<(node a) const { return v + f[x] > a.v + f[a.x]; }
};
priority_queue<node> q;
struct node2 {
  int x;
  double v;
  bool operator<(node2 a) const { return v > a.v; }
} x;
priority_queue<node2> Q;
int main() {
  scanf("%d%d%lf", &n, &m, &e);
  while (m--) {
    scanf("%d%d%lf", &u, &v, &ww);
    add_edge(u, v, ww);
    add_edge1(v, u, ww);
  }
  for (int i = 1; i < n; i++) f[i] = inf;
  Q.push({n, 0});
  while (!Q.empty()) {
    x = Q.top();
    Q.pop();
    if (tf[x.x]) continue;
    tf[x.x] = true;
    f[x.x] = x.v;
    for (int j = h1[x.x]; j; j = nxt1[j]) Q.push({p1[j], x.v + w1[j]});
  }
  k = (int)e / f[1];
  q.push({1, 0});
  while (!q.empty()) {
    node x = q.top();
    q.pop();
    cnt[x.x]++;
    if (x.x == n) {
      e -= x.v;
      if (e < 0) {
        printf("%d\n", ans);
        return 0;
      }
      ans++;
    }
    for (int j = h[x.x]; j; j = nxt[j])
      if (cnt[p[j]] <= k && x.v + w[j] <= e) q.push({p[j], x.v + w[j]});
  }
  printf("%d\n", ans);
  return 0;
}
```
