author: Dev-jqe, HeRaNO, huaruoji

## 常见用途

在算法竞赛中，我们有时需要维护多维度信息。在这种时候，我们经常需要树套树来记录信息。当需要维护前驱，后继，第 $k$ 大，某个数的排名，或者插入删除的时候，我们通常需要使用平衡树来满足我们的需求，即线段树套平衡树。

## 实现原理

我们以 **二逼平衡树** 为例，来解释实现原理。

关于树套树的构建，我们对于外层线段树正常建树，对于线段树上的某一个节点，建立一棵平衡树，包含该节点所覆盖的序列。具体操作时我们可以将序列元素一个个插入，每经过一个线段树节点，就将该元素加入到该节点的平衡树中。

操作一，求某区间中某值的排名：我们对于外层线段树正常操作，对于在某区间中的节点的平衡树，我们返回平衡树中比该值小的元素个数，合并区间时，我们将小的元素个数求和即可。最后将返回值 $+1$，即为某值在某区间中的排名。

操作二，求某区间中排名为 $k$ 的值：我们可以采用二分策略。因为一个元素可能存在多个，其排名为一区间，且有些元素原序列不存在。所以我们采取和操作一类似的思路，我们用小于该值的元素个数作为参考进行二分，即可得解。

操作三，将某个数替换为另外一个数：我们只要在所有包含某数的平衡树中删除某数，然后再插入另外一个数即可。外层依旧正常线段树操作。

操作四，求某区间中某值的前驱：我们对于外层线段树正常操作，对于在某区间中的节点的平衡树，我们返回某值在该平衡树中的前驱，线段树的区间结果合并时，我们取最大值即可。

## 空间复杂度

我们每个元素加入 $O(\log n)$ 个平衡树，所以空间复杂度为 $O((n + q)\log{n})$。

## 时间复杂度

- 对于 1，3，4 操作，我们考虑我们在外层线段树上进行 $O(\log{n})$ 次操作，每次操作会在一个内层平衡树树上进行 $O(\log{n})$ 次操作，所以时间复杂度为 $O(\log^2{n})$。
- 对于 2 操作，多一个二分过程，为 $O(\log^3{n})$。

## 经典例题

[二逼平衡树](https://loj.ac/problem/106) 外层线段树，内层平衡树。

## 示例代码

平衡树部分代码请参考 [Splay](./splay.md) 等其他条目。

操作一：

```cpp
int vec_rank(int k, int l, int r, int x, int y, int t) {
  if (x <= l && r <= y) {
    return spy[k].chk_rank(t);
  }
  int mid = l + r >> 1;
  int res = 0;
  if (x <= mid) res += vec_rank(k << 1, l, mid, x, y, t);
  if (y > mid) res += vec_rank(k << 1 | 1, mid + 1, r, x, y, t);
  if (x <= mid && y > mid) res--;
  return res;
}
```

操作二：

```cpp
int el = 0, er = 100000001, emid;
while (el != er) {
  emid = el + er >> 1;
  if (vec_rank(1, 1, n, tl, tr, emid) - 1 < tk)
    el = emid + 1;
  else
    er = emid;
}
printf("%d\n", el - 1);
```

操作三：

```cpp
void vec_chg(int k, int l, int r, int loc, int x) {
  int t = spy[k].find(dat[loc]);
  spy[k].dele(t);
  spy[k].insert(x);
  if (l == r) return;
  int mid = l + r >> 1;
  if (loc <= mid) vec_chg(k << 1, l, mid, loc, x);
  if (loc > mid) vec_chg(k << 1 | 1, mid + 1, r, loc, x);
}
```

操作四：

```cpp
int vec_front(int k, int l, int r, int x, int y, int t) {
  if (x <= l && r <= y) return spy[k].chk_front(t);
  int mid = l + r >> 1;
  int res = 0;
  if (x <= mid) res = max(res, vec_front(k << 1, l, mid, x, y, t));
  if (y > mid) res = max(res, vec_front(k << 1 | 1, mid + 1, r, x, y, t));
  return res;
}
```

## 相关算法

面对多维度信息的题目时，如果题目没有要求强制在线，我们还可以考虑 [CDQ 分治](../misc/cdq-divide.md)，或者 [整体二分](../misc/parallel-binsearch.md) 等分治算法，来避免使用高级数据结构，减少代码实现难度。
