dfs 全称是 [Depth First Search](https://en.wikipedia.org/wiki/Depth-first_search)。

是一种图的遍历算法。

所谓深度优先。就是说每次都尝试向更深的节点走。
如果没有更深的节点了，就回到上一层的下一个节点继续刚才的过程。

## 实现

伪代码：

```text
dfs(u) {
  visited[u] = true
  for each edge(u, v) {
    if (!visited[v]) {
      dfs(v)
    }
  }
}
```

C++：

```c++
void dfs(int u) {
  vis[u] = 1;
  for (int i = head[u]; i; i = e[i].x) {
    // 这里用到的是链式前向星来存图
    if (!vis[ e[i].t ]) {
      dfs(v);
    }
  }
}
```

时间复杂度 $O(n + m)$

空间复杂度 $O(n)$ （vis 数组和递归栈）


## $Meet\ in\ middle$

所谓 $Meet\ in\ middle$ ,就是让 $Dfs$ 的状态在中间的时候碰面。我们知道,如果一个暴力 $Dfs$ 有 $K$ 个转移,那么它的时间复杂度(大多数情况) 是 $O(K^N)$ 的。那我们就想,当 $N$ 到达一定程度时, $TLE$ 会变成必然。

[一道例题](https://www.luogu.org/problemnew/show/P2962)。

我们正常想,如果这道题暴力 $Dfs$ 找开关灯的状态,时间复杂度就是 $O(2^{35})$,显然超时。不过,如果我们用 $Meet\ in\ middle$ 的话,时间复杂度将会变为 $O(2^{18}) \times2$ 而已。

$Meet\ in\ middle$ 就是让我们先找一半的状态,也就是 $1$ 到 $mid$ ($N$ 的一半) 的状态,再找剩下的状态就可以了。我们把前半段的状态全部存储在 $hash$ 表或者 $map$ 里面,然后在找后半段的状态的时候,先判断后半段是不是都合法,就可以判断上半段有没有配对的上半段使得整段合法。

## [在树 / 图上 dfs](/graph/traverse)
