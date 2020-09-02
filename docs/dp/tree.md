在学习本章前请确认你已经学习了 [动态规划基础](./basic.md) 

树形 DP，即在树上进行的 DP。由于树固有的递归性质，树形 DP 一般都是递归进行的。

## 基础

以下面这道题为例，介绍一下树形 DP 的一般过程。

???+note " 例题[洛谷 P1352 没有上司的舞会](https://www.luogu.com.cn/problem/P1352)"
    某大学有 $n$ 个职员，编号为 $1 \sim N$ 。他们之间有从属关系，也就是说他们的关系就像一棵以校长为根的树，父结点就是子结点的直接上司。现在有个周年庆宴会，宴会每邀请来一个职员都会增加一定的快乐指数 $a_i$ ，但是呢，如果某个职员的上司来参加舞会了，那么这个职员就无论如何也不肯来参加舞会了。所以，请你编程计算，邀请哪些职员可以使快乐指数最大，求最大的快乐指数。

我们可以定义 $f(i,0/1)$ 代表以 $i$ 为根的子树的最优解（第二维的值为 0 代表 $i$ 不参加舞会的情况，1 代表 $i$ 参加舞会的情况）。

显然，我们可以推出下面两个状态转移方程（其中下面的 $x$ 都是 $i$ 的儿子）：

-  $f(i,0) = \sum\max \{f(x,1),f(x,0)\}$ （上司不参加舞会时，下属可以参加，也可以不参加）
-  $f(i,1) = \sum{f(x,0)} + a_i$ （上司参加舞会时，下属都不会参加）

我们可以通过 DFS，在返回上一层时更新当前节点的最优解。

代码：

```cpp
#include <algorithm>
#include <cstdio>
using namespace std;
struct edge {
  int v, next;
} e[6005];
int head[6005], n, cnt, f[6005][2], ans, is_h[6005], vis[6005];
void addedge(int u, int v) {
  e[++cnt].v = v;
  e[cnt].next = head[u];
  head[u] = cnt;
}
void calc(int k) {
  vis[k] = 1;
  for (int i = head[k]; i; i = e[i].next) {  // 枚举该节点的每个子节点
    if (vis[e[i].v]) continue;
    calc(e[i].v);
    f[k][1] += f[e[i].v][0];
    f[k][0] += max(f[e[i].v][0], f[e[i].v][1]);
  }
  return;
}
int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) scanf("%d", &f[i][1]);
  for (int i = 1; i < n; i++) {
    int l, k;
    scanf("%d%d", &l, &k);
    is_h[l] = 1;
    addedge(k, l);
  }
  for (int i = 1; i <= n; i++)
    if (!is_h[i]) {  // 从根节点开始DFS
      calc(i);
      printf("%d", max(f[i][1], f[i][0]));
      return 0;
    }
}
```

## 树上背包

树上的背包问题，简单来说就是背包问题与树形 DP 的结合。

???+note "例题[洛谷 P2014 CTSC1997 选课]"
    现在有 $n$ 门课程，第 $i$ 门课程的学分为 $a_i$ ，每门课程有零门或一门先修课，有先修课的课程需要先学完其先修课，才能学习该课程。
    
    一位学生要学习 $m$ 门课程，求其能获得的最多学分数。
    
     $n,m \leq 300$ 

每门课最多只有一门先修课的特点，与有根树中一个点最多只有一个父亲节点的特点类似。

因此可以想到根据这一性质建树，从而所有课程组成了一个森林的结构。为了方便起见，我们可以新增一门 $0$ 学分的课程（设这个课程的编号为 $0$ ），作为所有无先修课课程的先修课，这样我们就将森林变成了一棵以 $0$ 号课程为根的树。

我们设 $f(u,i,j)$ 表示以 $u$ 号点为根的子树中，已经遍历了 $u$ 号点的前 $i$ 棵子树，选了 $j$ 门课程的最大学分。

转移的过程结合了树形 DP 和背包 DP 的特点，我们枚举 $u$ 点的每个子节点 $v$ ，同时枚举以 $v$ 为根的子树选了几门课程，将子树的结果合并到 $u$ 上。

记点 $x$ 的儿子个数为 $s_x$ ，以 $x$ 为根的子树大小为 $\textit{siz_x}$ ，很容易写出下面的转移方程：

$$
f(u,i,j)=\max_{v,k \leq j,k \leq \textit{siz_v}} f(u,i-1,j-k)+f(v,s_v,k)
$$

注意上面转移方程中的几个限制条件，这些限制条件确保了一些无意义的状态不会被访问到。

 $f$ 的第二维可以很轻松地用滚动数组的方式省略掉，注意这时需要倒序枚举 $j$ 的值。

我们可以证明，该做法的时间复杂度为 $O(nm)$ [^note1]。

??? note "参考代码"
    ```cpp
    #include <algorithm>
    #include <cstdio>
    #include <vector>
    using namespace std;
    int f[305][305], s[305], n, m;
    vector<int> e[305];
    int dfs(int u) {
      int p = 1;
      f[u][1] = s[u];
      for (auto v : e[u]) {
        int siz = dfs(v);
        // 注意下面两重循环的上界和下界
        // 只考虑已经合并过的子树，以及选的课程数超过 m+1 的状态没有意义
        for (int i = min(p, m + 1); i; i--)
          for (int j = 1; j <= siz && i + j <= m + 1; j++)
            f[u][i + j] = max(f[u][i + j], f[u][i] + f[v][j]);
        p += siz;
      }
      return p;
    }
    int main() {
      scanf("%d%d", &n, &m);
      for (int i = 1; i <= n; i++) {
        int k;
        scanf("%d%d", &k, &s[i]);
        e[k].push_back(i);
      }
      dfs(0);
      printf("%d", f[0][m + 1]);
      return 0;
    }
    ```

## 习题

-  [HDU 2196 Computer](http://acm.hdu.edu.cn/showproblem.php?pid=2196) 
-  [POJ 1463 Strategic game](http://poj.org/problem?id=1463) 
-  [POJ 3585 Accumulation Degree](http://poj.org/problem?id=3585) 

## 参考资料与注释

[^note1]:  [子树合并背包类型的 dp 的复杂度证明 - LYD729 的 CSDN 博客](https://blog.csdn.net/lyd_7_29/article/details/79854245) 
