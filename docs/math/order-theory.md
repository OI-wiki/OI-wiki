## 引入

序理论是研究二元关系的一个数学分支。

在数学，计算机科学和相关知识领域中，次序无处不在。例如我们在入门数学课中学到的自然数之间的比较：「1 小于 2」，「100 大于 99」，「小明有 3 个苹果，小红有 12 个苹果。小红把自己的一半苹果分给小明，现在谁有更多的苹果？」。或者将这个概念扩展到其他数学集合的排序，比如整数和实数。实际上，大于或小于另一个数的概念是数学系统的基本直觉。很多时候我们并不知道两个数间的实际差，只有它们之间的次序。

上述类型的次序有特殊性质：每个元素都可以用于和另一个元素直接「比较」，也就是说，这个元素大于、小于、或等于另一个元素。但是，这不总是我们想要的结果。一个常见的例子是集合的子集排序。如果一个集合 $A$ 包含集合 $B$ 的所有元素，那么集合 $B$ 被称为小于等于 $A$。然而有些集合不能用这种方式来比较，因为其中每个集合都包含着其他集合中不存在的某些元素。例如，考虑一个系列集合的子集次序：尽管鸟类集合和狗的集合都是动物集合的子集，但鸟类和狗都不构成另一个的子集。所以，子集包含是偏次序，对立了前面给出的全次序。

更宽泛地讲，次序的概念非常普遍，远远超出了对序列或相对数量这些具有直观结论的描述。在特定情况下，次序可以用来描述专业化的概念。因为抽象地来看，这种类型的次序相当于子集关系。例如，「儿科医生是医生」，「圆是一种特殊的椭圆」。

序理论捕捉了在一般环境中从这些例子中产生的次序直觉。这是通过指定必须是数学顺序关系的 $\leq$ 属性来实现的。这种更抽象的方法很有意义，因为人们可以在一般环境中无需关注任何特定顺序的细节，就推导出许多定理。而这些方法可以很容易地转移到许多不太抽象的应用中。

在次序广泛应用的推动下，许多特殊类型的有序集有了定义，其中一些甚至已经发展成为了自己的数学领域。此外，序理论并不局限于各类序关系，而是考虑了它们之间的函数。函数的序理论的性质的一个简单例子来自在数学分析中常见的单调函数。

## 定义

### 二元关系

???+ note "定义"
    集合 $X$ 和集合 $Y$ 上的一个 **二元关系**（binary relation）$R$ 定义为元组 $(X,Y,G(R))$，其中 $X$ 称为定义域（domain），$Y$ 称为陪域（codomain），$G(R)\subseteq X\times Y=\{(x,y):x\in X,y\in Y\}$ 称为二元关系 $R$ 的图（graph）。$xRy$ 成立当且仅当 $(x,y)\in G(R)$。
    
    若 $X=Y$，则称该二元关系为齐次二元关系（homogeneous relation）或内关系（endorelation）。
    
    若没有特别说明，下文中的二元关系均为齐次二元关系。

例如 $\mathbf{N}_+$ 上的整除 $\mid$ 和小于等于 $\leq$ 均为二元关系。

我们研究二元关系时，往往会关注其是否具有一些特别的性质。对集合 $S$ 上的二元关系 $R$，我们定义如下特殊性质：

1.  自反性（reflexive）：$(\forall~a \in S)~~aRa$，
2.  反自反性（irreflexive，anti-reflexive）：$(\forall~a \in S)~~\lnot(aRa)$，
3.  对称性（symmetric）：$(\forall~a,b \in S)~~aRb \iff bRa$，
4.  反对称性（antisymmetric）：$(\forall~a,b \in S)~~(aRb \land bRa) \implies a=b$，
5.  非对称性（asymmetric）：$(\forall~a,b \in S)~~aRb \implies \lnot(bRa)$，
6.  传递性（transitive）：$(\forall~a,b,c \in S)~~(aRb \land bRc) \implies aRc$，
7.  连接性（connected）：$(\forall~a,b \in S)~~a \neq b \implies (aRb \lor bRa)$，
8.  良基性（well-founded）：$(\exists~m \in S \neq \varnothing)~~(\forall~a \in S)~~\lnot(aRm)$（即非空集合 $S$ 中有极小元 $m$），
9.  不可比的传递性（transitive of incomparability）：$(\forall~a,b,c \in S)~~(\lnot(aRb \lor bRa) \land \lnot(bRc \lor cRb)) \implies \lnot(aRc \lor cRa)$（若 $\lnot(aRb \lor bRa)$，我们则称 $a$ 和 $b$ 是不可比的）。

