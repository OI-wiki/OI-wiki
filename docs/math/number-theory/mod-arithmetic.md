author: 383494, buuzzing, c-forrest, cr4c1an, Emp7iness, Enter-tainer, Great-designer, HeRaNO, jifbt, Kaiser-Yang, Koishilll, ksyx, Marcythm, Qiu-Quanzhi, Saisyc, sshwy, StarryReverie, StudyingFather, Tiphereth-A, Xeonacid, xyf007

算法竞赛中，数论部分的一个重要组成部分就是 **模算术**（modular arithmetic），也就是在某一模数下进行各种整数运算。除了基础的四则运算和求幂外，还可以方便地进行取对数、开各次方、求阶乘和组合数等运算。

模算术常见于各类问题中，而不仅仅局限于数论部分。很多问题的实际答案可能非常大，超过了常见的整型变量的存储范围。此时，为了避免引入大整数运算和输出长数字，题目常常要求对答案取模后输出。这就要求熟练掌握各类模算术技巧。

## C/C++ 的整数除法和取模运算

在 C/C++ 中，整数除法和取模运算，与数学上习惯的取模和除法不一致。

对于所有标准版本的 C/C++，规定在整数除法中：

1.  当除数为 0 时，行为未定义；
2.  否则 `(a / b) * b + a % b` 的运算结果与 `a` 相等。

也就是说，取模运算的符号取决于除法如何取整；而除法如何取整，这是实现定义的（由编译器决定）。

