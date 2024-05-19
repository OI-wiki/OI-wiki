author: 97littleleaf11, abc1763613206, CCXXXI, EndlessCheng, Enter-tainer, fps5283, Great-designer, H-J-Granger, hly1204, hsfzLZH1, huayucaiji, Ir1d, kenlig, Marcythm, ouuan, SamZhangQingChuan, shuzhouliu, sshwy, StudyingFather, test12345-pupil, Tiphereth-A, TrisolarisHD, untitledunrevised

本页面包含多项式常见的初等函数操作。具体而言，本页面包含如下内容：

1.  多项式求逆
2.  多项式开方
3.  多项式除法
4.  多项式取模
5.  多项式指数函数
6.  多项式对数函数
7.  多项式三角函数
8.  多项式反三角函数

??? note "初等函数与非初等函数"
    初等函数的定义如下[^ref1]：
    
    若域 $F$ 中存在映射 $u\to \partial u$ 满足：
    
    1.  $\partial(u+v)=\partial u+\partial v$
    2.  $\partial(uv)=u\partial v+v\partial u$
    
    则称这个域为 **微分域**。
    
    若微分域 $F$ 上的函数 $u$ 满足以下的任意一条条件，则称该函数 $u$ 为初等函数：
    
    1.  $u$ 是 $F$ 上的代数函数。
    2.  $u$ 是 $F$ 上的指数性函数，即存在 $a\in F$ 使得 $\partial u=u\partial a$.
    3.  $u$ 是 $F$ 上的对数性函数，即存在 $a\in F$ 使得 $\partial u=\frac{\partial a}{a}$.
    
    以下是常见的初等函数：
    
    1.  代数函数：存在有限次多项式 $P$ 使得 $P(f(x))=0$ 的函数 $f(x)$，如 $2x+1$,$\sqrt{x}$,$(1+x^2)^{-1}$,$|x|$.
    2.  指数函数
    3.  对数函数
    4.  三角函数
    5.  反三角函数
    6.  双曲函数
    7.  反双曲函数
    8.  以上函数的复合，如：
    
        $$
        \frac{\mathrm{e}^{\tan x}}{1+x^2}\sin\left(\sqrt{1+\ln^2 x}\right)
        $$
    
        $$
        -\mathrm{i} \ln\left(x+\mathrm{i}\sqrt{1-x^2}\right)
        $$
    
    以下是常见的非初等函数：
    
    1.  误差函数：
    
        $$
        \operatorname{erf}(x):=\frac{2}{\sqrt{\pi}}\int_{0}^{x}\exp\left(-t^2\right)\mathrm{d}t
        $$

## 多项式求逆

给定多项式 $f\left(x\right)$，求 $f^{-1}\left(x\right)$。

### 解法

#### 倍增法

首先，易知

$$
\left[x^{0}\right]f^{-1}\left(x\right)=\left(\left[x^{0}\right]f\left(x\right)\right)^{-1}
$$

假设现在已经求出了 $f\left(x\right)$ 在模 $x^{\left\lceil\frac{n}{2}\right\rceil}$ 意义下的逆元 $f^{-1}_{0}\left(x\right)$。
有：

$$
\begin{aligned}
	f\left(x\right)f^{-1}_{0}\left(x\right)&\equiv 1 &\pmod{x^{\left\lceil\frac{n}{2}\right\rceil}}\\
	f\left(x\right)f^{-1}\left(x\right)&\equiv 1 &\pmod{x^{\left\lceil\frac{n}{2}\right\rceil}}\\
	f^{-1}\left(x\right)-f^{-1}_{0}\left(x\right)&\equiv 0 &\pmod{x^{\left\lceil\frac{n}{2}\right\rceil}}
\end{aligned}
$$

两边平方可得：

$$
f^{-2}\left(x\right)-2f^{-1}\left(x\right)f^{-1}_{0}\left(x\right)+f^{-2}_{0}\left(x\right)\equiv 0 \pmod{x^{n}}
$$

