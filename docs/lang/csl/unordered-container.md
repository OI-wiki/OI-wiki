## 概述

自 C++11 标准起，四种基于哈希实现的无序关联式容器正式纳入了 C++ 的标准模板库中，分别是： `unordered_set` ， `unordered_multiset` ， `unordered_map` ， `unordered_multimap` 。

它们与相应的关联式容器在功能，函数等方面有诸多共同点，而最大的不同点则体现在普通的关联式容器一般采用红黑树实现，内部元素按特定顺序进行排序；而这几种无序关联式容器则采用哈希方式存储元素，内部元素不以任何特定顺序进行排序。

采用哈希存储的特点使得无序关联式容器 **在平均情况下** 大多数操作（包括查找，插入，删除）都能在常数时间复杂度内完成，相较于关联式容器与容器大小成对数的时间复杂度更加优秀。

!!! warning
     **在最坏情况下，对无序关联式容器的操作时间复杂度会与容器大小成线性！** 这一情况往往在容器内出现大量哈希冲突时产生，因此在不保证数据随机的场合应谨慎使用无序关联式容器存储数据。

由于无序关联式容器与相应的关联式容器有很多共同点，这里主要对无序关联式容器的一些特殊之处进行介绍，而对于无序关联式容器与关联式容器的共同点则略去，这些内容读者可以参考 [OI-wiki](./associative-container/) 的介绍。

##  `unordered_set` 

### 插入与删除操作

 `unordered_set` 的插入与删除操作与 `set` 的 [插入与删除操作](./associative-container/#_2) 相同，这里不再赘述。

### 迭代器

 `unordered_set` 提供了以下几种迭代器：

1.   `begin()/cbegin()`   
    返回指向首元素的迭代器，其中 `*begin = front` 。
2.   `end()/cend()`   
    返回指向数组尾端占位符的迭代器，注意是没有元素的。

!!! note
    因为内部采用哈希存储， `begin()` 并不一定指向容器中最小的元素。

以上列出的迭代器中，含有字符 `c` 的为只读迭代器，你不能通过只读迭代器去修改 `unordered_set` 中的元素的值。如果一个 `unordered_set` 本身就是只读的，那么它的一般迭代器和只读迭代器完全等价。只读迭代器自 C++11 开始支持。

### 查找操作

 `unordered_set` 的查找操作与 `set` 的 [查找操作](./associative-container/#_2) 相比，除了不提供 `lower_bound(x)` 和 `upper_bound(x)` 以外，其余均完全相同，这里不再赘述。

##  `unordered_multiset` 

### 插入与删除操作

 `unordered_multiset` 的插入与删除操作与 `multiset` 的 [插入与删除操作](./associative-container/#_4) 相同，这里不再赘述。

### 迭代器

 `unordered_multiset` 的迭代器和 `unordered_set` 的 [迭代器](#_3) 类似，这里不再赘述。

### 查找操作

 `unordered_multiset` 的查找操作与 `multiset` 的 [查找操作](./associative-container/#_6) 相比，除了不提供 `lower_bound(x)` 和 `upper_bound(x)` 以外，其余均完全相同，这里不再赘述。

##  `unordered_map` 

和 `map` 一样， `unordered_map` 也重载了 `[]` 运算符，这使得我们可以直接用键作为下标访问对应的值。

因 `unordered_map` 和 `map` 的函数功能类似，这里不再赘述，可以直接参考 [OI-wiki 对 `map` 的介绍](./associative-container/#map) 。

##  `unordered_multimap` 

因 `unordered_multimap` 和 `multimap` 的函数功能类似，这里不再赘述，可以直接参考 [OI-wiki 对 `multimap` 的介绍](./associative-container/#multimap) 。
