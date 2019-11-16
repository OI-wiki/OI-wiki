author: Ir1d, cjsoft, Lans1ot
结构体（struct），可以看做是一系列称为成员元素的组合体。

可以看做是自定义的数据类型。

_事实上不同于 C 中 `struct` ，在 C++ 中 `struct` 被扩展为类似 [ `class` ](./class.md) 的类说明符_。

## 定义结构体

```cpp
struct Edge {
  int u, v;
  long long w;
  int* nxt;
} e[array_length];

const Edge a;
Edge b, B[array_length];
Edge* c;
```

上例中定义了一个名为 `Edge` 的类型，有四个成员元素 `u,v,w,nxt` 。其中 `u,v` 的数据类型都为 `int` ， `nxt` 是 `int` 型的指针， `w` 的类型为 `long long` 。

并在 `}` 后，定义了一个数据类型为 `Edge` 的数组 `e` 。当然，对于某种已经存在的类型，也可以使用第七行后中的方法进行定义 常量、变量、指针。

_关于指针：不必强求掌握。_

### 定义结构体指针

在定义中使用 `ClassName*` 进行定义。

```cpp
struct Edge {
  int u, v;
  long long w;
  Edge* nxt;
};
```

## 访问/修改成员元素

可以使用 `变量名.成员元素名` 进行访问（其中双引号不写入程序，下同）。

如 : 输出 `var` 的 `v` 成员： `cout << var.v` 。

也可以使用 `指针名->成员元素名` 或者 使用 `(*指针名).成员元素名` 进行访问。

如 : 将结构体指针 `ptr` 指向的结构体的成员元素 `nxt` 赋值为 `tmp` ： `(*ptr).nxt = tmp` 或者 `ptr->nxt = tmp` 。

## 更多的操作？

详见 [类](./class.md) 

## 参考资料

1.   [cppreference class](https://zh.cppreference.com/w/cpp/language/class) 
2.   [cplusplus Data structures](http://www.cplusplus.com/doc/tutorial/structures/) 
