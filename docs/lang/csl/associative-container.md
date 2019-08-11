##  `set`

##  `multiset`

##  `map`

 `map` 是有序键值对（Attribute–value pair）容器，它的元素的键是唯一的。搜索、移除和插入操作拥有对数复杂度。 `map` 通常实现为红黑树。

你可能需要存储一些键值对，例如存储学生姓名对应的分数： `Tom 0` ， `Bob 100` ， `Alan 100` 。
但是由于数组下标只能为非负整数，所以无法用姓名作为下标来存储，这个时候最简单的办法就是使用 STL 中的 `map` 了！

 `map` 重载了 `operator[]` ，因此可以用任意类型作为下标（在 `map` 中叫做 `key` ，也就是索引）：

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

使用迭代器遍历大小为 $n$ 的 `map` 的时间复杂度是 $O(n)$。

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
