author: HeRaNO, JuicyMio, Xeonacid, sailordiary, ouuan

![](images/disjoint-set.svg)

并查集是一种用于管理元素所属集合的数据结构，实现为一个森林，其中每棵树表示一个集合，树中的节点表示对应集合中的元素。

顾名思义，并查集支持两种操作：

- 合并（Union）：合并两个元素所属集合（合并对应的树）
- 查询（Find）：查询某个元素所属集合（查询对应的树的根节点），这可以用于判断两个元素是否属于同一集合

!!! warning
    并查集不支持集合的分离，但是并查集在经过修改后可以支持集合中单个元素的删除操作（详见 UVA11987 Almost Union-Find）。使用动态开点线段树还可以实现可持久化并查集。

## 初始化

初始时，每个元素都位于一个单独的集合，表示为一棵只有根节点的树。方便起见，我们将根节点的父亲设为自己。

```cpp
// C++ Version
struct dsu {
    vector<size_t> pa;

    dsu(size_t size) {
        pa.resize(size);
        iota(pa.begin(), pa.end(), 0);
    }
};
```

```python
# Python Version
class Dsu:
    def __init__(self, size):
        self.pa = list(range(size))
```

## 查询

我们需要沿着树向上移动，直至找到根节点。

![](images/disjoint-set-find.svg)

```cpp
// C++ Version
size_t find(size_t x) {
    return pa[x] == x ? x : find(pa[x]);
}
```

```python
# Python Version
def find(self, x):
    return x if self.pa[x] == x else self.find(self.pa[x])
```

### 路径压缩

查询过程中经过的每个元素都属于该集合，我们可以将其直接连到根节点以加快后续查询。

![](images/disjoint-set-compress.svg)

```cpp
// C++ Version
size_t find(size_t x) {
    return pa[x] == x ? x : pa[x] = find(pa[x]);
}
```

```python
# Python Version
def find(self, x):
    if self.pa[x] != x:
        self.pa[x] = self.find(self.pa[x])
    return self.pa[x]
```

## 合并

宴会上，一个家族的祖先突然对另一个家族说：我们两个家族交情这么好，不如合成一家好了。另一个家族也欣然接受了。  
我们之前说过，并不在意祖先究竟是谁，所以只要其中一个祖先变成另一个祖先的儿子就可以了。

![](images/disjoint-set-merge.svg)

C++ 的参考实现：

```cpp
// C++ Version
void unionSet(int x, int y) {
  // x 与 y 所在家族合并
  x = find(x);
  y = find(y);
  fa[x] = y;  // 把 x 的祖先变成 y 的祖先的儿子
}
```

Python 的参考实现：

```python
# Python Version
def unionSet(x, y):
    # x 与 y 所在家族合并
    x = find(x)
    y = find(y)
    fa[x] = y # 把 x 的祖先变成 y 的祖先的儿子
```

### 启发式合并（按秩合并）

一个祖先突然抖了个机灵：「你们家族人比较少，搬家到我们家族里比较方便，我们要是搬过去的话太费事了。」

由于需要我们支持的只有集合的合并、查询操作，当我们需要将两个集合合二为一时，无论将哪一个集合连接到另一个集合的下面，都能得到正确的结果。但不同的连接方法存在时间复杂度的差异。具体来说，如果我们将一棵点数与深度都较小的集合树连接到一棵更大的集合树下，显然相比于另一种连接方案，接下来执行查找操作的用时更小（也会带来更优的最坏时间复杂度）。

当然，我们不总能遇到恰好如上所述的集合————点数与深度都更小。鉴于点数与深度这两个特征都很容易维护，我们常常从中择一，作为估价函数。而无论选择哪一个，时间复杂度都为 $O (m\alpha(m,n))$，具体的证明可参见 References 中引用的论文。

在算法竞赛的实际代码中，即便不使用启发式合并，代码也往往能够在规定时间内完成任务。在 Tarjan 的论文[1]中，证明了不使用启发式合并、只使用路径压缩的最坏时间复杂度是 $O (m \log n)$。在姚期智的论文[2]中，证明了不使用启发式合并、只使用路径压缩，在平均情况下，时间复杂度依然是 $O (m\alpha(m,n))$。

