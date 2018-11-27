学习状压 dp 之前，请确认你已经完成了[动态规划初步](/dp/)部分内容的学习

(建议学习[位运算](/math/bit/)部分的内容)

### 状压 DP 简介

状压 dp 是动态规划的一种，借由将状态压缩（通常压缩为某整形）以达到节约空间和时间的目的

#### 常用格式

```cpp
int maxn = 1 << n;  //规定状态的上界
for (int i = 0; i < maxn; i++) {
  if (i & (i << 1)) continue;  //如果i情况不成立就忽略
  Type[++top] = i;             //记录情况i到Type数组中
}
for (int i = 1; i <= top; i++) {
  if (fit(situation[1], Type[i])) dp[1][Type[i]] = 1;  //初始化第一层
}
for (int i = 2; i <= 层数(dp上界); i++) {
  for (int l = 1; l <= top; l++)  //穷举本层情况
    for (int j = 1; j <= top; j++)  //穷举上一层情况(上一层对本层有影响时)
      if (situation[i], Type[l] 和Type[j] 符合题意)
        dp[i][l] = dp[i][l] + dp[i - 1][j];  //改变当前层(i)的状态(l)的方案种数
}
for (int i = 1; i <= top; i++) ans += dp[上界][Type[i]];
```

#### 典型例题

[\[USACO06NOV\] 玉米田 Corn Fields](https://www.luogu.org/problemnew/show/P1879)

显然，这是一道典型的动态规划题目，但由于方案数过多，应使用状压 dp 避免超时

本题所 "压缩" 的是 "每行可行的状态" 和 "每行土地的状态", 而储存答案的 dp 数组就应同时体现这两个特点 (所以本题 dp 数组为二维)

具体实现方法同上方伪代码

[例题代码](https://www.luogu.org/paste/kto3ua68)
