## 引入

[P6466 分散层叠算法（Fractional Cascading)](https://www.luogu.com.cn/problem/P6466)

考虑 $k$ 个长度为 $n$ 有序序列 $l_1 \dots l_n$，$q$ 次询问，每次给出一个数 $x$，询问 $x$ 在这些序列中的非严格后缀。

暴力做法是每个序列分别二分，时间复杂度 $\mathcal O(qk\log n)$。而分散层叠可以把复杂度优化为 $\mathcal O(q(k+\log n))$。

考虑建立 $k$ 个新序列 $M_1\dots M_k$，定义为 $M_k=l_k$，其余按照如下方法构造：

> $M_i$ 为 $M_{i+1}$ 的偶数项与 $l_i$ 归并排序后的序列。

举个例子：

    l1:1 4 5 8 9             M1:1 3 4 5 7 8 9
    l2:2 3 6 7 10            M2:2 3 6 7 10

考虑计算空间复杂度。$M_k$ 的长度为 $n$，$M_i(i<k)$ 的长度为 $\frac{M_{i+1}}{2}+n$。考虑设 $A_i$ 为 $M_{k-i+1}$ 的长度，则 $A_i=(2-\frac{1}{2^i})n$，当 $i$ 很大时 $A_i$ 趋近于 $2n$，所以空间复杂度依然是 $\mathcal O(nk)$。

归并的时候，我们可以顺便记下 $M_i$ 中的每个数在 $l_i$ 和 $M_{i+1}$ 中的后继。

对于每次询问，我们首先二分出 $x$ 在 $M_1$ 中的后继 $y$，则 $x\le y$。

### 引理 1：$y$ 在 $l_1$ 中的后继一定是 $x$ 在 $l_1$ 中的后继。

> 证明：若 $y$ 在 $l_1$ 中出现过，$y$ 的后继就是 $y$，显然成立。若 $y$ 不在 $l_1$ 中，$y$ 在 $l_1$ 中的后继就是 $x$ 在 $l_1$ 中的后继。

不难发现本条对任意 $l_i(1\le i\le k)$ 均成立。

### 引理 2：$y$ 在 $M_2$ 中的后继与 $x$ 在 $M_2$ 的后继下标差不超过 $2$。

> 证明：因为我们从 $M_2$ 中每两个数就选取一个加入 $M_1$，所以 $x$ 在 $M_2$ 的后继 $p$ 和 $x$ 在 $M_2$ 的后继的后继 $q$ 必定有一个加入了 $M_1$。（在 $M_2$ 中 $\ge x$ 的数 $< 2$ 个的情况下显然成立）因此 $x\le y\le q$，最极端情况下 $y=q$，此时 $y$ 在 $M_2$ 中的后继就是 $q$ 的后继，与 $x$ 的后继下标差为 $2$。

推广：

> “如果我们建立分散层叠时选取的比例为 $\frac{1}{r}$（本题 $r=2$），那么 $x$ 在 $M_i$ 中二分查找的结果（即 $y$）指向的 $M_{i+1}$ 的位置和 $x$ 在 $M_{i+1}$ 中二分查找的正确结果的距离不会超过 $r$。因为 $r$ 是一个常数，所以可以在 $\mathcal O(1)$ 的时间复杂度内求出 $x$ 在 $M_{i+1}$ 中二分查找的正确结果。”

那么做法就很明显了，我们二分出 $y$ 后，每次找到 $y$ 在 $l_i$ 中的后继（这个在归并时就已经处理好，可以 $\mathcal O(1)$ 查询）作为答案，然后从 $y$ 跳到 $y$ 在 $M_{i+1}$ 中的后继，然后暴力把这个位置调整为 $x$ 在 $M_{i+1}$ 中的后继，已经证明最多只会调整两次，把这个后继记为 $y'$，重复上面步骤即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define maxk 110
#define maxn 20010
int T;
int n, k, q, d;
int a[maxk][maxn];
int len[maxk];
int M[maxk][maxn];
int asuf[maxk][maxn];
int Msuf[maxk][maxn];
int tM[maxn], Mlim;

void fractional_cascading() {
  for (int i = 1; i <= n; i++)
    M[k][i] = a[k][i], asuf[k][i] = i, Msuf[k][i] = i;
  len[k] = n;
  for (int i = k - 1; i >= 1; i--) {
    // 归并
    int p1 = 1, p2 = 1;
    Mlim = 0;
    len[i] = len[i + 1] / 2 + n;
    for (int j = 2; j <= len[i + 1]; j += 2) {
      tM[++Mlim] = M[i + 1][j];
    }
    while (p1 + p2 <= len[i] + 1) {
      while (p1 < n + 1 && p2 == Mlim + 1) {
        M[i][p1 + p2 - 1] = a[i][p1];
        Msuf[i][p1 + p2 - 1] = len[i + 1];
        asuf[i][p1 + p2 - 1] = (p1 == n ? n : p1 + 1);
        ++p1;
      }
      while (p2 < Mlim + 1 && p1 == n + 1) {
        M[i][p1 + p2 - 1] = tM[p2];
        Msuf[i][p1 + p2 - 1] = (p2 == Mlim ? len[i + 1] : (p2 + 1) * 2);
        asuf[i][p1 + p2 - 1] = n;
        ++p2;
      }
      if (p1 < n + 1 && p2 < Mlim + 1) {
        if (a[i][p1] < tM[p2]) {
          M[i][p1 + p2 - 1] = a[i][p1];
          Msuf[i][p1 + p2 - 1] = p2 * 2;
          asuf[i][p1 + p2 - 1] = p1;
          ++p1;
        } else {
          M[i][p1 + p2 - 1] = tM[p2];
          Msuf[i][p1 + p2 - 1] = p2 * 2;
          asuf[i][p1 + p2 - 1] = p1;
          ++p2;
        }
      }
    }
  }
}

int x;
int lans;

int main() {
  cin >> n >> k >> q >> d;
  for (int i = 1; i <= k; i++) {
    for (int j = 1; j <= n; j++) {
      cin >> a[i][j];
    }
  }
  fractional_cascading();
  for (int i = 1; i <= q; i++) {
    cin >> x;
    x ^= lans;
    int res = 0;
    int pos = lower_bound(M[1] + 1, M[1] + len[1] + 1, x) - M[1];
    res ^= a[1][asuf[1][pos]];
    for (int i = 2; i <= k; i++) {
      pos = Msuf[i - 1][pos];
      while (M[i][pos] < x && pos < len[i]) ++pos;
      while (M[i][pos] >= x && M[i][pos - 1] >= x && pos > 1) --pos;
      if (a[i][asuf[i][pos]] >= x) res ^= a[i][asuf[i][pos]];
    }
    lans = res;
    if (i % d == 0) cout << res << '\n';
  }
  return 0;
}

```

## 应用

分散层叠目前主要用于优化分块问题。

### [#6278. 数列分块入门 2](https://loj.ac/p/6278)：

区间加，区间查询 $\le x$ 的数的个数。

绝大部分解法都是 $\mathcal O(n\sqrt n\log n)$ 或 $\mathcal O(n\sqrt{n\log n})$ 的，但是其实使用分散层叠能优化为 $\mathcal O(n\sqrt{n\log\log n})$ 甚至 $\mathcal O(n\sqrt n)$。

#### 传统做法

记原数组为 $a$。

考虑分块，设块长为 $B$，块内从小到大排好序，记排序后的数组为 $b$。

对于修改：整块直接打上修改标记，散块先下传标记，然后暴力改区间内的 $a$，把这些 $a$ 对应的 $b$ 拿出来，修改好，跟区间内剩下的 $b$ 做归并，复杂度 $\mathcal O(B+\frac{n}{B})$。

对于查询：散块暴力查询，整块在块内排好序的 $b$ 数组中二分即可。复杂度 $\mathcal O(B+\frac{n}{B}\log B)$。

综上，取块长为 $\sqrt{n\log n}$ 最优，复杂度 $\mathcal O(q\sqrt{n\log n)}$。

#### 单根号做法

建立一棵 $\mathcal O(\frac{n}{B})$ 个叶子的线段树，每个叶子维护一个长度为 $B$ 的有序序列，线段树的非叶子结点维护它两个儿子按 $\frac{1}{r}$ 的比例均匀选取元素归并合成的分散层叠结构。

对于修改：散块的序列暴力修改，然后沿线段树向上更新分散层叠。注意到这里如果令 $r=2$，则每一层的结点维护的序列长度都为 $B$，对散块的修改复杂度为 $\mathcal O(B\log \frac{n}{B})$。但是如果取一个 $>2$ 的数，比如 $r=3$，那么每层结点维护的序列长度都是上一层的 $\frac{2}{3}$，复杂度变为 $\mathcal O((1+\frac{2}{3}+\frac{4}{9}+\dots)B)$，等比数列求和得前面是一个不大于 $3$ 的常数，所以复杂度为 $\mathcal O(B)$。考虑整块，先在线段树上拆成 $\log \frac{n}{B}$ 个区间，每个区间打上标记。由于线段树的性质，整块修改复杂度同样是 $\mathcal O(B)$ 的。

对于查询：散块直接暴力查询。对于整块，因为线段树上的结点数是 $\mathcal O(\frac{n}{B})$ 的，所以我们完全可以在线段树上暴力查询到询问区间的叶子结点。因此我们先在根的 $M$ 数组中二分出 $x$ 的严格前驱 $y$，然后根据 $y$ 来递归左右子树，这个步骤跟模板题是一样的。但是懒标记 `pushdown` 的代价是巨大的，所以我们需要标记永久化。复杂度 $O(\frac{n}{B})$。

综上，取块长为 $\sqrt n$ 时复杂度最优，为 $\mathcal O(n\sqrt n)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define maxn 200010
int n, q;
#define SQRT 520
int a[maxn];
int B;
int bel[maxn];

struct node {
  int yuan, val;
} b[maxn];

int L[maxn], R[maxn];
int tag[SQRT];

struct Segment_Tree {
  int lf[SQRT << 2], rf[SQRT << 2];
  int lsuf[SQRT << 2][SQRT * 3 / 2], rsuf[SQRT << 2][SQRT * 3 / 2],
      M[SQRT << 2][SQRT * 3 / 2], len[SQRT << 2];
  int M1[SQRT * 3 / 2], M2[SQRT * 3 / 2];
  int add_tag[SQRT << 2];

  void pushup(int p) {
    int ls = (p << 1), rs = (p << 1 | 1);
    int p1 = 1, p2 = 1, t1 = 0, t2 = 0;
    for (int j = 1; j <= len[ls]; j += 3) M1[++t1] = M[ls][j];
    for (int j = 1; j <= len[rs]; j += 3) M2[++t2] = M[rs][j];
    len[p] = t1 + t2;
    while (p1 + p2 <= len[p] + 1) {
      while (p1 < t1 + 1 && p2 == t2 + 1) {
        M[p][p1 + p2 - 1] = M1[p1];
        lsuf[p][p1 + p2 - 1] = (p1 == t1 ? t1 : p1 + 1);
        rsuf[p][p1 + p2 - 1] = t2;
        ++p1;
      }
      while (p2 < t2 + 1 && p1 == t1 + 1) {
        M[p][p1 + p2 - 1] = M2[p2];
        lsuf[p][p1 + p2 - 1] = t1;
        rsuf[p][p1 + p2 - 1] = (p2 == t2 ? t2 : p2 + 1);
        ++p2;
      }
      if (p1 < t1 + 1 && p2 < t2 + 1) {
        if (M1[p1] < M2[p2]) {
          M[p][p1 + p2 - 1] = M1[p1];
          lsuf[p][p1 + p2 - 1] = p1;
          rsuf[p][p1 + p2 - 1] = p2;
          ++p1;
        } else {
          M[p][p1 + p2 - 1] = M2[p2];
          lsuf[p][p1 + p2 - 1] = p1;
          rsuf[p][p1 + p2 - 1] = p2;
          ++p2;
        }
      }
    }
    for (int j = 1; j <= len[p]; j++) M[p][j] += add_tag[p];
    for (int j = 1; j <= len[p]; j++)
      lsuf[p][j] = 1 + 3 * (lsuf[p][j] - 1),
      rsuf[p][j] = 1 + 3 * (rsuf[p][j] - 1);
  }

  void build(int p, int l, int r) {
    lf[p] = l, rf[p] = r;
    if (l == r) {
      len[p] = R[l] - L[l] + 1;
      for (int i = L[l]; i <= R[l]; i++) M[p][i - L[l] + 1] = b[i].val;
      return;
    }
    int ls = (p << 1), rs = (p << 1 | 1), mid = (l + r) >> 1;
    build(ls, l, mid);
    build(rs, mid + 1, r);
    pushup(p);
  }

  void push_tag(int p, int v) {
    for (int j = 1; j <= len[p]; j++) M[p][j] += v;
    add_tag[p] += v;
  }

  void modify(int p, int l, int r, int L, int R, int v) {
    if (L > R) return;
    if (L <= l && r <= R) {
      push_tag(p, v);
      return;
    }
    int ls = (p << 1), rs = (p << 1 | 1), mid = (l + r) >> 1;
    if (mid >= L) modify(ls, l, mid, L, R, v);
    if (mid < R) modify(rs, mid + 1, r, L, R, v);
    pushup(p);
  }

  void modify_san(int p, int l, int r, int pos) {
    if (l == r) {
      for (int i = L[l]; i <= R[l]; i++)
        M[p][i - L[l] + 1] = b[i].val + add_tag[p];
      return;
    }
    int ls = (p << 1), rs = (p << 1 | 1), mid = (l + r) >> 1;
    if (mid >= pos)
      modify_san(ls, l, mid, pos);
    else
      modify_san(rs, mid + 1, r, pos);
    pushup(p);
  }

  int query(int p, int l, int r, int L, int R, long long C, int x, int tag) {
    if (p == 1)
      x = max(1ll,
              1ll * (lower_bound(M[p] + 1, M[p] + len[p] + 1, C) - M[p] - 1));
    else {
      while (M[p][x] + tag < C && M[p][x + 1] + tag < C && x < len[p]) ++x;
      while (M[p][x] + tag >= C && x > 1) --x;
    }
    if (l == r) {
      return x - 1 + (M[p][x] + tag < C);
    }
    int res = 0;
    int ls = (p << 1), rs = (p << 1 | 1), mid = (l + r) >> 1;
    if (mid >= L)
      res += query(ls, l, mid, L, R, C, lsuf[p][x], tag + add_tag[p]);
    if (mid < R)
      res += query(rs, mid + 1, r, L, R, C, rsuf[p][x], tag + add_tag[p]);
    return res;
  }
} T;

void init() {
  for (int i = 1; i <= n; i++) {
    b[i].yuan = i;
    b[i].val = a[i];
  }
  for (int i = 1; i <= bel[n]; i++) {
    stable_sort(b + L[i], b + R[i] + 1, [](const node &x, const node &y) {
      if (x.val != y.val)
        return x.val < y.val;
      else
        return x.yuan < y.yuan;
    });
  }
}

node a1[maxn], a2[maxn];

void resort(int i, int l, int r) {
  int t1 = 0, t2 = 0;
  for (int j = L[i]; j <= R[i]; j++) {
    b[j].val = a[b[j].yuan];
    if (b[j].yuan > r || b[j].yuan < l)
      a1[++t1] = b[j];
    else
      a2[++t2] = b[j];
  }
  int p1 = 1, p2 = 1;
  int len = R[i] - L[i] + 1;
  while (p1 + p2 <= len + 1) {
    while (p1 < t1 + 1 && p2 == t2 + 1) {
      b[L[i] + p1 + p2 - 2] = a1[p1];
      ++p1;
    }
    while (p2 < t2 + 1 && p1 == t1 + 1) {
      b[L[i] + p1 + p2 - 2] = a2[p2];
      ++p2;
    }
    if (p1 < t1 + 1 && p2 < t2 + 1) {
      if (a1[p1].val < a2[p2].val) {
        b[L[i] + p1 + p2 - 2] = a1[p1];
        ++p1;
      } else {
        b[L[i] + p1 + p2 - 2] = a2[p2];
        ++p2;
      }
    }
  }
}

void modify_san(int id, int l, int r, int x) {
  for (int i = l; i <= r; i++) a[i] += x;
  resort(id, l, r);
}

void modify(int l, int r, int x) {
  if (bel[l] == bel[r])
    modify_san(bel[l], l, r, x), T.modify_san(1, 1, bel[n], bel[l]);
  else {
    modify_san(bel[l], l, R[bel[l]], x);
    modify_san(bel[r], L[bel[r]], r, x);
    T.modify_san(1, 1, bel[n], bel[l]);
    T.modify_san(1, 1, bel[n], bel[r]);
    T.modify(1, 1, bel[n], bel[l] + 1, bel[r] - 1, x);
    for (int i = bel[l] + 1; i <= bel[r] - 1; i++) tag[i] += x;
  }
}

int query_san(int id, int l, int r, long long C) {
  int res = 0;
  for (int i = l; i <= r; i++) res += (a[i] + tag[id] < C);
  return res;
}

int query(int l, int r, long long C) {
  if (bel[l] == bel[r])
    return query_san(bel[l], l, r, C);
  else {
    int res =
        query_san(bel[l], l, R[bel[l]], C) + query_san(bel[r], L[bel[r]], r, C);
    int qwq = T.query(1, 1, bel[n], bel[l] + 1, bel[r] - 1, C, 0, 0);
    return res + qwq;
  }
}

char t;
int l, r, x;

signed main() {
  ios::sync_with_stdio(false);
  cin.tie(0), cout.tie(0);
  cin >> n;
  q = n;
  B = sqrt(n);
  for (int i = 1; i <= n; i++) {
    bel[i] = (i - 1) / B + 1, L[bel[i]] = R[bel[i] - 1] + 1, R[bel[i]] = i;
  }
  for (int i = 1; i <= n; i++) cin >> a[i];
  init();
  T.build(1, 1, bel[n]);
  while (q--) {
    cin >> t >> l >> r >> x;
    if (t == '0') {
      modify(l, r, x);
    } else {
      cout << query(l, r, 1ll * x * x) << '\n';
    }
  }
  return 0;
}
```

### [P6578 \[Ynoi2019\] 魔法少女网站](https://www.luogu.com.cn/problem/P6578)

单点加，查询区间 $[L,R]$ 内有多少个子区间的 $\max\le x$。

还是先分块，块长为 $B$。对于一个 $x$，我们把块内 $\le x$ 的数设为 $1$，$>x$ 的数设为 $0$，那么问题就变成求出极长的前后缀 $1$ 连续段和块内的答案。因为我们只关心 $x$ 与块内元素的大小关系，所以对于一个块来说，本质不同的 $x$ 只有 $\mathcal O(B)$ 种。我们不妨直接对于每个块处理出这些 $x$ 的答案。

具体地，将排完序的块内数组记为 $b$，处理出 $f[i],pre[i],suf[i]$ 表示区间内的数都 $\le b[i]$ 时的块内答案，最长前缀，最长后缀。我们从小到大加入 $b$，考虑设 $oth[i]$ 表示当 $i$ 作为一个 $1$ 连续段的端点时的另一个端点，加入一个 $b$ 时相当于把一个位置的 $0$ 变成 $1$，合并左右两端点的 $oth$，同时计算答案。

对于修改修改，直接将块暴力重构。

对于查询，散块的答案是好处理的，因此问题相当于要在若干整块中二分出 $x$ 的非严格前驱 $y$，注意到这个等同于上面的问题，分散层叠优化二分即可。

当然，如果把这个题加强到区间加，强制在线，可以用同样的做法解决，而分散层叠的复杂度依然不变，取块长为 $\sqrt n$，时间复杂度 $\mathcal O(n\sqrt n)$。

## 参考文献

[蒋明润《浅谈利用分散层叠算法对经典分块问题的优化》](https://rusunoi.github.io/books/National-Team-Thesis/2020.pdf)
