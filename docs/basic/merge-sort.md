## 定义

归并排序（[merge sort](https://en.wikipedia.org/wiki/Merge_sort)）是高效的基于比较的稳定排序算法。

## 性质

归并排序基于分治思想将数组分段排序后合并，时间复杂度在最优、最坏与平均情况下均为 $\Theta (n \log n)$，空间复杂度为 $\Theta (n)$。

归并排序可以只使用 $\Theta (1)$ 的辅助空间，但为便捷通常使用与原数组等长的辅助数组。

## 过程

由于已分段排序，各非空段的首元素的最小值即是数组的最小值，不断从数组中取出当前最小值至辅助数组即可使其有序，最后将其从辅助数组复制至原数组。

为保证排序的正确性，应注意从数组中取出当前最小值可能导致非空段变为空，后段为空时（`j == r`）前段的首元素是当前最小值，否则在前段非空时（`i < mid`）比较前后段的首元素。

为保证排序的稳定性，前段首元素小于或等于后段首元素时（`a[i] <= a[j]`）而非小于时（`a[i] < a[j]`）就要作为最小值。

为保证排序的复杂度，通常将数组分为尽量等长的两段（$mid = \left\lfloor \dfrac{l + r}{2} \right\rfloor$）。

## 实现

### C++

```cpp
// C++ version
void merge(int l, int r) {
  if (r - l <= 1) return;
  int mid = l + ((r - l) >> 1);
  merge(l, mid), merge(mid, r);
  for (int i = l, j = mid, k = l; k < r; ++k) {
    if (j == r || (i < mid && a[i] <= a[j]))
      tmp[k] = a[i++];
    else
      tmp[k] = a[j++];
  }
  for (int i = l; i < r; ++i) a[i] = tmp[i];
}
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

逆序对是 $i < j$ 且 $a_i > a_j$ 的有序数对 $(i, j)$。

排序后的数组无逆序对，归并排序的合并操作中每次后段首元素被作为当前最小值取出时前段剩余元素个数之和即是合并操作减少的逆序对数量；故归并排序计算逆序对数量的额外时间复杂度为 $\Theta (n \log n)$，对于 C++ 代码将 `a[j++]` 替换为 `(cnt += mid - i, a[j++])` 即可。

此外，逆序对计数即是将元素依次加入数组时统计当前大于其的元素数量，将数组离散化后即是区间求和问题，使用树状数组或线段树解决的时间复杂度为 $\operatorname{O} (n \log n)$ 且空间复杂度为 $\Theta (n)$。

## 外部链接

- [Merge Sort - GeeksforGeeks](https://www.geeksforgeeks.org/merge-sort/)
- [归并排序 - 维基百科，自由的百科全书](https://zh.wikipedia.org/wiki/%E5%BD%92%E5%B9%B6%E6%8E%92%E5%BA%8F)
- [逆序对 - 维基百科，自由的百科全书](https://zh.wikipedia.org/wiki/%E9%80%86%E5%BA%8F%E5%AF%B9)
