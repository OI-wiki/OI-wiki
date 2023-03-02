## 定义

Wilson 定理：对于素数 $p$ 有 $(p-1)!\equiv -1\pmod p$。

## 证明

我们知道在模奇素数 $p$ 意义下，$1,2,\dots ,p-1$ 都存在逆元且唯一，那么只需要将一个数与其逆元配对发现其乘积均为（同余意义下）$1$，但前提是这个数的逆元不等于自身。那么很显然 $(p-1)!\bmod p$ 就是逆元等于其自身的数的乘积，这两个数为 $\pm 1$。在 $p$ 为 $2$ 时单独讨论即可。

对于整数 $n$，令 $(n!)_p$ 表示所有小于等于 $n$ 但不能被 $p$ 整除的正整数的乘积，即 $(n!)_p=n!/(\lfloor n/p\rfloor !p^{\lfloor n/p\rfloor})$。

Wilson 定理指出 $(p!)_p=(p-1)!\equiv -1\pmod p$ 且可被推广至模素数 $p$ 的幂次。

### 阶乘与素数

在某些情况下，有必要考虑以某个素数 $p$ 为模的公式，包含分子和分母中的阶乘，就像在二项式系数公式中遇到的那样。

只有当阶乘同时出现在分数的分子和分母中时，这个问题才有意义。否则，后续项 $p!$ 将减少为零。但在分数中，因子 $p$ 可以抵消，结果将是非零。

因此，要计算 $n! \bmod p$，而不考虑阶乘中出现因数 $p$。写下素因子分解，去掉所有因子 $p$，并计算乘积模。

用 $(n!)_p$ 表示这个修改的因子。例如：

$$
(7!)_p \equiv 1 \cdot 2 \cdot \underbrace{1}_{3} \cdot 4 \cdot 5 \underbrace{2}_{6} \cdot 7 \equiv 2 \bmod 3
$$

通过学习如何有效地计算这种修正的阶乘，可以快速计算各种组合公式的值。

#### 计算余数的算法

计算上述去掉因子 $p$ 的阶乘模 $p$ 的余数。

$$
\begin{aligned}
(n!)_p &= 1 \cdot 2 \cdot 3 \cdot \ldots \cdot (p-2) \cdot (p-1) \cdot \underbrace{1}_{p} \cdot (p+1) \cdot (p+2) \cdot \ldots \cdot (2p-1) \cdot \underbrace{2}_{2p} \\\
&\quad \cdot (2p+1) \cdot \ldots \cdot (p^2-1) \cdot \underbrace{1}_{p^2} \cdot (p^2 +1) \cdot \ldots \cdot n \pmod{p} \\\\
&= 1 \cdot 2 \cdot 3 \cdot \ldots \cdot (p-2) \cdot (p-1) \cdot \underbrace{1}_{p} \cdot 1 \cdot 2 \cdot \ldots \cdot (p-1) \cdot \underbrace{2}_{2p} \cdot 1 \cdot 2 \\\
&\quad \cdot \ldots \cdot (p-1) \cdot \underbrace{1}_{p^2} \cdot 1 \cdot 2 \cdot \ldots \cdot (n \bmod p) \pmod{p}
\end{aligned}
$$

可以清楚地看到，除了最后一个块外，阶乘被划分为几个长度相同的块。

$$
\begin{aligned}
(n!)_p&= \underbrace{1 \cdot 2 \cdot 3 \cdot \ldots \cdot (p-2) \cdot (p-1) \cdot 1}_{1\text{st}} \cdot \underbrace{1 \cdot 2 \cdot 3 \cdot \ldots \cdot (p-2) \cdot (p-1) \cdot 2}_{2\text{nd}} \cdot \ldots \\\\
& \cdot \underbrace{1 \cdot 2 \cdot 3 \cdot \ldots \cdot (p-2) \cdot (p-1) \cdot 1}_{p\text{th}} \cdot \ldots \cdot \quad \underbrace{1 \cdot 2 \cdot \cdot \ldots \cdot (n \bmod p)}_{\text{tail}} \pmod{p}.
\end{aligned}
$$

