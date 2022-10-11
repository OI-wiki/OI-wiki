LU 分解又名为三角分解，将一个可逆阵 $A$ 分解为一个下三角矩阵 $L$ 和一个上三角矩阵 $U$ 的乘积，即具有基本形式：

$$
A=LU
$$

有时将上三角矩阵记为 $R$，等式记为 $A=LR$，称 LU 分解为“LR 分解”，称后文的 LDU 分解为“LDR 分解”等等，其实两者完全是一回事，只是翻译与记法不同。

LU 分解由消元法演变而来，较为常见的有两种：

- 杜利特尔（Doolittle）分解：$L$ 为单位下三角矩阵，$U$ 为上三角矩阵。
- 克劳特（Crout，德语拼作 Kraut）分解：$L$ 为下三角矩阵，$U$ 为单位上三角矩阵。

这两种分解仅在主对角线上不同，Crout 分解可以视作 Doolittle 分解的转置。由于解方程时常使用初等行变换，一般 Doolittle 分解更加实用。

LU 分解不止有这两类，只要分解为下三角矩阵 $L$ 与上三角矩阵 $U$，均构成一个 LU 分解。矩阵 $A$ 只要可以进行 LU 分解，那么 Doolittle 分解和 Crout 分解都是唯一的。

如果中间增设一个对角矩阵 $D$，那么 LDU 分解只要可行就是唯一的，无需进一步分类。

对于正定矩阵或者厄米（Hermite，法语中字母 h 不发音）矩阵，常见的还有乔莱斯基（Cholesky）分解，Cholesky 分解也是一种 LU 分解。

对于一般的可逆阵 $A$，LU 分解不一定可以进行。这是因为，虽然可逆阵 $A$ 的行列式不为 $0$，但其中可能含有行列式为 $0$ 的子式。

如果在可逆阵 $A$ 左边增加一个置换矩阵 $P$，等价于对行顺序进行调整，则保证了新的矩阵 $PA$ 总是可以进行 LU 分解。于是形式变为：

$$
PA=LU
$$

这种分解方法称为 LUP 分解。

## 顺序主子式

对于一个方阵 $A$，它的 $k$ 阶顺序主子式是指它的前 $k$ 行和前 $k$ 列元素组成的行列式 $\det A_k$。

一个 $n$ 阶方阵 $A$ 共有 $n$ 个顺序主子式。按照阶数排列，顺序主子式的位置从左上角开始，逐步在下方和右方添加新的行和列。

## Doolittle 分解

定理：设 $A$ 是可逆矩阵，那么存在唯一的单位下三角矩阵 $L$ 和上三角矩阵 $U$ 使得：

$$
A=LU
$$

等价于 $A$ 的顺序主子式均非零。

该定理如果把 $L$ 改为下三角矩阵，$U$ 改为单位上三角矩阵，相应结论变为 Crout 分解的结论，仍然成立。

### 算法

Doolittle 分解将矩阵 $A$ 分解为 $A=LU$，其中 $L$ 为单位下三角矩阵，$U$ 为上三角矩阵。

可逆矩阵有 Doolittle 分解，当且仅当其所有顺序主子式都非零，并且只要有 Doolittle 分解即为唯一的。

由矩阵乘法：

$$
A=LU=\begin{pmatrix}
1 &  &  & 0\\
l_{21} & 1 &  & \\
\vdots &  & \ddots & \\
l_{n1} & l_{n2} & \cdots & 1\\
\end{pmatrix}\begin{pmatrix}
u_{11} & u_{12} & \cdots & u_{1n}\\
0 & u_{22} & \cdots & u_{2n}\\
\vdots &  & \ddots & \cdots\\
0 & \cdots & 0 & u_{nn}\\
\end{pmatrix}
$$

可以得到元素之间的对应关系，进而给出算法。虽然计算的是 Doolittle 分解，但是该算法的名字叫做 Crout 算法（Crout's method）。该算法具有 $O(n^3)$ 的时间复杂度。

设 $A$ 为 $n$ 阶方阵，使用以下步骤计算矩阵 $L$ 和 $U$：

