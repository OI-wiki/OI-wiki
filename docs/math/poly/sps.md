集合幂级数即多元形式幂级数形如

$$
A(x_1,\dots ,x_n)=a_0+a_1x_1+a_2x_2+a_3x_1x_2+\cdots
$$

且一般在环 $R\lbrack\lbrack x_1,\dots ,x_n\rbrack\rbrack /(x_1^2,\dots ,x_n^2)$ 上进行运算。后文我们称其为多项式因为 $R\lbrack\lbrack x_1,\dots ,x_n\rbrack\rbrack /(x_1^2,\dots ,x_n^2)\cong R\lbrack x_1,\dots ,x_n\rbrack /(x_1^2,\dots ,x_n^2)$。

## 子集卷积

子集卷积即集合幂级数的乘法，我们一共有 $n$ 个未定元，并且我们对系数进行了截断，这意味着这样的一个多项式有 $2^n$ 项系数。下面我们考虑这样两个多项式相乘，也就是计算

$$
AB\bmod{\left(x_1^2,\dots ,x_n^2\right)}
$$

我们注意到这一多项式对于任何一元来说，其都只有两项系数即 $a_0+a_1x$，不难想到我们对每一元使用 FFT，即求出

$$
A\left(\lbrace 1,-1 \rbrace^n\right)
$$

的值（$B$ 同理）即可计算出

$$
AB\bmod{\left(x_1^2-1,\dots ,x_n^2-1\right)}
$$

但是因为循环卷积的副作用，我们无法分离出想要的系数。考虑增加一元 $t$ 进行占位，转而计算

$$
AB\bmod{\left(x_1^2-t,\dots ,x_n^2-t\right)}
$$

然后令 $t\gets 0$ 即可。为了使得这一过程能够进行，我们将 $A$ 拆分为多个多项式之和，即

$$
A=\sum_i A_i
$$

其中 $A_i$ 的每一项都是形如 $cx_1^{d_1}\dots x_n^{d_n}$ 且 $\sum_j d_j=i$ 转而计算

$$
\left(\sum_i A_i\right)\left(\sum_i B_i\right)\bmod{\left(x_1^2-t,\dots ,x_n^2-t\right)}
$$

这样 $O(n^2)$ 次乘法，每一次都是计算 $A_iB_j \bmod{\left(x_1^2-t,\dots ,x_n^2-t\right)}$，注意到结果的每一项 $cx_1^{d_1}\dots x_n^{d_n}t^{d_t}$ 都满足下面的不等式

$$
d_1+\dots +d_n+d_t\leq i+j
$$

那么我们只需计算 $A_iB_j \bmod{\left(x_1^2-1,\dots ,x_n^2-1\right)}$ 然后只提取那些 $d_1+\dots +d_n=i+j$ 的项的系数，就相当于令 $t\gets 0$ 了，并且我们也有足够的信息可以还原出 $A_iB_j \bmod{\left(x_1^2-t,\dots ,x_n^2-t\right)}$，因为每当 $d_1+\dots +d_n$ 减少 $2$ 意味着这一项 $t$ 的次数增加 $1$。

上述算法已经足够我们完成子集卷积（但是要求 $2$ 在 $R$ 上可逆），传统的 Zeta 变换则是考虑计算

$$
AB\bmod{\left(x_1^2-tx_1,\dots ,x_n^2-tx_n\right)}
$$

即求出 $A\left(\lbrace 0,1 \rbrace^n\right)$。Zeta 变换的逆变换被称为 Möbius 变换。我们只需对上述算法稍作修改即可。

??? " 子集卷积模板（[LOJ 152. 子集卷积](https://loj.ac/p/152)）"
    ```cpp
    --8<-- "docs/math/code/poly/sps/sps_1.cpp"
    ```

## 乘法逆元

考虑计算

$$
A(x_1,\dots x_n)^{-1} \bmod{\left(x_1^2,\dots ,x_n^2\right)}
$$

我们考虑一元的情况，即

