## 简介
在阅读下列内容之前，请务必了解 [图论基础](/graph/basic) 部分

## Tarjan 算法

割点（连通无向图）：删掉这个结点后，原图不连通

桥（连通无向图）：删掉这条边后，原图不连通

点双连通（无向图）：任意两个结点之间存在两条结点不相交的路径

边双连通（无向图）：任意两个结点之间存在两条边不相交的路径

求出割点和桥，是我们的主要任务

### 定义

方便起见，我们先定义一些东西。

dfn(x)：节点 x 第一次被访问的时间戳(dfs number)

low(x)：节点 x 所能访问到的点的 dfn 值的最小值

AP：Articulation Point，割点 【也叫 Cut Vertex】

（伪代码）

```
dfs(u, fa) {
	dfn[u] = low[u] = ++index;
	int n_childs = 0;
	for each edge(u, v) {
		if (!dfn[v]) {
			dfs(v, u);
			low[u] = min(low[u], low[v]);
			if (low[v] == dfn[v]) {
				report_bridge(u, v);
			}
			if (low[v] >= dfn[u]) {
				is_AP[u] = true;
			}
			++n_childs;
		} else if (v != fa) {
			low[u] = min(low[u], dfn[v]);
		}
	}
	if (fa == NULL && n_childs > 1) {
		is_AP[u] = true;
	}
}
```

使劲脑补一下，应该就能知道为啥是对的了

## 应用

注意到，一张图可以分为很多个点双连通 / 边双连通分量

它们之间恰好是用割点和桥来分隔的

同时，点双 / 边双之间的拓扑关系，正好也构成了一棵树

我们可以把点双 / 边双缩起来，也能干很多事情

举个简单的例子，一个无向图，问 a 到 b 的所有路径中，必然经过哪些点

再举个简单例子，有向图，问 a 到 b 的所有路径中，必然经过恰好一次的是哪些点
