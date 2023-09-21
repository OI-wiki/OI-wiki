## 线段树与离线询问

线段树与离线询问结合的问题在 OI 领域也有出现。

假设一个数据结构，允许以 $O(T(n))$ 的时间复杂度添加元素。本文描述一种允许以 $O(T(n)\log n)$ 的时间复杂度进行离线删除的技术。

### 算法

从被添加开始到被删除结束，每个元素都在数据结构中存活一段时间。

在查询上构建一个线段树。元素处于活动状态的线段将拆分变为树的 $O(\log n)$ 节点。查询有关结构的信息时，将每个查询放入相应的叶节点中。

为了处理所有查询，在段树上运行深度优先搜索。进入节点时，添加该节点中的所有元素。然后进一步查找该节点的子节点，如果该节点是叶节点则回答查询。离开节点时撤消添加。

如果更改结构的时间复杂度为 $O(T(n))$，可以通过设置一个栈保留更改，以 $O(T(n))$ 的时间复杂度回滚。回滚不维持均摊复杂度。

### 注意

当某个对象处于活动状态时，在线段上创建线段树的想法不仅适用于数据结构问题。

### 实现

此实现用于动态连接问题。它可以添加边、删除边和计算连接的零部件数量。

```cpp
struct dsu_save {
  int v, rnkv, u, rnku;

  dsu_save() {}

  dsu_save(int _v, int _rnkv, int _u, int _rnku)
      : v(_v), rnkv(_rnkv), u(_u), rnku(_rnku) {}
};

struct dsu_with_rollbacks {
  vector<int> p, rnk;
  int comps;
  stack<dsu_save> op;

  dsu_with_rollbacks() {}

  dsu_with_rollbacks(int n) {
    p.resize(n);
    rnk.resize(n);
    for (int i = 0; i < n; i++) {
      p[i] = i;
      rnk[i] = 0;
    }
    comps = n;
  }

  int find_set(int v) { return (v == p[v]) ? v : find_set(p[v]); }

  bool unite(int v, int u) {
    v = find_set(v);
    u = find_set(u);
    if (v == u) return false;
    comps--;
    if (rnk[v] > rnk[u]) swap(v, u);
    op.push(dsu_save(v, rnk[v], u, rnk[u]));
    p[v] = u;
    if (rnk[u] == rnk[v]) rnk[u]++;
    return true;
  }

  void rollback() {
    if (op.empty()) return;
    dsu_save x = op.top();
    op.pop();
    comps++;
    p[x.v] = x.v;
    rnk[x.v] = x.rnkv;
    p[x.u] = x.u;
    rnk[x.u] = x.rnku;
  }
};

struct query {
  int v, u;
  bool united;

  query(int _v, int _u) : v(_v), u(_u) {}
};

struct QueryTree {
  vector<vector<query>> t;
  dsu_with_rollbacks dsu;
  int T;

  QueryTree() {}

  QueryTree(int _T, int n) : T(_T) {
    dsu = dsu_with_rollbacks(n);
    t.resize(4 * T + 4);
  }

  void add_to_tree(int v, int l, int r, int ul, int ur, query& q) {
    if (ul > ur) return;
    if (l == ul && r == ur) {
      t[v].push_back(q);
      return;
    }
    int mid = (l + r) / 2;
    add_to_tree(2 * v, l, mid, ul, min(ur, mid), q);
    add_to_tree(2 * v + 1, mid + 1, r, max(ul, mid + 1), ur, q);
  }

  void add_query(query q, int l, int r) { add_to_tree(1, 0, T - 1, l, r, q); }

  void dfs(int v, int l, int r, vector<int>& ans) {
    for (query& q : t[v]) {
      q.united = dsu.unite(q.v, q.u);
    }
    if (l == r)
      ans[l] = dsu.comps;
    else {
      int mid = (l + r) / 2;
      dfs(2 * v, l, mid, ans);
      dfs(2 * v + 1, mid + 1, r, ans);
    }
    for (query q : t[v]) {
      if (q.united) dsu.rollback();
    }
  }

  vector<int> solve() {
    vector<int> ans(T);
    dfs(1, 0, T - 1, ans);
    return ans;
  }
};
```

**本页面主要译自博文 [Deleting from a data structure](https://cp-algorithms.com/data_structures/deleting_in_log_n.html)，版权协议为 CC-BY-SA 4.0。**

### 习题

[Codeforces - Connect and Disconnect](https://codeforces.com/gym/100551/problem/A)

[Codeforces - Addition on Segments](https://codeforces.com/contest/981/problem/E)

[Codeforces - Extending Set of Points](https://codeforces.com/contest/1140/problem/F)