从 [C99](https://en.cppreference.com/w/c/language/operator_arithmetic) 和 [C++11](https://en.cppreference.com/w/cpp/language/operator_arithmetic) 标准版本起，规定 **商向零取整**（舍弃小数部分）；取模的符号就与被除数相同。从此，以下运算结果保证为真：

```c
5 % 3 == 2;
5 % -3 == 2;
-5 % 3 == -2;
-5 % -3 == -2;
```

## 模整数类

模算术可以看做是对某模数下的 [同余类](./basic.md#同余类与剩余系) 进行各种运算。如果用一个结构体来表示一个同余类，并且将同余类之间的加、减、乘等运算封装为结构体的方法或运算符重载，那么模算术就可以自然地实现为一个模整数类。下面给出一个简单的例子，它支持模数 $M < 2^{30}$ 下 $32$ 位带符号整数的加法、减法、乘法以及快速幂运算：

???+ example "一个简单的模整数类"
    ```cpp
    --8<-- "docs/math/code/mod-arithmetic/mod-arithmetic.cpp:core"
    ```

这个实现有意地减少了取模运算的次数，因为取模操作通常比普通的加、减、乘或比较运算要耗时得多。代码注释中提供了等价且更为直接的实现方式。这些简单优化的主要思路是，两个 $[0,M)$ 内的整数做加减运算时，结果一定落在区间 $(-M,2M)$ 内，因此可以通过一次加减法调整回区间 $[0,M)$。该实现中的取幂运算用到了 [快速幂](../binary-exponentiation.md#模意义下取幂) 的技巧。

除了这些基础运算外，还可以在各种模数下做如下运算：

-   [除法](./linear-equation.md)
-   [阶乘](./factorial.md)
-   [组合数](./lucas.md)
-   [开平方](./quad-residue.md)
-   [取对数](./discrete-logarithm.md)
-   [开方](./residue.md)

这些运算通常在素数模数下比较容易。对于合数模数，往往需要用到对应算法的扩展版本和 [中国剩余定理](./crt.md)。这些模意义下的运算大多可以看作求解某种同余方程。对于求解同余方程的一般方法，可以参考 [同余方程](./congruence-equation.md) 页面。

## 相关算法

本节将介绍几种在模意义下优化取模、乘法和快速幂运算的方法。对于绝大多数题目来说，前文提供的简单实现已经足够高效。然而，当题目对算法常数有严格要求时，这些优化方法就可以发挥作用，通过减少不必要的计算和取模操作，进一步降低算法的时间开销。

### 快速乘

在素性测试与质因数分解中，经常会遇到模数在 `long long` 范围内的乘法取模运算。为了避免运算中的整型溢出问题，本节介绍一种可以处理模数在 `long long` 范围内，不需要使用 `__int128` 且复杂度为 $O(1)$ 的「快速乘」。本算法要求测评系统中，`long double` 至少表示为 $80$ 位扩展精度浮点数[^long-double-80bit]。

注意到：

$$
a\times b\bmod m=a\times b-\left\lfloor \dfrac{ab}m \right\rfloor\times m.
$$

利用 `unsigned long long` 的自然溢出：

$$
a\times b\bmod m=a\times b-\left\lfloor \dfrac{ab}m \right\rfloor\times m=\left(a\times b-\left\lfloor \dfrac{ab}m \right\rfloor\times m\right)\bmod 2^{64}.
$$

只要能算出商 $\left\lfloor\dfrac{ab}m\right\rfloor$，最右侧表达式中的乘法和减法运算都可以使用 `unsigned long long` 直接计算。

接下来，只需要考虑如何计算 $\left\lfloor\dfrac {ab}m\right\rfloor$。解决方案是先使用 `long double` 算出 $\dfrac am$ 再乘上 $b$。既然使用了 `long double`，就无疑会有精度误差。假设 `long double` 表示为 $80$ 位扩展精度浮点数（即符号为 $1$ 位，指数为 $15$ 位，尾数为 $64$ 位），那么 `long double` 最多能精确表示的有效位数为 $64$[^note1]。所以 $\dfrac am$ 最差从第 $65$ 位开始出错，误差范围为 $\left(-2^{-64},2^{-64}\right)$。乘上 $b$ 这个 $64$ 位带符号整数，误差范围为 $(-0.5,0.5)$。为了简化后续讨论，可以先加一个 $0.5$ 再取整，最后的误差范围是 $\{0,1\}$。

最后，代入上式计算时，需要乘以 $-m$，所以最后的误差范围是 $\{0,-m\}$。因为 $m$ 在 `long long` 范围内，所以当结果 $r\in[0,m)$ 时，直接返回 $r$，否则返回 $r+m$。当然也可以直接返回 $(r+m)\bmod m$。

代码实现如下：

```cpp
long long mul(long long a, long long b, long long m) {
  unsigned long long c =
      (unsigned long long)a * b -
      (unsigned long long)((long double)a / m * b + 0.5L) * m;
  if (c < m) return c;
  return c + m;
}
```

如今，绝大多数测评系统所配备的 C/C++ 编译器已支持 `__int128` 类型，因此也可以利用 Barrett 约减进行快速乘。之所以不直接将乘数类型提升至 `__int128` 后取模计算是因为此方法仍然可以节省一次时间可观的 `__int128` 类型取模。

### Barrett 约减

前文提到，除法和取模运算通常比其他四则运算更为耗时。为了减少取模运算的开销，有一些算法可以在不直接做取模的情况下得到相同的结果。本节要介绍的 Barrett 约减算法就是其中之一。

设 $m$ 为固定模数，假设要对不同的 $a > 0$ 多次计算 $a\bmod m$。由带余除法可知

$$
z = a\bmod m = a - \left\lfloor\dfrac{a}{m}\right\rfloor m.
$$

关键在于商数 $\left\lfloor\dfrac{a}{m}\right\rfloor$ 的计算。设 $r$ 是某个常数，就有

$$
\left\lfloor\dfrac{a}{m}\right\rfloor = \left\lfloor a\dfrac{r}{m} / r\right\rfloor \approx \left\lfloor a\left\lfloor\dfrac{r}{m}\right\rfloor/r\right\rfloor.
$$

如果选取 $r = 2^k$，那么，右式中 $\left\lfloor\dfrac{r}{m}\right\rfloor$ 可以预处理，除以 $r$ 的操作可以通过移位运算进行。所以，用右式计算商数，仅需要一次乘法和一次移位操作。再代入 $a\bmod m$ 的表达式，就得到所求余数的估计 $z'$。

现在分析这样做的误差。因为对于 $x > y > 0$ 都有 $\lfloor x\rfloor - \lfloor y\rfloor \le \lceil x - y\rceil$，所以误差

$$
\begin{aligned}
\Delta &= |z' - z| = m\left|\left\lfloor\dfrac{a}{m}\right\rfloor - \left\lfloor a\left\lfloor\dfrac{r}{m}\right\rfloor/r\right\rfloor\right|\\
&\le m\left\lceil a\left(\dfrac{r}{m} - \left\lfloor\dfrac{r}{m}\right\rfloor\right) /r\right\rceil \le m\left\lceil\dfrac{a}{r}\right\rceil.
\end{aligned}
$$

只要 $a \le r$，误差 $\Delta$ 就不超过 $m$。由于 $z' \ge z$，所以估计值 $z'$ 只能是 $z$ 或 $z + m$。只要在得到估计值后，在 $z' \ge m$ 时再减去多余的 $m$，即可保证答案正确。

通常用到 Barrett 约减时，需要计算乘积的余数 $ab\bmod m$。如果 $a,b$ 都不固定，通常需要计算出 $ab$ 后再做 Barrett 约减。如果其中一个乘数固定，比如 $b$ 固定时，可以通过

$$
ab\bmod m = ab - \left\lfloor a\left\lfloor\dfrac{bR}{m}\right\rfloor/R\right\rfloor m
$$

进行类似的估计，只要预处理出 $\left\lfloor\dfrac{bR}{m}\right\rfloor$ 的值即可。这种 $b$ 固定的情形有时也称为 Shoup 模乘。

### Montgomery 模乘

## 参考资料与注释

-   [Fast modular multiplication by orz - Codeforces](https://codeforces.com/blog/entry/96759)
-   [Barrett Reduction](https://en.wikipedia.org/wiki/Barrett_reduction)

[^long-double-80bit]: 这适用于大多数 64 位系统上的 GCC 或 Clang 编译器。

[^note1]: 参见 [Double-precision floating-point format - Wikipedia](https://en.wikipedia.org/wiki/Double-precision_floating-point_format)。
