## Basic Concepts

### 多项式的度

对于一个多项式 $f\left(x\right)$，称其最高次项的次数为该多项式的**度(Degree)**，记作 $\operatorname{deg}{f}$。

### 多项式的逆元

对于多项式 $f\left(x\right)$，若存在 $g\left(x\right)$ 满足：

$$ \begin{aligned}
    f\left(x\right)g\left(x\right)&\equiv 1\pmod{x^{n}}\\
    \operatorname{deg}{g}&\leqslant\operatorname{deg}{f}
\end{aligned} $$

则称 $g\left(x\right)$ 为 $f\left(x\right)$ 在模 $x^{n}$ 意义下的**逆元(Inverse Element)**，记作 $f^{-1}\left(x\right)$。

### 多项式的余数和商

对于多项式 $f\left(x\right),g\left(x\right)$，存在**唯一**的 $Q\left(x\right),R\left(x\right)$ 满足：

$$ \begin{aligned}
    f\left(x\right)&=Q\left(x\right)g\left(x\right)+R\left(x\right)\\
    \operatorname{deg}{Q}&=\operatorname{deg}{f}-\operatorname{deg}{g}\\
    \operatorname{deg}{R}&<\operatorname{deg}{g}
\end{aligned} $$

我们称 $Q\left(x\right)$ 为 $g\left(x\right)$ 除 $f\left(x\right)$ 的**商(Quotient)**,$R\left(x\right)$ 为 $g\left(x\right)$ 除 $f\left(x\right)$ 的**余数(Remainder)**.

亦可记作

$$f\left(x\right)\equiv R\left(x\right)\pmod{g\left(x\right)}$$

### <span id="ln-exp">多项式的对数函数与指数函数</span>

对于一个多项式 $f\left(x\right)$，可以将其对数函数看作其与麦克劳林级数的复合:

$$\ln{\left(1-f\left(x\right)\right)}=-\sum_{i=1}^{+\infty}\frac{f^{i}\left(x\right)}{i}$$

其指数函数同样可以这样定义:

$$\exp{f\left(x\right)}=e^{f\left(x\right)}=\sum_{i=0}^{+\infty}\frac{f^{i}\left(x\right)}{i!}$$

### 多项式的多点求值和插值

**多项式的多点求值(Multi-point evaluation)** 即给出一个多项式 $f\left(x\right)$ 和 $n$ 个点 $x_{1},x_{2},...,x_{n}$，求

$$f\left(x_{1}\right),f\left(x_{2}\right),...,f\left(x_{n}\right) $$

**多项式的插值(Interpolation)** 即给出 $n+1$ 个点

$$\left(x_{0},y_{0}\right),\left(x_{1},y_{1}\right),...,\left(x_{n},y_{n}\right) $$

求一个 $n$ 次多项式 $f\left(x\right)$ 使得这 $n+1$ 个点都在 $f\left(x\right)$ 上.

这两种操作的实质就是将多项式在**系数表示**和**点值表示**间转化。

## References

[**Picks's Blog**](https://picks.logdown.com)

[**Miskcoo's Space**](https://blog.miskcoo.com)
