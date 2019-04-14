treap 是一种弱平衡的二叉搜索树。treap 这个单词是 tree 和 heap 的组合，表明 treap 是一种由树和堆组合形成的数据结构。treap 的每个结点上要额外储存一个值 $priority$ 。treap 除了要满足二叉搜索树的性质之外，还需满足父节点的 $priority$ 大于等于两个儿子的 $priority$ 。而 $priority$ 是每个结点建立时随机生成的，因此 treap 是期望平衡的。

treap 分为旋转式和无旋式两种。两种 treap 都易于编写，但无旋式 treap 的操作方式使得它天生支持维护序列、可持久化等特性。这里以重新实现 `set<int>` （不可重集合）为例，介绍无旋式 treap。

## 无旋式 treap 的核心操作

无旋式 treap 又称分裂合并 treap。它仅有两种核心操作，即为分裂与合并。下面逐一介绍这两种操作。

### 分裂（split）

分裂过程接受两个参数：根指针 $u$ 、关键值 $key$ 。结果为将根指针指向的 treap 分裂为两个 treap，第一个 treap 所有结点的关键值小于等于 $key$ ，第二个 treap 所有结点的关键值大于 $key$ 。该过程首先判断 $key$ 是否小于 $u$ 的关键值，若小于，则说明 $u$ 及其右子树全部属于第二个 treap，否则说明 $u$ 及其左子树全部属于第一个 treap。根据此判断决定应向左子树递归还是应向右子树递归，继续分裂子树。待子树分裂完成后按刚刚的判断情况连接 $u$ 的左子树或右子树到递归分裂所得的子树中。

```cpp
pair<node *, node *> split(node *u, int key) {
  if (u == nullptr) {
    return make_pair(nullptr, nullptr);
  }
  if (key < u->key) {
    pair<node *, node *> o = split(u->lch, key);
    u->lch = o.second;
    return make_pair(o.first, u);
  } else {
    pair<node *, node *> o = split(u->rch, key);
    u->rch = o.first;
    return make_pair(u, o.second);
  }
}
```

### 合并（merge）

合并过程接受两个参数：左 treap 的根指针 $u$ 、右 treap 的根指针 $v$ 。必须满足 $u$ 中所有结点的关键值小于等于 $v$ 中左右结点的关键值。因为两个 treap 已经有序，我们只需要考虑 $priority$ 来决定哪个 treap 应与另一个 treap 的儿子合并。若 $u$ 的根结点的 $priority$ 大于 $v$ 的，那么 $u$ 即为新根结点， $v$ 应与 $u$ 的右子树合并；反之，则 $v$ 作为新根结点，然后让 $u$ 与 $v$ 的左子树合并。不难发现，这样合并所得的树依然满足 $priority$ 的大根堆性质。

```cpp
node *merge(node *u, node *v) {
  if (u == nullptr) {
    return v;
  }
  if (v == nullptr) {
    return u;
  }
  if (u->priority > v->priority) {
    u->rch = merge(u->rch, v);
    return u;
  } else {
    v->lch = merge(u, v->lch);
    return v;
  }
}
```

### 建树（build）

将一个有 $n$ 个节点的序列 $a_i$ 转化为一棵 treap。

定义 `Merge(x,y)` 表示将根为 $x$ 和 $y$ 的两棵 Treap 合并成一棵，其根为该函数的返回值。需要保证 $x<y$ 。

定义 `Split(o,k,x,y)` 表示将根为 $o$ 的 Treap 分裂成 $x,y$ 两个部分，保证 $x < y$ ，即将该 Treap 分裂成权值小于等于 $k$ 的项和其他，分别为 $x$ 和 $y$ 。

可以依次暴力插入这 $n$ 个节点，每次插入一个权值为 $v$ 的节点时，将整棵 treap 按照权值分裂成权值小于等于 $v$ 的和权值大于 $v$ 的两部分，然后新建一个权值为 $v$ 的节点，将两部分和新节点按从小到大的顺序依次合并，时间复杂度 $O(n\log_2 n)$ ，单点插入时间复杂度 $O(\log_2 n)$ 。

```cpp
void build(int n, int a[]) {
  int x, y;
  for (int i = 1; i <= n; i++) {
    split(rt, a[i], x, y);
    rt = merge(merge(x, newnode(a[i])), y);
  }
}
```

在某些题目内，可能会有多次插入一段序列的操作，这是就需要在 $O(n)$ 的时间复杂度内完成建树操作。（假设这些节点已经有序）

方法一：直接将这 $n$ 个节点构造成一棵类线段树，即每次选取最中间的节点作为一段区间的树根，这样能保证树高为 $O(\log_2 n)$ 。然后对每个节点钦定优先值，保证其满足堆的性质。

方法二：直接将这 $n$ 个节点构造成一棵类线段树，即每次选取最中间的节点作为一段区间的树根，这样能保证树高为 $O(\log_2 n)$ 。然后给每个节点一个随机优先级，不保证其满足堆的性质。因为非旋式 treap 的优先级不是维护堆的性质，保证树高的，而是使 `merge` 操作更加随机一点，所以也是正确的。

方法三：观察到 treap 是一个笛卡尔树，利用笛卡尔树的 $O(n)$ 建树方法即可，用单调栈维护右脊柱即可。

## 将 treap 包装成为 `set<int>`

### count 函数

直接依靠二叉搜索树的性质查找即可。

```cpp
int find(node *u, int key) {
  if (u == nullptr) {
    return 0;
  }
  if (key == u->key) {
    return 1;
  }
  if (key < u->key) {
    return find(u->lch, key);
  } else {
    return find(u->rch, key);
  }
}

int count(int key) { return find(root, key); }
```

