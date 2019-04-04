## priority_queue 是什么？

`priority_queue` 是一个出队顺序由作用于所存储的值对上的某种谓词决定的的一种队列。相当于一个大根堆。

## 声明

`std::priority_queue<T,Container, Compare>`，`Container` 和 `Compare` 是可选的，若不填则默认为 `vector<T>` 和小于号（要求 `T` 重载了小于号）。

其中 `T` 是元素类型，`Container` 是所用容器，`Compare` 是用于比较的 **二元谓词**，可以是 STL 内置的谓词（如 `greater<int>`），也可以是一个重载了 `()` 的类（结构体）。

```cpp
#include <queue>

std::priority_queue<int,vector<int>,greater<int> > q1; // 一个小根堆

struct cmp
{
    bool operator()(int x,int y)
    {
        return x>y;
    }
};

std::priority_queue<int,vector<int>,cmp> q2; //也是一个小根堆

struct Node
{
    int x,y;
    bool operator<(const Node& b) const
    {
        return x*y<b.x*y;
    }
};

std::priority_queue<Node> q2; //若a.x*a.y<b.x*b.y则b为a父亲的堆
```

## 成员函数

1.   `top()` : 访问堆顶元素 常数复杂度
2.   `empty()` : 检查容器是否为空 常数复杂度
3.   `size()` : 返回容器的元素数量 常数复杂度
4.   `push()` : 插入一个元素 最坏 $\Theta(n)$ 均摊 $\Theta(\log(n))$ 
5.   `pop()` : 删除堆顶元素 最坏 $\Theta(\log(n))​$ 

## 应用

1. 大多数时候可以替代二叉堆，因此需要手写二叉堆的情况非常少。
2. 特别地，常用于优化 Dijkstra 算法。