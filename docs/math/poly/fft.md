author: AndrewWayne, GavinZhengOI. ChungZH, henryrabbit, Xeonacid, sshwy, Yukimaikoriya

前置知识： [复数](../complex.md) 。

本文将介绍一种算法，它支持在 $O(n\log n)$ 的时间内计算两个 $n$ 度的多项式的乘法，比朴素的 $O(n^2)$ 算法更高效。由于两个整数的乘法也可以被当作多项式乘法，因此这个算法也可以用来加速大整数的乘法计算。

## 概述

离散傅里叶变换（Discrete Fourier Transform，缩写为 DFT），是傅里叶变换在时域和频域上都呈离散的形式，将信号的时域采样变换为其 DTFT 的频域采样。

FFT 是一种高效实现 DFT 的算法，称为快速傅立叶变换（Fast Fourier Transform，FFT）。它对傅里叶变换的理论并没有新的发现，但是对于在计算机系统或者说数字系统中应用离散傅立叶变换，可以说是进了一大步。快速数论变换 (NTT) 是快速傅里叶变换（FFT）在数论基础上的实现。

在 1965 年，Cooley 和 Tukey 发表了快速傅里叶变换算法。事实上 FFT 早在这之前就被发现过了，但是在当时现代计算机并未问世，人们没有意识到 FFT 的重要性。一些调查者认为 FFT 是由 Runge 和 König 在 1924 年发现的。但事实上高斯早在 1805 年就发明了这个算法，但一直没有发表。

## 多项式的表示

### 系数表示法

系数表示法就是用一个多项式的各个项系数来表达这个多项式，即使用一个系数序列来表示多项式：

$$
f(x) = a_0+a_1x+a_2x^2+\cdots +a_{n}x^{n} \Leftrightarrow f(x) = \{a_0, a_1, \cdots,a_{n}\}
$$

### 点值表示法

点值表示法是把这个多项式看成一个函数，从上面选取 $n+1$ 个点，从而利用这 $n+1$ 个点来唯一的表示这个函数。

为什么用 $n+1$ 个点就能唯一的表示这个函数了呢？想一下高斯消元法，两点确定一条直线。再来一个点，能确定这个直线中的另一个参数，那么也就是说 $n+1$ 个点能确定 $n$ 个参数（不考虑倍数点之类的没用点）。

设

$$
\begin{array}{c}
f(x_0) = y_0 = a_0 + a_1x_0+a_2x_0^2+a_3x_0^3+ \cdots + a_nx_0^n\\
f(x_1) = y_1 = a_0 + a_1x_1+a_2x_1^2+a_3x_1^3+ \cdots + a_nx_1^n\\
f(x_2) = y_2 = a_0 + a_1x_2+a_2x_2^2+a_3x_2^3+ \cdots + a_nx_2^n\\
\vdots\\
f(x_{n}) = y_{n} = a_0 + a_1x_{n}+a_2x_{n}^2+a_3x_{n}^3+ \cdots + a_nx_{n}^n
\end{array}
$$

那么用点值表示法表示 $f(x)$ 如下

$$
f(x) = a_0+a_1x+a_2x^2+\cdots +a_{n}x^{n} \Leftrightarrow f(x) = \{(x_0,y_0),(x_1,y_1), \cdots,(x_n,y_{n})\}
$$

通俗地说，多项式由系数表示法转为点值表示法的过程，就是 DFT 的过程。相对地，把一个多项式的点值表示法转化为系数表示法的过程，就是 IDFT。而 FFT 就是通过取某些特殊的 $x$ 的点值来加速 DFT 和 IDFT 的过程。

## 单位复根

考虑这样一个问题：

DFT 是把多项式从系数表示转到了点值表示，那么我们把点值相乘之后，如果能够快速还原成系数表示，是不是就完美解决我们的问题了呢？上述过程如下：

假设我们 DFT 过程对于两个多项式选取的 $x$ 序列相同，那么可以得到

