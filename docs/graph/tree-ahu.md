author: Backl1ght

AHU 算法用于判断两棵有根树是否同构。

判断树同构外还有一种常见的做法是 [树哈希](/graph/tree-hash)。

前置知识：[树基础](/graph/tree-basic)，[树的重心](/graph/tree-centroid)

建议配合参考资料里给的例子观看。

## 树同构的定义

### 有根树同构

对于两棵有根树 $T_1(V_1,E_1,r_1)$ 和 $T_2(V_2,E_2,r_2)$，如果存在一个双射 $\varphi: V_1 \rightarrow V_2$，使得

$$
\forall u,v \in V_1,(u,v) \in E_1 \iff (\varphi(u),\varphi(v))  \in E_2
$$

**且** $\varphi(r_1)=r_2$ 成立，那么称有根树 $T_1(V_1,E_1,r_1)$ 和 $T_2(V_2,E_2,r_2)$ 同构。

### 无根树同构

对于两棵无根树 $T_1(V_1,E_1)$ 和 $T_2(V_2,E_2)$，如果存在一个双射 $\varphi: V_1 \rightarrow V_2$，使得

$$
\forall u,v \in V_1,(u,v) \in E_1 \iff (\varphi(u),\varphi(v))  \in E_2
$$

成立，那么称无根树 $T_1(V_1,E_1)$ 和 $T_2(V_2,E_2)$ 同构。

简单的说就是，如果能够通过把树 $T_1$ 的所有节点重新标号，使得树 $T_1$ 和树 $T_2$  **完全相同**，那么称这两棵树同构。

## 问题的转化

无根树同构问题可以转化为有根树同构问题。具体方法如下：

对于无根树 $T_1(V_1, E_1)$ 和 $T_2(V_2,E_2)$，先分别找出它们的 **所有** 重心。

