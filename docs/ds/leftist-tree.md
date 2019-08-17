## 什么是左偏树？

 **左偏树** 与 [ **配对堆** ](/ds/pairing-heap) 一样，是一种 **可并堆** ，具有堆的性质，并且可以快速合并。

## dist 的定义和性质

对于一棵二叉树，我们定义 **外节点** 为左儿子或右儿子为空的节点，定义一个外节点的 $\mathrm{dist}$ 为 $1$ ，一个不是外节点的节点 $\mathrm{dist}$ 为其到子树中最近的外节点的距离加一。空节点的 $\mathrm{dist}$ 为 $0$ 。

> 注：很多其它教程中定义的 $\mathrm{dist}$ 都是本文中的 $\mathrm{dist}$ 减去 $1$ ，本文这样定义是因为代码写起来方便。

一棵有 $n$ 个节点的二叉树，根的 $\mathrm{dist}$ 不超过 $\left\lceil\log (n+1)\right\rceil$ ，因为一棵根的 $\mathrm{dist}$ 为 $x$ 的二叉树至少有 $x-1$ 层是满二叉树，那么就至少有 $2^x-1$ 个节点。注意这个性质是所有二叉树都具有的，并不是左偏树所特有的。

## 左偏树的定义和性质

左偏树是一棵二叉树，它不仅具有堆的性质，并且是「左偏」的：每个节点左儿子的 $\mathrm{dist}$ 都大于等于右儿子的 $\mathrm{dist}$ 。

因此，左偏树每个节点的 $\mathrm{dist}$ 都等于其右儿子的 $\mathrm{dist}$ 加一。

需要注意的是， $\mathrm{dist}$ 不是深度， **左偏树的深度没有保证** ，一条向左的链也是左偏树。

## 核心操作：合并（merge)

合并两个堆时，由于要满足堆性质，先取值较小（为了方便，本文讨论小根堆）的那个根作为合并后堆的根节点，然后将这个根的左儿子作为合并后堆的左儿子，递归地合并其右儿子与另一个堆，作为合并后的堆的右儿子。为了满足左偏性质，合并后若左儿子的 $\mathrm{dist}$ 小于右儿子的 $\mathrm{dist}$ ，就交换两个儿子。

参考代码：

```cpp
int merge(int x, int y) {
  if (!x || !y) return x | y;  //若一个堆为空则返回另一个堆
  if (t[x].val > t[y].val) swap(x, y);  //取值较小的作为根
  t[x].rs = merge(t[x].rs, y);          //递归合并右儿子与另一个堆
  if (t[t[x].rs].d > t[t[x].ls].d)
    swap(t[x].ls, t[x].rs);   //若不满足左偏性质则交换左右儿子
  t[x].d = t[t[x].rs].d + 1;  //更新dist
  return x;
}
```

由于左偏性质，每递归一层，其中一个堆根节点的 $\mathrm{dist}$ 就会减小 $1$ ，而“一棵有 $n$ 个节点的二叉树，根的 $\mathrm{dist}$ 不超过 $\left\lceil\log (n+1)\right\rceil$ ”，所以合并两个大小分别为 $n$ 和 $m$ 的堆复杂度是 $O(\log n+\log m)$ 。

左偏树还有一种无需交换左右儿子的写法：将 $\mathrm{dist}$ 较大的儿子视作左儿子， $\mathrm{dist}$ 较小的儿子视作右儿子：

```cpp
int& rs(int x) { return t[x].ch[t[t[x].ch[1]].d < t[t[x].ch[0]].d]; }

int merge(int x, int y) {
  if (!x || !y) return x | y;
  if (t[x].val < t[y].val) swap(x, y);
  rs(x) = merge(rs(x), y);
  t[x].d = t[rs(x)].d + 1;
  return x;
}
```

## 左偏树的其它操作

### 插入节点

单个节点也可以视为一个堆，合并即可。

### 删除根

合并根的左右儿子即可。

### 删除任意节点

#### 做法

先将左右儿子合并，然后自底向上更新 $\mathrm{dist}$ 、不满足左偏性质时交换左右儿子，当 $\mathrm{dist}$ 无需更新时结束递归：