$$
f(x)={(x_0, f(x_0)), (x_1, f(x_1)), (x_2, f(x_2)), \cdots, (x_n, f(x_n))}\\
g(x)={(x_0, g(x_0)), (x_1, g(x_1)), (x_2, g(x_2)), \cdots, (x_n, g(x_n))}
$$

如果我们设 $F(x) = f(x) \cdot g(x)$ ，那么很容易得到 $F(x)$ 的点值表达式：

$$
F(x) = \{(x_0, f(x_0)g(x_0)), (x_1, f(x_1)g(x_1)), (x_2, f(x_2)g(x_2)), \cdots, (x_n, f(x_n)g(x_n))\}
$$

但是我们要的是系数表达式，接下来问题变成了从点值回到系数。如果我们带入到高斯消元法的方程组中去，会把复杂度变得非常高。光是计算 $x^i(0 \leq i \leq n)$ 就是 $n$ 项，这就已经 $O(n^2)$ 了，更别说还要把 $n+1$ 个方程进行消元……

这里会不会觉得我们不去计算 $x^i$ 比较好呢？ $1$ 和 $-1$ 的幂都很好算，但是也仅仅有两个不够啊，我们至少需要 $n+1$ 个。想到我们刚刚学的长度为 $1$ 的虚数了吗？不管怎么乘长度都是 $1$ 。我们需要的是 $\omega^k=1$ 中的 $\omega$ ，很容易想到 $-i$ 和 $1$ 是符合的。那其他的呢？

![img](./images/fft2.jpg)

现在我们看上图的圆圈。容易发现这是一个单位圆（圆心为原点，半径为 $1$ ），单位圆上的向量模长均为 $1$ ，根据复数的运算法则，两个复数相乘，在复平面上表示为两个向量模长相乘，辐角相加。因此两个模长为 $1$ 的向量相乘，得到的仍是模长为 $1$ 的向量，辐角为两个向量辐角的和。因此我们可以将 $\omega^k=1$ 中的 $\omega$ 理解为复平面上的一个单位向量，满足它的辐角的 $k$ 倍恰好是 $360^\circ$ ——即把圆周 $k$ 等分的角。我们把符合以上条件的复数（复平面上的向量）称为复根，用 $\omega$ 表示。

### 定义

严谨地，我们称 $x^n=1$ 在复数意义下的解是 $n$ 次复根。显然，这样的解有 $n$ 个，设 $\omega_n=e^{\frac{2\pi i}{n}}$ ，则 $x^n=1$ 的解集表示为 $\{w_n^k\mid k=0,1\cdots,n-1\}$ 。我们称 $w_n$ 是 $n$ 次单位复根（The $n$ -th roots of unity）。根据复平面的知识， $n$ 次单位复根是复平面把单位圆 $n$ 等分的第一个角所对应的向量。其他复根均可以用单位复根的幂表示。

另一方面，根据欧拉公式，还可以得到 $\omega_n=e^{\frac{2\pi i}{n}}=\cos\left(\dfrac{2\pi i}{n}\right)+i\cdot \sin\left(\dfrac{2\pi i}{n}\right)$ 。

举个例子，当 $n=4$ 时， $w_n=i$ ，即 $i$ 就是 $4$ 次单位复根：

![img](./images/fft3.png)

那么很容易发现当 $n = 4$ 的时候，相当于把单位圆等分 $n= 4$ 份。然后每一份按照极角编号。那么是不是（在 $n = 4$ 的时候）我们只要知道 $\omega_4^1$ （因为他的角度是相当于单位角度），就能知道 $\omega_4^0, \omega_4^1, \omega_4^2, \omega_4^3$ 。

 $\omega_4^0$ 恒等于 $1$ ， $\omega_4^2$ 的角度是 $\omega_4^0$ 的两倍，所以 $\omega_4^2 = (\omega_4^1)^2 = i^2=-1$ ，依次以此类推。

### 性质

单位复根有三个重要的性质。对于任意正整数 $n$ 和整数 $k$ ：

$$
\omega_n^n=1\\
\omega_n^k=\omega_{2n}^{2k}\\
\omega_{2n}^{k+n}=-\omega_{2n}^k\\
$$

## 快速傅里叶变换

