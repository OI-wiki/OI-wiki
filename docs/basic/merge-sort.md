## 定义

归并排序（[merge sort](https://en.wikipedia.org/wiki/Merge_sort)）是高效的基于比较的稳定排序算法。

## 性质

归并排序基于分治思想将数组分段排序后合并，时间复杂度在最优、最坏与平均情况下均为 $\Theta (n \log n)$，空间复杂度为 $\Theta (n)$。

归并排序可以只使用 $\Theta (1)$ 的辅助空间，但为便捷通常使用与原数组等长的辅助数组。

## 过程

### 合并

归并排序最核心的部分是合并（merge）过程：将两个有序的数组 `a[i]` 和 `b[j]` 合并为一个有序数组 `c[k]`。

从左往右枚举 `a[i]` 和 `b[j]`，找出最小的值并放入数组 `c[k]`；重复上述过程直到 `a[i]` 和 `b[j]` 有一个为空时，将另一个数组剩下的元素放入 `c[k]`。

为保证排序的稳定性，前段首元素小于或等于后段首元素时（`a[i] <= b[j]`）而非小于时（`a[i] < b[j]`）就要作为最小值放入 `c[k]`。

#### 实现

=== "C/C++"
    === "数组实现"
        ```cpp
        void merge(const int *a, size_t aLen, const int *b, size_t bLen, int *c) {
          size_t i = 0, j = 0, k = 0;
          while (i < aLen && j < bLen) {
            if (b[j] < a[i]) {  // <!> 先判断 b[j] < a[i]，保证稳定性
              c[k] = b[j];
              ++j;
            } else {
              c[k] = a[i];
              ++i;
            }
            ++k;
          }
          // 此时一个数组已空，另一个数组非空，将非空的数组并入 c 中
          for (; i < aLen; ++i, ++k) c[k] = a[i];
          for (; j < bLen; ++j, ++k) c[k] = b[j];
        }
        ```
    
    === "指针实现"
        ```cpp
        void merge(const int *aBegin, const int *aEnd, const int *bBegin,
                   const int *bEnd, int *c) {
          while (aBegin != aEnd && bBegin != bEnd) {
            if (*bBegin < *aBegin) {
              *c = *bBegin;
              ++bBegin;
            } else {
              *c = *aBegin;
              ++aBegin;
            }
            ++c;
          }
          for (; aBegin != aEnd; ++aBegin, ++c) *c = *aBegin;
          for (; bBegin != bEnd; ++bBegin, ++c) *c = *bBegin;
        }
        ```

    也可使用 `<algorithm>` 库的 `merge` 函数，用法与上述指针式写法的相同。

=== "Python"
    ```python
    def merge(a, b):
        i, j = 0, 0
        c = []
        while(i < len(a) and j < len(b)):
            # <!> 先判断 b[j] < a[i]，保证稳定性
            if(b[j] < a[i]):
                c.append(b[j])
                j += 1
            else:
                c.append(a[i])
                i += 1
        # 此时一个数组已空，另一个数组非空，将非空的数组并入 c 中
        c.extend(a[i:])
        c.extend(b[j:])
        return c
    ```

### 分治法实现归并排序

1.  当数组长度为 $1$ 时，该数组就已经是有序的，不用再分解。

2.  当数组长度大于 $1$ 时，该数组很可能不是有序的。此时将该数组分为两段，再分别检查两个数组是否有序（用第 1 条）。如果有序，则将它们合并为一个有序数组；否则对不有序的数组重复第 2 条，再合并。

用数学归纳法可以证明该流程可以将一个数组转变为有序数组。

为保证排序的复杂度，通常将数组分为尽量等长的两段（$mid = \left\lfloor \dfrac{l + r}{2} \right\rfloor$）。

#### 实现

注意下面的代码所表示的区间分别是 $[l, r)$，$[l, mid)$，$[mid, r)$。

=== "C/C++"
    ```cpp
    void merge_sort(int *a, int l, int r) {
      if (r - l <= 1) return;
      // 分解
      int mid = l + ((r - l) >> 1);
      merge_sort(a, l, mid), merge_sort(a, mid, r);
      // 合并
      int tmp[1024] = {};  // 请结合实际情况设置 tmp 数组的长度（与 a 相同），或使用
                           // vector；先将合并的结果放在 tmp 里，再返回到数组 a
      merge(a + l, a + mid, a + mid, a + r, tmp + l);  // pointer-style merge
      for (int i = l; i < r; ++i) a[i] = tmp[i];
    }
    ```

=== "Python"
    ```python
    def merge_sort(a, ll, rr):
        if rr - ll <= 1:
            return
        # 分解
        mid = (rr + ll) // 2
        merge_sort(a, ll, mid)
        merge_sort(a, mid, rr)
        # 合并
        a[ll:rr] = merge(a[ll:mid], a[mid:rr])
    ```

### 倍增法实现归并排序

已知当数组长度为 $1$ 时，该数组就已经是有序的。

将数组全部切成长度为 $1$ 的段。

从左往右依次合并两个长度为 $1$ 的有序段，得到一系列长度 $\le 2$ 的有序段；

从左往右依次合并两个长度 $\le 2$ 的有序段，得到一系列长度 $\le 4$ 的有序段；

从左往右依次合并两个长度 $\le 4$ 的有序段，得到一系列长度 $\le 8$ 的有序段；

……

重复上述过程直至数组只剩一个有序段，该段就是排好序的原数组。

???+ note " 为什么是 $\le n$ 而不是 $= n$"
    数组的长度很可能不是 $2^x$，此时在最后就可能出现长度不完整的段，可能出现最后一个段是独立的情况。

#### 实现

=== "C/C++"
    ```cpp
    void merge_sort(int *a, size_t n) {
      int tmp[1024] = {};  // 请结合实际情况设置 tmp 数组的长度（与 a 相同），或使用
                           // vector；先将合并的结果放在 tmp 里，再返回到数组 a
      for (size_t seg = 1; seg < n; seg <<= 1) {
        for (size_t left1 = 0; left1 < n - seg;
             left1 += seg + seg) {  // n - seg: 如果最后只有一个段就不用合并
          size_t right1 = left1 + seg;
          size_t left2 = right1;
          size_t right2 = std::min(left2 + seg, n);  // <!> 注意最后一个段的边界
          merge(a + left1, a + right1, a + left2, a + right2,
                tmp + left1);  // pointer-style merge
          for (size_t i = left1; i < right2; ++i) a[i] = tmp[i];
        }
      }
    }
    ```

=== "Python"
    ```python
    def merge_sort(a):
        seg = 1
        while seg < len(a):
            for l1 in range(0, len(a) - seg, seg + seg):
                r1 = l1 + seg
                l2 = r1
                r2 = l2 + seg
                a[l1:r2] = merge(a[l1:r1], a[l2:r2])
        seg <<= 1
    ```

## 逆序对

逆序对是 $i < j$ 且 $a_i > a_j$ 的有序数对 $(i, j)$。

排序后的数组无逆序对，归并排序的合并操作中，每次后段首元素被作为当前最小值取出时，前段剩余元素个数之和即是合并操作减少的逆序对数量；故归并排序计算逆序对数量的额外时间复杂度为 $\Theta (n \log n)$，对于 C/C++ 代码将 `merge` 过程的 `if(b[j] < a[i])` 部分加上 `cnt += aLen - i` 或 `cnt += aEnd - aBegin` 即可，对于 Python 代码将 `merge` 过程的 `if(b[j] < a[i]):` 部分加上 `cnt += len(a) - i` 即可。

此外，逆序对计数即是将元素依次加入数组时统计当前大于其的元素数量，将数组离散化后即是区间求和问题，使用树状数组或线段树解决的时间复杂度为 $O(n \log n)$ 且空间复杂度为 $\Theta (n)$。

## 外部链接

-   [Merge Sort - GeeksforGeeks](https://www.geeksforgeeks.org/merge-sort/)
-   [归并排序 - 维基百科，自由的百科全书](https://zh.wikipedia.org/wiki/%E5%BD%92%E5%B9%B6%E6%8E%92%E5%BA%8F)
-   [逆序对 - 维基百科，自由的百科全书](https://zh.wikipedia.org/wiki/%E9%80%86%E5%BA%8F%E5%AF%B9)
