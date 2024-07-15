???+warning
    在中国台湾地区关于 "column" 与 "row" 的翻译，恰好与中国大陆地区相反。在 **OI Wiki** 按照中国大陆地区的习惯，采用竖列（column）与横行（row）的翻译。

## 定义

由 $m\times n$ 个数按照矩形排列成的一个数表

$$
M=\left(\begin{matrix}
a_{11}&a_{12}&\cdots&a_{1m}\\
a_{21}&a_{22}&\cdots&a_{2m}\\
\vdots&\vdots&\ddots&\vdots\\
a_{n1}&a_{n2}&\cdots&a_{nm}
\end{matrix}\right)
$$

称为**矩阵**。其中矩阵中的数 $a_{ij}$ 称为矩阵的**元素**。如果 $n=m$，称矩阵 $M$ 为**方阵**。

??? note "关于矩阵两侧的括号"
    矩阵两侧使用小括号（$\left(\begin{matrix}1&1\\1&1\end{matrix}\right)$）或中括号（$\begin{bmatrix}1&1\\1&1\end{bmatrix}$）都是可以的。
    
    但是如果两侧是长竖线（$\left\vert\begin{matrix}1&1\\1&1\end{matrix}\right\vert$），则表示行列式而非矩阵。

如果一个矩阵的行和列相等（即 $m=n$），则称这个矩阵是 $n$ 阶**方阵**或 $n$ 阶矩阵，记作 $A_n$。其中，从方阵的左上角到右下角的连线称为**主对角线**。位于主对角线上的元素（即元素 $a_{ii}$）称为**主对角元素**。下面是一些特殊的矩阵（方阵）。

- **上（下）三角矩阵**：如果一个方阵的主对角线的上（下）方元素均为 $0$，则称它是一个上（下）三角矩阵。

- **对角矩阵**：如果一个方阵除主对角元素外其余元素均为 $0$，且主对角元素不全为 $0$，则称它是一个对角矩阵（对角阵），可记作 $\operatorname{diag}\{\lambda_1,\cdots,\lambda_n\}$，其中 $\lambda_i=a_{ii}$ 方阵第 $i$ 行 $i$ 列的主对角元素。特别地，如果一个对角阵的主对角元素均为 $1$，则称它是**单位矩阵**（单位阵），用字母 $I$ 或 $E$ 表示，即

$$
E=E_n=\operatorname{diag}\{1, 1, \cdots, 1\}=\left(\begin{matrix}
1&0&\cdots&0\\
0&1&\cdots&0\\
\vdots&\vdots&\ddots&\vdots\\
0&0&\cdots&1
\end{matrix}\right)
$$

- **零矩阵**：对于一个 $m\times n$ 的矩阵，如果它的元素全部是 $0$，称它是一个**零矩阵**，记作 $0$ 或 $0_{m\times n}$。注意不同阶的零矩阵不相等。

如果两个矩阵的行数与列数对应相同，称它们是同型矩阵。很显然，阶数相同的两个方阵时同型的。

在研究方程组、向量组、矩阵的秩的时候，我们使用一般的矩阵；研究特征值和特征向量、二次型的时候，则使用方阵。

## 运算

### 矩阵的线性运算

矩阵的线性运算分为加减法与数乘。请注意只有同型矩阵之间才可以进行加减运算。

#### 矩阵加法

对于两个 $m\times n$ 的矩阵 $A, B$，它们的和 $A+B$ 也是一个 $m\times n$ 矩阵 $C$，且满足 $c_{ij}=a_{ij}+b_{ij}$。可以理解为对应元素分别相加。

可以证明，矩阵加法满足交换律、结合律。

#### 矩阵减法

类似的，对于两个 $m\times n$ 的矩阵 $A, B$，它们的差 $A-B$ 也是一个 $m\times n$ 矩阵 $C$，且满足 $c_{ij}=a_{ij}-b_{ij}$。也可理解为对应元素分别相减。

同样可以证明减法满足交换律、结合律。

#### 矩阵数乘

对于一个矩阵 $A$ 和实数 $\lambda$，定义数乘 $B=\lambda A$ 表示将原矩阵 $A$ 中所有元素乘以实数 $\lambda$ 得到的新矩阵，即 $b_{ij}=\lambda\cdot a_{ij}$。可以注意到 $A-B=A+(-1\cdot B)$，因此我们记 $-1\cdot B=-B$。

