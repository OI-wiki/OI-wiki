author: abc1763613206, cesonic, Ir1d, MingqiHuang, xinchengo, xiaofu-15191, hsefz-ChenJunJie

## 引入

启发式算法是什么呢？

启发式算法是基于人类的经验和直观感觉，对一些算法的优化。

举个例子，最常见的就是并查集的启发式合并了，代码是这样的：

```cpp
void merge(int x, int y) {
  int xx = find(x), yy = find(y);
  if (size[xx] < size[yy]) swap(xx, yy);
  fa[yy] = xx;
  size[xx] += size[yy];
}
```

在这里，对于两个大小不一样的集合，我们将小的集合合并到大的集合中，而不是将大的集合合并到小的集合中。

为什么呢？这个集合的大小可以认为是集合的高度（在正常情况下），而我们将集合高度小的并到高度大的显然有助于我们找到父亲。

让高度小的树成为高度较大的树的子树，这个优化可以称为启发式合并算法。

## 算法内容

树上启发式合并（dsu on tree）对于某些树上离线问题可以速度大于等于大部分算法且更易于理解和实现的算法。

考虑下面的问题：[树上数颜色](https://www.luogu.com.cn/problem/U41492)。

???+ note "例题引入"
    给出一棵 $n$ 个节点以 $1$ 为根的树，节点 $u$ 的颜色为 $c_u$，现在对于每个节点 $u$ 询问以 $u$ 为根的子树里一共出现了多少种不同的颜色。
    
    $n\le 2\times 10^5$。

![dsu-on-tree-1.png](./images/dsu-on-tree-1.svg)

对于这种问题解决方式大多是运用大量的数据结构（树套树等），如果可以离线，是不是有更简单的方法？

## 过程

既然支持离线，考虑预处理后 $O(1)$ 输出答案。

直接暴力预处理的时间复杂度为 $O(n^2)$，即对每一个子节点进行一次遍历，每次遍历的复杂度显然与 $n$ 同阶，有 $n$ 个节点，故复杂度为 $O(n^2)$。

可以发现，每个节点的答案由其子树和其本身得到，考虑利用这个性质处理问题。

我们可以先预处理出每个节点子树的大小和它的重儿子，重儿子同树链剖分一样，是拥有节点最多子树的儿子，这个过程显然可以 $O(n)$ 完成。

我们用 $cnt_i$ 表示颜色 $i$ 的出现次数，$ans_u$ 表示节点 $u$ 的答案。

遍历一个节点 $u$，我们按以下的步骤进行遍历：

1.  先遍历 $u$ 的轻（非重）儿子，并计算答案，但 **不保留遍历后它对 $cnt$ 数组的影响**；
2.  遍历它的重儿子，**保留它对 $cnt$ 数组的影响**；
3.  再次遍历 $u$ 的轻儿子的子树节点，加入这些节点的贡献，以得到 $u$ 的答案。

![dsu-on-tree-2.png](./images/dsu-on-tree-2.svg)

上图是一个例子。

这样，对于一个节点，我们遍历了一次重子树，两次非重子树，显然是最划算的。

通过执行这个过程，我们获得了这个节点所有子树的答案。

为什么不合并第一步和第三步呢？因为 $cnt$ 数组不能重复使用，否则空间会太大，需要在 $O(n)$ 的空间内完成。

显然若一个节点 $u$ 被遍历了 $x$ 次，则其重儿子会被遍历 $x$ 次，轻儿子（如果有的话）会被遍历 $2x$ 次。

注意除了重儿子，每次遍历完 $cnt$ 要清零。

## 证明

我们像树链剖分一样定义重边和轻边（连向重儿子的为重边，其余为轻边）。关于重儿子和重边的定义，可以见下图，对于一棵有 $n$ 个节点的树：

根节点到树上任意节点的轻边数不超过 $\log n$ 条。我们设根到该节点有 $x$ 条轻边该节点的子树大小为 $y$，显然轻边连接的子节点的子树大小小于父亲的一半（若大于一半就不是轻边了），则 $y<n/2^x$，显然 $n>2^x$，所以 $x<\log n$。

又因为如果一个节点是其父亲的重儿子，则它的子树必定在它的兄弟之中最多，所以任意节点到根的路径上所有重边连接的父节点在计算答案时必定不会遍历到这个节点，所以一个节点的被遍历的次数等于它到根节点路径上的轻边数 $+1$（之所以要 $+1$ 是因为它本身要被遍历到），所以一个节点的被遍历次数 $=\log n+1$, 总时间复杂度则为 $O(n(\log n+1))=O(n\log n)$，输出答案花费 $O(m)$。

![dsu-on-tree-3.png](./images/dsu-on-tree-3.svg)

*图中标粗的即为重边，重边连向的子节点为重儿子*

## 实现

???+ note "实现"
    ```cpp
    #include <cstdio>
    #include <vector>
    using namespace std;
    
    constexpr int N = 2e5 + 5;
    
    int n;
    
    // g[u]: 存储与 u 相邻的节点
    vector<int> g[N];
    
    // sz: 子树大小
    // big: 重儿子
    // col: 节点颜色
    // L[u]: 节点 u 的 DFS 序
    // R[u]: 节点 u 子树中节点的 DFS 序的最大值
    // Node[i]: DFS 序为 i 的节点
    // ans: 存答案
    // cnt[i]: 颜色为 i 的节点个数
    // totColor: 目前出现过的颜色个数
    int sz[N], big[N], col[N], L[N], R[N], Node[N], totdfn;
    int ans[N], cnt[N], totColor;
    
    void add(int u) {
      if (cnt[col[u]] == 0) ++totColor;
      cnt[col[u]]++;
    }
    
    void del(int u) {
      cnt[col[u]]--;
      if (cnt[col[u]] == 0) --totColor;
    }
    
    int getAns() { return totColor; }
    
    void dfs0(int u, int p) {
      L[u] = ++totdfn;
      Node[totdfn] = u;
      sz[u] = 1;
      for (int v : g[u])
        if (v != p) {
          dfs0(v, u);
          sz[u] += sz[v];
          if (!big[u] || sz[big[u]] < sz[v]) big[u] = v;
        }
      R[u] = totdfn;
    }
    
    void dfs1(int u, int p, bool keep) {
      // 计算轻儿子的答案
      for (int v : g[u])
        if (v != p && v != big[u]) {
          dfs1(v, u, false);
        }
      // 计算重儿子答案并保留计算过程中的数据（用于继承）
      if (big[u]) {
        dfs1(big[u], u, true);
      }
      for (int v : g[u])
        if (v != p && v != big[u]) {
          // 子树节点的 DFS 序构成一段连续区间，可以直接遍历
          for (int i = L[v]; i <= R[v]; i++) {
            add(Node[i]);
          }
        }
      add(u);
      ans[u] = getAns();
      if (!keep) {
        for (int i = L[u]; i <= R[u]; i++) {
          del(Node[i]);
        }
      }
    }
    
    int main() {
      scanf("%d", &n);
      for (int i = 1; i < n; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        g[u].push_back(v);
        g[v].push_back(u);
      }
      for (int i = 1; i <= n; i++) scanf("%d", &col[i]);
      dfs0(1, 0);
      dfs1(1, 0, false);
      scanf("%d", &m);
      for (int i = 1; i <= m; i++) {
        int q; scanf("%d", &q);
        printf("%d\n", ans[q]);
      }
      return 0;
    }
    ```

## 优化

在证明过程中我们提到了 dsu on tree 使用了和重链剖分一样的轻重儿子定义加速合并，既然如此，我们也可以直接利用重链剖分得到的 dfs 序，化递归为迭代，进一步加速 dsu on tree 的合并过程。

dfs 序本身就有如下的性质：一个节点的子树在 dfs 序上一定连续。因此，我们想到可以倒序遍历 dfs 序数组，这样保证了在遍历到一个节点时，他的子树中的其他节点一定已经得到了处理。

重链剖分得到的 dfs 序又增加了如下优良的性质：一条重链在 dfs 序上一定是连续的。因此，我们倒序遍历一个数组时，在到达一条重链顶端时，我们要遍历的下一个节点一定不是自己的父亲，所以要清空自己的影响；在到达一条重链的顶端之前，之前遍历的一个节点一定是自己的重儿子（或者是已经清除了影响的其他分支的节点），所以可以直接继承其影响。在此基础上，再利用 dfs 序快速统计所有轻儿子的影响，记录答案。

以上过程被称为 dsu on tree 的非递归/迭代实现（也被称为 dsu on tree 的 dfs 序实现）。相较于原本递归实现，它减小了递归调用函数的时空开销，获得了不小的常数优化，在处理包含大量链状树的数据时拥有显著的栈空间优势。

???+ note "具体代码实现"
    ```cpp
    #include <cstdio>
    #include <vector>
    using namespace std;

    constexpr int N = 2e5 + 5;

    int n, m;

    // g[u]: 存储与 u 相邻的节点
    vector<int> g[N];

    // sz: 子树大小
    // son[u]: 节点u的重儿子的编号
    // col: 节点颜色
    // dfn[u]: 节点 u 的 DFS 序
    // bottom[u]: 节点 u 子树中节点的 DFS 序的最大值
    // fa[u]: 节点u的父亲编号
    // top[u]:节点u所在重链的顶端节点编号
    // rnk[i]: DFS 序为 i 的节点
    // ans[u]: 存答案
    // cnt[i]: 颜色为 i 的节点个数
    // totColor: 目前出现过的颜色个数
    int sz[N], son[N], col[N], dfn[N], fa[N], bottom[N];
    int top[N], rnk[N];
    int ans[N], cnt[N], totColor;

    void add(int u) {
      if (cnt[col[u]] == 0) ++totColor;
      cnt[col[u]]++;
    }

    void del(int u) {
      cnt[col[u]]--;
      if (cnt[col[u]] == 0) --totColor;
    }

    int getAns() { return totColor; }

    void dfs0(int u, int p) {
      sz[u] = 1;
      fa[u] = p;
      for (int v : g[u])
        if (v != p) {
          dfs0(v, u);
          sz[u] += sz[v];
          if (!son[u] || sz[son[u]] < sz[v]) son[u] = v;
        }
    }

    void dfs1(int u, int t) {
      rnk[bottom[u] = dfn[u] = ++ dfn[0]] = u;
      top[u] = t;
      if (!son[u]) return;
      dfs1(son[u], t);
      for (int v : g[u])
        if (v != fa[u] && v != son[u]) dfs1(v, v);
      bottom[u] = dfn[0];
    }

    void dsu_on_tree() {
      for (int i = dfn[0]; i >= 1; i--) {
        int u = rnk[i];
        for (int v : g[u])
          if (v != fa[u] && v != son[u]) {
            for (int i = dfn[v]; i <= bottom[v]; i++) {
              add(rnk[i]);
            }
          }
        add(u);
        ans[u] = getAns();
        if (u == top[u]) {
          for (int i = dfn[u]; i <= bottom[u]; i++) {
            del(rnk[i]);
          }
        }
      }
    }

    int main() {
      scanf("%d", &n);
      for (int i = 1; i < n; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        g[u].push_back(v);
        g[v].push_back(u);
      }
      for (int i = 1; i <= n; i++) scanf("%d", &col[i]);
      dfs0(1, 1);
      dfs1(1, 1);
      dsu_on_tree();
      scanf("%d", &m);
      for (int i = 1; i <= m; i++) {
        int q; scanf("%d", &q);
        printf("%d\n", ans[q]);
      }
      return 0;
    }
    ```

## 运用

1.  某些出题人设置的正解是 dsu on tree 的题

    如 [CF741D](http://codeforces.com/problemset/problem/741/D)。给一棵树，每个节点的权值是'a' 到'v' 的字母，每次询问要求在一个子树找一条路径，使该路径包含的字符排序后成为回文串。

    因为是排列后成为回文串，所以一个字符出现了两次相当于没出现，也就是说，这条路径满足 **最多有一个字符出现奇数次**。

    正常做法是对每一个节点 dfs，每到一个节点就强行枚举所有字母找到和它异或后结果为 1 的个数大于 1 的路径，再取最长值，这样是 $O(n^2\log n)$ 的，可以用 dsu on tree 优化到 $O(n\log^2n)$。关于具体做法，可以参考下面的扩展阅读。

2.  可以用 dsu 乱搞的题

    可以水一些树套树的部分分（没有修改操作），而且 dsu 的复杂度优于树上莫队的 $O(n\sqrt{m})$。

## 练习题

[CF600E Lomsat gelral](http://codeforces.com/problemset/problem/600/E)

题意翻译：树的节点有颜色，一种颜色占领了一个子树，当且仅当没有其他颜色在这个子树中出现得比它多。求占领每个子树的所有颜色之和。

[UOJ284 快乐游戏鸡](https://uoj.ac/problem/284)

[CF1709E XOR Tree](https://codeforces.com/contest/1709/problem/E)

## 参考资料/扩展阅读

[CF741D 作者介绍的 dsu on tree](http://codeforces.com/blog/entry/44351)

[这位作者的题解](http://codeforces.com/blog/entry/48871)
