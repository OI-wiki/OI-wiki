本页面将简要介绍选择排序。

## 定义

选择排序（英语：Selection sort）是一种简单直观的排序算法。它的工作原理是每次找出第 $i$ 小的元素（也就是 $A_{i..n}$ 中最小的元素），然后将这个元素与数组第 $i$ 个位置上的元素交换。

![selection sort animate example](images/selection-sort-animate.svg)

## 性质

### 稳定性

选择排序的稳定性取决于其具体实现。

倘若使用链表实现，由于链表的任意位置插入和删除均为 $O(1)$，故无需使用 swap（交换两个元素）操作：每次从未排序部分选择最小元素（若有多个，选取第 1 个）后，将其插入到未排序部分的第 1 个元素之前，这样就能够保证稳定性。

假如使用数组实现（OI 中一般的实现方式），由于数组任意位置插入和删除均为 $O(n)$，故只能使用 swap 将未排序部分的元素移到已排序部分。swap 操作使得数组实现的选择排序不稳定。

下面给出的实现示例均是基于数组元素的交换，因此均为 **不稳定的**。

### 时间复杂度

选择排序的最优时间复杂度、平均时间复杂度和最坏时间复杂度均为 $O(n^2)$。

## 代码实现

### 伪代码

$$
\begin{array}{ll}
1 & \textbf{Input. } \text{An array } A \text{ consisting of }n\text{ elements.} \\
2 & \textbf{Output. } A\text{ will be sorted in nondecreasing order.} \\
3 & \textbf{Method. }  \\
4 & \textbf{for } i\gets 1\textbf{ to }n-1\\
5 & \qquad ith\gets i\\
6 & \qquad \textbf{for }j\gets i+1\textbf{ to }n\\
7 & \qquad\qquad\textbf{if }A[j]<A[ith]\\
8 & \qquad\qquad\qquad ith\gets j\\
9 & \qquad \text{swap }A[i]\text{ and }A[ith]\\
\end{array}
$$

=== "C++"
    ```cpp
    --8<-- "docs/basic/code/selection-sort/selection-sort_1.cpp"
    ```

=== "Python"
    ```python
    --8<-- "docs/basic/code/selection-sort/selection-sort_1.py"
    ```

=== "Java"
    ```java
    // arr代码下标从 1 开始索引
    static void selection_sort(int[] arr, int n) {
        for (int i = 1; i < n; i++) {
            int ith = i;
            for (int j = i + 1; j <= n; j++) {
                if (arr[j] < arr[ith]) {
                    ith = j;
                }
            }
            // swap
            int temp = arr[i];
            arr[i] = arr[ith];
            arr[ith] = temp;
        }
    }
    ```
