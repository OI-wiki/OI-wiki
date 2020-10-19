本页面将简要介绍归并排序。

## 简介

归并排序（英语：merge sort）是一种采用了 [分治](./divide-and-conquer.md) 思想的排序算法。

## 工作原理

归并排序分为三个步骤：

1. 将数列划分为两部分；
2. 递归地分别对两个子序列进行归并排序；
3. 合并两个子序列。

不难发现，归并排序的前两步都很好实现，关键是如何合并两个子序列。注意到两个子序列在第二步中已经保证了都是有序的了，第三步中实际上是想要把两个 **有序** 的序列合并起来。

## 性质

### 稳定性

归并排序是一种稳定的排序算法。

### 复杂度

归并排序的最优时间复杂度、平均时间复杂度和最坏时间复杂度均为 $O(n\log n)$ 。

归并排序的空间复杂度为 $O(n)$。

## 代码实现

### 伪代码

$$
\begin{array}{ll}
1 & \textbf{Input. }\text{An array } A \text{ and its indices } p \text{, } q \text{, } r \text{ such that }p \leq q < r \text{.}\\
2 & \textbf{Ouput. } A\text{ will be sorted in non-decreasing order stably.}\\
3 & \textbf{Method.}\\
4 \\
5 & \text{MERGE}(A, p, q, r)\\
6 & n_1 \gets q - r + p \\
7 & n_2 \gets r - q\\
8 & \text{let } L[1\ldots n_1+1] \text{ and } R[1\ldots n_2+1] \text{ be new arrays}\\
9 & \textbf{for } i \gets 1 \textbf{ to } n_1\\
10 & \qquad L[i] \gets A[p+i-1]\\
11 & \textbf{for } j \gets 1 \textbf{ to } n_2\\
12 & \qquad R[i] \gets A[q+j]\\
13 & L[n+1] \gets \infty\\
14 & R[n+1] \gets \infty\\
15 & i \gets 1\\
16 & j \gets 1\\
17 & \textbf{for } k \gets p \textbf{ to } r\\
18 & \qquad \textbf{if } L[i]\leq R[i]\\
19 & \qquad \qquad A[k] \gets L[i]\\
20 & \qquad \qquad i \gets i + 1\\
21 & \qquad \textbf{else } A[k] \gets R[j]\\
22 & \qquad \qquad j \gets j + 1\\
23 \\
24 & \text{MERGE-SORT}(A, p, r)\\
25 & \textbf{if } p < r\\
26 & \qquad q \gets \lfloor(p + r) \ 2 \rfloor\\
27 & \qquad \text{MERGE-SORT}(A, p, q)\\
28 & \qquad \text{MERGE-SORT}(A, q + 1, r)\\
29 & \qquad \text{MERGE}(A, p, q, r)\\
\end{array}
$$

[^ref1]

### C++

```cpp
void merge(int ll, int rr) {
  // 用来把 a[ll.. rr - 1] 这一区间的数排序。 t 数组是临时存放有序的版本用的。
  if (rr - ll <= 1) return;
  int mid = ll + (rr - ll >> 1);
  merge(ll, mid);
  merge(mid, rr);
  int p = ll, q = mid, s = ll;
  while (s < rr) {
    if (p >= mid || (q < rr && a[p] > a[q])) {
      t[s++] = a[q++];
      // ans += mid - p;
    } else
      t[s++] = a[p++];
  }
  for (int i = ll; i < rr; ++i) a[i] = t[i];
}
//关键点在于一次性创建数组，避免在每次递归调用时创建，以避免对象的无谓构造和析构。
```

## 逆序对

归并排序还可以用来求逆序对的个数。

所谓逆序对，就是满足 $a_{i} > a_{j}$ 且 $i < j$ 的数对 $(i, j)$ 。

代码实现中注释掉的 `ans += mid - p` 就是在统计逆序对个数。具体来说，算法把靠后的数放到前面了（较小的数放在前面），所以在这个数原来位置之前的、比它大的数都会和它形成逆序对，而这个个数就是还没有合并进去的数的个数，即为 `mid - p` 。

另外，逆序对也可以用 [树状数组](../ds/fenwick.md) 、 [线段树](../ds/seg.md) 等数据结构求解。这三种方法的时间复杂度都是 $O(n \log n)$ 。

## 外部链接

-  [Merge Sort - GeeksforGeeks](https://www.geeksforgeeks.org/merge-sort/) 
-  [希尔排序 - 维基百科，自由的百科全书](https://zh.wikipedia.org/wiki/%E5%BD%92%E5%B9%B6%E6%8E%92%E5%BA%8F) 
-  [逆序对 - 维基百科，自由的百科全书](https://zh.wikipedia.org/wiki/%E9%80%86%E5%BA%8F%E5%AF%B9) 

## 参考资料与注释

[^ref1]: Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, and Clifford Stein.Introduction to Algorithms(3rd ed.). MIT Press and McGraw-Hill, 2009. ISBN 978-0-262-03384-8. "2.3 Designing algorithms", pp. 31-34.