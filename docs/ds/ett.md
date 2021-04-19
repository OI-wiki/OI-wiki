一般提到动态树，我们会不约而同的想到 LCT，这算是比较通用，实用，能力较为广泛的一种写法了。当然，掌握 LCT 就需要熟悉掌握 Splay 和各种操作和知识。ETT（中文常用称呼：欧拉游览树）是一种及其睿智且暴力，可以用暴力数据结构维护的一种除了能胜任普通动态树的 Link & Cut 操作还可以支持换子树操作（此操作 LCT 无法完成）的动态树。

大家对这括号序很熟悉吧，如：

![](./images/ett1.png)

其括号序为：`1 2 5 5 6 6 2 3 3 4 7 8 8 7 4 1`。

括号序其实是一个父亲包含儿子的一种树的顺序。

然后我们看一下，如果把 `4` 的子树移给 `3` 会怎样？如图：

![](./images/ett2.png)

原图括号序：`1 2 5 5 6 6 2 3 3 4 7 8 8 7 4 1`

后者括号序：`1 2 5 5 6 6 2 3 7 8 8 7 3 4 4 1`

可以发现，`7 8 8 7` 平移到了 `3` 的后面，而 `4` 合拢。这就是所谓换子树操作（同样可以用于 Link & Cut 操作）。现在只需要一个数据结构可以做到区间平移且维护一些值，众大佬肯定会说用 Splay，其确实效率很高，不过这里用块状链表维护会简单很多，对于一些数据低于 $2 \times 10^5$ 的题目都可以码得很快。

那怎么维护点到根的信息呢？

其实仔细想想，DFS 序也可以达到平移的效果，那么为什么需要括号序？其实，假如你要查询图中 `1` 到 `8` 的和，那么你从括号序中 `1` 到 `8`（第一个出现的）中出现两次的数的贡献抹去。如果维护的是 xor，那么直接 xor 两次即可。如果维护的是 sum，那么第一个出现的数字的贡献为正，第二个为负，然后用块状链表维护区间和即可。

用块状链表后除了单点修改是 $O(1)$ 外其他都是 $O(n^{\frac{1}{2}})$ 的。

ETT 不支持换根操作。对于链（区间）修改，分为两种情况，一是贡献相同（如 xor）是可以的，二是贡献不同（如 sum）是不行的。现在的主流做法毕竟是 LCT，所以这些操作比较多，在避开这种操作的情况下运用这种做法还是不错的。

注：标准的 ETT（用欧拉回路而不是 DFS 括号序实现）是支持换根操作的，但是实现较为复杂。

??? "例题 [星系探索](https://darkbzoj.tk/problem/3786) 参考代码"
    ```cpp
    /*
    虽然上文提到过块状链表实现 ETT
    在某些情况下可能较简单，但对于此题块状链表复杂度有可能无法通过而且实现较繁琐，所以这份代码采用
    FHQ Treap 实现。
    */
    #include <bits/stdc++.h>
    #define N 1000000
    #define int long long
    using namespace std;
    /*FHQ TREAP*/
    int rt, tot, f[N], rnd[N], ls[N], rs[N], siz[N], tag[N], val[N], sum[N], pd[N],
        pds[N];
    void pushup(int x) {
      siz[x] = siz[ls[x]] + siz[rs[x]] + 1;
      sum[x] = sum[ls[x]] + sum[rs[x]] + val[x];
      pds[x] = pds[ls[x]] + pds[rs[x]] + pd[x];
    }
    void link(int x, int c, int y) {
      if (c)
        rs[x] = y;
      else
        ls[x] = y;
      if (y) f[y] = x;
      pushup(x);
    }
    int newNode(int x, int y) {
      siz[++tot] = 1;
      val[tot] = sum[tot] = x;
      pd[tot] = pds[tot] = y;
      rnd[tot] = rand();
      return tot;
    }
    void setTag(int x, int v) {
      tag[x] += v;
      sum[x] += v * pds[x];
      val[x] += v * pd[x];
    }
    void pushdown(int x) {
      if (ls[x]) setTag(ls[x], tag[x]);
      if (rs[x]) setTag(rs[x], tag[x]);
      tag[x] = 0;
    }
    void split(int now, int k, int &x, int &y) {
      f[now] = 0;
      if (!now) {
        x = y = 0;
        return;
      }
      pushdown(now);
      if (siz[ls[now]] + 1 <= k) {
        x = now;
        split(rs[now], k - siz[ls[now]] - 1, rs[x], y);
        link(x, 1, rs[x]);
      } else {
        y = now;
        split(ls[now], k, x, ls[y]);
        link(y, 0, ls[y]);
      }
    }
    int merge(int x, int y) {
      if (!x || !y) return x | y;
      if (rnd[x] < rnd[y]) {
        pushdown(x);
        link(x, 1, merge(rs[x], y));
        return x;
      } else {
        pushdown(y);
        link(y, 0, merge(x, ls[y]));
        return y;
      }
    }
    int rnk(int x) {
      int c = 1, ans = 0;
      while (x) {
        if (c) ans += siz[ls[x]] + 1;
        c = (rs[f[x]] == x);
        x = f[x];
      }
      return ans;
    }
    /*ETT*/
    int s[N], e[N];
    void add(int x, int v) {
      int a, b, c;
      split(rt, rnk(s[x]) - 1, a, b);
      split(b, rnk(e[x]) - rnk(s[x]) + 1, b,
            c);  //这里 b 是我们要进行操作的子树的括号序列。
      setTag(b, v);
      rt = merge(merge(a, b), c);
    }
    int query(int x) {
      int a, b;
      split(rt, rnk(s[x]), a, b);
      int ans = sum[a];
      rt = merge(a, b);
      return ans;
    }
    void changeFa(int x, int y) {
      int a, b, c, d;
      split(rt, rnk(s[x]) - 1, a, b);
      split(b, rnk(e[x]) - rnk(s[x]) + 1, b, c);
      a = merge(
          a,
          c);  //因为我们确定不了要设置为父亲的节点在括号序列中的哪边，所以先把两边合并。
      split(a, rnk(s[y]), a, d);
      rt = merge(merge(a, b), d);  //把要进行操作的子树放在父亲括号序列的最前面。
    }
    /*main function*/
    int n, m, w[N];
    vector<int> v[N];
    void dfs(int x) {
      rt = merge(rt, s[x] = newNode(w[x], 1));
      for (auto to : v[x]) dfs(to);
      rt = merge(rt, e[x] = newNode(-w[x], -1));
    }
    signed main() {
      cin >> n;
      for (int i = 2; i <= n; i++) {
        int f;
        cin >> f;
        v[f].push_back(i);
      }
      for (int i = 1; i <= n; i++) cin >> w[i];
      dfs(1);
      cin >> m;
      for (int i = 1; i <= m; i++) {
        char c;
        cin >> c;
        if (c == 'Q') {
          int d;
          cin >> d;
          cout << query(d) << endl;
        } else if (c == 'C') {
          int x, y;
          cin >> x >> y;
          changeFa(x, y);
        } else {
          int p, q;
          cin >> p >> q;
          add(p, q);
        }
      }
      return 0;
    }
    ```
