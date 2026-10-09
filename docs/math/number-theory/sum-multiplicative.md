author: AlephInfinity1, aofall, Backl1ght, billchenchina, c-forrest, CCXXXI, chenyichen0420, CoelacanthusHex, CSPNOIP, cy1999, Early0v0, Enoch-xm, Enter-tainer, Great-designer, Haohu Shen, HeRaNO, iamtwz, Ir1d, kenlig, Konano, ksyx, LaDeXX, lrherqwq, Marcythm, MegaOwIer, Nanarikom, ouuan, Persdre, Revltalize, SamZhangQingChuan, scp020, shuzhouliu, StudyingFather, Tiphereth-A, Xeonacid, xyf007, ZnPdCo

前置知识：[积性函数](./basic.md#积性函数)、[素数幂前缀和](./prime-counting.md#推广素数幂前缀和)、[Dirichlet 卷积及生成函数](./dirichlet.md)、[块筛及其卷积](./hyperbola.md#块筛及其卷积)

## 引入

本文介绍能在亚线性时间内计算积性函数前缀和的算法．

## 记号约定

本文使用如下记号和约定：

-   用 $a,d,e,i,j,k,n$ 表示自然数．

-   用 $\mathbf P$ 表示（正）素数集，字母 $p,q$ 表示素数．特别地，用 $p_a$ 表示第 $a$ 小的素数，并补充规定 $p_0=1$．

-   用 $\operatorname{lpf}(n)$ 和 $\operatorname{gpf}(n)$ 分别表示 $n$ 的最小和最大素因子．规定 $\operatorname{lpf}(1)=+\infty$ 且 $\operatorname{gpf}(1)=1$．

-   用 $\pi(n)$ 表示素数计数函数，即不超过 $n$ 的素数个数．

-   用 $D(n)=\{\lfloor n/i\rfloor : i=1,2,\dots,n\}$ 表示数论分块关键值的集合．它的性质参见 [数论分块](./sqrt-decomposition.md#性质) 对应小节．

-   用小写字母 $f,g,h$ 表示积性函数，故总有 $f(1)=1$．

-   用 $f\ast g$ 表示 Dirichlet 卷积，$\widehat{\prod}$ 表示对应的连乘积．

-   $f_p(n) = f(n)[\exists e\ge 0(n=p^e)]$ 是 $f$ 限制在素数 $p$ 的幂次上得到的函数．注意 $f_p(1)=f(1)=1$．

-   $F(n) = \sum_{k=1}^n f(k)$，即 $f$ 的前缀和．规定 $F(0)=0$，下同．

-   $F_{\text{prime}}(n) = \sum_{p\le n} f(p)$，即 $f$ 在素数处的前缀和．

-   $F_a(n) = \sum_{k=1}^n [\operatorname{lpf}(k) > p_a]\,f(k)$，即 $[1,n]$ 中不含前 $a$ 个素数作为因子的正整数处函数值的和．由于 $\operatorname{lpf}(1)=+\infty$，$k=1$ 总在求和范围内．特别地，$F_0(n)=F(n)$；而且，对所有 $a\ge\pi(\sqrt{n})$ 都成立

    $$
    F_a(n)=1+F_\text{prime}(n)-F_\text{prime}(\min\{n,p_a\}).
    $$

-   $\mathcal S_f(n) = \{F(k) : k\in D(n)\}$ 是 $f$ 相对于 $n$ 的块筛．

-   对于本文涉及的所有数论函数，均规定它们在实数 $x$ 处的取值等于它们在 $\lfloor x\rfloor$ 处的取值．故而，本文将省略这些函数参数中的取整函数符号．

## 扩展 Eratosthenes 筛

Lucy 算法可以在亚线性时间内完成素数幂前缀和的计算．它的想法是，利用幂函数前缀和容易计算且满足完全积性这一性质，可以从幂函数前缀和出发，仿照 Eratosthenes 筛的过程，逐步去除合数处函数值的贡献，最终得到素数幂前缀和．

一个自然的想法是，将该过程反向，就可以从 $F_\text{prime}(n)$ 出发，逐步补充合数处函数值的贡献，最终得到 $f$ 的前缀和 $F(n)$ 的值．据此，考虑 $F_a(n)$ 需要满足的递推关系．从 $F_a$ 到 $F_{a-1}$，需要补回的恰是最小素因子为 $p_a$ 的整数．对于一般的积性函数 $f$，它在素数幂 $p^e$ 处的取值 $f(p^e)$ 不能从 $f(p)$ 中计算，所以需要枚举 $p_a$ 的幂次：

$$
F_{a-1}(n) = F_a(n) + \sum_{e\ge 1,~ p_a^e\le n}f(p_a^e)F_a(n/p_a^e).
$$

递推的边界条件是 $F_a(n)=1+F_\text{prime}(n)-F_\text{prime}(\min\{n,p_a\})~(a\ge\pi(\sqrt{n}))$．将它用于递推式中的各项：当 $n<p_a^{e+2}$ 时，相应的 $F_a(n/p_a^e)$ 可以直接算出

$$
F_a(n/p_a^e) = \begin{cases}1, & 1 \le n/p_a^{e} < p_a,\\ 1 + F_\text{prime}(n/p_a^e)-F_\text{prime}(p_a), & p_a \le n/p_a^{e} < p_a^2.\end{cases}
$$

最终的答案就是 $F(n) = F_0(n)$．

本节介绍的算法都依赖于这一关系式，它们都可以称作 **扩展 Eratosthenes 筛**．这类算法由于 Min\_25 的使用而广为人知，所以在不同的资料中，这类算法也常称作 **Min\_25 筛**．

观察上述过程可知，要对积性函数 $f$ 应用扩展 Eratosthenes 筛，需要它满足如下条件：

-   $F_\text{prime}(p)$ 容易计算．根据素数幂前缀和一节的讨论可知，这通常需要 $f(p)$ 可以写成若干前缀和容易计算的完全积性函数的线性组合．最常见的情形是，$f(p)$ 是关于 $p$ 的低次多项式．
-   $f(p^e)~(e>1)$ 容易通过 $p$ 和 $e$ 计算．本节假定可以在 $O(1)$ 时间内根据 $p,e$ 计算 $f(p^e)$．

注意，算法对于素数 $p$ 处的函数取值的限制，比对它在素数的其他幂次 $p^e$ 处的限制要更强．

从 Dirichlet 卷积的角度看，扩展 Eratosthenes 筛的想法十分直接．得益于 $f$ 的积性，它可以写作一系列仅在素数及其幂次处取值的函数 $f_p$ 的 Dirichlet 卷积：

$$
f = \widehat{\prod}_{p} f_p = \left(\widehat{\prod}_{p\le\sqrt{n}} f_p\right)\ast\left(\widehat{\prod}_{p > \sqrt{n}} f_p\right).
$$

以 $\sqrt{n}$ 作为素数的分界线，将乘积分成两部分．第二部分只在所有素因子都大于 $\sqrt{n}$ 的整数处非零，而不超过 $n$ 的这样的整数只有 $1$ 和大于 $\sqrt{n}$ 的素数，故它的前缀和恰是边界条件中的 $F_{\pi(\sqrt{n})}$．于是，扩展 Eratosthenes 筛就是从第二部分（即大素数）的贡献出发，维护前缀和，再逐个合并第一部分（即小素数）中每个 $f_p$ 的贡献；上述递推式的每一步，正是合并一个 $f_p$．

### 递归搜索：Black 算法

直接利用递推关系迭代到 $F_{\pi(\sqrt{n})}(n)$ 就得到：（设 $a\le\pi(\sqrt{n})$）

$$
F_{a-1}(n) = 1 + F_\text{prime}(n) - F_\text{prime}(\sqrt{n}) + \sum_{i=a}^{\pi(\sqrt{n})}\sum_{e\ge 1,~ p_i^e\le n}f(p_i^e)F_i(n/p_i^e).
$$

其中，$p_i^e\le n<p_i^{e+1}$ 的那些项满足 $n/p_i^e<p_i$，故 $F_i(n/p_i^e)=1$，可以直接算出；而 $p_i^{e+1}\le n<p_i^{e+2}$ 的那些项，满足 $p_i\le n/p_i^e<p_i^2$，由边界条件可知 $F_i(n/p_i^e) = 1 + F_\text{prime}(n/p_i^{e})-F_\text{prime}(p_i)$．

利用这一关系式直接求 $F_0(n)$ 就是 **Black 算法**[^black]．展开过程中，只要 $n/p_i^e\ge p_i^2$，边界条件就不适用，相应的 $F_i(n/p_i^e)$ 需要再次代入这一关系式展开；Black 算法不做任何记忆化，而是直接递归下去．

??? example "模板题 [LOJ 6053. 简单的函数](https://loj.ac/p/6053) 参考实现"
    ```cpp
    --8<-- "docs/math/code/sum-multiplicative/black.cpp"
    ```

Black 算法的时间复杂度是 $\Omega(n^{1-\varepsilon})$ 的，空间复杂度是 $O(\sqrt{n})$ 的．尽管理论时间复杂度是 $\Omega(n^{1-\varepsilon})$ 的，但在 $10^{10}\sim 10^{14}$ 的范围内算法实际相当高效：结点数在 $n=10^{10},10^{12},10^{14}$ 时分别约为 $6.3\times 10^6,1.9\times 10^8,6.0\times 10^9$，相当于 $n^{0.74}\sim n^{0.78}$．当然，实际应用时，还需要考虑 Lucy 算法的限制；通常，这一算法能够处理的问题数据范围不会超过 $10^{11}$．

??? note "时间复杂度的证明"
    将递归过程视作遍历一棵多叉树：结点 $(a,m)$ 表示要计算 $F_{a}(n/m)$ 的值；那么，上述递推关系式表明，需要继续计算 $F_{i}(n/(mp_i^e))$ 的值，即结点 $(a,m)$ 的子结点具有形式 $(i,mp_i^e)$，其中 $i>a$．对深度归纳即知每个结点都满足 $p_a=\operatorname{gpf}(m)$：根结点 $(0,1)$ 满足 $\operatorname{gpf}(1)=1=p_0$；而由 $p_i>p_a=\operatorname{gpf}(m)$ 得 $\operatorname{gpf}(mp_i^e)=p_i$．需要展开的结点还需满足 $p_am\le n$；否则 $n/m<p_a$，直接返回 $F_a(n/m)=1$ 即可．反之，任何满足这两个条件的 $(a,m)$，都可以沿 $m$ 的素因数分解所对应的路径在树上找到．因此，算法的时间复杂度与 $\#\{(a,m):p_a=\operatorname{gpf}(m),~p_am\le n\}$ 成正比．这等价于 $\#\{t\in[1,n]:\operatorname{gpf}(t)^2\mid t\}$，而后者渐近等价于 $n\exp(-(\sqrt{2}+o(1))\sqrt{\log n\log\log n})$．[^ivic-pomerance]

### 非递归版本

将扩展 Eratosthenes 筛的递推关系看作二维的状态转移方程，就可以用动态规划的方法解决该问题．因为第二维必然是 $n$ 整除某个整数的商，所以它的取值集合是 $D(n)$．这说明，对于每个 $a$，只需要用 $\Theta(\sqrt{n})$ 的空间就可以存储 $F_{a}(\cdot)$ 的取值．利用 $F_\text{prime}$ 可以初始化 $F_{\pi(\sqrt{n})}(\cdot)$，然后利用递推关系更新状态，最终得到的 $F_0(\cdot)$ 就存储着 $F$ 在 $D(n)$ 处的全部值，即 $f$ 的块筛 $\mathcal S_f(n)$．

状态转移过程中有两点优化．第一，由于 $F_{a-1}(\cdot)$ 仅依赖于 $F_a(\cdot)$ 的值，所以，只要每层都自大到小遍历 $D(n)$ 中的整数，就可以复用数组，节省空间．第二，仅当 $x\ge p_a^2$ 时才需要更新 $F_{a-1}(x)$；否则，$\pi(\sqrt{x})<a$，边界条件已经适用，此时

$$
F_a(x) = 1 + F_\text{prime}(x) - F_\text{prime}(\min\{x,p_a\})
$$

可以直接算出，故这些位置无需逐层维护．

??? example "模板题 [LOJ 6783. 简单的函数 加强版](https://loj.ac/p/6783) 参考实现"
    ```cpp
    --8<-- "docs/math/code/sum-multiplicative/min25-dp.cpp"
    ```

这就是非递归版本的扩展 Eratosthenes 筛．它的空间复杂度仍然是 $O(\sqrt{n})$ 的，而时间复杂度降低到了 $O(n^{3/4}\log^{-1} n)$．为了说明这一点，可以仿照对 Lucy 算法复杂度的 [分析](./prime-counting.md#lucy-算法) 说明，状态转移涉及到的运算次数为

$$
O\left(\sum_{p\le n^{1/4}}\sqrt{n}\log_p n + \sum_{n^{1/4} < p\le\sqrt{n}}\dfrac{n}{p^2}\log_p n\right) = O\left(\dfrac{n^{3/4}}{\log n}\right).
$$

算式中的因子 $\log_p n$ 是指每次状态转移时，都需要计算项数至多为 $\log_p n$ 的求和式；它的加入并没有改变算式整体的渐近行为[^log-p-n]．

第二点优化是保证这一复杂度的要点．如果不提前终止，复杂度将会恶化到 $O(n\log^{-1}n)$．另一种保证提前终止的方法是改变 $F_a(n)$ 的定义．为避免记号混淆，令 $S_a(n)=\sum_{k=2}^n[\operatorname{lpf}(k) > p_a \lor k\in\mathbf P]f(k)$，即 Eratosthenes 筛中，利用前 $a$ 个素数筛去合数后，$[2,n]$ 中剩下的整数处 $f$ 函数值之和．显然有 $F_a(n) = S_a(n) - F_\text{prime}(\min\{n,p_a\}) + 1$．将它代入 $F_a(n)$ 的递推关系，就得到

$$
\begin{aligned}
S_{a-1}(x) &= S_a(x) - f(p_a) + \sum_{e\ge 1,~p_a^{e}\le x}f(p_a^e)\left(S_a(x/p_a^e) - F_\text{prime}(\min\{x/p_a^e,p_a\}) + 1\right)\\
&= S_a(x) + \sum_{e\ge 1,~p_a^{e+1}\le x}\left(f(p_a^e)\left(S_a(x/p_a^e) - F_\text{prime}(p_a)\right) + f(p_a^{e+1})\right).
\end{aligned}
$$

边界条件为 $S_{\pi(\sqrt{n})}(x) = F_\text{prime}(x)$，最终答案为 $F(n)=S_0(n)+1$．最终表达式中的求和只在 $x\ge p_a^2$ 时才不为空，这就保证了提前终止．这一定义其实和 Lucy 算法中状态的定义一致；两者都保留素数，正是为了让每层的转移在 $x<p_a^2$ 时为空，从而获得 $O(n^{3/4}\log^{-1}n)$ 的时间复杂度．

??? example "模板题 [LOJ 6783. 简单的函数 加强版](https://loj.ac/p/6783) 参考实现"
    ```cpp
    --8<-- "docs/math/code/sum-multiplicative/unlucy.cpp"
    ```

利用 $S_a(n)$ 的这一版本实现相较于前述 $F_a(n)$ 版本更为简洁，常数也更小．

### 洲阁筛

非递归版本的扩展 Eratosthenes 筛实际上等价于洲阁筛．洲阁筛由任之洲在 2016 年提出．它将 $[1,n]$ 中的整数 $x$ 分解为 $py$，其中，$p$ 是 $1$ 或大于 $\sqrt{n}$ 的素因子，而 $y$ 不含有任何大于 $\sqrt{n}$ 的素因子；这样分解必然是唯一的，因为 $x\le n$ 至多只有一个大于 $\sqrt{n}$ 的素因子．由此，枚举分解中的 $y$，并利用函数 $f$ 的积性，就得到：

$$
\begin{aligned}
F(n) &= \sum_{y\le n,~\operatorname{gpf}(y)\le\sqrt{n}} f(y)\left(1 + \sum_{\sqrt{n} < p \le n/y}f(p)\right)\\
&= \sum_{y=1}^{\lfloor\sqrt{n}\rfloor}f(y)\left(1 + F_\text{prime}(n/y) - F_\text{prime}(\sqrt{n})\right) + \sum_{\sqrt{n}< y\le n,~\operatorname{gpf}(y)\le\sqrt{n}}f(y).
\end{aligned}
$$

利用 $F_\text{prime}$ 的值，第一项可以直接计算．而要得到第二项，只需计算 $g=\widehat\prod_{p\le \sqrt{n}}f_p$ 的前缀和 $G$，所求即 $G(n)-G(\sqrt{n})$．和扩展 Eratosthenes 筛一样，从大到小遍历 $p\le\sqrt{n}$，合并贡献即可．[^zhouge-variant]状态转移方程仍然是

$$
G_{a-1}(x) = G_a(x) + \sum_{e\ge 1,~ p_a^e\le x}f(p_a^e)G_a(x/p_a^e).
$$

只是初值条件替换成了 $G_{\pi(\sqrt{n})}(\cdot)=1$；相应地，$x<p_a^2$ 的位置无需维护，此时

$$
G_a(x) = 1 + F_\text{prime}(\min\{x,\sqrt{n}\}) - F_\text{prime}(\min\{x,p_a\}),
$$

即幸存下来的只有 $1$ 和 $(p_a,\min\{x,\sqrt{n}\}]$ 中的素数．前文的第一点优化同样适用．

??? example "模板题 [LOJ 6053. 简单的函数](https://loj.ac/p/6053) 参考实现"
    ```cpp
    --8<-- "docs/math/code/sum-multiplicative/zhou-1.cpp"
    ```

虽然洲阁筛本身只计算了 $F(n)$ 的值，但是很容易将它推广为计算块筛 $\mathcal S_f(n)$ 的版本．对于 $x\in D(n)$，如果 $x\le\sqrt{n}$，可以直接用线性筛计算；否则，有

$$
\begin{aligned}
F(x) &= \sum_{y=1}^{\lfloor\sqrt{n}\rfloor}f(y)\left(1 + F_\text{prime}(x/y) - F_\text{prime}(\min\{x/y,\sqrt{n}\})\right) + \sum_{\sqrt{n}< y\le x,~\operatorname{gpf}(y)\le\sqrt{n}}f(y) \\
&= F(\sqrt{n}) + \sum_{y=1}^{\lfloor x/\sqrt{n}\rfloor}f(y)\left(F_\text{prime}(x/y) - F_\text{prime}(\sqrt{n})\right) + G(x) - G(\sqrt{n}).
\end{aligned}
$$

这一部分的额外成本是

$$
O\left(\sum_{x\in D(n),~ x>\sqrt{n}}\dfrac{x}{\sqrt{n}}\right) = O\left(\sum_{i=1}^{\sqrt{n}}\dfrac{\sqrt{n}}{i}\right) = O(\sqrt{n}\log n)
$$

的，可以忽略不计．

??? example "模板题 [LOJ 6783. 简单的函数 加强版](https://loj.ac/p/6783) 参考实现"
    ```cpp
    --8<-- "docs/math/code/sum-multiplicative/zhou-2.cpp"
    ```

无论是计算点值还是块筛，洲阁筛的时间复杂度都是 $O(n^{3/4}\log^{-1}n)$ 的，空间复杂度都是 $O(\sqrt{n})$ 的．这和非递归版本的扩展 Eratosthenes 筛完全一致．实践中，由于洲阁筛常数略大，通常还是会使用非递归版本的扩展 Eratosthenes 筛．

### 改良 Min\_25 筛

Min\_25 在博客中给出了一版改良的实现．利用树状数组等技巧，可以将扩展 Eratosthenes 筛的时间复杂度改进为 $O(n^{2/3})$．国内竞赛选手有时会将这种算法称为「Min\_26 筛」．

考虑优化状态转移过程．从 $F_\text{prime}$ 出发求 $F$ 的过程可以分为如下三段：

-   $\pi(n^{1/3})< a \le \pi(n^{1/2})$：对于这一段，直接跳过逐层转移，转而直接计算结果．也就是说，考虑直接从 $F_\text{prime}$ 计算 $F_{\pi(n^{1/3})}(x)$．为此，考虑其意义：$F_{\pi(n^{1/3})}(x)$ 就是对所有素因子都严格大于 $n^{1/3}$ 的整数处 $f$ 函数值求和的结果．又因为 $x\le n$，这样的整数只可能是 $1$、素数、素数平方或者两个相异素数的乘积．由此，利用积性，可以直接写出 $F_{\pi(n^{1/3})}(x)$ 的表达式：

    $$
    F_{\pi(n^{1/3})}(x) = 1 + F_\text{prime}(x) - F_\text{prime}(\min\{x,n^{1/3}\}) + \sum_{n^{1/3} < p \le \sqrt{x}}\left(f(p^2) + f(p)\left(F_\text{prime}(x/p) - F_\text{prime}(p)\right)\right).
    $$

    当然，只有在 $x \ge p_{\pi(n^{1/3})+1}^2$ 时求和式才非空；否则，表达式就退化成边界条件．

-   $\pi(n^{1/6}) < a\le \pi(n^{1/3})$：对于这一段，将每层的转移分为两部分．设 $y = n^{2/3}$．对于 $x > y$，仍然用数组存储 $F_{a}(x)$ 的值；对于 $x \le y$，则转而使用树状数组维护 $F_{a}(x)$．进而，

    -   当 $x > y$ 时，自大到小地枚举 $x\in D(n)$，使用递推公式转移状态；过程中，如果 $x / p_a^e \le y$，就通过树状数组查询 $F_a(x/p_a^e)$ 的值．
    -   当 $x \le y$ 时，则枚举 $[1,y]$ 中所有满足 $\operatorname{lpf}(x) = p_a$ 的整数 $x$，并将 $f(x)$ 的贡献加入到树状数组中．

    为了节省空间，树状数组的下标对应的是 $D(n)\cap[1,y]$ 中的点．若将这些点依次记作 $1=x_1<x_2<\cdots<x_k$，那么，在树状数组第 $j$ 个位置处记录的就是 $F_a(x_j) - F_a(x_{j-1})$ 的值；自然地，令 $x_0=0$．

-   $0 < a\le \pi(n^{1/6})$：对于这一段，直接使用递推公式逐层转移．注意，不能在 $x < p_a^2$ 时提前终止．

算法的时间复杂度是 $O(n^{2/3})$ 的．第一段的时间成本是

$$
O\left(\sum_{x\in D(n),~ x > n^{2/3}}\pi(\sqrt{x})\right) = O\left(\sum_{i=1}^{n^{1/3}}\dfrac{\sqrt{n/i}}{\log n}\right) = O\left(\dfrac{n^{2/3}}{\log n}\right)
$$

的．第二段的时间成本主要分为两部分．对于 $x > y$ 的部分，需要更新 $O(n/y)$ 个 $F_{a-1}(x)$ 的值，每次更新需要访问 $O(\log_p n)$ 次 $F_a(x/p_a^e)$ 的值．即使这些访问都是对树状数组的查询，总成本也只有 $O((n/y)\log y\log_p n)$．第二段总共 $O(\pi(n^{1/3}))$ 层，所以这一部分的总成本是 $O\left(\pi(n^{1/3})\dfrac{n}{y}\log y\right) = O(n^{2/3})$ 的．对于 $x \le y$ 的部分，第二段中枚举的总次数就等于 $[1,y]$ 中最小素因子在区间 $(n^{1/6},n^{1/3}]$ 内的整数个数．这些整数都是 $n^{1/6}$‑粗糙数，其个数只有 $O\left(\dfrac{y}{\log y}\right)$．[^rough]单次修改是 $O(\log y)$ 的．所以，总成本仍然是 $O(y)=O(n^{2/3})$ 的．第三段，单层转移是 $O(\sqrt{n}\log_p n)$，总层数是 $O(\pi(n^{1/6}))$ 的，总时间成本就是 $O\left(\dfrac{n^{2/3}}{\log n}\right)$ 的．在上述分析中，由前文脚注[^log-p-n]可知，单层转移中的 $\log_p n$ 因子并不影响求和后的最终复杂度．

算法的空间复杂度是 $O(\sqrt{n})$ 的．算法有两处设计保证了这一点仍然成立．第一，在存储树状数组时，仅存储了 $D(n)$ 中的关键点处 $F_a$ 的值．第二，更新树状数组时，枚举的整数必然具有形式 $p_ar$，其中，$r$ 的最小素因子不小于 $p_a$，但是 $p_ar\le y$，故而，$r\le y/p_a < n^{1/2}$，这就保证了只需要线性筛预处理到 $\sqrt{n}$ 为止即可满足需求．

当然，为了保证整体时间复杂度仍然是 $O(n^{2/3})$ 的，$F_\text{prime}$ 的计算不再可以使用未经优化的 Lucy 算法．对于 Lucy 算法的优化，可以仿照上述过程，但需要自小到大地枚举 $a$，且不能移除素数的贡献．其中，$\pi(n^{1/3})< a \le \pi(n^{1/2})$ 这一段的封闭形式是

$$
F_\text{prime}(x) = S_{\pi(n^{1/3})}(x) - \sum_{n^{1/3} < p \le\sqrt{x}}(f(p^2) + f(p)(F_\text{prime}(x/p)-F_\text{prime}(x))).
$$

但仅就优化 Lucy 算法而言，这一段可以不必使用封闭形式，直接利用递推公式转移，复杂度也是正确的．

??? example "模板题 [LOJ 6785. 简单的函数 10^13 版](https://loj.ac/p/6785) 参考实现"
    ```cpp
    --8<-- "docs/math/code/sum-multiplicative/min26.cpp"
    ```

改良 Min\_25 筛足以处理 $n\sim 10^{13}$ 的问题．

## Powerful Number 筛

从对扩展 Eratosthenes 筛的讨论可以看出，积性函数求和的亚线性算法并不受限于函数在素数平方及以上幂次处的取值．不过，如果允许自由选取这些取值，往往可以进一步简化求和过程．例如，要对满足 $f(p^e)=p-e~(e\ge 1)$ 的积性函数 $f$ 求和，这个 $f$ 与 Euler 函数 $\varphi$ 在素数处取值相同，只在 $p^e~(e > 1)$ 处存在差异，而 $\varphi$ 的前缀和可以通过 [杜教筛](./hyperbola.md#杜教筛) 很方便地计算．又如，即使 $f$ 在素数处的取值与任何常见积性函数都不同，只要把 $p^e~(e > 1)$ 处的取值全部改为 $0$，就可以消去扩展 Eratosthenes 筛中逐层转移时的 $\log_p n$ 因子，从而降低算法常数．

受此启发，考虑如下问题：对于积性函数 $f$ 和 $g$，如果

-   它们在素数处取值相同，即 $f(p)=g(p)$；
-   $g$ 的块筛 $\mathcal S_g(n)$ 已知，

那么，能否快速求出前缀和 $F(n)$，或者进一步地，快速计算块筛 $\mathcal S_f(n)$ 呢？

**Powerful Number 筛**（简称 **PN 筛**）提供了这样一种算法．它可以快速修改积性函数在素数平方及以上幂次处的贡献：从块筛 $\mathcal S_g(n)$ 出发，在 $O(\sqrt{n})$ 时间内得到点值 $F(n)$，在 $O(\sqrt{n}\log n)$ 时间内得到块筛 $\mathcal S_f(n)$．也就是说，只要支付这些成本，就可以自由选取 $g$ 在 $p^e~(e > 1)$ 处的取值，先算出容易计算的 $\mathcal S_g(n)$，再用 PN 筛修正回 $f$ 的前缀和或块筛．这无论是解决某些特殊形式的求和问题，还是加速一般积性函数求和，都是有用的手段．

### Powerful Number

考察 $f$ 和 $g$ 的 Dirichlet 商 $h$，即 $f=h\ast g$．由于 $f$ 和 $g$ 都是积性的，$h$ 同样是积性的．交换求和次序，就得到

$$
F(n) = \sum_{m\le n}\sum_{k\mid m}h(k)g(m/k) = \sum_{k=1}^{n}h(k)G(n/k).
$$

利用该式直接计算，复杂度是 $O(n)$ 的．但是，$h$ 取非零值的位置相当稀疏；只要能够快速枚举这些位置，就能快速计算该和式．

为此，考察 $h$ 的性质．由 Dirichlet 卷积的定义，有 $f(p)=h(1)g(p)+h(p)g(1)$；代入 $g(1)=h(1)=1$ 且 $f(p)=g(p)$，即得 $h(p)=0$．又因为 $h$ 是积性函数，所以只要 $k$ 中包含幂次为一的素因子，$h(k)$ 就一定为零．也就是说，$h$ 能够取非零值的位置一定落在集合

$$
\mathrm{PN} = \{k\in\mathbf N_+ : \forall p \in\mathbf P(p\mid k\implies p^2\mid k)\}
$$

之中．这一集合中的元素称为 **Powerful Number**（即「幂数」）．按定义，$1\in\mathrm{PN}$．

Powerful Number 相当稀疏．任取 $k\in\mathrm{PN}$，记其素因数分解为 $k=\prod_{i=1}^{s}p_i^{e_i}$．因为 $k$ 不含幂次为一的素因子，所以 $e_i\ge 2$；也就是说，如果 $e_i$ 是奇数，那么 $e_i\ge 3$．令 $b$ 是 $k$ 中所有奇幂次素因子的乘积，就一定有 $b^3\mid k$；又因为 $k/b^3$ 中所有素因子的幂次都是偶数，所以 $k/b^3$ 是完全平方数，记其平方根为 $a$．由此，所有 $k\in\mathrm{PN}$ 都具有 $a^2b^3$ 的形式．反过来，枚举所有满足 $a^2b^3\le n$ 的数对 $(a,b)$，就得到 Powerful Number 个数的一个上界：

$$
\#\{k\in\mathrm{PN}:k\le n\} \le \sum_{a=1}^{\lfloor\sqrt{n}\rfloor}\left(\dfrac{n}{a^2}\right)^{1/3} \le \int_0^{\sqrt{n}}\dfrac{n^{1/3}}{x^{2/3}}\mathrm{d}x = O(\sqrt{n}).
$$

另一方面，所有完全平方数都是 Powerful Number，而这些平方数有 $\Omega(\sqrt{n})$ 个．所以，不超过 $n$ 的 Powerful Number 恰有 $\Theta(\sqrt{n})$ 个．这说明快速枚举这些位置是有可能的．

要枚举不超过 $n$ 的所有 Powerful Number，只需用线性筛求出 $[1,\sqrt{n}]$ 中的素数，再在这些素数上按递增顺序做 DFS：每次添加一个新的素因子 $p$ 时，从 $e=2$ 开始枚举其幂次，直到乘积超过 $n$ 就回溯．按递增顺序枚举素数，保证了每个 Powerful Number 恰好被搜索到一次；而每层枚举一旦失败就立刻回溯，失败的尝试次数不超过结点总数的常数倍．因此，搜索的总代价与 Powerful Number 的个数同阶，也是 $\Theta(\sqrt{n})$ 的．

从 Dirichlet 卷积的角度看，PN 筛的思想就是用容易求和的 $g$ 作为 $f$ 的一阶近似，而误差 $h$ 只落在稀疏的 Powerful Number 上，因此可以快速修正．算法的名称也正来源于此．

### 点值计算

应用 PN 筛计算点值 $F(n)$，只需在上述求和式中枚举 Powerful Number：

$$
F(n) = \sum_{k\le n,~k\in\mathrm{PN}} h(k)G(n/k).
$$

枚举 Powerful Number 的方法已经给出，剩下的问题是 $h$ 的计算．只要 $h(p^e)$ 的取值已知，就可以在 DFS 的过程中顺便维护搜索到的每个 $k$ 处的 $h(k)$．而计算 $h(p^e)$ 通常有两种方法：

-   对于较为特殊的 $f$ 和 $g$，可以推导出 $h(p^e)$ 关于 $p$ 和 $e$ 的表达式，在 DFS 过程中 $O(1)$ 计算．
-   对于一般情形，可以利用 Dirichlet 卷积的定义得到递推关系

    $$
    h(p^e) = f(p^e) - \sum_{i=1}^{e}g(p^i)h(p^{e-i}),
    $$

    并在 DFS 之前打表预处理．因为 $h(p^0)=1$ 且 $h(p)=0$，递推只需从 $e=2$ 开始．

综合前文讨论，PN 筛计算点值的流程如下：

1.  选取合适的积性函数 $g$，计算块筛 $\mathcal S_g(n)$；
2.  利用线性筛预处理 $[1,\sqrt{n}]$ 中的素数；
3.  用上述两种方法之一准备 $h(p^e)$ 的取值；
4.  枚举 $[1,n]$ 中的 Powerful Number，累加得到 $F(n)$．

不计 $\mathcal S_g(n)$ 的时空成本，PN 筛的时空复杂度都是 $O(\sqrt{n})$ 的．其中，线性筛与 Powerful Number 枚举的代价前文已经给出，只需再讨论 $h(p^e)$ 的时空开销：$[1,\sqrt{n}]$ 中共有 $\pi(\sqrt{n})$ 个素数；对于每个素数 $p$，需要长度为 $O(\log_p n)$ 的数组存储 $h(p^e)$ 的值，而每个值都需要对 $O(\log_p n)$ 项求和．所以，总的空间和时间开销分别是

$$
O\left(\sum_{p\le\sqrt{n}}\log_p n\right) = O\left(\dfrac{\sqrt{n}}{\log n}\right),\quad O\left(\sum_{p\le\sqrt{n}}(\log_p n)^2\right) = O\left(\dfrac{\sqrt{n}}{\log n}\right)
$$

的．如前文脚注[^log-p-n]所言，这些 $\log_p n$ 项并没有增加复杂度，只是增大了算法常数．由此可知，PN 筛的时空复杂度都是 $O(\sqrt{n})$ 的．

实际应用 PN 筛时，重点往往是积性函数 $g$ 的选取．常见的选取方法有两种：

-   如果 $f$ 在素数处的取值与某个常见积性函数一致，而后者的前缀和可以用杜教筛等方法快速求出，就直接取 $g$ 为该积性函数．此时 $\mathcal S_g(n)$ 本身就是容易计算的．
-   否则，仍然需要用扩展 Eratosthenes 筛求出 $\mathcal S_g(n)$，但可以借 $g$ 在 $p^e~(e > 1)$ 处的取值降低它的常数：取 $g(p^e)=0~(e > 1)$ 可以消去逐层转移中枚举幂次的循环；取 $g(p^e)=f(p)^e$ 则使 $g$ 成为完全积性函数，同样不必枚举幂次．

下面通过模板题展示这两种选取方法．

??? example "模板题 [LOJ 6053. 简单的函数](https://loj.ac/p/6053) 参考实现"
    题目要求计算满足 $f(p^e)=p\oplus e~(e>0)$ 的积性函数 $f$ 的前缀和．$g$ 的选取不同，相应的算法也不同：
    
    === "方法一：杜教筛 + PN 筛"
        设 $\varphi$ 是 Euler 函数，$\Phi$ 是其前缀和．因为 $f(p)=p\oplus 1$ 仅在 $p = 2$ 处与 $\varphi(p)=p-1$ 不同，所以考虑用 $\varphi$ 对 $f$ 做一阶近似，只需补上 $p=2$ 处的差额 $2$．故而，设数论函数 $w$ 满足 $w(1)=1,~w(2)=2$ 且 $w(n)=0~(n\ge 3)$，它显然是积性的；又设 $g = w\ast\varphi$，于是 $g$ 也是积性的，且 $f(p)=g(p)$．至于 $p^e~(e>1)$ 处的取值，直接计算可知，对奇素数 $p$ 有 $g(p^e) = p^{e-1}(p-1)$，而 $g(2^e)=2^e$；据此即可递推出 $h$ 在 $p^e~(e>1)$ 处的取值．
        
        由于 $w$ 仅在 $n=1,2$ 处非零，对 $\Phi$ 做简单修正就得到 $G$，即 $G(x) = \Phi(x) + 2\Phi(x/2)$．因此，只要利用杜教筛得到 $\phi$ 的块筛，再利用该表达式得到 $g$ 的块筛，最后用 PN 筛就可以得到点值 $F(n)$．
        
        这样得到的求和算法，时空复杂度都是 $O(n^{2/3})$ 的．
        
        ```cpp
        --8<-- "docs/math/code/sum-multiplicative/pn-du.cpp"
        ```
    
    === "方法二：扩展 Eratosthenes 筛 + PN 筛"
        令 $g(p^e)=0~(e>1)$，先用非递归版本的扩展 Eratosthenes 筛求出块筛 $\mathcal S_g(n)$，再用 PN 筛得到点值 $F(n)$．由于 $f(p)=g(p)$，Lucy 算法计算 $F_\text{prime}$ 的部分完全不必改动；而 $S_a(n)$ 的递推公式则简化为
        
        $$
        S_{a-1}(x) = S_a(x) + [p_a^2\le x]\,f(p_a)\left(S_a(x/p_a) - F_\text{prime}(p_a)\right),
        $$
        
        得到的结果就是 $\mathcal S_g(n)$．同理，$h(p^e)$ 的递推公式也简化为 $h(p^e) = f(p^e) - f(p)h(p^{e-1})$．
        
        这样得到的求和算法，时间复杂度是 $O(n^{3/4}\log^{-1}n)$ 的，空间复杂度是 $O(\sqrt{n})$ 的．
        
        ```cpp
        --8<-- "docs/math/code/sum-multiplicative/pn-unlucy.cpp"
        ```

实际应用时，第一种方法受限于杜教筛性能，在数据规模较小时用时甚至不如 Black 算法，在数据规模较大时空间占用又过大；相比之下，第二种方法则更为通用，运行效率也相当不错．

### 块筛计算

应用 Powerful Number 筛的思想，还可以快速计算块筛 $\mathcal S_f(n)$．

??? example "模板题 [LOJ 6783. 简单的函数 加强版](https://loj.ac/p/6783) 参考实现"
    ```cpp
    --8<-- "docs/math/code/sum-multiplicative/pn-block.cpp"
    ```

PN 筛优秀的时空表现使得它几乎不会成为整体算法的性能瓶颈，是改良整体算法常数的有效手段．

## Exp-Log 法

### ZZT 求和法

### ZKY 求和法

## 例题

## 习题

-   [Luogu P5325【模板】Min\_25 筛](https://www.luogu.com.cn/problem/P5325)

PN 筛：

-   [Project Euler 708 Twos are all you need](https://projecteuler.net/problem=708)
-   [Project Euler 639 Summing a multiplicative function](https://projecteuler.net/problem=639)
-   [Project Euler 484 Arithmetic Derivative](https://projecteuler.net/problem=484)

## 参考资料与注释

-   [朱震霆．一些特殊的数论函数求和问题．国家集训队 2018 年论文集．](https://github.com/OI-wiki/libs/blob/master/%E9%9B%86%E8%AE%AD%E9%98%9F%E5%8E%86%E5%B9%B4%E8%AE%BA%E6%96%87/%E5%9B%BD%E5%AE%B6%E9%9B%86%E8%AE%AD%E9%98%9F2018%E8%AE%BA%E6%96%87%E9%9B%86.pdf)
-   [任之洲．积性函数求和的几种方法．国家集训队 2016 年论文集．](https://github.com/OI-wiki/libs/blob/master/%E9%9B%86%E8%AE%AD%E9%98%9F%E5%8E%86%E5%B9%B4%E8%AE%BA%E6%96%87/%E5%9B%BD%E5%AE%B6%E9%9B%86%E8%AE%AD%E9%98%9F2016%E8%AE%BA%E6%96%87%E9%9B%86.pdf)
-   [周康阳．关于积性函数求和问题的一些进展．国家集训队 2024 年论文集．](https://github.com/OI-wiki/libs/blob/master/%E9%9B%86%E8%AE%AD%E9%98%9F%E5%8E%86%E5%B9%B4%E8%AE%BA%E6%96%87/IOI2024%E9%9B%86%E8%AE%AD%E9%98%9F%E8%AE%BA%E6%96%87%E9%9B%86.pdf)
-   [The prefix-sum of multiplicative function: the black algorithm - baihacker](https://baihacker.github.io/main/2020/The_prefix-sum_of_multiplicative_function_the_black_algorithm.html)
-   [Summing Multiplicative Functions (Pt. 1.5) - griff's math blog!](https://gbroxey.github.io/blog/2025/04/07/mult-sum-1-5.html)
-   [Sum of Multiplicative Functions - Min\_25](https://web.archive.org/web/20211009144526/https://min-25.hatenablog.com/entry/2018/11/11/172216)
-   [Min-25 筛学习笔记 - DaiRuiChen007](https://www.cnblogs.com/DaiRuiChen007/p/17492875.html)
-   [On the Min25 sieve and extensions/SPOJ ASSIEVE - box](https://codeforces.com/blog/entry/92703)
-   [洲阁筛学习笔记 - myee](https://www.cnblogs.com/myee/p/zhouge-sieve.html)
-   [积性函数线性筛/杜教筛/洲阁筛学习笔记 - Bill Yang's Blog](https://blog.bill.moe/multiplicative-function-sieves-notes)
-   [Powerful number - Wikipedia](https://en.wikipedia.org/wiki/Powerful_number)
-   [利用 powerful number 求积性函数前缀和 - ZZQ's Blog](https://www.cnblogs.com/zzqsblog/p/9904271.html)
-   [Powerful number 筛略解 - 破壁人五号](https://www.cnblogs.com/wallbreaker5th/p/13901487.html)
-   [杜教筛（+ 贝尔级数 + powerful number）- command\_block](https://www.luogu.com.cn/blog/command-block/du-jiao-shai)
-   [积性函数求和问题的一种筛法 - whzzt](https://blog.csdn.net/whzzt/article/details/104105025)
-   [An analog of the Euler transform for Dirichlet series (comment) - ecnerwala](https://codeforces.com/blog/entry/91632#comment-802482)
-   [关于积性函数求和的一点想法 - zhoukangyang](https://www.cnblogs.com/zkyJuruo/p/17544928.html)
-   [OI 中常用数论函数求和法的简化陈述 - negiizhao](https://negiizhao.blog.uoj.ac/blog/7165)
-   [OI 积性函数求和传统做法的最后一块拼图 - negiizhao](https://negiizhao.blog.uoj.ac/blog/8961)
-   [积性函数求和新做法初步研究 - negiizhao](https://negiizhao.blog.uoj.ac/blog/9019)

[^black]: 这个名字源于 baihacker 的博文．

[^inv-pn]: 另一个角度或许能更直观地看出 Powerful Number 稀疏性带来的增益．枚举所有 $kd\le n$ 时，复杂度中的 $\log n$ 因子源自倒数和 $\sum_{k\le n}1/k$ 的增长速度；对于 Powerful Number 来说，由于它足够稀疏，倒数和 $\sum_{k\in\mathrm{PN}}1/k$ 是收敛的，其值为 $\prod_{p}\left(1+\dfrac{1}{p(p-1)}\right) = \dfrac{\zeta(2)\zeta(3)}{\zeta(6)} = 1.9435964\cdots$，所以就没有这一对数因子．Powerful Number 的倒数和可以参考 [Powerful number - Wikipedia](https://en.wikipedia.org/wiki/Powerful_number#Mathematical_properties)．

[^ivic-pomerance]: 该集合见于 [OEIS A070003](https://oeis.org/A070003)．对该数量的估计引自 Ivić, Aleksandar. "On sums involving reciprocals of the largest prime factor of an integer II." Acta Arithmetica 71.3 (1995): 229-251. 一文，该文引用了 Ivić, A., and C. Pomerance. "Estimates for certain sums involving the largest prime factor of an integer." Coll. Math. Soc. J. Bolyai 34, North-Holland, 1984: 769-789. 中的结果．

[^log-p-n]: 一般地，在对素数求和的算式中插入任意固定次幂的因子 $(\log_p n)^t$，只会改变常数，不改变渐近阶．这可以通过积分估计说明，也可以在 $n^c$ 处分段直观地看出：取定足够小的常数 $c>0$，对于 $p>n^c$，有 $(\log_p n)^t<c^{-t}$，只是一个常数因子；对于 $p\le n^c$，这样的素数不超过 $n^c$ 个，而每项多出的因子不超过 $\log^t n$，由于 $c$ 可以取得任意小，这一部分在本文各处都可以忽略．

[^pn-block-bound]: 朱震霆在博文中给出的估计是 $\tilde O(n^{3/5})$ 的．这是因为他没有详细说明 $x\le z$ 部分的做法，讨论复杂度时沿用一般情形的结论，将第一部分的成本估作 $\tilde O(z)$，平衡后得到 $z=n^{3/5}$；而本文的做法只枚举 $d\le\sqrt{n}$ 的数对，第一部分的成本只有 $O(n^{1/4}z^{1/2})$．他在文末代码实现中，第一部分实际使用的正是本文叙述的做法．这一优化并非可有可无：如果线性筛出 $f$ 在 $[1,z]$ 上的全部点值，这一段直接求前缀和即可，但空间复杂度会退化为 $O(z)$．

[^rough]: 参见 [Buchstab function - Wikipedia](https://en.wikipedia.org/wiki/Buchstab_function#Applications)．

[^zhouge-variant]: 此处描述的是任之洲论文中 6.5.4 小节的「另一种实现」．任之洲本人提出的实现方法是自小到大遍历素数 $p$ 来进行状态转移．两者并无本质区别．
