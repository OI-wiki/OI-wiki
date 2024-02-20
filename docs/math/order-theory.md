## 引入

序理论是利用二元关系来将「次序」这一概念严格化的数学分支，下面将介绍这一分支的基本定义。

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
8.  良基性（well-founded）：$(\exists~m \in S \neq \varnothing)~~(\forall~a \in S\setminus\{m\})~~\lnot(aRm)$（即非空集合 $S$ 中有极小元 $m$），
9.  不可比的传递性（transitive of incomparability）：$(\forall~a,b,c \in S)~~(\lnot(aRb \lor bRa) \land \lnot(bRc \lor cRb)) \implies \lnot(aRc \lor cRa)$（若 $\lnot(aRb \lor bRa)$，则称 $a$ 和 $b$ 是不可比的）。

同时我们定义一些特殊的二元关系：

| 二元关系                       | 自反性 | 反自反性 | 对称性 | 反对称性 | 非对称性 | 传递性 | 连接性 | 良基性 | 不可比的传递性 |
| -------------------------- | --- | ---- | --- | ---- | ---- | --- | --- | --- | ------- |
| 等价关系（equivalence relation） | 有   |      | 有   |      |      | 有   |     |     |         |
| 预序（preorder，quasiorder）    | 有   |      |     |      |      | 有   |     |     |         |
| 偏序（partial order）          | 有   |      |     | 有    |      | 有   |     |     |         |
| 全序（total order）            | 有   |      |     | 有    |      | 有   | 有   |     |         |
| 良序（well-order）             | 有   |      |     | 有    |      | 有   | 有   | 有   |         |
| 严格预序（strict preorder）      |     | 有    |     |      |      | 有   |     |     |         |
| 严格偏序（strict partial order） |     | 有    |     |      | 有    | 有   |     |     |         |
| 严格弱序（strict weak order）    |     | 有    |     |      | 有    | 有   |     |     | 有       |
| 严格全序（strict total order）   |     | 有    |     |      | 有    | 有   | 有   |     |         |

### 关系间的运算

对集合 $X$ 和集合 $Y$ 上的二元关系 $R$ 和 $S$，我们可以定义如下运算：

1.  $R$ 和 $S$ 的并 $R\cup S$ 满足 $G(R\cup S):=\{(x,y):xRy \lor xSy\}$（如 $\leq$ 是 $<$ 和 $=$ 的并），
2.  $R$ 和 $S$ 的交 $R\cap S$ 满足 $G(R\cap S):=\{(x,y):xRy \land xSy\}$，
3.  $R$ 的补 $\bar{R}$ 满足 $G(\bar{R}):=\{(x,y):\lnot(xRy)\}$，
4.  $R$ 的对偶 $R^T$ 满足 $G(R^T):=\{(y,x):xRy\}$.

对集合 $X$ 和集合 $Y$ 上的二元关系 $R$ 以及集合 $Y$ 和集合 $Z$ 上的二元关系 $S$，我们可以定义其复合 $S\circ R$ 满足 $G(S\circ R):=\{(x,z):(\exists~y\in Y)~~xRy\land ySz\}$.

### 偏序集

???+ note "定义"
    若集合 $S$ 上的一个二元关系 $\preceq$ 具有 **自反性**、**反对称性**、**传递性**，则称 $S$ 是 **偏序集**（partially ordered set，poset），$\preceq$ 为其上一 **偏序**（partial order）。
    
    若偏序 $\preceq$ 还具有 **连接性**，则称其为 **全序**（total order），对应的集合称为 **全序集**（totally ordered set）、**线性序集**（linearly ordered set，loset）、**简单序集**（simply ordered set）。

由传递性和反对称性可以推出自反性，由传递性和自反性也可以推出反对称性。

不难发现 $\mathbf{N}$，$\mathbf{Z}$，$\mathbf{Q}$、$\mathbf{R}$ 均关于 $\leq$ 构成全序集。

### 偏序集的可视化表示：Hasse 图

对于有限偏序集，我们可以用 Hasse 图直观地表示其上的偏序关系。

???+ note "定义"
    对有限偏序集 $S$ 和其上的偏序 $\preceq$，定义 $x\prec y\iff (x\preceq y\land x\neq y)$ 其对应的 **Hasse 图** 为满足如下条件的图 $G=\langle V,E\rangle$：
    
    -   $V=S$,
    -   $E=\{(x,y)\in S\times S: x\prec y \land ((\nexists~z\in S)~~x\prec z\prec y)\}$

