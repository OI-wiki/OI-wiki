[静态区间 k 小值 (POJ 2104 K-th Number)](http://poj.org/problem?id=2104) 的问题可以用 [主席树](./persistent-seg.md) 在 $O(n\log n)$ 的时间复杂度内解决。

如果区间变成动态的呢？即，如果还要求支持一种操作：单点修改某一位上的值，又该怎么办呢？

??? note "例题 [二逼平衡树（树套树）](https://loj.ac/problem/106)"


??? note "例题 [ZOJ 2112 Dynamic Rankings](https://zoj.pintia.cn/problem-sets/91827364500/problems/91827365611)"


如果用 [线段树套平衡树](./balanced-in-seg.md) 中所论述的，用线段树套平衡树，即对于线段树的每一个节点，对于其所表示的区间维护一个平衡树，然后用二分来查找 $k$ 小值。由于每次查询操作都要覆盖多个区间，即有多个节点，但是平衡树并不能多个值一起查找，所以时间复杂度是 $O(n\log^3 n)$，并不是最优的。

思路是，把二分答案的操作和查询小于一个值的数的数量两种操作结合起来。最好的方法是使用 **线段树套主席树**。

说是主席树其实不准确，因为并不是对线段树的可持久化，各个线段树之间也没有像主席树各版本之间的强关联性，所以称为 **动态开点权值线段树** 更为确切。

思路类似于线段树套平衡树，即对于线段树所维护的每个区间，建立一个动态开点权值线段树，表示其所维护的区间的值。

在修改操作进行时，先在线段树上从上往下跳到被修改的点，删除所经过的点所指向的动态开点权值线段树上的原来的值，然后插入新的值，要经过 $O(\log n)$ 个线段树上的节点，在动态开点权值线段树上一次修改操作是 $O(\log n)$ 的，所以修改操作的时间复杂度为 $O(\log^2 n)$。

在查询答案时，先取出该区间覆盖在线段树上的所有点，然后用类似于静态区间 $k$ 小值的方法，将这些点一起向左儿子或向右儿子跳。如果所有这些点左儿子存储的值大于等于 $k$，则往左跳，否则往右跳。由于最多只能覆盖 $O(\log n)$ 个节点，所以最多一次只有这么多个节点向下跳，时间复杂度为 $O(\log^2 n)$。

由于线段树的常数较大，在实现中往往使用常数更小且更方便处理前缀和的 **树状数组** 实现。

给出一种代码实现：

```cpp
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <map>
#include <set>
#define LC o << 1
#define RC o << 1 | 1
using namespace std;
const int maxn = 1000010;
int n, m, a[maxn], u[maxn], x[maxn], l[maxn], r[maxn], k[maxn], cur, cur1, cur2,
    q1[maxn], q2[maxn], v[maxn];
char op[maxn];
set<int> ST;
map<int, int> mp;

struct segment_tree  // 封装的动态开点权值线段树
{
  int cur, rt[maxn * 4], sum[maxn * 60], lc[maxn * 60], rc[maxn * 60];

  void build(int& o) { o = ++cur; }

  void print(int o, int l, int r) {
    if (!o) return;
    if (l == r && sum[o]) printf("%d ", l);
    int mid = (l + r) >> 1;
    print(lc[o], l, mid);
    print(rc[o], mid + 1, r);
  }

  void update(int& o, int l, int r, int x, int v) {
    if (!o) o = ++cur;
    sum[o] += v;
    if (l == r) return;
    int mid = (l + r) >> 1;
    if (x <= mid)
      update(lc[o], l, mid, x, v);
    else
      update(rc[o], mid + 1, r, x, v);
  }
} st;

// 树状数组实现
inline int lowbit(int o) { return (o & (-o)); }

void upd(int o, int x, int v) {
  for (; o <= n; o += lowbit(o)) st.update(st.rt[o], 1, n, x, v);
}

void gtv(int o, int* A, int& p) {
  p = 0;
  for (; o; o -= lowbit(o)) A[++p] = st.rt[o];
}

int qry(int l, int r, int k) {
  if (l == r) return l;
  int mid = (l + r) >> 1, siz = 0;
  for (int i = 1; i <= cur1; i++) siz += st.sum[st.lc[q1[i]]];
  for (int i = 1; i <= cur2; i++) siz -= st.sum[st.lc[q2[i]]];
  // printf("j %d %d %d %d\n",cur1,cur2,siz,k);
  if (siz >= k) {
    for (int i = 1; i <= cur1; i++) q1[i] = st.lc[q1[i]];
    for (int i = 1; i <= cur2; i++) q2[i] = st.lc[q2[i]];
    return qry(l, mid, k);
  } else {
    for (int i = 1; i <= cur1; i++) q1[i] = st.rc[q1[i]];
    for (int i = 1; i <= cur2; i++) q2[i] = st.rc[q2[i]];
    return qry(mid + 1, r, k - siz);
  }
}

/*
线段树实现
void build(int o,int l,int r)
{
    st.build(st.rt[o]);
    if(l==r)return;
    int mid=(l+r)>>1;
    build(LC,l,mid);
    build(RC,mid+1,r);
}
void print(int o,int l,int r)
{
    printf("%d %d:",l,r);
    st.print(st.rt[o],1,n);
    printf("\n");
    if(l==r)return;
    int mid=(l+r)>>1;
    print(LC,l,mid);
    print(RC,mid+1,r);
}
void update(int o,int l,int r,int q,int x,int v)
{
    st.update(st.rt[o],1,n,x,v);
    if(l==r)return;
    int mid=(l+r)>>1;
    if(q<=mid)update(LC,l,mid,q,x,v);
    else update(RC,mid+1,r,q,x,v);
}
void getval(int o,int l,int r,int ql,int qr)
{
    if(l>qr||r<ql)return;
    if(ql<=l&&r<=qr){q[++cur]=st.rt[o];return;}
    int mid=(l+r)>>1;
    getval(LC,l,mid,ql,qr);
    getval(RC,mid+1,r,ql,qr);
}
int query(int l,int r,int k)
{
    if(l==r)return l;
    int mid=(l+r)>>1,siz=0;
    for(int i=1;i<=cur;i++)siz+=st.sum[st.lc[q[i]]];
    if(siz>=k)
    {
        for(int i=1;i<=cur;i++)q[i]=st.lc[q[i]];
        return query(l,mid,k);
    }
    else
    {
        for(int i=1;i<=cur;i++)q[i]=st.rc[q[i]];
        return query(mid+1,r,k-siz);
    }
}
*/
int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; i++) scanf("%d", a + i), ST.insert(a[i]);
  for (int i = 1; i <= m; i++) {
    scanf(" %c", op + i);
    if (op[i] == 'C')
      scanf("%d%d", u + i, x + i), ST.insert(x[i]);
    else
      scanf("%d%d%d", l + i, r + i, k + i);
  }
  for (set<int>::iterator it = ST.begin(); it != ST.end(); it++)
    mp[*it] = ++cur, v[cur] = *it;
  for (int i = 1; i <= n; i++) a[i] = mp[a[i]];
  for (int i = 1; i <= m; i++)
    if (op[i] == 'C') x[i] = mp[x[i]];
  n += m;
  // build(1,1,n);
  for (int i = 1; i <= n; i++) upd(i, a[i], 1);
  // print(1,1,n);
  for (int i = 1; i <= m; i++) {
    if (op[i] == 'C') {
      upd(u[i], a[u[i]], -1);
      upd(u[i], x[i], 1);
      a[u[i]] = x[i];
    } else {
      gtv(r[i], q1, cur1);
      gtv(l[i] - 1, q2, cur2);
      printf("%d\n", v[qry(1, n, k[i])]);
    }
  }
  return 0;
}
```
