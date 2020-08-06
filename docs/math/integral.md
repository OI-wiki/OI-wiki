## 定积分的定义

简单来说，函数 $f(x)$ 在区间 $[l,r]$ 上的定积分 $\int_{l}^{r}f(x)\mathrm{d}x$ 指的是 $f(x)$ 在区间 $[l,r]$ 中与 $x$ 轴围成的区域的面积（其中 $x$ 轴上方的部分为正值， $x$ 轴下方的部分为负值）。

很多情况下，我们需要高效，准确地求出一个积分的近似值。下面介绍的 **辛普森法** ，就是这样一种求数值积分的方法。

## 辛普森法

这个方法的思想是将被积区间分为若干小段，每段套用二次函数的积分公式进行计算。

??? note "二次函数积分公式（辛普森公式）"
    对于一个二次函数 $f(x)=Ax^2+Bx+C$ ，有：
    
    $$
    \int_l^r f(x) {\mathrm d}x = \frac{(r-l)(f(l)+f(r)+4 f(\frac{l+r}{2}))}{6}
    $$
    
    推导过程：
    对于一个二次函数 $f(x)=Ax^2+Bx+C$ ；
    求积分可得 $F(x)=\int_0^x f(x) {\mathrm d}x = \frac{a}{3}x^3+\frac{b}{2}x^2+cx+D$ 在这里 D 是一个常数，那么
    
    $$
    \begin{aligned}
    \int_l^r f(x) {\mathrm d}x &= F(r)-F(l) \\
    &= \frac{a}{3}(r^3-l^3)+\frac{b}{2}(r^2-l^2)+c(r-l) \\
    &=(r-l)(\frac{a}{3}(l^2+r^2+lr)+\frac{b}{2}(l+r)+c) \\
    &=\frac{r-l}{6}(2al^2+2ar^2+2alr+3bl+3br+6c)\\
    &=\frac{r-l}{6}((al^2+bl+c)+(ar^2+br+c)+4(a(\frac{l+r}{2})^2+b(\frac{l+r}{2})+c)) \\
    &=\frac{r-l}{6}(f(l)+f(r)+4f(\frac{l+r}{2}))
    \end{aligned}
    $$

根据这个辛普森公式，我们先介绍一种普通的辛普森积分法。

### 普通辛普森法

1743 年，这种方法发表于托马斯·辛普森的一篇论文中。

#### 描述

给定一个自然数 $n$ ，将区间 $[l, r]$ 分成 $2n$ 个等长的区间 $x$ 。

 $x_i = l + i h, ~~ i = 0 \ldots 2n,$  $h = \frac {r-l} {2n}.$ 

我们就可以计算每个小区间 $[x_ {2i-2}, x_ {2i}]$ , $i = 1\ldots n$ 的积分值，将所有区间的积分值相加即为总积分。

对于 $[x_ {2i-2}, x_ {2i}]$ , $i = 1\ldots n$ 的一个区间，选其中的三个点 $(x_ {2i-2}, x_ {2i-1}, x_ {2i})$ 就可以构成一条抛物线从而得到一个函数 $P(x)$ ，这个函数存在且唯一。计算原函数在该区间的积分值就变成了计算新的二次函数 $P(x)$ 在该段区间的积分值。这样我们就可以利用辛普森公式来近似计算它。

 $\int_{x_ {2i-2}} ^ {x_ {2i}} f (x) ~dx \approx \int_{x_ {2i-2}} ^ {x_ {2i}} P (x) ~dx = \left(f(x_{2i-2}) + 4f(x_{2i-1})+(f(x_{2i})\right)\frac {h} {3}$ 

将其分段求和即可得到如下结论：

 $\int_l ^ r f (x) dx \approx \left(f (x_0) + 4 f (x_1) + 2 f (x_2) + 4f(x_3) + 2 f(x_4) + \ldots + 4 f(x_{2N-1}) + f(x_{2N}) \right)\frac {h} {3}$ 

#### 误差

我们直接给出结论，普通辛普森法的误差为：

$$
-\tfrac{1}{90} \left(\tfrac{r-l}{2}\right)^5 f^{(4)}(\xi)
$$

其中 $\xi$ 是位于区间 $[l,r]$ 的某个值。

#### 实现

```cpp
const int N = 1000 * 1000;

double simpson_integration(double a, double b) {
  double h = (b - a) / N;
  double s = f(a) + f(b);
  for (int i = 1; i <= N - 1; ++i) {
    double x = a + h * i;
    s += f(x) * ((i & 1) ? 4 : 2);
  }
  s *= h / 3;
  return s;
}
```

### 自适应辛普森法

普通的方法为保证精度在时间方面无疑会受到 $n$ 的限制，我们应该找一种更加合适的方法。

现在唯一的问题就是如何进行分段。如果段数少了计算误差就大，段数多了时间效率又会低。我们需要找到一个准确度和效率的平衡点。

我们这样考虑：假如有一段图像已经很接近二次函数的话，直接带入公式求积分，得到的值精度就很高了，不需要再继续分割这一段了。

于是我们有了这样一种分割方法：每次判断当前段和二次函数的相似程度，如果足够相似的话就直接代入公式计算，否则将当前段分割成左右两段递归求解。

现在就剩下一个问题了：如果判断每一段和二次函数是否相似？

我们把当前段直接代入公式求积分，再将当前段从中点分割成两段，把这两段再直接代入公式求积分。如果当前段的积分和分割成两段后的积分之和相差很小的话，就可以认为当前段和二次函数很相似了，不用再递归分割了。

上面就是自适应辛普森法的思想。

参考代码如下：

```cpp
double simpson(double l, double r) {
  double mid = (l + r) / 2;
  return (r - l) * (f(l) + 4 * f(mid) + f(r)) / 6;  // 辛普森公式
}
double asr(double l, double r, double eqs, double ans) {
  double mid = (l + r) / 2;
  double fl = simpson(l, mid), fr = simpson(mid, r);
  if (abs(fl + fr - ans) <= 15 * eqs)
    return fl + fr + (fl + fr - ans) / 15;  // 足够相似的话就直接返回
  return asr(l, mid, eqs / 2, fl) +
         asr(mid, r, eqs / 2, fr);  // 否则分割成两段递归求解
}
```

## 习题

-  [Luogu4525【模板】自适应辛普森法 1](https://www.luogu.com.cn/problem/P4525) 
-  [HDU1724 Ellipse](http://acm.hdu.edu.cn/showproblem.php?pid=1724) 
-  [NOI2005 月下柠檬树](https://www.luogu.com.cn/problem/P4207) 
