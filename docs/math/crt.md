## 「物不知数」问题

> 有物不知其数，三三数之剩二，五五数之剩三，七七数之剩二。问物几何？

即求满足以下条件的整数：除以 $3$ 余 $2$，除以 $5$ 余 $3$，除以 $7$ 余 $2$。

该问题最早见于《孙子算经》中，并有该问题的具体解法。宋朝数学家秦九韶于 1247 年《数书九章》卷一、二《大衍类》对「物不知数」问题做出了完整系统的解答。上面具体问题的解答口诀由明朝数学家程大位在《算法统宗》中给出：

> 三人同行七十希，五树梅花廿一支，七子团圆正半月，除百零五便得知。

$2\times 70+3\times 21+2\times 15=233=2\times 105+23$，故答案为 $23$。

## 算法简介及过程

中国剩余定理 (Chinese Remainder Theorem, CRT) 可求解如下形式的一元线性同余方程组（其中 $n_1, n_2, \cdots, n_k$ 两两互质）：

$$
\begin{cases}
x &\equiv a_1 \pmod {n_1} \\
x &\equiv a_2 \pmod {n_2} \\
  &\vdots \\
x &\equiv a_k \pmod {n_k} \\
\end{cases}
$$

上面的「物不知数」问题就是一元线性同余方程组的一个实例。

### 算法流程

1. 计算所有模数的积 $n$；
2.  对于第 $i$ 个方程：
    1. 计算 $m_i=\frac{n}{n_i}$；
    2. 计算 $m_i$ 在模 $n_i$ 意义下的 [逆元](./inverse.md)  $m_i^{-1}$；
    3. 计算 $c_i=m_im_i^{-1}$（**不要对 $n_i$ 取模**）。
3. 方程组的唯一解为：$x=\sum_{i=1}^k a_ic_i \pmod n$。

### C 语言代码

```cpp
LL CRT(int k, LL* a, LL* r) {
  LL n = 1, ans = 0;
  for (int i = 1; i <= k; i++) n = n * r[i];
  for (int i = 1; i <= k; i++) {
    LL m = n / r[i], b, y;
    exgcd(m, r[i], b, y);  // b * m mod r[i] = 1
    ans = (ans + a[i] * m * b % mod) % mod;
  }
  return (ans % mod + mod) % mod;
}
```

## 算法的证明

我们需要证明上面算法计算所得的 $x$ 对于任意 $i=1,2,\cdots,k$ 满足 $x\equiv a_i \pmod {n_i}$。

当 $i\neq j$ 时，有 $m_j \equiv 0 \pmod {n_i}$，故 $c_j \equiv m_j \equiv 0 \pmod {n_i}$。又有 $c_i \equiv m_i \cdot (m_i^{-1} \bmod {n_i}) \equiv 1 \pmod {n_i}$，所以我们有：

$$
\begin{aligned}
x&\equiv \sum_{j=1}^k a_jc_j                      &\pmod {n_i} \\
 &\equiv a_ic_i                                   &\pmod {n_i} \\
 &\equiv a_i \cdot m_i \cdot (m^{-1}_i \bmod n_i) &\pmod {n_i} \\
 &\equiv a_i                                      &\pmod {n_i}
\end{aligned}
$$

**即对于任意 $i=1,2,\cdots,k$，上面算法得到的 $x$ 总是满足 $x\equiv a_i \pmod{n_i}$，即证明了解同余方程组的算法的正确性。**

因为我们没有对输入的 $a_i$ 作特殊限制，所以任何一组输入 $\{a_i\}$ 都对应一个解 $x$。

另外，若 $x\neq y$，则总存在 $i$ 使得 $x$ 和 $y$ 在模 $n_i$ 下不同余。

**故系数列表 $\{a_i\}$ 与解 $x$ 之间是一一映射关系，方程组总是有唯一解。**

## 例

下面演示 CRT 如何解「物不知数」问题。

1. $n=3\times 5\times 7=105$；
2. 三人同行 **七十** 希：$n_1=3, m_1=n/n_1=35, m_1^{-1}\equiv 2\pmod 3$，故 $c_1=35\times 2=70$；
3. 五树梅花 **廿一** 支：$n_2=5, m_2=n/n_2=21, m_2^{-1}\equiv 1\pmod 5$，故 $c_2=21\times 1=21$；
4. 七子团圆正 **半月**：$n_3=7, m_3=n/n_3=15, m_3^{-1}\equiv 1\pmod 7$，故 $c_3=15\times 1=15$；
5. 所以方程组的唯一解为 $x\equiv 2\times 70+3\times 21+2\times 15\equiv 233\equiv 23 \pmod {105}$。（除 **百零五** 便得知）

## Garner 算法

CRT 的另一个用途是用一组比较小的质数表示一个大的整数。

例如，若 $a$ 满足如下线性方程组，且 $a < \prod_{i=1}^k p_i$（其中 $p_i$ 为质数）：

$$
\begin{cases}
a &\equiv a_1 \pmod {p_1} \\
a &\equiv a_2 \pmod {p_2} \\
  &\vdots \\
a &\equiv a_k \pmod {p_k} \\
\end{cases}
$$

我们可以用以下形式的式子（称作 $a$ 的混合基数表示）表示 $a$：

