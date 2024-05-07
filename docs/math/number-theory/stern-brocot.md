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

??? 例题 "比较连分数的大小"
    对于 $A=[a_0; a_1, \dots, a_n]$ 和 $B=[b_0; b_1, \dots, b_m]$，哪个分数更小？

??? "解答"
    假设 $A$ 和 $B$ 是无理数，它们的连分数表示是 Stern–Brocot 树中的无限下降。
    
    正如已经提到的，在这个表示中，$a_0$ 表示下降中右转的次数，$a_1$ 表示随后左转的次数，依此类推。因此，当比较 $a_k$ 和 $b_k$ 时，如果 $a_k=b_k$，应该继续比较 $a_{k+1}$ 和 $b_{k+1}$。否则，如果在右下降，应该检查是否 $a_k<b_k$；如果在左下降，应检查 $a_k>b_k$，以判断 $a<b$。
    
    换言之，对于无理数 $A$ 和 $B$，当且仅当字典序（lexicographical comparison）有 $(a_0, -a_1, a_2, -a_3, \dots) < (b_0, -b_1, b_2, -b_3, \dots)$ 时，将是 $A<B$。
    
    现在，正式使用 $\infty$ 作为连分数表示的元素，可以模拟无理数 $A-\varepsilon$ 和 $A+\varepsilon$，即比 $A$ 小（大）但比任何其他实数大（小）的元素。具体而言，对于 $A=[a_0; a_1, \dots, a_n]$，这两个元素中的一个可以模拟 $[a_0; a_1, \dots, a_n, \infty]$，另一个可以模拟 $[a_0; a_1, \dots, a_n - 1, 1, \infty]$。
    
    哪一个对应于 $A-\varepsilon$，哪一个对应于 $A+\varepsilon$，可以通过 $n$ 的奇偶性或通过将它们作为无理数进行比较来确定。
    
        # check if a < b assuming that a[-1] = b[-1] = infty and a != b
        def less(a, b):
            a = [(-1)**i*a[i] for i in range(len(a))]
            b = [(-1)**i*b[i] for i in range(len(b))]
            return a < b
    
        # [a0; a1, ..., ak] -> [a0, a1, ..., ak-1, 1]
        def expand(a):
            if a: # empty a = inf
                a[-1] -= 1
                a.append(1)
            return a
    
        # return a-eps, a+eps
        def pm_eps(a):
            b = expand(a.copy())
            a.append(float('inf'))
            b.append(float('inf'))
            return (a, b) if less(a, b) else (b, a)

??? 例题 "最佳内点"
    对于 $\frac{0}{1} \leq \frac{p_0}{q_0} < \frac{p_1}{q_1} \leq \frac{1}{0}$，找到有理数 $\frac{p}{q}$ 使得 $(q; p)$ 在字典序最小，并且 $\frac{p_0}{q_0} < \frac{p}{q} < \frac{p_1}{q_1}$。

??? "解答"
    就 Stern–Brocot 树而言，这意味着需要找到 $\frac{p_0}{q_0}$ 和 $\frac{p_1}{q_1}$ 的 LCA。由于 Stern–Brocot 树和连分数之间的联系，该 LCA 将大致对应于 $\frac{p_0}{q_0}$ 和 $\frac{p_1}{q_1}$ 的连分数表示的最大公共前缀。
    
    因此，如果 $\frac{p_0}{q_0} = [a_0; a_1, \dots, a_{k-1}, a_k, \dots]$ 和 $\frac{p_1}{q_1} = [a_0; a_1, \dots, a_{k-1}, b_k, \dots]$ 是无理数，则 LCA 为 $[a_0; a_1, \dots, \min(a_k, b_k)+1]$。
    
    对于有理数 $r_0$ 和 $r_1$，其中之一可能是 LCA 本身，这需要对其进行讨论。为了简化有理数 $r_0$ 和 $r_1$ 的解决方案，可以使用前面问题中导出的 $r_0 + \varepsilon$ 和 $r_1 - \varepsilon$ 的连分数表示。
    
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

