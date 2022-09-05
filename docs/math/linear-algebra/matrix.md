本文介绍线性代数中一个非常重要的内容——矩阵（Matrix），主要讲解矩阵的性质、运算以及在常系数齐次递推式上的应用。

## 定义

对于矩阵 $A$，主对角线是指 $A_{i,i}$ 的元素。

一般用 $I$ 来表示单位矩阵，就是主对角线上为 1，其余位置为 0。

## 性质

### 矩阵的逆

$A$ 的逆矩阵 $P$ 是使得 $A \times P = I$ 的矩阵。

逆矩阵可以用 [高斯消元](./gauss.md) 的方式来求。

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

利用结合律，矩阵乘法可以利用 [快速幂](./quick-pow.md) 的思想来优化。

在比赛中，由于线性递推式可以表示成矩阵乘法的形式，也通常用矩阵快速幂来求线性递推数列的某一项。

#### 优化

首先对于比较小的矩阵，可以考虑直接手动展开循环以减小常数。

可以重新排列循环以提高空间局部性，这样的优化不会改变矩阵乘法的时间复杂度，但是会在得到常数级别的提升。

```cpp
// 以下文的参考代码为例
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

// 不如
inline mat operator*(const mat& T) const {
  mat res;
  int r;
  for (int i = 0; i < sz; ++i)
    for (int k = 0; k < sz; ++k) {
      r = a[i][k];
      for (int j = 0; j < sz; ++j)
        res.a[i][j] += T.a[k][j] * r, res.a[i][j] %= MOD;
    }
  return res;
}
```

## 参考代码

一般来说，可以用一个二维数组来模拟矩阵。

```cpp
struct mat {
  LL a[sz][sz];

  inline mat() { memset(a, 0, sizeof a); }

  inline mat operator-(const mat& T) const {
    mat res;
    for (int i = 0; i < sz; ++i)
      for (int j = 0; j < sz; ++j) {
        res.a[i][j] = (a[i][j] - T.a[i][j]) % MOD;
      }
    return res;
  }

  inline mat operator+(const mat& T) const {
    mat res;
    for (int i = 0; i < sz; ++i)
      for (int j = 0; j < sz; ++j) {
        res.a[i][j] = (a[i][j] + T.a[i][j]) % MOD;
      }
    return res;
  }

  inline mat operator*(const mat& T) const {
    mat res;
    int r;
    for (int i = 0; i < sz; ++i)
      for (int k = 0; k < sz; ++k) {
        r = a[i][k];
        for (int j = 0; j < sz; ++j)
          res.a[i][j] += T.a[k][j] * r, res.a[i][j] %= MOD;
      }
    return res;
  }

  inline mat operator^(LL x) const {
    mat res, bas;
    for (int i = 0; i < sz; ++i) res.a[i][i] = 1;
    for (int i = 0; i < sz; ++i)
      for (int j = 0; j < sz; ++j) bas.a[i][j] = a[i][j] % MOD;
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

综上所述：$\text{base} = \left[\begin{array}{ccc} 1 & 1 \\ 1 & 0 \end{array}\right]$ 原式化为 $\left[\begin{array}{ccc}F_{n-1} & F_{n-2}\end{array}\right] \times \left[\begin{array}{ccc} 1 & 1 \\ 1 & 0 \end{array}\right] = \left[ \begin{array}{ccc}F_n & F_{n-1} \end{array}\right]$

转化为代码，应该怎么求呢？

定义初始矩阵 $\text{ans} = \left[\begin{array}{ccc}F_2 & F_1\end{array}\right] = \left[\begin{array}{ccc}1 & 1\end{array}\right], \text{base} = \left[\begin{array}{ccc} 1 & 1 \\ 1 & 0 \end{array}\right]$。那么，$F_n$ 就等于 $\text{ans} \times \text{base}^{n-2}$ 这个矩阵的第一行第一列元素，也就是 $\left[\begin{array}{ccc}1 & 1\end{array}\right] \times \left[\begin{array}{ccc} 1 & 1 \\ 1 & 0 \end{array}\right]^{n-2}$ 的第一行第一列元素。

注意，矩阵乘法不满足交换律，所以一定不能写成 $\left[\begin{array}{ccc} 1 & 1 \\ 1 & 0 \end{array}\right]^{n-2} \times \left[\begin{array}{ccc}1 & 1\end{array}\right]$ 的第一行第一列元素。另外，对于 $n \leq 2$ 的情况，直接输出 $1$ 即可，不需要执行矩阵快速幂。

为什么要乘上 $\text{base}$ 矩阵的 $n-2$ 次方而不是 $n$ 次方呢？因为 $F_1, F_2$ 是不需要进行矩阵乘法就能求的。也就是说，如果只进行一次乘法，就已经求出 $F_3$ 了。如果还不是很理解为什么幂是 $n-2$，建议手算一下。

下面是求斐波那契数列第 $n$ 项对 $10^9+7$ 取模的示例代码（核心部分）。

```cpp
const int mod = 1000000007;