FFT 算法的基本思想是分治。就 DFT 来说，它分治地来求当 $x=\omega_n^k$ 的时候 $f(x)$ 的值。他的分治思想体现在将多项式分为奇次项和偶次项处理。

举个例子，对于一共 $8$ 项的多项式

$$
f(x) = a_0 + a_1x + a_2x^2+a_3x^3+a_4x^4+a_5x^5+a_6x^6+a_7x^7
$$

按照次数的奇偶来分成两组，然后右边提出来一个 $x$ 

$$
\begin{split}
f(x) &= (a_0+a_2x^2+a_4x^4+a_6x^6) + (a_1x+a_3x^3+a_5x^5+a_7x^7)\\
     &= (a_0+a_2x^2+a_4x^4+a_6x^6) + x(a_1+a_3x^2+a_5x^4+a_7x^6)
\end{split}
$$

分别用奇偶次次项数建立新的函数

$$
G(x) = a_0+a_2x+a_4x^2+a_6x^3\\
H(x)=a_1+a_3x+a_5x^2+a_7x^3
$$

那么原来的 $f(x)$ 用新函数表示为

$$
F(x)=G\left(x^2\right) + x  \times  H\left(x^2\right)
$$

利用单位复根的性质得到

$$
\begin{split}
\operatorname{DFT}(f(\omega_n^k))
&=\operatorname{DFT}(G((\omega_n^k)^2)) + \omega_n^k  \times \operatorname{DFT}(H((\omega_n^k)^2))\\
&=\operatorname{DFT}(G(\omega_n^{2k})) + \omega_n^k  \times \operatorname{DFT}(H(\omega_n^{2k}))\\
&=\operatorname{DFT}(G(\omega_{n/2}^k)) + \omega_n^k  \times \operatorname{DFT}(H(\omega_{n/2}^k))
\end{split}
$$

同理可得

$$
\begin{split}
\operatorname{DFT}(f(\omega_n^{k+n/2}))
&=\operatorname{DFT}(G(\omega_n^{2k+n})) + \omega_n^{k+n/2}  \times \operatorname{DFT}(H(\omega_n^{2k+n}))\\
&=\operatorname{DFT}(G(\omega_n^{2k})) - \omega_n^k  \times \operatorname{DFT}(H(\omega_n^{2k}))\\
&=\operatorname{DFT}(G(\omega_{n/2}^k)) - \omega_n^k  \times \operatorname{DFT}(H(\omega_{n/2}^k))
\end{split}
$$

因此我们求出了 $\operatorname{DFT}(G(\omega_{n/2}^k))$ 和 $\operatorname{DFT}(H(\omega_{n/2}^k))$ 后，就可以同时求出 $\operatorname{DFT}(f(\omega_n^k))$ 和 $\operatorname{DFT}(f(\omega_n^{k+n/2}))$ 。于是对 $G$ 和 $H$ 分别递归 DFT 即可。

考虑到分治 DFT 能处理的多项式长度只能是 $2^m(m \in N^ \ast )$ ，否则在分治的时候左右不一样长，右边就取不到系数了。所以要在第一次 DFT 之前就把序列向上补成长度为 $2^m(m \in N^\ast )$ （高次系数补 $0$ ）、最高项次数为 $2^m-1$ 的多项式。

在代入值的时候，因为要代入 $n$ 个不同值，所以我们代入 $\omega_n^0,\omega_n^1,\omega_n^2,\cdots, \omega_n^{n-1} (n=2^m(m \in N^ \ast ))$ 一共 $2^m$ 个不同值。

代码实现方面，STL 提供了复数的模板，当然也可以手动实现。两者区别在于，使用 STL 的 `complex` 可以调用 `exp` 函数求出 $\omega_n$ 。但事实上使用欧拉公式得到的虚数来求 $\omega_n$ 也是等价的。