如对于集合 $\{0,1,2\}$ 的幂集 $S$ 和集合的包含关系 $\subseteq$，其对应的 Hasse 图为：

![](images/order-theory1.svg)

由于偏序具有反对称性，所以 Hasse 图一定是 [有向无环图](../graph/dag.md)，进而我们可以根据 [拓扑排序](../graph/topo.md) 对任意有限偏序集构造全序。

### 链与反链

???+ note "定义"
    对偏序集 $S$ 和其上的偏序 $\preceq$，称 $S$ 的全序子集为 **链**（chain）。若 $S$ 的子集 $T$ 中任意两个不同元素均不可比（即 $(\forall~a,b \in T)~~a \neq b \implies (a \npreceq b \land b \npreceq a)$），则称 $T$ 为 **反链**（antichain）。
    
    对偏序集 $S$ 和其上的偏序 $\preceq$，我们将偏序集 $S$ 的最长反链长度称为 **宽度**（partial order width）。

如对于集合 $\{0,1,2\}$ 的幂集 $S$ 和集合的包含关系 $\subseteq$，$\{\varnothing,\{1\},\{1,2\}\}$ 为一条链，$\{\{1\},\{0,2\}\}$ 为一条反链，$S$ 的宽度为 $3$.

### 预序集中的特殊元素

在预序集中，我们可以定义极大（小）元、上（下）界、上（下）确界等概念，这些概念可以推广到其他序关系中。

???+ note "定义"
    对预序集 $S$ 和其上的预序 $\preceq$，取 $S$ 中的元素 $m$：
    
    1.  若 $(\forall~a \in S\setminus\{m\})~~\lnot(m\preceq a)$，则称 $m$ 为 **极大元**（maximal element），
    2.  若对 $T \subseteq S$ 满足 $(\forall~t\in T)~~t\preceq m$，则称 $m$ 为 $T$ 的 **上界**（upper bound），
    3.  若对 $T \subseteq S$ 满足 $m$ 是 $T$ 的上界且对 $T$ 的任意上界 $n$ 均有 $m \preceq n$，则称 $m$ 为 $T$ 的 **上确界**（supremum）。
    
    类似可定义 **极小元**（minimal element）、**下界**（lower bound）和 **下确界**（infimum）。

如 $1$ 是 $\mathbf{N}_+$ 的极小元和下界。

可以证明：

-   预序集中，极大（小）元、上（下）界、上（下）确界都是不一定存在的，即使存在也不一定唯一。

-   若偏序集 $S$ 的子集 $T$ 存在上（下）确界，则一定唯一。

    我们可将 $T$ 的上确界、下确界分别记为 $\sup T$，$\inf T$. 若偏序集 $S$ 既有上界又有下界，则称 $S$ 是有界的。

在无限偏序集中，极大元不一定存在。可用 **Zorn 引理**（Zorn's Lemma）来判断无限偏序集中是否存在极大元。

???+ note "[Zorn 引理](https://en.wikipedia.org/wiki/Zorn%27s_lemma)"
    **Zorn 引理** 也被称为 **Kuratowski–Zorn 引理**，其内容为：若非空偏序集的每条链都有上界，则该偏序集存在极大元。

