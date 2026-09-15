author: AlephInfinity1, aofall, Backl1ght, billchenchina, c-forrest, CCXXXI, chenyichen0420, CoelacanthusHex, CSPNOIP, cy1999, Early0v0, Enoch-xm, Enter-tainer, Great-designer, Haohu Shen, HeRaNO, iamtwz, Ir1d, kenlig, Konano, ksyx, LaDeXX, lrherqwq, Marcythm, MegaOwIer, Nanarikom, ouuan, Persdre, Revltalize, SamZhangQingChuan, scp020, shuzhouliu, StudyingFather, Tiphereth-A, Xeonacid, xyf007, ZnPdCo

## 引入

## 扩展 Eratosthenes 筛

### Black 算法

### 洲阁筛

### 原始 Min\_25 筛

## Powerful Number 筛

## 欧拉变换法

### zzt 求和法

### zky 求和法

## 洲阁筛

### 前置知识

-   [积性函数](./basic.md#积性函数)

### 定义

洲阁筛是一种能在亚线性时间复杂度内求出大多数积性函数前缀和的筛法．

下面将以求解 $\displaystyle\sum_{i=1}^nf(i)$ 为例，具体阐述洲阁筛的原理．

### 约定

-   $\mathbb P$ 表示质数集，$p_i$ 表示第 $i$ 个质数．
-   $m$ 表示 $\sqrt n$ 内的质数个数．

### 要求

当 $p\in\mathbb P,c\in\mathbb N$ 时，$f(p^c)$ 为一个关于 $p$ 的低阶多项式．

### 思想

-   对于任意 $[1,n]$ 内的整数，其至多只有一个 $>\sqrt n$ 的质因子．
-   利用 $\left\lfloor\dfrac ni\right\rfloor(i\in[1,n]\cap\mathbb N)$ 只有 $\sqrt n$ 级别个取值的性质来降低时间复杂度．

### 过程

将 $[1,n]$ 内的所有整数按是否有 $>\sqrt n$ 的质因子分为两类：

$$
\sum_{i=1}^nf(i)=\sum_{i=1}^n\left[\exists d\in(\sqrt n,n]\cap\mathbb P,d\mid i\right]f(i)+\sum_{i=1}^n\left[\forall d\in(\sqrt n,n]\cap\mathbb P,d\nmid i\right]f(i)
$$

对于前半部分，枚举最大因子，根据积性函数的性质可以转换：

$$
\sum_{i=1}^nf(i)=\sum_{i=1}^{\sqrt n}f(i)\cdot\left(\sum_{d=\lfloor\sqrt n\rfloor+1}^{\lfloor\frac ni\rfloor}[d\in\mathbb P]f(d)\right)+\sum_{i=1}^n\left[\forall d\in(\sqrt n,n]\cap\mathbb P,d\nmid i\right]f(i)
$$

前后部分可以分别计算．

#### Part 1

> 计算 $\displaystyle\sum_{i=1}^{\sqrt n}f(i)\cdot\left(\sum_{d=\lfloor\sqrt n\rfloor+1}^{\lfloor\frac ni\rfloor}[d\in\mathbb P]f(d)\right)$．

考虑枚举 $i$，然后 $O(1)$ 计算括号内部分．

记 $\displaystyle g(t,l)=\sum_{i=1}^l[\forall j\in[1,t],\gcd(i,p_j)=1]f(i)$，即 $[1,l]$ 中与 $p_1,p_2,\dots,p_t$ 均互质的数的 $f$ 值之和．

这样 Part 1 的计算就变成了 $\displaystyle\sum_{i=1}^{\sqrt n}f(i)\cdot g\left(m,\left\lfloor\frac ni\right\rfloor\right)$．

边界 $g(0,l)=\sum_{i=1}^lf(i)$，转移 $g(t,l)=g(t-1,l)-f(p_t)\cdot g\left(t-1,\left\lfloor\frac l{p_t}\right\rfloor\right)$．

$l$ 共有 $\sqrt n$ 级别种取值，对于每种取值则需要枚举其质因子，所以复杂度为 $\displaystyle O\left(\frac{\sqrt n}{\ln\sqrt n}\cdot\sqrt n\right)= O\left(\frac n{\log n}\right)$，需要优化．

注意到 $p_{t+1}^2>l$ 时符合条件的数只有 $1$，所以此时 $g(t,l)=f(1)=1$．

代入递推式可得：当 $p_t^2>l$ 时，$g(t,l)=g(t-1,l)-f(p_t)$．

所以一旦发现 $p_t^2>l$ 就停止转移，记此时的 $t$ 为 $t_l$，则 $\forall t>t_l,g(t,l)=g(t_l,l)-\sum_{i=t_l}^{t-1}f(p_i)$．

预处理质数的 $f$ 值前缀和即可快速求出 $g$，时间复杂度被优化至 $O\left(\dfrac{n^{\frac34}}{\log n}\right)$．

#### Part 2

> 计算 $\displaystyle\sum_{i=1}^n\left[\forall d\in(\sqrt n,n]\cap\mathbb P,d\nmid i\right]f(i)$．

记 $\displaystyle h(t,l)=\sum_{i=1}^l\left[i=\prod_{j=t}^mp_j^{c_j},c_j\in\mathbb N\right]f(i)$，即 $[1,l]$ 中所有只含 $p_t,p_{t+1},\dots,p_m$ 质因子的数的 $f$ 值之和．

Part 2 即为求 $h(0,n)$．

边界 $h(m+1,l)=1$，转移 $\displaystyle h(t,l)=h(t+1,l)+\sum_{c\in\mathbb N^*}f(p_t^c)\cdot h\left(t+1,\left\lfloor\frac l{p_t^c}\right\rfloor\right)$．

$l$ 共有 $\sqrt n$ 级别种取值，所以直接转移复杂度为 $\displaystyle O\left(\sqrt n\cdot\frac{\sqrt n}{\ln\sqrt n}\right)= O\left(\frac n{\log n}\right)$，需要优化．

与 $g$ 的优化方式类似，注意到 $p_t>l$ 时，能用 $p_t,p_{t+1},\dots,p_m$ 组成的数只有 $1$，此时的 $h(t,l)=f(1)=1$．

类似的，推出 $\forall p_t^2>l,h(t,l)=h(t+1,l)+f(p_t)$．

所以一旦发现 $p_t^2>l$ 就停止转移，记此时的 $t$ 为 $t_l$，之后用到 $h$ 时，把此时的 $h$ 值加上 $\displaystyle\sum_{i=p_{t_l}}^{\min(l,\sqrt n)}[i\in\mathbb P]f(i)$ 即可．

时间复杂度被优化至 $O\left(\dfrac{n^{\frac34}}{\log n}\right)$．

#### 求和

算出了 Part 1 和 Part 2 的答案，将其相加即为 $\displaystyle\sum_{i=1}^nf(i)$．

## Min\_25 筛

### 定义

从此种筛法的思想方法来说，其又被称为「Extended Eratosthenes Sieve」．

由于其由 [Min\_25](https://web.archive.org/web/20211104125457/http://min-25.hatenablog.com/) 发明并最早开始使用，故称「Min\_25 筛」．

### 性质

其可以在 $O\left(\frac{n^{\frac{3}{4}}}{\log{n}}\right)$ 或 $\Theta\left(n^{1 - \epsilon}\right)$ 的时间复杂度下解决一类 **积性函数** 的前缀和问题．

要求：$f(p)$ 是一个关于 $p$ 可以快速求值的完全积性函数之和（例如多项式）；$f(p^{c})$ 可以快速求值．

### 记号

-   **如无特别说明，本节中所有记为 $p$ 的变量的取值集合均为全体质数．**
-   $x / y := \left\lfloor\frac{x}{y}\right\rfloor$
-   $\operatorname{isprime}(n) := [ |\{d : d \mid n\}| = 2 ]$，即 $n$ 为质数时其值为 $1$，否则为 $0$．
-   $p_{k}$：全体质数中第 $k$ 小的质数（如：$p_{1} = 2, p_{2} = 3$）．特别地，令 $p_{0} = 1$．
-   $\operatorname{lpf}(n) := [1 < n] \min\{p : p \mid n\} + [1 = n]$，即 $n$ 的最小质因数．特别地，$n=1$ 时，其值为 $1$．
-   $F_{\mathrm{prime}}(n) := \sum_{2 \le p \le n} f(p)$
-   $F_{k}(n) := \sum_{i = 2}^{n} [p_{k} \le \operatorname{lpf}(i)] f(i)$

### 解释

观察 $F_{k}(n)$ 的定义，可以发现答案即为 $F_{1}(n) + f(1) = F_{1}(n) + 1$．

考虑如何求出 $F_{k}(n)$．通过枚举每个 $i$ 的最小质因子及其次数可以得到递推式：

$$
\begin{aligned}
    F_{k}(n)
    &= \sum_{i = 2}^{n} [p_{k} \le \operatorname{lpf}(i)] f(i) \\
    &= \sum_{\substack{k \le i \\ p_{i}^{2} \le n}} \sum_{\substack{c \ge 1 \\ p_{i}^{c} \le n}} f\left(p_{i}^{c}\right) ([c > 1] + F_{i + 1}\left(n / p_{i}^{c}\right)) + \sum_{\substack{k \le i \\ p_{i} \le n}} f(p_{i}) \\
    &= \sum_{\substack{k \le i \\ p_{i}^{2} \le n}} \sum_{\substack{c \ge 1 \\ p_{i}^{c} \le n}} f\left(p_{i}^{c}\right) ([c > 1] + F_{i + 1}\left(n / p_{i}^{c}\right)) + F_{\mathrm{prime}}(n) - F_{\mathrm{prime}}(p_{k - 1}) \\
    &= \sum_{\substack{k \le i \\ p_{i}^{2} \le n}} \sum_{\substack{c \ge 1 \\ p_{i}^{c + 1} \le n}} \left(f\left(p_{i}^{c}\right) F_{i + 1}\left(n / p_{i}^{c}\right) + f\left(p_{i}^{c + 1}\right)\right) + F_{\mathrm{prime}}(n) - F_{\mathrm{prime}}(p_{k - 1})
\end{aligned}
$$

最后一步推导基于这样一个事实：对于满足 $p_{i}^{c} \le n < p_{i}^{c + 1}$ 的 $c$，有 $p_{i}^{c + 1} > n \iff n / p_{i}^{c} < p_{i} < p_{i + 1}$，故 $F_{i + 1}\left(n / p_{i}^{c}\right) = 0$．  
其边界值即为 $F_{k}(n) = 0 (p_{k} > n)$．

假设现在已经求出了所有的 $F_{\mathrm{prime}}(n)$，那么有两种方式可以求出所有的 $F_{k}(n)$：

1.  直接按照递推式计算．
2.  从大到小枚举 $p$ 转移，仅当 $p^{2} < n$ 时转移增加值不为零，故按照递推式后缀和优化即可．

现在考虑如何计算 $F_{\mathrm{prime}}{(n)}$．  
观察求 $F_{k}(n)$ 的过程，容易发现 $F_{\mathrm{prime}}$ 有且仅有 $1, 2, \dots, \left\lfloor\sqrt{n}\right\rfloor, n / \sqrt{n}, \dots, n / 2, n$ 这 $O(\sqrt{n})$ 处的点值是有用的．  
一般情况下，$f(p)$ 是一个关于 $p$ 的低次多项式，可以表示为 $f(p) = \sum a_{i} p^{c_{i}}$．  
那么对于每个 $p^{c_{i}}$，其对 $F_{\mathrm{prime}}(n)$ 的贡献即为 $a_{i} \sum_{2 \le p \le n} p^{c_{i}}$．  
分开考虑每个 $p^{c_{i}}$ 的贡献，问题就转变为了：给定 $n, s, g(p) = p^{s}$，对所有的 $m = n / i$，求 $\sum_{p \le m} g(p)$．

???+ tip "注意"
    $g(p) = p^{s}$ 是完全积性函数！

于是设 $G_{k}(n) := \sum_{i = 2}^{n} \left[p_{k} < \operatorname{lpf}(i) \lor \operatorname{isprime}(i)\right] g(i)$，即埃筛第 $k$ 轮筛完后剩下的数的 $g$ 值之和．  
对于一个合数 $x \le n$，必定有 $\operatorname{lpf}(x) \le \sqrt{x} \le \sqrt{n}$．设 $p_{\ell(n)}$ 为不大于 $\sqrt{n}$ 的最大质数，则 $\sum_{2\le p\le n}g(p) = G_{\ell(n)}(n)$，即在埃筛进行 $\ell$ 轮之后剩下的均为质数．
考虑 $G$ 的边界值，显然为 $G_{0}(n) = \sum_{i = 2}^{n} g(i)$．（还记得吗？特别约定了 $p_{0} = 1$）  
对于转移，考虑埃筛的过程，分开讨论每部分的贡献，有：

1.  对于 $n < p_{k}^{2}$ 的部分，$G$ 值不变，即 $G_{k}(n) = G_{k - 1}(n)$．
2.  对于 $p_{k}^{2} \le n$ 的部分，被筛掉的数必有质因子 $p_{k}$，即 $-g(p_{k}) G_{k - 1}(n / p_{k})$．
3.  对于第二部分，由于 $p_{k}^{2} \le n \iff p_{k} \le n / p_{k}$，满足 $\operatorname{lpf}(i) < p_{k}$ 的 $i$ 会被额外减去．这部分应当加回来，即 $g(p_{k}) G_{k - 1}(p_{k - 1})$．

则有：

$$
G_{k}(n) = G_{k - 1}(n) - \left[p_{k}^{2} \le n\right] g(p_{k}) (G_{k - 1}(n / p_{k}) - G_{k - 1}(p_{k - 1}))
$$

### 复杂度分析

对于 $F_{k}(n)$ 的计算，其第一种方法的时间复杂度被证明为 $O\left(n^{1 - \epsilon}\right)$（见朱震霆集训队论文 [《一些特殊的数论函数求和问题》](https://github.com/OI-wiki/libs/blob/master/%E9%9B%86%E8%AE%AD%E9%98%9F%E5%8E%86%E5%B9%B4%E8%AE%BA%E6%96%87/%E5%9B%BD%E5%AE%B6%E9%9B%86%E8%AE%AD%E9%98%9F2018%E8%AE%BA%E6%96%87%E9%9B%86.pdf) 2.3）；  
对于第二种方法，其本质即为洲阁筛的第二部分，在任之洲论文 [《积性函数求和的几种方法》](https://github.com/OI-wiki/libs/blob/master/%E9%9B%86%E8%AE%AD%E9%98%9F%E5%8E%86%E5%B9%B4%E8%AE%BA%E6%96%87/%E5%9B%BD%E5%AE%B6%E9%9B%86%E8%AE%AD%E9%98%9F2016%E8%AE%BA%E6%96%87%E9%9B%86.pdf) 中也有提及（6.5.4），其时间复杂度被证明为 $O\left(\frac{n^{\frac{3}{4}}}{\log{n}}\right)$．

对于 $F_{\mathrm{prime}}(n)$ 的计算，事实上，其实现与洲阁筛第一部分是相同的．  
考虑对于每个 $m = n / i$，只有在枚举满足 $p_{k}^{2} \le m$ 的 $p_{k}$ 转移时会对时间复杂度产生贡献，则时间复杂度可估计为：

$$
\begin{aligned}
    T(n)
    &= \sum_{i^{2} \le n} O\left(\pi\left(\sqrt{i}\right)\right) + \sum_{i^{2} \le n} O\left(\pi\left(\sqrt{\frac{n}{i}}\right)\right) \\
    &= \sum_{i^{2} \le n} O\left(\frac{\sqrt{i}}{\ln{\sqrt{i}}}\right) + \sum_{i^{2} \le n} O\left(\frac{\sqrt{\frac{n}{i}}}{\ln{\sqrt{\frac{n}{i}}}}\right) \\
    &= O\left(\int_{1}^{\sqrt{n}} \frac{\sqrt{\frac{n}{x}}}{\log{\sqrt{\frac{n}{x}}}} \mathrm{d} x\right) \\
    &= O\left(\frac{n^{\frac{3}{4}}}{\log{n}}\right)
\end{aligned}
$$

对于空间复杂度，可以发现不论是 $F_{k}$ 还是 $F_{\mathrm{prime}}$，其均只在 $n / i$ 处取有效点值，共 $O(\sqrt{n})$ 个，仅记录有效值即可将空间复杂度优化至 $O(\sqrt{n})$．

首先，通过一次数论分块可以得到所有的有效值，用一个大小为 $O(\sqrt{n})$ 的数组 $\text{lis}$ 记录．对于有效值 $v$，记 $\text{id}(v)$ 为 $v$ 在 $\text{lis}$ 中的下标，易得：对于所有有效值 $v$，$\text{id}(v) \le \sqrt{n}$．

然后分开考虑小于等于 $\sqrt{n}$ 的有效值和大于 $\sqrt{n}$ 的有效值：对于小于等于 $\sqrt{n}$ 的有效值 $v$，用一个数组 $\text{le}$ 记录其 $\text{id}(v)$，即 $\text{le}_v = \text{id}(v)$；对于大于 $\sqrt{n}$ 的有效值 $v$，用一个数组 $\text{ge}$ 记录 $\text{id}(v)$，由于 $v$ 过大所以借助 $v' = n / v < \sqrt{n}$ 记录 $\text{id}(v)$，即 $\text{ge}_{v'} = \text{id}(v)$．

这样，就可以使用两个大小为 $O(\sqrt{n})$ 的数组记录所有有效值的 $\text{id}$ 并 $O(1)$ 查询．在计算 $F_{k}$ 或 $F_{\mathrm{prime}}$ 时，使用有效值的 $\text{id}$ 代替有效值作为下标，即可将空间复杂度优化至 $O(\sqrt{n})$．

### 过程

对于 $F_{k}(n)$ 的计算，我们实现时一般选择实现难度较低的第一种方法，其在数据规模较小时往往比第二种方法的表现要好；

对于 $F_{\mathrm{prime}}(n)$ 的计算，直接按递推式实现即可．

对于 $p_{k}^{2} \le n$，可以用线性筛预处理出 $s_{k} := F_{\mathrm{prime}}(p_{k})$ 来替代 $F_{k}$ 递推式中的 $F_{\mathrm{prime}}(p_{k - 1})$．  
相应地，$G$ 递推式中的 $G_{k - 1}(p_{k - 1}) = \sum_{i = 1}^{k - 1} g(p_{i})$ 也可以用此方法预处理．

用 Extended Eratosthenes Sieve 求 **积性函数**  $f$ 的前缀和时，应当明确以下几点：

-   如何快速（一般是线性时间复杂度）筛出前 $\sqrt{n}$ 个 $f$ 值；
-   $f(p)$ 的多项式表示；
-   如何快速求出 $f(p^{c})$．

明确上述几点之后按顺序实现以下几部分即可：

1.  筛出 $[1, \sqrt{n}]$ 内的质数与前 $\sqrt{n}$ 个 $f$ 值；
2.  对 $f(p)$ 多项式表示中的每一项筛出对应的 $G$，合并得到 $F_{\mathrm{prime}}$ 的所有 $O(\sqrt{n})$ 个有用点值；
3.  按照 $F_{k}$ 的递推式实现递归，求出 $F_{1}(n)$．

### 例题

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

### 例题

### [Luogu P5325【模板】Min\_25 筛](https://www.luogu.com.cn/problem/P5325)

**题意**：给定积性函数 $f(p^k) = p^k(p^k-1)$，求 $\sum_{i=1}^{n} f(i)$．

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

#### [「LOJ #6053」简单的函数](https://loj.ac/problem/6053)

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

### 习题

-   [PE708 Twos are all you need](https://projecteuler.net/problem=708)
-   [PE639 Summing a multiplicative function](https://projecteuler.net/problem=639)
-   [PE484 Arithmetic Derivative](https://projecteuler.net/problem=484)

## 参考资料与注释

-   [积性函数线性筛/杜教筛/洲阁筛学习笔记 | Bill Yang's Blog](https://blog.bill.moe/multiplicative-function-sieves-notes)
-   [破壁人五号 - Powerful number 筛略解](https://www.cnblogs.com/wallbreaker5th/p/13901487.html)
-   [command\_block - 杜教筛（+ 贝尔级数 + powerful number）](https://www.luogu.com.cn/blog/command-block/du-jiao-shai)
