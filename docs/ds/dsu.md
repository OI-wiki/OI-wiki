author: HeRaNO, JuicyMio, Xeonacid, sailordiary, ouuan, Pig-Eat-Earth

![](images/disjoint-set.svg)

## 引入

并查集是一种用于管理元素所属集合的数据结构，实现为一个森林，其中每棵树表示一个集合，树中的节点表示对应集合中的元素。

顾名思义，并查集支持两种操作：

-   合并（Union）：合并两个元素所属集合（合并对应的树）
-   查询（Find）：查询某个元素所属集合（查询对应的树的根节点），这可以用于判断两个元素是否属于同一集合

并查集在经过修改后可以支持单个元素的删除、移动；使用动态开点线段树还可以实现可持久化并查集。

??? warning
    并查集无法以较低复杂度实现集合的分离。

## 初始化

初始时，每个元素都位于一个单独的集合，表示为一棵只有根节点的树。方便起见，我们将根节点的父亲设为自己。

???+ note "实现"
    === "C++"
        ```cpp
        struct dsu {
          vector<size_t> pa;
        
          explicit dsu(size_t size) : pa(size) { iota(pa.begin(), pa.end(), 0); }
        };
        ```
    
    === "Python"
        ```python
        class Dsu:
            def __init__(self, size):
                self.pa = list(range(size))
        ```

## 查询

我们需要沿着树向上移动，直至找到根节点。

![](images/disjoint-set-find.svg)

???+ note "实现"
    === "C++"
        ```cpp
        size_t dsu::find(size_t x) { return pa[x] == x ? x : find(pa[x]); }
        ```
    
    === "Python"
        ```python
        def find(self, x):
            return x if self.pa[x] == x else self.find(self.pa[x])
        ```

### 路径压缩

查询过程中经过的每个元素都属于该集合，我们可以将其直接连到根节点以加快后续查询。

![](images/disjoint-set-compress.svg)

???+ note "实现"
    === "C++"
        ```cpp
        size_t dsu::find(size_t x) { return pa[x] == x ? x : pa[x] = find(pa[x]); }
        ```
    
    === "Python"
        ```python
        def find(self, x):
            if self.pa[x] != x:
                self.pa[x] = self.find(self.pa[x])
            return self.pa[x]
        ```

## 合并

要合并两棵树，我们只需要将一棵树的根节点连到另一棵树的根节点。

![](images/disjoint-set-merge.svg)

???+ note "实现"
    === "C++"
        ```cpp
        void dsu::unite(size_t x, size_t y) { pa[find(x)] = find(y); }
        ```
    
    === "Python"
        ```python
        def union(self, x, y):
            self.pa[self.find(x)] = self.find(y)
        ```

### 启发式合并

合并时，选择哪棵树的根节点作为新树的根节点会影响未来操作的复杂度。我们可以将节点较少或深度较小的树连到另一棵，以免发生退化。

??? note "具体复杂度讨论"
    由于需要我们支持的只有集合的合并、查询操作，当我们需要将两个集合合二为一时，无论将哪一个集合连接到另一个集合的下面，都能得到正确的结果。但不同的连接方法存在时间复杂度的差异。具体来说，如果我们将一棵点数与深度都较小的集合树连接到一棵更大的集合树下，显然相比于另一种连接方案，接下来执行查找操作的用时更小（也会带来更优的最坏时间复杂度）。
    
    当然，我们不总能遇到恰好如上所述的集合——点数与深度都更小。鉴于点数与深度这两个特征都很容易维护，我们常常从中择一，作为估价函数。而无论选择哪一个，时间复杂度都为 $O (m\alpha(m,n))$，具体的证明可参见 References 中引用的论文。
    
    在算法竞赛的实际代码中，即便不使用启发式合并，代码也往往能够在规定时间内完成任务。在 Tarjan 的论文[^tarjan1984worst]中，证明了不使用启发式合并、只使用路径压缩的最坏时间复杂度是 $O (m \log n)$。在姚期智的论文[^yao1985expected]中，证明了不使用启发式合并、只使用路径压缩，在平均情况下，时间复杂度依然是 $O (m\alpha(m,n))$。
    
    如果只使用启发式合并，而不使用路径压缩，时间复杂度为 $O(m\log n)$。由于路径压缩单次合并可能造成大量修改，有时路径压缩并不适合使用。例如，在可持久化并查集、线段树分治 + 并查集中，一般使用只启发式合并的并查集。

