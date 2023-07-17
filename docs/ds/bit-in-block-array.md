## 简介

分块套树状数组在特定条件下可以用来做一些树套树可以做的事情，但是相比起树套树，分块套树状数组代码编写更加简短，更加容易实现。

## 简单的例子

一个简单的例子就是二维平面中矩阵区域内点数的查询。

???+ note "矩形区域查询"
    给出 $n$ 个二维平面中的点 $(x_i, y_i)$，其中 $1 \le i \le n, 1 \le x_i, y_i \le n, 1 \le n \le 10^5$, 要求实现以下中操作：
    
    1.  给出 $a, b, c, d$，询问以 $(a, b)$ 为左上角，$c, d$ 为右下角的矩形区域内点的个数。
    2.  给出 $x, y$，将横坐标为 $x$ 的点的纵坐标改为 $y$。
    
    题目 **强制在线**，保证 $x_i \ne x_j(1 \le i, j \le n, i \ne j)$。

对于操作 1，可以通过矩形容斥将其转化为 4 个二维偏序的查询去解决，然后因为强制在线，CDQ 分治之类的离线算法就解决不了，于是想到了树套树，比如树状数组套 Treap。这确实可以解决这个问题，但是代码太长了，也不是特别好实现。

注意到，题目还额外保证了 $x_i \ne x_j(1 \le i, j \le n, i \ne j)$，这个时候就可以用分块套树状数组解决。

### 初始化

首先，一个 $x$ 只对应一个 $y$，所以可以用一个数组记录这个映射关系，比如令 $Y_i$ 表示横坐标为 $i$ 的点的纵坐标。

然后，以 $\sqrt n$ 为块大小对横坐标进行分块。为每个块建一棵权值树状数组。记 $T_i$ 为第 $i$ 个块对应的树状数组，$T_{i, j}$ 表示块 $i$ 里纵坐标在 $(j - lowbit(j), j]$ 内的点的个数。

### 查询

对于操作 1，将其转化为 4 个二维偏序的查询。现在只需要解决给出 $a, b$，询问有多少个点满足 $1 \le x_i \le a, 1\le y_i \le b$。

现在要查询横坐标的范围为 $[1, a]$。因为查询范围最右边可能有一段不是完整的块，所以暴力扫一遍这个段，看是否满足 $Y_i \le b$，统计出这个段满足要求的点的个数。

现在就只需要处理完整的块。暴力扫一遍前面的块，查询每个块对应的树状数组中值小于 $b$ 的个数，累加到答案上。

这就完事了？不，注意到处理完整的块的时候，其实相当于查询 $T$ 的前缀和，如果修改时也使用树状数组的技巧处理 $T$，那么查询时复杂度会更低。

### 修改

普通的做法就先找到点 $x$ 所在的块，然后一减一加两个权值树状数组单点修改，再将 $Y_x$ 置为 $y$。

如果用了上面说的优化，那就是对 $T$ 也走一个树状数组修改的流程，每次修改也是一减一加两个权值树状数组单点修改。

对上述步骤进行一定的改变，比如将一减一加改成只减，就是删点；改成只加，就是加点。但是必须要注意一个 $x$ 只能对应一个 $y$。

### 空间复杂度

分块分了 $\sqrt n$ 个块，每个块一颗线段树 $O (n)$ 的空间，所以空间复杂度为 $O(n \sqrt n)$。

### 时间复杂度

查询的话，遍历非完整块的段 $O(\sqrt n)$。然后，对 $T$ 走树状数组查询，每个经历到的 $T_i$ 也走树状数组查询，这一步是 $O(\log (\sqrt n) \log n)$ 的复杂度。所以查询的时间复杂度为 $O (\sqrt n + \log (\sqrt n) \log n)$。

修改和查询一样，复杂度为 $O (\sqrt n + \log (\sqrt n) \log n)$。

## 例题 1

