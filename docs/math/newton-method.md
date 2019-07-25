本文介绍牛顿迭代法（Newton's method for finding roots）求解方程的近似解。牛顿在 1664 年发明了这个方法。具体的任务是，对于在 $[a,b]$ 上连续且单调的函数 $f(x)$ ，求 $f(x)=0$ 的近似解。

## 算法描述

初始时我们从给定的 $f(x)$ 和一个粗略的近似解 $x_0$ 开始。

假设我们目前的近似解是 $x_i$ ，那么为了得到更优的近似解，我们画出与 $f(x)$ 切于点 $(x_0,f(x_0))$ 的直线 $l$ ，将 $l$ 与 $x$ 轴的交点横坐标记为 $x_{i+1}$ 。并重复这个迭代的过程。

上述过程可以表示为以下递推式：

$$
 x_{i+1} = x_i - \frac{f(x_i)}{f^\prime(x_i)}
$$

直观地说，如果 $f(x)$ 比较平滑，那么随着迭代次数的增加， $x_i$ 会越来越逼近方程的解。

牛顿迭代法的收敛率是平方级别的，这意味着每次迭代后近似解的精确数位会翻倍。

## 求解平方根

我们尝试用牛顿迭代法求解平方根。设 $f(x)=x^2-n$ ，这个方程的近似解就是 $\sqrt{n}$ 的近似解。于是我们得到

$$
x_{i+1}=x_i-\frac{x_i^2-n}{2x_i}=\frac{x_i+\frac{n}{x_i}}{2}
$$

在实现的时候注意设置合适的精度。代码如下

```cpp
double sqrt_newton(double n) {
  const double eps = 1E-15;
  double x = 1;
  while (1) {
    double nx = (x + n / x) / 2;
    if (abs(x - nx) < eps) break;
    x = nx;
  }
  return x;
}
```

## 求解整数平方根

尽管我们可以调用 `sqrt()` 函数来获取平方根的值，但我们还是讲一下牛顿迭代法的变种算法，用于求解 $x^2\le n$ 的 $x$ 的最大整数解。我们仍然考虑一个类似于牛顿迭代的过程，但需要在边界条件上稍作修改。如果 $x$ 在迭代的过程中上一次迭代值得近似解变小，而这一次迭代使得近似解变大，那么我们就不进行这次迭代，退出循环。

```cpp
int isqrt_newton(int n) {
  int x = 1;
  bool decreased = false;
  for (;;) {
    int nx = (x + n / x) >> 1;
    if (x == nx || nx > x && decreased) break;
    decreased = nx < x;
    x = nx;
  }
  return x;
}
```

## 高精度平方根

最后考虑高精度的牛顿迭代法。迭代的方法是不变的，但这次我们需要关注初始时近似解的设置，即 $x_0$ 的值。由于需要应用高精度的数一般都非常大，因此不同的初始值对于算法效率的影响也很大。一个自然的想法就是考虑 $x_0=2^{\left\lfloor\frac{1}{2}\log_2n\right\rfloor}$ ，这样既可以快速计算出 $x_0$ ，又可以较为接近平方根的近似解。

给出 Java 代码的实现：

```java
public static BigInteger isqrtNewton(BigInteger n) {
	BigInteger a = BigInteger.ONE.shiftLeft(n.bitLength() / 2);
	boolean p_dec = false;
	for (;;) {
		BigInteger b = n.divide(a).add(a).shiftRight(1);
		if (a.compareTo(b) == 0 || a.compareTo(b) < 0 && p_dec)
			break;
		p_dec = a.compareTo(b) > 0;
		a = b;
	}
	return a;
}
```

实践效果：在 $n=10^{1000}$ 的时候该算法的运行时间是 $60\,ms$ ，如果我们不优化 $x_0$ 的值，直接从 $x_0=1$ 开始算，那么运行时间将达到 $120\,ms$ 。

## 习题

-   [UVa 10428 - The Roots](https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=16&page=show_problem&problem=1369)

     **本页面主要译自博文[Метод Ньютона (касательных) для поиска корней](http://e-maxx.ru/algo/roots_newton)与其英文翻译版[Newton's method for finding roots](https://cp-algorithms.com/num_methods/roots_newton.html)。其中俄文版版权协议为 Public Domain + Leave a Link；英文版版权协议为 CC-BY-SA 4.0。** 
