author: Marcythm, zyf0726, hsfzLZH1, MingqiHuang, Ir1d, greyqz, billchenchina, Chrogeek, StudyingFather

## 区间类（2D1D）动态规划中的应用

在区间类动态规划（如石子合并问题）中，我们经常遇到以下形式的 2D1D 状态转移方程：

$$
f_{l,r} = \min_{k=l}^{r-1}\{f_{l,k}+f_{k+1,r}\} + w(l,r)\qquad\left(1 \leq l < r \leq n\right)
$$

直接简单实现状态转移，总时间复杂度将会达到 $O(n^3)$，但当函数 $w(l,r)$ 满足一些特殊的性质时，我们可以利用决策的单调性进行优化。

- **区间包含单调性**：如果对于任意 $l \leq l' \leq r' \leq r$，均有 $w(l',r') \leq w(l,r)$ 成立，则称函数 $w$ 对于区间包含关系具有单调性。
- **四边形不等式**：如果对于任意 $l_1\leq l_2 \leq r_1 \leq r_2$，均有 $w(l_1,r_1)+w(l_2,r_2) \leq w(l_1,r_2) + w(l_2,r_1)$ 成立，则称函数 $w$ 满足四边形不等式（简记为“交叉小于包含”）。若等号永远成立，则称函数 $w$ 满足 **四边形恒等式**。

**引理 1**：若 $w(l, r)$ 满足区间包含单调性和四边形不等式，则状态 $f_{l,r}$ 满足四边形不等式。

定义 $g_{k,l,r}=f_{l,k}+f_{k+1,r}+w(l,r)$ 表示当决策为 $k$ 时的状态值，任取 $l_1\leq l_2\leq r_1\leq r_2$，记 $u=\mathop{\arg\min}\limits_{l_1\leq k < r_2}g_{k,l_1,r_2},v=\mathop{\arg\min}\limits_{l_2\leq k < r_1}g_{k,l_2,r_1}$ 分别表示状态 $f_{l_1,r_2}$ 和 $f_{l_2,r_1}$ 的最小最优决策点。

> 注意到，仅当 $l_2 < r_1$ 时 $v$ 才有意义。因此我们有必要单独考虑 $l_2 = r_1$ 的情形。

首先注意到若 $l_1 = l_2$ 或 $r_1 = r_2$ 时，显然成立。

考虑对区间长度 $r_2 - l_1$ 使用数学归纳法（$r_2 - r_1 = 0$ 时，显然成立）。

-   $l_1 < l_2 = r_1 < r_2$（证明过程需要 $w$ 满足区间包含单调性）

    1.  若 $u < r_1$ 则 $f_{l_1, r_1} \leq f_{l_1, u} + f_{u + 1, r_1} + w(l_1, r_1)$，由归纳法 $f_{u + 1, r_1} + f_{l_2, r_2} \leq f_{u + 1, r_2} + f_{l_2, r_1}$，两式相加再消去相同部分得到（下面最后一个不等式用到了 $w(l_1, r_1) < w(l_1, r_2)$）：

        $$
        f_{l_1, r_1} + f_{l_2, r_2} \leq f_{l_1, u} + f_{u + 1, r_2} + f_{l_2, r_1} + w(l_1, r_1) \leq f_{l_1, r_2} + f_{l_2, r_1}
        $$

    2.  若 $u \geq r_1$ 则 $f_{l_2, r_2} \leq f_{l_2, u} + f_{u + 1, r_2} + w(l_2, r_2)$ 由归纳法 $f_{l_1, r_1} + f_{l_2, u} \leq f_{l_1, u} + f_{l_2, r_1}$，两式相加再消去相同部分得到（下面最后一个不等式用到了 $w(l_2, r_2) < w(l_1, r_2)$）：

        $$
        f_{l_1, r_1} + f_{l_2, r_2} \leq f_{l_1, u} + f_{l_2, r_1} + f_{u + 1, r_2} + w(l_2, r_2) \leq f_{l_1, r_2} + f_{l_2, r_1}
        $$

