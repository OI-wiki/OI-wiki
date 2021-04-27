## 定义

后缀之间的大小由字典序定义，后缀平衡树就是一个维护这些后缀顺序的平衡树，即字符串 $T$ 的后缀平衡树是 $T$ 所有后缀的有序集合。后缀平衡树上的一个节点相当于原字符串的一个后缀。

特别地，后缀平衡树的中序遍历即为后缀数组。

## 构造过程

对长度为 $n$ 的字符串 $T$ 建立其后缀平衡树，考虑逆序将其后缀加入后缀平衡树。

记后缀平衡树维护的集合为 $X$，当前添加的后缀为 $S$，则添加下一个后缀就是向 $X$ 中加入 $\texttt{c}S$（亦可理解为后缀平衡树维护的字符串为 $S$，下一步往 $S$ 前加入一个字符 $\texttt{c}$）。这一操作其实就是向平衡树中插入节点。

这里使用期望树高为 $O(\log n)$ 的平衡树，例如替罪羊树或 Treap 等。

### 做法 1

插入时，暴力比较两个后缀之间的大小关系，从而判断之后是往哪一个子树添加。这样子，单次插入至多比较 $O(\log n)$ 次，单次比较的时间复杂度至多为 $O(n)$，一共 $O(n\log n)$。

一共会插入 $n$ 次，所以该做法的时间复杂度存在上界 $O(n^2 \log n)$。

### 做法 2

注意到 $\texttt{c}S$ 与 $S$ 的区别仅在于 $\texttt{c}$，且 $S$ 已经属于 $X$ 了，可以利用这一点来优化插入操作。

假设当前要比较 $\texttt{c}S$ 与 $A$ 两个字符串的大小，且 $A, S \in X$。每次比较时，首先比较两串的首字符。若首字符不等，则两串的大小关系就已经确定了；若首字符相等，那么就只需要判断去除首字符后两字符串的大小关系。而两串去除首字符后都已经属于 $X$ 了，这时候可以借助平衡树 $O(\log n)$ 求排名的操作来完成后续的比较。这样，单次插入的操作至多 $O(\log^2 n)$。

一共会插入 $n$ 次，所以该做法的时间复杂度存在上界 $O(n \log^2 n)$。

### 做法 3

根据做法 2，如果能够 $O(1)$ 判断平衡树中两个节点之间的大小关系，那么就可以在 $O(n \log n)$ 的时间内完成后缀平衡树的构造。

记 $val_i$ 表示节点 $i$ 的值。如果在建平衡树时，每个节点多维护一个标记 $tag_i$，使得若 $tag_i > tag_j \Leftrightarrow val_i > val_j$，那么就可以根据 $tag_i$ 的大小 $O(1)$ 判断平衡树中两个节点的大小。

不妨令平衡树中每个节点对应一个实数区间，令根节点对应 $(0, 1)$。对于节点 $i$，记其对应的实数区间为 $(l, r)$，则 $tag_i = \frac{l + r}{2}$，其左子树对应实数区间 $(l, tag_i)$，其右子树对应实数区间 $(tag_i, r)$。易证 $tag_i$ 满足上述要求。

由于使用了期望树高为 $O(\log n)$ 的平衡树，所以精度是有一定保证的。实际实现时也可以用一个较大的区间来做，例如让根对应 $(0, 10^{18})$。

### 做法 4

其实可以先构建出后缀数组，然后再根据后缀数组构建后缀平衡树。这样做的复杂度瓶颈在于后缀数组的构建复杂度或者所用平衡树一次性插入 $n$ 个元素的复杂度。

## 删除操作

假设当前添加的后缀为 $\texttt{c}S$，上一个添加的后缀为 $S$。后缀平衡树还支持删除后缀 $\texttt{c}S$ 的操作（亦可理解为后缀平衡树维护的字符串为 $\texttt{c}S$，将开头的 $\texttt{c}$ 删除）。

类似于插入操作，借助平衡树的删除节点操作可以完成删除 $\texttt{c}S$ 的操作。

## 后缀平衡树的优点

