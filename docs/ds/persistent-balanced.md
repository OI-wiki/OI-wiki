Split-Merge Treap

* * *

### [前言]

据说某界有一种神奇的数据结构…… 据说它可以做很多事情。

小 VHOS 太菜了，就简单地学习了一下，写下这篇简介，仅供大家参考。

同时还借鉴了一些大佬的博客，增加了模拟该结构工作过程的完整性。

### [对于无旋 Treap 的提示：看楼上的 Treap]

1. 最小的 k 个值的分裂写法

对于一棵以 u 为根的 Treap, 将其权值前 k 小与剩下部分切开成两棵 Treap 并且将其根节点返回， 令 siz(u) 为根节点节点的左子节点的大小分三种情况讨论：

1. `siz(u)==k`，则直接断开左儿子, 返回左儿子和当前节点即可;

2. `siz(u)>k`，断开左儿子, 递归左子树, 得到的结果假设为 `<first,second>`，合并 u 和 second 作为第二关键字返回即可。

3. `siz(u)<k`，断开右儿子, 递归右子树, 得到的结果假设为 `<first,second>`，合并 u 与 first 作为第一关键字返回即可。

### [Treap]

大家都知道 BST 中有个依靠随机数吃饭的 Treap，它依靠同时 rotate(zig/zag) 来维护随机键值的堆性质和插入键值的 BST 性质来在统计意义上保持 BST 的 “平衡”；

大家都知道 rotate 可以维持 Treap 的平衡，那么有没有可以保持 Treap 堆性质的第二种方法呢？

### [时间复杂度]

所有操作，包括插入，删除，查询第 K 大等均为对数级 $O(\log N)$；

但是代价是时间常数略大，需要写得好看才好用。

### [定义]

- `u` 即一棵可爱的 Treap 的一个非空节点；

- `key(u)` 即插入键值，输入数据所赋予的；

- `fix(u)` 即随机键值，用于保持平衡；

- `siz(u)` 即 `u` 节点的左子树大小；

- `pair<first,second>` 分裂的返回值，即分裂出的两个子树根的位置

### [Split]

本树最精妙的操作之一就是 分裂 ->Split&lt;-。

**无旋 Treap 利用有序构树维护堆的性质…**

什么意思，就是把一棵 Treap 拆成两棵 Treap 

现在先讲正经的理论知识 -> 什么是 Split &lt;-：

split(x,k) -> 将 u 所在子树的 最小的 k 个值 / 小于等于 k 的值 与另外的部分分离出来，即拆成两棵树，复杂度 $O(\log N)$：

小于等于 k 值的分裂写法（两个写法大致相似，请按情况选择）：
对于一棵以 u 为根的 Treap，将其权值前 k 小与剩下部分切开成两棵 Treap 并且将其根节点分别返回。令 key 为根节点节点的 key 值分三种情况讨论：
1\. key(z)==k，则直接断开右儿子，返回当前节点和右儿子即可；
2\. key(z)>k，断开左儿子，递归左子树，得到的结果假设为 &lt;first,second>，合并 u 和 second 作为第二关键字返回即可；
3\. key(z)&lt;k，断开右儿子，递归右子树，得到的结果假设为 &lt;first,second>，合并 u 与 first 作为第一关键字返回即可。

2. 最小的 k 个值的分裂写法：

对于一棵以 u 为根的 Treap，将其权值前 k 小与剩下部分切开成两棵 Treap 并且将其根节点返回。令 siz(u) 为根节点节点的左子节点的大小分三种情况讨论：

1. siz(u)==k，则直接断开左儿子，返回左儿子和当前节点即可；
2. siz(u)>k，断开左儿子，递归左子树，得到的结果假设为 &lt;first,second>，合并 u 和 second 作为第二关键字返回即可；
3. siz(u)&lt;k，断开右儿子，递归右子树，得到的结果假设为 &lt;first,second>，合并 u 与 first 作为第一关键字返回即可。

### [C++ Code]

```cpp
std::pair<int,int> split(int x,int k) {
  if(x==0)
    return std::make_pair(0,0);
  std::pair<int,int> y;
  if(tree[x].key<=k) {
    y=split(tree[x].ch[1],k);
    tree[x].ch[1]=y.first;
    update(x);
    y.first=x;
  } else {
    y=split(tree[x].ch[0],k);
    tree[x].ch[0]=y.second;
    update(x);
    y.second=x;
  }
  return y;
}
```

