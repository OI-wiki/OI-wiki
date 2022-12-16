## 定义

快速幂，二进制取幂（Binary Exponentiation，也称平方法），是一个在 $\Theta(\log n)$ 的时间内计算 $a^n$ 的小技巧，而暴力的计算需要 $\Theta(n)$ 的时间。

这个技巧也常常用在非计算的场景，因为它可以应用在任何具有结合律的运算中。其中显然的是它可以应用于模意义下取幂、矩阵幂等运算，我们接下来会讨论。

## 解释

计算 $a$ 的 $n$ 次方表示将 $n$ 个 $a$ 乘在一起：$a^{n} = \underbrace{a \times a \cdots \times a}_{n\text{ 个 a}}$。然而当 $a,n$ 太大的时侯，这种方法就不太适用了。不过我们知道：$a^{b+c} = a^b \cdot a^c,\,\,a^{2b} = a^b \cdot a^b = (a^b)^2$。二进制取幂的想法是，我们将取幂的任务按照指数的 **二进制表示** 来分割成更小的任务。

## 过程

首先我们将 $n$ 表示为 2 进制，举一个例子：

$$
3^{13} = 3^{(1101)_2} = 3^8 \cdot 3^4 \cdot 3^1
$$

因为 $n$ 有 $\lfloor \log_2 n \rfloor + 1$ 个二进制位，因此当我们知道了 $a^1, a^2, a^4, a^8, \dots, a^{2^{\lfloor \log_2 n \rfloor}}$ 后，我们只用计算 $\Theta(\log n)$ 次乘法就可以计算出 $a^n$。

于是我们只需要知道一个快速的方法来计算上述 3 的 $2^k$ 次幂的序列。这个问题很简单，因为序列中（除第一个）任意一个元素就是其前一个元素的平方。举一个例子：

$$
\begin{align}
3^1 &= 3 \\
3^2 &= \left(3^1\right)^2 = 3^2 = 9 \\
3^4 &= \left(3^2\right)^2 = 9^2 = 81 \\
3^8 &= \left(3^4\right)^2 = 81^2 = 6561
\end{align}
$$

因此为了计算 $3^{13}$，我们只需要将对应二进制位为 1 的整系数幂乘起来就行了：

$$
3^{13} = 6561 \cdot 81 \cdot 3 = 1594323
$$

将上述过程说得形式化一些，如果把 $n$ 写作二进制为 $(n_tn_{t-1}\cdots n_1n_0)_2$，那么有：

$$
n = n_t2^t + n_{t-1}2^{t-1} + n_{t-2}2^{t-2} + \cdots + n_12^1 + n_02^0
$$

其中 $n_i\in\{0,1\}$。那么就有

$$
\begin{aligned}
a^n & = (a^{n_t 2^t + \cdots + n_0 2^0})\\\\
& = a^{n_0 2^0} \times a^{n_1 2^1}\times \cdots \times a^{n_t2^t}
\end{aligned}
$$

根据上式我们发现，原问题被我们转化成了形式相同的子问题的乘积，并且我们可以在常数时间内从 $2^i$ 项推出 $2^{i+1}$ 项。

这个算法的复杂度是 $\Theta(\log n)$ 的，我们计算了 $\Theta(\log n)$ 个 $2^k$ 次幂的数，然后花费 $\Theta(\log n)$ 的时间选择二进制为 1 对应的幂来相乘。

## 实现

首先我们可以直接按照上述递归方法实现：

=== "C++"

    ```cpp
    long long binpow(long long a, long long b) {
      if (b == 0) return 1;
      long long res = binpow(a, b / 2);
      if (b % 2)
        return res * res * a;
      else
        return res * res;
    }
    ```

=== "Python"

    ```python
    def binpow(a, b):
        if b == 0:
            return 1
        res = binpow(a, b // 2)
        if (b % 2) == 1:
            return res * res * a
        else:
            return res * res
    ```

第二种实现方法是非递归式的。它在循环的过程中将二进制位为 1 时对应的幂累乘到答案中。尽管两者的理论复杂度是相同的，但第二种在实践过程中的速度是比第一种更快的，因为递归会花费一定的开销。

=== "C++"

    ```cpp
    long long binpow(long long a, long long b) {
      long long res = 1;
      while (b > 0) {
        if (b & 1) res = res * a;
        a = a * a;
        b >>= 1;
      }
      return res;
    }
    ```

=== "Python"

    ```python
    def binpow(a, b):
        res = 1
        while b > 0:
            if (b & 1):
                res = res * a
            a = a * a
            b >>= 1
        return res
    ```

