一个数 $a$，如果不是 $p$ 的倍数且模 $p$ 同余于某个数的平方，则称 $a$ 为模 $p$ 的 **二次剩余**。而一个不是 $p$ 的倍数的数 $b$，不同余于任何数的平方，则称 $b$ 为模 $p$ 的 **二次非剩余**。

对二次剩余求解，也就是对常数 $a$ 解下面的这个方程：

$$
x^2 \equiv a \pmod p
$$

通俗一些，可以认为是求模意义下的开方。这里只讨论 $\boldsymbol{p}$ **为奇素数** 的求解方法。

后文可能在模 $p$ 显然的情况下简写成二次（非）剩余。

## Legendre 符号

$$
\left(\frac{a}{p}\right)=\begin{cases}
1,\,&p\nmid a \text{ 且 }a\text{ 是模 }p\text{ 的二次剩余}\\
-1,\,&p\nmid a \text{ 且 }a\text{ 不是模 }p\text{ 的二次剩余}\\
0,\,&p\mid a
\end{cases}
$$

通过 Legendre 符号可以判断一个数 $a$ 是否为二次剩余，具体判断 $a$ 是否为模 $p$ 的二次剩余，需要通过 Euler 判别准则来实现。

下表为部分 Legendre 符号的值![](./images/quad_residue.png)

## Euler 判别准则

对于奇素数 $p$ 和 $p\nmid a$ 有

$$
a^{(p-1)/2}\equiv \left(\frac{a}{p}\right)\equiv
\begin{cases}
1\pmod p,&\text{若 }x^2\equiv a\pmod p\text{ 有解}\\
-1\pmod p,&\text{若 }x^2\equiv a\pmod p\text{ 无解}
\end{cases}
$$

### 证明

**引理**：令 $p$ 为素数和模 $p$ 意义下原根 $g$ 并令 $a\equiv g^k\pmod p$。那么 $x^2\equiv a\pmod p$ 有解当且仅当 $k$ 为偶数。

**引理的证明**：（充分性）假设 $x^2\equiv a\pmod p$ 有解为 $g^l$ 对于某个 $l$ 成立。那么 $(g^l)^2\equiv a\pmod p\implies g^{2l}\equiv a\pmod p$。因此 $k=2l$ 所以 $k$ 为偶数。

（必要性）假设 $k$ 为偶数，那么

$$
x^2\equiv g^k\pmod p\iff x^2\equiv (g^{k/2})^2\pmod p
$$

而因为 $k$ 为偶数，所以 $k/2$ 为整数，因此 $x^2\equiv g^k\pmod p$ 有解为 $g^{k/2}$。

因为 $g$ 为模 $p$ 的原根，那么 $g$ 的阶为 $\varphi(p)=p-1$ 所以 $g^{p-1}\equiv 1\pmod p$ 且根据阶的定义，对于所有 $k\in\mathbb{Z}$ 满足 $1\leq k\lt p-1$ 都有 $g^k\not\equiv 1\pmod p$，所以

$$
\begin{aligned}
&{}g^{p-1}\equiv 1\pmod p\\
\iff &g^{p-1}-1\equiv 0\pmod p\\
\iff &\left(g^{(p-1)/2}-1\right)\cdot\left(g^{(p-1)/2}+1\right)\equiv 0\pmod p\\
\implies &g^{(p-1)/2}\equiv -1\pmod p
\end{aligned}
$$

考虑同余方程 $x^2\equiv a\pmod p$。因为 $a\in\mathbb{F}_p\setminus \lbrace 0\rbrace$ 且 $a\equiv g^k\pmod p$ 对于某个 $k$ 满足 $1\leq k\leq p-1$ 成立。若同余方程存在解，则 $k$ 为偶数，通过上述引理和 Fermat 小定理有

$$
\begin{aligned}
a^{(p-1)/2}&\equiv \left(g^k\right)^{(p-1)/2}\pmod p\\
&\equiv \left(g^{p-1}\right)^{k/2}\pmod p\\
&\equiv 1\pmod p
\end{aligned}
$$

所以当 $a^{(p-1)/2}\equiv 1\pmod p$ 时解存在。

又因上述引理，$x^2\equiv a\pmod p$ 无解时 $k$ 为奇数。假设 $k$ 为奇数，那么

$$
\begin{aligned}
a^{(p-1)/2}&\equiv (g^k)^{(p-1)/2}\pmod p\\
&\equiv \left(g^{(p-1)/2}\right)^k\pmod p\\
&\equiv \left(-1\right)^k\pmod p\\
&\equiv -1\pmod p
\end{aligned}
$$

即得 Euler 判别准则，也可以推断出 Legendre 符号为完全积性函数。

## 二次剩余和二次非剩余的数量