### [定义]

`x, y` 可爱的 Treap 的子树；

`key(x)` 即插入键值，输入数据所赋予的；

`fix(x)` 即随机键值，用于保持平衡；

`siz(x)` 即 `x` 节点的左子树大小；

### [Merge]

在你进行了加入 / 删除操作之后，你发现你手上现在有两到三棵树了，自然我们需要将这些树合并。合并的具体操作也是递归处理，此时就可以维护无旋 Treap 的堆性质。

对于两个相对有序的 Treap，那么 Merge 的复杂度是 $O(\log N)$ 的，否则采用启发式合并，合并两个大小为 $N,M(N\le M)$ 的 Treap 的复杂度是 $O(N\log M/N)$ 的，这里不介绍。

先说一说什么叫序，有两种序，一种是以值为序，即中序遍历的值递增。一种是以序列为序，即元素的相对位置，即中序遍历的值为序列（考虑字符串序列）。

这两个的差别，仅仅在插入上面。Treap 可以且仅能维护一种序列。

对于以值为序，那么相对有序就是一个 Treap 的最大元素小于另一个 Treap 的最小元素。

对于以序列为序，执行 Merge 操作就是把两个序列首尾相接，自然也就默认左边的 Treap 全部小于后面的 Treap。

Treap 的合并类似左偏树和斜堆，Merge(x,y) 是一个递归操作：

因为已知 x 的子树最大值小于等于 y 子树的最小值，很容易想到必定是 y 链接在 x 的右儿子节点，或者 x 链接在 y 的左儿子节点；

为了使深度尽量小，我们使用随机键值 fix，来判断 x 为 y 的儿子，或者 y 为 x 的儿子;

若 $fix(x)\le fix(y)$，则 x 的右子树为 y，递归合并 x 原本的右子树和 y；

若 $fix(x)\ge fix(y)$，则 y 的左子树为 x，递归合并 y 原本的左子树和 x；

### [额外操作]

### [get_rank]

找值为 v 的节点排名，就把整棵树以 v-1 为权值 split，那么小于 v 的节点全在左树内，输出左树的 size 即可。

### [precursor]

找前驱就把整棵树按 v-1 为权值 split 开，此时小于等于 v 的数全在左树里，在左树里找到排名为（左树的 size）的节点权值即可。

### [successor]

找后继是相同的，把整棵树按 v 为权值 split 开，此时右树排名第一的数就是后继。

### [reverse]

l 到 r 区间操作

先把 root 的以 r 个（注意这里是以 size 分了）split 出来，现在左树中是 1~r 的树，再在左树中以 l-1 个 split 开。

那么这时候 l 到 r 的数就在第二次 split 后的右树中，直接对一棵树操作即可，打上旋转标记，注意及时下传标记即可。

这个区间操作和 splay 的把区间旋转到一个子树有异曲同工之妙。

如果设置了哨兵节点，务必注意小心行事。

### [那么…][正文]

读者大大很容易注意到一个问题：以上操作似乎都可以由 splay 支持，而且非旋 Treap 在常数上也没有优势。

那为什么要写这个毒瘤玩意\~~

### [可持久化]

因为这棵树的最大优点是极为容易实现可持久化。

（Splay 实现不了蛤蛤蛤）

### [思想]

可持久化 treap 就是在无旋 treap 上加入历史版本，方法类似于主席树， 只要考虑清楚了应该没有什么困难的地方（emmm… 是大佬逼我说的我没有办法！！）。

可持久化是对数据结构的一种操作，即保留历史信息，使得在后面可以调用之前的历史版本。

### [做法]

我们来看看旋转的 Treap，现在应该知道为什么不能可持久化了吧？

如果带旋转，那么就会破环原有的父子关系，破环原有的路径和树形态，这是可持久化无法接受的。

如果把 Treap 变为非旋转的，那么我们可以发现只要可以可持久化 Merge 和 Split 就可以完成可持久化.

因为上文说到了「一切可支持操作都可以通过以上四个基本操作完成」，而 Build 操作只用于建造无需理会，Newnode 就是用来可持久化的工具。

我们来观察一下 Merge 和 Split，我们会发现它们都是由上而下的操作！

