## 引入

本文介绍存储最简分数的数据结构以及其它相关概念。它们与 [连分数](./continued-fraction.md) 紧密相关，在算法竞赛中可以用于解决一系列数论问题，并可能作为某些题目的隐含背景出现。

## Stern–Brocot 树

Stern–Brocot 树是一种维护分数的优雅的结构，包含所有不同的正有理数。这个结构分别由 Moritz Stern 在 1858 年和 Achille Brocot 在 1861 年独立发现。

### 逐层构造

Stern–Borcot 树可以通过迭代构造第 $k$ 阶 Stern–Brocot 序列（Stern–Brocot sequence of order $k$）得到。第 $0$ 阶 Stern–Brocot 序列由两个简单的分数组成：

$$
\frac{0}{1},\ \frac{1}{0}.
$$

此处的 $\dfrac{1}{0}$ 严格意义上并不算是有理分数，可以理解为表示 $\infty$ 的最简分数。

在第 $k$ 阶 Stern–Brocot 序列相邻的两个分数 $\dfrac{a}{b}$ 和 $\dfrac{c}{d}$ 中间插入它们的中位分数（mediant）[^mediant] $\dfrac{a+c}{b+d}$（不要通分），就得到第 $k+1$ 阶 Stern–Brocot 序列。由此，可以迭代地构造出所有阶的 Stern–Brocot 序列。前几次迭代的结果如下：

$$
\begin{array}{ccccccccc}
&&&\dfrac{0}{1}, & \dfrac{1}{1}, & \dfrac{1}{0} &&&\\\\
&&\dfrac{0}{1}, & \dfrac{1}{2}, & \dfrac{1}{1}, & \dfrac{2}{1}, & \dfrac{1}{0} &&\\\\
\dfrac{0}{1}, & \dfrac{1}{3}, & \dfrac{1}{2}, & \dfrac{2}{3}, & \dfrac{1}{1}, & \dfrac{3}{2}, & \dfrac{2}{1}, & \dfrac{3}{1}, & \dfrac{1}{0}
\end{array}
$$

将每次迭代中新添加的分数连结成树状结构，就得到了 Stern–Brocot 树。如下图所示：

![pic](./images/stern-brocot1.png)

第 $k$ 阶 Stern–Brocot 序列，不计左右端点，就是深度为 $k-1$ 的 Stern–Brocot 树的中序遍历。

### 三元组构造

另一种等价的构造方式是以三元组

$$
\left(\dfrac{0}{1},\dfrac{1}{1},\dfrac{1}{0}\right)
$$

作为根节点，且在每个节点

$$
\left(\dfrac{a}{b},\dfrac{p}{q},\dfrac{c}{d}\right)
$$

后都分别添加

$$
\left(\dfrac{a}{b},\dfrac{a+p}{b+q},\dfrac{p}{q}\right),\ \left(\dfrac{p}{q},\dfrac{p+c}{q+d},\dfrac{c}{d}\right)
$$

为左右子节点，就可以构造出整个 Stern–Brocot 树。Stern–Brocot 树的每个节点记录的三元组中，实际存储的分数是位于三元组中间的分数 $\dfrac{p}{q}$，而左右两个分数 $\dfrac{a}{b}$ 和 $\dfrac{c}{d}$ 是更早就出现过的分数。而且，在前一个构造中，分数 $\dfrac{p}{q}$ 正是通过插入 $\dfrac{a}{b}$ 和 $\dfrac{c}{d}$ 的中位分数得到的。

#### 建树实现

建树算法只需要模拟上述过程即可。下面是对前 $n$ 层的 Stern–Brocot 树做中序遍历的代码。

???+ example "建树"
    === "C++"
        ```cpp
        --8<-- "docs/math/code/stern-brocot/tree-build.cpp:3:10"
        ```

    === "Python"
        ```py
        --8<-- "docs/math/code/stern-brocot/tree-build.py:2:9"
        ```

建树算法的复杂度是 $O(n^2)$ 的。

### 性质

接下来讨论 Stern–Brocot 树的性质。简而言之，Stern–Brocot 树是包含所有正的最简有理分数的 [二叉搜索树](../../ds/bst.md)，它也是分子和分母的 [堆](../../ds/binary-heap.md)，也是分母和分子构成的二元组的 [笛卡尔树](../../ds/cartesian-tree.md)。如果考虑前文的三元组构造中的左右端点形成的区间，则 Stern–Brocot 树也可以看作是 $[0,\infty]$ 上的 [线段树](../../ds/seg.md)。 

