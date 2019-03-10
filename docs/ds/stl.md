让我们一起来认识认识高端的 STL。

## 什么是 STL？

STL 是 Standard Template Library 的简称，中文名为标准模板库。它是 C++ 的一大特色，里面包含了许多标准算法或数据结构。

在 C++ 标准中，STL 被组织为下面的 13 个头文件： `<algorithm>` , `<deque>` , `<functional>` , `<iterator>` , `<array>` , `<vector>` , `<list>` , `<forward_list>` , `<map>` , `<unordered_map>` , `<memory>` , `<numeric>` , `<set>` , `<unordered_set>` , `<stack>` , `<utility>` 。

## 数据结构

### 序列式容器

 **向量** (vector) 连续存储的元素。

 **列表** (list) 由节点组成的双向链表，每个结点包含着一个元素。

 **双端队列** (deque) 连续存储的指向不同元素的指针所组成的数组。

### 适配器容器

 **栈** (stack) 后进先出的值的排列。

 **队列** (queue) 先进先出的值的排列。

 **优先队列** (priority_queue) 元素的次序是由作用于所存储的值对上的某种谓词决定的的一种队列。

### 关联式容器

 **集合** (set) 由节点组成的红黑树，每个节点都包含着一个元素，节点之间以某种作用于元素对的谓词排列，没有两个不同的元素能够拥有相同的次序。

 **多重集合** (multiset) 允许存在两个次序相等的元素的集合。

 **映射** (map) 由 {键，值} 对组成的集合，以某种作用于键对上的谓词排列。

 **多重映射** (multimap) 允许键对有相等的次序的映射。

## 算法

STL 提供了大约 100 个实现算法的模版函数，基本都包含在 `<algorithm>` 之中，还有一部分包含在 `<numeric>` 和 `<functional>` 。

常用函数：

-    `sort` ：排序。 `sort(v.begin(), v.end(), cmp)` 或 `sort(a + begin, a + end, cmp)` ，其中 `end` 是排序的数组最后一个元素的后一位， `cmp` 为自定义的比较函数。
-    `reverse` ：翻转数组、字符串。 `reverse(v.begin(), v.end())` 或 `reverse(a + begin, a + end)` 。
-    `nth_element` ：按指定范围进行分类，即找出序列中第 $n$ 大的元素，使其左边均为小于它的数，右边均为大于它的数。 `nth_element(v.begin(), v.begin() + mid, v.end(), cmp)` 或 `nth_element(a + begin, a + begin + mid, a + end, cmp)` 。
-    `random_shuffle` ：随机地打乱数组。 `random_shuffle(v.begin(), v.end())` 或 `random_shuffle(v + begin, v + end)` 。

## 参考

<https://en.cppreference.com/w/>

<http://www.cplusplus.com/reference/>
