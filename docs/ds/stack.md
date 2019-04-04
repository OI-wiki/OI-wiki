栈是 OI 中常用的一种线性数据结构，请注意，本文讲的是栈这种数据结构，而非程序运行时的系统栈/栈空间。

栈的修改是按照后进先出的原则进行的，因此栈通常被称为是后进先出（last in first out）表，简称 LIFO 表。

我们可以方便的使用数组来模拟一个栈，如下：

```cpp
int stk[SIZE],top;

stk[++top]=x; //将元素压入栈中
stk[top--]; //弹出栈顶元素
top=0; //清空栈
```

也可以使用 STL 中的栈：参见 [OI Wiki/语言基础/C++ 标准库/STL 容器/容器适配器](/lang/container-adapter)。
