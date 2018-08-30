# std :: vector

## 为什么要用 vector 

作为 OIer ，对程序效率的追求远比对工程级别的稳定性要高得多，而 vector 由于其较静态数组复杂很多的原因，时间效率在大部分情况下都要满慢于静态数组，所以在一般的正常存储数据的时候，我们是不选择 vector 的， 下面给出几个 vector 优秀的特性，在需要用到这些特性的情况下，vector 能给我们带来很大的帮助

### vector 重写了比较运算符

vector 以字典序为关键字重载了6个比较运算符，这使得我们可以方便的判断两个容器是否相等   （复杂度与容器大小成线性关系）

### vector 的内存是动态分配的

由于其动态分配的特性， 所以在调用内存的常数上在很多情况下是要快于静态数组的。

很多时候我们不能提前开好那么大的空间（eg ：预处理1~n中所有数的约数）我们知道数据总量在空间允许的级别，但是单份数据还可能非常大，这种时候我们就需要vector 来保证复杂度。

### vector 可以用赋值运算符来进行初始化

由于 vector 重写了 `=` 运算符，所以我们可以方便的初始化。

## vector的构造函数

参见如下代码

```cpp
void Vector_Constructor_Test() {
    // 1. 创建空vector v0;  常数复杂度
    std::vector<int> v0;
    // 2. 创建一个初始空间为3的vector v1，其元素的默认值是0; 线性复杂度
    std::vector<int> v1(3);
    // 3. 创建一个初始空间为5的vector v2，其元素的默认值是2; 线性复杂度
    std::vector<int> v2(5, 2);
    // 4. 创建一个初始空间为3的vector v3，其元素的默认值是1，并且使用v2的空间配置器 线性复杂度
    std::vector<int> v3(3, 1, v2.get_allocator());
    // 5. 创建一个v2的拷贝vector v4， 其内容元素和v2一样; 线性复杂度
    std::vector<int> v4(v2);
    // 6. 创建一个v4的拷贝vector v5，其内容是v4的[__First， __Last)区间 线性复杂度
    std::vector<int> v5(v4.begin() + 1, v4.begin() + 3);
    // 以下是测试代码，有兴趣的同学可以自己编译运行一下本代码。
    std::cout << "v1 = ";
    std::copy(v1.begin(), v1.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;
    std::cout << "v2 = ";
    std::copy(v2.begin(), v2.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;
    std::cout << "v3 = ";
    std::copy(v3.begin(), v3.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;
    std::cout << "v4 = ";
    std::copy(v4.begin(), v4.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;
    std::cout << "v5 = ";
    std::copy(v5.begin(), v5.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;
    // 移动v2到新创建的vector v6;
    std::vector<int> v6(move(v2));
    std::cout << "v6 = ";
    std::copy(v6.begin(), v6.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;
};
```

可以利用上述的方法构造一个vector， 足够我们使用了。

## vector元素访问

vector提供了如下几种方法进行访问元素

1. `at() `

    使用方法 ：`v.at(pos)` 返回vector中下标为 `pos` 的引用。如果数组越界 抛出 `std::out_of_range` 类型的异常。

2. `operator[]`

    使用方法 ：`v[pos]` 返回vector中下标为 `pos` 的引用。如果数组越界就显示 `SIGSEGV` 错误。

3. `front()`

    使用方法 ：`v.front()` 返回首元素的引用

4. `back()`

    使用方法 ：`v.back()` 返回末尾元素的引用

5. `data()`

    使用方法 ：`v.data()` 返回指向数组第一个元素的指针。

## vecort 迭代器

vector 提供了如下几种迭代器

1. `begin() / cbegin()`

    返回指向首元素的迭代器，其中 `*begin = front`

2. `end() / cend()`

    返回指向数组尾端占位符的迭代器，注意是没有元素的。

3. `rbegin() / rcbegin()`

    返回指向逆向数组的首元素的逆向迭代器， 可以理解为正向容器的末元素

4. `rend() / rcend()`

    返回指向逆向数组末元素后一位置的迭代器，对应容器首的前一个位置， 没有元素。

## vector 容量

vector有如下几种返回容量的函数

1. `empty()`

    返回一个 `bool` 值，即 `(v.begin() == v.end())` True 为空，False 为非空

2. `size()`

    返回一个元素数量，即 `(std :: distance(v.begin(), v.end()))`

3. `shrink_to_fit()`

    释放未使用的内存来减少内存使用

此外，还有 `max_size()`, `reserve()`, `capacity()` 等 OIer 很难用到的函数，不做介绍。

## vector 修改器

- `clear()` 清除所有元素
- `insert()` 支持在某个迭代器位置插入元素、可以插入多个**此操作是与 `pos` 距离末尾长度成线性而非常数的**
- `erase()` 删除某个迭代器或者区间的元素，返回最后被删除的迭代器。
- `push_back()` 在末尾插入一个元素。 
- `pop_back()` 删除末尾元素。
- `swap()` 与另一个容器进行交换，此操作是**常数复杂度**而非线性的。

## vector 特化 `std::vector<bool>`

标准库提供对 bool 的 vector 优化，其空间占用与 bitset 一样，每个 `bool` 只占 1bit，且支持动态内存

注意，`vector<bool>`没有 bitset 的位运算重载，所以适用情况与 bitset 并不完全重合，请选择食用。
