author: accelsao

# 二分图最大权匹配

最大权匹配是指边权和最大的匹配。
首先，将两个集合中点数比较少的补点，使得两边点数相同，再将不存在的边权重设为 $0$ ，问题就转换成求 **最大权完美匹配问题** 。
即找一个匹配使得边权和最大且所有点都在匹配内。

## Hungarian Algorithm（Kuhn-Munkres Algorithm）

匈牙利算法又称为 **KM** 算法，可以在 $O(n^3)$ 时间内求出最大权完美匹配。

??? note "可行顶标"

    给每个节点 $i$ 分配一个权值 $l(i)$，对于所有边 $(u,v)$ 满足 $w(u,v) \leq l(u) + l(v)$。

??? note "相等子图"

    在一组可行顶标下原图的生成子图，包含所有点但只包含满足 $w(u,v) = l(u) + l(v)$ 的边 $(u,v)$。

??? note "定理 1 : 对于某组可行顶标，如果其相等子图存在完美匹配，那么，该匹配就是原二分图的最大权完美匹配。"

    ### 证明 1.
    考虑原二分图任意一组完美匹配 $M$，其边权和为

    $val(M) = \sum_{(u,v)\in M} {w(u,v)} \leq \sum_{(u,v)\in M} {l(u) + l(v)} \leq \sum_{i=1}^{n} l(i)$

    任意一组可行顶标的相等子图的完美匹配 $M'$ 的边权和

    $val(M') = \sum_{(u,v)\in M} {l(u) + l(v)} = \sum_{i=1}^{n} l(i)$

    即任意一组完美匹配的边权和都不会大于 $val(M')$，那个 $M'$ 就是最大权匹配。

有了定理 1，我们的目标就是透过不断的调整可行顶标，使得相等子图是完美匹配。

因为两边点数相等，假设点数为 $n$ ， $lx(i)$ 表示左边第 $i$ 个点的顶标， $ly(i)$ 表示右边第 $i$ 个点的顶标， $w(u,v)$ 表示左边第 $u$ 个点和右边第 $v$ 个点之间的权重。

首先初始化一组可行顶标，例如

 $lx(i)$ = max { $w(i, j)$ for j = 1 to n}, $ly(i) = 0$ 

然后选一个未匹配点，如同最大匹配一样求增广路。
找到增广路就增广，否则，会得到一个交错树。
令 $S$ , $T$ 表示二分图左边右边在交错树中的点， $S'$ , $T'$ 表示不在交错树中的点。

![bigraph-weight-match-1](./images/bigraph-weight-match-1.png)

在相等子图中：

-    $S-T'$ 的边不存在，否则交错树会增长。
-    $S'-T$ 一定是非匹配边，否则他就属于 $S$ 。

假设给 $S$ 中的顶标 $-a$ ，给 $T$ 中的顶标 $+a$ ，
可以发现

-    $S-T$ 边依然存在相等子图中。
-    $S'-T'$ 没变化。
-    $S-T'$ lx + ly 有所减少可能加入相等子图。
-    $S'-T$ lx + ly 会增加所以不可能加入相等子图。

所以这个 $a$ 值的选择，显然得是 $S-T'$ 当中最小的边权，

 $a$ = min { $lx(u) + ly(v) - w(u,v)$ \| $u\in{S}$ , $v\in{T'}$ }。

当一条新的边 $(u,v)$ 加入相等子图后有两种情况

-   v 是未匹配点，则找到增广路
-   v 和 S' 中的点已经匹配

这样至多修改 $n$ 次顶标后，就可以找到增广路。

每次修改顶标的时候，交错树中的边不会离开相等子图，那么我们直接维护这棵树。

我们对 $T$ 中的每个点 $v$ 维护

 $slack(v)$ = min { $lx(u) + ly(v) - w(u,v)$ \| $u\in{S}$ }。

所以可以在 $O(n)$ 算出顶标修改值 $a$ 

 $a$ = min { $slack(v)$ \| $v\in{T'}$ }

交错树新增一个点进入 $S$ 的时候需要 $O(n)$ 更新 $slack(v)$ 。
修改顶标需要 $O(n)$ 给每个 $slack(v)$ 减去 $a$ 。
只要交错树找到一个未匹配点，就找到增广路。
一开始枚举 $n$ 个点找增广路，为了找增广路需要延伸 $n$ 次交错树，每次延伸需要 $n$ 次维护，共 $O(n^3)$ 。

### 代码

这里是 $O(n^3)$ 的代码

```cpp
template <typename T>
struct hungarian {  // km
  int n;
  vector<int> matchx;  // 左集合对应的匹配点
  vector<int> matchy;  // 右集合对应的匹配点
  vector<int> pre;     // 连接右集合的左点
  vector<bool> visx;   // 拜访数组 左
  vector<bool> visy;   // 拜访数组 右
  vector<T> lx;
  vector<T> ly;
  vector<vector<T> > g;
  vector<T> slack;
  T inf;
  T res;
  queue<int> q;
  int org_n;
  int org_m;

  hungarian(int _n, int _m) {
    org_n = _n;
    org_m = _m;
    n = max(_n, _m);
    inf = numeric_limits<T>::max();
    res = 0;
    g = vector<vector<T> >(n, vector<T>(n));
    matchx = vector<int>(n, -1);
    matchy = vector<int>(n, -1);
    pre = vector<int>(n);
    visx = vector<bool>(n);
    visy = vector<bool>(n);
    lx = vector<T>(n, -inf);
    ly = vector<T>(n);
    slack = vector<T>(n);
  }

  void addEdge(int u, int v, int w) {
    g[u][v] = max(w, 0);  // 负值还不如不匹配 因此设为0不影响
  }

  bool check(int v) {
    visy[v] = true;
    if (matchy[v] != -1) {
      q.push(matchy[v]);
      visx[matchy[v]] = true;  // in S
      return false;
    }
    // 找到新的未匹配点 更新匹配点 pre 数组记录着"非匹配边"上与之相连的点
    while (v != -1) {
      matchy[v] = pre[v];
      swap(v, matchx[pre[v]]);
    }
    return true;
  }

  void bfs(int i) {
    while (!q.empty()) {
      q.pop();
    }
    q.push(i);
    visx[i] = true;
    while (true) {
      while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v = 0; v < n; v++) {
          if (!visy[v]) {
            T delta = lx[u] + ly[v] - g[u][v];
            if (slack[v] >= delta) {
              pre[v] = u;
              if (delta) {
                slack[v] = delta;
              } else if (check(v)) {  // delta=0 代表有机会加入相等子图 找增广路
                                      // 找到就return 重建交错树
                return;
              }
            }
          }
        }
      }
      // 没有增广路 修改顶标
      T a = inf;
      for (int j = 0; j < n; j++) {
        if (!visy[j]) {
          a = min(a, slack[j]);
        }
      }
      for (int j = 0; j < n; j++) {
        if (visx[j]) {  // S
          lx[j] -= a;
        }
        if (visy[j]) {  // T
          ly[j] += a;
        } else {  // T'
          slack[j] -= a;
        }
      }
      for (int j = 0; j < n; j++) {
        if (!visy[j] && slack[j] == 0 && check(j)) {
          return;
        }
      }
    }
  }

  void solve() {
    // 初始顶标
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        lx[i] = max(lx[i], g[i][j]);
      }
    }

    for (int i = 0; i < n; i++) {
      fill(slack.begin(), slack.end(), inf);
      fill(visx.begin(), visx.end(), false);
      fill(visy.begin(), visy.end(), false);
      bfs(i);
    }

    // custom
    for (int i = 0; i < n; i++) {
      if (g[i][matchx[i]] > 0) {
        res += g[i][matchx[i]];
      } else {
        matchx[i] = -1;
      }
    }
    cout << res << "\n";
    for (int i = 0; i < org_n; i++) {
      cout << matchx[i] + 1 << " ";
    }
    cout << "\n";
  }
};
```

## 习题

??? note "[UOJ #78. 二分图最大匹配](http://uoj.ac/problem/78) "

    模板题
    ```cpp
    #include <bits/stdc++.h>
    using namespace std;

    template <typename T>
    struct hungarian { // km
      int n;
      vector<int> matchx;
      vector<int> matchy;
      vector<int> pre;
      vector<bool> visx;
      vector<bool> visy;
      vector<T> lx;
      vector<T> ly;
      vector< vector<T> > g;
      vector<T> slack;
      T inf;
      T res;
      queue<int> q;
      int org_n;
      int org_m;

      hungarian(int _n, int _m) {
    	org_n = _n;
    	org_m = _m;
    	n = max(_n, _m);
    	inf = numeric_limits<T>::max();
    	res = 0;
    	g = vector< vector<T> >(n, vector<T>(n));
    	matchx = vector<int>(n, -1);
    	matchy = vector<int>(n, -1);
    	pre = vector<int>(n);
    	visx = vector<bool>(n);
    	visy = vector<bool>(n);
    	lx = vector<T>(n, -inf);
    	ly = vector<T>(n);
    	slack = vector<T>(n);
      }

      void addEdge(int u, int v, int w) {
    	g[u][v] = max(w, 0); // 负值还不如不匹配 因此设为0不影响
      }


      bool check(int v) {
    	visy[v] = true;
    	if(matchy[v] != -1) {
    	  q.push(matchy[v]);
    	  visx[matchy[v]] = true;
    	  return false;
    	}
    	while(v != -1) {
    	  matchy[v] = pre[v];
    	  swap(v, matchx[pre[v]]);
    	}
    	return true;
      }

      void bfs(int i) {
    	while(!q.empty()) {
    	  q.pop();
    	}
    	q.push(i);
    	visx[i] = true;
    	while(true) {
    	  while(!q.empty()) {
    		int u = q.front();
    		q.pop();
    		for(int v = 0; v < n; v++) {
    		  if(!visy[v]) {
    			T delta = lx[u] + ly[v] - g[u][v];
    			if(slack[v] >= delta) {
    			  pre[v] = u;
    			  if(delta) {
    				slack[v] = delta;
    			  } else if(check(v)) {
    				return ;
    			  }
    			}
    		  }
    		}
    	  }
    	  // 没有增广路 修改顶标
    	  T a = inf;
    	  for(int j = 0; j < n; j++) {
    		if(!visy[j]){
    		  a = min(a, slack[j]);
    		}
    	  }
    	  for(int j = 0; j < n; j++) {
    		if(visx[j]) { // S
    		  lx[j] -= a;
    		}
    		if(visy[j]) { // T
    		  ly[j] += a;
    		} else { // T'
    		  slack[j] -= a;
    		}
    	  }
    	  for(int j = 0; j < n; j++) {
    		if(!visy[j] && slack[j] == 0 && check(j)) {
    		  return ;
    		}
    	  }
    	}

      }

      void solve() {
    	// 初始顶标
    	for(int i = 0; i < n; i++) {
    	  for(int j = 0; j < n; j++) {
    		lx[i] = max(lx[i], g[i][j]);
    	  }
    	}

    	for(int i = 0; i < n; i++) {
    	  fill(slack.begin(), slack.end(), inf);
    	  fill(visx.begin(), visx.end(), false);
    	  fill(visy.begin(), visy.end(), false);
    	  bfs(i);
    	}

    	// custom
    	for(int i = 0; i < n; i++) {
    	  if(g[i][matchx[i]] > 0) {
    		res += g[i][matchx[i]];
    	  } else {
    		matchx[i] = -1;
    	  }

    	}
    	cout << res << "\n";
    	for(int i = 0; i < org_n; i++) {
    	  cout << matchx[i] + 1 << " ";
    	}
    	cout << "\n";
      }
    };

    int main(){
      ios::sync_with_stdio(0), cin.tie(0);
      int n, m, e;
      cin >> n >> m >> e;

      hungarian<long long> solver(n, m);

      int u, v, w;
      for(int i = 0; i < e; i++) {
    	cin >> u >> v >> w;
    	u--, v--;
    	solver.addEdge(u, v, w);
      }
      solver.solve();
    }

    ```
