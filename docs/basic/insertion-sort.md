本页面将简要介绍插入排序。

## 简介

插入排序（英语：Insertion sort）是一种简单直观的排序算法。它的工作原理为将待排列元素划分为“已排序”和“未排序”两部分，每次从“未排序的”元素中选择一个插入到“已排序的”元素中的正确位置。

一个与插入排序相同的操作是打扑克牌时，从牌桌上抓一张牌，按牌面大小插到手牌后，再抓下一张牌。

![insertion-sort-1-animate-example](images/insertion-sort-1-animate-example.svg)

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

### C++

```cpp
// C++ Version
void insertion_sort(int* a, int n) {
  // 对 a[1],a[2],...,a[n] 进行插入排序
  for (int i = 2; i <= n; ++i) {
    int key = a[i];
    int j = i - 1;
    while (j > 0 && a[j] > key) {
      a[j + 1] = a[j];
      --j;
    }
    a[j + 1] = key;
  }
}
```

### Python

```python
# Python Version
def insertion_sort(a, n):
    for i in range(2, n + 1):
        key = a[i]
        j = i - 1
        while j > 0 and a[j] > key:
            a[j + 1] = a[j]
            j = j - 1
        a[j + 1] = key
```