???+ note "递归版 FFT"
    ```cpp
    #include <cmath>
    #include <complex>
    
    typedef std::complex<double> Comp;  // STL complex
    
    const Comp I(0, 1);  // i
    const int MAX_N = 1 << 20;
    
    Comp tmp[MAX_N];
    
    void DFT(Comp *f, int n, int rev) {  // rev=1,DFT; rev=-1,IDFT
      if (n == 1) return;
      for (int i = 0; i < n; ++i) tmp[i] = f[i];
      for (int i = 0; i < n; ++i) {  //偶数放左边，奇数放右边
        if (i & 1)
          f[n / 2 + i / 2] = tmp[i];
        else
          f[i / 2] = tmp[i];
      }
      Comp *g = f, *h = f + n / 2;
      DFT(g, n / 2, rev), DFT(h, n / 2, rev);  //递归DFT
      Comp cur(1, 0), step(cos(2 * M_PI / n), sin(2 * M_PI * rev / n));
      // Comp step=exp(I*(2*M_PI/n*rev));//两个step定义是等价的
      for (int k = 0; k < n / 2; ++k) {
        tmp[k] = g[k] + cur * h[k];
        tmp[k + n / 2] = g[k] - cur * h[k];
        cur *= step;
      }
      for (int i = 0; i < n; ++i) f[i] = tmp[i];
    }
    ```

时间复杂度 $O(n\log n)$ 。

### 蝴蝶变换

这个算法还可以从“分治”的角度继续优化。我们每一次都会把整个多项式的奇数次项和偶数次项系数分开，一只分到只剩下一个系数。但是，这个递归的过程需要更多的内存。因此，我们可以先“模仿递归”把这些系数在原数组中“拆分”，然后再“倍增”地去合并这些算出来的值。然而我们又要如何去拆分这些数呢？

设初始序列为 $\{x_0, x_1, x_2, x_3, x_4, x_5, x_6, x_7\}$ 

一次二分之后 $\{x_0, x_2, x_4, x_6\},\{x_1, x_3,x_5, x_7 \}$ 

两次二分之后 $\{x_0,x_4\} \{x_2, x_6\},\{x_1, x_3\},\{x_5, x_7 \}$ 

三次二分之后 $\{x_0\}\{x_4\}\{x_2\}\{x_6\}\{x_1\}\{x_5\}\{x_3\}\{x_7 \}$ 

有啥规律呢？其实就是原来的那个序列，每个数用二进制表示，然后把二进制翻转对称一下，就是最终那个位置的下标。比如 $x_1$ 是 001，翻转是 100，也就是 4，而且最后那个位置确实是 4。我们称这个变换为蝴蝶变换。根据它的定义，我们可以在 $O(n\log n)$ 的时间内求出每个数蝴蝶变换的结果：

???+ note "蝴蝶变换实现（$O(n\log n)$）"
    ```cpp
    /*
     * 进行 FFT 和 IFFT 前的反置变换
     * 位置 i 和 i 的二进制反转后的位置互换
     *len 必须为 2 的幂
     */
    void change(Complex y[], int len) {
      int i, j, k;
      for (int i = 1, j = len / 2; i < len - 1; i++) {
        if (i < j) swap(y[i], y[j]);
        // 交换互为小标反转的元素，i<j 保证交换一次
        // i 做正常的 + 1，j 做反转类型的 + 1，始终保持 i 和 j 是反转的
        k = len / 2;
        while (j >= k) {
          j = j - k;
          k = k / 2;
        }
        if (j < k) j += k;
      }
    }
    ```

实际上，蝴蝶变换还可以 $O(n)$ 从小到大递推实现：（以下都为二进制数）

想一想我们要翻转 `11001` ，len 为 `100000` 时，我们是怎么实现的。

1.  考虑前面的 `1100` ，显然我们已经处理过它的翻转，它的翻转是 `0011` ，但前面求出 `(0)1100` 的翻转是 `0011(0)` ，因此去掉末尾的 `0` ，就可以得到 `0011` ；
2.  考虑最后一位，如果是 `1` ，它就要翻转到数的最高位，即翻转数加上 `10000` ，即 `len/2` ，如果是 `0` 则不用考虑。