struct Matrix {
  int a[3][3];

  Matrix() { memset(a, 0, sizeof a); }

  Matrix operator*(const Matrix &b) const {
    Matrix res;
    for (int i = 1; i <= 2; ++i)
      for (int j = 1; j <= 2; ++j)
        for (int k = 1; k <= 2; ++k)
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

* * *

这是一个稍微复杂一些的例子。

$$
\begin{gathered}
f_{1} = f_{2} = 0\\
f_{n} = 7f_{n-1}+6f_{n-2}+5n+4\times 3^n
\end{gathered}
$$

我们发现，$f_n$ 和 $f_{n-1}, f_{n-2}, n$ 有关，于是考虑构造一个矩阵描述状态。

但是发现如果矩阵仅有这三个元素 $\begin{bmatrix}f_n& f_{n-1}& n\end{bmatrix}$ 是难以构造出转移方程的，因为乘方运算和 $+1$ 无法用矩阵描述。

于是考虑构造一个更大的矩阵。

$$
\begin{bmatrix}f_n& f_{n-1}& n& 3^n & 1\end{bmatrix}
$$

我们希望构造一个递推矩阵可以转移到

$$
\begin{bmatrix}
f_{n+1}& f_{n}& n+1& 3^{n+1} & 1
\end{bmatrix}
$$

转移矩阵即为

$$
\begin{bmatrix}
7 & 1 & 0 & 0 & 0\\
6 & 0 & 0 & 0 & 0\\
5 & 0 & 1 & 0 & 0\\
12 & 0 & 0 & 3 & 0\\
5 & 0 & 1 & 0 & 1
\end{bmatrix}
$$

### 矩阵表达修改

???+note "「THUSCH 2017」大魔法师"
    大魔法师小 L 制作了 $n$ 个魔力水晶球，每个水晶球有水、火、土三个属性的能量值。小 L 把这 $n$ 个水晶球在地上从前向后排成一行，然后开始今天的魔法表演。
    
    我们用 $A_i,\ B_i,\ C_i$ 分别表示从前向后第 $i$ 个水晶球（下标从 $1$ 开始）的水、火、土的能量值。
    
    小 L 计划施展 $m$ 次魔法。每次，他会选择一个区间 $[l, r]$，然后施展以下 $3$ 大类、$7$ 种魔法之一：
    
    1.  魔力激发：令区间里每个水晶球中 **特定属性** 的能量爆发，从而使另一个 **特定属性** 的能量增强。具体来说，有以下三种可能的表现形式：
    
        - 火元素激发水元素能量：令 $A_i = A_i + B_i$。
        - 土元素激发火元素能量：令 $B_i = B_i + C_i$。
        -   水元素激发土元素能量：令 $C_i = C_i + A_i$。
    
            **需要注意的是，增强一种属性的能量并不会改变另一种属性的能量，例如 $A_i = A_i + B_i$ 并不会使 $B_i$ 增加或减少。**
    
    2.  魔力增强：小 L 挥舞法杖，消耗自身 $v$ 点法力值，来改变区间里每个水晶球的 **特定属性** 的能量。具体来说，有以下三种可能的表现形式：
    
        - 火元素能量定值增强：令 $A_i = A_i + v$。
        - 水元素能量翻倍增强：令 $B_i=B_i \cdot v$。
        - 土元素能量吸收融合：令 $C_i = v$。
    
    3. 魔力释放：小 L 将区间里所有水晶球的能量聚集在一起，融合成一个新的水晶球，然后送给场外观众。生成的水晶球每种属性的能量值等于区间内所有水晶球对应能量值的代数和。**需要注意的是，魔力释放的过程不会真正改变区间内水晶球的能量**。
    
    值得一提的是，小 L 制造和融合的水晶球的原材料都是定制版的 OI 工厂水晶，所以这些水晶球有一个能量阈值 $998244353$。当水晶球中某种属性的能量值大于等于这个阈值时，能量值会自动对阈值取模，从而避免水晶球爆炸。
    
    小 W 为小 L（唯一的）观众，围观了整个表演，并且收到了小 L 在表演中融合的每个水晶球。小 W 想知道，这些水晶球蕴涵的三种属性的能量值分别是多少。

由于矩阵的结合律和分配律成立，单点修改可以自然地推广到区间，即推出矩阵后直接用线段树维护区间矩阵乘积即可。

下面将举几个例子。

$A_i = A_i + v$ 的转移

$$
\begin{bmatrix}
A & B & C & 1
\end{bmatrix}
\begin{bmatrix}
1 & 0 & 0 & 0\\
0 & 1 & 0 & 0\\
0 & 0 & 1 & 0\\
v & 0 & 0 & 1\\
\end{bmatrix}=
\begin{bmatrix}
A+v & B & C & 1\\
\end{bmatrix}
$$

$B_i=B_i \cdot v$ 的转移

$$
\begin{bmatrix}
A & B & C & 1
\end{bmatrix}
\begin{bmatrix}
1 & 0 & 0 & 0\\
0 & v & 0 & 0\\
0 & 0 & 1 & 0\\
0 & 0 & 0 & 1\\
\end{bmatrix}=
\begin{bmatrix}
A & B \cdot v & C & 1\\
\end{bmatrix}
$$

* * *

???+note "「LibreOJ 6208」树上询问"
    有一棵 $n$ 节点的树，根为 $1$ 号节点。每个节点有两个权值 $k_i, t_i$，初始值均为 $0$。
    
    给出三种操作：
    
    1. $\operatorname{Add}( x , d )$ 操作：将 $x$ 到根的路径上所有点的 $k_i\leftarrow k_i + d$
    2. $\operatorname{Mul}( x , d )$ 操作：将 $x$ 到根的路径上所有点的 $t_i\leftarrow t_i + d \times k_i$
    3.  $\operatorname{Query}( x )$ 操作：询问点 $x$ 的权值 $t_x$
    
        $n,~m \leq 100000, ~-10 \leq d \leq 10$

若直接思考，下放操作和维护信息并不是很好想。但是矩阵可以轻松地表达。

$$
\begin{aligned}
\begin{bmatrix}k & t & 1 \end{bmatrix}
\begin{bmatrix}
1 & 0 & 0 \\
0 & 1 & 0 \\
d & 0 & 1
\end{bmatrix}
&=
\begin{bmatrix}k+d & t & 1 \end{bmatrix}\\
\begin{bmatrix}k & t & 1 \end{bmatrix}
\begin{bmatrix}
1 & d & 0 \\
0 & 1 & 0 \\
0 & 0 & 1
\end{bmatrix}
&=
\begin{bmatrix}k & t+d \times k & 1 \end{bmatrix}
\end{aligned}
$$

### 定长路径统计

???+note "问题描述"
    给一个 $n$ 阶有向图，每条边的边权均为 $1$，然后给一个整数 $k$，你的任务是对于所有点对 $(u,v)$ 求出从 $u$ 到 $v$ 长度为 $k$ 的路径的数量（不一定是简单路径，即路径上的点或者边可能走多次）。

我们将这个图用邻接矩阵 $G$（对于图中的边 $(u\to v)$，令 $G[u,v]=1$，其余为 $0$ 的矩阵；如果有重边，则设 $G[u,v]$ 为重边的数量）表示这个有向图。下述算法同样适用于图有自环的情况。

显然，该邻接矩阵对应 $k=1$ 时的答案。

假设我们知道长度为 $k$ 的路径条数构成的矩阵，记为矩阵 $C_k$，我们想求 $C_{k+1}$。显然有 DP 转移方程

$$
C_{k+1}[i,j] = \sum_{p = 1}^{n} C_k[i,p] \cdot G[p,j]
$$

我们可以把它看作矩阵乘法的运算，于是上述转移可以描述为

$$
C_{k+1} = C_k \cdot G
$$

那么把这个递推式展开可以得到

$$
C_k = \underbrace{G \cdot G \cdots G}_{k \text{ 次}} = G^k
$$

要计算这个矩阵幂，我们可以使用快速幂（二进制取幂）的思想，在 $O(n^3 \log k)$ 的复杂度内计算结果。

### 定长最短路

???+note "问题描述"
    给你一个 $n$ 阶加权有向图和一个整数 $k$。对于每个点对 $(u,v)$ 找到从 $u$ 到 $v$ 的恰好包含 $k$ 条边的最短路的长度。（不一定是简单路径，即路径上的点或者边可能走多次）

我们仍构造这个图的邻接矩阵 $G$，$G[i,j]$ 表示从 $i$ 到 $j$ 的边权。如果 $i,j$ 两点之间没有边，那么 $G[i,j]=\infty$。（有重边的情况取边权的最小值）

显然上述矩阵对应 $k=1$ 时问题的答案。我们仍假设我们知道 $k$ 的答案，记为矩阵 $L_k$。现在我们想求 $k+1$ 的答案。显然有转移方程

$$
L_{k+1}[i,j] = \min_{1\le p \le n} \left\{L_k[i,p] + G[p,j]\right\}
$$

事实上我们可以类比矩阵乘法，你发现上述转移只是把矩阵乘法的乘积求和变成相加取最小值，于是我们定义这个运算为 $\odot$，即

$$
A \odot B = C~~\Longleftrightarrow~~C[i,j]=\min_{1\le p \le n}\left\{A[i,p] + B[p,j]\right\}
$$

于是得到

$$
L_{k+1} = L_k \odot G
$$

展开递推式得到

$$
L_k = \underbrace{G \odot \ldots \odot G}_{k\text{ 次}} = G^{\odot k}
$$

我们仍然可以用矩阵快速幂的方法计算上式，因为它显然是具有结合律的。时间复杂度 $O(n^3 \log k)$。

### 限长路径计数/最短路

上述算法只适用于边数固定的情况。然而我们可以改进算法以解决边数小于等于 $k$ 的情况。具体地，考虑以下问题：

???+note "问题描述"
    给一个 $n$ 阶有向图，边权为 $1$，然后给一个整数 $k$，你的任务是对于每个点对 $(u,v)$ 找到从 $u$ 到 $v$ 长度小于等于 $k$ 的路径的数量（不一定是简单路径，即路径上的点或者边可能走多次）。

我们简单修改一下这个图，我们给每一个结点加一个权值为 $1$ 的自环。这样走的时侯就可以走自环，相当于原地走。这样就包含了小于等于 $k$ 的情况。修改后再做矩阵快速幂即可。（即使这个图在修改之前就有自环，该算法仍是成立的）。

同样的方法可以用于求边数小于等于 $k$ 的最短路，即加一个边权为 $0$ 的自环。

## 习题

- [洛谷 P1962 斐波那契数列](https://www.luogu.com.cn/problem/P1962)，即上面的例题，同题 POJ3070
- [洛谷 P1349 广义斐波那契数列](https://www.luogu.com.cn/problem/P1349)，$\text{base}$ 矩阵需要变化一下
-   [洛谷 P1939【模板】矩阵加速（数列）](https://www.luogu.com.cn/problem/P1939)，$\text{base}$ 矩阵变成了 $3 \times 3$ 的矩阵，推导过程与上面差不多。

    **本页面部分内容译自博文 [Кратчайшие пути фиксированной длины, количества путей фиксированной длины](http://e-maxx.ru/algo/fixed_length_paths) 与其英文翻译版 [Number of paths of fixed length/Shortest paths of fixed length](https://cp-algorithms.com/graph/fixed_length_paths.html)。其中俄文版版权协议为 Public Domain + Leave a Link；英文版版权协议为 CC-BY-SA 4.0。**
