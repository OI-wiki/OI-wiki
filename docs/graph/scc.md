## 简介

在阅读下列内容之前，请务必了解 [图论基础](/graph/basic) 部分。

强连通的定义是：有向图 G 强连通是指，G 中任意两个节点连通。

强连通分量的定义是：极大的强连通子图。

这里想要介绍的是如何来求这个强连通分量。

## Kosaraju 算法

## Tarjan 算法

Robert E. Tarjan (1948~) 美国人。

这是你们第一次在本课程中听说此人，但不会是最后一次。

Tarjan 发明了很多很有用的东西，下到 NOIP 上到 CTSC 难度的都有。

【举例子：Tarjan算法，并查集，Splay 树，Tarjan离线求lca（Lowest Common Ancestor，最近公共祖先）等等】

我们这里要介绍的是图论中的 Tarjan 算法，用来处理各种连通性相关的问题。

### 定义

方便起见，我们先定义一些东西。

dfn(x)：节点 x 第一次被访问的时间戳(dfs number)

low(x)：节点 x 所能访问到的点的 dfn 值的最小值

这里的树指的是 DFS 树

所有结点按 dfn 排序即可得 dfs 序列

### DFS 树的性质

一个结点的子树内的 dfn 都比该结点的 dfn 要大。

从根开始的一条路径上的 dfn 严格递增。

一棵 DFS 树被构造出来后，考虑图中的非树边。

前向边(forward edge)：祖先→儿子

后向边(backward edge)：儿子→祖先

横叉边(cross edge)：没有祖先—儿子关系的

注意：横叉边只会往 dfn 减小的方向连接

注意：在无向图中，没有横叉边（为什么？）

### 实现

    dfs(x) {
    	dfn[x] = low[x] = ++index;
    	S.push(x);
    	instack[x] = true;
    	for each edge(x, y) {
    		if (!dfn[y]) {
    			dfs(y);
    			low[x] = min(low[x], low[y]);
    		} else if (instack[y]) {
    			low[x] = min(low[x], dfn[y]);
    		}
    	}
    	if (dfn[x] == low[x]) {
    		while (1) {
    			t = S.pop();
    			instack[t] = false;
    			if (t == x) break;
    		}
    	}
    }

（转自维基：<https://en.wikipedia.org/wiki/Tarjan%27s_strongly_connected_components_algorithm）>

时间复杂度 $O(n+m)$

## Garbow算法

## 应用

我们可以将一张图的每个强连通分量都缩成一个点。

然后这张图会变成一个DAG（为什么？）。

DAG 好啊，能拓扑排序了就能做很多事情了。

举个简单的例子，求一条路径，可以经过重复结点，要求经过的不同结点数量最多。

## 推荐题目

[USACO Fall/HAOI 2006 受欢迎的牛](https://www.lydsy.com/JudgeOnline/problem.php?id=1051)

[POJ1236 Network of Schools](http://poj.org/problem?id=1236)
