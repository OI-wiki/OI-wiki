author: sshwy, FFjet

类欧几里德算法由洪华敦在 2016 年冬令营营员交流中提出的内容，其本质可以理解为，使用一个类似辗转相除法来做函数求和的过程。

## 引入

设

$$
f(a,b,c,n)=\sum_{i=0}^n\left\lfloor \frac{ai+b}{c} \right\rfloor
$$

其中 $a,b,c,n$ 是常数。需要一个 $O(\log n)$ 的算法。

这个式子和我们以前见过的式子都长得不太一样。带向下取整的式子容易让人想到数论分块，然而数论分块似乎不适用于这个求和。但是我们是可以做一些预处理的。

如果说 $a\ge c$ 或者 $b\ge c$ ，意味着可以将 $a,b$ 对 $c$ 取模以简化问题：

$$
\begin{split}
f(a,b,c,n)&=\sum_{i=0}^n\left\lfloor \frac{ai+b}{c} \right\rfloor\\
&=\sum_{i=0}^n\left\lfloor
\frac{\left(\left\lfloor\frac{a}{c}\right\rfloor c+a\bmod c\right)i+\left(\left\lfloor\frac{b}{c}\right\rfloor c+b\bmod c\right)}{c}\right\rfloor\\
&=\frac{n(n+1)}{2}\left\lfloor\frac{a}{c}\right\rfloor+(n+1)\left\lfloor\frac{b}{c}\right\rfloor+
\sum_{i=0}^n\left\lfloor\frac{\left(a\bmod c\right)i+\left(b\bmod c\right)}{c}
\right\rfloor\\
&=\frac{n(n+1)}{2}\left\lfloor\frac{a}{c}\right\rfloor
+(n+1)\left\lfloor\frac{b}{c}\right\rfloor+f(a\bmod c,b\bmod c,c,n)
\end{split}
$$

那么问题转化为了 $a<c,b<c$ 的情况。观察式子，你发现只有 $i$ 这一个变量。因此要推就只能从 $i$ 下手。在推求和式子中有一个常见的技巧，就是条件与贡献的放缩与转化。具体地说，在原式 $\displaystyle f(a,b,c,n)=\sum_{i=0}^n\left\lfloor \frac{ai+b}{c} \right\rfloor$ 中， $0\le i\le n$ 是条件，而 $\left\lfloor \dfrac{ai+b}{c} \right\rfloor$ 是对总和的贡献。

要加快一个和式的计算过程，所有的方法都可以归约为 **贡献合并计算** 。但你发现这个式子的贡献难以合并，怎么办？ **将贡献与条件做转化** 得到另一个形式的和式。具体地，我们直接把原式的贡献变成条件：

$$
\sum_{i=0}^n\left\lfloor \frac{ai+b}{c} \right\rfloor
=\sum_{i=0}^n\sum_{j=0}^{\left\lfloor \frac{ai+b}{c} \right\rfloor-1}1\\
$$

现在多了一个变量 $j$ ，既然算 $i$ 的贡献不方便，我们就想办法算 $j$ 的贡献。因此想办法搞一个和 $j$ 有关的贡献式。这里有另一个家喻户晓的变换方法，笔者概括为限制转移。具体来说，在上面的和式中 $n$ 限制 $i$ 的上界，而 $i$ 限制 $j$ 的上界。为了搞 $j$ ，就先把 j 放到贡献的式子里，于是我们~~神仙地~~交换一下 $i,j$ 的求和算子，强制用 $n$ 限制 $j$ 的上界。

$$
\begin{split}
&=\sum_{j=0}^{\left\lfloor \frac{an+b}{c} \right\rfloor-1}
\sum_{i=0}^n\left[j<\left\lfloor \frac{ai+b}{c} \right\rfloor\right]\\
\end{split}
$$

这样做的目的是让 $j$ 摆脱 $i$ 的限制，现在 $i,j$ 都被 $n$ 限制，而贡献式看上去是一个条件，但是我们仍把它叫作贡献式，再对贡献式做变换后就可以改变 $i,j$ 的限制关系。于是我们做一些放缩的处理。首先把向下取整的符号拿掉

$$
j<\left\lfloor \frac{ai+b}{c} \right\rfloor
\Leftrightarrow j+1\leq \left\lfloor \frac{ai+b}{c} \right\rfloor
\Leftrightarrow j+1\leq \frac{ai+b}{c}\\
$$

然后可以做一些变换

