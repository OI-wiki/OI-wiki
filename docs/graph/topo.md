## 定义

拓扑排序的英文名是 topological sort。

拓扑排序要解决的问题是给一个图的所有节点排序，而图中有若干限制，形如：“点 x 要在点 y 后面”。

举个现实一些的栗子，比如你去给刚开始学 OI 的同学们讲课，你会发现有很多知识点需要前置技能才能够听懂，并非是所有人都可以第一天就学明白 [线段树](/data-structure/intermediate/segment)。怎么办呢？讲课的时候是需要按顺序来的，并不能同时讲若干个知识点。这时候就需要用到拓扑排序了。

形式化定义一下：

给定一个 [DAG （有向无环图）])(dag)，如果从 $i$ 到 $j$ 有边，啧认为 $j$ 依赖于 $i$。如果 $i$ 到 $j$ 有路径（$i$ 可达 $j$），则称 $j$ 间接依赖于 $i$。

拓扑排序的目标是将所有节点排序，使得排在前面的节点不能依赖于排在后面的节点。

## 拓扑排序算法及实现

### 算法思路

核心思想是每次找一个入度为 0 的节点，取出来丢到答案序列里。然后再删除这个节点（以及对应的边），更新其他节点的入度，不断重复此操作直到答案序列包含了所有的节点。

在这个过程中，如果某一时刻发现找不到入度为 0 的节点，则可以认为这个图不能进行拓扑排序（会产生冲突）。

??? question "这里入度为 0 的点应该如何选取呢？"
    随便选就好啦！找到一个就可以直接用！

    为什么会这样呢？
    是因为某个点既然在新图中入度为 0 了，那么它就没有依赖的东西了（或者依赖的都已经被完成了）。

### 实现

伪代码：

    bool toposort() {
    	q = new queue();
    	for (i = 0; i < n; i++)
    		if (in_deg[i] == 0) q.push(i);
    	ans = new vector();
    	while (!q.empty()) {
    		u = q.pop();
    		ans.push_back(u);
    		for each edge(u, v) {
    			if (--in_deg[v] == 0) q.push(v);
    		}
    	}
    	if (ans.size() == n) {
    		for (i = 0; i < n; i++)
    			std::cout << ans[i] << std::endl;
    		return true;
    	} else {
    		return false;
    	}
    }

```c++
// dfs 版本
bool dfs(int u){
  c[u] = -1;
  for(int v = 0; v <= n; v++) if(G[u][v]) {
    if(c[v]<0) return false;
    else if(!c[v]) dfs(v);
  }
  c[u] = 1; topo.push_back(u);
  return true;
}
bool toposort(){
  topo.clear();
  memset(c, 0, sizeof(c));
  for(int u = 0; u <= n; u++) if(!c[u])
    if(!dfs(u)) return false;
  reverse(topo.begin(), topo.end());
  return true;
}
```

时间复杂度：$O(n+m)$
空间复杂度：$O(n)$

### 合理性证明

考虑一个图，删掉某个入度为 0 的节点之后，如果新图可以拓扑排序，那么原图一定也可以。反过来，如果原图可以拓扑排序，那么删掉后也可以。
