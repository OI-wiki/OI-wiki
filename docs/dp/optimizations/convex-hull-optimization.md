## 斜率优化

??? note " 例题[「HNOI2008」玩具装箱 TOY](https://www.lydsy.com/JudgeOnline/problem.php?id=1010)"
	令 $f_i$ 表示前 $i$ 个物品，随意分组装在任意多个容器里所能得到的最小费用。

写出 **状态转移方程** ： $f_i=max\{f_j+(pre_i-pre_j+i-j-1-L)^2\}$ ，其中 $pre_i$ 表示前 $i$ 个数的前缀和。

换元试图简化状态转移方程式：令 $s_i=pre_i+i,L'=L+1$ ，则 $f_i=f_j+(s_i-s_j-L')^2$ ，展开，移项得

 $f_i=f_j+(s_i-s_j-L')^2$

 $f_i+2\times s_i\times (s_j+L')=f_j+s_i^2+(s_j+L')^2$

我们观察到，式子的右端的所有项都只和 $i$ 有关或只和 $j$ 有关，式子左端的第一项是我们要求的目标值，式子左端的其余项都同时和 $i$ 和 $j$ 有关。我们将这个式子看作一条直线的函数解析式，形如 $b+k\times x=y$ ，和上式一一对应。我们发现如果我们要最小化 $f_i$ ，也就是说要最小化这个直线的截距，而对于每个确定的 $i$ ，这个直线的斜率 $s_i$ 都是确定的。

![](../images/optimization.png)

如图，我们将这个斜率固定的直线从下往上平移，直到有一个点在这条直线上，然后将新的点加入点集，这样肯定能保证所有的直线的斜率都是单调递升的（因为如果新的直线斜率小于斜率最大的直线，那么其一定不成被选择成为新的决策），所以我们相当于维护了一个下凸包。（如果求的是 $\max$ 那么就要维护一个 **上凸包** 。这种东西要具体情况具体分析，如果直线的斜率不满足单调性，那就要维护整个凸包/二分等奇技淫巧。）

可以用单调队列维护下凸包。

### 几道练习题

[「SDOI2016」征途](https://www.lydsy.com/JudgeOnline/problem.php?id=4518)

[「ZJOI2007」仓库建设](https://www.lydsy.com/JudgeOnline/problem.php?id=1096)

[「APIO2010」特别行动队](https://www.lydsy.com/JudgeOnline/problem.php?id=1911)

[「BZOJ 4709」「JSOI2011」柠檬](https://www.lydsy.com/JudgeOnline/problem.php?id=4709)

[「Codeforces 311B」Cats Transport](http://codeforces.com/problemset/problem/311/B)

[「NOI2007」货币兑换](https://www.lydsy.com/JudgeOnline/problem.php?id=1492)