如果只使用启发式合并，而不使用路径压缩，时间复杂度为 $O(m\log n)$。由于路径压缩单次合并可能造成大量修改，有时路径压缩并不适合使用。例如，在可持久化并查集、线段树分治 + 并查集中，一般使用只启发式合并的并查集。

C++ 的参考实现，其选择点数作为估价函数：

```cpp
// C++ Version
std::vector<int> size(N, 1);  // 记录并初始化子树的大小为 1

void unionSet(int x, int y) {
  int xx = find(x), yy = find(y);
  if (xx == yy) return;
  if (size[xx] > size[yy])  // 保证小的合到大的里
    swap(xx, yy);
  fa[xx] = yy;
  size[yy] += size[xx];
}
```

Python 的参考实现：

```python
# Python Version
size = [1] * N # 记录并初始化子树的大小为 1
def unionSet(x, y):
    xx = find(x); yy = find(y)
    if xx == yy:
        return
    if size[xx] > size[yy]: # 保证小的合到大的里
        xx, yy = yy, xx
    fa[xx] = yy
    size[yy] = size[yy] + size[xx]
```

## 时间复杂度及空间复杂度

### 时间复杂度

同时使用路径压缩和启发式合并之后，并查集的每个操作平均时间仅为 $O(\alpha(n))$，其中 $\alpha$ 为阿克曼函数的反函数，其增长极其缓慢，也就是说其单次操作的平均运行时间可以认为是一个很小的常数。

[Ackermann 函数](https://en.wikipedia.org/wiki/Ackermann_function)  $A(m, n)$ 的定义是这样的：

$A(m, n) = \begin{cases}n+1&\text{if }m=0\\A(m-1,1)&\text{if }m>0\text{ and }n=0\\A(m-1,A(m,n-1))&\text{otherwise}\end{cases}$

而反 Ackermann 函数 $\alpha(n)$ 的定义是阿克曼函数的反函数，即为最大的整数 $m$ 使得 $A(m, m) \leqslant n$。

时间复杂度的证明 [在这个页面中](./dsu-complexity.md)。

### 空间复杂度

显然为 $O(n)$。

## 带权并查集

我们还可以在并查集的边上定义某种权值、以及这种权值在路径压缩时产生的运算，从而解决更多的问题。比如对于经典的「NOI2001」食物链，我们可以在边权上维护模 3 意义下的加法群。

## 经典题目

[「NOI2015」程序自动分析](https://uoj.ac/problem/127)

[「JSOI2008」星球大战](https://www.luogu.com.cn/problem/P1197)

[「NOI2001」食物链](https://www.luogu.com.cn/problem/P2024)

[「NOI2002」银河英雄传说](https://www.luogu.com.cn/problem/P1196)

[UVA11987 Almost Union-Find](https://www.luogu.com.cn/problem/UVA11987)

## 其他应用

[最小生成树算法](../graph/mst.md) 中的 Kruskal 和 [最近公共祖先](../graph/lca.md) 中的 Tarjan 算法是基于并查集的算法。

相关专题见 [并查集应用](../topic/dsu-app.md)。

## 参考资料与拓展阅读

- [1]Tarjan, R. E., & Van Leeuwen, J. (1984). Worst-case analysis of set union algorithms. Journal of the ACM (JACM), 31(2), 245-281.[ResearchGate PDF](https://www.researchgate.net/profile/Jan_Van_Leeuwen2/publication/220430653_Worst-case_Analysis_of_Set_Union_Algorithms/links/0a85e53cd28bfdf5eb000000/Worst-case-Analysis-of-Set-Union-Algorithms.pdf)
- [2]Yao, A. C. (1985). On the expected performance of path compression algorithms.[SIAM Journal on Computing, 14(1), 129-133.](https://epubs.siam.org/doi/abs/10.1137/0214010?journalCode=smjcat)
- [3][知乎回答：是否在并查集中真的有二分路径压缩优化？](<https://www.zhihu.com/question/28410263/answer/40966441>)
- [4]Gabow, H. N., & Tarjan, R. E. (1985). A Linear-Time Algorithm for a Special Case of Disjoint Set Union. JOURNAL OF COMPUTER AND SYSTEM SCIENCES, 30, 209-221.[PDF](https://dl.acm.org/doi/pdf/10.1145/800061.808753)