-   $l_1 < l_2 < r_1 < r_2$（仅需要 $w$ 满足四边形不等式）

    1.  若 $u\leq v$，则 $l_1\leq u< r_1,\ l_2\leq v< r_2$，因此

        $$
        \begin{aligned}
            f_{l_1,r_1} \leq g_{u,l_1,r_1} &= f_{l_1,u} + f_{u+1,r_1} + w(l_1,r_1) \\
            f_{l_2,r_2} \leq g_{v,l_2,r_2} &= f_{l_2,v} + f_{v+1,r_2} + w(l_2,r_2)
        \end{aligned}
        $$

        再由 $u+1 \leq v+1 \leq r_1 \leq r_2$ 和归纳假设知

        $$
        f_{u+1,r_1} + f_{v+1,r_2} \leq f_{u+1,r_2} + f_{v+1,r_1}
        $$

        将前两个不等式累加，并将第三个不等式代入，可得

        $$
        \begin{aligned}
            f_{l_1,r_1} + f_{l_2,r_2} & \leq f_{l_1,u} + f_{l_2,v} + f_{u+1,r_1} + f_{v+1,r_2} + w(l_1,r_1) + w(l_2,r_2) \\
            & \leq g_{u,l_1,r_2} + g_{v,l_2,r_1} = f_{l_1,r_2} + f_{l_2,r_1}
        \end{aligned}
        $$

    2.  若 $v< u$，则 $l_1\leq v<r_1,l_2\leq u<r_2$，因此

        $$
        \begin{aligned}
        f_{l_1,r_1} \leq g_{v,l_1,r_1} &= f_{l_1,v} + f_{v+1,r_1} + w(l_1,r_1) \\
        f_{l_2,r_2} \leq g_{u,l_2,r_2} &= f_{l_2,u} + f_{u+1,r_2} + w(l_2,r_2)
        \end{aligned}
        $$

        再由 $l_1 \leq l_2 \leq v \leq u$ 和归纳假设知

        $$
        f_{l_1,v} + f_{l_2,u} \leq f_{l_1,u} + f_{l_2,v}
        $$

        将前两个不等式累加，并将第三个不等式代入，可得

        $$
        \begin{aligned}
        f_{l_1,r_1} + f_{l_2,r_2} & \leq f_{l_1,u} + f_{l_2,v} + f_{v+1,r_1} + f_{u+1,r_2} + w(l_1,r_2) + w(l_2,r_1) \\
        & \leq g_{u,l_1,r_2} + g_{v,l_2,r_1} = f_{l_1,r_2} + f_{l_2,r_1}
        \end{aligned}
        $$

综上所述，两种情形均有 $f_{l_1,r_1} + f_{l_2,r_2} \leq f_{l_1,r_2} + f_{l_2,r_1}$，即四边形不等式成立。

**定理 1**：若状态 $f$ 满足四边形不等式，记 $m_{l,r}=\min\{k:f_{l,r} = g_{k,l,r}\}$ 表示最优决策点，则有

$$
m_{l,r-1} \leq m_{l,r} \leq m_{l+1,r} \qquad (l + 1 < r)
$$

记 $u = m_{l,r},\ k_1=m_{l,r-1},\ k_2=m_{l+1,r}$，分情况讨论：

1.  若 $k_1>u$，则 $u+1 \leq k_1+1 \leq r-1 \leq r$，因此根据四边形不等式有

    $$
    f_{u+1,r-1} + f_{k_1+1,r} \leq f_{u+1,r} + f_{k_1+1,r-1}
    $$

    再根据 $u$ 是状态 $f_{l,r}$ 的最优决策点可知

    $$
    f_{l,u} + f_{u+1,r} \leq f_{l,k_1} + f_{k_1+1, r}
    $$

    将以上两个不等式相加，得

    $$
    f_{l,u} + f_{u+1,r-1} \leq f_{l,k_1}+f_{k_1+1,r-1}
    $$

    即 $g_{u,l,r-1} \leq g_{k_1,l,r-1}$，但这与 $k_1$ 是最小的最优决策点矛盾，因此 $k_1\leq u$。