$$
(a+bx)^{-1}\equiv a^{-1}-ba^{-2}x\pmod{x^2}
$$

首先我们先求出常数项的乘法逆元，然后逐一加入元 $x_1,\dots ,x_n$，每一次我们都将这个多项式当成一个一元多项式去套用上式。在仅有一元 $x_1$ 时套用上式不难理解，在加入一元 $x_2$ 后，对于关于 $x_2$ 的多项式，其系数在环 $R\lbrack x_1\rbrack /(x_1^2)$ 上，而在加入 $x_3$ 后，对于关于 $x_3$ 的多项式，其系数在环 $R\lbrack x_1,x_2\rbrack /(x_1^2,x_2^2)$ 上，那么我们使用上述子集卷积即可。

```cpp
template <typename T>
std::vector<T> sps_inv(const std::vector<T> &x) {
  const int len = static_cast<int>(x.size());
  const int n = __builtin_ctz(len);
  std::vector<T> res(len);
  res.front() = x.front().inv();
  for (int i = 0; i != n; ++i) {
    std::vector a_1(res.begin(), res.begin() + (1 << i));  // a^{-1}
    std::vector b(x.begin() + (1 << i), x.begin() + (2 << i));
    auto t = subset_convolution(subset_convolution(b, a_1), a_1);
    for (int j = 0; j != 1 << i; ++j) res[j + (1 << i)] = -t[j];
  }
  return res;
}
```

## 对数

考虑计算

$$
\log A(x_1,\dots ,x_n)
$$

我们考虑一元的情况，即

$$
\begin{aligned}
\log (a+bx)&=\log(a(1+b/ax))\\
&=\log(a)+\log(1+b/ax)\\
&\equiv \log(a)+b/ax\pmod{x^2}
\end{aligned}
$$

同上操作即可，注意我们要求 $A$ 的常数项为 $1$。

```cpp
template <typename T>
std::vector<T> sps_log(const std::vector<T> &x) {
  const int len = static_cast<int>(x.size());
  const int n = __builtin_ctz(len);
  if (n == 0) return {0};
  std::vector<T> res(len);
  res.front() = 0;
  for (int i = 0; i != n; ++i) {
    std::vector a(x.begin(), x.begin() + (1 << i));
    std::vector b(x.begin() + (1 << i), x.begin() + (2 << i));
    auto t = subset_convolution(b, sps_inv(a));
    for (int j = 0; j != 1 << i; ++j) res[j + (1 << i)] = t[j];
  }
  return res;
}
```

## 指数

考虑计算

$$
\exp A(x_1,\dots ,x_n)
$$

我们考虑一元的情况，即

$$
\begin{aligned}
\exp(a+bx)&=\exp(a)\exp(bx)\\
&\equiv \exp(a)(1+bx)\pmod{x^2}\\
&\equiv \exp(a)+ \exp(a)bx\pmod{x^2}
\end{aligned}
$$

同上操作即可，注意我们要求 $A$ 的常数项为 $0$。

```cpp
template <typename T>
std::vector<T> sps_exp(const std::vector<T> &x) {
  const int len = static_cast<int>(x.size());
  const int n = __builtin_ctz(len);
  std::vector<T> res(len);
  res.front() = 1;
  for (int i = 0; i != n; ++i) {
    std::vector expa(res.begin(), res.begin() + (1 << i));
    std::vector b(x.begin() + (1 << i), x.begin() + (2 << i));
    auto t = subset_convolution(expa, b);
    for (int j = 0; j != 1 << i; ++j) res[j + (1 << i)] = t[j];
  }
  return res;
}
```

## 其他操作

例如平方根，幂运算等可自行推导不再赘述。

## 多项式复合集合幂级数

假设有集合幂级数 $G\in R\left\lbrack\left\lbrack x_1,\dots,x_n\right\rbrack\right\rbrack /\left(x_1^2,\dots,x_n^2\right)$ 和多项式 $F\in R\left\lbrack x\right\rbrack$，我们要求 $F\left(G\right)$。

