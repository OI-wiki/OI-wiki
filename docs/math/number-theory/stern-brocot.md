## 连分数的树

有两种主要方法，可以将所有可能的连分数，合并为有用的树结构。

### Stern–Brocot 树

#### 定义

Stern–Brocot 树是一种维护分数的优雅的结构，包含所有不同的正有理数。这个结构由 Moritz Stern 在 1858 年和 Achille Brocot 在 1861 年发现。

#### 解释

Stern–Borcot 树从两个简单的分数开始：

$$
\frac{0}{1}, \frac{1}{0}
$$

这个 $\frac{1}{0}$ 可能看得你有点懵逼。不过我们不讨论这方面的严谨性，你只需要把它当作 $\infty$ 就行了。

每次在相邻的两个分数 $\frac{a}{b},\frac{c}{d}$ 中间插入一个分数 $\frac{a+c}{b+d}$，这样就完成了一次迭代，得到下一个序列。于是它就会变成这样

$$
\begin{array}{ccccccccc}
&&&\dfrac{0}{1}, & \dfrac{1}{1}, & \dfrac{1}{0} &&&\\\\
&&\dfrac{0}{1}, & \dfrac{1}{2}, & \dfrac{1}{1}, & \dfrac{2}{1}, & \dfrac{1}{0} &&\\\\
\dfrac{0}{1}, & \dfrac{1}{3}, & \dfrac{1}{2}, & \dfrac{2}{3}, & \dfrac{1}{1}, & \dfrac{3}{2}, & \dfrac{2}{1}, & \dfrac{3}{1}, & \dfrac{1}{0}
\end{array}
$$

既然称它为 Stern–Brocot 树，那么它总得有一个树的样子。来一张图：

![pic](./images/stern-brocot1.png)

可以把第 $i$ 层的序列当作是深度为 $i-1$ 的 Stern–Brocot 树的中序遍历。

#### 性质

接下来讨论 Stern–Brocot 树的性质。

##### 单调性

在每一层的序列中，真分数是单调递增的。

略证：只需要在 $\frac{a}{b}\le \frac{c}{d}$ 的情况下证明

$$
\frac{a}{b}\le \frac{a+c}{b+d}\le \frac{c}{d}
$$

就行了。这个很容易，直接做一下代数变换即可

$$
\begin{aligned}
             & \frac{a}{b}\le \frac{c}{d}    \\
    \implies & ad\le bc                      \\
    \implies & ad+ab\le bc+ab                \\
    \implies & \frac{a}{b}\le\frac{a+c}{b+d}
\end{aligned}
$$

另一边同理可证。

##### 最简性

序列中的分数（除了 $\frac{0}{1},\frac{1}{0}$）都是最简分数。

略证：为证明最简性，我们首先证明对于序列中连续的两个分数 $\frac{a}{b},\frac{c}{d}$：

$$
bc-ad=1
$$

显然，只需要在 $bc-ad=1$ 的条件下证明 $\frac{a}{b}, \frac{a+c}{b+d}, \frac{c}{d}$ 的情况成立即可。

$$
a(b+d)-b(a+c)=ad-bc=1
$$

后半部分同理。证明了这个，利用扩展欧几里德定理，如果上述方程有解，显然 $\gcd(a,b)=\gcd(c,d)=1$。这样就证完了。

有了上面的证明，可以证明 $\frac{a}{b}<\frac{c}{d}$。

有了这两个性质，就可以把它当成一棵平衡树来做了。建立和查询就向平衡树一样做就行了。

##### 连分数表示与父子节点

递推 $\frac{p_k}{q_k}=\frac{a_k p_{k-1} + p_{k-2}}{a_k q_{k-1} + q_{k-2}}$，意味着连分数表示对树中 $\frac{p_k}{q_k}$ 的路径进行编码。要查找 $[a_0; a_1, \dots, a_{k}, 1]$，必须使 $a_0$ 向右移动，$a_1$ 向左移动，$a_2$ 向右移动等等，直到 $a_k$。

连分数节点 $[a_0; a_1, \dots, a_k,1]$ 的父节点是沿最后使用的方向后退一步获得的分数。

换句话说，当 $a_k>1$ 时，它是 $[a_0; a_1, \dots, a_k-1,1]$，而当 $a_k=1$ 时，则是 $[a_0; a_1, \dots, a_{k-1}, 1]$。

因此，$[a_0; a_1, \dots, a_k, 1]$ 的子节点是 $[a_0; a_1, \dots, a_k+1, 1]$ 和 $[a_0; a_1, \dots, a_k, 1, 1]$。

##### 索引

为 Stern Brocot 树编制索引。根顶点被分配了一个索引 $1$。然后，对于顶点 $v$，通过将 $v$ 的前导位从 $1$ 更改为 $10$ 来分配其左子节点的索引，对于右子节点，通过将前导位从 $1$ 更改为 $11$ 来分配索引：

![pic](./images/Stern-brocot-index.svg)

在这种索引中，连分数表示规定了有理数的 **游程长度编码**（run-length encoding）。

对于 $\frac{5}{2} = [2;2] = [2;1,1]$，其索引为 $1011_2$，其游程长度编码（考虑按升序排列的位）为 $[2;1,1]$。

