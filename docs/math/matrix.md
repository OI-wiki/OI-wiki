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
C_{i,j} = \sum_{k=1}^MA_{i,k}B_{k,j}
$$

如果没看懂上面的式子，没关系。通俗的讲，在矩阵乘法中，结果 $C$ 矩阵的第 $i$ 行第 $j$ 列的数，就是由矩阵 $A$ 第 $i$ 行 $M$ 个数与矩阵 $B$ 第 $j$ 列 $M$ 个数分别相乘再相加得到的。

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
    for (int i = 0; i < sz; ++i)
      for (int j = 0; j < sz; ++j)
        res.a[i][j] = (a[i][j] - T.a[i][j] + MOD) % MOD;
    return res;
  }
  inline mat operator-(const mat& T) const {
    mat res;
    for (int i = 0; i < sz; ++i)
      for (int j = 0; j < sz; ++j) res.a[i][j] = (a[i][j] + T.a[i][j]) % MOD;
    return res;
  }
  inline mat operator*(const mat& T) const {
    mat res;
    for (int i = 0; i < sz; ++i)
      for (int j = 0; j < sz; ++j)
        for (int k = 0; k < sz; ++k) {
          res.a[i][j] += mul(a[i][k], T.a[k][j]);
          res.a[i][j] %= MOD;
        }
    return res;
  }
  inline mat operator^(LL x) const {
    mat res, bas;
    for (int i = 0; i < sz; ++i) res.a[i][i] = 1;
    for (int i = 0; i < sz; ++i)
      for (int j = 0; j < sz; ++j) bas.a[i][j] = a[i][j];
    while (x) {
      if (x & 1) res = res * bas;
      bas = bas * bas;
      x >>= 1;
    }
    return res;
  }
};
```

## 应用

### 矩阵加速递推

斐波那契数列（Fibonacci Sequence）大家应该都非常的熟悉了。在斐波那契数列当中，$F_1 = F_2 = 1$，$F_i = F_{i - 1} + F_{i - 2}(i \geq 3)$。

如果有一道题目让你求斐波那契数列第 $n$ 项的值，最简单的方法莫过于直接递推了。但是如果 $n$ 的范围达到了 $10^{18}$ 级别，递推就不行了，稳 TLE。考虑矩阵加速递推。

设 $Fib(n)$ 表示一个 $1 \times 2$ 的矩阵 $\left[ \begin{array}{ccc}F_n & F_{n-1} \end{array}\right]$。我们希望根据 $Fib(n-1)=\left[ \begin{array}{ccc}F_{n-1} & F_{n-2} \end{array}\right]$ 推出 $Fib(n)$。

试推导一个矩阵 $\text{base}$，使 $Fib(n-1) \times \text{base} = Fib(n)$，即 $\left[\begin{array}{ccc}F_{n-1} & F_{n-2}\end{array}\right] \times \text{base} = \left[ \begin{array}{ccc}F_n & F_{n-1} \end{array}\right]$。

怎么推呢？因为 $F_n=F_{n-1}+F_{n-2}$，所以 $\text{base}$ 矩阵第一列应该是 $\left[\begin{array}{ccc} 1 \\ 1 \end{array}\right]$，这样在进行矩阵乘法运算的时候才能令 $F_{n-1}$ 与 $F_{n-2}$ 相加，从而得出 $F_n$。同理，为了得出 $F_{n-1}$，矩阵 $\text{base}$ 的第二列应该为 $\left[\begin{array}{ccc} 1 \\ 0 \end{array}\right]$。

综上所述：$$\text{base} = \left[\begin{array}{ccc} 1 & 1 \\ 1 & 0 \end{array}\right]$$ 原式化为 $$\left[\begin{array}{ccc}F_{n-1} & F_{n-2}\end{array}\right] \times \left[\begin{array}{ccc} 1 & 1 \\ 1 & 0 \end{array}\right] = \left[ \begin{array}{ccc}F_n & F_{n-1} \end{array}\right]$$

转化为代码，应该怎么求呢？

定义初始矩阵 $\text{ans} = \left[\begin{array}{ccc}F_2 & F1\end{array}\right] = \left[\begin{array}{ccc}1 & 1\end{array}\right], \text{base} = \left[\begin{array}{ccc} 1 & 1 \\ 1 & 0 \end{array}\right]$。那么，$F_n$ 就等于 $\text{ans} \times \text{base}^{n-2}$ 这个矩阵的第一行第一列元素，也就是 $\left[\begin{array}{ccc}1 & 1\end{array}\right] \times \left[\begin{array}{ccc} 1 & 1 \\ 1 & 0 \end{array}\right]^{n-2}$ 的第一行第一列元素。

为什么要乘上 $\text{base}$ 矩阵的 $n-2$ 次方而不是 $n$ 次方呢？因为 $F_1, F_2$ 是不需要进行矩阵乘法就能求的。也就是说，如果只进行一次乘法，就已经求出 $F_3$ 了。如果还不是很理解为什么幂是 $n-2$，建议手算一下。

下面是求斐波那契数列第 $n$ 项对 $10^9+7$ 取模的示例代码（核心部分）。

```cpp
const int mod = 1000000007;

struct Matrix {
  int a[3][3];
  Matrix() { memset(a, 0, sizeof a); }
  Matrix operator*(const Matrix &b) const {
    Matrix res;
    rep(i, 1, 2) rep(j, 1, 2) rep(k, 1, 2)
      res.a[i][j] = (res.a[i][j] + a[i][k] * b.a[k][j]) % mod;
    return res;
  }
} ans, base;

void init() {
  base.a[1][1] = base.a[1][2] = base.a[2][1] = 1;
  ans.a[1][1] = ans.a[1][2] = 1;
}

void qpow(int b) {
  while (b) {
    if (b & 1) ans = ans * base;
    base = base * base;
    b >>= 1;
  }
}

int main() {
  int n = read();
  if (n <= 2) return puts("1"), 0;
  init();
  qpow(n - 2); 
  println(ans.a[1][1] % mod);
}
```