块的主要部分 $(p-1)!\ \mathrm{mod}\ p$ 很容易计算，可以应用 Wilson 定理：

$$
(p-1)!\equiv -1\pmod p
$$

总共有 $\lfloor \frac{n}{p} \rfloor$ 个块，因此需要将 $\lfloor \frac{n}{p} \rfloor$ 写到 $-1$ 的指数上。可以注意到结果在 $-1$ 和 $1$ 之间切换，因此只需要查看指数的奇偶性，如果是奇数，则乘以 $-1$。除了使用乘法，也可以从结果中减去 $p$。

最后一个部分块的值可以在 $O(p)$ 的时间复杂度单独计算。

这只留下每个块的最后一个元素。如果隐藏已处理的元素，可以看到以下模式：

$$
(n!)_p = \underbrace{ \ldots \cdot 1 } \cdot \underbrace{ \ldots \cdot 2} \cdot \ldots \cdot \underbrace{ \ldots \cdot (p-1)} \cdot \underbrace{ \ldots \cdot 1 } \cdot \underbrace{ \ldots \cdot 1} \cdot \underbrace{ \ldots \cdot 2} \cdots
$$

这也是一个修正的阶乘，只是维数小得多。它是：

$$
\left(\left\lfloor \frac{n}{p} \right\rfloor !\right)_p
$$

因此，在计算修改的阶乘 $(n!)_p$ 中，执行了 $O(p)$ 个操作，剩下的是计算 $(\lfloor \frac{n}{p} \rfloor !)_p$，于是有了递归，递归深度为 $O(\log_p n)$，因此算法的总时间复杂度为 $O(p \log_p n)$。

如果预先计算阶乘 $0!,~ 1!,~ 2!,~ \dots,~ (p-1)!$ 模 $p$，那么时间复杂度为 $O(\log_p n)$。

#### 计算余数算法的实现

具体实现不需要递归，因为这是尾部递归的情况，因此可以使用迭代轻松实现。在下面的实现中预计算了阶乘：

$$
0!,~ 1!,~ \dots,~ (p-1)!
$$

因此有时间复杂度 $O(p + \log_p n)$。如果需要多次调用函数，则可以在函数外部进行预计算，于是计算 $(n!)_p$ 拥有 $O(\log_p n)$ 的时间复杂度。

```cpp
int factmod(int n, int p) {
  vector<int> f(p);
  f[0] = 1;
  for (int i = 1; i < p; i++) f[i] = f[i - 1] * i % p;
  int res = 1;
  while (n > 1) {
    if ((n / p) % 2) res = p - res;
    res = res * f[n % p] % p;
    n /= p;
  }
  return res;
}
```

如果空间有限，无法存储所有阶乘，也可以只存储需要的阶乘，对它们进行排序，然后计算阶乘 $0!,~ 1!,~ 2!,~ \dots,~ (p-1)!$ 而不显式存储它们。

## 阶乘中素数的个数

如果想计算二项式系数模 $p$，那么还需要考虑在 $n$ 的阶乘的素因子分解中 $p$ 出现的次数，或在计算修改因子时删除因子 $p$ 的个数。

Legengre 在 1808 年提供了一个公式，可以在 $O(\log_p n)$ 时间复杂度计算 $p$ 的个数 $v_p$。指出 $n!$ 中含有的素数 $p$ 的幂次为：

$$
v_p(n!) = \sum_{i=1}^{\infty} \left\lfloor \frac{n}{p^i} \right\rfloor
$$

