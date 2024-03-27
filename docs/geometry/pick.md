## Pick 定理

Pick 定理：给定顶点均为整点的简单多边形，皮克定理说明了其面积 ${\displaystyle A}$ 和内部格点数目 ${\displaystyle i}$、边上格点数目 ${\displaystyle b}$ 的关系：${\displaystyle A=i+{\frac {b}{2}}-1}$。

具体证明：[Pick's theorem](https://en.wikipedia.org/wiki/Pick%27s_theorem)

它有以下推广：

-   取格点的组成图形的面积为一单位。在平行四边形格点，皮克定理依然成立。套用于任意三角形格点，皮克定理则是 ${\displaystyle A=2 \times i+b-2}$。
-   对于非简单的多边形 ${\displaystyle P}$，皮克定理 ${\displaystyle A=i+{\frac {b}{2}}-\chi (P)}$，其中 ${\displaystyle \chi (P)}$ 表示 ${\displaystyle P}$ 的 **欧拉特征数**。
-   高维推广：Ehrhart 多项式
-   皮克定理和 **欧拉公式**（${\displaystyle V-E+F=2}$）等价。

## 一道例题 ([POJ 1265](http://poj.org/problem?id=1265))

### 题目大意

在直角坐标系中，一个机器人从任意点出发进行 $\textit{n}$ 次移动，每次向右移动 $\textit{dx}$，向上移动 $\textit{dy}$，最后会形成一个平面上的封闭简单多边形，求边上的点的数量，多边形内的点的数量，多边形面积。

### 题解

这道题目其实用了以下三个知识：

-   以整点为顶点的线段，如果边 $\textit{dx}$ 和 $\textit{dy}$ 都不为 $0$，经过的格点数是 $\gcd(\textit{dx}, \textit{dy}) + 1$，当然，如果要算一整个图形的，多加的点会被上一条边计算，也就不需要加了。那么一条边覆盖的点的个数为 $\gcd(\textit{dx},\textit{dy})$，其中，$\textit{dx},\textit{dy}$ 分别为线段横向占的点数和纵向占的点数。如果 $\textit{dx}$ 或 $\textit{dy}$ 为 $0$，则覆盖的点数为 $\textit{dy}$ **或** $\textit{dx}$。
-   Pick 定理：平面上以整点为顶点的简单多边形的面积 = 边上的点数/2 + 内部的点数 - 1。
-   任意一个多边形的面积等于按顺序求相邻两个点与原点组成的向量的叉积之和的一半（这个也可以通过顺时针定积分求得）。

??? note "参考代码"
    ```cpp
    --8<-- "docs/geometry/code/pick/pick_1.cpp"
    ```
