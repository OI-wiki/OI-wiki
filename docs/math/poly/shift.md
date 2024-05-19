## 多项式平移

多项式平移是简单情况的多项式复合变换，给出 $f(x)=\sum _ {i=0}^nf_ix^i$ 的系数和一个常数 $c$，求 $f(x+c)$ 的系数，即 $f(x)\mapsto f(x+c)$。

### 分治法

令

$$
f(x)=f_0(x)+x^{\left\lfloor n/2\right\rfloor}f_1(x)
$$

那么

$$
f(x+c)=f_0(x+c)+(x+c)^{\left\lfloor n/2\right\rfloor}f_1(x+c)
$$

$(x+c)^{\left\lfloor n/2\right\rfloor}$ 的系数为二项式系数，那么

$$
T(n)=2T(n/2)+O(n\log n)=O(n\log^2 n)
$$

其中 $O(n\log n)$ 为多项式乘法的时间。

### Taylor 公式法

对 $f(x)$ 在 $c$ 处应用 Taylor 公式，有

$$
f(x)=f(c)+\frac{f'(c)}{1!}(x-c)+\frac{f''(c)}{2!}(x-c)^2+\cdots +\frac{f^{(n)}(c)}{n!}(x-c)^n
$$

那么

$$
f(x+c)=f(c)+\frac{f'(c)}{1!}x+\frac{f''(c)}{2!}x^2+\cdots +\frac{f^{(n)}(c)}{n!}x^n
$$

观察到对于 $t\geq 0$ 有

$$
\begin{aligned}
t!\lbrack x^t\rbrack f(x+c)&=f^{(t)}(c)\\
&=\sum _ {i=t}^nf_ii!\frac{c^{i-t}}{(i-t)!}\\
&=\sum _ {i=0}^{n-t}f _ {i+t}(i+t)!\frac{c^i}{i!}
\end{aligned}
$$

令

$$
\begin{aligned}
A_0(x)&=\sum _ {i=0}^nf _ {n-i}(n-i)!x^i\\
B_0(x)&=\sum _ {i=0}^n\frac{c^i}{i!}x^i
\end{aligned}
$$

那么

$$
\begin{aligned}
\lbrack x^{n-t}\rbrack (A_0(x)B_0(x))&=\sum _ {i=0}^{n-t} (\lbrack x^{n-t-i}\rbrack A_0(x))(\lbrack x^i\rbrack B_0(x))\\
&=\sum _ {i=0}^{n-t}f _ {i+t}(i+t)!\frac{c^i}{i!}\\
&=t!\lbrack x^t\rbrack f(x+c)
\end{aligned}
$$

### 二项式定理法

考虑二项式定理 $\displaystyle (a+b)^n=\sum _ {i=0}^n\binom{n}{i}a^ib^{n-i}$ 那么

$$
\begin{aligned}
f(x+c)&=\sum _ {i=0}^nf_i(x+c)^i\\
&=\sum _ {i=0}^nf_i\left(\sum _ {j=0}^i\binom{i}{j}x^jc^{i-j}\right)\\
&=\sum _ {i=0}^nf_ii!\left(\sum _ {j=0}^i\frac{x^j}{j!}\frac{c^{i-j}}{(i-j)!}\right)\\
&=\sum _ {i=0}^n\frac{x^i}{i!}\left(\sum _ {j=i}^{n}f_jj!\frac{c^{j-i}}{(j-i)!}\right)
\end{aligned}
$$

得到的结果与上述方法相同。

## 连续点值平移

???+ note " 例题 [LOJ 166 拉格朗日插值 2](https://loj.ac/p/166)"
    给出度数小于等于 $n$ 的多项式 $f$ 的连续点值 $f(0),f(1),\dots ,f(n)$，在模 $998244353$ 意义下计算 $f(c),f(c+1),\dots ,f(c+n)$，其中 $1\leq n\leq 10^5,n < m\leq 10^8$。

### Lagrange 插值公式法

考虑 [Lagrange 插值公式](../numerical/interp.md#lagrange-插值法)

$$
\begin{aligned}
f(x)&=\sum _ {0\leq i\leq n}f(i)\prod _ {0\leq j\leq n\,\land \,j\neq i}\frac{x-j}{i-j}\\
&=\sum _ {0\leq i\leq n}f(i)\frac{x!}{(x-n-1)!(x-i)}\frac{(-1)^{n-i}}{i!(n-i)!}\\
&=\frac{x!}{(x-n-1)!}\sum _ {0\leq i\leq n}\frac{f(i)}{(x-i)}\frac{(-1)^{n-i}}{i!(n-i)!}
\end{aligned}
$$

上式虽然是卷积形式但不能保证分母上 $x-i\neq 0$，所以下面仅考虑 $c > n$ 的情况，其他情况（如系数在模素数意义下时须避免 $B_0(x)$ 系数的分母出现零）可以分类讨论解决，令

$$
\begin{aligned}
A_0(x)&=\sum _ {0\leq i\leq n}\frac{f(i)(-1)^{n-i}}{i!(n-i)!}x^i\\
B_0(x)&=\sum _ {i\geq 0}\frac{1}{c-n+i}x^i
\end{aligned}
$$

那么对于 $t\geq 0$ 有

$$
\begin{aligned}
\lbrack x^{n+t}\rbrack (A_0(x)B_0(x))&=\sum _ {i=0}^{n+t}(\lbrack x^i\rbrack A_0(x))(\lbrack x^{n+t-i}\rbrack B_0(x))\\
&=\sum _ {i=0}^{n}\frac{f(i)(-1)^{n-i}}{i!(n-i)!}\frac{1}{c+t-i}\\
&=\frac{(c+t-n-1)!}{(c+t)!}f(c+t)
\end{aligned}
$$

实现中取 $B_0(x)$ 需要的部分截断可求出更多点值，且可利用循环卷积。

对问题稍加修改，假设对于某个 $d$ 给出的点值为 $f(d),f(d+k),\dots ,f(d+nk)$，我们可以计算 $f(c+d),f(c+d+k),\dots ,f(c+d+nk)$，视作平移 $g(x)=f(d+kx)$ 的点值 $g(0),g(1),\dots ,g(n)$ 为 $g(c/k),g(c/k+1),\dots ,g(c/k+n)$。

Lagrange 插值公式也给出了通过维护一些前后缀积的线性计算单个点值的方法。

## 应用

### 同一行第一类无符号 Stirling 数

???+ note " 例题 [P5408 第一类斯特林数·行](https://www.luogu.com.cn/problem/P5408)"
    在模素数 $167772161$ 意义下求 $\displaystyle {n\brack 0},{n\brack 1},\dots ,{n\brack n}$，其中 $1\leq n< 262144$。

考虑

$$
x^{\overline{n}}=\sum _ {i=0}^n{n\brack i}x^i,\quad n\geq 0
$$

其中 $x^{\overline{n}}=x\cdot (x+1)\cdots (x+n-1)$ 为上升阶乘幂，令 $f_n(x)=x^{\overline{n}}$ 那么

$$
f_{2n}(x)=x^{\overline{n}}\cdot (x+n)^{\overline{n}}=f_n(x)f_n(x+n)
$$

通过多项式平移可在 $O(n\log n)$ 求出 $f_n(x+n)$，问题被缩小为原先的一半即求出 $f_n(x)$ 的系数，那么

$$
T(n)=T(n/2)+O(n\log n)=O(n\log n)
$$

### 模素数意义下阶乘

???+ note " 例题 [P5282【模板】快速阶乘算法](https://www.luogu.com.cn/problem/P5282)"
    求 $n!\bmod p$，其中 $p$ 为素数且 $1\leq n< p\leq 2^{31}-1$。

令 $v=\lfloor\sqrt{n}\rfloor$ 和 $g(x)=\prod _ {i=1}^v(x+i)$ 那么

$$
n!\equiv \left(\prod _ {i=0}^{v-1}g(iv)\right)\cdot \prod _ {i=v^2+1}^n i\pmod{p}
$$

其中 $\prod _ {i=v^2+1}^n i$ 可在 $O(\sqrt{n})$ 时间计算，我们希望可以快速计算上式的前半部分。

#### 多项式多点求值

$g(x)$ 系数的计算可用上述多项式平移算法在 $O(n\log n)$ 时间得到，但多点求值计算 $g(0),g(v),g(2v),\dots ,g(v^2-v)$ 需要 $O(\sqrt{n}\log ^2n)$ 时间。

#### 连续点值平移

令 $g_d(x)=\prod _ {i=1}^d(x+i)$，我们可以用 $d+1$ 个点值 $g_d(0),g_d(v),\dots ,g_d(dv)$ 唯一确定这个度数为 $d$ 的多项式，又

$$
g _ {2d}(x)=g_d(x)g_d(x+d)
$$

所以只需 $2d+1$ 个点值可以唯一确定 $g _ {2d}(x)$，那么使用连续点值平移计算 $g_d((d+1)v),g_d((d+2)v),\dots ,g_d(2dv)$（即平移 $h(x)=g_d(vx)$ 的点值 $h(0),h(1),\dots ,h(d)$ 为 $h(d+1),h(d+2),\dots ,h(2d)$）和 $g_d(d),g_d(v+d),\dots ,g_d(2dv+d)$（即平移 $h(x)=g_d(vx)$ 的点值 $h(0),h(1),\dots ,h(d)$ 为 $h(d/v),h(d/v+1),h(d/v+2),\dots ,h(d/v+2d)$）后将这两者的对应点值相乘即得 $g _ {2d}(0),g _ {2d}(v),\dots ,g _ {2d}(2dv)$。

由 $g_d(0),g_d(v),\dots ,g_d(dv)$ 计算 $g _ {d+1}(0),g _ {d+1}(v),\dots ,g _ {d+1}(dv),g _ {d+1}((d+1)v)$ 考虑

$$
g _ {d+1}(x)=(x+d+1)\cdot g_d(x)
$$

额外增加的一个点值使用线性时间的算法即可。那么在开始时维护 $g_1(0)=1,g_1(v)=v+1$ 后使用连续点值平移来倍增地维护这些点值，有

$$
T(n)=T(n/2)+O(n\log n)=O(n\log n)
$$

而我们只需要约 $\sqrt{n}$ 个点值，所以时间复杂度为 $O(\sqrt{n}\log n)$。

### 模素数意义下二项式系数前缀和

???+ note " 例题 [LOJ 6386 组合数前缀和](https://loj.ac/p/6386)"
    求 $\displaystyle \sum _ {i=0}^m\binom{n}{i}\bmod 998244353$，其中 $0\leq m\leq n\leq 9\times 10^8$。

考虑使用矩阵描述 $n!=n\cdot (n-1)!$ 这一步递推，我们有

$$
\begin{bmatrix}
n!
\end{bmatrix}
=\left(
\prod _ {i=0}^{n-1}
\begin{bmatrix}i+1\end{bmatrix}
\right)
\begin{bmatrix}
1
\end{bmatrix}
$$

类似的可以将二项式系数前缀和的递推描述为

$$
\begin{bmatrix}
\binom{n}{m+1}\\
\sum _ {i=0}^m\binom{n}{i}
\end{bmatrix}=
\begin{bmatrix}
(n-m)/(m+1)&0\\
1&1
\end{bmatrix}
\begin{bmatrix}
\binom{n}{m}\\
\sum _ {i=0}^{m-1}\binom{n}{i}
\end{bmatrix}
$$

注意矩阵乘法的顺序，那么

$$
\begin{aligned}
\begin{bmatrix}
\binom{n}{m+1}\\
\sum _ {i=0}^m\binom{n}{i}
\end{bmatrix}
&=\left(
\prod _ {i=0}^{m}
\begin{bmatrix}
(n-i)/(i+1)&0\\1&1
\end{bmatrix}
\right)
\begin{bmatrix}
1\\0
\end{bmatrix}\\
&=
\frac{1}{(m+1)!}
\left(
\prod _ {i=0}^{m}
\begin{bmatrix}
n-i&0\\i+1&i+1
\end{bmatrix}
\right)
\begin{bmatrix}
1\\0
\end{bmatrix}
\end{aligned}
$$

令 $v=\lfloor\sqrt{m}\rfloor$，考虑维护矩阵

$$
\begin{aligned}
M _ d(x)&=
\prod _ {i=1}^d
\begin{bmatrix}
-x+n+1-i&0\\
x+i&x+i
\end{bmatrix}\\
&=
\begin{bmatrix}
f_d(x)&0\\
g_d(x)&h_d(x)
\end{bmatrix}
\end{aligned}
$$

的点值 $M _ d(0),M _ d(v),\dots ,M_d(dv)$ 即 $f_d(0),f_d(v),\dots ,f_d(dv)$、$h_d(0),\dots ,h_d(dv)$ 和 $g_d(0),\dots ,g_d(dv)$，又

$$
\begin{aligned}
M _ {2d}(x)&=
\prod _ {i=1}^{2d}
\begin{bmatrix}
-x+n+1-i&0\\
x+i&x+i
\end{bmatrix}\\
&=
\left(
\prod _ {i=1}^d
\begin{bmatrix}
-x-d+n+1-i&0\\
x+d+i&x+d+i
\end{bmatrix}
\right)
\left(
\prod _ {i=1}^d
\begin{bmatrix}
-x+n+1-i&0\\
x+i&x+i
\end{bmatrix}
\right) \\
&=
\begin{bmatrix}
f_d(x+d)&0\\
g_d(x+d)&h_d(x+d)
\end{bmatrix}
\begin{bmatrix}
f_d(x)&0\\
g_d(x)&h_d(x)
\end{bmatrix} \\
&=
\begin{bmatrix}
f_d(x+d)f_d(x)&0\\
g_d(x+d)f_d(x)+h_d(x+d)g_d(x)&h_d(x+d)h_d(x)
\end{bmatrix}
\end{aligned}
$$

且矩阵右下角元素恰为我们在阶乘算法中所维护的，那么

$$
\begin{aligned}
\prod _ {i=0}^{m}
\begin{bmatrix}
n-i&0\\i+1&i+1
\end{bmatrix}=
\left(
\prod _ {i=(k+1)v}^m
\begin{bmatrix}
n-i&0\\
i+1&i+1
\end{bmatrix}
\right)
\begin{bmatrix}
f_v(kv)&0\\
g_v(kv)&h_v(kv)
\end{bmatrix}
\cdots
\begin{bmatrix}
f_v(0)&0\\
g_v(0)&h_v(0)
\end{bmatrix}
\end{aligned}
$$

可在 $O(\sqrt m\log m)$ 时间完成计算。

### 模素数意义下调和数

???+ note " 例题 [P5702 调和级数求和](https://www.luogu.com.cn/problem/P5702)"
    求 $\sum _ {i=1}^ni^{-1}\bmod p$，其中 $p$ 为素数且 $1\leq n< p< 2^{30}$。

记 $H_n=\sum _ {k=1}^nk^{-1}$，一步递推为

$$
\begin{bmatrix}
(n+1)!\\(n+1)!H _ {n+1}
\end{bmatrix}=
\begin{bmatrix}
n+1&0\\1&n+1
\end{bmatrix}
\begin{bmatrix}
n!\\n!H_n
\end{bmatrix}
$$

那么

$$
\begin{bmatrix}
{n+1\brack 1}\\{n+1\brack 2}
\end{bmatrix}=
\begin{bmatrix}
n!\\n!H_n
\end{bmatrix}=
\left(
\prod _ {i=0}^{n-1}
\begin{bmatrix}
i+1&0\\1&i+1
\end{bmatrix}
\right)
\begin{bmatrix}
1\\0
\end{bmatrix}
$$

在这里 $\displaystyle {n+1\brack 1}$ 和 $\displaystyle {n+1\brack 2}$ 为第一类无符号 Stirling 数。维护点值矩阵的方法同上。

## 整式递推

对于更一般的情况，类似于上述快速阶乘算法的案例，我们期望得到一个怎么样的算法？

???+ note " 例题 [P6115【模板】整式递推](https://www.luogu.com.cn/problem/P6115)"
    现有数列 $a$ 满足 $\forall n\ge m,\sum_{k=0}^ma_{n-k}P_k(n)=0$，其中 $P_k$ 为不超过 $d$ 次的多项式。  
    给定所有 $P_k$ 的系数，和 $a_0,a_1,\dots,a_{m-1}$，求 $a_n$。
    对 $998244353$ 取模。$n\le6\times10^8$，$1\le m,d\le7$，时限 $7s$。

为了更系统地描述上述几道例题中构造矩阵的过程，我们引入 [$\lambda$ 矩阵](../linear-algebra/jordan.md#lambda-%E7%9F%A9%E9%98%B5) 的概念。

为了实现整式递推，我们应当注意到快速阶乘算法过程中，我们维护的点值其实并不是 $n!$，而是 $\prod_{i=0}^{T-1}(aT+i)$，即 **一对点值之间的倍数关系**。

由于整式递推阶数 $m$ 不止是 $1$ 了，我们就 **不能直接维护一对数之间的倍数关系了**；而是维护出 **一对 $m$ 维向量之间的线性变换**，即 $m\times m$ 的一个矩阵，**矩阵的每一项对应于某个多项式的一个点值**。

容易发现，对于一般的整式递推远处系数求值问题，我们可以构造

$$
-{\frac{1}{P_0(n)}}\begin{bmatrix}P_1(n)&P_2(n)&P_3(n)&\cdots&P_{m-1}(n)&P_m(n)\\-P_0(n)\\&-P_0(n)\\&&-P_0(n)\\&&&\ddots\\&&&&-P_0(n)\\\end{bmatrix}
\begin{bmatrix}a_{n-1}\\a_{n-2}\\a_{n-3}\\\vdots\\a_{n-m+1}\\a_{n-m}\end{bmatrix}
=\begin{bmatrix}a_n\\a_{n-1}\\a_{n-2}\\\vdots\\a_{n-m+2}\\a_{n-m+1}\end{bmatrix}
$$

设

$$
B(\lambda)=\begin{bmatrix}
    P_1(\lambda)&P_2(\lambda)&P_3(\lambda)&\cdots&P_{m-1}(\lambda)&P_m(\lambda)\\
    -P_0(\lambda)\\
    &-P_0(\lambda)\\
    &&-P_0(\lambda)\\
    &&&\ddots\\
    &&&&-P_0(\lambda)\\
\end{bmatrix}
$$

我们先撇开前面的 $-\frac1{P_0(n)}$ 因子不论，我们现在要维护 $\prod_{i=0}^{T-1}B(aT+m+i)$ 这种形式的量，其中乘法自右往左。

容易发现 $B_T(\lambda)=\prod_{i=0}^{T-1}B(\lambda+i)$ 是一个各项次数不高于 $dT$ 的 $\lambda$ 矩阵，只用 $dT+1$ 个值即可维护。

于是我们维护出 $B_T(m)$，$B_T(m+T)$，$B_T(m+2T)$，$\dots$，$B_T(m+(dT-1)T)$，$B_T(m+dT^2)$ 这几个 $\lambda$ 矩阵的 **点值**，然后用类似于快速阶乘算法的方式暴力进行多项式点值平移和倍增就好了。

具体地，为了让 $t=\log_2T$ 抬高 $1$，我们这么干：

1.  在 $O(m^2dT\log(dT))$ 时间内获取 $B_T(p+dT^2)$，$B_T(p+(dT+1)T)$，$B_T(p+(dT+2)T)$，$\cdots$，$B_T(p+(2dT-1)T)$，$B_T(p+(2dT)dT)$。
2.  在 $O(m^2dT\log(dT))$ 时间内获取 $B_T(p+2dT^2)$，$B_T(p+(2dT+1)T)$，$B_T(p+(2dT+2)T)$，$\cdots$，$B_T(p+(3dT-1)T)$，$B_T(p+(3dT)dT)$。
3.  在 $O(m^2dT\log(dT))$ 时间内获取 $B_T(p+3dT^2)$，$B_T(p+(3dT+1)T)$，$B_T(p+(3dT+2)T)$，$\cdots$，$B_T(p+(4dT-1)T)$，$B_T(p+(4dT)dT)$。
4.  计算 $B_{2T}(v)=B_{T}(v+T)B_{T}(v)$。

我们每轮花费 $O(m^2dT\log(dT))$ 的复杂度进行平移；同时，我们每轮只用做 $\Theta(dT)$ 次矩阵乘法，复杂度可以认为是 $O(m^3dT)$。

最后，我们只用做到 $T\ge\sqrt{n/d}$ 即可。

之前的 $-\frac1{P_0(n)}$ 因子可以用类似的方法解决。

这样，我们预处理的复杂度即为 $\Theta(\sqrt{nd}(m^3+m^2\log(nd)))$。

考虑查询，我们只用 $\Theta(n/T)$ 次向量与矩阵的乘法，以及 $O(T)$ 次暴力转移。

容易发现这部分计算并不是复杂度瓶颈。

因此，该算法的总复杂度为 $\Theta(\sqrt{nd}(m^3+m^2\log(nd)))$。

编码时，我们可以使用循环卷积的技巧来减小 NTT 的常数。

在实际应用时，我们往往是对一个已知的微分有限的 GF 提取其远处系数，从而 $m,d$ 均为常数，也即做到了 $\Theta(\sqrt n\log n)$ 的远处系数求值。

## 参考文献

-   Alin Bostan, Pierrick Gaudry, and Eric Schost. Linear recurrences with polynomial coefficients and application to integer factorization and Cartier–Manin operator.
-   Min\_25 的博客
-   [ZZQ 的博客 - 阶乘模大质数](https://www.cnblogs.com/zzqsblog/p/8408691.html)
