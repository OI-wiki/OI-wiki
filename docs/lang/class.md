author: Ir1d, cjsoft, Lans1ot
类（class）是结构体的拓展，不仅能够拥有成员元素，还拥有成员函数。

在面向对象编程（OOP）中，对象就是类的实例，也就是变量。

C++ 中 `struct` 关键字定义的也是类，上文中的 **结构体** 的定义来自 C。因为某些历史原因，C++ 保留并拓展了 `struct`。

## 定义类

类使用关键字 `class` 或者 `struct` 定义，下文以 `class` 举例。

```cpp
class ClassName {
  ...
};

// Example:
class Object {
 public:
  int weight;
  int value;
} e[array_length];

const Object a;
Object b, B[array_length];
Object *c;
```

与使用 `struct` 大同小异。该例定义了一个名为 `Object` 的类。该类拥有四个成员元素，分别为 `weight,value`；并在 `}` 后定义了一个数组 `B`。

定义类的指针形同 [`struct`](./struct.md)。

### 访问说明符

不同于 [`struct`](./struct.md) 中的举例，本例中出现了 `public`，这属于访问说明符。

- `public`：该访问说明符之后的各个成员都可以被公开访问，简单来说就是无论 **类内** 还是 **类外** 都可以访问。
- `protected`：该访问说明符之后的各个成员可以被 **类内**、派生类或者友元的成员访问，但类外 **不能访问**。
- `private`：该访问说明符之后的各个成员 **只能** 被 **类内** 成员或者友元的成员访问，**不能** 被从类外或者派生类中访问。

对于 `struct`，它的所有成员都是默认 `public`。对于 `class`，它的所有成员都是默认 `private`。

*关于 "友元" 和 "派生类"，可以参考下方折叠框，或者查询网络资料进行详细了解。*

*对于算法竞赛来说，友元和派生类并不是必须要掌握的知识点。*

??? note "关于友元以及派生类的基本概念"
    友元（`friend`）：使用 `friend` 关键字修饰某个函数或者类。可以使得在 **被修饰者** 在不成为成员函数或者成员类的情况下，访问该类的私有（`private`）或者受保护（`protected`）成员。简单来说就是只要带有这个类的 `friend` 标记，就可以访问私有或受保护的成员元素。
    
    派生类（`derived class`）：C++ 允许使用一个类作为 **基类**，并通过基类 **派生** 出 **派生类**。其中派生类（根据特定规则）继承基类中的成员变量和成员函数。可以提高代码的复用率。
    
    派生类似 "is" 的关系。如猫（派生类）"is" 哺乳动物（基类）。
    
    对于上面 `private` 和 `protected` 的区别，可以看做派生类可以访问基类的 `protected` 的元素（`public` 同），但不能访问 `private` 元素。

## 访问与修改成员元素的值

方法形同 [`struct`](./struct.md)

- 对于变量，使用 `.` 符号。
- 对于指针，使用 `->` 符号。

## 成员函数

成员函数，顾名思义。就是类中所包含的函数。

??? note "常见成员函数举例"
    ```cpp
    vector.push_back();
    set.insert();
    queue.empty();
    ```

```cpp
class Class_Name {
  ... type Function_Name(...) { ... }
};

// Example:
class Object {
 public:
  int weight;
  int value;
  void print() {
    cout << weight << endl;
    return;
  }
  void change_w(int);
};

void Object::change_w(int _weight) { weight = _weight; }
```

该类有一个打印 `Object` 成员元素的函数，以及更改成员元素 `weight` 的函数。

和函数类似，对于成员函数，也可以先声明，在定义，如第十四行（声明处）以及十七行后（定义处）。

如果想要调用 `var` 的 `print` 成员函数，可以使用 `var.print()` 进行调用。

### 重载运算符

??? note "何为重载"
    C++ 允许编写者为名称相同的函数或者运算符指定不同的定义。这称为 **重载**（overload）。
    
    如果同名函数的参数种类、数量、返回类型不相同其中一者或多者两两不相同，则这些同名函数被看做是不同的。
    
    如果在调用时不会出现混淆（指调用某些同名函数时，无法根据所填参数种类和数量唯一地判断出被调用函数。常发生在具有默认参数的函数中），则编译器会根据调用时所填参数判断应调用函数。
    
    而上述过程被称作重载解析。

