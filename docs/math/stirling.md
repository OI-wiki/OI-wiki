## 第一类 Stirling 数

设有多项式 $x(x-1)(x-2) \cdots (x-n+1)$，它的展开式形如 $s_nx^n - s_{n-1}x^{n-1}+s_{n-2}x^{n-2}-\cdots$。

不考虑各项系数的符号，将 $x^r$ 的系数的绝对值记做 $s(n, r)$，称为第一类 Stirling 数。

关于第一类 Stirling 数的性质可以阅读 [Stirling Number of the First Kind](http://mathworld.wolfram.com/StirlingNumberoftheFirstKind.html)。

### 递推形式

$$
s(n,r) = (n-1)s(n-1,r)+s(n-1,r-1),\ n > r \geq 1
$$

## 第二类 Stirling 数

把 n 个不同的球放到 r 个相同的盒子里，假设没有空盒，则放球方案数记做 $S(n, r)$，称为第二类 Stirling 数。

关于第二类 Stirling 数的性质可以阅读 [Stirling Number of the Second Kind](http://mathworld.wolfram.com/StirlingNumberoftheSecondKind.html)。

### 递推形式

$$
S(n,r) = r S(n-1,r) + S(n-1,r-1),\ n > r \geq 1
$$

## 例题

根据例题来讲解：  
（2007 普及）将 $n$ 个数 $（1，2，…，n）$ 分成 $r$ 个部分。每个部分至少一个数。将不同划分方法的总数记为 $S_n^r$ 。例如， $S_4^2=7$ ，这 7 种不同的划分方法依次为 $\{\ (1) , (234) \}\,\{\ (2) ,  (134) \}\,\{\ (3) , (124) \}\,\{\ (4) , (123) \}\,\{\ (12) , (34) \}\,\{\ (13) , (24) \}\,\{\ (14) , (23) \}$ 。当 $n=6，r=3$ 时， $S_6^3$ =（）

> 提示：先固定一个数，对于其余的 5 个数考虑 $S_5^3$ 与 $S_5^2$ ，再分这两种情况对原固定的数进行分析。

题解：在近几年算法竞赛中，递推算法越来越重要：

$$
S_6^3=3 \times S_5^3 + S_5^2
$$

$$
S_5^3=3 \times S_4^3 + S_4^2
$$

$$
S_5^2=2 \times S_4^2 + S_4^1
$$

第二类 stirling 数，显然拥有这样的性质：

$$
S_n^m = m \times S_{n-1}^{m} + S_{n-1}^{m-1}
$$

$$
S_n^1 = 1,S_n^0 = 0,S_n^n = 1
$$

而这些性质就可以总结成：

$$
S_n^3 = \frac{1}{2} \times (3^{n-1}+1) - 2^{n-1}
$$
