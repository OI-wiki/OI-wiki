斐波那契数列（The Fibonacci sequence，[OEIS A000045](http://oeis.org/A000045)）的定义如下：

$$
F_0 = 0, F_1 = 1, F_n = F_{n-1} + F_{n-2}
$$

该数列的前几项如下：

$$
0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, ...
$$

## 性质

斐波那契数列拥有许多有趣的性质，这里列举出一部分简单的性质：

1.  卡西尼性质（Cassini's identity）： $F_{n-1} F_{n+1} - F_n^2 = (-1)^n$ 。
2.  附加性质： $F_{n+k} = F_k F_{n+1} + F_{k-1} F_n$ 。
3.  取上一条性质中 $k = n$ ，我们得到 $F_{2n} = F_n (F_{n+1} + F_{n-1})$ 。
4.  由上一条性质可以归纳证明， $\forall k\in \mathbb{N},F_n|F_{nk}$ 。
5.  上述性质可逆，即 $\forall F_a|F_b,a|b$ 。
6.  GCD 性质： $(F_m, F_n) = F_{(m, n)}$ 。
7.  以斐波那契数列相邻两项作为输入会使欧几里德算法达到最坏复杂度（具体参见[维基 - 拉梅](https://en.wikipedia.org/wiki/Gabriel_Lam%C3%A9)）。

## 斐波那契编码

我们可以利用斐波那契数列为正整数编码。根据[齐肯多夫定理](https://zh.wikipedia.org/wiki/%E9%BD%8A%E8%82%AF%E5%A4%9A%E5%A4%AB%E5%AE%9A%E7%90%86)，任何自然数 $n$ 可以被唯一地表示成一些斐波那契数的和：

$$
N = F_{k_1} + F_{k_2} + \ldots + F_{k_r}
$$

并且 $k_1 \ge k_2 + 2,\ k_2 \ge k_3 + 2,\  \ldots,\  k_r \ge 2$ （即不能使用两个相邻的斐波那契数）

于是我们可以用 $d_0 d_1 d_2 \dots d_s 1$ 的编码表示一个正整数，其中 $d_i=1$ 则表示 $F_{i+2}$ 被使用。编码末位我们强制给它加一个 1（这样会出现两个相邻的 1），表示这一串编码结束。举几个例子：

$$
\begin{eqnarray}
1 &=& 1 &=& F_2 &=& (11)_F \\
2 &=& 2 &=& F_3 &=& (011)_F \\
6 &=& 5 + 1 &=& F_5 + F_2 &=& (10011)_F \\
8 &=& 8 &=& F_6 &=& (000011)_F \\
9 &=& 8 + 1 &=& F_6 + F_2 &=& (100011)_F \\
19 &=& 13 + 5 + 1 &=& F_7 + F_5 + F_2 &=& (1001011)_F
\end{eqnarray}
$$

给 $n$ 编码的过程可以使用贪心算法解决：

1.  从大到小枚举斐波那契数 $F_i$ ，直到 $F_i\le n$ 。
2.  把 $n$ 减掉 $F_i$ ，在编码的 $i-2$ 的位置上放一个 1（编码从左到右以 0 为起点）。
3.  如果 $n$ 为正，回到步骤 1。
4.  最后在编码末位添加一个 1，表示编码的结束位置。

解码过程同理，先删掉末位的 1，对于编码为 1 的位置 $i$ （编码从左到右以 0 为起点），累加一个 $F_{i+2}$ 到答案。最后的答案就是原数字。

## 斐波那契数列通项公式

第 $n$ 个斐波那契数可以在 $\Theta (n)$ 的时间内使用递推公式计算。但我们仍有更快速的方法计算。

### 解析解

解析解即公式解。我们有斐波那契数列的通项公式（Binet's Formula）：

$$
F_n = \frac{\left(\frac{1 + \sqrt{5}}{2}\right)^n - \left(\frac{1 - \sqrt{5}}{2}\right)^n}{\sqrt{5}}
$$

这个公式可以很容易地用归纳法证明，当然也可以通过生成函数的概念推导，或者解一个方程得到。

当然你可能发现，这个公式分子的第二项总是小于 $1$ ，并且它以指数级的速度减小。因此我们可以把这个公式写成

$$
F_n = \left[\frac{\left(\frac{1 + \sqrt{5}}{2}\right)^n}{\sqrt{5}}\right]
$$

这里的中括号表示取离它最近的整数。

这两个公式在计算的时侯要求极高的精确度，因此在实践中很少用到。但是请不要忽视！结合模意义下二次剩余和逆元的概念，在 OI 中使用这个公式仍是有用的。

### 矩阵形式

斐波那契数列的递推可以用矩阵乘法的形式表达：

$$
\begin{bmatrix}F_{n-1} & F_{n} \cr\end{bmatrix} = \begin{bmatrix}F_{n-2} & F_{n-1} \cr\end{bmatrix} \cdot \begin{bmatrix}0 & 1 \cr 1 & 1 \cr\end{bmatrix}
$$

设 $P = \begin{bmatrix}0 & 1 \cr 1 & 1 \cr\end{bmatrix}$ ，我们得到

$$
\begin{bmatrix}F_n & F_{n+1} \cr\end{bmatrix} = \begin{bmatrix}F_0 & F_1 \cr\end{bmatrix} \cdot P^n
$$

于是我们可以用矩阵乘法在 $\Theta(\log_2n)$ 的时间内计算斐波那契数列。此外，前一节讲述的公式也可通过矩阵对角化的技巧来得到。

### 快速倍增法

使用上面的方法我们可以得到以下等式：

$$
\begin{array}{rll}
F_{2k} &= F_k \left( 2F_{k+1} - F_{k} \right)\\
F_{2k+1} &= F_{k+1}^2 + F_{k}^2
\end{array}
$$

于是可以通过这样的方法快速计算两个相邻的斐波那契数（常数比矩乘小）。代码如下，返回值是一个二元组 $(F_n,F_{n+1})$ 。

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

## 模意义下周期性

考虑模 $p$ 意义下的斐波那契数列，可以容易地使用抽屉原理证明，该数列是有周期性的。考虑模意义下前 $p^2+1$ 个斐波那契数对（两个相邻数配对）：

$$
(F_1,\ F_2),\ (F_2,\ F_3),\ \ldots,\ (F_{p^2 + 1},\ F_{p^2 + 2})
$$

 $p$ 的剩余系大小为 $p$ ，意味着在前 $p^2+1$ 个数对中必有两个相同的数对，于是这两个数对可以往后生成相同的斐波那契数列，那么他们就是周期性的。

事实上，我们有一个远比它要强的结论。模 $n$ 意义下斐波那契数列的周期被称为[皮萨诺周期](https://en.wikipedia.org/wiki/Pisano_period)（[OEIS A001175](http://oeis.org/A001175)），该数可以证明总是不超过 $6n$，且只有在满足 $n=2\times 5^k$ 的形式时才取到等号。

## 习题

-   [SPOJ - Euclid Algorithm Revisited](http://www.spoj.com/problems/MAIN74/)
-   [SPOJ - Fibonacci Sum](http://www.spoj.com/problems/FIBOSUM/)
-   [HackerRank - Is Fibo](https://www.hackerrank.com/contests/codesprint5/challenges/is-fibo/problem)
-   [Project Euler - Even Fibonacci numbers](https://www.hackerrank.com/contests/projecteuler/challenges/euler002/problem)

     **本页面主要译自博文[Числа Фибоначчи](http://e-maxx.ru/algo/fibonacci_numbers)与其英文翻译版[Fibonacci Numbers](https://cp-algorithms.com/algebra/fibonacci-numbers.html)。其中俄文版版权协议为 Public Domain + Leave a Link；英文版版权协议为 CC-BY-SA 4.0。** 
