author: hydingsy, hyp1231, ranwen, 383494

前置知识：[数论分块](./sqrt-decomposition.md)、[狄利克雷卷积](./dirichlet.md#dirichlet-卷积)

莫比乌斯反演是数论中的重要内容．对于一些函数 $f(n)$，如果很难直接求出它的值，而容易求出其倍数和或约数和 $g(n)$，那么可以通过莫比乌斯反演简化运算，求得 $f(n)$ 的值．

## 莫比乌斯函数

莫比乌斯函数（Möbius 函数）定义为

$$
\mu(n)=
\begin{cases}
1,&n=1,\\
0,&n\text{ is divisible by a square }>1,\\
(-1)^k,&n\text{ is the product of }k\text{ distinct primes}.\\
\end{cases}
$$

具体地，假设正整数 $n$ 有素因数分解 $n=\prod_{i=1}^kp_i^{e_i}$，其中，$p_i$ 是素数，$e_i$ 是正整数．那么，三种情形分别对应：

1.  $\mu(1) = 1$；
2.  当存在 $i$ 使得 $e_i > 1$，即存在任何素因数出现超过一次时，$\mu(n)=0$；
3.  否则，对于所有 $i$ 都有 $e_i = 1$，即任何素因数都只出现一次时，$\mu(n)=(-1)^k$，其中，$k$ 就是互异素因子的个数．

### 性质

根据定义容易验证，莫比乌斯函数 $\mu(n)$ 是积性函数，但不是完全积性函数．除此之外，最为重要的性质是下述恒等式：

???+ note "性质"
    对于正整数 $n$，有
    
    $$
    \sum_{d\mid n}\mu(d) = [n = 1] =
    \begin{cases}
    1,&n=1,\\
    0,&n\neq 1.\\
    \end{cases}
    $$
    
    其中 $[\cdot]$ 是 Iverson 括号．

??? note "证明"
    令 $n=\prod_{i=1}^kp_i^{e_i}$，设 $n' = \prod_{i=1}^kp_i$．根据 [二项式定理](../combinatorics/combination.md#二项式定理)，有
    
    $$
    \sum_{d\mid n}\mu(d) = \sum_{d\mid n'}\mu(d) = \sum_{i=0}^k\binom{k}{i}(-1)^i = (1 + (-1))^k = [k = 0] = [n = 1].
    $$

利用 Dirichlet 卷积，该表达式可以写作 $\varepsilon = 1 * \mu$．也就是说，莫比乌斯函数是常值函数 $1$ 的 Dirichlet 逆．

这一性质有一个很常见的应用：

$$
[i\perp j] = [\gcd(i,j) = 1] = \sum_{d\mid\gcd(i,j)} \mu(d) = \sum_{d}[d\mid i][d\mid j]\mu(d).
$$

它将互素的条件转化为关于莫比乌斯函数的求和式，方便进一步推导．

### 求法

如果需要对单个 $n$ 计算莫比乌斯函数 $\mu(n)$ 的值，可以利用它的 [质因数分解](./pollard-rho.md)．例如，在 $n$ 不太大时，可以在 $O(\sqrt{n})$ 时间内求出 $\mu(n)$ 的值．

???+ example "参考实现"
    === "C++"
        ```cpp
        --8<-- "docs/math/code/mobius/mobius-func-1.cpp:core"
        ```
    
    === "Python"
        ```python
        --8<-- "docs/math/code/mobius/mobius-func-1.py:core"
        ```

如果需要对前 $n$ 个正整数预处理出 $\mu(n)$ 的值，可以利用它是积性函数，通过 [线性筛](./sieve.md#筛法求莫比乌斯函数) 在 $O(n)$ 时间内计算．

???+ example "参考实现"
    === "C++"
        ```cpp
        --8<-- "docs/math/code/mobius/mobius-func-2.cpp:core"
        ```
    
    === "Python"
        ```python
        --8<-- "docs/math/code/mobius/mobius-func-2.py:core"
        ```

## 莫比乌斯反演

莫比乌斯函数最重要的应用就是莫比乌斯反演．

???+ note "莫比乌斯反演"
    设 $f(n),g(n)$ 是两个数论函数．那么，有
    
    $$
    f(n) = \sum_{d\mid n}g(d) \iff g(n) = \sum_{d\mid n}\mu\left(\dfrac{n}{d}\right)f(d).
    $$

??? note "证明一"
    直接验证，有：
    
    $$
    \begin{aligned}
    \sum_{d\mid n}\mu\left(\dfrac{n}{d}\right)f(d)
    &= \sum_{d\mid n}\mu\left(\dfrac{n}{d}\right)\sum_{k\mid d}g(k)\\
    &= \sum_{k\mid n}g(k)\sum_d[k\mid d\mid n]\mu\left(\dfrac{n}{d}\right)\\
    &= \sum_{k\mid n}g(k)\sum_{d\mid n}\left[\frac{n}{d}\mid\frac{n}{k}\right]\mu\left(\dfrac{n}{d}\right)\\
    &= \sum_{k\mid n}g(k)\left[\frac{n}{k} = 1\right] \\
    &= g(n).
    \end{aligned}
    $$
    
    式子变形的关键在于交换求和次序，并注意到 $k\mid d\mid n$ 就等价于 $\dfrac{n}{d}\mid\dfrac{n}{k}$．倒数第二个等号相当于对 $\dfrac{n}{k}$ 的因子 $\dfrac{n}{d}$ 处的莫比乌斯函数求和，所以就等于 $\left[\dfrac{n}{k} = 1\right]$．这一表达式仅在 $n=k$ 处不是 $0$，最后就会得到 $g(n)$．

??? note "证明二"
    利用 Dirichlet 卷积，命题等价于
    
    $$
    f = 1 * g \iff g = \mu * f.
    $$
    
    利用 $1 * \mu = \varepsilon$，在左式的等号两侧同时对 $\mu$ 做卷积，就得到
    
    $$
    f * \mu = (1 * g) * \mu = (1 * \mu) * g = \varepsilon * g = g.
    $$

在涉及各种整除关系的数论函数求和中，莫比乌斯反演是有力的变形工具．

???+ example "例子"
    1.  [欧拉函数](./euler-totient.md) $\varphi(n)$ 满足关系式 $n = \sum_{d\mid n}\varphi(d)$，亦即 $\mathrm{id}=1*\varphi$．对它进行反演，就得到 $\varphi = \mu * \mathrm{id}$，亦即
    
        $$
        \varphi(n) = \sum_{d\mid n}d\mu\left(\dfrac{n}{d}\right).
        $$
    2.  除数函数 $\sigma_k(n) = \sum_{d\mid n}d^k$，亦即 $\sigma_k = 1 * \mathrm{id}_k$．对它进行反演，就得到 $\mathrm{id}_k = \mu * \sigma_k$，亦即
    
        $$
        n^k = \sum_{d\mid n}\mu\left(\dfrac{n}{d}\right)\sigma_k(d).
        $$
    3.  互异素因子数目函数 $\omega(n)=\sum_{d\mid n}[d\in\mathbf P]$，亦即 $\omega = 1* \mathbf{1}_{\mathbf P}$，其中 $\mathbf{1}_{\mathbf P}$ 是素数集 $\mathbf P$ 的指示函数．对它进行反演，就得到 $\mathbf{1}_{\mathbf P} = \mu * \omega$，亦即
    
        $$
        [n\in\mathbf P] = \sum_{d\mid n}\mu\left(\dfrac{n}{d}\right)\omega(d).
        $$
    4.  考察满足 $\log n = \sum_{d\mid n}\Lambda(d)$ 的数论函数 $\Lambda(n)$．它就是对数函数的莫比乌斯反演，也称为 von Mangoldt 函数：
    
        $$
        \Lambda(n) = \sum_{d\mid n}\mu\left(\dfrac{n}{d}\right)\log d = 
        \begin{cases}
        \log p, & n = p^e,~p\in\mathbf P,~e\in\mathbf N_+, \\
        0, &\text{otherwise}.
        \end{cases}
        $$

??? note "附：$\Lambda(n)$ 表达式的证明"
    对于素数幂 $n=p^e~(e\in\mathbf N_+)$，有
    
    $$
    \Lambda(n) = \sum_{i=0}^e\mu(p^{e-i})\log p^i = \log p^{e} - \log p^{e-1} = \log p.
    $$
    
    对于 $n=1$，显然有 $\Lambda(n)=\log 1=0$．对于其他合数 $n$，有
    
    $$
    \Lambda(n) = \sum_{d\mid n}\mu(d)(\log n-\log d) = \left(\sum_{d\mid n}\mu(d)\right)\log n-\sum_{d\mid n}\mu(d)\log d.
    $$
    
    根据莫比乌斯函数的性质，$\log n$ 一项的系数为 $[n=1]=0$．对于后面的一项，可以进一步将 $d$ 分解为素因数之积．对于任何素数 $p\mid n$，考察 $\log p$ 的系数，都有：
    
    $$
    -\sum_{p\mid d\mid n}\mu(d) = \sum_{(d/p)\mid(n/p)}\mu\left(\dfrac{d}{p}\right) = \left[\dfrac{n}{p}=1\right]=0.
    $$
    
    由此，对于不止一个素因子的合数 $n$，都有 $\Lambda(n)=0$．

### 拓展形式

除了上述基本形式外，莫比乌斯反演还有一些常见的拓展形式．首先，可以考虑它的倍数和形式．

???+ note "拓展一"
    设 $f(n),g(n)$ 是两个数论函数．那么，有
    
    $$
    f(n) = \sum_{n\mid d}g(d) \iff g(n) = \sum_{n\mid d}\mu\left(\dfrac{d}{n}\right)f(d).
    $$

??? note "证明"
    直接验证，有：
    
    $$
    \begin{aligned}
    \sum_{n\mid d}\mu\left(\dfrac{d}{n}\right)f(d)
    &= \sum_{n\mid d}\mu\left(\dfrac{d}{n}\right)\sum_{d\mid k}g(k)\\
    &= \sum_{n\mid k}g(k)\sum_{d}[n\mid d\mid k]\mu\left(\dfrac{d}{n}\right)\\
    &= \sum_{n\mid k}g(k)\sum_{n\mid d}\left[\dfrac{d}{n}\mid\dfrac{k}{n}\right]\mu\left(\dfrac{d}{n}\right)\\
    &= \sum_{n\mid k}g(k)\left[\dfrac{k}{n}=1\right]\\
    &= g(n).
    \end{aligned}
    $$
    
    这和基本形式的推导完全对偶．

其次，莫比乌斯反演并不仅限于加法，它实际上对于任何 [Abel 群](../algebra/basic.md#群) 中的运算都成立．例如，它有如下的乘法形式：

???+ note "拓展二"
    设 $f(n),g(n)$ 是两个数论函数．那么，有
    
    $$
    f(n) = \prod_{d\mid n}g(d) \iff g(n) = \prod_{d\mid n}f(d)^{\mu(n/d)}.
    $$

??? note "证明"
    直接验证，有：
    
    $$
    \begin{aligned}
    \prod_{d\mid n}f(d)^{\mu(n/d)}
    &= \prod_{d\mid n}\left(\prod_{k\mid d}g(k)\right)^{\mu(n/d)}\\
    &= \prod_{k\mid n}g(k)\uparrow\left(\sum_d[k\mid d\mid n]\mu\left(\dfrac{n}{d}\right)\right)\\
    &= \prod_{k\mid n}g(k)\uparrow\left(\sum_{d\mid n}\left[\frac{n}{d}\mid\frac{n}{k}\right]\mu\left(\dfrac{n}{d}\right)\right)\\
    &= \prod_{k\mid n}g(k)\uparrow\left[\frac{n}{k} = 1\right] \\
    &= g(n).
    \end{aligned}
    $$
    
    其中，$a\uparrow b = a^b$ 是 Knuth 箭头．对比基本形式的证明可以发现，唯一的区别就是加法换成了乘法，且乘法换成了取幂．

从 Dirichlet 卷积的角度看，莫比乌斯反演只是利用了「莫比乌斯函数是常值函数的 Dirichlet 逆」这一点．容易想象，类似莫比乌斯反演的关系对于一般的 [Dirichlet 逆](./dirichlet.md#dirichlet-卷积) 同样成立．

???+ note "拓展三"
    设 $f(n),g(n),\alpha(n)$ 都是数论函数，且 $\alpha^{-1}(n)$ 是 $\alpha(n)$ 的 Dirichlet 逆，即
    
    $$
    [n=1] = \sum_{d\mid n}\alpha\left(\dfrac{n}{d}\right)\alpha^{-1}(d).
    $$
    
    那么，有
    
    $$
    f(n) = \sum_{d\mid n}\alpha\left(\dfrac{n}{d}\right)g(d) \iff g(n) = \sum_{d\mid n}\alpha^{-1}\left(\dfrac{n}{d}\right)f(d).
    $$

??? note "证明"
    直接验证，有：
    
    $$
    \begin{aligned}
    \sum_{d\mid n}\alpha^{-1}\left(\dfrac{n}{d}\right)f(d)
    &= \sum_{d\mid n}\alpha^{-1}\left(\dfrac{n}{d}\right)\sum_{k\mid d}\alpha\left(\dfrac{d}{k}\right)g(k)\\
    &= \sum_{k\mid n}g(k)\sum_d[k\mid d\mid n]\alpha\left(\dfrac{d}{k}\right)\alpha^{-1}\left(\dfrac{n}{d}\right)\\
    &= \sum_{k\mid n}g(k)\sum_{d\mid n}\left[\frac{n}{d}\mid\frac{n}{k}\right]\alpha\left(\dfrac{d}{k}\right)\alpha^{-1}\left(\dfrac{n/k}{d/k}\right)\\
    &= \sum_{k\mid n}g(k)\left[\frac{n}{k} = 1\right] \\
    &= g(n).
    \end{aligned}
    $$
    
    和基本形式的证明相比较，只需要将倒数第二个等号替换成 Dirichlet 逆的定义式．

???+ note "推论"
    设 $f(n),g(n)$ 是数论函数，且 $t(n)$ 是完全积性函数．那么，有
    
    $$
    f(n) = \sum_{d\mid n}t\left(\dfrac{n}{d}\right)g(d) \iff g(n) = \sum_{d\mid n}\mu\left(\dfrac{n}{d}\right)t\left(\dfrac{n}{d}\right)f(d).
    $$

??? note "证明"
    由 Dirichlet 卷积的 [性质](./dirichlet.md#性质) 可知，对于完全积性函数 $t(n)$，它的 Dirichlet 逆就是 $\mu(n)t(n)$．

最后，莫比乌斯反演还可以推广到 $[1,+\infty)$ 上的复值函数，而不仅仅局限于数论函数．基本形式的莫比乌斯反演可以看作是复值函数在所有非整数点处均取零值的特殊情形．

???+ note "拓展四"
    设 $F(x)$ 和 $G(x)$ 都是 $[1,+\infty)$ 上的复值函数．那么，有
    
    $$
    F(x) = \sum_{n = 1}^{\lfloor x\rfloor}G\left(\dfrac{x}{n}\right) \iff G(x) = \sum_{n = 1}^{\lfloor x\rfloor}\mu(n)F\left(\dfrac{x}{n}\right).
    $$

??? note "证明"
    不妨对 $F$ 和 $G$ 补充定义，设当 $x < 1$ 时，恒有 $F(x)=G(x)=0$．那么，命题就等价于：
    
    $$
    F(x) = \sum_n G\left(\dfrac{x}{n}\right) \iff G(x) = \sum_n \mu(n)F\left(\dfrac{x}{n}\right).
    $$
    
    这些求和式都是对 $n\in\mathbf N_+$ 求和．
    
    直接验证，有：
    
    $$
    \begin{aligned}
    \sum_n \mu(n)F\left(\dfrac{x}{n}\right)
    &= \sum_n\mu(n)\sum_d G\left(\dfrac{x/n}{d}\right)\\
    &= \sum_k G\left(\dfrac{x}{k}\right)\sum_{n\mid k}\mu(n)\\
    &= \sum_k G\left(\dfrac{x}{k}\right)[k=1]\\
    &= G(x).
    \end{aligned}
    $$
    
    其中，为得到第二个等号，需要令 $k = nd$．

???+ note "推论"
    设 $f(n),g(n)$ 是数论函数．那么，有
    
    $$
    f(n) = \sum_{k=1}^ng\left(\left\lfloor\dfrac{n}{k}\right\rfloor\right) \iff g(n)=\sum_{k=1}^n\mu(k)f\left(\left\lfloor\dfrac{n}{k}\right\rfloor\right).
    $$

??? note "证明"
    只需要取 $F(x)=f(\lfloor x\rfloor)$ 和 $G(x)=g(\lfloor x\rfloor)$ 即可．

这些拓展形式之间可以互相组合，进而得到更为复杂的反演关系．

### Dirichlet 前缀和

前置知识：[前缀和与差分](../../basic/prefix-sum.md)

考虑基本形式的莫比乌斯反演关系：

$$
f(n) = \sum_{d\mid n}g(d) \iff g(n) = \sum_{d\mid n}\mu\left(\dfrac{n}{d}\right)f(d).
$$

左侧等式中，$f(n)$ 的值是 $n$ 的所有因数处 $g(n)$ 的值之和．如果将 $a\mid b$ 理解为 $a$ 排在 $b$ 之前，那么 $f(n)$ 就可以理解为某种意义下 $g(n)$ 的前缀和．因此，在国内竞赛圈，由 $\{g(k)\}_{k=1}^n$ 求出 $\{f(k)\}_{k=1}^n$ 的过程也称为 **Dirichlet 前缀和**，相应的逆过程则称为 Dirichlet 差分．这些方法大多出现在需要预处理某个数论函数在前 $N$ 个点处取值的情形．

接下来，讨论 Dirichlet 前缀和的计算．如果将每一个素数都看作一个维度，这就是一种高维前缀和．回忆高维前缀和的 [逐维前缀和算法](../../basic/prefix-sum.md#逐维前缀和)：逐个遍历所有的维度，并将每个位置的值都累加到该位置在该维度上的后继位置．对于数论函数，这相当于说，从小到大遍历所有素数 $p$，并将 $n$ 处的函数值累加到 $np$ 处．这和 [Eratosthenes 筛法](./sieve.md#埃拉托斯特尼筛法) 的遍历顺序是一致的．因此，这一算法可以在 $O(n\log\log n)$ 时间内计算出长度为 $n$ 的数列的 Dirichlet 前缀和．类似地，利用逐维差分就可以在相同时间复杂度内求出数列的 Dirichlet 差分．

???+ example "参考实现"
    === "Dirichlet 前缀和"
        ```cpp
        --8<-- "docs/math/code/mobius/mobius-func-3.cpp:presum"
        ```
    
    === "Dirichlet 差分"
        ```cpp
        --8<-- "docs/math/code/mobius/mobius-func-3.cpp:diff"
        ```

这一计算方法可以推广到倍数和（拓展一）、乘积形式（拓展二）、利用完全积性函数代替常值函数（拓展三的推论）等拓展形式中．

## 例题

本节通过例题展示莫比乌斯反演的应用方法以及一些常见变形技巧．首先，通过一道例题熟悉处理求和式中最大公因数条件的基本技巧．

???+ example "[Luogu P2522 \[HAOI 2011\] Problem b](https://www.luogu.com.cn/problem/P2522)"
    $T$ 组数据．对每组数据，求值：
    
    $$
    \sum_{i=x}^{n}\sum_{j=y}^{m}[\gcd(i,j)=k].
    $$
    
    数据范围：$1\le T,x,y,n,m,k\le 5\times 10^4$．

??? note "解答"
    根据容斥原理，原式可以分成 $4$ 块来处理，且每一块的式子都具有形式
    
    $$
    f(n,m,k)=\sum_{i=1}^{n}\sum_{j=1}^{m}[\gcd(i,j)=k].
    $$
    
    对于这类式子，接下来是一段标准的推导流程：提取公因数，应用莫比乌斯函数性质，交换求和次序．
    
    首先，由于 $i,j$ 都只能取 $k$ 的倍数，可以先将这个因子提出来——这相当于代入 $i=ki'$ 和 $j=kj'$，就得到：
    
    $$
    f(n,m,k)=\sum_{i=1}^{\lfloor n/k\rfloor}\sum_{j=1}^{\lfloor m/k\rfloor}[\gcd(i,j)=1].
    $$
    
    再利用莫比乌斯函数的性质可知：
    
    $$
    [\gcd(i,j)=1] = \sum_{d\mid\gcd(i,j)}\mu(d) = \sum_d[d\mid i][d\mid j]\mu(d).
    $$
    
    将它代入表达式，并交换求和次序，就得到：
    
    $$
    f(n,m,k)=\sum_d\mu(d)\left(\sum_{i=1}^{\lfloor n/k\rfloor}[d\mid i]\right)\left(\sum_{j=1}^{\lfloor m/k\rfloor}[d\mid j]\right).
    $$
    
    这样一段操作的好处是，固定 $d$ 时，求和式中关于 $i$ 和 $j$ 的项相互分离，可以分别求和．接下来，因为
    
    $$
    \sum_{i=1}^{\lfloor n/k\rfloor}[d\mid i] = \left\lfloor\dfrac{\lfloor n/k\rfloor}{d}\right\rfloor,~\sum_{j=1}^{\lfloor m/k\rfloor}[d\mid j]=\left\lfloor\dfrac{\lfloor m/k\rfloor}{d}\right\rfloor,
    $$
    
    所以，有
    
    $$
    f(n,m,k)=\sum_d\mu(d)\left\lfloor\dfrac{\lfloor n/k\rfloor}{d}\right\rfloor\left\lfloor\dfrac{\lfloor m/k\rfloor}{d}\right\rfloor.
    $$
    
    用线性筛预处理完 $\mu(d)$，并预处理其前缀和后，就可以通过数论分块求解．总的时间复杂度为 $O(N + T\sqrt{N})$，其中，$N$ 为 $n,m$ 的上界，$T$ 为数据组数．

??? note "参考代码"
    ```cpp
    --8<-- "docs/math/code/mobius/mobius_1.cpp"
    ```

接下来的两道例题展示了枚举公因数的处理方法，并利用 [筛法](./sieve.md#一般的积性函数) 计算一般积性函数的值．

???+ example "[SPOJ LCMSUM](https://www.spoj.com/problems/LCMSUM/)"
    $T$ 组数据．对每组数据，求值：
    
    $$
    \sum_{i=1}^n \operatorname{lcm}(i,n).
    $$
    
    数据范围：$1\le T\le 3\times 10^5,~1\le n\le 10^6$．

??? note "解答一"
    题目提供的是最小公倍数，但往往最大公因数更容易处理．所以，首先做变形：
    
    $$
    f(n)=\sum_{i=1}^n \operatorname{lcm}(i,n) = \sum_{i=1}^n \frac{i\cdot n}{\gcd(i,n)}.
    $$
    
    将 $n$ 提出，并枚举最大公因数 $k$：
    
    $$
    f(n)=n\sum_{k\mid n}\sum_{i=1}^n\dfrac{i}{k}[\gcd(i,n)=k].
    $$
    
    对于内层的求和式，这是最常见的含有最大公因数的情形，重复标准的处理流程，就有：
    
    $$
    \begin{aligned}
    f(n) &= n\sum_{k\mid n}\sum_{i=1}^{n/k}i\left[\gcd\left(i,\dfrac{n}{k}\right)=1\right]\\
    &= n\sum_{k\mid n}\sum_{i=1}^{n/k}i\sum_d\mu(d)[d\mid i]\left[d\mid \dfrac{n}{k}\right]\\
    &= n\sum_{k\mid n}\sum_d\mu(d)\left[d\mid \dfrac{n}{k}\right]\left(\sum_{i=1}^{n/k}i[d\mid i]\right).
    \end{aligned}
    $$
    
    再次地，关于 $i$ 的求和式与其他部分分离，可以单独处理．最后的求和式实际上是一个等差数列求和：（取 $i=di'$）
    
    $$
    \sum_{i=1}^{n/k}i[d\mid i] = d\frac{1}{2}\left(\dfrac{n}{kd}+1\right)\dfrac{n}{kd}=:dG\left(\dfrac{n}{kd}\right).
    $$
    
    由此，就得到如下表达式：
    
    $$
    f(n) = n\sum_{k\mid n}\sum_d\mu(d)\left[d\mid \dfrac{n}{k}\right]dG\left(\dfrac{n}{kd}\right).
    $$
    
    在枚举公因数之后，这样形式的二重求和式很常见．对于它，同样有固定的处理方法：将乘积设为新变量 $\ell=kd$，然后再次交换求和次序．因为 $d\mid(n/k)$ 就相当于 $d\mid\ell\mid n$，所以，原式变形为：
    
    $$
    f(n) = n\sum_{\ell\mid n}G\left(\dfrac{n}{\ell}\right)\sum_{d\mid\ell}\mu(d)d.
    $$
    
    设 $F(\ell)=\sum_{d\mid\ell}\mu(d)d$，则原式具有形式：
    
    $$
    f(n) = n\sum_{\ell\mid n}G\left(\dfrac{n}{\ell}\right)F(\ell).
    $$
    
    因为 $\mu(d)d$ 是积性函数，所以它和常值函数 $1$ 的卷积 $F(n)$ 也是积性函数．尽管上述表达式中，求和式呈现 Dirichlet 卷积的形式，但是 $G(n)$ 并非积性函数，所以这一求和式的整体并非积性函数．但是，$G(n)$ 是多项式，所以它其实是若干完全积性函数的线性组合．所以，有
    
    $$
    f(n) = \dfrac{1}{2}n\left(\sum_{\ell}\left(\dfrac{n}{\ell}\right)^2F(\ell) + \sum_{\ell}\dfrac{n}{\ell}F(\ell)\right).
    $$
    
    这两项（不包含系数）都是积性函数，可以直接通过线性筛预处理（或者也可以线性筛出内层函数后，用 Dirichlet 前缀和在 $O(N\log\log N)$ 时间内预处理）．具体地，设
    
    $$
    H_s(n) = \sum_{\ell}\left(\dfrac{n}{\ell}\right)^sF(\ell),~s=1,2.
    $$
    
    要推导它们的表达式，只需要确定它们在素数幂处的取值即可．为此，对于素数 $p$ 和正指数 $e$，有
    
    $$
    \begin{aligned}
    F(p^e) &= \mu(1) + \mu(p)p + \sum_{j=2}^e\mu(p^j)p^j = 1-p,\\
    H_s(p^e) &= (p^e)^{s}F(1) + \sum_{j=1}^e(p^{e-j})^sF(p^j) = p^{es} + (1-p)\dfrac{1-p^{es}}{1-p^s},~s=1,2.
    \end{aligned}
    $$
    
    特别地，$H_1(p^e)\equiv 1$ 是常值函数，而
    
    $$
    H_2(p^e) = p^{2e} + (1-p)\dfrac{1-p^{2e}}{1-p^2} = H_2(p^{e-1}) + p^{2e} - p^{2e-1}.
    $$
    
    这就很容易通过线性筛求解．在线性筛预处理出 $H_2(n)$ 后，单次询问可以通过表达式 $f(n)=(n/2)(H_2(n)+1)$ 在 $O(1)$ 时间内求解．总的时间复杂度为 $O(N+T)$，其中，$N$ 为 $n$ 的上界，$T$ 为数据组数．
    
    参考实现中，利用本题表达式的特殊性，对线性筛部分做了进一步推导，这并非必须的．仅利用素数幂处的取值，仍然可以在 $O(N)$ 时间内完成预处理．这些推导详见解答二．

??? note "解答二"
    就本题而言，有着更为灵活的处理方法．从解答一可以看出
    
    $$
    f(n) = n\sum_{k\mid n}\sum_{i=1}^{n/k}i\left[\gcd\left(i,\dfrac{n}{k}\right)=1\right] = n\sum_{k\mid n}F\left(\dfrac{n}{k}\right).
    $$
    
    如果在这一步不继续做莫比乌斯反演，而是观察后面的求和式实际上是不超过 $d=n/k$ 且与之互素的整数之和．对于 $d>1$，因为与 $d$ 互素的整数成对出现，即 $i$ 和 $d-i$ 必定同时与 $d$ 互素，所以，有
    
    $$
    F(d)=\sum_{i=1}^{n'}i[i\perp d] = \sum_{i=1}^{d}(d-i)[i\perp d] = \dfrac{1}{2}d\sum_{i=1}^{d}[i\perp d] = \dfrac{1}{2}d\varphi(d).
    $$
    
    对于 $d=1$，则有
    
    $$
    F(d)=1=\dfrac{1}{2}+\dfrac{1}{2}d\varphi(d).
    $$
    
    进而，原式可以表示为
    
    $$
    f(n) = \dfrac{1}{2}n\left(\sum_{d\mid n}d\varphi(d) + 1\right).
    $$
    
    由于 $G(n)=\sum_{d\mid n}d\varphi(d)$ 是积性函数 $n\varphi(n)$ 与常值函数 $1$ 的 Dirichlet 卷积，所以它也是积性函数，可以通过线性筛预处理．为此，只需要确定它在素数幂处的取值．对于素数 $p$ 和正指数 $e$，有
    
    $$
    G(p^e) = 1 + \sum_{i=1}^ep^e(p^e-1) = G(p^{e-1}) + p^{2e} - p^{2e-1}.
    $$
    
    可以看出，这一表达式和解答一推导的结果是一致的．这一方法的总时间复杂度仍然是 $O(N+T)$．
    
    最后，利用本题积性函数的表达式，可以进一步优化线性筛的计算过程．对于素数 $p$，有
    
    $$
    G(p) = 1 - p + p^2.
    $$
    
    线性筛的关键在于对于一般的 $n$，需要求出 $G(pn)$ 的取值．这进一步分为两种情形．当 $p\perp n$ 时，因为 $G$ 是积性函数，所以
    
    $$
    G(pn) = G(p)G(n).
    $$
    
    否则，当 $p\mid n$ 时，设 $n=p^em$ 且 $p\perp m$，就有
    
    $$
    \begin{aligned}
    G(pn) &= G(p^{e+1})G(m)\\
    &= G(p^e)G(m) + (p^{2e+2} - p^{2e+1})G(m)\\
    &= G(n) + (p^{2e+2} - p^{2e+1})G(m).
    \end{aligned}
    $$
    
    直接验证可知，这一表达式对于 $p\perp n$ 的情形也成立．因此，就有
    
    $$
    G(n) - G\left(\dfrac{n}{p}\right) = (p^{2e}-p^{2e-1})G(m).
    $$
    
    代入上式，就得到
    
    $$
    G(pn) = G(n) + p^2\left(G(n) - G\left(\dfrac{n}{p}\right)\right).
    $$
    
    这简化了线性筛部分的计算．当然，这一推导并非必需，对于没有特殊性质的积性函数，直接利用 $G(pn)=G(p^{e+1})G(m)$ 就可以完成线性筛的计算．

??? note "参考代码"
    ```cpp
    --8<-- "docs/math/code/mobius/mobius_2.cpp"
    ```

???+ example "[BZOJ 2154 \[国家集训队\] Crash 的数字表格](https://hydro.ac/p/bzoj-P2154)"
    求值：
    
    $$
    \sum_{i=1}^n\sum_{j=1}^m\operatorname{lcm}(i,j)\mod{20101009}.
    $$
    
    数据范围：$1\le n,m\le 10^7$．

??? note "解答"
    推导过程中忽略模数．设
    
    $$
    f(n,m) = \sum_{i=1}^n\sum_{j=1}^m\operatorname{lcm}(i,j).
    $$
    
    依然是将最小公倍数转换为最大公因数，枚举公因数，并应用标准的处理流程，就得到
    
    $$
    \begin{aligned}
    f(n,m)
    &= \sum_k\sum_{i=1}^n\sum_{j=1}^m\dfrac{ij}{k}[\gcd(i,j)=k] \\
    &= \sum_k\sum_{i=1}^{\lfloor n/k\rfloor}\sum_{j=1}^{\lfloor m/k\rfloor} kij[\gcd(i,j)=1]\\
    &= \sum_k\sum_{i=1}^{\lfloor n/k\rfloor}\sum_{j=1}^{\lfloor m/k\rfloor} kij\sum_d\mu(d)[d\mid i][d\mid j]\\
    &= \sum_kk\sum_d\mu(d)\left(\sum_{i=1}^{\lfloor n/k\rfloor}i[d\mid i]\right)\left(\sum_{j=1}^{\lfloor m/k\rfloor}j[d\mid j]\right).
    \end{aligned}
    $$
    
    再次地，求和式对于 $i$ 和 $j$ 分离．首先计算这些内层的求和式，提取因数（即取 $i=di'$），就有
    
    $$
    \sum_{i=1}^{\lfloor n/k\rfloor}i[d\mid i] = d\sum_{i=1}^{\lfloor\lfloor n/k\rfloor/d\rfloor}i = dG\left(\left\lfloor\dfrac{\lfloor n/k\rfloor}{d}\right\rfloor\right) = dG\left(\left\lfloor\dfrac{n}{kd}\right\rfloor\right).
    $$
    
    其中，$G(n)=\dfrac{1}{2}n(n+1)$ 就是等差数列求和，最后一个等号利用了 [下取整函数](./basic.md#取整函数) 的性质．对称地，对于另一个和式可以类似计算．代回前文表达式，就有
    
    $$
    f(n,m) = \sum_k k\sum_{d}\mu(d)d^2G\left(\left\lfloor\dfrac{n}{kd}\right\rfloor\right)G\left(\left\lfloor\dfrac{m}{kd}\right\rfloor\right).
    $$
    
    和前文的情形一致，对于这类枚举公因数的式子，往往都需要枚举乘积 $\ell = kd$，再次交换求和次序：
    
    $$
    f(n,m) = \sum_{\ell}\left(\sum_{d\mid\ell}\mu(d)d\ell\right)G\left(\left\lfloor\dfrac{n}{\ell}\right\rfloor\right)G\left(\left\lfloor\dfrac{m}{\ell}\right\rfloor\right).
    $$
    
    设
    
    $$
    F(\ell) = \sum_{d\mid\ell}\mu(d)d\ell.
    $$
    
    这是积性函数 $\ell$ 与积性函数 $\sum_{d\mid\ell}\mu(d)d$ 的乘积，所以也是积性函数，可以直接用线性筛预处理，并预处理出它的前缀和．然后，就可以用数论分块计算 $f(n,m)$ 的值．总的时间复杂度为 $O(\min\{n,m\})$．

??? note "参考代码"
    ```cpp
    --8<-- "docs/math/code/mobius/mobius_3.cpp"
    ```

接下来的一道例题较为特殊，需要对乘积的约数个数函数进行转换．

???+ example "[LOJ 2185. \[SDOI2015\] 约数个数和](https://loj.ac/problem/2185)"
    $T$ 组数据．对每组数据，求值：
    
    $$
    \sum_{i=1}^n\sum_{j=1}^m\sigma_0(ij).
    $$
    
    其中，$\sigma_0(n)=\sum_{d \mid n}1$ 表示 $n$ 的约数个数．
    
    数据范围：$1\le n,m,T\le 5\times 10^4$．

??? note "解答"
    这道题目的难点在于将 $\sigma_0(ij)$ 转换为关于最大公因数的表达式．由于 $\sigma_0$ 是积性函数，可以首先考虑素数幂的情形．对于素数 $p$ 和非负指数 $e_1,e_2$，设 $i=p^{e_1},~j=p^{e_2}$，就有
    
    $$
    \sigma_0(ij) = 1 + e_1 + e_2 = \sum_{x\mid i}\sum_{y\mid j}[x\perp y].
    $$
    
    对于一般情形，不妨设 $i=\prod_p i_p$ 且 $j=\prod_p j_p$，其中，$i_p,j_p$ 分别是 $i,j$ 的素因数分解中 $p$ 的幂次．进而，有
    
    $$
    \sigma_0(ij) = \prod_p\sigma_0(i_pj_p)= \prod_p\sum_{x_p\mid i_p}\sum_{y_p\mid j_p}[x_p\perp y_p].
    $$
    
    注意到，对于 $i$ 的每个素数幂因子 $i_p$ 都枚举它的因数 $x_p$，就相当于对 $i$ 枚举它的因数 $x$ 再分解出所有素数幂因子 $x_p$；对 $j$ 同理．因此，利用乘法分配律，该式就有
    
    $$
    \sigma_0(ij) = \sum_{x\mid i}\sum_{y\mid j}\prod_p[x_p\perp y_p] = \sum_{x\mid i}\sum_{y\mid j}[x\perp y].
    $$
    
    最后一步用到了结论：$x\perp y$，当且仅当对于每个素因子 $p$，都有 $x_p\perp y_p$ 成立．
    
    得到这一表达式后，就可以应用标准的处理流程：
    
    $$
    \begin{aligned}
    \sigma_0(ij) 
    &= \sum_{x\mid i}\sum_{y\mid j}[x\perp y]\\
    &= \sum_{x\mid i}\sum_{y\mid j}\sum_d\mu(d)[d\mid x][d\mid y]\\
    &= \sum_d\mu(d)\left(\sum_{x}[d\mid x\mid i]\right)\left(\sum_{y}[d\mid y\mid j]\right)\\
    &= \sum_d\mu(d)[d\mid i][d\mid j]\sigma_0\left(\dfrac{i}{d}\right)\sigma_0\left(\dfrac{j}{d}\right).
    \end{aligned}
    $$
    
    最后一步推导的含义是：函数只有在 $d\mid i$ 且 $d\mid j$ 时才取非零值，且此时，枚举满足 $d\mid x\mid i$ 的 $x$ 就相当于枚举 $\dfrac{i}{d}$ 的因数 $\dfrac{x}{d}$，枚举满足 $d\mid y\mid j$ 的 $y$ 同理．
    
    将这一表达式再代回原式，并交换求和次序：
    
    $$
    \begin{aligned}
    f(n,m)
    &= \sum_{i=1}^n\sum_{j=1}^m\sigma_0(ij)\\
    &= \sum_{i=1}^n\sum_{j=1}^m\sum_d\mu(d)[d\mid i][d\mid j]\sigma_0\left(\dfrac{i}{d}\right)\sigma_0\left(\dfrac{j}{d}\right)\\
    &= \sum_d\mu(d)\left(\sum_{i=1}^n[d\mid i]\sigma_0\left(\dfrac{i}{d}\right)\right)\left(\sum_{j=1}^m[d\mid j]\sigma_0\left(\dfrac{j}{d}\right)\right)\\
    &= \sum_d\mu(d)\left(\sum_{i=1}^{\lfloor n/d\rfloor}\sigma_0(i)\right)\left(\sum_{j=1}^{\lfloor m/d\rfloor}\sigma_0(j)\right).
    \end{aligned}
    $$
    
    令 $G(n)=\sum_{i=1}^n\sigma_0(i)$，就有
    
    $$
    f(n,m)=\sum_{d}\mu(d)G\left(\left\lfloor\dfrac{n}{d}\right\rfloor\right)G\left(\left\lfloor\dfrac{m}{d}\right\rfloor\right).
    $$
    
    这可以通过数论分块求解．只需要预处理出 $\mu(n)$ 和 $\sigma_0(n)$ 的前缀和即可．总时间复杂度为 $O(N+T\sqrt{N})$，其中，$N$ 为 $n,m$ 的上界，$T$ 为数据组数．

??? note "参考代码"
    ```cpp
    --8<-- "docs/math/code/mobius/mobius_4.cpp"
    ```

最后一道例题展示了如何应用乘法版本的莫比乌斯反演．

???+ example "[Luogu P5221 Product](https://www.luogu.com.cn/problem/P5221)"
    求值：
    
    $$
    \prod_{i=1}^n\prod_{j=1}^n\dfrac{\operatorname{lcm}(i,j)}{\gcd(i,j)}\pmod{104857601}.
    $$
    
    数据范围：$1\le n\le 1\times 10^6$．

??? note "解答一"
    推导过程中忽略模数．设
    
    $$
    f(n) = \prod_{i=1}^n\prod_{j=1}^n\dfrac{\operatorname{lcm}(i,j)}{\gcd(i,j)}.
    $$
    
    依然是将最小公倍数转换为最大公因数：
    
    $$
    f(n) = \prod_{i=1}^n\prod_{j=1}^n\dfrac{ij}{(\gcd(i,j))^2}.
    $$
    
    注意，对这些因子的乘积是相互独立的，可以分别计算．令
    
    $$
    g(n) = \prod_{i=1}^n\prod_{j=1}^n\gcd(i,j).
    $$
    
    原式就等于：
    
    $$
    f(n) = \dfrac{(n!)^{2n}}{g(n)^2}.
    $$
    
    重点是解决 $g(n)$ 的计算问题．对它的处理流程和前文描述的相仿，但是需要换成相应的乘法版本．首先，枚举并提取公因数：
    
    $$
    \begin{aligned}
    g(n) &= \prod_k\prod_{i=1}^n\prod_{j=1}^nk\uparrow[\gcd(i,j)=k]\\
    &= \prod_k\prod_{i=1}^{\lfloor n/k\rfloor}\prod_{j=1}^{\lfloor n/k\rfloor}k\uparrow[\gcd(i,j)=1].
    \end{aligned}
    $$
    
    其中，$a\uparrow b=a^b$ 是 Knuth 箭头．然后，代入 $[\gcd(i,j)=1]=\sum_d\mu(d)[d\mid i][d\mid j]$，并将指数上的和式转换为幂的乘积式，得到：
    
    $$
    g(n) = \prod_k\prod_d\prod_{i=1}^{\lfloor n/k\rfloor}\prod_{j=1}^{\lfloor n/k\rfloor}k\uparrow(\mu(d)[d\mid i][d\mid j]).
    $$
    
    进一步地提取因数（即令 $i=di'$，$j=dj'$），并应用 [下取整函数](./basic.md#取整函数) 的性质，就得到：
    
    $$
    g(n) = \prod_k\prod_d\prod_{i=1}^{\lfloor n/(kd)\rfloor}\prod_{j=1}^{\lfloor n/(kd)\rfloor}k\uparrow\mu(d).
    $$
    
    然后分离关于 $i,j$ 的乘积，就发现乘式中并不含有 $i,j$，因此它就相当于对乘式取幂：
    
    $$
    g(n) = \prod_k\prod_d k\uparrow\left(\mu(d)\left\lfloor\dfrac{n}{kd}\right\rfloor^2\right).
    $$
    
    因为前面枚举了公因数，所以对于这个式子需要再次交换求乘积的次序．令 $\ell = kd$，有：
    
    $$
    \begin{aligned}
    g(n) &= \prod_{\ell}\prod_{d\mid\ell}\left(\dfrac{\ell}{d}\right)\uparrow\left(\mu(d)\left\lfloor\dfrac{n}{\ell}\right\rfloor^2\right)\\
    &= \prod_\ell\left(\prod_{d\mid\ell}\left(\dfrac{\ell}{d}\right)\uparrow\mu(d)\right)\uparrow\left\lfloor\dfrac{n}{\ell}\right\rfloor^2.
    \end{aligned}
    $$
    
    设
    
    $$
    F(n) = \prod_{d\mid n}\left(\dfrac{n}{d}\right)\uparrow\mu(d).
    $$
    
    容易发现这是关于 $\tilde F(n)=n$ 的乘积形式莫比乌斯反演．即使不知道它的表达式，也可以应用 [Dirichlet 差分](#dirichlet-前缀和) 方法在 $O(n\log\log n)$ 时间内预处理．当然，由于 $\tilde F(n)$ 的形式非常简单，$F(n)$ 的表达式可以直接求出：
    
    $$
    F(n) = 
    \begin{cases}
    p, & n = p^e,~p\in\mathbf P,~e\in\mathbf N_+, \\
    1, &\text{otherwise}.
    \end{cases}
    $$
    
    [von Mangoldt 函数](#莫比乌斯反演) 就是它的自然对数．得到 $F(n)$ 的取值后，直接应用乘积版本的数论分块就可以在 $O(\sqrt{n})$ 时间内求出 $g(n)$ 的取值，进而得到 $f(n)$ 的取值．总的时间复杂度为 $O(n)$．
    
    值得注意的是，涉及乘积的计算时，往往需要用到 [欧拉定理](./fermat.md)，因此指数部分取模用到的模数与题目所给的模数并不相同．

??? note "解答二"
    乘积版本推导的难点在于对乘积和幂次的处理相对陌生，因此，对于这类问题，也可以取对数后再推导．对于本题，仅考虑 $g(n)$ 的推导．将它取对数后，有：
    
    $$
    \log g(n) = \sum_{i=1}^n\sum_{j=1}^n\log\gcd(i,j).
    $$
    
    对于这类含有最大公因数的式子，直接应用标准的推导流程，就得到：
    
    $$
    \begin{aligned}
    \log g(n) 
    &= \sum_k\log k\sum_{i=1}^n\sum_{j=1}^n[\gcd(i,j)=k]\\
    &= \sum_k\log k\sum_{i=1}^{\lfloor n/k\rfloor}\sum_{j=1}^{\lfloor n/k\rfloor}[\gcd(i,j)=1]\\
    &= \sum_k\log k\sum_d\mu(d)\left(\sum_{i=1}^{\lfloor n/k\rfloor}[i\mid d]\right)\left(\sum_{j=1}^{\lfloor n/k\rfloor}[j\mid d]\right)\\
    &= \sum_k\log k\sum_d\mu(d)\left\lfloor\dfrac{n}{kd}\right\rfloor^2\\
    &= \sum_{\ell}\left(\sum_d\mu(d)\log\dfrac{\ell}{d}\right)\left\lfloor\dfrac{n}{\ell}\right\rfloor^2\\
    &= \sum_{\ell}\Lambda(\ell)\left\lfloor\dfrac{n}{\ell}\right\rfloor^2.
    \end{aligned}
    $$
    
    其中，$\Lambda(n)$ 是 [von Mangoldt 函数](#莫比乌斯反演)．将这一推导结果取幂，就得到解答一的结果．

??? note "参考代码"
    ```cpp
    --8<-- "docs/math/code/mobius/mobius_5.cpp"
    ```

## 习题

-   [Luogu P3312 \[SDOI2014\] 数表](https://www.luogu.com.cn/problem/P3312)
-   [Luogu P3700 \[CQOI2017\] 小 Q 的表格](https://www.luogu.com.cn/problem/P3700)
-   [Luogu P3704 \[SDOI2017\] 数字表格](https://www.luogu.com.cn/problem/P3704)
-   [Luogu P3768 简单的数学题](https://www.luogu.com.cn/problem/P3768)
-   [Luogu P4464 \[国家集训队\] JZPKIL](https://www.luogu.com.cn/problem/P4464)
-   [Luogu P4619 \[SDOI2018\] 旧试题](https://www.luogu.com.cn/problem/P4619)
-   [Luogu P5518 \[MtOI2019\] 幽灵乐团](https://www.luogu.com.cn/problem/P5518)
-   [Luogu P6222 简单题 加强版](https://www.luogu.com.cn/problem/P6222)
-   [Luogu P6825「EZEC-4」求和](https://www.luogu.com.cn/problem/P6825)
-   [Luogu P7486「Stoi2031」彩虹](https://www.luogu.com.cn/problem/P7486)
-   [AtCoder Grand Contest 038 C - LCMs](https://atcoder.jp/contests/agc038/tasks/agc038_c)
-   [Codeforeces 1139 D. Steps to One](https://codeforces.com/problemset/problem/1139/D)

## 参考文献

-   [Möbius function - Wikipedia](https://en.wikipedia.org/wiki/M%C3%B6bius_function)
-   [Möbius inversion formula - Wikipedia](https://en.wikipedia.org/wiki/M%C3%B6bius_inversion_formula)
-   [Von Mangoldt function - Wikipedia](https://en.wikipedia.org/wiki/Von_Mangoldt_function)
-   [algocode 算法博客](https://web.archive.org/web/20190523150159/https://algocode.net/2018/04/18/20180418-KB-Mobius-Inversion-Formula/)