Zorn 引理与 **[选择公理](https://en.wikipedia.org/wiki/Axiom_of_choice)**、**[良序定理](https://en.wikipedia.org/wiki/Well-ordering_theorem)** 等价。

### 有向集与格

我们知道若偏序集的子集存在上（下）确界，则一定唯一。但是这一点并不适用于极大（小）元。例如：考虑偏序集 $S=\{\{0\},\{1\},\{2\},\{0,1\},\{0,2\},\{1,2\}\}$ 和其上的偏序 $\subseteq$，不难发现其有 $3$ 个极大元和 $3$ 个极小元。

我们希望通过向偏序集添加一定的条件来使得若极大（小）元存在则一定唯一，这样我们就可以定义最大（小）元的概念了。

???+ note "有向集"
    对预序集 $S$ 和其上的预序 $\preceq$，若 $(\forall~a,b\in S)~~(\exists~c\in S)~~a\preceq c\land b\preceq c$，则称 $\preceq$ 为 $S$ 的一个 **方向**（direction），$S$ 称为 **有向集**（directed set）或 **过滤集**（filtered set）。
    
    有时也将满足上述定义的集合 $S$ 称为 **上有向集**（upward directed set），类似地可定义 **下有向集**（downward directed set）。

有向集也可用如下方式定义：

???+ note "有向集的等价定义"
    对预序集 $S$ 和其上的预序 $\preceq$，若 $S$ 的任意有限子集 $T$ 均有上界，则称 $\preceq$ 为 $S$ 的一个方向，$S$ 称为有向集。

不难发现：

-   若上有向集存在极大元，则一定唯一。我们将上有向集的极大元称为 **最大元**（greatest element）。
-   若下有向集存在极小元，则一定唯一。我们将下有向集的极小元称为 **最小元**（least element）。

有方向的偏序集中，对任意元素 $a,b$，$\{a,b\}$ 都有上界，若将上界修改为上确界，则得到了并半格的定义。

对偏序集 $S$ 和其上的偏序 $\preceq$：

???+ note "并半格"
    若对 $S$ 中的任意元素 $a,b$，$\{a,b\}$ 均有上确界 $c$，则称 $S$ 为 **并半格**（join-semilattice，upper semilattice），并且我们称 $c$ 为 $a$ 和 $b$ 的 **并**（join），记为 $a\lor b$.

???+ note "交半格"
    若对 $S$ 中的任意元素 $a,b$，$\{a,b\}$ 均有下确界 $c$，则称 $S$ 为 **交半格**（meet-semilattice，lower semilattice），并且我们称 $c$ 为 $a$ 和 $b$ 的 **交**（meet），记为 $a\land b$.

???+ note "格"
    若 $S$ 既是并半格也是交半格，则称 $S$ 为 **格**（lattice）。

例如 $60$ 的正因子构成的集合 $S=\{1,2,3,4,5,6,10,12,15,20,30,60\}$ 关于整除构成偏序集，其上的任意正整数 $a,b$，$\operatorname{lcm}(a,b)$ 为 $a$ 和 $b$ 的并，$\gcd(a,b)$ 为 $a$ 和 $b$ 的交，从而 $S$ 是格。

### 对偶

在序理论中，对偶是非常常见的概念，如上文提到的极大元与极小元对偶、上界与下界对偶、上确界与下确界对偶。

对偏序集 $P$ 和其上的偏序 $\preceq$，定义其 **对偶**（dual，opposite）偏序集 $P^d$ 满足：$x \preceq y$ 在 $P$ 中成立当且仅当 $y \preceq x$ 在 $P^d$ 中成立。将 $P$ 的 Hasse 图的边反转即可得到 $P^d$ 的 Hasse 图。

## Dilworth 定理与 Mirsky 定理

对有限偏序集 $S$ 和其上的偏序 $\preceq$，我们有如下的一对对偶的定理：

???+ note "Dilworth 定理"
    $S$ 的宽度（最长反链长度）等于最小的链覆盖数。
    
    ??? note "证明"
        考虑数学归纳法。当 $|S|\leq 3$ 时，命题显然成立。
        
        假设命题对所有元素个数小于 $|S|$ 的偏序集都成立，令 $S$ 的宽度为 $d$. 若 $|S|$ 中所有元素均不可比，则命题显然成立，否则在 $S$ 中取一条长度大于 $1$ 的链，令其中的最小元为 $m$，最大元为 $M$.
        
        令 $T=S\setminus\{m,M\}$，若 $T$ 中的宽度不超过 $d-1$，则由归纳假设知 $T$ 可被至多 $d-1$ 条链覆盖，进而 $S$ 可被这些链再加上链 $\{m,M\}$ 覆盖，命题成立，否则说明 $T$ 中的宽度也为 $d$，令 $T$ 中最长的一条反链为 $A$.
        
        我们考虑如下两个集合：
        
        $$
        S^+:=\{x\in S:(\exists~a\in A)~~a\preceq x\}
        $$
        
        $$
        S^-:=\{x\in S:(\exists~a\in A)~~x\preceq a\}
        $$
        
        我们不难发现如下性质：
        
        -   $S^+\cup S^-=S$，
        -   $S^+\cap S^-=A$，
        -   $|S^+|<|S|$,$|S^-|<|S|$（因为 $m\notin S^+$ 且 $M\notin S^-$）。
        
        对 $S^+$ 和 $S^-$ 都应用归纳假设，则这两个集合的最小链覆盖数为 $d$，且这些链中恰好包含一个 $A$ 中的元素 $a$，设这些链分别为 $C_a^+$，$C_a^-$，则 $\{C_a^-\cup\{a\}\cup C_a^+\}_{a\in A}$ 是 $S$ 的一个最小链覆盖，命题得证。

???+ note "Mirsky 定理"
    $S$ 的最长链长度等于最小的反链覆盖数。
    
    ??? note "证明"
        设 $S$ 的最长链长度为 $d$，则由定义，最小反链覆盖数至少为 $d$.
        
        令 $f(s)$ 为以 $s$ 为最小元的最长链长度，注意到若 $f(s)=f(t)$，则 $s$ 与 $t$ 不可比，进而 $(\forall~n\in\mathbf{N})~~f^{-1}(\{n\})$ 均为反链，其中 $f^{-1}(\{n\}):=\{a\in S:f(a)=n\}$ 称为 [水平集（level set）](https://en.wikipedia.org/wiki/Level_set)。
        
        因此不难得出 $\{f^{-1}(\{i\}):1\leq i\leq d\}$ 是一个反链覆盖，从而最小反链覆盖数至多为 $d$.

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
        
        进而根据 Dilworth 定理有：**序列的不上升子序列的最少覆盖数等于最长上升子序列长度**。从而可以通过 [最长不下降子序列的 $O(n\log n)$ 做法](../dp/basic.md#算法二2) 解决本题。
    
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

### 习题

-   [\[CTSC2008\] 祭祀](https://www.luogu.com.cn/problem/P4298)
-   [CodeForces 590E Birthday](https://codeforces.com/problemset/problem/590/E)

## C++ 中的应用

另请参阅：[排序相关 STL -  算法基础](../basic/stl-sort.md)。

C++ STL 中 [需要使用比较的算法和数据结构](https://en.cppreference.com/w/cpp/named_req/Compare#Standard_library) 中有序理论的应用。我们经常需要在 C++ 中自定义比较器，STL [要求](https://en.cppreference.com/w/cpp/named_req/Compare) 其必须为 **严格弱序**。令 $<$ 为自定义比较器，则可以定义：

-   $x>y$ 为 $y<x$；
-   $x \leq y$ 为 $y \nless x$；
-   $x \geq y$ 为 $x \nless y$；
-   $x=y$ 为 $x \nless y\land y \nless x$.

## 参考资料与拓展阅读

1.  [Order theory - From Academic Kids](https://academickids.com/encyclopedia/index.php/Order_theory)
2.  [Binary Relation - Wikipedia](https://en.wikipedia.org/wiki/Binary_relation)
3.  [Order Theory - Wikipedia](https://en.wikipedia.org/wiki/Order_theory)
4.  [Hasse diagram - Wikipedia](https://en.wikipedia.org/wiki/Hasse_diagram)
5.  [Directed set - Wikipedia](https://en.wikipedia.org/wiki/Directed_set)
6.  [Order Theory, Lecture Notes by Mark Dean for Decision Theory](http://www.columbia.edu/~md3405/DT_Order_15.pdf)
7.  卢开澄，卢华明，[《组合数学》（第 3 版）](http://www.tup.tsinghua.edu.cn/bookscenter/book_00458101.html), 2006
8.  [List of Order Theory Topics - Wikipedia](https://en.wikipedia.org/wiki/List_of_order_theory_topics)
9.  [浅谈邻项交换排序的应用以及需要注意的问题 by ouuan](https://ouuan.github.io/post/%E6%B5%85%E8%B0%88%E9%82%BB%E9%A1%B9%E4%BA%A4%E6%8D%A2%E6%8E%92%E5%BA%8F%E7%9A%84%E5%BA%94%E7%94%A8%E4%BB%A5%E5%8F%8A%E9%9C%80%E8%A6%81%E6%B3%A8%E6%84%8F%E7%9A%84%E9%97%AE%E9%A2%98/)
10. [One thing you should know about comparators—Strict Weak Ordering](https://codeforces.com/blog/entry/72525)
11. [Dilworth's theorem - Wikipedia](https://en.wikipedia.org/wiki/Dilworth%27s_theorem)
12. [Dilworth's Theorem | Brilliant Math & Science Wiki](https://brilliant.org/wiki/dilworths-theorem/)
13. [Hall's marriage theorem - Wikipedia](https://en.wikipedia.org/wiki/Hall's_marriage_theorem)
14. [Hall's Marriage Theorem | Brilliant Math & Science Wiki](https://brilliant.org/wiki/hall-marriage-theorem/)
15. [Dilworth 学习笔记 - Selfish](https://www.luogu.com.cn/blog/Rolling-Code/dilworth)
