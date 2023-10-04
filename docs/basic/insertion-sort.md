本页面将简要介绍插入排序。

## 定义

插入排序（英语：Insertion sort）是一种简单直观的排序算法。它的工作原理为将待排列元素划分为「已排序」和「未排序」两部分，每次从「未排序的」元素中选择一个插入到「已排序的」元素中的正确位置。

一个与插入排序相同的操作是打扑克牌时，从牌桌上抓一张牌，按牌面大小插到手牌后，再抓下一张牌。

![insertion sort animate example](images/insertion-sort-animate.svg)

## 性质

### 稳定性

插入排序是一种稳定的排序算法。

### 时间复杂度

插入排序的最优时间复杂度为 $O(n)$，在数列几乎有序时效率很高。

插入排序的最坏时间复杂度和平均时间复杂度都为 $O(n^2)$。

## 代码实现

### 伪代码

$$
\begin{array}{ll}
1 & \textbf{Input. } \text{An array } A \text{ consisting of }n\text{ elements.} \\
2 & \textbf{Output. } A\text{ will be sorted in nondecreasing order stably.} \\
3 & \textbf{Method. }  \\
4 & \textbf{for } i\gets 2\textbf{ to }n\\
5 & \qquad key\gets A[i]\\
6 & \qquad j\gets i-1\\
7 & \qquad\textbf{while }j>0\textbf{ and }A[j]>key\\
8 & \qquad\qquad A[j + 1]\gets A[j]\\
9 & \qquad\qquad j\gets j - 1\\
10 & \qquad A[j + 1]\gets key
\end{array}
$$

=== "C++"
    ```cpp
    void insertion_sort(int arr[], int len) {
      for (int i = 1; i < len; ++i) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
          arr[j + 1] = arr[j];
          j--;
        }
        arr[j + 1] = key;
      }
    }
    ```

=== "Python"
    ```python
    def insertion_sort(arr, n):
        for i in range(1, n):
            key = arr[i]
            j = i - 1
            while j >= 0 and arr[j] > key:
                arr[j + 1] = arr[j]
                j = j - 1
            arr[j + 1] = key
    ```

## 折半插入排序

插入排序还可以通过二分算法优化性能，在排序元素数量较多时优化的效果比较明显。

### 时间复杂度

折半插入排序与直接插入排序的基本思想是一致的，折半插入排序仅对插入排序时间复杂度中的常数进行了优化，所以优化后的时间复杂度仍然不变。

### 代码实现

=== "C++"
    ```cpp
    void insertion_sort(int arr[], int len) {
      if (len < 2) return;
      for (int i = 1; i != len; ++i) {
        int key = arr[i];
        auto index = upper_bound(arr, arr + i, key) - arr;
        // 使用 memmove 移动元素，比使用 for 循环速度更快，时间复杂度仍为 O(n)
        memmove(arr + index + 1, arr + index, (i - index) * sizeof(int));
        arr[index] = key;
      }
    }
    ```
