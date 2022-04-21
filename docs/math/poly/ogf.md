author: sshwy

序列 $a$ 的普通生成函数（ordinary generating function，OGF）定义为形式幂级数：

$$
F(x)=\sum_{n}a_n x^n
$$

$a$ 既可以是有穷序列，也可以是无穷序列。常见的例子（假设 $a$ 以 $0$ 为起点）：

1. 序列 $a=\langle 1,2,3\rangle$ 的普通生成函数是 $1+2x+3x^2$。
2. 序列 $a=\langle 1,1,1,\cdots\rangle$ 的普通生成函数是 $\sum_{n\ge 0}x^n$。
3. 序列 $a=\langle 1,2,4,8,16,\cdots\rangle$ 的生成函数是 $\sum_{n\ge 0}2^nx^n$。
4. 序列 $a=\langle 1,3,5,7,9,\cdots\rangle$ 的生成函数是 $\sum_{n\ge 0}(2n+1)x^n$。

换句话说，如果序列 $a$ 有通项公式，那么它的普通生成函数的系数就是通项公式。

## 基本运算

考虑两个序列 $a,b$ 的普通生成函数，分别为 $F(x),G(x)$。那么有

$$
F(x)\pm G(x)=\sum_n (a_n\pm b_n)x^n
$$

因此 $F(x)\pm G(x)$ 是序列 $\langle a_n\pm b_n\rangle$ 的普通生成函数。

考虑乘法运算，也就是卷积：

$$
F(x)G(x)=\sum_n x^n \sum_{i=0}^na_ib_{n-i}
$$

因此 $F(x)G(x)$ 是序列 $\langle \sum_{i=0}^n a_ib_{n-i} \rangle$ 的普通生成函数。

## 封闭形式

在运用生成函数的过程中，我们不会一直使用形式幂级数的形式，而会适时地转化为封闭形式以更好地化简。

例如 $\langle 1,1,1,\cdots\rangle$ 的普通生成函数 $F(x)=\sum_{n\ge 0}x^n$，我们可以发现

$$
F(x)x+1=F(x)
$$

那么解这个方程得到

$$
F(x)=\frac{1}{1-x}
$$

这就是 $\sum_{n\ge 0}x^n$ 的封闭形式。

考虑等比数列 $\langle 1,p,p^2,p^3,p^4,\cdots\rangle$ 的生成函数 $F(x)=\sum_{n\ge 0}p^nx^n$，有

$$
\begin{aligned}F(x)px+1 &=F(x)\\F(x) &=\frac{1}{1-px}\end{aligned}
$$

等比数列的封闭形式与展开形式是常用的变换手段。

???+note "小练习"
    请求出下列数列的普通生成函数（形式幂级数形式和封闭形式）。难度是循序渐进的。
    
    1. $a=\langle 0,1,1,1,1,\cdots\rangle$。
    2. $a=\langle 1,0,1,0,1,\cdots \rangle$。
    3. $a=\langle 1,2,3,4,\cdots \rangle$。
    4. $a_n=\binom{m}{n}$（$m$ 是常数，$n\ge 0$）。
    5. $a_n=\binom{m+n}{n}$（$m$ 是常数，$n\ge 0$）。

??? note "答案"
    第一个：
    
    $$
    F(x)=\sum_{n\ge 1}x^n=\dfrac{x}{1-x}
    $$
    
    第二个：
    
    $$
    \begin{aligned}
    F(x)&=\sum_{n\ge 0}x^{2n}\\
    &=\sum_{n\ge 0}(x^2)^{n}\\
    &=\frac{1}{1-x^2}
    \end{aligned}
    $$
    
    第三个（求导）：
    
    $$
    \begin{aligned}F(x)&=\sum_{n\ge 0}(n+1)x^n\\&=\sum_{n\ge 1}nx^{n-1}\\&=\sum_{n\ge 0}(x^n)'\\&=\left(\frac{1}{1-x}\right)'\\&=\frac{1}{(1-x)^2}\end{aligned}
    $$
    
    第四个（二项式定理）：
    
    $$
    F(x)=\sum_{n\ge 0}\binom{m}{n}x^n=(1+x)^m
    $$
    
    第五个：
    
    $$
    F(x)=\sum_{n\ge 0}\binom{m+n}{n}x^n=\frac{1}{(1-x)^{m+1}}
    $$
    
    可以使用归纳法证明。
    
    首先当 $m=0$ 时，有 $F(x)=\dfrac{1}{1-x}$。
    
    而当 $m>0$ 时，有
    
    $$
    \begin{aligned}
    \frac{1}{(1-x)^{m+1}}
    &=\frac{1}{(1-x)^m}\frac{1}{1-x}\\
    &=\left(\sum_{n\ge 0}\binom{m+n-1}{n}x^n \right)\left(\sum_{n\ge 0}x^n \right)\\
    &=\sum_{n\ge 0} x^n\sum_{i=0}^n \binom{m+i-1}{i}\\
    &=\sum_{n\ge 0}\binom{m+n}{n}x^n
    \end{aligned}
    $$

