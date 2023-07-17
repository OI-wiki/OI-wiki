## 引入

**Kahan 求和** 算法，又名补偿求和或进位求和算法，是一个用来 **降低有限精度浮点数序列累加值误差** 的算法。它主要通过保持一个单独变量用来累积误差（常用变量名为 $c$）来完成的。

该算法主要由 William Kahan 于 1960s 发现。因为 Ivo Babuška 也曾独立提出了一个类似的算法，Kahan 求和算法又名为 Kahan–Babuška 求和算法。

## 舍入误差

在计算机程序中，我们需要用有限位数对实数做近似表示，如今的大多数计算机都使用 [IEEE-754](https://en.wikipedia.org/wiki/IEEE_754) 规定的浮点数来作为这个近似表示。对于 $\frac{1}{3}$，由于我们不能在有限位数内对它进行精准表示，因此在使用 IEEE-754 表示法时，必须四舍五入一部分数值（truncate）。这种 **舍入误差**（Rounding off error）是浮点计算的一个特征。

在浮点加法计算中，交换律（commutativity）成立，但结合律（associativity）不成立。也就是说，$a+b = b+a$ 但 $(a+b)+c \neq a+(b+c)$。因此在浮点序列加法计算中，我们可以从左到右一个个累加，也可以在原有顺序上，将他们两两分成一对。第二种算法会相对较慢并需要更多内存，也常被一些语言的特定求和函数使用，但相对结果更准确。

为了得到更准确的浮点累加结果，我们需要使用 Kahan 求和算法。

在计算 $S_{new}=S_{old}+a$（$a$ 为浮点序列的一个数值）时，定义实际计算加入 $S$ 的值为 $a_{eff}=S_{new}-S_{old}$, 如果 $a_{eff}$ 比 $a$ 大，则证明有向上舍入误差；如果 $a_{eff}$ 比 $a$ 小，则证明有向下舍入误差。则舍入误差定义为 $E_{roundoff} = a_{eff} - a$。那么用来纠正这部分舍入误差的值就为 $a-a_{eff}$, 即 $E_{roundoff}$ 的负值。定义 $c$ 是对丢失的低位进行运算补偿的变量，就可以得到 $c_{new} = c_{old} + (a - a_{eff})$。

## 过程

Kahan 求和算法主要通过一个单独变量用来累积误差。如下方参考代码所示，$sum$ 为最终返回的累加结果。$c$ 是对丢失的低位进行运算补偿的变量（其被舍去的部分），也是 Kahan 求和算法中的必要变量。

因为 $sum$ 大，$y$ 小，所以 $y$ 的低位数丢失。$(t - sum)$ 抵消了 $y$ 的高阶部分，减去 $y$ 则会恢复负值（$y$ 的低价部分）。因此代数值中 $c$ 始终为零。在下一轮迭代中，丢失的低位部分会被更新添加到 $y$。

## 实现

??? 参考代码
    ```cpp
    float kahanSum(vector<float> nums) {
      float sum = 0.0f;
      float c = 0.0f;
      for (auto num : nums) {
        float y = num - c;
        float t = sum + y;
        c = (t - sum) - y;
        sum = t;
      }
      return sum;
    }
    ```

## 习题

在 OI 中，Kahan 求和主要作为辅助工具存在，为计算结果提供误差更小的值。

???+ note " 例题 [CodeForces Contest 800 Problem A. Voltage Keepsake](https://codeforces.com/contest/800/problem/A)"
    有 $n$ 个同时使用的设备。第 $i$ 个设备每秒使用 $a_{i}$ 单位的功率。这种用法是连续的。也就是说，在 $\lambda$ 秒内，设备将使用 $\lambda \times a_{i}$ 单位的功率。第 $i$ 个设备当前存储了 $b_{i}$ 单位的电力。所有设备都可以存储任意数量的电量。有一个可以插入任何单个设备的充电器。充电器每秒会为设备增加 $p$ 个单位的电量。这种充电是连续的。也就是说，如果将设备插入 $\lambda$ 秒，它将获得 $\lambda \times p$ 单位的功率。我们可以在任意时间单位内（包括实数）切换哪个设备正在充电（切换所需时间忽略不计）。求其中一个设备达到 $0$ 单位功率前，可以使用这些设备的最长时间。

???+ note " 例题 [CodeForces Contest 504 Problem B. Misha and Permutations Summation](https://codeforces.com/problemset/problem/504/B)"
    定义数字 $0, 1, \cdots, (n - 1)$ 的两个排列 $p$ 和 $q$ 的和为 $Perm((Ord(p)+Ord(q))\bmod n!)$，其中 $Perm(x)$ 是数字 $0, 1, \cdots, (n-1)$ 的第 $x$ 个字典排列（从零开始计数），$Ord(p)$ 是字典序排列 $p$ 的个数。例如，$Perm(0) = (0, 1, \cdots , n - 2, n - 1)$，$Perm(n! - 1) = (n - 1, n-2,\cdots, 1,0))$。Misha 有两个排列 $p$ 和 $q$，找到它们的总和。

## 编程语言的求和

Python 的标准库指定了精确舍入求和的 [fsum](https://docs.python.org/3/library/math.html#math.fsum) 函数可用于返回可迭代对象中值的准确浮点总和，它通过使用 Shewchuk 算法跟踪多个中间部分和来避免精度损失。

Julia 语言中，[sum](https://docs.julialang.org/en/v1/base/collections/#Base.sum) 函数的默认实现是成对求和，以获得高精度和良好的性能。同时外部库函数 [sum\_kbn](http://www.jlhub.com/julia/manual/en/function/sum_kbn) 为需要更高精度的情况提供了 Neumaier 变体的实现，具体可见 [KahanSummation.jl](https://github.com/JuliaMath/KahanSummation.jl)。

## 参考资料与注释

1.  [Kahan\_summation\_algorithm - Wikipedia](https://en.wikipedia.org/wiki/Kahan_summation_algorithm)
2.  [Kahan summation - Rosetta Code](https://rosettacode.org/wiki/Kahan_summation)
3.  [VK Cup Round 2 + Codeforces Round 409 Announcement](https://codeforces.com/blog/entry/51577)
4.  [Rounding off errors in Java - GeeksforGeeks](https://www.geeksforgeeks.org/rounding-off-errors-java/)