## 中间分数

对于 $0\leq n\leq a_{k+1}$，记中间分数为

$$
F_{k,n}=\frac{np_k+p_{k-1}}{nq_k+q_{k-1}}
$$

中间分数还包含这样的分数：

$$
F_{0,n}=\frac{np_0+p_{-1}}{nq_0+q_{-1}}=\frac{na_0+1}{n}=a_0+\frac{1}{n}
$$

这些中间分数介于 $\dfrac{p_{-1}}{q_{-1}}$ 与 $\dfrac{p_0}{q_0}=a_0$ 之间。

对于给定的 $k$，第 $0$ 个中间分数 $F_{k,0}=\dfrac{p_{k-1}}{q_{k-1}}$ 与最后一个中间分数 $F_{k,0}=\dfrac{p_{k-1}}{q_{k-1}}$ 是渐进分数。

对比上述表达式与

$$
x=\frac{r_{k+1}p_k+p_{k-1}}{r_{k+1}q_k+q_{k-1}}
$$

可以得到 $F_{k,n}=\left[a_0,\ldots,a_k,n\right]$。因此，中间分数也是某个连分数展开的渐进分数，中间分数表达式的分子分母也一定互素。

两个相邻中间分数的差为

$$
F_{k,n+1}-F_{k,n}=\frac{(p_{k-1}q_k-p_kq_{k-1})n+(p_kq_{k-1}-p_{k-1}q_k)(n+1)}{((n+1)q_k+q_{k-1})(nq_k+q_{k-1})}=\frac{(-1)^{k-1}}{((n+1)q_k+q_{k-1})(nq_k+q_{k-1})}
$$

对于确定的 $k$，中间分数随着 $n$ 的增加递增或递减。

定理：对实数 $x$ 与渐进分数 $\dfrac{p_k}{q_k}$，有

$$
\frac{1}{q_k(q_k+q_{k+1})}<\left|x-\frac{p_k}{q_k}\right|<\frac{1}{q_kq_{k+1}}
$$

???+ note "证明"
    一种证法可以定量计算。根据连分数中的定理有
    
    $$
    \left|x-\frac{p_k}{q_k}\right|=\frac{1}{q_k(r_{k+1}q_k+q_{k-1})}
    $$
    
    由于
    
    $$
    a_{k+1}<\lfloor r_{k+1}\rfloor<a_{k+1}+1
    $$
    
    因此
    
    $$
    q_{k+1}=a_{k+1}q_k+q_{k-1}<r_{k+1}q_k+q_{k-1}<a_{k+1}q_k+q_k+q_{k-1}=q_k+q_{k+1}
    $$
    
    取倒数即证毕。
    
    另一种证法使用中间分数。首先，两个相邻渐进分数之间的距离有
    
    $$
    \left|\frac{p_{k+1}}{q_{k+1}}-\frac{p_k}{q_k}\right|=\frac{1}{q_{k+1}q_k}
    $$
    
    由于 $x$ 本身介于两个相邻渐进分数之间，到其中一个渐进分数的距离 $\left|x-\frac{p_k}{q_k}\right|$ 一定小于 $\frac{1}{q_{k+1}q_k}$。不等式右边即证毕。
    
    对于不等式左边，由于对于固定的 $k$，两头的中间分数就是渐进分数，因此有位置关系
    
    $$
    \frac{p_{k-1}}{q_{k-1}}=F_{k,0}~F{k,1}~\frac{p_{k+1}}{q_{k+1}}~x~\frac{p_k}{q_k}
    $$
    
    因此有距离关系
    
    $$
    \left|x-\frac{p_{k-1}}{q_{k-1}}\right|>|F_{k,0}-F_{k,1}|=\frac{1}{q_{k-1}(q_k+q_{k+1})}
    $$
    
    更换下标，不等式左边即证毕。

