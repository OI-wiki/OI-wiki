## 名称简介

老司机树，ODT(Old Driver Tree)，又名珂朵莉树（Chtholly Tree)。
起源自 [CF896C](https://codeforces.com/problemset/problem/896/C)。

## 前置知识

会用 STL 的 set 就行。

## 核心思想

把值相同的区间合并成一个结点保存在 set 里面。

## 用处

骗分。
只要是有区间赋值操作的数据结构题都可以用来骗分。
一般出题人不会 **刻意** 卡，但是不小心卡了就……

如果要保证复杂度正确，必须保证数据随机。
证明在[此](http://codeforces.com/blog/entry/56135?#comment-398940)。

## 正文

首先，结点的保存方式：

```cpp
struct Node_t {
  int l, r;
  mutable int v;
  Node_t(const int &il, const int &ir, const int &iv) : l(il), r(ir), v(iv) {}
  inline bool operator<(const Node_t &o) const { return l < o.l; }
};
```

其中， `int v` 是你自己指定的附加数据。

然后，我们定义一个 `set<Node_t> odt;` 来维护这些结点。
为简化代码，可以 `typedef set<Node_t>::iterator iter`，当然在题目支持 C++11时也可以使用 `auto`。

### split

最核心的操作之一 `split` ，它用于取得以 $x$ 开头的结点。
参考代码如下：

```cpp
auto split(int x) {
  if (x > n)
    return odt.end();
  auto it = --odt.upper_bound((Node_t){x, 0, 0});
  if (it->l == x) return it;
  int l = it->l, r = it->r, v = it->v;
  odt.erase(it);
  odt.insert(Node_t(l, x - 1, v));
  return odt.insert(Node_t(x, r, v)).first;
}
```

这个玩意有什么用呢？
任何对于 $[l,r]$ 的区间操作，都可以转换成 set 上 $[split(l),split(r + 1))$ 的操作。

### assign

另外一个重要的操作 `assign` 用于对一段区间进行赋值。
对于 ODT 来说，区间操作只有这个比较特殊，也是保证复杂度的关键。
如果 ODT 里全是长度为 $1$ 的区间，就成了暴力，但是有了 `assign` ，可以使 ODT 的大小下降。
参考代码如下：

```cpp
void assign(int l, int r, int v) {
  auto itr = split(r + 1), itl = split(l);
  odt.erase(itl, itr);
  odt.insert(Node_t(l, r, v));
}
```

### 其他操作

套模板就好了，参考代码如下：

```cpp
void performance(int l, int r) {
  auto itr = split(r + 1), itl = split(l);
  for (; itl != itr; ++itl) {
    // Perform Operations here
  }
}
```

## 习题

-   [「SCOI2010」序列操作](https://www.lydsy.com/JudgeOnline/problem.php?id=1858)
-   [「SHOI2015」脑洞治疗仪](https://www.lydsy.com/JudgeOnline/problem.php?id=4592)
-   [「Luogu 2787」理理思维](https://www.luogu.org/problemnew/show/P2787)
-   [「Luogu 4979」矿洞：坍塌](https://www.luogu.org/problemnew/show/P4979)
