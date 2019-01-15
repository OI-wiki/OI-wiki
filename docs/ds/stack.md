## 栈

栈是 OI 中常用的一种线性数据结构，请注意，本文主要讲的是栈这种数据结构，而非程序运行时的系统栈/栈空间

栈的修改是按照后进先出的原则进行的，因此栈通常被称为是后进先出（last in first out）表，简称 LIFO 表。

!!! warning
    为什么不是 FILO 呢？

我们可以方便的使用数组来模拟一个栈，如下：

```cpp
int stk[N];
// 这里使用 stk[0]( 即 *stk ) 代表栈中元素数量，同时也是栈顶下标
// 压栈 ：
stk[++*stk] = var1;
// 取栈顶 ：
int u = stk[*stk];
// 弹栈 ：注意越界问题, *stk == 0 时不能继续弹出
if (*stk) --*stk;
// 清空栈
*stk = 0;
```

同时 STL 也提供了一个方法`std :: stack`

```cpp
#include <stack>
// stack 构造 ：
1. stack<Typename T> s;
2. stack<Typename T, Container> s;
/* stack 的 Container 需要满足有如下接口 ：
 * back()
 * push_back()
 * pop_back()
 * 标准容器 std :: vector / deque / list 满足这些要求
 * 如使用 1 方式构造，默认容器使用 deque
 */
```

`std :: stack`支持赋值运算符`=`

元素访问：

`s.top()`返回栈顶

容量：

`s.empty()`返回是否为空

`s.size()`返回元素数量

修改：

`s.push()`插入传入的参数到栈顶

`s.pop()`弹出栈顶

其他运算符：

`==`、`!=`、`<`、`<=`、`>`、`>=`可以按照字典序比较两个`stack`的值
