本页面将简要介绍冒泡排序。

## 简介

冒泡排序（英语：Bubble sort）是一种简单的排序算法。由于在算法的执行过程中，较小的元素像是气泡般慢慢「浮」到数列的顶端，故叫做冒泡排序。

## 工作原理

它的工作原理是每次检查相邻两个元素，如果前面的元素与后面的元素满足给定的排序条件，就将相邻两个元素交换。当没有相邻的元素需要交换时，排序就完成了。

经过 $i$ 次扫描后，数列的末尾 $i$ 项必然是最大的 $i$ 项，因此冒泡排序最多需要扫描 $n-1$ 遍数组就能完成排序。

## 性质

### 稳定性

冒泡排序是一种稳定的排序算法。

### 时间复杂度

在序列完全有序时，冒泡排序只需遍历一遍数组，不用执行任何交换操作，时间复杂度为 $O(n)$。

在最坏情况下，冒泡排序要执行 $\frac{(n-1)n}{2}$ 次交换操作，时间复杂度为 $O(n^2)$。

冒泡排序的平均时间复杂度为 $O(n^2)$。

## 代码实现

### 伪代码

$$
\begin{array}{ll}
1 & \textbf{Input. } \text{An array } A \text{ consisting of }n\text{ elements.} \\
2 & \textbf{Output. } A\text{ will be sorted in nondecreasing order stably.} \\
3 & \textbf{Method. }  \\
4 & flag\gets True\\
5 & \textbf{while }flag\\
6 & \qquad flag\gets False\\
7 & \qquad\textbf{for }i\gets1\textbf{ to }n-1\\
8 & \qquad\qquad\textbf{if }A[i]>A[i + 1]\\
9 & \qquad\qquad\qquad flag\gets True\\
10 & \qquad\qquad\qquad \text{Swap } A[i]\text{ and }A[i + 1]
\end{array}
$$

### C++

```cpp
// C++ Version
// 假设数组的大小是n+1，冒泡排序从数组下标1开始
void bubble_sort(int *a, int n) {
  bool flag = true;
  while (flag) {
    flag = false;
    for (int i = 1; i < n; ++i) {
      if (a[i] > a[i + 1]) {
        flag = true;
        int t = a[i];
        a[i] = a[i + 1];
        a[i + 1] = t;
      }
    }
  }
}
```

### Python

```python
# Python Version
def bubble_sort(a, n):
    flag = True
    while flag:
        flag = False
        for i in range(1, n):
            if a[i] > a[i + 1]:
                flag = True
                a[i], a[i + 1] = a[i + 1], a[i]
```