- 对于 $i=1,2,\cdots,n$，设 $l_{ii}=1$。

在《算法导论》上给出的最终方阵是由 $L$ 和 $U$ 拼起来构成的 $n$ 阶方阵，主对角线上是 $U$，因此这一步被省略。

- 矩阵 $U$ 的第 $1$ 行与矩阵 $A$ 完全相同：

$$
u_{1j}=a_{1j}
$$

- 矩阵 $L$ 的第 $1$ 列，从第 $2$ 个元素开始，均为相应元素与左上角元素的比值：

$$
l_{i1}=\frac{a_{1j}}{u_{11}}
$$

剩余的部分也是循环进行求解。在手算的情形，可以先求一行 $U$，再求一列 $L$：

$$
u_{ki}=a_{ki}-\sum_{t=1}^{k-1}l_{kt}u_{tj}
$$

$$
l_{ik}=\frac{1}{u_{kk}}\left(a_{ik}-\sum_{t=1}^{k-1}l_{it}u^{tk}\right)
$$

在写代码的时候为了方便，计算 $U$ 也可以改为按列进行。对于每个列 $j=1,2,\cdots,n$，执行两步：

- 对于位置 $i=1,2,\cdots,j$，求解这列 $U$：

$$
u_{ij}=a_{ij}-\sum_{k=1}^{i-1}l_{ik}u_{kj}
$$

- 对于位置 $i=j+1,j+2,\cdots,n$，求解这列 $L$：

$$
l_{ij}=\frac{1}{u_{jj}}\left(a_{ij}-\sum_{k=1}^{j-1}l_{ik}u_{kj}\right)
$$

使用初等行变换的办法，也可以求 Doolittle 分解。初等行变换等价于左乘初等矩阵，而左边的 $L$ 是单位下三角矩阵，所以只需要用到倍加变换，并且需要按照一定的顺序进行。

在《算法导论》上的 Gauss 消元，使用 LUP 分解。对换变换对应于置换矩阵 $P$，在 LU 分解中没有体现。

《算法导论》上的算法将 $A$ 变形成为 $U$，行列式不变，因此只进行了倍加变换。即，所有行（除了当前行）减去若干倍当前行，消去此元。

每个步骤只对对角线当前元素的右下角子矩阵进行操作：

- 对角线元素下方这一列，即矩阵 $L$ 的这一列，乘非零数。
- 对角线元素右下方整个部分进行倍加操作，当前行被留下作为矩阵 $U$ 的行。

算法变为：

```c
for (i = k + 1; i <= n; i++) {
  a[i][k] /= a[k][k];  // 对矩阵L的当前列乘非零数
  for (j = k + 1; j <= n; j++) {
    a[i][j] -=
        a[i][k] *
        a[k][j];  // 对右下方整个部分进行倍乘操作，当前行被留下作为矩阵 $U$ 的行
  }
}
```

### 实现

这里以使用 Doolittle 分解计算矩阵的行列式为例。求出 $L$ 和 $U$ 之后，$A$ 的行列式等于矩阵 $U$ 主对角线上所有元素的乘积。

这里给出一个 java 版本的实现。

