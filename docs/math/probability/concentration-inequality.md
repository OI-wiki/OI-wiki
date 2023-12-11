算法竞赛中有时会用到 [随机化算法](../../misc/rand-technique.md)，这些算法的正确性与时空复杂度通常依赖于「某些随机事件发生的概率很小」这一前提。例如，快速排序的复杂度依赖于「所选的 `pivot` 元素几乎是最小或最大元素」这一事件较少发生。

本文将简要介绍一些用于分析随机化算法的工具并给出几个简单应用的例子。

## Union Bound

记 $A_1, \cdots, A_m$ 为随机事件，则

$$
P\left\{ \bigcup_{i=1}^m A_i \right\} \leq \sum_{i=1}^m P\{A_i\}
$$

即：一组事件中至少一个发生的概率，不超过每一个的发生概率之和。

实际上，这一结论还可以稍作加强：

-   一组事件中至少一者发生的概率，**不小于** 每一个的发生概率之和，减掉每两个同时发生的概率之和。
-   一组事件中至少一者发生的概率，**不超过** 每一个的发生概率之和，减掉每两个同时发生的概率之和，加上每三个同时发生的概率之和。
-   ……

随着层数越来越多，交替出现的上界和下界也越来越紧。这一系列结论形式上类似容斥原理，证明过程也和容斥类似，这里略去。

## Markov 不等式

设 $X$ 是一个取值非负的随机变量，则对任意正实数 $a$ 有

$$
P\{ X \geq a \} \leq \frac{EX}{a}
$$

事实上，由于 Markov 不等式本身并没有用到随机变量除期望外的与分布有关的任何信息，因此直接应用这个不等式得到的约束通常很松。

### 证明

记 $I$ 为事件 $X \geq a$ 的示性函数，则有

$$
I \leq \frac{X}{a}
$$

进而

$$
P\{ X \geq a \} = EI \leq E \left[ \frac{X}{a} \right] = \frac{EX}{a}
$$

## Chebyshev 不等式

设 $X$ 是一随机变量，则对任意的 $a > 0$ 都有

$$
P \{ |X - EX| \geq a \} \leq \frac{DX}{a^2}
$$

特别地，当 $a$ 取 $k\sigma$ 时有

$$
P \{ |X - EX| \geq k\sigma \} \leq \frac{1}{k^2}
$$

其中 $\sigma$ 是 $X$ 的标准差。

### 证明

由已知，有

$$
P \{ |X - EX| \geq a \} = P \{ (X - EX)^2 \geq a^2 \}
$$

注意到 $(X - EX)^2$ 非负，故由 Markov 不等式可知

$$
P \{ (X - EX)^2 \geq a^2 \} \leq \frac{E(X - EX)^2}{a^2} = \frac{DX}{a^2}
$$

## Chernoff 不等式

一般的 Chernoff 不等式可以从直接对随机变量 $\mathrm{e}^{tX}$ 应用 Markov 不等式得出：

设 $X$ 是一随机变量，则对任意的 $t > 0$ 都有

$$
P\{ X \geq a \} = P\{ \mathrm{e}^{tX} > \mathrm{e}^{ta} \} \leq \frac{E \mathrm{e}^{tX}}{\mathrm{e}^{ta}}
$$

类似地，当 $t < 0$ 时有

$$
P\{ X \leq a \} = P\{ \mathrm{e}^{tX} > \mathrm{e}^{ta} \} \leq \frac{E \mathrm{e}^{tX}}{\mathrm{e}^{ta}}
$$

### Poisson 试验之和的 Chernoff 不等式

算法竞赛中涉及的随机变量通常没有那么「一般」，我们可以用概率论中的 Poisson 试验对其进行描述。

所谓 Poisson 试验，是指在只有两种可能结果的随机试验。

一次的 Poisson 试验的结果可以用一个取值为 $0$ 或 $1$ 的随机变量 $X$ 进行刻画，其概率分布为

$$
P\{ X = i \} = \begin{cases}
    p_i, & i = 1 \\
    1 - p_1, & i = 0
