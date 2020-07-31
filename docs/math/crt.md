## 「物不知数」问题

> 有物不知其数，三三数之剩二，五五数之剩三，七七数之剩二。问物几何？

即求满足以下条件的整数：除以 $3$ 余 $2$ ，除以 $5$ 余 $3$ ，除以 $7$ 余 $2$ 。

该问题最早见于《孙子算经》中，并有该问题的具体解法。宋朝数学家秦九韶于 1247 年《数书九章》卷一、二《大衍类》对「物不知数」问题做出了完整系统的解答。上面具体问题的解答口诀由明朝数学家程大位在《算法统宗》中给出：

> 三人同行七十希，五树梅花廿一支，七子团圆正半月，除百零五便得知。

 $2\times 70+3\times 21+2\times 15=233=2\times 105+23$ ，故答案为 $23$ 。

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

1. 计算所有模数的积 $n$ ；
2.  对于第 $i$ 个方程：
    1. 计算 $m_i=\frac{n}{n_i}$ ；
    2. 计算 $m_i$ 在模 $n_i$ 意义下的 [逆元](./inverse.md)  $m_i^{-1}$ ；
    3. 计算 $c_i=m_im_i^{-1}$ （ **不要对 $n_i$ 取模** ）。
3. 方程组的唯一解为： $a=\sum_{i=1}^k a_ic_i \pmod n$ 。

### 伪代码

```text
n ← 1
ans ← 0
for i = 1 to k
  n ← n * n[i]
for i = 1 to k
  m ← n / n[i]
  b ← inv(m, n[i])               // b * m mod n[i] = 1
  ans ← (ans + a[i] * m * b) mod n
return ans
```

## 算法的证明

我们需要证明上面算法计算所得的 $a$ 对于任意 $i=1,2,\cdots,k$ 满足 $a\equiv a_i \pmod {n_i}$ 。

当 $i\neq j$ 时，有 $m_j\equiv 0 \pmod {n_i}$ ，故 $c_j\equiv m_j\equiv 0 \pmod {n_i}$ 。又有 $c_i\equiv m_i(m_i^{-1}\bmod {n_i})\equiv 1 \pmod {n_i}$ ，所以我们有：

$$
\begin{aligned}
a&\equiv \sum_{j=1}^k a_jc_j        &\pmod {n_i} \\
 &\equiv a_ic_i                     &\pmod {n_i} \\
 &\equiv a_im_i(m^{-1}_i \bmod n_i) &\pmod {n_i} \\
 &\equiv a_i                        &\pmod {n_i}
\end{aligned}
$$

 **即对于任意 $i=1,2,\cdots,k$ ，上面算法得到的 $a$ 总是满足 $a\equiv a_i \pmod{n_i}$ ，即证明了解同余方程组的算法的正确性。** 

因为我们没有对输入的 $a_i$ 作特殊限制，所以任何一组输入 $\{a_i\}$ 都对应一个解 $a$ 。

另外，若 $x\neq y$ ，则总存在 $i$ 使得 $x$ 和 $y$ 在模 $n_i$ 下不同余。

 **故系数列表 $\{a_i\}$ 与解 $a$ 之间是一一映射关系，方程组总是有唯一解。** 

## 例

下面演示 CRT 如何解「物不知数」问题。

1.  $n=3\times 5\times 7=105$ ；
2. 三人同行 **七十** 希： $n_1=3, m_1=n/n_1=35, m_1^{-1}\equiv 2\pmod 3$ ，故 $c_1=35\times 2=70$ ；
3. 五树梅花 **廿一** 支： $n_2=5, m_2=n/n_2=21, m_2^{-1}\equiv 1\pmod 5$ ，故 $c_2=21\times 1=21$ ；
4. 七子团圆正 **半月** ： $n_3=7, m_3=n/n_3=15, m_3^{-1}\equiv 1\pmod 7$ ，故 $c_3=15\times 1=15$ ；
5. 所以方程组的唯一解为 $a\equiv 2\times 70+3\times 21+2\times 15\equiv 233\equiv 23 \pmod {105}$ 。（除 **百零五** 便得知）

## 应用

某些计数问题或数论问题出于加长代码、增加难度、或者是一些其他不可告人的原因，给出的模数： **不是质数** ！