```cpp
int& rs(int x) { return t[x].ch[t[t[x].ch[1]].d < t[t[x].ch[0]].d]; }

int merge(int x,
          int y)  //有了pushup，直接merge左右儿子就实现了删除节点并保持左偏性质
{
  if (!x || !y) return x | y;
  if (t[x].val < t[y].val) swap(x, y);
  t[rs(x) = merge(rs(x), y)].fa = x;
  pushup(x);
  return x;
}

void pushup(int x) {
  if (!x) return;
  if (t[x].d != t[rs(x)].d + 1) {
    t[x].d = t[rs(x)].d + 1;
    pushup(t[x].fa);
  }
}
```

#### 复杂度证明

我们令当前 `pushup` 的这个节点为 $x$ ，其父亲为 $y$ ，一个节点的“初始 $\mathrm{dist}$ ”为它在 `pushup` 前的 $\mathrm{dist}$ 。我们先 `pushup` 一下删除的节点，然后从其父亲开始起讨论复杂度。

继续递归下去有两种情况：

1.   $x$ 是 $y$ 的右儿子，此时 $y$ 的初始 $\mathrm{dist}$ 为 $x$ 的初始 $\mathrm{dist}$ 加一。
2.   $x$ 是 $y$ 的左儿子，只有 $y$ 的左右儿子初始 $\mathrm{dist}$ 相等时（此时左儿子 $\mathrm{dist}$ 减一会导致左右儿子互换）才会继续递归下去，因此 $y$ 的初始 $\mathrm{dist}$ 仍然是 $x$ 的初始 $\mathrm{dist}$ 加一。

所以，我们得到，除了第一次 `pushup` （因为被删除节点的父亲的初始 $\mathrm{dist}$ 不一定等于被删除节点左右儿子合并后的初始 $\mathrm{dist}$ 加一），每递归一层 $x$ 的初始 $\mathrm{dist}$ 就会加一，因此最多递归 $O(\log n)$ 层。

### 整个堆加上/减去一个值、乘上一个正数

其实可以打标记且不改变相对大小的操作都可以。

在根打上标记，删除根/合并堆（访问儿子）时下传标记即可：

```cpp
int merge(int x, int y) {
  if (!x || !y) return x | y;
  if (t[x].val > t[y].val) swap(x, y);
  pushdown(x);
  t[x].rs = merge(t[x].rs, y);
  if (t[t[x].rs].d > t[t[x].ls].d) swap(t[x].ls, t[x].rs);
  t[x].d = t[t[x].rs].d + 1;
  return x;
}

int pop(int x) {
  pushdown(x);
  return merge(t[x].ls, t[x].rs);
}
```

## 例题

