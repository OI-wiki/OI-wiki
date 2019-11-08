author: Ir1d, cjsoft, Lans1ot
类（class）是结构体的拓展，不仅能够拥有成员元素，还拥有成员函数。

在面向对象编程（OOP）中，对象就是类的实例，也就是变量。

Ps：C++ 中 `struct` 关键字定义的也是类，上文中的 **结构体** 的定义来自 C。因为某些历史原因，C++ 保留并拓展了 `struct` 。

## 定义类

类使用关键字 `class` 或者 `struct` 定义，下文以 `class` 举例。

```cpp
class Class_Name{
    ...
};

//Example:
class Edge{
    public:
    int u,v;
    long long w;
    int* nxt;
}e[];

const Edge a;
Edge b,B[];
Edge* c,C[];
```

该例定义了一个名为 `Edge` 的类。该类拥有四个成员元素，其中 `u,v` 的数据类型都为 `int` ， `nxt` 是 `int` 型的指针， `w` 的类型为 `long long` 。

并在 `}` 后定义了一个数据类型为 `Edge` 的数组 `e` 。当然，对于某种已经存在的类型，也可以使用第十三行后中的方法进行定义 [常量](./var.md) 、 [变量](./var.md) 、 [指针](./pointer.md) 。

### 访问符

不同于 [struct](./struct.md) 中的举例，本例中出现了 `public` ，这属于访问符。

-    `public` ：该访问符之后的各个成员都可以被公开访问，简单来说就是无论 **类内** 还是 **类外** 都可以访问。
-    `protected` ：该访问符之后的各个成员可以被 **类内** 或者派生类或者友元的成员访问，但类外 **不能访问** 。
-    `private` ：该访问符之后的各个成员 **只能** 被 **类内** 成员或者友元的成员访问。

对于 `struct` ，它的所有成员都是默认 `public` 。对于 `class` ， 它的所有成员都是默认 ` private ` 。

### 定义同种类型的类指针

需要前置声明。

声明一个将稍后将在此作用域定义的类型，这允许类之间彼此引用。

```cpp
class Edge;
class Edge{
    int u,v;
    long long w;
    Edge* nxt;
};
```

## 访问与修改成员元素的值

对于数据类型为 `Edge` 的变量 `var` ，可以使用 `变量名 + "." + 成员元素名` 进行访问。

如：打印 `var` 的 `v` 变量： `cout<<var.v` 。

对于数据类型为 `Edge` 的指针 `ned` ，可以使用 `指针名 + "->" + 成员元素名` 或者 使用 `(*指针名）+ "." + 成员元素名` 进行访问。

如：修改 `ned` 的成员元素 `nxt` ，并将其赋值为 `tmp` ： `(*ned).nxt = tmp` 或者 `ned->nxt = tmp` 。

## 成员函数

成员函数，顾名思义。就是类中所包含的 [函数](./func.md) 。

??? note "常见成员函数举例。"
    ```cpp
    vector.push_back()
    set.insert()
    queue.empty()
    ```

```cpp
class Class_Name{
    ...
    type Funciton_Name(...){
        ...
    }
};

//Example:
class Edge{
    public:
    int u,v;
    long long w;
    int* nxt;
    void print(){
        cout<<u<<" "<<v<<" "<<w<<" "<<nxt;
        return ;
    }
    void change_w(int);
};

void Edge::change_w(int _w){
    w=_w;
    return ;
}
```

该类有一个打印 `Edge` 成员元素的函数，以及更改成员元素 `w` 的函数。

和 [函数](./func.md) 类似，对于成员函数，也可以先声明，在定义，如第十八行（声明处）以及二十一行后（定义处）。

如果想要调用 `var` 的 `print` 成员函数，可以使用 `var.print()` 进行调用。

### 在实例化变量时设定初始值

为完成这种操作，需要重载 **默认构造函数** (Default constructor)。

```cpp
class Class_Name{
    ...
    Class_Name(...)...{
        ...
    }
};

//Example:
class Edge{
    public:
   	int u,v;
    long long w;
    int* nxt ;
    Edge(){
        u = 0; v = 0;
        w = 0ll;
        nxt = NU::
    }
};
```

该例 **重载** 了 `Edge`的默认构造函数，该函数能够在我们实例化 `Edge` 类型变量时，将所有的成员元素初始化为 `0` 或者 `NULL` 。

若无显式的默认构造函数，则编译器认为该类有隐式的默认构造函数。换言之，若无重载构造函数，则编译器会自动定义一个默认构造函数，并会根据成员元素的类型进行初始化（与定义 [内置类型](./var.md) 变量相同）。

在这种情况下，成员变量的初值可能会具有随机性（如定义局部 `int` 型变量后，无法确定该变量的初始值），可能会造成程序运行错误（Running Error），或者造成答案错误（Wrong Answer）。

如果需要自定义初始化的值，可以在重载默认构造函数时增加参数。