按节点数合并的参考实现：

???+ note "实现"
    === "C++"
        ```cpp
        struct dsu {
          vector<size_t> pa, size;
        
          explicit dsu(size_t size_) : pa(size_), size(size_, 1) {
            iota(pa.begin(), pa.end(), 0);
          }
        
          void unite(size_t x, size_t y) {
            x = find(x), y = find(y);
            if (x == y) return;
            if (size[x] < size[y]) swap(x, y);
            pa[y] = x;
            size[x] += size[y];
          }
        };
        ```
    
    === "Python"
        ```python
        class Dsu:
            def __init__(self, size):
                self.pa = list(range(size))
                self.size = [1] * size
        
            def union(self, x, y):
                x, y = self.find(x), self.find(y)
                if x == y:
                    return
                if self.size[x] < self.size[y]:
                    x, y = y, x
                self.pa[y] = x
                self.size[x] += self.size[y]
        ```

## 删除

要删除一个叶子节点，我们可以将其父亲设为自己。为了保证要删除的元素都是叶子，我们可以预先为每个节点制作副本，并将其副本作为父亲。

???+ note "实现"
    === "C++"
        ```cpp
        struct dsu {
          vector<size_t> pa, size;
        
          explicit dsu(size_t size_) : pa(size_ * 2), size(size_ * 2, 1) {
            iota(pa.begin(), pa.begin() + size_, size_);
            iota(pa.begin() + size_, pa.end(), size_);
          }
        
          void erase(size_t x) {
            --size[find(x)];
            pa[x] = x;
          }
        };
        ```
    
    === "Python"
        ```python
        class Dsu:
            def __init__(self, size):
                self.pa = list(range(size, size * 2)) * 2
                self.size = [1] * size * 2
        
            def erase(self, x):
                self.size[self.find(x)] -= 1
                self.pa[x] = x
        ```

## 移动

与删除类似，通过以副本作为父亲，保证要移动的元素都是叶子。

???+ note "实现"
    === "C++"
        ```cpp
        void dsu::move(size_t x, size_t y) {
          auto fx = find(x), fy = find(y);
          if (fx == fy) return;
          pa[x] = fy;
          --size[fx], ++size[fy];
        }
        ```
    
    === "Python"
        ```python
        def move(self, x, y):
            fx, fy = self.find(x), self.find(y)
            if fx == fy:
                return
            self.pa[x] = fy
            self.size[fx] -= 1
            self.size[fy] += 1
        ```

## 复杂度

### 时间复杂度

同时使用路径压缩和启发式合并之后，并查集的每个操作平均时间仅为 $O(\alpha(n))$，其中 $\alpha$ 为阿克曼函数的反函数，其增长极其缓慢，也就是说其单次操作的平均运行时间可以认为是一个很小的常数。