???+ note "蝴蝶变换实现（$O(n)$ 递推版）"
    ```cpp
    //同样需要保证 len 是 2 的幂
    //记 rev[i] 为 i 翻转后的值
    void change(Complex y[], int len) {
      for (int i = 0; i < len; ++i) {
        rev[i] = rev[i >> 1] >> 1;
        if (i & 1) {  //如果最后一位是 1，则翻转成 len/2
          rev[i] |= len >> 1;
        }
      }
      for (int i = 0; i < len; ++i) {
        if (i < rev[i]) {  //保证每对数只翻转一次
          swap(y[i], y[rev[i]]);
        }
      }
      return;
    }
    ```

## 快速傅里叶逆变换

这一步 IDFT（傅里叶反变换）的作用我说的已经很清楚啦，就是把上一步获得的目标多项式的点值形式转换成系数形式。但是似乎并不简单呢……但是，我们把单位复根代入多项式之后，就是下面这个样子（矩阵表示方程组）

$$
\begin{bmatrix}y_0 \\ y_1 \\ y_2 \\ y_3 \\ \vdots \\ y_{n-1} \end{bmatrix}
=
\begin{bmatrix}1 & 1 & 1 & 1 & \cdots & 1 \\
1 & \omega_n^1 & \omega_n^2 & \omega_n^3 & \cdots & \omega_n^{n-1} \\
1 & \omega_n^2 & \omega_n^4 & \omega_n^6 & \cdots & \omega_n^{2(n-1)} \\
1 & \omega_n^3 & \omega_n^6 & \omega_n^9 & \cdots & \omega_n^{3(n-1)} \\
\vdots & \vdots & \vdots & \vdots & \ddots & \vdots \\
1 & \omega_n^{n-1} & \omega_n^{2(n-1)} & \omega_n^{3(n-1)} & \cdots & \omega_n^{(n-1)^2} \end{bmatrix}
\begin{bmatrix} a_0 \\ a_1 \\ a_2 \\ a_3 \\ \vdots \\ a_{n-1} \end{bmatrix}
$$

而且现在我们已经得到最左边的结果了，中间的 $x$ 值在目标多项式的点值表示中也是一一对应的，所以，根据矩阵的基础知识，我们只要在式子两边左乘中间那个大矩阵的逆矩阵就行了。由于这个矩阵的元素非常特殊，他的逆矩阵也有特殊的性质，就是每一项取倒数，再除以 $n$ ，就能得到他的逆矩阵。

如何改变我们的操作才能使计算的结果为原来的倒数呢？根据单位复根的性质并结合欧拉公式，可以得到

$$
\frac{1}{\omega_k}=\omega_k^{-1}=e^{-\frac{2\pi i}{k}}=\cos\left(\frac{2\pi i}{k}\right)+i\cdot \sin\left(-\frac{2\pi i}{k}\right)
$$

因此我们可以尝试着把 $π$ 取成 - 3.14159…，这样我们的计算结果就会变成原来的倒数，而其它的操作过程与 DFT 是完全相同的。我们可以定义一个函数，在里面加一个参数 $1$ 或者是 $-1$ ，然后把它乘到 $π$ 的身上。传入 $1$ 就是 DFT，传入 $-1$ 就是 IDFT。

### 对 IDFT 操作的证明

由于上述矩阵的逆矩阵并未给出严格的推理过程，因此这里提供另一种对 IDFT 操作的证明。考虑原本的多项式是 $f(x)=a_0+a_1x+a_2x^2+\cdots+a_{n-1}x^{n-1}=\sum_{i=0}^{n-1}a_ix^i$ 。而 IDFT 就是把你的点值表示还原为系数表示。

考虑 **构造法** 。我们已知 $y_i=f\left( \omega_n^i \right),i\in\{0,1,\cdots,n-1\}$ ，求 $\{a_0,a_1,\cdots,a_{n-1}\}$ 。构造多项式如下

$$
A(x)=\sum_{i=0}^{n-1}y_ix^i
$$

