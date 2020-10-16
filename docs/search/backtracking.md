本页面将简要介绍回溯法的概念和应用。

## 简介

回溯法是一种经常被用在 [深度优先搜索（DFS）](dfs.md) 和 [广度优先搜索（BFS）](bfs.md) 的技巧。

其本质是：走不通就回头。

## 工作原理

1. 构造空间树；

2. 进行遍历；

3. 如遇到边界条件，即不再向下搜索，转而搜索另一条链；

4. 达到目标条件，输出结果。

## 例题

???+ note "[USACO 1.5.4 Checker Challenge](https://www.luogu.com.cn/problem/P1219)"
    检查一个如下的 $6 \times 6$ 的跳棋棋盘，有六个棋子被放置在棋盘上，使得每行，每列，每条对角线（包括两条主对角线的所有对角线）上都至多有一个棋子。
    
    列号
    
        0   1   2   3   4   5   6
          -------------------------
        1 |   | O |   |   |   |   |
          -------------------------
        2 |   |   |   | O |   |   |
          -------------------------
        3 |   |   |   |   |   | O |
          -------------------------
        4 | O |   |   |   |   |   |
          -------------------------
        5 |   |   | O |   |   |   |
          -------------------------
        6 |   |   |   |   | O |   |
          -------------------------
    
    上面的布局可以用序列 $\{2,4,6,1,3,5\}$ 来描述，第 $i$ 个数字表示在第 $i$ 行的相应位置有一个棋子，如下：
    
    行号 $1 2 3 4 5 6$ 
    
    列号 $2 4 6 1 3 5$ 
    
    这只是跳棋放置的一个解。请遍一个程序找出所有跳棋放置的解。并把它们以上面的序列方法输出。解按字典顺序排列。请输出前 $3$ 个解。最后一行是解的总个数。特别注意：对于更大的 $N$ （棋盘大小 $N \times N$ ）你的程序应当改进得更有效。

??? note "参考代码"
    ```cpp
    // 该代码为回溯法的 DFS 实现
    #include <cstdio>
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

* * *

???+note "[迷宫](https://www.luogu.com.cn/problem/P1605)"
    给定一个 $N \times M$ 方格的迷宫，迷宫里有 $T$ 处障碍，障碍处不可通过。给定起点坐标和终点坐标，问：每个方格最多经过 $1$ 次，有多少种从起点坐标到终点坐标的方案。在迷宫中移动有上下左右四种方式，每次只能移动一个方格。数据保证起点上没有障碍。

??? note "参考代码"
    ```cpp
    // 该代码为回溯法的 BFS 实现
    #include <cstdio>
    #include <queue>
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