-   如果这两棵无根树重心数量不同，那么这两棵树不同构。
-   如果这两颗无根树重心数量都为 $1$，分别记为 $c_1$ 和 $c_2$，那么如果有根树 $T_1(V_1,E_1,c_1)$ 和有根树 $T_2(V_2,E_2,c_2)$ 同构，那么无根树 $T_1(V_1, E_1)$ 和 $T_2(V_2,E_2)$ 同构，反之则不同构。
-   如果这两颗无根树重心数量都为 $2$，分别记为 $c_1,c'_1$ 和 $c_2,c'_2$，那么如果有根树 $T_1(V_1,E_1,c_1)$ 和有根树 $T_2(V_2,E_2,c_2)$ 同构 **或者** 有根树 $T_1(V_1,E_1,c'_1)$ 和 $T_2(V_2,E_2,c_2)$ 同构，那么无根树 $T_1(V_1, E_1)$ 和 $T_2(V_2,E_2)$ 同构，反之则不同构。

所以，只要解决了有根树同构问题，我们就可以把无根树同构问题根据上述方法转化成有根树同构的问题，进而解决无根树同构的问题。

假设有一个可以 $O(\left|V\right|)$ 解决有根树同构问题的算法，那么根据上述方法我们也可以在 $O(\left|V\right|)$ 的时间内解决无根树同构问题。

## 朴素的 AHU 算法

朴素的 AHU 算法是基于括号序的。

### 原理 1

我们知道一段合法的括号序和一棵有根树唯一对应，而且一棵树的括号序是由它的子树的括号序拼接而成的。如果我们通过改变子树括号序拼接的顺序，从而获得了一段新的括号序，那么新括号序对应的树和原括号序对应的树同构。

### 原理 2

树的同构关系是传递的。既如果 $T_1$ 和 $T_2$ 同构，$T_2$ 和 $T_3$ 同构，那么 $T_1$ 和 $T_3$ 同构。

### 推论

考虑求树括号序的递归算法，我们在回溯时拼接子树的括号序。如果在拼接的时候将字典序小的序列先拼接，并将最后的结果记为 $NAME$。

将以节点 $r$ 为根的子树的 $NAME$ 作为节点 $r$ 的 $NAME$，记为 $NAME(r)$，那么对于有根树 $T_1(V_1,E_1,r_1)$ 和 $T_2(V_2,E_2,r_2)$，如果 $NAME(r_1)=NAME(r_2)$，那么 $T_1$ 和 $T_2$ 同构。

### 命名算法

???+ note "实现"
    $$
    \begin{array}{ll}
    1 & \textbf{Input. } \text{A rooted tree }T\\
    2 & \textbf{Output. } \text{The name of rooted tree }T\\
    3 & \text{ASSIGN-NAME(u)}\\
    4 & \qquad \text{if  } u \text{  is a leaf}\\
    5 & \qquad \qquad \text{NAME(} u \text{) = (0)}\\
    6 & \qquad \text{else }\\
    7 & \qquad \qquad \text{for all child } v \text{ of } u\\
    8 & \qquad \qquad \qquad \text{ASSIGN-NAME(}v\text{)}\\
    9 & \qquad \text{sort the names of the children of }u\\
    10 & \qquad \text{concatenate the names of all children }u\text{ to temp}\\
    11 & \qquad \text{NAME(} u \text{) = (temp)}
    \end{array}
    $$

### AHU 算法

???+ note "实现"
    $$
    \begin{array}{ll}
    1 & \textbf{Input. } \text{Two rooted trees }T_1(V_1,E_1,r_1)\text{ and }T_2(V_2,E_2,r_2) \\
    2 & \textbf{Output. } \text{Whether these two trees are isomorphic}\\
    3 & \text{AHU}(T_1(V_1,E_1,r_1), T_2(V_2,E_2,r_2))\\
    4 & \qquad \text{ASSIGN-NAME(}r_1\text{)}\\
    5 & \qquad \text{ASSIGN-NAME(}r_2\text{)}\\
    6 & \qquad \text{if  NAME}(r_1) = \text{NAME}(r_2)\\
    7 & \qquad \qquad \text{return true}\\
    8 & \qquad \text{else}\\
    10 & \qquad \qquad \text{return false}
    \end{array}
    $$

### 复杂度证明

对于一颗有 $n$ 个节点的有根树，假设他是链状的，那么节点名字长度最长可以是 $n$，那么 ASSIGN-NAME 算法的复杂度是 $1+2+\cdots+n$ 的常数倍，即 $\Theta(n^2)$。由此，朴素 AHU 算法的复杂度为 $O(n^2)$。

## 优化的 AHU 算法

朴素的 AHU 算法的缺点是树的 $NAME$ 的长度可能会过长，我们可以针对这一点做一些优化。

### 原理 1

对树进行层次划分，第 $i$ 层的节点到根的最短距离为 $i$。位于第 $i$ 层的节点的 $NAME$ 可以 **只** 由位于第 $i+1$ 层的节点的 $NAME$ 拼接得到。

### 原理 2

在同一层内，节点的 $NAME$ 可以由其在层内的排名唯一标识。

**注意**，这里的排名是对两棵树而言的，假设节点 $u$ 位于第 $i$ 层，那么节点 $u$ 的排名等于所有 $T_1$ 和 $T_2$ 第 $i$ 层的节点中 $NAME$ 比 $NAME(u)$ 小的节点的个数。

### 推论

我们可以将节点原来的 $NAME$ 用其在层内的排名代替，然后把原来拼接节点 $NAME$ 用向数组加入元素代替。

这样用整数和数组来代替字符串，既不会影响算法的正确性，又很大的降低了算法的复杂度。

### 复杂度证明

首先注意到第 $i$ 层由拼接得到的 $NAME$ 的总长度为第 $i$ 层点的度数之和，即第 $i+1$ 层的总点数，以下用 $L_i$ 表示。算法的下一步会将这些 $NAME$ 看成字符串（数组）并排序，然后将它们替换为其在层内的排名（即重新映射为一个数）。以下引理表明了对总长为 $L$ 的 $m$ 个字符串排序的复杂度：

1.  我们可以使用基数排序在 $O(L+|\Sigma|)$ 的时间内完成排序，其中 $|\Sigma|$ 为字符集的大小。（有一些实现细节，参见参考资料）
2.  我们可以使用快速排序在 $O(L \log m)$ 的时间内完成排序。证明的大致思路为快排递归树的高度为 $O(\log m)$，且暴力比较长度为 $\ell_1$ 和 $\ell_2$ 的两个字符串的复杂度为 $O(\min\{\ell_1,\ell_2\})$。

在 AHU 算法中，第 $i$ 层字符串的字符集大小最多为第 $i+1$ 层的点数，即 $L_i$，所以基数排序的复杂度是线性的。根据 $\sum_i L_i=O(n)$，并将每层的复杂度相加后可以看出，若使用字符串的基数排序，则算法的总复杂度为 $T(n)=O(n)$。同理，如果使用快排排序字符串，那么 $T(n)=O(n \log n)$。

## 例题

[SPOJ-TREEISO](https://www.spoj.com/problems/TREEISO/en/)

题意翻译：给你两颗无根树，判断两棵树是否同构。

???+ note "参考代码"
    ```cpp
    --8<-- "docs/graph/code/tree-ahu/tree-ahu_1.cpp"
    ```

## 参考资料

本文大部分内容译自 [Paper](http://wwwmayr.in.tum.de/konferenzen/Jass08/courses/1/smal/Smal_Paper.pdf) 和 [Slide](https://logic.pdmi.ras.ru/~smal/files/smal_jass08_slides.pdf)。参考资料里的证明会更加全面和严谨，本文做了一定的简化。

对 AHU 算法的复杂度分析，以及字符串的线性时间基数排序算法可以参见 The Design and Analysis of Computer Algorithms 的 3.2 节 Radix sorting，以及其中的 Example 3.2。