[Ackermann 函数](https://en.wikipedia.org/wiki/Ackermann_function)  $A(m, n)$ 的定义是这样的：

$A(m, n) = \begin{cases}n+1&\text{if }m=0\\A(m-1,1)&\text{if }m>0\text{ and }n=0\\A(m-1,A(m,n-1))&\text{otherwise}\end{cases}$

而反 Ackermann 函数 $\alpha(n)$ 的定义是阿克曼函数的反函数，即为最大的整数 $m$ 使得 $A(m, m) \leqslant n$。

时间复杂度的证明 [在这个页面中](./dsu-complexity.md)。

### 空间复杂度

显然为 $O(n)$。

## 带权并查集

我们还可以在并查集的边上定义某种权值和这种权值在路径压缩时产生的运算，从而解决更多的问题。比如对于经典的「NOI2001」食物链，我们可以在边权上维护模 $3$ 意义下的加法群。对于这类维护模意义下边权的问题，有时还可以通过将并查集的单个点拆分为多个状态的方式来解决。这种特殊情形下的技巧，也称为「种类并查集」或「拓展域并查集」。后文会通过例题来说明这些做法。

## 例题

算法竞赛中，直接考察并查集的题目大多都需要针对题目设计特殊的结构。

???+ example "[UVa11987 Almost Union-Find](https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=229&page=show_problem&problem=3138)"
    实现类似并查集的数据结构，支持以下操作：
    
    1.  合并两个元素所属集合。
    2.  将单个元素移动到另一个元素所在的集合。
    3.  查询某个元素所属集合的大小及元素和。

??? note "思路"
    这道题目中，操作 1 和操作 3 都容易处理，难点在于操作 2。假定要将元素 $x$ 移动到元素 $y$ 所在的集合。在普通的并查集中，直接将元素 $x$ 的父亲设为元素 $y$ 所在集合的根节点是不行的，因为这样会将元素 $x$ 所在子树的元素都一起移动。针对这个问题，解决方法就是保证元素 $x$ 没有子节点。为此，在建立并查集时为每个元素 $x$ 都建立一个虚点 $\tilde x$，并将元素 $x$ 的父亲指向对应的虚点 $\tilde x$。这样，在合并两个集合的时候，因为总是将一个树根连接到另一个树根，而树根又全部是虚点，所以，只有虚点会有子节点，而所有实际存储元素的点都没有子节点。此时，要移动元素，就容易实现得多。
    
    下面的实现中，元素 $i$ 对应的虚点为 $i+n$。

??? note "参考代码"
    === "C++"
        ```cpp
        --8<-- "docs/ds/code/dsu/dsu_1.cpp"
        ```
    
    === "Python"
        ```python
        --8<-- "docs/ds/code/dsu/dsu_1.py"
        ```

???+ example "[Luogu P2024「NOI2011」食物链](https://www.luogu.com.cn/problem/P2024)"
    动物王国中有三类动物 $A,B,C$，这三类动物的食物链构成了有趣的环形。$A$ 吃 $B$，$B$ 吃 $C$，$C$ 吃 $A$。
    
    现有 $N$ 个动物，以 $1 \sim N$ 编号。每个动物都是 $A,B,C$ 中的一种，但是我们并不知道它到底是哪一种。
    
    有人用两种说法对这 $N$ 个动物所构成的食物链关系进行描述：
    
    - 第一种说法是 `1 X Y`，表示 $X$ 和 $Y$ 是同类。
    - 第二种说法是 `2 X Y`，表示 $X$ 吃 $Y$。
    
    此人对 $N$ 个动物，用上述两种说法，一句接一句地说出 $K$ 句话，这 $K$ 句话有的是真的，有的是假的。当一句话满足下列三条之一时，这句话就是假话，否则就是真话。
    
    - 当前的话与前面的某些真的话冲突，就是假话；
    - 当前的话中 $X$ 或 $Y$ 比 $N$ 大，就是假话；
    - 当前的话表示 $X$ 吃 $X$，就是假话。
    
    你的任务是根据给定的 $N$ 和 $K$ 句话，输出假话的总数。

??? note "思路"
    将一种生物 $x$ 拆分为三种状态。在具体实现中，我们可以直接将不同的状态当作不同的元素：
    
    -   与 `x` 处于同一集合的状态与 `x` 属于同一物种；
    -   与 `x+n` 处于同一集合的状态能被 `x` 吃；
    -   与 `x+2n` 处于同一集合的能吃 `x`。
    
    于是，对于一句话：  
    
    -   `1 x y` 为假话当且仅当：  
    
        1. $x>N$ 或 $y>N$；  
        2. `y` 与 `x+n` 或 `x+2n` 中的一个处于同一集合内。  
    
    -   `2 x y` 为假话当且仅当：  
    
        1. $x>N$ 或 $y>N$；  
        2. `y` 与 `x` 或 `x+2n` 中的一个处于同一集合内。  
    
    -   若为真话，合并对应状态。

??? note "实现"
    ```cpp
    --8<-- "docs/ds/code/dsu/dsu_2.cpp"
    ```

???+ example "[ABC396E Min of Restricted Sum](https://atcoder.jp/contests/abc396/tasks/abc396_e)"
    给定整数 $N, M$ 和长度为 $M$ 的整数序列 $X=(X_1,X_2,\ldots,X_M)$、$Y=(Y_1,Y_2,\ldots,Y_M)$、$Z=(Z_1,Z_2,\ldots,Z_M)$。其中，保证 $X$ 和 $Y$ 的所有元素均在 $1$ 至 $N$ 的范围内。
    
    定义长度为 $N$ 的非负整数序列 $A=(A_1,A_2,\ldots,A_N)$ 为 **好的整数序列**，当且仅当满足以下条件：
    - 对于所有满足 $1 \leq i \leq M$ 的整数 $i$，有 $A_{X_i} \oplus A_{Y_i} = Z_i$，其中 $\oplus$ 表示异或运算。
    
    请判断是否存在这样的好的整数序列。若存在，请找出使得元素总和 $\displaystyle \sum_{i=1}^N A_i$ 最小的好的整数序列，并输出该序列。
    
??? note "思路"
    异或就是单个二进制位上的「相同」或「不同」关系。那么，将 $A_i$ 的所有二进制位拆开，异或关系就能用拓展域并查集维护了。另外，不同位会对答案产生不同贡献，因此要使用带权并查集进行维护。
    
    最后，在统计答案时，一个二进制位取 $1$ 或取 $0$ 会确定别的某些二进制位的取值，在两种中选择贡献（即权值）较小者。

??? note "实现"
    ```cpp
    --8<-- "docs/ds/code/dsu/dsu_3.cpp"
    ```

## 习题

-   [「NOI2015」程序自动分析](https://uoj.ac/problem/127)
-   [「JSOI2008」星球大战](https://www.luogu.com.cn/problem/P1197)
-   [「NOIP2023」三值逻辑](https://www.luogu.com.cn/problem/P9869)
-   [「NOI2002」银河英雄传说](https://www.luogu.com.cn/problem/P1196)

## 其他应用

[最小生成树算法](../graph/mst.md) 中的 Kruskal 和 [最近公共祖先](../graph/lca.md) 中的 Tarjan 算法是基于并查集的算法。

相关专题见 [并查集应用](../topic/dsu-app.md)。

## 参考资料与拓展阅读

1.  [知乎回答：是否在并查集中真的有二分路径压缩优化？](https://www.zhihu.com/question/28410263/answer/40966441)
2.  Gabow, H. N., & Tarjan, R. E. (1985). A Linear-Time Algorithm for a Special Case of Disjoint Set Union. JOURNAL OF COMPUTER AND SYSTEM SCIENCES, 30, 209-221.[PDF](https://dl.acm.org/doi/pdf/10.1145/800061.808753)
3.  [CSDN：扩展域并查集 & 带权并查集](https://blog.csdn.net/qqqqqwerttwtwe/article/details/145440100)

[^tarjan1984worst]: Tarjan, R. E., & Van Leeuwen, J. (1984). Worst-case analysis of set union algorithms. Journal of the ACM (JACM), 31(2), 245-281.[ResearchGate PDF](https://www.researchgate.net/profile/Jan_Van_Leeuwen2/publication/220430653_Worst-case_Analysis_of_Set_Union_Algorithms/links/0a85e53cd28bfdf5eb000000/Worst-case-Analysis-of-Set-Union-Algorithms.pdf)

[^yao1985expected]: Yao, A. C. (1985). On the expected performance of path compression algorithms.[SIAM Journal on Computing, 14(1), 129-133.](https://epubs.siam.org/doi/abs/10.1137/0214010?journalCode=smjcat)