#### 线性运算的线性性

对于两个同型矩阵 $A,B$ 和实数 $k,l$，我们有以下性质成立：

- $k(A\pm B)=kA\pm kB$。
- $(kl)\cdot A=k\cdot(lA)$。
- $(k+l)A=kA+lA$。

因此我们将矩阵加减法、数乘运算称为**线性运算**。

??? tip "什么是线性？"
    在现实生活中，我们会遇到类似这样的情景：在平地上，可以将一个网球用 5 m/s 的速度扔出；在速度为 10 m/s 的自行车上，用同样的力扔同一个球，球最终的速度是 10+5=15m/s。「线性」的意义就在于：两个输入之和的输出，等价于两个输入分别的输出之和。[^ref1]
    
    在数学中，对于一个函数 $f$，如果它对于两个输入 $x,y$ 满足 $f(x+y)=f(x)+f(y)$，其中的「加法」是可以任意定义的二元运算，那么我们称函数 $f$ 是线性的（linear）。

### 矩阵的转置

对于一个 $m\times n$ 的矩阵 $A$，它的转置是一个 $n\times m$ 的矩阵 $B$，其中元素 $b_{ij}=a_{ji}$，记作 $B=A^T$。

通俗理解就是将矩阵行列互换（或者将方阵沿主对角线对称）。显然，对于实数 $k$ 和同型矩阵 $A,B$，有下列事实：

- $(A^T)^T=A$。
- $(A+B)^T=A^T+B^T$。
- $(kA)^T=k(A^T)$。

特别地，若矩阵 $A$ 满足 $A=A^T$，则称 $A$ 是**对称矩阵**；若满足 $-A=A^T$，则称 $A$ 是**反对称矩阵**。

### 矩阵乘法

矩阵的乘法是向量内积的推广，只有在第一个矩阵的列数和第二个矩阵的行数相同时才有意义。

设 $A$ 为 $p \times m$ 的矩阵，$B$ 为 $m \times q$ 的矩阵，则 $A$ 和 $B$ 的乘积是一个 $p\times q$ 的矩阵 $C$，记作 $C=A\times B$，其中元素满足：

$$
c_{ij} = \sum_{k=1}^ma_{ik}b_{kj}
$$

矩阵乘法满足结合律，一般不满足交换律.同时，矩阵乘法还满足：

- 分配律：$C\times (A+B)=CA+CB$ 以及 $(A+B)\times C=AC+AB$。
- 对于实数 $k$，有 $k(AB)=(kA)B=A(kB)$。
- $(AB)^T=B^TA^T$。

按照矩阵乘法的规则，对于 $n$ 阶方阵 $A_n$ 而言，它乘以 $n$ 阶单位阵的结果就是它本身（无论左乘或右乘），即 $A_nI_n=I_nA_n=A_n$。

???+warning "关于左右乘"
    由于矩阵乘法不满足交换律，我们需要注意乘法是乘在左边还是乘在右边！