\end{cases}
$$

对于 Poisson 试验，我们有如下结论：

对于 $n$ 个独立的 Poisson 试验 $X_1, X_2, \cdots, X_n$，记 $X = \sum_{i=1}^{n} X_i$ 以及 $\mu = EX$，则对任意 $0 < \epsilon < 1$ 有

$$
P\left\{ |X - \mu| \geq \epsilon \mu \right\} \leq 2 \exp\left( - \frac{1}{3} \mu \epsilon^2 \right)
$$

## Hoeffding 不等式

若 $X_1, \cdots, X_n$ 为互相独立的实随机变量且 $X_i\in [a_i,b_i]$，记随机变量 $X=\sum\limits_{i=1}^n X_i$，则

$$
P\{ |X - EX| \geq \epsilon \} \leq 2\exp \left( \frac {-2\epsilon^2}{\sum\limits_{i=1}^n (b_i-a_i)^2} \right)
$$

Chernoff 不等式和 Hoeffding 不等式都限制了随机变量偏离其期望值的程度。这两个不等式的证明过程较为冗长，有兴趣的同学可以查阅 Probability and Computing 一书中的相关章节。

从经验上讲，如果 $EX$ 不太接近 $a_1+\cdots+a_n$，则该不等式给出的界往往相对比较紧；如果非常接近的话（例如在 [UOJ #72 全新做法](https://matthew99.blog.uoj.ac/blog/5511) 中），给出的界则往往很松，此时更好的选择是使用 Chernoff 不等式。

## 应用举例

### 例：随机撒点估算圆周率

考虑下列估计圆周率 $\pi$ 的精确值的算法：

在正方形区域 $[-1, 1]^2$ 内随机生成 $n$ 个点，记其中落入单位圆盘 $x^2 + y^2 \leq 1$ 的点数为 $m$，则可以取 $\dfrac{4m}{n}$ 为 $\pi$ 的近似值。

问题：若要保证上述算法以至少 $(1 - \delta)$ 的概率返回相对误差不超过 $\epsilon$ 的结果，$n$ 应该如何取定？

??? note "解答"
    记 $X_i$ 表示事件「随机生成的第 $i$ 个点在单位圆内」，则圆内总点数 $X = \sum_{i=1}^{n} X_i$。我们需要找到一个合适的 $n$ 使得
    
    $$
    P\left\{ \left| \frac{4X}{n} - \pi \right| \geq \epsilon \pi \right\} \leq \delta
    $$
    
    上式等价于
    
    $$
    P\left\{ \left| X - \frac{\pi}{4}n \right| \geq \epsilon \cdot \frac{\pi}{4}n  \right\} \leq \delta
    $$
    
    根据 Chernoff 不等式，我们只需令
    
    $$
    2 \exp\left( - \frac{1}{3} \epsilon^2 \cdot \frac{\pi}{4}n \right) \leq \delta
    $$
    
    即可，由此可解得
    
    $$
    n \geq \frac{12}{\pi} \epsilon^{-2} \ln \frac{2}{\delta}
    $$
    
    即当 $n = \Omega(\epsilon^{-2} \ln \frac{1}{\delta})$ 时可以达到需要的准确率。

### 例：抽奖问题

一个箱子里有 $n$ 个球，其中恰有 $k$ 个球对应着大奖。你要进行若干次独立、等概率的随机抽取，每次抽完之后会把球放回箱子。请问抽多少次能保证以至少 $(1 - \epsilon)$ 的概率，满足 **每一个** 奖球都被抽到至少一次？

??? note "解答"
    假如只有一个奖球，则抽取 $M=n\log\epsilon^{-1}$ 次即可保证，因为 $M$ 次全不中的概率
    
    $$
    \Big(1-\dfrac 1n\Big)^{n\log\epsilon^{-1}}\leq e^{\log\epsilon}=\epsilon
    $$
    
    现在有 $k>1$ 个奖球，那么根据 Union Bound，我们只需保证每个奖球被漏掉的概率都不超过 $\dfrac \epsilon k$ 即可。于是答案是 $n \log \dfrac{k}{\epsilon}$。

### 例：随机选取一半元素

给出一个算法，从 $n$ 个元素中等概率随机选取一个大小为 $\dfrac{n}{2}$ 的子集，保证 $n$ 是偶数。你能使用的唯一的随机源是一枚均匀硬币，同时请你尽量减少抛硬币的次数（不要求最少）。

??? note "解法"
    首先可以想到这样的算法：
    
    -   通过抛 $n$ 次硬币，可以从所有子集中等概率随机选一个。
    -   不断重复这一过程，直到选出的子集大小恰好为 $\dfrac n2$。
        -   注意到大小为 $\dfrac n2$ 的子集至少占所有子集的 $\dfrac 1n$，因此重复次数的期望值 $\leq n$。
    
    这一算法期望需要抛 $n^2$ 次硬币。
    
    另一个算法：
    
    -   我们可以通过抛期望 $2\lceil\log_2 n\rceil$ 次硬币来实现随机 $n$ 选 1。
        -   具体方法：随机生成 $\lceil\log_2 n\rceil$ 位的二进制数，如果大于等于 $n$ 则重新随机，否则选择对应编号（编号从 0 开始）的元素并结束过程。
    -   然后我们从所有元素中选一个，再从剩下的元素中再选一个，以此类推，直到选出 $\dfrac n2$ 个元素为止。
    
    这一算法期望需要抛 $n\lceil\log_2 n\rceil$ 次硬币。
    
    将两个算法缝合起来：
    
    -   先用第一个算法随机得到一个子集。
    -   如果该子集大小不到 $\dfrac n2$，则利用第二个算法不断添加元素，直到将大小补到 $\dfrac n2$。
    -   如果该子集大小超过 $\dfrac n2$，则利用第二个算法不断删除元素，直到将大小削到 $\dfrac n2$。
    
    尝试分析第二、第三步所需的操作次数（即添加/删除元素的次数）：
    
    -   记 01 随机变量 $X_i$ 表示 $i$ 是否被选入初始的子集，令 $X:=X_1+\cdots+X_n$ 表示子集大小，则第二、第三步所需的操作次数等于 $\big|X-\mathrm{E}[X]\big|$。在 Hoeffding 不等式中取 $t=c\cdot\sqrt n$（其中 $c$ 为任意常数），得到 $\mathrm{Pr}\Big[\big|X-\mathrm{E}[X]\big|\geq t\Big]\leq 2\mathrm{e}^{-c^2}$。也就是说，我们可以通过允许 $\Theta(\sqrt n)$ 级别的偏移，来得到任意小的常数级别的失败概率。
    
    至此我们已经说明：该算法可以以很大概率保证抛硬币次数在 $n+\Theta(\sqrt n\log n)$ 以内。
    
    -   其中 $n$ 来自获得初始子集的抛硬币次数；$\Theta(\sqrt n\log n)$ 是 $\Theta(\sqrt n)$ 次添加/删除元素的总开销。
    
    ??? note "计算期望复杂度"
        我们再从另一个角度分析，尝试计算该算法的期望抛硬币次数。
        
        用 Hoeffding 不等式求第二、第三步中操作次数期望值的上界：
        
        $$
        E|X - EX| = \int_0^\infty P\{ |X - E[X]| \geq t \} \mathrm{d}t \leq 
        2 \int_0^\infty \exp \left(-\frac {t^2}{n}\right) \mathrm{d}t=\sqrt{\pi n}
        $$
        
        从而第二、第三步所需抛硬币次数的期望值是 $\sqrt{\pi n}\cdot2\lceil\log_2 n\rceil$。
        
        综上，该算法期望需要抛 $n+2\sqrt{\pi n}\lceil\log_2 n\rceil$ 次硬币。

### 练习：Balls and Bins

$n$ 个球独立随机地扔到 $n$ 个盒子里，试证明：球最多的盒子中的球数以 $1 - \dfrac{1}{n}$ 的概率不少于 $\Omega \left( \dfrac{\log n}{\log \log n} \right)$。
