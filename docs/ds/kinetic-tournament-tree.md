author: Jerry3128

前置知识：[线段树](./seg.md)

## 问题引入

给定单变量线性函数序列 $F=\{f_1,\dots,f_n\}$：$f_i: \mathbf{R} \rightarrow \mathbf{R}$．其中 $f_i(x)=k_ix+b_i$ 且 $k_i,b_i \in \mathbf{R}$．我们需要维护以下操作：

-   $\operatorname{QueryMax}(l,r)$：给定 $l$ 和 $r$, 返回 $\max_{i=l}^r{f_i(0)}$．
-   $\operatorname{TranslateLeft}(l,r,\delta)$：给定 $l$,$r$ 和 $\delta$, 对于所有 $i\in[l,r]$，执行操作 $f_i(x) \leftarrow f_i(x+\delta)$，这个操作等价于执行 $b_i\leftarrow b_i+k_i\delta$．其中 $\delta > 0$．

为了方便，我们假定所有函数互不相同．

一次函数区间向左平移的本质是 $b_i \leftarrow k_i\cdot \delta$，也就是对于 $b_i$ 常数项，让它加上斜率 $k_i$ 乘上横坐标的平移量 $\delta$；这种操作等价于我们在许多数据结构问题中遇到的「按位置系数加权区间加」：即对于区间 $[l, r]$ 内的每个下标 $i$，给其值加上一个固定的数 $\delta$ 乘上该位置特有的系数 $k_i$．因此本质上一次函数区间平移就是所谓的，按位置系数加权区间加法．

为了展示 KTT 独特的二叉树形分治结构，我们将直接从区间平移入手．

## Kinetic Data Structures

Kinetic Data Structures 简称 KDS．KDS 用于维护几何对象系统在连续运动过程中的属性．

### 事件队列

我们假设每一个点都有一个已知的运动计划，这个计划可以提供它的完整或者部分运动信息，例如函数 $f_i(x)$ 形成的曲线或直线能够很好的描述动点 $i$ 的运动轨迹．运动计划随时可能变化，它可能是由于碰撞，或者环境交互的原因；我们称造成运动计划更改的原因为事件．事件队列会按时间顺序给出事件．

KDS 的一个关键方面是需要拥有容易维护的事件，即事件队列中事件类型对应于可能的组合变化，这些变化涉及数量恒定且通常较少的物体．例如，在本题的维护中，我们使用的一种事件类型是「函数 $f_i(0)$ 与函数 $f_{j}(0)$ 的大小发生变化」．

事件队列可以隐式维护．

### 证书

这些事件应当可以等价于通过一系列低阶代数条件的交保证，每个代数条件都涉及有限数量的对象．我们将这些条件称为 KDS 的证书．例如 $[f_i(0) > f_j(0)]$.

## Kinetic Tournament Tree

### 简介

