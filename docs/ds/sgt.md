author: Ir1d, 0xis-cn

**替罪羊树** 是一种依靠重构操作维持平衡的重量平衡树。替罪羊树会在插入、删除操作时，检测途经的节点，若发现失衡，则将以该节点为根的子树重构。

我们在此实现一个可重的权值平衡树。

```cpp
int cnt,                 // 树中元素总数
    rt,                  // 根节点，初值为 0 代表空树
    w[MAXN],             // 点中的数据 / 权值
    lc[MAXN], rc[MAXN],  // 左右子树
    wn[MAXN],            // 本数据出现次数（为 0 代表已删除）
    s[MAXN],  // 以本节点为根的子树大小（每个节点记 1 次）
    sz[MAXN],  // 以本节点为根的子树大小（每个节点记 wn[k] 次）
    sd[MAXN];  // 已删除节点不计的子树大小（每个节点记 1 次）

void Calc(int k) {
  // 重新计算以 k 为根的子树大小
  s[k] = s[lc[k]] + s[rc[k]] + 1;
  sz[k] = sz[lc[k]] + sz[rc[k]] + wn[k];
  sd[k] = sd[lc[k]] + sd[rc[k]] + (wn[k] != 0);
}
```

## 重构

首先，如前所述，我们需要判定一个节点是否应重构。为此我们引入一个比例常数 $\alpha$（取值在 $(0.5,1)$，一般采用 $0.7$ 或 $0.8$），若某节点的子节点大小占它本身大小的比例超过 $\alpha$，则重构。

另外由于我们采用惰性删除（删除只使用 `wn[k]--`），已删除节点过多也影响效率。因此若未被删除的子树大小占总大小的比例低于 $\alpha$，则亦重构。

```cpp
inline bool CanRbu(int k) {
  // 判断节点 k 是否需要重构
  return wn[k] && (alpha * s[k] <= (double)std::max(s[lc[k]], s[rc[k]]) ||
                   (double)sd[k] <= alpha * s[k]);
}
```

重构分为两个步骤——先中序遍历展开存入数组，再二分重建成树。

```cpp
void Rbu_Flatten(int& ldc, int k) {
  // 中序遍历展开以 k 节点为根子树
  if (!k) return;
  Rbu_Flatten(ldc, lc[k]);
  if (wn[k]) ldr[ldc++] = k;
  // 若当前节点已删除则不保留
  Rbu_Flatten(ldc, rc[k]);
}

int Rbu_Build(int l, int r) {
  // 将 ldr[] 数组内 [l, r) 区间重建成树，返回根节点
  int mid = l + r >> 1;  // 选取中间为根使其平衡
  if (l >= r) return 0;
  lc[ldr[mid]] = Rbu_Build(l, mid);
  rc[ldr[mid]] = Rbu_Build(mid + 1, r);  // 建左右子树
  Calc(ldr[mid]);
  return ldr[mid];
}

void Rbu(int& k) {
  // 重构节点 k 的全过程
  int ldc = 0;
  Rbu_Flatten(ldc, k);
  k = Rbu_Build(0, ldc);
}
```

## 基本操作

几种操作的处理方式较为类似，都规定了 **到达空结点** 与 **找到对应结点** 的行为，之后按 **小于向左、大于向右** 的方式向下递归。

### 插入

插入时，到达空结点则新建节点，找到对应结点则 `wn[k]++`。递归结束后，途经的节点可重构的要重构。

```cpp
void Ins(int& k, int p) {
  // 在以 k 为根的子树内添加权值为 p 节点
  if (!k) {
    k = ++cnt;
    if (!rt) rt = 1;
    w[k] = p;
    lc[k] = rc[k] = 0;
    wn[k] = s[k] = sz[k] = sd[k] = 1;
  } else {
    if (w[k] == p)
      wn[k]++;
    else if (w[k] < p)
      Ins(rc[k], p);
    else
      Ins(lc[k], p);
    Calc(k);
    if (CanRbu(k)) Rbu(k);
  }
}
```

### 删除

惰性删除，到达空结点则忽略，找到对应结点则 `wn[k]--`。递归结束后，可重构节点要重构。

```cpp
void Del(int& k, int p) {
  // 从以 k 为根子树移除权值为 p 节点
  if (!k)
    return;
  else {
    if (w[k] == p) {
      if (wn[k]) wn[k]--;
    } else {
      if (w[k] < p)
        Del(rc[k], p);
      else
        Del(lc[k], p);
    }
    Calc(k);
    if (CanRbu(k)) Rbu(k);
  }
}
```

### upper_bound

返回权值严格大于某值的最小名次。

到达空结点则返回 1，因为只有该子树左边的数均小于查找数才会递归至此。找到对应结点，则返回该节点所占据的最后一个名次 + 1。

```cpp
int MyUprBd(int k, int p) {
  // 在以 k 为根子树中，大于 p 的最小数的名次
  if (!k)
    return 1;
  else if (w[k] == p && wn[k])
    return sz[lc[k]] + 1 + wn[k];
  else if (p < w[k])
    return MyUprBd(lc[k], p);
  else
    return sz[lc[k]] + wn[k] + MyUprBd(rc[k], p);
}
```

以下是反义函数，相当于采用 `std::greater<>` 比较，即返回权值严格小于某值的最大名次。查询一个数的排名可以用 `MyUprGrt(rt, x) + 1`。

```cpp
int MyUprGrt(int k, int p) {
  if (!k)
    return 0;
  else if (w[k] == p && wn[k])
    return sz[lc[k]];
  else if (w[k] < p)
    return sz[lc[k]] + wn[k] + MyUprGrt(rc[k], p);
  else
    return MyUprGrt(lc[k], p);
}
```

### at

给定名次，返回该名次上的权值。到达空结点说明无此名次，找到对应结点则返回其权值。

```cpp
int MyAt(int k, int p) {
  // 以 k 为根的子树中，名次为 p 的权值
  if (!k)
    return 0;
  else if (sz[lc[k]] < p && p <= sz[lc[k]] + wn[k])
    return w[k];
  else if (sz[lc[k]] + wn[k] < p)
    return MyAt(rc[k], p - sz[lc[k]] - wn[k]);
  else
    return MyAt(lc[k], p);
}
```

### 前驱后继

以上两种功能结合即可。

```cpp
inline int MyPre(int k, int p) { return MyAt(k, MyUprGrt(k, p)); }
inline int MyPost(int k, int p) { return MyAt(k, MyUprBd(k, p)); }
```