同时我们定义一些特殊的二元关系：

| 二元关系                         | 自反性 | 反自反性 | 对称性 | 反对称性 | 非对称性 | 传递性 | 连接性 | 良基性 | 不可比的传递性 |
| -------------------------------- | ------ | -------- | ------ | -------- | -------- | ------ | ------ | ------ | -------------- |
| 等价关系（equivalence relation） | 有     |          | 有     |          |          | 有     |        |        |                |
| 预序（preorder，quasiorder）     | 有     |          |        |          |          | 有     |        |        |                |
| 偏序（partial order）            | 有     |          |        | 有       |          | 有     |        |        |                |
| 全序（total order）              | 有     |          |        | 有       |          | 有     | 有     |        |                |
| 良序（well-order）               | 有     |          |        | 有       |          | 有     | 有     | 有     |                |
| 严格预序（strict preorder）      |        | 有       |        |          |          | 有     |        |        |                |
| 严格偏序（strict partial order） |        | 有       |        |          | 有       | 有     |        |        |                |
| 严格弱序（strict weak order）    |        | 有       |        |          | 有       | 有     |        |        | 有             |
| 严格全序（strict total order）   |        | 有       |        |          | 有       | 有     | 有     |        |                |

### 关系间的运算

对集合 $X$ 和集合 $Y$ 上的二元关系 $R$ 和 $S$，我们可以定义如下运算：

1.  $R$ 和 $S$ 的并 $R\cup S$ 满足 $G(R\cup S):=\{(x,y):xRy \lor xSy\}$（如 $\leq$ 是 $<$ 和 $=$ 的并）,
2.  $R$ 和 $S$ 的交 $R\cap S$ 满足 $G(R\cap S):=\{(x,y):xRy \land xSy\}$,
3.  $R$ 的补 $\bar{R}$ 满足 $G(\bar{R}):=\{(x,y):\lnot(xRy)\}$,
4.  $R$ 的对偶 $R^T$ 满足 $G(R^T):=\{(y,x):xRy\}$.

对集合 $X$ 和集合 $Y$ 上的二元关系 $R$ 以及集合 $Y$ 和集合 $Z$ 上的二元关系 $S$，我们可以定义其复合 $S\circ R$ 满足 $G(S\circ R):=\{(x,z):(\exists~y\in Y)~~xRy\land ySz\}$.

### 偏序集

???+ note "定义"
    若集合 $S$ 上的一个二元关系 $\preceq$ 具有**自反性**、**反对称性**、**传递性**，则称 $S$ 是 **偏序集**（partially ordered set，poset）, $\preceq$ 为其上一 **偏序**（partial order）。
    
    若偏序 $\preceq$ 还具有**连接性**，则称其为**全序**（total order），对应的集合称为 **全序集**（totally ordered set）、**线性序集**（linearly ordered set，loset）、**简单序集**（simply ordered set）。

由传递性和反对称性可以推出自反性，由传递性和自反性也可以推出反对称性。

不难发现 $\mathbf{N}$，$\mathbf{Z}$，$\mathbf{Q}$、$\mathbf{R}$ 均关于 $\leq$ 构成全序集。

### 偏序集的可视化表示：Hasse 图

对于有限偏序集，我们可以用 Hasse 图直观地表示其上的偏序关系。

