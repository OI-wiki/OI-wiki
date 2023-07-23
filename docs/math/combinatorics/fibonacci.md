斐波那契数列（The Fibonacci sequence，[OEIS A000045](http://oeis.org/A000045)）的定义如下：

$$
F_0 = 0, F_1 = 1, F_n = F_{n-1} + F_{n-2}
$$

该数列的前几项如下：

$$
0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, \dots
$$

## 卢卡斯数列

卢卡斯数列（The Lucas sequence，[OEIS A000032](http://oeis.org/A000032)）的定义如下：

$$
L_0 = 2, L_1 = 1, L_n = L_{n-1} + L_{n-2}
$$

该数列的前几项如下：

$$
2, 1, 3, 4, 7, 11, 18, 29, 47, 76, 123, 199, \dots
$$

研究斐波那契数列，很多时候需要借助卢卡斯数列为工具。

## 斐波那契数列通项公式

第 $n$ 个斐波那契数可以在 $\Theta (n)$ 的时间内使用递推公式计算。但我们仍有更快速的方法计算。

### 解析解

解析解即公式解。我们有斐波那契数列的通项公式（Binet's Formula）：

$$
F_n = \frac{\left(\frac{1 + \sqrt{5}}{2}\right)^n - \left(\frac{1 - \sqrt{5}}{2}\right)^n}{\sqrt{5}}
$$

这个公式可以很容易地用归纳法证明，当然也可以通过生成函数的概念推导，或者解一个方程得到。

当然你可能发现，这个公式分子的第二项总是小于 $1$，并且它以指数级的速度减小。因此我们可以把这个公式写成

$$
F_n = \left[\frac{\left(\frac{1 + \sqrt{5}}{2}\right)^n}{\sqrt{5}}\right]
$$

这里的中括号表示取离它最近的整数。

这两个公式在计算的时候要求极高的精确度，因此在实践中很少用到。但是请不要忽视！结合模意义下二次剩余和逆元的概念，在 OI 中使用这个公式仍是有用的。

### 卢卡斯数列通项公式

我们有卢卡斯数列的通项公式：

$$
L_n = \left(\frac{1 + \sqrt{5}}{2}\right)^n + \left(\frac{1 - \sqrt{5}}{2}\right)^n
$$

与斐波那契数列非常相似。事实上有：

$$
\frac{L_n + F_n\sqrt{5}}{2} = \left(\frac{1 + \sqrt{5}}{2}\right)^n
$$

也就是说，$L_n$ 和 $F_n$ 恰好构成 $\left(\frac{1 + \sqrt{5}}{2}\right)^n$ 二项式展开再合并同类项后的分子系数。也就是说，Pell 方程

$$
x^2-5y^2=-4
$$

的全体解，恰好是

$$
\frac{x_n + y_n\sqrt{5}}{2} = \frac{L_n + F_n\sqrt{5}}{2}
$$

恰好是卢卡斯数列和斐波那契数列。因此有

$$
{L_n}^2-5{F_n}^2=-4
$$

### 矩阵形式

斐波那契数列的递推可以用矩阵乘法的形式表达：

$$
\begin{bmatrix}F_{n-1} & F_{n} \cr\end{bmatrix} = \begin{bmatrix}F_{n-2} & F_{n-1} \cr\end{bmatrix} \begin{bmatrix}0 & 1 \cr 1 & 1 \cr\end{bmatrix}
$$

设 $P = \begin{bmatrix}0 & 1 \cr 1 & 1 \cr\end{bmatrix}$，我们得到

$$
\begin{bmatrix}F_n & F_{n+1} \cr\end{bmatrix} = \begin{bmatrix}F_0 & F_1 \cr\end{bmatrix} P^n
$$

于是我们可以用矩阵乘法在 $\Theta(\log n)$ 的时间内计算斐波那契数列。此外，前一节讲述的公式也可通过矩阵对角化的技巧来得到。

### 快速倍增法

使用上面的方法我们可以得到以下等式：

$$
\begin{aligned}
F_{2k} &= F_k (2 F_{k+1} - F_{k}) \\
F_{2k+1} &= F_{k+1}^2 + F_{k}^2
\end{aligned}
$$

于是可以通过这样的方法快速计算两个相邻的斐波那契数（常数比矩乘小）。代码如下，返回值是一个二元组 $(F_n,F_{n+1})$。

```cpp
pair<int, int> fib(int n) {
  if (n == 0) return {0, 1};
  auto p = fib(n >> 1);
  int c = p.first * (2 * p.second - p.first);
  int d = p.first * p.first + p.second * p.second;
  if (n & 1)
    return {d, c + d};
  else
    return {c, d};
}
```

## 性质

斐波那契数列拥有许多有趣的性质，这里列举出一部分简单的性质：

1.  卡西尼性质（Cassini's identity）：$F_{n-1} F_{n+1} - F_n^2 = (-1)^n$。
2.  附加性质：$F_{n+k} = F_k F_{n+1} + F_{k-1} F_n$。
3.  取上一条性质中 $k = n$，我们得到 $F_{2n} = F_n (F_{n+1} + F_{n-1})$。
4.  由上一条性质可以归纳证明，$\forall k\in \mathbb{N},F_n|F_{nk}$。
5.  上述性质可逆，即 $\forall F_a|F_b,a|b$。
6.  GCD 性质：$(F_m, F_n) = F_{(m, n)}$。
7.  以斐波那契数列相邻两项作为输入会使欧几里德算法达到最坏复杂度（具体参见 [维基 - 拉梅](https://en.wikipedia.org/wiki/Gabriel_Lam%C3%A9)）。

### 斐波那契数列与卢卡斯数列的关系

不难发现，关于卢卡斯数列与斐波那契数列的等式，与三角函数公式具有很高的相似性。比如：

$$
\frac{L_n + F_n\sqrt{5}}{2} = \left(\frac{1 + \sqrt{5}}{2}\right)^n
$$

与

$$
\cos nx + i\sin nx = \left(\cos x + i\sin x\right)^n
$$

很像。以及

$$
{L_n}^2-5{F_n}^2=-4
$$

与

$$
\cos^2 x + \sin^2 x = 1
$$

很像。因此，卢卡斯数列与余弦函数很像，而斐波那契数列与正弦函数很像。比如，根据

$$
\left(\frac{1 + \sqrt{5}}{2}\right)^m\left(\frac{1 + \sqrt{5}}{2}\right)^n = \left(\frac{1 + \sqrt{5}}{2}\right)^{m+n}
$$

可以得到两下标之和的等式：

$$
2L_{m+n}=5F_mF_n+L_mL_n
$$

$$
2F_{m+n}=F_mL_n+L_mF_n
$$

于是推论就有二倍下标的等式：

$$
L_{2n}={L_n}^2-2{\left(-1\right)}^n
$$

$$
F_{2n}=F_nL_n
$$

这也是一种快速倍增下标的办法。同样地，也可以仿照三角函数的公式，比如奇偶性、和差化积、积化和差、半角、万能代换等等，推理出更多有关卢卡斯数列与斐波那契数列的相应等式。

## 斐波那契编码

我们可以利用斐波那契数列为正整数编码。根据 [齐肯多夫定理](https://zh.wikipedia.org/wiki/%E9%BD%8A%E8%82%AF%E5%A4%9A%E5%A4%AB%E5%AE%9A%E7%90%86)，任何自然数 $n$ 可以被唯一地表示成一些斐波那契数的和：

$$
N = F_{k_1} + F_{k_2} + \ldots + F_{k_r}
$$

并且 $k_1 \ge k_2 + 2,\ k_2 \ge k_3 + 2,\  \ldots,\  k_r \ge 2$（即不能使用两个相邻的斐波那契数）

于是我们可以用 $d_0 d_1 d_2 \dots d_s 1$ 的编码表示一个正整数，其中 $d_i=1$ 则表示 $F_{i+2}$ 被使用。编码末位我们强制给它加一个 1（这样会出现两个相邻的 1），表示这一串编码结束。举几个例子：

$$
\begin{aligned}
1 &=& 1 &=& F_2 &=& (11)_F \\
2 &=& 2 &=& F_3 &=& (011)_F \\
6 &=& 5 + 1 &=& F_5 + F_2 &=& (10011)_F \\
8 &=& 8 &=& F_6 &=& (000011)_F \\
9 &=& 8 + 1 &=& F_6 + F_2 &=& (100011)_F \\
19 &=& 13 + 5 + 1 &=& F_7 + F_5 + F_2 &=& (1001011)_F
\end{aligned}
$$

给 $n$ 编码的过程可以使用贪心算法解决：

1.  从大到小枚举斐波那契数 $F_i$，直到 $F_i\le n$。
2.  把 $n$ 减掉 $F_i$，在编码的 $i-2$ 的位置上放一个 1（编码从左到右以 0 为起点）。
3.  如果 $n$ 为正，回到步骤 1。
4.  最后在编码末位添加一个 1，表示编码的结束位置。

解码过程同理，先删掉末位的 1，对于编码为 1 的位置 $i$（编码从左到右以 0 为起点），累加一个 $F_{i+2}$ 到答案。最后的答案就是原数字。

## 模意义下周期性

考虑模 $p$ 意义下的斐波那契数列，可以容易地使用抽屉原理证明，该数列是有周期性的。考虑模意义下前 $p^2+1$ 个斐波那契数对（两个相邻数配对）：

$$
(F_1,\ F_2),\ (F_2,\ F_3),\ \ldots,\ (F_{p^2 + 1},\ F_{p^2 + 2})
$$

$p$ 的剩余系大小为 $p$，意味着在前 $p^2+1$ 个数对中必有两个相同的数对，于是这两个数对可以往后生成相同的斐波那契数列，那么他们就是周期性的。

### 皮萨诺周期

模 $m$ 意义下斐波那契数列的最小正周期被称为 [皮萨诺周期](https://en.wikipedia.org/wiki/Pisano_period)（Pisano periods,[OEIS A001175](http://oeis.org/A001175)）。

皮萨诺周期总是不超过 $6m$，且只有在满足 $m=2\times 5^k$ 的形式时才取到等号。

当需要计算第 $n$ 项斐波那契数模 $m$ 的值的时候，如果 $n$ 非常大，就需要计算斐波那契数模 $m$ 的周期。当然，只需要计算周期，不一定是最小正周期。

容易验证，斐波那契数模 $2$ 的最小正周期是 $3$，模 $5$ 的最小正周期是 $20$。

显然，如果 $a$ 与 $b$ 互素，$ab$ 的皮萨诺周期就是 $a$ 的皮萨诺周期与 $b$ 的皮萨诺周期的最小公倍数。

计算周期还需要以下结论：

结论 1：对于奇素数 $p\equiv 1,4 \pmod 5$，$p-1$ 是斐波那契数模 $p$ 的周期。即，奇素数 $p$ 的皮萨诺周期整除 $p-1$。

证明：

此时 $5^\frac{p-1}{2} \equiv 1\pmod p$。

由二项式展开：

$$
F_p=\frac{2}{2^p\sqrt{5}}\left(\dbinom{p}{1}\sqrt{5}+\dbinom{p}{3}\sqrt{5}^3+\ldots+\dbinom{p}{p}\sqrt{5}^p\right)\equiv\sqrt{5}^{p-1}\equiv 1\pmod p
$$

$$
F_{p+1}=\frac{2}{2^{p+1}\sqrt{5}}\left(\dbinom{p+1}{1}\sqrt{5}+\dbinom{p+1}{3}\sqrt{5}^3+\ldots+\dbinom{p+1}{p}\sqrt{5}^p\right)\equiv\frac{1}{2}\left(1+\sqrt{5}^{p-1}\right)\equiv 1\pmod p
$$

因为 $F_p$ 和 $F_{p+1}$ 两项都同余于 $1$，与 $F_1$ 和 $F_2$ 一致，所以 $p-1$ 是周期。

结论 2：对于奇素数 $p\equiv 2,3 \pmod 5$，$2p+2$ 是斐波那契数模 $p$ 的周期。即，奇素数 $p$ 的皮萨诺周期整除 $2p+2$。

证明：

此时 $5^\frac{p-1}{2} \equiv -1\pmod p$。

由二项式展开：

$$
F_{2p}=\frac{2}{2^{2p}\sqrt{5}}\left(\dbinom{2p}{1}\sqrt{5}+\dbinom{2p}{3}\sqrt{5}^3+\ldots+\dbinom{2p}{2p-1}\sqrt{5}^{2p-1}\right)
$$

$$
F_{2p+1}=\frac{2}{2^{2p+1}\sqrt{5}}\left(\dbinom{2p+1}{1}\sqrt{5}+\dbinom{2p+1}{3}\sqrt{5}^3+\ldots+\dbinom{2p+1}{2p+1}\sqrt{5}^{2p+1}\right)
$$

模 $p$ 之后，在 $F_{2p}$ 式中，只有 $\dbinom{2p}{p}\equiv 2 \pmod p$ 项留了下来；在 $F_{2p+1}$ 式中，有 $\dbinom{2p+1}{1}\equiv 1 \pmod p$、$\dbinom{2p+1}{p}\equiv 2 \pmod p$、$\dbinom{2p+1}{2p+1}\equiv 1 \pmod p$，三项留了下来。

$$
F_{2p}\equiv\frac{1}{2}\dbinom{2p}{p}\sqrt{5}^{p-1}\equiv -1 \pmod p
$$

$$
F_{2p+1}\equiv\frac{1}{4}\left(\dbinom{2p+1}{1}+\dbinom{2p+1}{p}\sqrt{5}^{p-1}+\dbinom{2p+1}{2p+1}\sqrt{5}^{2p}\right)\equiv\frac{1}{4}\left(1-2+5\right)\equiv 1 \pmod p
$$

于是 $F_{2p}$ 和 $F_{2p+1}$ 两项与 $F_{-2}$ 和 $F_{-1}$ 一致，所以 $2p+2$ 是周期。

结论 3：对于素数 $p$，$M$ 是斐波那契数模 $p^{k-1}$ 的周期，等价于 $Mp$ 是斐波那契数模 $p^k$ 的周期。特别地，$M$ 是模 $p^{k-1}$ 的皮萨诺周期，等价于 $Mp$ 是模 $p^k$ 的皮萨诺周期。

证明：

这里的证明需要把 $\frac{1+\sqrt{5}}{2}$ 看作一个整体。

由于：

$$
F_M=\frac{1}{\sqrt{5}}\left(\left(\frac{1+\sqrt{5}}{2}\right)^M-\left(\frac{1-\sqrt{5}}{2}\right)^M\right)\equiv 0\pmod {p^{k-1}}
$$

$$
F_{M+1}=\frac{1}{\sqrt{5}}\left(\left(\frac{1+\sqrt{5}}{2}\right)^{M+1}-\left(\frac{1-\sqrt{5}}{2}\right)^{M+1}\right)\equiv 1\pmod {p^{k-1}}
$$

因此：

$$
\left(\frac{1+\sqrt{5}}{2}\right)^M \equiv \left(\frac{1-\sqrt{5}}{2}\right)^M\pmod {p^{k-1}}
$$

$$
1\equiv\frac{1}{\sqrt{5}}\left(\frac{1+\sqrt{5}}{2}\right)^M\left(\left(\frac{1+\sqrt{5}}{2}\right)-\left(\frac{1-\sqrt{5}}{2}\right)\right)=\left(\frac{1+\sqrt{5}}{2}\right)^M\pmod {p^{k-1}}
$$

因为反方向也可以推导，所以 $M$ 是斐波那契数模 $p^{k-1}$ 的周期，等价于：

$$
\left(\frac{1+\sqrt{5}}{2}\right)^M \equiv \left(\frac{1-\sqrt{5}}{2}\right)^M\equiv 1\pmod {p^{k-1}}
$$

当 $p$ 是奇素数时，由 [升幂引理](../number-theory/lift-the-exponent.md)，有：

$$
v_p\left(a^t-1\right)=v_p\left(a-1\right)+v_p(t)
$$

当 $p=2$ 时，由 [升幂引理](../number-theory/lift-the-exponent.md)，有：

$$
v_2\left(a^t-1\right)=v_2\left(a-1\right)+v_2\left(a+1\right)+v_2(t)-1
$$

代入 $a$ 为 $\left(\frac{1+\sqrt{5}}{2}\right)$ 和 $\left(\frac{1-\sqrt{5}}{2}\right)$，$t$ 为 $M$ 和 $Mp$，上述条件也就等价于：

$$
\left(\frac{1+\sqrt{5}}{2}\right)^{Mp} \equiv \left(\frac{1-\sqrt{5}}{2}\right)^{Mp}\equiv 1\pmod {p^k}
$$

因此也等价于 $Mp$ 是斐波那契数模 $p^k$ 的周期。

因为周期等价，所以最小正周期也等价。

三个结论证完。据此可以写出代码：

```cpp
struct prime {
  unsigned long long p;
  int times;
};

struct prime pp[2048];
int pptop;

unsigned long long get_cycle_from_mod(
    unsigned long long mod)  // 这里求解的只是周期，不一定是最小正周期
{
  pptop = 0;
  srand(time(0));
  while (n != 1) {
    __int128_t factor = (__int128_t)10000000000 * 10000000000;
    min_factor(mod, &factor);  // 计算最小素因数
    struct prime temp;
    temp.p = factor;
    for (temp.times = 0; mod % factor == 0; temp.times++) {
      mod /= factor;
    }
    pp[pptop] = temp;
    pptop++;
  }
  unsigned long long m = 1;
  for (int i = 0; i < pptop; ++i) {
    int g;
    if (pp[i].p == 2) {
      g = 3;
    } else if (pp[i].p == 5) {
      g = 20;
    } else if (pp[i].p % 5 == 1 || pp[i].p % 5 == 4) {
      g = pp[i].p - 1;
    } else {
      g = (pp[i].p + 1) << 1;
    }
    m = lcm(m, g * qpow(pp[i].p, pp[i].times - 1));
  }
  return m;
}
```

## 习题

-   [SPOJ - Euclid Algorithm Revisited](http://www.spoj.com/problems/MAIN74/)
-   [SPOJ - Fibonacci Sum](http://www.spoj.com/problems/FIBOSUM/)
-   [HackerRank - Is Fibo](https://www.hackerrank.com/contests/codesprint5/challenges/is-fibo/problem)
-   [Project Euler - Even Fibonacci numbers](https://www.hackerrank.com/contests/projecteuler/challenges/euler002/problem)
-   [洛谷 P4000 斐波那契数列](https://www.luogu.com.cn/problem/P4000)

    **本页面主要译自博文 [Числа Фибоначчи](http://e-maxx.ru/algo/fibonacci_numbers) 与其英文翻译版 [Fibonacci Numbers](https://cp-algorithms.com/algebra/fibonacci-numbers.html)。其中俄文版版权协议为 Public Domain + Leave a Link；英文版版权协议为 CC-BY-SA 4.0。**
