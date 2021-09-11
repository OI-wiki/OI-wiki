### 数论分块

数论分块可以在 $O{\sqrt{n}}$ 的时间里计算一些有除法下取整的和式。

它主要利用了富比尼定理（Fubini's theorem），将 $n/d$ 相同的数打包同时计算。

???+note "富比尼定理"
    又称“算两次”，以意大利数学家圭多·富比尼（Guido Fubini）命名。
    富比尼定理的积分形式：只要二重积分 $\int\int |f(x,y)|dxdy$ 有界，则可以逐次计算二重积分，并且可以交换逐次积分的顺序。
    积分号也是特殊的求和号，因此在一般求和中，富比尼定理往往呈现为更换计数顺序，即交换两个求和号。
    组合数学中的富比尼定理表现为，用两种不同的方法计算同一个量，从而建立相等关系。

例如这里的双曲线下整点的图片：

![双曲线下整点](./images/sqrt-decomposition.png)

图中共分为了 $5$ 块，这 $5$ 块整点的最大纵坐标都相同。如果统计整点的个数，可以从纵向计数改为横向计数，直接计算 $5$ 个矩形即可。

### 引理 1

$$
\forall a,b,c\in\mathbb{Z},\left\lfloor\frac{a}{bc}\right\rfloor=\left\lfloor\frac{\left\lfloor\frac{a}{b}\right\rfloor}{c}\right\rfloor
$$

略证：

$$
\begin{aligned}
&\frac{a}{b}=\left\lfloor\frac{a}{b}\right\rfloor+r(0\leq r<1)\\
\implies
&\left\lfloor\frac{a}{bc}\right\rfloor
=\left\lfloor\frac{a}{b}\cdot\frac{1}{c}\right\rfloor
=\left\lfloor \frac{1}{c}\left(\left\lfloor\frac{a}{b}\right\rfloor+r\right)\right\rfloor
=\left\lfloor \frac{\left\lfloor\frac{a}{b}\right\rfloor}{c} +\frac{r}{c}\right\rfloor
=\left\lfloor \frac{\left\lfloor\frac{a}{b}\right\rfloor}{c}\right\rfloor\\
&&\square
\end{aligned}
$$

??? note "关于证明最后的小方块"
    QED 是拉丁词组“Quod Erat Demonstrandum”（这就是所要证明的）的缩写，代表证明完毕。现在的 QED 符号通常是 $\blacksquare$ 或者 $\square$。（[维基百科](https://en.wikipedia.org/wiki/Q.E.D.)）

### 引理 2

$$
\forall n \in \mathbb{N}_{+},  \left|\left\{ \lfloor \frac{n}{d} \rfloor \mid d \in \mathbb{N}_{+},d\leq n \right\}\right| \leq \lfloor 2\sqrt{n} \rfloor
$$

$|V|$ 表示集合 $V$ 的元素个数

略证：

对于 $d\leq \left\lfloor\sqrt{n}\right\rfloor$，$\left\lfloor\frac{n}{d}\right\rfloor$ 有 $\left\lfloor\sqrt{n}\right\rfloor$ 种取值

对于 $d> \left\lfloor\sqrt{n}\right\rfloor$，有 $\left\lfloor\frac{n}{d}\right\rfloor\leq\left\lfloor\sqrt{n}\right\rfloor$，也只有 $\left\lfloor\sqrt{n}\right\rfloor$ 种取值

综上，得证

## 具体过程

数论分块的过程大概如下：考虑含有 $\left\lfloor\frac{n}{i}\right\rfloor$ 的求和式子（$n$ 为常数）

对于任意一个 $i(i\leq n)$，我们需要找到一个最大的 $j(i\leq j\leq n)$，使得 $\left\lfloor\frac{n}{i}\right\rfloor = \left\lfloor\frac{n}{j}\right\rfloor$.

此时 $j=\left\lfloor\frac{n}{\left\lfloor\frac{n}{i}\right\rfloor}\right\rfloor$.

显然 $j\leq n$，考虑证明 $j\geq i$：

$$
\begin{aligned}
&\left\lfloor\frac{n}{i}\right\rfloor \leq \frac{n}{i}\\
\implies
&\left\lfloor\frac{n}{ \left\lfloor\frac{n}{i}\right\rfloor }\right\rfloor
\geq \left\lfloor\frac{n}{ \frac{n}{i} }\right\rfloor
= \left\lfloor i \right\rfloor=i \\
\implies
&i\leq \left\lfloor\frac{n}{ \left\lfloor\frac{n}{i}\right\rfloor }\right\rfloor=j\\
&&\square
\end{aligned}
$$

不妨设 $k=\left\lfloor\frac{n}{i}\right\rfloor$，考虑证明当 $\left\lfloor\frac{n}{j}\right\rfloor=k$ 时，$j$ 的最大值为 $\left\lfloor\frac{n}{k}\right\rfloor$：

$$
\left\lfloor\frac{n}{j}\right\rfloor=k
\iff
k\leq\frac{n}{j}<k+1
\iff
\frac{1}{k+1}<\frac{j}{n}\leq\frac{1}{k}
\iff
\frac{n}{k+1}<j\leq\frac{n}{k}
$$

又因为 $j$ 为整数 所以 $j_{max}=\left\lfloor\frac{n}{k}\right\rfloor$

利用上述结论，我们每次以 $[i,j]$ 为一块，分块求和即可

例如 [「luogu P2261」\[CQOI2007\]余数求和](https://www.luogu.com.cn/problem/P2261),$ans=\sum_{i=1}^n(k\bmod i)=\sum_{i=1}^nk-i\left\lfloor\frac{k}{i}\right\rfloor$.

??? note "代码实现"
    ```cpp
    long long ans = n * k;
    for (long long l = 1, r; l <= n;
         l = r + 1) {  //此处l意同i,r意同j,下个计算区间的l应为上个区间的r+1
      if (k / l != 0)
        r = min(k / (k / l), n);
      else
        r = n;  // l大于k时
      ans -= (k / l) * (r - l + 1) * (l + r) /
             2;  //这个区间内k/i均相等,对i求和是等差数列求和
    }
    ```

???+note "二维数论分块"
    求
    
    $$
    \sum_{i=1}^{\min (n,m)}\left\lfloor\frac{n}{i}    \right\rfloor\left\lfloor\frac{m}{i}    \right\rfloor
    $$
    
    此时可将代码中 `r = n/(n/i)` 替换成 `r = min(n/(n/i), m/(m/i))`

* * *
