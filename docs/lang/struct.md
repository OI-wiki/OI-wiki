author: Ir1d, cjsoft, Lans1ot
结构体（struct），可以看做是一系列称为成员元素（变量、指针）的组合体。

可以看做是自定义的 [数据类型](./var.md) 。

_事实上在 C++ 中 struct 被扩展为类似 [class](./class.md) 的类说明符_。

## 定义结构体

```text
struct Edge{
    int u,v;
    long long w;
    int* nxt;
}e[];

const Edge a;
Edge b,B[];
Edge* c,C[];
```

上例中定义了一个名为_Edge_的类型，有四个成员元素_u,v,w,nxt_。其中_u,v_的数据类型都为_int_，_nxt_是_int_型的指针，_w_的类型为_long long_。

并在 `}` 后，定义了一个数据类型为_Edge_的数组_e_。当然，对于某种已经存在的类型，也可以使用第七行后中的方法进行定义 [常量](./var.md) 、 [变量](./var.md) 、 [指针](./pointer.md) 。

### 定义结构体指针

需要前置声明。

声明一个将稍后将在此作用域定义的类型，这允许类之间彼此引用。

```text
struct Edge;
struct Edge{
    int u,v;
    long long w;
    Edge* nxt;
};
```

## 访问/修改成员元素

对于数据类型为_Edge_的变量_var_，可以使用 `变量名 + "." + 成员元素名` 进行访问。

如 : 打印_var_的_v_变量： `cout<<val.v`。 

对于数据类型为_Edge_的指针_ned_，可以使用 `指针名 + "->" + 成员元素名` 或者 使用 `(*指针名） + "." + 成员元素名` 进行访问。

如 : 修改_ned_的成员元素_nxt_，并将其赋值为_tmp_： `(*ned).nxt = tmp`或者`ned->nxt = tmp` 。

## 更多的操作？

详见 [类](./class.md) 

## 参考资料

1.   [cppreference class](https://zh.cppreference.com/w/cpp/language/class) 
2.   [cplusplus Data structures](http://www.cplusplus.com/doc/tutorial/structures/) 
