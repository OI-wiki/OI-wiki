## 定义

Powerful Number（以下简称 PN）筛类似于杜教筛，或者说是杜教筛的一个扩展，可以拿来求一些积性函数的前缀和。

假设现在要求积性函数 $f$ 的前缀和 $F(n) = \sum_{i=1}^{n} f(i)$。

**要求**：

-   存在一个函数 $g$ 满足：
    - $g$ 是积性函数。
    - $g$ 易求前缀和。
    - 对于质数 $p$，$g(p) = f(p)$。

## Powerful Number

**定义**：对于正整数 $n$，记 $n$ 的质因数分解为 $n = \sum_{i=1}^{m} p_{i}^{e_{i}}$。$n$ 是 PN 当且仅当 $\forall 1 \le i \le m, e_{i} > 1$。

**性质 1**：所有 PN 都可以表示成 $a^{2}b^{3}$ 的形式。

**证明**：若 $e_i$ 是偶数，则将 $p_{i}^{e_{i}}$ 合并进 $a^{2}$ 里；若 $e_i$ 为奇数，则先将 $p_{i}^{3}$ 合并进 $b^{3}$ 里，再将 $p_{i}^{e_{i}-3}$ 合并进 $a^{2}$ 里。

**性质 2**：$n$ 以内的 PN 至多有 $O(\sqrt{n})$ 个。

**证明**：考虑枚举 $a$，再考虑满足条件的 $b$ 的个数，有 PN 的个数约等于

$$
\int_{1}^{\sqrt{n}} \sqrt[3]{\frac{n}{x^2}} dx = \sqrt{n}
$$

那么如何求出 $n$ 以内所有的素数呢？线性筛找出 $\sqrt{n}$ 内的所有素数，再 dfs 搜索各素数的指数即可。由于 $n$ 以内的 PN 至多有 $O(\sqrt{n})$ 个，所以搜索的复杂度也为 $O(\sqrt{n})$。

## PN 筛

首先，构造出一个易求前缀和的积性函数 $g$，且满足对于质数 $p$，$g(p) = f(p)$。记 $G(n) = \sum_{i=1}^{n} g(i)$。

然后，构造函数 $h = f / g$，这里的 $/$ 表示狄利克雷卷积除法。根据狄利克雷卷积的性质可以得知 $h$ 也为积性函数，$f = g * h$，这里 $*$ 表示狄利克雷卷积。

易得 $h(1) = 1$。

对于素数 $p$，$f(p) = g(1)h(p) + g(p)f(1) = h(p) + g(p) \Rightarrow h(p) = 0$。根据 $h(p)=0$ 和 $h$ 是积性函数可以推出对于非 PN 的数 $n$ 有 $h(n) = 0$，即 $h$ 仅在 PN 处取有效值。

$$
\begin{align}
F(n) &= \sum_{i = 1}^{n} f(i)\\
     &= \sum_{i = 1}^{n} \sum_{d|i} h(i) g(\frac{i}{d})\\
     &= \sum_{d=1}^{n} \sum_{i=1}^{\lfloor \frac{n}{d}\rfloor} h(d) g(i)\\
     &= \sum_{d=1}^{n} h(d) \sum_{i=1}^{\lfloor \frac{n}{d}\rfloor}  g(i) \\
     &= \sum_{d=1}^{n} h(d) G(\lfloor \frac{n}{d}\rfloor)\\
     &= \sum_{\substack{d=1 \\ d \text{ is PN}}}^{n}h(d) G(\lfloor \frac{n}{d}\rfloor)
\end{align}
$$

$O(\sqrt{n})$ 找出所有 PN，计算出所有 $h$ 的有效值。对于 $h$ 有效值的计算，只需要计算出所有 $h(p^c)$ 处的值，就可以根据 $h$ 为积性函数推出 $h$ 的所有有效值。下面考虑计算 $h(p^c)$。根据 $f = g * h$ 有 $f(p^c) = \sum_{i=0}^c h(p^i)g(p^{c-i})$，移项可得 $h(p^c) = f(p^c) - \sum_{i=0}^{c-1}g(p^{c-i})h(p^i)$，现在可以枚举素数 $p$ 再枚举质数 $c$ 求解出 $h(p^c)$。

现在 $O(\sqrt{n})$ 对 $G$ 进行数论分块，即可求出 $F(n)$。

## 例题

### [「LOJ #6053」简单的函数](https://loj.ac/problem/6053)

给定 $f(n)$：

$$
f(n) = 
\left\{
\begin{array}{ll}
1 & n = 1 \\
p \oplus c & n=p^c \\
f(a)f(b) & n=ab \text{ and } a \perp b
\end{array}
\right.
$$

不妨令 $f(p) = p-1$，再特判 $p=2$ 时的情况。又因为 $\varphi(p) = p-1$，且 $\varphi$ 可以利用杜教筛快速求前缀和，所以不妨令 $g = \varphi$。
