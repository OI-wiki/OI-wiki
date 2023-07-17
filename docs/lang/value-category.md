**注意**：这部分的内容很可能对算法竞赛无用，但如果你希望更深入地理解 C++，写出更高效的代码，那么本文的内容也许会对你有所帮助。

每个 C++ 表达式都有两个属性：类型 (type) 和值类别 (value category)。前者是大家都熟悉的，但作为算法竞赛选手，很可能完全不知道后者是什么。不管你在不在意，值类别是 C++ 中非常重要的一个概念。

???+ note "关于名词的翻译"
    type 和 category 都可以翻译为「类型」或「类别」，但为了区分两者，下文中统一将 type 翻译为「类型」，category 翻译为「类别」。

## 从 CPL 语言的定义说起

左值与右值的概念最早出现在 C 语言的祖先语言：CPL。

在 CPL 的定义中，lvalue 意为 left-hand side value，即能够出现在赋值运算符（等号）左侧的值，右值的定义亦然。

## C 和 C++11 以前

C 语言沿用了相似的分类方法，但左右值的判断标准已经与赋值运算符无关。在新的定义中，lvalue 意为 locate value，即能进行取地址运算 (`&`) 的值。

可以这么理解：左值是有内存地址的对象，而右值只是一个中间计算结果（虽然编译器往往需要在内存中分配地址来储存这个值，但这个内存地址是无法被程序员感知的，所以可以认为它不存在）。中间计算结果就意味着这个值马上就没用了，以后不会再访问它。

比如在 `int a = 0;` 这段代码中，`a` 就是一个左值，而 `0` 是一个右值。

???+ warning "常见的关于左右值的误解"
    以下几种类型是经常被误认为右值的左值：
    
    -   **字符串字面量**：由于 C++ 兼容 C 风格的字符串，需要能对一个字符串字面量取地址（即头指针）来传参。但是其他的字面量，包括自定义字面量，都是右值。
    -   **数组**：数组名就是数组首个元素的指针这种说法似乎误导了很多人，但这个说法显然是错误的，对数组进行取地址是可以编译的。数组名可以隐式的退化成首个元素的指针，这才是右值。

## C++11 开始

从 C++11 开始，为了配合移动语义，值的类别就不是左值右值这么简单了。

考虑一个简单的场景：

```cpp
std::vector<int> a{...};
std::vector<int> b;
b = a;
```

我们知道第三行的赋值运算复杂度是正比于 `a` 的长度的，复制的开销很大。但有些情况下，比如 `a` 在以后的代码中不会再使用，那么我们完全可以把 `a` 所持有的内存「转移」到 `b` 上，这就是移动语义干的事情。

我们姑且不管移动是怎么实现的，先来考虑一下我们如何标记 `a` 是可以移动的。显然不管能否移动，这个表达式的类型都是 `vector` 不变，所以只能对值类别下手。不可移动的 `a` 是左值，如果要在原有的体系下标记可以移动的 `a`，我们只能把它标记为右值。但标记为右值又是不合理的，因为这个 `a` 实际上拥有自己的内存地址，与其他右值有有根本上的不同。所以 C++11 引入了 亡值 (xvalue) 这一值类别来标记这一种表达式。

于是我们现在有了三种类别：左值 (lvalue)、纯右值 (prvalue)、亡值 (xvalue)（纯右值就是原先的右值）。

然后我们发现亡值同时具有一些左值和纯右值的性质，比如它可以像左值一样取地址，又像右值一样不会再被访问。

所以又有了两种组合类别：泛左值 (glvalue)（左值和亡值）、右值 (rvalue)（纯右值和亡值）。

有一个初步的感性理解后，来看一下标准委员会对它们的定义：

-   A **glvalue**(generalized lvalue) is an expression whose evaluation determines the identity of an object, bit-field, or function.
-   A **prvalue**(pure rvalue) is an expression whose evaluation initializes an object or a bit-field, or computes the value of an operand of an operator, as specified by the context in which it appears, or an expression that has type cv void.
-   An **xvalue**(eXpiring value) is a glvalue that denotes an object or bit-field whose resources can be reused（usually because it is near the end of its lifetime）。
-   An **lvalue** is a glvalue that is not an xvalue.
-   An **rvalue** is a prvalue or an xvalue.

上述定义中提到了一个叫位域 (bit-field) 的东西。如果你不知道位域是什么，忽略它即可，后文也不会提及。

其中关键的两个概念：

-   是否拥有身份 (identity)：可以确定表达式是否与另一表达式指代同一实体，例如比较它们所标识的对象或函数的（直接或间接获得的）地址
-   是否可以被移动 (resources can be reused)：对象的资源可以移动到别的对象中

这 5 种类型无非就是根据上面两种属性的是与否区分的，所以用下面的这张表格可以帮助理解：

|             | 拥有身份（glvalue） | 不拥有身份   |
| ----------- | ------------- | ------- |
| 可移动（rvalue） | xvalue        | prvalue |
| 不可移动        | lvalue        | 不存在     |

注意不拥有身份就意味着这个对象以后无法被访问，这样的对象显然是可以被移动的，所以不存在不拥有身份不可移动的值。

## C++17 带来的新变化

从拷贝到移动提升了不少速度，那么我们是否能够优化的更彻底一点，把移动的开销都省去呢？

考虑这样的代码：

```cpp
std::vector<int> make_vector(...) {
  std::vector<int> result;
  // ...
  return result;
}

std::vector<int> a = make_vector(...);
```

`make_vector` 函数根据一输入生成一个 `vector`。这个 `vector` 一开始在 `make_vector` 的栈上被构造，随后又被移动到调用者的栈上，需要一次移动操作，这显然很浪费，能不能省略这次移动？

答案是肯定的，这就是 RVO 优化，即省略拷贝。通常的方法是编译器让 `make_vector` 返回的对象直接在调用者的栈上构造，然后 `make_vector` 在上面进行修改。这相当与这样的代码：

```cpp
void make_vector(std::vector<int>& result, ...) {
  // ... (对 result 进行操作)
}

std::vecctor<int> a;
make_vector(a, ...);
```

在 C++17 以前，尽管标准未做出规定，但主流编译器都实现了这种优化。在 C++17 以后，这种优化成为标准的硬性规定。

回到和移动语义刚被提出时的问题，如何确定一个移动赋值是可以省略的？再引入一种新的值类别？

不，C++11 的值类别已经够复杂了。我们意识到在 C++11 的标准下，亡值和纯右值都是可以移动的，那么就可以在这两种类别上做文章。

C++17 以后，纯右值不再能移动，但可以隐式地转变为亡值。对于纯右值用于初始化的情况下，可以省略拷贝，而其他不能省略的情况下，隐式转换为亡值进行移动。

所以在 C++17 之后的值类别，被更为整齐的划分为泛左值与纯右值两大块，右值存在的意义被削弱。这样的改变某种程度上简化了整个值类别体系。

## 参考文献与推荐阅读

1.  [Value categories](https://en.cppreference.com/w/cpp/language/value_category)
2.  [Wording for guaranteed copy elision through simplified value categories](http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2016/p0135r1.html)
3.  [C++ 中的值类别](https://paul.pub/cpp-value-category/)