模板：[Luogu P1226](https://www.luogu.com.cn/problem/P1226)

## 应用

### 模意义下取幂

???+note "问题描述"
    计算 $x^n\bmod m$。

这是一个非常常见的应用，例如它可以用于计算模意义下的乘法逆元。

既然我们知道取模的运算不会干涉乘法运算，因此我们只需要在计算的过程中取模即可。

=== "C++"

    ```cpp
    long long binpow(long long a, long long b, long long m) {
      a %= m;
      long long res = 1;
      while (b > 0) {
        if (b & 1) res = res * a % m;
        a = a * a % m;
        b >>= 1;
      }
      return res;
    }
    ```

=== "Python"

    ```python
    def binpow(a, b, m):
        a = a % m
        res = 1
        while b > 0:
            if (b & 1):
                res = res * a % m
            a = a * a % m
            b >>= 1
        return res
    ```

注意：根据费马小定理，如果 $m$ 是一个质数，我们可以计算 $x^{n\bmod (m-1)}$ 来加速算法过程。

### 计算斐波那契数

???+note "问题描述"
    计算斐波那契数列第 $n$ 项 $F_n$。

根据斐波那契数列的递推式 $F_n = F_{n-1} + F_{n-2}$，我们可以构建一个 $2\times 2$ 的矩阵来表示从 $F_i,F_{i+1}$ 到 $F_{i+1},F_{i+2}$ 的变换。于是在计算这个矩阵的 $n$ 次幂的时侯，我们使用快速幂的思想，可以在 $\Theta(\log n)$ 的时间内计算出结果。对于更多的细节参见 [斐波那契数列](./combinatorics/fibonacci.md)。

### 多次置换

???+note "问题描述"
    给你一个长度为 $n$ 的序列和一个置换，把这个序列置换 $k$ 次。

简单地把这个置换取 $k$ 次幂，然后把它应用到序列 $n$ 上即可。时间复杂度是 $O(n \log k)$ 的。

注意：给这个置换建图，然后在每一个环上分别做 $k$ 次幂（事实上做一下 $k$ 对环长取模的运算即可）可以取得更高效的算法，达到 $O(n)$ 的复杂度。

### 加速几何中对点集的操作

#### 引入

> 三维空间中，$n$ 个点 $p_i$，要求将 $m$ 个操作都应用于这些点。包含 3 种操作：
>
> 1. 沿某个向量移动点的位置（Shift）。
> 2. 按比例缩放这个点的坐标（Scale）。
> 3. 绕某个坐标轴旋转（Rotate）。
>
> 还有一个特殊的操作，就是将一个操作序列重复 $k$ 次（Loop），这个序列中也可能有 Loop 操作（Loop 操作可以嵌套）。现在要求你在低于 $O(n \cdot \textit{length})$ 的时间内将这些变换应用到这个 $n$ 个点，其中 $\textit{length}$ 表示把所有的 Loop 操作展开后的操作序列的长度。

#### 解释

让我们来观察一下这三种操作对坐标的影响：

1. Shift 操作：将每一维的坐标分别加上一个常量；
2. Scale 操作：把每一维坐标分别乘上一个常量；
3. Rotate 操作：这个有点复杂，我们不打算深入探究，不过我们仍然可以使用一个线性组合来表示新的坐标。

可以看到，每一个变换可以被表示为对坐标的线性运算，因此，一个变换可以用一个 $4\times 4$ 的矩阵来表示：

$$
\begin{bmatrix}
a_{11} & a_ {12} & a_ {13} & a_ {14} \\
a_{21} & a_ {22} & a_ {23} & a_ {24} \\
a_{31} & a_ {32} & a_ {33} & a_ {34} \\
a_{41} & a_ {42} & a_ {43} & a_ {44} \\
\end{bmatrix}
$$

使用这个矩阵就可以将一个坐标（向量）进行变换，得到新的坐标（向量）：

$$
\begin{bmatrix}
a_{11} & a_ {12} & a_ {13} & a_ {14} \\
a_{21} & a_ {22} & a_ {23} & a_ {24} \\
a_{31} & a_ {32} & a_ {33} & a_ {34} \\
a_{41} & a_ {42} & a_ {43} & a_ {44} \\
\end{bmatrix}\cdot
\begin{bmatrix} x \\ y \\ z \\ 1 \end{bmatrix}
 = \begin{bmatrix} x' \\ y' \\ z' \\ 1 \end{bmatrix}
$$

你可能会问，为什么一个三维坐标会多一个 1 出来？原因在于，如果没有这个多出来的 1，我们没法使用矩阵的线性变换来描述 Shift 操作。

#### 过程

接下来举一些简单的例子来说明我们的思路：

1.  Shift 操作：让 $x$ 坐标方向的位移为 $5$，$y$ 坐标的位移为 $7$，$z$ 坐标的位移为 $9$：

    $$
    \begin{bmatrix}
    1 & 0 & 0 & 5 \\
    0 & 1 & 0 & 7 \\
    0 & 0 & 1 & 9 \\
    0 & 0 & 0 & 1 \\
    \end{bmatrix}
    $$

2.  Scale 操作：把 $x$ 坐标拉伸 10 倍，$y,z$ 坐标拉伸 5 倍：

    $$
    \begin{bmatrix}
    10 & 0 & 0 & 0 \\
    0 & 5 & 0 & 0 \\
    0 & 0 & 5 & 0 \\
    0 & 0 & 0 & 1 \\
    \end{bmatrix}
    $$

3.  Rotate 操作：绕 $x$ 轴旋转 $\theta$ 弧度，遵循右手定则（逆时针方向）

    $$
    \begin{bmatrix}
    1 & 0 & 0 & 0 \\
    0 & \cos \theta & \sin \theta & 0 \\
    0 & -\sin \theta & \cos \theta & 0 \\
    0 & 0 & 0 & 1 \\
    \end{bmatrix}
    $$

现在，每一种操作都被表示为了一个矩阵，变换序列可以用矩阵的乘积来表示，而一个 Loop 操作相当于取一个矩阵的 k 次幂。这样可以用 $O(m \log k)$ 计算出整个变换序列最终形成的矩阵。最后将它应用到 $n$ 个点上，总复杂度 $O(n + m \log k)$。

### 定长路径计数

???+note "问题描述"
    给一个有向图（边权为 1），求任意两点 $u,v$ 间从 $u$ 到 $v$，长度为 $k$ 的路径的条数。

我们把该图的邻接矩阵 M 取 k 次幂，那么 $M_{i,j}$ 就表示从 $i$ 到 $j$ 长度为 $k$ 的路径的数目。该算法的复杂度是 $O(n^3 \log k)$。有关该算法的细节请参见 [矩阵](./linear-algebra/matrix.md) 页面。

### 模意义下大整数乘法

> 计算 $a\times b\bmod m,\,\,a,b\le m\le 10^{18}$。

与二进制取幂的思想一样，这次我们将其中的一个乘数表示为若干个 2 的整数次幂的和的形式。因为在对一个数做乘 2 并取模的运算的时侯，我们可以转化为加减操作防止溢出。这样仍可以在 $O (\log_2 m)$ 的时内解决问题。递归方法如下：

$$
a \cdot b = \begin{cases}
0 &\text{if }a = 0 \\\\
2 \cdot \frac{a}{2} \cdot b &\text{if }a > 0 \text{ and }a \text{ even} \\\\
2 \cdot \frac{a-1}{2} \cdot b + b &\text{if }a > 0 \text{ and }a \text{ odd}
\end{cases}
$$

#### 快速乘

但是 $O(\log_2 m)$ 的“龟速乘”还是太慢了，这在很多对常数要求比较高的算法比如 Miller_Rabin 和 Pollard-Rho 中，就显得不够用了。所以我们要介绍一种可以处理模数在 `long long` 范围内、不需要使用黑科技 `__int128` 的、复杂度为 $O(1)$ 的“快速乘”。

我们发现：

$$
a\times b\bmod m=a\times b-\left\lfloor \dfrac{ab}m \right\rfloor\times m
$$

我们巧妙运用 `unsigned long long` 的自然溢出：

$$
a\times b\bmod m=a\times b-\left\lfloor \dfrac{ab}m \right\rfloor\times m=\left(a\times b-\left\lfloor \dfrac{ab}m \right\rfloor\times m\right)\bmod 2^{64}
$$

于是在算出 $\left\lfloor\dfrac{ab}m\right\rfloor$ 后，两边的乘法和中间的减法部分都可以使用 `unsigned long long` 直接计算，现在我们只需要解决如何计算 $\left\lfloor\dfrac {ab}m\right\rfloor$。

我们考虑先使用 `long double` 算出 $\dfrac am$ 再乘上 $b$。

既然使用了 `long double`，就无疑会有精度误差。极端情况就是第一个有效数字（二进制下）在小数点后一位。在 `x86-64` 机器下，`long double` 将被解释成 $80$ 位拓展小数（即符号为 $1$ 位，指数为 $15$ 位，尾数为 $64$ 位），所以 `long double` 最多能精确表示的有效位数为 $64$[^note1]。所以 $\dfrac am$ 最差从第 $65$ 位开始出错，误差范围为 $\left(-2^{-64},2^{64}\right)$。乘上 $b$ 这个 $64$ 位整数，误差范围为 $(-0.5,0.5)$，再加上 $0.5$ 误差范围为 $(0,1)$，取整后误差范围位 $\{0,1\}$。于是乘上 $-m$ 后，误差范围变成 $\{0,-m\}$，我们需要判断这两种情况。

因为 $m$ 在 `long long` 范围内，所以如果计算结果 $r$ 在 $[0,m)$ 时，直接返回 $r$，否则返回 $r+m$，当然你也可以直接返回 $(r+m)\bmod m$。

代码实现如下：

```cpp
long long binmul(long long a, long long b, long long m) {
  unsigned long long c =
      (unsigned long long)a * b -
      (unsigned long long)((long double)a / m * b + 0.5L) * m;
  if (c < m) return c;
  return c + m;
}
```

### 高精度快速幂

??? note "前置技能"
    请先学习 [高精度](./bignum.md)

???+note " 例题【NOIP2003 普及组改编·麦森数】（[原题在此](https://www.luogu.com.cn/problem/P1045)）"
    题目大意：从文件中输入 P（1000&lt;P&lt;3100000），计算 $2^P−1$ 的最后 100 位数字（用十进制高精度数表示），不足 100 位时高位补 0。

代码实现如下：

```cpp
--8<-- "docs/math/code/quick-pow/quick-pow_1.cpp"
```

### 同一底数与同一模数的预处理快速幂

在同一底数与同一模数的条件下，可以利用分块思想，用一定的时间（一般是 $O(\sqrt n)$）预处理后用 $O(1)$ 的时间回答一次幂询问。

#### 过程

1. 选定一个数 $s$，预处理出 $a^0$ 到 $a^s$ 与 $a^{0\cdot s}$ 到 $a^{\lceil\frac ps\rceil\cdot s}$ 的值并存在一个（或两个）数组里；
2. 对于每一次询问 $a^b\bmod p$，将 $b$ 拆分成 $\left\lfloor\dfrac bs\right\rfloor\cdot s+b\bmod s$，则 $a^b=a^{\lfloor\frac bs\rfloor\cdot s}\times a^{b\bmod s}$，可以 $O(1)$ 求出答案。

关于这个数 $s$ 的选择，我们一般选择 $\sqrt p$ 或者一个大小适当的 $2$ 的次幂（选择 $\sqrt p$ 可以使预处理较优，选择 $2$ 的次幂可以使用位运算优化/简化计算）。

??? note " 参考代码"
    ```cpp
    int pow1[65536], pow2[65536];
    
    void preproc(int a, int mod) {
      pow1[0] = pow2[0] = 1;
      for (int i = 1; i < 65536; i++) pow1[i] = 1LL * pow1[i - 1] * a % mod;
      int pow65536 = 1LL * pow1[65535] * a % mod;
      for (int i = 1; i < 65536; i++) pow2[i] = 1LL * pow2[i - 1] * pow65536 % mod;
    }
    
    int query(int pows) { return 1LL * pow1[pows & 65535] * pow2[pows >> 16]; }
    ```

## 习题

- [UVa 1230 - MODEX](http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=24&page=show_problem&problem=3671)
- [UVa 374 - Big Mod](http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=24&page=show_problem&problem=310)
- [UVa 11029 - Leading and Trailing](https://uva.onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=1970)
- [Codeforces - Parking Lot](http://codeforces.com/problemset/problem/630/I)
- [SPOJ - The last digit](http://www.spoj.com/problems/LASTDIG/)
- [SPOJ - Locker](http://www.spoj.com/problems/LOCKER/)
- [LA - 3722 Jewel-eating Monsters](https://icpcarchive.ecs.baylor.edu/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1723)
-   [SPOJ - Just add it](http://www.spoj.com/problems/ZSUM/)

    **本页面部分内容译自博文 [Бинарное возведение в степень](http://e-maxx.ru/algo/binary_pow) 与其英文翻译版 [Binary Exponentiation](https://cp-algorithms.com/algebra/binary-exp.html)。其中俄文版版权协议为 Public Domain + Leave a Link；英文版版权协议为 CC-BY-SA 4.0。**

## 参考资料与注释

[^note1]: 参见 [C 语言小数表示法 - 维基百科](https://en.wikipedia.org/wiki/Double-precision_floating-point_format)
