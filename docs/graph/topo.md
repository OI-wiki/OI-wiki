## 定义

拓扑排序的英文名是 Topological sorting。

拓扑排序要解决的问题是给一个图的所有节点排序。

我们可以拿大学选课的例子来描述这个过程，比如学习大学课程中有：单变量微积分，线性代数，离散数学概述，概率论与统计学概述，语言基础，算法导论，机器学习。当我们想要学习 算法导论 的时候，就必须先学会 离散数学概述 和 概率论与统计学概述，不然在课堂就会听的一脸懵逼。当然还有一个更加前的课程 单变量微积分。这些课程就相当于几个顶点 $u$, 顶点之间的有向边 $(u,v)$ 就相当于学习课程的顺序。显然拓扑排序不是那么的麻烦，不然你是如何选出合适的学习顺序。下面将介绍如何将这个过程抽象出来，用算法来实现。

但是如果某一天排课的老师打瞌睡了，说想要学习 算法导论，还得先学 机器学习，而 机器学习 的前置课程又是 算法导论，然后你就一万脸懵逼了，我到底应该先学哪一个？当然我们在这里不考虑什么同时学几个课程的情况。在这里，算法导论 和 机器学习 间就出现了一个环，显然你现在没办法弄清楚你需要学什么了，于是你也没办法进行拓扑排序了。因而如果有向图中存在环路，那么我们就没办法进行 拓扑排序 了。

因此我们可以说 在一个 [DAG（有向无环图）](./dag.md) 中，我们将图中的顶点以线性方式进行排序，使得对于任何的顶点 $u$ 到 $v$ 的有向边 $(u,v)$, 都可以有 $u$ 在 $v$ 的前面。

还有给定一个 DAG，如果从 $i$ 到 $j$ 有边，则认为 $j$ 依赖于 $i$。如果 $i$ 到 $j$ 有路径（$i$ 可达 $j$），则称 $j$ 间接依赖于 $i$。

拓扑排序的目标是将所有节点排序，使得排在前面的节点不能依赖于排在后面的节点。

## AOV网
日常生活中，一项大的工程可以看作是由若干个子工程组成的集合，这些子工程之间必定存在一定的先后顺序，即某些子工程必须在其他的一些子工程完成后才能开始。
我们用有向图来表现子工程之间的先后关系，子工程之间的先后关系为有向边，这种有向图称为“顶点活动网络”，即AOV 网。
一个 AOV 网必定是一个有向无环图，即不带有回路。与 DAG 不同的是，AOV 的活动都表示在边上。

在AOV网中，顶点表示活动，弧表示活动间的优先关系。
AOV网中不应该出现环，这样就能够找到一个顶点序列，使得每个顶点代表的活动的前驱活动都排在该顶点的前面，这样的序列称为拓扑序列，由AOV网构造拓扑序列的过程称为拓扑排序。
检测AOV网中是否带环的方式是构造拓扑序列，看是否包含所有顶点。

### 构造拓扑序列步骤：
1.选一个没有前驱的顶点输出
2.图中删去该顶点，以及所有从该顶点出发的弧
重复上面两步，直到所有顶点都输出或没有不带前驱的顶点


## 关键路径和AOE网
与AOV 网对应的是AOE 网（Activity on Edge）即便表示活动的网。AOE网是一个带权的有向无环图，其中，顶点表示事件，弧表示活动持续的时间。通常，AOE网可以用来估算工程的完成时间。
由于AOE网中的有些活动是可以并行进行的，所以完成整个工程的最短时间是从开始点到完成点的最长路径长度（这里所说的路径长度是指路径上各活动的持续时间之和，不是路径上弧的数目。）路径长度最长的路径叫做关键路径。