如两个函数名相同但参数不相同，且在调用时不会出现混淆时，则编译器认为两个函数时不同的。并会根据调用时所填参数判断应调用函数。

可以使用 `{}` 进行变量的初始化， **当且仅当** 使用 `C++11` 标准或以上。

若要在为一个类变量赋值非同等类型值（常为 [内置类型](./var.md) ）时进行报错，请使用 `explicit` 关键字。

```cpp
class Edge{
    public:
    int u,v;
    long long w;
    int* nxt;
    Edge(){
        u = 0; v = 0;
        w = 0ll;
        nxt = NULL;
    }
    explicit Edge(int _u, int _v, long long _w, int* _nxt){
        u = _u; v = _v;
        w = _w;
        nxt = _nxt;
    }
    //the same as
    //Edge(int _u, int _v, long long _w, int* _nxt):u（_u), v(_v), w(_w), nxt(_nxt) {}
};

//the same as
//Edge::Edge(int _u, int _v, long long _w, int* _nxt){
//        u = _u; v = _v;
//        w = _w;
//        nxt = _nxt;
//}

Edge A;                //ok
Edge B(1,2,5ll,NULL);  //ok
Edge C=1;              //error
Edge D{1,2,5ll,NULL};  // ok,c++11
```

### 销毁

这是不可避免的问题。每一个变量都将在作用范围结束走向销毁。

但对于指针，如果用指针动态申请内存，则在指针销毁时，则不会返还之前申请的内存，便造成了内存泄漏（memory leak)。需要手动使用 `delete` 进行销毁。

如果结构体的成员元素包含指针，同样会遇到这种问题。需要用到析构函数。

 **析构** 函数（Destructor）将会在该变量被销毁时被调用。重载的方法形同构造函数，但需要在前加 `~` 

如果没有用户重载的析构函数，则编译器会默认定义一个析构函数。

_默认定义的析构函数对于指针使用十分少见的算法竞赛已经足够使用。只有在成员元素包含指针时才可能会重载析构函数。_

```cpp
class Edge{
    public:
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

### 为类变量赋值

默认情况下，赋值时会按照对应成员元素赋值的规则进行。也可以使用 `类名称()` 或 `类名称{}` 作为临时变量来进行赋值。前者需要重载相应默认构造函数，后者则需要支持 `C++11` 标准或以上。

```cpp
Edge tmp1=A;
Edge tmp2=Edge{...},tmp3;
tmp3=Edge(...);
```

默认情况下，进行的赋值都是 **浅拷贝** ，如果成员元素中有指针，则在赋值完成后，两个变量的成员指针具有相同的地址。

如需解决指针问题或更多操作，需要重载相应 **constructor** 。

_更多 constructor/destructor，参见“参考资料”第六条。_

### 重载运算符

重载运算符，可以部分程度上代替函数，简化代码。

下面给出重载运算符的例子。

```cpp
class Vector{
    public:
    int x,y;
    Vector():x(_x),y(_y) {}
    Vector(int _x,int _y):x(_x),y(_y) {}
    int operator* (const Vector& other){
        return x * other.y + y * other.x;
    }
    Vector operator+ (const Vector&);
    Vector operator- (const Vector&);
};

Vector Vector::operator+ (const Vector& other){
    return Vector(x + other.x ,y + other.y );
}

Vector Vector::operator- (const Vector& other){
    return Vector(x - other.x ,y - other.y );
}
```

该例定义了一个向量类，并重载了 ` * + -` 运算符，并分别代表向量内积，向量加，向量减。

重载运算符的模板大致可分为下面几部分。

```cpp
类定义内重载： 返回类型 operator符号 （参数）{...}
类定义内声明，在外部定义： 返回类型 类名称::operator符号 （参数）{...}
```

对于自定义的类，如果重载了某些运算符，便可以使用相应的 stl 容器或算法，如 [ `sort` ](../basic/stl-sort.md) 。

_如要了解更多，参见“参考资料”第四条，。_

??? note " 可以被重载的运算符。"

      ```cpp
         =
         +  -  *  /  =  %
         +=  -=  *=  /=  %=
         <  >  ==  !=  <=  >=  
         &  |  !  ^  ~
         &=  |=  ^= 
         //----------
         <<  <<=  >>  >>=
         ++  -- 
         &&  ||  
         []  ()  ,
         ->*  ->  new  delete  new[]  delete[]
      ```

## 参考资料

1.   [cppreference class](https://zh.cppreference.com/w/cpp/language/class) 
2.   [cppreference access](https://zh.cppreference.com/w/cpp/language/access) 
3.   [cppreference default_constructor](https://zh.cppreference.com/w/cpp/language/default_constructor) 
4.   [cppreference operator](https://zh.cppreference.com/w/cpp/language/operators) 
5.   [cplusplus Data structures](http://www.cplusplus.com/doc/tutorial/structures/) 
6.   [cplusplus Special members](http://www.cplusplus.com/doc/tutorial/classes2/) 
7.   [C++11 FAQ](http://www.stroustrup.com/C++11FAQ.html) 