证明：将 $n!$ 记为 $1\times 2\times \cdots \times p\times \cdots \times 2p\times \cdots \times \lfloor n/p\rfloor p\times \cdots \times n$ 那么其中 $p$ 的倍数有 $p\times 2p\times \cdots \times \lfloor n/p\rfloor p=p^{\lfloor n/p\rfloor }\lfloor n/p\rfloor !$ 然后在 $\lfloor n/p\rfloor !$ 中继续寻找 $p$ 的倍数即可，这是一个递归的过程。为了方便记 $\nu(n!)=\sum_{j\geq 1}\lfloor n/p^j\rfloor$。

因此得到实现：

```cpp
int multiplicity_factorial(int n, int p) {
  int count = 0;
  do {
    n /= p;
    count += n;
  } while (n);
  return count;
}
```

很容易证明，这个公式与前面的部分使用了相同的想法。删除所有不包含因子 $p$ 的元素，保留元素 $\lfloor \frac{n}{p} \rfloor$。从它们中移除因子 $p$，可以得到乘积：

$$
1 \cdot 2 \cdots \left\lfloor \frac{n}{p} \right\rfloor = \left\lfloor \frac{n}{p} \right\rfloor !
$$

然后再次得到递归。

另一种其他地方比较常见的公式，用到了 p 进制下各位数字和：

$v_p(n!)=\frac{n-S_p(n)}{p-1}$

与等比数列求和公式很相似。由于涉及各位数字和，利用数学归纳法可以轻松证明。

特别地，阶乘中 2 的幂次是：

$v_2(n!)=n-S_2(n)$

### Kummer 定理

组合数对一个数取模的结果，往往构成分形结构，例如谢尔宾斯基三角形就可以通过组合数模 2 得到。

$v_p(C_m^n)=\frac{S_p(n)+S_p(m-n)-S_p(m)}{p-1}$

如果仔细分析，p 是否整除组合数其实和上下标在 p 进制下减法是否需要借位有关。这就有了 **Kummer 定理**。

Kummer 定理：p 在组合数 $C_m^n$ 中的幂次，恰好是 p 进制下 m 减掉 n 需要借位的次数。

特别地，组合数中 2 的幂次是：

$v_2(C_m^n)=S_2(n)+S_2(m-n)-S_2(m)$

## Wilson 定理的推广

对于素数 $p$ 和正整数 $q$ 有 $(p^q!)_p\equiv \pm 1\pmod{p^q}$。

依然考虑配对一个数与其逆元，也就是考虑关于 $m$ 的同余方程 $m^2\equiv 1\pmod{p^q}$ 的根的乘积，当 $p^q=2$ 时方程仅有一根，当 $p=2$ 且 $q\geq 3$ 时有四根为 $\pm 1,2^{q-1}\pm 1$ 其他时候则有两根为 $\pm 1$。

至此我们对 Wilson 定理的推广中的 $\pm 1$ 有了详细的定义即

$(p^q!)_p\equiv \begin{cases}1&\text{if }p=2\text{ and }q\geq 3,\\-1&\text{otherwise.}\end{cases}$

下文两个推论中的 $\pm 1$，均特指这样的定义：当模数 $p^q$ 取 $8$ 及以上的 $2$ 的幂时取 $1$，其余取 $-1$。

### 推论 1

对于素数 $p$、正整数 $q$、非负整数 $n$ 和 $N_0=n\bmod{p^q}$ 有 $(n!)_p\equiv (\pm 1)^{\lfloor n/{p^q}\rfloor}(N_0!)_p\pmod{p^q}$。

??? note "证明"
    证明：令 $\displaystyle \prod '$ 表示不能被 $p$ 整除的数的乘积，有

    $$
    \begin{aligned}
    (n!)_p&=\prod_{1\leq r\leq n}'r\\
    &=\left(\prod_{i=0}^{\lfloor n/p^q \rfloor -1}\prod_{1\leq j\leq p^q}'(ip^q+j)\right)\left(\prod_{1\leq j\leq N_0}'(\lfloor n/p^q\rfloor p^q+j)\right)\\
    &\equiv ((p^q!)_p)^{\lfloor n/p^q\rfloor}(N_0!)_p\\
    &\equiv (\pm 1)^{\lfloor n/p^q\rfloor}(N_0!)_p\pmod{p^q}
    \end{aligned}
    $$

    将 $1\times 2\times 3\times \cdots \times n$ 记为 $(0\times p^q+1)\times (0\times p^q+2)\times \cdots \times (\lfloor n/p^q\rfloor p^q+N_0)$ 就得到了上述第二行。

    至此得到了