```java
static BigInteger det (BigDecimal a [][], int n) {
	try {

	for (int i=0; i<n; i++) {
		boolean nonzero = false;
		for (int j=0; j<n; j++)
			if (a[i][j].compareTo (new BigDecimal (BigInteger.ZERO)) > 0)
				nonzero = true;
		if (!nonzero)
			return BigInteger.ZERO;
	}

	BigDecimal scaling [] = new BigDecimal [n];
	for (int i=0; i<n; i++) {
		BigDecimal big = new BigDecimal (BigInteger.ZERO);
		for (int j=0; j<n; j++)
			if (a[i][j].abs().compareTo (big) > 0)
				big = a[i][j].abs();
		scaling[i] = (new BigDecimal (BigInteger.ONE)) .divide
			(big, 100, BigDecimal.ROUND_HALF_EVEN);
	}

	int sign = 1;

	for (int j=0; j<n; j++) {
		for (int i=0; i<j; i++) {
			BigDecimal sum = a[i][j];
			for (int k=0; k<i; k++)
				sum = sum.subtract (a[i][k].multiply (a[k][j]));
			a[i][j] = sum;
		}

		BigDecimal big = new BigDecimal (BigInteger.ZERO);
		int imax = -1;
		for (int i=j; i<n; i++) {
			BigDecimal sum = a[i][j];
			for (int k=0; k<j; k++)
				sum = sum.subtract (a[i][k].multiply (a[k][j]));
			a[i][j] = sum;
			BigDecimal cur = sum.abs();
			cur = cur.multiply (scaling[i]);
			if (cur.compareTo (big) >= 0) {
				big = cur;
				imax = i;
			}
		}

		if (j != imax) {
			for (int k=0; k<n; k++) {
				BigDecimal t = a[j][k];
				a[j][k] = a[imax][k];
				a[imax][k] = t;
			}

			BigDecimal t = scaling[imax];
			scaling[imax] = scaling[j];
			scaling[j] = t;

			sign = -sign;
		}

		if (j != n-1)
			for (int i=j+1; i<n; i++)
				a[i][j] = a[i][j].divide
					(a[j][j], 100, BigDecimal.ROUND_HALF_EVEN);

	}

	BigDecimal result = new BigDecimal (1);
	if (sign == -1)
		result = result.negate();
	for (int i=0; i<n; i++)
		result = result.multiply (a[i][i]);

	return result.divide
		(BigDecimal.valueOf(1), 0, BigDecimal.ROUND_HALF_EVEN).toBigInteger();
	}
	catch (Exception e) {
		return BigInteger.ZERO;
	}
}
```

### 应用

如果线性方程组 $Ax=b$ 的系数矩阵 $A$ 可以进行 LU 分解 $A=LU$，则 $Ax=b$ 与以下方程组同解：

$$
Ly=b
$$

$$
Ux=y
$$

## LUP 分解

LUP 分解也称列主元三角分解，在 LU 分解的基础上增加主元的选取。由于置换矩阵 $P$ 不唯一，LUP 分解也不唯一。

定理：若 $A$ 可逆。则一定存在置换矩阵 $P$，使得 $PA$ 有三角分解 $PA=LU$，其中 $L$ 是单位下三角矩阵，而 $U$ 是上三角矩阵。

在《算法导论》上讲述的 Gauss 消元，使用了 Doolittle 分解（而不是 Crout 分解）。在使用 LUP 分解，增加左乘置换阵 $P$ 之后，等式变为 $PA=LU$，并将 $L$ 和 $U$ 两个方阵拼成新方阵，单位下三角阵 $L$ 的主对角线被省略，主对角线为 $U$ 的主对角线。

## LDU 分解

LDU 分解是 LU 分解的推广。

不同于 Doolittle 分解和 Crout 分解，在 LDU 分解中的矩阵 $L$ 和 $U$ 均为单位三角矩阵。

设 $A$ 是可逆矩阵，则存在唯一的单位下三角矩阵 $L$，对角矩阵 $D=diag\{d_1,d_2,\cdots,d_n\}$ 和单位上三角矩阵 $U$，使得：

$$
A=LDU
$$

等价于 $A$ 的顺序主子式均非零。

## Cholesky 分解

Cholesky 分解也称平方根分解。

设 $A$ 是正定 Hermite 矩阵，则存在下三角矩阵 $G$ 使得：

$$
A=GG^H
$$

事实上 Hermite 矩阵一定酉相似于实对角阵，将实对角阵各元素进行开方并乘到两边的矩阵中，就可以得到上述形式。因此 Hermite 矩阵一定酉合同于单位阵。

这里指出，如果 Hermite 矩阵是正定的，则存在下三角矩阵完成上述酉合同变换。

**本页面主要译自博文 [Calculating the determinant using Kraut method](https://cp-algorithms.com/linear_algebra/determinant-kraut.html)，版权协议为 CC-BY-SA 4.0。**