$$
j+1\leq \frac{ai+b}{c} \Leftrightarrow jc+c\le ai+b \Leftrightarrow jc+c-b-1< ai
$$

最后一步，向下取整得到：

$$
jc+c-b-1< ai\Leftrightarrow \left\lfloor\frac{jc+c-b-1}{a}\right\rfloor< i
$$

这一步的重要意义在于，我们可以把变量 $i$ 消掉了！具体地，令 $m=\left\lfloor \frac{an+b}{c} \right\rfloor$ ，那么原式化为

$$
\begin{split}
f(a,b,c,n)&=\sum_{j=0}^{m-1}
\sum_{i=0}^n\left[i>\left\lfloor\frac{jc+c-b-1}{a}\right\rfloor \right]\\
&=\sum_{j=0}^{m-1}
n-\left\lfloor\frac{jc+c-b-1}{a}\right\rfloor\\
&=nm-f\left(c,c-b-1,a,m-1\right)
\end{split}
$$

这是一个递归的式子。并且你发现 $a,c$ 分子分母换了位置，又可以重复上述过程。先取模，再递归。这就是一个辗转相除的过程，这也是类欧几里德算法的得名。

容易发现时间复杂度为 $O(\log n)$ 。

## 扩展

理解了最基础的类欧几里德算法，我们再来思考以下两个变种求和式：

$$
g(a,b,c,n)=\sum_{i=0}^ni\left\lfloor \frac{ai+b}{c} \right\rfloor\\
h(a,b,c,n)=\sum_{i=0}^n\left\lfloor \frac{ai+b}{c} \right\rfloor^2
$$

### 推导 g

我们先考虑 $g$ ，类似地，首先取模：

$$
g(a,b,c,n)
=g(a\bmod c,b\bmod c,c,n)+\left\lfloor\frac{a}{c}\right\rfloor\frac{n(n+1)(2n+1)}{6}+\left\lfloor\frac{b}{c}\right\rfloor\frac{n(n+1)}{2}
$$

接下来考虑 $a<c,b<c$ 的情况，令 $m=\left\lfloor\frac{an+b}{c}\right\rfloor$ 。之后的过程我会写得很简略，因为方法和上文略同：

$$
\begin{split}
&g(a,b,c,n)=\sum_{i=0}^ni\left\lfloor \frac{ai+b}{c} \right\rfloor\\
&=\sum_{j=0}^{m-1}
\sum_{i=0}^n\left[j<\left\lfloor\frac{ai+b}{c}\right\rfloor\right]\cdot i
\end{split}
$$

这时我们设 $t=\left\lfloor\frac{jc+c-b-1}{a}\right\rfloor$ ，可以得到

$$
\begin{split}
&=\sum_{j=0}^{m-1}\sum_{i=0}^n[i>t]\cdot i\\
&=\sum_{j=0}^{m-1}\frac{1}{2}(t+n+1)(n-t)\\
&=\frac{1}{2}\left[mn(n+1)-\sum_{j=0}^{m-1}t^2-\sum_{j=0}^{m-1}t\right]\\
&=\frac{1}{2}[mn(n+1)-h(c,c-b-1,a,m-1)-f(c,c-b-1,a,m-1)]
\end{split}
$$

### 推导 h

同样的，首先取模：

$$
\begin{split}
h(a,b,c,n)&=h(a\bmod c,b\bmod c,c,n)\\
&+2\left\lfloor\frac{b}{c}\right\rfloor f(a\bmod c,b\bmod c,c,n)
+2\left\lfloor\frac{a}{c}\right\rfloor g(a\bmod c,b\bmod c,c,n)\\
&+\left\lfloor\frac{a}{c}\right\rfloor^2\frac{n(n+1)(2n+1)}{6}+\left\lfloor\frac{b}{c}\right\rfloor^2(n+1)
+\left\lfloor\frac{a}{c}\right\rfloor\left\lfloor\frac{b}{c}\right\rfloor n(n+1)
\end{split}
$$

考虑 $a<c,b<c$ 的情况， $m=\left\lfloor\dfrac{an+b}{c}\right\rfloor, t=\left\lfloor\dfrac{jc+c-b-1}{a}\right\rfloor$ .

我们发现这个平方不太好处理，于是可以这样把它拆成两部分：

$$
n^2=2\dfrac{n(n+1)}{2}-n=\left(2\sum_{i=0}^ni\right)-n
$$

