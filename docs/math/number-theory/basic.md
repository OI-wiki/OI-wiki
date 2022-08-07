本文对于数论的开头部分做一个简介。

## 整除

整除的定义：设 $a,b\in\mathbf{Z}$，$a\ne0$。如果 $\exists q\in\mathbf{Z}$，使得 $b=aq$，那么就说 $b$ 可被 $a$ 整除，记作 $a\mid b$，且称 $b$ 是 $a$ 的倍数，$a$ 是 $b$ 的约数（因数）。

$b$ 不被 $a$ 整除记作 $a\nmid b$。

整除的性质：

- $a\mid b\iff-a\mid b\iff a\mid-b\iff|a|\mid|b|$
- $a\mid b\land b\mid c\implies a\mid c$
- $a\mid b\land a\mid c\iff\forall x,y\in\mathbf{Z}, a\mid(xb+yc)$
- $a\mid b\land b\mid a\implies b=\pm a$
- 设 $m\ne0$，那么 $a\mid b\iff ma\mid mb$。
- 设 $b\ne0$，那么 $a\mid b\implies|a|\le|b|$。
- 设 $a\ne0,b=qa+c$，那么 $a\mid b\iff a\mid c$。

$0$ 是所有非 $0$ 整数的倍数。对于整数 $b\ne0$，$b$ 的约数只有有限个。

显然约数（显然因数）：对于整数 $b\ne0$，$\pm1$、$\pm b$ 是 $b$ 的显然约数。当 $b=\pm1$ 时，$b$ 只有两个显然约数。

对于整数 $b\ne0$，$b$ 的其他约数称为真约数（真因数、非显然约数、非显然因数）。

约数的性质：

- 设整数 $b\ne0$。当 $d$ 遍历 $b$ 的全体约数的时候，$\dfrac{b}{d}$ 也遍历 $b$ 的全体约数。
- 设整数 $b>0$，则当 $d$ 遍历 $b$ 的全体正约数的时候，$\dfrac{b}{d}$ 也遍历 $b$ 的全体正约数。

## 带余数除法

余数的定义：设 $a,b$ 为两个给定的整数，$a\ne0$。设 $d$ 是一个给定的整数。那么，一定存在唯一的一对整数 $q$ 和 $r$，满足 $b=qa+r,d\le r<|a|+d$。

无论整数 $d$ 取何值，$r$ 统称为余数。$a\mid b$ 等价于 $a\mid r$。

一般情况下，$d$ 取 $0$，此时等式 $b=qa+r,0\le r<|a|$ 称为带余数除法（带余除法）。这里的余数 $r$ 称为最小非负余数。

余数往往还有两种常见取法：

绝对最小余数：$d$ 取 $a$ 的绝对值的一半的相反数。即 $b=qa+r,-\dfrac{|a|}{2}\le r<|a|-\dfrac{|a|}{2}$。

最小正余数：$d$ 取 $1$。即 $b=qa+r,1\le r<|a|+1$。

带余数除法的余数只有最小非负余数。**如果没有特别说明，余数总是指最小非负余数。**

余数的性质：

- 任一整数被正整数 $a$ 除后，余数一定是且仅是 $0$ 到 $(a-1)$ 这 $a$ 个数中的一个。
- 相邻的 $a$ 个整数被正整数 $a$ 除后，恰好取到上述 $a$ 个余数。特别地，一定有且仅有一个数被 $a$ 整除。

## 最大公约数与最小公倍数

关于公约数、公倍数、最大公约数与最小公倍数，四个名词的定义，见 [最大公约数](./gcd.md)。

### 互素

两个整数互素（既约）的定义：若 $\gcd(a_1,a_2)=1$，则称 $a_1$ 和 $a_2$ 互素（既约）。

多个整数互素（既约）的定义：若 $\gcd(a_1,\ldots,a_k)=1$，则称 $a_1,\ldots,a_k$ 互素（既约）。

多个整数互素，不一定两两互素。例如 $6$、$10$ 和 $15$ 互素，但是任意两个都不互素。

互素的性质与最大公约数理论：裴蜀定理（Bézout's identity）。见 [裴蜀定理](./bezouts.md)。

### 辗转相除法

辗转相除法是一种算法，也称 Euclid 算法。见 [最大公约数](./gcd.md)。

## 素数与合数

关于素数的算法见 [素数](./prime.md)。