???+ note "[Intersection of Permutations](https://codeforces.com/problemset/problem/1093/E)"
    给出两个排列 $a$ 和 $b$，要求实现以下两种操作：
    
    1.  给出 $l_a, r_a, l_b, r_b$，要求查询既出现在 $a[l_a ... r_a]$ 又出现在 $b[l_b ... r_b]$ 中的元素的个数。
    2.  给出 $x, y$，$swap(b_x, b_y)$。
    
    序列长度 $n$ 满足 $2 \le n \le 2 \cdot 10^5$，操作个数 $q$ 满足 $1 \le q \le 2 \cdot 10^5$。

对于每个值 $i$，记 $x_i$ 是它在排列 $b$ 中的下标，$y_i$ 是它在排列 $a$ 中的下标。这样，操作一就变成了一个矩形区域内点的个数的询问，操作 2 可以看成两个修改操作。而且因为是排列，所以满足一个 $x$ 对应一个 $y$，所以这题可以用分块套树状数组来写。

??? note "参考代码（分块套树状数组 - 1s）"
    ```cpp
    #include <bits/stdc++.h>
    using namespace std;
    const int N = 2e5 + 5;
    const int M = sqrt(N) + 5;
    
    int n, m, pa[N], pb[N];
    
    int nn, block_size, block_cnt, block_id[N], L[N], R[N], T[M][N];
    
    void build(int n) {
      nn = n;
      block_size = sqrt(nn);
      block_cnt = nn / block_size;
      for (int i = 1; i <= block_cnt; ++i) {
        L[i] = R[i - 1] + 1;
        R[i] = i * block_size;
      }
      if (R[block_cnt] < nn) {
        ++block_cnt;
        L[block_cnt] = R[block_cnt - 1] + 1;
        R[block_cnt] = nn;
      }
      for (int j = 1; j <= block_cnt; ++j)
        for (int i = L[j]; i <= R[j]; ++i) block_id[i] = j;
    }
    
    int lb(int x) { return x & -x; }
    
    void add(int p, int v, int d) {
      for (int i = block_id[p]; i <= block_cnt; i += lb(i))
        for (int j = v; j <= nn; j += lb(j)) T[i][j] += d;
    }
    
    int getsum(int p, int v) {
      if (!p) return 0;
      int res = 0;
      int id = block_id[p];
      for (int i = L[id]; i <= p; ++i)
        if (pb[i] <= v) ++res;
      for (int i = id - 1; i; i -= lb(i))
        for (int j = v; j; j -= lb(j)) res += T[i][j];
      return res;
    }
    
    void update(int x, int y) {
      add(x, pb[x], -1);
      add(y, pb[y], -1);
      swap(pb[x], pb[y]);
      add(x, pb[x], 1);
      add(y, pb[y], 1);
    }
    
    int query(int la, int ra, int lb, int rb) {
      int res = getsum(rb, ra) - getsum(rb, la - 1) - getsum(lb - 1, ra) +
                getsum(lb - 1, la - 1);
      return res;
    }
    
    int main() {
      scanf("%d %d", &n, &m);
      int v;
      for (int i = 1; i <= n; ++i) scanf("%d", &v), pa[v] = i;
      for (int i = 1; i <= n; ++i) scanf("%d", &v), pb[i] = pa[v];
    
      build(n);
      for (int i = 1; i <= n; ++i) add(i, pb[i], 1);
    
      int op, la, lb, ra, rb, x, y;
      for (int i = 1; i <= m; ++i) {
        scanf("%d", &op);
        if (op == 1) {
          scanf("%d %d %d %d", &la, &ra, &lb, &rb);
          printf("%d\n", query(la, ra, lb, rb));
        } else if (op == 2) {
          scanf("%d %d", &x, &y);
          update(x, y);
        }
      }
      return 0;
    }
    ```

