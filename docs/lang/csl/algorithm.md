STL 提供了大约 100 个实现算法的模版函数，基本都包含在 `<algorithm>` 之中，还有一部分包含在 `<numeric>` 和 `<functional>` 。完备的函数列表请 [参见参考手册](https://zh.cppreference.com/w/cpp/algorithm) ，排序相关的可以参考 [排序内容的对应页面](../../basic/stl-sort.md) 。

-  `find` ：顺序查找。 `find(v.begin(), v.end(), value)` ，其中 `value` 为需要查找的值。
-  `find_end` ：逆序查找。 `find_end(v.begin(), v.end(), value)` 。
-  `reverse` ：翻转数组、字符串。 `reverse(v.begin(), v.end())` 或 `reverse(a + begin, a + end)` 。
-  `unique` ：去除容器中相邻的重复元素。 `unique(ForwardIterator first, ForwardIterator last)` ，返回值为指向 **去重后** 容器结尾的迭代器，原容器大小不变。与 `sort` 结合使用可以实现完整容器去重。
-  `random_shuffle` ：随机地打乱数组。 `random_shuffle(v.begin(), v.end())` 或 `random_shuffle(v + begin, v + end)` 。

???+warning "`random_shuffle` 函数在最新 C++ 标准中已被移除"
     `random_shuffle` 自 C++14 起被弃用，C++17 起被移除。
    
    在 C++11 以及更新的标准中，您可以使用 `shuffle` 函数代替原来的 `random_shuffle` 。使用方法为 `shuffle(v.begin(),v.end(),rand)` （最后一个参数传入的是使用的随机数生成器，一般情况下传入 `rand` 即可）。

-  `sort` ：排序。 `sort(v.begin(), v.end(), cmp)` 或 `sort(a + begin, a + end, cmp)` ，其中 `end` 是排序的数组最后一个元素的后一位， `cmp` 为自定义的比较函数。
-  `stable_sort` ：稳定排序，用法同 `sort()` 。
-  `nth_element` ：按指定范围进行分类，即找出序列中第 $n$ 大的元素，使其左边均为小于它的数，右边均为大于它的数。 `nth_element(v.begin(), v.begin() + mid, v.end(), cmp)` 或 `nth_element(a + begin, a + begin + mid, a + end, cmp)` 。
-  `binary_search` ：二分查找。 `binary_search(v.begin(), v.end(), value)` ，其中 `value` 为需要查找的值。
-  `merge` ：将两个（已排序的）序列合并。 `merge(v1.begin(), v1.end(), v2.begin(), v2.end())` 。
-  `lower_bound` ：在一个有序序列中进行二分查找，返回指向第一个 **大于等于**  $x$ 的元素的位置的迭代器。如果不存在这样的元素，则返回尾迭代器。 `lower_bound(v.begin(),v.end(),x)` 。
-  `upper_bound` ：在一个有序序列中进行二分查找，返回指向第一个 **大于**  $x$ 的元素的位置的迭代器。如果不存在这样的元素，则返回尾迭代器。 `upper_bound(v.begin(),v.end(),x)` 。

???+warning "`lower_bound` 和 `upper_bound` 的时间复杂度"
    在一般的数组里，这两个函数的时间复杂度均为 $O(\log n)$ ，但在 `set` 等关联式容器中，直接调用 `lower_bound(s.begin(),s.end(),val)` 的时间复杂度是 $O(n)$ 的。
    
     `set` 等关联式容器中已经封装了 `lower_bound` 等函数（像 `s.lower_bound(val)` 这样），这样调用的时间复杂度是 $O(\log n)$ 的。

-  `next_permutation` ：将当前排列更改为 **全排列中的下一个排列** 。如果当前排列已经是 **全排列中的最后一个排列** （元素完全从大到小排列），函数返回 `false` 并将排列更改为 **全排列中的第一个排列** （元素完全从小到大排列）；否则，函数返回 `true` 。 `next_permutation(v.begin(), v.end())` 或 `next_permutation(v + begin, v + end)` 。
-  `partial_sum` ：求前缀和。设源容器为 $x$ ，目标容器为 $y$ ，则令 $y[i]=x[0]+x[1]+...+x[i]$ 。 `partial_sum(src.begin(), src.end(), back_inserter(dst))` 。

### 使用样例

- 使用 `next_permutation` 生成 $1$ 到 $9$ 的全排列

```cpp
int N = 9, a[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
do {
  for (int i = 0; i < N; i++) cout << a[i] << " ";
  cout << endl;
} while (next_permutation(a, a + N));
```

- 使用 `lower_bound` 与 `upper_bound` 查找小于 $x$ ，等于 $x$ ，大于 $x$ 元素的分界线

```cpp
int N = 10, a[] = {1, 1, 2, 4, 5, 5, 7, 7, 9, 9}, x = 5;
int i = lower_bound(a, a + N, x) - a, j = upper_bound(a, a + N, x) - a;
// a[0] ~ a[i - 1] 为小于x的元素， a[i] ~ a[j - 1] 为等于x的元素， a[j] ~ a[N -
// 1] 为大于x的元素
cout << i << " " << j << endl;
```

- 使用 `partial_sum` 求解 `src` 中元素的前缀和，并存储于 `dst` 中。

```cpp
vector<int> src = {1, 2, 3, 4, 5}, dst;
// 求解src中元素的前缀和，dst[i] = src[0] + ... + src[i]
// back_inserter 函数作用在 dst 容器上，提供一个迭代器
partial_sum(src.begin(), src.end(), back_inserter(dst));
for (unsigned int i = 0; i < dst.size(); i++) cout << dst[i] << " ";
```
