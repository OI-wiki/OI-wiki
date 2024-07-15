贝尔数 $B_n$ 以埃里克·坦普尔·贝尔命名，是组合数学中的一组整数数列，开首是（[OEIS A000110](https://oeis.org/A000110)）：

$$
B_0 = 1,B_1 = 1,B_2=2,B_3=5,B_4=15,B_5=52,B_6=203,\dots
$$

$B_n$ 是基数为 $n$ 的集合的划分方法的数目。集合 $S$ 的一个划分是定义为 $S$ 的两两不相交的非空子集的族，它们的并是 $S$。例如 $B_3 = 5$ 因为 3 个元素的集合 ${a, b, c}$ 有 5 种不同的划分方法：

$$
\begin{aligned}
&\{ \{a\},\{b\},\{c\}\} \\
&\{ \{a\},\{b,c\}\} \\
&\{ \{b\},\{a,c\}\} \\
&\{ \{c\},\{a,b\}\} \\
&\{ \{a,b,c\}\} \\
\end{aligned}
$$

$B_0$ 是 1 因为空集正好有 1 种划分方法。

## 递推公式

贝尔数适合递推公式：

$$
B_{n+1}=\sum_{k=0}^n\binom{n}{k}B_{k}
$$

证明：

$B_{n+1}$ 是含有 $n+1$ 个元素集合的划分个数，设 $B_n$ 的集合为 $\{b_1,b_2,b_3,\dots,b_n\}$，$B_{n+1}$ 的集合为 $\{b_1,b_2,b_3,\dots,b_n,b_{n+1}\}$，那么可以认为 $B_{n+1}$ 是有 $B_{n}$ 增添了一个 $b_{n+1}$ 而产生的，考虑元素 $b_{n+1}$。

-   假如它被单独分到一类，那么还剩下 $n$ 个元素，这种情况下划分数为 $\dbinom{n}{n}B_{n}$;

-   假如它和某 1 个元素分到一类，那么还剩下 $n-1$ 个元素，这种情况下划分数为 $\dbinom{n}{n-1}B_{n-1}$；

-   假如它和某 2 个元素分到一类，那么还剩下 $n-2$ 个元素，这种情况下划分数为 $\dbinom{n}{n-2}B_{n-2}$；

-   ……

以此类推就得到了上面的公式。

每个贝尔数都是相应的 [第二类斯特林数](./stirling.md#第二类斯特林数stirling-number) 的和。
因为第二类斯特林数是把基数为 $n$ 的集合划分为正好 $k$ 个非空集的方法数目。

$$
B_{n} = \sum_{k=0}^n{n\brace k}
$$

## 贝尔三角形

用以下方法构造一个三角矩阵（形式类似杨辉三角形）：

-   $a_{0,0} = 1$；
-   对于 $n \ge 1$，第 $n$ 行首项等于上一行的末项，即 $a_{n,0}=a_{n-1,n-1}$；
-   对于 $m,n \ge 1$，第 $n$ 行第 $m$ 项等于它左边和左上角两个数之和，即 $a_{n,m}=a_{n,m-1}+a_{n-1,m-1}$。

部分结果如下：

$$
\begin{aligned}
& 1 	\\
& 1\quad\qquad 2	\\
& 2\quad\qquad 3\quad\qquad 5	\\
& 5\quad\qquad 7\quad\qquad 10\,\,\,\qquad 15 \\
& 15\,\,\,\qquad 20\,\,\,\qquad	27\,\,\,\qquad 37\,\,\,\qquad 52	\\
& 52\,\,\,\qquad	67\,\,\,\qquad 87\,\,\,\qquad 114\qquad 151\qquad 203\\
& 203\qquad	255\qquad 322\qquad	409\qquad 523\qquad	674\qquad 877 \\	
\end{aligned}
$$

每行的首项是贝尔数。可以利用这个三角形来递推求出贝尔数。

??? note "参考实现"
    === "C++"
        ```cpp
        const int maxn = 2000 + 5;
        int bell[maxn][maxn];
        
        void f(int n) {
          bell[0][0] = 1;
          for (int i = 1; i <= n; i++) {
            bell[i][0] = bell[i - 1][i - 1];
            for (int j = 1; j <= i; j++)
              bell[i][j] = bell[i - 1][j - 1] + bell[i][j - 1];
          }
        }
        ```
    
    === "Python"
        ```python
        maxn = 2000 + 5
        bell = [[0 for i in range(maxn + 1)] for j in range(maxn + 1)]
        
        
        def f(n):
            bell[0][0] = 1
            for i in range(1, n + 1):
                bell[i][0] = bell[i - 1][i - 1]
                for j in range(1, i + 1):
                    bell[i][j] = bell[i - 1][j - 1] + bell[i][j - 1]
        ```

## 指数生成函数

考虑贝尔数的指数生成函数及其导函数：

$$
\begin{aligned}
\hat B(x) &= \sum_{n = 0}^{+\infty}\frac{B_n}{n!}x^n \\
&= 1 + \sum_{n = 0}^{+\infty}\frac{B_{n+1}}{(n + 1)!}x^{n + 1} \\
\hat B'(x) &= \sum_{n = 0}^{+\infty}\frac{B_{n+1}}{n!}x^{n}
\end{aligned}
$$

根据贝尔数的递推公式可以得到：

$$
\frac{B_{n+1}}{n!} = \sum_{k = 0}^{n}\frac{1}{(n-k)!}\frac{B_{k}}{k!}
$$

这是一个卷积的式子，因此有：

$$
\hat B'(x) = \mathrm{e}^x \hat B(x)
$$

这是一个微分方程，解得：

$$
\hat B(x) = \exp\left(\mathrm{e}^x + C\right)
$$

最后当 $x = 0$ 时 $\hat B(x) = 1$，带入后解得 $C = -1$，得到贝尔数指数生成函数的封闭形式：

$$
\hat B(x) = \exp\left(\mathrm{e}^x - 1\right)
$$

预处理出 $\mathrm{e}^x - 1$ 的前 $n$ 项后做一次 [多项式 exp](../poly/elementary-func.md#多项式对数函数--指数函数) 即可得出贝尔数前 $n$ 项，时间复杂度瓶颈在多项式 exp，可做到 $O(n \log n)$ 的时间复杂度。

## 参考文献

<https://en.wikipedia.org/wiki/Bell_number>
