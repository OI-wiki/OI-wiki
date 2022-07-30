## 简介

序理论（order theory）是使用二元关系（binary relation）研究顺序的数学分支。

集合 $A, B$ 上的二元关系就是 $A, B$ 的笛卡儿积 $A \times B$ 的子集。  

## 定义

### 偏序和全序

有限集上的偏序关系常用哈斯图（Hasse diagram）表示。

偏序集合（partially ordered set, poset）就是具有偏序（partial order）的集合，偏序是特殊的二元关系；$\leq$ 是集合 $S$ 上的偏序，当且仅当其对于 $S$ 的任意元素满足：

1. 自反性：$a \leq a$；
2. 反对称性：若 $a \leq b$ 且 $b \leq a$，则 $a = b$；
3. 传递性： 如果 $a \leq b$ 且 $b \leq c$，则 $a \leq c$。

全序集合（totally ordered set, linearly ordered set, loset）就是具有全序（total order, linear order）的集合，全序就是满足全序性的偏序：

4. 全序性：$a\leq b$ 或 $b\leq a$

### 偏序下的特殊元素

偏序集合中，$a$ 是最小元（least element）当且仅当对于任意元素 $b$ 有 $a \leq b$，$a$ 是最大元（greatest element）当且仅当对于任意元素 $b$ 有 $b \leq a$，$a$ 是极小元（minimal element）当且仅当不存在非 $a$ 的元素 $b$ 使得 $b \leq a$，$a$ 是极大元（maximal element）当且仅当不存在非 $a$ 的元素 $b$ 使得 $a \leq b$。

由于反对称性，最小元是极小元，最大元是极大元，最小元和最大元存在时一定唯一，极小元和极大元不一定唯一，最小元和最大元可能不存在，极小元和极大元也可能不存在。

以 $\left\{ 2, 3, 4, 5, 6 \right\}$ 为例，规定 $a \leqslant b$ 当且仅当 $a \mid b$；其中，不存在最小元和最大元，$2, 3, 5$ 是极小元，$4, 5, 6$ 是极大元，

### 对偶

偏序 $\preceq$ 是 $\leq$ 的对偶（dual）当且仅当 $a \preceq b \iff b \leq a$。

## 相关领域和应用

尽管大多数数学领域通过自定的方法使用次序，但也有一些理论的关系远远超出了应用范围。以下我们会着重介绍他们和序理论的关联。

### 通用代数

和之前提到的一样，通用代数的方法和形式是许多序理论的重要工具。除了根据满足某些定义的代数结构形式化次序外，还可以建立与代数的其他联系。布尔代数和布尔环之间的对应关系就是一个例子。其他问题与自由结构的存在有关，例如基于一个给定生成器集的自由格（free lattices）。此外，闭包算子（closure operator）的研究在通用代数中也很重要。

### 拓扑

在拓扑学中，次序起着非常重要的作用。事实上，开集的集合提供了一个完整格的例子，或者准确地说是一个完整的 Heyting 代数（或“框架”（frame）/“区域”（locale））。滤子和网是与序理论密切相关的概念，集合的闭包算子可用于定义拓扑。除了这些以外，拓扑也可以仅从开集格的角度来看待。此外，拓扑底层集合的元素的自然 git s 预序由所谓的特化顺序给出，如果拓扑是 $T_{0}$，这实际上是偏序。

### 范畴论

使用哈斯图的次序可视化有一个简单的概括：不是在较大的元素下方显示较小的元素，次序的方向也可以通过向图的边缘给出方向来描述。这样，每个序就可以被看作是一个有向无环图，其中节点是偏序集的元素，并且当且仅当 $a \leq b$ 时存在从 $a$ 到 $b$ 的有向路径。去掉非循环的要求，还可以获得所有的预序（preorder）。

### 算法

[C++ 基础库的排序函数](../basic/stl-sort.md) 中有偏序关系的应用。很多情况时，我们需要在 C++ 中自定义比较器（custom comparator），而 STL 自定义比较器的要求就是它必须为 **严格弱序** 的（strict weak ordering）。严格弱序定义为部分有序集合，其中不可比性是传递关系。设比较器为 $f$，$f(x,y)$ 为真表示 $x<y$，则有：

- $f(x,x)$ 必须为假。（非自反性）

- 如果 $f(x,y)$ 为真，则 $f(y,x)$ 必须为假。（非对称性）

- 如果 $f(x,y)$ 为真且 $f(y,z)$ 为真，则 $f(x,z)$ 必须为真。（传递性）

- 如果 $f(x,y)$ 为假，$f(y,x)$ 为假，$f(y,z)$ 为假且 $f(z,y)$ 为假，则 $f(x,z)$ 为假 且 $f(z,x)$ 为假。（不可比性的传递性）

其中反对称性可以由非自反性和传递性推导得到。而所有 STL 中的自定义比较器都可以用简单的 $<$ 关系表示。因为我们可以推断得知：

- $x>y$ 表示 $y<x$;
- $x \leq y$ 表示 $y \nless x$；
- $x \geq y$ 表示 $x \nless y$；
- $x=y$ 表示 $x \nless y$ 和 $y \nless x$。这就是为什么上面第四条规则被称为等价的传递性。如果 $x \nless y$ 和 $y \nless x$，我们可以说“$x$ 和 $y$ 是不可比的”。

## 参考资料与拓展阅读

- [1][Order theory - From Academic Kids](<https://academickids.com/encyclopedia/index.php/Order_theory>)
- [2][Binary Relation - Wikipedia](<https://en.wikipedia.org/wiki/Binary_relation>)
- [3][Order Theory - Wikipedia](<https://en.wikipedia.org/wiki/Order_theory>)
- [3][Order Theory, Lecture Notes by Mark Dean for Decision Theory](<http://www.columbia.edu/~md3405/DT_Order_15.pdf>)
- [4]卢开澄，卢华明，[《组合数学》（第 3 版）](http://www.tup.tsinghua.edu.cn/bookscenter/book_00458101.html), 2006
- [5][List of Order Theory Topics - Wikipedia](<https://en.wikipedia.org/wiki/List_of_order_theory_topics>)
- [6][浅谈邻项交换排序的应用以及需要注意的问题 by ouuan](<https://ouuan.github.io/post/%E6%B5%85%E8%B0%88%E9%82%BB%E9%A1%B9%E4%BA%A4%E6%8D%A2%E6%8E%92%E5%BA%8F%E7%9A%84%E5%BA%94%E7%94%A8%E4%BB%A5%E5%8F%8A%E9%9C%80%E8%A6%81%E6%B3%A8%E6%84%8F%E7%9A%84%E9%97%AE%E9%A2%98/>)
- [7][One thing you should know about comparators — Strict Weak Ordering](<https://codeforces.com/blog/entry/72525>)