- 后缀平衡树的思路比较清晰，相比后缀自动机等后缀结构更好理解，会写平衡树就能写。
- 后缀平衡树的复杂度不依赖于字符集的大小
- 后缀平衡树支持在字符串开头删除一个字符
- 如果使用支持可持久化的平衡树，那么后缀平衡树也能可持久化

## 例题

### [P3809【模板】后缀排序](https://www.luogu.com.cn/problem/P3809)

后缀数组的模板题，建出后缀平衡树之后，通过中序遍历得到后缀数组。

??? note "SGT版本的参考代码"
    ```cpp
    #include <bits/stdc++.h>
    using namespace std;
    
    const int N = 1e6 + 5;
    const double INF = 1e18;
    
    int n, m, sa[N];
    char t[N];
    
    // SuffixBST(SGT Ver)
    
    // 顺序加入，查询时将询问串翻转
    // 以i开始的后缀，对应节点的编号为i
    const double alpha = 0.75;
    int root;
    int sz[N], L[N], R[N];
    double tag[N];
    int buffer_size, buffer[N];
    
    bool cmp(int x, int y) {
      if (t[x] != t[y]) return t[x] < t[y];
      return tag[x + 1] < tag[y + 1];
    }
    
    void init() { root = 0; }
    
    void new_node(int& rt, int p, double lv, double rv) {
      rt = p;
      sz[rt] = 1;
      tag[rt] = (lv + rv) / 2;
      L[rt] = R[rt] = 0;
    }
    
    void push_up(int x) {
      if (!x) return;
      sz[x] = sz[L[x]] + 1 + sz[R[x]];
    }
    
    bool balance(int rt) { return alpha * sz[rt] > max(sz[L[rt]], sz[R[rt]]); }
    
    void flatten(int rt) {
      if (!rt) return;
      flatten(L[rt]);
      buffer[++buffer_size] = rt;
      flatten(R[rt]);
    }
    
    void build(int& rt, int l, int r, double lv, double rv) {
      if (l > r) {
        rt = 0;
        return;
      }
      int mid = (l + r) >> 1;
      double mv = (lv + rv) / 2;
    
      rt = buffer[mid];
      tag[rt] = mv;
      build(L[rt], l, mid - 1, lv, mv);
      build(R[rt], mid + 1, r, mv, rv);
      push_up(rt);
    }
    
    void rebuild(int& rt, double lv, double rv) {
      buffer_size = 0;
      flatten(rt);
      build(rt, 1, buffer_size, lv, rv);
    }
    
    void insert(int& rt, int p, double lv, double rv) {
      if (!rt) {
        new_node(rt, p, lv, rv);
        return;
      }
    
      if (cmp(p, rt))
        insert(L[rt], p, lv, tag[rt]);
      else
        insert(R[rt], p, tag[rt], rv);
    
      push_up(rt);
      if (!balance(rt)) rebuild(rt, lv, rv);
    }
    
    void remove(int& rt, int p, double lv, double rv) {
      if (!rt) return;
    
      if (rt == p) {
        if (!L[rt] || !R[rt]) {
          rt = (L[rt] | R[rt]);
        } else {
          // 找到rt的前驱来替换rt
          int nrt = L[rt], fa = rt;
          while (R[nrt]) {
            fa = nrt;
            sz[fa]--;
            nrt = R[nrt];
          }
          if (fa == rt) {
            R[nrt] = R[rt];
          } else {
            L[nrt] = L[rt];
            R[nrt] = R[rt];
            R[fa] = 0;
          }
          rt = nrt;
          tag[rt] = (lv + rv) / 2;
        }
      } else {
        double mv = (lv + rv) / 2;
        if (cmp(p, rt))
          remove(L[rt], p, lv, mv);
        else
          remove(R[rt], p, mv, rv);
      }
    
      push_up(rt);
      if (!balance(rt)) rebuild(rt, lv, rv);
    }
    
    void inorder(int rt) {
      if (!rt) return;
      inorder(L[rt]);
      sa[++m] = rt;
      inorder(R[rt]);
    }
    
    void solve(int Case) {
      scanf("%s", t + 1);
      n = strlen(t + 1);
    
      init();
      for (int i = n; i >= 1; --i) {
        insert(root, i, 0, INF);
      }
    
      // 后缀平衡树的中序遍历即为后缀数组
      m = 0;
      inorder(root);
    
      for (int i = 1; i <= n; ++i) printf("%d ", sa[i]);
      printf("\n");
    
      // for (int i = 1; i <= n; ++i)
      //     printf("%lld ", tag[sa[i]]);
      // printf("\n");
    }
    
    int main() {
      int T = 1;
      // cin >> T;
      for (int i = 1; i <= T; ++i) solve(i);
      return 0;
    }
    ```

