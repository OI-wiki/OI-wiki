author: Ir1d, Catreap, TianyiQ, Tiphereth-A, Enter-tainer, Henry-ZHR, HeRaNO, iamtwz, ksyx, ouuan, sshwy, Xeonacid, GWBailang553

## 引入

对平面上的 $n$ 个点 $P_1,P_2,\cdots,P_n$，找出一个半径最小的圆，使得所有点都在圆内（包含边界）．

## 过程

求解最小圆覆盖问题的最常见做法是 [随机增量法](random-incremental.md)．

不妨设 $n>4$ 且这 $n$ 个点互不相同，则最小覆盖圆一定过两个或三个点．我们考虑加一个「已知最小覆盖圆过若干个固定点」的额外条件，然后逐步弱化该条件直至消除，从而得到最小覆盖圆的算法．

### 已知过三点

假设我们已知最小覆盖圆过三个点 $A=(x_A,y_A), B=(x_B,y_B), C=(x_C,y_C)$，不妨假设这三点不共线，则只需求 $\triangle ABC$ 的外接圆即可．我们知道圆心 $O$ 是 $\triangle ABC$ 的外心，所以 $O$ 是线段 $AB$ 的垂直平分线与线段 $AC$ 的垂直平分线的交点，因此我们可以通过 [求两条直线的交点](./2d.md#求两条直线的交点) 来直接得出圆心．当然，我们也可以推导外心的表达式．设外心 $O=(x,y)$，则

$$
\begin{cases}
(x-x_A)^2+(y-y_A)^2&=(x-x_B)^2+(y-y_B)^2,\\
(x-x_A)^2+(y-y_A)^2&=(x-x_C)^2+(y-y_C)^2,
\end{cases}
$$

令

$$
\begin{aligned}
A_1&=2(x_B-x_A),&B_1&=2(y_B-y_A),&C_1&=x_B^2+y_B^2-x_A^2-y_A^2,\\
A_2&=2(x_C-x_A),&B_2&=2(y_C-y_A),&C_2&=x_C^2+y_C^2-x_A^2-y_A^2,
\end{aligned}
$$

则有

$$
x=\frac{C_1B_2-C_2B_1}{A_1B_2-A_2B_1},\quad y=\frac{A_1C_2-A_2C_1}{A_1B_2-A_2B_1}.
$$

### 已知过两点

假设我们已知最小覆盖圆过两个点 $A, B$，则最小覆盖圆必定是以下三个圆之一：

-   以 $AB$ 为直径的圆；
-   过 $A$，$B$，以及直线 $AB$ 左侧一点 $P_l$ 的圆中，半径最大的圆；
-   过 $A$，$B$，以及直线 $AB$ 右侧一点 $P_r$ 的圆中，半径最大的圆．

其中当 $\overrightarrow{AB}\times\overrightarrow{AP_l}>0$ 时我们认为 $P_l$ 在直线 $AB$ 左侧，当 $\overrightarrow{AB}\times\overrightarrow{AP_r}<0$ 时我们认为 $P_r$ 在直线 $AB$ 右侧．

???+ tip "为什么要选择半径最大的？"
    固定 $A,B$ 后，圆只由半径和在哪一侧决定．如果同样选择左侧点，那么半径越大，覆盖的左侧点越多．

故最多有三个候选圆，如下图所示：

![最小圆覆盖示意图](./images/smallest-enclosing-circle1.svg)

判断哪个是最小圆覆盖即可．总时间复杂度 $O(n)$．

### 已知过一点

假设我们已知最小覆盖圆过一个点 $A$，则我们可以枚举另一个点 $B$，根据 [已知过两点](#已知过两点) 提到的方法得到过 $A,B$ 的最小覆盖圆，在这 $n-1$ 个圆中取半径最小的圆即可．

这个做法的时间复杂度看上去是 $O(n^2)$ 的，但是我们可以通过随机增量法使时间复杂度的期望是 $O(n)$ 的，具体而言，我们维护一个点集 $S$ 的最小覆盖圆，初始状态 $S=\{A\}$，之后我们在没枚举过的点中随机取一个点 $B$ 并加入点集 $S$．每次加入时，如果 $B$ 在当前的最小覆盖圆外，那么 $B$ 一定在新的最小覆盖圆上，此时转化为 [已知过两点](#已知过两点) 的情况，$O(n)$ 处理即可．

??? note "复杂度证明"
    倒序考虑每一次操作．加入第 $j$ 个点答案发生变化等价于第 $j$ 个点在前 $j$ 个点的最小覆盖圆上．由于我们进行了随机打乱操作，故我们认为 $j$ 是平面上所有点等概率选择出的．平面上一共有 $j$ 个点，除固定点 $P$ 外，不超过 $2$ 个点在圆上．由此可得 $j$ 在圆上的概率小于等于 $\frac{2}{j}$．故加入第 $j$ 个点的期望时间复杂度为 $\frac{2}{j}\times O(j)+\frac{j-2}{j}\times O(1)=O(1)$．

### 求解原问题

现在我们可以去除假设，使用随机增量法得到最小覆盖圆了．思路和 [已知过一点](#已知过一点) 的思路类似，令点集 $S$ 初始为 $\varnothing$，按随机顺序枚举第一个点插入并维护最小覆盖圆，然后使用 [已知过一点](#已知过一点) 提到的方法即可．期望时间复杂度仍是 $O(n)$ 的．

## 例题

???+ note "[洛谷 P1742 最小圆覆盖](https://www.luogu.com.cn/problem/P1742)"
    给出 $N$ 个点，求包含所有点的最小圆，输出圆的半径和圆心坐标．

??? note "参考实现"
    ```cpp
    --8<-- "docs/geometry/code/smallest-enclosing-circle/smallest-enclosing-circle_1.cpp"
    ```

## 练习

[「POI 2011」WYK-Plot](https://www.luogu.com.cn/problem/P3517)

## 参考资料与扩展阅读

[Computational Geometry Lecture 4: Smallest enclosing circles and more - University of Florida](https://www.cise.ufl.edu/~sitharam/COURSES/CG/kreveldnbhd.pdf)
