本页面将简要介绍快速排序。

## 简介

快速排序（英语：Quicksort），又称分区交换排序（英语：partition-exchange sort），简称快排，是一种被广泛运用的排序算法。

## 基本原理与实现

### 原理

快速排序的工作原理是通过 [分治](./divide-and-conquer.md) 的方式来将一个数组排序。

快速排序分为三个过程：

1. 将数列划分为两部分（要求保证相对大小关系）；
2. 递归到两个子序列中分别进行快速排序；
3. 不用合并，因为此时数列已经完全有序。

和归并排序不同，第一步并不是直接分成前后两个序列，而是在分的过程中要保证相对大小关系。具体来说，第一步要是要把数列分成两个部分，然后保证前一个子数列中的数都小于后一个子数列中的数。为了保证平均时间复杂度，一般是随机选择一个数 $m$ 来当做两个子数列的分界。

之后，维护一前一后两个指针 $p$ 和 $q$，依次考虑当前的数是否放在了应该放的位置（前还是后）。如果当前的数没放对，比如说如果后面的指针 $q$ 遇到了一个比 $m$ 小的数，那么可以交换 $p$ 和 $q$ 位置上的数，再把 $p$ 向后移一位。当前的数的位置全放对后，再移动指针继续处理，直到两个指针相遇。

其实，快速排序没有指定应如何具体实现第一步，不论是选择 $m$ 的过程还是划分的过程，都有不止一种实现方法。

第三步中的序列已经分别有序且第一个序列中的数都小于第二个数，所以直接拼接起来就好了。

### 实现（C++）[^ref2]

```cpp
// C++ Version
struct Range {
  int start, end;
  Range(int s = 0, int e = 0) { start = s, end = e; }
};

template <typename T>
void quick_sort(T arr[], const int len) {
  if (len <= 0) return;
  Range r[len];
  int p = 0;
  r[p++] = Range(0, len - 1);
  while (p) {
    Range range = r[--p];
    if (range.start >= range.end) continue;
    T mid = arr[range.end];
    int left = range.start, right = range.end - 1;
    while (left < right) {
      while (arr[left] < mid && left < right) left++;
      while (arr[right] >= mid && left < right) right--;
      std::swap(arr[left], arr[right]);
    }
    if (arr[left] >= arr[range.end])
      std::swap(arr[left], arr[range.end]);
    else
      left++;
    r[p++] = Range(range.start, left - 1);
    r[p++] = Range(left + 1, range.end);
  }
}
```

### 实现（Python）[^ref2]

```python
# Python Version
def quick_sort(alist, first, last):
    if first >= last:
        return
    mid_value = alist[first]
    low = first
    high = last
    while low < high:
        while low < high and alist[high] >= mid_value:
            high -= 1
        alist[low] = alist[high]
        while low < high and alist[low] < mid_value:
            low += 1
        alist[high] = alist[low]
    alist[low] = mid_value
    quick_sort(alist, first, low - 1)
    quick_sort(alist, low + 1, last)
```

## 性质

### 稳定性

快速排序是一种不稳定的排序算法。

### 时间复杂度

快速排序的最优时间复杂度和平均时间复杂度为 $O(n\log n)$，最坏时间复杂度为 $O(n^2)$。

## 优化

### 朴素优化思想

