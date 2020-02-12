插入排序将数列划分为“已排序的”和“未排序的”两部分，每次从“未排序的”元素中选择一个插入到“已排序的”元素中的正确位置。

插入排序的最坏情况时间复杂度和平均情况时间复杂度都为 $O(n^2)$ ，但其在数列几乎有序时效率很高。

插入排序是一个稳定排序。

伪代码：

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

C++ 代码：

```cpp
void insertion_sort(int* a, int n) {
  //对 a[1],a[2],...,a[n] 进行插入排序
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