### 推论 2

对于素数 $p$ 和正整数 $q$ 和非负整数 $n$ 有

$\frac{n!}{p^{\sum_{j\geq 1}\lfloor \frac{n}{p^j}\rfloor}}\equiv (\pm 1)^{\sum_{j\geq q}\lfloor \frac{n}{p^j}\rfloor}\prod_{j\geq 0}(N_j!)_p\pmod{p^q}$

其中 $N_j=\lfloor n/p^j\rfloor \bmod{p^q}$ 而 $\pm 1$ 与上述相同。

记 $r=n-m$ 且 $n > m$ 有

$\frac{(\pm 1)^{\sum_{j\geq q}\left(\lfloor n/p^j\rfloor -\lfloor m/p^j\rfloor -\lfloor r/p^j\rfloor\right)}}{p^{\nu(n!)-\nu(m!)-\nu(r!)}}\binom{n}{m}\equiv \frac{n!/p^{\nu(n!)}}{(m!/p^{\nu(m!)})(r!/p^{\nu(r!)})}\pmod{p^q}$

右边的分母中括号内的项均在模 $p^q$ 意义下均存在逆元，可直接计算，而 $\pm 1$ 的与上述相同。

## 例题

???+ note " 例题 [HDU 2973 - YAPTCHA](https://acm.hdu.edu.cn/showproblem.php?pid=2973)"
    给定 $n$, 计算
    
    $\sum_{k=1}^n\left\lfloor\frac{(3k+6)!+1}{3k+7}-\left\lfloor\frac{(3k+6)!}{3k+7}\right\rfloor\right\rfloor$

??? note "解题思路"
    若 $3k+7$ 是质数，则
    
    $(3k+6)!\equiv-1\pmod{3k+7}$
    
    设 $(3k+6)!+1=k(3k+7)$
    
    则
    
    $\left\lfloor\frac{(3k+6)!+1}{3k+7}-\left\lfloor\frac{(3k+6)!}{3k+7}\right\rfloor\right\rfloor=\left\lfloor k-\left\lfloor k-\frac{1}{3k+7}\right\rfloor\right\rfloor=1$
    
    若 $3k+7$ 不是质数，则有 $(3k+7)\mid(3k+6)!$，即
    
    $(3k+6)!\equiv 0\pmod{3k+7}$
    
    设 $(3k+6)!=k(3k+7)$
    
    则
    
    $\left\lfloor\frac{(3k+6)!+1}{3k+7}-\left\lfloor\frac{(3k+6)!}{3k+7}\right\rfloor\right\rfloor=\left\lfloor k+\frac{1}{3k+7}-k\right\rfloor=0$
    
    因此
    
    $\sum_{k=1}^n\left\lfloor\frac{(3k+6)!+1}{3k+7}-\left\lfloor\frac{(3k+6)!}{3k+7}\right\rfloor\right\rfloor=\sum_{k=1}^n[3k+7\text{ is prime}]$

??? note "参考代码"
    ```cpp
    --8<-- "docs/math/code/wilson/wilson_1.cpp"
    ```

**本页面主要译自博文 [Вычисление факториала по модулю](http://e-maxx.ru/algo/modular_factorial) 与其英文翻译版 [Factorial modulo p](https://cp-algorithms.com/algebra/factorial-modulo.html)。其中俄文版版权协议为 Public Domain + Leave a Link；英文版版权协议为 CC-BY-SA 4.0。**
