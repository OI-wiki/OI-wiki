##  `set` 

 `set` 是关联容器，含有键值类型对象的已排序集，搜索、移除和插入拥有对数复杂度。 `set` 内部通常采用红黑树实现。

和数学中的集合相似， `set` 中不会出现值相同的元素。

### 插入与删除操作

-    `insert(x)` 当容器中没有等价元素的时候，将元素 x 插入到 `set` 中。
-    `erase(x)` 删除值为 x 的元素，返回删除元素的个数。
-    `erase(pos)` 删除迭代器为 pos 的元素，要求迭代器必须合法。
-    `erase(first,last)` 删除迭代器在 $[first,last)$ 范围内的所有元素。
-    `clear()` 清空 `set` 。

???+note "insert 函数的返回值"
    insert 函数的返回值类型为 `pair<iterator, bool>` ，其中 iterator 是一个指向所插入元素（或者是指向等于所插入值的原本就在容器中的元素）的迭代器，而 bool 则代表元素是否插入成功，由于 `set` 中的元素具有唯一性质，所以如果在 `set` 中已有等值元素，则插入会失败，返回 false，否则插入成功，返回 true； `map` 中的 insert 也是如此。

### 迭代器

 `set` 提供了以下几种迭代器：

1.   `begin()/cbegin()`   
    返回指向首元素的迭代器，其中 `*begin = front` 。
2.   `end()/cend()`   
    返回指向数组尾端占位符的迭代器，注意是没有元素的。
3.   `rbegin()/rcbegin()`   
    返回指向逆向数组的首元素的逆向迭代器，可以理解为正向容器的末元素。
4.   `rend()/rcend()`   
    返回指向逆向数组末元素后一位置的迭代器，对应容器首的前一个位置，没有元素。

以上列出的迭代器中，含有字符 `c` 的为只读迭代器，你不能通过只读迭代器去修改 `set` 中的元素的值。如果一个 `set` 本身就是只读的，那么它的一般迭代器和只读迭代器完全等价。只读迭代器自 C++11 开始支持。

### 查找操作

-    `count(x)` 返回 `set` 内键为 x 的元素数量。
-    `find(x)` 在 `set` 内存在键为 x 的元素时会返回该元素的迭代器，否则返回 `end()` 。
-    `lower_bound(x)` 返回指向首个不小于给定键的元素的迭代器。
-    `upper_bound(x)` 返回指向首个大于给定键的元素的迭代器。
-    `empty()` 返回容器是否为空。
-    `size()` 返回容器内元素个数。

##  `multiset` 

 `multiset` 是关联容器，含有键值类型对象的已排序集，搜索、移除和插入拥有对数复杂度。

与 `set` 不同的是， `multiset` 允许不同元素间拥有相同的值。

### 插入与删除操作

-    `insert(x)` 将元素 x 插入到 `multiset` 中。
-    `erase(x)` 删除值为 x 的 **所有** 元素，返回删除元素的个数。
-    `erase(pos)` 删除迭代器为 pos 的元素，要求迭代器必须合法。
-    `erase(first,last)` 删除迭代器在 $[first,last)$ 范围内的所有元素。
-    `clear()` 清空 `multiset` 。

