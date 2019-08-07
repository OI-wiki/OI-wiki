author: Xeonacid, ouuan, Ir1d, WAAutoMaton, Chrogeek, abc1763613206, Planet6174, i-Yirannn

##  `__gnu_pbds :: priority_queue` 

附： [官方文档地址——复杂度及常数测试](https://gcc.gnu.org/onlinedocs/libstdc++/ext/pb_ds/pq_performance_tests.html#std_mod1) 

```cpp
#include <ext/pb_ds/priority_queue.hpp>
using namespace __gnu_pbds;
__gnu_pbds ::priority_queue<T, Compare, Tag, Allocator>
```

## 模板形参

-    `T` : 储存的元素类型
-    `Compare` : 提供严格的弱序比较类型
-    `Tag` : 是 `__gnu_pbds` 提供的不同的五种堆，Tag 参数默认是 `pairing_heap_tag` 五种分别是：
    -    `pairing_heap_tag` ：配对堆
        官方文档认为在非原生元素（如自定义结构体/ `std :: string` / `pair` ) 中，配对堆表现最好
    -    `binary_heap_tag` ：二叉堆 
        官方文档认为在原生元素中二叉堆表现最好，不过我测试的表现并没有那么好
    -    `binomial_heap_tag` ：二项堆
        二项堆在合并操作的表现要优于配对堆\*但是其取堆顶元素的
    -    `rc_binomial_heap_tag` ：冗余计数二项堆
    -    `thin_heap_tag` ：除了合并的复杂度都和 Fibonacci 堆一样的一个 tag
-    `Allocator` ：空间配置器，由于 OI 中很少出现，故这里不做讲解

由于本篇文章只是提供给学习算法竞赛的同学们，故对于后四个 tag 只会简单的介绍复杂度，第一个会介绍成员函数和使用方法。

经作者本机 Core i5@3.1 GHz On macOS 测试堆的基础操作，结合 GNU 官方的复杂度测试，Dijkstra 测试，都表明：
至少对于 OIer 来讲，除了配对堆的其他四个 tag 都是鸡肋，要么没用，要么常数大到不如 `std` 的，且有可能造成 MLE，故这里只推荐用默认的配对堆。同样，配对堆也优于 `algorithm` 库中的 `make_heap()` 。

## 构造方式

要注明命名空间因为和 `std` 的类名称重复。

    __gnu_pbds ::priority_queue<int> __gnu_pbds::priority_queue<int, greater<int> >
    __gnu_pbds ::priority_queue<int, greater<int>, pairing_heap_tag>
    __gnu_pbds ::priority_queue<int>::point_iterator id; // 迭代器
    // 在 modify 和 push 的时候都会返回一个 point_iterator，下文会详细的讲使用方法
    id = q.push(1);

## 成员函数

-    `push()` : 向堆中压入一个元素，返回该元素位置的迭代器。
-    `pop()` : 将堆顶元素弹出。
-    `top()` : 返回堆顶元素。
-    `size()` 返回元素个数。
-    `empty()` 返回是否非空。
-    `modify(point_iterator, const key)` : 把迭代器位置的 `key` 修改为传入的 `key` ，并对底层储存结构进行排序。
-    `erase(point_iterator)` : 把迭代器位置的键值从堆中擦除。
-    `join(__gnu_pbds :: priority_queue &other)` : 把 `other` 合并到 `*this` 并把 `other` 清空。

使用的 tag 决定了每个操作的时间复杂度：

|                          | push                                 | pop                                  | modify                               | erase                                  | Join                |
| ------------------------ | ------------------------------------ | :----------------------------------- | ------------------------------------ | -------------------------------------- | ------------------- |
|  `pairing_heap_tag`      |  $O(1)$                              | 最坏 $\Theta(n)$ 均摊 $\Theta(\log(n))$  | 最坏 $\Theta(n)$ 均摊 $\Theta(\log(n))$  | 最坏 $\Theta(n)$ 均摊 $\Theta(\log(n))$    |  $O(1)$             |
|  `binary_heap_tag`       | 最坏 $\Theta(n)$ 均摊 $\Theta(\log(n))$  | 最坏 $\Theta(n)$ 均摊 $\Theta(\log(n))$  |  $\Theta(n)$                         |  $\Theta(n)$                           |  $\Theta(n)$        |
|  `binomial_heap_tag`     | 最坏 $\Theta(\log(n))$ 均摊 $O(1)$       |  $\Theta(\log(n))$                   |  $\Theta(\log(n))$                   |  $\Theta(\log(n))$                     |  $\Theta(\log(n))$  |
|  `rc_binomial_heap_tag`  |  $O(1)$                              |  $\Theta(\log(n))$                   |  $\Theta(\log(n))$                   |  $\Theta(\log(n))$                     |  $\Theta(\log(n))$  |
|  `thin_heap_tag`         |  $O(1)$                              | 最坏 $\Theta(n)$ 均摊 $\Theta(\log(n))$  | 最坏 $\Theta(\log(n))$ 均摊 $O(1)$       | 最坏 $\Theta(n)$ 0 均摊 $\Theta(\log(n))$  |  $\Theta(n)$        |

## 示例

```cpp
#include <algorithm>
#include <cstdio>
#include <ext/pb_ds/priority_queue.hpp>
#include <iostream>
using namespace __gnu_pbds;
// 由于面向OIer, 本文以常用堆 : pairing_heap_tag作为范例
// 为了更好的阅读体验，定义宏如下 ：
#define pair_heap __gnu_pbds ::priority_queue<int>
pair_heap q1;  //大根堆, 配对堆
pair_heap q2;
pair_heap ::point_iterator id;  // 一个迭代器
int main() {
  id = q1.push(1);
  // 堆中元素 ： [1];
  for (int i = 2; i <= 5; i++) q1.push(i);
  // 堆中元素 :  [1, 2, 3, 4, 5];
  std ::cout << q1.top() << std ::endl;
  // 输出结果 : 5;
  q1.pop();
  // 堆中元素 : [1, 2, 3, 4];
  id = q1.push(10);
  // 堆中元素 : [1, 2, 3, 4, 10];
  q1.modify(id, 1);
  // 堆中元素 :  [1, 1, 2, 3, 4];
  std ::cout << q1.top() << std ::endl;
  // 输出结果 : 4;
  q1.pop();
  // 堆中元素 : [1, 1, 2, 3];
  id = q1.push(7);
  // 堆中元素 : [1, 1, 2, 3, 7];
  q1.erase(id);
  // 堆中元素 : [1, 1, 2, 3];
  q2.push(1), q2.push(3), q2.push(5);
  // q1中元素 : [1, 1, 2, 3], q2中元素 : [1, 3, 5];
  q2.join(q1);
  // q1中无元素，q2中元素 ：[1, 1, 1, 2, 3, 3, 5];
}
```
