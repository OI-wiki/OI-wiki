author: Ir1d, Tiphereth-A, c-forrest, Xeonacid, Enter-tainer, StudyingFather, iamtwz, ksyx, Marcythm, MegaOwIer, 383494, Alpacabla, HeRaNO, abc1763613206, alphagocc, Backl1ght, CCXXXI, drkelo, Early0v0, Great-designer, greyqz, GuanghaoYe, H-J-Granger, HHH2309, isdanni, kenlig, lazyasn, Menci, ouuan, r-value, shawlleyw, shopee-jin, shuzhouliu, Siger Young, TrisolarisHD, untitledunrevised, void-mian, Voileexperiments, weilycoder, xtlsoft, yusancky, YuzhenQin1, sun2snow, karsl-program

素数与合数的定义，见 [数论基础](./basic.md)．

素数计数函数：小于或等于 $x$ 的素数的个数，用 $\pi(x)$ 表示．随着 $x$ 的增大，有这样的近似结果：

$$
\pi(x)\sim \frac{x}{\ln x}.
$$

## 素性测试

**素性测试**（Primality test）可以用于判定所给自然数是否为素数．

素性测试主要分为两类：

1. **确定性测试**：能够确定一个数是否为素数．常见例子包括试除法、Lucas–Lehmer 测试、椭圆曲线素性证明，以及基于已证明的广义 Riemann 猜想（GRH）的确定性 Miller–Rabin 测试．

2. **概率性测试**：通常具有较高的执行效率，但存在将合数误判为素数的可能性（尽管概率很小）．因此，通过概率性素性测试的数字被称为**可能素数**，直到它们的素性得到确定性证明．通过测试但实际上为合数的数字称为**伪素数**．常见例子包括 Fermat 伪素数和强伪素数．

### 试除法

最直接的方法是枚举从小到大的每个数，检查它能否整除给定的数．

