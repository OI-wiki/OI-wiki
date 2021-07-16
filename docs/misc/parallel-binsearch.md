## 引子

在信息学竞赛中，有一部分题可以使用二分的办法来解决。但是当这种题目有多次询问且每次询问我们对每个查询都直接二分，可能会收获一个 TLE。这时候我们就会用到整体二分。整体二分的主体思路就是把多个查询一起解决。（所以这是一个离线算法）

> 可以使用整体二分解决的题目需要满足以下性质：
>
> 1. 询问的答案具有可二分性
>
> 2. **修改对判定答案的贡献互相独立**，修改之间互不影响效果
>
> 3. 修改如果对判定答案有贡献，则贡献为一确定的与判定标准无关的值
>
> 4. 贡献满足交换律，结合律，具有可加性
>
> 5.  题目允许使用离线算法
>
>     ——许昊然《浅谈数据结构题几个非经典解法》

## 思路

记 $[l,r]$ 为答案的值域，$[L,R]$ 为答案的定义域。（也就是说求答案时仅考虑下标在区间 $[L,R]$ 内的操作和询问，这其中询问的答案在 $[l,r]$ 内）

- 我们首先把所有操作 **按时间顺序** 存入数组中，然后开始分治。
- 在每一层分治中，利用数据结构（常见的是树状数组）统计当前查询的答案和 $mid$ 之间的关系。
- 根据查询出来的答案和 $mid$ 间的关系（小于等于 $mid$ 和大于 $mid$）将当前处理的操作序列分为 $q1$ 和 $q2$ 两份，并分别递归处理。
- 当 $l=r$ 时，找到答案，记录答案并返回即可。

需要注意的是，在整体二分过程中，若当前处理的值域为 $[l,r]$，则此时最终答案范围不在 $[l,r]$ 的询问会在其他时候处理。

## 详解

注：

1. 为可读性，文中代码或未采用实际竞赛中的常见写法。
2.  若觉得某段代码有难以理解之处，请先参考之前题目的解释，
    因为节省篇幅解释过的内容不再赘述。

从普通二分说起：

### 查询第 k 小：一次二分多个询问

> **题 1** 在一个数列中查询第 $k$ 小的数。

当然可以直接排序。如果用二分法呢？可以用数据结构记录每个大小范围内有多少个数，然后用二分法猜测，利用数据结构检验。

> **题 2** 在一个数列中多次查询第 $k$ 小的数。

可以对于每个询问进行一次二分；但是，也可以把所有的询问放在一起二分。

先考虑二分的本质：假设要猜一个 $[l,r]$ 之间的数，猜测之后会知道是猜大了，猜小了还是刚好。当然可以从 $l$ 枚举到 $r$，但更优秀的方法是二分：猜测答案是 $m = \lfloor\frac{l + r}{2}\rfloor$，然后去验证 $m$ 的正确性，再调整边界。这样做每次询问的复杂度为 $O(n\log n)$，若询问次数为 $q$，则时间复杂度为 $O(qn\log n)$。

回过头来，对于当前的所有询问，可以去猜测所有询问的答案都是 $mid$，然后去依次验证每个询问的答案应该是小于等于 $mid$ 的还是大于 $mid$ 的，并将询问分为两个部分（不大于/大于），对于每个部分继续二分。注意：如果一个询问的答案是大于 $mid$ 的，则在将其划至右侧前需更新它的 $k$，即，如果当前数列中小于等于 $mid$ 的数有 $t$ 个，则将询问划分后实际是在右区间询问第 $k - t$ 小数。如果一个部分的 $l = r$ 了，则结束这个部分的二分。利用线段树的相关知识，我们每次将整个答案可能在的区间 $[1,maxans]$ 划分成了若干个部分，这样的划分共进行了 $O(\log maxans)$ 次，一次划分会将整个操作序列操作一次。若对整个序列进行操作，并支持对应的查询的时间复杂度为 $O(T)$，则整体二分的时间复杂度为 $O(T\log n)$。

试试完成以下代码：

```cpp
struct Query {
  int id, k;  // 这个询问的编号, 这个询问的k
};
int ans[N];        // ans[i] 表示编号为i的询问的答案
int check(int x);  // 返回原数列中小于等于x的数的个数
void solve(int l, int r, vector<Query> q)
// 请补全这个函数
{
  int m = (l + r) / 2;
  vector<Query> q1, q2;  // 将被划到左侧的询问和右侧的询问
  if (l == r) {
    // ...
    return;
  }
  // ...
  solve(l, m, q1), solve(m + 1, r, q2);
  return;
}
```

参考代码如下