### 迭代器

 `multiset` 的迭代器和 `set` 的 [迭代器](#_2) 类似，这里不再赘述。

### 查找操作

 `multiset` 的查找操作和 `set` 的 [查找操作](#_3) 类似，这里不再赘述。

##  `map` 

 `map` 是有序键值对（Attribute–value pair）容器，它的元素的键是唯一的。搜索、移除和插入操作拥有对数复杂度。 `map` 通常实现为红黑树。

你可能需要存储一些键值对，例如存储学生姓名对应的分数： `Tom 0` ， `Bob 100` ， `Alan 100` 。
但是由于数组下标只能为非负整数，所以无法用姓名作为下标来存储，这个时候最简单的办法就是使用 STL 中的 `map` 了！

 `map` 重载了 `operator[]` ，可以用任意定义了 `operator <` 的类型作为下标（在 `map` 中叫做 `key` ，也就是索引）：

```cpp
map<Key, T> yourMap;
```

其中， `Key` 是键的类型， `T` 是值的类型，下面是使用 `map` 的实例：

```cpp
map<string, int> mp;
```

### 添加元素

1.  直接赋值，例如 `mp["Tom"]=0` 
2.  通过插入一个类型为 `pair<Key, T>` 的值，例如 `mp.insert(pair<string,int>("Alan",100));` 
3.  使用 `initializer_list` ：

```cpp
map<string, int> mp = {{"Tom", 0}, {"Bob", "100"}, {"Alan", 100}};
```

### 查找、修改元素

1.  使用赋值语法： `int grade=mp["Tom"]` 。
2.  使用成员函数 `iterator find( const Key& key );` 来确定一个索引是否在 `map` 中。它会返回指向该元素的迭代器；如果索引不在 `map` 中，则会返回尾后迭代器 `mp.end()` 。
3.  如果你想获得 `map` 里全部的元素，请使用迭代器，解引用迭代器会得到一个类型为 `pair<Key, T>` 的值：

```cpp
for (iter = mp.begin(); iter != mp.end(); ++iter)
  cout << iter->first << " " << iter->second << endl;
```

其中使用 `mp.begin()` 可以得到指向 `map` 首元素的迭代器。
如果使用 C++11（及以上），还可以使用 C++11 的范围 for 循环

```cpp
for (auto &i : mp) {
  printf("Key : %d, Value : %d\n", i.first, i.second);
}
```

使用迭代器遍历大小为 $n$ 的 `map` 的时间复杂度是 $O(n)$ 。

### 删除元素

如果你想删除 `Tom` 这个元素，则可以利用 `find` 函数找到 `Tom` ，然后再 `erase` 如下

```cpp
map<string, int>::iterator it;
it = mp.find("Tom");
mp.erase(it)
```

如果你想清空所有的元素，可以直接 `mp.clear()` 

### 其他函数

-    `count` 返回匹配特定键的元素出现的次数，例如 `mp.count("Tom")` 。
-    `swap` 可以交换两个 `map` ，例如 `swap(m1,m2)` 。
-    `size` 返回 `map` 中元素的个数。
-    `empty` 如果 `map` 为空则返回 `true` ，例如 `mp.empty()` 。

##  `multimap` 

和 `map` 类似， `multimap` 是有序键值对容器，但允许多个元素拥有同一键。其搜索、插入操作拥有对数复杂度。删除单个元素在最坏情况下具有对数复杂度，均摊为常数复杂度。

!!! warning
    正是因为 multimap 允许多个元素拥有同一键的特点，multimap 并没有提供给出键访问其对应值的方法。

### 插入与删除操作

-   通过向 `multimap` 中插入一个类型为 `pair<Key, T>` 的值可以达到插入元素的目的，例如 `mp.insert(pair<string,int>("Alan",100));` ；
-    `erase(x)` : 删除键为 x 的 **所有** 元素，返回删除元素的个数。
-    `erase(pos)` : 删除迭代器为 pos 的元素，要求迭代器必须合法。
-    `erase(first,last)` : 删除迭代器在 $[first,last)$ 范围内的所有元素。
-    `clear()` : 清空容器。

### 查找操作

-    `count(x)` : 返回容器内键为 x 的元素数量。复杂度为 $O(\log(size)+ans)$ （关于容器大小对数复杂度，加上匹配个数）。
-    `find(x)` : 若容器内存在键为 x 的元素，会返回该元素的迭代器（如果有多个键为 x 的元素会返回任意一个）；否则返回 `end()` 。
-    `lower_bound(x)` : 返回指向首个不小于给定键的元素的迭代器。
-    `upper_bound(x)` : 返回指向首个大于给定键的元素的迭代器。若容器内所有元素均小于或等于给定键，返回 `end()` 。
-    `empty()` : 返回容器是否为空。
-    `size()` : 返回容器内元素个数。