## 斐波那契数列的生成函数

接下来我们来推导斐波那契数列的生成函数。

斐波那契数列定义为 $a_0=0,a_1=1,a_n=a_{n-1}+a_{n-2}\;(n>1)$。设它的普通生成函数是 $F(x)$，那么根据它的递推式，我们可以类似地列出关于 $F(x)$ 的方程：

$$
F(x)=xF(x)+x^2F(x)-a_0x+a_1x+a_0
$$

那么解得

$$
F(x)=\frac{x}{1-x-x^2}
$$

那么接下来的问题是，如何求出它的展开形式？

### 展开方式一

不妨将 $x+x^2$ 当作一个整体，那么可以得到

$$
\begin{aligned}
F(x)&=\frac{x}{1-(x+x^2)}\\
&=\sum_{n\ge 0}(x+x^2)^n\\
&=\sum_{n\ge 0}\sum_{i=0}^n\binom{n}{i}x^{2i}x^{n-i}\\
&=\sum_{n\ge 0}\sum_{i=0}^n\binom{n}{i}x^{n+i}\\
&=\sum_{n\ge 0}x^n\sum_{i=0}^n\binom{n-i}{i}
\end{aligned}
$$

我们得到了 $a_n$ 的通项公式，但那并不是我们熟知的有关黄金分割比的形式。

### 展开方式二

考虑求解一个待定系数的方程：

$$
\frac{A}{1-ax}+\frac{B}{1-bx}= \frac{x}{1-x-x^2}
$$

通分得到

$$
\frac{A-Abx+B-aBx}{(1-ax)(1-bx)} = \frac{x}{1-x-x^2}
$$

待定项系数相等，我们得到

$$
\begin{cases}
A+B=0\\
-Ab-aB=1\\
a+b=1\\
ab=-1
\end{cases}
$$

解得

$$
\begin{cases}
A=\frac{1}{\sqrt{5}}\\
B=-\frac{1}{\sqrt{5}}\\
a=\frac{1+\sqrt{5}}{2}\\
b=\frac{1-\sqrt{5}}{2}
\end{cases}
$$

那么我们根据等比数列的展开式，就可以得到斐波那契数列的通项公式：

$$
\frac{x}{1-x-x^2}=\sum_{n\ge 0}x^n
\frac{1}{\sqrt{5}}\left( \left(\frac{1+\sqrt{5}}{2}\right)^n-\left(\frac{1-\sqrt{5}}{2}\right)^n \right)
$$

这也被称为斐波那契数列的另一个封闭形式（$\frac{x}{1-x-x^2}$ 是一个封闭形式）。

对于任意多项式 $P(x),Q(x)$，生成函数 $\dfrac{P(x)}{Q(x)}$ 的展开式都可以使用上述方法求出。在实际运用的过程中，我们往往先求出 $Q(x)$ 的根，把分母表示为 $\prod (1-p_ix)^{d_i}$ 的形式，然后再求分子。

## 牛顿二项式定理

我们重新定义组合数的运算：

$$
\binom{r}{k}=\frac{r^{\underline{k}}}{k!}\quad(r\in\mathbf{C},k\in\mathbf{N})
$$

注意 $r$ 的范围是复数域。在这种情况下。对于 $\alpha\in\mathbf{C}$，有

$$
(1+x)^{\alpha}=\sum_{n\ge 0}\binom{\alpha}{n}x^n
$$

二项式定理其实是牛顿二项式定理的一个特殊情况。

## 卡特兰数的生成函数

卡特兰数的递推式为