2.  若 $u>k_2$，则 $l\leq l+1 \leq k_2\leq u$，根据四边形不等式可得

    $$
    f_{l,k_2} + f_{l+1,u} \leq f_{l,u} + f_{l+1, k_2}
    $$

    再根据 $k_2$ 是状态 $f_{l+1, r}$ 的最优决策点可知

    $$
    f_{l+1,k_2} + f_{k_2+1, r} \leq f_{l+1,u} + f_{u+1,r}
    $$

    将以上两个不等式相加，得

    $$
    f_{l,k_2}+f_{k_2+1,r} \leq f_{l,u} + f_{u+1,r}
    $$

    即 $g_{k_2,l,r} \leq g_{u,l,r}$，但这与 $u$ 是最小的最优决策点矛盾，因此 $u \leq k_2$。

因此，如果在计算状态 $f_{l,r}$ 的同时将其最优决策点 $m_{l,r}$ 记录下来，那么我们对决策点 $k$ 的总枚举量将降为

$$
\sum_{1\leq l<r\leq n} m_{l+1,r} - m_{l,r-1} = \sum_{i=1}^n m_{i,n} - m_{1,i}\leq n^2
$$

???+note "核心代码"
    ```cpp
    for (int len = 2; len <= n; ++len)  // 枚举区间长度
      for (int l = 1, r = len; r <= n; ++l, ++r) {
        // 枚举长度为len的所有区间
        f[l][r] = INF;
        for (int k = m[l][r - 1]; k <= m[l + 1][r]; ++k)
          if (f[l][r] > f[l][k] + f[k + 1][r] + w(l, r)) {
            f[l][r] = f[l][k] + f[k + 1][r] + w(l, r);  // 更新状态值
            m[l][r] = k;  // 更新（最小）最优决策点
          }
      }
    ```

### 另一种常见的形式

某些 dp 问题有着如下的形式：

$$
f_{i,j} = \min_{k \leq j}\{f_{i-1,k}\} + w(k,j)\qquad\left(1 \leq i \leq n,1 \leq j \leq m\right)
$$

总共有 $n \times m$ 个状态，每个状态要有 $m$ 次转换，上述 dp 问题的时间复杂度就是 $O(n m^2)$。

> 实际上此形式也有同样的结论，可以在 $O(n m)$ 复杂度解决，读者可以模仿 2D1D 类似的给出证明。

令 $opt(i, j)$ 为使上述表达式最小化的 $k$ 的值。如果对于所有的 $i, j$ 都有 $opt(i, j) \leq opt(i, j + 1)$，那么我们就可以用分治法来优化 dp 问题。

