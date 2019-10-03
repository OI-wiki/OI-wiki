基数排序是将待排序的元素拆分为 $k$ 个关键字（比较两个元素时，先比较第一关键字，如果相同再比较第二关键字……），然后先对第 $k$ 关键字进行稳定排序，再对第 $k-1$ 关键字进行稳定排序，再对第 $k-2$ 关键字进行稳定排序……最后对第一关键字进行稳定排序，这样就完成了对整个待排序序列的稳定排序。

基数排序的正确性可以自己感性理解一下，也可以参考 <https://walkccc.github.io/CLRS/Chap08/8.3/#83-3> 。

一般来说，每个关键字的值域都不大，就可以使用 [计数排序](./counting-sort.md) 作为内层排序，复杂度为 $O(nk+\sum\limits_{i=1}^k w_i)$ ，其中 $w_i$ 为第 $i$ 关键字的值域大小。

（如果关键字值域很大，就可以直接使用基于比较的 $O(nk\log n)$ 排序而无需使用基数排序了。）

伪代码：

$$
\begin{array}{ll}
1 & \textbf{Input. } \text{An array } A \text{ consisting of }n\text{ elements, where each element has }k\text{ keys.}\\
2 & \textbf{Output. } \text{Array }A\text{ will be sorted in nondecreasing order stably.} \\
3 & \textbf{Method. }  \\
4 & \textbf{for }i\gets k\textbf{ down to }1\\
5 & \qquad\text{sort }A\text{ into nondecreasing order by the }i\text{-th key stably}
\end{array}
$$

C++ 代码：

```cpp
const int N = 100010;
const int W = 100010;
const int K = 100;

int n, w[K], k, cnt[W];

struct Element {
  int key[K];
  bool operator<(const Element& y) const  // shows how two elements are compared
  {
    for (int i = 1; i <= k; ++i) {
      if (key[i] == y.key[i]) continue;
      return key[i] < y.key[i];
    }
    return false;
  }
} a[N], b[N];

void counting_sort(int p) {
  memset(cnt, 0, sizeof(cnt));
  for (int i = 1; i <= n; ++i) ++cnt[a[i].key[p]];
  for (int i = 1; i <= w[p]; ++i) cnt[i] += cnt[i - 1];
  for (int i = 1; i <= n; ++i) b[cnt[a[i].key[p]]--] = a[i];
  memcpy(a, b, sizeof(a));
}

void radix_sort() {
  for (int i = k; i >= 1; --i) {
    counting_sort(i);
  }
}
```