在使用中这个定理经常放缩一下。由于 $q_k\leq q_{k+1}$，有

$$
\frac{1}{2{q_{k+1}}^2}<\frac{1}{q_k(q_k+q_{k+1})}<\left|x-\frac{p_k}{q_k}\right|<\frac{1}{q_kq_{k+1}}<\frac{1}{{q_k}^2}
$$

右半部分 $\left|x-\frac{p_k}{q_k}\right|<\frac{1}{{q_k}^2}$ 无需计算更高阶的渐进分数，很常用，即下文 Dirichlet 逼近定理的连分数证法。

### Dirichlet 逼近定理

Dirichlet 逼近定理是说，对于任意的一个无理数 $\theta$，均能找到无穷个有理数逼近它，满足不等式：

$\left|\frac{p}{q}-\theta\right|\leqslant\frac{1}{q^2}$

由于任一实数 $qx$ 到最近的整数距离不超过 $\dfrac{1}{2}$，显然存在整数 $p$ 和 $q$ 使得

$$
|qx-p|\leq\frac{1}{2}
$$

$$
\left|x-\frac{p}{q}\right|\leq\frac{1}{2q}
$$

Dirichlet 逼近定理将右侧优化到了 $\dfrac{1}{q^2}$。等价的写法，$|qx-p|<\dfrac{1}{q}$ 总有解。

当 $x$ 是无理数的时候，可以让渐进分数的分母任意大，$|qx-p|$ 任意小。

另外还有瓦伦定理：实数 $x$ 连续两个渐进分数至少有一个满足 $\left|x-\dfrac{p}{q}\right|<\dfrac{1}{2q^2}$，由瓦伦（Vahlen）在 1895 年证明。

另外还有伯雷尔定理：实数 $x$ 连续两个渐进分数至少有一个满足 $\left|x-\dfrac{p}{q}\right|<\dfrac{1}{\sqrt{5}q^2}$，由伯雷尔（Borel）在 1903 年证明。

这个 $\sqrt{5}$ 是最优的，在无理数为例如黄金分割 $\dfrac{1+\sqrt{5}}{2}=\left[1,1,1,\ldots\right]$ 等连分数展开自某位起均为 $1$ 的时候取等。这些后续的定理也同样表明，在 Dirichlet 逼近定理中的小于等于号事实上也可以是小于号。

另外还有定理：实数 $x$ 连分数展开无穷项不小于 $n$，则存在无穷多渐进分数满足 $\left|x-\dfrac{p}{q}\right|<\dfrac{1}{\sqrt{n^2+4}q^2}$。这种条件的极端情形例如 $\dfrac{n+\sqrt{n^2+4}}{2}=\left[n,n,n,\ldots\right]$。

其他的，还有 Kronecker 逼近定理：

如果 $\theta$ 为无理数，$\alpha$ 为实数，则对任意正数 $\varepsilon$, 存在整数 $n$ 和整数 $m$，使得：

$\left|n\theta−m−\alpha\right|<\varepsilon$

Dirichlet 逼近定理和 Kronecker 逼近定理，都可以用抽屉原理来解决。事实上，正是 Dirichlet 为了解决 [Pell 方程](./pell-equation.md)，研究有理数逼近条件，抽屉原理才在历史上被第一次正式提出。

当然，采用抽屉原理的证明可以发现，下文中提到的最佳逼近有理数列，每项满足定理中右边改成分母为一次式的不等式。

进一步有结论，渐进有理数列中，每一项均满足 Dirichlet 逼近定理的不等式。

## 最佳有理逼近

讨论如何用有理数「最佳地」逼近无理数，不妨假设无理数落入 $(0,1)$ 区间。

「最佳」一词的概念：选定的有理数必须保证，比它与无理数的距离更近的有理数，分母都比它大。不存在分母比它小的有理数，到给定无理数的距离更近。

