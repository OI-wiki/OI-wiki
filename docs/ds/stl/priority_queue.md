```cpp
#include <queue>  // std::priority_queue
// 本文里的所有优先队列都会加上命名空间
// 如果不想加命名空间，需要使用：using std::priority_queue;
// 不推荐直接使用 using namespace std;
std::priority_queue<T, Container, Compare>
    /*
     * T: 储存的元素类型
     * Container:
     * 储存的容器类型，且要求满足顺序容器的要求、具有随机访问迭代器的要求 且支持
     * front() / push_back() / pop_back() 三个函数， 标准容器中 std::vector /
     * std::deque 满足这些要求。 Compare: 默认为严格的弱序比较类型
     * priority_queue 是按照元素优先级大的在堆顶，根据 operator <
     * 的定义，默认是大根堆， 我们可以利用
     * greater<T>（若支持），或者自定义类的小于号重载实现排序。
     * 注意：只支持小于号重载而不支持其他比较符号的重载。
     */
        // 构造方式 ：
        std::priority_queue<int>;
std::priority_queue<int, vector<int>>
    // C++11前，请使用 vector<int> >，空格不可省略
    std::priority_queue<int, deque<int>, greater<int>>
    // 注意：不可跳过容器参数直接传入比较类
```

## 成员函数 ：

1. `top()`: 访问栈顶元素 常数复杂度
2. `empty()`: 检查底层的容器是否为空 常数复杂度
3. `size()`: 返回底层容器的元素数量 常数复杂度
4. `push()`: 插入元素，并对底层容器排序 最坏 $\Theta(n)$ 均摊 $\Theta(\log(n))$
5. `pop()`: 删除第一个元素 最坏 $\Theta(\log(n))$

由于 `std::priority_queue` 原生不支持 `modify()` / `join()` / `erase()` 故不做讲解。

## 示例 ：

```cpp
q1.push(1);
// 堆中元素 ： [1];
for (int i = 2; i <= 5; i++) q1.push(i);
// 堆中元素 :  [1, 2, 3, 4, 5];
std ::cout << q1.top() << std ::endl;
// 输出结果 : 5;
q1.pop();
std ::cout << q1.size() << std ::endl;
// 输出结果 ：4
// 堆中元素 : [1, 2, 3, 4];
q1.push(10);
// 堆中元素 : [1, 2, 3, 4, 10];
std::cout << q1.top() << std ::endl;
// 输出结果 : 10;
q1.pop();
// 堆中元素 : [1, 2, 3, 4];
```