因此我们完全可以参考线段树的可持久化对它进行可持久化。

每次需要修改一个节点，就 Newnode 出来继续做就可以了。

### [可持久化]

```c++
static std::pair<int,int> _split(int _x,int k) {
  if(_x==0)
    return std::make_pair(0,0);
  else {
    int _vs=++_cnt; //新建节点（可持久化的精髓）
    _trp[_vs]=_trp[_x];
    std::pair<int,int> _y;
    if(_trp[_vs].key<=k) {
      _y=_split(_trp[_vs].leaf[1],k);
      _trp[_vs].leaf[1]=_y.first;
      _y.first=_vs;
    } else {
      _y=_split(_trp[_vs].leaf[0],k);
      _trp[_vs].leaf[0]=_y.second;
      _y.second=_vs;
    }
    _trp[_vs]._update();
    return _y;
  }
}
```

### [Luogu P3835 可持久化平衡树]

题目背景

本题为题目 普通平衡树 的可持久化加强版。

数据已经经过强化

题目描述

您需要写一种数据结构（可参考题目标题），来维护一些数，其中需要提供以下操作（对于各个以往的历史版本）：

1. 插入 x 数

2. 删除 x 数（若有多个相同的数，因只删除一个，如果没有请忽略该操作）

3. 查询 x 数的排名（排名定义为比当前数小的数的个数 + 1。若有多个相同的数，因输出最小的排名）

4. 查询排名为 x 的数

5. 求 x 的前驱（前驱定义为小于 x，且最大的数，如不存在输出 -2147483647）

6. 求 x 的后继（后继定义为大于 x，且最小的数，如不存在输出 2147483647）

和原本平衡树不同的一点是，每一次的任何操作都是基于某一个历史版本，同时生成一个新的版本（操作 3, 4, 5, 6 即保持原版本无变化）。

每个版本的编号即为操作的序号（版本 0 即为初始状态，空树）

输入格式：

第一行为 n，表示操作的个数, 下面 n 行每行有两个数 opt 和 x，opt 表示操作的序号 $(1\le opt\le6)$。

输出格式：

对于操作 3,4,5,6 每行输出一个数，表示对应答案。

### [分析]

就是这样~

给大家练一练手\~~

### [C++ Code]