??? note "矩阵乘法的常数优化"
    对于比较小的矩阵，可以考虑直接手动展开循环以减小常数。
    
    对于一般的矩阵，可以考虑改变循环顺序以提高局部性和缓存命中率，减小常数。
    
    ```cpp
    // 优化前
    mat operator*(const mat& T) const {
      mat res;
      for (int i = 0; i < sz; ++i)
        for (int j = 0; j < sz; ++j)
          for (int k = 0; k < sz; ++k) {
            res.a[i][j] += a[i][k] * T.a[k][j];
            res.a[i][j] %= MOD;
          }
      return res;
    }
    
    // 优化后
    mat operator*(const mat& T) const {
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

### 方阵的幂

对于方阵 $A$ 和正整数 $k$，我们定义方阵的幂

$$
A^k=\begin{cases}
A&&k=1\\
A^{k-1}\times A&&k>1
\end{cases}
$$

为了方便计算，我们定义 $A^0=I_n$ 为单位阵。容易证明：$A^pA^q=A^{p+q},(A^p)^q=A^{pq}$，即方阵的幂和普通实数的幂有类似的运算规律。

由于矩阵乘法具有结合率，方阵的幂可以利用[快速幂](../binary-exponentiation.md)的思想来优化，称为**矩阵快速幂**。

由于线性递推式可以表示成矩阵乘法的形式，我们可以用矩阵快速幂来求线性递推数列的某一项。

???+"[洛谷 P1962 斐波那契数列](https://www.luogu.com.cn/problem/P1962)"
    题意简述：求斐波那契第 $n$ 项模 $10^9+7$ 的值。其中 $n\le 2^{63}$。

思路：对于斐波那契数列 $f_n$，有递推 $f_n=f_{n-1}+f_{n-2}$。

考虑将其用矩阵乘法表示。我们发现

$$\left(\begin{matrix}f_{n-1}&f_{n-2}\end{matrix}\right)\left(\begin{matrix}1&1\\1&0\end{matrix}\right)=\left(\begin{matrix}f_n&f_{n-1}\end{matrix}\right)$$

因此，由递推可知

$$
\left(\begin{matrix}f_n&f_{n-1}\end{matrix}\right)=\left(\begin{matrix}f_2&f_1\end{matrix}\right)\left(\begin{matrix}1&1\\1&0\end{matrix}\right)^{n-2}
$$

由于矩阵乘法满足结合率，我们可以用快速幂计算出 $\left(\begin{matrix}1&1\\1&0\end{matrix}\right)^{n-2}$ 的值，再乘 $\left(\begin{matrix}f_2&f_1\end{matrix}\right)=\left(\begin{matrix}1&1\end{matrix}\right)$ 就可以得到答案了。

??? "核心代码"
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

### 方阵的行列式

对于一个 $n$ 阶方阵 $A_n$，我们定义它的**行列式**，记作 $\det A$ 或 $|A|$，其定义为

$$
\det A=\sum_{k_1,k_2,\cdots,k_n}(-1)^ka_{1k_1}a_{2k_2}\cdots a_{nk_n}
$$

其中 $(k_1,\cdots,k_n)$ 是由 $(1,\cdots,n)$ 交换 $n$ 次次序得到的排列。

### 方阵的逆

对于一个行列式不为零的 $n$ 阶方阵 $A_n$，存在一个 $n$ 阶方阵 $P_n$ 使得它和 $A_n$ 的乘积为 $n$ 阶单位阵，即对 $\det(A_n)\neq 0$，存在 $P_n$ 使得 $A_nP_n=P_nA_n=I_n$。我们称这个 $P_n$ 是 $A_n$ 的逆矩阵，记作 $P_n=A_n^{-1}$。当 $\det(A_n)=0$ 时，$A_n$ 没有逆矩阵。

对于正整数 $k$，我们定义 $A_{-k}=(A_{-1})^k$ 为 $A$ 的逆的 $k$ 次幂。此时上文中矩阵幂的性质可以推广到所有整数

如果逆矩阵存在，可以使用 [高斯消元](../numerical/gauss.md) 进行求解。

## 应用

### 矩阵加速递推

这是一个比斐波那契稍微复杂一些的例子。

$$
f_n=\begin{cases}
0&&n\le 2\\
7f_{n-1}+6f_{n-2}+5n+4\times 3^n+1&&\text{otherwise}
\end{cases}
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

???+ note "「THUSCH 2017」大魔法师"
    大魔法师小 L 制作了 $n$ 个魔力水晶球，每个水晶球有水、火、土三个属性的能量值。小 L 把这 $n$ 个水晶球在地上从前向后排成一行，然后开始今天的魔法表演。
    
    我们用 $A_i,\ B_i,\ C_i$ 分别表示从前向后第 $i$ 个水晶球（下标从 $1$ 开始）的水、火、土的能量值。
    
    小 L 计划施展 $m$ 次魔法。每次，他会选择一个区间 $[l, r]$，然后施展以下 $3$ 大类、$7$ 种魔法之一：
    
    1.  魔力激发：令区间里每个水晶球中 **特定属性** 的能量爆发，从而使另一个 **特定属性** 的能量增强。具体来说，有以下三种可能的表现形式：
    
        -   火元素激发水元素能量：令 $A_i = A_i + B_i$。
        -   土元素激发火元素能量：令 $B_i = B_i + C_i$。
        -   水元素激发土元素能量：令 $C_i = C_i + A_i$。
    
            **需要注意的是，增强一种属性的能量并不会改变另一种属性的能量，例如 $A_i = A_i + B_i$ 并不会使 $B_i$ 增加或减少。**
    2.  魔力增强：小 L 挥舞法杖，消耗自身 $v$ 点法力值，来改变区间里每个水晶球的 **特定属性** 的能量。具体来说，有以下三种可能的表现形式：
    
        -   火元素能量定值增强：令 $A_i = A_i + v$。
        -   水元素能量翻倍增强：令 $B_i=B_i \cdot v$。
        -   土元素能量吸收融合：令 $C_i = v$。
    3.  魔力释放：小 L 将区间里所有水晶球的能量聚集在一起，融合成一个新的水晶球，然后送给场外观众。生成的水晶球每种属性的能量值等于区间内所有水晶球对应能量值的代数和。**需要注意的是，魔力释放的过程不会真正改变区间内水晶球的能量**。
    
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

***

???+ note "「LibreOJ 6208」树上询问"
    有一棵 $n$ 节点的树，根为 $1$ 号节点。每个节点有两个权值 $k_i, t_i$，初始值均为 $0$。
    
    给出三种操作：
    
    1.  $\operatorname{Add}( x , d )$ 操作：将 $x$ 到根的路径上所有点的 $k_i\leftarrow k_i + d$
    2.  $\operatorname{Mul}( x , d )$ 操作：将 $x$ 到根的路径上所有点的 $t_i\leftarrow t_i + d \times k_i$
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

???+ note "问题描述"
    给一个 $n$ 阶有向图，每条边的边权均为 $1$，然后给一个整数 $k$，你的任务是对于所有点对 $(u,v)$ 求出从 $u$ 到 $v$ 长度为 $k$ 的路径的数量（不一定是简单路径，即路径上的点或者边可能走多次）。

我们将这个图用邻接矩阵 $G$（对于图中的边 $(u\to v)$，令 $G_{u,v}=1$，其余为 $0$ 的矩阵；如果有重边，则设 $G_{u,v}$ 为重边的数量）表示这个有向图。下述算法同样适用于图有自环的情况。

显然，该邻接矩阵对应 $k=1$ 时的答案。

假设我们知道长度为 $k$ 的路径条数构成的矩阵，记为矩阵 $C^{(k)}$，我们想求 $C^{(k+1)}$。显然有 DP 转移方程

$$
C^{(k+1)}_{i,j} = \sum_{p = 1}^{n} C^{(k)}_{i,p} \cdot G_{p,j}
$$

它具有矩阵乘法的形式。把它看作矩阵乘法的运算，于是上述转移可以描述为

$$
C^{(k+1)} = C^{(k)} \cdot G
$$

那么把这个递推式展开可以得到

$$
C^{(k)} = \underbrace{G \cdot G \cdots G}_{k \text{ 次}} = G^k
$$

使用矩阵快速幂，在 $O(n^3 \log k)$ 的复杂度内计算结果。

### 定长最短路

???+ note "问题描述"
    给你一个 $n$ 阶加权有向图和一个整数 $k$。对于每个点对 $(u,v)$ 找到从 $u$ 到 $v$ 的恰好包含 $k$ 条边的最短路的长度。（不一定是简单路径，即路径上的点或者边可能走多次）

我们仍构造这个图的邻接矩阵 $G$，$G_{i,j}$ 表示从 $i$ 到 $j$ 的边权。如果 $i,j$ 两点之间没有边，那么 $G_{i,j}=\infty$。（有重边的情况取边权的最小值）

显然上述矩阵对应 $k=1$ 时问题的答案。我们仍假设我们知道 $k$ 的答案，记为矩阵 $L^{(k)}$。现在我们想求 $k+1$ 的答案。显然有转移方程

$$
L^{(k+1)}_{i,j} = \min_{1\le p \le n} \left\{L^{(k)}_{i,p} + G_{p,j}\right\}
$$

事实上我们可以类比矩阵乘法，你发现上述转移只是把矩阵乘法的乘积求和变成相加取最小值，于是我们定义这个运算为 $\odot$，即

$$
A \odot B = C\Leftrightarrow C_{i,j}=\min_{1\le p \le n}\left\{A_{i,p} + B_{p,j}\right\}
$$

可以证明该运算满足结合律s。于是得到

$$
L^{(k+1)} = L^{(k)} \odot G
$$

展开递推式得到

$$
L^{(k)} = \underbrace{G \odot \ldots \odot G}_{k\text{ 次}} = G^{\odot k}
$$

我们仍然可以用类似矩阵快速幂的方法计算上式。时间复杂度 $O(n^3 \log k)$。

### 限长路径计数/最短路

上述算法只适用于边数固定的情况。然而我们可以改进算法以解决边数小于等于 $k$ 的情况。具体地，考虑以下问题：

???+ note "问题描述"
    给一个 $n$ 阶有向图，边权为 $1$，然后给一个整数 $k$，你的任务是对于每个点对 $(u,v)$ 找到从 $u$ 到 $v$ 长度小于等于 $k$ 的路径的数量（不一定是简单路径，即路径上的点或者边可能走多次）。

我们对于每个点 $v$，建立一个虚点 $v'$ 用于记录答案，并在图中加入 $(v,v')$ 和 $(v',v')$ 这两条边。那么对于点对 $(u,v)$，从 $u$ 到 $v$ 边数小于等于 $k$ 的路径的数量，就和从 $u$ 到 $v'$ 边数恰好等于 $k+1$ 的路径的数量相等，这是因为对于任意一条边数为 $m(m \le k)$ 的路径 $(p_0=u)\to p_1\to p_2 \to \dots \to p_{m-1} \to (p_m=v)$，都存在一条边数为 $k+1$ 的路径 $(p_0=u)\to p_1 \to p_2 \to \dots \to p_{m-1} \to (p_m=v) \to v'  \to \dots \to v'$ 与之一一对应。

对于求边数小于等于 $k$ 的最短路，只需对每个点加一个边权为 $0$ 的自环即可。

## 矩阵类代码模板

??? note "矩阵类的一个实现"
    ```cpp
    template <typename _Tp = long long, size_t sz = 100>
    class mat
    {
    private:
        _Tp a[sz][sz];
    
    public:
        mat() { memset(a, 0, sizeof a); }
        mat operator-(const mat &T) const
        {
            mat res;
            for (int i = 0; i < sz; ++i)
                for (int j = 0; j < sz; ++j)
                    res.a[i][j] = (a[i][j] - T.a[i][j]) % MOD;
            return res;
        }
        mat operator+(const mat &T) const
        {
            mat res;
            for (int i = 0; i < sz; ++i)
                for (int j = 0; j < sz; ++j)
                    res.a[i][j] = (a[i][j] + T.a[i][j]) % MOD;
            return res;
        }
        mat operator*(const mat &T) const // 矩乘
        {
            mat res;
            int r;
            for (int i = 0; i < sz; ++i)
                for (int k = 0; k < sz; ++k)
                {
                    r = a[i][k];
                    for (int j = 0; j < sz; ++j)
                        res.a[i][j] += T.a[k][j] * r, res.a[i][j] %= MOD;
                }
            return res;
        }
        mat operator*(const _Tp &v) // 数乘
        {
            mat res;
            for (int i = 0; i < sz; i++)
                for (int j = 0; j < sz; j++)
                    res.a[i][j] = a[i][j] * v % MOD;
            return res;
        }
        mat operator^(unsigned long long x) const // 快速幂
        {
            mat res, bas;
            for (int i = 0; i < sz; ++i)
                res.a[i][i] = 1;
            for (int i = 0; i < sz; ++i)
                for (int j = 0; j < sz; ++j)
                    bas.a[i][j] = a[i][j] % MOD;
            while (x)
            {
                if (x & 1)
                    res = res * bas;
                bas = bas * bas;
                x >>= 1;
            }
            return res;
        }
    };
    ```

## 习题

- [洛谷 P1962 斐波那契数列](https://www.luogu.com.cn/problem/P1962)，即上面的例题，同题 POJ3070
- [洛谷 P1349 广义斐波那契数列](https://www.luogu.com.cn/problem/P1349)，$\text{base}$ 矩阵需要变化一下
- [洛谷 P1939【模板】矩阵加速（数列）](https://www.luogu.com.cn/problem/P1939)，$\text{base}$ 矩阵变成了 $3 \times 3$ 的矩阵，推导过程与上面差不多。

## 参考资料与注释

[^ref1]: [解释：线性系统与非线性系统 - MIT news](https://news.mit.edu/2010/explained-linear-0226)

  **本页面部分内容译自博文 [Кратчайшие пути фиксированной длины, количества путей фиксированной длины](http://e-maxx.ru/algo/fixed_length_paths) 与其英文翻译版 [Number of paths of fixed length/Shortest paths of fixed length](https://cp-algorithms.com/graph/fixed_length_paths.html)。其中俄文版版权协议为 Public Domain + Leave a Link；英文版版权协议为 CC-BY-SA 4.0。**