### insert 函数

先在待插入的关键值处将整棵 treap 分裂，判断关键值是否已插入过之后新建一个结点，包含待插入的关键值，然后进行两次合并操作即可。

```cpp
void insert(int key) {
  pair<node*, node*> o = split(root, key);
  if (find(root, key) == 0) {
    o.first = merge(o.first, new node(key));
  }
  root = merge(o.first, o.second);
}
```

### erase 函数

将具有待删除的关键值的结点从整棵 treap 中孤立出来（进行两侧分裂操作），删除中间的一段（具有待删除关键值），再将左右两端合并即可。

```cpp
void erase(int key) {
  pair<node*, node*> o = split(root, key - 1);
  pair<node*, node*> p = split(o.second, key);
  delete p.first;
  root = merge(o.first, p.second);
}
```

## 旋转 treap

旋转 treap 在做普通平衡树题的时候，是所有平衡树中常数较小的

维护平衡的方式为旋转。性质与普通二叉搜索树类似

因为普通的二叉搜索树会被递增或递减的数据卡，用 treap 对每个节点定义一个权值，由 rand 得到，从而防止特殊数据卡。

每次删除/插入时通过 rand 值决定要不要旋转即可，其他操作与二叉搜索树类似

以下是 bzoj 普通平衡树模板代码

```cpp
#include <algorithm>
#include <cstdio>
#include <iostream>

#define maxn 100005
#define INF (1 << 30)

int n;

struct treap {
  int l[maxn], r[maxn], val[maxn], rnd[maxn], size[maxn], w[maxn];
  int sz, ans, rt;
  inline void pushup(int x) { size[x] = size[l[x]] + size[r[x]] + w[x]; }
  void lrotate(int &k) {
    int t = r[k];
    r[k] = l[t];
    l[t] = k;
    size[t] = size[k];
    pushup(k);
    k = t;
  }
  void rrotate(int &k) {
    int t = l[k];
    l[k] = r[t];
    r[t] = k;
    size[t] = size[k];
    pushup(k);
    k = t;
  }
  void insert(int &k, int x) {
    if (!k) {
      sz++;
      k = sz;
      size[k] = 1;
      w[k] = 1;
      val[k] = x;
      rnd[k] = rand();
      return;
    }
    size[k]++;
    if (val[k] == x) {
      w[k]++;
    } else if (val[k] < x) {
      insert(r[k], x);
      if (rnd[r[k]] < rnd[k]) lrotate(k);
    } else {
      insert(l[k], x);
      if (rnd[l[k]] < rnd[k]) rrotate(k);
    }
  }

  void del(int &k, int x) {
    if (!k) return;
    if (val[k] == x) {
      if (w[k] > 1) {
        w[k]--;
        size[k]--;
        return;
      }
      if (l[k] == 0 || r[k] == 0)
        k = l[k] + r[k];
      else if (rnd[l[k]] < rnd[r[k]]) {
        rrotate(k);
        del(k, x);
      } else {
        lrotate(k);
        del(k, x);
      }
    } else if (val[k] < x) {
      size[k]--;
      del(r[k], x);
    } else {
      size[k]--;
      del(l[k], x);
    }
  }

  int queryrank(int k, int x) {
    if (!k) return 0;
    if (val[k] == x)
      return size[l[k]] + 1;
    else if (x > val[k]) {
      return size[l[k]] + w[k] + queryrank(r[k], x);
    } else
      return queryrank(l[k], x);
  }

  int querynum(int k, int x) {
    if (!k) return 0;
    if (x <= size[l[k]])
      return querynum(l[k], x);
    else if (x > size[l[k]] + w[k])
      return querynum(r[k], x - size[l[k]] - w[k]);
    else
      return val[k];
  }

  void querypre(int k, int x) {
    if (!k) return;
    if (val[k] < x)
      ans = k, querypre(r[k], x);
    else
      querypre(l[k], x);
  }

  void querysub(int k, int x) {
    if (!k) return;
    if (val[k] > x)
      ans = k, querysub(l[k], x);
    else
      querysub(r[k], x);
  }
} T;

int main() {
  srand(123);
  scanf("%d", &n);
  int opt, x;
  for (int i = 1; i <= n; i++) {
    scanf("%d%d", &opt, &x);
    if (opt == 1)
      T.insert(T.rt, x);
    else if (opt == 2)
      T.del(T.rt, x);
    else if (opt == 3) {
      printf("%d\n", T.queryrank(T.rt, x));
    } else if (opt == 4) {
      printf("%d\n", T.querynum(T.rt, x));
    } else if (opt == 5) {
      T.ans = 0;
      T.querypre(T.rt, x);
      printf("%d\n", T.val[T.ans]);
    } else if (opt == 6) {
      T.ans = 0;
      T.querysub(T.rt, x);
      printf("%d\n", T.val[T.ans]);
    }
  }
  return 0;
}
```

## 练习题

[luogu P3369【模板】普通平衡树](https://www.luogu.org/problemnew/show/P3369)

[luogu P3391【模板】文艺平衡树（Splay）](https://www.luogu.org/problemnew/show/P3391)

[luogu P2596\[ZJOI2006\]书架](https://www.luogu.org/problemnew/show/P2596)

[luogu P2042\[NOI2005\]维护数列](https://www.luogu.org/problemnew/show/P2042)

[CF 702F T-Shirts](http://codeforces.com/problemset/problem/702/F)
