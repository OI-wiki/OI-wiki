## 定义

形如

$$
ax\equiv b\pmod n
$$

的方程称为 **线性同余方程**（Linear Congruence Equation）。其中，$a$、$b$ 和 $n$ 为给定整数，$x$ 为未知数。需要从区间 $[0, n-1]$ 中求解 $x$，当解不唯一时需要求出全体解。

## 用逆元求解

首先考虑简单的情况，当 $a$ 和 $n$ 互素（coprime 或 relatively prime）时，即 $\gcd(a, n) = 1$。

此时可以计算 $a$ 的逆元，并将方程的两边乘以 $a$ 的逆元，可以得到唯一解。

### 证明

$$
x\equiv ba ^ {- 1} \pmod n
$$

接下来考虑 $a$ 和 $n$ 不互素（not coprime），即 $\gcd(a, n) \ne 1$ 的情况。此时不一定有解。例如，$2x\equiv 1\pmod 4$ 没有解。

设 $g = \gcd(a, n)$，即 $a$ 和 $n$ 的最大公约数，其中 $a$ 和 $n$ 在本例中大于 1。

当 $b$ 不能被 $g$ 整除时无解。此时，对于任意的 $x$，方程 $ax\equiv b\pmod n$ 的左侧始终可被 $g$ 整除，而右侧不可被 $g$ 整除，因此无解。

如果 $g$ 整除 $b$，则通过将方程两边 $a$、$b$ 和 $n$ 除以 $g$，得到一个新的方程：

$$
a^{'}x\equiv b^{'} \pmod{n^{'}}
$$

其中 $a^{'}$ 和 $n^{'}$ 已经互素，这种情形已经解决，于是得到 $x^{'}$ 作为 $x$ 的解。

很明显，$x^{'}$ 也将是原始方程的解。这不是唯一的解。可以看出，原始方程有如下 $g$ 个解：

$$
x_i\equiv (x^{'} + i\cdot n^{'}) \pmod n \quad \text{for } i = 0 \ldots g-1
$$

总之，线性同余方程的 **解的数量** 等于 $g = \gcd(a, n)$ 或等于 $0$。

## 用扩展欧几里得算法求解

根据以下两个定理，可以求出线性同余方程 $ax\equiv b \pmod n$ 的解。

**定理 1**：线性同余方程 $ax\equiv b \pmod n$ 可以改写为如下线性不定方程：

$$
ax + nk = b
$$

其中 $x$ 和 $k$ 是未知数。这两个方程是等价的，有整数解的充要条件为 $\gcd(a,n) \mid b$。

应用扩展欧几里德算法可以求解该线性不定方程。根据定理 1，对于线性不定方程 $ax+nk=b$，可以先用扩展欧几里得算法求出一组 $x_0,k_0$，也就是 $ax_0+nk_0=\gcd(a,n)$，然后两边同时除以 $\gcd(a,n)$，再乘 $b$。就得到了方程

$$
a\dfrac{b}{\gcd(a,n)}x_0+n\dfrac{b}{\gcd(a,n)}k_0=b
$$

于是找到方程的一个解。

**定理 2**：若 $\gcd(a,n)=1$，且 $x_0$、$k_0$ 为方程 $ax+nk=b$ 的一组解，则该方程的任意解可表示为：

$$
x=x_0+nt
$$

$$
k=k_0-at
$$

并且对任意整数 $t$ 都成立。

根据定理 2，可以从已求出的一个解，求出方程的所有解。实际问题中，往往要求出一个最小整数解，也就是一个特解

$$
x=(x \bmod t+t) \bmod t
$$

其中有

$$
t=\dfrac{n}{\gcd(a,n)}
$$

如果仔细考虑，用扩展欧几里得算法求解与用逆元求解，两种方法是等价的。

### 实现

???+ note "代码实现"
    === "C++"
        ```cpp
        int ex_gcd(int a, int b, int& x, int& y) {
          if (b == 0) {
            x = 1;
            y = 0;
            return a;
          }
          int d = ex_gcd(b, a % b, x, y);
          int temp = x;
          x = y;
          y = temp - a / b * y;
          return d;
        }
        
        bool liEu(int a, int b, int c, int& x, int& y) {
          int d = ex_gcd(a, b, x, y);
          if (c % d != 0) return 0;
          int k = c / d;
          x *= k;
          y *= k;
          return 1;
        }
        ```
    
    === "Python"
        ```python
        def ex_gcd(a, b, x, y):
            if b == 0:
                x = 1
                y = 0
                return a
            d = ex_gcd(b, a % b, x, y)
            temp = x
            x = y
            y = temp - a // b * y
            return d
        
        
        def liEu(a, b, c, x, y):
            d = ex_gcd(a, b, x, y)
            if c % d != 0:
                return 0
            k = c // d
            x = x * k
            y = y * k
            return 1
        ```

**本页面主要译自博文 [Модульное линейное уравнение первого порядка](http://e-maxx.ru/algo/diofant_1_equation) 与其英文翻译版 [Linear Congruence Equation](https://cp-algorithms.com/algebra/linear_congruence_equation.html)。其中俄文版版权协议为 Public Domain + Leave a Link；英文版版权协议为 CC-BY-SA 4.0。**

### 习题

[「NOIP2012」同余方程](https://loj.ac/problem/2605)
