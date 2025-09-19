## 引入

本页面列举了一些常见的动态规划（dynamic programming，DP）优化方法．所谓 DP 优化，是指许多动态规划问题虽然容易列出朴素的状态转移方程，但直接计算往往效率低下，因此需要借助一些技巧来降低时间复杂度．

这些方法彼此联系紧密，常常包含相似的思想，且往往需要结合多种技巧共同使用．因此，本文仅作粗略分类，侧重介绍一些最基本的思路．

## 利用常见技巧优化

许多动态规划问题的转移，可以通过常见的算法和数据结构进行优化．

这类技巧有两种常见的情形．第一种情形中，DP 问题有着如下状态转移方程：

$$
f(i) = F(a_i,\{f(j) : j < i\}).
$$

其中，当前状态 $f(i)$ 的计算依赖于当前的输入 $a_i$ 和之前整个序列的状态 $\{f(j):j < i\}$．因此，可以维护一个数据结构，将每次 $f(i)$ 的计算都看作是一次查询操作；而得到当前状态 $f(i)$ 后，可以再执行一次修改操作，更新该数据结构，用于后续的转移．

第二种情形中，DP 问题有着如下状态转移方程：

$$
f(i,\cdot) = F(a_i,f(i-1,\cdot)).
$$

其中，每个 $f(i,\cdot)$ 都是一个数组或其他较复杂的对象．因此，虽然 $f(i,\cdot)$ 只依赖于之前的单个状态，但是单次转移的复杂度很高，需要通过数据结构等技巧进行优化．

### 前缀和优化 DP