### [P6164【模板】后缀平衡树](https://www.luogu.com.cn/problem/P6164)

???+ note "题意"
    给定初始字符串 $s$ 和 $q$ 个操作：
    
    1. 在当前字符串的后面插入若干个字符。
    2. 在当前字符串的后面删除若干个字符。
    3. 询问字符串 $t$ 作为连续子串在当前字符串中出现了几次？
    
    题目 **强制在线**，字符串变化长度以及初始长度 $\le 8 \times 10^5$，$q \le 10^5$，询问的总长度 $\le 3 \times 10^6$。

对于操作 1 和操作 2，由于后缀平衡树维护头插和头删操作比较方便，所以想到把尾插和尾删操作搞成头插和头删。这里如果维护 $s$ 的反串的后缀平衡树，而非 $s$ 的后缀平衡树，就可以完成上述转换。平衡树的添加和删除都是 $O(\log n)$ 的，所以添加或者删除一个字符的时间复杂度为 $O(\log n)$。记添加和删除的总字符数为 $N$，那么这一部分总的时间复杂度为 $O(N \log n)$。

对于操作 3，$t$ 的出现次数等于以 $t$ 为前缀的后缀数量，而以 $t$ 为前缀的后缀数量等于其后继的排名减去其前驱的排名。在 $t$ 后面加入一个极大的字符，就可以构造出 $t$ 的一个后继。将 $t$ 的最后一个字符减小 1，就可以构造出 $t$ 的一个前驱。

现在要查询某一个串 $t$ 在后缀平衡树中排名，由于不能保证 $t$ 在后缀平衡树中出现过，所以每次只能暴力比较字符串大小。单次比较的时间复杂度为 $O(|t|)$，每次查询至多比较 $O(\log n)$ 次，所以单次查询的复杂度为 $O(|t|\log n)$。记所有询问串的长度和为 $L$，那么这一部分总的时间复杂度为 $O(L \log n)$。