$$
H_n=\sum_{i=0}^{n-1}H_{i}H_{n-i-1} \quad (n\ge 2)
$$

其中 $H_0=1,H_1=1$。设它的普通生成函数为 $H(x)$。

我们发现卡特兰数的递推式与卷积的形式很相似，因此我们用卷积来构造关于 $H(x)$ 的方程：

$$
\begin{aligned}
H(x)&=\sum_{n\ge 0}H_nx^n\\
&=1+\sum_{n\ge 1}\sum_{i=0}^{n-1}H_ix^iH_{n-i-1}x^{n-i-1}x\\
&=1+x\sum_{i\ge 0}H_{i}x^i\sum_{n\ge 0}H_{n}x^{n}\\
&=1+xH^2(x)
\end{aligned}
$$

解得

$$
H(x)=\frac{1\pm \sqrt{1-4x}}{2x}
$$

那么这就产生了一个问题：我们应该取哪一个根呢？我们将其分子有理化：

$$
H(x)=\frac{2}{1\mp \sqrt{1-4x}}
$$

代入 $x=0$，我们得到的是 $H(x)$ 的常数项，也就是 $H_0$。当 $H(x)=\dfrac{2}{1+\sqrt{1-4x}}$ 的时候有 $H(0)=1$，满足要求。而另一个解会出现分母为 $0$ 的情况（不收敛），舍弃。

因此我们得到了卡特兰数生成函数的封闭形式：

$$
H(x)=\frac{1- \sqrt{1-4x}}{2x}
$$

接下来我们要将其展开。但注意到它的分母不是斐波那契数列那样的多项式形式，因此不方便套用等比数列的展开形式。在这里我们需要使用牛顿二项式定理。我们来先展开 $\sqrt{1-4x}$：

$$
\begin{aligned}
(1-4x)^{\frac{1}{2}}
&=\sum_{n\ge 0}\binom{\frac{1}{2}}{n}(-4x)^n\\
&=1+\sum_{n\ge 1}\frac{\left(\frac{1}{2}\right)^{\underline{n}}}{n!}(-4x)^n
\end{aligned} \tag{1}
$$

注意到

$$
\begin{aligned}
\left(\frac{1}{2}\right)^{\underline{n}}
&=\frac{1}{2}\frac{-1}{2}\frac{-3}{2}\cdots\frac{-(2n-3)}{2}\\
&=\frac{(-1)^{n-1}(2n-3)!!}{2^n}\\
&=\frac{(-1)^{n-1}(2n-2)!}{2^n(2n-2)!!}\\
&=\frac{(-1)^{n-1}(2n-2)!}{2^{2n-1}(n-1)!}
\end{aligned}
$$

这里使用了双阶乘的化简技巧。那么带回 $(1)$ 得到

$$
\begin{aligned}
(1-4x)^{\frac{1}{2}}
&=1+\sum_{n\ge 1}\frac{(-1)^{n-1}(2n-2)!}{2^{2n-1}(n-1)!n!}(-4x)^n\\
&=1-\sum_{n\ge 1}\frac{(2n-2)!}{(n-1)!n!}2x^n\\
&=1-\sum_{n\ge 1}\binom{2n-1}{n}\frac{1}{(2n-1)}2x^n
\end{aligned}
$$

带回原式得到

$$
\begin{aligned}
H(x)&=\frac{1- \sqrt{1-4x}}{2x}\\
&=\frac{1}{2x}\sum_{n\ge 1}\binom{2n-1}{n}\frac{1}{(2n-1)}2x^n\\
&=\sum_{n\ge 1}\binom{2n-1}{n}\frac{1}{(2n-1)}x^{n-1}\\
&=\sum_{n\ge 0}\binom{2n+1}{n+1}\frac{1}{(2n+1)}x^{n}\\
&=\sum_{n\ge 0}\binom{2n}{n}\frac{1}{n+1}x^{n}\\
\end{aligned}
$$

这样我们就得到了卡特兰数的通项公式。

## 应用

接下来给出一些例题，来介绍生成函数在 OI 中的具体应用。

### 食物