另一个例子是 $\frac{2}{5} = [0;2,2]=[0;2,1,1]$，其索引为 $1100_2$，其游程编码实际上为 $[0;2,2]$。

值得注意的是，Stern–Brocot 树实际上是一个堆。也就是说，它是 $\frac{p}{q}$ 的二叉树，它也是 $p$ 和 $q$ 的堆。

#### 实现

构建实现

=== "C++"
    ```cpp
    void build(int a = 0, int b = 1, int c = 1, int d = 0, int level = 1) {
      int x = a + c, y = b + d;
      // ... output the current fraction x/y
      // at the current level in the tree
      build(a, b, x, y, level + 1);
      build(x, y, c, d, level + 1);
    }
    ```

=== "Python"
    ```python
    def build(a=1, b=1, c=1, d=0, level=1):
        x = a + c
        y = b + d
        # ... output the current fraction x/y
        # at the current level in the tree
        build(a, b, x, y, level + 1)
        build(x, y, c, d, level + 1)
    ```

查询实现

=== "C++"
    ```cpp
    string find(int x, int y, int a = 0, int b = 1, int c = 1, int d = 0) {
      int m = a + c, n = b + d;
      if (x == m && y == n) return "";
      if (x * n < y * m)
        return 'L' + find(x, y, a, b, m, n);
      else
        return 'R' + find(x, y, m, n, c, d);
    }
    ```

=== "Python"
    ```python
    def find(x, y, a=0, b=1, c=1, d=0):
        m = a + c
        n = b + d
        if x == m and y == n:
            return ""
        if x * n < y * m:
            return "L" + find(x, y, a, b, m, n)
        else:
            return "R" + find(x, y, m, n, c, d)
    ```

#### 例题

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

### Calkin–Wilf 树

#### 定义

在二叉树中组织连分数的一种更简单的方法是 Calkin–Wilf 树。

通常如下所示：

![pic](./images/Calkin–Wilf_tree.svg)

树的根节点为 $\frac{1}{1}$。然后，对于数字为 $\frac{p}{q}$ 的顶点，其子节点为 $\frac{p}{p+q}$ 和 $\frac{p+q}{q}$。

#### 性质

与 Stern–Brocot 树不同，Calkin–Wilf 树不是二叉搜索树，因此不能用于执行有理二叉搜索。

在 Calkin–Wilf 树中，当 $p>q$ 时，分数 $\frac{p}{q}$ 的直接父节点为 $\frac{p-q}{q}$；当 $p<q$ 时，为 $\frac{p}{q-p}$。

在 Stern–Brocot 树中使用了收敛的递归。为了得出连分数和 Calkin–Wilf 树之间的联系，应该使用完整商（complete quotients）的递归。如果 $s_k = \frac{p}{q}$，则 $s_{k+1} = \frac{q}{p \mod q} = \frac{q}{p-\lfloor p/q \rfloor \cdot q}$。

另一方面，当 $p>q$ 时，在 Calkin–Wilf 树中重复从 $s_k = \frac{p}{q}$ 到它的父节点，那么将以 $\frac{p \mod q}{q} = \frac{1}{s_{k+1}}$ 结尾。如果继续这样做，将以 $s_{k+2}$，然后 $\frac{1}{s_{k+3}}$ 等结尾。由此可以推断：

1.  当 $a_0>0$ 时，Calkin–Wilf 树中 $[a_0; a_1, \dots, a_k]$ 的直接父节点为 $\frac{p-q}{q}=[a_0 - 1; a_1, \dots, a_k]$。
2.  当 $a_0=0$ 且 $a_1>1$ 时，其直接父节点为 $\frac{p}{q-p} = [0; a_1 - 1, a_2, \dots, a_k]$。
3.  当 $a_0=0$ 且 $a_1=1$ 时，其直接父节点为 $\frac{p}{q-p} = [a_2; a_3, \dots, a_k]$。

相应地，$\frac{p}{q} = [a_0; a_1, \dots, a_k]$ 的子节点为

1.  $\frac{p+q}{q}=1+\frac{p}{q}$，即 $[a_0+1; a_1, \dots, a_k]$。
2.  $\frac{p}{p+q} = \frac{1}{1+\frac{q}{p}}$，对于 $a_0>0$，它是 $[0, 1, a_0, a_1, \dots, a_k]$；对于 $a_0=0$，则是 $[0, a_1+1, a_2, \dots, a_k]$。

值得注意的是，如果以广度优先搜索顺序枚举 Calkin–Wilf 树的顶点（即，根有一个数字 $1$，而顶点 $v$ 的子节点有相应的索引 $2v$ 和 $2v+1$），Calkin–Welf 树中有理数的索引将与 Stern–Brocot 树中的索引相同。

因此，Stern–Brocot 树和 Calkin–Wilf 树的相同级别上的数字是相同的，但它们的排序通过 **位反转排列**（bit-reversal permutation）而不同。

## Farey 序列

### 定义

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

**本页面主要译自博文 [Дерево Штерна-Броко. Ряд Фарея](http://e-maxx.ru/algo/stern_brocot_farey) 与其英文翻译版 [The Stern-Brocot Tree and Farey Sequences](https://cp-algorithms.com/others/stern_brocot_tree_farey_sequences.html)。其中俄文版版权协议为 Public Domain + Leave a Link；英文版版权协议为 CC-BY-SA 4.0。**