设整数 $p\ne0,\pm1$。如果 $p$ 除了显然约数外没有其他约数，那么称 $p$ 为素数（不可约数）。

若整数 $a\ne0,\pm 1$ 且 $a$ 不是素数，则称 $a$ 为合数。

$p$ 和 $-p$ 总是同为素数或者同为合数。**如果没有特别说明，素数总是指正的素数。**

整数的因数是素数，则该素数称为该整数的素因数（素约数）。

素数与合数的简单性质：

- 大于 $1$ 的整数 $a$ 是合数，等价于 $a$ 可以表示为整数 $d$ 和 $e$（$1<d,e<a$）的乘积。
- 如果素数 $p$ 有大于 $1$ 的约数 $d$，那么 $d=p$。
- 大于 $1$ 的整数 $a$ 一定可以表示为素数的乘积。
- 对于合数 $a$，一定存在素数 $p\le\sqrt{a}$ 使得 $p\mid a$。
- 素数有无穷多个。
- 所有大于 $3$ 的素数都可以表示为 $6n\pm 1$ 的形式[^ref1]。

## 算术基本定理

算术基本引理：

设 $p$ 是素数，$p\mid a_1a_2$，那么 $p\mid a_1$ 和 $p\mid a_2$ 至少有一个成立。

算术基本引理是素数的本质属性，也是素数的真正定义。

上文给出的素数定义，事实上叫做不可约数，素数是不可约数的子集。在一些整环中（如：唯一分解整环），不可约数和素数是两个不同的集合，在两集合不相等的整环中，算术基本定理不成立。由于整数范围内两个集合完全一致，因此可以不做区分。

算术基本定理（唯一分解定理）：

设正整数 $a$，那么必有表示：

$$
a=p_1p_2\cdots p_s
$$

其中 $p_j(1\le j\le s)$ 是素数。并且在不计次序的意义下，该表示唯一。

标准素因数分解式：

将上述表示中，相同的素数合并，可得：

$$
a={p_1}^{\alpha_1}{p_2}^{\alpha_2}\cdots{p_s}^{\alpha_s},p_1<p_2<\cdots<p_s
$$

称为正整数 $a$ 的标准素因数分解式。

算术基本定理和算术基本引理，两个定理是等价的。

## 同余

同余的定义：设整数 $m\ne0$。若 $m\mid(a-b)$，称 $m$ 为模数（模），$a$ 同余于 $b$ 模 $m$，$b$ 是 $a$ 对模 $m$ 的剩余。记作 $a\equiv b\pmod m$。

否则，$a$ 不同余于 $b$ 模 $m$，$b$ 不是 $a$ 对模 $m$ 的剩余。记作 $a\not\equiv b\pmod m$。

这样的等式，称为模 $m$ 的同余式，简称同余式。

根据整除的性质，上述同余式也等价于 $a\equiv b\pmod{(-m)}$。

**如果没有特别说明，模数总是正整数。**

式中的 $b$ 是 $a$ 对模 $m$ 的剩余，这个概念与余数完全一致。通过限定 $b$ 的范围，相应的有 $a$ 对模 $m$ 的最小非负剩余、绝对最小剩余、最小正剩余。

同余的性质：

- 自反性：$a\equiv a\pmod m$。
- 对称性：若 $a\equiv b\pmod m$，则 $b\equiv a\pmod m$。
- 传递性：若 $a\equiv b\pmod m,b\equiv c\pmod m$，则 $a\equiv c\pmod m$。
-   线性运算：若 $a,b,c,d\in\mathbf{Z},m\in\mathbf{N}^*,a\equiv b\pmod m,c\equiv d\pmod m$ 则有：
    - $a\pm c\equiv b\pm d\pmod m$。
    - $a\times c\equiv b\times d\pmod m$。
- 若 $a,b\in\mathbf{Z},k,m\in\mathbf{N}^*,a\equiv b\pmod m$, 则 $ak\equiv bk\pmod{mk}$。
- 若 $a,b\in\mathbf{Z},d,m\in\mathbf{N}^*,d\mid a,d\mid b,d\mid m$，则当 $a\equiv b\pmod m$ 成立时，有 $\dfrac{a}{d}\equiv\dfrac{b}{d}\left(\bmod\;{\dfrac{m}{d}}\right)$。
- 若 $a,b\in\mathbf{Z},d,m\in\mathbf{N}^*,d\mid m$，则当 $a\equiv b\pmod m$ 成立时，有 $a\equiv b\pmod d$。
- 若 $a,b\in\mathbf{Z},d,m\in\mathbf{N}^*$，则当 $a\equiv b\pmod m$ 成立时，有 $\gcd(a,m)=\gcd(b,m)$。若 $d$ 能整除 $m$ 及 $a,b$ 中的一个，则 $d$ 必定能整除 $a,b$ 中的另一个。