对于奇素数 $p$ 和集合 $\left\lbrace 1,2,\dots ,p-1\right\rbrace$，在模 $p$ 意义下二次剩余的数量等于二次非剩余的数量。

### 证明

**引理**：对于 $d\mid (p-1)$ 和奇素数 $p\in\mathbb{Z}$，$x^d\equiv 1\pmod p$ 恰有 $d$ 个解。

**引理的证明**：根据 Fermat 小定理，当 $\gcd(a,p)=1$ 时有 $a^{p-1}\equiv 1\pmod p$。因此对于每个 $a\in\left\lbrace 1,\dots ,p-1\right\rbrace$，$x=a$ 是 $x^{p-1}\equiv 1\pmod p$ 的解。通过因式分解 $x^{p-1}-1$ 有

$$
\begin{aligned}
x^{p-1}-1&\equiv (x^d-1)(x^{p-1-d}+x^{p-1-2d}+\cdots +1)\pmod p\\
&\equiv (x^d-1)\cdot g(x)\pmod p\\
&\equiv 0\pmod p
\end{aligned}
$$

其中 $\deg(g(x))=p-1-d$。根据 [Lagrange 定理](./lagrange.md) 我们知道 $g(x)=0$ 最多有 $p-1-d$ 个解。因为 $x^{p-1}-1\equiv 0\pmod p$ 有 $p-1$ 个解，所以显然 $x^d-1\equiv 0\pmod p$ 至少有 $d$ 个解。如果只考虑 $x^d-1\equiv 0\pmod p$，我们知道最多有 $d$ 个解。所以 $x^d-1\equiv 0\pmod p$ 恰有 $d$ 个解。

根据 Euler 判别准则，对于 $a^{(p-1)/2}\equiv 1\pmod p$ 显然 $\frac{p-1}{2}\mid (p-1)$，又因上述引理所以 $a^{(p-1)/2}\equiv 1\pmod p$ 有 $\frac{p-1}{2}$ 个解，而集合中有 $p-1$ 个元素，所以也有 $\frac{p-1}{2}$ 个二次非剩余。

## 特殊情况时的算法

对于同余方程 $x^2\equiv a\pmod p$，其中 $p$ 为奇素数且 $a$ 为二次剩余在 $p\bmod 4=3$ 时有更简单的解法，考虑

$$
\begin{aligned}
\left(a^{(p+1)/4}\right)^2&\equiv a^{(p+1)/2}\pmod p\\
&\equiv x^{p+1}\pmod p\\
&\equiv \left(x^2\right)\left(x^{p-1}\right)\pmod p\\
&\equiv x^2\pmod p\quad (\because{\text{Fermat 小定理}})
\end{aligned}
$$

那么 $a^{(p+1)/4}\bmod p$ 为一个解。

### Atkin 算法

仍然考虑上述同余方程，此时 $p\bmod 8=5$，那么令 $b\equiv (2a)^{(p-5)/8}\pmod p$ 和 $\mathrm{i}\equiv 2ab^2\pmod p$ 那么此时 $\mathrm{i}^2\equiv -1\pmod p$ 且 $ab(\mathrm{i}-1)\bmod p$ 为一个解。

**证明**：

$$
\begin{aligned}
\mathrm{i}^2&\equiv\left(2ab^2\right)^2\pmod p\\
&\equiv \left(2a\cdot \left(2a\right)^{(p-5)/4}\right)^2\pmod p\\
&\equiv \left(\left(2a\right)^{(p-1)/4}\right)^2\pmod p\\
&\equiv \left(2a\right)^{(p-1)/2}\pmod p\\
&\equiv -1\pmod p
\end{aligned}
$$