如果仅按照上文所述的基本思想来实现快速排序（或者是直接照抄模板）的话，那大概率是通不过 [P1177【模板】快速排序](https://www.luogu.com.cn/problem/P1177) 这道模板的。因为有毒瘤数据能够把朴素的快速排序卡成 $O(n^2)$。

所以，我们需要对朴素快速排序思想加以优化。较为常见的优化思路有以下三种[^ref3]。

- 通过 **三数取中（即选取第一个、最后一个以及中间的元素中的中位数）** 的方法来选择两个子序列的分界元素（即比较基准）。这样可以避免极端数据（如升序序列或降序序列）带来的退化；
- 当序列较短时，使用 **插入排序** 的效率更高；
- 每趟排序后，**将与分界元素相等的元素聚集在分界元素周围**，这样可以避免极端数据（如序列中大部分元素都相等）带来的退化。

下面列举了几种较为成熟的快速排序优化方式。

### 三路快速排序

三路快速排序（英语：3-way Radix Quicksort）是快速排序和 [基数排序](radix-sort.md) 的混合。它的算法思想基于 [荷兰国旗问题](https://en.wikipedia.org/wiki/Dutch_national_flag_problem) 的解法。

与原始的快速排序不同，三路快速排序在随机选取分界点 $m$ 后，将待排数列划分为三个部分：小于 $m$、等于 $m$ 以及大于 $m$。这样做即实现了将与分界元素相等的元素聚集在分界元素周围这一效果。

三路快速排序在处理含有多个重复值的数组时，效率远高于原始快速排序。其最佳时间复杂度为 $O(n)$。

三路快速排序实现起来非常简单。下面给出了一种三路快排的 C++ 实现，其表现在模板题中并不输给 STL 的 sort。

```cpp
// C++ Version
// 模板的T参数表示元素的类型，此类型需要定义小于（<）运算
template <typename T>
// arr为需要被排序的数组，len为数组长度
void quick_sort(T arr[], const int len) {
  if (len <= 1) return;
  // 随机选择基准（pivot）
  const T pivot = arr[rand() % len];
  // i：当前操作的元素
  // j：第一个等于pivot的元素
  // k：第一个大于pivot的元素
  int i = 0, j = 0, k = len;
  // 完成一趟三路快排，将序列分为：小于pivot的元素 ｜ 等于pivot的元素 ｜
  // 大于pivot的元素
  while (i < k) {
    if (arr[i] < pivot)
      swap(arr[i++], arr[j++]);
    else if (pivot < arr[i])
      swap(arr[i], arr[--k]);
    else
      i++;
  }
  // 递归完成对于两个子序列的快速排序
  quick_sort(arr, j);
  quick_sort(arr + k, len - k);
}
```

```python
# Python Version
def quick_sort(arr, l, r):
    if l >= r:
        return
    random_index = random.randint(l, r)
    pivot = arr[random_index]
    arr[l], arr[random_index] = arr[random_index], arr[l]
    i = l + 1
    j = l 
    k = r + 1
    while i < k:
        if arr[i] < pivot:
            arr[i], arr[j + 1] = arr[j + 1], arr[i]
            j += 1
            i += 1
        elif arr[i] > pivot:
            arr[i], arr[k - 1] = arr[k - 1], arr[i]
            k -= 1
        else: 
            i += 1
    arr[l], arr[j] = arr[j], arr[l]
    quick_sort(arr, l, j - 1)
    quick_sort(arr, k, r)
```

### 内省排序[^ref4]

内省排序（英语：Introsort 或 Introspective sort）是快速排序和 [堆排序](heap-sort.md) 的结合，由 David Musser 于 1997 年发明。内省排序其实是对快速排序的一种优化，保证了最差时间复杂度为 $O(n\log n)$。

内省排序将快速排序的最大递归深度限制为 $\lfloor \log_2n \rfloor$，超过限制时就转换为堆排序。这样既保留了快速排序内存访问的局部性，又可以防止快速排序在某些情况下性能退化为 $O(n^2)$。

从 2000 年 6 月起，SGI C++ STL 的 `stl_algo.h` 中 `sort()` 函数的实现采用了内省排序算法。

## 线性找第 k 大的数

在下面的代码示例中，第 $k$ 大的数被定义为序列排成升序时，第 $k$ 个位置上的数（编号从 0 开始）。

找第 $k$ 大的数（K-th order statistic），最简单的方法是先排序，然后直接找到第 $k$ 大的位置的元素。这样做的时间复杂度是 $O(n\log n)$，对于这个问题来说很不划算。

我们可以借助快速排序的思想解决这个问题。考虑快速排序的划分过程，在快速排序的「划分」结束后，数列 $A_{p} \cdots A_{r}$ 被分成了 $A_{p} \cdots A_{q}$ 和 $A_{q+1} \cdots A_{r}$，此时可以按照左边元素的个数（$q - p + 1$）和 $k$ 的大小关系来判断是只在左边还是只在右边递归地求解。

可以证明，在期望意义下，程序的时间复杂度为 $O(n)$。

### 实现（C++）

```cpp
// 模板的T参数表示元素的类型，此类型需要定义小于（<）运算
template <typename T>
// arr为查找范围数组，rk为需要查找的排名（从0开始），len为数组长度
T find_kth_element(T arr[], int rk, const int len) {
  if (len <= 1) return arr[0];
  // 随机选择基准（pivot）
  const T pivot = arr[rand() % len];
  // i：当前操作的元素
  // j：第一个等于pivot的元素
  // k：第一个大于pivot的元素
  int i = 0, j = 0, k = len;
  // 完成一趟三路快排，将序列分为：小于pivot的元素 ｜ 等于pivot的元素 ｜
  // 大于pivot的元素
  while (i < k) {
    if (arr[i] < pivot)
      swap(arr[i++], arr[j++]);
    else if (pivot < arr[i])
      swap(arr[i], arr[--k]);
    else
      i++;
  }
  // 根据要找的排名与两条分界线的位置，去不同的区间递归查找第k大的数
  // 如果小于pivot的元素个数比k多，则第k大的元素一定是一个小于pivot的元素
  if (rk < j) return find_kth_element(arr, rk, j);
  // 否则，如果小于pivot和等于pivot的元素加起来也没有k多，则第k大的元素一定是一个大于pivot的元素
  else if (rk >= k)
    return find_kth_element(arr + k, rk - k, len - k);
  // 否则，pivot就是第k大的元素
  return pivot;
}
```

## 参考资料与注释

[^ref1]: [C++ 性能榨汁机之局部性原理 - I'm Root lee !](http://irootlee.com/juicer_locality/)

[^ref2]: [算法实现/排序/快速排序 - 维基教科书，自由的教学读本](https://zh.wikibooks.org/wiki/%E7%AE%97%E6%B3%95%E5%AE%9E%E7%8E%B0/%E6%8E%92%E5%BA%8F/%E5%BF%AB%E9%80%9F%E6%8E%92%E5%BA%8F)

[^ref3]: [三种快速排序以及快速排序的优化](https://blog.csdn.net/insistGoGo/article/details/7785038)

[^ref4]: [introsort](https://en.wikipedia.org/wiki/Introsort)
