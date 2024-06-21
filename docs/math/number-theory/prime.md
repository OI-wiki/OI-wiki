素数与合数的定义，见 [数论基础](./basic.md)。

素数计数函数：小于或等于 $x$ 的素数的个数，用 $\pi(x)$ 表示。随着 $x$ 的增大，有这样的近似结果：$\pi(x) \sim \dfrac{x}{\ln(x)}$。

## 素数判定

我们自然地会想到，如何用计算机来判断一个数是不是素数呢？

### 实现

暴力做法自然可以枚举从小到大的每个数看是否能整除

=== "C++"
    ```cpp
    bool isPrime(a) {
      if (a < 2) return 0;
      for (int i = 2; i < a; ++i)
        if (a % i == 0) return 0;
      return 1;
    }
    ```

=== "Python"
    ```python
    def isPrime(a):
        if a < 2:
            return False
        for i in range(2, a):
            if a % i == 0:
                return False
        return True
    ```

这样做是十分稳妥了，但是真的有必要每个数都去判断吗？

很容易发现这样一个事实：如果 $x$ 是 $a$ 的约数，那么 $\frac{a}{x}$ 也是 $a$ 的约数。

这个结论告诉我们，对于每一对 $(x, \frac{a}{x} )$，只需要检验其中的一个就好了。为了方便起见，我们之考察每一对里面小的那个数。不难发现，所有这些较小数就是 $[1, \sqrt{a}]$ 这个区间里的数。

由于 $1$ 肯定是约数，所以不检验它。

=== "C++"
    ```cpp
    bool isPrime(a) {
      if (a < 2) return 0;
      for (int i = 2; i * i <= a; ++i)
        if (a % i == 0) return 0;
      return 1;
    }
    ```

=== "Python"
    ```python
    def isPrime(a):
        if a < 2:
            return False
        for i in range(2, int(sqrt(a)) + 1):
            if a % i == 0:
                return False
        return True
    ```

### 素性测试

#### 定义

**素性测试**（Primality test）是一类在 **不对给定数字进行素数分解**（prime factorization）的情况下，测试其是否为素数的算法。

素性测试有两种：

