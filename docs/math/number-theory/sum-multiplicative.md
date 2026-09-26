author: AlephInfinity1, aofall, Backl1ght, billchenchina, c-forrest, CCXXXI, chenyichen0420, CoelacanthusHex, CSPNOIP, cy1999, Early0v0, Enoch-xm, Enter-tainer, Great-designer, Haohu Shen, HeRaNO, iamtwz, Ir1d, kenlig, Konano, ksyx, LaDeXX, lrherqwq, Marcythm, MegaOwIer, Nanarikom, ouuan, Persdre, Revltalize, SamZhangQingChuan, scp020, shuzhouliu, StudyingFather, Tiphereth-A, Xeonacid, xyf007, ZnPdCo

前置知识：[积性函数](./basic.md#积性函数)、[素数幂前缀和](./prime-counting.md#推广素数幂前缀和)、[Dirichlet 卷积及生成函数](./dirichlet.md)、[块筛及其卷积](./hyperbola.md#块筛及其卷积)

## 引入

本文介绍能在亚线性时间内计算积性函数前缀和的算法．

## 记号约定

本文使用如下记号和约定：

-   用 $a,e,i,j,k,n$ 表示自然数．
-   用 $\mathbf P$ 表示（正）素数集，字母 $p,q$ 表示素数．特别地，用 $p_a$ 表示第 $a$ 小的素数，并补充规定 $p_0=1$．
-   用 $\operatorname{lpf}(n)$ 和 $\operatorname{gpf}(n)$ 分别表示 $n$ 的最小和最大素因子．规定 $\operatorname{lpf}(1)=+\infty$ 且 $\operatorname{gpf}(1)=1$．
-   用 $\pi(n)$ 表示素数计数函数，即不超过 $n$ 的素数个数．
-   用 $D(n)=\{\lfloor n/i\rfloor : i=1,2,\dots,n\}$ 表示数论分块关键值的集合．它的性质参见 [数论分块](./sqrt-decomposition.md#性质) 对应小节．
-   用小写字母 $f,g,h$ 表示积性函数，故总有 $f(1)=1$．
-   用 $f\ast g$ 表示 Dirichlet 卷积，$\widehat{\prod}$ 表示对应的连乘积．
-   $f_p(n) = f(n)[\exists e\ge 0(n=p^e)]$ 是 $f$ 限制在素数 $p$ 的幂次上得到的函数．注意 $f_p(1)=f(1)=1$．
-   $F(n) = \sum_{k=1}^n f(k)$，即 $f$ 的前缀和．规定 $F(0)=0$，下同．
-   $F_{\text{prime}}(n) = \sum_{p\le n} f(p)$，即 $f$ 在素数处的前缀和．
-   $F_a(n) = \sum_{k=1}^n [\operatorname{lpf}(k) > p_a]\,f(k)$，即 $[1,n]$ 中不含前 $a$ 个素数作为因子的正整数处函数值的和．由于 $\operatorname{lpf}(1)=+\infty$，$k=1$ 总在求和范围内．特别地，$F_0(n)=F(n)$；而且，$F_a(n)=1+F_\text{prime}(n)-F_\text{prime}(\min\{n,p_a\})$ 对所有 $a\ge\pi(\sqrt{n})$ 都成立．
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
&= S_a(x) + \sum_{e\ge 1,~p_a^{e+1}\le x}\left(f(p_a^e)\left[S_a(x/p_a^e) - F_\text{prime}(p_a)\right] + f(p_a^{e+1})\right).
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

## Powerful Number 筛

## 欧拉变换法

### zzt 求和法

### zky 求和法

## PN 筛

### 定义

Powerful Number（以下简称 PN）筛类似于杜教筛，或者说是杜教筛的一个扩展，可以拿来求一些积性函数的前缀和．

**要求**：

-   存在一个函数 $g$ 满足：
    -   $g$ 是积性函数．
    -   $g$ 易求前缀和．
    -   对于质数 $p$，$g(p) = f(p)$．

假设现在要求积性函数 $f$ 的前缀和 $F(n) = \sum_{i=1}^{n} f(i)$．

### Powerful Number

**定义**：对于正整数 $n$，记 $n$ 的质因数分解为 $n = \prod_{i=1}^{m} p_{i}^{e_{i}}$．$n$ 是 PN 当且仅当 $\forall 1 \le i \le m, e_{i} > 1$．

**性质 1**：所有 PN 都可以表示成 $a^{2}b^{3}$ 的形式．

**证明**：若 $e_i$ 是偶数，则将 $p_{i}^{e_{i}}$ 合并进 $a^{2}$ 里；若 $e_i$ 为奇数，则先将 $p_{i}^{3}$ 合并进 $b^{3}$ 里，再将 $p_{i}^{e_{i}-3}$ 合并进 $a^{2}$ 里．

**性质 2**：$n$ 以内的 PN 至多有 $O(\sqrt{n})$ 个．

**证明**：考虑枚举 $a$，再考虑满足条件的 $b$ 的个数，有 PN 的个数约等于

$$
\int_{1}^{\sqrt{n}} \sqrt[3]{\frac{n}{x^2}} \mathrm{d}x = O(\sqrt{n})
$$

那么如何求出 $n$ 以内所有的 PN 呢？线性筛找出 $\sqrt{n}$ 内的所有素数，再 DFS 搜索各素数的指数即可．由于 $n$ 以内的 PN 至多有 $O(\sqrt{n})$ 个，所以至多搜索 $O(\sqrt{n})$ 次．

### PN 筛

首先，构造出一个易求前缀和的积性函数 $g$，且满足对于素数 $p$，$g(p) = f(p)$．记 $G(n) = \sum_{i=1}^{n} g(i)$．

然后，构造函数 $h = f / g$，这里的 $/$ 表示狄利克雷卷积除法．根据狄利克雷卷积的性质可以得知 $h$ 也为积性函数，因此 $h(1) = 1$．$f = g * h$，这里 $*$ 表示狄利克雷卷积．

对于素数 $p$，$f(p) = g(1)h(p) + g(p)h(1) = h(p) + g(p) \implies h(p) = 0$．根据 $h(p)=0$ 和 $h$ 是积性函数可以推出对于非 PN 的数 $n$ 有 $h(n) = 0$，即 $h$ 仅在 PN 处取有效值．

现在，根据 $f = g * h$ 有

$$
\begin{aligned}
F(n) &= \sum_{i = 1}^{n} f(i)\\
     &= \sum_{i = 1}^{n} \sum_{d|i} h(d) g\left(\frac{i}{d}\right)\\
     &= \sum_{d=1}^{n} \sum_{i=1}^{\lfloor \frac{n}{d}\rfloor} h(d) g(i)\\
     &= \sum_{d=1}^{n} h(d) \sum_{i=1}^{\lfloor \frac{n}{d}\rfloor}  g(i) \\
     &= \sum_{d=1}^{n} h(d) G\left(\left\lfloor \frac{n}{d}\right\rfloor\right)\\
     &= \sum_{\substack{d=1 \\ d \text{ is PN}}}^{n}h(d) G\left(\left\lfloor \frac{n}{d}\right\rfloor\right)
\end{aligned}
$$

$O(\sqrt{n})$ 找出所有 PN，计算出所有 $h$ 的有效值．对于 $h$ 有效值的计算，只需要计算出所有 $h(p^c)$ 处的值，就可以根据 $h$ 为积性函数推出 $h$ 的所有有效值．现在对于每一个有效值 $d$，计算 $h(d)G\left(\left\lfloor \dfrac{n}{d} \right\rfloor\right)$ 并累加即可得到 $F(n)$．

下面考虑计算 $h(p^c)$，一共有两种方法：一种是直接推出 $h(p^c)$ 仅与 $p, c$ 有关的计算公式，再根据公式计算 $h(p^c)$；另一种是根据 $f = g * h$ 有 $f(p^c) = \sum_{i=0}^c g(p^i)h(p^{c-i})$，移项可得 $h(p^c) = f(p^c) - \sum_{i=1}^{c}g(p^i)h(p^{c-i})$，现在就可以枚举素数 $p$ 再枚举指数 $c$ 求解出所有 $h(p^c)$．

#### 过程

1.  构造 $g$
2.  构造快速计算 $G$ 的方法
3.  计算 $h(p^c)$
4.  搜索 PN，过程中累加答案
5.  得到结果

对于第 3 步，可以直接根据公式计算，可以使用枚举法预处理打表，也可以搜索到了再临时推．

#### 性质

以使用第二种方法计算 $h(p^c)$ 为例进行分析．可以分为计算 $h(p^c)$ 和搜索两部分进行分析．

对于第一部分，根据 $O(\sqrt{n})$ 内的素数个数为 $O\left(\dfrac{\sqrt{n}}{\log n}\right)$，每个素数 $p$ 的指数 $c$ 至多为 $\log n$，计算 $h(p^c)$ 需要循环 $(c - 1)$ 次，由此有第一部分的时间复杂度为 $O\left(\dfrac{\sqrt{n}}{\log n} \cdot \log n \cdot \log n\right) = O(\sqrt{n}\log{n})$，且这是一个宽松的上界．根据题目的不同还可以添加不同的优化，从而降低第一部分的时间复杂度．

对于搜索部分，由于 $n$ 以内的 PN 至多有 $O(\sqrt{n})$ 个，所以至多搜索 $O(\sqrt{n})$ 次．对于每一个 PN，根据计算 $G$ 的方法不同，时间复杂度也不同．例如，假设计算 $G\left(\left\lfloor \dfrac{n}{d}\right\rfloor\right)$ 的时间复杂度为 $O(1)$，则第二部分的复杂度为 $O(\sqrt{n})$．

特别地，若借助杜教筛计算 $G\left(\left\lfloor \dfrac{n}{d}\right\rfloor\right)$，则第二部分的时间复杂度为杜教筛的时间复杂度，即 $O(n^{\frac{2}{3}})$．因为若事先计算一次 $G(n)$，并且预先使用线性筛优化和用支持快速随机访问的数据结构（如 C++ 中的 `std::map` 和 `std::unordered_map`）记录较大的值，则杜教筛过程中用到的 $G\left(\left\lfloor \dfrac{n}{d}\right\rfloor\right)$ 都是线性筛中记录的或者 `std::map` 中记录的，这一点可以直接用程序验证．

对于空间复杂度，其瓶颈在于存储 $h(p^c)$．若使用二维数组 $a$ 记录，$a_{i,j}$ 表示 $h(p_i^j)$ 的值，则空间复杂度为 $O\left(\dfrac{\sqrt{n}}{\log n} \cdot \log n\right) = O(\sqrt{n})$．

## 例题

Min\_25 筛：

???+ example "[Luogu P4213【模板】杜教筛](https://www.luogu.com.cn/problem/P4213)"
    求 $\displaystyle \sum_{i = 1}^{n} \varphi(i)$ 和 $\displaystyle \sum_{i = 1}^{n} \mu(i)$．

??? note "解答"
    对于求 $\varphi(i)$ 的前缀和，首先易知 $f(p) = p - 1$．对于 $f(p)$ 的一次项 $(p)$，有 $g(p) = p, G_{0}(n) = \sum_{i = 2}^{n} g(i) = \frac{(n + 2) (n - 1)}{2}$；对于 $f(p)$ 的常数项 $(-1)$，有 $g(p) = -1, G_{0}(n) = \sum_{i = 2}^{n} g(i) = -n + 1$．筛两次加起来即可得到 $F_{\mathrm{prime}}$ 的所有 $O(\sqrt{n})$ 个所需点值．
    
    对于求 $\mu(i)$ 的前缀和，易知 $f(p) = -1$．则 $g(p) = -1, G_{0}(n) = \sum_{i = 2}^{n} g(i) = -n + 1$．直接筛即可得到 $F_{\mathrm{prime}}$ 的所有 $O(\sqrt{n})$ 个所需点值．

???+ example "[LOJ 6053 简单的函数](https://loj.ac/p/6053)"
    给定 $f(n)$：
    
    $$
    f(n) = \begin{cases}
        1 & n = 1 \\
        p \operatorname{xor} c & n = p^{c} \\
        f(a)f(b) & n = ab \land a \perp b
    \end{cases}
    $$
    
    求 $\displaystyle \sum_{i = 1}^{n} f(i)$．

??? note "解答"
    易知 $f(p) = p - 1 + 2[p = 2]$．则按照筛 $\varphi$ 的方法筛，对 $2$ 讨论一下即可．

??? note "参考代码"
    ```cpp
    --8<-- "docs/math/code/min-25/min-25_1.cpp"
    ```

PN 筛：

???+ example "[Luogu P5325【模板】Min_25 筛](https://www.luogu.com.cn/problem/P5325)"
    给定积性函数 $f(p^k) = p^k(p^k-1)$，求 $\sum_{i=1}^{n} f(i)$．

??? note "解答"
    易得 $f(p) = p(p-1) = \operatorname{id}(p)\varphi(p)$，构造 $g(n) = \operatorname{id}(n)\varphi(n)$．
    
    考虑使用杜教筛求 $G(n)$，根据 $(\operatorname{id}\cdot \varphi) * \operatorname{id} = \operatorname{id}_2$ 可得 $G(n)= \sum_{i=1}^{n} i^2 - \sum_{d=2}^{n} d \cdot G\left(\left\lfloor \dfrac{n}{d} \right\rfloor\right)$．
    
    之后 $h(p^k)$ 的取值可以枚举计算，这种方法不再赘述．
    
    此外，此题还可以直接求出 $h(p^k)$ 仅与 $p, k$ 有关的公式，过程如下：
    
    $$
    \begin{aligned}
    & f(p^k) = \sum_{i=0}^{k} g(p^{k-i})h(p^i)\\
    \iff & p^k(p^k-1) = \sum_{i=0}^{k} p^{k-i}\varphi(p^{k-i}) h(p^i)\\
    \iff & p^k(p^k-1) = \sum_{i=0}^{k} p^{2k-2i-1}(p - 1) h(p^i)\\
    \iff & p^k(p^k-1) = h(p^k) + \sum_{i=0}^{k-1} p^{2k-2i-1}(p - 1) h(p^i)\\
    \iff & h(p^k) = p^k(p^k-1) - \sum_{i=0}^{k-1} p^{2k-2i-1}(p - 1) h(p^i)\\
    \iff & h(p^k) - p^2h(p^{k-1}) = p^{k}(p^k-1)-p^{k+1}(p^{k-1}-1) - p(p-1)h(p^{k-1})\\
    \iff & h(p^k) - ph(p^{k-1}) = p^{k+1} - p^k\\
    \iff & \frac{h(p^k)}{p^k} - \frac{h(p^{k-1})}{p^{k-1}} = p - 1\\
    \end{aligned}
    $$
    
    再根据 $h(p) = 0$，通过累加法即可推出 $h(p^k) = (k-1)(p-1)p^k$．

??? note "参考代码"
    ```cpp
    --8<-- "docs/math/code/powerful-number/powerful-number_1.cpp"
    ```

???+ example "[「LOJ #6053」简单的函数](https://loj.ac/problem/6053)"
    略．

??? note "解答"
    给定 $f(n)$：
    
    $$
    f(n) =
    \begin{cases}
    1 & n = 1 \\
    p \oplus c & n=p^c \\
    f(a)f(b) & n=ab \text{ and } a \perp b
    \end{cases}
    $$
    
    易得：
    
    $$
    f(p) =
    \begin{cases}
    p + 1 & p = 2 \\
    p - 1 & \text{otherwise} \\
    \end{cases}
    $$
    
    构造 $g$ 为
    
    $$
    g(n) =
    \begin{cases}
    3 \varphi(n) & 2 \mid n \\
    \varphi(n) & \text{otherwise} \\
    \end{cases}
    $$
    
    易证 $g(p) = f(p)$ 且 $g$ 为积性函数．
    
    下面考虑求 $G(n)$．
    
    $$
    \begin{aligned}
    G(n)
    &= \sum_{i=1}^{n}[i \bmod 2 = 1] \varphi(i) + 3 \sum_{i=1}^{n}[i \bmod 2 = 0] \varphi(i)\\
    &= \sum_{i=1}^{n} \varphi(i) + 2\sum_{i=1}^{n} [i \bmod 2 = 0]\varphi(i) \\
    &= \sum_{i=1}^{n} \varphi(i) + 2\sum_{i=1}^{\lfloor \frac{n}{2} \rfloor} \varphi(2i)
    \end{aligned}
    $$
    
    记 $S_1(n) = \sum_{i=1}^{n} \varphi(i)$，$S_2(n) = \sum_{i=1}^{n} \varphi(2i)$，则 $G(n) = S_1(n) + 2S_2\left(\left\lfloor \dfrac{n}{2} \right\rfloor\right)$．
    
    当 $2 \mid n$ 时，有
    
    $$
    \begin{aligned}
    S_2(n)
    &= \sum_{i=1}^{n} \varphi(2i) \\
    &= \sum_{i=1}^{\frac{n}{2}} (\varphi(2(2i-1)) + \varphi(2(2i))) \\
    &= \sum_{i=1}^{\frac{n}{2}} (\varphi(2i-1) + 2\varphi(2i)) \\
    &= \sum_{i=1}^{\frac{n}{2}} (\varphi(2i-1) + \varphi(2i)) + \sum_{i=1}^{\frac{n}{2}} \varphi(2i) \\
    &= \sum_{i=1}^{n} \varphi(i) + S_2\left(\frac{n}{2}\right)\\
    &= S_1(n) + S_2\left(\left\lfloor \frac{n}{2} \right\rfloor\right)\\
    \end{aligned}
    $$
    
    当 $2 \nmid n$ 时，有
    
    $$
    \begin{aligned}
    S_2(n)
    &= S_2(n-1) + \varphi(2n) \\
    &= S_2(n-1) + \varphi(n) \\
    &= \sum_{i=1}^{n-1} \varphi(i) + S_2\left(\frac{n-1}{2}\right) + \varphi(n)\\
    &= S_1(n) + S_2\left(\left\lfloor \frac{n}{2} \right\rfloor\right)\\
    \end{aligned}
    $$
    
    综上，有 $S_2(n) = S_1(n) + S_2\left(\left\lfloor \dfrac{n}{2} \right\rfloor\right)$．
    
    $S_1$ 可以用杜教筛求，$S_2$ 直接按照公式推，这样 $G$ 也可以求出来了．

??? note "参考代码"
    ```cpp
    --8<-- "docs/math/code/powerful-number/powerful-number_2.cpp"
    ```

## 习题

PN 筛：

-   [PE708 Twos are all you need](https://projecteuler.net/problem=708)
-   [PE639 Summing a multiplicative function](https://projecteuler.net/problem=639)
-   [PE484 Arithmetic Derivative](https://projecteuler.net/problem=484)

## 参考资料与注释

-   [朱震霆．一些特殊的数论函数求和问题．国家集训队 2018 年论文集．](https://github.com/OI-wiki/libs/blob/master/%E9%9B%86%E8%AE%AD%E9%98%9F%E5%8E%86%E5%B9%B4%E8%AE%BA%E6%96%87/%E5%9B%BD%E5%AE%B6%E9%9B%86%E8%AE%AD%E9%98%9F2018%E8%AE%BA%E6%96%87%E9%9B%86.pdf)
-   [任之洲．积性函数求和的几种方法．国家集训队 2016 年论文集．](https://github.com/OI-wiki/libs/blob/master/%E9%9B%86%E8%AE%AD%E9%98%9F%E5%8E%86%E5%B9%B4%E8%AE%BA%E6%96%87/%E5%9B%BD%E5%AE%B6%E9%9B%86%E8%AE%AD%E9%98%9F2016%E8%AE%BA%E6%96%87%E9%9B%86.pdf)
-   [The prefix-sum of multiplicative function: the black algorithm - baihacker](https://baihacker.github.io/main/2020/The_prefix-sum_of_multiplicative_function_the_black_algorithm.html)
-   [Summing Multiplicative Functions (Pt. 1.5) - griff's math blog!](https://gbroxey.github.io/blog/2025/04/07/mult-sum-1-5.html)
-   [Min-25 筛学习笔记 by DaiRuiChen007](https://www.cnblogs.com/DaiRuiChen007/p/17492875.html)
-   [洲阁筛学习笔记 by myee](https://www.cnblogs.com/myee/p/zhouge-sieve.html)
-   [积性函数线性筛/杜教筛/洲阁筛学习笔记 | Bill Yang's Blog](https://blog.bill.moe/multiplicative-function-sieves-notes)
-   [破壁人五号 - Powerful number 筛略解](https://www.cnblogs.com/wallbreaker5th/p/13901487.html)
-   [command\_block - 杜教筛（+ 贝尔级数 + powerful number）](https://www.luogu.com.cn/blog/command-block/du-jiao-shai)

[^black]: 这个名字源于 baihacker 的博文．

[^ivic-pomerance]: 该集合见于 [OEIS A070003](https://oeis.org/A070003)．对该数量的估计引自 Ivić, Aleksandar. "On sums involving reciprocals of the largest prime factor of an integer II." Acta Arithmetica 71.3 (1995): 229-251. 一文，该文引用了 Ivić, A., and C. Pomerance. "Estimates for certain sums involving the largest prime factor of an integer." Coll. Math. Soc. J. Bolyai 34, North-Holland, 1984: 769-789. 中的结果．

[^log-p-n]: 这一点可以通过积分估计直接说明．此处再提供一种更符合直觉的解释．取定常数 $c\in(0,1/4)$，将求和式在 $n^c$ 处分成两部分：小于 $n^c$ 的部分，$\log_p n$ 可以直接放缩到 $\log_2 n$，而这一部分总共不超过 $\pi(n^c)$ 项，每项至多 $O(\sqrt{n})$，故整体是 $O(n^{c+1/2}\log n)=o(n^{3/4})$，可以忽略；大于 $n^c$ 的部分，$\log_p n<1/c$ 只是一个常数因子．因此，增加 $\log_p n$ 项并不会影响整体复杂度．

[^zhouge-variant]: 此处描述的是任之洲论文中 6.5.4 小节的「另一种实现」．任之洲本人提出的实现方法是自小到大遍历素数 $p$ 来进行状态转移．两者并无本质区别．
