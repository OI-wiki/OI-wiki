## 介绍

形如 $ax \equiv b \pmod c$ 的方程被称为**线性同余方程**(Congruence Equation)。

[\[NOIp 2012\]同余方程](https://www.luogu.org/problemnew/show/P1082)

## 求解方法

根据以下两个定理，我们可以求出同余方程 $ax \equiv b \pmod c$ 的解。

定理 1：

> 方程 $ax+by=c$ 与方程 $ax \equiv c \pmod b$ 是等价的，有整数解的充要条件为 $\gcd(a,b) \mid c$ 。

根据定理 1，方程 $ax+by=c$ ，我们可以先用扩展欧几里得算法求出一组 $x_0,y_0$ ，也就是 $ax_0+by_0=\gcd(a,b)$ ，然后两边同时除以 $\gcd(a,b)$ ，再乘 $c$ 。然后就得到了方程 $acx_0/\gcd(a,b)+bcy_0/\gcd(a,b)=c$ ，然后我们就找到了方程的一个解。

定理 2：

> 若 $\gcd(a,b)=1$ ，且 $x_0,y_0$ 为方程 $ax+by=c$ 的一组解，则该方程的任意解可表示为： $x=x_0+bt,y=y_0+at$ , 且对任意整数 $t$ 都成立。

根据定理 2，可以求出方程的所有解。但在实际问题中，我们往往被要求求出一个最小整数解，也就是一个特解 $x,t=b/\gcd(a,b),x=(x \mod t+t)\mod t$ 。

代码：

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