??? note "SGT版本的参考代码"
    ```cpp
    #include <bits/stdc++.h>
    using namespace std;
    
    const int N = 8e5 + 5;
    const double INF = 1e18;
    
    void decode(char* s, int len, int mask) {
      for (int i = 0; i < len; ++i) {
        mask = (mask * 131 + i) % len;
        swap(s[i], s[mask]);
      }
    }
    
    int q, n, na;
    char a[N], t[N];
    
    // SuffixBST(SGT Ver)
    
    // 顺序加入，查询时将询问串翻转
    // 以i结束的前缀，对应节点的编号为i
    // 注意：不能写懒惰删除，否则可能会破坏树的结构
    const double alpha = 0.75;
    int root;
    int sz[N], L[N], R[N];
    double tag[N];
    int buffer_size, buffer[N];
    
    bool cmp(int x, int y) {
      if (t[x] != t[y]) return t[x] < t[y];
      return tag[x - 1] < tag[y - 1];
    }
    
    void init() { root = 0; }
    
    void new_node(int& rt, int p, double lv, double rv) {
      rt = p;
      sz[rt] = 1;
      tag[rt] = (lv + rv) / 2;
      L[rt] = R[rt] = 0;
    }
    
    void push_up(int x) {
      if (!x) return;
      sz[x] = sz[L[x]] + 1 + sz[R[x]];
    }
    
    bool balance(int rt) { return alpha * sz[rt] > max(sz[L[rt]], sz[R[rt]]); }
    
    void flatten(int rt) {
      if (!rt) return;
      flatten(L[rt]);
      buffer[++buffer_size] = rt;
      flatten(R[rt]);
    }
    
    void build(int& rt, int l, int r, double lv, double rv) {
      if (l > r) {
        rt = 0;
        return;
      }
      int mid = (l + r) >> 1;
      double mv = (lv + rv) / 2;
    
      rt = buffer[mid];
      tag[rt] = mv;
      build(L[rt], l, mid - 1, lv, mv);
      build(R[rt], mid + 1, r, mv, rv);
      push_up(rt);
    }
    
    void rebuild(int& rt, double lv, double rv) {
      buffer_size = 0;
      flatten(rt);
      build(rt, 1, buffer_size, lv, rv);
    }
    
    void insert(int& rt, int p, double lv, double rv) {
      if (!rt) {
        new_node(rt, p, lv, rv);
        return;
      }
    
      if (cmp(p, rt))
        insert(L[rt], p, lv, tag[rt]);
      else
        insert(R[rt], p, tag[rt], rv);
    
      push_up(rt);
      if (!balance(rt)) rebuild(rt, lv, rv);
    }
    
    void remove(int& rt, int p, double lv, double rv) {
      if (!rt) return;
    
      if (rt == p) {
        if (!L[rt] || !R[rt]) {
          rt = (L[rt] | R[rt]);
        } else {
          // 找到rt的前驱来替换rt
          int nrt = L[rt], fa = rt;
          while (R[nrt]) {
            fa = nrt;
            sz[fa]--;
            nrt = R[nrt];
          }
          if (fa == rt) {
            R[nrt] = R[rt];
          } else {
            L[nrt] = L[rt];
            R[nrt] = R[rt];
            R[fa] = 0;
          }
          rt = nrt;
          tag[rt] = (lv + rv) / 2;
        }
      } else {
        double mv = (lv + rv) / 2;
        if (cmp(p, rt))
          remove(L[rt], p, lv, mv);
        else
          remove(R[rt], p, mv, rv);
      }
    
      push_up(rt);
      if (!balance(rt)) rebuild(rt, lv, rv);
    }
    
    bool cmp1(char* s, int len, int p) {
      for (int i = 1; i <= len; ++i, --p) {
        if (s[i] < t[p]) return true;
        if (s[i] > t[p]) return false;
      }
    }
    
    int query(int rt, char* s, int len) {
      if (!rt) return 0;
      if (cmp1(s, len, rt))
        return query(L[rt], s, len);
      else
        return sz[L[rt]] + 1 + query(R[rt], s, len);
    }
    
    void solve(int Case) {
      n = 0;
      scanf("%d", &q);
      init();
    
      scanf("%s", a + 1);
      na = strlen(a + 1);
      for (int i = 1; i <= na; ++i) {
        t[++n] = a[i];
        insert(root, n, 0, INF);
      }
    
      int mask = 0;
      char op[10];
      for (int i = 1; i <= q; ++i) {
        scanf("%s", op);
        if (op[0] == 'A') {
          scanf("%s", a + 1);
          na = strlen(a + 1);
          decode(a + 1, na, mask);
    
          for (int i = 1; i <= na; ++i) {
            t[++n] = a[i];
            insert(root, n, 0, INF);
          }
        } else if (op[0] == 'D') {
          int x;
          scanf("%d", &x);
          while (x) {
            remove(root, n, 0, INF);
            --n;
            --x;
          }
        } else if (op[0] == 'Q') {
          scanf("%s", a + 1);
          na = strlen(a + 1);
          decode(a + 1, na, mask);
    
          reverse(a + 1, a + 1 + na);
    
          a[na + 1] = 'Z' + 1;
          a[na + 2] = 0;
          int ans = query(root, a, na + 1);
    
          --a[na];
          ans -= query(root, a, na + 1);
    
          printf("%d\n", ans);
          mask ^= ans;
        }
      }
    }
    
    int main() {
      int T = 1;
      // cin >> T;
      for (int i = 1; i <= T; ++i) solve(i);
      return 0;
    }
    ```

## 参考资料

[^1]: 陈立杰 -《重量平衡树和后缀平衡树在信息学奥赛中的应用》
