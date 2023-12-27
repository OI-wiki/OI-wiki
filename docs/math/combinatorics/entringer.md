## 恩特林格数

恩特林格数（Entringer number，[OEIS A008281](http://oeis.org/A008281)）$E(n,k)$ 是满足下述条件的 $0$ 到 $n$ 共 $n+1$ 个数的置换数目：

-   首元素是 $k$；
-   首元素的下一个元素比首元素小，再下一个元素比前一个元素大，再下一个元素比前一个元素小……后面相邻元素的大小关系均满足这样的规则。

恩特林格数的初值有：

$$
E(0,0)=1
$$

$$
E(n,0)=0
$$

有递推关系：

$$
E(n,k)=E(n,k-1)+E(n-1,n-k)
$$

## Seidel–Entringer–Arnold 三角

恩特林格数的一个适当排列的数字三角，称为 Seidel–Entringer–Arnold 三角（Seidel–Entringer–Arnold triangle，[OEIS A008280](http://oeis.org/A008280)）。该三角是按照「牛耕」顺序（ox-plowing order）排列的恩特林格数 $E_(n,k)$：

$$
\begin{aligned}
& E(0,0) \\
& E(1,0) \rightarrow E(1,1) \\
& E(2,2) \leftarrow E(2,1) \leftarrow E(2,0) \\
& E(3,0) \rightarrow E(3,1) \rightarrow E(3,2) \rightarrow E(3,3) \\
& E(4,4) \leftarrow E(4,3) \leftarrow E(4,2) \leftarrow E(4,1) \leftarrow E(4,0)
\end{aligned}
$$

即：

$$
\begin{aligned}
& 1 \\
& 0 \rightarrow 1 \\
& 1 \leftarrow 1 \leftarrow 0 \\
& 0 \rightarrow 1 \rightarrow 2 \rightarrow 2 \\
& 5 \leftarrow 5 \leftarrow 4 \leftarrow 2 \leftarrow 0
\end{aligned}
$$

按照这种方式排列的恩特林格数的优势是，与它的递推关系 $E(n,k)=E(n,k-1)+E(n-1,n-k)$ 一致，可以方便记忆和理解。

恩特林格数有一个指数型生成函数：

$$
\sum_{m=0}^\infty\sum_{n=0}^\infty E\left(m+n,\frac{1}{2}\left(m+n+{(-1)}^{m+n}(n-m)\right)\right)\frac{x^m}{m!}\frac{x^n}{n!}=\frac{\cos x+\sin x}{\cos (x+y)}
$$

这个生成函数的系数分布事实上是上面的 Seidel–Entringer–Arnold 三角的简单拉伸变形：

$$
\begin{array}{ccccc}
E(0,0) & E(1,1) & E(2,0) & E(3,3) & E(4,0) \\
E(1,0) & E(2,1) & E(3,2) & E(4,1) & \\
E(2,2) & E(3,1) & E(4,2) & & \\
E(3,0) & E(4,3) & & & \\
E(4,4) & & & &
\end{array}
$$

即：

$$
\begin{aligned}
& 1\quad 1\quad 0\quad 2\quad 0\\
& 0\quad 1\quad 2\quad 2\\
& 1\quad 1\quad 4\\
& 0\quad 5\\
& 5
\end{aligned}
$$

## zigzag 置换

一个 zigzag 置换（zigzag permutation）是一个 $1$ 到 $n$ 的排列 $c_1$ 到 $c_i$，使得任意一个元素 $c_i$ 的大小都不介于 $c_{i-1}$ 和 $c_{i+1}$ 之间。

对于 zigzag 置换的个数 $Z_n$（[OEIS A001250](http://oeis.org/A001250)），从 $n=0$ 开始有：

$$
1, 1, 2, 4, 10, 32, 122, 544, \cdots
$$

例如，前几个 $n$ 的交替置换有：

$$
\begin{aligned}
n=1: & \{1\}\\
n=2: & \{1,2\}, \{2,1\}\\
n=3: & \{1,3,2\}, \{2,1,3\}, \{2,3,1\}, \{3,1,2\}\\
n=4: & \{1,3,2,4\}, \{1,4,2,3\}, \{2,1,4,3\}, \{2,3,1,4\}, \{2,4,1,3\}, \\
& \{3,1,4,2\}, \{3,2,4,1\}, \{3,4,1,2\}, \{4,1,3,2\}, \{4,2,3,1\}
\end{aligned}
$$

## 交替置换与 zigzag 数

（注意和「错位排列」进行概念上的区分。）

对于大于 $1$ 的 $n$，每个 zigzag 置换翻转过来仍旧为 zigzag 置换，可以两两配对，所以必然为偶数。

这里再给出一种配对的方法：将 zigzag 置换分为交替置换（alternating permutation）和反交替置换（reverse alternating permutation）。

交替置换的首元素大于第二个元素，大小关系为：

$$
c_1>c_2<c_3>\cdots
$$

反交替置换的首元素小于第二个元素，大小关系为：

$$
c_1<c_2>c_3<\cdots
$$

如果将 $1$ 和 $n$ 位置互换，$2$ 和 $n-1$ 位置互换，以此类推，即可将交替置换与反交替置换两个集合互换。因此，交替置换与反交替置换的个数相等，恰好为 zigzag 置换的一半。

对于大于 $1$ 的 $n$，记：

$$
A_n=\frac{Z_n}{2}
$$

定义初值：

$$
A_0=A_1=1
$$

这里的 $A_n$ 称为 zigzag 数（Euler zigzag number，[OEIS A000111](http://oeis.org/A000111)），从 $n=0$ 开始有：

$$
1, 1, 1, 2, 5, 16, 61, 272, \cdots
$$

接下来试着求解 $A_n$。

从 $1$ 到 $n$ 之中，选取 $k$ 个数构成子集，有 $\dbinom{n}{k}$ 种选法。

在这个 $k$ 元子集中，选反交替置换 $u$，有 $A_k$ 种选法；用全集减掉这个 $k$ 元子集，剩余的 $n-k$ 元子集中，选反交替置换 $v$，有 $A_{n-k}$ 种选法。

考虑 $n+1$ 元排列 $w$，将 $u$ 倒置作为开头，接上 $n+1$，再接上 $v$。那么，$w$ 一定是 zigzag 置换，并且任意一个 $n+1$ 元 zigzag 置换，都可以在 $n+1$ 处截断得到对应的反交替置换 $u$ 和 $v$，并且不同的 $n+1$ 元 zigzag 置换对应的 $u$ 和 $v$ 不同。

因此有递推关系：

$$
2A_{n+1}=\sum_{k=0}^n \dbinom{n}{k} A_k A_{n-k}
$$

$$
2(n+1)\frac{A_{n+1}}{(n+1)!}=\sum_{k=0}^n \frac{A_k}{k!}\frac{A_{n-k}}{(n-k)!}
$$

当 $n$ 为 $0$ 时并不满足这个递推式，初值 $A_0$ 和 $A_1$ 都是 $1$。

可见，这是一个指数型生成函数的卷积。假设 $A_n$ 的指数型生成函数为 $y$，就有微分方程：

$$
2\frac{\mathrm{d}y}{\mathrm{d}x}=y^2+1
$$

等式右面加 $1$ 是为了处理 $n$ 为 $0$ 时的特殊情况。该方程的通解为：

$$
y=\tan\left(\frac{1}{2}x+C\right)
$$

代入第 $0$ 项为 $1$ 之后，可以得到特解：

$$
y=\tan x+\sec x
$$

正切函数是奇函数，正割函数是偶函数，两者之和构成 zigzag 数的生成函数。

## 恩特林格数与 zigzag 数的关系

根据恩特林格数的定义，恩特林格数 $E(n,k)$ 是首元素为 $k$ 的 $0$ 到 $n$ 的交替置换个数。因此恩特林格数与 zigzag 数事实上有关系：

$$
A_n=E(n,n)
$$

将 $A_n$ 称为「zigzag 数」也有原因：记 $E_n$ 是欧拉数（Euler number），$B_n$ 是伯努利数。

当 $n$ 为偶数时，偶数项下标的 zigzag 数也称「正割数」$S_n$ 或者「zig 数」。有关系：

$$
A_n=(-1)^{n/2}E_n
$$

前几项为（[OEIS A000364](http://oeis.org/A000364)）：

$$
1, 1, 5, 61, 1385, \cdots
$$

当 $n$ 为奇数时，奇数项下标的 zigzag 数也称「正切数」$T_n$ 或者「zag 数」。有关系：

$$
A_n=\frac{(-1)^{(n-1)/2}2^{n+1}(2^{n+1}-1)B_{n+1}}{n+1}
$$

前几项为（[OEIS A000182](http://oeis.org/A000182)）：

$$
1, 2, 16, 272, 7936, \cdots
$$

于是对于在 $x=0$ 处的泰勒展开，可以给出正割数和正切数：

$$
\sec x=A_0+A_2\frac{x^2}{2!}+A_4\frac{x^4}{4!}+\cdots
$$

$$
\tan x=A_1x+A_3\frac{x^3}{3!}+A_5\frac{x^5}{5!}+\cdots
$$

或者写到一起：

$$
\sec x+\tan x=A_0+A_1x+A_2\frac{x^2}{2!}+A_3\frac{x^3}{3!}+A_4\frac{x^4}{4!}+A_5\frac{x^5}{5!}+\cdots
$$

构成 zigzag 数的生成函数。

## 参考资料与链接

1.  [Alternating permutation - Wikipedia](https://en.wikipedia.org/wiki/Alternating_permutation)
