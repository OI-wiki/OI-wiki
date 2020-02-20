author: accelsao

# 二分图最大匹配

為了描述方便將兩個集合分成左和右兩個部分，所有匹配邊都是橫跨左右兩個集合，可以假想成男女配對。

假設圖有$n$個頂點，$m$條邊。

## 增廣路算法 Augmenting Path Algorithm

因為增廣路長度為奇數，路徑起始點非左即右，不失一般性考慮從左邊的未匹配點找增廣路。
注意到因為交錯陸的關係，奇數次都是走非匹配邊，偶數次走匹配邊，於是左到右都是非匹配邊，右到左都是匹配邊。
於是我們給二分圖**定向**，問題轉換成，有向圖中從給定起點找一條簡單路徑走到某個未匹配點，此問題等價給定起始點$s$能否走到終點$t$。
那麼只要從起始點開始*DFS*遍歷直到找到某個未匹配點，$O(m)$。
未找到增廣路時，我們拓展的路也稱為**交錯樹**。

因為要枚舉$n$個點，總複雜度為$O(nm)$。

### 代碼
```cpp
struct augment_path {
  vector< vector<int> > g;
  vector<int> pa; // 匹配
  vector<int> pb;
  vector<int> vis; // 訪問
  int n, m; // 頂點數量
  int dfn; // 時間戳記
  int res; // 匹配數

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
```

使用例子

* 宣告 augment_path solver(n, m)
* 建邊 solver.add(u, v);
* 計算匹配數 solver.solve()

## Dinic 算法

二分圖最大匹配可以轉換成網路流模型。
將左邊所有點接上源點，右邊所有點接上匯點，容量皆為$1$。
原來的每條邊從左往右連邊，容量耶皆為$1$，最大流即最大匹配，可在$O(\sqrt{n}m)$求出。

Dinic 算法分成兩部分，第一部分用 $O(m)$ 時間 BFS 建立網路流，第二步是 $O(nm)$ 時間 DFS 進行增廣。
但因為容量為 $1$，這邊只需要 $O(m)$。
接下來前 $O(\sqrt{n})$ 輪，複雜度為 $O(\sqrt{n}m)$。
$O(\sqrt{n})$ 輪以後，每條增廣路徑長度至少 $\sqrt{n}$，而這樣的路徑不超過 $\sqrt{n}$ ，
所以最多也只剩下 $\sqrt{n}$ 輪需要跑，整體複雜度為 $O(\sqrt{n}m)$。

## 補充

### 二分圖最大獨立集

選最多的點，滿足兩兩之間沒有邊相連。

二分圖中，最大獨立集 = $n$ - 最大匹配。

### 二分圖最小點覆蓋

選最少的點，滿足每條邊至少有一個端點被選，不難發現補集是獨立集。

二分圖中，最小點覆蓋 = $n$ - 最大獨立集。

## 习题

??? note "[UOJ #78. 二分图最大匹配](http://uoj.ac/problem/78) "

	模板題
    ```cpp
	#include <bits/stdc++.h>
	using namespace std;

	struct augment_path {
	  vector< vector<int> > g;
	  vector<int> pa; // 匹配
	  vector<int> pb;
	  vector<int> vis; // 訪問
	  int n, m; // 頂點數量
	  int dfn; // 時間戳記
	  int res; // 匹配數

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


