桶排序适用于待排序数据值域较大但分布比较均匀的情况，是一个期望时间复杂度为 $O(n)$ 的排序算法。

其大致思想是对值域进行分块，每块分别排序。由于每块元素不多，一般使用插入排序。如果使用稳定的内层排序，并且将元素插入桶中时不改变相对顺序，那么桶排序就是稳定的。

如果待排序数据是随机生成的，将值域平均分成 $n$ 块的期望时间复杂度是 $O(n)$ ，证明可以参考算法导论或 [维基百科](https://en.wikipedia.org/wiki/Bucket_sort) 。

C++ 代码：

```cpp
const int N = 100010;

int n, w, a[N];
vector<int> bucket[N];

void insertion_sort(vector<int>& A) {
  for (int i = 1; i < A.size(); ++i) {
    int key = A[i];
    int j = i - 1;
    while (j >= 0 && A[j] > key) {
      A[j + 1] = A[j];
      --j;
    }
    A[j + 1] = key;
  }
}

void bucket_sort() {
  int bucket_size = w / n + 1;
  for (int i = 0; i < n; ++i) {
    bucket[i].clear();
  }
  for (int i = 1; i <= n; ++i) {
    bucket[a[i] / bucket_size].push_back(a[i]);
  }
  int p = 0;
  for (int i = 0; i < n; ++i) {
    insertion_sort(bucket[i]);
    for (int j = 0; j < bucket[i].size(); ++j) {
      a[++p] = bucket[i][j];
    }
  }
}
```
