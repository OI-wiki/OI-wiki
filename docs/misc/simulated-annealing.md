## 基础概念

### 简介

> 模拟退火算法（Simulate Anneal，SA）是一种通用概率演算法，用来在一个大的搜寻空间内找寻命题的最优解。模拟退火是由 S.Kirkpatrick, C.D.Gelatt 和 M.P.Vecchi 在 1983 年所发明的。V.Černý在 1985 年也独立发明此演算法。模拟退火算法是解决 TSP 问题的有效方法之一。
>
> 模拟退火的出发点是基于物理中固体物质的退火过程与一般组合优化问题之间的相似性。模拟退火算法是一种通用的优化算法，其物理退火过程由加温过程、等温过程、冷却过程这三部分组成。
>
> ——百度百科

简单说，模拟退火是一种随机化算法。当一个问题的方案数量极大（甚至是无穷的）而且不是一个单峰函数时，我们常使用模拟退火求解。

它与爬山算法最大的不同是，在寻找到一个局部最优解时，赋予了它一个跳出去的概率，也就有更大的机会能找到全局最优解。

### 原理

> 模拟退火的原理也和金属退火的原理近似：将热力学的理论套用到统计学上，将搜寻空间内每一点想像成空气内的分子；分子的能量，就是它本身的动能；而搜寻空间内的每一点，也像空气分子一样带有“能量”，以表示该点对命题的合适程度。演算法先以搜寻空间内一个任意点作起始：每一步先选择一个“邻居”，然后再计算从现有位置到达“邻居”的概率。
>
> ——百度百科

