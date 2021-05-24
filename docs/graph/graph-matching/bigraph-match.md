author: accelsao, thallium, Chrogeek, Enter-tainer, ksyx, StudyingFather, H-J-Granger, Henry-ZHR, countercurrent-time, william-song-shy

为了描述方便将两个集合分成左和右两个部分，所有匹配边都是横跨左右两个集合，可以假想成男女配对。

假设图有 $n$ 个顶点，$m$ 条边。

## 增广路算法 Augmenting Path Algorithm

因为增广路长度为奇数，路径起始点非左即右，所以我们先考虑从左边的未匹配点找增广路。
注意到因为交错路的关系，增广路上的第奇数条边都是非匹配边，第偶数条边都是匹配边，于是左到右都是非匹配边，右到左都是匹配边。
于是我们给二分图 **定向**，问题转换成，有向图中从给定起点找一条简单路径走到某个未匹配点，此问题等价给定起始点 $s$ 能否走到终点 $t$。
那么只要从起始点开始 DFS 遍历直到找到某个未匹配点，$O(m)$。
未找到增广路时，我们拓展的路也称为 **交错树**。

因为要枚举 $n$ 个点，总复杂度为 $O(nm)$。

### 代码

```cpp
struct augment_path {
  vector<vector<int> > g;
  vector<int> pa;  // 匹配
  vector<int> pb;
  vector<int> vis;  // 访问
  int n, m;         // 两个点集中的顶点数量
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
```

## 转为网络最大流模型

二分图最大匹配可以转换成网络流模型。

将左边所有点接上源点，右边所有点接上汇点，容量皆为 $1$。原来的每条边从左往右连边，容量也皆为 $1$，最大流即最大匹配。

如果使用 [Dinic 算法](../../graph/flow/max-flow.md#dinic) 求该网络的最大流，可在 $O(\sqrt{n}m)$ 求出。

Dinic 算法分成两部分，第一部分用 $O(m)$ 时间 BFS 建立网络流，第二步是 $O(nm)$ 时间 DFS 进行增广。

但因为容量为 $1$，所以实际时间复杂度为 $O(m)$。

接下来前 $O(\sqrt{n})$ 轮，复杂度为 $O(\sqrt{n}m)$。$O(\sqrt{n})$ 轮以后，每条增广路径长度至少 $\sqrt{n}$，而这样的路径不超过 $\sqrt{n}$，所以此时最多只需要跑 $\sqrt{n}$ 轮，整体复杂度为 $O(\sqrt{n}m)$。

代码可以参考 [Dinic 算法](../../graph/flow/max-flow.md#dinic) 的参考实现，这里不再给出。

## 补充

### 二分图最大独立集

选最多的点，满足两两之间没有边相连。

二分图中，最大独立集 =$n$- 最大匹配。

### 二分图最小点覆盖

选最少的点，满足每条边至少有一个端点被选，不难发现补集是独立集。

二分图中，最小点覆盖 =$n$- 最大独立集。

## 习题

??? note "[UOJ #78. 二分图最大匹配](https://uoj.ac/problem/78) "
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

??? note "[P1640 [SCOI2010]连续攻击游戏](https://www.luogu.com.cn/problem/P1640) "
    关键在于建图。我们建立每个物品两个属性值连向其编号的单向边。因为属性值一定是连续的，所以我们从小到大枚举属性值依次判断是否可以匹配，若枚举到 $i$ 时无法匹配，则最多只能攻击 $i-1$ 次。
    
    ```cpp
    #include <bits/stdc++.h>
    using namespace std;
    typedef long long ll;
    
    const int N = 1e6 + 7;
    int n, maxn, book[N], match[N];
    struct edge {
      int to, nxt;
    } e[N * 2];
    int cnt, he[N];
    
    void add(int u, int v) {
      e[++cnt].to = v;
      e[cnt].nxt = he[u];
      he[u] = cnt;
    }
    
    bool dfs(int u, int tag) {  //二分图匹配
      if (book[u] == tag) return false;
      book[u] = tag;
      for (int i = he[u]; i; i = e[i].nxt) {
        int v = e[i].to;
        if (!match[v] || dfs(match[v], tag)) {
          match[v] = u;
          return true;
        }
      }
      return false;
    }
    
    int main() {
      scanf("%d", &n);
      for (int i = 1; i <= n; i++) {
        int x, y;
        scanf("%d%d", &x, &y);
        add(x, i), add(y, i);
        maxn = max(maxn, max(x, y));
      }
      for (int i = 1; i <= maxn + 1; i++)
        if (!dfs(i, i)) return printf("%d", i - 1), 0;
    }
    ```

??? note "[Codeforces 1139E - Maximize Mex](https://codeforces.com/problemset/problem/1139/E) "
    建立每个学生能力值连向其社团编号的单向边。求 $\operatorname{mex}$ 的最大值只需从小到大枚举能力值判断是否可以匹配，当我们枚举到 $i$ 时，若其无法匹配，则 $\operatorname{mex}$ 的最大值即为 $i$。
    
    每天都有学生退出社团，我们很难维护这种操作，正难则反，我们倒序枚举删去的学生，统计完当天的答案后，就将当前枚举的学生加入图中。注意匹配和标记数组初始化应为 $-1$，因为 $0$ 也是能力值。
    
    ```cpp
    #include <bits/stdc++.h>
    using namespace std;
    typedef long long ll;
    
    inline ll read() {
      ll sum = 0, ff = 1;
      char ch = getchar();
      while (ch < '0' || ch > '9') {
        if (ch == '-') ff = -1;
        ch = getchar();
      }
      while (ch >= '0' && ch <= '9') sum = sum * 10 + ch - '0', ch = getchar();
      return sum * ff;
    }
    
    void write(ll x) {
      if (x < 0) putchar('-'), x = -x;
      if (x > 9) write(x / 10);
      putchar(x % 10 + '0');
    }
    
    const int N = 1e4 + 7;
    int n, m, d, maxn, p[N], c[N], k[N], match[N], book[N], ans[N];
    bool vis[N];
    struct edge {
      int to, nxt;
    } e[N];
    int cnt, he[N];
    
    void add(int u, int v) {
      e[++cnt].to = v;
      e[cnt].nxt = he[u];
      he[u] = cnt;
    }
    
    bool dfs(int u, int tag) {
      if (book[u] == tag) return false;
      book[u] = tag;
      for (int i = he[u]; i; i = e[i].nxt) {
        int v = e[i].to;
        if (match[v] == -1 || dfs(match[v], tag)) {
          match[v] = u;
          return true;
        }
      }
      return false;
    }
    ```

    int main() {
        //	freopen("", "r", stdin);
        //	freopen("", "w", stdout);
        n = read(), m = read();
        for(int i = 1; i <= n; i++)
            p[i] = read(), maxn = max(maxn, p[i]);
        for(int i = 1; i <= n; i++)
            c[i] = read();
        d = read();
        for(int i = 1; i <= d; i++)
            k[i] = read(), vis[k[i]] = true;
        for(int i = 1; i <= n; i++)
            if(!vis[i])
                add(p[i], c[i]);
        for(int i = d; i >= 1; i--) {
            memset(match, -1, sizeof(match));
            memset(book, -1, sizeof(book));
            int mex = 0;
            for(int j = 0; j <= maxn + 1; j++)
            if(!dfs(j, j)) {
                mex = j;
                break;
            }
            ans[i] = mex;
            add(p[k[i]], c[k[i]]);
        }
        for(int i = 1; i <= d; i++)
            write(ans[i]), puts("");
        return 0;
    }
    ```
