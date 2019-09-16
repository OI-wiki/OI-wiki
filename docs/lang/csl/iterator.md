在 STL 中，迭代器（Iterator）是用来访问和检查 STL 容器中元素的对象，它的行为模式和指针类似，甚至有不少容器的迭代器类型就是指针。但是它封装了一些有效性检查，并且提供了统一的访问格式。迭代器尽管在使用上与常规的下标访问效果相似，但是由于部分 STL 容器（如 `std::list` ）的下标访问有很大的开销，这时在顺序访问的情况下迭代器会比下标访问更加高效。类似的概念在其他很多高级语言中都存在，如 Python 的 `__iter__` 函数，C# 的 `IEnumerator` 。

## 使用方法

迭代器听起来比较晦涩，其实迭代器本身可以看作一个数据指针。迭代器主要支持两个运算符：自增和解引用（单目 `*` 运算符），其中自增用来移动迭代器，解引用可以获取或修改它指向的元素。
最常用的使用方法是用迭代器替换普通的 `for` 循环，例如下列代码中两个循环的效果是一致的。（假设已经引用了 `std` 空间中的相关类型）

```cpp
vector<int> data(10);

for (int i = 0; i < data.size(); i++)
  cout << data[i] << endl;  // 使用下标访问元素

for (vector<int>::iterator iter = data.begin(); iter != data.end(); iter++)
  cout << *iter << endl;  // 使用迭代器访问元素
// 在C++11后可以使用 auto iter = data.begin() 来简化上述代码
```

## 分类

在 STL 的定义中，迭代器根据其支持的操作依次分为以下几类：

-   InputIterator：只要求支持拷贝、自增和解引访问
-   OutputIterator：只要求支持拷贝、自增和解引赋值
-   ForwardIterator：即同时满足 InputIterator 和 OutputIterator 的要求
-   BidirectionalIterator：在 ForwardIterator 的基础上支持自减（即反向访问）
-   RandomAccessIterator：在 BidirectionalIterator 的基础上支持加减运算和比较运算（即随机访问）

不同的 STL 容器支持的迭代器类型不同，在使用时需要留意。

## 获取途径

STL 容器一般支持从一端或两端开始的访问，以及对 [const 修饰符](../const.md) 的支持。例如容器的 `begin()` 函数可以获得指向容器头部的迭代器，而 `rbegin()` 函数可以获得指向容器尾部的元素的反向迭代器。