不妨假设 $G$ 的常数项 $c=0$，否则的话我们也可以通过 $F\circ (x+c)\circ \left(G-c\right)$ 来计算，此时 $\left(G-c\right)^{n+1}\equiv 0\bmod{\left(x_1^2,\dots,x_n^2\right)}$ 所以只需要 $F\left(x+c\right)\bmod{x^{n+1}}$ 的系数即可，后文设 $\deg F\leq n$。

考虑

$$
\frac{\partial}{\partial x_n}\left(F\circ G\right)=F'\left(G\right)\frac{\partial}{\partial x_n}G
$$

而显然 $\frac{\partial}{\partial x_n}\left(F\circ G\right)=\left\lbrack x_n^1\right\rbrack\left(F\circ G\right)$，$\frac{\partial}{\partial x_n}G=\left\lbrack x_n^1\right\rbrack G$，也就是说我们将一个问题分解成两个子问题，分别是 $\left\lbrack x_n^0\right\rbrack F(G)$ 和 $\left\lbrack x_n^0\right\rbrack F'\left(G\right)$，下一轮递归我们则需要求出 $\left\lbrack x_{n-1}^0x_n^0\right\rbrack F(G)$，$\left\lbrack x_{n-1}^0x_n^0\right\rbrack F'(G)$ 和 $\left\lbrack x_{n-1}^0x_n^0\right\rbrack F''(G)$，因为两者有共同的一个子问题，所以子问题增长是线性的。