??? node "参考代码（树状数组套 Treap—TLE）"
    ```cpp
    #include <bits/stdc++.h>
    using namespace std;
    const int N = 2e5 + 5;
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    
    int n, m, pa[N], pb[N];
    
    // Treap
    struct Treap {
      struct node {
        node *l, *r;
        int sz, rnd, v;
    
        node(int _v) : l(NULL), r(NULL), sz(1), rnd(rng()), v(_v) {}
      };
    
      int get_size(node*& p) { return p ? p->sz : 0; }
    
      void push_up(node*& p) {
        if (!p) return;
        p->sz = get_size(p->l) + get_size(p->r) + 1;
      }
    
      node* root;
    
      node* merge(node* a, node* b) {
        if (!a) return b;
        if (!b) return a;
        if (a->rnd < b->rnd) {
          a->r = merge(a->r, b);
          push_up(a);
          return a;
        } else {
          b->l = merge(a, b->l);
          push_up(b);
          return b;
        }
      }
    
      void split_val(node* p, const int& k, node*& a, node*& b) {
        if (!p)
          a = b = NULL;
        else {
          if (p->v <= k) {
            a = p;
            split_val(p->r, k, a->r, b);
            push_up(a);
          } else {
            b = p;
            split_val(p->l, k, a, b->l);
            push_up(b);
          }
        }
      }
    
      void split_size(node* p, int k, node*& a, node*& b) {
        if (!p)
          a = b = NULL;
        else {
          if (get_size(p->l) <= k) {
            a = p;
            split_size(p->r, k - get_size(p->l), a->r, b);
            push_up(a);
          } else {
            b = p;
            split_size(p->l, k, a, b->l);
            push_up(b);
          }
        }
      }
    
      void ins(int val) {
        node *a, *b;
        split_val(root, val, a, b);
        a = merge(a, new node(val));
        root = merge(a, b);
      }
    
      void del(int val) {
        node *a, *b, *c, *d;
        split_val(root, val, a, b);
        split_val(a, val - 1, c, d);
        delete d;
        root = merge(c, b);
      }
    
      int qry(int val) {
        node *a, *b;
        split_val(root, val, a, b);
        int res = get_size(a);
        root = merge(a, b);
        return res;
      }
    
      int qry(int l, int r) { return qry(r) - qry(l - 1); }
    };
    
    // Fenwick Tree
    Treap T[N];
    
    int lb(int x) { return x & -x; }
    
    void ins(int x, int v) {
      for (; x <= n; x += lb(x)) T[x].ins(v);
    }
    
    void del(int x, int v) {
      for (; x <= n; x += lb(x)) T[x].del(v);
    }
    
    int qry(int x, int mi, int ma) {
      int res = 0;
      for (; x; x -= lb(x)) res += T[x].qry(mi, ma);
      return res;
    }
    
    int main() {
      scanf("%d %d", &n, &m);
      int v;
      for (int i = 1; i <= n; ++i) scanf("%d", &v), pa[v] = i;
      for (int i = 1; i <= n; ++i) scanf("%d", &v), pb[i] = pa[v];
      for (int i = 1; i <= n; ++i) ins(i, pb[i]);
    
      int op, la, lb, ra, rb, x, y;
      for (int i = 1; i <= m; ++i) {
        scanf("%d", &op);
        if (op == 1) {
          scanf("%d %d %d %d", &la, &ra, &lb, &rb);
          printf("%d\n", qry(rb, la, ra) - qry(lb - 1, la, ra));
        } else if (op == 2) {
          scanf("%d %d", &x, &y);
          del(x, pb[x]);
          del(y, pb[y]);
          swap(pb[x], pb[y]);
          ins(x, pb[x]);
          ins(y, pb[y]);
        }
      }
      return 0;
    }
    ```

## 例题 2

???+ note "[Complicated Computations](https://codeforces.com/contest/1436/problem/E)"
    给出一个序列 $a$，将 $a$ 所有连续子序列的 MEX 构成的数组作为 $b$，问 $b$ 的 MEX。一个序列的 MEX 是序列中最小的没出现过的 **正整数**。
    
    序列的长度 $n$ 满足 $1 \le n \le 10^5$。

**观察**：一个序列的 MEX 为 $mex$，当且仅当这个序列包含 $1$ 至 $mex-1$，但不包含 $mex$。

依次判断是否存在 MEX 为 $1$ 至 $n+1$ 的连续子序列。如果没有 MEX 为 $i$ 的连续子序列，那么答案即为 $i$。如果都存在，那么答案为 $n + 2$。

