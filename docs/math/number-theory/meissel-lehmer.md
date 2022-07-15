author: Peanut-Tang, Early0v0, Vxlimo, GHLinZhengyu, 1196131597

「Meissel-Lehmer 算法」是一种能在亚线性时间复杂度内求出 $1\sim n$ 内质数个数的一种算法。

## 记号规定

$\left[x\right]$ 表示对 $x$ 下取整得到的结果。  
$p_k$ 表示第 $k$ 个质数，$p_1=2$。  
$\pi\left(x\right)$ 表示 $1\sim x$ 范围内素数的个数。  
$\mu\left(x\right)$ 表示莫比乌斯函数。  
对于集合 $S$，$\# S$ 表示集合 $S$ 的大小。  
$\delta\left(x\right)$ 表示 $x$ 最小的质因子。  
$P^+\left(n\right)$ 表示 $x$ 最大的质因子。

## Meissel-Lehmer 算法求 π(x)

定义 $\phi\left(x,a\right)$ 为所有小于 $x$ 的正整数中满足其所有质因子都大于 $p_a$ 的数的个数，即：

$$
\phi\left(x,a\right)=\#\big\{n\le x\mid n\bmod p=0\Rightarrow p>p_a\big\}\tag{1}
$$

再定义 $P_k\left(x,a\right)$ 表示为所有小于 $x$ 的正整数中满足可重质因子恰好有 $k$ 个且所有质因子都大于 $p_a$ 的数的个数，即：

$$
P_k\left(x,a\right)=\#\big\{n\le x\mid n=q_1q_2\cdots q_k\Rightarrow\forall i,q_i>p_a\big\}\tag{2}
$$

特殊的，我们定义：$P_0\left(x,a\right)=1$，如此便有：

$$
\phi\left(x,a\right)=P_0\left(x,a\right)+P_1\left(x,a\right)+\cdots+P_k\left(x,a\right)+\cdots
$$

这个无限和式实际上是可以表示为有限和式的，因为在 $p_a^k>x$ 时，有 $P_k\left(x,a\right)=0$。

设 $y$ 为满足 $x^{1/3}\le y\le x^{1/2}$ 的整数，再记 $a=\pi\left(y\right)$。

在 $k\ge 3$ 时，有 $P_1\left(x,a\right)=\pi\left(x\right)-a$ 与 $P_k\left(x,a\right)=0$，由此我们可以推出：

$$
\pi\left(x\right)=\phi\left(x,a\right)+a-1-P_2\left(x,a\right)\tag{3}
$$

这样，计算 $\pi\left(x\right)$ 便可以转化为计算 $\phi\left(x,a\right)$ 与 $P_2\left(x,a\right)$。

## 计算 P₂(x,a)

由等式 $\left(2\right)$ 我们可以得出 $P_2\left(x,a\right)$ 等于满足 $y<p\le q$ 且 $pq\le x$ 的质数对 $\left(p,q\right)$ 的个数。

首先我们注意到 $p\in \left[y+1,\sqrt{x}\right]$。此外，对于每个 $p$，我们都有 $q\in\left[p,x/p\right]$。因此：

$$
P_2\left(x,a\right)=\sum\limits_{y<p\le \sqrt{x}}{\left(\pi\left(\dfrac{x}{p}\right)-\pi\left(p\right)+1\right)}\tag{4}
$$

当 $p\in \left[y+1,\sqrt{x}\right]$ 时，我们有 $\dfrac{x}{p}\in \left[1,\dfrac{x}{y}\right]$。因此，我们可以筛区间 $\left[1,\dfrac{x}{y}\right]$，然后对于所有的的质数 $p\in \left[y+1,\sqrt{x}\right]$ 计算 $\pi\left(\dfrac{x}{p}\right)-\pi\left(p\right)+1$。为了减少上述算法的空间复杂度，我们可以考虑分块，块长为 $L$。若块长 $L=y$，则我们可以在 $O\left(\dfrac{x}{y}\log{\log{x}}\right)$ 的时间复杂度，$O\left(y\right)$ 的空间复杂度内计算 $P_2\left(x,a\right)$。

