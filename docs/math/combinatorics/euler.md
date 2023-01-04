???+ warning "注意"
    下文中的欧拉数特指 Euler number。注意与后文的 Eulerian Number，以及 Euler's number（指与欧拉相关的数学常数例如 $\gamma$ 或 $e$）作区分。

**欧拉数（Euler number）** 是与伯努利数形式相似的一个数列。

## 欧拉多项式

欧拉多项式 $E_n(x)$ 由展开式给出：

$$
\frac{2e^{xt}}{e^t+1}=\sum_{n=0}^\infty\frac{t^n}{n!}E_n(x)
$$

左方的函数称为欧拉多项式的生成函数。级数在 $|t|<\pi$ 时收敛，因为左方函数距离 $t=0$ 最近的奇点是 $t=\pm \pi i$。

在欧拉多项式的生成函数中，令 $x$ 取 $\frac{1}{2}$，等式左端变为 $t$ 的偶函数，右边不出现 $t$ 的奇次方，有：

$$
\frac{2e^{\frac{t}{2}}}{e^t+1}=sech \frac{t}{2}=\sum_{n=0}^\infty\frac{E_n}{n!}{\left(\frac{t}{2}\right)}^n
$$

其中欧拉数定义为：

$$
E_n=2^nE_n\left(\frac{1}{2}\right)
$$

所有的奇数项欧拉数均为 $0$。因此，欧拉数是双曲正割函数的展开式系数。

前几个欧拉多项式为：

$$
E_0(x)=1
$$

$$
E_1(x)=x-\frac{1}{2}
$$

$$
E_2(x)=x(x-1)
$$

$$
E_3(x)=\left(x-\frac{1}{2}\right)\left(x^2-x-\frac{1}{2}\right)
$$

$$
E_4(x)=x(x-1)(x^2-x-1)
$$

$$
E_5(x)=\left(x-\frac{1}{2}\right)(x^4-2x^3-x^2+2x+1)
$$

$$
E_6(x)=x(x-1)(x^4-2x^3-2x^2+3x+3)
$$

从下标为 $0$ 开始的欧拉数的前几项为：

$$
1,0,-1,0,5,0,-61,0,1385,0,-50521,0,2702765,0,-199360981,0,19391512145,0,-2404879675441,0,\cdots
$$

对比：伯努利多项式 $B_n(x)$：

$$
\frac{te^{xt}}{e^t-1}=\sum_{n=0}^\infty\frac{t^n}{n!}B_n(x)
$$

左方的函数称为伯努利多项式的生成函数。级数在 $|t|<2\pi$ 时收敛，因为左方函数距离 $t=0$ 最近的奇点是 $t=\pm 2\pi i$。

在伯努利多项式的生成函数中，令 $x$ 取 $0$，等式左端变为：

$$
\frac{t}{e^t-1}=\sum_{n=0}^\infty\frac{t^n}{n!}B_n
$$

其中伯努利数定义为：

$$
B_n=B_n(0)
$$

即为伯努利多项式的常数项。除了下标为 $1$ 的伯努利数为 $-\frac{1}{2}$ 以外，所有的奇数项伯努利数均为 $0$。

前几个伯努利多项式为：

$$
B_0(x)=1
$$

$$
B_1(x)=x-\frac{1}{2}
$$

$$
B_2(x)=x^2-x+\frac{1}{6}
$$

$$
B_3(x)=x(x-1)\left(x-\frac{1}{2}\right)=x^3-\frac{3}{2}x^2+\frac{1}{2}x
$$

$$
B_4(x)=x^4-2x^3+x^2-\frac{1}{30}
$$

$$
B_5(x)=x(x-1)\left(x-\frac{1}{2}\right)\left(x^2-x-\frac{1}{3}\right)=x^5-\frac{5}{2}x^4+\frac{5}{3}x^3-\frac{1}{6}x
$$

$$
B_6(x)=x^6-3x^5+\frac{2}{5}x^4-\frac{1}{2}x^2+\frac{1}{42}
$$

从下标为 $0$ 开始的伯努利数的前几项为：

$$
1,-\frac{1}{2},\frac{1}{6},0,-\frac{1}{30},0,\frac{1}{42},0,-\frac{1}{30},0,\frac{5}{66},0,-\frac{691}{2730},0,\frac{7}{6},0,-\frac{3617}{510},0,\frac{43867}{798},0,-\frac{174611}{330},0,\cdots
$$

## 欧拉多项式与欧拉数的递推关系

欧拉多项式的生成函数可以整理为：

$$
\frac{2e^{\frac{t}{2}}e^{\left(x-\frac{1}{2}\right)t}}{e^t+1}=\sum_{k=0}^\infty\frac{E_k}{k!}{\left(\frac{t}{2}\right)}^k\sum_{t=0}^\infty\frac{{\left(x-\frac{1}{2}\right)}^l}{l!}t^l=\sum_{n=0}^\infty\frac{t^n}{n!}\sum_{k=0}^n\frac{E_k}{2^k}C_n^k{\left(x-\frac{1}{2}\right)}^{n-k}
$$

因此欧拉多项式的显式表达为：

$$
E_n(x)=\sum_{k=0}^n\frac{E_k}{2^k}C_n^k{\left(x-\frac{1}{2}\right)}^{n-k}
$$

这个等式可以形式上记为：

$$
E_n(x)={\left(\frac{E_k}{2}+x-\frac{1}{2}\right)}^n
$$

在前文欧拉数的双曲正割定义法中，将 $t$ 换为 $2t$，可以得到：