```cpp
void solve(int l, int r, vector<Query> q) {
  int m = (l + r) / 2;
  if (l == r) {
    for (unsigned i = 0; i < q.size(); i++) ans[q[i].id] = l;
    return;
  }
  vector<int> q1, q2;
  for (unsigned i = 0; i < q.size(); i++)
    if (q[i].k <= check(m))
      q1.push_back(q[i]);
    else
      q[i].k -= check(m), q2.push_back(q[i]);
  solve(l, m, q1), solve(m + 1, r, q2);
  return;
}
```

### 区间查询第 k 小：对只询问指定区间的处理

> **题 3** 在一个数列中多次查询区间第 $k$ 小的数。

涉及到给定区间的查询，再按之前的方法进行二分就会导致 `check` 函数的时间复杂度爆炸。仍然考虑询问与值域中点 $m$ 的关系：若询问区间内小于等于 $m$ 的数有 $t$ 个，询问的是区间内的 $k$ 小数，则当 $k \leq t$ 时，答案应小于等于 $m$；否则，答案应大于 $m$。（注意边界问题）此处需记录一个区间小于等于指定数的数的数量，即单点加，求区间和，可用树状数组快速处理。为提高效率，只对数列中值在值域区间 $[l,r]$ 的数进行统计，即，在进一步递归之前，不仅将询问划分，将当前处理的数按值域范围划为两半。

参考代码（关键部分）

```cpp
struct Num {
  int p, x;
};  // 位于数列中第 p 项的数的值为 x
struct Query {
  int l, r, k, id;
};  // 一个编号为 id, 询问 [l,r] 中第 k 小数的询问
int ans[N];
void add(int p, int x);  // 树状数组, 在 p 位置加上 x
int query(int p);        // 树状数组, 求 [1,p] 的和
void clear();            // 树状数组, 清空
void solve(int l, int r, vector<Num> a, vector<Query> q)
// a中为给定数列中值在值域区间 [l,r] 中的数
{
  int m = (l + r) / 2;
  if (l == r) {
    for (unsigned i = 0; i < q.size(); i++) ans[q[i].id] = l;
    return;
  }
  vector<Num> a1, a2;
  vector<Query> q1, q2;
  for (unsigned i = 0; i < a.size(); i++)
    if (a[i].x <= m)
      a1.push_back(a[i]), add(a[i].p, 1);
    else
      a2.push_back(a[i]);
  for (unsigned i = 0; i < q.size(); i++) {
    int t = query(q[i].r) - query(q[i].l - 1);
    if (q[i].k <= t)
      q1.push_back(q[i]);
    else
      q[i].k -= t, q2.push_back(q[i]);
  }
  clear();
  solve(l, m, a1, q1), solve(m + 1, r, a2, q2);
  return;
}
```

