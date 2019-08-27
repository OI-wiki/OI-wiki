author: Xeonacid

## stack

STL 栈 ( `std::stack` ) 是一种后进先出 (Last In, First Out) 的容器适配器，仅支持查询或删除最后一个加入的元素（栈顶元素），不支持随机访问，且为了保证数据的严格有序性，不支持迭代器。

### 头文件和命名空间

```cpp
#include <stack>
using std::stack
```

### 栈的定义

```cpp
stack<TypeName> s;  // 使用默认底层容器 deque，数据类型为 TypeName
stack<TypeName, Container> s;  // 使用 Container 作为底层容器

stack<TypeName> s2(s1);  // 以 s1 为模板定义一个栈 s2
```

### 成员函数

#### 以下所有函数均为常数复杂度

-    `top()` 访问栈顶元素（如果栈为空，此处会出错）
-    `push(x)` 向栈中插入元素 x
-    `pop()` 删除栈顶元素
-    `size()` 查询容器中的元素数量
-    `empty()` 询问容器是否为空

### 简单示例

```cpp
stack<int> s1;
s1.push(2);
s1.push(1);
stack<int> s2(s1);
s1.pop();
std::cout << s1.size() << " " << s2.size() << endl;  // 1 2
std::cout << s1.top() << " " << s2.top() << endl;    // 2 1
s1.pop();
std::cout << s1.empty() << " " << s2.empty() << endl;  // 1 0
```

## queue

STL 队列 ( `std::queue` ) 是一种先进先出 (First In, First Out) 的容器适配器，仅支持查询或删除第一个加入的元素（队首元素），不支持随机访问，且为了保证数据的严格有序性，不支持迭代器。

### 头文件和命名空间

```cpp
#include <queue>
using std::queue
```

### 队列的定义

```cpp
queue<TypeName> q;  // 使用默认底层容器 deque，数据类型为 TypeName
queue<TypeName, Container> q;  // 使用 Container 作为底层容器

queue<TypeName> q2(q1);  // 以 q1 为模板定义一个队列 q2
```

### 成员函数

#### 以下所有函数均为常数复杂度

-    `front()` 访问队首元素（如果队列为空，此处会出错）
-    `push(x)` 向队列中插入元素 x
-    `pop()` 删除队首元素
-    `size()` 查询容器中的元素数量
-    `empty()` 询问容器是否为空

### 简单示例

```cpp
stack<int> q1;
q1.push(2);
q1.push(1);
stack<int> q2(q1);
q1.pop();
std::cout << q1.size() << " " << q2.size() << endl;    // 1 2
std::cout << q1.front() << " " << q2.front() << endl;  // 1 2
q1.pop();
std::cout << q1.empty() << " " << q2.empty() << endl;  // 1 0
```

## priority_queue

```cpp
#include <queue>  // std::priority_queue
// 本文里的所有优先队列都会加上命名空间
// 如果不想加命名空间，需要使用：using std::priority_queue;
// 不推荐直接使用 using namespace std;
std::priority_queue<T, Container, Compare> q;
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
std::priority_queue<int> q1;
std::priority_queue<int, vector<int>> q2;
// C++11 前，请使用 vector<int> >，空格不可省略
std::priority_queue<int, deque<int>, greater<int>> q3;
// 注意：不可跳过容器参数直接传入比较类
```

### 成员函数

1.   `top()` : 访问栈顶元素 常数复杂度
2.   `empty()` : 检查底层的容器是否为空 常数复杂度
3.   `size()` : 返回底层容器的元素数量 常数复杂度
4.   `push()` : 插入元素，并对底层容器排序 最坏 $\Theta(n)$ 均摊 $\Theta(\log(n))$ 
5.   `pop()` : 删除第一个元素 最坏 $\Theta(\log(n))$ 

由于 `std::priority_queue` 原生不支持 `modify()` / `join()` / `erase()` 故不做讲解。

### 示例

```cpp
q1.push(1);
// 堆中元素 ： [1];
for (int i = 2; i <= 5; i++) q1.push(i);
// 堆中元素 :  [1, 2, 3, 4, 5];
std::cout << q1.top() << std::endl;
// 输出结果 : 5;
q1.pop();
std::cout << q1.size() << std::endl;
// 输出结果 ：4
// 堆中元素 : [1, 2, 3, 4];
q1.push(10);
// 堆中元素 : [1, 2, 3, 4, 10];
std::cout << q1.top() << std::endl;
// 输出结果 : 10;
q1.pop();
// 堆中元素 : [1, 2, 3, 4];
```
