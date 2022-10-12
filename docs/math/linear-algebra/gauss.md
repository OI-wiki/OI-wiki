高斯-若尔当消元法（Gauss-Jordan elimination）是求解线性方程组的经典算法，它在当代数学中有着重要的地位和价值，是线性代数课程教学的重要组成部分。

本算法为 Gauss-Jordan 消元法，是 Jordan 在 1887 年描述的 Gauss 方法的变体。

高斯消元法除了用于线性方程组求解外，还可以用于行列式计算、求矩阵的逆，以及其他计算机和工程方面。

夏建明等人之前提出了应用图形处理器 (GPU) 加速求解线性方程组的高斯消元法，所提出的算法与基于 CPU 的算法相比较取得更快的运算速度。二是提出各种变异高斯消元法以满足特定工作的需要。

* * *

## 线性方程组

给定一个含有 $n$个未知数的线性方程组（SLAE）。要求求解方程组：确定它是否有解，只有一个解还是无穷多个解。如果它至少有一个解，求出其中任何一个。

从形式上讲，问题的表述为解方程组：

$$
\begin{align}
a_{11} x_1 + a_{12} x_2 + &\dots + a_{1m} x_m = b_1 \\
a_{21} x_1 + a_{22} x_2 + &\dots + a_{2m} x_m = b_2\\
&\vdots \\
a_{n1} x_1 + a_{n2} x_2 + &\dots + a_{nm} x_m = b_n
\end{align}
$$

其中，系数$a_{ij}$和$b_i$是已知的，变量$x_i$是未知的。

这个问题还有一个简单的矩阵表示法：

$$
Ax = b
$$

其中$A$是系数$A_{ij}$的大小为 $n \times m$ 的矩阵，称为系数矩阵，$b$是大小为$n$的列向量。

本文的算法也可用于求解模为任意数 $p$ 的方程，即：

$$
\begin{align}
a_{11} x_1 + a_{12} x_2 + &\dots + a_{1m} x_m \equiv b_1 \pmod p \\
a_{21} x_1 + a_{22} x_2 + &\dots + a_{2m} x_m \equiv b_2 \pmod p \\
&\vdots \\
a_{n1} x_1 + a_{n2} x_2 + &\dots + a_{nm} x_m \equiv b_n \pmod p
\end{align}
$$

## 消元法及高斯消元法思想

### 定义

消元法是将方程组中的一方程的未知数用含有另一未知数的代数式表示，并将其带入到另一方程中，这就消去了一未知数，得到一解；或将方程组中的一方程倍乘某个常数加到另外一方程中去，也可达到消去一未知数的目的。消元法主要用于二元一次方程组的求解。

### 解释

例一：利用消元法求解二元一次线性方程组：

