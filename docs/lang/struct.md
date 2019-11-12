author: Ir1d, cjsoft, Lans1ot
结构体（struct），可以看做是一系列称为成员元素（变量、指针）的组合体。

可以看做是自定义的数据类型。

_事实上在 C++ 中 `struct` 被扩展为类似 [ `class` ](./class.md) 的类说明符_。

## 定义结构体

```cpp
struct Edge {
  int u, v;
  long long w;
  int* nxt;
} e[array_length];

const Edge a;
Edge b, B[array_length];
Edge *c, C[array_length];
```

上例中定义了一个名为 `Edge` 的类型，有四个成员元素 `u,v,w,nxt` 。其中 `u,v` 的数据类型都为 `int` ， `nxt` 是 `int` 型的指针， `w` 的类型为 `long long` 。

并在 `}` 后，定义了一个数据类型为 `Edge` 的数组 `e` 。当然，对于某种已经存在的类型，也可以使用第七行后中的方法进行定义 常量、变量、指针。

### 定义结构体指针

需要前置声明。

声明一个将稍后将在此作用域定义的类型，这允许类之间彼此引用。

```cpp
struct Edge;
struct Edge {
  int u, v;
  long long w;
  Edge* nxt;
};
```

## 访问/修改成员元素

对于数据类型为 `Edge` 的变量 `var` ，可以使用 `变量名"."成员元素名` 进行访问（其中双引号不写入程序，下同）。

如 : 打印 `var` 的 `v` 变量： `cout << var.v` 。

对于数据类型为 `Edge` 的指针 `ned` ，可以使用 `指针名"->"成员元素名` 或者 使用 `(*指针名）"."成员元素名` 进行访问。

如 : 修改 `ned` 的成员元素 `nxt` ，并将其赋值为 `tmp` ： `(*ned).nxt = tmp` 或者 `ned->nxt = tmp` 。

## 更多的操作？

详见 [类](./class.md) 

## 参考资料

1.   [cppreference class](https://zh.cppreference.com/w/cpp/language/class) 
2.   [cplusplus Data structures](http://www.cplusplus.com/doc/tutorial/structures/) 
