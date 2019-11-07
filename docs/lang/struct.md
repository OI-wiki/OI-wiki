结构体(struct)，可以看做是一系列称为成员元素(变量、指针)的组合体。

可以看做是自定义的[数据类型](./var.md)，用于减小编程难度。

*事实上在C++中struct被扩展为类似[类](./class.md)的类说明符*。



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

上例中定义了一个名为*Edge*的类型，有四个成员元素 *u,v,w,nxt*。其中*u,v*的数据类型都为*int*，*nxt*是*int*型的指针，*w*的类型为*long long*。

并在第四行  **" } "**  后，定义了一个数据类型为*Edge*的数组*e*。当然，对于某种已经存在的类型，也可以使用第七行后中的方法进行定义[常量](./var.md)、[变量](./var.md)、[指针](./pointer.md)。


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


对于数据类型为*Edge*的变量*var*，可以使用 **变量名 + "." + 成员元素名** 进行访问。

如 打印*var*的*v*变量：**" cout<<val.v ;"。**

对于数据类型为*Edge*的指针*ned*，可以使用**指针名 + "->" + 成员元素名** 或者 使用**(\* 指针名) + "." + 成员元素名 **进行访问。

如 修改*ned*的成员元素*nxt*，并将其赋值为*tmp*：**"(\*ned).nxt = tmp" 或者 "ned->nxt = tmp"**。

当使用指针时，请谨慎使用[**\***](./pointer.md)操作符，如果你的的成员元素中存在指针，有可能在使用**\***时会进行错误的访问： 如**”\*ned.nxt **与 **\*(ned.nxt)**作用相同，而不是**\*(ned).nxt“**。

### 在实例化变量时设定初始值

*以下内容属于类，请查看[类](./class.md)了解更多*

为了完成这种操作，需要重载**默认构造函数**(Default constructor)。

```text
struct Function_Name{
    ...
    Function_Name(...) ... {
        ...
    }
};
//Example:
struct Edge{
    int u,v;
    long long w;
    int* nxt;
    Edge(){
        u = 0; v = 0;
        w = 0ll;
        nxt = NULL;
    }
};
```

上例中重载了一个*Edge*的默认构造函数，该函数能够在我们实例化*Edge*类型变量时，将所有的成员元素初始化为0或者NULL。

若无重载构造函数，则编译器会默认定义一个构造函数。

如果需要自定义初始化的值，可以在定义构造函数时增加参数。

```text
struct Edge{
    int u,v;
    long long w;
    int* nxt;
    Edge(){
        u = 0; v = 0;
        w = 0ll;
        nxt = NULL;
    }
    Edge(int _u, int _v, long long _w,int* _nxt){
        u = _u; v = _v;
        w = _w;
        nxt = _nxt;
    }
};

Edge A;
Edge B(1,2,5ll,NULL);
```

如两个函数名相同但参数不相同，且在调用时不会出现混淆时，则编译器认为两个函数时不同的。

并会根据调用时所填参数判断应调用参数。


### 销毁


这是一个不可避免的问题。每一个变量都将在作用范围结束走向销毁。

但对于指针，如果用指针动态申请内存，则在指针销毁时，则不会返还之前申请的内存，便造成了内存泄漏(memory leak)。需要手动使用delete进行销毁。

如果结构体的成员元素包含指针，同样会遇到这种问题。需要用到析构函数。

**析构**函数(Destructor)将会在该变量被销毁时被调用。重载的方法形同构造函数，但需要在前加"~"

```text
struct Edge{
    int u,v;
    long long w;
    int* nxt;
    Edge(){
        u = 0; v = 0;
        w = 0ll;
        nxt = NULL;
    }
    ~Edge(){
        delete nxt;
    }
};
```

## 更多的操作？

详见[类](./class.md)

## 参考资料

1.  [cppreference class](<https://zh.cppreference.com/w/cpp/language/class>)
2.  [cppreference default_constructor](<https://zh.cppreference.com/w/cpp/language/default_constructor>)
3.  [cplusplus Data structures](<http://www.cplusplus.com/doc/tutorial/structures/>)
4.  [cplusplus Special members](<http://www.cplusplus.com/doc/tutorial/classes2/>)