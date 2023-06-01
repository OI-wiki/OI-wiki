## 定义

一个数 $a$，如果不是 $p$ 的倍数且模 $p$ 同余于某个数的平方，则称 $a$ 为模 $p$ 的 **二次剩余**。而一个不是 $p$ 的倍数的数 $b$，不同余于任何数的平方，则称 $b$ 为模 $p$ 的 **二次非剩余**。

对二次剩余求解，也就是对常数 $a$ 解下面的这个方程：

$$
x^2 \equiv a \pmod p
$$

通俗一些，可以认为是求模意义下的 **开平方** 运算。对于更高次方的开方的简单讨论，可以参见离散对数一文。

这里只讨论 $\boldsymbol{p}$ **为奇素数** 的求解方法。后文可能在模 $p$ 显然的情况下简写成二次（非）剩余。

## Legendre 符号

$$
\left(\frac{a}{p}\right)=\begin{cases}
1,\,&p\nmid a \text{ and }a\text{ is a quadratic residue modulo }p\\
-1,\,&p\nmid a \text{ and }a\text{ is a quadratic non-residue modulo }p\\
0,\,&p\mid a
\end{cases}
$$

通过 Legendre 符号可以判断一个数 $a$ 是否为二次剩余，具体判断 $a$ 是否为模 $p$ 的二次剩余，需要通过 [Euler 判别准则](./residue.md#euler-判别准则) 来实现。

下表为部分 Legendre 符号的值![](./images/quad_residue.png)

## 特殊情况时的算法

对于同余方程 $x^2\equiv a\pmod p$，其中 $p$ 为奇素数且 $a$ 为二次剩余在 $p\bmod 4=3$ 时有更简单的解法，考虑

$$
\begin{aligned}
\left(a^{(p+1)/4}\right)^2&\equiv a^{(p+1)/2}&\pmod p\\
&\equiv x^{p+1}&\pmod p\\
&\equiv \left(x^2\right)\left(x^{p-1}\right)&\pmod p\\
&\equiv x^2&\pmod p&\quad (\because{\text{Fermat's little theorem}})
\end{aligned}
$$

那么 $a^{(p+1)/4}\bmod p$ 为一个解。

### Atkin 算法

#### 过程

仍然考虑上述同余方程，此时 $p\bmod 8=5$，那么令 $b\equiv (2a)^{(p-5)/8}\pmod p$ 和 $\mathrm{i}\equiv 2ab^2\pmod p$ 那么此时 $\mathrm{i}^2\equiv -1\pmod p$ 且 $ab(\mathrm{i}-1)\bmod p$ 为一个解。

#### 证明

$$
\begin{aligned}
\mathrm{i}^2&\equiv\left(2ab^2\right)^2&\pmod p\\
&\equiv \left(2a\cdot \left(2a\right)^{(p-5)/4}\right)^2&\pmod p\\
&\equiv \left(\left(2a\right)^{(p-1)/4}\right)^2&\pmod p\\
&\equiv \left(2a\right)^{(p-1)/2}&\pmod p\\
&\equiv -1&\pmod p
\end{aligned}
$$

其中 $2$ 在模形如 $8k+3$ 或 $8k+5$ 的素数时为二次非剩余，这由二次互反律给出，由于证明较复杂，读者可参考 [Wikipedia](https://en.wikipedia.org/wiki/Quadratic_reciprocity)。

那么

$$
\begin{aligned}
\left(ab(\mathrm{i}-1)\right)^2&\equiv a^2\cdot \left(2a\right)^{(p-5)/4}\cdot (-2\mathrm{i})&\pmod p\\
&\equiv a\cdot (-\mathrm{i})\cdot \left(2a\right)^{(p-1)/4}&\pmod p\\
&\equiv a&\pmod p
\end{aligned}
$$

得证。

## Cipolla 算法

### 定义

Cipolla 算法用于求解同余方程 $x^2\equiv a\pmod p$，其中 $p$ 为奇素数且 $a$ 为二次剩余。

### 过程

算法可描述为找到 $r$ 满足 $r^2-a$ 为二次非剩余，$(r-x)^{(p+1)/2}\bmod (x^2-(r^2-a))$ 为一个解。

在复数域 $\mathbb{C}$ 中，记 $\mathrm{i}^2=-1$ 后 $\mathbb{C}=\lbrace a_0+a_1\mathrm{i}\mid a_0,a_1\in\mathbb{R}\rbrace$。考虑令 $x^2+1\in\mathbb{R}\lbrack x\rbrack$ 和实系数多项式的集合 $\mathbb{R}\lbrack x\rbrack$ 对 $x^2+1$ 取模后的集合记作 $\mathbb{R}\lbrack x\rbrack /(x^2+1)$，那么集合中的元素都可以表示为 $a_0+a_1x$ 的形式，其中 $a_0,a_1\in\mathbb{R}$，又因为 $x^2\equiv -1\pmod{\left(x^2+1\right)}$，考虑多项式的运算可以发现 $\mathbb{R}\lbrack x\rbrack /(x^2+1)$ 中元素的运算与 $\mathbb{C}$ 中一致。

后文考虑对于系数属于有限域 $\mathbb{F}_p$ 的多项式 $\mathbb{F}_p\lbrack x\rbrack$ 和对 $x^2-(r^2-a)\in\mathbb{F}_p\lbrack x\rbrack$ 取模后的集合 $\mathbb{F}_p\lbrack x\rbrack /(x^2-(r^2-a))$ 中的运算。

**选择**  $r$：

若 $a\equiv 0\pmod p$ 那么 $r^2-a$ 为二次剩余，此时解显然为 $x\equiv 0\pmod p$。所以假设 $a\not\equiv 0\pmod p$。使得 $r^2-a$ 为非零二次剩余的选择有 $(p-3)/2$ 个，而使得 $r^2\equiv a\pmod p$ 的选择恰有两个，那么有 $(p-1)/2$ 种选择可以使得 $r^2-a$ 为二次非剩余，使用随机方法平均约两次可得 $r$。

### 证明

令 $f(x)=x^2-(r^2-a)\in\mathbb{F}_p\lbrack x\rbrack$ 和 $a_0+a_1x=(r-x)^{(p+1)/2}\bmod (x^2-(r^2-a))$ 那么有 $a_0^2\equiv a\pmod p$ 且 $a_1\equiv 0\pmod p$。

$$
\begin{aligned}
x^p&\equiv x(x^2)^{(p-1)/2}&\pmod{f(x)}\\
&\equiv x(r^2-a)^{(p-1)/2}&\pmod{f(x)}&\quad (\because{x^2\equiv r^2-a\pmod{f(x)}})\\
&\equiv -x&\pmod{f(x)}&\quad (\because{r^2-a}\text{ is quadratic non-residue})
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
(r-x)^{p}&\equiv r^p-x^p&\pmod{f(x)}\\
&\equiv r+x&\pmod{f(x)}
\end{aligned}
$$

所以

$$
\begin{aligned}
(a_0+a_1x)^2&=a_0^2+2a_0a_1x+a_1^2x^2\\
&\equiv (r-x)^{p+1}&\pmod{f(x)}\\
&\equiv (r-x)^p(r-x)&\pmod{f(x)}\\
&\equiv (r+x)(r-x)&\pmod{f(x)}\\
&\equiv r^2-x^2&\pmod{f(x)}\\
&\equiv a&\pmod{f(x)}
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

## Bostan–Mori 算法

该算法基于 Cipolla 算法，我们将问题转换为 [常系数齐次线性递推](../poly/linear-recurrence.md) 再应用 Bostan–Mori 算法。考虑另一种常见的 Cipolla 算法的描述为 $b=x^{\left(p+1\right)/2}\bmod{\left(x^2-tx+a\right)}$ 为满足 $b^2\equiv a\pmod{p}$ 的一个解[^ref3]，其中 $x^2-tx+a\in \mathbb{F}_p\lbrack x\rbrack$ 为不可约多项式。选取 $t$ 同样使用随机。证明过程略。参考文献[^ref4]中的算法我们可以发现问题可转化为求解形式幂级数的乘法逆元的某一项系数：

$$
b=\left\lbrack x^{(p+1)/2}\right\rbrack\dfrac{1}{1-tx+ax^2}
$$

且

$$
\left\lbrack x^n\right\rbrack\dfrac{k_0+k_1x}{1+k_2x+k_3x^2}=
\begin{cases}
\left\lbrack x^{(n-1)/2}\right\rbrack\dfrac{k_1-k_0k_2+k_1k_3x}{1+(2k_3-k_2^2)x+k_3^2x^2},&\text{if }n\bmod 2=1\\
\left\lbrack x^{n/2}\right\rbrack\dfrac{k_0+(k_0k_3-k_1k_2)x}{1+(2k_3-k_2^2)x+k_3^2x^2},&\text{else if }n\neq 0
\end{cases}
$$

而 $n=0$ 时显然有 $\left\lbrack x^0\right\rbrack\dfrac{k_0+k_1x}{1+k_2x+k_3x^2}=k_0$，该算法乘法次数相较于 Cipolla 算法更少，其他相关乘法次数较少的算法可见[^ref2]。

## Legendre 算法

### 定义

对于同余方程 $x^2\equiv a\pmod p$，其中 $p$ 为奇素数且 $a$ 为二次剩余。Legendre 算法可描述为找到 $r$ 满足 $r^2-a$ 为二次非剩余，令 $a_0+a_1x=(r-x)^{(p-1)/2}\bmod (x^2-a)$，那么 $a_0\equiv 0\pmod p$ 且 $a_1^{-2}\equiv a\pmod p$。

### 证明

考虑选择一个 $b$ 满足 $b^2\equiv a\pmod p$，那么 $(r-b)(r+b)=r^2-a$ 为二次非剩余，所以

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

## Tonelli–Shanks 算法

### 定义

Tonelli–Shanks 算法是基于离散对数求解同余方程 $x^2\equiv a\pmod p$ 的算法[^ref1]，其中 $p$ 为奇素数且 $a$ 为模 $p$ 的二次剩余。

令 $p-1=2^n\cdot m$ 其中 $m$ 为奇数。仍然使用随机方法寻找 $r\in\mathbb{F}_p$ 满足 $r$ 为二次非剩余。令 $g\equiv r^m\pmod p$ 且 $b\equiv a^{(m-1)/2}\pmod p$，那么存在整数 $e\in\lbrace 0,1,2,\dots ,2^n-1\rbrace$ 满足 $ab^2\equiv g^e\pmod p$。若 $a$ 为二次剩余，那么 $e$ 为偶数且 $\left(abg^{-e/2}\right)^2\equiv a\pmod p$。

### 证明

$$
\begin{aligned}
g^{2^n}&\equiv r^{2^n\cdot m}&\pmod p\\
&\equiv r^{p-1}&\pmod p\\
&\equiv 1&\pmod p
\end{aligned}
$$

而

$$
\begin{aligned}
g^{2^{n-1}}&\equiv r^{2^{n-1}\cdot m}&\pmod p\\
&\equiv r^{(p-1)/2}&\pmod p\\
&\equiv -1&\pmod p
\end{aligned}
$$

所以 $g$ 的阶为 $2^n$，又因为 $ab^2\equiv a^m\pmod p$ 是 $x^{2^n}\equiv 1\pmod p$ 的解，所以 $a^m$ 是 $g$ 的幂次，记 $a^m\equiv g^e\pmod p$。

若 $a$ 是二次剩余，那么

$$
\begin{aligned}
g^{2^{n-1}\cdot e}&\equiv (-1)^e&\pmod p\\
&\equiv a^{2^{n-1}\cdot m}&\pmod p\\
&\equiv a^{(p-1)/2}&\pmod p\\
&\equiv 1&\pmod p
\end{aligned}
$$

所以 $e$ 为偶数，而

$$
\begin{aligned}
\left(abg^{-e/2}\right)^2&\equiv a^2b^2g^{-e}&\pmod p\\
&\equiv a^{m+1}g^{-e}&\pmod p\\
&\equiv a&\pmod p
\end{aligned}
$$

剩下的问题是如何计算 $e$，Tonelli 和 Shanks 提出一次确定 $e$ 的一个比特。令 $e$ 在二进制下表示为 $e=e_0+2e_1+4e_2+\cdots$ 其中 $e_k\in\lbrace 0,1\rbrace$。

因为 $a$ 是二次剩余，所以开始时 $e_0=0$，然后计算 $e_1$ 然后 $e_2$ 等等，由以下公式给出

$$
\left(g^eg^{-(e\bmod 2^k)}\right)^{2^{n-1-k}}\equiv g^{2^{n-1}\cdot e_k}\equiv 
\begin{cases}
1\pmod p,&\text{if }e_k=0\\
-1\pmod p,&\text{else if }e_k=1
\end{cases}
$$

正确性显然。

## 习题

[【模板】二次剩余](https://www.luogu.com.cn/problem/P5491)

[「Timus 1132」Square Root](https://acm.timus.ru/problem.aspx?space=1&num=1132)

## 外部链接

-   <https://en.wikipedia.org/wiki/Quadratic_residue>
-   <https://en.wikipedia.org/wiki/Euler%27s_criterion>

## 参考文献

[^ref1]: Daniel. J. Bernstein. Faster Square Roots in Annoying Finite Fields.

[^ref2]: S. Müller, On the computation of square roots in finite fields, Design, Codes and Cryptography, Vol.31, pp. 301-312, 2004

[^ref3]: A. Menezes, P. van Oorschot and S. Vanstone. Handbook of Applied Cryptography, 1996.

[^ref4]: Alin Bostan, Ryuhei Mori.[A Simple and Fast Algorithm for Computing the N-th Term of a Linearly Recurrent Sequence](https://arxiv.org/abs/2008.08822).