### 模板题

 [luogu P3377【模板】左偏树（可并堆）](https://www.luogu.org/problemnew/show/P3377) 

 [Monkey King](https://www.luogu.org/problemnew/show/P1456) 

 [罗马游戏](https://www.luogu.org/problemnew/show/P2713) 

需要注意的是：

1.  合并前要检查是否已经在同一堆中。

2.  左偏树的深度可能达到 $O(n)$ ，因此找一个点所在的堆顶要用并查集维护，不能直接暴力跳父亲。（虽然很多题数据水，暴力跳父亲可以过……）（用并查集维护根时要保证原根指向新根，新根指向自己。）

??? "罗马游戏参考代码"
    ```cpp
    #include <algorithm>
    #include <cctype>
    #include <cstdio>
    #include <iostream>
    
    using namespace std;
    
    int read() {
      int out = 0;
      char c;
      while (!isdigit(c = getchar()))
        ;
      for (; isdigit(c); c = getchar()) out = out * 10 + c - '0';
      return out;
    }
    
    const int N = 1000010;
    
    struct Node {
      int val, ch[2], d;
    } t[N];
    
    int& rs(int x);
    int merge(int x, int y);
    
    int find(int x);
    
    int n, m, f[N];
    bool kill[N];
    char op[10];
    
    int main() {
      int i, x, y;
    
      n = read();
    
      for (i = 1; i <= n; ++i) {
        t[i].val = read();
        f[i] = i;
      }
    
      m = read();
    
      while (m--) {
        scanf("%s", op);
        if (op[0] == 'M') {
          x = read();
          y = read();
          if (kill[x] || kill[y] || find(x) == find(y)) continue;
          f[find(x)] = f[find(y)] = merge(find(x), find(y));
        } else {
          x = read();
          if (!kill[x]) {
            x = find(x);
            kill[x] = true;
            f[x] = f[t[x].ch[0]] = f[t[x].ch[1]] = merge(
                t[x].ch[0], t[x].ch[1]);  //由于堆中的点会find到x，所以f[x]也要修改
            printf("%d\n", t[x].val);
          } else
            puts("0");
        }
      }
    
      return 0;
    }
    
    int& rs(int x) { return t[x].ch[t[t[x].ch[1]].d < t[t[x].ch[0]].d]; }
    
    int merge(int x, int y) {
      if (!x || !y) return x | y;
      if (t[x].val > t[y].val) swap(x, y);
      rs(x) = merge(rs(x), y);
      t[x].d = t[rs(x)].d + 1;
      return x;
    }
    
    int find(int x) { return x == f[x] ? x : f[x] = find(f[x]); }
    ```

### 树上问题

 [「APIO2012」派遣](https://www.luogu.org/problemnew/show/P1552) 

 [「JLOI2015」城池攻占](https://www.luogu.org/problemnew/show/P3261) 

这类题目往往是每个节点维护一个堆，与儿子合并，依题意弹出、修改、计算答案，有点像线段树合并的类似题目。

??? "城池攻占参考代码"
    ```cpp
    #include <algorithm>
    #include <cctype>
    #include <cstdio>
    #include <iostream>
    
    using namespace std;
    
    typedef long long ll;
    
    ll read() {
      ll out = 0;
      int f = 1;
      char c;
      for (c = getchar(); !isdigit(c) && c != '-'; c = getchar())
        ;
      if (c == '-') f = -1, c = getchar();
      for (; isdigit(c); c = getchar()) out = out * 10 + c - '0';
      return out * f;
    }
    
    const int N = 300010;
    
    struct Node {
      int ls, rs, d;
      ll val, add, mul;
      Node() {
        ls = rs = add = 0;
        d = mul = 1;
      }
    } t[N];
    
    int merge(int x, int y);
    int pop(int x);
    void madd(int u, ll x);
    void mmul(int u, ll x);
    void pushdown(int x);
    
    void add(int u, int v);
    void dfs(int u);
    
    int head[N], nxt[N], to[N], cnt;
    int n, m, p[N], f[N], a[N], dep[N], c[N], ans1[N],
        ans2[N];  // p是树上每个点对应的堆顶
    ll h[N], b[N];
    
    int main() {
      int i;
    
      n = read();
      m = read();
    
      for (i = 1; i <= n; ++i) h[i] = read();
    
      for (i = 2; i <= n; ++i) {
        f[i] = read();
        add(f[i], i);
        a[i] = read();
        b[i] = read();
      }
    
      for (i = 1; i <= m; ++i) {
        t[i].val = read();
        c[i] = read();
        p[c[i]] = merge(i, p[c[i]]);
      }
    
      dfs(1);
    
      for (i = 1; i <= n; ++i) printf("%d\n", ans1[i]);
      for (i = 1; i <= m; ++i) printf("%d\n", ans2[i]);
    
      return 0;
    }
    
    void dfs(int u) {
      int i, v;
      for (i = head[u]; i; i = nxt[i]) {
        v = to[i];
        dep[v] = dep[u] + 1;
        dfs(v);
      }
      while (p[u] && t[p[u]].val < h[u]) {
        ++ans1[u];
        ans2[p[u]] = dep[c[p[u]]] - dep[u];
        p[u] = pop(p[u]);
      }
      if (a[u])
        mmul(p[u], b[u]);
      else
        madd(p[u], b[u]);
      if (u > 1)
        p[f[u]] = merge(p[u], p[f[u]]);
      else
        while (p[u]) {
          ans2[p[u]] = dep[c[p[u]]] + 1;
          p[u] = pop(p[u]);
        }
    }
    
    void add(int u, int v) {
      nxt[++cnt] = head[u];
      head[u] = cnt;
      to[cnt] = v;
    }
    
    int merge(int x, int y) {
      if (!x || !y) return x | y;
      if (t[x].val > t[y].val) swap(x, y);
      pushdown(x);
      t[x].rs = merge(t[x].rs, y);
      if (t[t[x].rs].d > t[t[x].ls].d) swap(t[x].ls, t[x].rs);
      t[x].d = t[t[x].rs].d + 1;
      return x;
    }
    
    int pop(int x) {
      pushdown(x);
      return merge(t[x].ls, t[x].rs);
    }
    
    void madd(int u, ll x) {
      t[u].val += x;
      t[u].add += x;
    }
    
    void mmul(int u, ll x) {
      t[u].val *= x;
      t[u].add *= x;
      t[u].mul *= x;
    }
    
    void pushdown(int x) {
      mmul(t[x].ls, t[x].mul);
      madd(t[x].ls, t[x].add);
      mmul(t[x].rs, t[x].mul);
      madd(t[x].rs, t[x].add);
      t[x].add = 0;
      t[x].mul = 1;
    }
    ```

###  [「SCOI2011」棘手的操作](https://www.luogu.org/problemnew/show/P3273) 

~~这题题如其名，非常棘手~~。

首先，找一个节点所在堆的堆顶要用并查集，而不能暴力向上跳。

再考虑单点查询，若用普通的方法打标记，就得查询点到根路径上的标记之和，最坏情况下可以达到 $O(n)$ 的复杂度。如果只有堆顶有标记，就可以快速地查询了，但如何做到呢？

可以用类似启发式合并的方式，每次合并的时候把较小的那个堆标记暴力下传到每个节点，然后把较大的堆的标记作为合并后的堆的标记。由于合并后有另一个堆的标记，所以较小的堆下传标记时要下传其标记减去另一个堆的标记。由于每个节点每被合并一次所在堆的大小至少乘二，所以每个节点最多被下放 $O(\log n)$ 次标记，暴力下放标记的总复杂度就是 $O(n\log n)$ 。

再考虑单点加，先删除，再更新，最后插入即可。

然后是全局最大值，可以用一个平衡树/支持删除任意节点的堆（如左偏树）/multiset 来维护每个堆的堆顶。

所以，每个操作分别如下：

1.  暴力下传点数较小的堆的标记，合并两个堆，更新 size、tag，在 multiset 中删去合并后不在堆顶的那个原堆顶。
2.  删除节点，更新值，插入回来，更新 multiset。需要分删除节点是否为根来讨论一下。
3.  堆顶打标记，更新 multiset。
4.  打全局标记。
5.  查询值 + 堆顶标记 + 全局标记。
6.  查询根的值 + 堆顶标记 + 全局标记。
7.  查询 multiset 最大值 + 全局标记。

??? "棘手的操作参考代码"
    ```cpp
    #include <algorithm>
    #include <cctype>
    #include <cstdio>
    #include <iostream>
    #include <set>
    
    using namespace std;
    
    int read() {
      int out = 0, f = 1;
      char c;
      for (c = getchar(); !isdigit(c) && c != '-'; c = getchar())
        ;
      if (c == '-') {
        f = -1;
        c = getchar();
      }
      for (; isdigit(c); c = getchar()) out = out * 10 + c - '0';
      return out * f;
    }
    
    const int N = 300010;
    
    struct Node {
      int val, ch[2], d, fa;
    } t[N];
    
    int& rs(int x);
    int merge(int x, int y);
    void pushup(int x);
    void pushdown(int x, int y);
    
    int find(int x);
    
    int n, m, f[N], tag[N], siz[N], delta;
    char op[10];
    multiset<int> s;
    
    int main() {
      int i, x, y;
    
      n = read();
    
      for (i = 1; i <= n; ++i) {
        t[i].val = read();
        f[i] = i;
        siz[i] = 1;
        s.insert(t[i].val);
      }
    
      m = read();
    
      while (m--) {
        scanf("%s", op);
        if (op[0] == 'U') {
          x = find(read());
          y = find(read());
          if (x != y) {
            if (siz[x] > siz[y]) swap(x, y);
            pushdown(x, tag[x] - tag[y]);
            f[x] = f[y] = merge(x, y);
            if (f[x] == x) {
              s.erase(s.find(t[y].val + tag[y]));
              tag[x] = tag[y];
              siz[x] += siz[y];
              tag[y] = siz[y] = 0;
            } else {
              s.erase(s.find(t[x].val + tag[y]));
              siz[y] += siz[x];
              tag[x] = siz[x] = 0;
            }
          }
        } else if (op[0] == 'A') {
          if (op[1] == '1') {
            x = read();
            if (x == find(x)) {
              t[t[x].ch[0]].fa = t[t[x].ch[1]].fa = 0;
              y = merge(t[x].ch[0], t[x].ch[1]);
              s.erase(s.find(t[x].val + tag[x]));
              t[x].val += read();
              t[x].fa = t[x].ch[0] = t[x].ch[1] = 0;
              t[x].d = 1;
              f[x] = f[y] = merge(x, y);
              s.insert(t[f[x]].val + tag[x]);
              if (f[x] == y) {
                tag[y] = tag[x];
                siz[y] = siz[x];
                tag[x] = siz[x] = 0;
              }
            } else {
              t[t[x].ch[0]].fa = t[t[x].ch[1]].fa = t[x].fa;
              t[t[x].fa].ch[x == t[t[x].fa].ch[1]] = merge(t[x].ch[0], t[x].ch[1]);
              t[x].val += read();
              t[x].fa = t[x].ch[0] = t[x].ch[1] = 0;
              t[x].d = 1;
              y = find(x);
              f[x] = f[y] = merge(x, y);
              if (f[x] == x) {
                s.erase(s.find(t[y].val + tag[y]));
                s.insert(t[x].val + tag[y]);
                tag[x] = tag[y];
                siz[x] = siz[y];
                tag[y] = siz[y] = 0;
              }
            }
          } else if (op[1] == '2') {
            x = find(read());
            s.erase(s.find(t[x].val + tag[x]));
            tag[x] += read();
            s.insert(t[x].val + tag[x]);
          } else
            delta += read();
        } else {
          if (op[1] == '1') {
            x = read();
            printf("%d\n", t[x].val + tag[find(x)] + delta);
          } else if (op[1] == '2') {
            x = find(read());
            printf("%d\n", t[x].val + tag[x] + delta);
          } else
            printf("%d\n", *s.rbegin() + delta);
        }
      }
    
      return 0;
    }
    
    int& rs(int x) { return t[x].ch[t[t[x].ch[1]].d < t[t[x].ch[0]].d]; }
    
    int merge(int x, int y) {
      if (!x || !y) return x | y;
      if (t[x].val < t[y].val) swap(x, y);
      t[rs(x) = merge(rs(x), y)].fa = x;
      pushup(x);
      return x;
    }
    
    void pushup(int x) {
      if (!x) return;
      if (t[x].d != t[rs(x)].d + 1) {
        t[x].d = t[rs(x)].d + 1;
        pushup(t[x].fa);
      }
    }
    
    void pushdown(int x, int y) {
      if (!x) return;
      t[x].val += y;
      pushdown(t[x].ch[0], y);
      pushdown(t[x].ch[1], y);
    }
    
    int find(int x) { return x == f[x] ? x : f[x] = find(f[x]); }
    ```

###  [「BOI2004」Sequence 数字序列](https://www.luogu.org/problemnew/show/P4331) 

这是一道论文题，详见 [《黄源河 -- 左偏树的特点及其应用》](https://github.com/OI-wiki/libs/blob/master/%E9%9B%86%E8%AE%AD%E9%98%9F%E5%8E%86%E5%B9%B4%E8%AE%BA%E6%96%87/%E5%9B%BD%E5%AE%B6%E9%9B%86%E8%AE%AD%E9%98%9F2005%E8%AE%BA%E6%96%87%E9%9B%86/%E9%BB%84%E6%BA%90%E6%B2%B3--%E5%B7%A6%E5%81%8F%E6%A0%91%E7%9A%84%E7%89%B9%E7%82%B9%E5%8F%8A%E5%85%B6%E5%BA%94%E7%94%A8/%E9%BB%84%E6%BA%90%E6%B2%B3.pdf) 。