相关页面：[前缀和](../../basic/prefix-sum.md#前缀和)

如果当前状态的计算依赖于之前状态的子段和，那么，可以通过维护前缀和来加速计算．其中，一类涉及高维前缀和的问题也称为 [SOS DP](../../basic/prefix-sum.md#特例子集和-dp)．

习题：

-   [Luogu P2513 \[HAOI2009\] 逆序对数列](https://www.luogu.com.cn/problem/P2513)
-   [AtCoder Educational DP Contest M - Candies](https://atcoder.jp/contests/dp/tasks/dp_m)

### 单调队列/单调栈优化 DP

主页面：[单调队列/单调栈优化](./monotonous-queue-stack.md)

如果当前状态依赖于之前状态的区间最值等信息时，可以通过维护单调队列、单调栈来加速计算．

### 线段树/树状数组优化 DP

相关页面：[线段树](../../ds/seg.md)、[树状数组](../../ds/fenwick.md)

如果每次状态转移时，查询的都是某段区间上的和、最值等信息，或是单次修改操作涉及区间更新时，可以通过维护线段树、树状数组来加速计算．

习题：

-   [AtCoder Educational DP Contest Q - Flowers](https://atcoder.jp/contests/dp/tasks/dp_q)
-   [AtCoder Educational DP Contest W - Intervals](https://atcoder.jp/contests/dp/tasks/dp_w)
-   [Codeforces 115 E. Linear Kingdom Races](https://codeforces.com/problemset/problem/115/E)

### CDQ 分治优化 DP

主页面：[CDQ 分治优化 DP](../../misc/cdq-divide.md#cdq-分治优化-1d1d-动态规划的转移)

类似前文，将整个 DP 过程看作是一系列查询和修改操作．对于有些问题，顺次计算复杂度过高，可以将整个查询和修改过程离线，利用 CDQ 分治加速计算．

CDQ 分治优化 DP 也常见于下列各类问题中：

-   [基于 CDQ 分治的斜率优化 DP](./slope.md#二分cdq平衡树优化-dp)
-   [分治优化斜率单调性 DP](./quadrangle.md#分治)

### 倍增优化 DP

相关页面：[倍增](../../basic/binary-lifting.md)

有些问题中，需要将状态 $f(i)$ 设为从初始状态开始，进行了 $2^i$ 次转移时得到的结果．它利用了倍增的思想转化了原问题，因此常常称为倍增优化 DP．

有些时候，也会将状态转移方程类似

$$
f(i,j) = f(i-1,f(i-1,j))
$$

的 DP 问题称为倍增（优化）DP．

习题：

-   [Luogu P1081 \[NOIP 2012 提高组\] 开车旅行](https://www.luogu.com.cn/problem/P1081)
-   [Luogu P1613 跑路](https://www.luogu.com.cn/problem/P1613)
-   [Luogu P4739 \[CERC2017\] Donut Drone](https://www.luogu.com.cn/problem/P4739)

## 利用问题结构优化

许多动态规划问题具备如凸性、单调性等结构性质，合理利用这些性质可以快速求解．

### 斜率优化 DP

主页面：[斜率优化](./slope.md)

类似于上一节介绍的优化方法，利用问题的凸性，可以通过维护凸包加速单次转移．

### 四边形不等式优化 DP

主页面：[四边形不等式优化](./quadrangle.md)

涉及的函数满足四边形不等式的 DP 问题，往往满足某种决策单调性．利用这一特性，有很多专门的方法可以降低计算复杂度．常见的问题类型包括一维决策单调性问题、区间分拆问题、区间合并问题等．

### Slope Trick 优化 DP

主页面：[Slope Trick](./slope-trick.md)

有些问题中，状态函数的差分（即斜率）在状态转移过程中更容易维护．这种优化也往往需要问题具有凸性．

### WQS 二分/凸优化 DP

主页面：[WQS 二分](./wqs-binary-search.md)

对于带个数限制的最优化 DP 问题，如果不考虑个数限制时，问题更容易解决，且最优价值是关于该限制的凸函数，那么，可以通过 WQS 二分的方法简化计算．

## 利用数学方法优化

许多动态规划问题的转移，可以通过数学工具加速．

### 矩阵快速幂优化 DP

相关页面：[快速幂](../../math/binary-exponentiation.md)

如果 DP 问题的状态转移方程可以写作一个自治的形式

$$
f(i) = F(f(i-1)),
$$

也就是说，当前状态 $f(i)$ 只取决于前一个状态 $f(i-1)$，而不依赖于其他输入，那么，可以直接通过快速幂加速计算

$$
f(n) = F^n(f(0))
$$

获得最终答案．由于单次操作 $F$ 经常可以写作矩阵的形式，所以这一优化方法常称为矩阵快速幂优化 DP．实际上，任何满足结合律的变换（即任何 [幺半群](../../math/algebra/basic.md#群) 内的元素）都可以应用该方法加速．

习题：

-   [Luogu P1397 \[NOI2013\] 矩阵游戏](https://www.luogu.com.cn/problem/P1397)
-   [Luogu P3176 \[HAOI2015\] 数字串拆分](https://www.luogu.com.cn/problem/P3176)
-   [Codeforces 576 D. Flights for Regular Customers](https://codeforces.com/problemset/problem/576/D)
-   [Luogu P6772 \[NOI2020\] 美食家](https://www.luogu.com.cn/problem/P6772)

### FFT 优化 DP

相关页面：[FFT](../../math/poly/fft.md)

如果 DP 问题的状态转移方程是一个卷积的形式，那么，可以考虑用 FFT 加速转移．当然，根据具体的题目，也可能会用到其他多项式技术．

习题：

-   [Codeforces 553 E. Kyoya and Train](https://codeforces.com/contest/553/problem/E)
-   [Codeforces 1784 D. Wooden Spoon](https://codeforces.com/problemset/problem/1784/D)

### Lagrange 插值优化 DP

相关页面：[Lagrange 插值](../../math/numerical/interp.md#lagrange-插值法)

有些 DP 问题的状态函数 $f(i,j)$ 是关于 $j$ 的 $k$ 次多项式函数．此时，可以直接暴力计算它在 $k+1$ 个点处的取值，并通过 Lagrange 插值求出 $f(i,\cdot)$ 的表达式，进而优化转移甚至直接得到答案．

习题：

-   [Luogu P5223 Function](https://www.luogu.com.cn/problem/P5223)
-   [Luogu P4463 \[集训队互测 2012\] calc](https://www.luogu.com.cn/problem/P4463)
-   [Luogu P5469 \[NOI2019\] 机器人](https://www.luogu.com.cn/problem/P5469)

## 通过简化状态优化

除了优化转移外，还可以通过简化状态降低计算复杂度．

### DP 套 DP 与 DFA 最小化

主页面：[DP 套 DP](../dp-of-dp.md)、[DFA 最小化](../../misc/fsm.md#dfa-最小化)

一些 DP 问题的状态函数可以写成 $f(i,x)$ 的形式，但是 $x$ 自身的转移较为复杂，甚至可能依赖于另一个 DP 问题．对于这类问题，可以首先为状态 $x$ 的转移建立自动机，并通过 DFA 最小化的方法减少状态数量，再进行外层 DP．

### 状态设计优化 DP

主页面：[状态设计优化](./state.md)

有些特殊的问题可以通过巧妙的状态设计大幅减少状态数量．

## 拓展阅读

-   [DP 优化方法大杂烩 by Alex Wei](https://www.cnblogs.com/alex-wei/p/DP_Involution.html)
