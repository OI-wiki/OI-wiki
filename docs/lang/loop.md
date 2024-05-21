有时，我们需要做一件事很多遍，为了不写过多重复的代码，我们需要循环。

有时，循环的次数不是一个常量，那么我们无法将代码重复多遍，必须使用循环。

有时，我们使用循环遍历一个容器。

## for 语句

以下是 for 语句的结构：

```cpp
for (初始化; 判断条件; 更新) {
  循环体;
}
```

执行顺序：

![](images/for-loop.svg)

e.g. 读入 n 个数：

```cpp
for (int i = 1; i <= n; ++i) {
  cin >> a[i];
}
```

for 语句的三个部分中，任何一个部分都可以省略。其中，若省略了判断条件，相当于判断条件永远为真。

### 基于范围的 for 循环

这是 C++11 的特性，结构如下：

```cpp
for ( 范围变量声明 : 范围表达式 )
  循环语句
```

上述语法将遍历范围表达式，等价于以下代码：

```cpp
{
  auto && __range = 范围表达式 ;
  for (auto __begin = 首表达式, __end = 尾表达式 ; __begin != __end; ++__begin)
  {
    范围变量声明 = *__begin;
    循环语句
  }
}
```

要迭代的序列或范围通过对范围表达式求值以确定。依次对序列的每个元素进行解引用，并赋值给具有范围变量声明中所给定的类型和名字的变量。

首表达式和尾表达式定义如下：

+ 如果范围表达式是数组类型的表达式，那么首表达式是 `__range` 而尾表达式是 `(__range + __bound)`，其中 `__bound` 是数组的元素数目（如果数组大小未知或拥有不完整类型，那么程序非良构）
+ 如果范围表达式是同时拥有名为 `begin` 以及名为 `end` 的成员的类类型 `C` 的表达式（不管这些成员的类型或可见性），那么首表达式是 `__range.begin()` 而尾表达式是 `__range.end()`；
+ 否则，首表达式是 `begin(__range)` 而尾表达式是 `end(__range)`，通过实参依赖查找进行查找（不进行非实参依赖查找）。

正如传统循环一样，`break` 语句可用于提早退出循环，`continue` 语句可用于以下个元素重新开始循环。

如果从初始化语句中引入的名字在循环语句的最外层块被重声明，那么程序非良构：

```cpp
for (int i : { 1, 2, 3 })
    int i = 1; // 错误：重声明
```

示例：

```cpp
#include <iostream>
#include <vector>
using namespace std;
 
int main() {
    vector<int> v = {0, 1, 2, 3, 4, 5};
 
    for (const int& i : v) // 以 const 引用访问
        cout << i << ' ';
    cout << '\n';
 
    for (auto i : v) // 以值访问，i 的类型是 int
        cout << i << ' ';
    cout << '\n';
 
    for (auto&& i : v) // 以转发引用访问，i 的类型是 int&
        cout << i << ' ';
    cout << '\n';
 
    for (int n : {0, 1, 2, 3, 4, 5}) // 初始化式可以是花括号初始化式列表
        cout << n << ' ';
    cout << '\n';
 
    int a[] = {0, 1, 2, 3, 4, 5};
    for (int n : a) // 初始化式可以是数组
        cout << n << ' ';
    cout << '\n';
}
```

更多内容参见 [基于范围的 for 循环](https://zh.cppreference.com/w/cpp/language/range-for)

## while 语句

以下是 while 语句的结构：

```cpp
while (判断条件) {
  循环体;
}
```

执行顺序：

![](images/while-loop.svg)

e.g. 验证 3x+1 猜想：

```cpp
while (x > 1) {
  if (x % 2 == 1) {
    x = 3 * x + 1;
  } else {
    x = x / 2;
  }
}
```

## do...while 语句

以下是 do...while 语句的结构：

```cpp
do {
  循环体;
} while (判断条件);
```

执行顺序：

![](images/do-while-loop.svg)

与 while 语句的区别在于，do...while 语句是先执行循环体再进行判断的。

e.g. 枚举排列：

```cpp
do {
  // do someting...
} while (next_permutation(a + 1, a + n + 1));
```

## 三种语句的联系

```cpp
// for 语句

for (statement1; statement2; statement3) {
  statement4;
}

// while 语句

statement1;
while (statement2) {
  statement4;
  statement3;
}
```

在 statement4 中没有 `continue` 语句（见下文）的时候是等价的，但是下面一种方法很少用到。

```cpp
// while 语句

statement1;
while (statement2) {
  statement1;
}

// do...while 语句

do {
  statement1;
} while (statement2);
```

在 statement1 中没有 `continue` 语句的时候这两种方式也也是等价的。

```cpp
while (1) {
  // do something...
}

for (;;) {
  // do something...
}
```

这两种方式都是永远循环下去。（可以使用 `break`（见下文）退出。）

可以看出，三种语句可以彼此代替，但一般来说，语句的选用遵守以下原则：

1.  循环过程中有个固定的增加步骤（最常见的是枚举）时，使用 for 语句；
2.  只确定循环的终止条件时，使用 while 语句；
3.  使用 while 语句时，若要先执行循环体再进行判断，使用 do...while 语句。一般很少用到，常用场景是用户输入。

## break 与 continue 语句

break 语句的作用是退出循环。

continue 语句的作用是跳过循环体的余下部分。下面以 continue 语句在 do...while 语句中的使用为例：

```cpp
do {
  // do something...
  continue;  // 等价于 goto END;
// do something...
END:;
} while (statement);

```

break 与 continue 语句均可在三种循环语句的循环体中使用。

一般来说，break 与 continue 语句用于让代码的逻辑更加清晰，例如：

```cpp
// 逻辑较为不清晰，大括号层次复杂

for (int i = 1; i <= n; ++i) {
  if (i != x) {
    for (int j = 1; j <= n; ++j) {
      if (j != x) {
        // do something...
      }
    }
  }
}

// 逻辑更加清晰，大括号层次简单明了

for (int i = 1; i <= n; ++i) {
  if (i == x) continue;
  for (int j = 1; j <= n; ++j) {
    if (j == x) continue;
    // do something...
  }
}
```

```cpp
// for 语句判断条件复杂，没有体现「枚举」的本质

for (int i = l; i <= r && i % 10 != 0; ++i) {
  // do something...
}

// for 语句用于枚举，break 用于「到何时为止」

for (int i = l; i <= r; ++i) {
  if (i % 10 == 0) break;
  // do something...
}
```

```cpp
// 语句重复，顺序不自然

statement1;
while (statement3) {
  statement2;
  statement1;
}

// 没有重复语句，顺序自然

while (1) {
  statement1;
  if (!statement3) break;
  statement2;
}
```
