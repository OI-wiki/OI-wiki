## 概念表述

回溯法是一种经常被用在深度深度优先搜索（DFS）和广度优先搜索（BFS）的技巧。

其本质是：走不通就回头。

## 实现过程

1\. 构造空间树。

2\. 进行遍历。

3\. 如遇到边界条件，即不再向下搜索，转而搜索另一条链。

4\. 达到目标条件，输出结果。

## 经典例题：

### DFS 实现

八皇后问题（USACO 版本）的回溯代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
int ans[14], check[3][28] = {0}, sum = 0, n;
void eq(int line) {
  if (line > n) {
    sum++;
    if (sum > 3)
      return;
    else {
      for (int i = 1; i <= n; i++) printf("%d ", ans[i]);
      printf("\n");
      return;
    }
  }
  for (int i = 1; i <= n; i++) {
    if ((!check[0][i]) && (!check[1][line + i]) && (!check[2][line - i + n])) {
      ans[line] = i;
      check[0][i] = 1;
      check[1][line + i] = 1;
      check[2][line - i + n] = 1;
      eq(line + 1);
      check[0][i] = 0;
      check[1][line + i] = 0;
      check[2][line - i + n] = 0;
    }
  }
}
int main() {
  scanf("%d", &n);
  eq(1);
  printf("%d", sum);
  return 0;
}
```

### BFS 实现

迷宫问题（USACO 版本）的回溯代码：

```cpp
using namespace std;
int n, m, k, x, y, a, b, ans;
int dx[4] = {0, 0, 1, -1}, dy[4] = {1, -1, 0, 0};
bool vis[6][6];
struct oo {
  int x, y, used[6][6];
};

oo sa;

void bfs() {
  queue<oo> q;
  sa.x = x;
  sa.y = y;
  sa.used[x][y] = 1;
  q.push(sa);
  while (!q.empty()) {
    oo now = q.front();
    q.pop();
    for (int i = 0; i < 4; i++) {
      int sx = now.x + dx[i];
      int sy = now.y + dy[i];
      if (now.used[sx][sy] || vis[sx][sy] || sx == 0 || sy == 0 || sx > n ||
          sy > m)
        continue;
      if (sx == a && sy == b) {
        ans++;
        continue;
      }
      sa.x = sx;
      sa.y = sy;
      memcpy(sa.used, now.used, sizeof(now.used));
      sa.used[sx][sy] = 1;
      q.push(sa);
    }
  }
}

int main() {
  scanf("%d%d%d", &n, &m, &k);
  scanf("%d%d%d%d", &x, &y, &a, &b);
  for (int i = 1, aa, bb; i <= k; i++) {
    scanf("%d%d", &aa, &bb);
    vis[aa][bb] = 1;
  }
  bfs();
  printf("%d", ans);
  return 0;
}
```