#### 单调性

在上面的构造中，每一层的分数都是单调递增的。为此只需要归纳证明。因为如果 $\dfrac{a}{b} < \dfrac{c}{d}$，那么必然有

$$
\dfrac{a}{b} < \dfrac{a+b}{c+d} < \dfrac{c}{d}.
$$

这一点可以通过消去不等式的分母得出。归纳起点是 $\dfrac{0}{1} < \dfrac{1}{0}$，这也是显然的。

#### 最简性

在上面的构造中，每个分数都是最简分数。为此同样需要归纳证明上面的构造中，每一层相邻的分数 $\dfrac{a}{b}$ 和 $\dfrac{c}{d}$ 都满足等式

$$
ad-bc = \det\begin{pmatrix}a & c \\ b & d\end{pmatrix} = -1.
$$

根据 [行列式](../linear-algebra/determinant.md) 的性质可知，在下一层同样成立

$$
\det\begin{pmatrix}a & a+c \\ b & b+d\end{pmatrix} = \det\begin{pmatrix}a+c & c \\ b+d & d\end{pmatrix} = -1.
$$

对于归纳起点 $\dfrac{0}{1}$ 和 $\dfrac{1}{0}$ 这也是显然的。由此，根据 [裴蜀定理](./bezouts.md)，必然可知每个分数的分子和分母都是互素的，即所有分数都是最简分数。

#### 完全性

最后，需要说明 Stern–Brocot 树包括了所有正的最简分数。因为前两条性质已经说明 Stern–Brocot 树是二叉搜索树，而任何正的最简分数 $\dfrac{p}{q}$ 必然位于 $\dfrac{0}{1}$ 和 $\dfrac{1}{0}$ 之间，根据二叉搜索树上做搜索的方法，二叉搜索树上没有 $\dfrac{p}{q}$ 的唯一可能性就是搜索过程无限长。这是不可能的。

假设现在已经知道

$$
\dfrac{a}{b} < \dfrac{p}{q} < \dfrac{c}{d},
$$

那么必然有

$$
bp-aq \ge 1,\ cq-dp \ge 1.
$$

将两个不等式分别乘以 $(c+d)$ 和 $(a+b)$，就能够得到

$$
(c+d)(bp-aq) + (a+b)(cq-dp) \ge a+b+c+d.
$$

利用前面已经说明的等式 $bc-ad=1$ 可知

$$
p+q \ge a+b+c+d.
$$

每次搜索更深入一层的时候，等式右侧都严格地增加，因此必然在有限步内停止。

### 查找分数

在实际应用 Stern–Brocot 树的过程中，经常需要查询给定分数在 Stern–Brocot 树上的位置。

#### 朴素算法：Stern–Brocot 数系

因为 Stern–Brocot 是二叉搜索树，只需要通过比较当前分数和要寻找的分数的大小关系，就可以确定从根节点到给定分数的路径。在路径上，每次向左子节点移动记作 `L`，向右子节点移动记作 `R`，那么每条路径都唯一对应着一个由 `L` 和 `R` 组成的字符串。将每个正的有理分数都对应到这样的字符串，就得到 **Stern–Brocot 数系**（Stern–Brocot number system）。

朴素的分数查找算法的实现如下：

???+ example "朴素分数查找"
    === "C++"
        ```cpp
        --8<-- "docs/math/code/stern-brocot/fraction-finding-1.cpp:4:13"
        ```

    === "Python"
        ```python
        --8<-- "docs/math/code/stern-brocot/fraction-finding-1.py:2:11"
        ```

算法的复杂度是 $O(p+q)$ 的，因此在算法竞赛中并不实用。

