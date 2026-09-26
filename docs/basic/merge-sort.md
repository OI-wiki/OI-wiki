本页面将介绍归并排序及其计算逆序对的应用．

## 定义

归并排序（[merge sort](https://en.wikipedia.org/wiki/Merge_sort)）是高效的基于比较的稳定排序算法．

## 性质

归并排序基于分治思想将数组分段排序后合并，时间复杂度在最优、最坏与平均情况下均为 $\Theta (n \log n)$，空间复杂度为 $\Theta (n)$．

归并排序可以只使用 $\Theta (1)$ 的辅助空间，但为便捷通常使用与原数组等长的辅助数组．

## 过程

### 合并

归并排序最核心的部分是合并（merge）过程：将两个有序的数组 `a` 和 `b` 合并为一个有序数组 `c`．

从左往右枚举 `a[i]` 和 `b[j]`，每次将较小元素写入 `c[k]`；当一个数组遍历完毕时，将另一个数组的剩余元素追加到 `c` 中．

为保证排序的稳定性，前段首元素小于或等于后段首元素时（`a[i] <= b[j]`）而非小于时（`a[i] < b[j]`）就要作为最小值放入 `c[k]`．

#### 实现

=== "C/C++"
    === "数组实现"
        ```cpp
        --8<-- "docs/basic/code/merge-sort/merge-sort_1.cpp:array"
        ```
    
    === "指针实现"
        ```cpp
        --8<-- "docs/basic/code/merge-sort/merge-sort_1.cpp:pointer"
        ```
    
    也可使用 `<algorithm>` 库的 `std::merge` 函数，用法与上述指针式写法相同．

=== "Python"
    ```python
    --8<-- "docs/basic/code/merge-sort/merge-sort_1.py:merge"
    ```

### 分治法实现归并排序

1.  当数组长度为 $1$ 时，该数组就已经是有序的，不用再分解．
2.  当数组长度大于 $1$ 时，该数组很可能不是有序的．此时将该数组分为两段，再分别检查两个数组是否有序（用第一条）．如果有序，则将它们合并为一个有序数组；否则对尚未有序的数组重复第二条，再合并．

用数学归纳法可以证明该流程可以将一个数组转变为有序数组．

为保证排序的复杂度，通常将数组分为尽量等长的两段（$\textit{mid} = \left\lfloor \dfrac{l + r}{2} \right\rfloor$）．

#### 实现

注意下面的代码所表示的区间分别是 $[l, r)$，$[l, \textit{mid})$，$[\textit{mid}, r)$．

=== "C/C++"
    ```cpp
    --8<-- "docs/basic/code/merge-sort/merge-sort_1.cpp:recursive"
    ```

=== "Python"
    ```python
    --8<-- "docs/basic/code/merge-sort/merge-sort_1.py:recursive"
    ```

### 倍增法实现归并排序

已知当数组长度为 $1$ 时，该数组就已经是有序的．

将数组全部切成长度为 $1$ 的段．

从左往右依次合并两个长度为 $1$ 的有序段，得到一系列长度 $\le 2$ 的有序段；

从左往右依次合并两个长度 $\le 2$ 的有序段，得到一系列长度 $\le 4$ 的有序段；

从左往右依次合并两个长度 $\le 4$ 的有序段，得到一系列长度 $\le 8$ 的有序段；

……

重复上述过程直至数组只剩一个有序段，该段就是排好序的原数组．

???+ note "为什么是 $\le n$ 而不是 $= n$"
    数组的长度很可能不是 $2^x$，此时在最后就可能出现长度不完整的段，可能出现最后一个段是独立的情况．

#### 实现

=== "C/C++"
    ```cpp
    --8<-- "docs/basic/code/merge-sort/merge-sort_1.cpp:iterative"
    ```

=== "Python"
    ```python
    --8<-- "docs/basic/code/merge-sort/merge-sort_1.py:iterative"
    ```

## 逆序对

相关阅读和参考实现：[逆序对](../math/permutation.md#逆序数)

逆序对是 $i < j$ 且 $a_i > a_j$ 的有序数对 $(i, j)$．

排序后的数组无逆序对．归并排序的合并操作中，每次后段首元素被作为当前最小值取出时，前段剩余元素个数之和即是合并操作减少的逆序对数量；故归并排序计算逆序对数量的时间复杂度为 $\Theta (n \log n)$．此外，逆序对计数还可以通过树状数组或线段树解决，时间复杂度也是 $O(n \log n)$；这一算法的详细解释参见 [树状数组](../ds/fenwick.md#全局逆序对全局二维偏序) 相应描述．两种算法的参考实现都在 [逆序对](../math/permutation.md#逆序数) 章节．

## 外部链接

-   [Merge Sort - GeeksforGeeks](https://www.geeksforgeeks.org/merge-sort/)
-   [归并排序 - 维基百科，自由的百科全书](https://zh.wikipedia.org/wiki/%E5%BD%92%E5%B9%B6%E6%8E%92%E5%BA%8F)
-   [逆序对 - 维基百科，自由的百科全书](https://zh.wikipedia.org/wiki/%E9%80%86%E5%BA%8F%E5%AF%B9)