### 相关基本概念
活动：子工程组成的集合，每个子工程即为一个活动。
前驱活动：有向边起点的活动称为终点的前驱活动（只有当一个活动的前驱全部都完成后，这个活动才能进行）。
后继活动：有向边终点的活动称为起点的后继活动。
拓扑排序：将 AOV 网中所有活动排成一个序列，使得每个活动的前驱活动都排在该活动的前面。
拓扑序列：经过拓扑排序后得到的活动序列（一个 AOV 网的拓扑序列不是唯一的）。
关键路径：AOV 网中从源点到汇点的最长路径的长度（一个 AOV 网中的拓扑排序不是唯一的）。
活动 aj的最早开始时间：初始点到该弧起点的最长路径长度，记为e(j)。
活动 aj的最迟开始时间：在不推迟整个工期的前提下，工程达到弧起点所表示的状态最晚能容忍的时间，记为l(j)。
顶点 vj的最早发生时间：初始点到该顶点的最长路径长度，记为 ve(j) ，它决定了以该顶点开始的活动的最早发生时间，所以 ve(j)=e(j)。
顶点 vj的最迟发生时间：在不推迟整个工期的前提下，工程达到顶点所表示的状态最晚能容忍的时间，记为 vl(j) ，它决定了所有以该状态结束的活动的最迟发生时间，所以 l(j)=vl(j)-dul(aj)。
关键活动：关键路径上的活动，最早开始时间和最迟开始时间相等。

### 最早和最迟发生时间的递推关系
ve(j) = max{ve(k) + dut(<k,j>)} <k,j>∈T,2≤j≤n
vl(j) = min{vl(k) - dut(<j,k>)} <j,k>∈S,1≤j≤n-1 
按拓扑顺序求，最早--从前往后，前驱顶点的最早开始时间与边的权重之和最大者，最迟--从后往前，后继顶点的最迟开始时间与边的权重之差的最小者。

### 关键路径算法
关键路径可能不止一条。
在AOE 网中，源点为入度为零的节点，汇点为出度为零的点。
1）输入e条弧（j，k），建立AOE网；
（2）从源点v0出发，令ve[0] = 0,按照拓扑排序求其余各个顶点的最早发生时间ve[i],(i <= i <= n-1)。如果得到的拓扑有序序列中顶点的个数小于网中的顶点数n，则说明网中存在环，不能求关键路径，算法终止；否则执行步骤三；
（3）从汇点vn出发，令vl[n-1] = ve[n-1]，按照逆拓扑有序求其余各顶点的最迟发生时间vl[i],(n-2 >= i >= 2);
（4）根据各顶点的ve和vl值，求每条弧s的最早开始时间e(s)和最迟开始时间l(s)。若某条弧满足条件e(s) = l(s),则为关键活动。


## Kahn 算法

### 过程

初始状态下，集合 $S$ 装着所有入度为 $0$ 的点，$L$ 是一个空列表。

每次从 $S$ 中取出一个点 $u$（可以随便取）放入 $L$, 然后将 $u$ 的所有边 $(u, v_1), (u, v_2), (u, v_3) \cdots$ 删除。对于边 $(u, v)$，若将该边删除后点 $v$ 的入度变为 $0$，则将 $v$ 放入 $S$ 中。

不断重复以上过程，直到集合 $S$ 为空。检查图中是否存在任何边，如果有，那么这个图一定有环路，否则返回 $L$，$L$ 中顶点的顺序就是拓扑排序的结果。

