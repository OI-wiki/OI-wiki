## 引入

**傅里叶——莫茨金消元法**（原名 Fourier–Motzkin Elimination，简称 **FME** 算法）是一种用于从线性不等式中消除变量的数学方法。

它的命名源自于在 1827 年和 1936 年独立发现该算法的 Joseph Fourier 和 Theodore Motzkin 的姓氏。

## 过程

从线性不等式中消除一组变量，是指通过将关系式中的若干个元素有限次地变换，消去其中的某些元素，从而解决问题的一种方法。

如果线性不等式中的所有变量都被消除，那么我们会得到一个常不等式。因为当且仅当原不等式有解时，消元后的不等式才为真，消除所有变量可用于检测不等式系统是否有解。

考虑一个含 $n$ 个不等式的系统 $S$，有从 $x_{1}$ 到 $x_{r}$ 的 $r$ 个变量，其中 $x_{r}$ 为要消除的变量。根据 $x_r$ 系数的符号（正、负或空），$S$ 中的线性不等式可以分为三类：

1.  形式为 $x_{r}\geq b_{i}-\sum _{k=1}^{r-1}a_{ik}x_{k}$ 的不等式，对于范围从 $1$ 到 $n_{A}$（$n_{A}$ 为这种不等式的数量）的 $j$，用 $x_{r}\geq A_{j}(x_{1},\dots ,x_{r-1})$ 表示；
2.  形式为 $x_{r}\leq b_{i}-\sum _{k=1}^{r-1}a_{ik}x_{k}$ 的不等式，对于范围从 $1$ 到 $n_{B}$（$n_{B}$ 为这种不等式的数量）的 $j$，用 $x_{r}\leq B_{j}(x_{1},\dots ,x_{r-1})$ 表示；
3.  不包含 $x_{r}$ 的不等式，设它们构成的不等式组为 $\phi$。

因此原系统等价于

$$
\max(A_{1}(x_{1},\dots ,x_{r-1}),\dots ,A_{n_{A}}(x_{1},\dots ,x_{r-1}))\leq x_{r}\leq \min(B_{1}(x_{1},\dots ,x_{r-1}),\dots ,B_{n_{B}}(x_{1},\dots ,x_{r-1}))\wedge \phi
$$

消元包括产生一个等价于 $\exists x_{r}~S$ 的系统。显然，这个公式等价于

$$
\max(A_{1}(x_{1},\dots ,x_{r-1}),\dots ,A_{n_{A}}(x_{1},\dots ,x_{r-1}))\leq \min(B_{1}(x_{1},\dots ,x_{r-1}),\dots ,B_{n_{B}}(x_{1},\dots ,x_{r-1}))\wedge \phi
$$

不等式

$$
\max(A_{1}(x_{1},\dots ,x_{r-1}),\dots ,A_{n_{A}}(x_{1},\dots ,x_{r-1}))\leq \min(B_{1}(x_{1},\dots ,x_{r-1}),\dots ,B_{n_{B}}(x_{1},\dots ,x_{r-1}))
$$

等价于对于 $1 \leq i \leq n_{A}$ 且 $1\leq j\leq n_{B}$，所有 $n_{A}n_{B}$ 个不等式 $A_{i}(x_{1},\dots ,x_{r-1})\leq B_{j}(x_{1},\dots ,x_{r-1})$ 构成的不等式组。

因此，我们将原系统 $S$ 转换为另一个消掉 $x_{r}$ 的系统，这个系统有 $(n-n_{A}-n_{B})+n_{A}n_{B}$ 个不等式。特别地，如果 $n_{A}=n_{B}=n/2$，那么新系统不等式的个数为 $n^{2}/4$。

### 例题

考虑以下不等式系统：

$2x-5y+4z \leq 10$

$3x-6y+3z \leq 9$

$-x+5y-2z \leq -7$

$-3x+2y+6z \leq 12$

为了消除 $x$，我们可以根据 $x$ 改写不等式：

$x \leq (10 + 5y - 4z)/2$

$x \leq (9 + 6y - 3z)/3$

$x \geq 7 + 5y - 2z$

$x \geq (-12 + 2y + 6z)/3$

这样我们得到两个 $\leq$ 不等式和两个 $\geq$ 不等式；如果每个 $\leq$ 不等式的右侧至少是每个 $\geq$ 不等式的右侧，则系统有一个解。我们有 $2\times2$ 这样的组合：

$7 + 5y - 2z \leq  (10 + 5y - 4z)/2$

$7 + 5y - 2z \leq  (9 + 6y - 3z)/3$

$(-12 + 2y + 6z)/3 \leq (10 + 5y - 4z)/2$

$(-12 + 2y + 6z)/3 \leq (9 + 6y - 3z)/3$

现在我们有了一个新的少了一个变量不等式系统。

## 时间复杂度

在 $n$ 个不等式上消元可以最多得到 $n^{2}/4$ 个不等式，因此连续运行 $d$ 步可以得到最多 $4(n/4)^{2^{d}}$ 的双指数复杂度。这是由于算法产生了许多不必要的约束（其他约束隐含的约束）。必要约束的数量以单一指数增长。

可以使用线性规划 (Linear Programming, LP) 检测不必要的约束。

## 应用

信息论的可实现性证明保证了存在性能良好的编码方案的条件。这些条件通常使用线性不等式系统描述。系统的变量包括传输速率和附加辅助速率。通常，人们旨在仅根据问题的参数（即传输速率）来描述通信的基本限制，因此述辅助率需要消除上。而我们正是通过傅立叶 - 莫茨金消元法来做到这一点的。

## 实现

在编程语言中，[Racket](https://racket-lang.org/)，一种基于 Lisp 的多范式编程语言在 [fme - Fourier–Motzkin Elimination for Integer Systems)](https://docs.racket-lang.org/fme/index.html) 中对 FME 算法做了简单函数代数实现。

## 参考资料与拓展阅读

1.  Rui-Juan Jing, Marc Moreno-Maza, Delaram Talaashrafi, "[Complexity Estimates for Fourier-Motzkin Elimination](https://arxiv.org/abs/1811.01510)", Journal of Functional Programming 16:2 (2006) pp 197-217.
2.  [Fourier–Motzkin elimination - Wikipedia](https://en.wikipedia.org/wiki/Fourier%E2%80%93Motzkin_elimination)
3.  [Fourier-Motzkin elimination and its dual](https://www.sciencedirect.com/science/article/pii/0097316573900046)
4.  GE Liepins,[Fourier-Motzkin elimination for mixed systems](https://www.osti.gov/servlets/purl/5860090), 1983