**最佳有理数：在 Farey 数列的某一行中，与给定无理数距离最近的那个有理数。**

这个有理数可能在下面几行依旧与无理数「距离最近」，但一定有某一行，会找到一个新的有理数，与无理数距离更近。因此去重复后可以得到 **最佳逼近有理数列**，分母严格递增，距离递减。

更加严谨的叙述为：

对实数 $x$ 和有理数 $\dfrac{p}{q}$，如果对于任意的整数 $a$ 和整数 $0<b\leq q$，$\dfrac{a}{b}\neq\dfrac{p}{q}$，均有

$$
\left|x-\frac{a}{b}\right|>\left|x-\frac{p}{q}\right|
$$

则称 $\dfrac{p}{q}$ 是 $x$ 的一个最佳有理逼近。

比无理数大的称为上逼近，否则为下逼近。由于无理数和有理数之间一定有有理数，最佳逼近有理数列必然为若干个上逼近，之后若干个下逼近，交替进行的形式。

有结论：

**渐进分数必然为最佳有理逼近。**

**偶项渐进分数全都是下逼近，奇项渐进分数全都是上逼近。渐进分数列是下上交错的逼近。**

在最佳逼近有理数列中，渐进分数是下上关系改变之前的倒数第一个数。如果将最佳逼近有理数列都写成有限简单连分数，那么在渐进分数之后（下上关系改变之后），连分数长度加一。

例如，$[0,2,4,2]$ 是 $\sqrt{6}$ 减去 $2$ 的一个渐进分数。

那么它的渐进分数列是：

$$
[0,2]=\frac{1}{2},[0,2,4]=\frac{4}{9},[0,2,4,2]=\frac{9}{20}\ldots
$$

它的最佳逼近有理数列是：

$$
\left[0,1\right]=1,\left[0,2\right]=\frac{1}{2}
$$

$$
\left[0,2,1\right]=\frac{1}{3},\left[0,2,2\right]=\frac{2}{5},\left[0,2,3\right]=\frac{3}{7},\left[0,2,4\right]=\frac{4}{9}
$$

$$
\left[0,2,4,1\right]=\frac{5}{11},\left[0,2,4,2\right]=\frac{9}{20},\ldots
$$

从每个渐进分数（不包含）开始，到下一个渐进分数（包含）为止，同为上逼近，或同为下逼近。

在最佳逼近列中，每一个最佳分数是上一个最佳分数与再往前一个渐进分数的分子分母对应求和。

### 性质

定理：最佳有理逼近一定是中间分数。

它的逆定理并不成立，中间分数不一定是最佳有理逼近。

???+ note "证明"
    首先，$a_0$ 与 $a_0+1$ 中必有一个是 $x$ 的分母为 $1$ 的最佳有理逼近。它们分别是 $F_{1,0}$ 和 $F_{0,1}$。其他分母更大的第一类最优逼近肯定介于这两个数中间。
    
    当然，除非 $x=n+\frac{1}{2}$ 为半奇数。这时两边距离一样，$x$ 没有分母为 $1$ 的最佳有理逼近，不过这属于连分数太短的情况。
    
    当 $n$ 增加时，渐近分数从 $F_{1,0}$ 和 $F_{0,1}$ 两边向中间排布。由于 $F_{k,a_{k+1}}=F_{k+2,0}$，有分布
    
    $$
    F_{1,0}<F_{1,1}\leq F_{1,a_2}=F_{3,0}<\ldots<x<\ldots<F_{2,0}=F_{0,a_1}≤F_{0,1}
    $$
    
    因为中间分数可以任意接近 $x$，从而任何一个不是中间分数的有理数 $\frac{a}{b}$，一定介于两个同阶的渐近分数 F\*{k,r} 与 F\*{k,r+1} 之间。其位置分布情况为：
    
    $$
    F_{k,r}~\frac{a}{b}~F_{k,r+1}~x
    $$
    
    于是有
    
    $$
    \left|F_{k,r}-\frac{a}{b}\right|<|F_{k,r+1}-F_{k,r}|=\frac{1}{((r+1)q_k+q_{k-1})(rq_k+q_{k-1})}
    $$
    
    另一方面，$\frac{a}{b}$ 与中间分数 $F_{k,r}$，有
    
    $$
    \left|F_{k,r}-\frac{a}{b}\right|=\frac{|a(rq_k+q_{k-1})-b(rp_k+p_{k-1})|}{b(rq_k+q_{k-1})}\geq\frac{1}{b(rq_k+q_{k-1})}
    $$
    
    因此有 $b>(r+1)q_k+q_{k-1}$。介于 $F_{k,r}$ 和 $F_{k,r+1}$ 之间的有理数，分母一定大于 $F_{k,r+1}$ 的分母。由位置分布可以看出
    
    $$
    \left|x-\frac{a}{b}\right|>|x-F_{k,r+1}|
    $$
    
    分母更小的分数 $F_{k,r+1}$ 到 $x$ 的距离更近。因此，非中间分数的 $\frac{a}{b}$ 不可能是最佳有理逼近。证毕。

