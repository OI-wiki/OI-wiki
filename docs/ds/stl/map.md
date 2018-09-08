### `map` 是啥鬼？

`map` 是利用红黑树实现的。

当你在写程序的时候，可能需要存储一些信息，例如存储学生姓名对应的分数，例如：`Tom 0`，`Bob 100`，`Alan 100`。
但是由于数组下标只能为非负整数，所以无法用姓名来存储，这个时候最简单的办法就是使用 STL 的 `map` 了！

`map` 可任意类型为下标（在 `map` 中叫做 `key`，也就是索引），下面是 `map` 的模型：

```cpp
map <类型名,类型名> 你想给map起的名字
```

其中两个类型名第一个是 `key`（索引，可以理解为数组的下标），第二个是 `value`（对应的元素）。例如上面的例子，我们可以这样的存储：

```cpp
map <string,int> mp
```

是不是感觉很神奇？

### `map`  具体怎么使用？

- `map` 添加元素

1\. 直接存，例如 `mp["Tom"]=0`

2\. 通过插入，例如 `mp.insert(pair<string,int>("Alan",100));`

3\. 初始化（ C++11 及以上）和数组差不多：

```cpp
map <string,int> mp= {
                {"Tom",0},
                {"Bob","100"},
                {"Alan",100}};
```

- `map` 查找删除元素

1\. 在你知道查找元素是啥的时候直接来就可以了，例如：`int grade=mp["Tom"]`

2\. 如果你知道了元素的下标，但是想知道这个元素是否已经存在 `map` 中，可以使用 `find` 函数。

格式：`if(mp.find()==mp.end())`，意思是是否返回的是 `map` 的末尾，因为 `map` 如果没有查找到元素，迭代器会返回末尾。

其中 `mp.end()` 返回指向 map 尾部的迭代器， 另外 也可以用 `mp.count(__key) != 0` 来判断

3\. 如果你想知道 map 里全部的元素，那么最正确的做法使用迭代器了，如果你还不会，请查阅之前文章中的迭代器。

```cpp
for(iter=mp.begin();iter!=mp.end();iter++)
        cout<<iter->first<<" "<<iter->second<<endl;
```

其中 `mp.begin()` 返回指向 `map` 头部的迭代器
当然，如果使用 C++11 （及以上）你还可以使用 C++11 的新特性 ，如下

```cpp
  for(auto &i : mp) {
      printf("Key : %d, Value : %d\n", i.first, i.second);
  }
```

`iter->first` 是 `key` 索引，例如 `Tom`，而 `iter->second` 是 `value`。

如果你想删除 `Tom` 这个元素，则可以利用 `find` 函数找到 `Tom` ，然后再 `erase` 如下

```cpp
map<string, int> :: iterator it;
it = mp.find("Tom");
mp.erase(it)
```

如果你想清空所有的元素，可以直接 `mp.clear()`

- 其他

我们刚才介绍了最常用的，下面是其他比较常用的：

- `count()` 返回指定元素出现的次数 ，例如 `mp.count()`

- `swap()` 可以交换两个 `map` ，例如 `swap(m1,m2)`

-   `size()` 返回 `map` 中元素的个数
       
- `empty()` 如果 `map` 为空则返回 `true`，例如 `mp.empty()`。

### `map` 常数靠得住吗？

一般情况下是可以的。无论查询，插入，删除的复杂度都是 $O(\log N)$，遍历是 $O(N)$。

不过有的时候不会满足啊！我只想查询元素，插入元素，但是时间不够咋办？请往下看！

- 由于 NOIP 不资瓷吸氧（开启 O2 优化），所以 NOIP 要注意是否会被卡

### 更快：基于 `Hash` 实现的 `map`！

这个 `map` 的名字就是 `unordered_map` 了，它的查询，插入，删除的复杂度几乎是 $O(1)$ 级别（不过最坏会达到 $O(N)$）的！所有的操作几乎和 `map`一样（注意 `unordered_map` 用迭代器遍历是无序的）。

不过它的遍历速度会很慢，而且空间占用的会更大。