```c++
#include<cstdio>
#include<cctype>

#ifdef __GNUG__
#pragma GCC diagnostic error "-std=c++14"
#endif

#ifdef __GNUG__
#pragma GCC optimize("O3")
#endif

template<typename int_type>inline int_type next_int(int_type &ret) {
  int neg=false;
  int bit=getchar();
  while(!isdigit(bit)) {
    if(bit=='-')
      neg^=true;
    bit=getchar();
  }
  ret=0;
  while(isdigit(bit)) {
    ret=(ret<<3)+(ret<<1)+(bit^'0');
    bit=getchar();
  }
  return ret=neg?~ret+1:ret;
}

template<typename int_type>inline void writeln(int_type res) {
  if(res<0) {
    putchar('-');
    res=~res+1;
  }
  int_type bit=10;
  int len=1;
  while(bit<=res) {
    bit=(bit<<3)+(bit<<1);
    len++;
  }
  while(len--) {
    bit/=10;
    putchar(res/bit+'0');
    res%=bit;
  }
  putchar('\n');
  return;
}

#ifdef  __linux
typedef long long __int64;
#endif

#include<algorithm>
inline int rand_int(int x,int y) {
  return (rand()|((__int64)rand()<<15))%(y-x+1)+x;
}

static const int max_node=5e5+5;
static const int inf=0x7fffffff;

class _node_t { //Spilt Treap...
  public:
    int leaf[2];
    int key;
    int siz;
    int fix;
  public:
    void _update(void);
    _node_t(void);
    _node_t(int _key);
    ~_node_t(void);
};
_node_t _trp[max_node<<5]= {};
int _cnt=0,root[max_node]= {};

inline void _node_t::_update(void) {
  this->siz=_trp[this->leaf[0]].siz+_trp[this->leaf[1]].siz+1;
  return;
}

inline _node_t::_node_t(void) {
  this->key=this->leaf[0]=this->leaf[1]=0;
  return;
}

inline _node_t::_node_t(int _key) {
  this->key=_key;
  this->siz=1;
  this->fix=rand_int(1,max_node);
  this->leaf[0]=this->leaf[1]=0;
  return;
}

inline _node_t::~_node_t(void) {
  return;
}

static int _merge(int _x,int _y) {
  if(_x==0||_y==0)
    return _x^_y;
  else {
    if(_trp[_x].fix<_trp[_y].fix) {
      _trp[_x].leaf[1]=_merge(_trp[_x].leaf[1],_y);
      _trp[_x]._update();
      return _x;
    } else {
      _trp[_y].leaf[0]=_merge(_x,_trp[_y].leaf[0]);
      _trp[_y]._update();
      return _y;
    }
  }
}

static std::pair<int,int> _split(int _x,int k) {
  if(_x==0)
    return std::make_pair(0,0);
  else {
    int _vs=++_cnt;
    _trp[_vs]=_trp[_x];
    std::pair<int,int> _y;
    if(_trp[_vs].key<=k) {
      _y=_split(_trp[_vs].leaf[1],k);
      _trp[_vs].leaf[1]=_y.first;
      _y.first=_vs;
    } else {
      _y=_split(_trp[_vs].leaf[0],k);
      _trp[_vs].leaf[0]=_y.second;
      _y.second=_vs;
    }
    _trp[_vs]._update();
    return _y;
  }
}

inline int find_kth(int ves,int val) {
  std::pair<int,int> _ptr=_split(root[ves],val-1);
  int res=_trp[_ptr.first].siz+1;
  root[ves]=_merge(_ptr.first,_ptr.second);
  return res;
}

inline int get_kth(int x,int k) {
  if(x==0)
    return 0;
  else {
    int l_leaf=_trp[x].leaf[0];
    if(_trp[l_leaf].siz>=k)
      return get_kth(l_leaf,k);
    else if(_trp[l_leaf].siz+1==k)
      return _trp[x].key;
    else
      return get_kth(_trp[x].leaf[1],k-_trp[l_leaf].siz-1);
  }
}

inline int get_prev(int ves,int val) {
  int k=find_kth(ves,val);
  return get_kth(root[ves],k-1);
}

inline int get_next(int ves,int val) {
  std::pair<int,int> _ptr=_split(root[ves],val);
  int res=get_kth(_ptr.second,1);
  root[ves]=_merge(_ptr.first,_ptr.second);
  return res;
}

inline void _insert(int val,int ves) {
  std::pair<int,int> _ptr=_split(root[ves],val);
  _trp[++_cnt]=_node_t(val);
  root[ves]=_merge(_merge(_ptr.first,_cnt),_ptr.second);
  return;
}

inline void _delete(int val,int ves) {
  std::pair<int,int> _x=_split(root[ves],val);
  std::pair<int,int> _y=_split(_x.first,val-1);
  if(_trp[_y.second].key==val)
    _y.second=_merge(_trp[_y.second].leaf[0],_trp[_y.second].leaf[1]);
  root[ves]=_merge(_merge(_y.first,_y.second),_x.second);
  return;
}

inline void update_version(int las,int clo) {
  if(_trp[root[las]].siz^0) {
    root[clo]=++_cnt;
    _trp[root[clo]]=_trp[root[las]];
  }
  return;
}

#include<ctime>
inline void build_treap(void) {
  srand((unsigned)time(NULL));
  _insert(inf,0);
  _insert(-inf,0);
  return;
}

void work(void) {
  build_treap();
  int times=next_int(times);
  for(int i=1; i<=times; i++) {
    int las=next_int(las);
    int tag=next_int(tag);
    int x=next_int(x);
    update_version(las,i);
    switch(tag) {
      case 1:
        _insert(x,i);
        break;
      case 2:
        _delete(x,i);
        break;
      case 3:
        writeln(find_kth(i,x)-1);
        break;
      case 4:
        writeln(get_kth(root[i],x+1));
        break;
      case 5:
        writeln((__int64)get_prev(i,x));
        break;
      case 6:
        writeln((__int64)get_next(i,x));
        break;
      default:
        writeln(-1);
        break;
    }
  }
  return;
}

int main(int argc,char *argv[],char *env[]) {
  work();
  return 0;
}
```

### [另外]

可持久化平衡树可以用来维护动态凸包，仙人掌等东西，但他们太过于毒瘤，如果读者有兴趣可以阅读相应的计算几何知识，再来食用。
