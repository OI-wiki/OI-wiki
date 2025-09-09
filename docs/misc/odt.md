## 简介

珂朵莉树（Chtholly Tree），又名老司机树 ODT（Old Driver Tree）。起源自 [CF896C](https://codeforces.com/problemset/problem/896/C)。

这个名称指代的是一种「使用平衡树（`std::set`、`std::map` 等）或链表（`std::list`、手写链表等）维护颜色段均摊」的技巧，而不是一种特定的数据结构。其核心思想是将值相同的一段区间合并成一个结点处理。相较于传统的线段树等数据结构，对于含有区间覆盖的操作的问题，珂朵莉树可以更加方便地维护每个被覆盖区间的值。

## 实现（std::set）

### 结点类型

```cpp
struct Node_t {
  int l, r;
  mutable int v;

  Node_t(const int &il, const int &ir, const int &iv) : l(il), r(ir), v(iv) {}

  bool operator<(const Node_t &o) const { return l < o.l; }
};
```

其中，`int v` 是你自己指定的附加数据。

???+ note "`mutable` 关键字的含义是什么？"
    `mutable` 的意思是「可变的」，让我们可以在后面的操作中修改 `v` 的值。在 C++ 中，mutable 是为了突破 const 的限制而设置的。被 mutable 修饰的变量（mutable 只能用于修饰类中的非静态数据成员），将永远处于可变的状态，即使在一个 const 函数中。
    
    这意味着，我们可以直接修改已经插入 `set` 的元素的 `v` 值，而不用将该元素取出后重新加入 `set`。

### 结点存储

我们希望维护所有结点，使得这些结点所代表的区间左端点单调增加且两两不交，最好可以保证所有区间的并是一个极大的连续范围。此处以 `std::set` 为例，用一个 `set<Node_t> odt;` 维护所有结点。

初始化时，向珂朵莉树中插入一个极长区间（如题目要求维护位置 $1$ 到 $n$ 的信息，插入区间 $[1,n+1]$）。

### split 操作

`split` 操作是珂朵莉树的核心。它接受一个位置 $x$，将原本包含点 $x$ 的区间（设为 $[l, r]$）分裂为两个区间 $[l, x)$ 和 $[x, r]$，并返回指向后者的迭代器。

参考代码如下：

```cpp
auto split(int x) {
  auto it = odt.lower_bound(Node_t(x, 0, 0));
  if (it != odt.end() && it->l == x) return it;
  --it;
  int l = it->l, r = it->r, v = it->v;
  odt.erase(it);
  odt.insert(Node_t(l, x - 1, v));
  return odt.insert(Node_t(x, r, v)).first;
}
```

在不支持使用 `auto` 进行返回类型推导的编译器上，可以将函数的返回类型改为 `set<Node_t>::iterator`。

### assign 操作

另外一个重要的操作：`assign`。用于对一段区间进行赋值。设将要对区间 $[l,r]$ 赋值为 $v$。

首先，将区间 $[l, r]$ 截取出来。依次调用 `split(r + 1), split(l)`，将此两者返回的迭代器记作 $itr, itl$，那么 $[itl, itr)$ 这个迭代器范围就指向了珂朵莉树中 $[l,r]$ 包含的所有区间。

然后，将原有的信息删除。`std::set` 有成员方法 `erase`，签名如同 `iterator erase( const_iterator first, const_iterator last );`，可以移除范围 `[first; last)` 中的元素。于是我们调用 `odt.erase(itl, itr);` 以删除原有的信息。

最后，插入区间 $[l,r]$ 的新值。调用 `odt.insert(Node_t(l, r, v))` 即可。

参考代码如下：

```cpp
void assign(int l, int r, int v) {
  auto itr = split(r + 1), itl = split(l);
  odt.erase(itl, itr);
  odt.insert(Node_t(l, r, v));
}
```

???+ note " 为什么需要先 `split(r + 1)` 再 `split(l)`？"
    1.  `std::set::erase` 方法将使指向被擦除元素的引用和迭代器失效。而其他引用和迭代器不受影响。
    2.  `std::set::insert` 方法不会使任何迭代器或引用失效。
    3.  `split` 操作会将区间拆开。调用 `split(r + 1)` 之后 $r + 1$ 会成为两个新区间中右边区间的左端点，此时 `split` 左区间，必然不会访问到 $r + 1$ 为左端点的那个区间，也就不会将其拆开，删去 $r + 1$ 为左端点的区间，使迭代器失效。反之，先 `split(l)`，再 `split(r + 1)`，可能会把 $l$ 为左端点的区间删去，使迭代器失效。

### perform 操作

将珂朵莉树上的一段区间提取出来并进行操作。与 `assign` 操作类似，只不过是将删除区间改为遍历区间。

参考代码如下：

```cpp
void perform(int l, int r) {
  auto itr = split(r + 1), itl = split(l);
  for (; itl != itr; ++itl) {
    // Perform Operations here
  }
}
```

注意不应该滥用这样的提取操作，可能使得时间复杂度错误。见下文「复杂度分析」一栏。

## 实现（std::map）

相较于 `std::set` 的实现，`std::map` 的实现的 `split` 操作写法更简单。除此之外，其余操作与 `std::set` 并无二异。

### 结点存储

由于珂朵莉树存储的区间是连续的，我们不一定要记下右端点是什么。不妨使用一个 `map<int, int> mp;` 存储所有区间，其键维护左端点，其值维护其对应的左端点到下一个左端点之前的值。

初始化时，如题目要求维护位置 $1$ 到 $n$ 的信息，则调用 `mp[1] = -1, mp[n + 1] = -1` 表示将 $[1,n+1)$ 即 $[1, n]$ 都设为特殊值 $-1$，$[n+1, +\infty)$ 这个区间当作哨兵使用，也可以对它进行初始化。

### split 操作

参考代码：（第一份）

```cpp
void split(int x) {
  auto it = prev(mp.upper_bound(x));  // 找到左端点小于等于 x 的区间。
  mp[x] = it->second;  // 设立新的区间，并将上一个区间储存的值复制给本区间。
}
```

参考代码：（第二份）

```cpp
auto split(int pos) {
  auto it = prev(mp.upper_bound(pos));  // 找到左端点小于等于 x 的区间。
  return mp.insert(it, make_pair(pos, it->second));
  // 设立新的区间，并将上一个区间储存的值复制给本区间。
}
```

这里使用了 `std::map::insert` 的重载 `iterator insert( const_iterator pos, const value_type& value );`，其插入 `value` 到尽可能接近正好在 `pos` 之前的位置。如果插入恰好发生在正好在 `pos` 之前的位置，那么复杂度是均摊常数，否则复杂度与容器大小成对数。

### assign 操作

对于 assign 操作，我们需要把 $[l,r−1]$ 内所有区间左端点删除，再建立新的区间。

```cpp
void assign(int l, int r, int v) {  // 注意，这里的r是区间右端点+1
  split(l);
  split(r);
  auto it = mp.find(l);
  while (it->first != r) {
    it = mp.erase(it);
  }
  mp[l] = v;
}
```

### perform 操作

```cpp
void perform(int l, int r) {  // 注意，这里的r是区间右端点+1
  split(l);
  split(r);
  auto it = mp.find(l);
  while (it->first != r) {
    // Perform Operations here
    it = next(it);
  }
}
```

## 实现（链表）

目前主流的实现是基于 `set` 来维护节点，但由于平均维护的区间个数很小，`set` 的优势并不明显。相比之下，链表（或数组）能更简洁地维护分裂与合并操作。

### 结点存储

```cpp
using i64 = int64_t;

struct Block {
  Block *next;  // 链表下一节点
  int l, r;     // 区间范围
  i64 val;      // 区间上的值

  Block(Block *next, int l, int r, i64 val)
      : next(next), l(l), r(r), val(val) {}

  bool operator<(const Block &b) const { return val < b.val; }
} *root;
```

### split 操作

```cpp
// 返回左端点为 mid+1 的区间
Block *split(int mid) {
  for (Block *b = root; b; b = b->next) {  // 遍历链表
    if (b->l == mid + 1) {                 // 左端点为 mid+1
      return b;
    }
    // 寻找能包含 mid 和 mid+1 的区间 [l, r]，将其被拆分成 [l, mid] 和 [mid+1,
    // r]
    if (b->l <= mid && mid + 1 <= b->r) {
      b->next = new Block(b->next, mid + 1, b->r, b->val);
      b->r = mid;
      return b->next;
    }
  }
  return nullptr;  // 未找到，返回空
}
```

在操作区间时，由于不能只维护区间的一部分，所以下面的操作进行之前都需要预先分裂区间，再完成相应操作。

```cpp
Block *lb, *rb;

// 预分裂，保证后续操作在 [l, r] 内部
void prepare(int l, int r) {
  lb = split(l - 1);
  rb = split(r);
}
```

### assign 操作

```cpp
void assign(int l, int r, i64 val) {
  prepare(l, r);
  lb->r = r;  // 将区间 [lb.l, lb.r] 修改成 [lb.l, r]
  lb->val = val;
  lb->next = rb;  // 将 [lb.l, r] 链至其右侧相邻区间
}

// 注：这里没有释放被删除节点的内存，若有需要可自行添加
```

### perform 操作

```cpp
void perform(int l, int r) {
  prepare(l, r);
  for (Block *b = lb; b != rb; b = b->next) {
    // Perform Operations here
  }
}
```

## 复杂度分析

### perform 以后立即对同一区间调用 assign

此时观察发现，两次 `split` 操作至多增加两个区间；一次 `assign` 将删除范围内的所有区间并增加一个区间，同时遍历所删除的区间。所以，我们所遍历的区间与所删除的区间数量成线性，而每次操作都只会增加 $O(1)$ 个区间，所以我们操作的区间数量关于操作次数（包括初始化）成线性，时间复杂度为均摊 $O(m\log n)$，其中 $m$ 为操作次数，$n$ 为珂朵莉树中最大区间个数（可以认为 $n\leq m$）。

### perform 以后不进行 assign

如果允许特殊构造数据，这样一定是能被卡掉的，只需要使珂朵莉树中有足够多的不同区间并反复遍历，就能使珂朵莉树的复杂度达到甚至高于平方级别。

如果要保证复杂度正确，必须保证数据随机。详见 [Codeforces 上关于珂朵莉树的复杂度的证明](http://codeforces.com/blog/entry/56135?#comment-398940)。更详细的严格证明见 [珂朵莉树的复杂度分析](https://zhuanlan.zhihu.com/p/102786071)。证明的结论是：用 `std::set` 实现的珂朵莉树的复杂度为 $O(n \log \log n)$，而用链表实现的复杂度为 $O(n \log n)$。

## 习题

-   [「Luogu 1840」Color the Axis](https://www.luogu.com.cn/problem/P1840)
-   ~~[「SCOI2010」序列操作](https://www.luogu.com.cn/problem/P2572)~~（该题目来源已添加 Hack 数据）
-   [「SHOI2015」脑洞治疗仪](https://loj.ac/problem/2037)
-   [「Luogu 4979」矿洞：坍塌](https://www.luogu.com.cn/problem/P4979)
-   [「Luogu 8146」risrqnis](https://www.luogu.com.cn/problem/P8146)

## 扩展阅读

[ODT 的映射思想的推广 - 洛谷专栏 (luogu.com.cn)](https://www.luogu.com.cn/article/0mys9qkh)

## 参考资料和注释

-   [Problem - 896C - Codeforces](https://codeforces.com/problemset/problem/896/C)（珂朵莉树的起源）
-   [CF896C Willem, Chtholly and Seniorious 题解 - 洛谷专栏 (luogu.com.cn)](https://www.luogu.com.cn/article/gyxbe23s)（`std::set` 实现参考）
-   [珂朵莉树的 map 实现 - 知乎 (zhihu.com)](https://zhuanlan.zhihu.com/p/469794466)（`std::map` 实现参考）
-   [题解 CF896C【Willem, Chtholly and Seniorious】- 洛谷专栏 (luogu.com.cn)](https://www.luogu.com.cn/article/umiw1fwp)（链表实现参考）
-   [Codeforces Round #449 Editorial - Codeforces](https://codeforces.com/blog/entry/56135?#comment-398940)（关于珂朵莉树的复杂度的证明）
-   [珂朵莉树的复杂度分析 - 知乎 (zhihu.com)](https://zhuanlan.zhihu.com/p/102786071)（珂朵莉树的复杂度分析）
