Author:Backl1ght

tim 排序是归并排序和插入排序的结合，是一个 **稳定** 的排序算法，由 Tim Peters 于 2002 年用 Python 实现。现在，tim 排序是 Python 的标准排序算法，且被 Java SE7 用于对非原始类型的数组排序。

tim 排序在最好情况下的时间复杂度为 $O(n)$，最差情况下的时间复杂度为 $O(n \log n)$，期望时间复杂度为 $O(n \log n)$。tim 排序在最坏情况下的空间复杂度为 $O(n)$。

## 算法

众所周知，归并排序是先将数组划分为两部分，然后递归地对两个子数组进行归并排序，最后合并两个子数组。这样一来，归并排序合并操作的最小单位就是单个元素。但是，数组中可能原本就存在连续且有序的子数组，归并排序无法利用这个特性。

tim 排序为了利用数组中本身就存在的连续且有序的子数组，以 RUN 作为合并操作的最小单位。其中，RUN 是一个满足以下性质的子数组：

- 一个 RUN 要么是非降序的，要么是严格升序的。
- 一个 RUN 存在一个长度的下限。

tim 排序的过程就是一个类似归并排序的过程，将数组划分为多个 RUN，然后以某种规则不断地合并两个 RUN，直到数组有序。具体过程如下：

令 $nRemaining$ 初始化为数组的大小，$minRun$ 初始化为 $getMinRunLength(nRemaining)$。

$$
\begin{array}{ll}
1 & \textbf{do}\\
2 & \qquad \text{确定} run \text{的起点}\\
3 & \qquad \textbf{if} run \text{比} minRun \text{短}\\
4 & \qquad \qquad \text{延长} run \text{直至} \min(minRun, nRemaining)\\
5 & \qquad \textbf{push} run \text{放到} pending-run stack \text{上}\\
6 & \qquad \textbf{if} pending-run stack \text{最顶上的 2 个} run \text{长度相近}\\
7 & \qquad  \qquad \text{合并} pending-run stack \text{最顶上的 2 个} run\\
8 & \qquad \text{start index} \gets \text{start index} + run \text{的长度}\\
9 & \qquad nRemaining \gets nRemaining - run \text{的长度}\\
10 & \textbf{while} \text{ } nRemaining \ne 0\\
\end{array}
$$

其中，$getMinRunLength$ 函数是根据当前数组长度确定 $minRun$ 具体值的函数，natural run 的意思是原本就非降序或者严格升序的 run，扩展长度不够的 run 就是用插入排序往 run 中添加元素。

## 复杂度证明

最好情况下，数组本身就有序，即数组本身就是一个 RUN，这个时候 tim 排序就遍历了一遍数组，找到了唯一的 RUN，就结束了。所以，最好的情况下，tim 排序的时间复杂度为 $O(n)$。

## 写在后面

本文只是简单介绍了 tim 排序的原理，实际上 tim 排序在实现的时候还有一些其他的优化，这里不再一一列举。tim 排序在 java 中的实现写得非常好，要想知道真正的 tim 排序推荐去看 java 中 tim 排序的实现。

## 参考资料

1. [Timsort](https://en.wikipedia.org/wiki/Timsort)
2. [On the Worst-Case Complexity of TimSort](https://drops.dagstuhl.de/opus/volltexte/2018/9467/pdf/LIPIcs-ESA-2018-4.pdf)
3. [original explanation by Tim Peters](https://bugs.python.org/file4451/timsort.txt)
4. [java 实现](https://web.archive.org/web/20150716000631/https://android.googlesource.com/platform/libcore/+/gingerbread/luni/src/main/java/java/util/TimSort.java)
5. [c 语言实现](http://svn.python.org/projects/python/trunk/Objects/listobject.c)
