集合幂级数即多元形式幂级数形如

$$
A(x_1,\dots ,x_n)=a_0+a_1x_1+a_2x_2+a_3x_1x_2+\cdots
$$

且一般在环 $R\lbrack\lbrack x_1,\dots ,x_n\rbrack\rbrack /(x_1^2,\dots ,x_n^2)$ 上进行运算。后文我们称其为多项式因为 $R\lbrack\lbrack x_1,\dots ,x_n\rbrack\rbrack /(x_1^2,\dots ,x_n^2)\cong R\lbrack x_1,\dots ,x_n\rbrack /(x_1^2,\dots ,x_n^2)$。

## 子集卷积

子集卷积即集合幂级数的乘法，我们一共有 $n$ 个未定元，并且我们对系数进行了截断，这意味着这样的一个多项式有 $2^n$ 项系数。下面我们考虑这样两个多项式相乘，也就是计算

$$
AB\bmod{\left(x_1^2,\dots x_n^2\right)}
$$

我们注意到这一多项式对于任何一元来说，其都只有两项系数即 $a_0+a_1x$，不难想到我们对每一元使用 FFT 即求出

$$
A\left(\lbrace 1,-1 \rbrace^n\right)
$$

的值（$B$ 同理）即可计算出

$$
AB\bmod{\left(x_1^2-1,\dots ,x_n^2-1\right)}
$$

但是我们因为循环卷积的副作用，无法分离出想要的系数。考虑增加一元 $t$ 进行占位，转而计算

$$
AB\bmod{\left(x_1^2-t,\dots ,x_n^2-t\right)}
$$

然后令 $t\gets 0$ 即可。为了使得这一过程能够进行，我们将 $A$ 拆分为多个多项式之和即

$$
A=\sum_i A_i
$$

其中 $A_i$ 的每一项都是形如 $cx_1^{d_1}\dots x_n^{d_n}$ 且 $\sum_j d_j=i$ 转而计算

$$
\left(\sum_i A_i\right)\left(\sum_i B_i\right)\bmod{\left(x_1^2-t,\dots ,x_n^2-t\right)}
$$

这样 $O(n^2)$ 次乘法，每一次都是形如计算 $A_iB_j \bmod{\left(x_1^2-t,\dots ,x_n^2-t\right)}$，注意到结果的每一项 $cx_1^{d_1}\dots x_n^{d_n}t^{d_t}$ 都满足下面的不等式

$$
d_1+\dots +d_n+d_t\leq i+j
$$

那么我们只需计算 $A_iB_j \bmod{\left(x_1^2-1,\dots ,x_n^2-1\right)}$ 然后只提取那些 $d_1+\dots +d_n=i+j$ 的项的系数，就相当于令 $t\gets 0$ 了，并且我们也有足够的信息可以还原出 $A_iB_j \bmod{\left(x_1^2-t,\dots ,x_n^2-t\right)}$，因为每当 $d_1+\dots +d_n$ 减少 $2$ 意味着这一项 $t$ 的次数增加 $1$。

上述算法已经足够我们完成子集卷积（但是要求 $2$ 在 $R$ 上可逆），传统的 Zeta 变换则是考虑计算

$$
AB\bmod{\left(x_1^2-tx_1,\dots ,x_n^2-tx_n\right)}
$$

即求出 $A\left(\lbrace 0,1 \rbrace^n\right)$。Zeta 变换的逆变换被称为 Moebius 变换。我们只需对上述算法稍作修改即可。

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
  const int n = std::countr_zero(static_cast<unsigned>(len));
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
  const int n = std::countr_zero(static_cast<unsigned>(len));
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
  const int n = std::countr_zero(static_cast<unsigned>(len));
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

## 参考文献

-   Andreas Björklund and Thore Husfeldt.[Fourier Meets Möbius: Fast Subset Convolution](http://algo.inria.fr/flajolet/Publications/books.html).
-   adamant.[Subset convolution interpretation](https://codeforces.com/blog/entry/92153).
-   Elegia.[Optimal Algorithm on Polynomial Composite Set Power Series](https://codeforces.com/blog/entry/92183).
