操纵 有限项/无限项 的多项式是 OI 数学中，尤其是生成函数中的重要内容。

需要指出，从大学数学分析的角度而言，将无限项的多项式（幂级数）  
单纯地看作一个函数将导致敛散性的问题，例如

$$
\begin{aligned}
1+x+x^2+\cdots=\lim_{n\rightarrow\infty}(1+x+x^2+\cdots+x^n)\\
=\lim_{n\rightarrow\infty}\dfrac{1-x^{n+1}}{1-x}=\dfrac{1}{1-x}\quad(-1<x<1)
\end{aligned}$$

本部分将给出不基于数学分析的，多项式及其运算的严格化定义，  
并给出其基于快速傅里叶变换的快速计算方法。

## 形式幂级数环

环的一般定义详见 [群论简介](https://oi-wiki.org/math/group-theory/#_3)。

对于一般环 $R$，定义 $R$ 上的 **多项式环**（Polynomial ring）$R[x]$ 是一个 $R$ 上的自由模，  
其中的每个元素 $f$ 称为 $R$ 上的 **多项式**（Polynomial），可表示为  

$f=\left<f_0,f_1,f_2,\cdots,f_n\right>\quad(f_0,f_1,f_2,\cdots,f_n\in R\land(n=0\lor f_n\not =0))$

或

$f(x)=f_0+f_1x+f_2x^2+\cdots+f_nx^n$

其中 $n$ 被称为 $f(x)$ 的 **度数**（degree），记为 $\deg f$。

此处我们认为 $x$ 只是一个形式符号，一个对系数位置的标识符。

如果我们还允许无穷项的存在，即

$f(x)=f_0+f_1x+f_2x^2+\cdots$

则可得到 **形式幂级数环**（
    Formal power series ring）$R[[x]]$，  
其中的每个元素 $f$ 称为 **形式幂级数**（Formal power series），以下简称幂级数。

### 加法

对于 $R[[x]]$ 中的元素 $f,g$，我们定义

$f+g=\left<f_0+g_0,f_1+g_1,f_2+g_2,\cdots\right>$

也即

$\displaystyle\sum_{k=0}^{\infty}f_kx^k+\sum_{k=0}^\infty g_kx^k=\sum_{k=0}^{\infty}(f_k+g_k)x^k$

并验证 $(R[[x]],+)$ 的交换群性质——封闭性、交换律、结合律、单位元、逆元。

### 乘法

$R[[x]]$ 中元素 $f,g$ 的乘法被定义为
$$

\\left(\\sum*{k=0}^\\infty f_kx^k\\right)\\left(\\sum*{k=0}^\\infty g*kx^k\\right)=\\sum*{n=0}^{\\infty}\\left(\\sum*{k=0}^nf_kg*{n-k}\\right)x^n

$$
我们可以验证形式幂级数乘法的结合律及其关于加法的分配律。

若 $R$ 为交换环或幺环，也能相应地验证形式幂级数乘法的交换律和单位元性质。

若 $R$ 上存在 $2^n$ 次单位根，[快速傅里叶变换](https://oi-wiki.org/math/poly/fft/) 允许我们在  
 $O(n2^n)$ 而不是 $O(2^{2n})$ 的时间内计算两个 $2^n$ 次多项式的乘积。

### 复合

定义 $R[[x]]$ 中元素 $f$ 的乘方为

$f^1=f,f^k=f^{k-1}\times f$

在此基础上，定义 $R[[x]]$ 中元素 $f,g$ 的复合为
$$

(f\\circ g)(x)=f(g(x))=f*0+\\sum*{k=1}^{\\infty}f_kg^k(x)

$$
当 $f$ 为有限项多项式或 $g_0=0$ 时，该运算是良定义的，不涉及 $R$ 上的极限。

可以证明 $\circ$ 满足结合律，且 $R$ 为幺半群时单位元为 $1\times x$。

$R$ 为素数域时，有限项多项式的复合有 $O((n\log n)^{1.5})$ 的算法，但此算法常数较大，  
实战中往往 $O(n^2)$ 的一种“分块 FFT”算法具有更好的表现。

### 导数

尽管一般环上无拓扑结构更无完备性，我们依然可以定义形式幂级数的导数为
$$

\\left(\\sum*{k=0}^{\\infty}f_kx^k\\right)'=\\sum*{k=1}^{\\infty}kf_kx^{k-1}

$$
其中 $kf_k=\underbrace{f_k+f_k+\cdots+f_k}_{k \text{个} f_k}$

并验证加法法则、乘法法则、链式法则的正确性。

## 形式幂级数的复杂运算

以下运算假定都在复数域 $\mathbb{C}$ 上的形式幂级数环 $\mathbb{C}[[x]]$ 上进行。

### 乘法逆元

对于形式幂级数 $f$，若 $f_0\not=0$，定义其 **乘法逆元**（Multiplicative Inversion）$f^{-1}$ 为另一形式幂级数，满足

$f\times f^{-1}=f^{-1}\times f=1$

用形式幂级数乘法定义展开该式，可得 $f^{-1}$ 系数的递推式
$$

f^{-1}*0=\\dfrac{1}{f_0},f^{-1}\_n=\\dfrac{-1}{f_0}\\sum*{k=0}^{n-1}f^{-1}*kf*{n-k}

$$
直接用递推式计算是 $\mathcal{O}(n^2)$ 的，[运用 FFT](https://oi-wiki.org/math/poly/inv/) 可得到 $O(n\log n)$ 的算法。

### 与基本初等函数的复合

形式幂级数与幂函数的复合（开根）由其与广义二项式定理的复合定义
$$

(1+f(x))^{r}=\\sum\_{k=0}^\\infty\\dbinom{r}{k}f^k(x)

$$
其中 $\dbinom{r}{k}=\dfrac{r^{\underline{k}}}{k!}=\displaystyle\prod_{j=0}^{k-1}\dfrac{r-j}{j+1}$ 为广义二项式系数。

形式幂级数的指数和对数直接由其与麦克劳林级数的复合定义
$$

\\begin{aligned}
\\exp f(x)=\\sum*{k=0}^\\infty\\dfrac{f^k(x)}{k!}\\\\ln{(1 - f(x))} = -\\sum*{i = 1}^{+\\infty} \\frac{f^{i}(x)}{i}\\\\ln{(1 + f(x))} = \\sum\_{i = 1}^{+\\infty} \\frac{(-1)^{i - 1}f^{i}(x)}{i}
\\end{aligned}

$$
套用定义可验证开根、指数和对数的大部分运算性质。  
三角函数、反三角函数同理。

### 复合逆

对于满足 $f_0=0$ 且 $f_1\not=0$ 的形式幂级数 $f$，  
其 **复合逆**（Compound inverse）为满足 $g(f(x))=f(g(x))=x$ 的形式幂级数 $g$。  
由拉格朗日反演可得对于任意整数 $n,k$ 有

$n[x^n]f^k=k[x^{-k}]g^{-n}$

注意此处我们允许有限个负数次项的存在，即 **形式洛朗级数**（Formal Laurent series）。

## 多项式的复杂运算

以下运算假定都在复数域 $\mathbb{C}$ 上的多项式环 $\mathbb{C}[x]$ 上进行。

### 带余除法

多项式的带余除法又称大除法。

对于多项式 $f(x),g(x)$，存在 **唯一** 的 $Q(x),R(x)$ 满足

$f(x)=Q(x)g(x)+R(x),\deg R<\deg g$

当 $\deg f\ge \deg g$ 时有 $\deg Q=\deg f-\deg g$，否则有 $Q(x)=0$。

我们称 $Q(x)$ 为 $g(x)$ 除 $f(x)$ 的 **商**（Quotient），$R(x)$ 为 $g(x)$ 除 $f(x)$ 的 **余数**（Remainder）。亦可记作

$f(x) \equiv R(x) \pmod{g(x)}$

### 多项式的多点求值和插值

**多项式的多点求值**（Multi-point evaluation）即给出一个多项式 $f(x)$ 和 $n$ 个点 $x_{1}, x_{2}, \dots, x_{n}$，求

$f(x_{1}), f(x_{2}), \dots, f(x_{n})$

**多项式的插值**（Interpolation）即给出 $n + 1$ 个点

$(x_{0}, y_{0}), (x_{1}, y_{1}), \dots, (x_{n}, y_{n})$

求一个 $n$ 次多项式 $f(x)$ 使得这 $n + 1$ 个点都在 $f(x)$ 上。

这两种操作的实质就是将多项式在 **系数表示** 和 **点值表示** 间转化。

### 多项式因式分解、欧几里得和模多项式意义下乘法逆元

由代数基本定理可得，复系数 $n$ 次多项式 $f$ 可唯一分解为如下形式

$a(x-x_1)^{c_1}(x-x_2)^{c_2}\cdots(x-x_m)^{c_m}\\
c_1+c_2+\cdots+c_m=n,x_1,x_2,\cdots,x_m \text{互不相同}$

类比数的最大公因数，可得多项式的 **最大公因式**（The greatest common factor），有定理：

任意域 $P$ 上的多项式环 $P[x]$ 均为欧几里得整环，即可用欧几里得算法计算最大公因式

$\gcd(f,0)=f,\gcd(f,g)=\gcd(g,f\bmod g)$

在此基础上，可用扩展欧几里得给出

$P(x)f(x)+Q(x)g(x)=\gcd(P(x),Q(x))$

的一组特解 $(P(x),Q(x))$。

[HALF-GCD](https://loj.ac/p/172) 允许我们在 $O(n\log^2 n)$ 时间内计算多项式欧几里得。

对于多项式 $f(x),g(x)$，$f(x)$ 在模 $g(x)$ 意义下的乘法逆元定义为满足

$f(x)P(x)\equiv 1\pmod{g(x)}$

的多项式 $P(x)$。这等价于求解

$f(x)P(x)+g(x)Q(x)=1$

的一组特解 $(P(x),Q(x))$。

于是可得，$P(x)$ 存在当且仅当 $\gcd(f,g)=1$。

## 参考资料与拓展阅读

- [**Picks's Blog**](https://picks.logdown.com)
- [**Miskcoo's Space**](https://blog.miskcoo.com)
- [**Formal power series - Wikipedia**](https://en.wikipedia.org/wiki/Formal_power_series#The_ring_of_formal_power_series)
- [**信息学竞赛中的生成函数计算理论框架**](https://github.com/wangr-x/OI-Public-Library-master/blob/main/IOI%E4%B8%AD%E5%9B%BD%E5%9B%BD%E5%AE%B6%E5%80%99%E9%80%89%E9%98%9F%E8%AE%BA%E6%96%87/%E5%9B%BD%E5%AE%B6%E9%9B%86%E8%AE%AD%E9%98%9F2021%E8%AE%BA%E6%96%87%E9%9B%86/pdf-files/%E4%BF%A1%E6%81%AF%E5%AD%A6%E7%AB%9E%E8%B5%9B%E4%B8%AD%E7%9A%84%E7%94%9F%E6%88%90%E5%87%BD%E6%95%B0%E8%AE%A1%E7%AE%97%E7%90%86%E8%AE%BA%E6%A1%86%E6%9E%B6.pdf)
$$
