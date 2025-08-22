autor: iamtwz, billchenchina, CBW2007, CCXXXI, chinggg, Enter-tainer, eyedeng, FFjet, gaojude, Great-designer, H-J-Granger, Henry-ZHR, hsfzLZH1, Ir1d, kenlig, Konano, ksyx, luoguyuntianming, Marcythm, Menci, NachtgeistW, ouuan, Peanut-Tang, qwqAutomaton, sshwy, StudyingFather, Tiphereth-A, TrisolarisHD, TRSWNCA, Xeonacid, Yuuko10032, Zhangjiacheng2006, Zhoier, Hszzzx, shenshuaijie, kfy666

## 定义

快速幂，二进制取幂（Binary Exponentiation，也称平方法），是一个在 $\Theta(\log n)$ 的时间内计算 $a^n$ 的小技巧，而暴力的计算需要 $\Theta(n)$ 的时间。

这个技巧也常常用在非计算的场景，因为它可以应用在任何具有结合律的运算中。其中显然的是它可以应用于模意义下取幂、矩阵幂等运算，我们接下来会讨论。

## 解释

计算 $a$ 的 $n$ 次方表示将 $n$ 个 $a$ 乘在一起：$a^{n} = \underbrace{a \times a \cdots \times a}_{n\text{ 个 a}}$。然而当 $a,n$ 太大的时侯，这种方法就不太适用了。不过我们知道：$a^{b+c} = a^b \cdot a^c,\,\,a^{2b} = a^b \cdot a^b = (a^b)^2$。二进制取幂的想法是，我们将取幂的任务按照指数的 **二进制表示** 来分割成更小的任务。

## 过程

### 迭代版本

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

### 递归版本

上述迭代版本中，由于 $2^{i+1}$ 项依赖于 $2^i$，使得其转换为递归版本比较困难（一方面需要返回一个额外的 $a^{2^i}$，对函数来说无法实现一个只返回计算结果的接口；另一方面则是必须从低位往高位计算，即从高位往低位调用，这也造成了递归实现的困扰），下面则提供递归版本的思路。

给定形式 $n_{t\dots i} = (n_tn_{t-1}\cdots n_i)_2$，即 $n_{t\dots i}$ 表示将 $n$ 的前 $t - i + 1$ 位二进制位当作一个二进制数，则有如下变换：

$$
\begin{aligned}
n &= n_{t\dots 0} \\
  &= 2\times n_{t\dots 1} + n_0\\
  &= 2\times (2\times n_{t\dots 2} + n_1) + n_0 \\
  &\cdots
\end{aligned}
$$

那么有：

$$
\begin{aligned}
a^n &= a^{n_{t\dots 0}} \\
    &= a^{2\times n_{t\dots 1} + n_0} = \left(a^{n_{t\dots 1}}\right)^2  a^{n_0} \\
    &= \left(a^{2\times n_{t\dots 2} + n_1}\right)^2  a^{n_0} = \left(\left(a^{n_{t\dots 2}}\right)^2 a^{n_1}\right)^2  a^{n_0} \\
    &\cdots
\end{aligned}
$$

如上所述，在递归时，对于不同的递归深度是相同的处理：$a^{n_{t\dots i}} = (a^{n_{t\dots (i+1)}})^2a^{n_i}$，即将当前递归的二进制数拆成两部分：最低位在递归出来时乘上去，其余部分则变成新的二进制数递归进入更深一层作相同的处理。

可以观察到，每递归深入一层则二进制位减少一位，所以该算法的时间复杂度也为 $\Theta(\log n)$。

## 应用

### 模意义下取幂

???+ example "[洛谷 P1226【模板】快速幂](https://www.luogu.com.cn/problem/P1226)"
    给定三个整数 $a,b,p$，求 $a^b\bmod p$。

这是一个非常常见的应用，例如它可以用于计算模意义下的乘法逆元。既然我们知道取模的运算不会干涉乘法运算，因此我们只需要在计算的过程中取模即可。

首先我们可以直接按照上述递归方法实现：