我们可以更有效地解出所有状态。假设我们对于固定的 $i$ 和 $j$ 计算 $opt(i, j)$。那么我们就可以确定对于任何 $j' < j$ 都有 $opt(i, j') \leq opt(i, j)$，这意味着在计算 $opt(i, j')$ 时，我们不必考虑那么多其他的点。

为了最小化运行时间，我们便需要应用分治法背后的思想。首先计算 $opt(i, \dfrac{m}{2})$ 然后计算 $opt(i, \dfrac{m}{4})$。通过递归地得到 $opt$ 的上下界，就可以达到 $O(n m \log m)$ 的时间复杂度。每一个 $opt(i, j)$ 的值只可能出现在 $\log m$ 个不同的节点中。

??? note "参考代码"
    ```cpp
    int n;
    long long C(int i, int j);
    vector<long long> dp_before(n), dp_cur(n);
    // compute dp_cur[l], ... dp_cur[r] (inclusive)
    void compute(int l, int r, int optl, int optr) {
      if (l > r) return;
      int mid = (l + r) >> 1;
      pair<long long, int> best = {INF, -1};
      for (int k = optl; k <= min(mid, optr); k++) {
        best = min(best, {dp_before[k] + C(k, mid), k});
      }
      dp_cur[mid] = best.first;
      int opt = best.second;
      compute(l, mid - 1, optl, opt);
      compute(mid + 1, r, opt, optr);
    }
    ```

## 1D1D 动态规划中的应用

除了经典的石子合并问题外，四边形不等式的性质在一类 1D1D 动态规划中也能得出决策单调性，从而优化状态转移的复杂度。考虑以下状态转移方程：

$$
f_{r} = \min_{l=1}^{r-1}\{f_{l}+w(l,r)\}\qquad\left(1 < r \leq n\right)
$$

**定理 2**：若函数 $w(l,r)$ 满足四边形不等式，记 $h_{l,r}=f_l+w(l,r)$ 表示从 $l$ 转移过来的状态 $r$,$k_{r}=\min\{l|f_{r}=h_{l,r}\}$ 表示最小最优决策点，则有

$$
\forall r_1 \leq r_2:k_{r_1} \leq k_{r_2}
$$

记 $l_1=k_{r_1},\ l_2=k_{r_2}$，若 $l_1>l_2$，则 $l_2<l_1<r_1\leq r_2$，根据四边形不等式有

$$
w(l_2,r_1) + w(l_1,r_2) \leq w(l_1,r_1) + w(l_2,r_2)
$$

又由于 $l_2$ 是最优决策点，因此 $h_{l_2,r_2} \leq h_{l_1,r_2}$，即

$$
f_{l_2}+w(l_2,r_2) \leq f_{l_1}+w(l_1,r_2)
$$

将以上两个不等式相加，可得

$$
f_{l_2}+w(l_2,r_1) \leq f_{l_1}+w(l_1,r_1)
$$

即 $h_{l_2,r_1} \leq h_{l_1,r_1}$，但这与 $l_1$ 是最小最优决策点矛盾，因此必有 $l_1 \leq l_2$。

但与 2D1D 动态规划中的情形不同，在这里我们根据决策单调性只能得出每次枚举 $l$ 时的下界，而无法确定其上界。因此，简单实现该状态转移方程仍然无法优化最坏时间复杂度。

先考虑一种简单的情况，转移函数的值在动态规划前就已完全确定。即如下所示状态转移方程：

$$
f_{r} = \min_{l=1}^{r-1}w(l,r) \qquad\left(1 \leq r \leq n\right)
$$

在这种情况下，我们定义过程 $\textsf{DP}(l, r, k_l, k_r)$ 表示求解 $f_{l}\sim f_{r}$ 的状态值，并且已知这些状态的最优决策点必定位于 $[k_l, k_r]$ 中，然后使用分治算法如下：

???+note "代码实现"
    ```cpp
    void DP(int l, int r, int k_l, int k_r) {
      int mid = (l + r) / 2, k = k_l;
      // 求状态f[mid]的最优决策点
      for (int i = k_l; i <= min(k_r, mid - 1); ++i)
        if (w(i, mid) < w(k, mid)) k = i;
      f[mid] = w(k, mid);
      // 根据决策单调性得出左右两部分的决策区间，递归处理
      if (l < mid) DP(l, mid - 1, k_l, k);
      if (r > mid) DP(mid + 1, r, k, k_r);
    }
    ```

使用递归树的方法，容易分析出该分治算法的复杂度为 $O(n\log n)$，因为递归树每一层的决策区间总长度不超过 $2n$，而递归层数显然为 $O(\log n)$ 级别。

### [「POI2011」Lightning Conductor](https://loj.ac/problem/2157)

???+note "题目大意"
    给定一个长度为 $n$（$n\leq 5\times 10^5$）的序列 $a_1, a_2, \cdots, a_n$，要求对于每一个 $1 \leq r \leq n$，找到最小的非负整数 $f_r$ 满足
    
    $$
    \forall l\in\left[1,n\right]:a_l \leq a_r + f_{r} - \sqrt{|r-l|}
    $$

显然，经过不等式变形，我们可以得到待求整数 $f_r = \max\limits_{l=1}^{n}\{a_l+\sqrt{r-l}-a_r\}$。不妨先考虑 $l < r$ 的情况（另外一种情况类似），此时我们可以得到状态转移方程：

$$
f_r = \min_{l=1}^{r-1}\{\ -a_l-\sqrt{r-l}+a_r\}
$$

根据 $-\sqrt{x}$ 的凸性，我们很容易得出（后文将详细描述）函数 $w(l, r) = -a_l - \sqrt{r-l} + a_r$ 满足四边形不等式，因此套用上述的分治算法便可在 $O(n\log n)$ 的时间内解决此题了。

现在处理一般情况，即转移函数的值是在动态规划的过程中按照一定的拓扑序逐步确定的。此时我们需要改变思维方式，由“确定一个状态的最优决策”转化为“确定一个决策是哪些状态的最优决策“。具体可见上文的「单调栈优化 DP」。

## 满足四边形不等式的函数类

为了更方便地证明一个函数满足四边形不等式，我们有以下几条性质：

**性质 1**：若函数 $w_1(l,r),w_2(l,r)$ 均满足四边形不等式（或区间包含单调性），则对于任意 $c_1,c_2\geq 0$，函数 $c_1w_1+c_2w_2$ 也满足四边形不等式（或区间包含单调性）。

**性质 2**：若存在函数 $f(x),g(x)$ 使得 $w(l,r) = f(r)-g(l)$，则函数 $w$ 满足四边形恒等式。当函数 $f,g$ 单调增加时，函数 $w$ 还满足区间包含单调性。

**性质 3**：设 $h(x)$ 是一个单调增加的凸函数，若函数 $w(l,r)$ 满足四边形不等式并且对区间包含关系具有单调性，则复合函数 $h(w(l,r))$ 也满足四边形不等式和区间包含单调性。

**性质 4**：设 $h(x)$ 是一个凸函数，若函数 $w(l,r)$ 满足四边形恒等式并且对区间包含关系具有单调性，则复合函数 $h(w(l,r))$ 也满足四边形不等式。

首先需要澄清一点，凸函数（Convex Function）的定义在国内教材中有分歧，此处的凸函数指的是（可微的）下凸函数，即一阶导数单调增加的函数。

前两条性质根据定义很容易证明，下面证明第三条性质，性质四的证明过程类似。

任取 $l \leq l' \leq r' \leq r$，根据函数 $w$ 对区间包含关系的单调性有 $w(l',r')\leq w(l,r)$ 成立。又因为 $h(x)$ 单调增加，故 $h(w(l',r')) \leq h(w(l,r))$，即复合函数 $h\circ w$ 满足区间包含单调性。

任取 $l_1\leq l_2\leq r_1\leq r_2$，根据函数 $w$ 满足四边形不等式，有

$$
w(l_1,r_1) + w(l_2,r_2) \leq w(l_1,r_2) + w(l_2,r_1)
$$

移项，并根据 $w$ 对区间包含满足单调性，可得

$$
0 \leq w(l_1,r_1) - w(l_2,r_1) \leq w(l_1,r_2) - w(l_2,r_2)
$$

记 $t = w(l_1,r_2) - w(l_2,r_2)\geq 0$，则 $w(l_1,r_1)\leq w(l_2,r_1)+t,\ w(l_1,r_2)= w(l_2,r_2)+t$，故根据函数 $h$ 的单调性可知（如果是证明性质四则第一个不等式变为等式，无需用到单调性）

$$
\begin{aligned}
    h(w(l_1,r_1)) - h(w(l_2,r_1)) & \leq  h(w(l_2,r_1)+t) - h(w(l_2,r_1)) \\
    h(w(l_1,r_2)) - h(w(l_2,r_2)) & = h(w(l_2,r_2)+t) - h(w(l_2,r_2))
\end{aligned}
$$

设 $\Delta h(x) = h(x+t)-h(x)$，则 $\Delta h'(x) = h'(x+t)-h'(x)$。由于 $h(x)$ 是一个凸函数，故导函数 $h'(x)$ 单调增加，因此函数 $\Delta h$ 也单调增加，此时有

$$
\begin{aligned}
h(w(l_1,r_1)) - h(w(l_2,r_1)) & \leq \Delta h(w(l_2,r_1)) \\
    & \leq \Delta h(w(l_2,r_2)) = h(w(l_1,r_2)) - h(w(l_2,r_2))
\end{aligned}
$$

即 $h(w(l_1,r_1)) + h(w(l_2,r_2)) \leq h(w(l_1,r_2)) + h(w(l_2,r_1))$，说明 $h\circ w$ 也满足四边形不等式。

回顾例题 1 中的 $w(l, r) = -a_l - \sqrt{r-l} + a_r$，由性质 2 可知 $-a_l+a_r$ 满足四边形不等式，而 $r-l$ 满足四边形恒等式和区间包含单调性。再根据 $-\sqrt{x}$ 的凸性以及性质 4 可知 $-\sqrt{r-l}$ 也满足四边形不等式，最终利用性质 1，即可得出 $w(l, r)$ 满足四边形不等式性质了。

### [「HNOI2008」玩具装箱 toy](https://loj.ac/problem/10188)

???+note "题目大意"
    有 $n$ 个玩具需要装箱，要求每个箱子中的玩具编号必须是连续的。每个玩具有一个长度 $C_i$，如果一个箱子中有多个玩具，那么每两个玩具之间要加入一个单位长度的分隔物。形式化地说，如果将编号在 $[l,r]$ 间的玩具装在一个箱子里，那么这个箱子的长度为 $r-l+\sum_{k=l}^r C_k$。现在需要制定一个装箱方案，使得所有容器的长度与 $K$ 差值的平方之和最小。

设 $f_{r}$ 表示将前 $r$ 个玩具装箱的最小代价，则枚举第 $r$ 个玩具与哪些玩具放在一个箱子中，可以得到状态转移方程为

$$
f_{r} = \min_{l=1}^{r-1}\{f_{l} + \left(r-l-1-K+\sum_{k=l+1}^r C_k\right)^2\}
$$

记 $s(r) = r+\sum_{k=1}^r C_k$，则有 $w(l, r) = (s(r) - s(l) - 1 - K)^2$。显然 $s(r)$ 单调增加，因此根据性质 1 和性质 2 可知 $s(r) - s(l) - 1 - K$ 满足区间包含单调性和四边形不等式。再根据 $x^2$ 的单调性和凸性以及性质 3 可知，$w(l, r)$ 也满足四边形不等式，此时使用单调栈优化即可。

## 习题

- [「IOI2000」邮局](https://www.luogu.com.cn/problem/P4767)
- [Codeforces - Ciel and Gondolas](https://codeforces.com/contest/321/problem/E)(Be careful with I/O!)
- [SPOJ - LARMY](https://www.spoj.com/problems/LARMY/)
- [Codechef - CHEFAOR](https://www.codechef.com/problems/CHEFAOR)
- [Hackerrank - Guardians of the Lunatics](https://www.hackerrank.com/contests/ioi-2014-practice-contest-2/challenges/guardians-lunatics-ioi14)
- [ACM ICPC World Finals 2017 - Money](https://open.kattis.com/problems/money)

## 参考资料

- [noiau 的 CSDN 博客](https://blog.csdn.net/noiau/article/details/72514812)
- [Quora Answer by Michael Levin](https://www.quora.com/What-is-divide-and-conquer-optimization-in-dynamic-programming)
- [Video Tutorial by "Sothe" the Algorithm Wolf](https://www.youtube.com/watch?v=wLXEWuDWnzI)

* * *

**本页面主要译自英文版博文 [Divide and Conquer DP](https://cp-algorithms.com/dynamic_programming/divide-and-conquer-dp.html)。版权协议为 CC-BY-SA 4.0。**
