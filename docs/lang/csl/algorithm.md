STL 提供了大约 100 个实现算法的模版函数，基本都包含在 `<algorithm>` 之中，还有一部分包含在 `<numeric>` 和 `<functional>` 。

常用函数：

-    `sort` ：排序。 `sort(v.begin(), v.end(), cmp)` 或 `sort(a + begin, a + end, cmp)` ，其中 `end` 是排序的数组最后一个元素的后一位， `cmp` 为自定义的比较函数。
-    `reverse` ：翻转数组、字符串。 `reverse(v.begin(), v.end())` 或 `reverse(a + begin, a + end)` 。
-    `nth_element` ：按指定范围进行分类，即找出序列中第 $n$ 大的元素，使其左边均为小于它的数，右边均为大于它的数。 `nth_element(v.begin(), v.begin() + mid, v.end(), cmp)` 或 `nth_element(a + begin, a + begin + mid, a + end, cmp)` 。复杂度 $\mathcal O(n)$ 。
-    `random_shuffle` ：随机地打乱数组。 `random_shuffle(v.begin(), v.end())` 或 `random_shuffle(v + begin, v + end)` 。
