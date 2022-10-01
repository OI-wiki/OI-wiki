author: sbofgayschool

`std::pair` 是标准库中定义的一个类模板。用于将两个变量关联在一起，组成一个“对”，而且两个变量的数据类型可以是不同的。

??? 类模板
    类模板（class template）本身不是一个类，而是可以根据 **不同数据类型** 产生 **不同类** 的“模板”。
    
    在使用时，编译器会根据传入的数据类型产生对应的类，再创建对应实例。
    
    模板属于 C++ 较为高级的语言特性，在信息学竞赛中几乎不会出现。如果对此感兴趣，可以进一步阅读《C++ Primer》以学习更深层次的 C++ 知识。

通过灵活使用 `pair`，可以轻松应对 **需要将关联数据捆绑存储、处理** 的场景。

??? pair与自定义struct
    与自定义的 `struct` 相比，`pair` 不需要额外定义结构与重载运算符，因此使用起来更加简便。
    
    然而，自定义 `struct` 的变量命名往往更加清晰（`pair` 只能使用 `first` 与 `second` 访问包含的两个变量）。同时，如果需要将两个以上的变量进行关联，自定义 `struct` 会更加合适。

## 使用

### 初始化

可以在定义时直接完成 `pair` 的初始化。

```cpp
pair<int, double> p0(1, 2.0);
```

也可以使用先定义，后赋值的方法完成 `pair` 的初始化。

```cpp
pair<int, double> p1;
p1.first = 1;
p1.second = 2.0;
```

还可以使用 `std::make_pair` 函数。该函数接受两个变量，并返回由这两个变量组成的 `pair`。

```cpp
pair<int, double> p2 = make_pair(1, 2.0);
```

一种常用的方法是使用宏定义 `#define mp make_pair`，将有些冗长的 `make_pair` 化简为 `mp`。

在 C++11 以及之后的版本中，`make_pair` 可以配合 `auto` 使用，以避免显式声明数据类型。

```cpp
auto p3 = make_pair(1, 2.0);
```

关于 `auto` 的在信息学竞赛中的使用，参见 [迭代器](./iterator.md) 部分的说明。

### 访问

通过成员函数 `first` 与 `second`，可以访问 `pair` 中包含的两个变量。

```cpp
int i = p0.first;
double d = p0.second;
```

也可以对其进行修改。

```cpp
p1.first++;
```

### 比较

`pair` 已经预先定义了所有的比较运算符，包括 `<`、`>`、`<=`、`>=`、`==`、`!=`。当然，这需要组成 `pair` 的两个变量所属的数据类型定义了 `==` 和/或 `<` 运算符。

其中，`<`、`>`、`<=`、`>=` 四个运算符会先比较两个 `pair` 中的第一个变量，在第一个变量相等的情况下再比较第二个变量。

```cpp
if (p2 >= p3) {
  cout << "do something here" << endl;
}
```

由于 `pair` 定义了 STL 中常用的 `<` 与 `==`，使得其能够很好的与其他 STL 函数或数据结构配合。比如，`pair` 可以作为 `priority_queue` 的数据类型。

```cpp
priority_queue<pair<int, double> > q;
```

### 赋值与交换

可以将 `pair` 的值赋给另一个类型一致的 `pair`。

```cpp
p0 = p1;
```

也可以使用 `swap` 函数交换 `pair` 的值。

```cpp
swap(p0, p1);
p2.swap(p3);
```

## 应用举例

### 离散化

`pair` 可以轻松实现离散化。

我们可以创建一个 `pair` 数组，将原始数据的值作为每个 `pair` 第一个变量，将原始数据的位置作为第二个变量。在排序后，将原始数据值的排名（该值排序后所在的位置）赋给该值原本所在的位置即可。

```cpp
// a为原始数据
pair<int, int> a[MAXN];
// ai为离散化后的数据
int ai[MAXN];
for (int i = 0; i < n; i++) {
  // first为原始数据的值，second为原始数据的位置
  scanf("%d", &a[i].first);
  a[i].second = i;
}
// 排序
sort(a, a + n);
for (int i = 0; i < n; i++) {
  // 将该值的排名赋给该值原本所在的位置
  ai[a[i].second] = i;
}
```

### Dijkstra

如前所述，`pair` 可以作为 `priority_queue` 的数据类型。

那么，在 Dijkstra 算法的堆优化中，可以使用 `pair` 与 `priority_queue` 维护节点，将节点当前到起点的距离作为第一个变量，将节点编号作为第二个变量。

```cpp
priority_queue<pair<int, int>, std::vector<pair<int, int> >,
               std::greater<pair<int, int> > >
    q;
... while (!q.empty()) {
  // dis为入堆时节点到起点的距离，i为节点编号
  int dis = q.top().first, i = q.top().second;
  q.pop();
  ...
}
```

### pair 与 map

`map` 的是 C++ 中存储键值对的数据结构。很多情况下，`map` 中存储的键值对通过 `pair` 向外暴露。

```cpp
map<int, double> m;
m.insert(make_pair(1, 2.0));
```

关于 `map` 更多的内容，请见 [关联式容器](./associative-container.md) 与 [无序关联式容器](./unordered-container.md) 中相关部分。