这样做的意义在于，添加变量 $j$ 的时侯就只会变成一个求和算子，不会出现 $\sum\times \sum$ 的形式：

$$
\begin{split}
&h(a,b,c,n)=\sum_{i=0}^n\left\lfloor \frac{ai+b}{c} \right\rfloor^2
=\sum_{i=0}^n\left[\left(2\sum_{j=1}^{\left\lfloor \frac{ai+b}{c} \right\rfloor}j \right)-\left\lfloor\frac{ai+b}{c}\right\rfloor\right]\\
=&\left(2\sum_{i=0}^n\sum_{j=1}^{\left\lfloor \frac{ai+b}{c} \right\rfloor}j\right) -f(a,b,c,n)\\
\end{split}
$$

接下来考虑化简前一部分：

$$
\begin{split}
&\sum_{i=0}^n\sum_{j=1}^{\left\lfloor \frac{ai+b}{c} \right\rfloor}j\\
=&\sum_{i=0}^n\sum_{j=0}^{\left\lfloor \frac{ai+b}{c} \right\rfloor-1}(j+1)\\
=&\sum_{j=0}^{m-1}(j+1)
\sum_{i=0}^n\left[j<\left\lfloor \frac{ai+b}{c} \right\rfloor\right]\\
=&\sum_{j=0}^{m-1}(j+1)\sum_{i=0}^n[i>t]\\
=&\sum_{j=0}^{m-1}(j+1)(n-t)\\
=&\frac{1}{2}nm(m+1)-\sum_{j=0}^{m-1}(j+1)\left\lfloor \frac{jc+c-b-1}{a} \right\rfloor\\
=&\frac{1}{2}nm(m+1)-g(c,c-b-1,a,m-1)-f(c,c-b-1,a,m-1)
\end{split}
$$

因此

$$
h(a,b,c,n)=nm(m+1)-2g(c,c-b-1,a,m-1)-2f(c,c-b-1,a,m-1)-f(a,b,c,n)
$$

## 模板与实现

在计算的时侯，因为 $3$ 个函数各有交错递归，因此可以考虑三个一起整体递归，同步计算，否则有很多项会被多次计算。这样实现的复杂度是 $O(\log n)$ 的。

模板： [luogu5170](https://www.luogu.org/problemnew/show/P5170) 

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int P = 998244353;
int i2 = 499122177, i6 = 166374059;
struct data {
  data() { f = g = h = 0; }
  int f, g, h;
};  // 三个函数打包
data calc(int n, int a, int b, int c) {
  int ac = a / c, bc = b / c, m = (a * n + b) / c, n1 = n + 1, n21 = n * 2 + 1;
  data d;
  if (a == 0)  // 迭代到最底层
  {
    d.f = bc * n1 % P;
    d.g = bc * n % P * n1 % P * i2 % P;
    d.h = bc * bc % P * n1 % P;
    return d;
  }
  if (a >= c || b >= c)  // 取模
  {
    d.f = n * n1 % P * i2 % P * ac % P + bc * n1 % P;
    d.g = ac * n % P * n1 % P * n21 % P * i6 % P + bc * n % P * n1 % P * i2 % P;
    d.h = ac * ac % P * n % P * n1 % P * n21 % P * i6 % P +
          bc * bc % P * n1 % P + ac * bc % P * n % P * n1 % P;
    d.f %= P, d.g %= P, d.h %= P;

    data e = calc(n, a % c, b % c, c);  // 迭代

    d.h += e.h + 2 * bc % P * e.f % P + 2 * ac % P * e.g % P;
    d.g += e.g, d.f += e.f;
    d.f %= P, d.g %= P, d.h %= P;
    return d;
  }
  data e = calc(m - 1, c, c - b - 1, a);
  d.f = n * m % P - e.f, d.f = (d.f % P + P) % P;
  d.g = m * n % P * n1 % P - e.h - e.f, d.g = (d.g * i2 % P + P) % P;
  d.h = n * m % P * (m + 1) % P - 2 * e.g - 2 * e.f - d.f;
  d.h = (d.h % P + P) % P;
  return d;
}
int T, n, a, b, c;
signed main() {
  scanf("%lld", &T);
  while (T--) {
    scanf("%lld%lld%lld%lld", &n, &a, &b, &c);
    data ans = calc(n, a, b, c);
    printf("%lld %lld %lld\n", ans.f, ans.h, ans.g);
  }
  return 0;
}
```