## 计算 ϕ(x,a)

对于 $b\le a$，考虑所有不超过 $x$ 的正整数，满足它的所有质因子都大于 $p_{b-1}$。这些数可以被分为两类：

1. 可以被 $p_b$ 整除的；
2. 不可以被 $p_b$ 整除的。

属于第 $1$ 类的数有 $\phi\left(\dfrac{x}{p_b},b-1\right)$ 个，属于第二类的数有 $\phi\left(x,b\right)$ 个。

因此我们得出结论：

> **定理 $5.1$：** 函数 $\phi$ 满足下列性质
>
> $$
> \phi\left(u,0\right)=\left[u\right]\tag{5}
> $$
>
> $$
> \phi\left(x,b\right)=\phi\left(x,b-1\right)-\phi\left(\dfrac{x}{p_b},b-1\right)\tag{6}
> $$

计算 $\phi\left(x,a\right)$ 的简单方法可以从这个定理推导出来：我们重复使用等式 $\left(7\right)$，知道最后得到 $\phi\left(u,0\right)$。这个过程可以看作从根节点 $\phi\left(x,a\right)$ 开始创建有根二叉树，图 $1$ 画出了这一过程。通过这种方法，我们得到如下公式：

$$
\phi\left(x,a\right)=\sum\limits_{1\le n\le x\\\\ P^+\left(n\right)\le y}{\mu\left(n\right)\left[x/n\right]}
$$

$$
\begin{matrix}&&\phi\left(x,a\right)&&\\
&\swarrow&&\searrow&\\
&\phi\left(x,a-1\right)&&-\phi\left(\frac{x}{p_a},a-1\right)&\\
\swarrow&\downarrow&&\downarrow&\searrow\\
\phi\left(x,a-2\right)&\phi\left(\frac{x}{p_{a-1}},a-2\right)&&-\phi\left(\frac{x}{p_a},a-2\right)&\phi\left(\frac{x}{p_ap_{a-1}},a-2\right)\end{matrix}\\
\vdots\\
$$

上图表示计算 $\phi\left(x,a\right)$ 过程的二叉树：叶子节点权值之和就是 $\phi\left(x,a\right)$。

但是，这样需要计算太多东西。因为 $y\geq x^{1/3}$，仅仅计算为 $3$ 个 不超过 $y$ 质数的乘积的数，如果按照这个方法计算，会有至少 $\dfrac{x}{\log^3 x}$ 个项，没有办法我们对复杂度的需求。

为了限制这个二叉树的“生长”，我们要改变原来的终止条件。这是原来的终止条件。

> **终止条件 $1$：** 如果 $b=0$，则不要再对节点 $\mu\left(n\right)\phi\left(\dfrac xn,b\right)$ 调用等式 $\left(6\right)$。

我们把它改成更强的终止条件：

> **终止条件 $2$：** 如果满足下面 $2$ 个条件中的一个，不要再对节点 $\mu\left(n\right)\phi\left(\dfrac xn,b\right)$ 调用等式 $\left(6\right)$:
>
> 1. $b=0$ 且 $n\le y$；
> 2. $n>y$。

我们根据 **终止条件 $2$** 将原二叉树上的叶子分成两种：

1. 如果叶子节点 $\mu\left(n\right)\phi\left(\dfrac xn,b\right)$ 满足 $n\le y$，则称这种叶子节点为 **普通叶子**；
2. 如果叶子节点 $\mu\left(n\right)\phi\left(\dfrac xn,b\right)$ 满足 $n>y$ 且 $n=mp_b\left(m\le y\right)$，则称这种节点为 **特殊叶子**。

由此我们得出：

