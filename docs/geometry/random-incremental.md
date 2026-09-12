author: Ir1d, TianyiQ, GWBailang553

## 介绍

随机增量算法是计算几何的一个重要算法，它对理论知识要求不高，算法时间复杂度低，应用范围广大．

增量法 (Incremental Algorithm) 的思想与第一数学归纳法类似，它的本质是将一个问题化为规模刚好小一层的子问题．解决子问题后加入当前的对象．写成递归式是：

$$
T(n)=T(n-1)+g(n)
$$

增量法形式简洁，可以应用于许多的几何题目中．

增量法往往结合随机化，即随机增量法．

随机增量法的思路是：每次加入一个新的对象时，如果改变答案，那么局部重新计算．因此，随机增量法通常要求容易快速判断加入一个元素是否修改答案，且在随机顺序下答案改变次数的期望较少．

随机增量法常用于求解 [最小圆覆盖](smallest-enclosing-circle.md) 问题，也可以用于求解半空间交、高维凸包、随机 Delaunay 三角剖分等问题．

## 练习

[最小圆覆盖](https://www.luogu.com.cn/problem/P1742)

[「HNOI2012」射箭](https://www.luogu.com.cn/problem/P3222)

[CodeForces 442E](https://codeforces.com/problemset/problem/442/E)

## 参考资料与扩展阅读

[随机增量算法 - 解轶伦](https://github.com/hzwer/shareOI/blob/master/%E8%AE%A1%E7%AE%97%E5%87%A0%E4%BD%95/%E9%9A%8F%E6%9C%BA%E5%A2%9E%E9%87%8F%E7%AE%97%E6%B3%95_%E8%A7%A3%E8%BD%B6%E4%BC%A6.pdf)

<https://www.cnblogs.com/aininot260/p/9635757.html>

<https://blog.csdn.net/u014609452/article/details/62039612>

[随机 Delaunay 三角剖分](https://zhuanlan.zhihu.com/p/364390356)