$$
a = x_1 + x_2 p_1 + x_3 p_1 p_2 + \ldots + x_k p_1 \ldots p_{k-1}
$$

**Garner 算法** 将用来计算系数 $x_1, \ldots, x_k$。

令 $r_{ij}$ 为 $p_i$ 在模 $p_j$ 意义下的 [逆](./inverse.md)：

$$
p_i \cdot r_{i,j} \equiv 1 \pmod{p_j}
$$

把 $a$ 代入我们得到的第一个方程：

$$
a_1 \equiv x_1 \pmod{p_1}
$$

代入第二个方程得出：

$$
a_2 \equiv x_1 + x_2 p_1 \pmod{p_2}
$$

方程两边减 $x_1$，除 $p_1$ 后得

$$
\begin{array}{rclr}
a_2 - x_1           &\equiv& x_2 p_1             &\pmod{p_2} \\
(a_2 - x_1) r_{1,2} &\equiv& x_2                 &\pmod{p_2} \\
x_2                 &\equiv& (a_2 - x_1) r_{1,2} &\pmod{p_2}
\end{array}
$$

类似地，我们可以得到：

$$
x_k=(...((a_k-x_1)r_{1,k}-x_2)r_{2,k})-...)r_{k-1,k} \bmod p_k
$$

??? note "参考代码"
    ```cpp
    for (int i = 0; i < k; ++i) {
      x[i] = a[i];
      for (int j = 0; j < i; ++j) {
        x[i] = r[j][i] * (x[i] - x[j]);
        x[i] = x[i] % p[i];
        if (x[i] < 0) x[i] += p[i];
      }
    }
    ```

该算法的时间复杂度为 $O(k^2)$。

## 应用

某些计数问题或数论问题出于加长代码、增加难度、或者是一些其他原因，给出的模数：**不是质数**！

但是对其质因数分解会发现它没有平方因子，也就是该模数是由一些不重复的质数相乘得到。

那么我们可以分别对这些模数进行计算，最后用 CRT 合并答案。

下面这道题就是一个不错的例子。

???+note "[洛谷 P2480 [SDOI2010]古代猪文](https://www.luogu.com.cn/problem/P2480)"
    给出 $G,n$（$1 \leq G,n \leq 10^9$），求：
    
    $$
    G^{\sum_{k\mid n}\binom{n}{k}} \bmod 999~911~659
    $$

首先，当 $G=999~911~659$ 时，所求显然为 $0$。

否则，根据 [欧拉定理](./fermat.md)，可知所求为：

$$
G^{\sum_{k\mid n}\binom{n}{k} \bmod 999~911~658} \bmod 999~911~659
$$

现在考虑如何计算：

$$
\sum_{k\mid n}\binom{n}{k} \bmod 999~911~658
$$

因为 $999~911~658$ 不是质数，无法保证 $\forall x \in [1,999~911~657]$，$x$ 都有逆元存在，上面这个式子我们无法直接计算。

注意到 $999~911~658=2 \times 3 \times 4679 \times 35617$，其中每个质因子的最高次数均为一，我们可以考虑分别求出 $\sum_{k\mid n}\binom{n}{k}$ 在模 $2$，$3$，$4679$，$35617$ 这几个质数下的结果，最后用中国剩余定理来合并答案。

也就是说，我们实际上要求下面一个线性方程组的解：

$$
\begin{cases}
x \equiv a_1 \pmod 2\\
x \equiv a_2 \pmod 3\\
x \equiv a_3 \pmod {4679}\\
x \equiv a_4 \pmod {35617}
\end{cases}
$$

而计算一个组合数对较小的质数取模后的结果，可以利用 [卢卡斯定理](./lucas.md)。

## 扩展：模数不互质的情况

### 两个方程

设两个方程分别是 $x\equiv a_1 \pmod {m_1}$、$x\equiv a_2 \pmod {m_2}$；

将它们转化为不定方程：$x=m_1p+a_1=m_2q+a_2$，其中 $p, q$ 是整数，则有 $m_1p-m_2q=a_2-a_1$。

由裴蜀定理，当 $a_2-a_1$ 不能被 $\gcd(m_1,m_2)$ 整除时，无解；

其他情况下，可以通过扩展欧几里得算法解出来一组可行解 $(p, q)$；

则原来的两方程组成的模方程组的解为 $x\equiv b\pmod M$，其中 $b=m_1p+a_1$，$M=\text{lcm}(m_1, m_2)$。

### 多个方程

用上面的方法两两合并即可。

## 习题

- [【模板】扩展中国剩余定理](https://www.luogu.com.cn/problem/P4777)
- [「NOI2018」屠龙勇士](https://uoj.ac/problem/396)
-   [「TJOI2009」猜数字](https://www.luogu.com.cn/problem/P3868)

    **本页面部分内容译自博文 [Китайская теорема об остатках](http://e-maxx.ru/algo/chinese_theorem) 与其英文翻译版 [Chinese Remainder Theorem](https://cp-algorithms.com/algebra/chinese-remainder-theorem.html)。其中俄文版版权协议为 Public Domain + Leave a Link；英文版版权协议为 CC-BY-SA 4.0。**
