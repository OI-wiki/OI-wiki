本文介绍和队列有关的数据结构及其应用。

## 队列

队列，英文名是 queue，在 C++ STL 中有 [std::queue](https://en.cppreference.com/w/cpp/container/queue) 和 [std::priority_queue](https://en.cppreference.com/w/cpp/container/priority_queue) 。

先进入队列的元素一定先出队列，因此队列通常也被称为先进先出（first in first out）表，简称 FIFO 表。

注： `std::stack` 和 `std::queue` 都是容器适配器，默认底层容器为 `std::deque` （双端队列）。

## 双端队列

双端队列是指一个可以在队首/队尾插入或删除元素的队列。相当于是栈与队列功能的结合。具体地，双端队列支持的操作有 4 个：

1.  在队首插入一个元素
2.  在队尾插入一个元素
3.  在队首删除一个元素
4.  在队尾删除一个元素

## 数组模拟队列

通常用一个数组模拟一个队列，用两个变量标记队列的首尾。

```cpp
int q[SIZE], ql = 1, qr;
```

插入元素： `q[++qr]=x;` 

删除元素： `++ql;` 

访问队首/队尾： `q[ql]` / `q[qr]` 

清空队列： `ql=1;qr=0;` 

数组模拟双端队列是同理的。

## 循环队列

这样会导致一个问题：随着时间的推移，整个队列会向数组的尾部移动，一旦到达数组的最末端，即使数组的前端还有空闲位置，再进行入队操作也会导致溢出。（这种数组上实际有空闲位置而发生了上溢的现象称为是“假溢出”。

解决假溢出的办法是采用循环的方式来组织存放队列元素的数组，即将数组下标为 0 的位置看做是最后一个位置的后继。（ `x` 的后继为 `(x + 1) % Size` ）。这样就形成了循环队列。

## 双栈模拟队列

其实不仅仅可以用数组模拟队列，还有一种冷门的方法是双栈模拟队列。

我们使用两个栈 F,S 模拟一个队列，其中 F 是队尾的栈，S 代表队首的栈，支持 push（在队尾插入），pop（在队首弹出）操作：

1.  Push：插入到栈 F 中
2.  Pop：如果 S 非空，让 S 弹栈；否则把 F 的元素倒过来圧到 S 中（其实就是一个一个弹出插入，做完后是首位颠倒的），然后再让 S 弹栈。

容易证明，每个元素只会进入/转移/弹出一次，均摊复杂度 $O(1)$ 。

有人问这个东西有什么用吗？参见下面这道题。这道题顺便可以给大家一个 **双栈模拟双端队列** 的方法。

### 例题

LOJ6515 贪玩蓝月

> 一个双端队列（deque），m 个事件：
>
> 1.  在前端插入 (w,v)
> 2.  在后端插入 (w,v)
> 3.  删除前端的二元组
> 4.  删除后端的二元组
> 5.  给定 l,r，在当前 deque 中选择一个子集 S 使得 $\sum_{(w,v)\in S}w\bmod p\in[l,r]$ ，且最大化 $\sum_{(w,v)\in S}v$ .
>
>      $m\leq 5\times 10^4,p\leq 500$ .

### 离线算法

每个二元组是有一段存活时间的，因此对时间建立线段树，每个二元组做 log 个存活标记。因此我们要做的就是对每个询问，求其到根节点的路径上的标记的一个最优子集。显然这个可以 DP 做。 $f[S,j]$ 表示选择集合 S 中的物品余数为 j 的最大价值。（其实实现的时侯是有序的，直接 f[i,j]做）

一共有 $O(m\log_2m)$ 个标记，因此这么做的话复杂度是 $O(mp\log_2m)$ 的。

### 在线算法

这是一个在线算法比离线算法快的神奇题目。而且还比离线的好写

上述离线算法其实是略微小题大做的，因为如果把题目的 deque 改成直接维护一个集合的话（即随机删除集合内元素），那么离线算法同样适用。既然是 deque，不妨在数据结构上做点文章。

### 栈

如果题目中维护的数据结构是一个栈呢？

直接 DP 即可。 $f[i,j]$ 表示前 i 个二元组，余数为 j 时的最大价值。

$$
f[i,j]=\max(f[i-1,j],f[i-1,(j-w_i)\bmod p]+v_i)
$$

妥妥的背包啊

删除的时侯直接指针前移即可。这样做的复杂度是 $O(mp)$ 的。

### 队列

如果题目中维护的数据结构是队列？

有一种操作叫双栈模拟队列。这就是这个东西的用武之地。因为用栈是可以轻松维护 DP 过程的，而双栈模拟队列的复杂度是均摊 $O(1)$ 的，因此，复杂度仍是 $O(mp)$ .

### 双端队列

回到原题，那么 Deque 怎么做？

类比推理，我们尝试用栈模拟双端队列，于是似乎把维护队列的方法扩展一下就可以了。但如果每次是全部转移栈中的元素的话，单次操作复杂度很容易退化为 $O(m)$ .

于是乎，神仙的想一想，我们可以丢一半过去啊

这样的复杂度其实均摊下来仍是常数级别。具体地说，丢一半指的是把一个栈靠近栈底的一半倒过来丢到另一个栈中。也就是说要手写栈以支持这样的操作。

### 丢一半的复杂度

似乎可以用 [势能分析法](https://yhx-12243.github.io/OI-transit/records/cf601E.html) 证明。其实本蒟蒻有一个很仙的想法。我们考虑这个双栈结构的整体复杂度。m 个事件，我们希望尽可能增加这个结构的复杂度。

首先，如果全是插入操作的话显然是严格 $\Theta(m)$ 的，因为插入的复杂度是 $O(1)$ 的。

“丢一半”操作是在什么时侯触发的？当某一个栈为空又要求删除元素的时侯。设另一个栈的元素个数是 $O(k)$ ，那么丢一半的复杂度就是 $O(k)\geq O(1)$ 的。因此我们要尽可能增加“丢一半”操作的次数。

为了增加丢一半的操作次数，必然需要不断删元素直到某一个栈为空。由于插入操作对增加复杂度是无意义的，因此我们不考虑插入操作。初始时有 m 个元素，假设全在一个栈中。则第一次丢一半的复杂度是 $O(m)$ 的。然后两个栈就各有 $\frac{m}{2}$ 个元素。这时就需要 $O(\frac{m}{2})$ 删除其中一个栈，然后就又可以触发一次复杂度为 $O(\frac{m}{2})$ 的丢一半操作……

考虑这样做的总复杂度。

$$
T(m)=2\cdot O(m)+T\left(\frac{m}{2}\right)
$$

解得 $T(m)=O(m)$ .

于是，总复杂度仍是 $O(mp)$ .

### 询问操作

在询问的时侯，我们要处理的应该是“在两个栈中选若干个元素的最大价值”的问题。因此要对栈顶的 DP 值做查询，即两个 $f,g$ 对于询问[l,r]的最大价值：

$$
\max_{0\leq i<p}\left\{f[i]+\max_{l\leq i+j\leq r}g_j\right\}
$$

这个问题暴力做是 $O(p^2)$ 的，不过一个妥妥的单调队列可以做到 $O(p)$ .

```cpp
#include <algorithm>
#include <cctype>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <vector>
using namespace std;
typedef long long lld;
typedef long double lf;
typedef unsigned long long uld;
typedef pair<int, int> pii;
#define fi first
#define se second
#define pb push_back
#define mk make_pair
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define ROF(i, a, b) for (int i = (a); i >= (b); --i)
/******************heading******************/
const int M = 5e4 + 5, P = 505;
int I, m, p;

inline int _(int d) { return (d + p) % p; }
namespace DQ {       // 双栈模拟双端队列
pii fr[M], bc[M];    // front,back; fi:w,se:v;
int tf = 0, tb = 0;  // top
int ff[M][P], fb[M][P];
void update(pii *s, int f[][P], int i) {  // update f[i] from f[i-1]
  FOR(j, 0, p - 1) {
    f[i][j] = f[i - 1][j];
    if (~f[i - 1][_(j - s[i].fi)])
      f[i][j] = max(f[i][j], f[i - 1][_(j - s[i].fi)] + s[i].se);
  }
}
void push_front(pii x) { fr[++tf] = x, update(fr, ff, tf); }
void push_back(pii x) { bc[++tb] = x, update(bc, fb, tb); }
void pop_front() {
  if (tf) {
    --tf;
    return;
  }
  int mid = (tb + 1) / 2, top = tb;
  ROF(i, mid, 1) push_front(bc[i]);
  tb = 0;
  FOR(i, mid + 1, top) push_back(bc[i]);
  --tf;
}
void pop_back() {
  if (tb) {
    --tb;
    return;
  }
  int mid = (tf + 1) / 2, top = tf;
  ROF(i, mid, 1) push_back(fr[i]);
  tf = 0;
  FOR(i, mid + 1, top) push_front(fr[i]);
  --tb;
}
int q[M], ql, qr;
int query(int l, int r) {
  const int *const f = ff[tf], *const g = fb[tb];
  int ans = -1;
  ql = 1, qr = 0;
  FOR(i, l - p + 1, r - p + 1) {
    int x = g[_(i)];
    while (ql <= qr && g[q[qr]] <= x) --qr;
    q[++qr] = _(i);
  }
  ROF(i, p - 1, 0) {
    if (ql <= qr && ~f[i] && ~g[q[ql]]) ans = max(ans, f[i] + g[q[ql]]);
    // 删 l-i，加 r-i+1
    if (ql <= qr && _(l - i) == q[ql]) ++ql;
    int x = g[_(r - i + 1)];
    while (ql <= qr && g[q[qr]] <= x) --qr;
    q[++qr] = _(r - i + 1);
  }
  return ans;
}
void init() { FOR(i, 1, P - 1) ff[0][i] = fb[0][i] = -1; }
}  // namespace DQ
int main() {
  DQ::init();
  scanf("%d%d%d", &I, &m, &p);
  FOR(i, 1, m) {
    char op[5];
    int x, y;
    scanf("%s%d%d", op, &x, &y);
    if (op[0] == 'I' && op[1] == 'F')
      DQ::push_front(mk(_(x), y));
    else if (op[0] == 'I' && op[1] == 'G')
      DQ::push_back(mk(_(x), y));
    else if (op[0] == 'D' && op[1] == 'F')
      DQ::pop_front();
    else if (op[0] == 'D' && op[1] == 'G')
      DQ::pop_back();
    else
      printf("%d\n", DQ::query(x, y));
  }
  return 0;
}
```
