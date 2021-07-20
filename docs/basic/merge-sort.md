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

归并排序是一种稳定的排序算法。

归并排序的最优时间复杂度、平均时间复杂度和最坏时间复杂度均为 $O(n\log n)$。

归并排序的空间复杂度为 $O(n)$。

## 代码实现

### 伪代码

$$
\begin{array}{ll}
1 & \textbf{Input. }\text{待排序的数组}A\text{和用作临时存储的数组}T\\
2 & \textbf{Output. }\text{数组}A\text{中的元素将会按照不减的顺序进行稳定排序}\\
3 & \textbf{Method.}\\
4 & \text{merge}(A,\ T)\\
5 & \qquad\text{merge0}(A,\ T,\ 0,\ A.length)\\
6 & \text{merge0}(A,\ T,\ ll,\ rr)\\
7 & \qquad \textbf{if}\ \ rr - ll \leqslant 1\\
8 & \qquad\qquad \textbf{return}\\
9 & \qquad mid \gets \large\lfloor\frac{ll+rr}{2}\rfloor\\
10& \qquad\text{merge0}(A,\ T,\ ll,\ mid)\\
11&\qquad\text{merge0}(A,\ T,\ mid,\ rr)\\
12&\\
13&\qquad p \gets rr\\
14&\qquad q \gets mid\\
15&\qquad\textbf{for}\text{ each } i \text{ in the } ll\dots rr-1\\
16&\qquad\qquad\textbf{if}\ p\geqslant mid\ or\ q < rr\ and\ A[q] < A[p]\\
17&\qquad\qquad\qquad T[i] \gets A[q]\\
18&\qquad\qquad\qquad q \gets q+1\\
19&\qquad\qquad\textbf{else}\\
20&\qquad\qquad\qquad T[i] \gets A[p]\\
21&\qquad\qquad\qquad p \gets p+1\\
22&\qquad \text{copy }T[ll\dots rr-1] \text{ to } A[ll\dots rr-1]\\
\end{array}
$$

### C++

```cpp
// C++ Version
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

### Python

```python
# Python Version
def merge_sort(ll, rr):
    if rr - ll <= 1:
        return
    mid = math.floor((rr + ll) / 2)
    merge_sort(ll, mid)
    merge_sort(mid, rr)
    p = s = ll
    q = mid
    while(s < rr):
        if p >= mid or (q < rr and a[p] > a[q]):
            s += 1
            q += 1
            t[s] = a[q]
        else:
            s += 1
            p += 1
            t[s] = a[p]
    for i in range(ll, rr):
        a[i] = t[i]
```

## 逆序对

归并排序还可以用来求逆序对的个数。

所谓逆序对，就是满足 $a_{i} > a_{j}$ 且 $i < j$ 的数对 $(i, j)$。

代码实现中注释掉的 `ans += mid - p` 就是在统计逆序对个数。具体来说，算法把靠后的数放到前面了（较小的数放在前面），所以在这个数原来位置之前的、比它大的数都会和它形成逆序对，而这个个数就是还没有合并进去的数的个数，即为 `mid - p`。

另外，逆序对也可以用 [树状数组](../ds/fenwick.md)、[线段树](../ds/seg.md) 等数据结构求解。这三种方法的时间复杂度都是 $O(n \log n)$。

## 外部链接

- [Merge Sort - GeeksforGeeks](https://www.geeksforgeeks.org/merge-sort/)
- [希尔排序 - 维基百科，自由的百科全书](https://zh.wikipedia.org/wiki/%E5%BD%92%E5%B9%B6%E6%8E%92%E5%BA%8F)
- [逆序对 - 维基百科，自由的百科全书](https://zh.wikipedia.org/wiki/%E9%80%86%E5%BA%8F%E5%AF%B9)