??? "算法流程"
    整个算法的流程大概是，我们在刚开始时可以立刻得到

    $$
    \begin{aligned}
    \left\lbrack x_1^0x_2^0\dots x_n^0\right\rbrack F^{\left(\red{n}\right)}(G)&=\frac{1}{\red{n}!}\left\lbrack x^\red{n}\right\rbrack F \\
    \left\lbrack x_1^0x_2^0\dots x_n^0\right\rbrack F^{\left(\red{n-1}\right)}(G)&=\frac{1}{\left(\red{n-1}\right)!}\left\lbrack x^\red{n-1}\right\rbrack F \\
    \vdots \\
    \left\lbrack x_1^0x_2^0\dots x_n^0\right\rbrack F(G)&=\frac{1}{\red{0}!}\left\lbrack x^\red{0}\right\rbrack F
    \end{aligned}
    $$

    然后计算

    $$
    \begin{aligned}
    \left\lbrack x_1^\red{1}x_2^0\dots x_n^0\right\rbrack F^{\left(\red{n-1}\right)}(G)&=\left(\left\lbrack x_1^\red{0}x_2^0\dots x_n^0\right\rbrack F^{\left(\red{n}\right)}(G)\right)\left(\left\lbrack x_1^{\red{1}}x_2^0\dots x_n^0\right\rbrack G\right) \\
    \left\lbrack x_1^\red{1}x_2^0\dots x_n^0\right\rbrack F^{\left(\red{n-2}\right)}(G)&=\left(\left\lbrack x_1^\red{0}x_2^0\dots x_n^0\right\rbrack F^{\left(\red{n-1}\right)}(G)\right)\left(\left\lbrack x_1^{\red{1}}x_2^0\dots x_n^0\right\rbrack G\right) \\
    \vdots \\
    \left\lbrack x_1^\red{1}x_2^0\dots x_n^0\right\rbrack F(G)&=\left(\left\lbrack x_1^\red{0}x_2^0\dots x_n^0\right\rbrack F^{\left(\red{1}\right)}(G)\right)\left(\left\lbrack x_1^{\red{1}}x_2^0\dots x_n^0\right\rbrack G\right)
    \end{aligned}
    $$

    也就是对 $k\in\left\lbrace 0,\dots,n-1\right\rbrace$ 计算出了 $\left\lbrack x_2^\red{0}\dots x_n^0\right\rbrack F^{\left(k\right)}(G)$，再迭代应用这个方法就可以了。当然我们也可以考虑从 $\left\lbrack \red{x_2}^0\dots x_n^0\right\rbrack F^{\left(\red{n-1}\right)}\left(G\right)$ 到 $\left\lbrack \red{x_3}^0\dots x_n^0\right\rbrack F^{\left(\red{n-2}\right)}\left(G\right)$ 类似这样的计算顺序。

    ```cpp
    #include <algorithm>
    #include <cassert>
    // 返回 F(G) 其中 deg(F) <= N 且 F 为 EGF
    // 限制 `std::size(F) - 1 = N` 和 `std::size(G) = (1 << N)` 和 `G[0] == 0`
    // 参考 Elegia. Optimal Algorithm on Polynomial Composite Set Power Series.
    //     https://codeforces.com/blog/entry/92183
    template <typename T>
    std::vector<T> sps_in_egf(const std::vector<T> &F, const std::vector<T> &G) {
        const int len = static_cast<int>(G.size());
        const int n   = __builtin_ctz(len);
        assert(static_cast<int>(F.size()) - 1 == n);
        assert(G[0] == 0);
        std::vector res = {F[n]};
        for (int i = 0; i < n; ++i) {
            std::vector<T> R(1 << (i + 1));
            // 注意我们直接使用了系数这是因为 F 是 EGF
            R[0] = F[n - (i + 1)];
            for (int j = 0; j <= i; ++j) {
                const auto FG = subset_convolution(
                    std::vector(res.begin(), res.begin() + (1 << j)),
                    std::vector(G.begin() + (1 << j), G.begin() + (2 << j)));
                std::copy(FG.begin(), FG.end(), R.begin() + (1 << j));
            }
            // now R = F^((N-(i+1)))(G)
            R.swap(res);
        }
        return res;
    }

    // 返回 F(G) 其中 F 为多项式
    template <typename T>
    inline std::vector<T> sps_in_poly(std::vector<T> F, std::vector<T> G) {
        const int len = static_cast<int>(G.size());
        const int n   = __builtin_ctz(len);
        // 当 G 的常数项不为 0 时，我们按照上述方法处理
        if (G[0] != 0) {
            std::vector<T> bin(n + 1), pw(F.size() + 1), FF(n + 1);
            // `pw[i]` 为 c^i
            pw[0] = 1;
            for (int i = 1; i < static_cast<int>(pw.size()); ++i) pw[i] = pw[i - 1] * G[0];
            G[0]   = 0;
            bin[0] = 1;
            for (int i = 0; i < static_cast<int>(F.size()); ++i) {
                // `bin[j]` 为 (1+x)^i 中 x^j 的系数
                // 因为我们只需要计算 F(x+c) mod x^(n+1) 的系数
                for (int j = 0; j <= std::min(n, i); ++j)
                    FF[j] += F[i] * bin[j] * pw[i - j];
                for (int j = n; j > 0; --j) bin[j] += bin[j - 1];
            }
            FF.swap(F);
        }
        // 然后我们将问题转换为 EGF 复合集合幂级数
        // 如果直接调用后者，我们注意到和计算指数时一样
        // 我们不需要 1,...,n 存在乘法逆元也是可以计算的
        F.resize(n + 1);
        T c = 1;
        for (int i = 1; i <= n; ++i) F[i] *= c *= i; // to EGF
        return sps_in_egf(F, G);
    }
    ```

时间复杂度为 $\sum_{k=0}^{n-1}\left(n-k\right)\cdot O\left(k^22^k\right)=O\left(n^22^n\right)$。

## 参考文献

-   Andreas Björklund and Thore Husfeldt.[Fourier Meets Möbius: Fast Subset Convolution](https://arxiv.org/abs/cs/0611101).
-   adamant.[Subset convolution interpretation](https://codeforces.com/blog/entry/92153).
-   Elegia.[Optimal Algorithm on Polynomial Composite Set Power Series](https://codeforces.com/blog/entry/92183).