其中 $2$ 在模形如 $8k+3$ 或 $8k+5$ 的素数时为二次非剩余，这由二次互反律给出，由于证明较复杂，读者可参考 [Wikipedia](https://en.wikipedia.org/wiki/Quadratic_reciprocity)。

那么

$$
\begin{aligned}
\left(ab(\mathrm{i}-1)\right)^2&\equiv a^2\cdot \left(2a\right)^{(p-5)/4}\cdot (-2\mathrm{i})\pmod p\\
&\equiv a\cdot (-\mathrm{i})\cdot \left(2a\right)^{(p-1)/4}\pmod p\\
&\equiv a\pmod p
\end{aligned}
$$

得证。

## Cipolla 算法

Cipolla 算法用于求解同余方程 $x^2\equiv a\pmod p$，其中 $p$ 为奇素数且 $a$ 为二次剩余。算法可描述为找到 $r$ 满足 $r^2-a$ 为二次非剩余，$(r-x)^{(p+1)/2}\bmod (x^2-(r^2-a))$ 为一个解。

在复数域 $\mathbb{C}$ 中，记 $\mathrm{i}^2=-1$ 后 $\mathbb{C}=\lbrace a_0+a_1\mathrm{i}\mid a_0,a_1\in\mathbb{R}\rbrace$。考虑令 $x^2+1\in\mathbb{R}\lbrack x\rbrack$ 和实系数多项式的集合 $\mathbb{R}\lbrack x\rbrack$ 对 $x^2+1$ 取模后的集合记作 $\mathbb{R}\lbrack x\rbrack /(x^2+1)$，那么集合中的元素都可以表示为 $a_0+a_1x$ 的形式，其中 $a_0,a_1\in\mathbb{R}$，又因为 $x^2\equiv -1\pmod{\left(x^2+1\right)}$，考虑多项式的运算可以发现 $\mathbb{R}\lbrack x\rbrack /(x^2+1)$ 中元素的运算与 $\mathbb{C}$ 中一致。

后文考虑对于系数属于有限域 $\mathbb{F}_p$ 的多项式 $\mathbb{F}_p\lbrack x\rbrack$ 和对 $x^2-(r^2-a)\in\mathbb{F}_p\lbrack x\rbrack$ 取模后的集合 $\mathbb{F}_p\lbrack x\rbrack /(x^2-(r^2-a))$ 中的运算。

**选择**  $r$：

若 $a\equiv 0\pmod p$ 那么 $r^2-a$ 为二次剩余，此时解显然为 $x\equiv 0\pmod p$。所以假设 $a\not\equiv 0\pmod p$。使得 $r^2-a$ 为非零二次剩余的选择有 $(p-3)/2$ 个，而使得 $r^2\equiv a\pmod p$ 的选择恰有两个，那么有 $(p-1)/2$ 种选择可以使得 $r^2-a$ 为二次非剩余，使用随机方法平均约两次可得 $r$。

**证明**：

令 $f(x)=x^2-(r^2-a)\in\mathbb{F}_p\lbrack x\rbrack$ 和 $a_0+a_1x=(r-x)^{(p+1)/2}\bmod (x^2-(r^2-a))$ 那么有 $a_0^2\equiv a\pmod p$ 且 $a_1\equiv 0\pmod p$。

$$
\begin{aligned}
x^p&\equiv x(x^2)^{(p-1)/2}\pmod{f(x)}\\
&\equiv x(r^2-a)^{(p-1)/2}\pmod{f(x)}&\quad (\because{x^2\equiv r^2-a\pmod{f(x)}})\\
&\equiv -x\pmod{f(x)}&\quad (\because{r^2-a}\text{ 为二次非剩余})
\end{aligned}
$$

又因为二项式定理

$$
\begin{aligned}
(a+b)^p&=\sum_{i=0}^p\binom{p}{i}a^ib^{p-i}\\
&=\sum_{i=0}^p\frac{p!}{i!(p-i)!}a^ib^{p-i}\\
&\equiv a^p+b^p\pmod p
\end{aligned}
$$

可以发现只有当 $i=0$ 和 $i=p$ 时由于没有因子 $p$ 不会因为模 $p$ 被消去，其他的项都因为有 $p$ 因子被消去了。所以

$$
\begin{aligned}
(r-x)^{p}&\equiv r^p-x^p\pmod{f(x)}\\
&\equiv r+x\pmod{f(x)}
\end{aligned}
$$

所以

$$
\begin{aligned}
(a_0+a_1x)^2&=a_0^2+2a_0a_1x+a_1^2x^2\\
&\equiv (r-x)^{p+1}\pmod{f(x)}\\
&\equiv (r-x)^p(r-x)\pmod{f(x)}\\
&\equiv (r+x)(r-x)\pmod{f(x)}\\
&\equiv r^2-x^2\pmod{f(x)}\\
&\equiv a\pmod{f(x)}
\end{aligned}
$$

若 $a_1\not\equiv 0\pmod p$ 且

$$
\begin{aligned}
(a_0+a_1x)^2&=a_0^2+2a_0a_1x+a_1^2x^2\\
&\equiv a_0^2+2a_0a_1x+a_1^2(r^2-a)\pmod{f(x)}
\end{aligned}
$$

所以 $x$ 的系数必须为零即 $a_0\equiv 0\pmod p$ 此时考虑 Legendre 符号为完全积性函数可知 $r^2-a\equiv a/a_1^2\pmod p$ 显然为二次剩余，不符合定义。因此 $a_1\equiv 0\pmod p$ 且 $a_0^2\equiv a\pmod p$。

## Legendre 算法

对于同余方程 $x^2\equiv a\pmod p$，其中 $p$ 为奇素数且 $a$ 为二次剩余。Legendre 算法可描述为找到 $r$ 满足 $r^2-a$ 为二次非剩余，令 $a_0+a_1x=(r-x)^{(p-1)/2}\bmod (x^2-a)$，那么 $a_0\equiv 0\pmod p$ 且 $a_1^{-2}\equiv a\pmod p$。

**证明**：考虑选择一个 $b$ 满足 $b^2\equiv a\pmod p$，那么 $(r-b)(r+b)=r^2-a$ 为二次非剩余，所以

$$
(r-b)^{(p-1)/2}(r+b)^{(p-1)/2}\equiv -1\pmod p
$$

存在环态射

$$
\begin{aligned}
\phi:\mathbb{F}_p\lbrack x\rbrack/(x^2-a)&\to \mathbb{F}_p\times \mathbb{F}_p\\
x&\mapsto (b,-b)
\end{aligned}
$$

那么

$$
\begin{aligned}
(a_0+a_1b,a_0-a_1b)&=\phi(a_0+a_1x)\\
&=\phi(r-x)^{(p-1)/2}\\
&=((r-b)^{(p-1)/2},(r+b)^{(p-1)/2})\\
&=(\pm 1,\mp 1)
\end{aligned}
$$

所以 $2a_0=(\pm 1)+(\mp 1)=0$ 而 $2a_1b=(\pm 1)-(\mp 1)=\pm 2$。

## Tonelli-Shanks 算法

Tonelli-Shanks 算法是基于离散对数求解同余方程 $x^2\equiv a\pmod p$ 的算法，其中 $p$ 为奇素数且 $a$ 为模 $p$ 的二次剩余。

令 $p-1=2^n\cdot m$ 其中 $m$ 为奇数。仍然使用随机方法寻找 $r\in\mathbb{F}_p$ 满足 $r$ 为二次非剩余。令 $g\equiv r^m\pmod p$ 且 $b\equiv a^{(m-1)/2}\pmod p$，那么存在整数 $e\in\lbrace 0,1,2,\dots ,2^n-1\rbrace$ 满足 $ab^2\equiv g^e\pmod p$。若 $a$ 为二次剩余，那么 $e$ 为偶数且 $\left(abg^{-e/2}\right)^2\equiv a\pmod p$。

**证明**：

$$
\begin{aligned}
g^{2^n}&\equiv r^{2^n\cdot m}\pmod p\\
&\equiv r^{p-1}\pmod p\\
&\equiv 1\pmod p
\end{aligned}
$$

而

$$
\begin{aligned}
g^{2^{n-1}}&\equiv r^{2^{n-1}\cdot m}\pmod p\\
&\equiv r^{(p-1)/2}\pmod p\\
&\equiv -1\pmod p
\end{aligned}
$$

所以 $g$ 的阶为 $2^n$，又因为 $ab^2\equiv a^m\pmod p$ 是 $x^{2^n}\equiv 1\pmod p$ 的解，所以 $a^m$ 是 $g$ 的幂次，记 $a^m\equiv g^e\pmod p$。

若 $a$ 是二次剩余，那么

$$
\begin{aligned}
g^{2^{n-1}\cdot e}&\equiv (-1)^e\pmod p\\
&\equiv a^{2^{n-1}\cdot m}\pmod p\\
&\equiv a^{(p-1)/2}\pmod p\\
&\equiv 1\pmod p
\end{aligned}
$$

所以 $e$ 为偶数，而

$$
\begin{aligned}
\left(abg^{-e/2}\right)^2&\equiv a^2b^2g^{-e}\pmod p\\
&\equiv a^{m+1}g^{-e}\pmod p\\
&\equiv a\pmod p
\end{aligned}
$$

剩下的问题是如何计算 $e$，Tonelli 和 Shanks 提出一次确定 $e$ 的一个比特。令 $e$ 在二进制下表示为 $e=e_0+2e_1+4e_2+\cdots$ 其中 $e_k\in\lbrace 0,1\rbrace$。

因为 $a$ 是二次剩余，所以开始时 $e_0=0$，然后计算 $e_1$ 然后 $e_2$ 等等，由以下公式给出

$$
\left(g^eg^{-(e\bmod 2^k)}\right)^{2^{n-1-k}}\equiv g^{2^{n-1}\cdot e_k}\equiv 
\begin{cases}
1\pmod p&\text{if }e_k=0\text{,}\\
-1\pmod p&\text{if }e_k=1\text{.}
\end{cases}
$$

正确性显然。

## 习题

[【模板】二次剩余](https://www.luogu.com.cn/problem/P5491)

[「Timus 1132」Square Root](https://acm.timus.ru/problem.aspx?space=1&num=1132)

## 参考文献

- <https://en.wikipedia.org/wiki/Quadratic_residue>
- <https://en.wikipedia.org/wiki/Euler%27s_criterion>
- Daniel. J. Bernstein. Faster Square Roots in Annoying Finite Fields.
- S. Müller, On the computation of square roots in finite fields, Design, Codes and Cryptography, Vol.31, pp. 301-312, 2004
- A. Menezes, P. van Oorschot and S. Vanstone. Handbook of Applied Cryptography, 1996.
