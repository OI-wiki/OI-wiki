## 定义

对于矩阵 $A$，主对角线是指 $A[i][i]$ 的元素。

一般用 $I$ 来表示单位矩阵，就是主对角线上为 1，其余位置为 0。

## 性质

### 矩阵的逆

$A$ 的逆矩阵 $P$ 是使得 $A \times P = I$ 的矩阵。

逆矩阵可以用 [高斯消元](/math/gauss/) 的方式来求。

## 运算

矩阵的加减法是逐个元素进行的。

### 矩阵乘法

矩阵相乘只有在第一个矩阵的列数和第二个矩阵的行数相同时才有意义。

设 $A$ 为 $P \times M$ 的矩阵，$B$ 为 $M \times Q$ 的矩阵，设矩阵 $C$ 为矩阵 $A$ 与 $B$ 的乘积，

其中矩阵 $C$ 中的第 $i$ 行第 $j$ 列元素可以表示为：

$$
C_{ij} = \sum_{k=1}^MA_{i,k}B_{k,j}
$$

矩阵乘法满足结合律，不满足一般的交换律。

利用结合律，矩阵乘法可以利用 [快速幂](/math/quick-pow/) 的思想来优化。

在比赛中，由于线性递推式可以表示成矩阵乘法的形式，也通常用矩阵快速幂来求线性递推数列的某一项。

## 参考代码

一般来说，可以用一个二维数组来模拟矩阵。

```c++
struct mat {
  LL a[sz][sz];
  inline mat() { memset(a, 0, sizeof a); }
  inline mat operator+(const mat& T) const {
    mat res;
    for (int i = 0; i < 3; ++i)
      for (int j = 0; j < 3; ++j)
        res.a[i][j] = (a[i][j] - T.a[i][j] + MOD) % MOD;
    return res;
  }
  inline mat operator-(const mat& T) const {
    mat res;
    for (int i = 0; i < 3; ++i)
      for (int j = 0; j < 3; ++j) res.a[i][j] = (a[i][j] + T.a[i][j]) % MOD;
    return res;
  }
  inline mat operator*(const mat& T) const {
    mat res;
    for (int i = 0; i < 3; ++i)
      for (int j = 0; j < 3; ++j)
        for (int k = 0; k < 3; ++k) {
          res.a[i][j] += mul(a[i][k], T.a[k][j]);
          res.a[i][j] %= MOD;
        }
    return res;
  }
  inline mat operator^(LL x) const {
    mat res, bas;
    for (int i = 0; i < 3; ++i) res.a[i][i] = 1;
    for (int i = 0; i < 3; ++i)
      for (int j = 0; j < 3; ++j) bas.a[i][j] = a[i][j];
    while (x) {
      if (x & 1) res = res * bas;
      bas = bas * bas;
      x >>= 1;
    }
    return res;
  }
};
```