$$
1=\frac{e^t+e^{-t}}{2}\sum_{l=0}^\infty\frac{E_l}{l!}t^l=\sum_{r=0}^\infty\frac{t^{2r}}{(2r)!}\sum_{l=0}^\infty\frac{E_l}{l!}t^l=\sum_{k=0}^\infty\frac{t^{2k}}{(2k)!}\sum_{l=0}^k\frac{E_l(2k)!}{l!(2k-l)!}
$$

于是欧拉数 $E_k$ 可以用递推关系求出。初值有：

$$
E_0=1
$$

对于至少为 $1$ 的 $k$ 有：

$$
\sum_{l=0}^k C_{2k}^l E_l=0
$$

这个等式可以形式上记为：

$$
(E+1)^{2k}=0
$$

对比：

伯努利多项式的生成函数可以整理为：

$$
\frac{te^{xt}}{e^t-1}=\sum_{k=0}^\infty\frac{t^k}{k!}B_k\sum_{l=0}^\infty\frac{t^l}{l!}x^l=\sum_{n=0}^\infty\frac{t^n}{n!}\sum_{k=0}^n C_n^k B_k x^{n-k}
$$

因此伯努利多项式的显式表达为：

$$
B_n(x)=\sum_{k=0}^n C_n^k B_k x^{n-k}
$$

这个等式可以形式上记为：

$$
B_n(x)={(B+x)}^n
$$

在伯努利数的定义中，有：

$$
1=\frac{e^t-1}{t}\sum_{k=0}^\infty \frac{t^k}{k!}B_k=\sum{l=1}^\infty\frac{t^{l-1}}{l!}\sum\frac{t^k}{k!}B_k=\sum_{n=1}^\infty t^{n-1}\sum_{k=0}^{n-1}\frac{B_k}{k!(n-k)!}
$$

于是伯努利数 $B_k$ 可以用递推关系求出。初值有：

$$
B_0=1
$$

对于至少为 $2$ 的 $n$ 有：

$$
\sum_{k=0}^{n-1} C_n^k B_k=0
$$

这个等式可以形式上记为：

$$
{(B+1)}^n-B_n=0
$$

## 求和公式

对于欧拉多项式，有均值关系：

$$
E_n(x+1)+E_n(x)=2x^n
$$

根据上式有求和公式：

$$
\sum_{s=1}^m {(-1)}^s s^n=\frac{1}{2}\sum_{s=1}^m {(-1)}^s(E_n(s+1)+E_n(s))=\frac{1}{2}({(-1)}^m E_n(m+1)-E_n(1))
$$

因此交错的 $n$ 次方的部分和是欧拉多项式。

这里应用的求和是整数取值，然而欧拉多项式在 $\frac{1}{2}$ 处取值才是欧拉数。考虑半整数取值，有：

$$
\sum_{s=1}^m {(-1)}^s\frac{{(2s-1)}^n}{2^n}=\frac{1}{2}\left({-1}^m E_n\left(m+\frac{1}{2}\right)-E_n\left(\frac{1}{2}\right)\right)
$$

$$
\sum_{s=1}^m {(-1)}^s {(2s-1)}^n=\frac{1}{2}\left({-1}^m 2^n E_n\left(m+\frac{1}{2}\right)-E_n\right)
$$

因此交错的奇数 $n$ 次方的部分和是欧拉多项式，并且式中减去的一项是欧拉数。

对比：

对于 $n$ 至少为 $1$ 的伯努利多项式，有差分关系：

$$
B_n(x+1)=B_n(x)+nx^{n-1}
$$

根据上式，对于 $n$ 至少为 $1$ 有求和公式：

$$
\sum_{s=1}^m s^m=\frac{1}{n+1}(B_{n+1}(m+1)-B_{n+1})
$$

因此 $n$ 次方的部分和是伯努利多项式，并且式中减去的一项是伯努利数。

## 欧拉多项式的导数

欧拉多项式的 $p$ 阶导数为：

$$
\frac{d^p}{dx^p}E_n(x)=\frac{n!}{(n-p)!}E_{n-p}(x)
$$

欧拉多项式的积分为：

$$
\int_a^x E_n(y)dy=\frac{1}{n+1}(E_{n+1}(x)-E_{n+1}(a))
$$

对比：

伯努利多项式的 $p$ 阶导数为：

$$
\frac{d^p}{dx^p}B_n(x)=\frac{n!}{(n-p)!}B_{n-p}(x)
$$

伯努利多项式的积分为：

$$
\int_a^x B_n(y)dy=\frac{1}{n+1}(B_{n+1}(x)-B_{n+1}(a))
$$

## 欧拉多项式的互余宗量关系

对于欧拉多项式有：

$$
E_n(1-x)={(-1)}^n E_n(x)
$$

对比：

对于伯努利多项式有：

$$
B_n(1-x)={(-1)}^n B_n(x)
$$

## 正割函数的展开式

由定义式的双曲正割，通过代换变为正割，可以得到：

$$
\sec t=\sum_{n=0}^\infty {(-1)}^n\frac{E_{2n}}{(2n)!}t^{2n}
$$

对比：

由伯努利数的定义式可以得到余切、正切和余割函数的展开式：

$$
\frac{t}{2}\cot\frac{t}{2}=1+\sum_{n=1}^\infty {(-1)}^n\frac{B_{2n}}{(2n)!}t^{2n}
$$

$$
\frac{t}{2}\tan\frac{t}{2}=\frac{t}{2}\cot\frac{t}{2}-t\cot t=\sum_{n=1}^\infty {(-1)}^n\frac{(1-2^{2n})B_{2n}}{(2n)!}t^{2n}
$$

$$
t\csc t=\frac{t}{2}\cot\frac{t}{2}+\frac{t}{2}\tan\frac{t}{2}=1+\sum_{n=1}^\infty {(-1)}^n\frac{(2-2^{2n})B_{2n}}{(2n)!}t^{2n}
$$
