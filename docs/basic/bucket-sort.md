本页面将简要介绍桶排序．

## 定义

桶排序（英文：Bucket sort）是排序算法的一种，适用于待排序数据值域较大但分布比较均匀的情况．

## 过程

桶排序按下列步骤进行：

1.  设置一个定量的数组当作空桶；
2.  遍历序列，并将元素一个个放到对应的桶中；
3.  对每个不是空的桶进行排序；
4.  从不是空的桶里把元素再放回原来的序列中．

## 性质

### 稳定性

如果使用稳定的内层排序，并且将元素插入桶中时不改变元素间的相对顺序，那么桶排序就是一种稳定的排序算法．

由于每块元素不多，一般使用插入排序．此时桶排序是一种稳定的排序算法．

### 时间复杂度

设 $n$ 为元素个数，$k$ 为桶数．若元素独立且均匀落桶，桶排序的平均时间复杂度为 $O(n + n^2/k + k)$（将值域平均分成 $k$ 块 + 排序 + 重新合并元素），当 $k\approx n$ 时为 $O(n)$．[^ref1]

桶排序的最坏时间复杂度为 $O(n^2+k)$．

## 实现

下面 `a[]` 下标从 $1$ 开始，要求 $0\le a_i\le w$、$0\le n<N$，其中 $w$ 是最大键值的上界．

=== "C++"
    ```cpp
    --8<-- "docs/basic/code/bucket-sort/bucket-sort_1.cpp:sort"
    ```

=== "Python"
    ```python
    --8<-- "docs/basic/code/bucket-sort/bucket-sort_1.py:sort"
    ```

## 参考资料与注释

[^ref1]: [（英文）Bucket sort - Wikipedia](https://en.wikipedia.org/wiki/Bucket_sort#Average-case_analysis)
