author: Anguei, sshwy, Xeonacid, Ir1d, MonkeyOliver, hsfzLZH1

拆点是一种图论建模思想，常用于 [网络流](./flow.md)，用来处理 **点权或者点的流量限制** 的问题，也常用于 **分层图**．

## 结点有流量限制的最大流

如果把结点转化成边，那么这个问题就可以套板子解决了．

我们考虑把有流量限制的结点转化成这样一种形式：由两个结点 $u,v$ 和一条边 $\left\langle u,v \right\rangle$ 组成的部分．其中，结点 $u$ 承接所有从原图上其他点的出发到原图上该点的边，结点 $v$ 引出所有从原图上该点出发到达原图上其他点的边．边 $\left\langle u,v \right\rangle$ 的流量限制为原图该点的流量限制，再套板子就可以解决本题．这就是拆点的基本思想．

如果原图是这样：

![](./images/node.svg)

拆点之后的图是这个样子：

![](./images/node-split.svg)

## 分层图最短路

分层图最短路，如：有 $k$ 次零代价通过一条路径，求总的最小花费．对于这种题目，我们可以采用 DP 相关的思想，设 $\text{dis}_{i, j}$ 表示当前从起点 $i$ 号结点，使用了 $j$ 次免费通行权限后的最短路径．显然，$\text{dis}$ 数组可以这么转移：

$\text{dis}_{i, j} = \min\{\min\{\text{dis}_{from, j - 1}\}, \min\{\text{dis}_{from,j} + w\}\}$

其中，$from$ 表示 $i$ 的父亲节点，$w$ 表示当前所走的边的边权．当 $j - 1 \geq k$ 时，$\text{dis}_{from, j}$=$\infty$．

事实上，这个 DP 就相当于把每个结点拆分成了 $k+1$ 个结点，每个新结点代表使用不同多次免费通行后到达的原图结点．换句话说，就是每个结点 $u_i$ 表示使用 $i$ 次免费通行权限后到达 $u$ 结点．

??? note "[「JLOI2011」飞行路线](https://www.luogu.com.cn/problem/P4568)"
    题意：有一个 $n$ 个点 $m$ 条边的无向图，你可以选择 $k$ 条道路以零代价通行，求 $s$ 到 $t$ 的最小花费．
    
    参考核心代码：
    
    ```cpp
    --8<-- "docs/graph/code/node/node_1.cpp:state"
    --8<-- "docs/graph/code/node/node_1.cpp:algorithm"
    ```