在判断 $i$ 时，将序列视为由零或多个 $i$ 分隔的多个段。如果存在一个段，这个段中包含 $1$ 至 $i - 1$，但不包含 $i$，那么就说明存在值为 $i$ 的连续子序列。

用一个数组 $Y_j$ 记录上一个值为 $a_j$ 的元素的位置，以 $j$ 作为 $x$，$Y_j$ 作为 $y$，$a_j$ 作为 $z$。这样，计算段内是否包含 $1$ 至 $i - 1$ 就是一个三维偏序的问题。形式化的说，判断段 $[l, r]$ 的 MEX 值是否为 $i$，就是看满足 $l \le j \le r, Y_j \le l - 1, a_j \le i - 1$ 的点的个数是否为 $i-1$。

如果在判断完值为 $i$ 的元素之后再将对应的点插入，这时因为 $[l, r]$ 内只存在 $a_j \le i - 1$ 的元素，所以上述三维偏序问题就可以转换为二维偏序的问题。

??? note "参考代码（分块套树状数组 - 78ms）"
    ```cpp
    #include <bits/stdc++.h>
    using namespace std;
    const int N = 1e5 + 5;
    const int M = sqrt(N) + 5;
    
    // 分块
    int nn, b[N], block_size, block_cnt, block_id[N], L[N], R[N], T[M][N];
    
    void build(int n) {
      nn = n;
      block_size = sqrt(nn);
      block_cnt = nn / block_size;
      for (int i = 1; i <= block_cnt; ++i) {
        L[i] = R[i - 1] + 1;
        R[i] = i * block_size;
      }
      if (R[block_cnt] < nn) {
        ++block_cnt;
        L[block_cnt] = R[block_cnt - 1] + 1;
        R[block_cnt] = nn;
      }
      for (int j = 1; j <= block_cnt; ++j)
        for (int i = L[j]; i <= R[j]; ++i) block_id[i] = j;
    }
    
    int lb(int x) { return x & -x; }
    
    // d = 1: 加点(p, v)
    // d = -1: 删点(p, v)
    void add(int p, int v, int d) {
      for (int i = block_id[p]; i <= block_cnt; i += lb(i))
        for (int j = v; j <= nn; j += lb(j)) T[i][j] += d;
    }
    
    // 询问[1, r]内，纵坐标小于等于val的点有多少个
    int getsum(int p, int v) {
      if (!p) return 0;
      int res = 0;
      int id = block_id[p];
      for (int i = L[id]; i <= p; ++i)
        if (b[i] && b[i] <= v) ++res;
      for (int i = id - 1; i; i -= lb(i))
        for (int j = v; j; j -= lb(j)) res += T[i][j];
      return res;
    }
    
    // 询问[l, r]内，纵坐标小于等于val的点有多少个
    int query(int l, int r, int val) {
      if (l > r) return -1;
      int res = getsum(r, val) - getsum(l - 1, val);
      return res;
    }
    
    // 加点(p, v)
    void update(int p, int v) {
      b[p] = v;
      add(p, v, 1);
    }
    
    int n, a[N];
    vector<int> g[N];
    
    int main() {
      scanf("%d", &n);
    
      // 为了减少讨论，加了哨兵节点
      // 因为树状数组添加的时候，为0可能会死循环，所以整体往右偏移一位
      // a_1和a_{n+2}为哨兵节点
      for (int i = 2; i <= n + 1; ++i) scanf("%d", &a[i]);
      for (int i = 2; i <= n + 1; ++i) g[a[i]].push_back(i);
    
      // 分块
      build(n + 2);
    
      int ans = n + 2, lst, ok;
      for (int i = 1; i <= n + 1; ++i) {
        g[i].push_back(n + 2);
    
        lst = 1;
        ok = 0;
        for (int pos : g[i]) {
          if (query(lst + 1, pos - 1, lst) == i - 1) {
            ok = 1;
            break;
          }
          lst = pos;
        }
    
        if (!ok) {
          ans = i;
          break;
        }
    
        lst = 1;
        g[i].pop_back();
        for (int pos : g[i]) {
          update(pos, lst);
          lst = pos;
        }
      }
      printf("%d\n", ans);
      return 0;
    }
    ```

