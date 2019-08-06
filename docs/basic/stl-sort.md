## sort

C 标准库实现了快速排序，即 `stdlib.h` 当中的 `qsort` 。

但在 OI 相关比赛当中，更为常见的库排序函数是 C++ `algorithm` 库中的 `std::sort` 函数。

C++ 标准并未严格要求此函数的实现算法，具体实现取决于编译器。

旧版 C++ 标准中仅要求它的 **平均** 时间复杂度达到 $O(n\log n)$ ，但 C++11 标准要求它的 **最坏** 时间复杂度是达到 $O(n\log n)$ 。可以查阅[std::sort()](https://en.cppreference.com/w/cpp/algorithm/sort)

在[libstdc++](https://github.com/mirrors/gcc/blob/master/libstdc++-v3/include/bits/stl_algo.h)和[libc++](http://llvm.org/svn/llvm-project/libcxx/trunk/include/algorithm)中使用的都是[Introsort](https://en.wikipedia.org/wiki/Introsort)。

Introsort 限制了快速排序的分治深度，当分治达到一定深度之后，改用最坏时间复杂度为 $O(n\log n)$ 的排序算法（比如堆排序）来给子数组排序。

Introsort 的这个限制使得它的最坏时间复杂度是 $O(n\log n)$ 的。

快速用法：

```cpp
// a[0] .. a[n - 1] 为需要排序的数列
std::sort(a, a + n);
// 这句代码直接修改 a 数组里的元素顺序，使得现在它是从小到大排列的
```

## nth_element

作用是找到选定区间内第 $k$ 大的数，并将所有比它小的数与比它大的数分别置于两侧，返回它的地址。

原理是未完成的快速排序

用法

```cpp
std::nth_element(begin, mid, end);
```

时间复杂度：期望 $O(n)$ 

常用于构建 K-DTree

## stable_sort

稳定的 $O(nlogn)$ 排序，即保证相等元素排序后的相对位置与原序列相同。

用法

```cpp
std::stable_sort(begin, end, cmp);
```

## partial_sort

将序列中前 $k$ 小元素按顺序置于前 $k$ 个位置，后面的元素不保证顺序。

复杂度： $O(nlogk)$ 

用法：

```cpp
std::partial_sort(begin, begin + k, end);
```

原理：

实现 partial_sort 的思想是：对原始容器内区间为 $[first, middle)$ 的元素执行 make_heap() 操作构造一个大根堆，然后拿 $[middle, last)$ 中的每个元素和 $first$ 进行比较， $first$ 内的元素为堆内的最大值。如果小于该最大值，则互换元素位置，并对 $[first, middle)$ 内的元素进行调整，使其保持最大堆序。比较完之后在对 $[first, middle)$ 内的元素做一次对排序 sort_heap() 操作，使其按增序排列。注意，堆序和增序是不同的。

## 定义运算符

对于内置类型（如 `int` ）和用户定义的结构体，你都可以定义调用 STL 排序函数时使用的 **小于运算符** 。你可以在调用函数时同时传入一个比较运算符的函数（一般是最后一项），也可以直接重载该类型的默认运算符。参见[cppreference](https://zh.cppreference.com/w/cpp/language/operators)。
下面是几个例子：

```cpp
int a[1009], n = 10;
// ......
std::sort(a + 1, a + 1 + n);  // 不重载，从小到大排序。
std::sort(a + 1, a + 1 + n,
          greater<int>());  // 重载小于运算符为大于，从大到小排序。
```

```cpp
struct data {
  int a, b;
  bool operator<(const data rhs) const {
    return (a == rhs.a) ? (b < rhs.b) : (a < rhs.a);
  }
} da[1009];
bool cmp(const data u1, const data u2) {
  return (u1.a == u2.a) ? (u1.b > u2.b) : (u1.a > u2.a);
}
// ......
std::sort(da + 1, da + 1 + 10, cmp);  // 不重载，从小到大排序。
std::sort(da + 1, da + 1 + 10, cmp);  // 重载小于运算符为大于，从大到小排序。
```

### 严格弱序

进行排序的运算符必须满足严格弱序（[Strict weak orderings](https://en.wikipedia.org/wiki/Weak_ordering#Strict_weak_orderings)），否则会出现不可预料的情况（如运行时错误）。
严格弱序的要求：

1.   $x \not< x$ （非自反性）
2.  若 $x < y$ ，则 $y \not< x$ （非对称性）
3.  若 $x < y, y < z$ ，则 $x < z$ （传递性）
4.  若 $x \not< y, y \not< x, y \not< z, z \not< y$ ，则 $x \not< z, z \not< x$ （不可比性的传递性）

常见的错误做法：

-   使用 `<=` 来定义排序中的小于运算符。
-   在调用排序运算符时，读取外部数值可能会改变的数组。（常见于最短路算法）
-   将多个数的最大最小值进行比较的结果作为排序运算符。

### Reference

-   [浅谈邻项交换排序的应用以及需要注意的问题](https://ouuan.github.io/浅谈邻项交换排序的应用以及需要注意的问题/)