## 渐进分数的等价性质

实数 $x$ 的渐进分数 $\dfrac{p}{q}$ 等价于这样的一类分数：

对于任意的整数 $a$ 和整数 $0<b\leq q$，$\dfrac{a}{b}\neq\dfrac{p}{q}$，均有

$$
|bx-a|>|qx-p|
$$

也就是

$$
\left|x-\frac{a}{b}\right|>\frac{q}{b}\left|x-\frac{p}{q}\right|
$$

根据等价性，这可以直接作为渐进分数的另一个定义方法。这个性质比最佳逼近更加严格，因此根据这个性质，渐进分数必然为最佳逼近。

证明：

首先有 $|q_kx-p_k|<\dfrac{1}{q_{k+1}}$。对于一个非渐近分数的中间分数 $F_{k,n}=\dfrac{a}{b}$，有位置分布

$$
\frac{p_{k-1}}{q_{k-1}}~\frac{a}{b}~\frac{p_{k+1}}{q_{k+1}}~x~\frac{p_k}{q_k}
$$

于是有

$$
\left|x-\frac{a}{b}\right|>\left|\frac{p_{k+1}}{q_{k+1}}-\frac{a}{b}\right|
$$

即 $|bx-a|\geq\dfrac{1}{q_{k+1}}$。由于 $b=nq_k+q_{k-1}>q_k$，因此 $F_{k,n}=\dfrac{a}{b}$ 劣于比它分母更小的 $\dfrac{p_k}{q_k}$。

接下来证明，满足这个条件的都是渐进分数。

首先，越高阶的渐近分数越靠近 $x$，具有严格单调性。如果有 $s<k$，就有 $|q_sx-p_s|>|q_kx-p_k|$。

这是因为 $q_{k+1}\geq q_s+q_{s+1}$，有

$$
|q_sx-p_s|>\frac{1}{q_s+q_{s+1}}\leq\frac{1}{q_{k+1}}>|q_kx-p_k|
$$

整理即为上式。

接下来找出分母为 $q_k$ 的满足上述性质的数，并指出它是渐进分数。

在给定 $b$ 的时候，$\min |bx-a|\leq\dfrac{1}{2}$，并且取到最小的 $a$ 最多只有两个取值。

当 $b$ 在范围 $0<b\leq q_k$ 遍历的时候，将上述的最小值继续比较其中的最小值，并记取到最小值中的最小值的多个 $b$ 中，最小的 $b$ 为 $b_0$，对应的 $a$ 为 $a_0$。

这里的 $a_0$ 至多有两个，而事实上只有一个，可以证明其唯一性。唯一性的证明补在最后。

