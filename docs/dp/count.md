author: Persdre

前置知识：[动态规划部分简介](./index.md)。

## 简介

计数是组合数学中的内容，纯数学的做法是找到含有阶乘的公式求组合数。

「计数 dp」是利用动态规划的算法思想，利用递推式计算出解决这个问题有多少种方法。比如给定了一个地图，限定了左上角是起点右下角是终点，每一步只能走右边或者下边。那么从起点出发走到终点，可以有多少种路径。需要注意的是，这里需要解决的问题是有多少条路径，而不是每一条路径具体是怎么走的。

以卡特兰 (Catalan) 数为例：

1. 含有阶乘的公式

$$
C_n = \dbinom{2n}{n}-\dbinom{2n}{n-1} = \prod_{k=2}^n(\frac{n+k}{k})
$$

2. dp 递推式

$$
C_n = \sum_{i=0}^{N-1}C_iC_{n-i-1}
$$

我们通常采用第二种方法计算。

## 例题

???+note " 例 1 [62 不同路径](https://leetcode.cn/problems/unique-paths/)"
    题目大意：一个机器人位于一个 $m*n$ 网格的左上角，机器人每次只能往下或者往右移动一步，问要移动到右下角总共有多少条不同的路径。

思路与算法：

这个题目有组合数学的解法。因为机器人只能走 $m+n-2$ 步，那么我们要做的就是在 $m+n-2$ 步中挑出 $m-1$ 步向下走。所以总共会有 $\mathrm C_n = \binom{m+n-2}{m-1}$ 条路径。

如果用动态规划的思路，那么我们首先要定义状态和状态转移方程。

设 $f(i,j)$ 表示从左上角走到 $(i,j)$ 的路径的数量，这是状态。$f(m,n)$ 是我们想要求的结果。

如果想要走到 $(i,j)$，那么在它的上一步只有两种选择：向下走一步或者向右走一步。因此我们可以写出状态转移方程如下：

$$
f(i,j) = f(i-1,j) + f(i,j-1)
$$

???+ note "参考代码"

    ```c++
    #include <bits/stdc++.h>
    using namespace std;
    
    int m, n;
    
    inline int uniquePaths(int m, int n) {
        /* 定义dp二维数组 */
        vector<vector<int>> dp(m,vector<int>(n,0));
        /* 初始化dp数组 */
        for(int i = 0; i < m; i++)
            dp[i][0] = 1;
        for(int i = 0; i < n; i++)
            dp[0][i] = 1;
        /* 一行一行遍历 */
        for(int i = 1; i < m; i++) {
            for(int j = 1; j < n; j++) {
                dp[i][j] = dp[i-1][j] + dp[i][j-1];
            }
        }
        return dp[m-1][n-1];
    }

    int main() {
      scanf("%d%d", &m, &n);
      printf("%d\n", uniquePaths(m, n));
      return 0;
    }
    ```

## 参考资料

[不同路径 - 力扣官方题解](https://leetcode.cn/problems/unique-paths/solution/bu-tong-lu-jing-by-leetcode-solution-hzjf/)