???+note "[食物](https://darkbzoj.tk/problem/3028)"
    在许多不同种类的食物中选出 $n$ 个，每种食物的限制如下：
    
    1. 承德汉堡：偶数个
    2. 可乐：0 个或 1 个
    3. 鸡腿：0 个，1 个或 2 个
    4. 蜜桃多：奇数个
    5. 鸡块：4 的倍数个
    6. 包子：0 个，1 个，2 个或 3 个
    7. 土豆片炒肉：不超过一个。
    8. 面包：3 的倍数个
    
    每种食物都是以“个”为单位，只要总数加起来是 $n$ 就算一种方案。对于给出的 $n$ 你需要计算出方案数，对 $10007$ 取模。

这是一道经典的生成函数题。对于一种食物，我们可以设 $a_n$ 表示这种食物选 $n$ 个的方案数，并求出它的生成函数。而两种食物一共选 $n$ 个的方案数的生成函数，就是它们生成函数的卷积。多种食物选 $n$ 个的方案数的生成函数也是它们生成函数的卷积。

在理解了方案数可以用卷积表示以后，我们就可以构造生成函数（标号对应题目中食物的标号）：

1. $\displaystyle\sum_{n\ge 0}x^{2n}=\dfrac{1}{1-x^2}$。
2. $1+x$。
3. $1+x+x^2=\dfrac{1-x^3}{1-x}$。
4. $\dfrac{x}{1-x^2}$。
5. $\displaystyle \sum_{n\ge 0}x^{4n}=\dfrac{1}{1-x^4}$。
6. $1+x+x^2+x^3=\dfrac{1-x^4}{1-x}$。
7. $1+x$。
8. $\dfrac{1}{1-x^3}$。

那么全部乘起来，得到答案的生成函数：

$$
F(x)=\frac{(1+x)(1-x^3)x(1-x^4)(1+x)}{(1-x^2)(1-x)(1-x^2)(1-x^4)(1-x)(1-x^3)}
=\frac{x}{(1-x)^4}
$$

然后将它转化为展开形式（使用封闭形式练习中第五个练习）：

$$
F(x)=\sum_{n\ge 1}\binom{n+2}{n-1}x^n
$$

因此答案就是 $\dbinom{n+2}{n-1}=\dbinom{n+2}{3}$。

### Sweet

???+note "[「CEOI2004」Sweet](https://darkbzoj.tk/problem/3027)"
    有 $n$ 堆糖果。不同的堆里糖果的种类不同（即同一个堆里的糖果种类是相同的，不同的堆里的糖果的种类是不同的）。第 $i$ 个堆里有 $m_i$ 个糖果。现在要吃掉至少 $a$ 个糖果，但不超过 $b$ 个。求有多少种方案。
    
    两种方案不同当且仅当吃的个数不同，或者吃的糖果中，某一种糖果的个数在两个方案中不同。
    
    $n\le 10,0\le a\le b\le 10^7,m_i\le 10^6$。

在第 $i$ 堆吃 $j$ 个糖果的方案数（显然为 1）的生成函数为

$$
F_i(x)=\sum_{j=0}^{m_i}x^j=\frac{1-x^{m_i+1}}{1-x}
$$

因此总共吃 $i$ 个糖果的方案数的生成函数就是

$$
G(x)=\prod_{i=1}^n F_i(x)=(1-x)^{-n}\prod_{i=1}^n(1-x^{m_i+1})
$$

现在我们要求的是 $\sum_{i=a}^b[x^i]G(x)$。

由于 $n\le 10$，因此我们可以暴力展开 $\prod_{i=1}^n(1-x^{m_i+1})$（最多只有 $2^n$ 项）。

然后对 $(1-x)^{-n}$ 使用牛顿二项式定理：

$$
\begin{aligned}
(1-x)^{-n}
&=\sum_{i\ge 0}\binom{-n}{i}(-x)^i\\
&=\sum_{i\ge 0}\binom{n-1+i}{i}x^i
\end{aligned}
$$

我们枚举 $\prod_{i=1}^n(1-x^{m_i+1})$ 中 $x^k$ 项的系数，假设为 $c_k$。那么它和 $(1-x)^{-n}$ 相乘后，对答案的贡献就是

$$
c_k\sum_{i=a-k}^{b-k}\binom{n-1+i}{i}=c_k\left(
\binom{n+b-k}{b-k}-
\binom{n+a-k-1}{a-k-1}
\right)
$$

这样就可以 $O(b)$ 地求出答案了。

时间复杂度 $O(2^n+b)$。