$$
\left\{\begin{aligned}
4x+y&=100 \notag \\
x-y&=100 \notag
\end{aligned}\right.
$$

解：将方程组中两方程相加，消元 $y$ 可得：

$5x = 200$

解得：

$x = 40$

将 $x = 40$ 代入方程组中第二个方程可得：

$y = -60$

### 高斯消元法思想概念

德国数学家高斯对消元法进行了思考分析，得出了如下结论：

- 在消元法中，参与计算和发生改变的是方程中各变量的系数；

- 各变量并未参与计算，且没有发生改变；

- 可以利用系数的位置表示变量，从而省略变量；

- 在计算中将变量简化省略，方程的解不变。

> 高斯在这些结论的基础上，提出了高斯消元法，首先将方程的增广矩阵利用行初等变换化为行最简形，然后以线性无关为准则对自由未知量赋值，最后列出表达方程组通解。

按照指定顺序进行消元的办法称为高斯消元法。

记单位阵为 $I$。假设 $A$ 的逆矩阵存在，那么消元的过程就是求 $A$ 的逆矩阵的过程。于是就有：

$$
Ax=Ib\implies Ix=A^{-1}b
$$

如果在等式两端，同时左乘一系列初等矩阵，使得 $A$ 变为单位阵 $I$，那么 $I$ 将同时变为 $A$ 的逆。

按照方程的观点，左乘上述三种矩阵，都是对“行”操作，即对方程操作，本质还是加减消元法。由于引入了方程换位与扩大倍数，可以保证消元的按序进行。

因为逆可能不存在，未必一定需要求逆。对于一般的矩阵 $A$，可以对 $A$ 做行变换消元，能消多少消多少，直到无法进行为止。上面说“求逆”只是为了方便理解。

### 行最简型矩阵

一个矩阵 $A$，行变换消元至无法进行，会变成：

$$
Ax=Ib\overset{\tiny B\thinspace :=\thinspace PA}{\Longrightarrow} Bx=Pb
$$

就是对 $A$ 左乘了变换 $P$，变为最终的矩阵 $B$。最终的矩阵 $B$ 一定是行最简形矩阵。行最简形矩阵是引入概念“秩”最重要的前置概念，是行变换消元得来的最终结果。

行最简形矩阵，要求在阶梯形矩阵中：

- 非零行的第一个非零元素全是 $1$。

- 非零行的第一个元素 $1$ 所在列的其余元素全为零。

也就是说，消元的顺序是，每次先从左上角，用第一个元素消这一列。要把当前行拿来消其他行上相应元素的首元素变为 $1$。不仅把下方的元素全部消成 $0$，同时也要把上方的元素也全部消成 $0$。

行最简形矩阵 $B$ 是由矩阵 $A$ 唯一确定的，行阶梯形矩阵 $B$ 的行数，即阶梯数，也是由矩阵 $A$ 唯一确定的。阶梯数也称为矩阵 $A$ 的 **秩**（rank），阶梯数越高则秩越高。读者可以把秩理解为“等级”，事实上“秩”与“等级”对应于英语的同一个单词。

## 概述

算法是对每个方程中的变量进行“顺序消除”，直到每个方程只剩下一个变量。如果$n=m$，可以将其视为将矩阵$A$转换为单位矩阵，并在这种明显的情况下求解方程，其中解是唯一的，并且等于系数$b_i$。

### 消元法理论的核心

Gauss-Jordan算法的核心是初等行变换：

* 对换变换：可以交换两个方程。
* 倍乘变换和倍加变换：任何方程都可以替换为该行（具有非零系数）和其他一些行（具有任意系数）的线性组合。

在第一步中，Gauss-Jordan算法将第一行除以$a_{11}$。然后，该算法将第一行添加到其余行中，使第一列中的系数变为全零。为了实现这一点，要在第i行添加第一行乘以$-a_{i1}$，同时对向量$b$执行此操作。

在某种意义上，它的行为就像向量$b$是矩阵$A$的第 $m+1$ 列一样，两者拼起来构成增广矩阵。

因此，在第一步之后，矩阵$A$的第一列将由第一行的$1$和其他行的$0$组成。

类似地，执行算法的第二步，考虑第二行的第二列。首先，该行除以$a_{22}$，然后从其他行中减去该行，使所有第二列变为$0$（第二行除外）。

对矩阵$A$的所有列继续此过程。如果$n=m$，则$A$将成为单位矩阵。

未引入对换变换的 Gauss-Jordan 算法与LU分解的算法几乎一致，LU分解的算法仅执行上三角部分。

## 高斯消元五步骤法

## 解释

高斯消元法在将增广矩阵化为最简形后对于自由未知量的赋值，需要掌握线性相关知识，且赋值存在人工经验的因素，使得在学习过程中有一定的困难，将高斯消元法划分为五步骤，从而提出五步骤法，内容如下：

1. 增广矩阵行初等行变换为行最简形；

2. 还原线性方程组；

3. 求解第一个变量；

4. 补充自由未知量；

5. 列表示方程组通解。

利用实例进一步说明该算法的运作情况。

## 过程

例二：利用高斯消元法五步骤法求解线性方程组：

$$
\left\{\begin{aligned}
2x_1+5x_3+6x_4&=9 \notag \\
x_3+x_4&=-4 \notag \\
2x_3+2x_4&=-8 \notag
\end{aligned}\right.
$$

### 增广矩阵行（初等）变换为行最简形

所谓增广矩阵，即为方程组系数矩阵 $A$ 与常数列 $b$ 的并生成的新矩阵，即 $(A | b)$，增广矩阵行初等变换化为行最简形，即是利用了高斯消元法的思想理念，省略了变量而用变量的系数位置表示变量，增广矩阵中用竖线隔开了系数矩阵和常数列，代表了等于符号。

$$
\left(\begin{matrix}
2 & 0 & 5 & 6 \\
0 & 0 & 1 & 1 \\
0 & 0 & 2 & 2
\end{matrix} \middle|
\begin{matrix}
9 \\
-4 \\
-8
\end{matrix} \right)
$$

$$
\xrightarrow{r_3-2r_2}
\left(\begin{matrix}
2 & 0 & 5 & 6 \\
0 & 0 & 1 & 1 \\
0 & 0 & 0 & 0
\end{matrix} \middle|
\begin{matrix}
9 \\
-4 \\
0
\end{matrix} \right)
$$

化为行阶梯形

$$
\xrightarrow{\frac{r_1}{2}}
\left(\begin{matrix}
1 & 0 & 2.5 & 3 \\
0 & 0 & 1 & 1 \\
0 & 0 & 0 & 0
\end{matrix} \middle|
\begin{matrix}
4.5 \\
-4 \\
0
\end{matrix} \right)
$$

$$
\xrightarrow{r_1-r_2 \times 2.5}
\left(\begin{matrix}
1 & 0 & 0 & 0.5 \\
0 & 0 & 1 & 1 \\
0 & 0 & 0 & 0
\end{matrix} \middle|
\begin{matrix}
14.5 \\
-4 \\
0
\end{matrix} \right)
$$

化为最简形

### 还原线性方程组

$$
\left\{\begin{aligned}
x_1+0.5x_4 &= 14.5 \notag\\
x_3+x_4 &= -4 \notag \\
\end{aligned}\right.
$$

解释

> 所谓的还原线性方程组，即是在行最简形的基础上，将之重新书写为线性方程组的形式，即将行最简形中各位置的系数重新赋予变量，中间的竖线还原为等号。

### 求解第一个变量

$$
\left\{\begin{aligned}
x_1 &= -0.5x_4+14.5\notag \\
x_3 &= -x_4-4\notag
\end{aligned}\right.
$$

解释

> 即是对于所还原的线性方程组而言，将方程组中每个方程的第一个变量，用其他量表达出来。如方程组两方程中的第一个变量 $x_1$ 和 $x_3$

### 补充自由未知量

$$
\left\{\begin{aligned}
x_1 &= -0.5x_4+14.5 \notag \\
x_2 &= x_2 \notag \\
x_3 &= -x_4-4 \notag \\
x_4 &= x_4 \notag
\end{aligned}\right.
$$

解释

> 第 3 步中，求解出变量 $x_1$ 和 $x_3$，从而说明了方程剩余的变量 $x_2$ 和 $x_4$ 不受方程组的约束，是自由未知量，可以取任意值，所以需要在第 3 步骤解得基础上进行解得补充，补充的方法为 $x_2 = x_2,x_4 = x_4$，这种解得补充方式符合自由未知量定义，并易于理解，因为是自由未知量而不受约束，所以只能自己等于自己。

### 列表示方程组的通解

$$
\begin{aligned}
\begin{pmatrix} x_1 \\ x_2 \\ x_3 \\ x_4 \end{pmatrix} &=
\begin{pmatrix} 0 \\ 1 \\ 0 \\ 0 \end{pmatrix} x_2+
\begin{pmatrix} -0.5 \\ 0 \\ -1 \\ 1 \end{pmatrix} x_4 +
\begin{pmatrix} 14.5 \\ 0 \\ -4 \\ 0 \end{pmatrix} \notag \\
&= \begin{pmatrix} 0 \\ 1 \\ 0 \\ 0 \end{pmatrix} C_1+
\begin{pmatrix} -0.5 \\ 0 \\ -1 \\ 1 \end{pmatrix} C_2 +
\begin{pmatrix} 14.5 \\ 0 \\ -4 \\ 0 \end{pmatrix} \notag
\end{aligned}
$$

其中 $C_1$ 和 $C_2$ 为任意常数。

解释

> 即在第 4 步的基础上，将解表达为列向量组合的表示形式，同时由于 $x_2$ 和 $x_4$ 是自由未知量，可以取任意值，所以在解得右边，令二者分别为任意常数 $C_1$ 和 $C_2$，即实现了对方程组的求解。

* * *

## 矩阵的等价

矩阵的 **等价** 就是矩阵的秩相同。秩相同的矩阵相互等价，秩不同的矩阵相互不等价。

只要矩阵 $A$ 与矩阵 $B$ 的秩相同，就一定存在可逆矩阵 $P$,$Q$ 使得：

$$
PAQ=B
$$

这是因为，右乘操作相当于对列操作，可以将行最简形矩阵进行列重排，再列消元，得到“标准形矩阵”，只有左上角是单位阵。由于秩相同，标准型矩阵就相同。于是根据可逆性一整理，就能整理成左乘 $P$ 右乘 $Q$ 的形式。

引出秩的概念，是“按行看”观点的完结，后文线性相关部分进入重要的“按列看”观点。


## 搜索旋转（pivoting）元素

在第 $i$ 步，如果 $a_{i}$ 为零，则无法直接应用所描述的方法。必须首先选择一个旋转（pivoting）行：找到矩阵中为相应元素不为零的一行，然后交换到当前第 $i$ 行。

注意，这里交换的是行而不是列。这是因为如果交换列，那么在找到解决方案时，必须记住交换回正确的位置。因此，交换行要容易得多。

在许多实现中，当 $a_{ii} \neq 0$时，仍然使用一些启发式算法（heuristic）来交换第 $i$ 行和一些旋转（pivoting）行，例如选择绝对值最大的 $a_{ji}$ 为旋转行。在后面的步骤中，此启发式算法用于减少矩阵的值范围。如果没有这种启发式方法，即使对于大小约为 $20$ 的矩阵，错误也会太大，并可能导致C++浮点数据类型溢出。

## 一般情况

在 $m=n$，并且方程组的系数矩阵可逆，并且方程组具有唯一解的情况下，上述算法将 $A$ 转换为单位矩阵。

现在考虑一般情况，其中 $n$ 和 $m$ 不一定相等。在这些情况下，可能找不到第 $i$ 步中的旋转元素。这意味着在第 $i$ 列上，从当前位置开始，所有下方的元素都为零。在这种情况下，要么变量 $x_i$ 没有可能的值，意味着 SLAE 无解；要么 $x_i$ 是一个独立变量，可以取任意值。在 Gauss-Jordan 算法中，应该继续后续变量的工作，只需跳过第 $i$ 列，也等价于删除矩阵的第 $i$ 列。

因此可以发现一些变量是独立的。当变量的数量 $m$ 大于方程的数量 $n$ 时，将至少找到 $m-n$ 个独立的自变量。

通常，如果您找到至少一个自变量，它可以取任意值，而其他因变量则通过自变量来表示。这意味着方程组可能有无穷多个解。当存在自变量，且其余未处理的方程至少有一个非零常数项时，SLAE 也可能无解。可以通过给所有自变量赋值 $0$ 来检查这一点，计算其他变量，然后插入原始 SLAE 以检查它们是否满足要求。

## 实现

以下是 Gauss-Jordan 算法的实现。使用启发式算法选择旋转行，在当前列中选择最大值。

函数 gauss 的输入是系数矩阵 $a$ 最后一列拼上向量 $b$ 构成的增广矩阵。

函数返回方程组的解数。如果至少存在一个解，那么它将在向量 $ans$ 中返回。

```cpp
const double EPS = 1e-9;
const int INF = 2; // it doesn't actually have to be infinity or a big number

int gauss (vector < vector<double> > a, vector<double> & ans) {
	int n = (int) a.size();
	int m = (int) a[0].size() - 1;

	vector<int> where (m, -1);
	for (int col=0, row=0; col<m && row<n; ++col) {
		int sel = row;
		for (int i=row; i<n; ++i)
			if (abs (a[i][col]) > abs (a[sel][col]))
				sel = i;
		if (abs (a[sel][col]) < EPS)
			continue;
		for (int i=col; i<=m; ++i)
			swap (a[sel][i], a[row][i]);
		where[col] = row;

		for (int i=0; i<n; ++i)
			if (i != row) {
				double c = a[i][col] / a[row][col];
				for (int j=col; j<=m; ++j)
					a[i][j] -= a[row][j] * c;
			}
		++row;
	}

	ans.assign (m, 0);
	for (int i=0; i<m; ++i)
		if (where[i] != -1)
			ans[i] = a[where[i]][m] / a[where[i]][i];
	for (int i=0; i<n; ++i) {
		double sum = 0;
		for (int j=0; j<m; ++j)
			sum += ans[j] * a[i][j];
		if (abs (sum - a[i][m]) > EPS)
			return 0;
	}

	for (int i=0; i<m; ++i)
		if (where[i] == -1)
			return INF;
	return 1;
}
```

实现的说明：

*该函数使用两个指针-当前列 $col$ 和当前行 $row$。

*对于每个变量 $x_i$，值 $where(i)$ 是该列不为零的行。这个向量是必需的，因为一些变量可以是独立的。

*在这个实现中，当前的第 $i$ 行没有如上所述被 $a_{ii}$ 分割，因此最终矩阵不是单位矩阵，尽管分割第 $i$ 行显然有助于减少错误。

*找到解决方案后，将其插入矩阵中，以检查系统是否至少有一个解决方案。如果测试解决方案成功，则函数返回 $1$ 或 $\inf$，具体取决于是否至少有一个自变量。

## 复杂度

算法由 $m$ 个阶段组成，每个阶段：

*搜索并重新排列旋转行。当使用上述启发式时，这需要 $O(n + m)$ 。

*如果找到当前列中的旋转元素，则必须将此方程添加到所有其他方程中，这需要花费 $O(nm)$ 时间。

因此，算法的最终复杂度为 $O(\min (n, m)nm)$。

在 $n=m$ 的情况下，复杂度仅为 $O(n^3)$。

请注意，当 SLAE 的模数为 $2$ 时，系统的求解速度会更快，如下所述。

## 算法加速

通过将算法分为两个阶段：正向和反向，可以将之前的实现速度提高两倍：

*正向：与前面的实现类似，但当前行只添加到它后面的行中。因此得到一个上三角矩阵而不是对角矩阵。

*反向：当矩阵是上三角矩阵时，首先计算最后一个变量的值。然后代入此值求解下一个变量的值。然后代入这两个值求解下一个变量的值。

反向只需要 $O(nm)$，这比正向快得多。在正向阶段，将操作数减少一半，从而减少实现的运行时间。

事实上，正向阶段等价于系数矩阵的 LU 分解的过程，将系数矩阵变换为上三角矩阵 U。由于向量 b 同时进行行变换，可以略去左侧的变换矩阵 L。

## 求解取模 SLAE

取模的 SLAE 求解仍然可以使用所描述的算法。如果模数为 2，可以使用逐位运算和 C++ bitset 类型，更快地执行 Gauss-Jordan 算法：

```cpp
int gauss (vector < bitset<N> > a, int n, int m, bitset<N> & ans) {
	vector<int> where (m, -1);
	for (int col=0, row=0; col<m && row<n; ++col) {
		for (int i=row; i<n; ++i)
			if (a[i][col]) {
				swap (a[i], a[row]);
				break;
			}
		if (! a[row][col])
			continue;
		where[col] = row;

		for (int i=0; i<n; ++i)
			if (i != row && a[i][col])
				a[i] ^= a[row];
		++row;
	}
        // The rest of implementation is the same as above
}
```

由于使用位压缩，实现不仅更短，而且速度快 32 倍。

## 选择旋转行的不同启发法

对于使用什么样的启发法没有一般规则。

上述实现中使用的启发式方法，在实践中效果很好。它实现了和完全旋转（full pivoting）几乎相同的效果，即在其子矩阵的全部行和全部列所有元素中搜索旋转行。

不过应该注意，这两种启发式都取决于原始方程的缩放比例。例如，如果其中一个等式乘以$10^6$，那么几乎可以肯定在第一步中会选择这个等式作为旋转行。因此可以修改为更复杂的启发式，称为隐式旋转（implicit pivoting）。

隐式旋转将整行进行比较，就像每行都被规范化了一样，这样最大的元素将是一个整体。要实现此方法，需要保持每行的最大值为 $1$，但这可能会导致累积错误的增加。

## 改进算法

尽管有各种各样的启发式算法，Gauss-Jordan 算法仍然会在特殊的矩阵中导致较大的误差，即使矩阵的大小为 $50 - 100$。

有时必须通过应用简单的数值方法，例如简单迭代法，来改进得到的 Gauss-Jordan 解。

求解分为两步：首先应用 Gauss-Jordan 算法，然后以得到的解为初始值采用数值方法。

## 应用

### 行列式计算

#### 解释

$N \times N$ 方阵行列式（Determinant）可以理解为所有列向量所夹的几何体的有向体积

例如：

$$
\begin{vmatrix}
1 & 0 \\
0 & 1 \end{vmatrix} = 1
$$

$$
\begin{vmatrix}
1 & 2 \\
2 & 1 \end{vmatrix} = -3
$$

行列式有公式

$$
\operatorname{det}(A)=\sum_{\sigma \in S_{n}} \operatorname{sgn}(\sigma) \prod_{i=1}^{n} a_{i, \sigma(i)}
$$

其中 $S_n$ 是指长度为 $n$ 的全排列的集合，$\sigma$ 就是一个全排列，如果 $\sigma$ 的逆序对对数为偶数，则 $\operatorname{sgn}(\sigma)=1$，否则 $\operatorname{sgn}(\sigma)=−1$。

通过体积概念理解行列式不变性是一个非常简单的办法：

- 矩阵转置，行列式不变；

- 矩阵行（列）交换，行列式取反；

- 矩阵行（列）相加或相减，行列式不变；

- 矩阵行（列）所有元素同时乘以数 $k$，行列式等比例变大。

> 由此，对矩阵应用高斯消元之后，我们可以得到一个对角线矩阵，此矩阵的行列式由对角线元素之积所决定。其符号可由交换行的数量来确定（如果为奇数，则行列式的符号应颠倒）。因此，我们可以在 $O(n^3)$ 的复杂度下使用高斯算法计算矩阵。
>
> 注意，如果在某个时候，我们在当前列中找不到非零单元，则算法应停止并返回 0。

* * *

#### 实现

```c++
const double EPS = 1E-9;
int n;
vector<vector<double> > a(n, vector<double>(n));

double det = 1;
for (int i = 0; i < n; ++i) {
  int k = i;
  for (int j = i + 1; j < n; ++j)
    if (abs(a[j][i]) > abs(a[k][i])) k = j;
  if (abs(a[k][i]) < EPS) {
    det = 0;
    break;
  }
  swap(a[i], a[k]);
  if (i != k) det = -det;
  det *= a[i][i];
  for (int j = i + 1; j < n; ++j) a[i][j] /= a[i][i];
  for (int j = 0; j < n; ++j)
    if (j != i && abs(a[j][i]) > EPS)
      for (int k = i + 1; k < n; ++k) a[j][k] -= a[i][k] * a[j][i];
}

cout << det;
```

### 矩阵求逆

对于方阵 $A$，若存在方阵 $A^{-1}$，使得 $A \times A^{-1} = A^{-1} \times A = I$，则称矩阵 $A$ 可逆，$A^{-1}$ 被称为它的逆矩阵。

给出 $n$ 阶方阵 $A$，求解其逆矩阵的方法如下：

1. 构造 $n \times 2n$ 的矩阵 $(A, I_n)$；
2. 用高斯消元法将其化简为最简形 $(I_n, A^{-1})$，即可得到 $A$ 的逆矩阵 $A^{-1}$。如果最终最简形的左半部分不是单位矩阵 $I_n$，则矩阵 $A$ 不可逆。

根据上文，初等行变换等价于左乘初等矩阵，那么只要矩阵 $A$ 的逆存在，将 $A$ 变为 $I$ 的变换，等价于将 $A$ 左乘一系列初等矩阵得到 $I$，左乘的一系列初等矩阵构成了矩阵 $A$ 的逆。所以，矩阵 $I$ 左乘这一系列初等矩阵会得到矩阵 $A$ 的逆，矩阵 $I$ 经过同样的变换也会变为 $A$ 的逆。

### 生成树计数

一个无向图的生成树个数为邻接矩阵度数矩阵去一行一列的行列式。

详见：[矩阵树定理](../../graph/matrix-tree.md)

例如，一个正方形图的生成树个数

$$
\begin{pmatrix}
2 & 0 & 0 & 0 \\
0 & 2 & 0 & 0 \\
0 & 0 & 2 & 0 \\
0 & 0 & 0 & 2 \end{pmatrix}-\begin{pmatrix}
0 & 1 & 0 & 1 \\
1 & 0 & 1 & 0 \\
0 & 1 & 0 & 1 \\
1 & 0 & 1 & 0 \end{pmatrix}=\begin{pmatrix}
2 & -1 & 0 & -1 \\
-1 & 2 & -1 & 0 \\
0 & -1 & 2 & -1 \\
-1 & 0 & -1 & 2 \end{pmatrix}
$$

$$
\begin{vmatrix}
2 & -1 & 0 \\
-1 & 2 & -1 \\
0 & -1 & 2 \end{vmatrix} = 4
$$

可以用高斯消元解决，时间复杂度为 $O(n^3)$。

??? note "实现"
    ```cpp
    #include <algorithm>
    #include <cassert>
    #include <cmath>
    #include <cstdio>
    #include <cstring>
    #include <iostream>
    using namespace std;
    #define MOD 100000007
    #define eps 1e-7
    
    struct matrix {
      static const int maxn = 20;
      int n, m;
      double mat[maxn][maxn];
    
      matrix() { memset(mat, 0, sizeof(mat)); }
    
      void print() {
        cout << "MATRIX " << n << " " << m << endl;
        for (int i = 0; i < n; i++) {
          for (int j = 0; j < m; j++) {
            cout << mat[i][j] << "\t";
          }
          cout << endl;
        }
      }
    
      void random(int n) {
        this->n = n;
        this->m = n;
        for (int i = 0; i < n; i++)
          for (int j = 0; j < n; j++) mat[i][j] = rand() % 100;
      }
    
      void initSquare() {
        this->n = 4;
        this->m = 4;
        memset(mat, 0, sizeof(mat));
        mat[0][1] = mat[0][3] = 1;
        mat[1][0] = mat[1][2] = 1;
        mat[2][1] = mat[2][3] = 1;
        mat[3][0] = mat[3][2] = 1;
        mat[0][0] = mat[1][1] = mat[2][2] = mat[3][3] = -2;
        this->n--;  // 去一行
        this->m--;  // 去一列
      }
    
      double gauss() {
        double ans = 1;
        for (int i = 0; i < n; i++) {
          int sid = -1;
          for (int j = i; j < n; j++)
            if (abs(mat[j][i]) > eps) {
              sid = j;
              break;
            }
          if (sid == -1) continue;
          if (sid != i) {
            for (int j = 0; j < n; j++) {
              swap(mat[sid][j], mat[i][j]);
              ans = -ans;
            }
          }
          for (int j = i + 1; j < n; j++) {
            double ratio = mat[j][i] / mat[i][i];
            for (int k = 0; k < n; k++) {
              mat[j][k] -= mat[i][k] * ratio;
            }
          }
        }
        for (int i = 0; i < n; i++) ans *= mat[i][i];
        return abs(ans);
      }
    };
    
    int main() {
      srand(1);
      matrix T;
      // T.random(2);
      T.initSquare();
      T.print();
      double ans = T.gauss();
      T.print();
      cout << ans << endl;
    }
    ```

### 解异或方程组

异或方程组是指形如

$$
\begin{cases}
a_{1,1}x_1 \oplus a_{1,2}x_2 \oplus \cdots \oplus a_{1,n}x_n &= b_1\\
a_{2,1}x_1 \oplus a_{2,2}x_2 \oplus \cdots \oplus a_{2,n}x_n &= b_2\\
\cdots &\cdots \\ a_{m,1}x_1 \oplus a_{m,2}x_2 \oplus \cdots \oplus a_{m,n}x_n &= b_1
\end{cases}
$$

的方程组，其中 $\oplus$ 表示“按位异或”（即 `xor` 或 C++ 中的 `^`），且式中所有系数/常数（即 $a_{i,j}$ 与 $b_i$）均为 $0$ 或 $1$。

由于“异或”符合交换律与结合律，故可以按照高斯消元法逐步消元求解。值得注意的是，我们在消元的时候应使用“异或消元”而非“加减消元”，且不需要进行乘除改变系数（因为系数均为 $0$ 和 $1$）。

注意到异或方程组的增广矩阵是 $01$ 矩阵（矩阵中仅含有 $0$ 与 $1$），所以我们可以使用 C++ 中的 `std::bitset` 进行优化，将时间复杂度降为 $O(\dfrac{n^2m}{\omega})$，其中 $n$ 为元的个数，$m$ 为方程条数，$\omega$ 一般为 $32$（与机器有关）。

参考实现：

```cpp
std::bitset<1010> matrix[2010];  // matrix[1~n]：增广矩阵，0 位置为常数

std::vector<bool> GaussElimination(
    int n, int m)  // n 为未知数个数，m 为方程个数，返回方程组的解（多解 /
                   // 无解返回一个空的 vector）
{
  for (int i = 1; i <= n; i++) {
    int cur = i;
    while (cur <= m && !matrix[cur].test(i)) cur++;
    if (cur > m) return std::vector<bool>(0);
    if (cur != i) swap(matrix[cur], matrix[i]);
    for (int j = 1; j <= m; j++)
      if (i != j && matrix[j].test(i)) matrix[j] ^= matrix[i];
  }
  std::vector<bool> ans(n + 1, 0);
  for (int i = 1; i <= n; i++) ans[i] = matrix[i].test(0);
  return ans;
}
```

## 练习题

* [Codeforces - 巫师和赌注](http://codeforces.com/contest/167/problem/E)
* [luogu - SDOI2010 外星千足虫](https://www.luogu.com.cn/problem/P2447)
* [Spoj - Xor Maximization](http://www.spoj.com/problems/XMAX/)
* [Codechef - Knight Moving](https://www.codechef.com/SEP12/problems/KNGHTMOV)
* [Lightoj - Graph Coloring](http://lightoj.com/volume_showproblem.php?problem=1279)
* [UVA 12910 - Snakes and Ladders](https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=4775)
* [TIMUS1042 Central Heating](http://acm.timus.ru/problem.aspx?space=1&num=1042)
* [TIMUS1766 Humpty Dumpty](http://acm.timus.ru/problem.aspx?space=1&num=1766)
* [TIMUS1266 Kirchhoff's Law](http://acm.timus.ru/problem.aspx?space=1&num=1266)
* [Codeforces - No game no life](https://codeforces.com/problemset/problem/1411/G)

**本页面主要译自博文[Метод Гаусса решения системы линейных уравнений](http://e-maxx.ru/algo/linear_systems_gauss)与其英文翻译版[Gauss method for solving system of linear equations](https://cp-algorithms.com/linear_algebra/linear-system-gauss.html)。其中俄文版版权协议为 Public Domain + Leave a Link；英文版版权协议为 CC-BY-SA 4.0。** 