还有性质是乘法逆元。见 [乘法逆元](./inverse.md)。

## C/C++ 的整数除法和取模运算

在 C/C++ 中，整数除法和取模运算，与数学上习惯的取模和除法不一致。

对于所有标准版本的 C/C++，规定在整数除法中：

1. 当除数为 0 时，行为未定义；
2. 否则 `(a / b) * b + a % b` 的运算结果与 `a` 相等。

也就是说，取模运算的符号取决于除法如何取整；而除法如何取整，这是实现定义的（由编译器决定）。

**从 C99[^operatorc]和 C++11[^operatorcpp]标准版本起**，规定 **商向零取整**（舍弃小数部分）；取模的符号即与被除数相同。从此以下运算结果保证为真：

```text
5 % 3 == 2;
5 % -3 == 2;
-5 % 3 == -2;
-5 % -3 == -2;
```

## 数论函数

数论函数指定义域为正整数的函数。数论函数也可以视作一个数列。

## 积性函数

### 定义

若函数 $f(n)$ 满足 $f(1)=1$ 且 $\forall x,y\in\mathbf{N}^*,\gcd(x,y)=1$ 都有 $f(xy)=f(x)f(y)$，则 $f(n)$ 为积性函数。

若函数 $f(n)$ 满足 $f(1)=1$ 且 $\forall x,y\in\mathbf{N}^*$ 都有 $f(xy)=f(x)f(y)$，则 $f(n)$ 为完全积性函数。

### 性质

若 $f(x)$ 和 $g(x)$ 均为积性函数，则以下函数也为积性函数：

$$
\begin{aligned}
h(x)&=f(x^p)\\
h(x)&=f^p(x)\\
h(x)&=f(x)g(x)\\
h(x)&=\sum_{d\mid x}f(d)g\left(\dfrac{x}{d}\right)
\end{aligned}
$$

设 $x=\prod p_i^{k_i}$

若 $F(x)$ 为积性函数，则有 $F(x)=\prod F(p_i^{k_i})$。

若 $F(x)$ 为完全积性函数，则有 $F(x)=\prod F(p_i)^{k_i}$。

### 例子

- 单位函数：$\varepsilon(n)=[n=1]$。（完全积性）
- 恒等函数：$\operatorname{id}_k(n)=n^k$，$\operatorname{id}_{1}(n)$ 通常简记作 $\operatorname{id}(n)$。（完全积性）
- 常数函数：$1(n)=1$。（完全积性）
- 除数函数：$\sigma_{k}(n)=\sum_{d\mid n}d^{k}$。$\sigma_{0}(n)$ 通常简记作 $d(n)$ 或 $\tau(n)$，$\sigma_{1}(n)$ 通常简记作 $\sigma(n)$。
- 欧拉函数：$\varphi(n)=\sum_{i=1}^n[\gcd(i,n)=1]$
- 莫比乌斯函数：$\mu(n)=\begin{cases}1&n=1\\0&\exists d>1,d^{2}\mid n\\(-1)^{\omega(n)}&\text{otherwise}\end{cases}$，其中 $\omega(n)$ 表示 $n$ 的本质不同质因子个数，它是一个加性函数。

???+note "加性函数"
    此处加性函数指数论上的加性函数 (Additive function)。对于加性函数 $f$，当整数 $a,b$ 互质时，均有 $f(ab)=f(a)+f(b)$。
    应与代数中的加性函数 (Additive map) 区分。

* * *

## 参考资料与注释

[^ref1]: [Are all primes (past 2 and 3) of the forms 6n+1 and 6n-1?](https://primes.utm.edu/notes/faq/six.html)

[^operatorc]: [Arithmetic operators (C) - cppreference.com](https://en.cppreference.com/w/c/language/operator_arithmetic)

[^operatorcpp]: [Arithmetic operators (C++) - cppreference.com](https://en.cppreference.com/w/cpp/language/operator_arithmetic)
