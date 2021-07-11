???+ warning
    本页面要介绍的不是 [**基数排序**](radix-sort.md)。

本页面将简要介绍计数排序。

## 简介

计数排序（英语：Counting sort）是一种线性时间的排序算法。

## 工作原理

计数排序的工作原理是使用一个额外的数组 $C$，其中第 $i$ 个元素是待排序数组 $A$ 中值等于 $i$ 的元素的个数，然后根据数组 $C$ 来将 $A$ 中的元素排到正确的位置。[^ref1]

它的工作过程分为三个步骤：

1. 计算每个数出现了几次；
2. 求出每个数出现次数的 [前缀和](prefix-sum.md)；
3. 利用出现次数的前缀和，从右至左计算每个数的排名。

## 性质

### 稳定性

计数排序是一种稳定的排序算法。

### 时间复杂度

计数排序的时间复杂度为 $O(n+w)$，其中 $w$ 代表待排序数据的值域大小。

## 代码实现

### 伪代码

$$
\begin{array}{ll}
1 & \textbf{Input. } \text{An array } A \text{ consisting of }n\text{ positive integers no greater than } w. \\
2 & \textbf{Output. } \text{Array }A\text{ after sorting in nondecreasing order stably.} \\
3 & \textbf{Method. }  \\
4 & \textbf{for }i\gets0\textbf{ to }w\\
5 & \qquad cnt[i]\gets0\\
6 & \textbf{for }i\gets1\textbf{ to }n\\
7 & \qquad cnt[A[i]]\gets cnt[A[i]]+1\\
8 & \textbf{for }i\gets1\textbf{ to }w\\
9 & \qquad cnt[i]\gets cnt[i]+cnt[i-1]\\
10 & \textbf{for }i\gets n\textbf{ downto }1\\
11 & \qquad B[cnt[A[i]]]\gets A[i]\\
12 & \qquad cnt[A[i]]\gets cnt[A[i]]-1\\
13 & \textbf{return } B
\end{array}
$$

### C++

```cpp
// C++ Version
const int N = 100010;
const int W = 100010;

int n, w, a[N], cnt[W], b[N];

void counting_sort() {
  memset(cnt, 0, sizeof(cnt));
  for (int i = 1; i <= n; ++i) ++cnt[a[i]];
  for (int i = 1; i <= w; ++i) cnt[i] += cnt[i - 1];
  for (int i = n; i >= 1; --i) b[cnt[a[i]]--] = a[i];
}
```

### Python

    # Python Version
    N = W = 100010
    n = w = 0
    a = b = [0] * N
    cnt = [0] * W

    def counting_sort():
        for i in range(1, n + 1):
            cnt[a[i]] += 1
        for i in range(1, w + 1):
            cnt[i] += cnt[i - 1]
        for i in range(n, 0, -1):
            b[cnt[a[i]] - 1] = a[i]
            cnt[a[i]] -= 1

## 参考资料与注释

[^ref1]: [计数排序 - 维基百科，自由的百科全书](https://zh.wikipedia.org/wiki/%E8%AE%A1%E6%95%B0%E6%8E%92%E5%BA%8F)
