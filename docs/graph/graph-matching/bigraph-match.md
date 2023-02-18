author: accelsao, thallium, Chrogeek, Enter-tainer, ksyx, StudyingFather, H-J-Granger, Henry-ZHR, countercurrent-time, william-song-shy, 5ab-juruo, XiaoQuQuSD

为了描述方便将两个集合分成左和右两个部分，所有匹配边都是横跨左右两个集合，可以假想成男女配对。

假设图有 $n$ 个顶点，$m$ 条边。

## 题目描述

给定一个二分图 $G$，即分左右两部分，各部分之间的点没有边连接，要求选出一些边，使得这些边没有公共顶点，且边的数量最大。

## 匈牙利算法

匈牙利算法，是一种解决二分图最大匹配问题的算法。

首先我们要知道什么是二分图：

二分图是一种奇妙的图，它满足可以把其内部的节点划分成两个集合，且这每个集合内部的的点没有边相连。

![这就是一个二分图](https://photo-1314795557.cos.ap-beijing.myqcloud.com/image-20230216092910554.png)

知道了二分图是什么，我们还需要知道“匹配”是什么。我们称图 $G$ 的一个匹配是由一组没有公共端点的边的集合。最大匹配包含的边数即为最大匹配。

归纳一下，对于一个匹配有两点要求：

-   匹配是边的集合
-   在匹配中，任意两边不能有公共顶点

然后我们就可以开始解决二分图的最大匹配问题啦！

我们形象地描述一下这个问题，对于上面的二分图，$U$ 表示男生，$V$ 表示女生，两集合中点之间的边表示两人有暧昧关系，作为一名单身狗，你的目的是尽可能多地撮合情侣，这就是找最大匹配的过程。但是注意，如果一个人已经有了男/女朋友就不能在找别的了，这就是要满足“任意两边不能有公共顶点”。

下面模拟匈牙利算法的过程：

1.  $U$ 中的第一个 $U_1$ 寻求匹配，发现只能到 $V_1$，所以这一对可以；
2.  再看 $U_2$，发现它可以到 $V_1$ 和 $V_2$，但是 $V_1$ 已经有男朋友了，虽然 $U_2$ 是海王但是它不会抢别人的女友，并且 $U_1$ 只能和 $V_1$ 在一起，所以 $U_2$ 只好去找 $V_2$ 了；
3.  再看 $U_3$，发现它可以到 $V_3$ 和 $V_4$，这两个人都没有男朋友，所以先假设 $U_3$ 和 $V_3$ 在一起了。
4.  再看 $U_4$，发现它只能到 $V_2$，可是 $V_2$ 已经名花有主了，考虑让 $U_2$ 换一个目标，但是 $U_2$ 的另一个暧昧对象已经给 $U_1$，根据“先来后到”原则，$U_4$ 就和我们一样注定单身了；
5.  最后看 $U_5$，可以到 $V_1$ 和 $V_5$，$V_5$ 刚好没有男朋友，所以 $U_5$ 就开开心心地抱得美人（V\_5）归了。

这样一模拟，就是匈牙利算法的过程。

具体代码实现如下（用的是更常用的链前写法）：

> [练手板子题](https://www.luogu.com.cn/problem/P3386)

```cpp
#include <bits/stdc++.h>
using namespace std;

const int maxn = 5e4 + 5;
int head[maxn], nxt[maxn], to[maxn], vis[maxn], cnt,
    match[505] /*表示右边点对应左边的cp*/, m, n, e;

void add(int x, int y) {
  to[++cnt] = y;
  nxt[cnt] = head[x];
  head[x] = cnt;
}

bool dfs(int now)  // 找对象
{
  for (int i = head[now]; i; i = nxt[i]) {
    if (vis[to[i]]) continue;
    vis[to[i]] = 1;
    if (!match[to[i]] ||
        dfs(match
                [to[i]]))  // 想找的对象没有男朋友或者这个对象的当前男朋友还可以找别的女朋友
    {
      match[to[i]] = now;  // 左侧元素和当前的右侧元素形成匹配
      return 1;
    }
  }
  return 0;
}

void gett() {
  int ans = 0;
  for (int i = 1; i <= n; i++) {
    memset(vis, 0, sizeof(vis));
    if (dfs(i)) ans++;
  }
  cout << ans;
}

int main() {
  cin >> n >> m >> e;
  for (int i = 1; i <= e; i++) {
    int u, v;
    cin >> u >> v;
    add(u, v);
  }
  gett();
  return 0;
}
```

## 转为网络最大流模型

二分图最大匹配可以转换成网络流模型。

将源点连上左边所有点，右边所有点连上汇点，容量皆为 $1$。原来的每条边从左往右连边，容量也皆为 $1$，最大流即最大匹配。

如果使用 [Dinic 算法](../flow/max-flow.md#dinic-算法) 求该网络的最大流，可在 $O(\sqrt{n}m)$ 求出。

Dinic 算法分成两部分，第一部分用 $O(m)$ 时间 BFS 建立网络流，第二步是 $O(nm)$ 时间 DFS 进行增广。

但因为容量为 $1$，所以实际时间复杂度为 $O(m)$。

接下来前 $O(\sqrt{n})$ 轮，复杂度为 $O(\sqrt{n}m)$。$O(\sqrt{n})$ 轮以后，每条增广路径长度至少 $\sqrt{n}$，而这样的路径不超过 $\sqrt{n}$，所以此时最多只需要跑 $\sqrt{n}$ 轮，整体复杂度为 $O(\sqrt{n}m)$。

代码可以参考 [Dinic 算法](../flow/max-flow.md#dinic-算法) 的参考实现，这里不再给出。

## 补充

### 二分图最小点覆盖（König 定理）

最小点覆盖：选最少的点，满足每条边至少有一个端点被选。

二分图中，最小点覆盖 $=$ 最大匹配。

???+ note "证明"
    将二分图点集分成左右两个集合，使得所有边的两个端点都不在一个集合。
    
    考虑如下构造：从左侧未匹配的节点出发，按照匈牙利算法中增广路的方式走，即先走一条未匹配边，再走一条匹配边。由于已经求出了最大匹配，所以这样的增广路一定以匹配边结束。在所有经过这样“增广路”的节点上打标记。则最后构造的集合是：所有左侧未打标记的节点和所有右侧打了标记的节点。
    
    首先，易证这个集合的大小等于最大匹配。打了标记的节点一定都是匹配边上的点，一条匹配的边两侧一定都有标记（在增广路上）或都没有标记，所以两个节点中必然有一个被选中。
    
    其次，这个集合是一个点覆盖。一条匹配边一定有一个点被选中，而一条未匹配的边一定是增广路的一部分，而右侧端点也一定被选中。
    
    同时，不存在更小的点覆盖。为了覆盖最大匹配的所有边，至少要有最大匹配边数的点数。

### 二分图最大独立集

最大独立集：选最多的点，满足两两之间没有边相连。

因为在最小点覆盖中，任意一条边都被至少选了一个顶点，所以对于其点集的补集，任意一条边都被至多选了一个顶点，所以不存在边连接两个点集中的点，且该点集最大。因此二分图中，最大独立集 $=n-$ 最小点覆盖。

## 习题

??? note "[UOJ #78. 二分图最大匹配](https://uoj.ac/problem/78)"
    模板题
    
    ```cpp
    #include <bits/stdc++.h>
    using namespace std;
    
    struct augment_path {
      vector<vector<int> > g;
      vector<int> pa;  // 匹配
      vector<int> pb;
      vector<int> vis;  // 访问
      int n, m;         // 顶点和边的数量
      int dfn;          // 时间戳记
      int res;          // 匹配数
    
      augment_path(int _n, int _m) : n(_n), m(_m) {
        assert(0 <= n && 0 <= m);
        pa = vector<int>(n, -1);
        pb = vector<int>(m, -1);
        vis = vector<int>(n);
        g.resize(n);
        res = 0;
        dfn = 0;
      }
    
      void add(int from, int to) {
        assert(0 <= from && from < n && 0 <= to && to < m);
        g[from].push_back(to);
      }
    
      bool dfs(int v) {
        vis[v] = dfn;
        for (int u : g[v]) {
          if (pb[u] == -1) {
            pb[u] = v;
            pa[v] = u;
            return true;
          }
        }
        for (int u : g[v]) {
          if (vis[pb[u]] != dfn && dfs(pb[u])) {
            pa[v] = u;
            pb[u] = v;
            return true;
          }
        }
        return false;
      }
    
      int solve() {
        while (true) {
          dfn++;
          int cnt = 0;
          for (int i = 0; i < n; i++) {
            if (pa[i] == -1 && dfs(i)) {
              cnt++;
            }
          }
          if (cnt == 0) {
            break;
          }
          res += cnt;
        }
        return res;
      }
    };
    
    int main() {
      int n, m, e;
      cin >> n >> m >> e;
      augment_path solver(n, m);
      int u, v;
      for (int i = 0; i < e; i++) {
        cin >> u >> v;
        u--, v--;
        solver.add(u, v);
      }
      cout << solver.solve() << "\n";
      for (int i = 0; i < n; i++) {
        cout << solver.pa[i] + 1 << " ";
      }
      cout << "\n";
    }
    ```

??? note "[P1640 \[SCOI2010\] 连续攻击游戏](https://www.luogu.com.cn/problem/P1640)"
    None

??? note "[Codeforces 1139E - Maximize Mex](https://codeforces.com/problemset/problem/1139/E)"
    None

## 参考资料

1.  <http://www.matrix67.com/blog/archives/116>