Kinetic Tournament Tree（简称 KTT），属于 Kinetic Data Structures，首次出现于 1999 年的 [Data Structures for Mobile Data](https://www.sciencedirect.com/science/article/pii/S0196677498909889)，用于维护连续变化的数据．更普遍地，每一个采用如下动态化策略（kinetization strategy）的结构，都可以称为 Kinetic Tournament：

-   为静态算法中的关键操作（例如比较）生成正确性证书，并将每个证书与一个全局事件队列关联，记录该证书可能失效的时间点．
-   当某个证书失效时，我们能够高效地更新算法输出并维护证书集合．

在算法竞赛社区，它兴起于 2020 年国家集训队论文《[浅谈函数最值的动态维护](https://github.com/OI-wiki/libs/blob/master/%E9%9B%86%E8%AE%AD%E9%98%9F%E5%8E%86%E5%B9%B4%E8%AE%BA%E6%96%87/IOI2020%E4%B8%AD%E5%9B%BD%E5%9B%BD%E5%AE%B6%E5%80%99%E9%80%89%E9%98%9F%E8%AE%BA%E6%96%87%E9%9B%86%20%E9%9D%9E%E6%AD%A3%E5%BC%8F%E7%89%88.pdf)》．学术界的 KTT 与算法竞赛界的 KTT 在应用领域和实现上有所不同，因此我们将介绍为算法竞赛界进行一些优化过后的 KTT．

### 基本结构

首先我们考虑设计一个线段树结构相似的数据结构用于维护静态最大值．我们将线段树的结构建立出来，对于每个非叶节点，它的权值为两个孩子节点中较大的权值．在执行了 $O(n)$ 次比较过后，我们得到根节点的权值就是全局的最大值．现在，权值开始变化．只要 KTT 能探测到每一次树上点的最大值来源改变，我们就能够维护全局最大值．

为了让 KTT 能够探测到每一次树上最大值来源变换，对于树上节点 $x$ 以及其左、右儿子提供的函数 $f_L$ 和 $f_R$，我们定义证书为「$f_L$ 和 $f_R$ 的大小关系保持不变」．当证书失效的时候，我们就需要通过树上路径走到当前证书失效的节点来更新它的信息．为了维护每个证书失效的时间，我们发现证书失效的时刻正是两个函数拥有相同值的时刻，那么问题就变成了找到两个线性函数的交点的横坐标，可以在 $O(1)$ 时间内解决．

对于每个树上的节点维护出了它在 $0$ 处取到最大值的函数，以及当前证书失效的时间和整个子树内最早失效证书的失效时间；那么对于每个节点证书失效的时刻，我们就可以在这个时刻找到它并更新它的信息．这些信息是用来记录函数本身的信息的．接下来我们考虑维护区间平移操作，因为它是可以简单累加的，我们就可以使用懒标记去处理区间平移操作．

我们定义懒标记 $\Delta_v$ 表示 $v$ 节点子树内的所有其他节点上的函数都应该向左平移 $\Delta_v$ 个单位．此时，对于树上节点 $v$，一个新的操作要将其子树内的所有函数区间向左平移 $\delta$, 即 $f(x)\leftarrow f(x+\delta)$．我们需要更新懒标记：$\Delta_v\leftarrow \Delta_v + \delta$，即将子树内所有其他节点的偏移量进行累加．同时向左平移也意味着 $0$ 点函数值的变化．我们可以发现如果证书的失效横坐标为 $t$，那么平移后的失效横坐标应为 $t-\delta$；此时，如果 $t-\delta$ 越过 $0$ 点，就代表着证书失效，我们就需要往下递归找到当前证书所在节点，更新当前节点，并将新的信息向上更新到根．这个过程可以跟随着修改一起做．

因此我们便可以得到简单实现．

???+ example "参考实现"
    ```cpp
    --8<-- "docs/ds/code/ktt/ktt_1.cpp:core"
    ```

### 复杂度分析

证明 KTT 的时间复杂度需要用到势能分析．

设 $d(x)$ 为节点 $x$ 在线段树上的深度，根节点的深度为 $1$．定义节点 $x$ 在线段树上的势能为：

$$
\alpha(x) = \begin{cases}
d(x) & \text{if the lower slope function has larger value}  \\
0    & \text{otherwise}\\
\end{cases}
$$

即在 $x$ 比较的两个函数，如果拥有较小斜率的函数的值在 $0$ 点更大，那么当前节点势能为 $d(x)$，否则为 $0$．

定义整个 KTT 的势能为所有节点势能之和：

$$
\Phi = \sum_x \alpha(x)
$$

考虑某次对于节点 $x$，和它的父亲 $p$ 的实际更新代价 $c=1$，更新前后的势能分别为 $\Phi$ 和 $\Phi'$．我们去计算更新节点 $x$ 的均摊更新代价．由于当前节点 $x$ 被更新，那么在当下它的势能一定是由 $d(x)$ 下降到 $0$．而对于 $p$，它的势能最坏情况可能由 $0$ 上升到 $d(p)$：

$$
\begin{aligned}
\hat{c} &= 1 + \Phi' - \Phi\\
    &= 1 + (\alpha'(p) + \alpha'(x)) - (\alpha(p) + \alpha(x))\\
    &= 1 + (\alpha'(p) - \alpha(p)) + (\alpha'(x) - \alpha(x))\\
    &\leq 1 + d(p) - d(x)\\
    &= 0
\end{aligned}
$$

对实际代价求和，定义初始势能 $\Phi_s$ 以及最终势能 $\Phi_t$：

$$
\begin{aligned}
\sum c  &= \sum \hat{c} + \Phi_{s} - \Phi_{t}\\
    &\leq \Phi_{s} - \Phi_{t}\\
    &=O(n\log n)
\end{aligned}
$$

这部分为 KTT 在仅存在全局修改的情况下，它将所有证书失效更新完毕的次数．

额外的，考虑区间平移对势能的影响．对于某次区间平移，我们需要考虑的节点应当为，其子树当中存在但不是所有树节点被执行区间平移操作的节点．这样的节点也就是我们在执行修改操作的时候在树上经过的节点，它的数量不超过 $O(\log n)$ 个，最坏情况下每个节点的势能上涨 $d(x)\le \log n$，因此每次操作上涨 $O(\log^2 n)$ 的势能．

为了维护区间平移，更新证书的操作将会被执行 $O(n\log n + m\log^2 n)$ 次．每次更新证书我们需要从树上沿着路径走到证书失效的节点，这部分是 $O(\log n)$ 的．因此总时间复杂度为 $O(n\log^2 n+ m\log^3 n)$．

这个方法的优秀之处在于他已经触及问题时间复杂度的下界 $O(\lambda_{s}(n)\log^2 n)$．$\lambda_{s}(n)$ 表示长度最长的 (n, s) Davenport-Schinzel 序列．其中线性函数对应 $s=1$ 的 $\lambda_1(n)=n$．这部分属于计算几何内容，本篇不在这里赘述．

### 高次情况

如果我们维护的不是线性函数而是多项式函数，或者更加复杂的函数我们如何应对．两个复杂函数之间可能拥有多个交点．给定一个连续、完全定义的单变量函数序列 $F=\{f_1,\dots,f_n\}$：$f_i: \mathbf{R} \rightarrow \mathbf{R}$．其中每对函数的图像至多相交于 $s$ 个点．具有代表性的，$s$ 次多项式函数集合符合这个要求．

对于同样的问题，我们使用势能分析．

$d(x)$ 为节点 $x$ 在线段树上的深度，根节点的深度为 $1$．定义 $I(x)$ 表示在节点 $x$ 比较的两个函数，在 $0$ 点过后有几个交点．定义节点 $x$ 在线段树上的势能为：

$$
\alpha(x)=d(x)^{\log_2(s+1)}I(x)
$$

定义整个 KTT 的势能为所有节点势能之和：

$$
\Phi = \sum_x \alpha(x)
$$

考虑某次对于节点 $x$，和它的父亲 $p$ 的实际更新代价 $c=1$，更新前后的势能分别为 $\Phi$ 和 $\Phi'$．我们去计算更新节点 $x$ 的均摊更新代价．由于当前节点 $x$ 被更新，那么在当下它的势能一定是由 $d(x)^{\log_2(s+1)}I(x)$ 下降到 $d(x)^{\log_2(s+1)}(I(x)-1)$．而对于 $p$，它的势能最坏情况可能由 $0$ 上升到 $d(p)^{\log_2(s+1)}$：

$$
\begin{aligned}
        \hat{c} &= 1 + \Phi' - \Phi\\
                &= 1 + (\alpha'(x) - \alpha(x)) + (\alpha'(p) - \alpha(p))\\
                &\leq 1 - d(x)^{\log_2{(s+1)}} + s(d(x)-1)^{\log_2{(s+1)}}\\
                &\leq 0
    \end{aligned}
$$

由第三行到第四行我们使用了 $d(x)$ 为正整数的限制．

对实际代价求和，定义初始势能 $\Phi_s$ 以及最终势能 $\Phi_t$：

$$
\begin{aligned}
    \sum c  &= \sum \hat{c} - \Phi_t + \Phi_s\\
            &\leq \Phi_s - \Phi_t\\
            &= O(ns (\log n)^{\log_2{(s+1)}})
\end{aligned}
$$

我们得到复杂度的上界 $O(ns (\log n)^{1+\log_2{(s+1)}} + ms (\log n)^{2+\log_2{(s+1)}})$．[^ref1]

### 近似情况

给定一个连续、完全定义的单变量函数序列 $F=\{f_1,\dots,f_n\}$，定义 $\mathfrak U_F(x)$，$\mathfrak L_F(x)$ 和 $\mathfrak E_F(x)$ 分别为上包络、下包络和幅度．

$$
\begin{aligned}
    \mathfrak U_F(x) & = \max\{f_i(x) \mid f_i \in F\} \\
    \mathfrak L_F(x) & = \min\{f_i(x) \mid f_i \in F\} \\
    \mathfrak E_F(x) & = \mathfrak U_F(x) - \mathfrak L_F(x)
\end{aligned}
$$

我们只要求程序返回 $\tilde{\mathfrak U}_F(x)$ 满足

$$
\mathfrak U_F(x) \geq \tilde{\mathfrak U}_F(x) \geq \mathfrak U_F(x) - \epsilon \mathfrak E_F(x)
$$

那么在复杂情况下我们可以做到 $O((1/\epsilon^2)n\log^3 n)$，与多项式次数无关，以及我们允许函数同时进行区间左移或者右移．

## 参考文献与注释

[^ref1]: 需要注意的是，这仅仅给出的是上界，复杂度的下界应为 $O(\lambda_{s}(n)\log n)$．笔者猜测这里的势能分析构造应当参考 Davenport-Schinzel 序列对应的 $\lambda_{s}(n)$ 的通项公式以获取更紧的上界．

-   P. K. Agarwal, S. Har-Peled, and K. R. Varadarajan. Approximating extent measures of points. J. ACM, 51(4):606–635, July 2004.
-   J. Basch, L. J. Guibas, and J. Hershberger. Data structures for mobile data. Journal of Algorithms, 31(1):1–28, 1999.
-   G. Alexandron, H. Kaplan, and M. Sharir. Kinetic and dynamic data structures for convex hulls and upper envelopes. Computational Geometry, 36(2):144–158, 2007.