> **定理 $5.2$：** 我们有：
>
> $$
> \phi\left(x,a\right)=S_0+S\tag{7}
> $$
>
> 其中 $S_0$ 表示 **普通叶子** 的贡献：
>
> $$
> S_0=\sum\limits_{n\le y}{\mu\left(n\right)\left[\dfrac xn\right]}\tag{8}
> $$
>
> $S$ 表示 **特殊叶子** 的贡献：
>
> $$
> S=\sum\limits_{n/\delta\left(n\right)\le y\le n}{\mu\left(n\right)\phi\left(\dfrac{x}{n},\pi\left(\delta\left(n\right)\right)-1 \right)}\tag{9}
> $$

计算 $S_0$ 显然是可以在 $O\left(y\log{\log x}\right)$ 的时间复杂度内解决的，现在我们要考虑如何计算 $S$。

## 计算 S

我们有：

$$
S=-\sum\limits_{p\le y}{\ \sum\limits_{\delta\left(m\right)>p\\\\ m\le y<mp}{\mu\left(m\right)\phi\left(\dfrac{x}{mp},\pi\left(p\right)-1\right)}}\tag{10}
$$

我们将这个等式改写为：

$$
S=S_1+S_2+S_3
$$

其中：

$$
S_1=-\sum\limits_{x^{1/3}<p\le y}{\ \sum\limits_{\delta\left(m\right)>p\\m\le y<mp}{\mu\left(m\right)\phi\left(\dfrac{x}{mp},\pi\left(p\right)-1\right)}}
$$

$$
S_2=-\sum\limits_{x^{1/4}<p\le x^{1/3}}{\ \sum\limits_{\delta\left(m\right)>p\\\\ m\le y<mp}{\mu\left(m\right)\phi\left(\dfrac{x}{mp},\pi\left(p\right)-1\right)}}
$$

$$
S_3=-\sum\limits_{p\le x^{1/4}}{\ \sum\limits_{\delta\left(m\right)>p\\\\ m\le y<mp}{\mu\left(m\right)\phi\left(\dfrac{x}{mp},\pi\left(p\right)-1\right)}}
$$

注意到计算 $S_1,S_2$ 的和式中涉及到的 $m$ 都是质数，证明如下：

> 如果不是这样，因为有 $\delta\left(m\right)>p>x^{1/4}$，所以有 $m>p^2>\sqrt{x}$，这与 $m\le y$ 矛盾，所以原命题成立。

更多的，当 $mp>x^{1/2}\ge y$ 时，有 $y\le mp$。因此我们有：

$$
S_1=\sum\limits_{x^{1/3}<p\le y}{\ \sum\limits_{p<q\le y}{\phi\left(\dfrac{x}{pq},\pi\left(p\right)-1\right)}}
$$

$$
S_2=\sum\limits_{x^{1/4}<p\le x^{1/3}}{\ \sum\limits_{p<q\le y}{\phi\left(\dfrac{x}{pq},\pi\left(p\right)-1\right)}}
$$

### 计算 S₁

因为：

$$
\dfrac{x}{pq}<x^{1/3}<p
$$

所以：

$$
\phi\left(\dfrac{x}{pq},\pi\left(p\right)-1\right)=1
$$

所以计算 $S_1$ 的和式中的项都是 $1$。所以我们实际上要计算质数对 $\left(p,q\right)$ 的个数，满足：$x^{1/3}<p<q\le y$。

因此：

$$
S_1=\dfrac{\left(\pi\left(y\right)-\pi\left(x^{1/3}\right)\right)\left(\pi\left(y\right)-\pi\left(x^{1/3}\right)-1\right)}{2}
$$

有了这个等式我们便可以在 $O\left(1\right)$ 的时间内计算 $S_1$。

### 计算 S₂

我们有：

$$
S_2=\sum\limits_{x^{1/4}<p\le x^{1/3}}{\ \sum\limits_{p<q\le y}{\phi\left(\dfrac{x}{pq},\pi\left(p\right)-1\right)}}
$$

我们将 $S_2$ 分成 $q>\dfrac x{p^2}$ 与 $q\le \dfrac x{p^2}$ 两部分：

$$
S_2=U+V
$$

其中：

$$
U=\sum\limits_{x^{1/4}<p\le x^{1/3}}{\ \sum\limits_{p<q<y\\q>x/p^2}{\phi\left(\dfrac{x}{pq},\pi\left(p\right)-1 \right)}}
$$