相当于把 $\{y_0,y_1,y_2,\cdots,y_{n-1}\}$ 当做多项式 $A$ 的系数表示法。设 $b_i=\omega_n^{-i}$ ，则多项式 $A$ 在 $x=b_0,b_1,\cdots,b_{n-1}$ 处的点值表示法为 $\left\{ A(b_0),A(b_1),\cdots,A(b_{n-1}) \right\}$ 。

对 $A(x)$ 的定义式做一下变换，可以将 $A(b_k)$ 表示为

$$
\begin{split}
A(b_k)&=\sum_{i=0}^{n-1}f(\omega_n^i)\omega_n^{-ik}=\sum_{i=0}^{n-1}\omega_n^{-ik}\sum_{j=0}^{n-1}a_j(\omega_n^i)^{j}\\
&=\sum_{i=0}^{n-1}\sum_{j=0}^{n-1}a_j\omega_n^{i(j-k)}=\sum_{j=0}^{n-1}a_j\sum_{i=0}^{n-1}\left(\omega_n^{j-k}\right)^i\\
\end{split}
$$

记 $S\left(\omega_n^a\right)=\sum_{i=0}^{n-1}\left(\omega_n^a\right)^i$ 。

当 $a=0$ 时， $S\left(\omega_n^a\right)=n$ 。

当 $a\neq 0$ 时，我们错位相减一下

$$
\begin{split}
S\left(\omega_n^a\right)&=\sum_{i=0}^{n-1}\left(\omega_n^a\right)^i\\
\omega_n^a S\left(\omega_n^a\right)&=\sum_{i=1}^{n}\left(\omega_n^a\right)^i\\
S\left(\omega_n^a\right)&=\frac{\left(\omega_n^a\right)^n-\left(\omega_n^a\right)^0}{\omega_n^a-1}=0\\
\end{split}
$$

也就是说