??? note "参考代码（线段树套 Treap-468ms）"
    ```cpp
    #include <bits/stdc++.h>
    using namespace std;
    const int N = 1e5 + 5;
    
    vector<int> g[N];
    int n, a[N];
    
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    
    struct Treap {
      struct node {
        node *l, *r;
        unsigned rnd;
        int sz, v;
    
        node(int _v) : l(NULL), r(NULL), rnd(rng()), sz(1), v(_v) {}
      };
    
      int get_size(node*& p) { return p ? p->sz : 0; }
    
      void push_up(node*& p) {
        if (!p) return;
        p->sz = get_size(p->l) + get_size(p->r) + 1;
      }
    
      node* root;
    
      node* merge(node* a, node* b) {
        if (!a) return b;
        if (!b) return a;
        if (a->rnd < b->rnd) {
          a->r = merge(a->r, b);
          push_up(a);
          return a;
        } else {
          b->l = merge(a, b->l);
          push_up(b);
          return b;
        }
      }
    
      void split_val(node* p, const int& k, node*& a, node*& b) {
        if (!p)
          a = b = NULL;
        else {
          if (p->v <= k) {
            a = p;
            split_val(p->r, k, a->r, b);
            push_up(a);
          } else {
            b = p;
            split_val(p->l, k, a, b->l);
            push_up(b);
          }
        }
      }
    
      void split_size(node* p, int k, node*& a, node*& b) {
        if (!p)
          a = b = NULL;
        else {
          if (get_size(p->l) <= k) {
            a = p;
            split_size(p->r, k - get_size(p->l), a->r, b);
            push_up(a);
          } else {
            b = p;
            split_size(p->l, k, a, b->l);
            push_up(b);
          }
        }
      }
    
      void insert(int val) {
        node *a, *b;
        split_val(root, val, a, b);
        a = merge(a, new node(val));
        root = merge(a, b);
      }
    
      int query(int val) {
        node *a, *b;
        split_val(root, val, a, b);
        int res = get_size(a);
        root = merge(a, b);
        return res;
      }
    
      int qry(int l, int r) { return query(r) - query(l - 1); }
    };
    
    // Segment Tree
    Treap T[N << 2];
    
    void insert(int x, int l, int r, int p, int val) {
      T[x].insert(val);
      if (l == r) return;
      int mid = (l + r) >> 1;
      if (p <= mid)
        insert(x << 1, l, mid, p, val);
      else
        insert(x << 1 | 1, mid + 1, r, p, val);
    }
    
    int query(int x, int l, int r, int L, int R, int val) {
      if (l == L && r == R) return T[x].query(val);
      int mid = (l + r) >> 1;
      if (R <= mid) return query(x << 1, l, mid, L, R, val);
      if (L > mid) return query(x << 1 | 1, mid + 1, r, L, R, val);
      return query(x << 1, l, mid, L, mid, val) +
             query(x << 1 | 1, mid + 1, r, mid + 1, R, val);
    }
    
    int query(int l, int r, int val) {
      if (l > r) return -1;
      return query(1, 1, n, l, r, val);
    }
    
    int main() {
      scanf("%d", &n);
      for (int i = 1; i <= n; ++i) scanf("%d", &a[i]);
      for (int i = 1; i <= n; ++i) g[a[i]].push_back(i);
    
      // a_0 和 a_{n+1}为哨兵节点
      int ans = n + 2, lst, ok;
      for (int i = 1; i <= n + 1; ++i) {
        g[i].push_back(n + 1);
    
        lst = 0;
        ok = 0;
        for (int pos : g[i]) {
          if (query(lst + 1, pos - 1, lst) == i - 1) {
            ok = 1;
            break;
          }
          lst = pos;
        }
    
        if (!ok) {
          ans = i;
          break;
        }
    
        lst = 0;
        g[i].pop_back();
        for (int pos : g[i]) {
          insert(1, 1, n, pos, lst);
          lst = pos;
        }
      }
      printf("%d\n", ans);
      return 0;
    }
    ```
