## Basic Concepts

### 多项式的度

对于一个多项式 $f(x)$，称其最高次项的次数为该多项式的 **度（Degree）**，记作 $\operatorname{deg}{f}$。

### 多项式的乘法

最核心的操作是两个多项式的乘法，即给定多项式 $f(x)$ 和 $g(x)$：

$$
f(x)=a_0+a_1x+\dots+a_nx^n\quad \quad (1)\\ 
g(x)=b_0+b_1x+\dots+b_mx^m\quad \quad (2)
$$

要计算多项式 $Q(x)=f(x)\cdot g(x)$：

$$
\boxed {Q(x) = \sum \limits_ {i = 0} ^ n \sum \limits_ {j = 0 } ^ m a_i b_j x ^ {i + j}} = c_0 + c_1 x + \dots + c_ {n + m} x ^ {n + m}
$$

上述过程可以通过快速傅里叶变换在 $O(n\log n)$ 下计算。

???+note "注"
    一系列的插值变换，相当于将无穷项的信息“压缩”到有限个点值表示，再还原到相应个数的系数表示去近似。

### 多项式的逆元

对于多项式 $f(x)$，若存在 $g(x)$ 满足：

$$
\begin{aligned}
	f(x) g(x) & \equiv 1 \pmod{x^{n}}
\end{aligned}
$$

则称 $g(x)$ 为 $f(x)$ 在模 $x^{n}$ 意义下的 **逆元（Inverse Element）**，记作 $f^{-1}(x)$。若要求 $\operatorname{deg}{g} < n$，则此时 $g$ 唯一。

???+note "注"
    多项式的逆元相当于“截断”，将无穷项的多项式（幂级数）截断到前 $n$ 项，直接将更高位的信息丢失。
    一个问题是，可不可以直接用各种插值变换求解“逆元”，比如计算：
    
    $$
    IDFT\left(\frac{DFT(1)}{DFT(f(x))}\right)
    $$
    
    答案是否定的，不可以这样做。
    首先，该步骤很可能无法顺利执行。插值变换压缩了无限项的信息，导致点值可能是 $0$。比如：
    
    $$
    \frac{1}{1-x}=1+x+x^2+x^3+\ldots
    $$
    
    于是多项式 $1-x$ 在 $1$ 处的插值倒数不存在，而多项式的逆元存在。
    假设这样做了，求出了一个“逆元”，求出的“逆元”会是多项式逆元吗？答案仍旧是否定的。比如：
    
    $$
    \frac{1}{1+x}=1-x+x^2-x^3+\ldots
    $$
    
    多项式 $1+x$ 虽然可以在 $1$ 的位置插值，但是等式右端在不同的位置截断，得到的多项式逆元在 $1$ 的位置插值结果是 $1$ 或 $0$，存在多个结果，并且与原多项式在 $1$ 处插值的倒数 $\frac{1}{2}$ 均不相同。

### 多项式的余数和商

对于多项式 $f(x), g(x)$，存在 **唯一** 的 $Q(x), R(x)$ 满足：

$$
\begin{aligned}
    f(x) &= Q(x) g(x) + R(x) \\
    \operatorname{deg}{R} &< \operatorname{deg}{g}
\end{aligned}
$$

当 $\operatorname{deg}{f} \ge \operatorname{deg}{g}$ 时有 $\operatorname{deg}{Q} = \operatorname{deg}{f} - \operatorname{deg}{g}$，否则有 $Q(x) = 0$。
我们称 $Q(x)$ 为 $g(x)$ 除 $f(x)$ 的 **商（Quotient）**，$R(x)$ 为 $g(x)$ 除 $f(x)$ 的 **余数（Remainder）**。亦可记作

$$
f(x) \equiv R(x) \pmod{g(x)}
$$

### <span id="ln-exp">多项式的对数函数与指数函数</span>

对于一个多项式 $f(x)$，可以将其对数函数看作其与麦克劳林级数的复合：

$$
\ln{(1 - f(x))} = -\sum_{i = 1}^{+\infty} \frac{f^{i}(x)}{i}\\
\ln{(1 + f(x))} = \sum_{i = 1}^{+\infty} \frac{(-1)^{i - 1}f^{i}(x)}{i}
$$

其指数函数同样可以这样定义：

$$
\exp{f(x)} = e^{f(x)} = \sum_{i = 0}^{+\infty} \frac{f^{i}(x)}{i!}
$$

### 多项式的多点求值和插值

**多项式的多点求值（Multi-point evaluation）** 即给出一个多项式 $f(x)$ 和 $n$ 个点 $x_{1}, x_{2}, \dots, x_{n}$，求

$$
f(x_{1}), f(x_{2}), \dots, f(x_{n})
$$

**多项式的插值（Interpolation）** 即给出 $n + 1$ 个点

$$
(x_{0}, y_{0}), (x_{1}, y_{1}), \dots, (x_{n}, y_{n})
$$

求一个 $n$ 次多项式 $f(x)$ 使得这 $n + 1$ 个点都在 $f(x)$ 上。

这两种操作的实质就是将多项式在 **系数表示** 和 **点值表示** 间转化。

## References

- [**Picks's Blog**](https://picks.logdown.com)
- [**Miskcoo's Space**](https://blog.miskcoo.com)