???+ note "参考实现"
    === "C++"
        ```cpp
        --8<-- "docs/math/code/binary-exponentiation/luogu-P1226-1.cpp:core"
        ```
    
    === "Python"
        ```python
        --8<-- "docs/math/code/binary-exponentiation/luogu-P1226-1.py:core"
        ```

第二种实现方法是非递归式的。它在循环的过程中将二进制位为 1 时对应的幂累乘到答案中。尽管两者的理论复杂度是相同的，但第二种在实践过程中的速度是比第一种更快的，因为递归会花费一定的开销。

???+ note "参考实现"
    === "C++"
        ```cpp
        --8<-- "docs/math/code/binary-exponentiation/luogu-P1226-2.cpp:core"
        ```
    
    === "Python"
        ```python
        --8<-- "docs/math/code/binary-exponentiation/luogu-P1226-2.py:core"
        ```

???+ warning "注意"
    当指数很大时，需利用 [扩展欧拉定理](./number-theory/fermat.md#扩展欧拉定理) 降幂后计算。

### 计算斐波那契数

根据斐波那契数列的递推式 $F_n = F_{n-1} + F_{n-2}$，我们可以构建一个 $2\times 2$ 的矩阵来表示从 $F_i,F_{i+1}$ 到 $F_{i+1},F_{i+2}$ 的变换。于是在计算这个矩阵的 $n$ 次幂的时侯，我们使用快速幂的思想，可以在 $\Theta(\log n)$ 的时间内计算出结果。对于更多的细节参见 [斐波那契数列](./combinatorics/fibonacci.md)，矩阵快速幂的实现参见 [矩阵加速递推](../math/linear-algebra/matrix.md#矩阵加速递推) 中的实现。

### 多次置换

???+ note "问题描述"
    给你一个长度为 $n$ 的序列和一个置换，把这个序列置换 $k$ 次。

简单地把这个置换取 $k$ 次幂，然后把它应用到序列上即可。时间复杂度为 $O(n \log k)$。对于更多的细节参见 [置换的复合](./permutation.md#复合)。

???+ warning "注意"
    对这个置换建图，然后在每一个环上分别做 $k$ 次幂（事实上等价于 $k$ 对环长取模），可以在 $O(n)$ 的时间复杂度下解决此问题。

### 加速几何中对点集的操作

???+ example "[HDU 4087 A Letter to Programmers](https://acm.hdu.edu.cn/showproblem.php?pid=4087)"
    给定三维空间中 $n$ 个点 $p_i$，要求将 $m$ 个操作都应用于这些点。包含 3 种操作：
    
    1.  沿某个向量移动点的位置（Shift）。
    2.  按比例缩放这个点的坐标（Scale）。
    3.  绕某条直线旋转（Rotate）。
    
    还有一个特殊的操作，就是将某个操作序列重复 $k$ 次（Repeat），Repeat 操作可以嵌套。输出操作结束后每个点的坐标。

让我们来观察一下这三种操作对坐标的影响：

1.  Shift 操作：将每一维的坐标分别加上一个常量；
2.  Scale 操作：把每一维坐标分别乘上一个常量；
3.  Rotate 操作：参考 [Rotation matrix from axis and angle](https://en.wikipedia.org/wiki/Rotation_matrix#Rotation_matrix_from_axis_and_angle)，可以用旋转矩阵乘以点对应的向量得到。

可以看到，每一个操作可以用一个 $4\times 4$ 的矩阵来表示：

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

在矩阵中，我们在三维坐标之外添加了一维，并将其置为 $1$。这样的话，我们就可以使用矩阵乘法来描述 Shift 操作了。

对于每个操作，可以按如下方法构造矩阵。

1.  （Shift 操作）让 $x$ 坐标方向的位移为 $\Delta x$，$y$ 坐标的位移为 $\Delta y$，$z$ 坐标的位移为 $\Delta z$：

    $$
    \begin{bmatrix}
    1 & 0 & 0 & \Delta x \\
    0 & 1 & 0 & \Delta y \\
    0 & 0 & 1 & \Delta z \\
    0 & 0 & 0 & 1 \\
    \end{bmatrix}
    $$

2.  （Scale 操作）把 $x$ 坐标拉伸 $\Delta x$ 倍，$y$ 坐标拉伸 $\Delta y$ 倍，$z$ 坐标拉伸 $\Delta z$ 倍：

    $$
    \begin{bmatrix}
    \Delta x & 0 & 0 & 0 \\
    0 & \Delta y & 0 & 0 \\
    0 & 0 & \Delta z & 0 \\
    0 & 0 & 0 & 1 \\
    \end{bmatrix}
    $$

3.  （Rotate 操作）绕单位向量 $\mathbf{u}=(u_x,u_y,u_z)$ 逆时针旋转 $\theta$ 弧度

    $$
    \begin{bmatrix}
    u_x^2 \left(1-\cos \theta\right) + \cos \theta & u_x u_y \left(1-\cos \theta\right) - u_z \sin \theta & u_x u_z \left(1-\cos \theta\right) + u_y \sin \theta & 0 \\ 
    u_x u_y \left(1-\cos \theta\right) + u_z \sin \theta & u_y^2\left(1-\cos \theta\right) + \cos \theta & u_y u_z \left(1-\cos \theta\right) - u_x \sin \theta & 0 \\ 
    u_x u_z \left(1-\cos \theta\right) - u_y \sin \theta & u_y u_z \left(1-\cos \theta\right) + u_x \sin \theta & u_z^2\left(1-\cos \theta\right) + \cos \theta & 0 \\
    0 & 0 & 0 & 1
    \end{bmatrix}
    $$

现在，每一种操作都被表示为了一个矩阵，变换序列可以用矩阵的乘积来表示，而一个 Repeat 操作相当于取一个矩阵的 $k$ 次幂。这样可以用 $O(m \log k)$ 的时间计算出整个变换序列最终形成的矩阵。最后将它应用到 $n$ 个点上，总复杂度 $O(n + m \log k)$。

### 定长路径计数

???+ note "问题描述"
    给一个有向图（边权为 1），求任意两点 $u,v$ 间从 $u$ 到 $v$，长度为 $k$ 的路径的条数。

我们把该图的邻接矩阵 $M$ 取 $k$ 次幂，那么 $M_{i,j}$ 就表示从 $i$ 到 $j$ 长度为 $k$ 的路径的数目。该算法的复杂度是 $O(n^3 \log k)$。有关该算法的细节请参见 [矩阵](./linear-algebra/matrix.md#定长路径统计) 页面。

### 模意义下的整数乘法

???+ note "问题描述"
    给定非负整数 $a,b$ 和正整数 $m$，计算 $a\times b\bmod m$，其中 $a,b\le m\le 10^{18}$。

与二进制取幂的思想一样，这次我们将其中的一个乘数表示为若干个 2 的整数次幂的和的形式。因为在对一个数做乘 2 并取模的运算的时侯，我们可以转化为加减操作防止整型溢出。这样可以在 $O (\log m)$ 的时间复杂度下解决问题。递归方法如下：

$$
a \cdot b = \begin{cases}
0 &\text{if }a = 0 \\\\
2 \cdot \frac{a}{2} \cdot b &\text{if }a > 0 \text{ and }a \text{ even} \\\\
2 \cdot \frac{a-1}{2} \cdot b + b &\text{if }a > 0 \text{ and }a \text{ odd}
\end{cases}
$$

#### 快速乘

本节介绍一种可以处理模数在 `long long` 范围内，不需要使用 `__int128` 且复杂度为 $O(1)$ 的「快速乘」。

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

既然使用了 `long double`，就无疑会有精度误差。极端情况就是第一个有效数字（二进制下）在小数点后一位。在 64 位系统中，`long double` 通常表示为 $80$ 位扩展精度浮点数（即符号为 $1$ 位，指数为 $15$ 位，尾数为 $64$ 位），所以 `long double` 最多能精确表示的有效位数为 $64$[^note1]。所以 $\dfrac am$ 最差从第 $65$ 位开始出错，误差范围为 $\left(-2^{-64},2^{-64}\right)$。乘上 $b$ 这个 $64$ 位整数，误差范围为 $(-0.5,0.5)$，再加上 $0.5$ 误差范围为 $(0,1)$，取整后误差范围位 $\{0,1\}$。于是乘上 $-m$ 后，误差范围变成 $\{0,-m\}$，我们需要判断这两种情况。

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

如今，绝大多数测评系统所配备的 C/C++ 编译器已支持 `__int128` 类型，因此也可以利用 [Barrett Reduction](https://en.wikipedia.org/wiki/Barrett_reduction) 进行快速乘。之所以不直接将乘数类型提升至 `__int128` 后取模计算是因为此方法仍然可以节省一次时间可观的 `__int128` 类型取模。

### 高精度快速幂

前置技能：[大整数乘法](./bignum.md#乘法)

???+ example "[洛谷 P1045 \[NOIP 2003 普及组\] 麦森数](https://www.luogu.com.cn/problem/P1045)"
    给定整数 $P$（$1000 < P < 3100000$），计算 $2^P−1$ 的位数与最后 $500$ 位数字（用十进制数表示），不足 $500$ 位时高位补 0。

??? note "代码实现"
    ```cpp
    --8<-- "docs/math/code/binary-exponentiation/luogu-P1045.cpp"
    ```

### 同一底数与同一模数的预处理快速幂

在同一底数与同一模数的条件下，可以利用 [分块思想](../ds/decompose.md)，用一定的时间（一般是 $O(\sqrt n)$）预处理后用 $O(1)$ 的时间回答一次幂询问。

#### 过程

1.  选定一个数 $s$，预处理出 $a^0$ 到 $a^s$ 与 $a^{0\cdot s}$ 到 $a^{\lfloor\frac ps\rfloor\cdot s}$ 的值并存在两个数组里；
2.  对于每一次询问 $a^b\bmod p$，将 $b$ 拆分成 $\left\lfloor\dfrac bs\right\rfloor\cdot s+b\bmod s$，则 $a^b=a^{\lfloor\frac bs\rfloor\cdot s}\times a^{b\bmod s}$，可以 $O(1)$ 求出答案。

关于这个数 $s$ 的选择，我们一般选择 $\sqrt p$ 或者一个大小适当的 $2$ 的次幂。选择 $\sqrt p$ 可以使预处理较优，选择 $2$ 的次幂可以使用位运算简化计算。

??? note "参考代码"
    ```cpp
    int pow1[65536], pow2[65536];
    
    void preproc(int a, int mod) {
      pow1[0] = pow2[0] = 1;
      for (int i = 1; i < 65536; i++) pow1[i] = 1LL * pow1[i - 1] * a % mod;
      int pow65536 = 1LL * pow1[65535] * a % mod;
      for (int i = 1; i < 65536; i++) pow2[i] = 1LL * pow2[i - 1] * pow65536 % mod;
    }
    
    int query(int pows) {
      return 1LL * pow1[pows & 65535] * pow2[pows >> 16] % mod;
    }
    ```

## 习题

-   [UVa 1230 - MODEX](http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=24&page=show_problem&problem=3671)
-   [UVa 374 - Big Mod](http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=24&page=show_problem&problem=310)
-   [UVa 11029 - Leading and Trailing](https://uva.onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=1970)
-   [Codeforces - Parking Lot](http://codeforces.com/problemset/problem/630/I)
-   [SPOJ - The last digit](http://www.spoj.com/problems/LASTDIG/)
-   [SPOJ - Locker](http://www.spoj.com/problems/LOCKER/)
-   [SPOJ - Just add it](http://www.spoj.com/problems/ZSUM/)

**本页面部分内容译自博文 [Бинарное возведение в степень](http://e-maxx.ru/algo/binary_pow) 与其英文翻译版 [Binary Exponentiation](https://cp-algorithms.com/algebra/binary-exp.html)。其中俄文版版权协议为 Public Domain + Leave a Link；英文版版权协议为 CC-BY-SA 4.0。**

## 参考资料与注释

[^note1]: 参见 [C 语言小数表示法 - 维基百科](https://en.wikipedia.org/wiki/Double-precision_floating-point_format)