在 Stern–Brocot 数系中，每个正的无理数都对应着唯一的无限长的字符串。可以使用同样的算法构造出这个字符串。这个无限长的字符串的每个前缀都对应着一个有理的最简分数。将这些最简分数排成一列，数列中的分数的分母是严格递增的，而数列的极限就是该无理数。因此，Stern-Brocot 树可以用于找到某个无理数的任意精度的有理逼近。但是，应当注意的是，这个有理数数列和无理数之间的差距并非严格递减的。对于有理逼近的严格理论，应当参考连分数页面的 [丢番图逼近](./continued-fraction.md#丢番图逼近) 一节。在实际应用 Stern-Brocot 树寻找某个实数在分母不超过某范围的最佳逼近时，最后应当注意比较左右区间端点到该实数的距离。

#### 快速算法

查找分数的朴素算法效率并不高，但是经过简单的优化就可以得到 $O(\log(p+q))$ 的快速查找算法。优化的关键是将连续的 `L` 和 `R` 合并处理。

如果要查找的分数 $\dfrac{p}{q}$ 落入 $\dfrac{a}{b}$ 和 $\dfrac{c}{d}$ 之间，那么连续 $t$ 次向右移动时，右侧边界保持不动，而左侧节点移动到 $\dfrac{a+tc}{b+td}$ 处；反过来，连续 $t$ 次向左移动时，左侧边界保持不动，而右侧节点移动到 $\dfrac{ta+c}{tb+d}$ 处。因此，可以直接通过 $\dfrac{a+tc}{b+td}<\dfrac{p}{q}$ 或 $\dfrac{p}{q}<\dfrac{ta+c}{tb+d}$ 来确定向右和向左移动的次数。此处取严格不等号，是因为算法移动的是左右端点，而要寻找的分数是作为最后得到的端点的中位分数出现的。

???+ example "快速分数查找"
    === "C++"
        ```cpp
        --8<-- "docs/math/code/stern-brocot/fraction-finding-2.cpp:5:25"
        ```

    === "Python"
        ```python
        --8<-- "docs/math/code/stern-brocot/fraction-finding-2.py:2:19"
        ```

当前查找算法需要在分数 $\dfrac{p}{q}$ 已知。如果目标分数未知，往往需要在每次向右或向左移动时，对移动次数进行倍增查找或者二分查找。此时，分数查找算法的复杂度是 $O(\log^2(p+q))$。

#### 连分数表示与树上路径

对于分数已知的情形，可以利用连分数给出更为简单的算法。不妨假设首组移动是向右的；如果不然，则设首组向右移动的次数为零。向右、向左交替移动端点，将每组移动后的端点位置排列如下：

$$
\dfrac{p_0}{q_0},~\dfrac{p_1}{q_1},~\dfrac{p_2}{q_2},~\cdots,~\dfrac{p_{n-2}}{q_{n-2}},~\dfrac{p_{n-1}}{q_{n-1}},~\dfrac{p_n}{q_n}.
$$

其中，偶数组移动是向右的，故而记录的是左端点的位置；奇数组移动是向左的，故而记录的是右端点的位置。在这一列端点前面再添加两个端点

$$
\dfrac{p_{-2}}{q_{-2}}=\dfrac{0}{1},~\dfrac{p_{-1}}{q_{-1}}=\dfrac{1}{0}.
$$

设第 $k$ 组移动的次数为 $t_k$，那么根据上面得到的移动次数与端点位置之间的关系可知

$$
\dfrac{p_k}{q_k} = \dfrac{t_kp_{k-1}+p_{k-2}}{t_kq_{k-1}+q_{k-2}}.
$$

根据连分数的 [递推关系](./continued-fraction.md#递推关系) 就可以知道，端点

$$
\dfrac{p_k}{q_k} = [t_0,t_1,\cdots,t_k].
$$

最后得到的连分数是

$$
\dfrac{p}{q} = \dfrac{p_k+p_{k-1}}{q_k+q_{k-1}} = [t_0,t_1,\cdots,t_{n-1},t_n,1].
$$

因此，在目标分数的末尾为一的 [连分数表示](./continued-fraction.md#简单连分数) 中，不计最后的一，前面的项就编码了 Stern–Brocot 树上自根节点到当前节点的路径。其中，偶数项（下标自 $0$ 开始）是向右子节点的边，奇数项是向左子节点的边。

有理数的连分数表示可以通过辗转相除法求得，因此基于连分数表示的分数查找算法的复杂度是 $O(\log\min\{p,q\})$ 的。

???+ example "基于连分数的分数查找"
    === "C++"
        ```cpp
        --8<-- "docs/math/code/stern-brocot/fraction-finding-3.cpp:5:17"
        ```

    === "Python"
        ```python
        --8<-- "docs/math/code/stern-brocot/fraction-finding-3.py:2:11"
        ```

利用连分数表示，可以简单地表达出某个节点的父节点和子节点。对于节点 $[t_0,t_1,\cdots,t_n,1]$，它的父节点就是沿最后的移动方向少移动一步的节点：在 $t_k>1$ 时，父节点是 $[t_0,t_1,\cdots,t_n - 1,1]$；否则，父节点是 $[t_0,t_1,\cdots,t_{n-1},1]$。它的两个子节点则分别是 $[t_0,t_1,\cdots,t_n+1,1]$ 和 $[t_0,t_1,\cdots,t_n,1,1]$；两个节点哪个是左子节点，哪个是右子节点，需要根据 $n$ 的奇偶性判断。

### 例题

??? 例题 "最佳内点"
    对于 $\frac{0}{1} \leq \frac{p_0}{q_0} < \frac{p_1}{q_1} \leq \frac{1}{0}$，找到有理数 $\frac{p}{q}$ 使得 $(q; p)$ 在字典序最小，并且 $\frac{p_0}{q_0} < \frac{p}{q} < \frac{p_1}{q_1}$。

??? "解答"
    就 Stern–Brocot 树而言，这意味着需要找到 $\frac{p_0}{q_0}$ 和 $\frac{p_1}{q_1}$ 的 LCA。由于 Stern–Brocot 树和连分数之间的联系，该 LCA 将大致对应于 $\frac{p_0}{q_0}$ 和 $\frac{p_1}{q_1}$ 的连分数表示的最大公共前缀。
    
    因此，如果 $\frac{p_0}{q_0} = [a_0; a_1, \dots, a_{k-1}, a_k, \dots]$ 和 $\frac{p_1}{q_1} = [a_0; a_1, \dots, a_{k-1}, b_k, \dots]$ 是无理数，则 LCA 为 $[a_0; a_1, \dots, \min(a_k, b_k)+1]$。
    
    对于有理数 $r_0$ 和 $r_1$，其中之一可能是 LCA 本身，这需要对其进行讨论。为了简化有理数 $r_0$ 和 $r_1$ 的解决方案，可以使用前面问题中导出的 $r_0 + \varepsilon$ 和 $r_1 - \varepsilon$ 的连分数表示。
    
    ```python
    # finds lexicographically smallest (q, p)
    # such that p0/q0 < p/q < p1/q1
    def middle(p0, q0, p1, q1):
        a0 = pm_eps(fraction(p0, q0))[1]
        a1 = pm_eps(fraction(p1, q1))[0]
        a = []
        for i in range(min(len(a0), len(a1))):
            a.append(min(a0[i], a1[i]))
            if a0[i] != a1[i]:
                break
        a[-1] += 1
        p, q = convergents(a)
        return p[-1], q[-1]
    ```

??? 例题 "[GCJ 2019, Round 2 - New Elements: Part 2](https://codingcompetitions.withgoogle.com/codejam/round/0000000000051679/0000000000146184)"
    您得到 $N$ 个正整数对 $(C_i, J_i)$。您需要找到一个正整数对 $(x, y)$，这样 $C_i x + J_i y$ 就是一个严格递增的序列。
    
    在这类配对中，找到词典中最小的一对。

??? "解答"
    重新表述语句，$A_i x + B_i y$ 对于所有 $i$ 都必须为正，其中 $A_i = C_i - C_{i-1}$，$B_i = J_i - J_{i-1}$。
    
    在这些方程中，对于 $A_i x + B_i y > 0$，有四个情况：
    
    1.  $A_i, B_i > 0$ 可以忽略，因为正在查找 $x, y > 0$。
    2.  $A_i, B_i \leq 0$ 将提供「IMPOSSIBLE」作为答案。
    3.  $A_i > 0$,$B_i \leq 0$。这样的约束相当于 $\frac{y}{x} < \frac{A_i}{-B_i}$。
    4.  $A_i \leq 0$,$B_i > 0$。这样的约束相当于 $\frac{y}{x} > \frac{-A_i}{B_i}$。
    
    让 $\frac{p_0}{q_0}$ 是第四组中最大的 $\frac{-A_i}{B_i}$，而 $\frac{p_1}{q_1}$ 则是第三组中最小的 $\frac{A_i}{-B_i}$。
    
    现在的问题是，给定 $\frac{p_0}{q_0} < \frac{p_1}{q_1}$，找到一个分数 $\frac{p}{q}$ 使得 $(q;p)$ 在字典上最小，并且 $\frac{p_0}{q_0} < \frac{p}{q} < \frac{p_1}{q_1}$。
    
    ```python
    def solve():
        n = int(input())
        C = [0] * n
        J = [0] * n
        # p0/q0 < y/x < p1/q1
        p0, q0 = 0, 1
        p1, q1 = 1, 0
        fail = False
        for i in range(n):
            C[i], J[i] = map(int, input().split())
            if i > 0:
                A = C[i] - C[i - 1]
                B = J[i] - J[i - 1]
                if A <= 0 and B <= 0:
                    fail = True
                elif B > 0 and A < 0:  # y/x > (-A)/B if B > 0
                    if (-A) * q0 > p0 * B:
                        p0, q0 = -A, B
                elif B < 0 and A > 0:  # y/x < A/(-B) if B < 0
                    if A * q1 < p1 * (-B):
                        p1, q1 = A, -B
        if p0 * q1 >= p1 * q0 or fail:
            return "IMPOSSIBLE"
        p, q = middle(p0, q0, p1, q1)
        return str(q) + " " + str(p)
    ```

## Calkin–Wilf 树

另外一种更为简单的存储正有理分数的结构是 Calkin–Wilf 树。它通常如下所示：

![pic](./images/Calkin–Wilf_tree.svg)

树的根节点为 $\dfrac{1}{1}$。然后，对于分数 $\dfrac{p}{q}$ 所在的节点，其左右子节点分别为 $\dfrac{p}{p+q}$ 和 $\dfrac{p+q}{q}$。与 Stern–Brocot 树类似，它的每个分数都是最简分数，且包括全体正的最简分数各恰好一次。

### 与连分数的关系

另一方面，与 Stern–Brocot 树不同，Calkin–Wilf 树不是二叉搜索树，因此不能用于二分查找有理数。

在 Calkin–Wilf 树中，当 $p>q$ 时，分数 $\dfrac{p}{q}$ 的父节点为 $\dfrac{p-q}{q}$；当 $p<q$ 时，为 $\dfrac{p}{q-p}$。对于第一种情形，自 $\dfrac{p}{q}$ 出发，它是父节点的右子节点，可以一直通过父节点的右边向上移动，直到分子不再大于分母为止，此时节点存储的分数是 $\dfrac{p\bmod q}{q}$，本组移动的次数是 $\left\lfloor\dfrac{p}{q}\right\rfloor$；对于第二种情形，它是父节点的左子节点，可以一直通过父节点的左边向上移动，直到分母不再大于分子为止，此时节点存储的分数是 $\dfrac{p}{q\bmod q}$，本组移动的次数是 $\left\lfloor\dfrac{q}{p}\right\rfloor$。

利用连分数的语言，设当前的节点存储的是某个连分数的余项 $s_k$，则沿父节点的右边向上移动 $\lfloor s_k\rfloor$ 次，到达分数 $\dfrac{1}{s_{k+1}}$，随后沿父节点的左边移动 $\lfloor s_{k+1}\rfloor$ 次，到达分数 $s_{k+2}$。因此，从节点 $s_0=\dfrac{p}{q}$ 开始向上到达根节点 $\dfrac{1}{1}$ 的路径由连分数 $[t_0,t_1,\cdots,t_n,1]$ 编码：除去最后的 $1$，偶数项（下标自 $0$ 开始）表示沿父节点的右边移动的次数，奇数项表示沿父节点的左边移动的次数。

对于分数 $\dfrac{p}{q}=[t_0,t_1,\cdots,t_n,1]$ 所在的节点，它的父节点有如下表示：

1.  当 $t_0>0$ 时，它的父节点为 $\dfrac{p-q}{q}=[t_0 - 1, t_1, \cdots, t_n,1]$；
2.  当 $t_0=0$ 且 $t_1>1$ 时，它的父节点为 $\dfrac{p}{q-p} = [0, t_1 - 1, t_2, \cdots, t_n,1]$；
3.  当 $t_0=0$ 且 $t_1=1$ 时，它的父节点为 $\dfrac{p}{q-p} = [t_2, t_3, \cdots, t_n,1]$。

反过来，它的子节点则分别是 $\dfrac{p+q}{q}=[t_0+1,t_1,\cdots,t_n,1]$ 和 $\dfrac{p}{p+q}=[0,1,t_0,t_1,\cdots,t_n,1]$。对于第二个子节点的连分数表示，在 $t_0=0$ 时，应当理解为 $[0,1+t_1,\cdots,t_n,1]$。

### 与 Stern–Brocot 树的关系

同样和连分数建立起联系，Stern–Brocot 树中路径上节点呈现的是渐近分数的递归关系，而 Calkin–Wilf 树中路径上节点呈现的是余项的递归关系。同一个分数的连分数表示是一定的，因此它在 Calkin–Wilf 树上到达根节点的路径和 Stern–Brocot 树的根节点到它的路径是完全一样的。但是，由于路径的方向相反，所以虽然 Stern–Brocot 树和 Calkin–Wilf 树同一层存储的分数是一样的，但是位置并不相同。

如果对两个树分别做 [广度优先搜索](../../graph/bfs.md) 并依次对节点编号，根节点编号为 $1$，那么编号为 $v$ 的节点的左右子节点分别是 $2v$ 和 $2v+1$。从编号的二进制表示来看，除去起始的 $1$，从高位至低位每个 $1$ 均表示向右子节点移动，每个 $0$ 均表示向左子节点移动。Calkin–Wilf 树上，连分数 $[t_0,t_1,\cdots,t_n,1]$ 表示的有理数所在节点的编号是

$$
1\cdots \underbrace{0\cdots 0}_{t_3}\underbrace{1\cdots 1}_{t_2}\underbrace{0\cdots 0}_{t_1}\underbrace{1\cdots 1}_{t_0}.
$$

相应地，Stern–Brocot 树上，连分数 $[t_0,t_1,\cdots,t_n,1]$ 表示的有理数所在节点的编号是

$$
1\underbrace{1\cdots 1}_{t_0}\underbrace{0\cdots 0}_{t_1}\underbrace{1\cdots 1}_{t_2}\underbrace{0\cdots 0}_{t_3}\cdots.
$$

删去初始的 $1$，余下的二进制位组成的编号，恰为同一层的顶点自左向右的编号（自 $0$ 开始）。此处的推导说明，Stern–Brocot 树和 Calkin–Wilf 树中同一层的分数的排列互为位逆序置换（bit-reversal permutation），即将下标的二进制位（补齐起始的 $0$）反转得到的 $0\sim (2^k-1)$ 上的置换。

正因如此，Stern–Brocot 树上的节点有时会按照对应的 Calkin–Wilf 树上的节点编号，由此得到的编号如下图所示：

![pic](./images/Stern-brocot-index.svg)

这个编号可以递归地构造。根节点编号为 $1$，每次移动到左子节点时，就将编号首位的 $1$ 替换成 $10$，而移动到右子节点时，就将编号首位的 $1$ 替换成 $11$。对该编号自右向左就可以解读出自根节点到该节点的路径。

### Stern 双原子序列

将 Calkin–Wilf 树中的所有分数按照广度优先搜索的编号排列，或将 Stern–Brocot 树中的所有分数按照上图所示的编号排列，就得到如下序列：

$$
\frac{1}{1},~\dfrac{1}{2},~\dfrac{2}{1},~\dfrac{1}{3},~\dfrac{3}{2},~\dfrac{2}{3},~\dfrac{3}{1},~\dfrac{1}{4},~\dfrac{4}{3},~\dfrac{3}{5},~\dfrac{5}{2},\cdots.
$$

利用 Calkin–Wilf 树的构造过程，可以证明，该序列中相邻的两个分数，前一个的分母必然等于后一个的分子。将分子单独列出，就得到 Stern 双原子序列（Stern diatomic sequence, [OEIS A002487](https://oeis.org/A002487)），也称为 Stern–Brocot 序列（Stern–Brocot sequence）。序列的编号从 $1$ 开始，并规定第 $0$ 个数是 $0$。

设 $a_n$ 是 Stern 双原子序列中第 $n$ 个数，那么，它满足如下递归关系：

$$
\begin{aligned}
a_{2n} &= a_n,\\
a_{2n+1} &= a_n + a_{n+1}. 
\end{aligned}
$$

递归起点是 $a_0=0$ 和 $a_1=1$。要求得 Stern 双原子序列中 $a_n$ 的值，直接利用递归关系复杂度为 $O(\log^2n)，并不优秀，应当将它视为 Calkin–Wilf 树上编号为 $n$ 的分数的分子，利用连分数的递归关系求解，复杂度为 $O(\log n)$。

## Farey 序列

Stern–Brocot 树与 Farey 序列有着极其相似的特征。第 $i$ 个 Farey 序列记作 $F_i$，表示把分母小于等于 $i$ 的所有最简真分数按大小顺序排列形成的序列。

$$
\begin{array}{lllllllllllll}
F_1=\bigg\{&\dfrac{0}{1},&&&&&&&&&&\dfrac{1}{1}&\bigg\}\\\\
F_2=\bigg\{&\dfrac{0}{1},&&&&&\dfrac{1}{2},&&&&&\dfrac{1}{1}&\bigg\}\\\\
F_3=\bigg\{&\dfrac{0}{1},&&&\dfrac{1}{3},&&\dfrac{1}{2},&&\dfrac{2}{3},&&&\dfrac{1}{1}&\bigg\}\\\\
F_4=\bigg\{&\dfrac{0}{1},&&\dfrac{1}{4},&\dfrac{1}{3},&&\dfrac{1}{2},&&\dfrac{2}{3},&\dfrac{3}{4},&&\dfrac{1}{1}&\bigg\}\\\\
F_5=\bigg\{&\dfrac{0}{1},&\dfrac{1}{5},&\dfrac{1}{4},&\dfrac{1}{3},&\dfrac{2}{5},&\dfrac{1}{2},&\dfrac{3}{5},&\dfrac{2}{3},&\dfrac{3}{4},&\dfrac{4}{5},&\dfrac{1}{1}&\bigg\}
\end{array}
$$

显然，上述构建 Stern–Brocot 树的算法同样适用于构建 Farey 序列。因为 Stern–Brocot 树中的数是最简分数，因此在边界条件（分母）稍微修改一下就可以形成构造 Farey 序列的代码。可以认为 Farey 序列 $F_i$ 是 Stern–Brocot 第 $i-1$ 次迭代后得到的序列的子序列。

Farey 序列同样满足最简性和单调性，并且满足一个与 Stern–Brocot 树相似的性质：对于序列中连续的三个数 $\dfrac ab,\dfrac xy,\dfrac cd$，有 $x=a+c,y=b+d$。这个可以轻松证明，不再赘述。

由 Farey 序列的定义，可以得到 $F_i$ 的长度 $L_i$ 公式为：

$$
\begin{aligned}
L_i=L_{i-1}+\varphi(i)\\
L_i=1+\sum_{k=1}^i\varphi(k)
\end{aligned}
$$

## 习题

-   [Luogu P5179. Fraction](https://www.luogu.com.cn/problem/P5179)
-   [AtCoder ABC333G. Nearest Fraction](https://atcoder.jp/contests/abc333/tasks/abc333_g)
-   [LOJ 6685. 迷宫](https://loj.ac/p/6685)
-   [Luogu P8058. \[BalkanOI2003\] Farey 序列](https://www.luogu.com.cn/problem/P8058)
-   [UVa 12995. Farey Sequence](https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=862&page=show_problem&problem=4878)
-   [AtCoder ARC123F. Insert Addition](https://atcoder.jp/contests/arc123/tasks/arc123_f)
-   [UVa 12438. Farey Polygon](https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=279&page=show_problem&problem=3869)


## 参考资料

**本页面部分内容译自博文 [Дерево Штерна-Броко. Ряд Фарея](http://e-maxx.ru/algo/stern_brocot_farey) 与其英文翻译版 [The Stern-Brocot Tree and Farey Sequences](https://cp-algorithms.com/others/stern_brocot_tree_farey_sequences.html)。其中俄文版版权协议为 Public Domain + Leave a Link；英文版版权协议为 CC-BY-SA 4.0。本页面另有部分内容译自博文 [Continued fractions](https://cp-algorithms.com/algebra/continued-fractions.html)，版权协议为 CC-BY-SA 4.0。内容均有改动。**

[^mediant]: 译名来自张明尧、张凡翻译的《具体数学》第 4.5 节。