要讲模拟退火，首先要知道[金属退火](https://baike.baidu.com/item/%E9%80%80%E7%81%AB/1039313?fr=aladdin)。

简单来说，就是将金属加热到一定温度，保持足够时间，然后以适宜速度冷却。

对应到 OI 上，就是每次随机出一个新解，如果这个解更优，则接受它，否则以一个与温度和与最优解的差相关的概率接受它。

设这个新的解与最优解的差为 $\Delta E$ ，温度为 $T$ ， $k$ 为一个随机数，那么这个概率为 $e^{\frac{\Delta E}{kT}}$ 。

### 过程

#### 降温

模拟退火时有三个参数，分别是初始温度 $T_0$ 、降温系数 $\Delta$ 、终止温度 $T_k$ 。

其中， $T_0$ 是一个比较大的数， $\Delta$ 是一个略小于 $1$ 的正数， $T_k$ 是一个略大于 $0$ 的正数。

我们先让温度 $T=T_0$ ，然后每次降温时 $T=T\cdot \Delta$ ，直到 $T\leq T_k$ 为止。

大致过程如下（图片来自[Wiki](https://en.wikipedia.org/wiki/Simulated_annealing)）：

![img](https://upload.wikimedia.org/wikipedia/commons/d/d5/Hill_Climbing_with_Simulated_Annealing.gif)

可以看出，随着温度的降低，解逐渐稳定下来，并逐渐集中在最优解附近。

#### 其它

程序开始时，我们要先 `srand（一个常数）` 。这个常数可以决定分数。你可以使用 233333，2147483647，~~甚至某个八位质数~~。

一遍模拟退火往往无法跑出最优解，所以可以多跑几遍。

可以用一个全局变量记录所有跑过的模拟退火的最优解，每次从全局最优解开始跑模拟退火，也许更容易找到最优解。

### 时间复杂度

时间复杂度 $O(\text{玄学})$ 。

一般来说，降温系数 $\Delta$ 与 $1$ 的差减少一个数量级，耗时大约多 $10$ 倍； $T_0$ 和 $T_k$ 变化一个数量级，耗时不会变化很大。

## 进阶内容

### 如何调参

容易知道，不同的 $\Delta$ 、 $T_0$ ， $T_k$ ，甚至 `srand()` 和模拟退火的次数都会影响到答案。

我们探讨一下模拟退火的~~玄学~~调参。

Q：答案不是最优的怎么办？

A：有以下几种方法：调大 $\Delta$ 、调大 $T_0$ 、调小 $T_k$ ，以及多跑几遍模拟退火。

当您的程序跑的比较快时，可以选择多跑几遍模拟退火，或者调大 $\Delta$ ，从而增大得到最优解的概率。

调大 $T_0$ 和调小 $T_k$ 也可以，而且时间并不会增大太多，~~只是用处似乎不大~~。

Q：还是跑不出最优解怎么办？

A：尝试更换随机数种子，或者用一些奇怪的随机姿势，总有可能跑出正解。

Q：我是非酋，交了两页也没有用模拟退火 AC，怎么办？

A：~~那您还是选择打正解吧。~~

### 如何生成新解

-   坐标系内：随机生成一个向量，模长随着温度的降低而减小。
-   序列问题：随机交换两个数。当然 `random_shuffle` 也行。
-   网格问题：随机交换两个格子。

### 例题

这里以[JSOI2004 平衡点](https://www.luogu.org/problemnew/show/P1337)为例，讲解模拟退火的实际应用。

题目要使整个系统的能量最小。那么我们只要用模拟退火跑出这个最小值即可。

```cpp
#include <bits/stdc++.h>
#define re register
using namespace std;

inline int read() {  //读入优化
  int X = 0, w = 1;
  char c = getchar();
  while (c < '0' || c > '9') {
    if (c == '-') w = -1;
    c = getchar();
  }
  while (c >= '0' && c <= '9') X = (X << 3) + (X << 1) + c - '0', c = getchar();
  return X * w;
}

struct node {
  int x, y, w;
};

node a[1010];
int n, sx, sy;

double ansx, ansy;           //全局最优解的坐标
double ans = 1e18, t;        //全局最优解、温度
const double delta = 0.993;  //降温系数

inline double calc_energy(double x, double y) {  //计算整个系统的能量
  double rt = 0;
  for (re int i = 1; i <= n; i++) {
    double deltax = x - a[i].x, deltay = y - a[i].y;
    rt += sqrt(deltax * deltax + deltay * deltay) * a[i].w;
  }
  return rt;
}

inline void simulate_anneal() {  // SA主过程
  double x = ansx, y = ansy;
  t = 2000;  //初始温度
  while (t > 1e-14) {
    double X = x + ((rand() << 1) - RAND_MAX) * t;
    double Y = y + ((rand() << 1) - RAND_MAX) * t;  //得出一个新的坐标
    double now = calc_energy(X, Y);
    double Delta = now - ans;
    if (Delta < 0) {  //接受
      x = X, y = Y;
      ansx = x, ansy = y, ans = now;
    } else if (exp(-Delta / t) * RAND_MAX > rand())
      x = X, y = Y;  //以一个概率接受
    t *= delta;
  }
}

inline void Solve() {  //多跑几遍模拟退火，减小误差
  ansx = (double)sx / n, ansy = (double)sy / n;  //从平均值开始更容易接近最优解
  simulate_anneal();
  simulate_anneal();
  simulate_anneal();
}

int main() {
  srand(1 * *****7);
  srand(rand());
  srand(rand());  //玄学 srand
  n = read();
  for (re int i = 1; i <= n; i++) {
    a[i].x = read(), a[i].y = read(), a[i].w = read();
    sx += a[i].x, sy += a[i].y;
  }
  Solve();
  printf("%.3f %.3f\n", ansx, ansy);
  return 0;
}
```

这份代码跑了 $476\ ms$ ，可以通过，而且时间比较充裕。

## 一些 trick

### 分块模拟退火

有时函数的峰很多，模拟退火难以跑出最优解。

此时可以把整个值域分成几段，每段跑一遍模拟退火，然后再取最优解。

### 在不会 TLE 的情况下尽量多地跑模拟退火

我们知道，有一个 `clock()` 函数，返回程序运行时间。

那么这样即可：

```cpp
while ((double)clock() / CLOCKS_PER_SEC < MAX_TIME) simulate_anneal();
```

其中 `MAX_TIME` 是一个自定义的略小于 $1$ 的正数，可以取 $0.7\sim 0.8$ 。

## 习题

-   [HAOI2006 均分数据](https://www.luogu.org/problem/P2503)
