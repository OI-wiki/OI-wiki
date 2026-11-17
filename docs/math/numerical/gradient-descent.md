author: terryduan-chn

本页面将介绍梯度下降法（gradient descent），讨论步长、光滑性与凸性对其收敛性的影响，并结合例题说明它在算法竞赛中的适用范围．

## 引入

算法竞赛中有一类连续优化问题：给定一个多元函数 $f:\mathbf{R}^n\to\mathbf{R}$，求它的最小值点．例如，平面上有若干带权的点，求一点使它到各点的带权距离之和最小．

如果 $f$ 只有一个自变量且是单峰函数，可以使用 [三分法](../../basic/binary.md#三分法)；如果能直接解出导数的零点，也可以直接求解．当自变量有多个、又没有简单的结构可以利用时，一个自然的想法是：从某个初始点出发，每次朝着函数值下降最快的方向走一小步，逐步逼近最小值点．这就是梯度下降法．

## 原理

### 梯度与下降方向

对于可微函数 $f(\boldsymbol{x})$，它在点 $\boldsymbol{x}$ 处的 **梯度**（gradient）是由各个偏导数组成的向量：

$$
\mathbf{\nabla} f(\boldsymbol{x})=\left(\frac{\partial f}{\partial x_1},\frac{\partial f}{\partial x_2},\cdots,\frac{\partial f}{\partial x_n}\right).
$$

在 $\boldsymbol{x}$ 附近，函数可以用一阶 Taylor 展开近似：

$$
f(\boldsymbol{x}+\boldsymbol{d})\approx f(\boldsymbol{x})+\mathbf{\nabla} f(\boldsymbol{x})\cdot\boldsymbol{d}.
$$

在长度 $\lvert\boldsymbol{d}\rvert$ 固定的前提下，由 Cauchy–Schwarz 不等式，$\mathbf{\nabla} f(\boldsymbol{x})\cdot\boldsymbol{d}\geq-\lvert\mathbf{\nabla} f(\boldsymbol{x})\rvert\lvert\boldsymbol{d}\rvert$，等号在 $\boldsymbol{d}$ 与 $-\mathbf{\nabla} f(\boldsymbol{x})$ 同向时成立．因此，**负梯度方向** 是函数值在局部下降最快的方向．也正因如此，梯度下降法又称为 **最速下降法**（steepest descent）．有些资料中，最速下降法特指每一步都沿负梯度方向做精确线搜索的版本．

### 过程

梯度下降法从初始点 $\boldsymbol{x}_0$ 出发，按照

$$
\boldsymbol{x}_{k+1}=\boldsymbol{x}_k-\eta\mathbf{\nabla} f(\boldsymbol{x}_k)
$$

迭代，其中 $\eta>0$ 称为 **步长**（step size），在机器学习中也常称为学习率．当梯度的长度足够小、相邻两次迭代的位置足够接近或者迭代次数达到上限时停止．

伪代码如下：

$$
\begin{array}{l}
\textbf{Algorithm}\operatorname{GradientDescent}(f,\boldsymbol{x}_0,\eta):\\
\textbf{Input. } \text{A differentiable function } f\text{, an initial point }\boldsymbol{x}_0\text{ and a step size }\eta.\\
\textbf{Output. } \text{An approximate stationary point of } f.\\
\textbf{Method. } \\
\begin{array}{ll}
1 & k\gets 0\\
2 & \textbf{while } \lvert\mathbf{\nabla} f(\boldsymbol{x}_k)\rvert>\varepsilon \textbf{ and } k<K\\
3 & \qquad \boldsymbol{x}_{k+1}\gets\boldsymbol{x}_k-\eta\mathbf{\nabla} f(\boldsymbol{x}_k)\\
4 & \qquad k\gets k+1\\
5 & \textbf{return } \boldsymbol{x}_k
\end{array}
\end{array}
$$

## 示例

考虑二元函数

$$
f(x,y)=x^2+4y^2,
$$

它的最小值点为 $(0,0)$．它的梯度为 $\mathbf{\nabla} f(x,y)=(2x,8y)$，因此迭代公式为

$$
x_{k+1}=(1-2\eta)x_k,\quad y_{k+1}=(1-8\eta)y_k.
$$

从 $(x_0,y_0)=(2,1)$ 出发，分别取 $\eta=0.05$，$\eta=0.2$，$\eta=0.3$，前几步的函数值如下：

| $k$ | $\eta=0.05$ | $\eta=0.2$ | $\eta=0.3$ |
| --- | ----------- | ---------- | ---------- |
| 0   | 8.0000      | 8.0000     | 8.0000     |
| 1   | 4.6800      | 2.8800     | 8.4800     |
| 2   | 3.1428      | 1.0368     | 15.4688    |
| 3   | 2.3124      | 0.3732     | 30.1345    |
| 4   | 1.7891      | 0.1344     | 59.0342    |
| 5   | 1.4189      | 0.0484     | 115.7023   |

三种步长表现出了不同的行为：

-   $\eta=0.05$ 时，$x$ 方向每步只缩小为原来的 $0.9$ 倍，函数值下降缓慢．
-   $\eta=0.2$ 时，两个方向每步都缩小为原来的 $0.6$ 倍（$y$ 的符号来回变化），函数值每步变为原来的 $0.36$ 倍．
-   $\eta=0.3$ 时，$\lvert 1-8\eta\rvert=1.4>1$，$y$ 方向来回振荡且振幅不断增大，迭代发散．

由迭代公式可知，迭代对任意初始点收敛当且仅当 $\lvert 1-2\eta\rvert<1$ 且 $\lvert 1-8\eta\rvert<1$，即 $0<\eta<\dfrac{1}{4}$．而 $\max(\lvert 1-2\eta\rvert,\lvert 1-8\eta\rvert)$ 在 $\eta=0.2$ 时取到最小值 $0.6$，所以 $\eta=0.2$ 是这个函数上最好的固定步长．这个例子说明：步长过小时收敛慢，步长过大时会振荡甚至发散；而且函数在不同方向上的弯曲程度相差越大，越难选出一个对所有方向都合适的步长．

??? note "参考代码"
    输入初始点、迭代次数和若干个步长，输出每一步的位置和函数值．
    
    ```cpp
    --8<-- "docs/math/code/numerical/gradient-descent/gradient-descent_1.cpp"
    ```

## 收敛性

上面的例子中可以直接写出迭代的通项．对一般的函数，梯度下降的表现取决于函数的光滑性与凸性，以及步长的选取．下文中，$f^*$ 表示 $f$ 的最小值，$\boldsymbol{x}^*$ 表示一个最小值点．

### 光滑性与步长

如果对任意 $\boldsymbol{x}$，$\boldsymbol{y}$，都有

$$
\lvert\mathbf{\nabla} f(\boldsymbol{x})-\mathbf{\nabla} f(\boldsymbol{y})\rvert\leq L\lvert\boldsymbol{x}-\boldsymbol{y}\rvert,
$$

就称 $f$ 是 $L$ 光滑（$L$-smooth）的．对于二阶可微的函数，这等价于 Hesse 矩阵的特征值的绝对值都不超过 $L$．直观地说，$L$ 刻画了函数最「弯」的方向上的弯曲程度．上例中 Hesse 矩阵为 $\operatorname{diag}(2,8)$，所以 $L=8$．

光滑性保证了函数不会在一步之内偏离一阶近似太远：

$$
f(\boldsymbol{y})\leq f(\boldsymbol{x})+\mathbf{\nabla} f(\boldsymbol{x})\cdot(\boldsymbol{y}-\boldsymbol{x})+\frac{L}{2}\lvert\boldsymbol{y}-\boldsymbol{x}\rvert^2.
$$

代入 $\boldsymbol{y}=\boldsymbol{x}_{k+1}=\boldsymbol{x}_k-\eta\mathbf{\nabla} f(\boldsymbol{x}_k)$，得到

$$
f(\boldsymbol{x}_{k+1})\leq f(\boldsymbol{x}_k)-\eta\left(1-\frac{L\eta}{2}\right)\lvert\mathbf{\nabla} f(\boldsymbol{x}_k)\rvert^2.
$$

因此，只要 $0<\eta<\dfrac{2}{L}$，函数值就会单调下降，直到梯度为零．上例中 $\dfrac{2}{L}=\dfrac{1}{4}$，恰好是收敛所需的步长上界．

这一结论并不要求 $f$ 是凸函数．取 $\eta=\dfrac{1}{L}$ 并对上式求和，若 $f$ 有下界，则

$$
\min_{0\leq k<K}\lvert\mathbf{\nabla} f(\boldsymbol{x}_k)\rvert^2\leq\frac{2L\left(f(\boldsymbol{x}_0)-\inf f\right)}{K}.
$$

但这只说明迭代点的梯度会变小，即迭代会逼近 **驻点**（梯度为零的点）．驻点可能是局部最小值点，也可能是鞍点．例如对 $f(x,y)=x^2-y^2$，从 $(1,0)$ 出发，$y$ 始终为 $0$，迭代收敛到鞍点 $(0,0)$．

### 凸性

如果 $f$ 是可微的凸函数，那么驻点就是全局最小值点，上面的结论可以加强为全局最优性的保证．设 $f$ 是 $L$ 光滑的凸函数，取 $\eta=\dfrac{1}{L}$，则[^nesterov]

$$
f(\boldsymbol{x}_k)-f^*\leq\frac{2L\lvert\boldsymbol{x}_0-\boldsymbol{x}^*\rvert^2}{k+4}.
$$

也就是说，函数值以 $O(1/k)$ 的速度收敛到最小值．这一结论只保证函数值接近最小值；如果最小值点不唯一，迭代点不一定靠近某个特定的最小值点．

### 强凸性

如果存在 $\mu>0$，使得对任意 $\boldsymbol{x}$，$\boldsymbol{y}$，都有

$$
f(\boldsymbol{y})\geq f(\boldsymbol{x})+\mathbf{\nabla} f(\boldsymbol{x})\cdot(\boldsymbol{y}-\boldsymbol{x})+\frac{\mu}{2}\lvert\boldsymbol{y}-\boldsymbol{x}\rvert^2,
$$

就称 $f$ 是 $\mu$ 强凸（$\mu$-strongly convex）的．此时最小值点唯一．设 $f$ 是 $L$ 光滑且 $\mu$ 强凸的函数，记 $\kappa=L/\mu$ 为它的条件数．取 $\eta=\dfrac{2}{\mu+L}$，则[^nesterov]

$$
\lvert\boldsymbol{x}_k-\boldsymbol{x}^*\rvert\leq\left(\frac{\kappa-1}{\kappa+1}\right)^k\lvert\boldsymbol{x}_0-\boldsymbol{x}^*\rvert.
$$

迭代点以几何级数的速度（线性收敛）趋近于最小值点，条件数越大，收敛越慢．上例中 $\mu=2$，$L=8$，$\kappa=4$，最优步长 $\dfrac{2}{\mu+L}=0.2$，收敛因子 $\dfrac{\kappa-1}{\kappa+1}=0.6$，与前文的计算一致．

### 小结

| 条件                  | 步长             | 结论                                     |
| --------------------- | ---------------- | ---------------------------------------- |
| $L$ 光滑              | $0<\eta<2/L$     | 函数值单调下降，梯度趋于零（逼近驻点）   |
| $L$ 光滑且凸          | $\eta=1/L$       | 函数值以 $O(1/k)$ 的速度收敛到全局最小值 |
| $L$ 光滑且 $\mu$ 强凸 | $\eta=2/(\mu+L)$ | 迭代点线性收敛到唯一的全局最小值点       |

???+ warning "注意"
    算法竞赛中的目标函数常常含有绝对值、最大值、距离等运算，在某些点不可导，也不满足 $L$ 光滑的条件．此时固定步长的梯度下降往往会在最优点附近来回振荡，需要逐渐减小步长，或者利用问题的结构设计专门的迭代方法．[爬山算法](../../misc/hill-climbing.md) 中逐渐降低的「温度」，就起到了逐渐减小步长的作用．

## 例题

???+ example "[「JSOI2004」平衡点/吊打 XXX](https://www.luogu.com.cn/problem/P1337)"
    桌面上有 $n$ 个洞，第 $i$ 个洞的坐标为 $(x_i,y_i)$．每个洞穿过一根绳子，绳子下端挂着重量为 $w_i$ 的重物，上端都系在同一个绳结上．忽略一切摩擦，且绳结不能穿过洞，求绳结最终平衡的位置．
    
    $1\leq n\leq 1000$，$-10000\leq x_i,y_i\leq 10000$，$0<w_i\leq 1000$，坐标与重量均为整数．保证平衡点唯一．输出保留三位小数．

### 建模

记第 $i$ 个洞的位置为 $\boldsymbol{a}_i$，绳结的位置为 $\boldsymbol{p}$．设第 $i$ 根绳子长为 $l_i$，它在桌面上的部分长为 $\lvert\boldsymbol{p}-\boldsymbol{a}_i\rvert$，所以第 $i$ 个重物位于桌面下方 $l_i-\lvert\boldsymbol{p}-\boldsymbol{a}_i\rvert$ 处，它的重力势能等于 $w_i\lvert\boldsymbol{p}-\boldsymbol{a}_i\rvert$ 加上一个与 $\boldsymbol{p}$ 无关的常数（取重力加速度为 $1$）．系统平衡时势能最小，因此问题等价于求

$$
f(\boldsymbol{p})=\sum_{i=1}^n w_i\lvert\boldsymbol{p}-\boldsymbol{a}_i\rvert
$$

的最小值点．这个问题称为带权的 Fermat–Weber 问题，最优点也称为带权费马点．$f$ 是若干个凸函数的非负加权和，因此是凸函数．

### 梯度与不可导点

当 $\boldsymbol{p}$ 不与任何 $\boldsymbol{a}_i$ 重合时，记 $d_i=\lvert\boldsymbol{p}-\boldsymbol{a}_i\rvert$，则

$$
\mathbf{\nabla} f(\boldsymbol{p})=\sum_{i=1}^n w_i\frac{\boldsymbol{p}-\boldsymbol{a}_i}{d_i}.
$$

第 $i$ 根绳子对绳结的拉力大小为 $w_i$，方向从 $\boldsymbol{p}$ 指向 $\boldsymbol{a}_i$，所以负梯度 $-\mathbf{\nabla} f(\boldsymbol{p})$ 正是各根绳子拉力的合力．因此梯度下降在这里有直观的物理含义：绳结沿合力的方向移动．

直接使用梯度下降会遇到以下问题：

1.  当 $\boldsymbol{p}=\boldsymbol{a}_k$ 时，$\lvert\boldsymbol{p}-\boldsymbol{a}_k\rvert$ 不可导，梯度公式中会出现除以零；
2.  在输入点附近，梯度的方向变化剧烈，$f$ 不是 $L$ 光滑的，固定步长难以收敛到精确解；
3.  最优点本身可能就是某个输入点．题面中「绳结卡在洞口」的情形正对应这种情况，例如某个重物远重于其他重物时．

对于第三点，可以用 [次梯度](../../dp/opt/wqs-binary-search.md#次梯度) 刻画输入点的最优性．为方便起见，先将坐标相同的点合并，权重相加．对于输入点 $\boldsymbol{a}_k$，记其余各点对它的「拉力」的合力为

$$
\boldsymbol{R}_k=\sum_{i\neq k} w_i\frac{\boldsymbol{a}_i-\boldsymbol{a}_k}{\lvert\boldsymbol{a}_i-\boldsymbol{a}_k\rvert},
$$

则 $f$ 在 $\boldsymbol{a}_k$ 处的次微分是以 $-\boldsymbol{R}_k$ 为圆心、$w_k$ 为半径的圆盘．由于 $f$ 是凸函数，$\boldsymbol{a}_k$ 是最小值点当且仅当零向量属于该次微分，即[^kuhn]

$$
\lvert\boldsymbol{R}_k\rvert\leq w_k.
$$

### Weiszfeld 迭代

令梯度为零，整理得

$$
\boldsymbol{p}=\frac{\sum_i w_i\boldsymbol{a}_i/d_i}{\sum_i w_i/d_i}.
$$

右侧仍与 $\boldsymbol{p}$ 有关．把它当作迭代式，记右侧为 $T(\boldsymbol{p})$，反复令 $\boldsymbol{p}\gets T(\boldsymbol{p})$，就得到 **Weiszfeld 迭代**[^weiszfeld]．可以验证

$$
T(\boldsymbol{p})=\boldsymbol{p}-\frac{1}{\sum_i w_i/d_i}\mathbf{\nabla} f(\boldsymbol{p}),
$$

所以 Weiszfeld 迭代就是步长随位置变化的梯度下降，步长为

$$
\eta(\boldsymbol{p})=\left(\sum_{i=1}^n\frac{w_i}{d_i}\right)^{-1}.
$$

离某个输入点越近，步长越小．

这个步长保证了函数值不增．对任意 $\boldsymbol{q}$，由均值不等式，$w_i\lvert\boldsymbol{q}-\boldsymbol{a}_i\rvert\leq\dfrac{w_i}{2}\left(\dfrac{\lvert\boldsymbol{q}-\boldsymbol{a}_i\rvert^2}{d_i}+d_i\right)$，且 $\boldsymbol{q}=\boldsymbol{p}$ 时取等．对 $i$ 求和，右侧是关于 $\boldsymbol{q}$ 的二次函数，记为 $g(\boldsymbol{q})$．它满足 $f(\boldsymbol{q})\leq g(\boldsymbol{q})$，$f(\boldsymbol{p})=g(\boldsymbol{p})$，而它的最小值点恰为 $T(\boldsymbol{p})$．于是

$$
f(T(\boldsymbol{p}))\leq g(T(\boldsymbol{p}))\leq g(\boldsymbol{p})=f(\boldsymbol{p}).
$$

Kuhn 证明了，在输入点不全共线时，只要迭代点不落在输入点上，Weiszfeld 迭代就收敛到最优点[^kuhn]．迭代点恰好落在输入点上时，$T(\boldsymbol{p})$ 没有定义．Vardi 和 Zhang 给出了一种修正[^vardi-zhang]：设 $\boldsymbol{p}$ 与输入点 $\boldsymbol{a}_j$ 重合，在 $T$ 和 $\boldsymbol{R}_j$ 的定义中都只对其余的点求和，记 $r=\lvert\boldsymbol{R}_j\rvert$．若 $r\leq w_j$，则 $\boldsymbol{p}$ 已经是最优点；否则下一个迭代点取为

$$
\boldsymbol{p}'=\left(1-\frac{w_j}{r}\right)T(\boldsymbol{p})+\frac{w_j}{r}\boldsymbol{p}.
$$

在输入点不全共线时，修正后的迭代对任意初始点都收敛到最优点．关于 Weiszfeld 迭代的更多性质，可以参考综述[^beck-sabach]．

### 实现

最优点恰为输入点时，迭代点只会无限接近它，收敛可能很慢．由于 $n\leq 1000$，可以先用 $O(n^2)$ 的时间对每个输入点检查 $\lvert\boldsymbol{R}_k\rvert\leq w_k$ 是否成立．若都不成立，说明最优点不是输入点，再从带权重心出发进行 Weiszfeld 迭代，并对迭代点落在输入点上的情形使用上述修正．每轮迭代的时间复杂度为 $O(n)$．

输入点全部共线的情形也由第一步处理：把任意一点投影到这条直线上，它到各输入点的距离都不会增大，所以最优点在直线上；而 $f$ 在直线上是分段线性的凸函数，题目保证最小值点唯一，它只能是某个分段点，即某个输入点．

??? note "参考代码"
    ```cpp
    --8<-- "docs/math/code/numerical/gradient-descent/gradient-descent_2.cpp"
    ```

[爬山算法](../../misc/hill-climbing.md) 和 [模拟退火](../../misc/simulated-annealing.md) 页面也以本题为例．其中爬山算法每一步都沿合力（即负梯度）方向移动，并随过程调整移动的距离，可以看作梯度下降的一种变体．

## 与三分法的比较

并不是所有连续优化问题都适合使用梯度下降．下面的例题说明了如何根据问题的结构选择算法．

???+ example "[洛谷 P3382 - 三分](https://www.luogu.com.cn/problem/P3382)"
    给定一个 $N$ 次多项式 $f(x)$ 和区间 $[l,r]$，保证存在 $x\in[l,r]$，使得 $f$ 在 $[l,x]$ 上单调递增、在 $[x,r]$ 上单调递减，求 $x$．
    
    $6\leq N\leq 13$，系数在 $[-100,100]$ 内，$\lvert l\rvert,\lvert r\rvert\leq 10$．答案与标准答案的相对误差或绝对误差不超过 $10^{-5}$，或者对应的函数值满足同样的误差要求，即视为正确．

题目保证 $f$ 在 $[l,r]$ 上先增后减．由于 $f$ 是不恒为常数的多项式，它的导数只有有限个零点，因此这里的单调都是严格单调，$f$ 是 [三分法](../../basic/binary.md#三分法) 一节所约定的严格单峰函数．对于 $l\leq\textit{lmid}<\textit{rmid}\leq r$，若 $f(\textit{lmid})<f(\textit{rmid})$，则最大值点不在 $[l,\textit{lmid})$ 中，反之则不在 $(\textit{rmid},r]$ 中．三分法只用到函数值的大小比较，不需要导数，也不需要选择步长，每轮迭代至少将区间缩短为原来的 $2/3$．

如果改用梯度上升（沿导数方向移动以求最大值），则会遇到以下问题：

1.  **平坦点**：单峰只保证函数先增后减，不保证导数只在最大值点处为零．例如 $f(x)=\dfrac{x^3}{3}-\dfrac{x^4}{4}$ 在 $[-1,2]$ 上严格单峰，最大值点为 $x=1$，但 $f'(x)=x^2(1-x)$ 在 $x=0$ 处也为零．从 $x_0=-1$ 出发，迭代式为 $x_{k+1}=x_k+\eta x_k^2(1-x_k)$．当 $0<\eta<\dfrac{1}{2}$ 时，可以验证迭代点始终为负且单调递增，因此收敛到驻点 $0$，永远不会到达 $1$．例如取 $\eta=0.1$，迭代 $10^5$ 次后 $x\approx -10^{-4}$．而三分法在这个函数上可以正常工作．
2.  **区间边界**：最大值点可能是区间端点．例如 $f$ 在整个 $[l,r]$ 上递增时，最大值点为 $r$，而 $f'(r)$ 不为零．不加限制的迭代会离开区间，到达函数值更大的区间外的点．此时需要在每一步之后把迭代点投影回区间内（即投影梯度法）．
3.  **步长**：多项式次数较高、定义域较宽时，二阶导数的绝对值可能很大，很难事先给出对所有数据都安全的固定步长．

一般而言：

-   一元单峰函数应优先使用三分法；如果导数容易计算且单调，也可以二分导数的零点．
-   多元可微函数，若能保证凸性（尤其是强凸性），梯度下降能够可靠地收敛到全局最优解．
-   非凸函数上，梯度下降只能保证逼近驻点，可以考虑多次随机选取初始点，或使用 [模拟退火](../../misc/simulated-annealing.md) 等方法．
-   问题有特殊结构时，例如本页的带权距离和，专门的迭代方法（如 Weiszfeld 迭代）往往比固定步长的梯度下降更稳定．

## 习题

-   [POJ 2420 - A Star not a Tree?](http://poj.org/problem?id=2420)
-   [「JSOI2008」球形空间产生器](https://www.luogu.com.cn/problem/P4035)

## 参考资料与注释

[^nesterov]: Yurii Nesterov.[Lectures on Convex Optimization](https://doi.org/10.1007/978-3-319-91578-4), 2nd ed. Springer, 2018. 第 2.1 节．

[^kuhn]: Harold W. Kuhn.[A note on Fermat's problem](https://doi.org/10.1007/BF01584648). Mathematical Programming, 4(1): 98–107, 1973.

[^weiszfeld]: Endre Weiszfeld. Sur le point pour lequel la somme des distances de n points donnés est minimum. Tôhoku Mathematical Journal, 43: 355–386, 1937.

[^vardi-zhang]: Yehuda Vardi, Cun-Hui Zhang.[The multivariate $L_1$-median and associated data depth](https://doi.org/10.1073/pnas.97.4.1423). Proceedings of the National Academy of Sciences, 97(4): 1423–1426, 2000.

[^beck-sabach]: Amir Beck, Shoham Sabach.[Weiszfeld's Method: Old and New Results](https://doi.org/10.1007/s10957-014-0586-7). Journal of Optimization Theory and Applications, 164(1): 1–40, 2015.
