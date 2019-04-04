让我们一起来认识认识高端的 STL。

## 什么是 STL？

STL 是 Standard Template Library 的简称，中文名为标准模板库。它是 C++ 的一大特色，里面包含了许多标准算法或数据结构。

在 C++ 标准中，STL 被组织为下面的若干个头文件： `<algorithm>` , `<deque>` , `<functional>` , `<iterator>` , `<array>` , `<vector>` , `<list>` , `<forward_list>` , `<map>` , `<unordered_map>` , `<memory>` , `<numeric>` , `<queue>`, `<set>` , `<unordered_set>` , `<stack>` , `<utility>` 。

## 容器

### 分类

#### 序列式容器

 **向量** (vector) 连续存储的元素。

 **列表** (list) 由节点组成的双向链表，每个结点包含着一个元素。

 **双端队列** (deque) 连续存储的指向不同元素的指针所组成的数组。

#### 关联式容器

 **集合** (set) 由节点组成的红黑树，每个节点都包含着一个元素，节点之间以某种作用于元素对的谓词排列，没有两个不同的元素能够拥有相同的次序。

 **多重集合** (multiset) 允许存在两个次序相等的元素的集合。

 **映射** (map) 由 {键，值} 对组成的集合，以某种作用于键对上的谓词排列。

 **多重映射** (multimap) 允许键对有相等的次序的映射。

#### 容器适配器

 容器适配器其实并不是容器。它们不具有容器的某些特点（如：有迭代器、有 `max_size()` 函数……）。

>  ”适配器是使一种事物的行为类似于另外一种事物行为的一种机制”，适配器对容器进行包装，使其表现出另外一种行为。

 **栈** (stack) 后进先出的值的排列。

 **队列** (queue) 先进先出的值的排列。

 **优先队列** (priority_queue) 元素的次序是由作用于所存储的值对上的某种谓词决定的的一种队列。

### 共同点

#### 容器声明

都是 `containerName<typeName,...> name`  的形式，但模板参数（`<>` 内的参数）的个数、形式会根据具体容器而变。

本质原因：STL 就是 “标准模板库”，所以容器都是模板类。

#### 迭代器

STL 容器中的元素都可以用迭代器指向。

迭代器是一种类似指针的东西，可以通过 `containerName<typeName,...>::iterator` 来声明，通过 `*it` 来访问所指向的元素，通过 `++`/`--` 来访问下一个/上一个元素。

迭代器分为输入/输出迭代器、正向/反向迭代器、随机访问迭代器。

#### 共有函数

`begin()/rbegin()`：返回指向开头/末尾元素的正向/反向迭代器。

`end()/rend()`：返回指向末尾/开头的下一个元素的正向/反向迭代器。`end()` 不指向某个元素，但它是末尾元素的后继。

`size()`：返回容器内的元素个数。

`max_size()`：返回容器 **理论上** 能存储的最大元素个数。依容器类型和所存储变量的类型而变。

`empty()`：返回容器是否为空。

`swap()`：交换两个容器。

`==`/`!=`/`<`/`>`/`<=`/`>=`：按 **字典序** 比较两个容器的大小。

## 算法

STL 提供了大约 100 个实现算法的模版函数，基本都包含在 `<algorithm>` 之中，还有一部分包含在 `<numeric>` 和 `<functional>` 。

常用函数：

-    `sort` ：排序。 `sort(v.begin(), v.end(), cmp)` 或 `sort(a + begin, a + end, cmp)` ，其中 `end` 是排序的数组最后一个元素的后一位， `cmp` 为自定义的比较函数。
-    `reverse` ：翻转数组、字符串。 `reverse(v.begin(), v.end())` 或 `reverse(a + begin, a + end)` 。
-    `nth_element` ：按指定范围进行分类，即找出序列中第 $n$ 大的元素，使其左边均为小于它的数，右边均为大于它的数。 `nth_element(v.begin(), v.begin() + mid, v.end(), cmp)` 或 `nth_element(a + begin, a + begin + mid, a + end, cmp)` 。
-    `random_shuffle` ：随机地打乱数组。 `random_shuffle(v.begin(), v.end())` 或 `random_shuffle(v + begin, v + end)` 。
-    `swap(x,y)`：交换两个元素的值。

## 参考

<https://en.cppreference.com/w/>

<http://www.cplusplus.com/reference/>

《C++ Primer Plus》