???+ note "定义"
    对有限偏序集 $S$ 和其上的偏序 $\preceq$，定义 $x\prec y\iff (x\preceq y\land x\neq y)$ 其对应的 **Hasse 图**为满足如下条件的图 $G=\langle V,E\rangle$：
    
    -   $V=S$,
    -   $E=\{(x,y)\in S\times S: x\prec y \land ((\nexists~z\in S)~~x\prec z\prec y)\}$

如对于集合 $\{0,1,2\}$ 的幂集 $S$ 和集合的包含关系 $\subseteq$，其对应的 Hasse 图为：

![](images\order-theory1.svg)

由于偏序具有反对称性，所以 Hasse 图一定是[有向无环图](../graph/dag.md)，进而我们可以根据[拓扑排序](../graph/topo.md)对任意有限偏序集构造全序。

### 链与反链

???+ note "定义"
    对偏序集 $S$ 和其上的偏序 $\preceq$，称 $S$ 的全序子集为**链**（chain）。若 $S$ 的子集 $T$ 中任意两个不同元素均不可比（即 $(\forall~a,b \in T)~~a \neq b \implies (a \npreceq b \land b \npreceq a)$），则称 $T$ 为**反链**（antichain）。
    
    对偏序集 $S$ 和其上的偏序 $\preceq$，我们将偏序集 $S$ 的最长反链长度称为**宽度**（partial order width）。

如对于集合 $\{0,1,2\}$ 的幂集 $S$ 和集合的包含关系 $\subseteq$，$\{\varnothing,\{1\},\{1,2\}\}$ 为一条链，$\{\{1\},\{0,2\}\}$ 为一条反链，$S$ 的宽度为 $3$.

### 预序集中的特殊元素

在预序集中，我们可以定义极大（小）元、上（下）界、上（下）确界等概念，这些概念可以推广到其他序关系中。

???+ note "定义"
    对预序集 $S$ 和其上的预序 $\preceq$，取 $S$ 中的元素 $m$：
    
    1.  若 $(\forall~a \in S\setminus\{m\})~~\lnot(m\preceq a)$，则称 $m$ 为**极大元**（maximal element），
    2.  若对 $T \subseteq S$ 满足 $(\forall~t\in T)~~t\preceq m$，则称 $m$ 为 $T$ 的**上界**（upper bound），
    3.  若对 $T \subseteq S$ 满足 $m$ 是 $T$ 的上界且对 $T$ 的任意上界 $n$ 均有 $m \preceq n$，则称 $m$ 为 $T$ 的**上确界**（supremum）。
    
    类似可定义**极小元**（minimal element）、**下界**（lower bound）和**下确界**（infimum）。

如 $1$ 是 $\mathbf{N}_+$ 的极小元和下界。

可以证明：

-   预序集中，极大（小）元、上（下）界、上（下）确界都是不一定存在的，即使存在也不一定唯一。

-   若偏序集 $S$ 的子集 $T$ 存在上（下）确界，则一定唯一。
    
    我们可将 $T$ 的上确界、下确界分别记为 $\sup T$，$\inf T$. 若偏序集 $S$ 既有上界又有下界，则称 $S$ 是有界的。

在无限偏序集中，极大元不一定存在。可用 **Zorn 引理**（Zorn's Lemma）来判断无限偏序集中是否存在极大元。

???+ note "[Zorn 引理](https://en.wikipedia.org/wiki/Zorn%27s_lemma)"
    **Zorn 引理** 也被称为 **Kuratowski–Zorn 引理**，其内容为：若非空偏序集的每条链都有上界，则该偏序集存在极大元。