重载运算符，可以部分程度上代替函数，简化代码。

下面给出重载运算符的例子。

```cpp
class Vector {
 public:
  int x, y;
  Vector() : x(0), y(0) {}
  Vector(int _x, int _y) : x(_x), y(_y) {}
  int operator*(const Vector& other) { return x * other.y + y * other.x; }
  Vector operator+(const Vector&);
  Vector operator-(const Vector&);
};

Vector Vector::operator+(const Vector& other) {
  return Vector(x + other.x, y + other.y);
}

Vector Vector::operator-(const Vector& other) {
  return Vector(x - other.x, y - other.y);
}
//关于4,5行表示为x,y赋值，具体实现参见后文。
```

该例定义了一个向量类，并重载了 `* + -` 运算符，并分别代表向量内积，向量加，向量减。

重载运算符的模板大致可分为下面几部分。

```text
/*类定义内重载*/ 返回类型 operator符号(参数){...}

/*类定义内声明，在外部定义*/ 返回类型 类名称::operator符号(参数){...}
```

对于自定义的类，如果重载了某些运算符（一般来说只需要重载 `<` 这个比较运算符），便可以使用相应的 STL 容器或算法，如 [`sort`](../basic/stl-sort.md)。

*如要了解更多，参见“参考资料”第四条。*

??? note " 可以被重载的运算符"
    ```cpp
    = +-* / = % += -= *= /= %= <> == != <= >= & | !^~ &= |= ^=
        //----------
        << <<= >> >>= ++--&& || [](),
        ->*->new delete new[] delete[]
    ```

### 在实例化变量时设定初始值

为完成这种操作，需要定义 **默认构造函数**(Default constructor)。

```cpp
class ClassName {
  ... ClassName(...)... { ... }
};

// Example:
class Object {
 public:
  int weight;
  int value;
  Object() {
    weight = 0;
    value = 0;
  }
};
```

该例定义了 `Object` 的默认构造函数，该函数能够在我们实例化 `Object` 类型变量时，将所有的成员元素初始化为 `0`。

若无显式的构造函数，则编译器认为该类有隐式的默认构造函数。换言之，若无定义任何构造函数，则编译器会自动生成一个默认构造函数，并会根据成员元素的类型进行初始化（与定义 内置类型 变量相同）。

在这种情况下，成员元素都是未初始化的，访问未初始化的变量的结果是未定义的（也就是说并不知道会返回和值）。

如果需要自定义初始化的值，可以再定义（或重载）构造函数。

??? note "关于定义(或重载)构造函数"
    一般来说，默认构造函数是不带参数的，这区别于构造函数。构造函数和默认构造函数的定义大同小异，只是参数数量上的不同。
    
    构造函数可以被重载（当然首次被叫做定义）。需要注意的是，如果已经定义了构造函数，且构造函数的参数列表不为空，那么编译器便不会再生成无参数的默认构造函数。这会可能会使试图以默认方法构造变量的行为编译失败（指不填入初始化参数）。

使用 C++11 或以上时，可以使用 `{}` 进行变量的初始化。

??? note "关于`{}`"
    使用 `{}` 进行初始化，会用到 std::initializer_list 这一个轻量代理对象进行初始化。
    
    初始化步骤大概如下
    
    1. 尝试寻找参数中有 `std::initializer_list` 的默认构造函数，如果有则调用（调用完后不再进行下面的查找，下同）。
    
    2. 尝试将 `{}` 中的元素填入其他构造参数，如果能将参数按照顺序填满（默认参数也算在内），则调用该默认构造函数。
    
    3. 若无 `private` 成员元素，则尝试在 **类外** 按照元素定义顺序或者下标顺序依次赋值。
    
    *上述过程只是完整过程的简化版本，详细内容参见 "参考资料九"*

