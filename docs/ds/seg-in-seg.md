author: Chrogeek, HeRaNO, Dev-XYS, Dev-jqe

## 常见用途

在算法竞赛中，我们有时需要维护多维度信息。在这种时候，我们经常需要树套树来记录信息。

## 实现原理

我们考虑用树套树如何实现在二维平面上进行单点修改，区域查询。我们考虑外层的线段树，最底层的 $1$ 到 $n$ 个节点的子树，分别代表第 $1$ 到第 $n$ 行的线段树。那么这些底层的节点对应的父节点，就代表其两个子节点的子树所在的一片区域。

## 空间复杂度

通常情况下，我们不可能对于外层线段树的每一个结点都建立一颗子线段树，空间需求过大。树套树一般采取动态开点的策略。单次修改，我们会涉及到外层线段树的 $\log{n}$ 个节点，且对于每个节点的子树涉及 $\log{n}$ 个节点，所以单次修改产生的空间最多为 $\log^2{n}$ 。

## 时间复杂度

对于询问操作，我们考虑我们在外层线段树上进行 $\log{n}$ 次操作，每次操作会在一个内层线段树上进行 $\log{n}$ 次操作，所以时间复杂度为 $\log^2{n}$ 。
修改操作，与询问操作复杂度相同，也为 $\log^2{n}$ 。

## 经典例题

 [陌上花开](https://www.lydsy.com/JudgeOnline/problem.php?id=3262) 将第一维排序处理，然后用树套树维护第二维和第三维。

## 示例代码

第二维查询

```cpp
int tree_query(int k, int l, int r, int x) {
  if (k == 0) return 0;
  if (1 <= l && r <= sec[x].y) return vec_query(ou_root[k], 1, p, 1, sec[x].z);
  int mid = l + r >> 1, res = 0;
  if (1 <= mid) res += tree_query(ou_ch[k][0], l, mid, x);
  if (sec[x].y > mid) res += tree_query(ou_ch[k][1], mid + 1, r, x);
  return res;
}
```

第二维修改

```cpp
void tree_insert(int &k, int l, int r, int x) {
  if (k == 0) k = ++ou_tot;
  vec_insert(ou_root[k], 1, p, sec[x].z);
  if (l == r) return;
  int mid = l + r >> 1;
  if (sec[x].y <= mid)
    tree_insert(ou_ch[k][0], l, mid, x);
  else
    tree_insert(ou_ch[k][1], mid + 1, r, x);
}
```

第三维查询

```cpp
int vec_query(int k, int l, int r, int x, int y) {
  if (k == 0) return 0;
  if (x <= l && r <= y) return data[k];
  int mid = l + r >> 1, res = 0;
  if (x <= mid) res += vec_query(ch[k][0], l, mid, x, y);
  if (y > mid) res += vec_query(ch[k][1], mid + 1, r, x, y);
  return res;
}
```

第三维修改

```cpp
void vec_insert(int &k, int l, int r, int loc) {
  if (k == 0) k = ++tot;
  data[k]++;
  if (l == r) return;
  int mid = l + r >> 1;
  if (loc <= mid) vec_insert(ch[k][0], l, mid, loc);
  if (loc > mid) vec_insert(ch[k][1], mid + 1, r, loc);
}
```

## 相关算法

面对多维度信息的题目时，如果题目没有要求强制在线，我们还可以考虑 **CDQ 分治** ，或者 **整体二分** 等分治算法，来避免使用高级数据结构，减少代码实现难度。