Zorn 引理与 **[选择公理](https://en.wikipedia.org/wiki/Axiom_of_choice)**、**[良序定理](https://en.wikipedia.org/wiki/Well-ordering_theorem)** 等价。

### 格

我们知道若偏序集的子集存在上（下）确界，则一定唯一。但是这一点并不适用于极大（小）元。例如：考虑偏序集 $S=\{\{0\},\{1\},\{2\},\{0,1\},\{0,2\},\{1,2\}\}$ 和其上的偏序 $\subseteq$，不难发现其有 $3$ 个极大元和 $3$ 个极小元。

我们希望通过向偏序集添加一定的条件来使得若极大（小）元存在则一定唯一，这样我们就可以定义最大（小）元的概念了。

对偏序集 $S$ 和其上的偏序 $\preceq$：

???+ note "并半格"
    若对 $S$ 中的任意元素 $a,b$，$\{a,b\}$ 均有上确界 $c$，则称 $S$ 为**并半格**（meet-semilattice，lower semilattice），并且我们称 $c$ 为 $a$ 和 $b$ 的**并**（meet），记为 $a\lor b$.

???+ note "交半格"
    若对 $S$ 中的任意元素 $a,b$，$\{a,b\}$ 均有下确界 $c$，则称 $S$ 为**交半格**（join-semilattice，upper semilattice），并且我们称 $c$ 为 $a$ 和 $b$ 的**交**（join），记为 $a\land b$.

不难发现：

-   若并半格存在极大元，则一定唯一。我们将并半格的极大元称为**最大元**（greatest element）。
-   若交半格存在极小元，则一定唯一。我们将交半格的极小元称为**最小元**（least element）。

???+ note "格"
    对偏序集 $S$ 和其上的偏序 $\preceq$，$S$ 既是并半格也是交半格，则称 $S$ 为**格**（lattice）。

例如对于 $\mathbf{N}_+$ 上的任意正整数 $a,b$，$\lcm(a,b)$ 为 $a$ 和 $b$ 的交，$\gcd(a,b)$ 为 $a$ 和 $b$ 的并，从而 $\mathbf{N}_+$ 是格。

### 对偶

在序理论中，对偶是非常常见的概念，如上文提到的极大元与极小元对偶、上界与下界对偶、上确界与下确界对偶。

对偏序集 $P$ 和其上的偏序 $\preceq$，定义其**对偶**（dual，opposite）偏序集 $P^d$ 满足：$x \preceq y$ 在 $P$ 中成立当且仅当 $y \preceq x$ 在 $P^d$ 中成立。将 $P$ 的 Hasse 图的边反转即可得到 $P^d$ 的 Hasse 图。

## Dliworth 定理与 Mirsky 定理

对有限偏序集 $S$ 和其上的偏序 $\preceq$，我们有如下的一对对偶的定理：

???+ note "Dilworth 定理"
    $S$ 的宽度（最长反链长度）等于最小的链覆盖数。
    
    ??? note "证明"
        考虑数学归纳法。当 $|S|\leq 3$ 时，命题显然成立。
        
        假设命题对所有元素个数小于 $|S|$ 的偏序集都成立，令 $S$ 的最长反链长度为 $d$. 若 $|S|$ 中所有元素均不可比，则命题显然成立，否则在 $S$ 中取一条长度大于 $1$ 的链，令其中的最小元为 $m$，最大元为 $M$.
        
        令 $T=S\setminus\{m,M\}$，若 $T$ 中的最长反链长度不超过 $d-1$，则 $T$ 显然可被 $d-1$ 条链覆盖，进而 $S$ 可被这 $d-1$ 条链再加上链 $\{m,M\}$ 覆盖，命题成立，否则说明 $T$ 中的最长反链长度也为 $d$，令这条反链为 $A$.
        
        我们考虑如下两个集合：
        
        $$
        S^+:=\{x\in S:(\exists~a\in A)~~a\preceq x\}
        $$
        
        $$
        S^-:=\{x\in S:(\exists~a\in A)~~x\preceq a\}
        $$
        
        我们不难发现如下性质：
        
        - $S^+\cup S^-=S$，
        - $S^+\cap S^-=A$，
        - $|S^+|<|S|$, $|S^-|<|S|$（因为 $m\notin S^+$ 且 $M\notin S^-$）。
        
        对 $S^+$ 和 $S^-$ 都应用归纳假设，则这两个集合的最小链覆盖数为 $d$，且这些链中恰好包含一个 $A$ 中的元素 $a$，设这些链分别为 $C_a^+$，$C_a^-$，则 $\{C_a^-\cup\{a\}\cup C_a^+\}$ 是 $S$ 的一个最小链覆盖，命题得证。

???+ note "Mirsky 定理"
    $S$ 的最长链长度等于最小的反链覆盖数。
    
    ??? note "证明"
        设 $S$ 的最长链长度为 $d$，则由定义，最小反链覆盖数显然至少为 $d$.
        
        令 $f(s)$ 为以 $s$ 为最小元的最长链长度，注意到若 $f(s)=f(t)$，则 $s$ 与 $t$ 不可比，进而 $(\forall~n\in\mathbf{N}_+)~~f^{-1}(n)$ 是一条反链。
        
        因此不难得出 $f^{-1}(1),\dots,f^{-1}(d)$ 是一个反链覆盖，从而最小反链覆盖数至多为 $d$.

Dilworth 定理与 [Hall 婚配定理](../graph/graph-matching/graph-match.md#霍尔定理) 等价。

我们可以用 Dilworth 定理证明如下定理：

???+ note "Erdős–Szekeres 定理"
    含至少 $rs+1$ 个元素的实数序列 $\{a_i\}$ 要么有一个长为 $r+1$ 的不下降子序列，要么有一个长为 $s+1$ 的不上升子序列。
    
    ??? note "证明"
        设序列长度为 $n\geq rs+1$，定义偏序集 $\{(i,a_i)\}_{i=1}^{n}$，其上的偏序 $\preceq$ 定义为：
        
        $$
        (i,a_i)\preceq (j,a_j)\iff (i\leq j\land a_i\leq a_j)
        $$
        
        假设该偏序集的宽度不超过 $s+1$，则由 Dilworth 定理可知该偏序集可以被至多 $s$ 条链覆盖，若这些链的长度都不超过 $r$，则序列所含元素数至多为 $rs$，与条件矛盾。

### 例题

???+ note "[Luogu P1020 \[NOIP1999 提高组\] 导弹拦截](https://www.luogu.com.cn/problem/P1020)"
    某国为了防御敌国的导弹袭击，发展出一种导弹拦截系统。但是这种导弹拦截系统有一个缺陷：虽然它的第一发炮弹能够到达任意的高度，但是以后每一发炮弹都不能高于前一发的高度。某天，雷达捕捉到敌国的导弹来袭。由于该系统还在试用阶段，所以只有一套系统，因此有可能不能拦截所有的导弹。
    
    输入导弹依次飞来的高度，计算这套系统最多能拦截多少导弹，如果要拦截所有导弹最少要配备多少套这种导弹拦截系统。
    
    对于全部数据，满足导弹的高度为正整数，且不超过 $5\times 10^4$.
    
    ??? note "题解"
        令一共有 $n$ 个导弹，第 $i$ 个导弹的高度为 $h_i$，则集合 $\{(i,h_i)\}_{i=1}^{n}$ 为偏序集，其上的偏序 $\preceq$ 定义为：
        
        $$
        (i,h_i)\preceq(j,h_j) \iff (i\leq j \land h_i\geq h_j)
        $$
        
        进而根据 Dilworth 定理有：**序列的不上升子序列的最少覆盖数等于最长上升子序列长度**。从而可以通过[最长不下降子序列的 $O(n\log n)$ 做法](../dp/basic.md#算法二2)解决本题。
    
    ??? note "参考代码"
        ```cpp
        --8<-- "docs/math/code/order-theory/order-theory_1.cpp"
        ```

???+ note "[\[TJOI2015\] 组合数学](https://www.luogu.com.cn/problem/P3974)"
    给一个 $n$ 行 $m$ 列的网格图，其中每个格子中均有若干块财宝。每次从左上角出发，只能往右或下走，每次经过一个格子至多只能捡走一块财宝。问至少要走几次才可能把财宝全捡完。
    
    $1\le n \le 1000$，$1\le m \le 1000$，每个格子中的财宝不超过 $10^6$ 块。
    
    ??? note "题解"
        不考虑网格图的点权，不难发现按给定的规则下在网格图上行走等价于在 DAG 上行走，从而我们可以将其视作 Hasse 图来构造偏序集，进而根据 Dilworth 定理有：**DAG 的最小链覆盖数等于最大的点独立集大小**。
        
        因此本题所求即为给定网格图最大点权独立集的点权和。
        
        令 $a_{ij}$ 为网格图在点 $(i,j)$ 处的权值，$f(i,j)$ 为 从 $(i,j)$ 到 $(1,m)$ 这个子网格中的答案，注意到每个点都和其右上角的点不相邻，则状态转移方程为：
        
        $$
        f(i,j)=\max\{f(i-1,j),f(i,j+1),f(i-1,j+1)+a_{ij}\}
        $$
        
        答案即为 $f(n,1)$.
    
    ??? note "参考代码"
        ```cpp
        --8<-- "docs/math/code/order-theory/order-theory_2.cpp"
        ```

### 算法

[C++ 基础库的排序函数](../basic/stl-sort.md) 中有偏序关系的应用。很多情况时，我们需要在 C++ 中自定义比较器（custom comparator），而 STL 要求自定义比较器必须为 **严格弱序**。而所有 STL 中的自定义比较器都可以用简单的 $<$ 关系表示。因为我们可以推断得知：

-   $x>y$ 表示 $y<x$;
-   $x \leq y$ 表示 $y \nless x$；
-   $x \geq y$ 表示 $x \nless y$；
-   $x=y$ 表示 $x \nless y$ 和 $y \nless x$。这就是为什么上面第四条规则被称为等价的传递性。如果 $x \nless y$ 和 $y \nless x$，我们可以说「$x$ 和 $y$ 是不可比的」。

## 参考资料与拓展阅读

1.  [Order theory - From Academic Kids](https://academickids.com/encyclopedia/index.php/Order_theory)
2.  [Binary Relation - Wikipedia](https://en.wikipedia.org/wiki/Binary_relation)
3.  [Order Theory - Wikipedia](https://en.wikipedia.org/wiki/Order_theory)
4.  [Hasse diagram - Wikipedia](https://en.wikipedia.org/wiki/Hasse_diagram)
5.  [Order Theory, Lecture Notes by Mark Dean for Decision Theory](http://www.columbia.edu/~md3405/DT_Order_15.pdf)
6.  卢开澄，卢华明，[《组合数学》（第 3 版）](http://www.tup.tsinghua.edu.cn/bookscenter/book_00458101.html), 2006
7.  [List of Order Theory Topics - Wikipedia](https://en.wikipedia.org/wiki/List_of_order_theory_topics)
8.  [浅谈邻项交换排序的应用以及需要注意的问题 by ouuan](https://ouuan.github.io/post/%E6%B5%85%E8%B0%88%E9%82%BB%E9%A1%B9%E4%BA%A4%E6%8D%A2%E6%8E%92%E5%BA%8F%E7%9A%84%E5%BA%94%E7%94%A8%E4%BB%A5%E5%8F%8A%E9%9C%80%E8%A6%81%E6%B3%A8%E6%84%8F%E7%9A%84%E9%97%AE%E9%A2%98/)
9.  [One thing you should know about comparators—Strict Weak Ordering](https://codeforces.com/blog/entry/72525)
10. [Dilworth's theorem - Wikipedia](https://en.wikipedia.org/wiki/Dilworth%27s_theorem)
11. [Dilworth's Theorem | Brilliant Math & Science Wiki](https://brilliant.org/wiki/dilworths-theorem/)
12. [Hall's marriage theorem - Wikipedia](https://en.wikipedia.org/wiki/Hall's_marriage_theorem)
13. [Hall's Marriage Theorem | Brilliant Math & Science Wiki](https://brilliant.org/wiki/hall-marriage-theorem/)