下面提供 [【模板】可持久化线段树 2（主席树）](https://www.luogu.com.cn/problem/P3834) 一题使用整体二分的，偏向竞赛风格的写法。

???+note "参考代码"
    ```cpp
    #include <bits/stdc++.h>
    using namespace std;
    const int N = 200020;
    const int INF = 1e9;
    int n, m;
    int ans[N];
    // BIT begin
    int t[N];
    int a[N];
    int sum(int p) {
      int ans = 0;
      while (p) {
        ans += t[p];
        p -= p & (-p);
      }
      return ans;
    }
    void add(int p, int x) {
      while (p <= n) {
        t[p] += x;
        p += p & (-p);
      }
    }
    // BIT end
    int tot = 0;
    struct Query {
      int l, r, k, id, type;  // set values to -1 when they are not used!
    } q[N * 2], q1[N * 2], q2[N * 2];
    void solve(int l, int r, int ql, int qr) {
      if (ql > qr) return;
      if (l == r) {
        for (int i = ql; i <= qr; i++)
          if (q[i].type == 2) ans[q[i].id] = l;
        return;
      }
      int mid = (l + r) / 2, cnt1 = 0, cnt2 = 0;
      for (int i = ql; i <= qr; i++) {
        if (q[i].type == 1) {
          if (q[i].l <= mid) {
            add(q[i].id, 1);
            q1[++cnt1] = q[i];
          } else
            q2[++cnt2] = q[i];
        } else {
          int x = sum(q[i].r) - sum(q[i].l - 1);
          if (q[i].k <= x)
            q1[++cnt1] = q[i];
          else {
            q[i].k -= x;
            q2[++cnt2] = q[i];
          }
        }
      }
      // rollback changes
      for (int i = 1; i <= cnt1; i++)
        if (q1[i].type == 1) add(q1[i].id, -1);
      // move them to the main array
      for (int i = 1; i <= cnt1; i++) q[i + ql - 1] = q1[i];
      for (int i = 1; i <= cnt2; i++) q[i + cnt1 + ql - 1] = q2[i];
      solve(l, mid, ql, cnt1 + ql - 1);
      solve(mid + 1, r, cnt1 + ql, qr);
    }
    pair<int, int> b[N];
    int toRaw[N];
    int main() {
      scanf("%d%d", &n, &m);
      // read and discrete input data
      for (int i = 1; i <= n; i++) {
        int x;
        scanf("%d", &x);
        b[i].first = x;
        b[i].second = i;
      }
      sort(b + 1, b + n + 1);
      int cnt = 0;
      for (int i = 1; i <= n; i++) {
        if (b[i].first != b[i - 1].first) cnt++;
        a[b[i].second] = cnt;
        toRaw[cnt] = b[i].first;
      }
      for (int i = 1; i <= n; i++) {
        q[++tot] = {a[i], -1, -1, i, 1};
      }
      for (int i = 1; i <= m; i++) {
        int l, r, k;
        scanf("%d%d%d", &l, &r, &k);
        q[++tot] = {l, r, k, i, 2};
      }
      solve(0, cnt + 1, 1, tot);
      for (int i = 1; i <= m; i++) printf("%d\n", toRaw[ans[i]]);
    }
    ```

### 带修区间第 k 小：整体二分的完整运用

> **题 4**  [Dynamic Rankings](http://acm.zju.edu.cn/onlinejudge/showProblem.do?problemCode=2112) 给定一个数列，要支持单点修改，区间查第 $k$ 小。

修改操作可以直接理解为从原数列中删去一个数再添加一个数，为方便起见，将询问和修改统称为“操作”。因后面的操作会依附于之前的操作，不能如题 3 一样将统计和处理询问分开，故可将所有操作存于一个数组，用标识区分类型，依次处理每个操作。为便于处理树状数组，修改操作可分拆为擦除操作和插入操作。

**优化**

1. 注意到每次对于操作进行分类时，只会更改操作顺序，故可直接在原数组上操作。具体实现，在二分时将记录操作的 $q, a$ 数组换为一个大的全局数组，二分时记录信息变为 $L, R$，即当前处理的操作是全局数组上的哪个区间。利用临时数组记录当前的分类情况，进一步递归前将临时数组信息写回原数组。
2. 树状数组每次清空会导致时间复杂度爆炸，可采用每次使用树状数组时记录当前修改位置（这已由 1 中提到的临时数组实现），本次操作结束后在原位置加 $-1$ 的方法快速清零。
3. 一开始对于数列的初始化操作可简化为插入操作。

关键部分参考代码

```cpp
struct Opt {
  int x, y, k, type, id;
  // 对于询问, type = 1, x, y 表示区间左右边界, k 表示询问第 k 小
  // 对于修改, type = 0, x 表示修改位置, y 表示修改后的值,
  // k 表示当前操作是插入(1)还是擦除(-1), 更新树状数组时使用.
  // id 记录每个操作原先的编号, 因二分过程中操作顺序会被打散
};
Opt q[N], q1[N], q2[N];
// q 为所有操作,
// 二分过程中, 分到左边的操作存到 q1 中, 分到右边的操作存到 q2 中.
int ans[N];
void add(int p, int x);
int query(int p);  // 树状数组函数, 含义见题3
void solve(int l, int r, int L, int R)
// 当前的值域范围为 [l,r], 处理的操作的区间为 [L,R]
{
  if (l > r || L > R) return;
  int cnt1 = 0, cnt2 = 0, m = (l + r) / 2;
  // cnt1, cnt2 分别为分到左边, 分到右边的操作数
  if (l == r) {
    for (int i = L; i <= R; i++)
      if (q[i].type == 1) ans[q[i].id] = l;
    return;
  }
  for (int i = L; i <= R; i++)
    if (q[i].type == 1) {  // 是询问: 进行分类
      int t = query(q[i].y) - query(q[i].x - 1);
      if (q[i].k <= t)
        q1[++cnt1] = q[i];
      else
        q[i].k -= t, q2[++cnt2] = q[i];
    } else
        // 是修改: 更新树状数组 & 分类
        if (q[i].y <= m)
      add(q[i].x, q[i].k), q1[++cnt1] = q[i];
    else
      q2[++cnt2] = q[i];
  for (int i = 1; i <= cnt1; i++)
    if (q1[i].type == 0) add(q1[i].pos, -q1[i].k);  // 清空树状数组
  for (int i = 1; i <= cnt1; i++) q[L + i - 1] = q1[i];
  for (int i = 1; i <= cnt2; i++)
    q[L + cnt1 + i - 1] = q2[i];  // 将临时数组中的元素合并回原数组
  solve(l, m, L, L + cnt1 - 1), solve(m + 1, r, L + cnt1, R);
  return;
}
```

### 参考习题

[「国家集训队」矩阵乘法](https://www.luogu.com.cn/problem/P1527)

[「POI2011 R3 Day2」流星 Meteors](https://loj.ac/problem/2169)

## 参考资料

- 许昊然《浅谈数据结构题几个非经典解法》