两边同乘 $f\left(x\right)$ 并移项可得：

$$
f^{-1}\left(x\right)\equiv f^{-1}_{0}\left(x\right)\left(2-f\left(x\right)f^{-1}_{0}\left(x\right)\right) \pmod{x^{n}}
$$

递归计算即可。

**时间复杂度**

$$
T\left(n\right)=T\left(\frac{n}{2}\right)+O\left(n\log{n}\right)=O\left(n\log{n}\right)
$$

#### Newton's Method

参见 [Newton's Method](./newton.md#newtons-method).

#### Graeffe 法

欲求 $f^{-1}(x)\bmod x^{2n}$ 考虑

$$
\begin{aligned}
f^{-1}(x)\bmod x^{2n}&= f(-x)(f(x)f(-x))^{-1}\bmod x^{2n}\\
&=f(-x)g^{-1}(x^2)\bmod x^{2n}
\end{aligned}
$$

只需求出 $g^{-1}(x)\bmod x^n$ 即可还原出 $g^{-1}(x^2)\bmod x^{2n}$ 因为 $f(x)f(-x)$ 是偶函数，时间复杂度同上。

### 代码

??? "多项式求逆"
    ```cpp
    constexpr int maxn = 262144;
    constexpr int mod = 998244353;
    
    using i64 = long long;
    using poly_t = int[maxn];
    using poly = int *const;
    
    void polyinv(const poly &h, const int n, poly &f) {
      /* f = 1 / h = f_0 (2 - f_0 h) */
      static poly_t inv_t;
      std::fill(f, f + n + n, 0);
      f[0] = fpow(h[0], mod - 2);
      for (int t = 2; t <= n; t <<= 1) {
        const int t2 = t << 1;
        std::copy(h, h + t, inv_t);
        std::fill(inv_t + t, inv_t + t2, 0);
    
        DFT(f, t2);
        DFT(inv_t, t2);
        for (int i = 0; i != t2; ++i)
          f[i] = (i64)f[i] * sub(2, (i64)f[i] * inv_t[i] % mod) % mod;
        IDFT(f, t2);
    
        std::fill(f + t, f + t2, 0);
      }
    }
    ```

### 例题

1.  有标号简单无向连通图计数：[「POJ 1737」Connected Graph](http://poj.org/problem?id=1737)

## 多项式开方

给定多项式 $g\left(x\right)$，求 $f\left(x\right)$，满足：

$$
f^{2}\left(x\right)\equiv g\left(x\right) \pmod{x^{n}}
$$

### 解法

#### 倍增法

首先讨论 $\left[x^0\right]g(x)$ 不为 $0$ 的情况。

易知：

$$
\left[x^0\right]f(x) = \sqrt{\left[x^0\right]g(x)}
$$

若 $\left[x^0\right]g(x)$ 没有平方根，则多项式 $g(x)$ 没有平方根。

> $\left[x^0\right]g(x)$ 可能有多个平方根，选取不同的根会求出不同的 $f(x)$。

假设现在已经求出了 $g\left(x\right)$ 在模 $x^{\left\lceil\frac{n}{2}\right\rceil}$ 意义下的平方根 $f_{0}\left(x\right)$，则有：

$$
\begin{aligned}
	f_{0}^{2}\left(x\right)&\equiv g\left(x\right) &\pmod{x^{\left\lceil\frac{n}{2}\right\rceil}}\\
	f_{0}^{2}\left(x\right)-g\left(x\right)&\equiv 0 &\pmod{x^{\left\lceil\frac{n}{2}\right\rceil}}\\
	\left(f_{0}^{2}\left(x\right)-g\left(x\right)\right)^{2}&\equiv 0 &\pmod{x^{n}}\\
	\left(f_{0}^{2}\left(x\right)+g\left(x\right)\right)^{2}&\equiv 4f_{0}^{2}\left(x\right)g\left(x\right) &\pmod{x^{n}}\\
	\left(\frac{f_{0}^{2}\left(x\right)+g\left(x\right)}{2f_{0}\left(x\right)}\right)^{2}&\equiv g\left(x\right) &\pmod{x^{n}}\\
	\frac{f_{0}^{2}\left(x\right)+g\left(x\right)}{2f_{0}\left(x\right)}&\equiv f\left(x\right) &\pmod{x^{n}}\\
	2^{-1}f_{0}\left(x\right)+2^{-1}f_{0}^{-1}\left(x\right)g\left(x\right)&\equiv f\left(x\right) &\pmod{x^{n}}
\end{aligned}
$$

倍增计算即可。

**时间复杂度**

$$
T\left(n\right)=T\left(\frac{n}{2}\right)+O\left(n\log{n}\right)=O\left(n\log{n}\right)
$$

还有一种常数较小的写法就是在倍增维护 $f\left(x\right)$ 的时候同时维护 $f^{-1}\left(x\right)$ 而不是每次都求逆。

> 当 $\left[x^{0}\right]g\left(x\right)\neq 1$ 时，可能需要使用二次剩余来计算 $\left[x^{0}\right]f\left(x\right)$。

上述方法需要知道 $f_{0}(x)$ 的逆，所以常数项不能为 $0$。

若 $\left[x^0\right]g(x) = 0$，则将 $g(x)$ 分解成 $x^{k}h(x)$，其中 $\left[x^0\right]h(x) \not = 0$。

-   若 $k$ 是奇数，则 $g(x)$ 没有平方根。

-   若 $k$ 是偶数，则求出 $h(x)$ 的平方根 $\sqrt{h(x)}$，然后得到 $f(x) \equiv x^{k/2} \sqrt{h(x)} \pmod{x^{n}}$。

??? " 洛谷模板题 [P5205【模板】多项式开根](https://www.luogu.com.cn/problem/P5205) 参考代码 "
    ```cpp
    --8<-- "docs/math/code/poly/sqrt/sqrt_1.cpp"
    ```

#### Newton's Method

参见 [Newton's Method](./newton.md#newtons-method).

### 例题

1.  [「Codeforces Round #250」E. The Child and Binary Tree](https://codeforces.com/contest/438/problem/E)

## 多项式除法 & 取模

给定多项式 $f\left(x\right),g\left(x\right)$，求 $g\left(x\right)$ 除 $f\left(x\right)$ 的商 $Q\left(x\right)$ 和余数 $R\left(x\right)$。

### 解法

发现若能消除 $R\left(x\right)$ 的影响则可直接 [多项式求逆](#多项式求逆) 解决。

考虑构造变换

$$
f^{R}\left(x\right)=x^{\operatorname{deg}{f}}f\left(\frac{1}{x}\right)
$$

观察可知其实质为反转 $f\left(x\right)$ 的系数。

设 $n=\operatorname{deg}{f},m=\operatorname{deg}{g}$。

将 $f\left(x\right)=Q\left(x\right)g\left(x\right)+R\left(x\right)$ 中的 $x$ 替换成 $\frac{1}{x}$ 并将其两边都乘上 $x^{n}$，得到：

$$
\begin{aligned}
    x^{n}f\left(\frac{1}{x}\right)&=x^{n-m}Q\left(\frac{1}{x}\right)x^{m}g\left(\frac{1}{x}\right)+x^{n-m+1}x^{m-1}R\left(\frac{1}{x}\right)\\
    f^{R}\left(x\right)&=Q^{R}\left(x\right)g^{R}\left(x\right)+x^{n-m+1}R^{R}\left(x\right)
\end{aligned}
$$

注意到上式中 $R^{R}\left(x\right)$ 的系数为 $x^{n-m+1}$，则将其放到模 $x^{n-m+1}$ 意义下即可消除 $R^{R}\left(x\right)$ 带来的影响。

又因 $Q^{R}\left(x\right)$ 的次数为 $\left(n-m\right)<\left(n-m+1\right)$，故 $Q^{R}\left(x\right)$ 不会受到影响。

则：

$$
f^{R}\left(x\right)\equiv Q^{R}\left(x\right)g^{R}\left(x\right)\pmod{x^{n-m+1}}
$$

使用多项式求逆即可求出 $Q\left(x\right)$，将其反代即可得到 $R\left(x\right)$。

**时间复杂度**  $O\left(n\log{n}\right)$。

## 多项式对数函数 & 指数函数

给定多项式 $f(x)$，求模 $x^{n}$ 意义下的 $\ln{f(x)}$ 与 $\exp{f(x)}$。

### 解法

#### 普通方法

=== "多项式对数函数"
    首先，对于多项式 $f(x)$，若 $\ln{f(x)}$ 存在，则由其 [定义](./intro.md#复合)，其必须满足：
    
    $$
    [x^{0}]f(x)=1
    $$
    
    对 $\ln{f(x)}$ 求导再积分，可得：
    
    $$
    \begin{aligned}
        \frac{\mathrm{d} \ln{f(x)}}{\mathrm{d} x} & \equiv \frac{f'(x)}{f(x)} & \pmod{x^{n}} \\
        \ln{f(x)} & \equiv \int \mathrm{d} \ln{x} \equiv \int\frac{f'(x)}{f(x)} \mathrm{d} x & \pmod{x^{n}}
    \end{aligned}
    $$
    
    多项式的求导，积分时间复杂度为 $O(n)$，求逆时间复杂度为 $O(n\log{n})$，故多项式求 $\ln$ 时间复杂度 $O(n\log{n})$。

=== "多项式指数函数"
    首先，对于多项式 $f(x)$，若 $\exp{f(x)}$ 存在，则其必须满足：
    
    $$
    [x^{0}]f(x)=0
    $$
    
    否则 $\exp{f(x)}$ 的常数项不收敛。
    
    对 $\exp{f(x)}$ 求导，可得：
    
    $$
    \frac{\mathrm{d} \exp{f(x)}}{\mathrm{d} x} \equiv \exp{f(x)}f'(x)\pmod{x^{n}}
    $$
    
    比较两边系数可得：
    
    $$
    [x^{n-1}]\frac{\mathrm{d} \exp{f(x)}}{\mathrm{d} x} = \sum_{i = 0}^{n - 1} \left([x^{i}]\exp{f(x)}\right) \left([x^{n-i-1}]f'(x)\right)
    $$
    
    $$
    n[x^{n}]\exp{f(x)} = \sum_{i = 0}^{n - 1} \left([x^{i}]\exp{f(x)}\right) \left((n - i)[x^{n - i}]f(x)\right)
    $$
    
    使用分治 FFT 即可解决。
    
    **时间复杂度**  $O(n\log^{2}{n})$。

#### Newton's Method

使用 [Newton's Method](./newton.md#newtons-method) 即可在 $O(n\log{n})$ 的时间复杂度内解决多项式 $\exp$。

### 代码

??? "多项式 ln/exp"
    ```cpp
    constexpr int maxn = 262144;
    constexpr int mod = 998244353;
    
    using i64 = long long;
    using poly_t = int[maxn];
    using poly = int *const;
    
    void derivative(const poly &h, const int n, poly &f) {
      for (int i = 1; i != n; ++i) f[i - 1] = (i64)h[i] * i % mod;
      f[n - 1] = 0;
    }
    
    void integrate(const poly &h, const int n, poly &f) {
      for (int i = n - 1; i; --i) f[i] = (i64)h[i - 1] * inv[i] % mod;
      f[0] = 0; /* C */
    }
    
    void polyln(const poly &h, const int n, poly &f) {
      /* f = ln h = ∫ h' / h dx */
      assert(h[0] == 1);
      static poly_t ln_t;
      const int t = n << 1;
    
      derivative(h, n, ln_t);
      std::fill(ln_t + n, ln_t + t, 0);
      polyinv(h, n, f);
    
      DFT(ln_t, t);
      DFT(f, t);
      for (int i = 0; i != t; ++i) ln_t[i] = (i64)ln_t[i] * f[i] % mod;
      IDFT(ln_t, t);
    
      integrate(ln_t, n, f);
    }
    
    void polyexp(const poly &h, const int n, poly &f) {
      /* f = exp(h) = f_0 (1 - ln f_0 + h) */
      assert(h[0] == 0);
      static poly_t exp_t;
      std::fill(f, f + n + n, 0);
      f[0] = 1;
      for (int t = 2; t <= n; t <<= 1) {
        const int t2 = t << 1;
    
        polyln(f, t, exp_t);
        exp_t[0] = sub(pls(h[0], 1), exp_t[0]);
        for (int i = 1; i != t; ++i) exp_t[i] = sub(h[i], exp_t[i]);
        std::fill(exp_t + t, exp_t + t2, 0);
    
        DFT(f, t2);
        DFT(exp_t, t2);
        for (int i = 0; i != t2; ++i) f[i] = (i64)f[i] * exp_t[i] % mod;
        IDFT(f, t2);
    
        std::fill(f + t, f + t2, 0);
      }
    }
    ```

### 例题

1.  计算 $f^{k}(x)$

    普通做法为多项式快速幂，时间复杂度 $O(n\log{n}\log{k})$。

    当 $[x^{0}]f(x)=1$ 时，有：

    $$
    f^{k}(x)=\exp{\left(k\ln{f(x)}\right)}
    $$

    当 $[x^{0}]f(x)\neq 1$ 时，设 $f(x)$ 的最低次项为 $f_{i}x^{i}$，则：

    $$
    f^{k}(x)=f_{i}^{k}x^{ik}\exp{\left(k\ln{\frac{f(x)}{f_{i}x^{i}}}\right)}
    $$

    **时间复杂度**  $O(n\log{n})$。

## 多项式三角函数

给定多项式 $f\left(x\right)$，求模 $x^{n}$ 意义下的 $\sin{f\left(x\right)}, \cos{f\left(x\right)}$ 与 $\tan{f\left(x\right)}$。

### 解法

首先由 [Euler's formula](../complex.md#欧拉公式) $\left(\mathrm{e}^{\mathrm{i}x} = \cos{x} + \mathrm{i}\sin{x}\right)$ 可以得到 [三角函数的另一个表达式](https://en.wikipedia.org/wiki/Trigonometric_functions#Relationship_to_exponential_function_and_complex_numbers)：

$$
\begin{aligned}
	\sin{x} &= \frac{\mathrm{e}^{\mathrm{i}x} - \mathrm{e}^{-\mathrm{i}x}}{2\mathrm{i}} \\
	\cos{x} &= \frac{\mathrm{e}^{\mathrm{i}x} + \mathrm{e}^{-\mathrm{i}x}}{2}
\end{aligned}
$$

那么代入 $f\left(x\right)$ 就有：

$$
\begin{aligned}
	\sin{f\left(x\right)} &= \frac{\exp{\left(\mathrm{i}f\left(x\right)\right)} - \exp{\left(-\mathrm{i}f\left(x\right)\right)}}{2\mathrm{i}} \\
	\cos{f\left(x\right)} &= \frac{\exp{\left(\mathrm{i}f\left(x\right)\right)} + \exp{\left(-\mathrm{i}f\left(x\right)\right)}}{2}
\end{aligned}
$$

直接按上述表达式编写程序即可得到模 $x^{n}$ 意义下的 $\sin{f\left(x\right)}$ 与 $\cos{f\left(x\right)}$。再由 $\tan{f\left(x\right)} = \frac{\sin{f\left(x\right)}}{\cos{f\left(x\right)}}$ 可求得 $\tan{f\left(x\right)}$。

### 代码

??? "多项式三角函数"
    注意到我们是在 $\mathbb{Z}_{998244353}$ 上做 NTT，那么相应地，虚数单位 $\mathrm{i}$ 应该被换成 $86583718$ 或 $911660635$：
    
    $$
    \begin{aligned}
               & \mathrm{i} = \sqrt{-1} \equiv \sqrt{998244352} \pmod{998244353}       \\
      \implies & \phantom{\text{or}} \quad \mathrm{i} \equiv 86583718 \pmod{998244353} \\
               & \text{or} \quad \mathrm{i} \equiv 911660635 \pmod{998244353}
    \end{aligned}
    $$
    
    ```cpp
    constexpr int maxn = 262144;
    constexpr int mod = 998244353;
    constexpr int imgunit = 86583718; /* sqrt(-1) = sqrt(998233452) */
    
    using i64 = long long;
    using poly_t = int[maxn];
    using poly = int *const;
    
    void polytri(const poly &h, const int n, poly &sin_t, poly &cos_t) {
      /* sin(f) = (exp(i * f) - exp(- i * f)) / 2i */
      /* cos(f) = (exp(i * f) + exp(- i * f)) / 2 */
      /* tan(f) = sin(f) / cos(f) */
      assert(h[0] == 0);
      static poly_t tri1_t, tri2_t;
    
      for (int i = 0; i != n; ++i) tri2_t[i] = (i64)h[i] * imgunit % mod;
      polyexp(tri2_t, n, tri1_t);
      polyinv(tri1_t, n, tri2_t);
    
      if (sin_t != nullptr) {
        const int invi = fpow(pls(imgunit, imgunit), mod - 2);
        for (int i = 0; i != n; ++i)
          sin_t[i] = (i64)(tri1_t[i] - tri2_t[i] + mod) * invi % mod;
      }
      if (cos_t != nullptr) {
        for (int i = 0; i != n; ++i) cos_t[i] = div2(pls(tri1_t[i], tri2_t[i]));
      }
    }
    ```

## 多项式反三角函数

给定多项式 $f\left(x\right)$，求模 $x^{n}$ 意义下的 $\arcsin{f\left(x\right)}, \arccos{f\left(x\right)}$ 与 $\arctan{f\left(x\right)}$。

### 解法

仿照求多项式 $\ln$ 的方法，对反三角函数求导再积分可得：

$$
\begin{aligned}
	\frac{\mathrm{d}}{\mathrm{d} x} \arcsin{x} &= \frac{1}{\sqrt{1 - x^{2}}} \\
	\arcsin{x} &= \int \frac{1}{\sqrt{1 - x^{2}}} \mathrm{d} x \\
	\frac{\mathrm{d}}{\mathrm{d} x} \arccos{x} &= - \frac{1}{\sqrt{1 - x^{2}}} \\
	\arccos{x} &= - \int \frac{1}{\sqrt{1 - x^{2}}} \mathrm{d} x \\
	\frac{\mathrm{d}}{\mathrm{d} x} \arctan{x} &= \frac{1}{1 + x^{2}} \\
	\arctan{x} &= \int \frac{1}{1 + x^{2}} \mathrm{d} x
\end{aligned}
$$

那么代入 $f\left(x\right)$ 就有：

$$
\begin{aligned}
	\frac{\mathrm{d}}{\mathrm{d} x} \arcsin{f\left(x\right)} &= \frac{f'\left(x\right)}{\sqrt{1 - f^{2}\left(x\right)}} \\
	\arcsin{f\left(x\right)} &= \int \frac{f'\left(x\right)}{\sqrt{1 - f^{2}\left(x\right)}} \mathrm{d} x \\
	\frac{\mathrm{d}}{\mathrm{d} x} \arccos{f\left(x\right)} &= - \frac{f'\left(x\right)}{\sqrt{1 - f^{2}\left(x\right)}} \\
	\arccos{f\left(x\right)} &= - \int \frac{f'\left(x\right)}{\sqrt{1 - f^{2}\left(x\right)}} \mathrm{d} x \\
	\frac{\mathrm{d}}{\mathrm{d} x} \arctan{f\left(x\right)} &= \frac{f'\left(x\right)}{1 + f^{2}\left(x\right)} \\
	\arctan{f\left(x\right)} &= \int \frac{f'\left(x\right)}{1 + f^{2}\left(x\right)} \mathrm{d} x
\end{aligned}
$$

直接按式子求就可以了。

### 代码

??? "多项式反三角函数"
    ```cpp
    constexpr int maxn = 262144;
    constexpr int mod = 998244353;
    
    using i64 = long long;
    using poly_t = int[maxn];
    using poly = int *const;
    
    void derivative(const poly &h, const int n, poly &f) {
      for (int i = 1; i != n; ++i) f[i - 1] = (i64)h[i] * i % mod;
      f[n - 1] = 0;
    }
    
    void integrate(const poly &h, const int n, poly &f) {
      for (int i = n - 1; i; --i) f[i] = (i64)h[i - 1] * inv[i] % mod;
      f[0] = 0; /* C */
    }
    
    void polyarcsin(const poly &h, const int n, poly &f) {
      /* arcsin(f) = ∫ f' / sqrt(1 - f^2) dx  */
      static poly_t arcsin_t;
      const int t = n << 1;
      std::copy(h, h + n, arcsin_t);
      std::fill(arcsin_t + n, arcsin_t + t, 0);
    
      DFT(arcsin_t, t);
      for (int i = 0; i != t; ++i) arcsin_t[i] = sqr(arcsin_t[i]);
      IDFT(arcsin_t, t);
    
      arcsin_t[0] = sub(1, arcsin_t[0]);
      for (int i = 1; i != n; ++i)
        arcsin_t[i] = arcsin_t[i] ? mod - arcsin_t[i] : 0;
    
      polysqrt(arcsin_t, n, f);
      polyinv(f, n, arcsin_t);
      derivative(h, n, f);
    
      DFT(f, t);
      DFT(arcsin_t, t);
      for (int i = 0; i != t; ++i) arcsin_t[i] = (i64)f[i] * arcsin_t[i] % mod;
      IDFT(arcsin_t, t);
    
      integrate(arcsin_t, n, f);
    }
    
    void polyarccos(const poly &h, const int n, poly &f) {
      /* arccos(f) = - ∫ f' / sqrt(1 - f^2) dx  */
      polyarcsin(h, n, f);
      for (int i = 0; i != n; ++i) f[i] = f[i] ? mod - f[i] : 0;
    }
    
    void polyarctan(const poly &h, const int n, poly &f) {
      /* arctan(f) = ∫ f' / (1 + f^2) dx  */
      static poly_t arctan_t;
      const int t = n << 1;
      std::copy(h, h + n, arctan_t);
      std::fill(arctan_t + n, arctan_t + t, 0);
    
      DFT(arctan_t, t);
      for (int i = 0; i != t; ++i) arctan_t[i] = sqr(arctan_t[i]);
      IDFT(arctan_t, t);
    
      inc(arctan_t[0], 1);
      std::fill(arctan_t + n, arctan_t + t, 0);
    
      polyinv(arctan_t, n, f);
      derivative(h, n, arctan_t);
    
      DFT(f, t);
      DFT(arctan_t, t);
      for (int i = 0; i != t; ++i) arctan_t[i] = (i64)f[i] * arctan_t[i] % mod;
      IDFT(arctan_t, t);
    
      integrate(arctan_t, n, f);
    }
    ```

## 参考资料与链接

[^ref1]: [Elementary function——Wikipedia](https://en.wikipedia.org/wiki/Elementary_function)
