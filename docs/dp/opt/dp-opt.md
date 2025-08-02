## 引入

本页面列举了一些常见的 DP 优化方法。

## 利用常见技巧优化

许多动态规划问题的转移，可以通过常见的算法和数据结构进行优化。

### 前缀和优化 DP

相关页面：[前缀和](../../basic/prefix-sum.md#前缀和)

### 单调队列/单调栈优化 DP

主页面：[单调队列/单调栈优化](./monotonous-queue-stack.md)

### 线段树/树状数组优化 DP

相关页面：[线段树](../../ds/seg.md)、[树状数组](../../ds/fenwick.md)

### 倍增优化 DP

相关页面：[倍增](../../basic/binary-lifting.md)

### CDQ 分治优化 DP

主页面：[CDQ 分治优化 DP](../../misc/cdq-divide.md#cdq-分治优化-1d1d-动态规划的转移)

CDQ 分治优化 DP 常见于下列各类问题中：

-   [基于 CDQ 分治的斜率优化 DP](./slope.md#二分cdq平衡树优化-dp)
-   [分治优化斜率单调性 DP](./quadrangle.md#分治)

## 利用问题结构优化

许多动态规划问题具备如凸性、单调性等结构性质，合理利用这些性质可以快速求解。

### 斜率优化 DP

主页面：[斜率优化](./slope.md)

### 四边形不等式优化 DP

主页面：[四边形不等式优化](./quadrangle.md)

### Slope Trick 优化 DP

主页面：[Slope Trick](./slope-trick.md)

### WQS 二分优化 DP

主页面：[WQS 二分](./wqs-binary-search.md)

## 利用数学方法优化

许多动态规划问题的转移，可以通过数学工具加速。

### 矩阵快速幂优化 DP

相关页面：[快速幂](../../math/binary-exponentiation.md)

### FFT 优化 DP

相关页面：[FFT](../../math/poly/fft.md)

### Lagrange 插值优化 DP

相关页面：[Lagrange 插值](../../math/numerical/interp.md#lagrange-插值法)

## 其他优化方法

一些特殊的问题，有着特别的优化方法。

### 状态设计优化 DP

主页面：[状态设计优化](./state.md)
