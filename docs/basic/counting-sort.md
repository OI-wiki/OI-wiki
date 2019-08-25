计数排序是一种复杂度为 $O(n+w)$ 的稳定排序，其中 $w$ 代表待排序数据的值域大小。

计数排序分为三个步骤：

1.  计算每个数出现了几次。
2.  求出每个数出现次数的前缀和。
3.  利用出现次数的前缀和，从右至左计算每个数的排名。

伪代码：

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

C++ 代码：

```cpp
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