从上述选取方式可以看出 $\dfrac{a_0}{b_0}$ 也满足定理的条件，因此它是一个渐进分数 $\dfrac{p_s}{q_s}$。

又根据严格单调性，在 $s<k$ 时无法取到最小，只能有 $s=k$。

至此距离证毕只剩下 $a_0$ 的唯一性。

如果给定 $b_0$，取到 $|b_0x-a|$ 的 $a$ 不唯一，而是相邻的两个数，只能有 $|b_0x-a|=\dfrac{1}{2}$。此时记较小的一个为 $a_0$。于是有

$$
x=\frac{2a_0+1}{2b_0}
$$

如果它们不互素，记 $d=\gcd(2a_0+1, 2b_0)\geq 3$，则有

$$
b_1=\frac{2b_0}{d}<b_0
$$

$$
a_1=\frac{2a_0+1}{d}
$$

使得 $|b_1x-a_1|=|b_0x-a_0|=\dfrac{1}{2}$。这与上述选取方式中 $b_0$ 的最小性矛盾。

此时将有理数 $x$ 做连分数展开，则最后一个渐进分数的分子分母就是

$$
p_N=2a_0+1
$$

$$
q_N=2b_0=a_Nq_{N-1}+q_{N-2}
$$

由于 $a_N\geq 2$，$q_{N-2}\geq 1$，得到 $q_{N-1}<b_0$。于是

$$
|q_{N-1}x-p_{N-1}|=\frac{1}{q_N}=\frac{1}{2b_0}\leq\frac{1}{2}
$$

此时有更小的 $q_{N-1}$ 可以取到最小值，仍旧与上述 $b_0$ 的选取方式矛盾。证毕。

## 勒让德判别法

对实数 $x$ 与分数 $\dfrac{p}{q}$，如果有

$$
\left|x−\frac{p}{q}\right|<\frac{1}{2q^2}
$$

则 $\dfrac{p}{q}$ 一定是 $x$ 的渐近分数。

勒让德判别法的原始形式更加复杂，由勒让德（Legendre）于 1797 年发表在他的专著中。

勒让德判别法的原始表述是一个等价关系，这里给出的形式相对简化与宽松，是一个渐进分数的充分条件而非必要条件。

???+ note "证明"
    假设 $\dfrac{p}{q}$ 不是渐进分数，则存在 $0<b\leq q$，且 $\dfrac{a}{b}\neq\dfrac{p}{q}$ 使得
    
    $$
    |bx-a|\leq|qx-p|<\frac{1}{2q}
    $$
    
    于是有
    
    $$
    \left|x-\frac{a}{b}\right|<\frac{1}{2qb}
    $$
    
    此时首先两个分数之间的距离有
    
    $$
    \left|\frac{p}{q}-\frac{a}{b}\right|=\frac{|pb-aq|}{qb}\geq\frac{1}{qb}
    $$
    
    又有绝对值不等式
    
    $$
    \left|\frac{p}{q}-\frac{a}{b}\right|=\left|\frac{p}{q}-x+x-\frac{a}{b}\right|\leq\left|\frac{p}{q}-x\right|+\left|x-\frac{a}{b}\right|<\frac{b+q}{2bq^2}
    $$
    
    连起来有
    
    $$
    \frac{1}{qb}\leq\left|\frac{p}{q}-\frac{a}{b}\right|<\frac{b+q}{2bq^2}
    $$
    
    整理有 $b>q$。这与假设矛盾。证毕。

**本页面主要译自博文 [Дерево Штерна-Броко. Ряд Фарея](http://e-maxx.ru/algo/stern_brocot_farey) 与其英文翻译版 [The Stern-Brocot Tree and Farey Sequences](https://cp-algorithms.com/others/stern_brocot_tree_farey_sequences.html)。其中俄文版版权协议为 Public Domain + Leave a Link；英文版版权协议为 CC-BY-SA 4.0。**
