## \_\_gnu_pbds :: priority_queue

附 ：[官方文档地址——复杂度及常数测试](https://gcc.gnu.org/onlinedocs/libstdc++/ext/pb_ds/pq_performance_tests.html#std_mod1)

```cpp
#include <ext/pb_ds/priority_queue.hpp>
using namespace __gnu_pbds;
__gnu_pbds :: priority_queue<T, Compare, Tag, Allocator> // 由于 OI 中很少出现空间配置器，故这里不做讲解（其实是我也不知道是啥，逃
/*
 * T : 储存的元素类型
 * Compare : 提供严格的弱序比较类型
 * Tag : 是__gnu_pbds提供的不同的五种堆，Tag参数默认是 pairing_heap_tag
 * 五种分别是 ：
 * pairing_heap_tag -> 配对堆 // 官方文档认为在非原生元素(如自定义结构体/ std :: string / pair)中
 * pairing heap 表现的最好
 * binary_heap_tag -> 二叉堆 // 官方文档认为在原生元素中 二叉堆表现最好，不过我测试的表现并没有那么好
 * binomial_heap_tag -> 二项堆 // 二项堆在合并操作的表现要优于配对堆* 但是其取堆顶元素的
 * rc_binomial_heap_tag -> 冗余计数二项堆
 * thin_heap_tag -> 除了合并的复杂度都和 Fibonacci 堆一样的一个 tag
 * 由于本篇文章只是提供给学习算法竞赛的同学们，故对于后四个 tag 只会简单的介绍复杂度，第一个会介绍成员函数和
 * 使用方法，经作者本机 Core i5@3.1 GHz On macOS 测试堆的基础操作/结合 GNU 官方的复杂度测试/Dijkstra
 * 测试，都表明至少对于*** OIer ***来讲，除了配对堆的其他4个tag都是鸡肋，不是没什么用就是常数大到不如 std 的
 * 且有可能造成 MLE    
 * priority_queue，故这里只推荐用默认的 pairing_heap。
 * 同样，配对堆也优于 algorithm 库中的 make_heap()
 */
 // 构造方式 ： 要注明命名空间因为和std的类名称重复
 __gnu_pbds :: priority_queue<int>
 __gnu_pbds :: priority_queue<int, greater<int> >
 __gnu_pbds :: priority_queue<int, greater<int>, pairing_heap_tag>
 // 迭代器 ：迭代器是一个内存地址，在modify和push的时候都会返回一个迭代器，下文会详细的讲使用方法
 __gnu_pbds :: priority_queue<int> :: point_iterator id;
 id = q.push(1);
```

复杂度如下表 ：

|                      | push                                 | pop                                  | modify                               | erase                                  | Join              |
| -------------------- | ------------------------------------ | :----------------------------------- | ------------------------------------ | -------------------------------------- | ----------------- |
| Pairing_heap_tag     | $O(1)$                               | 最坏$\Theta(n)$    均摊$\Theta(\log(n))$ | 最坏$\Theta(n)$    均摊$\Theta(\log(n))$ | 最坏$\Theta(n)$    均摊$\Theta(\log(n))$   | $O(1)$            |
| Binary_heap_tag      | 最坏$\Theta(n)$    均摊$\Theta(\log(n))$ | 最坏$\Theta(n)$    均摊$\Theta(\log(n))$ | $\Theta(n)$                          | $\Theta(n)$                            | $\Theta(n)$       |
| Binomial_heap_tag    | 最坏$\Theta(\log(n))$   均摊$O(1)$       | $\Theta(\log(n))$                    | $\Theta(\log(n))$                    | $\Theta(\log(n))$                      | $\Theta(\log(n))$ |
| Rc_Binomial_heap_tag | $O(1)$                               | $\Theta(\log(n))$                    | $\Theta(\log(n))$                    | $\Theta(\log(n))$                      | $\Theta(\log(n))$ |
| Thin_heap_tag        | $O(1)$                               | 最坏$\Theta(n)$    均摊$\Theta(\log(n))$ | 最坏$\Theta(\log(n))$   均摊$O(1)$       | 最坏$\Theta(n)$    0 均摊$\Theta(\log(n))$ | $\Theta(n)$       |

##### 成员函数：

1. `push()`: 向堆中压入一个元素, 返回该元素位置的迭代器
2. `pop()`: 将堆顶元素弹出
3. `top()`: 返回堆顶元素
4. `size()`返回元素个数
5. `empty()`返回是否非空
6. `modify(point_iterator, const key)` : 把迭代器位置的 key 修改为传入的 key，并对底层储存结构进行排序
7. `erase(point_iterator)` : 把迭代器位置的键值从堆中擦除
8. `join(__gnu_pbds :: priority_queue &other)`: 把 other 合并到 \* this 并把 other 清空。

##### 示例:

```cpp
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <ext/pb_ds/priority_queue.hpp>
using namespace __gnu_pbds;
// 由于面向OIer, 本文以常用堆 : pairing_heap_tag作为范例
// 为了更好的阅读体验，定义宏如下 ：
#define pair_heap __gnu_pbds :: priority_queue<int>
pair_heap q1; //大根堆, 配对堆
pair_heap q2;
pair_heap :: point_iterator id; // 一个迭代器
int main() {
	id = q1.push(1); 
	// 堆中元素 ： [1];
	for(int i = 2; i <= 5; i ++ ) q1.push(i);
	// 堆中元素 :  [1, 2, 3, 4, 5];
	std :: cout << q1.top() << std :: endl;
	// 输出结果 : 5;
	q1.pop();
	// 堆中元素 : [1, 2, 3, 4];
	id = q1.push(10);
	// 堆中元素 : [1, 2, 3, 4, 10];
	q1.modify(id, 1);
	// 堆中元素 :  [1, 1, 2, 3, 4];
	std :: cout << q1.top() << std :: endl;
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
