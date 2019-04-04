## std::queue

**队列** 是一种先进先出（FIFO）的基础数据结构。

### 头文件

```cpp
#include <queue>
```

### 声明

```cpp
queue<int> q; // a queue which contains ints
```

### 相关函数

- `q.front()`：返回队首元素。
- `q.back()`：返回队尾元素。
- `q.push(val)`：将一个元素压入至队尾。
- `q.emplace(val)`：**C++11**，大致和 `q.push(val)` 相同，但在插入复杂的类/结构体时效率更高。
- `q.pop()`：弹出队首元素。
- `q1.swap(q2)`, `swap(q1,q2)`：**C++11**，常量时间交换两个队列。

`queue` 不支持 `clear()`，所以清空 `queue` 要 `while (!q.empty()) q.pop();`，或者将其赋值为另一个空队。

### 应用

- bfs
- ~~已经死掉的~~SPFA

## std::deque

`std::deque` 是一个 **双端队列**，即队列两端都可以插入/弹出元素。并且，`std::deque` 还支持 **随机访问**（可以访问任意一个下标）。

虽然 `deque` 和 `queue` 都叫做 “队列”，但它们有本质区别：`deque` 是一个 STL 容器，而 `queue` 是一个容器适配器。

### 头文件

```cpp
#include <deque>
```

### 声明

```cpp
deque<int> dq; // a deque  which contains ints
```

### 相关函数

详见 [C++ Reference](https://zh.cppreference.com/w/cpp/container/deque)。

### 应用

- ~~已经死掉的~~SPFA的 slf “优化”。加引号是因为 slf 可以被卡到指数级复杂度。