1.  确定性测试：绝对确定一个数是否为素数。常见示例包括 Lucas–Lehmer 测试和椭圆曲线素性证明。
2.  概率性测试：通常比确定性测试快很多，但有可能（尽管概率很小）错误地将 [合数](../number-theory/basic.md#素数与合数) 识别为质数（尽管反之则不会）。因此，通过概率素性测试的数字被称为 **可能素数**，直到它们的素数可以被确定性地证明。而通过测试但实际上是合数的数字则被称为 **伪素数**。有许多特定类型的伪素数，最常见的是费马伪素数，它们是满足费马小定理的合数。概率性测试的常见示例包括 Miller–Rabin 测试。

接下来我们将着重介绍几个概率性素性测试：

#### Fermat 素性测试

**Fermat 素性检验** 是最简单的概率性素性检验。

我们可以根据 [费马小定理](./fermat.md#费马小定理) 得出一种检验素数的思路：

基本思想是不断地选取在 $[2, n-1]$ 中的基 $a$，并检验是否每次都有 $a^{n-1} \equiv 1 \pmod n$。

##### 实现

=== "C++"
    ```cpp
    bool millerRabin(int n) {
      if (n < 3) return n == 2;
      // test_time 为测试次数,建议设为不小于 8
      // 的整数以保证正确率,但也不宜过大,否则会影响效率
      for (int i = 1; i <= test_time; ++i) {
        int a = rand() % (n - 2) + 2;
        if (quickPow(a, n - 1, n) != 1) return 0;
      }
      return 1;
    }
    ```

=== "Python"
    ```python
    def millerRabin(n):
        if n < 3:
            return n == 2
        # test_time 为测试次数,建议设为不小于 8
        # 的整数以保证正确率,但也不宜过大,否则会影响效率
        for i in range(1, test_time + 1):
            a = random.randint(0, 32767) % (n - 2) + 2
            if quickPow(a, n - 1, n) != 1:
                return False
        return True
    ```

如果 $a^{n−1} \equiv 1 \pmod n$ 但 $n$ 不是素数，则 $n$ 被称为以 $a$ 为底的 **伪素数**。我们在实践中观察到，如果 $a^{n−1} \equiv 1 \pmod n$，那么 $n$ 通常是素数。但这里也有个反例：如果 $n = 341$ 且 $a = 2$，即使 $341 = 11 \cdot 31$ 是合数，有 $2^{340}\equiv 1 {\pmod {341}}$。事实上，$341$ 是最小的伪素数基数。

很遗憾，费马小定理的逆定理并不成立，换言之，满足了 $a^{n-1} \equiv 1 \pmod n$，$n$ 也不一定是素数。甚至有些合数 $n$ 满足对任意满足 $n\nmid a$ 的整数 $a$ 均有 $a^{n−1} \equiv 1 \pmod n$，这样的数称为 [Carmichael 数](#carmichael-数)。

##### Carmichael 函数

对正整数 $n$，定义 Carmichael 函数（卡迈克尔函数）为对任意满足 $(a,n)=1$ 的整数 $a$，使

$$
a^m\equiv 1\pmod n
$$

恒成立的最小正整数 $m$.

即：

$$
\lambda(n)=\max\{\delta_n(a):(a,n)=1\}
$$

Carmichael 函数有如下性质：

1.  （**Carmichael 定理**）对任意素数 $p$ 和任意正整数 $r$，

    $$
    \lambda\left(p^r\right)=\begin{cases}
        \frac{1}{2}\varphi\left(p^r\right), & p=2 \land r\geq 3, \\
        \varphi\left(p^r\right),            & \text{otherwise}.
    \end{cases}
    $$

    ??? note "证明"
        该定理等价于：
        
        若模 $n=p^r$ 有 [原根](./primitive-root.md)，则 $\lambda(n)=\varphi(n)$，否则 $\lambda(n)=\dfrac{1}{2}\varphi(n)$.
        
        当模 $p^r$ 有原根时，由 [原根存在定理](./primitive-root.md#原根存在定理) 可知命题成立。否则 $p=2$ 且 $r\geq 3$，我们有：
        
        $$
        \lambda\left(2^r\right)\mid 2^{r-2}
        $$
        
        又由 $5^{2^{r-3}}\equiv 1+2^{r-1}\pmod{2^{r-2}}$ 知 $\lambda\left(2^r\right)>2^{r-3}$，因此
        
        $$
        \lambda\left(p^r\right)=2^{r-2}=\frac{1}{2}\varphi\left(p^r\right)
        $$

    进而有：

    1.  对任意正整数 $n$，有 $\lambda(n)\mid \varphi(n)$

    2.  对任意正整数 $a$，$b$，有 $a\mid b\implies \lambda(a)\mid \lambda(b)$

2.  令 $n$ 的唯一分解式为 $n=\prod_{i=1}^k p_i^{r_i}$，则

    $$
    \lambda(n)=\left[\lambda\left(p_1^{r_1}\right),\lambda\left(p_2^{r_2}\right),\dots,\lambda\left(p_k^{r_k}\right)\right]
    $$

    由 [中国剩余定理](./crt.md) 和 Carmichael 定理易证。

    进而有：

    1.  对任意正整数 $a$，$b$，有 $\lambda([a,b])=[\lambda(a),\lambda(b)]$

##### Carmichael 数

对于合数 $n$，如果对于所有正整数 $a$，$a$ 和 $n$ 互素，都有同余式 $a^{n-1} \equiv 1 \pmod n$ 成立，则合数 $n$ 为 **Carmichael 数**（卡迈克尔数，[OEIS:A002997](https://oeis.org/A002997)）。

比如 $561 = 3 \times 11 \times 17$ 就是一个 Carmichael 数，同时也是最小的 Carmichael 数。

我们可以用如下方法判断合数 $n$ 是否为 Carmichael 数：

???+ note "Korselt 判别法[^korselt1899probleme]"
    合数 $n$ 是 Carmichael 数当且仅当 $n$ 无平方因子且对 $n$ 的任意质因子 $p$ 均有 $p-1 \mid n-1$.

上述判别法可简化为：

???+ note
    合数 $n$ 是 Carmichael 数当且仅当 $\lambda(n)\mid n-1$，其中 $\lambda(n)$ 为 [Carmichael 函数](#carmichael-函数)。

Carmichael 数有如下性质：

1.  Carmichael 数无平方因子且至少有 $3$ 个不同的质因子。
2.  设 $C(n)$ 为小于 $n$ 的 Carmichael 数个数，则：
    1.  （Alford, Granville, Pomerance. 1994[^alford1994infinitely]）$C(n)>n^{2/7}$

        由此可知 Carmichael 数有无限多个。

    2.  （Erdős. 1956[^erdos1956pseudoprimes]）$C(n)<n\exp\left(-c\dfrac{\ln n\ln\ln\ln n}{\ln\ln n}\right)$，其中 $c$ 为常数。

        由此可知 Carmichael 数的分布十分稀疏。实际上 $C(10^9)=646$，$C(10^{18})=1~401~644$[^pinchcarmichael].

???+ warning "注意"
    「若 $n$ 为 Carmichael 数，则 $2^n-1$ 也为 Carmichael 数」是错误的。
    
    如 $561=3 \cdot 11 \cdot 17$ 为 Carmichael 数，考虑 $2^{561}-1$。
    
    注意到 $23\cdot 89=2^{11}-1\mid 2^{561}-1$，由 Korselt 判别法知，若 $2^{561}-1$ 是 Carmichael 数，则 $22$ 和 $88$ 均为 $2^{561}-2$ 的因子。
    
    而 $v_2\left(2^{561}-2\right)=1<v_2(88)=3$，故 $88\nmid 2^{561}-2$，因此 $2^{561}-1$ 不是 Carmichael 数。

#### Miller–Rabin 素性测试

**Miller–Rabin 素性测试**（Miller–Rabin primality test）是进阶的素数判定方法。它是由 Miller 和 Rabin 二人根据费马小定理的逆定理（费马测试）优化得到的。因为和许多类似算法一样，它是使用伪素数的概率性测试，我们必须使用慢得多的确定性算法来保证素性。然而，实际上没有已知的数字通过了高级概率性测试（例如 Miller–Rabin）但实际上却是复合的。因此我们可以放心使用。

在不考虑乘法的复杂度时，对数 $n$ 进行 $k$ 轮测试的时间复杂度是 $O(k \log n)$。Miller-Rabbin 素性测试常用于对高精度数进行测试，此时时间复杂度是 $O(k \log^3n)$，利用 FFT 等技术可以优化到 [$O(k \log^2n \log \log n \log \log \log n)$](https://en.wikipedia.org/wiki/Miller%E2%80%93Rabin_primality_test#Complexity)。

##### 二次探测定理

如果 $p$ 是奇素数，则 $x^2 \equiv 1 \pmod p$ 的解为 $x \equiv 1 \pmod p$ 或者 $x \equiv p - 1 \pmod p$。

要证明该定理，只需将上面的方程移项，再使用平方差公式，得到 $(x+1)(x-1) \equiv 0 \bmod p$，即可得出上面的结论。

##### 实现

根据卡迈克尔数的性质，可知其一定不是 $p^e$。

不妨将费马小定理和二次探测定理结合起来使用：

将 $a^{n-1} \equiv 1 \pmod n$ 中的指数 $n−1$ 分解为 $n−1=u \times 2^t$，在每轮测试中对随机出来的 $a$ 先求出 $v = a^{u} \bmod n$，之后对这个值执行最多 $t$ 次平方操作，若发现非平凡平方根时即可判断出其不是素数，否则再使用 Fermat 素性测试判断。

还有一些实现上的小细节：

-   对于一轮测试，如果某一时刻 $a^{u \times 2^s} \equiv n-1 \pmod n$，则之后的平方操作全都会得到 $1$，则可以直接通过本轮测试。
-   如果找出了一个非平凡平方根 $a^{u \times 2^s} \not\equiv n-1 \pmod n$，则之后的平方操作全都会得到 $1$。可以选择直接返回 `false`，也可以放到 $t$ 次平方操作后再返回 `false`。

这样得到了较正确的 Miller Rabin：（来自 fjzzq2002）

=== "C++"
    ```cpp
    bool millerRabin(int n) {
      if (n < 3 || n % 2 == 0) return n == 2;
      int u = n - 1, t = 0;
      while (u % 2 == 0) u /= 2, ++t;
      // test_time 为测试次数，建议设为不小于 8
      // 的整数以保证正确率，但也不宜过大，否则会影响效率
      for (int i = 0; i < test_time; ++i) {
        // 0, 1, n-1 可以直接通过测试, a 取值范围 [2, n-2]
        int a = rand() % (n - 3) + 2, v = quickPow(a, u, n);
        if (v == 1) continue;
        int s;
        for (s = 0; s < t; ++s) {
          if (v == n - 1) break;  // 得到平凡平方根 n-1，通过此轮测试
          v = (long long)v * v % n;
        }
        // 如果找到了非平凡平方根，则会由于无法提前 break; 而运行到 s == t
        // 如果 Fermat 素性测试无法通过，则一直运行到 s == t 前 v 都不会等于 -1
        if (s == t) return 0;
      }
      return 1;
    }
    ```

=== "Python"
    ```python
    def millerRabin(n):
        if n < 3 or n % 2 == 0:
            return n == 2
        u, t = n - 1, 0
        while u % 2 == 0:
            u = u // 2
            t = t + 1
        # test_time 为测试次数,建议设为不小于 8
        # 的整数以保证正确率,但也不宜过大,否则会影响效率
        for i in range(test_time):
            # 0, 1, n-1 可以直接通过测试, a 取值范围 [2, n-2]
            a = random.randint(2, n - 2)
            v = pow(a, u, n)
            if v == 1:
                continue
            s = 0
            while s < t:
                if v == n - 1:
                    break
                v = v * v % n
                s = s + 1
            # 如果找到了非平凡平方根，则会由于无法提前 break; 而运行到 s == t
            # 如果 Fermat 素性测试无法通过，则一直运行到 s == t 前 v 都不会等于 -1
            if s == t:
                return False
        return True
    ```

另外，假设 [广义 Riemann 猜想](https://en.wikipedia.org/wiki/Generalized_Riemann_hypothesis)（generalized Riemann hypothesis, GRH）成立，则对数 $n$ 最多只需要测试 $[2, \min\{n-2, \lfloor 2\ln^2 n \rfloor\}]$ 中的全部整数即可 **确定** 数 $n$ 的素性，证明参见注释 7。

而在 OI 范围内，通常都是对 $[1, 2^{64})$ 范围内的数进行素性检验。对于 $[1, 2^{32})$ 范围内的数，选取 $\{2, 7, 61\}$ 三个数作为基底进行 Miller–Rabin 素性检验就可以确定素性；对于 $[1, 2^{64})$ 范围内的数，选取 $\{2, 325, 9375, 28178, 450775, 9780504, 1795265022\}$ 七个数作为基底进行 Miller–Rabin 素性检验就可以确定素性。参见注释 8。

也可以选取 $\{2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37\}$（即前 $12$ 个素数）检验 $[1, 2^{64})$ 范围内的素数。

注意如果要使用上面的数列中的数 $a$ 作为基底判断 $n$ 的素性：

-   所有的数都要取一遍，不能只选小于 $n$ 的；
-   把 $a$ 换成 $a \bmod n$；
-   如果 $a \equiv 0 \pmod n$ 或 $a \equiv \pm 1 \pmod n$，则直接通过该轮测试。

## 反素数

### 引入

顾名思义，素数就是因子只有两个的数，那么反素数，就是因子最多的数（并且因子个数相同的时候值最小），所以反素数是相对于一个集合来说的。

一种符合直觉的反素数定义是：在一个正整数集合中，因子最多并且值最小的数，就是反素数。

### 定义

如果某个正整数 $n$ 满足如下条件，则称为是 **反素数**：任何小于 $n$ 的正数的约数个数都小于 $n$ 的约数个数。

???+ warning "注意"
    注意区分 [emirp](https://en.wikipedia.org/wiki/Emirp)，它表示的是逐位反转后是不同素数的素数（如 149 和 941 均为 emirp，101 不是 emirp）。

### 过程

那么，如何来求解反素数呢？

首先，既然要求因子数，首先要做的就是素因子分解。把 $n$ 分解成 $n=p_{1}^{k_{1}}p_{2}^{k_{2}} \cdots p_{n}^{k_{n}}$ 的形式，其中 $p$ 是素数，$k$ 为他的指数。这样的话总因子个数就是 $(k_1+1) \times (k_2+1) \times (k_3+1) \cdots \times (k_n+1)$。

但是显然质因子分解的复杂度是很高的，并且前一个数的结果不能被后面利用。所以要换个方法。

我们来观察一下反素数的特点。

1.  反素数肯定是从 $2$ 开始的连续素数的幂次形式的乘积。

2.  数值小的素数的幂次大于等于数值大的素数，即 $n=p_{1}^{k_{1}}p_{2}^{k_{2}} \cdots p_{n}^{k_{n}}$ 中，有 $k_1 \geq k_2 \geq k_3 \geq \cdots \geq k_n$

解释：

1.  如果不是从 $2$ 开始的连续素数，那么如果幂次不变，把素数变成数值更小的素数，那么此时因子个数不变，但是 $n$ 的数值变小了。交换到从 $2$ 开始的连续素数的时候 $n$ 值最小。

2.  如果数值小的素数的幂次小于数值大的素数的幂，那么如果把这两个素数交换位置（幂次不变），那么所得的 $n$ 因子数量不变，但是 $n$ 的值变小。

另外还有两个问题，

1.  对于给定的 $n$，要枚举到哪一个素数呢？

    最极端的情况大不了就是 $n=p_{1}p_{2} \cdots p_{n}$，所以只要连续素数连乘到刚好小于等于 $n$ 就可以的呢。再大了，连全都一次幂，都用不了，当然就是用不到的啦！

2.  我们要枚举到多少次幂呢？

    我们考虑一个极端情况，当我们最小的素数的某个幂次已经比所给的 $n$（的最大值）大的话，那么展开成其他的形式，最大幂次一定小于这个幂次。`unsigned long long` 的最大值是 $2^{64} - 1$，所以可以枚举到 $2^{64} - 1$。

细节有了，那么我们具体如何具体实现呢？

我们可以把当前走到每一个素数前面的时候列举成一棵树的根节点，然后一层层的去找。找到什么时候停止呢？

1.  当前走到的数字已经大于我们想要的数字了

2.  当前枚举的因子已经用不到了（和 $1$ 重复了嘻嘻嘻）

3.  当前因子大于我们想要的因子了

4.  当前因子正好是我们想要的因子（此时判断是否需要更新最小 $ans$）

然后 dfs 里面不断一层一层枚举次数继续往下迭代可以。

### 常见题型

1.  求因子数一定的最小数

???+ note " 例题 [Codeforces 27E. A number with a given number of divisors](https://codeforces.com/problemset/problem/27/E)"
    求具有给定除数的最小自然数。请确保答案不超过 $10^{18}$。

??? note "解题思路"
    对于这种题，我们只要以因子数为 dfs 的返回条件基准，不断更新找到的最小值就可以了

??? note "参考代码"
    ```cpp
    --8<-- "docs/math/code/prime/prime_1.cpp"
    ```

2.  求 n 以内因子数最多的数

???+ note " 例题 [ZOJ - More Divisors](https://zoj.pintia.cn/problem-sets/91827364500/problems/91827366061)"
    大家都知道我们使用十进制记数法，即记数的基数是 $10$。历史学家说这是因为人有十个手指，也许他们是对的。然而，这通常不是很方便，十只有四个除数——$1$、$2$、$5$ 和 $10$。因此，像 $\frac{1}{3}$、$\frac{1}{4}$ 或 $\frac{1}{6}$ 这样的分数不便于用十进制表示。从这个意义上说，以 $12$、$24$ 甚至 $60$ 为底会方便得多。主要原因是这些数字的除数要大得多——分别是 $6$、$8$ 和 $12$。请回答：除数最多的不超过 $n$ 的数是多少？

??? note "解题思路"
    思路同上，只不过要改改 dfs 的返回条件。注意这样的题目的数据范围，32 位整数可能溢出。

??? note "参考代码"
    ```cpp
    --8<-- "docs/math/code/prime/prime_2.cpp"
    ```

## 参考资料与注释

1.  Rui-Juan Jing, Marc Moreno-Maza, Delaram Talaashrafi, "[Complexity Estimates for Fourier-Motzkin Elimination](https://arxiv.org/abs/1811.01510)", Journal of Functional Programming 16:2 (2006) pp 197-217.
2.  [数论部分第一节：素数与素性测试](http://www.matrix67.com/blog/archives/234)
3.  [Miller-Rabin 与 Pollard-Rho 学习笔记 - Bill Yang's Blog](https://blog.bill.moe/miller-rabin-notes/)
4.  [Primality test - Wikipedia](https://en.wikipedia.org/wiki/Primality_test)
5.  [桃子的算法笔记——反素数详解（acm/OI）](https://zhuanlan.zhihu.com/p/41759808)
6.  [The Rabin-Miller Primality Test](http://home.sandiego.edu/~dhoffoss/teaching/cryptography/10-Rabin-Miller.pdf)
7.  Bach, Eric , "[Explicit bounds for primality testing and related problems](https://doi.org/10.2307%2F2008811)", Mathematics of Computation, 55:191 (1990) pp 355–380.
8.  [Deterministic variant of the Miller-Rabin primality test](https://miller-rabin.appspot.com/#)
9.  [Fermat pseudoprime - Wikipedia](https://en.wikipedia.org/wiki/Fermat_pseudoprime)
10. [Carmichael number - Wikipedia](https://en.wikipedia.org/wiki/Carmichael_number)
11. [Carmichael function - Wikipedia](https://en.wikipedia.org/wiki/Carmichael_function)
12. [Carmichael Number -- from Wolfram MathWorld](https://mathworld.wolfram.com/CarmichaelNumber.html)
13. [Carmichael's Lambda Function | Brilliant Math & Science Wiki](https://brilliant.org/wiki/carmichaels-lambda-function/)

[^korselt1899probleme]: Korselt, A. R. (1899). "Problème chinois".*L'Intermédiaire des Mathématiciens*.**6**: 142–143.

[^alford1994infinitely]: W. R. Alford; Andrew Granville; Carl Pomerance (1994). "There are Infinitely Many Carmichael Numbers".*Annals of Mathematics*. 140 (3): 703–722.

[^erdos1956pseudoprimes]: Erdős, P. (1956). "On pseudoprimes and Carmichael numbers".*Publ. Math. Debrecen*. 4 (3–4): 201–206.

[^pinchcarmichael]: PINCH, Richard GE. The Carmichael numbers up to ${10}^{20}$.