$$
S\left(\omega_n^a\right)=
\left\{\begin{split}
n,a=0\\
0,a\neq 0
\end{split}\right.
$$

那么代回原式

$$
A(b_k)=\sum_{j=0}^{n-1}a_jS\left(\omega_n^{j-k}\right)=a_k\cdot n
$$

也就是说给定点 $b_i=\omega_n^{-i}$ ，则 $A$ 的点值表示法为

$$
\begin{split}
&\left\{ (b_0,A(b_0)),(b_1,A(b_1)),\cdots,(b_{n-1},A(b_{n-1})) \right\}\\
=&\left\{ (b_0,a_0\cdot n),(b_1,a_1\cdot n),\cdots,(b_{n-1},a_{n-1}\cdot n) \right\}
\end{split}
$$

综上所述，我们取单位根为其倒数，对 $\{y_0,y_1,y_2,\cdots,y_{n-1}\}$ 跑一遍 FFT，然后除以 $n$ 即可得到 $f(x)$ 的系数序列，这就是 IDFT 操作的过程。

所以我们 FFT 函数可以集 DFT 和 IDFT 于一身。代码实现如下：

???+ note "非递归版 FFT"
    ```cpp
    /*
     * 做 FFT
     *len 必须是 2^k 形式
     *on == 1 时是 DFT，on == -1 时是 IDFT
     */
    void fft(Complex y[], int len, int on) {
      change(y, len);
      for (int h = 2; h <= len; h <<= 1) {                  // 模拟合并过程
        Complex wn(cos(2 * PI / h), sin(on * 2 * PI / h));  // 计算当前单位复根
        for (int j = 0; j < len; j += h) {
          Complex w(1, 0);  // 计算当前单位复根
          for (int k = j; k < j + h / 2; k++) {
            Complex u = y[k];
            Complex t = w * y[k + h / 2];
            y[k] = u + t;  // 这就是吧两部分分治的结果加起来
            y[k + h / 2] = u - t;
            // 后半个 “step” 中的ω一定和 “前半个” 中的成相反数
            //“红圈”上的点转一整圈“转回来”，转半圈正好转成相反数
            // 一个数相反数的平方与这个数自身的平方相等
            w = w * wn;
          }
        }
      }
      if (on == -1) {
        for (int i = 0; i < len; i++) {
          y[i].x /= len;
        }
      }
    }
    ```

??? "FFT 模板（ [HDU 1402](http://acm.hdu.edu.cn/showproblem.php?pid=1402) ）"
    ```cpp
    #include <cmath>
    #include <cstdio>
    #include <cstring>
    #include <iostream>
    
    const double PI = acos(-1.0);
    struct Complex {
      double x, y;
      Complex(double _x = 0.0, double _y = 0.0) {
        x = _x;
        y = _y;
      }
      Complex operator-(const Complex &b) const {
        return Complex(x - b.x, y - b.y);
      }
      Complex operator+(const Complex &b) const {
        return Complex(x + b.x, y + b.y);
      }
      Complex operator*(const Complex &b) const {
        return Complex(x * b.x - y * b.y, x * b.y + y * b.x);
      }
    };
    /*
     * 进行 FFT 和 IFFT 前的反置变换
     * 位置 i 和 i 的二进制反转后的位置互换
     *len 必须为 2 的幂
     */
    void change(Complex y[], int len) {
      int i, j, k;
      for (int i = 1, j = len / 2; i < len - 1; i++) {
        if (i < j) swap(y[i], y[j]);
        // 交换互为小标反转的元素，i<j 保证交换一次
        // i 做正常的 + 1，j 做反转类型的 + 1，始终保持 i 和 j 是反转的
        k = len / 2;
        while (j >= k) {
          j = j - k;
          k = k / 2;
        }
        if (j < k) j += k;
      }
    }
    /*
     * 做 FFT
     *len 必须是 2^k 形式
     *on == 1 时是 DFT，on == -1 时是 IDFT
     */
    void fft(Complex y[], int len, int on) {
      change(y, len);
      for (int h = 2; h <= len; h <<= 1) {
        Complex wn(cos(2 * PI / h), sin(on * 2 * PI / h));
        for (int j = 0; j < len; j += h) {
          Complex w(1, 0);
          for (int k = j; k < j + h / 2; k++) {
            Complex u = y[k];
            Complex t = w * y[k + h / 2];
            y[k] = u + t;
            y[k + h / 2] = u - t;
            w = w * wn;
          }
        }
      }
      if (on == -1) {
        for (int i = 0; i < len; i++) {
          y[i].x /= len;
        }
      }
    }
    
    const int MAXN = 200020;
    Complex x1[MAXN], x2[MAXN];
    char str1[MAXN / 2], str2[MAXN / 2];
    int sum[MAXN];
    
    int main() {
      while (scanf("%s%s", str1, str2) == 2) {
        int len1 = strlen(str1);
        int len2 = strlen(str2);
        int len = 1;
        while (len < len1 * 2 || len < len2 * 2) len <<= 1;
        for (int i = 0; i < len1; i++) x1[i] = Complex(str1[len1 - 1 - i] - '0', 0);
        for (int i = len1; i < len; i++) x1[i] = Complex(0, 0);
        for (int i = 0; i < len2; i++) x2[i] = Complex(str2[len2 - 1 - i] - '0', 0);
        for (int i = len2; i < len; i++) x2[i] = Complex(0, 0);
        fft(x1, len, 1);
        fft(x2, len, 1);
        for (int i = 0; i < len; i++) x1[i] = x1[i] * x2[i];
        fft(x1, len, -1);
        for (int i = 0; i < len; i++) sum[i] = int(x1[i].x + 0.5);
        for (int i = 0; i < len; i++) {
          sum[i + 1] += sum[i] / 10;
          sum[i] %= 10;
        }
        len = len1 + len2 - 1;
        while (sum[len] == 0 && len > 0) len--;
        for (int i = len; i >= 0; i--) printf("%c", sum[i] + '0');
        printf("\n");
      }
      return 0;
    }
    ```

## 快速数论变换

若要计算的多项式系数是别的具有特殊意义的整数，那么 FFT 全部用浮点数运算，从时间上比整数运算慢，且只能用 long double 类型。

可否应用数论变化从而避开浮点运算，快速求解？参见 [快速数论变换](/math/poly/ntt) 。

## 参考文献

1.   [桃酱的算法笔记](https://zhuanlan.zhihu.com/p/41867199) .