首先看来自 [Wikipedia](https://en.wikipedia.org/wiki/Topological_sorting#Kahn's_algorithm) 的伪代码

???+ note "实现"
    ```text
    L ← Empty list that will contain the sorted elements
    S ← Set of all nodes with no incoming edges
    while S is not empty do
        remove a node n from S
        insert n into L
        for each node m with an edge e from n to m do
            remove edge e from the graph
            if m has no other incoming edges then
                insert m into S
    if graph has edges then
        return error (graph has at least one cycle)
    else
        return L (a topologically sorted order)
    ```

代码的核心是维持一个入度为 0 的顶点的集合。

可以参考该图

![topo](images/topo-example.svg)

对其排序的结果就是：2 -> 8 -> 0 -> 3 -> 7 -> 1 -> 5 -> 6 -> 9 -> 4 -> 11 -> 10 -> 12

### 时间复杂度

假设这个图 $G = (V, E)$ 在初始化入度为 $0$ 的集合 $S$ 的时候就需要遍历整个图，并检查每一条边，因而有 $O(E+V)$ 的复杂度。然后对该集合进行操作，显然也是需要 $O(E+V)$ 的时间复杂度。

因而总的时间复杂度就有 $O(E+V)$

### 实现

```cpp
int n, m;
vector<int> G[MAXN];
int in[MAXN];  // 存储每个结点的入度

bool toposort() {
  vector<int> L;
  queue<int> S;
  for (int i = 1; i <= n; i++)
    if (in[i] == 0) S.push(i);
  while (!S.empty()) {
    int u = S.front();
    S.pop();
    L.push_back(u);
    for (auto v : G[u]) {
      if (--in[v] == 0) {
        S.push(v);
      }
    }
  }
  if (L.size() == n) {
    for (auto i : L) cout << i << ' ';
    return true;
  } else {
    return false;
  }
}
```

## DFS 算法

### 实现

=== "C++"

    ```cpp
    using Graph = vector<vector<int>>;  // 邻接表

    struct TopoSort {
      enum class Status : uint8_t { to_visit, visiting, visited };

      const Graph& graph;
      const int n;
      vector<Status> status;
      vector<int> order;
      vector<int>::reverse_iterator it;

      TopoSort(const Graph& graph)
          : graph(graph),
            n(graph.size()),
            status(n, Status::to_visit),
            order(n),
            it(order.rbegin()) {}

      bool sort() {
        for (int i = 0; i < n; ++i) {
          if (status[i] == Status::to_visit && !dfs(i)) return false;
        }
        return true;
      }

      bool dfs(const int u) {
        status[u] = Status::visiting;
        for (const int v : graph[u]) {
          if (status[v] == Status::visiting) return false;
          if (status[v] == Status::to_visit && !dfs(v)) return false;
        }
        status[u] = Status::visited;
        *it++ = u;
        return true;
      }
    };
    ```

=== "Python"

    ```python
    from enum import Enum, auto


    class Status(Enum):
        to_visit = auto()
        visiting = auto()
        visited = auto()


    def topo_sort(graph: list[list[int]]) -> list[int] | None:
        n = len(graph)
        status = [Status.to_visit] * n
        order = []

        def dfs(u: int) -> bool:
            status[u] = Status.visiting
            for v in graph[u]:
                if status[v] == Status.visiting:
                    return False
                if status[v] == Status.to_visit and not dfs(v):
                    return False
            status[u] = Status.visited
            order.append(u)
            return True

        for i in range(n):
            if status[i] == Status.to_visit and not dfs(i):
                return None

        return order[::-1]
    ```

时间复杂度：$O(E+V)$ 空间复杂度：$O(V)$

### 合理性证明

考虑一个图，删掉某个入度为 $0$ 的节点之后，如果新图可以拓扑排序，那么原图一定也可以。反过来，如果原图可以拓扑排序，那么删掉后也可以。

### 应用

拓扑排序可以用来判断图中是否有环，

还可以用来判断图是否是一条链。

### 求字典序最大/最小的拓扑排序

将 Kahn 算法中的队列替换成最大堆/最小堆实现的优先队列即可，此时总的时间复杂度为 $O(E+V \log{V})$。

## 习题

[CF 1385E](https://codeforces.com/problemset/problem/1385/E)：需要通过拓扑排序构造。

[Luogu P1347](https://www.luogu.com.cn/problem/P1347): 拓扑排序模板。

## 参考

1.  离散数学及其应用。ISBN:9787111555391
2.  <https://blog.csdn.net/dm_vincent/article/details/7714519>
3.  Topological sorting,<https://en.wikipedia.org/w/index.php?title=Topological_sorting&oldid=854351542>
4.  <https://blog.csdn.net/time_money/article/details/109857779>
5.  <https://zhuanlan.zhihu.com/p/164751109>
