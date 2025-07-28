## 动态规划简介

本页面将介绍动态规划（Dynamic Programming，DP）的基本原理、设计方法及其在算法竞赛中的典型应用。

## 基本原理

动态规划是一种通过 **将原问题分解为重叠子问题** 的方式求解复杂问题的方法。其核心思想包含两个关键要素：

1.  **最优子结构**：问题的最优解包含子问题的最优解
2.  **重叠子问题**：不同的子问题会重复调用相同的更小子问题

## 方法分类

### 1. 记忆化搜索（自顶向下）

```text
function dp(i):
    if memo[i] exists:
        return memo[i]
    res = calculate(dp(subproblems))
    memo[i] = res
    return res
```

### 2. 递推法（自底向上）

```text
initialize dp[0..n]
for i from 1 to n:
    dp[i] = calculate(dp[0..i-1])
```

## 典型例题

???+ note "[斐波那契数列](https://leetcode-cn.com/problems/fibonacci-number/)"
    **问题描述**：计算第 n 个斐波那契数（n ≤ 30）

    **DP 状态定义**：
    ```text
    dp[i] 表示第 i 个斐波那契数
    ```

    **状态转移方程**：
    ```math
    dp[i] = \begin{cases}
    i & \text{if } i \leq 1 \\
    dp[i-1] + dp[i-2] & \text{otherwise}
    \end{cases}
    ```

=== "C++"
    ```cpp
    int fib(int n) {
      vector<int> dp(n + 1);
      dp[0] = 0;
      dp[1] = 1;
      for (int i = 2; i <= n; ++i) dp[i] = dp[i - 1] + dp[i - 2];
      return dp[n];
    }
    ```

=== "Python"
    ```python
    def fib(n: int) -> int:
        dp = [0, 1] + [0] * (n - 1)
        for i in range(2, n + 1):
            dp[i] = dp[i - 1] + dp[i - 2]
        return dp[n]
    ```

## 与其他算法的比较

| 特性     | 动态规划 | 分治算法  | 贪心算法 |
| ------ | ---- | ----- | ---- |
| 子问题重叠性 | 有    | 通常无   | 无    |
| 最优子结构  | 必须满足 | 必须满足  | 必须满足 |
| 决策后效性  | 可能有  | 无     | 无    |
| 时间复杂度  | 多项式级 | 视情况而定 | 通常较低 |

## 参考资料与注释

[动态规划 - 维基百科](https://zh.wikipedia.org/wiki/%E5%8A%A8%E6%80%81%E8%A7%84%E5%88%92)