???+ example "参考实现"

    === "C++"

        ```cpp
        bool isPrime(int a) {
          if (a < 2) return false;
          for (int i = 2; i < a; ++i)
            if (a % i == 0) return false;
          return true;
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

这样做十分稳妥，但实际上没有必要检查所有小于 $a$ 的整数．

很容易发现：如果 $x$ 是 $a$ 的约数，那么 $\frac{a}{x}$ 也是 $a$ 的约数．

这个结论说明，对于每一对约数

$$
\left(x,\frac{a}{x}\right),
$$

只需要检查其中较小的一个即可．所有这些较小的约数都位于区间 $[1,\sqrt a]$ 内．

由于 $1$ 肯定是约数，因此不需要检查它．这样就可以将试除范围缩小到 $[2,\sqrt a]$．

???+ example "参考实现"

    === "C++"

        ```cpp
        bool isPrime(int a) {
          if (a < 2) return false;
          for (int i = 2; (long long)i * i <= a; ++i)
            if (a % i == 0) return false;
          return true;
        }
        ```

        这里使用 `long long` 进行乘法，避免 `i * i` 发生整数溢出．

    === "Python"

        ```python
        from math import isqrt

        def isPrime(a):
            if a < 2:
                return False
            for i in range(2, isqrt(a) + 1):
                if a % i == 0:
                    return False
            return True
        ```

试除法的时间复杂度为 $O(\sqrt a)$．

### Fermat 素性测试

**Fermat 素性测试**是最简单的概率性素性测试之一．

根据 [费马小定理](./fermat.md#费马小定理)，如果 $n$ 是素数，且 $a$ 与 $n$ 互质，那么

$$
a^{n-1}\equiv 1\pmod n.
$$

由此可以得到一种素性测试方法：

不断从区间 $[2,n-1]$ 中随机选取基底 $a$，检查是否满足

$$
a^{n-1}\equiv 1\pmod n.
$$

如果某次检查不满足同余式，就可以确定 $n$ 是合数．如果多次检查均满足，则将 $n$ 判定为可能素数．

???+ example "参考实现"

    === "C++"

        ```cpp
        bool fermat(int n, int test_time) {
          if (n < 3) return n == 2;

          for (int i = 0; i < test_time; ++i) {
            int a = rand() % (n - 2) + 2;
            if (quickPow(a, n - 1, n) != 1)
              return false;
          }
          return true;
        }
        ```

    === "Python"

        ```python
        import random

        def fermat(n, test_time=8):
            if n < 3:
                return n == 2

            for _ in range(test_time):
                a = random.randrange(2, n)
                if pow(a, n - 1, n) != 1:
                    return False
            return True
        ```

其中，`test_time` 表示测试次数．Python 实现直接使用 `pow(a, n - 1, n)` 进行模幂运算．

如果 $a^{n-1}\equiv 1\pmod n$，但 $n$ 实际上是合数，则称 $n$ 为以 $a$ 为底的 **Fermat 伪素数**．

例如，当 $n=341$、$a=2$ 时，有

$$
2^{340}\equiv 1\pmod {341},
$$

但

$$
341=11\cdot31
$$

显然是合数．

对于任何固定的基底 $a>1$，这样的反例都有无穷多个[^inf-fermat-pp]．

增加测试次数可以降低误判概率，但无法完全消除误判．更进一步，即使检查所有与 $n$ 互素的基底 $a$，依然无法保证 $n$ 是素数．

也就是说，费马小定理的逆命题不成立：即使对于所有满足 $\gcd(a,n)=1$ 的整数 $a$，都有

$$
a^{n-1}\equiv 1\pmod n,
$$

$n$ 也不一定是素数．

满足这一条件的合数称为 [Carmichael 数](./primitive-root.md#carmichael-数)．Carmichael 数也有无穷多个．

因此，需要寻找更加严格的素性测试方法．

### Miller–Rabin 素性测试

**Miller–Rabin 素性测试**（Miller–Rabin primality test）是对 Fermat 素性测试的改进．它结合了费马小定理和二次探测定理，具有较高的测试效率和可靠性．

Miller–Rabin 素性测试可以采用随机基底进行概率性测试，也可以采用指定范围内的全部基底进行确定性测试．

在概率性测试中，随机选取若干个基底进行检验．对于任意奇合数 $n>9$，单轮测试将其误判为可能素数的概率至多为 $1/4$．因此，独立随机选取多个基底可以显著降低误判概率．

在确定性测试中，可以利用已经得到证明的广义 Riemann 猜想（GRH），结合 Bach 给出的显式界，得到一个有限的基底范围．遍历该范围内的全部整数，就可以确定输入数字的素性[^deterministic-proof]．

这里所使用的 GRH 指关于所有模数、所有 Dirichlet 特征对应的 Dirichlet $L$-函数的广义 Riemann 猜想．

**复杂度分析**

在不考虑大整数乘法复杂度时，对数 $n$ 进行 $k$ 轮 Miller–Rabin 测试，需要进行 $O(k\log n)$ 次模乘运算．

对于高精度整数，每次模乘运算涉及 $O(\log n)$ 位整数．采用普通乘法时，时间复杂度为

$$
O(k\log^3 n).
$$

利用 FFT 等快速乘法技术，可以将时间复杂度优化到

$$
O(k\log^2 n\log\log n\log\log\log n).
$$

上述复杂度适用于进行 $k$ 轮测试的情况．

对于后面介绍的 GRH 确定性版本，需要测试 $O(\log^2 n)$ 个基底．因此，在不考虑乘法复杂度时，其总时间复杂度为

$$
O(\log^3 n)
$$

次模乘运算．采用普通整数乘法时，其位复杂度为 $O(\log^5 n)$．

**二次探测定理**

为了解决 Carmichael 数给 Fermat 素性测试带来的问题，Miller–Rabin 素性测试进一步利用了素数的如下性质．

???+ note "二次探测定理"

    如果 $p$ 是奇素数，则方程

    $$
    x^2\equiv 1\pmod p
    $$

    仅有两个解：

    $$
    x\equiv 1\pmod p
    $$

    或

    $$
    x\equiv p-1\pmod p.
    $$

??? note "证明"

    容易验证，$x\equiv 1\pmod p$ 和 $x\equiv p-1\pmod p$ 都满足原方程．

    将原方程变形为

    $$
    (x-1)(x+1)\equiv 0\pmod p.
    $$

    由于 $p$ 是素数，根据模素数的运算性质，必有

    $$
    p\mid x-1
    $$

    或

    $$
    p\mid x+1.
    $$

    因此，原方程只有上述两个解．

将费马小定理和二次探测定理结合起来，就得到 Miller–Rabin 素性测试．

1. 将指数 $n-1$ 分解为

   $$
   n-1=u\cdot 2^t,
   $$

   其中 $u$ 为奇数．

2. 每轮测试中随机选取一个基底 $a$，先计算

   $$
   v=a^u\bmod n,
   $$

   随后对 $v$ 连续进行最多 $t$ 次平方操作．

3. 如果在平方过程中出现非平凡平方根，即某个数 $x$ 满足

   $$
   x^2\equiv 1\pmod n,
   $$

   但

   $$
   x\not\equiv \pm1\pmod n,
   $$

   则可以确定 $n$ 是合数．

4. 如果最终没有发现非平凡平方根，再根据费马小定理相关的同余条件判断本轮测试是否通过．

还有一些实现上的细节：

- 如果某一时刻出现

  $$
  a^{u\cdot 2^s}\equiv n-1\pmod n,
  $$

  则当前轮测试可以直接通过，因为之后的平方操作会得到 $1$．

- 如果出现

  $$
  a^{u\cdot 2^s}\not\equiv n-1\pmod n
  $$

  且

  $$
  a^{u\cdot 2^{s+1}}\equiv 1\pmod n,
  $$

  那么 $a^{u\cdot 2^s}$ 就是 $1$ 的非平凡平方根，可以直接判定 $n$ 为合数．

这样得到了 Miller–Rabin 的一种常见实现（来自 fjzzq2002）：

???+ example "参考实现"

    === "C++"

        ```cpp
        bool millerRabin(int n, int test_time) {
          if (n < 3 || n % 2 == 0) return n == 2;
          if (n % 3 == 0) return n == 3;

          int u = n - 1, t = 0;
          while (u % 2 == 0) u /= 2, ++t;

          for (int i = 0; i < test_time; ++i) {
            // 随机选取 [2, n-2] 中的基底
            int a = rand() % (n - 3) + 2;
            int v = quickPow(a, u, n);

            if (v == 1) continue;

            int s;
            for (s = 0; s < t; ++s) {
              if (v == n - 1) break;
              v = (long long)v * v % n;
            }

            // 如果没有得到 n-1，则本轮测试未通过
            if (s == t) return false;
          }
          return true;
        }
        ```

    === "Python"

        ```python
        import random

        def millerRabin(n, test_time=8):
            if n < 3 or n % 2 == 0:
                return n == 2
            if n % 3 == 0:
                return n == 3

            u, t = n - 1, 0
            while u % 2 == 0:
                u //= 2
                t += 1

            for _ in range(test_time):
                # 随机选取 [2, n-2] 中的基底
                a = random.randint(2, n - 2)
                v = pow(a, u, n)

                if v == 1:
                    continue

                for s in range(t):
                    if v == n - 1:
                        break
                    v = v * v % n
                else:
                    return False

            return True
        ```

上面的实现采用随机选取基底的方式，仍然属于概率性测试．若选择固定次数的随机测试，测试通过后只能将数字判定为可能素数．

可以证明[^millerrabinproof]，对于任意奇合数 $n>9$，随机均匀选取一个基底 $a$ 时，该基底通过 Miller–Rabin 测试的概率至多为 $1/4$．

因此，独立随机选取 $k$ 个基底后，合数通过全部测试的概率不超过

$$
\boxed{\frac{1}{4^k}}.
$$

??? note "证明"

    设

    $$
    n-1=u2^t,
    $$

    其中 $u$ 为奇数且 $t$ 为正整数．

    根据 Miller–Rabin 测试的判定条件，一个基底 $a$ 能够通过测试，当且仅当

    $$
    a^u\equiv 1\pmod n
    $$

    或者

    $$
    a^{u2^i}\equiv -1\pmod n
    $$

    对某个 $0\le i<t$ 成立．

    记满足上述条件的模 $n$ 的剩余类集合为 $S$．我们需要证明

    $$
    |S|\le \frac14\varphi(n).
    $$

    其中，$\varphi(n)$ 是 [欧拉函数](./euler-totient.md)．

    证明分为三步．

    **第一步：构造集合 $S'$．**

    设 $\ell$ 是满足

    $$
    2^\ell\mid p-1
    $$

    对所有 $n$ 的素因子 $p$ 均成立的最大正整数．

    可以证明

    $$
    S\subseteq S'
    =
    \left\{
    a\bmod n:
    a^{u2^{\ell-1}}\equiv\pm1\pmod n
    \right\}.
    $$

    对于集合 $S$ 中的元素 $a$，有两种情况．

    如果

    $$
    a^u\equiv1\pmod n,
    $$

    那么显然

    $$
    a^{u2^{\ell-1}}\equiv1\pmod n,
    $$

    因此 $a\in S'$．

    如果对于某个 $0\le i<t$，有

    $$
    a^{u2^i}\equiv-1\pmod n,
    $$

    那么对于任意素因子 $p\mid n$，都有

    $$
    a^{u2^i}\equiv-1\pmod p.
    $$

    设 $\delta_p(a)$ 是 $a$ 模 $p$ 的 [阶](./primitive-root.md#阶)，则

    $$
    \delta_p(a)\mid u2^{i+1},
    $$

    但

    $$
    \delta_p(a)\nmid u2^i.
    $$

    这说明 $\delta_p(a)$ 的素因数分解中，$2$ 的指数恰为 $i+1$，因而

    $$
    2^{i+1}\mid\delta_p(a).
    $$

    根据费马小定理，

    $$
    \delta_p(a)\mid p-1.
    $$

    因此

    $$
    2^{i+1}\mid p-1.
    $$

    这一结论对 $n$ 的所有素因子 $p$ 都成立．根据 $\ell$ 的定义，有 $i+1\le\ell$．

    于是

    $$
    \begin{aligned}
    a^{u2^{\ell-1}}
    &=(a^{u2^i})^{2^{\ell-1-i}}\\
    &\equiv\pm1\pmod n.
    \end{aligned}
    $$

    因此 $a\in S'$．

    综合两种情况，得到

    $$
    S\subseteq S'.
    $$

    **第二步：计算 $|S'|$．**

    设 $n$ 的素因数分解为

    $$
    n=p_1^{e_1}p_2^{e_2}\cdots p_k^{e_k}.
    $$

    根据 [中国剩余定理](./crt.md)，条件

    $$
    a^{u2^{\ell-1}}\equiv1\pmod n
    $$

    等价于

    $$
    a^{u2^{\ell-1}}\equiv1\pmod{p_i^{e_i}}
    $$

    对所有 $p_i^{e_i}$ 均成立．

    由于模奇素数幂 $p_i^{e_i}$ 的 [原根](./primitive-root.md#原根) 总是存在，方程

    $$
    a^{u2^{\ell-1}}\equiv1\pmod{p_i^{e_i}}
    $$

    的解的数量为

    $$
    \begin{aligned}
    &\gcd(u2^{\ell-1},p_i^{e_i-1}(p_i-1))\\
    &\quad=\gcd(u2^{\ell-1},p_i-1)\\
    &\quad=2^{\ell-1}\gcd(u,p_i-1).
    \end{aligned}
    $$

    第一个等号成立，是因为 $u$ 是 $n-1$ 的因子，不可能是 $p_i$ 的倍数．第二个等号成立，是因为 $\ell$ 的选取方式．

    因此，根据中国剩余定理，方程

    $$
    a^{u2^{\ell-1}}\equiv1\pmod n
    $$

    的解的数量为

    $$
    \prod_{p\mid n}
    2^{\ell-1}\gcd(u,p-1).
    $$

    同理，条件

    $$
    a^{u2^{\ell-1}}\equiv-1\pmod n
    $$

    等价于

    $$
    a^{u2^{\ell-1}}\equiv-1\pmod{p_i^{e_i}}
    $$

    对所有 $p_i^{e_i}$ 均成立．

    对任意 $p_i^{e_i}$，条件

    $$
    a^{u2^{\ell-1}}\equiv-1\pmod{p_i^{e_i}}
    $$

    等价于

    $$
    a^{u2^{\ell-1}}\not\equiv1\pmod{p_i^{e_i}}
    $$

    且

    $$
    a^{u2^\ell}\equiv1\pmod{p_i^{e_i}}.
    $$

    类似上文，可以计算出方程

    $$
    a^{u2^\ell}\equiv1\pmod{p_i^{e_i}}
    $$

    的解的数量为

    $$
    2^\ell\gcd(u,p_i-1).
    $$

    因而方程

    $$
    a^{u2^{\ell-1}}\equiv-1\pmod{p_i^{e_i}}
    $$

    的解的数量也等于

    $$
    \begin{aligned}
    &2^\ell\gcd(u,p_i-1)\\
    &\quad-2^{\ell-1}\gcd(u,p_i-1)\\
    &=2^{\ell-1}\gcd(u,p_i-1).
    \end{aligned}
    $$

    再次应用中国剩余定理，得到方程

    $$
    a^{u2^{\ell-1}}\equiv-1\pmod n
    $$

    的解的数量为

    $$
    \prod_{p\mid n}
    2^{\ell-1}\gcd(u,p-1).
    $$

    综合两种情况，有

    $$
    |S'|=
    2\prod_{p\mid n}
    2^{\ell-1}\gcd(u,p-1).
    $$

    **第三步：证明 $|S'|\le\varphi(n)/4$．**

    结合欧拉函数的表达式

    $$
    \varphi(n)=\prod_i p_i^{e_i-1}(p_i-1),
    $$

    可得

    $$
    \frac{\varphi(n)}{|S'|}
    =
    \frac12
    \prod_i
    p_i^{e_i-1}
    \frac{p_i-1}
    {2^{\ell-1}\gcd(u,p_i-1)}.
    $$

    对于每个 $i$，相应的因子

    $$
    p_i^{e_i-1}
    \frac{p_i-1}
    {2^{\ell-1}\gcd(u,p_i-1)}
    $$

    都是偶数．因此，$\varphi(n)/|S'|$ 是一个整数．

    假设

    $$
    |S'|\le\frac14\varphi(n)
    $$

    不成立，则必然有

    $$
    \frac{\varphi(n)}{|S'|}=1,2,3.
    $$

    也就是说，

    $$
    \prod_i
    p_i^{e_i-1}
    \frac{p_i-1}
    {2^{\ell-1}\gcd(u,p_i-1)}
    =2,4,6.
    $$

    由于连乘式中的每个因子都是偶数，只有以下两种可能：

    - 只有一个因子，且该因子等于 $2$、$4$ 或 $6$；

    - 恰有两个因子，且它们都等于 $2$．

    先考虑有两个因子的情况．

    此时两个因子都没有奇素因子，因此

    $$
    p_i^{e_i-1}=1.
    $$

    亦即 $n$ 没有平方因子．不妨设

    $$
    n=p_1p_2,\qquad p_1<p_2,
    $$

    其中 $p_1,p_2$ 都是素数．

    两个因子都等于 $2$，因此

    $$
    p_i-1=2^\ell\gcd(u,p_i-1).
    $$

    所以可以写成

    $$
    p_i=1+2^\ell m_i,
    $$

    其中 $m_i$ 是奇数，且 $m_i\mid u$．

    将

    $$
    p_1p_2=n=1+u2^t
    $$

    对 $m_1$ 取模，得到

    $$
    p_1p_2\equiv1\pmod{m_1}.
    $$

    因此

    $$
    p_2\equiv1\pmod{m_1},
    $$

    说明 $m_1\mid m_2$．交换 $p_1,p_2$ 后可以得到 $m_2\mid m_1$．

    因而 $m_1=m_2$，进而 $p_1=p_2$，这与 $p_1<p_2$ 矛盾．

    再考虑只有一个因子的情况．

    此时合数 $n$ 为

    $$
    n=p^e,\qquad e>1.
    $$

    必然有

    $$
    p^{e-1}\mid 2,4,6.
    $$

    唯一可能的情况是 $p=3,e=2$，即 $n=9$，这与命题中 $n>9$ 的条件矛盾．

    综上，

    $$
    |S'|\le\frac14\varphi(n)
    $$

    成立．

    结合前两步，

    $$
    |S|\le |S'|\le\frac14\varphi(n).
    $$

    因此，对于所有奇合数 $n>9$，随机选择的一个基底通过 Miller–Rabin 测试的概率至多为 $1/4$．

    独立进行 $k$ 轮测试后，误判概率至多为

    $$
    \frac{1}{4^k}.
    $$

**基于 GRH 的确定性 Miller–Rabin 测试**

在 GRH 得到证明后，可以将 Miller–Rabin 测试转化为确定性算法．

Eric Bach 在 1990 年给出了素性测试所需的显式上界．根据其结果，对于任意奇合数 $n$，存在一个不超过 $2\ln^2 n$ 的 Miller–Rabin 见证[^deterministic-proof]．

因此，对于待判定的整数 $n$，先处理 $n<2$、$n=2$ 和偶数等特殊情况，然后只需要依次检验区间

$$
a\in
\left[
2,
\min\left\{
n-2,\left\lfloor2\ln^2 n\right\rfloor
\right\}
\right]
$$

中的全部整数作为测试基底．

- 如果存在某个基底无法通过 Miller–Rabin 测试，则可以确定 $n$ 是合数．

- 如果所有基底都通过测试，则可以确定 $n$ 是素数．

因此，这种方法能够在不使用随机数的情况下确定任意整数的素性．

这里的测试范围需要遍历全部整数，不能只随机抽取其中的一部分．计算时，$\ln$ 表示自然对数．

由于基底数量为 $O(\log^2 n)$，每个基底所需的模幂运算需要 $O(\log n)$ 次模乘，因此该确定性算法在不考虑乘法复杂度时的总时间复杂度为

$$
O(\log^3 n).
$$

采用普通整数乘法时，位复杂度为

$$
O(\log^5 n).
$$

另外，在 OI 范围内，通常会对 $[1,2^{64})$ 范围内的数进行素性检验．

对于 $[1,2^{32})$ 范围内的数，选取

$$
\{2,7,61\}
$$

三个数作为基底进行 Miller–Rabin 测试，就可以确定其素性．

对于 $[1,2^{64})$ 范围内的数，选取

$$
\{2,325,9375,28178,450775,9780504,1795265022\}
$$

七个数作为基底进行 Miller–Rabin 测试，就可以确定其素性[^witnesses]．

也可以选取

$$
\{2,3,5,7,11,13,17,19,23,29,31,37\}
$$

即前 $12$ 个素数，检验 $[1,2^{64})$ 范围内的整数．

这些固定基底集合给出了相应有限范围内的确定性测试方法，实际使用时通常比遍历 GRH 给出的基底范围更加高效．

注意，如果使用上面的数列作为基底判断 $n$ 的素性：

- 所有的数都要取一遍，不能只选小于 $n$ 的数；

- 把基底 $a$ 替换为 $a\bmod n$；

- 如果 $a\equiv0\pmod n$ 或 $a\equiv\pm1\pmod n$，则直接通过该轮测试．

## 反素数

顾名思义，素数是只有两个正约数的数．反素数则与约数个数有关：在给定范围内，约数个数最多的数中，反素数是最小的那个．因此，反素数的定义与所考虑的正整数范围有关．

一种符合直觉的反素数定义是：在所有不超过某个数的正整数中，约数个数最多且数值最小的数．

???+ abstract "反素数"

    对于某个正整数 $n$，如果任何小于 $n$ 的正整数的约数个数都小于 $n$ 的约数个数，则称 $n$ 为**反素数**（anti-prime, a.k.a. highly composite number）．

???+ warning "注意"

    注意区分 [emirp](https://en.wikipedia.org/wiki/Emirp)，它表示逐位反转后得到另一个不同素数的素数．例如，149 和 941 均为 emirp，101 不是 emirp．

### 过程

那么，如何求解反素数呢？

既然需要计算约数个数，首先考虑素因子分解．将 $n$ 分解为

$$
n=p_1^{k_1}p_2^{k_2}\cdots p_m^{k_m},
$$

其中 $p_i$ 是素数，$k_i$ 为其指数．

根据约数个数公式，$n$ 的约数总数为

$$
d(n)=(k_1+1)(k_2+1)\cdots(k_m+1).
$$

直接进行素因子分解的复杂度较高，而且计算前一个数的结果通常无法直接用于后一个数．因此，可以利用反素数的性质，通过 DFS 枚举指数来求解．

反素数具有以下两个重要特点：

1. 反素数的素因子一定是从 $2$ 开始的连续素数．

2. 数值较小的素数对应的指数不小于数值较大的素数对应的指数．也就是说，如果

   $$
   n=p_1^{k_1}p_2^{k_2}\cdots p_m^{k_m},
   $$

   且 $p_1<p_2<\cdots<p_m$，则必有

   $$
   k_1\ge k_2\ge\cdots\ge k_m.
   $$

解释：

1. 如果素因子没有从 $2$ 开始连续选取，那么可以保持各素因子的指数不变，将其中的素数替换为更小的素数．此时约数个数不变，而 $n$ 的数值减小．经过这样的替换，最终可以得到由从 $2$ 开始的连续素数组成的素因子分解形式．

2. 如果较小的素数对应的指数小于较大的素数对应的指数，那么交换这两个素数对应的指数，约数个数保持不变，但 $n$ 的数值会减小．因此，反素数必须满足指数单调不增的性质．

另外，还有两个问题需要考虑．

1. **对于给定的上界 $n$，应该枚举到哪个素数？**

   最极端的情况是

   $$
   n=p_1p_2\cdots p_m.
   $$

   因此，只需要枚举连续素数的乘积仍然不超过 $n$ 的情况．

   如果继续加入更大的素数，就意味着之前某个素数的指数为 $0$，这种形式不符合反素数的性质．

2. **应该枚举到多少次幂？**

   考虑极端情况：当最小的素数 $2$ 的幂次已经超过给定上界时，再加入其他素数也无法得到更小的合法结果．

   因此，最大幂次不会超过

   $$
   \lfloor\log_2 n\rfloor.
   $$

   可以据此设置 DFS 的搜索范围．

明确这些条件后，就可以使用 DFS 进行枚举．

可以将当前枚举到的每一个素数看作树中的一个层级，然后枚举该素数的幂次，递归进入下一层．

搜索过程中，需要考虑以下几种终止或更新条件：

1. 当前构造的数字已经大于给定上界，结束当前分支．

2. 当前枚举的素数已经超出允许范围，结束当前分支．

3. 当前因子数已经超过题目要求的约数个数，结束当前分支．

4. 当前因子数恰好等于目标约数个数时，判断并更新答案．

DFS 中不断枚举当前素数的指数，并递归处理下一个素数即可．

### 例题

???+ example "[Codeforces 27E. A number with a given number of divisors](https://codeforces.com/problemset/problem/27/E)"

    求具有给定约数个数的最小自然数．答案保证不超过 $10^{18}$．

??? note "解题思路"

    对于这种题目，可以将当前约数个数作为 DFS 的搜索状态．每次选择一个素数及其指数，更新当前数值和约数个数．当约数个数达到目标值时，更新最小答案．

??? note "参考代码"

    ```cpp
    --8<-- "docs/math/code/prime/prime_1.cpp"
    ```

???+ example "[ZOJ 2562 More Divisors](https://pintia.cn/problem-sets/91827364500/exam/problems/type/7?problemSetProblemId=91827366061)"

    求不超过 $n$ 的数中，约数个数最多的数．

??? note "解题思路"

    思路与上一题类似，只需要修改 DFS 的答案更新和终止条件．

    需要注意数据范围，使用 32 位整数可能发生溢出，应根据题目范围选择合适的数据类型．

??? note "参考代码"

    ```cpp
    --8<-- "docs/math/code/prime/prime_2.cpp"
    ```

## 参考资料与注释

1. Rui-Juan Jing, Marc Moreno-Maza, Delaram Talaashrafi, "[Complexity Estimates for Fourier-Motzkin Elimination](https://arxiv.org/abs/1811.01510)", Journal of Functional Programming 16:2 (2006), pp. 197–217.

2. [数论部分第一节：素数与素性测试](http://www.matrix67.com/blog/archives/234)

3. [Miller–Rabin 与 Pollard–Rho 学习笔记 - Bill Yang's Blog](https://blog.bill.moe/miller-rabin-notes/)

4. [Primality test - Wikipedia](https://en.wikipedia.org/wiki/Primality_test)

5. [Fermat pseudoprime - Wikipedia](https://en.wikipedia.org/wiki/Fermat_pseudoprime)

6. [桃子的算法笔记——反素数详解（acm/OI）](https://zhuanlan.zhihu.com/p/41759808)

7. [The Rabin-Miller Primality Test](http://home.sandiego.edu/~dhoffoss/teaching/cryptography/10-Rabin-Miller.pdf)

8. [Highly composite number - Wikipedia](https://en.wikipedia.org/wiki/Highly_composite_number)

9. Eric Bach, "[Explicit bounds for primality testing and related problems](https://doi.org/10.1090/S0025-5718-1990-1023756-8)", Mathematics of Computation, 55:191 (1990), pp. 355–380.

10. Andrew W. Sutherland, "[RH Lean proof: verification files](https://math.mit.edu/~drew/grh/)", Massachusetts Institute of Technology, 2026.

11. Lean and Mathlib communities, "[Lean verification of the Riemann Hypothesis](https://leanprover-community.github.io/blog/posts/riemann-hypothesis/)", 2026.

[^inf-fermat-pp]: Pomerance, Carl, John L. Selfridge, and Samuel S. Wagstaff. "The pseudoprimes to $25\cdot10^9$." Mathematics of Computation 35, no. 151 (1980): 1003–1026. 该文讨论了 Fermat 伪素数及其更严格的变体．

[^millerrabinproof]: 本结论及其证明参考了 Crandall, Richard, and Carl Pomerance. *Prime Numbers: A Computational Perspective*. New York, NY: Springer New York, 2005, 第 3.5 节．

[^deterministic-proof]: Bach, Eric. "[Explicit bounds for primality testing and related problems](https://doi.org/10.1090/S0025-5718-1990-1023756-8)." Mathematics of Computation 55:191 (1990): 355–380．该文在广义 Riemann 猜想成立的条件下，给出了确定性素性测试所需见证的显式上界．

[^grh-proof]: Andrew W. Sutherland, "[RH Lean proof: verification files](https://math.mit.edu/~drew/grh/)"．该核验记录列出了已验证的 Dirichlet $L$-函数相关定理，覆盖所有模数和所有 Dirichlet 特征，并记录了 Lean 内核及独立检查工具的验证结果．这里使用的 GRH 范围为 Dirichlet $L$-函数版本，不包括一般的 Dedekind zeta 函数、Hecke $L$-函数及 automorphic $L$-函数．

[^witnesses]: 更多类似的结果请参考 [Deterministic variant of the Miller–Rabin primality test](https://miller-rabin.appspot.com/#)．