但是对其质因数分解会发现它没有平方因子，也就是该模数是由一些不重复的质数相乘得到。

那么我们可以分别对这些模数进行计算，最后用 CRT 合并答案。

下面这道题就是一个不错的例子。

???+note "[洛谷 P2480 [SDOI2010]古代猪文](https://www.luogu.com.cn/problem/P2480)"
    给出 $G,n$ （ $1 \leq G,n \leq 10^9$ ），求：
    
    $$
    G^{\sum_{k\mid n}\binom{n}{k}} \bmod 999~911~659
    $$

首先，当 $G=999~911~659$ 时，所求显然为 $0$ 。

否则，根据 [欧拉定理](./fermat.md) ，可知所求为：

$$
G^{\sum_{k\mid n}\binom{n}{k} \bmod 999~911~658} \bmod 999~911~659
$$

现在考虑如何计算：

$$
\sum_{k\mid n}\binom{n}{k} \bmod 999~911~658
$$

因为 $999~911~658$ 不是质数，无法保证 $\forall x \in [1,999~911~657]$ ， $x$ 都有逆元存在，上面这个式子我们无法直接计算。

注意到 $999~911~658=2 \times 3 \times 4679 \times 35617$ ，其中每个质因子的最高次数均为一，我们可以考虑分别求出 $\sum_{k\mid n}\binom{n}{k}$ 在模 $2$ ， $3$ ， $4679$ ， $35617$ 这几个质数下的结果，最后用中国剩余定理来合并答案。

也就是说，我们实际上要求下面一个线性方程组的解：

$$
\begin{cases}
x \equiv a_1 \pmod 2\\
x \equiv a_2 \pmod 3\\
x \equiv a_3 \pmod {4679}\\
x \equiv a_4 \pmod {35617}
\end{cases}
$$

而计算一个组合数对较小的质数取模后的结果，可以利用 [卢卡斯定理](./lucas.md) 。

## 比较两 CRT 下整数

考虑 CRT, 不妨假设 $n_1\leq n_2 \leq ... \leq n_k$ 

$$
\begin{cases}
x &\equiv a_1 \pmod {n_1} \\
x &\equiv a_2 \pmod {n_2} \\
  &\vdots \\
x &\equiv a_k \pmod {n_k} \\
\end{cases}
$$

与 PMR(Primorial Mixed Radix) 表示

 $x=b_1+b_2n_1+b_3n_1n_2...+b_kn_1n_2...n_{k-1} ,b_i\in [0,n_i)$ 

将数字转化到 PMR 下，逐位比较即可

转化方法考虑依次对 PMR 取模

$$
\begin{aligned}
b_1&=a_1 \bmod n_1\\
b_2&=(a_2-b_1)c_{1,2} \bmod n_2\\
b_3&=((a_3-b_1')c_{1,3}-x_2')c_{2,3} \bmod n_3\\
&...\\
b_k&=(...((a_k-b_1)c_{1,k}-b_2)c_{2,k})-...)c_{k-1,k} \bmod n_k
\end{aligned}
$$

其中 $c_{i,j}$ 表示 $n_i$ 对 $n_j$ 的逆元， $c_{i,j}n_i \equiv 1 \pmod {n_j}$ 

## 扩展：模数不互质的情况

### 两个方程

设两个方程分别是 $x\equiv a_1 \pmod {m_1}$ 、 $x\equiv a_2 \pmod {m_2}$ ；

将它们转化为不定方程： $x=m_1p+a_1=m_2q+a_2$ ，其中 $p, q$ 是整数，则有 $m_1p-m_2q=a_2-a_1$ 。

由裴蜀定理，当 $a_2-a_1$ 不能被 $\gcd(m_1,m_2)$ 整除时，无解；

其他情况下，可以通过扩展欧几里得算法解出来一组可行解 $(p, q)$ ；

则原来的两方程组成的模方程组的解为 $x\equiv b\pmod M$ ，其中 $b=m_1p+a_1$ ， $M=\text{lcm}(m_1, m_2)$ 。

### 多个方程

用上面的方法两两合并就可以了……

 [【模板】扩展中国剩余定理](https://www.luogu.com.cn/problem/P4777) 

 [「NOI2018」屠龙勇士](https://uoj.ac/problem/396) 

 [「TJOI2009」猜数字](https://www.luogu.com.cn/problem/P3868) 