```cpp
class Object {
 public:
  int weight;
  int value;
  Object() {
    weight = 0;
    value = 0;
  }
  Object(int _weight = 0, int _value = 0) {
    weight = _weight;
    value = _value;
  }
  // the same as
  // Object(int _weight,int _value):weight(_weight),value(_value) {}
};

// the same as
// Object::Object(int _weight,int _value){
//   weight = _weight;
//   value = _value;
// }
//}

Object A;        // ok
Object B(1, 2);  // ok
Object C{1, 2};  // ok,(C++11)
```

??? note "关于隐式类型转换"
    有时候会写出如下的代码
    
    ```cpp
    class Node {
     public:
      int var;
      Node(int _var) : var(_var) {}
    };
    Node a = 1;
    ```
    
    看上去十分不符合逻辑，一个 `int` 类型不可能转化为 `node` 类型。但是编译器不会进行 `error` 提示。
    
    原因是在进行赋值时，首先会将 `1` 作为参数调用 `node::node(int)`，然后调用默认的复制函数进行赋值。
    
    但大多数情况下，编写者会希望编译器进行报错。这时便可以在构造函数前追加 `explicit` 关键字。这会告诉编译器必须显式进行调用。
    
    ```cpp
    class Node {
     public:
      int var;
      explicit Node(int _var) : var(_var) {}
    };
    ```
    
    也就是说 `node a=1` 将会报错，但 `node a=node(1)` 不会。因为后者显式调用了构造函数。当然大多数人不会写出后者的代码，但此例足以说明 explicit 的作用。
    
    *不过在算法竞赛中，为了避免此类情况常用的是 "加强对代码的规范程度"，从源头上避免*

### 销毁

这是不可避免的问题。每一个变量都将在作用范围结束走向销毁。

但对于已经指向了动态申请的内存的指针来说，该指针在销毁时不会自动释放所指向的内存，需要手动释放动态内存。

如果结构体的成员元素包含指针，同样会遇到这种问题。需要用到析构函数来手动释放动态内存。

**析构** 函数（Destructor）将会在该变量被销毁时被调用。重载的方法形同构造函数，但需要在前加 `~`

*默认定义的析构函数通常对于算法竞赛已经足够使用，通常我们只有在成员元素包含指针时才会重载析构函数。*

```cpp
class Object {
 public:
  int weight;
  int value;
  int* ned;
  Object() {
    weight = 0;
    value = 0;
  }
  ~Object() { delete ned; }
};
```

### 为类变量赋值

默认情况下，赋值时会按照对应成员元素赋值的规则进行。也可以使用 `类名称()` 或 `类名称{}` 作为临时变量来进行赋值。

前者只是调用了复制构造函数（copy constructor)，而后者在调用复制构造函数前会调用默认构造函数。

另外默认情况下，进行的赋值都是对应元素间进行 **浅拷贝**，如果成员元素中有指针，则在赋值完成后，两个变量的成员指针具有相同的地址。

```cpp
// A,tmp1,tmp2,tmp3类型为Object
tmp1 = A;
tmp2 = Object(...);
tmp3 = {...};
```

如需解决指针问题或更多操作，需要重载相应的构造函数。

*更多 构造函数（constructor）内容，参见“参考资料”第六条。*

## 参考资料

1. [cppreference class](https://zh.cppreference.com/w/cpp/language/class)
2. [cppreference access](https://zh.cppreference.com/w/cpp/language/access)
3. [cppreference default_constructor](https://zh.cppreference.com/w/cpp/language/default_constructor)
4. [cppreference operator](https://zh.cppreference.com/w/cpp/language/operators)
5. [cplusplus Data structures](http://www.cplusplus.com/doc/tutorial/structures/)
6. [cplusplus Special members](http://www.cplusplus.com/doc/tutorial/classes2/)
7. [C++11 FAQ](http://www.stroustrup.com/C++11FAQ.html)
8. [cppreference Friendship and inheritance](http://www.cplusplus.com/doc/tutorial/inheritance/)
9. [cppreference value initialization](https://zh.cppreference.com/w/cpp/language/value_initialization)
