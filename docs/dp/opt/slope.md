author: TrisolarisHD, hsfzLZH1, abc1763613206, greyqz, Ir1d, billchenchina, Chrogeek, Enter-tainer, StudyingFather, MrFoodinChina, luoguyuntianming, sshwy

## 例题选讲

???+note " 例题[「HNOI2008」玩具装箱 TOY](https://loj.ac/problem/10188)"
    有 $n$ 个玩具，第 $i$ 个玩具价值为 $c_i$ 。要求将这 $n$ 个玩具排成一排，分成若干段。对于一段 $[l,r]$ ，它的代价为 $(r-l+\sum_{i=L}^R c_i-L)^2$ 。求分段的最小代价。
    
     $1\le n\le 5\times 10^4,1\le L,c_i\le 10^7$ 。

令 $f_i$ 表示前 $i$ 个物品，分若干段的最小代价。

状态转移方程： $f_i=\min_{j<i}\{f_j+(pre_i-pre_j+i-j-1-L)^2\}$ 。

其中 $pre_i$ 表示前 $i$ 个数的前缀和。

简化状态转移方程式：令 $s_i=pre_i+i,L'=L+1$ ，则 $f_i=\min_{j<i}\{f_j+(s_i-s_j-L')^2\}$ 。

将与 $j$ 无关的移到外面，我们得到

$$
f_i - (s_i-L')^2=\min_{j<i}\{f_j+s_j^2 + 2s_j(s_i-L') \} 
$$

考虑一次函数的斜截式 $y=kx+b$ ，将其移项得到 $b=y-kx$ 。我们将与 $j$ 有关的信息表示为 $y$ 的形式，把同时与 $i,j$ 有关的信息表示为 $kx$ ，把要最小化的信息（与 $i$ 有关的信息）表示为 $b$ ，也就是截距。具体地，设

$$
\begin{aligned}
x_j&=s_j\\
y_j&=f_j+s_j^2\\
k_i&=-2(s_i-L')\\
b_i&=f_i-(s_i-L')^2\\
\end{aligned}
$$

则转移方程就写作 $b_i = \min_{j<i}\{ y_j-k_ix_j \}$ 。我们把 $(x_j,y_j)$ 看作二维平面上的点，则 $k_i$ 表示直线斜率， $b_i$ 表示一条过 $(x_j,y_j)$ 的斜率为 $k_i$ 的直线的截距。问题转化为了，选择合适的 $j$ （ $1\le j<i$ ），最小化直线的截距。

![](../images/optimization.svg)

如图，我们将这个斜率为 $k_i$ 的直线从下往上平移，直到有一个点 $(x_p,y_p)$ 在这条直线上，则有 $b_i=y_p-k_ix_p$ ，这时 $b_i$ 取到最小值。算完 $f_i$ ，我们就把 $(x_i,y_i)$ 这个点加入点集中，以做为新的 DP 决策。那么，我们该如何维护点集？

容易发现，可能让 $b_i$ 取到最小值的点一定在下凸壳上。因此在寻找 $p$ 的时候我们不需要枚举所有 $i-1$ 个点，只需要考虑凸包上的点。而在本题中 $k_i$ 随 $i$ 的增加而递减，因此我们可以单调队列维护凸包。

具体地，设 $K(a,b)$ 表示过 $(x_a,y_a)$ 和 $(x_b,y_b)$ 的直线的斜率。考虑队列 $q_l,q_{l+1},\ldots,q_r$ ，维护的是下凸壳上的点。也就是说，对于 $l<i<r$ ，始终有 $K(q_{i-1},q_i) < K(q_i,q_{i+1})$ 成立。

我们维护一个指针 $e$ 来计算 $b_i$ 最小值。我们需要找到一个 $K(q_{e-1},q_e)\le k_i< K(q_e,q_{e+1})$ 的 $e$ （特别地，当 $e=l$ 或者 $e=r$ 时要特别判断），这时就有 $p=q_e$ ，即 $q_e$ 是 $i$ 的最优决策点。由于 $k_i$ 是单调递减的，因此 $e$ 的移动次数是均摊 $O(1)$ 的。

在插入一个点 $(x_i,y_i)$ 时，我们要判断是否 $K(q_{r-1},q_r)<K(q_r,i)$ ，如果不等式不成立就将 $q_r$ 弹出，直到等式满足。然后将 $i$ 插入到 $q$ 队尾。

这样我们就将 DP 的复杂度优化到了 $O(n)$ 。

## 小结

斜率优化 DP 需要灵活运用，其宗旨是将最优化问题转化为二维平面上与凸包有关的截距最值问题。遇到性质不太好的方程，有时需要辅以数据结构来加以解决，届时还请就题而论。

## 习题

 [「SDOI2016」征途](https://loj.ac/problem/2035) 

 [「ZJOI2007」仓库建设](https://loj.ac/problem/10189) 

 [「APIO2010」特别行动队](https://loj.ac/problem/10190) 

 [「JSOI2011」柠檬](https://www.luogu.com.cn/problem/P5504) 

 [「Codeforces 311B」Cats Transport](http://codeforces.com/problemset/problem/311/B) 

 [「NOI2007」货币兑换](https://loj.ac/problem/2353) 

 [「NOI2019」回家路线](https://loj.ac/problem/3156) 

 [「NOI2016」国王饮水记](https://uoj.ac/problem/223) 

 [「NOI2014」购票](https://uoj.ac/problem/7) 