$$
V=\sum\limits_{x^{1/4}<p\le x^{1/3}}{\ \sum\limits_{p<q<y\\q\le x/p^2}{\phi\left(\dfrac{x}{pq},\pi\left(p\right)-1 \right)}}
$$

### 计算 U

由 $q>\dfrac x{p^2}$ 可得 $p^2>\dfrac xq\le \dfrac xy,p>\sqrt{\dfrac xy}$，因此：

$$
U=\sum\limits_{\sqrt{x/y}<p\le x^{1/3}}{\ \sum\limits_{p<q\le y\\q>x/p^2}{\phi\left(\dfrac{x}{pq},\pi\left(p\right)-1 \right)}}
$$

因此：

$$
U=\sum\limits_{\sqrt{x/y}<p\le x^{1/3}}{\#\left\{q\mid \dfrac x{p^2}<q\le y \right\}}
$$

因此：

$$
U=\sum\limits_{\sqrt{x/y}<p\le x^{1/3}}{\left(\pi\left(y\right)-\pi\left(\dfrac{x}{p^2} \right) \right)}
$$

因为有 $\dfrac x{p^2}<y$，所以我们可以预处理出所有的 $\pi\left(t\right)\left(t\le y\right)$，这样我们就可以在 $O\left(y\right)$ 的时间复杂度内计算出 $U$。

### 计算 V

对于计算 $V$ 的和式中的每一项，我们都有 $p\le \dfrac{x}{pq}<x^{1/2}<p^2$。因此：

$$
\phi\left(\dfrac{x}{pq},\pi\left(p\right)-1 \right)=1+\pi\left(\dfrac{x}{pq} \right)-\left(\pi\left(p\right)-1\right)=2-\pi\left(p\right)+\pi\left(\dfrac{x}{pq} \right)
$$

所以 $V$ 可以被表示为：

$$
V=V_1+V_2
$$

其中：

$$
V_1=\sum\limits_{x^{1/4}<p\le x^{1/3}}{\ \sum\limits_{p<q\le \min\left(x/p^2,y\right)}{\left(2-\pi\left(p\right)\right)}}
$$

$$
V_2=\sum\limits_{x^{1/4}<p\le x^{1/3}}{\ \sum\limits_{p<q\le \min\left(x/p^2,y\right)}{\pi\left(\dfrac{x}{pq} \right)}}
$$

预处理出 $\pi\left(t\right)\left(t\le y\right)$ 我们就可以在 $O\left(x^{1/3}\right)$ 的时间复杂度内计算出 $V_1$。

考虑我们如何加速计算 $V_2$ 的过程。我们可以把 $q$ 的贡献拆分成若干个 $\pi\left(\dfrac{x}{pq} \right)$ 为定值的区间上，这样我就只需要计算出每一个区间的长度和从一个区间到下一个区间的 $\pi\left(\dfrac{x}{pq} \right)$ 的改变量。

更准确的说，我们首先将 $V_2$ 分成两个部分，将 $q\le \min\left(\dfrac x{p^2},y\right)$ 这个复杂的条件简化：

$$
V_2=\sum\limits_{x^{1/4}<p\le \sqrt{x/y}}{\ \sum\limits_{p<q\le y}{\pi\left(\dfrac{x}{pq} \right)}}+\sum\limits_{\sqrt{x/y}<p\le x^{1/3}}{\ \sum\limits_{p<q\le x/p^2}{\pi\left(\dfrac{x}{pq} \right)}}
$$

接着我们把这个式子改写为：

$$
V_2=W_1+W_2+W_3+W_4+W_5
$$

其中：

$$
W_1=\sum\limits_{x^{1/4}<p\le x/y^2}{\ \sum\limits_{p<q\le y}{\pi\left(\dfrac{x}{pq} \right)}}
$$

$$
W_2=\sum\limits_{x/y^2<p\le \sqrt{x/y}}{\ \sum\limits_{p<q\le \sqrt{x/p}}{\pi\left(\dfrac{x}{pq} \right)}}
$$

$$
W_3=\sum\limits_{x/y^2<p\le \sqrt{x/y}}{\ \sum\limits_{\sqrt{x/p}<q\le y}{\pi\left(\dfrac{x}{pq} \right)}}
$$

$$
W_4=\sum\limits_{\sqrt{x/y}<p\le x^{1/3}}{\ \sum\limits_{p<q\le \sqrt{x/p}}{\pi\left(\dfrac{x}{pq} \right)}}
$$

$$
W_5=\sum\limits_{\sqrt{x/y}<p\le x^{1/3}}{\ \sum\limits_{\sqrt{x/p}<q\le x/p^2}{\pi\left(\dfrac{x}{pq} \right)}}
$$

#### 计算 W₁ 与 W₂

计算这两个值需要计算满足 $y<\dfrac{x}{pq}<x^{1/2}$ 的 $\pi\left(\dfrac{x}{pq} \right)$ 的值。可以在区间 $[1,\sqrt x]$ 分块筛出。在每个块中我们对于所有满足条件的 $(p,q)$ 都累加 $\pi\left(\dfrac x{pq}\right)$。

#### 计算 W₃

对于每个 $p$，我们把 $q$ 分成若干个区间，每个区间都满足它们的 $\pi\left(\dfrac x{pq}\right)$ 是定值，每个区间我们都可以 $O(1)$ 计算它的贡献。当我们获得一个新的 $q$ 时，我们用 $\pi(t)$（$t\leq y$）的值表计算 $\pi\left(\dfrac x{pq}\right)$。$y$ 以内的质数表可以给出使得 $\pi(t)<\pi(t+1)=\pi\left(\dfrac x{pq}\right)$ 成立的 $t$。以此类推使得 $\pi\left(\dfrac x{pq}\right)$ 变化的下一个 $q$ 的值。

#### 计算 W₄

相比于 $W_3$，$W_4$ 中 $q$ 更小，所以 $\pi\left(\dfrac x{pq}\right)$ 改变得更快。这时候再按照计算 $W_3$ 的方法计算 $W_4$ 就显得没有任何优势。于是我们直接暴力枚举数对 $(p,q)$ 来计算 $W_4$。

#### 计算 W₅

我们像计算 $W_3$ 那样来计算 $W_5$。

## 计算 S₃

我们使用所有小于 $x^{1/4}$ 的素数一次筛出区间 $\left[1,\dfrac xy\right]$。当我们的筛法进行到 $p_k$ 的时候，我们算出了所有 $m$ 满足没有平方因子并且 $\delta(m)>p_k$ 的 $-\mu(m)\phi\left(\dfrac{x}{mp_k},k-1 \right)$ 值。这个筛法是分块进行的，我们在筛选间隔中维护一个二叉树，以实时维护所有素数筛选到给定素数后的中间结果。这样我们就可以只用 $O(\log x)$ 的时间复杂度求出在筛法进行到某一个值的时候没有被筛到的数的数量。

## 算法的时空复杂度

时空复杂度被如下 $3$ 个过程影响：

1. 计算 $P_2\left(x,a\right)$；
2. 计算 $W_1,W_2,W_3,W_4,W_5$；
3. 计算 $S_3$。

### 计算 P₂(x,y) 的复杂度

我们已经知道了这个过程的时间复杂度为 $O\left(\dfrac{x}{y}\log{\log x}\right)$，空间复杂度为 $O\left(y\right)$。

### 计算 W₁,W₂,W₃,W₄,W₅ 的复杂度

计算 $W_1,W_2$ 所进行的块长度为 $y$ 的筛的时间按复杂度为 $O\left(\sqrt{x}\log{\log x}\right)$，空间复杂度为 $O\left(y\right)$。

计算 $W_1$ 所需的时间复杂度为：

$$
\pi\left(\dfrac{x}{y^2} \right)\pi\left(y\right)=O\left(\dfrac{x}{y\log^2 x} \right)
$$

计算 $W_2$ 的时间复杂度为：

$$
O\left(\sum\limits_{x/y^2<p\le \sqrt{x/y}}{\pi\left(\sqrt{\dfrac xp}\right)} \right)=O\left(\dfrac{x^{3/4}}{y^{1/4}\log^2 x} \right)
$$

因此，计算 $W_3$ 的时间复杂度为：

$$
O\left(\sum\limits_{x/y^2<p\le \sqrt{x/y}}{\pi\left(\sqrt{\dfrac xp}\right)} \right)=O\left(\dfrac{x^{3/4}}{y^{1/4}\log^2 x} \right)
$$

计算 $W_4$ 的时间复杂度为：

$$
O\left(\sum\limits_{\sqrt{x/y}<p\le x^{1/3}}{\pi\left(\sqrt{\dfrac xp}\right)} \right)=O\left(\dfrac{x^{2/3}}{\log^2 x} \right)
$$

计算 $W_5$ 的时间复杂度为：

$$
O\left(\sum\limits_{\sqrt{x/y}<p\le x^{1/3}}{\pi\left(\sqrt{\dfrac xp}\right)} \right)=O\left(\dfrac{x^{2/3}}{\log^2 x} \right)
$$

### 计算 S₃ 的复杂度

对于预处理：由于要快速查询 $\phi(u,b)$ 的值，我们没办法用普通的筛法 $O(1)$ 求出，而是要维护一个数据结构使得每次查询的时间复杂度是 $O(\log x)$，因此时间复杂度为 $O\left(\dfrac{x}{y}\log x\log\log x\right)$。

对于求和：对于计算 $S_3$ 和式中的每一项，我们查询上述数据结构，一共 $O\left(\log x\right)$ 次查询。我们还需要计算和式的项数，即二叉树中叶子的个数。所有叶子的形式均为 $\pm\phi\left(\dfrac{x}{mp_b},b-1\right)$，其中 $m\le y,b<\pi(x^{1/4})$。因此，叶子的数目是 $O\left(y\pi\left(x^{1/4}\right)\right)$ 级别的。所以计算 $S_3$ 的总时间复杂度为：

$$
O\left(\dfrac{x}{y}\log x\log\log x+yx^{1/4}\right)
$$

### 总复杂度

这个算法的空间复杂度为 $O\left(y\right)$，时间复杂度为：

$$
O\left(\dfrac{x}{y}\log{\log x}+\dfrac{x}{y}\log x\log{\log x}+x^{1/4}y+\dfrac{x^{2/3}}{\log^2{x}} \right)
$$

我们取 $y=x^{1/3}\log^3{x}\log{\log x}$，就有最优时间复杂度为 $O\left(\dfrac{x^{2/3}}{\log^2 x}\right)$，空间复杂度为 $O\left(x^{1/3}\log^3{x}\log{\log x}\right)$。

## 一些改进

我们在这里给出改进方法，以减少算法的常数，提高它的实际效率。

-   在 **终止条件 $2$** 中，我们可以用一个 $z$ 来代替 $y$，其中 $z$ 满足 $z>y$。我们可以证明这样子计算 $S_3$ 的时间复杂度可以优化到：

    $$
    O\left(\dfrac{x}{z}\log x\log{\log x}+\dfrac{yx^{1/4}}{\log x}+z^{3/2} \right)
    $$

    这也为通过改变 $z$ 的值来检查计算提供了一个很好的方法。

- 为了清楚起见，我们在阐述算法的时候选择在 $x^{1/4}$ 处拆分来计算总和 $S$，但实际上我们只需要有 $p\le \dfrac{x}{pq}<p^2$ 就可以计算。我们可以利用这一点，渐近复杂性保持不变。

- 用前几个素数 $2,3,5$ 预处理计算可以节省更多的时间。

## 参考资料与拓展阅读

本文翻译自：[Computing $\pi(x)$: the Meissel, Lehmer, Lagarias, Miller, Odlyzko method](https://dl.acm.org/doi/abs/10.1090/s0025-5718-96-00674-6)
