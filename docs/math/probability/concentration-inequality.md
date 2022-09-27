算法竞赛中有时会用到 [随机化算法](../../misc/rand-technique.md)，本文将简要介绍一些用于分析随机化算法正确性的工具。

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

一般的 Chernoff 不等式可以从直接对随机变量 $e^{tX}$ 应用 Markov 不等式得出：

设 $X$ 是一随机变量，则对任意的 $t > 0$ 都有
$$
P\{ X \geq a \} = P\{ e^{tX} > e^{ta} \} \leq \frac{E e^{tX}}{e^{ta}}
$$
类似地，当 $t < 0$ 时有
$$
P\{ X \leq a \} = P\{ e^{tX} > e^{ta} \} \leq \frac{E e^{tX}}{e^{ta}}
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

这一不等式的证明过程较为冗长，有兴趣的同学可以查阅 Probability and Computing 一书中的相关章节。

## 应用举例

### 例：随机撒点估算圆周率

考虑下列估计圆周率 $\pi$ 的精确值的算法：

在正方形区域 $[-1, 1]^2$ 内随机生成 $n$ 个点，记其中落入单位圆盘 $x^2 + y^2 \leq 1$ 的点数为 $m$，则取 $\frac{4m}{n}$ 为 $\pi$ 的近似值。

问题：若要保证上述算法以至少 $(1 - \delta)$ 的概率返回相对误差不超过 $\epsilon$ 的结果，$n$ 应该如何取定？

??? note "解答"
    记 $X_i$ 表示事件“随机生成的第 $i$ 个点在单位圆内”，则圆内总点数 $X = \sum_{i=1}^{n} X_i$。我们需要找到一个合适的 $n$ 使得
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
