操纵 有限项/无限项 的多项式是 OI 数学中，尤其是生成函数中的重要内容。

以 [快速傅里叶变换](https://oi-wiki.org/math/poly/fft/) 为基石的多项式算法赋予了算法竞赛选手直接操纵生成函数的能力。

但需要指出，从大学数学分析的角度而言，如果将无限项的多项式（幂级数）  
单纯地看作一个函数，对它的许多处理并不是严谨的，例如

$$
\begin{aligned}
	f(x)=1+x+x^2+\cdots\\
	xf(x)=x+x^2+x^3+\cdots\\
	f(x)-xf(x)=1\\
	f(x)=\dfrac{1}{1-x}
\end{aligned}
$$

然而，从极限的角度看，我们有

$$
\begin{aligned}
1+x+x^2+\cdots=\lim_{n\rightarrow\infty}(1+x+x^2+\cdots+x^n)\\
=\lim_{n\rightarrow\infty}\dfrac{1-x^{n+1}}{1-x}=\dfrac{1}{1-x}\quad(-1<x<1)
\end{aligned}
$$

敛散性成为了我们处理幂级数的障碍，  
因此我们需要不依赖数学分析的，多项式及其运算的严格化定义，  
从而将这些处理建立在牢固的基础之上。

## 形式幂级数环

环、域及其衍生结构的一般定义详见 [群论简介](https://oi-wiki.org/math/group-theory/#_3)。

其实我们并不关心幂级数的取值、敛散性问题，而着重于系数组成的序列。

对于一般环 $R$，定义 $R$ 上的 **多项式环**（polynomial ring）$R[x]$，  
其中的每个元素 $f$ 称为 $R$ 上的 **多项式**（polynomial），可表示为

$$
f=\left<f_0,f_1,f_2,\cdots,f_n\right>\quad(f_0,f_1,f_2,\cdots,f_n\in R)
$$

换言之，我们将多项式直接定义为系数序列。也可以表示为

$$
f(x)=f_0+f_1x+f_2x^2+\cdots+f_nx^n
$$

此处我们认为 $x$ 只是一个 **形式符号**，一个对系数位置的标识符。

如果我们还允许无穷项的存在，即

$$
f(x)=f_0+f_1x+f_2x^2+\cdots
$$

则可得到 **形式幂级数环**（
    formal power series ring）$R[[x]]$，  
其中的每个元素 $f$ 称为 **形式幂级数**（formal power series），以下简称幂级数。

### 度数

对于有限项多项式

$$
f=f_0+f_1x+f_2x^2+\cdots+f_nx^n\quad(f_0,f_1,f_2,\cdots,f_n\in R\land(n=0\lor f_n\not =0))
$$

我们将 $n$ 称为 $f(x)$ 的 **度数**（degree），记为 $\deg f$。

除了 $f_k$ 以外，我们还使用 $[x^k]f(x)$ 表示 $f(x)$ 在 $x^k$ 处系数的值，例如

$$
[x^2](1-x)^3=3
$$

### 加法

我们直接将形式幂级数的加法定义为系数逐项相加

$$
f+g=\left<f_0+g_0,f_1+g_1,f_2+g_2,\cdots\right>
$$

我们希望新定义的多项式加法满足原本初等的定义中的大部分运算性质。  
我们已经知道了环 $R$ 上的加法满足以下性质：

- 交换律：对于 $R$ 上任意的 $a,b$，$a+b=b+a$
- 结合律：对于 $R$ 上任意的 $a,b,c$，$(a+b)+c=a+(b+c)$
-   单位元：$R$ 上存在一个元素 $0$（注意不是我们一般所熟知的自然数 $0$），  
    使得对于 $R$ 上任意元素 $a$，总有 $a+0=0+a=a$，它被称为加法的单位元。
-   逆元：对于 $R$ 上任意元素 $a$，总存在 $R$ 中的元素 $-a$，  
    使得 $(-a)+a=a+(-a)=0$，它被称为 $a$ 的加法逆元。

它们相应地验证了 $R[[x]]$ 上多项式加法的性质：

-   交换律：由 $R$ 上加法的交换律得到

    $$
    \begin{aligned}
       f+g=\left<f_0+g_0,f_1+g_1,f_2+g_2,\cdots\right>\\
    	=\left<g_0+f_0,g_1+f_1,g_2+f_2,\cdots\right>=g+f
    \end{aligned}
    $$

-   结合律：由 $R$ 上加法的结合律得到

    $$
    \begin{aligned}
      (f+g)+h=\left<(f_0+g_0)+h_0,(f_1+g_1)+h_1,(f_2+g_2)+h_2,\cdots\right>\\
      =\left<f_0+(g_0+h_0),f_1+(g_1+h_1),f_2+(g_2+h_2),\cdots\right>=f+(g+h)
    \end{aligned}
    $$

-   单位元：我们可以知道 $R[[x]]$ 上加法的单位元为

    $$
    0=\left<0,0,0,\cdots\right>
    $$

    注意等式两边 $0$ 的意义不同，一个是 $R[[x]]$ 上的单位元，一个是 $R$ 上的单位元。

-   逆元：我们可以知道幂级数 $f$ 的加法逆元为

    $$
    -f=\left<-f_0,-f_1,-f_2,\cdots\right>
    $$

接下来定义的其他运算也是类似的，读者可以自行验证。

### 乘法

$R[[x]]$ 中元素 $f,g$ 的乘法被定义为

$$
\left(\sum_{k=0}^\infty f_kx^k\right)\left(\sum_{k=0}^\infty g_kx^k\right)=\sum_{n=0}^{\infty}\left(\sum_{k=0}^nf_kg_{n-k}\right)x^n
$$

形式幂级数乘法满足结合律，关于加法满足分配律。  
若 $R$ 为交换环或幺环，形式幂级数乘法相应的有交换律和单位元。

若 $R$ 上存在 $2^n$ 次单位根，[快速傅里叶变换](https://oi-wiki.org/math/poly/fft/) 允许我们在  
 $O(n2^n)$ 而不是 $O(2^{2n})$ 的时间内计算两个 $2^n$ 次多项式的乘积。

### 复合

定义 $R[[x]]$ 中元素 $f$ 的乘方为

$$
f^1=f,f^k=f^{k-1}\times f
$$

在此基础上，定义 $R[[x]]$ 中元素 $f,g$ 的复合为

$$
(f\circ g)(x)=f(g(x))=f_0+\sum_{k=1}^{\infty}f_kg^k(x)
$$

我们规定 $f\circ g$ 存在当且仅当 $f$ 为有限项或 $g_0=0$，这样就不涉及 $R$ 上的极限了。

对于所有有限项或满足常数项为 $0$ 的多项式的复合，$\circ$ 满足结合律，不满足交换律。  
$R$ 为幺环时 $\circ$ 存在单位元 $1\times x$。

FFT 可行时，有限项多项式的复合有 $O((n\log n)^{1.5})$ 的算法，但此算法常数较大，  
实战中往往 $O(n^2)$ 的一种“分块 FFT”算法具有更好的表现。

### 导数

尽管一般环甚至未必存在极限，我们依然可以定义形式幂级数的导数为

$$
\left(\sum_{k=0}^{\infty}f_kx^k\right)'=\sum_{k=1}^{\infty}kf_kx^{k-1}
$$

其中

$$
kf_k=\underbrace{f_k+f_k+\cdots+f_k}_{k \text{个} f_k}
$$

基本求导法则——加法法则、乘法法则、链式法则（复合允许的情况下）依然是正确的。

如果 $R$ 上允许作除法，同样可以类似定义形式幂级数的积分。

## 形式幂级数的复杂运算

以下运算假定都在复数域 $\mathbb{C}$ 上的形式幂级数环 $\mathbb{C}[[x]]$ 上进行。

### 乘法逆元

由最开始的例子

$$
\dfrac{1}{1-x}=1+x+x^2+\cdots
$$

可以知道，多项式的倒数是能展开为无穷级数的。

因此定义：对于形式幂级数 $f$，若 $f_0\not=0$，其 **乘法逆元**  
（multiplicative inversion）$f^{-1}$ 为另一形式幂级数，满足

$$
f\times f^{-1}=f^{-1}\times f=1
$$

用形式幂级数乘法定义展开该式，可得 $f^{-1}$ 系数的递推式

$$
f^{-1}_0=\dfrac{1}{f_0},f^{-1}_n=\dfrac{-1}{f_0}\sum_{k=0}^{n-1}f^{-1}_kf_{n-k}
$$

直接用递推式计算前 $n$ 项是 $O(n^2)$ 的，[运用 FFT](https://oi-wiki.org/math/poly/inv/) 可得到 $O(n\log n)$ 的算法。

### 与基本初等函数的复合

形式幂级数与幂函数的复合（开根）由其与广义二项式定理的复合定义

$$
(1+f(x))^{r}=\sum_{k=0}^\infty\dbinom{r}{k}f^k(x)
$$

其中 $\dbinom{r}{k}=\dfrac{r^{\underline{k}}}{k!}=\displaystyle\prod_{j=0}^{k-1}\dfrac{r-j}{j+1}$ 为广义二项式系数。

形式幂级数的指数和对数直接由其与麦克劳林级数的复合定义

$$
\exp f(x)=\sum_{k=0}^\infty\dfrac{f^k(x)}{k!}
$$

$$
\ln{(1 - f(x))} = -\sum_{i = 1}^{+\infty} \frac{f^{i}(x)}{i}
$$

$$
\ln{(1 + f(x))} = \sum_{i = 1}^{+\infty} \frac{(-1)^{i - 1}f^{i}(x)}{i}
$$

需要注意的是，由之前形式幂级数复合的定义可得，以上复合存在均需要 $f_0=0$。

开根、指数和对数的大部分运算性质依然成立。  
三角函数、反三角函数同理。

### 复合逆

**复合逆**（compound inversion）即反函数概念在形式幂级数环上的推广。

对于满足 $f_0=0$ 且 $f_1\not=0$ 的形式幂级数 $f$，  
其复合逆为满足 $g(f(x))=f(g(x))=x$ 的形式幂级数 $g$。  
由拉格朗日反演可得对于任意整数 $n,k$ 有

$$
n[x^n]f^k=k[x^{-k}]g^{-n}
$$

注意此处我们允许有限个负数次项的存在，即 **形式洛朗级数**（formal Laurent series）。

## 多项式的复杂运算

以下运算假定都在一般 **域**  $P$ 上的多项式环 $P[x]$ 上进行。

### 带余除法

多项式的带余除法又称大除法。

对于多项式 $f(x),g(x)$ 且 $g(x)\not=0$，存在 **唯一** 的 $Q(x),R(x)$ 满足

$$
f(x)=Q(x)g(x)+R(x),\deg R<\deg g
$$

当 $\deg f\ge \deg g$ 时有 $\deg Q=\deg f-\deg g$，否则有 $Q(x)=0$。

我们称 $Q(x)$ 为 $g(x)$ 除 $f(x)$ 的 **商**（quotient），  
$R(x)$ 为 $g(x)$ 除 $f(x)$ 的 **余数**（remainder）。亦可记作

$$
f(x) \equiv R(x) \pmod{g(x)}
$$

大除法是可以用纸笔手工计算的，跟数的除法类似。

### 多点求值和插值

从函数的角度而言，$n+1$ 个点可唯一确定一个 $n$ 次多项式。

**多项式的多点求值**（multi-point evaluation）即给出一个多项式 $f(x)$   
和 $P$ 中 $n$ 个点 $x_{1}, x_{2}, \dots, x_{n}$，求

$$
f(x_{1}), f(x_{2}),\cdots,f(x_{n})
$$

**多项式的插值**（interpolation）即给出 $n + 1$ 个点

$$
(x_{0}, y_{0}), (x_{1}, y_{1}),\cdots,(x_{n}, y_{n})
$$

求一个 $n$ 次多项式 $f(x)$ 使得这 $n + 1$ 个点都在 $f(x)$ 上。

### 因式分解、欧几里得和模多项式意义下乘法逆元

初等数论中的许多结论可以推广到多项式上。

复数域上，由代数基本定理可得，对于 $n$ 次多项式 $f$，方程

$$
f(x)=0
$$

有且仅有 $n$ 个解（重根按重数计）。

于是 $f(x)$ 在复数域内可唯一因式分解为如下形式

$$
a(x-x_1)^{c_1}(x-x_2)^{c_2}\cdots(x-x_m)^{c_m}
$$

$$
c_1+c_2+\cdots+c_m=n,x_1,x_2,\cdots,x_m \text{ 互不相同}
$$

此时类比数的最大公因数，可得多项式的 [**最大公因式**](https://oi-wiki.org/math/number-theory/gcd/)  
（the greatest common divisor,gcd）。其可用欧几里得算法求解

$$
\gcd(f,0)=f,\gcd(f,g)=\gcd(g,f\bmod g)
$$

该性质可以推广到较为一般的情况：

> 对于任意域 $P$ 上的多项式环 $P[x]$，  
> 多项式均可唯一因式分解，且可用欧几里得算法计算最大公因式。

需要注意的是，对于一般环上的多项式该结论未必成立。

欧几里得算法成立时，可用扩展欧几里得给出不定方程

$$
f(x)P(x)+g(x)Q(x)=\gcd(f(x),g(x))
$$

的一组特解 $(P(x),Q(x))$，并用 [裴蜀定理](https://oi-wiki.org/math/number-theory/bezouts/) 判断不定方程

$$
f(x)P(x)+g(x)Q(x)=h(x)
$$

的可解性。

[HALF-GCD](https://loj.ac/p/172) 允许我们在 $O(n\log^2 n)$ 时间内计算多项式欧几里得。

类比数在模意义下的乘法逆元，可以得到模多项式意义下的乘法逆元：  
对于多项式 $f(x),g(x)$，$f(x)$ 在模 $g(x)$ 意义下的乘法逆元定义为满足

$$
f(x)P(x)\equiv 1\pmod{g(x)}
$$

的多项式 $P(x)$。这等价于求解

$$
f(x)P(x)+g(x)Q(x)=1
$$

的一组特解 $(P(x),Q(x))$。

于是可得，当多项式欧几里得允许时，$P(x)$ 存在当且仅当 $\gcd(f,g)=1$。

## 参考资料与拓展阅读

- [**Picks's Blog**](https://picks.logdown.com)
- [**Miskcoo's Space**](https://blog.miskcoo.com)
- [**Polynomial ring - Wikipedia**](https://en.wikipedia.org/wiki/Polynomial_ring)
- [**Formal power series - Wikipedia**](https://en.wikipedia.org/wiki/Formal_power_series#The_ring_of_formal_power_series)
- 《信息学竞赛中的生成函数计算理论框架》
