STL 提供了大约 100 个实现算法的模版函数，基本都包含在 `<algorithm>` 之中，还有一部分包含在 `<numeric>` 和 `<functional>` 。完备的函数列表请 [参见参考手册](https://zh.cppreference.com/w/cpp/algorithm) ，排序相关的可以参考 [排序内容的对应页面](../../basic/stl-sort.md) 。

-    `find` ：顺序查找。 `find(v.begin(), v.end(), value)` ，其中 `value` 为需要查找的值。
-    `find_end` ：逆序查找。 `find_end(v.begin(), v.end(), value)` 。
-    `reverse` ：翻转数组、字符串。 `reverse(v.begin(), v.end())` 或 `reverse(a + begin, a + end)` 。
-    `unique` ：去除容器中相邻的重复元素。 `unique(ForwardIterator first, ForwardIterator last)` ，返回值为指向 **去重后** 容器结尾的迭代器，原容器大小不变。与 `sort` 结合使用可以实现完整容器去重。
-    `random_shuffle` ：随机地打乱数组。 `random_shuffle(v.begin(), v.end())` 或 `random_shuffle(v + begin, v + end)` 。
-    `sort` ：排序。 `sort(v.begin(), v.end(), cmp)` 或 `sort(a + begin, a + end, cmp)` ，其中 `end` 是排序的数组最后一个元素的后一位， `cmp` 为自定义的比较函数。
-    `stable_sort` ：稳定排序，用法同 `sort()` 。
-    `nth_element` ：按指定范围进行分类，即找出序列中第 $n$ 大的元素，使其左边均为小于它的数，右边均为大于它的数。 `nth_element(v.begin(), v.begin() + mid, v.end(), cmp)` 或 `nth_element(a + begin, a + begin + mid, a + end, cmp)` 。
-    `binary_search` ：二分查找。 `binary_search(v.begin(), v.end(), value)` ，其中 `value` 为需要查找的值。
-    `merge` ：将两个（已排序的）序列合并。 `merge(v1.begin(), v1.end(), v2.begin(), v2.end())` 。
-    `lower_bound` ：在一个有序序列中进行二分查找，返回指向第一个 **大于等于**  $x$ 的元素的位置的迭代器。如果不存在这样的元素，则返回尾迭代器。 `lower_bound(v.begin(),v.end(),x)` 。
-    `upper_bound` ：在一个有序序列中进行二分查找，返回指向第一个 **大于**  $x$ 的元素的位置的迭代器。如果不存在这样的元素，则返回尾迭代器。 `upper_bound(v.begin(),v.end(),x)` 。

???+warning "`lower_bound` 和 `upper_bound` 的时间复杂度"
    在一般的数组里，这两个函数的时间复杂度均为 $O(\log n)$ ，但在 `set` 等关联式容器中，直接调用 `lower_bound(s.begin(),s.end(),val)` 的时间复杂度是 $O(n)$ 的。
    
     `set` 等关联式容器中已经封装了 `lower_bound` 等函数（像 `s.lower_bound(val)` 这样），这样调用的时间复杂度是 $O(\log n)$ 的。
