author: accelsao

# 二分图最大匹配

为了描述方便将两个集合分成左和右两个部分，所有匹配边都是横跨左右两个集合，可以假想成男女配对。

假设图有 $n$ 个顶点， $m$ 条边。

## 增广路算法 Augmenting Path Algorithm

因为增广路长度为奇数，路径起始点非左即右，不失一般性考虑从左边的未匹配点找增广路。
注意到因为交错路的关系，奇数次都是走非匹配边，偶数次走匹配边，于是左到右都是非匹配边，右到左都是匹配边。
于是我们给二分图 **定向** ，问题转换成，有向图中从给定起点找一条简单路径走到某个未匹配点，此问题等价给定起始点 $s$ 能否走到终点 $t$ 。
那么只要从起始点开始 DFS 遍历直到找到某个未匹配点， $O(m)$ 。
未找到增广路时，我们拓展的路也称为 **交错树** 。

因为要枚举 $n$ 个点，总复杂度为 $O(nm)$ 。

### 代码

```cpp
struct augment_path {
  vector<vector<int> > g;
  vector<int> pa;  // 匹配
  vector<int> pb;
  vector<int> vis;  // 访问
  int n, m;         // 顶点数量
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

## Dinic 算法

二分图最大匹配可以转换成网路流模型。
将左边所有点接上源点，右边所有点接上汇点，容量皆为 $1$ 。
原来的每条边从左往右连边，容量耶皆为 $1$ ，最大流即最大匹配，可在 $O(\sqrt{n}m)$ 求出。

Dinic 算法分成两部分，第一部分用 $O(m)$ 时间 BFS 建立网路流，第二步是 $O(nm)$ 时间 DFS 进行增广。
但因为容量为 $1$ ，这边只需要 $O(m)$ 。
接下来前 $O(\sqrt{n})$ 轮，复杂度为 $O(\sqrt{n}m)$ 。 $O(\sqrt{n})$ 轮以后，每条增广路径长度至少 $\sqrt{n}$ ，而这样的路径不超过 $\sqrt{n}$ ，
所以最多也只剩下 $\sqrt{n}$ 轮需要跑，整体复杂度为 $O(\sqrt{n}m)$ 。

### 代碼

待補。

## 补充

### 二分图最大独立集

选最多的点，满足两两之间没有边相连。

二分图中，最大独立集 = $n$ - 最大匹配。

### 二分图最小点复盖

选最少的点，满足每条边至少有一个端点被选，不难发现补集是独立集。

二分图中，最小点复盖 = $n$ - 最大独立集。

## 习题

??? note "[UOJ #78. 二分图最大匹配](http://uoj.ac/problem/78) "

    模板题
    ```cpp
    #include <bits/stdc++.h>
    using namespace std;

    struct augment_path {
      vector< vector<int> > g;
      vector<int> pa; // 匹配
      vector<int> pb;
      vector<int> vis; // 访问
      int n, m; // 顶点数量
      int dfn; // 时间戳记
      int res; // 匹配数

      augment_path(int _n, int _m) : n(_n), m(_m) {
    	assert(0 <= n && 0 <= m);
    	pa = vector<int> (n, -1);
    	pb = vector<int> (m, -1);
    	vis = vector<int> (n);
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
    	for(int u: g[v]) {
    	  if(pb[u] == -1) {
    		pb[u] = v;
    		pa[v]= u;
    		return true;
    	  }
    	}
    	for(int u: g[v]) {
    	  if(vis[pb[u]] != dfn && dfs(pb[u])) {
    		pa[v] = u;
    		pb[u] = v;
    		return true;
    	  }
    	}
    	return false;
      }

      int solve() {
    	while(true) {
    	  dfn++;
    	  int cnt = 0;
    	  for(int i = 0; i < n; i++) {
    		if(pa[i] == -1 && dfs(i)) {
    		  cnt++;
    		}
    	  }
    	  if(cnt == 0) {
    		break;
    	  }
    	  res += cnt;
    	}
    	return res;
      }
    };

    int main(){
    	int n, m, e;
    	cin >> n >> m >> e;
    	augment_path solver(n, m);
    	int u, v;
    	for(int i = 0; i < e; i++){
    	cin >> u >> v;
    	u--, v--;
    	solver.add(u, v);
    	}
    	cout << solver.solve() << "\n";
    	for(int i = 0; i < n; i++) {
    	cout << solver.pa[i] + 1 << " ";
    	}
    	cout << "\n";
    }

    ```

??? note "[P1640 [SCOI2010]连续攻击游戏](https://www.luogu.com.cn/problem/P1640) "

    None

??? note "[Codeforces 1139E - Maximize Mex](https://codeforces.com/problemset/problem/1139/E) "

    None
