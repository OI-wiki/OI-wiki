## 第一类斯特林数（Stirling Number）

 **第一类斯特林数** （斯特林轮换数） $\begin{bmatrix}n\\ k\end{bmatrix}$ 表示将 $n$ 个两两不同的元素，划分为 $k$ 个非空圆排列的方案数。

### 递推式

$$
\begin{bmatrix}n\\ k\end{bmatrix}=\begin{bmatrix}n-1\\ k-1\end{bmatrix}+(n-1)\begin{bmatrix}n-1\\ k\end{bmatrix}
$$

边界是 $\begin{bmatrix}n\\ 0\end{bmatrix}=[n=0]$ 。

该递推式的证明可以考虑其组合意义。

我们插入一个新元素时，有两种方案：

- 将该新元素置于一个单独的圆排列中，共有 $\begin{bmatrix}n-1\\ k-1\end{bmatrix}$ 种方案；
- 将该元素插入到任何一个现有的圆排列中，共有 $(n-1)\begin{bmatrix}n-1\\ k\end{bmatrix}$ 种方案。

根据加法原理，将两式相加即可得到递推式。

## 第二类斯特林数（Stirling Number）

 **第二类斯特林数** （斯特林子集数） $\begin{Bmatrix}n\\ k\end{Bmatrix}$ 表示将 $n$ 个两两不同的元素，划分为 $k$ 个非空子集的方案数。

### 递推式

$$
\begin{Bmatrix}n\\ k\end{Bmatrix}=\begin{Bmatrix}n-1\\ k-1\end{Bmatrix}+k\begin{Bmatrix}n-1\\ k\end{Bmatrix}
$$

边界是 $\begin{Bmatrix}n\\ 0\end{Bmatrix}=[n=0]$ 。

还是考虑组合意义来证明。

我们插入一个新元素时，有两种方案：

- 将新元素单独放入一个子集，有 $\begin{Bmatrix}n-1\\ k-1\end{Bmatrix}$ 种方案；
- 将新元素放入一个现有的非空子集，有 $k\begin{Bmatrix}n-1\\ k\end{Bmatrix}$ 种方案。

根据加法原理，将两式相加即可得到递推式。

## 应用

### 上升幂与普通幂的相互转化

我们记上升阶乘幂 $x^{\overline{n}}=\prod_{k=0}^{n-1} (x+k)$ 。

则可以利用下面的恒等式将上升幂转化为普通幂：

$$
x^{\overline{n}}=\sum_{k} \begin{bmatrix}n\\ k\end{bmatrix} x^k
$$

如果将普通幂转化为上升幂，则有下面的恒等式：

$$
x^n=\sum_{k} \begin{Bmatrix}n\\ k\end{Bmatrix} (-1)^{n-k} x^{\overline{k}}
$$

### 下降幂与普通幂的相互转化

我们记下降阶乘幂 $x^{\underline{n}}=\dfrac{x!}{(x-n)!}=\prod_{k=0}^{n-1} (x-k)$ 。

则可以利用下面的恒等式将普通幂转化为下降幂：

$$
x^n=\sum_{k} \begin{Bmatrix}n\\ k\end{Bmatrix} x^{\underline{k}}
$$

如果将下降幂转化为普通幂，则有下面的恒等式：

$$
x^{\underline{n}}=\sum_{k} \begin{bmatrix}n\\ k\end{bmatrix} (-1)^{n-k} x^k
$$

## 习题

 [HDU3625 Examining the Rooms](http://acm.hdu.edu.cn/showproblem.php?pid=3625) 

## 参考资料与注释

1.  [Stirling Number of the First Kind - Wolfram MathWorld](http://mathworld.wolfram.com/StirlingNumberoftheFirstKind.html) 
2.  [Stirling Number of the Second Kind - Wolfram MathWorld](http://mathworld.wolfram.com/StirlingNumberoftheSecondKind.html) 
