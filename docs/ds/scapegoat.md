# 替罪羊树

**替罪羊树**是一种依靠重构操作维持平衡的重量平衡树。替罪羊树会在插入、删除操作时，检测途经的所有节点，若发现失衡，则将以该节点为根的子树重构。

我们在此实现一个可重的权值平衡树。

``` cpp
int cnt, // 树中元素总数
  rt, // 根节点，初值为 0 代表空树
  w[MAXN], // 点中的数据/权值
 lc[MAXN], rc[MAXN], // 左右子树
 wn[MAXN], // 本数据出现次数（为 0 代表已删除）
  s[MAXN], // 以本节点为根的子树大小
 sd[MAXN]; // 已删除节点不计的子树大小
```

## 重构

首先，如前所述，我们需要判定一个节点是否需要重构。为此我们引入一个比例常数 $\alpha$（取值在 $$(0.5,1)），如某节点的子节点大小占它本身大小的比例超过 $\alpha$，则重构。

另外由于我们采用惰性删除（删除只使用 `wn[i]--`），已删除节点过多也影响效率。因此如果未被删除的子树大小占子树总大小的比例低于 $\alpha$，则亦重构。

``` cpp
inline bool CanRbu(int k) {
// 判断节点 k 是否需要重构
 return wn[k] && (alpha * s[k] <= (double)std::max(s[lc[k]], s[rc[k]])
  || alpha * s[k] >= (double)sd[k]);
}
```

重构分为两个步骤——先前序遍历展开存入数组，再二分重建成树。

``` cpp
void Rbu_Flatten(int& ldc, int k) {
// 前序遍历展开以 k 节点为根子树
 if(!k) return;
 Rbu_Flatten(ldc, lc[k]);
 if(wn[k]) ldr[ldc++] = k;
// 若当前节点已删除则不保留
 Rbu_Flatten(ldc, rc[k]);
}

int Rbu_Build(int l, int r) {
// 将数组内 [l, r) 区间重建成树
 int mid = l + r >> 1;
 if(l >= r) return 0;
 lc[ldr[mid]] = Rbu_Build(l, mid);
 rc[ldr[mid]] = Rbu_Build(mid + 1, r);
 if(l + 1 == r) s[ldr[mid]] = sd[ldr[mid]] = wn[ldr[mid]];
 else Calc(ldr[mid]);
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

### 插入

插入时，从根节点向下寻找插入元素位置。如没有相同元素则新建节点，如有则直接 `wn[k]++`。最后，途经的可重构节点进行重构。

``` cpp
void Ins(int& k, int p) {
// 在以 k 为根的子树内添加权值为 p 节点
 if(!k) { k = ++cnt; if(!rt) rt = 1;
  w[k] = p; lc[k] = rc[k] = 0; wn[k] = s[k] = sd[k] = 1;
 } else {
  if(w[k] == p) wn[k]++;
  else if(w[k] < p) Ins(rc[k], p);
  else Ins(lc[k], p);
  Calc(k); if(CanRbu(k)) Rbu(k);
 }
}
```

### 删除

惰性删除，可以采用 `wn[k]--`。在最后沿途可重构节点要重构。

``` cpp
void Del(int& k, int p) {
// 从以 k 为根子树移除权值为 p 节点
 if(!k) return; else {
  sd[k]--; if(w[k] == p) { if(wn[k]) wn[k]--; }
   else {
    if(w[k] < p) Del(rc[k], p);
    else Del(lc[k], p);
    Calc(k);
   }
 }
 if(CanRbu(k)) Rbu(k);
}
```

### upper_bound

返回权值严格大于某值的最小数的名次。每到一个节点，若查找值等于该节点权值，则返回该节点之后的名次。小于则向左走，大于则向右走。

``` cpp
int MyUprBd(int k, int p) {
// 在以 k 为根子树中，大于 p 的最小数的名次
 if(!k) return 1;
 else if(w[k] == p && wn[k]) return sd[lc[k]] + 1 + wn[k];
 else if(p < w[k]) return MyUprBd(lc[k], p);
 else return sd[lc[k]] + wn[k] + MyUprBd(rc[k], p);
}
 
int MyUprGrt(int k, int p) {
// 反义的函数，相当于采用 std::greater<> 比较
 if(!k) return 0;
 else if(w[k] == p && wn[k]) return sd[lc[k]];
 else if(w[k] < p) return sd[lc[k]] + wn[k] + MyUprGrt(rc[k], p);
 else return MyUprGrt(lc[k], p);
}
```

### at

给定名次，返回该名次上的权值。将名次与节点左子树大小及本节点重复次数比较，同样小于向左，大于向右。

``` cpp
int MyAt(int k, int p) {
// 以 k 为根的子树中，名次为 p 的权值
 if(!k) return 0;
 else if(sd[lc[k]] < p && p <= sd[lc[k]] + wn[k]) return w[k];
 else if(sd[lc[k]] + wn[k] < p) return MyAt(rc[k], p - sd[lc[k]] - wn[k]);
 else return MyAt(lc[k], p);
}
```

### 前驱后继

以上两种功的组合。

``` cpp
inline int  MyPre(int k, int p) { return MyAt(k, MyUprGrt(k, p)); }
inline int MyPost(int k, int p) { return MyAt(k, MyUprBd (k, p)); }
```
